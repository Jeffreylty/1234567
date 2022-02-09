#ifndef _ASSIGNMENT_BODY_
#define _ASSIGNMENT_BODY_

// A. Pin number definitions (DO NOT MODIFY)
// Important! USE the pin numbers and WIRE.
// We use 8 sensors.
//
// 1. Button
#define PIN_BUTTON 0

// 2. Big audio sensor
#define PIN_BIG 4

// 3. Rotary encoder
#define PIN_ROTARY_CLK 5
#define PIN_ROTARY_DT 6

// 4. Obstacle avoidance sensor
#define PIN_OBS 7

// 5. DIP two-color LED (Dual In-line Package)
#define PIN_DIP_RED 8
#define PIN_DIP_GRN 9

// 6. SMD RGB LED (Surface Mount Device)
#define PIN_SMD_RED 27
#define PIN_SMD_GRN 28
#define PIN_SMD_BLU 29

// 7. Auto-flash LED
#define PIN_ALED 12

// 8. Buzzer
#define PIN_BUZZER 13

// B. Shared structure
// All thread fuctions get a shared variable of the structure
// as the function parameter.
// If needed, you can add anything in this structure.
typedef struct shared_variable {
	int bProgramExit; // Once it is set to 1, the program will be terminated.
	int pause;
	int bigAudio;
	int obstacle;
	int rotary;
	int pinLieter;

	int workload[NUM_TASKS];
	int mobil[NUM_TASKS];
} SharedVariable;


// C. Functions
// You need to implement following functions.
// Do not change any function name here.
void init_shared_variable(SharedVariable* sv);
void init_sensors(SharedVariable* sv);
void body_button(SharedVariable* sv); // Button
void body_big(SharedVariable* sv); // Big audio sensor
void body_encoder(SharedVariable* sv); // Rotary encoder
void body_obstacle(SharedVariable* sv); // Obstacle avoidance sensor
void body_twocolor(SharedVariable* sv); // DIP two-color LED
void body_rgbcolor(SharedVariable* sv); // SMD RGB LED
void body_aled(SharedVariable* sv); // Auto-flash LED
void body_buzzer(SharedVariable* sv); // Buzzer
void writeDIP_RG(int red, int green);
void writeSMD_RGB(int red, int green, int blue);
#endif
