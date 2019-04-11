// Define Pins LEDS
int led_green = 50;
int led_red = 51;

//Define Pins ultrasonic****************************************************
 
int trigPin = 25;    // Trigger
int echoPin = 24;    // Echo
long duration, cm;

//Define Pins motors********************************************************

//Motor A (left)

int enableA = 8;
int MotorA1 = 29;
int MotorA2 = 28;
 
//Motor B (right)
int enableB = 7;
int MotorB1 = 27;
int MotorB2 = 26;

//Define pins RGB**************************************************************
int s0=3,s1=4,s2=5,s3=6;
int out=2;
int led=23;
int flag=0;
int motor_coupe =22;
byte counter=0;
byte countR=0,countG=0,countB=0;

/***************************************************************************
 * the setup () initialization function which is executed once at startup.*
 ***************************************************************************/
 
void setup() {

  
//Serial Port begin*********************************************************
   
  Serial.begin (9600);
  
//Define inputs and outputs*************************************************
  // Leds
    pinMode(led_green, OUTPUT);
    pinMode(led_red, OUTPUT);
    
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
  
  // RGB
  
   pinMode(motor_coupe, OUTPUT);
   pinMode(s0,OUTPUT);
   pinMode(s1,OUTPUT); 
   pinMode(s2,OUTPUT);
   pinMode(s3,OUTPUT);
   pinMode(out,INPUT);
   pinMode(led,OUTPUT);
     TCS();
  
Stop();
delay(5000);
}


/********************************************************************************
* the endless loop function loop ()                                             *
* which is executed in a loop once the setup () function has been executed once.*
*********************************************************************************/ 


void loop() {
 

// call ultrasonic
  cm = calcul_distance();
  Serial.print(cm);
  Serial.println("cm");
  
  
//if else condition to avoid obstacles***************************
  
  if (cm <= 50 || countR>150)
{
  Stop();
  delay(2000);
  Marche_arriere();
  delay(750);
  Demi_tour();
  delay(750);
  Stop();
  delay(750);
  Marche_avant();
  delay(600);
  Stop();
  delay(650);
  
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
 
  analogWrite(enableA, 160);
 
  // Turn on motor B
 
  digitalWrite(MotorB1, HIGH);
  digitalWrite(MotorB2, LOW);
 
  // Set speed to 200 out of possible range 0~255
 
  analogWrite(enableB, 120);  

  //activation led green

   digitalWrite (led_red, LOW);
   digitalWrite (led_green, HIGH);
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
 
  analogWrite(enableB, 120);  

  // activation led_red

  digitalWrite (led_red, HIGH);
  delay(100);
  digitalWrite (led_red, LOW);
  delay(100);
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
 
  analogWrite(enableA, 125);
 
  // Turn on motor B
 
  digitalWrite(MotorB1, HIGH);
  digitalWrite(MotorB2, LOW);
 
  // Set speed to 200 out of possible range 0~255
 
  analogWrite(enableB, 100);  

  //activation led green

   digitalWrite (led_green, HIGH);
  delay(100);
  digitalWrite (led_green, LOW);
  delay(100);
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

  //activation led red

   digitalWrite (led_red, HIGH);
   digitalWrite (led_green, LOW);
}

/* ***************************************************************
 * function of calculating the colors of the RGB sensor          *
******************************************************************/

void TCS()
 {
 flag=0;  
 digitalWrite(s1,HIGH);
 digitalWrite(s0,HIGH);
 digitalWrite(s2,LOW);
 digitalWrite(s3,LOW);
 attachInterrupt(0, ISR_INTO, CHANGE);
 timer0_init();

 }
void ISR_INTO()
 {
 counter++;
 }
 void timer0_init(void)
 {
  TCCR2A=0x00;
  TCCR2B=0x07;   //the clock frequency source 1024 points
  TCNT2= 100;    //10 ms overflow again
  TIMSK2 = 0x01; //allow interrupt
 }
 int i=0;
 ISR(TIMER2_OVF_vect)//the timer 2, 10ms interrupt overflow again. Internal overflow interrupt executive function
{
    TCNT2=100;
    flag++;
 if(flag==1)
  {
    countR=counter;
    Serial.print("red=");
    Serial.println(countR,DEC);
    digitalWrite(s2,HIGH);
    digitalWrite(s3,HIGH);

 
  }
  else if(flag==2)
   {
    countG=counter;
    Serial.print("green=");
    Serial.println(countG,DEC);
    digitalWrite(s2,LOW);
    digitalWrite(s3,HIGH);
 
   }
   else if(flag==3)
    {
    countB=counter;
    Serial.print("blue=");
    Serial.println(countB,DEC);
    Serial.println("\n"); 
    digitalWrite(s2,LOW);
    digitalWrite(s3,LOW);
    
   
    }
    else if(flag==4)
     {
     flag=0;
     }
       counter=0;
}
