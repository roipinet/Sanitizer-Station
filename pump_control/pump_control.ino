int greenLED = 2;
int redLED = 3;
int initTime = 60;
int sanitTime = 6;
int exitTime = 2;
int relayPin = 4;
int counter = 0;
int ultraTrigger = 7;
int ultraEcho = 6;
int height = 120;
void setup()
{
  //Pin mode for LEDS
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  //Pin mode for ultrasonic
  pinMode(ultraTrigger, OUTPUT);
  pinMode(ultraEcho, INPUT);
  digitalWrite(ultraTrigger, LOW);
  //Pin mode for relay
  pinMode(relayPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  //pirInitialization();
  //Turn on green LED to signal ready
  while(1){
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, LOW);
   //Start sensing
   digitalWrite(ultraTrigger, HIGH);
   delayMicroseconds(10);
   digitalWrite(ultraTrigger, LOW);
   int travelTime = pulseIn(ultraEcho, HIGH);
   //Calculate distance
   int distance = travelTime/59;
   //Report back distance
   Serial.print("Distance: ");
   Serial.print(distance);
   Serial.println(" cm");
   delay(100);
    if(distance < height){
        Serial.print("Motion detected. Count:  ");
        Serial.println(counter);
        counter++;
        startSanitization();
      }
  }
    
}

void pirInitialization(){
    //Blink both lights to wait for PIR stabilization
  Serial.println("Initializing... ");
  for(int i = 0; i < initTime; i++){
    //Turn on lights
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, HIGH);
    //Wait for 1/2 second
    delay(500);
    //Turn off lights
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, LOW);
    //Wait for 1/2 second
    delay(500);
    Serial.print("Initializing... ");
    Serial.println(i);
  }
}

void startSanitization(){
  //Turn off green light
  digitalWrite(greenLED, LOW);
  //Turn on red light
  digitalWrite(redLED, HIGH);
  //Turn on pump
  //Wait for person to get in.
  delay(2000);
  Serial.println("Turning on pump...");
  digitalWrite(relayPin, HIGH);
  delay(sanitTime*1000-100);
  digitalWrite(relayPin, LOW);
  Serial.println("Turning off pump..."); 
  delay(exitTime*1000-100);
  digitalWrite(relayPin, LOW);
  //Turn off red light
  digitalWrite(redLED, LOW);
  //Turn on green light
  digitalWrite(greenLED, HIGH);
}
