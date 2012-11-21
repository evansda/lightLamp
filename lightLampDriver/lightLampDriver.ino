int LED_RED = 11;
int LED_BLUE = 10;
int LED_GREEN = 5;
int rgbValue = 0;
int light;
String input = "";
int i = 0;


void setup() {

  Serial.begin(9600);
  Serial.println("GO TIme");
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

}

void loop() {

  rgbValue = random(0,255);
  setLED(rgbValue, 255);
  delay(500);
  /*if (Serial.available()) {
    delay(10);

    while (Serial.available() > 0){
      char c = Serial.read();
      input += c;

      if (c == ']'){
        parse_message(input);
        input = "";
      }
    }
  }*/
}

void parse_message(String message) {
  if (message[i] == '[') {
    rgbValue = 100*(message[i+1] -'0') + 10*(message[i+2]-'0') + (message[i+3]-'0');
    Serial.println(rgbValue);
    light = 100*(message[i+4] -'0') + 10*(message[i+5]-'0') + (message[i+6]-'0');
    setLED(rgbValue, 255);
  } 
}

void setLED(int hue, int l){
  int col[3] = {
    0,0,0  };
  getRGB(hue, 255, l, col);
  ledWrite(col[0], col[1], col[2]);
}

void getRGB(int hue, int sat, int val, int colors[3]) {
  // hue: 0-259, sat: 0-255, val (lightness): 0-255
  int r, g, b, base;

  if (sat == 0) { // Achromatic color (gray).
    colors[0]=val;
    colors[1]=val;
    colors[2]=val;
  } 
  else  {
    base = ((255 - sat) * val)>>8;
    switch(hue/60) {
    case 0:
      r = val;
      g = (((val-base)*hue)/60)+base;
      b = base;
      break;
    case 1:
      r = (((val-base)*(60-(hue%60)))/60)+base;
      g = val;
      b = base;
      break;
    case 2:
      r = base;
      g = val;
      b = (((val-base)*(hue%60))/60)+base;
      break;
    case 3:
      r = base;
      g = (((val-base)*(60-(hue%60)))/60)+base;
      b = val;
      break;
    case 4:
      r = (((val-base)*(hue%60))/60)+base;
      g = base;
      b = val;
      break;
    case 5:
      r = val;
      g = base;
      b = (((val-base)*(60-(hue%60)))/60)+base;
      break;
    }
    colors[0]=r;
    colors[1]=g;
    colors[2]=b;
  }
}

void ledWrite(int r, int g, int b){
  analogWrite(LED_RED, 255-r);
  analogWrite(LED_GREEN, 255-g);
  analogWrite(LED_BLUE, 255-b);
}

