// C++ code
//
int led_green = 5 ;
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(led_green, OUTPUT);
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(led_green, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(led_green, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
}