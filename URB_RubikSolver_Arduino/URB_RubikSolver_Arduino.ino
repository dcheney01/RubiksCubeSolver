// Arduino 1 -> Controls URB
const int enPin = 8;

const int step_U = 2;
const int step_R = 3;
const int step_B = 4;

const int dir_U = 5;
const int dir_R = 6;
const int dir_B = 7;

const int steps_U = 50;
const int steps_UPRIME = 50;
const int steps_U2 = 100;
const int steps_R = 50;
const int steps_RPRIME = 50;
const int steps_R2 = 100;
const int steps_B = 50;
const int steps_BPRIME = 50;
const int steps_B2 = 100;

const int timeBetweenSteps = 2; // ms
const int stepCoolDown = 50; // ms

void setup() {
  pinMode(enPin, OUTPUT);

  pinMode(step_U, OUTPUT);
  pinMode(step_R, OUTPUT);
  pinMode(step_B, OUTPUT);

  pinMode(dir_U, OUTPUT);
  pinMode(dir_R, OUTPUT);
  pinMode(dir_B,OUTPUT);

  Serial.begin(9600);
  Serial.flush();
}

void loop() {
  if (Serial.available() > 0) {
    char c = Serial.read();

    if (isAlphaNumeric(c)) { // if we didn't get a whitespace, perform a turn
      switch(c) {
        case 'u':
          turn(step_U, dir_U, steps_U, false);
          break;
        case 'U':
          turn(step_U, dir_U, steps_UPRIME, true);
          break;
        case 'z':
          turn(step_U, dir_U, steps_U2, true);
          break;
        case 'r':
          turn(step_R, dir_R, steps_R, false);
          break;
        case 'R':
          turn(step_R, dir_R, steps_RPRIME, true);
          break;
        case 'x':
          turn(step_R, dir_R, steps_R2, true);
          break;
        case 'b':
          turn(step_B, dir_B, steps_B, false);
          break;
        case 'B':
          turn(step_B, dir_B, steps_BPRIME, true);
          break;
        case 'c':
          turn(step_B, dir_B, steps_B2, true);
          break;
        default:
          break; // an incorrect character so do nothing
      }
      Serial.print(c);
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

