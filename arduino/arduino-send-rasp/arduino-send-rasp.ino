char dataSerial;

void setup() {
    Serial.begin(9600);
}
void loop() {
    
    delay(1000);

    if(Serial.available())
    {
     
      dataSerial = Serial.read(); //Conduct a serial read
      Serial.println(dataSerial);
    }
}
