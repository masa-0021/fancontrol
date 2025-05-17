#include "Arduino.h"

const int pwmPin = 3; // digital PWM pin 9

int pwmVal = 1; // The PWM Value
unsigned long time;
unsigned int rpm;
String stringRPM;

void setup() {
	// generate 25kHz PWM pulse rate on Pin 3
	pinMode(pwmPin, OUTPUT); // OCR2B sets duty cycle

	// Set up Fast PWM on Pin 3
	TCCR2A = 0x23; // COM2B1, WGM21, WGM20
	
	// Set prescaler
	TCCR2B = 0x0A; // WGM21, Prescaler = /8
	
	// Set TOP and initialize duty cycle to zero(0)
	OCR2A = 79; // TOP DO NOT CHANGE, SETS PWM PULSE RATE
	OCR2B = 0; // duty cycle for Pin 3 (0-79) generates 1 500nS pulse even when 0

	digitalWrite(2, HIGH); // Starts reading
	Serial.begin(9600);
}


void loop() {

	unsigned int x = 0U;
	
	// ramp up fan speed by increasing duty cycle every 200mS, takes 16 seconds
	// for(x = 0; x < 80; x++) {
	//  OCR2B = x;    // set duty cycle
	//  getRPMS();
	//  Serial.println(x);
	//  delay(200);
	//}
	
	// Wait for serial
	while (Serial.available() == 0);

	int val = Serial.parseInt();
	if (val > 0 && val < 80) {
		OCR2B = val;
	}
}

char getRPMS() {
	time = pulseIn(2, HIGH);
	rpm = (1000000 * 60) / (time * 4);
	stringRPM = String(rpm);
	if (stringRPM.length() < 5) {
		Serial.println(rpm, DEC);
	}
}
