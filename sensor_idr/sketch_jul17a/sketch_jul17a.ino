int ledyellow = 7;
int ledgreen = 6;
int ledred = 5;
int sensorPin = A5;

void setup() {
  Serial.begin(9600);
  pinMode(ledred, OUTPUT);
  pinMode(ledyellow, OUTPUT);
  pinMode(ledgreen, OUTPUT);
}

void loop() {
  lowlight();
}

void lowlight() {
  int sensorValue = analogRead(sensorPin);
  Serial.print("LDR Value = ");
  Serial.println(sensorValue);

  if (sensorValue >= 360) {
    digitalWrite(ledyellow, HIGH);

    if (sensorValue >= 450) {
      digitalWrite(ledgreen, HIGH);
    }
    else {
      digitalWrite(ledgreen, LOW);
    }

    if (sensorValue >= 600) {
      digitalWrite(ledred, HIGH);
    }
   	else{
    digitalWrite(ledred, LOW);
    }
  }
  else {
    digitalWrite(ledyellow, LOW);
  }
}
