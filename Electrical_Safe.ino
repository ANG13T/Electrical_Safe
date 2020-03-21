#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Keypad.h>

Servo lockServo;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
   Serial.begin(9600);
   lcd.init();
   lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
   lcd.backlight();//To Power ON the back light
   lcd.setCursor(0,0);
   lcd.print("Enter Password:");
   lockServo.attach(10);
}

int passwordLength = 0;
  
void loop(){
  //Defining positon to write from first row,first column .
   //You can write 16 Characters per line .
  char key = keypad.getKey();
  
  if (key){
    Serial.println(key);
    passwordLength = passwordLength + 1;
    lcd.setCursor(passwordLength,1);
    lcd.print(key);
  }

  if(key == '#'){
    Serial.println("enter");
  }

  if(key == '*'){
    Serial.println("reset");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter Password:");
    passwordLength = 0;
  }
}
