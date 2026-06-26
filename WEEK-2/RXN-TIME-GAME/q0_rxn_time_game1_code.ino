// C++ code
//
const int red = 7;
const int blue = 6;
const int green = 5;
const int button = 2;

unsigned long startTime;
unsigned long endTime;
unsigned long reactionTime;

int buttonState=1;

void setup()
{
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(button ,INPUT_PULLUP);
  Serial.begin(9600);
  
randomSeed(analogRead(A0));
  
Serial.println("Reaction Time Game Started");
  
}

void loop()
{
  digitalWrite(red, LOW);
  digitalWrite(blue, LOW);
  digitalWrite(green, LOW); 
  delay(1000);
  
  int blinks = random(5, 15);
  
  for(int i = 0; i < blinks; i++) {

    int randomLED = random(6,8);      
    int randomTime = random(200, 1000);
    
    digitalWrite(randomLED, HIGH);

    delay(randomTime);

    digitalWrite(randomLED, LOW);

    delay(200);}
    
  Serial.println("START!");

  digitalWrite(green, HIGH);
  
  startTime = millis();
    
   while(digitalRead(button) == HIGH) {
    
  }
    
   endTime = millis();


  reactionTime = endTime - startTime;
    
  Serial.print("Your Reaction Time: ");
  Serial.print(reactionTime);
  Serial.println(" ms");


  digitalWrite(green, LOW);


  delay(3000);
      
}