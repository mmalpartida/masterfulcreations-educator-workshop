"use strict";

var Cylon = require("cylon");
var playing = false;
var playingDone = false;
var minAngle = 30;
var maxAngle = 150;
var maxAngleY = 180;
var handResetX = 90;
var handResetY = 90;


Cylon.robot({
	connections: {
		arduino: {adaptor: 'firmata', port:'COM6'},
		leapmotion: { adaptor: 'leapmotion' },
		audio: { adaptor: 'audio'}
	},

	devices :{
		servo1: { driver: 'servo', pin: 1, connection:'arduino' },
		servo2: { driver: 'servo', pin: 10, connection:'arduino' },
		leapmotion: { driver: 'leapmotion', connection: 'leapmotion'},
		audio: { driver: 'audio', connection: 'audio'}
	},

	work: function(my){
		
		function toggleSound(){
			if(!playing){
				my.audio.play('./smaug-edit.mp3');
				playing = true;	
			}else{
				my.audio.stop();
				playing = false;
			}
			
		}

		my.servo1.angle(handResetX);
		my.servo2.angle(handResetY);


		my.leapmotion.on('hand', function(hand){
			
			var rawValueX = hand.palmPosition[0];
			var rawValueY = hand.palmPosition[1];
			//var rawValueZ = hand.palmPosition[2];

			var handPosX = Math.round(rawValueX + 90);
			var handPosY = Math.round(rawValueY);

			//console.log(Math.round(rawValueY));
			

			if(handPosX > maxAngle){

			handPosX = maxAngle;

			}else if(handPosX < 0){

			handPosX = minAngle;

			}

			if(handPosY > maxAngleY){

			handPosY = maxAngleY;
			}else if(handPosY < 0){

			handPosY = minAngle;

			}

			 //console.log(handPosX, handPosY);

			 my.servo1.angle(handPosX);
			 my.servo2.angle(handPosY);
	
		});
		
		my.leapmotion.on('frame', function(frame){
			
			if(frame.hands.length == 0){
				my.servo1.angle(handResetX);
				my.servo2.angle(handResetY);
				
			}
			
		});
		
		
		my.leapmotion.on('gesture', function(gesture){
			
			if(gesture.type == 'screenTap'){
			
				toggleSound();
			}
			
			
		});
		
	}

}).start();
