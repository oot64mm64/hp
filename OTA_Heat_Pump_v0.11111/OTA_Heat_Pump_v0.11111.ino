int ledState = LOW;  // ledState used to set the LED
String input;
String password = "M";

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  // Initialize the LED_BUILTIN pin as an output
  digitalWrite(LED_BUILTIN, HIGH); //Turn LED OFF
  Serial.begin(115200);
}

void loop() {
  while(Serial.available()>0){
    input = Serial.readString();
    Serial.print(input);
    if(input == password){
      ledState = not(ledState);
      digitalWrite(LED_BUILTIN,  ledState);
    }
  }
}
