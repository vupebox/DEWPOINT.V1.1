
void moveMotor(int direction1){
  stepper.setSpeedInStepsPerSecond(MOTOR_STEP_PER_SECOND);
  stepper.setAccelerationInStepsPerSecondPerSecond(MOTOR_STEP_PER_SECOND);
  stepper.setTargetPositionRelativeInSteps(200*direction1);
  stepper.setCurrentPositionInSteps((MOTOR_STEP_PER_SECOND-1)*direction1);
  stepper.processMovement();
}
