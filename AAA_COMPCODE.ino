/****************************************************************
  Author Names: Kin Blandford, Talon Rencher, Nico Scialdone
  Lab section: 002
  Team number: 008
  Date:  04/19/2022
  Sketch Description: Sketch for 1010 competition

  Button Usage: Up/Down    -
              Left/Right -
              Select     -

  Pin Usage:    Pin type/number     Hardware
                Digital Pin 4       Motor
                Digital Pin 5       Motor
                Analog Pin A5       IR Reflectance Sensor
                Digital pin 9       Launcher Servo
                Digital pin 10      Reloader Servo

  
  //COMP TESTING is search keyword for changing encoder boolean


*******************************************************************/

/****************************
 ** #defines and #includes **
 ****************************/

#include <Servo.h>
#include <math.h>

#define PRINTBOOL true
#define PRINT if(PRINTBOOL)Serial

#define CODEMESSAGE Serial


/***********************
 ** Global Variables ***
 ***********************/
// *** Declare & Initialize Pins ***

const int ledPin = 13;
const int leftSwitchPin = 11;
const int rightSwitchPin = 12;
const int buttonPin = A7;
const int motorDirectionPin = 4;
const int motorPowerPin = 5;
const int irSensorPin = A5;
const int launcherServoPin = 9;
const int solenoidPowerPin = 6;
const int solenoidDirectionPin = 7;
const int reloaderServoPin = 10;


// *** Create Servo Objects ***

Servo launcherServo;
Servo reloaderServo;

// *** Declare & Initialize Program Variables ***
//timing
unsigned long incrementTime = 0;
unsigned long timeSinceLastIncrement = 0;

//user input
bool newUserInput = 1;
char userInput = 'z';


//IR
const int ledOnTime = 1000;
const int ledOffTime = 2000;
unsigned long blinkTime = 0;
unsigned long timeSinceLastBlink = 0;
bool ledOn = 0;

//switches
int leftSwitchState = 0;
int rightSwitchState = 0;
unsigned long printTime = 0;
unsigned long timeSinceLastPrint = 0;
int printDelay = 250;
unsigned long leftSwitchChangeTime = 0;
unsigned long rightSwitchChangeTime = 0;
unsigned long timeSinceLastLeftSwitchChange = 0;
unsigned long timeSinceLastRightSwitchChange = 0;
int switchDebounceTime = 20;

//buttons
int buttonNumber = 0;
unsigned long cibn = 0;
int buttonPressed = 0;

//motors
const int motorPower = 255;
bool motorOn = 0;
bool motorRight = 0;

//stripes
int irSensorValue = 0;
bool black = 1;
unsigned long stripeChangeTime = 0;
unsigned long timeSinceLastStripeChange = 0;
int counts = 24;

//movement
bool startMotion = 0;
int desiredPosition = 24;
int desiredServoAngle = 90;
int servoAngleIncrement = 5;

//control stages
int state = 0;
unsigned long stateChangeTime = 0;
unsigned long timeSinceLastStateChange = 0;

//solenoid
int solenoidPower = 255;
int solenoidActivationTime = 500; //TESTING 2

//reloader
int holdAngle = 40;
int dispenseAngle = 0;
int dispenseDelay = 300;
int reloadAngle = 60;


//debug print
unsigned long debugPrintTime = 0;
unsigned long debugTimeSinceLastPrint = 0;
int debugPrintDelay = 200;  // you can choose this time
//debug blink
const int debugLedPin = 13;   // onboard LED
unsigned long debugBlinkTime = 0;
unsigned long debugTimeSinceLastBlink = 0;
int debugLedHiLo = 0;

//DEMO 1/3/Competition
int target = 0;
int driveTo[] = {0, 0, 0, 0, 0, 0}; //{19, 35, 33, 31, 32, 34};
float xTargetVec[] = {0, 0, 0, 0, 0, 0}; //{0.7, 0.8, 0.9, 1.0, 1.1, 1.2};
int headed = 0;
int writeToServo[] = {0, 0, 0, 0, 0, 0}; //{140, 110, 130, 90, 120, 80};
float alpha = 38.4;
float beta = 0.015;
float thetaL0 = 11.77;
float kappa = 3.279;
float lambda = -0.0022;

float d[] = {0.0400, 0.1583, 0.0553};
float H[] = {0.1301, 0.0960, 0.0880, 0.0465};

float xTarget0;

float computeStuffAccuracy = 0.02; //for accurate calculations while we drive to reloader from start
float FirstTargetServoAngleAccuracy = 0.085; //for quick start //0.065 is good

boolean firstTimeCompute = true;
boolean firstTimeShooting = true;
boolean firstTimeSolenoid = true;
boolean doneWithStartingStuff = false;


/********************
 ** Setup Function **
 ********************/
void setup(void) {

  // *** Initialize Serial Communication ***

  Serial.begin(9600);


  // *** Configure Digital Pins & Attach Servos ***

  pinMode(ledPin, OUTPUT);
  pinMode(leftSwitchPin, INPUT_PULLUP);
  pinMode(rightSwitchPin, INPUT_PULLUP);

  pinMode(motorDirectionPin, OUTPUT);
  pinMode(motorPowerPin, OUTPUT);

  pinMode(solenoidDirectionPin, OUTPUT);
  pinMode(solenoidPowerPin, OUTPUT);


  launcherServo.attach(launcherServoPin);
  reloaderServo.attach(reloaderServoPin);


  // *** Take Initial Readings ***

  black = GetEncoderBoolean();

  // *** Move Hardware to Desired Initial Positions ***

  launcherServo.write(desiredServoAngle);
  digitalWrite(solenoidDirectionPin, HIGH);
  reloaderServo.write(holdAngle);

}// end setup() function

/*******************
 ** Loop Function **
 *******************/
void loop(void) {

  //only reads when user inputs
  if (Serial.available() >= 2)
  {
    //Reads user input
    userInput = Serial.read();

    //Clears buffer to ignore newline
    Serial.read();

    delay (250);
    newUserInput = 1;
  }

  //switch case for user input
  switch (userInput)
  {

    case 'a': //does once
      if (newUserInput == 1) {
        PRINT.println(F("Test a: check that IR LED is blinking"));
        newUserInput = 0;
      }
      //call testing functions
      TestIRLED();
      break;

    case 'b': //does once
      if (newUserInput == 1) {
        PRINT.println(F("Test b: press the switches to test"));
        newUserInput = 0;
      }
      TestSwitches();
      break;

    case 'c': //does once
      if (newUserInput == 1) {
        PRINT.println(F("Test c: press the buttons to test"));
        newUserInput = 0;
      }
      TestButtons();
      break;

    case 'd': //does once
      if (newUserInput == 1) {
        PRINT.println(F("Press buttons to move launcher left and right."));
        newUserInput = 0;
      }
      TestMotor();
      break;

    case 'e': //does once
      if (newUserInput == 1) {
        PRINT.println(F("Press buttons to test the motor and the sensor."));
        newUserInput = 0;
      }
      TestMotor();
      break;
    case 'f': //does once
      if (newUserInput == 1) {
        PRINT.println(F("Press buttons to test the motor and the encoder."));
        newUserInput = 0;
      }
      TestMotor();
      break;
    case 'g': //does once
      if (newUserInput == 1) {
        PRINT.println(F("Press the left and right buttons to count stripes."));
        PRINT.println(F("Press the up and down buttons to increment counts"));
        PRINT.println(F("Press the select button to set counts to 24."));

        newUserInput = 0;
      }
      TestMotor();
      break;
    case 'h': //does once
      if (newUserInput == 1) {
        startMotion = 0;
        PRINT.println(F("Press the left and right buttons to increment desiredPosition."));
        PRINT.println(F("Press the up and down buttons to increment counts."));
        PRINT.println(F("Press the select button to send the launcher to the desired position."));

        newUserInput = 0;
      }
      TestMoveLauncher();
      break;

    case 'i': //does once
      if (newUserInput == 1) {
        PRINT.println(F("Press the up/down/left/right buttons to increment desiredServoAngle."));
        PRINT.println(F("Press the select button to command the servo and fire the solenoid."));

        newUserInput = 0;
      }
      TestAimFire();
      break;
    case 'j': //does once
      if (newUserInput == 1) {
        PRINT.println(F("Press the select button to reload a ball."));
        newUserInput = 0;
      }
      TestReloader();
      break;

    case 'k': //does once
      if (newUserInput == 1) {
        startMotion = 0;
        PRINT.println(F("Press the left and right buttons to increment headed."));
        PRINT.println(F("Press the up and down buttons to increment target."));
        PRINT.println(F("Press the select button to start demo 1."));

        newUserInput = 0;
      }
      Demo1();
      break;

    case 'z': //does once
      if (newUserInput == 1) {
        PrintMenu();
        newUserInput = 0;
      }
      delay(500);
      break;

    case 's': //does once
      GetDataFromMatlab();
      userInput = 'x';
      CODEMESSAGE.println("done");
      break;

    case 't': //does once
      GetDataFromMatlab();
      ComputeStuff(computeStuffAccuracy);
      userInput = 'x';
      CODEMESSAGE.println("done");
      break;
    case 'v': //does once
      if (newUserInput == 1) {
        startMotion = 0;
        PRINT.println(F("Running demo 4 / competition code"));
        newUserInput = 0;
        GetDataFromMatlab();
        PRINT.println(F("Target and Headed Set to 0"));
        target = 0;
        headed = 0;
        startMotion = 1;
        state = 1;
      }
      Demo1();
      break;

    default:
      if (newUserInput == 1) {
        PRINT.println(F("Waiting for valid user input..."));
        PRINT.println(F("Enter z to print menu."));

        newUserInput = 0;
        if (motorOn == 1)
        {
          TurnMotorOff(25);
          PRINT.println(F("Killing motion"));
          startMotion = 0;
          headed = 0;
          target = 0;
        }
      }
      delay(500);
      break;

  }//end of switch on userInput



} // end loop() function

/****************************
 ** User-Defined Functions **
 ****************************/

void TurnMotorOn(void) // If the motor is not already on, sets the motor direction, turns the motor on, and sets the motorOn flag to 1
{
  if (motorOn == 0)
  {
    digitalWrite(motorDirectionPin, motorRight);
    analogWrite(motorPowerPin, motorPower);
    motorOn = 1;
  }

}

void TurnMotorOff(int reverseTime) //If the motor is on, turns the motor off and sets the motorOn flag to 0
{
  if (motorOn == 1)
  {
    analogWrite(motorPowerPin, 0);
    delay(10);

    digitalWrite(motorDirectionPin, !motorRight);
    analogWrite(motorPowerPin, motorPower);

    delay(reverseTime);
    analogWrite(motorPowerPin, 0);
    motorOn = 0;

  }

}

bool GetEncoderBoolean(void) //COMP TESTING
{

  irSensorValue = analogRead(irSensorPin);
  if ((black == 1) && (irSensorValue < 50))
  {
    return 0;
  }
  else if ((black == 0) && (irSensorValue > 285))
  {
    return 1;
  }

  else
  {
    return black;
  }

}

void CountStripes(void)
{
  int prevBlack = black;
  black = GetEncoderBoolean();
  timeSinceLastStripeChange = millis() - stripeChangeTime;
  if (black != prevBlack)
  {
    stripeChangeTime = millis();
    if (motorRight)
    {
      counts++;

    }
    if (!motorRight)
    {
      counts--;
    }
    PRINT.print(F("Counts: "));
    PRINT.print(counts);
    PRINT.print(F("       Time since last stripe change: "));
    PRINT.println(timeSinceLastStripeChange);

  }

}
