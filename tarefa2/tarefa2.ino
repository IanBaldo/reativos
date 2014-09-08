#define LED1_PIN 13
#define LED2_PIN 12
#define BUT1_PIN 7
#define BUT2_PIN 2

unsigned long old;
unsigned long button1_timer;
unsigned long button2_timer;
int t;
int st;
int button1_pressed;
int button2_pressed;

void setup(){
  pinMode(BUT1_PIN, INPUT);
  pinMode(BUT2_PIN, INPUT);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  
  Serial.begin(9600);
  st = 0;
  t = 1000;
  old = millis();
  button1_pressed = 0;
  button2_pressed = 0;
}

void loop() {
  unsigned now = millis();
  int dt = now - old;
  
  //button1 pressed
  int button1 = digitalRead(BUT1_PIN);
  if (button1==0){
    //faster
    button1_timer = millis();
    int dt_b1 = button1_timer - button2_timer;
    if (dt_b1 >= 500)
      button2_pressed = 0;
    button1_pressed = 1;
    t = t - 500;
    if (t <= 0)
      t = 350;
//     Serial.println("BUTTON 1"); 
     delay(100);
    if(button2_pressed){
      while(1);
    }
  }
  
  // button2 pressed
  int button2 = digitalRead(BUT2_PIN);
  if (button2==0){
   //slower
    button2_timer = millis();
    int dt_b2 = button2_timer - button1_timer;
    if (dt_b2 >= 500)
      button1_pressed = 0;
   button2_pressed = 1;
   t = t + 500;
//   Serial.println("BUTTON 2");
   delay(100);
   if (button1_pressed){
     while(1);
   }
  }
  
  // general blink
  int dif = t - dt;
  if (dif <= 0){
    st = !st;
    old = now;
    digitalWrite(LED1_PIN, st);
    digitalWrite(LED2_PIN, st);
  }
  
   
}

