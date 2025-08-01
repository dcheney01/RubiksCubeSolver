// Arduino 1 -> Controls DLF
const int enPin = 8;

const int step_D = 2;
const int step_L = 3;
const int step_F = 4;

const int dir_D = 5;
const int dir_L = 6;
const int dir_F = 7;

const int steps_D = 50;
const int steps_DPRIME = 50;
const int steps_D2 = 100;
const int steps_L = 50;
const int steps_LPRIME = 50;
const int steps_L2 = 100;
const int steps_F = 50;
const int steps_FPRIME = 50;
const int steps_F2 = 100;

const int timeBetweenSteps = 2; // ms
const int stepCoolDown = 50; // ms

void setup() {
  pinMode(enPin, OUTPUT);

  pinMode(step_D, OUTPUT);
  pinMode(step_L, OUTPUT);
  pinMode(step_F, OUTPUT);

  pinMode(dir_D, OUTPUT);
  pinMode(dir_L, OUTPUT);
  pinMode(dir_F,OUTPUT);

  Serial.begin(9600);
  Serial.flush();
}

void loop() {

  if (Serial.available() > 0) {
    char c = Serial.read();

    if (isAlphaNumeric(c)) { // if we didn't get a whitespace, perform a turn
      switch(c) {
        case 'd':
          turn(step_D, dir_D, steps_D, false);
          break;
        case 'D':
          turn(step_D, dir_D, steps_DPRIME, true);
          break;
        case 'v':
          turn(step_D, dir_D, steps_D2, true);
          break;
        case 'l':
          turn(step_L, dir_L, steps_L, false);
          break;
        case 'L':
          turn(step_L, dir_L, steps_LPRIME, true);
          break;
        case 'n':
          turn(step_L, dir_L, steps_L2, true);
          break;
        case 'f':
          turn(step_F, dir_F, steps_F, false);
          break;
        case 'F':
          turn(step_F, dir_F, steps_FPRIME, true);
          break;
        case 'm':
          turn(step_F, dir_F, steps_F2, true);
          break;
        default:
          break; // a character for the other arduino
      }
      Serial.print(c); // Print to tell the computer that the stepper is done turning
    }
  }
}

/*
  This function rotates one face of the cube
    inputs:
      * stepPin -> Pin that controls the step
      * DirPin -> Pin that controls rotation direction
      * stepsToTake -> number of steps to make a 90 degree turn of the cube face 
      * prime -> whether or not to turn +/- 90 degrees
*/
void turn(int stepPin, int dirPin, int stepsToTake, bool prime) {
  digitalWrite(enPin, LOW);
  digitalWrite(dirPin, prime);

  for(int n = 0; n < stepsToTake; n++) {
    digitalWrite(stepPin, HIGH);
    digitalWrite(stepPin, LOW);
    delay(timeBetweenSteps);
  }
  digitalWrite(enPin, HIGH);
  
  delay(stepCoolDown);
}

