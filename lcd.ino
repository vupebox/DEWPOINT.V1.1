void LCD_setup(){
  lcd.init(); //lcd.init(); //lcd.begin();
  lcd.begin(20,4);
  lcd.clear();
  lcd.home();
  lcd.print("                    ");
  lcd.setCursor(0,1);
  lcd.print("                    ");
  lcd.backlight();//Encender back light
  lcd.clear();
  lcd.clear();
  LCD_sendMessage(LcdLine1, "         VSI        ");
  LCD_sendMessage(LcdLine2, "     Iniciando      ");
  delay(2000);
}

void LCD_updateMode(){
  bool isAutomatic = mode;//1 automatic MODE, use !mode for 1 manual mode.
  lcd.setCursor(19,LcdLine1);
  if(isAutomatic){
    lcd.print("A");  
  }else{
    lcd.print("M");
  }
}

void LCD_sendMessage(int Line,String Msn){
  //lcd.clear();
  lcd.setCursor(0,Line);
  lcd.print(Msn);  
  LCD_updateMode();
}

void LCD_longToChar(long value, char *var, int sizeIntVar){
  char bufferInt[sizeIntVar]="";
  char tmp[sizeIntVar+1]="";

  long entero = abs(value);

  int y = 0;

  //get int
  y = snprintf (tmp, sizeof(tmp), "%d", entero);  //para enteros  sizeof(bufferInt)

  for(int i=0;i<sizeIntVar-y;i++){
    bufferInt[i]=' ';  
  }

  if(value < 0)
    bufferInt[sizeIntVar-y-1] = '-';

 snprintf (var, sizeof(bufferInt), "%s%s", bufferInt,tmp); //para entero  
}

void LCD_floatToChar(float value, char *var, int sizeIntVar, int sizeDecimalVar){
  char bufferInt[sizeIntVar+1]="";
  char bufferDecimal[sizeDecimalVar+1]="";
  char tmp[sizeDecimalVar+sizeIntVar+3]="";
  int decimalX;
  

    switch (sizeDecimalVar) {
      case 1:
         decimalX=10;
        break;
      case 2:
        decimalX=100;
        break;
      case 3:
         decimalX=1000;
        break;
      case 4:
        decimalX=10000;
        break;
      case 5:
        decimalX=100000;
        break;
      
      default:
        decimalX=1;
        break;
    }
  
  int entero = (int) (value);
  long decimal = (long) abs((value-float(entero))*float(decimalX)); //hasta 5 decimales

  int y = 0;

  //get int
  y = snprintf (tmp, sizeof(tmp), "%d", entero);  //para enteros  sizeof(bufferInt)

  for(int i=0;i<sizeIntVar-y;i++){
    bufferInt[i]=' ';  
  }

  snprintf (bufferInt, sizeof(bufferInt), "%s%s", bufferInt,tmp); //para entero

  if(decimalX > 1){
          //get decimal
        y = snprintf (tmp, sizeof(tmp), "%d", decimal); //para decimales
      
        for(int i=0;i<sizeDecimalVar-y;i++){
          bufferDecimal[i]='0';  
        }
      
        snprintf (bufferDecimal, sizeof(bufferDecimal), "%s%s", bufferDecimal,tmp); //para decimales
  }
  

  if(decimalX == 1){
    snprintf (var, sizeof(tmp), "%s",bufferInt); //para decimales
  }else{
    snprintf (var, sizeof(tmp), "%s.%s",bufferInt, bufferDecimal); //para decimales
  }
  
}
