// event_driven.c

#include <string.h>

#define MAX_BUTTONS 5

// TIMER
unsigned int timer1;
unsigned int timer2;
bool timer1_active;
bool timer2_active;


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
	
	timer1 = millis() + ms;
	timer1_active = 1;
	
}
void timer2_set (int ms) {

	timer2 = millis() + ms;
	timer2_active = 1;
}

void button_changed (int pin, int v);
void timer_expired ();


void setup () {
	timer1_active = 0;
	timer2_active = 0;
	buttons = 0;
	memset(previous_state,0,MAX_BUTTONS);
	init();
}

void loop () {
	
	if (buttons > 0){
		int i;
		for(i=0;i<buttons;i++) {
			bool current_state = digitalRead(button_pin[i]);
			if (current_state != previous_state[i]){
				button_changed (button_pin[i], current_state);
				previous_state[i] = current_state;
			}
		}
	}

	if (timer1_active)				// testa se existe timer ativo
		if (millis() >= timer1){		// testa se passou o tempo do timer
			timer1_expired();
			timer1_active = 0;
		}
	if (timer2_active)			
		if (millis() >= timer2){		
			timer2_expired();
			timer2_active = 0;
		}
}