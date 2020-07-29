int greenLED = 3;
int redLED = 4;
int pir1 = 8;
int pir2 = 10;
int initTime = 60;
int sanitTime = 6;
int exitTime = 2;
int relayPin = 12;
int counter = 0;
int pirState = LOW;
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
  Serial.begin(9600);
}

void loop()
{
  pirInitialization();
  //Turn on green LED to signal ready
  while(1){
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, LOW);
   //Wait for sensor reading. 

    if(digitalRead(pir1) == HIGH || digitalRead(pir2) == HIGH){
      if(pirState == LOW){
        Serial.print("Motion detected. Count:  ");
        Serial.println(counter);
        counter++;
        startSanitization();
        pirState = HIGH;
      }
      else{
        pirState = LOW;
      }
  }}
    
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
