long randNumber;
long prevNumber = 0;

// digital pin 2 has a pushbutton attached to it. Give it a name:
int leftArrow = A1;
int spaceBar = A0;
int rightArrow = 0;

int correctAnswer = 5;
int wrongAnswer = 9;

bool gameOn = false;

void setup(){
  Serial.begin(9600);

   pinMode(leftArrow, INPUT);
   pinMode(rightArrow, INPUT);
   pinMode(spaceBar, INPUT);

   pinMode(correctAnswer, OUTPUT);
   pinMode(wrongAnswer, OUTPUT);

   randNumber = random(1, 3);


}

void loop() {
 

while (!gameOn){

  
  Serial.println("Game initializing"); 

  digitalWrite(correctAnswer, LOW); // turn the green LED on pin 3 on
    digitalWrite(wrongAnswer, LOW);  // turn the red LED on pin 4 off
    
  randNumber = random(1, 4);

  if(randNumber == prevNumber){
    randNumber = random(1, 4);
  }
  
gameOn = true;

}


while (gameOn){

if(randNumber > 3){
  randNumber = 3;
}

prevNumber = randNumber;

 
Serial.println("Game on!"); 
 int guess;

  // read the input pin:
  int ans1 = digitalRead(leftArrow);
  int ans2 = digitalRead(rightArrow);
  int ans3 = digitalRead(spaceBar);


if (ans1 == HIGH){

guess = 1;

Serial.println("You picked 1"); 

}else if (ans2 == HIGH){

guess = 2;
// guess is one
Serial.println("You picked 2"); 
}else if (ans3 == HIGH){

guess = 3;
// guess is one
Serial.println("You picked 3"); 
}else{

  guess = 0;
}



  Serial.println(randNumber); 

if (guess == randNumber){
  
    digitalWrite(correctAnswer, HIGH); 
    digitalWrite(wrongAnswer, LOW);  

    Serial.println("Youre Right"); 
    delay(2000);
gameOn = false;
}else if (guess != randNumber && guess != 0){
  
    digitalWrite(correctAnswer, LOW); // turn the green LED on pin 3 on
    digitalWrite(wrongAnswer, HIGH);  // turn the red LED on pin 4 off

Serial.println("You are wrong!"); 
 gameOn = false; 
  delay(2000);
}





  
}

delay(5000);
 
}
