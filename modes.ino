void fn_read_mode(){
  bool last_mode = mode;
  mode = digitalRead(BTN_MODE); //1 automatic MODE, use !digitalRead for 1 manual mode.
  if(last_mode != mode)
    LCD_updateMode(); 
}

void fn_automatic_mode(){
}

void fn_manual_mode(){
  if((millis() - timeReadButton)>250){
    BTN_R = digitalRead(BTN_R_PIN); 
    BTN_L = digitalRead(BTN_L_PIN);
    timeReadButton = millis();  
  }
    LIMIT_R = digitalRead(LIMIT_R_PIN); 
    LIMIT_L = digitalRead(LIMIT_L_PIN);


  if( (BTN_L == HIGH) && (LIMIT_L == LOW) ){
      moveMotor(MOTOR_LEFT);
  }

  if( (BTN_R == HIGH) && (LIMIT_R == LOW) ){
      moveMotor(MOTOR_RIGHT);
  }
}
