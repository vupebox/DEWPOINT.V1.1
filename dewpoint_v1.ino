#include <Wire.h> //Libreria I2C
#include <LiquidCrystal_I2C.h> //Libreria LCD  //https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
 
 #include <FlexyStepper.h> // Libreria FlexyStepper //https://github.com/Stan-Reifel/FlexyStepper

#include <Encoder.h> //https://github.com/PaulStoffregen/Encoder
 
 #define MOTOR_RIGHT -1
 #define MOTOR_LEFT 1
 #define MOTOR_STEP_PER_SECOND 200
 #define MANUAL_MODE 0
 #define AUTOMATIC_MODE 1
 #define LcdLine1 0
 #define LcdLine2 1
 #define LcdLine3 2
 #define LcdLine4 3

const float minSensor = 0.0;
const float maxSensor = 10.0;
const float minSensorValue = -30.0;
const float maxSensorValue = 105.0;
//#include <SpeedyStepper.h>
 #include <Controllino.h> 

//
// pin assignments
//
const int BTN_R_PIN =  CONTROLLINO_AI0; //10;
const int BTN_L_PIN = CONTROLLINO_AI1; // 9;
const int BTN_MODE =  CONTROLLINO_AI2;//  2;
const int LIMIT_R_PIN =  CONTROLLINO_AI3; //8;
const int LIMIT_L_PIN = CONTROLLINO_AI4; //7;  
const int MOTOR_STEP_PIN =  CONTROLLINO_DO1; //3;
const int MOTOR_DIRECTION_PIN =  CONTROLLINO_DO3; //4;
const int ENCODER_SIG_PIN = CONTROLLINO_IN0;
const int ENCODER_DIR_PIN = CONTROLLINO_IN1;
const int RELAY_PIN = CONTROLLINO_R5;
const int SENSOR_PIN = CONTROLLINO_AI12;



////////////NO CHANGE
FlexyStepper stepper;


bool BTN_R;
bool BTN_L;
bool LIMIT_R;
bool LIMIT_L;
unsigned long timeReadButton;
bool mode = true;



LiquidCrystal_I2C lcd(0x27, 20, 4);

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(ENCODER_SIG_PIN, ENCODER_DIR_PIN);

long ENC_pos_100 = 0;
long ENC_pos_0 = 0;

void setup() 
{
  LCD_setup();
  pinMode(BTN_R_PIN,INPUT);
  pinMode(BTN_L_PIN,INPUT);
  pinMode(BTN_MODE, INPUT);
  pinMode(LIMIT_R_PIN,INPUT);
  pinMode(LIMIT_L_PIN,INPUT);
  pinMode(RELAY_PIN,INPUT);
  pinMode(MOTOR_STEP_PIN,OUTPUT);
  pinMode(MOTOR_DIRECTION_PIN,OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  stepper.connectToPins(MOTOR_STEP_PIN, MOTOR_DIRECTION_PIN);
  fn_read_mode();
  fn_swetp_door(); //open a close the to limit
  timeReadButton = millis();   
}



void loop(){
  if(mode == MANUAL_MODE)
    fn_manual_mode();

  if(mode == AUTOMATIC_MODE)
    fn_automatic_mode();

  fn_read_mode();
  SENSOR_show_lcd();
  //ENC_show_lcd();
}

void fn_swetp_door(){
  char encoder_val[20];
  LCD_sendMessage(LcdLine2,"Verificar movimiento");
  LCD_longToChar(0,encoder_val,20);
  LCD_sendMessage(LcdLine3, encoder_val);
  
  while(!digitalRead(LIMIT_R_PIN)){
    moveMotor(MOTOR_RIGHT);
  }
  LCD_longToChar(myEnc.read(), encoder_val,20);
  LCD_sendMessage(LcdLine3, encoder_val);
  myEnc.write(0); //Reset Encoder  
  while(!digitalRead(LIMIT_L_PIN)){
    moveMotor(MOTOR_LEFT);
  }
  ENC_pos_100 = myEnc.read();
  LCD_longToChar(myEnc.read(),encoder_val,20);
  LCD_sendMessage(LcdLine2,"     Verificado     ");
  LCD_sendMessage(LcdLine3, encoder_val);
}
