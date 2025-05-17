const int servoPin = 9;           /* Servo control pin */
const int potPin = A0;            /* Potentiometer connected to analog pin A0 */
const int periodTicks = 5000;     /* 20 ms = 5000 ticks (fixed for servo control) */
const int minPulseWidthTicks = 375;  /* 1 ms pulse width = 375 ticks */
const int maxPulseWidthTicks = 750;  /* 2 ms pulse width = 750 ticks */

void setup() {
  Serial.begin(9600);
  pinMode(servoPin, OUTPUT);

  /* Set Timer1 to Normal Mode */
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= 0b00000011;             /* prescaler = 64 */

  TCNT1 = 0;  /* initially reset counter */
}

void loop() {
  int potValue = analogRead(potPin);  // Read the potentiometer value (0-1023)
  
  // Map the potentiometer value to pulse width (375 to 750 ticks)
  int pulseWidthTicks = map(potValue, 0, 1023, minPulseWidthTicks, maxPulseWidthTicks);

  TCNT1 = 0;                        /* Start timer from 0 (TCNT1 = 0) */
  digitalWrite(servoPin, HIGH);

  while (TCNT1 < pulseWidthTicks) {  /* Wait until the mapped pulse width is reached */
    // Serial.println("high1");      // You can remove this line if you don't want to flood the serial monitor
  }

  digitalWrite(servoPin, LOW);

  while (TCNT1 < periodTicks) {      /* Wait until the full 20 ms period is complete */
    // Serial.println("low1");       // You can remove this line as well
  }

  delay(10);  // Small delay for stability (you can adjust this value if needed)
}
