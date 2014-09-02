// event_driven.c

#include <string.h>

#define MAX_BUTTONS 5

// TIMER
unsigned int timer1;
unsigned int timer2;
unsigned int ms1;
unsigned int ms2;
int timer1_active;
int timer2_active;


// BUTTON
int buttons;
int previous_state[MAX_BUTTONS];
int button_pin[MAX_BUTTONS];

void button_listen(int pin) {

	pinMode(pin,INPUT);
	button_pin[buttons] = pin;
	buttons = buttons + 1;
}

void timer1_set (int ms) {
	timer1 = millis();
        ms1 = ms;
	timer1_active = 1;
	
}
void timer2_set (int ms) {
        ms2 = ms;
	timer2 = millis();
	timer2_active = 1;
}

void button_changed (int pin, int v);
void timer1_expired ();
void timer2_expired ();


void setup () { 
        Serial.begin(9600);
	timer1_active = 0;
	timer2_active = 0;
	buttons = 0;
	memset(previous_state,0,MAX_BUTTONS);
	init1();
}

void loop () {
	
	if (buttons > 0){
		int i;
		for(i=0;i<buttons;i++) {
			int current_state = digitalRead(button_pin[i]);
			if (current_state != previous_state[i]){
				button_changed (button_pin[i], current_state);
                                Serial.print("ENTREI BOTAO -> ");
                                Serial.print(button_pin[i]);
                                Serial.print(" ");
                                Serial.println(i);
				previous_state[i] = current_state;
			}
		}
	}
	if (timer1_active){			
		unsigned int dt1 = millis() - timer1;
  //              Serial.print("dt1 = ");
   //             Serial.println(dt1);
                if (dt1 >= ms1){		
                        timer1_active = 0;			
			timer1_expired();			
		}
        }
	if (timer2_active){
                unsigned int dt2 = millis() - timer2;			
		if (dt2 >= ms2){		
			timer2_active = 0;			
			timer2_expired();			
		}
        }
}

#define LED1_PIN 13
#define LED2_PIN 12
#define BUT1_PIN 7
#define BUT2_PIN 2

unsigned int led_freq; 	// LED frequency
int button1_pressed;
int button2_pressed;
int state;

void init1() {
	pinMode(LED1_PIN,OUTPUT);
	pinMode(LED2_PIN,OUTPUT);
	
        button_listen(BUT1_PIN);
	button_listen(BUT2_PIN);

	led_freq = 1000;
	button1_pressed = 0;
	button2_pressed = 0;
        state = 0;
        
	timer1_set(led_freq);
}

void button_changed(int pin, int v){
	if (pin == BUT1_PIN && v == 0){
		// button 1
		led_freq = led_freq + 1000;
		button1_pressed = 1;

		if (button2_pressed)
			while(1);
		else {
			timer2_set(500);
		}
	}
	else if (pin == BUT2_PIN && v == 0){
		// button 2
		led_freq = led_freq - 1000;
                if (led_freq <= 0)
                    led_freq = 1000;
		button2_pressed = 1;

		if (button1_pressed)
			while(1);
		else {
			timer2_set(500);
		}
	}
}

void timer2_expired(){
	button1_pressed = 0;
	button2_pressed = 0;
}

void timer1_expired(){
        Serial.print("LED_freq -> ");
        Serial.println(led_freq);
	digitalWrite(LED1_PIN,state);
	digitalWrite(LED2_PIN,state);
	state = !state;
	timer1_set(led_freq);
}
