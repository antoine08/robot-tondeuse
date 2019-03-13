int motor_coupe = 2;
void setup() {
 Serial.begin (9600);
 pinMode(motor_coupe, OUTPUT);
}

void loop() {
digitalWrite(motor_coupe, HIGH);
delay(10000);
digitalWrite(motor_coupe, LOW);
delay(500);
}
