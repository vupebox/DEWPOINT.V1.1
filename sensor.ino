float SENSOR_read(){
  uint16_t val = analogRead(SENSOR_PIN);
  float voltage = float(val)*0.0097; // 0.03 because 24v source on controllino.
  return mapFloat(voltage, minSensor, maxSensor, minSensorValue, maxSensorValue);
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (((x - in_min) * (out_max - out_min)) / (in_max - in_min)) + out_min;
}

void SENSOR_show_lcd(){
  char sensor_val[20];
  LCD_floatToChar(SENSOR_read(),sensor_val,17,2);
  LCD_sendMessage(LcdLine2, sensor_val);
}
