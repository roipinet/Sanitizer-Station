int greenLED = 3;
int redLED = 1;
int pir1 = 8;
int pir2 = 10;
int initTime = 60;
int sanitTime = 6;
int exitTime = 2;
int relayPin = 12;
void setup()
{
  //Pin mode for LEDS
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  //Pin mode for PIRs
  pinMode(pir1, INPUT);
  pinMode(pir2, INPUT);
  //Pin mode for relay
  pinMode(relayPin, OUTPUT);
}

void loop()
{
  pirInitialization();
  //Turn on green LED to signal ready
  digitalWrite(greenLED, HIGH);
   //Wait for sensor reading. 

    if(digitalRead(pir1) == HIGH || digitalRead(pir2) == HIGH){
    //Motion detected
    Serial.println("Motion detected");
    startSanitization();
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
    Serial.println("Initializing... " + i);
  }
}

void startSanitization(){
  //Turn off green light
  digitalWrite(greenLED, LOW);
  //Turn on red light
  digitalWrite(redLED, HIGH);
  //Turn on pump
  digitalWrite(relayPin, HIGH);
  delay(sanitTime*1000-100);
  digitalWrite(relayPin, LOW);
  //Wait for sanitization to complete
  
  //Turn off pump
  digitalWrite(relayPin, HIGH);
  delay(exitTime*1000-100);
  digitalWrite(relayPin, LOW);
  //Wait for person to get out
  
  //Turn off red light
  digitalWrite(redLED, LOW);
  //Turn on green light
  digitalWrite(greenLED, HIGH);
}
