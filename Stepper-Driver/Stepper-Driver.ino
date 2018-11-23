#include <uStepperS.h>

uStepperS stepper; 

float perSpeed = 0.0;
char buff[10];
uint8_t index = 0;
unsigned long timeoutTimer = 0;
bool newSpeed = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(115200, SERIAL_8N1);

  stepper.setMaxVelocity( 1000 ); // Steps/s
  stepper.setMaxAcceleration( 200 ); // Steps/s
  stepper.setCurrent(100);
  
  stepper.setup();
}

unsigned long byteCounter = 0;
int x = 0;

void loop() {

  if( Serial1.available() ){

    char c = Serial1.read();
    byteCounter++;

    if( c == '\n' ){
      buff[index++] = '\0';
      index = 0;

      perSpeed = atof( buff );
      timeoutTimer = millis();
      newSpeed = true;
      
      memset(buff, 0, sizeof(buff));
    }else{
      buff[index++] = c; 
    }
  }

  if(millis() - timeoutTimer > 50){

    perSpeed = 0.0;
    newSpeed = true;
  
  }
  
  if(newSpeed){

    Serial.println( perSpeed );
    stepper.setRPM( perSpeed  );
    
    newSpeed = false;  
  }
  
}