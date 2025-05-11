// Function to check for incoming SMS
void checkSMS() {
  mySerial.println("AT+CMGL=\"REC UNREAD\"");
  delay(500);
  while (mySerial.available()) {
    String line = mySerial.readStringUntil('\n');
    if (line.startsWith("+CMGL:")) {
      String message = mySerial.readStringUntil('\n');
      message.trim(); // Remove leading/trailing whitespace
      
      if (message == "ON") {
        // Send success SMS
        sendSMS("+8801719905286", "Starting...");

        // Indicate receipt of 'ON' SMS
        Serial.println("Received 'ON' SMS");

        // Allow movement
        // allowMovement = true;
      } else if (message == "STOP") {
        // Send stop SMS
        sendSMS("+8801719905286", "Stopping...");

        // Indicate receipt of 'STOP' SMS
        Serial.println("Received 'STOP' SMS");

        // Prevent movement
        // allowMovement = false;
      }
    }
  }
}

// Function to send an SMS
void sendSMS(String phoneNumber, String message) {
  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  delay(100);
  mySerial.println("AT+CMGS=\"" + phoneNumber + "\""); // Set the phone number
  delay(100);
  mySerial.print(message); // Set the SMS body
  delay(100);
  mySerial.println((char)26); // End the SMS by sending Ctrl+Z
  delay(100);
}

// Function to configure SIM900 module
void configureSIM900() {
  // Check SIM900 module response
  sendATCommand("AT");
  delay(1000);

  // Configure SMS mode
  sendATCommand("AT+CMGF=1");
  delay(1000);

  // Set SMS indications to come through serial
  sendATCommand("AT+CNMI=1,2,0,0,0");
  delay(1000);
}

// Function to send AT command to SIM900 module
void sendATCommand(String command) {
  mySerial.println(command);
  delay(100);
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
}

void updateSerial()
{
  delay(500);
  // while (Serial.available()) 
  // {
  //   mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  // }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
  // Serial.println(sms);
  
}
