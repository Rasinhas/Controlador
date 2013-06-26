#include <Servo.h>

int led = 13;
int incomingByte = 0;

Servo myServo[6];

//position of the joint in degrees
int cpos[6] = {90,90,90,90,90,180};

//limits of each joint 
int lb[6] = {0,0,0,0,0,90};
int ub[6] = {180,180,180,180,180,180};

//degrees turned for each iteration
int jsp = 5; // [1,5]

//selected joints
int cd=0;
//garra => 90˜180

void setup() {
    pinMode(led, OUTPUT);

    // setting servos    
    for(int i=0;i<6;i++) {
      myServo[i].attach(i+2);
    }
    for(int i=0;i<6;i++) {
      myServo[i].write(cpos[i]);
    }
    //initializing the serial port (9600 baud)
    Serial.begin(9600);
    
    Serial.println("Press H to turn LED ON");
}
 
// Validates the received byte
// Movements are based on the WASD standard
void validateByte(int b)
{
  // The numbers are used to select the joint to be moved
  if(b == '1') cd = 0;
  else if(b == '2') cd = 1;
  else if(b == '3') cd = 2;
  else if(b == '4') cd = 3;
  else if(b == '5') cd = 4;
  else if(b == '6') cd = 5;
  else if(b == '-') jsp = max(1,jsp--);
  else if(b == '=') jsp = min(5,jsp++);
  else
  {
    if(cd == 0 && b == 'a') doMove(-1);
    else if(cd == 0 && b == 'd') doMove(1);
    else if(cd == 1 && b == 'w') doMove(1);
    else if(cd == 1 && b == 's') doMove(-1);
    else if(cd == 2 && b == 'w') doMove(1);
    else if(cd == 2 && b == 's') doMove(-1);
    else if(cd == 3 && b == 'w') doMove(1);
    else if(cd == 3 && b == 's') doMove(-1);
    else if(cd == 4 && b == 'a') doMove(-1);
    else if(cd == 4 && b == 'd') doMove(1);
    else if(cd == 5 && b == 'w') doMove(1);
    else if(cd == 5 && b == 's') doMove(-1);
  }
}

// Move the joint given the signal
void doMove(int s)
{
  if((s == 1 && cpos[cd] < ub[cd]) || (s == -1 && cpos[cd] > lb[cd]))
  {
    cpos[cd] += s*jsp;
    Serial.println(cpos[cd]);
    myServo[cd].write(cpos[cd]);
  }
  else
  {
      //Handle exceptions
  }
}
 
void loop() {
    if (Serial.available() > 0) {
        // receives a byte if serial port is available
        incomingByte = Serial.read();     
        validateByte(incomingByte);
        
        // Test to see if the serial port communication is working properly
        // h turns the arduino led on and l turns the led off
        if(incomingByte == 'h'){
            digitalWrite(led, HIGH);
        }else if(incomingByte == 'l'){
            digitalWrite(led, LOW);
        }
       
    }
}

