void ENC_show_lcd(){
  char encoder_val[20];
  LCD_floatToChar(ENC_toPercent(),encoder_val,17,2);
  LCD_sendMessage(LcdLine4, encoder_val);
}

float ENC_toPercent(){
  return (float(abs(myEnc.read()))*100.0)/float(abs(ENC_pos_100-ENC_pos_0));
}
