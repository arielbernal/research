void setup() {
  Serial.begin(57600);
}

void loop() {
  while(!Serial.available());
  char ch = (char) Serial.read();
  switch (ch) {
    case '1': Serial.println("Got 1"); break;
    case '2': Serial.println("Got 2"); break;
    default:
      Serial.println("Invalid option");
  }
}
