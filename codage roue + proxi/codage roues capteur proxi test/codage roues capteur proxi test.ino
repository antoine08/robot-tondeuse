/***************************************************************************
    Ultrasonic sensor                                                      *
        VCC: +5VDC                                                         *
        Trig : Trigger (INPUT) - Pin11                                     *
        Echo: Echo (OUTPUT) - Pin 12                                       *
        GND: GND                                                           *
 ***************************************************************************/
//Define Pins ultrasonic****************************************************
 
int trigPin = 12;    // Trigger
int echoPin = 11;    // Echo
long duration, cm;

//Define Pins motors********************************************************

//Motor A (left)

int enableA = 5;
int MotorA1 = 6;
int MotorA2 = 7;
 
//Motor B (right)
int enableB = 8;
int MotorB1 = 9;
int MotorB2 = 10;

/***************************************************************************
 * the setup () initialization function which is executed once at startup.*
 ***************************************************************************/
 
void setup() {

  
//Serial Port begin*********************************************************
   
  Serial.begin (9600);
  
//Define inputs and outputs*************************************************
   
  // ultrasonic 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Motors
  pinMode (enableA, OUTPUT);
  pinMode (MotorA1, OUTPUT);
  pinMode (MotorA2, OUTPUT);  
  
  pinMode (enableB, OUTPUT);
  pinMode (MotorB1, OUTPUT);
  pinMode (MotorB2, OUTPUT);  
  
  
  Stop();
  delay(1);
}


/********************************************************************************
* the endless loop function loop ()                                             *
* which is executed in a loop once the setup () function has been executed once.*
*********************************************************************************/ 


void loop() {
  cm = calcul_distance();
  Serial.print(cm);
  Serial.println("cm");
  
  
//if else condition to avoid obstacles***************************
  
  if (cm <= 20 )
{
  Stop();
  delay(2000);
  Marche_arriere();
  delay(2000);
  Demi_tour();
  delay(1000);
  
}
else
{
  Marche_avant();
}
 

  delay(250);
}




/* ***************************************************************
 * function of calculating the distance of the ultrasonic sensor *
******************************************************************/

int calcul_distance()
{  
  
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  cm =(duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
 
  return cm ; 
  }
  
/****************************
* Robot forward function    *
*****************************/  

void Marche_avant()
{
// This function will run the motors in both directions at a fixed speed
 
  // Turn on motor A
 
  digitalWrite(MotorA1, HIGH);
  digitalWrite(MotorA2, LOW);
 
  // Set speed to 200 out of possible range 0~255
 
  analogWrite(enableA, 200);
 
  // Turn on motor B
 
  digitalWrite(MotorB1, HIGH);
  digitalWrite(MotorB2, LOW);
 
  // Set speed to 200 out of possible range 0~255
 
  analogWrite(enableB, 200);  
}

/****************************
* Robot back function       *
*****************************/ 


void Marche_arriere()
{
// This function will run the motors in both directions at a fixed speed
 
  // Turn on motor A
 
  digitalWrite(MotorA1, LOW);
  digitalWrite(MotorA2, HIGH);
 
  // Set speed to 200 out of possible range 0~255
 
  analogWrite(enableA, 150);
 
  // Turn on motor B
 
  digitalWrite(MotorB1, LOW);
  digitalWrite(MotorB2, HIGH);
 
  // Set speed to 200 out of possible range 0~255
 
  analogWrite(enableB, 150);  
}


/****************************
* Robot half turn function  *
*****************************/ 


void Demi_tour()
{
// This function will run the motors in both directions at a fixed speed
 
  // Turn on motor A
 
  digitalWrite(MotorA1, LOW);
  digitalWrite(MotorA2, HIGH);
 
  // Set speed to 200 out of possible range 0~255
 
  analogWrite(enableA, 150);
 
  // Turn on motor B
 
  digitalWrite(MotorB1, HIGH);
  digitalWrite(MotorB2, LOW);
 
  // Set speed to 200 out of possible range 0~255
 
  analogWrite(enableB, 150);  
}



/****************************
* Robot Stop function       *
*****************************/  


void Stop()
{
  // Turn on motor A
 
  digitalWrite(MotorA1, LOW);
  digitalWrite(MotorA2, LOW);

  // Turn on motor B
 
  digitalWrite(MotorB1, LOW);
  digitalWrite(MotorB2, LOW);
}

