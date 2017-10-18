String read_buffer;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Ready");
}

void loop() {
  if (Serial.available() > 0) {
    read_buffer = Serial.readStringUntil('\n');
    // Takes the corresponding action according to the first char of the String.
    take_action(read_buffer.charAt(0));
    read_buffer = "";
    Serial.flush();
  }
  delay(100);
}

void take_action(char action) {
    switch (action) {
      case 'l':
        // Turn left.
        Serial.println("left");
        break;
      case 'r':
        // Turn right.
        Serial.println("right");
        break;
    }
}
