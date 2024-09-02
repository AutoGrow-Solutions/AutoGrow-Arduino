#define EC_PIN A0  // The analog pin for the EC sensor
#define VREF 3.3  // The reference voltage of the Arduino (3.3V)
#define EC_CALIBRATION 12880  // Calibration solution value in µS/cm (12.88 mS/cm)

float rawECValue = 0.0;
float calibrationCoefficient = 1.0;  // This will be adjusted during calibration

void setup() {
  Serial.begin(9600);
  pinMode(EC_PIN, INPUT);
  Serial.println("Type 'up' to increase or 'down' to decrease the calibration coefficient.");
}

void loop() {
  // Read EC value
  rawECValue = analogRead(EC_PIN);
  float voltage = (rawECValue / 1024.0) * VREF;
  float EC = (voltage * 1000) / calibrationCoefficient;  // Convert voltage to EC value

  // Display the raw and adjusted EC values
  Serial.print("Raw EC Value: ");
  Serial.print(rawECValue);
  Serial.print("  |  EC: ");
  Serial.print(EC, 2);
  Serial.println(" µS/cm");

  // Read user input from Serial Monitor
  if (Serial.available() > 0) {
    String input = Serial.readString();

    if (input.startsWith("up")) {
      calibrationCoefficient += 0.1;  // Increase calibration coefficient
      Serial.print("Calibration Coefficient increased to: ");
      Serial.println(calibrationCoefficient);
    } else if (input.startsWith("down")) {
      calibrationCoefficient -= 0.1;  // Decrease calibration coefficient
      Serial.print("Calibration Coefficient decreased to: ");
      Serial.println(calibrationCoefficient);
    }
  }

  delay(1000);
}
