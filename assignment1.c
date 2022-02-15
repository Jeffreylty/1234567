#include "assignment1.h"
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdint.h>

void init_shared_variable(SharedVariable* sv) {
	// You can initialize the shared variable if needed.
	sv->state = 1; // 0 for pause, 1 for running
	sv->bProgramExit = 0;
	sv->bigAudio = 0;
	sv->rotary = -1;
	sv->obstacle = 0;
	sv->pinLieter = 0;
}

void init_sensors(SharedVariable* sv) {
	pinMode(PIN_BIG, INPUT);
	pinMode(PIN_BUTTON, INPUT);
	pinMode(PIN_OBS, INPUT);
	pinMode(PIN_ROTARY_CLK, INPUT);
	pinMode(PIN_ROTARY_DT, INPUT);

	pinMode(PIN_ALED, OUTPUT);
	pinMode(PIN_BUZZER, OUTPUT);
	pinMode(PIN_DIP_RED, OUTPUT);
	pinMode(PIN_DIP_GRN, OUTPUT);
	
	softPwmCreate(PIN_SMD_RED, 0, 0xFF);
	softPwmCreate(PIN_SMD_GRN, 0, 0xFF);
	softPwmCreate(PIN_SMD_BLU, 0, 0xFF);
}

// 1. Button
void body_button(SharedVariable* sv) {
	if(digitalRead(PIN_BUTTON) == LOW) {
		if(sv->state == 0) {
			sv->state = 1;
		} else {
			sv->state = 0;
		}
	}
}

// 2. Big audio sensor
void body_big(SharedVariable* sv) {
	if(digitalRead(PIN_BIG) == HIGH) {
		sv->bigAudio = 1;
	} else {
		sv->bigAudio = 0;
	}
}

// 3. Rotary encoder
void body_encoder(SharedVariable* sv) {
	int encod_in;
	encod_in = digitalRead(PIN_ROTARY_CLK);

	if(encod_in != sv->pinLieter) {
		if(digitalRead(PIN_ROTARY_DT) != encod_in) {
			sv->rotary = 0;
		} else {
			sv->rotary = 1;
		}
	}
	sv->pinLieter = encod_in;
}

// 4. Obstacle avoidance sensor
void body_obstacle(SharedVariable* sv) {
	if(digitalRead(PIN_OBS) == HIGH) {
		sv->obstacle = 1;
	} else {
		sv->obstacle = 0;
	}
}

// 5. DIP two-color LED (Dual In-line Package)
void body_twocolor(SharedVariable* sv) {
	if(sv->state == 0){
		digitalWrite(PIN_DIP_RED,LOW);
		digitalWrite(PIN_DIP_GRN,LOW);		
	} else if (sv->obstacle == 0) {
		digitalWrite(PIN_DIP_RED,LOW);
		digitalWrite(PIN_DIP_GRN,HIGH);	
	} else if (sv->obstacle == 1) {
		digitalWrite(PIN_DIP_RED,HIGH);
		digitalWrite(PIN_DIP_GRN,LOW);	
	}
}

// 6. SMD RGB LED (Surface Mount Device)
void body_rgbcolor(SharedVariable* sv) {
	if(sv->state == 0){
		softPwmWrite(PIN_SMD_RED,0x00);
		softPwmWrite(PIN_SMD_GRN,0x00);
		softPwmWrite(PIN_SMD_BLU,0x00);			
	}
	else if((sv->rotary) == 0 &&(sv->obstacle) == 0){
		softPwmWrite(PIN_SMD_RED,0xff);
		softPwmWrite(PIN_SMD_GRN,0x00);
		softPwmWrite(PIN_SMD_BLU,0x00);			
	} else if((sv->rotary) == 1 &&(sv->obstacle) == 0){
		softPwmWrite(PIN_SMD_RED,0xee);
		softPwmWrite(PIN_SMD_GRN,0x00);
		softPwmWrite(PIN_SMD_BLU,0xc8);			

	} else if((sv->rotary) == 0 &&(sv->obstacle) == 1){
		softPwmWrite(PIN_SMD_RED,0x80);
		softPwmWrite(PIN_SMD_GRN,0xff);
		softPwmWrite(PIN_SMD_BLU,0x00);			

	} else if((sv->rotary) == 1 &&(sv->obstacle) == 1){
		softPwmWrite(PIN_SMD_RED,0x00);
		softPwmWrite(PIN_SMD_GRN,0xff);
		softPwmWrite(PIN_SMD_BLU,0xff);			
	}
}

// 7. Auto-flash LED
void body_aled(SharedVariable* sv) {
	if(sv->state == 1) {
		digitalWrite(PIN_ALED, HIGH);
	} else {
		digitalWrite(PIN_ALED, LOW);
	}
}

// 8. Buzzer
void body_buzzer(SharedVariable* sv) {
	int time = 0;
	if(sv->bigAudio == 1) {
		while(time++ < 100){
			digitalWrite(PIN_BUZZER,HIGH);
			delay(1);
			digitalWrite(PIN_BUZZER,LOW);
			delay(1);
		}
		time = 0;
	} else {
		digitalWrite(PIN_BUZZER, LOW);
	}
}

void writeDIP_RG(int red, int green) {
}

void writeSMD_RGB(int red, int green, int blue) {
}
