// event_driven.c

// TIMER
unsigned int timer1;
unsigned int timer2;
bool timer1_active;
bool timer2_active;


// BUTTON
bool button_active;
bool previous_state;
int button_pin;

void button_listen(int pin) {

	pinMode(pin,INPUT);
	BUT_PIN = pin;
	button_active = 1;
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
	button_active = 0;
	previous_state = 0;
	init();
}

void loop () {
	
	if (button_active){
		bool current_state = digitalRead(BUT_PIN);
		if (current_state != previous_state){
			button_changed (BUT_PIN, current_state);
			previous_state = current_state;
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