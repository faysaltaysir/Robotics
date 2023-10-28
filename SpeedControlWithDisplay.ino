
const int RS = 12,EN = 11, D4 = 10, D5 = 9, D6 = 8 ,D7 = 7;

void lcdCommand(byte command) {
  digitalWrite(RS, LOW);   
  digitalWrite(EN, LOW);
  digitalWrite(D4, bitRead(command, 4));
  digitalWrite(D5, bitRead(command, 5));
  digitalWrite(D6, bitRead(command, 6));
  digitalWrite(D7, bitRead(command, 7));

  digitalWrite(EN, HIGH);   
  digitalWrite(EN, LOW);    

  digitalWrite(D4, bitRead(command, 0));
  digitalWrite(D5, bitRead(command, 1));
  digitalWrite(D6, bitRead(command, 2));
  digitalWrite(D7, bitRead(command, 3));
  digitalWrite(EN, HIGH);   
  digitalWrite(EN, LOW);  

  delayMicroseconds(100);   
}

void lcdData(byte data) {
  digitalWrite(RS, HIGH);   
  digitalWrite(EN, LOW);    

  digitalWrite(D4, bitRead(data, 4));
  digitalWrite(D5, bitRead(data, 5));
  digitalWrite(D6, bitRead(data, 6));
  digitalWrite(D7, bitRead(data, 7));
  digitalWrite(EN, HIGH);  
  digitalWrite(EN, LOW);   

  
  digitalWrite(D4, bitRead(data, 0));
  digitalWrite(D5, bitRead(data, 1));
  digitalWrite(D6, bitRead(data, 2));
  digitalWrite(D7, bitRead(data, 3));
  digitalWrite(EN, HIGH);   
  digitalWrite(EN, LOW);    

  delayMicroseconds(100);   
}

void lcdInit() {
 
  lcdCommand(0x33);         
  lcdCommand(0x32);        
  lcdCommand(0x28);        
  lcdCommand(0x0C);         
  lcdCommand(0x06);         
  lcdCommand(0x01);         
  delayMicroseconds(2000); 
}
void writeString(String s) {
  for (int i = 0; i < s.length(); i++) {

    lcdData(s[i]);
  }
}
void lcdSendString(const char* str) {
  int i = 0;
  while (str[i] != '\0') {
    lcdData(str[i]);
    i++;
  }
}

int k1 = 6, k2 = 5, k3 = 4;
int flag = 0, q = 1, k = 0, p = 1, g = 1;
static int a = 0, j = 0, b,num=0,num2=0;
String s;

class Button{
  int buttonState;        
  int lastButtonState;    
  int buttonState_1;       
  int lastButtonState_1;   
  bool outputState;     
  int buttonPin,counter=0; 
  public:
  Button(int pin){
    buttonPin = pin;     
    buttonState = HIGH;       
    lastButtonState = HIGH;    
    outputState = false;     
    pinMode(buttonPin, INPUT);  
  }
  int onPress(){
    buttonState_1 = digitalRead(buttonPin);
    if (buttonState_1 == HIGH && lastButtonState_1 == LOW) {
      counter++;
      delay(100);
    }
    lastButtonState_1 = buttonState_1;
    counter = counter % 2;
    return counter;
    }

  bool press() {
    buttonState = digitalRead(buttonPin);
    if (buttonState != lastButtonState) {     
      delay(50);
      if (buttonState == LOW) {
      outputState = true;a=1;delay(200);
      return 1;
    }
  }return 0;
  lastButtonState = buttonState;
  }   
};
void setup() {
  pinMode(RS, OUTPUT);
  pinMode(EN, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);

  lcdInit();
  int pwm = 150;
    Serial.begin(9600);
    int x=1,pwmValue;String s;
    Button a(k1), b(k2), c(k3), d(k1), e(k2), f(k3);
    while( 1 ) { 
      if(a.onPress()==0){
        if(x==1){ lcdCommand(0x01);x=0;}
        lcdCommand(0x80);        
        writeString("PWM: ");
        s = String(pwm);
        writeString(s);
      }
      else{
        if(x==0){ lcdCommand(0x01);x=1;}
        lcdCommand(0x80);
        writeString("InPut Mode  ");
        writeString(s);
        if(b.press() == 1) {
          pwm -= 10;
          if(pwm < 20) pwm = 0;
          s = String(pwm);
        }
        if(c.press() == 1) {
          pwm += 10;
          if(pwm > 0 && pwm < 20) 
            pwm += 10;
          if(pwm > 250) pwm = 250;
          s = String(pwm);
        }
        if(pwm <100 && pwm >=20){
          writeString(" "); 
        }
        if(pwm == 0){
          writeString(" ");
        }
      }
    }                  
}

void loop() {
}
 
