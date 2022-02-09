#include "assignment1.h"
#include "assignment2.h"
#include "workload.h"
#include "scheduler.h"
#include "governor.h"

#include <stdio.h>
#include <limits.h>

// Note: Deadline of each workload is defined in the "workloadDeadlines" variable.
// i.e., You can access the dealine of the BUTTON thread using workloadDeadlines[BUTTON]
// The same for workload dependencies which is defined in the "workloadDependencies" variable
// See also deadlines.c and workload.h

// Assignment: You need to implement the following two functions.

static int global_max =0;

int[] asap(){
	int as[NUM_TASKS];
	int visited[NUM_TASKS];
	for(int i = 0; i< NUM_TASKS ; i++){
		as[NUM_TASKS] == 1;
		visited[i] =1;
		for (int j =0; j< NUM_TASKS ; j++){
			if(workloadDependencies[i][j] == 1){
				as[NUM_TASKS] == 0;
				visited[i] =0;
				break;
			}
		}
	}


	int vst = 0;
	while(1){
		vst =0;
		for(int i = 0; i< NUM_TASKS ; i++){
			if(visited[i] ==0 && check_pred(visited,i) ==1){
				int max = 0;
				for (int j =0; j< NUM_TASKS; j++){
					if(workloadDependencies[i][j] == 1){
						max = max >= as[j] ? max : as[j];
					}
				}
				as[i] = max+1;
				global_max = global_max < as[i] ? as[i] : global_max;
				visited[i] =1;
				vst = 1;
			}
		}
		if(vst == 0) break;
	}
	return as;
}


int[] alap(){
	int al[NUM_TASKS];
	int visited[NUM_TASKS];
	for(int i = 0; i< NUM_TASKS ; i++){
		al[NUM_TASKS] == global_max;
		visited[i] =1;
		for (int j =0; j< NUM_TASKS ; j++){
			if(workloadDependencies[j][i] == 1){
				al[NUM_TASKS] == 0;
				visited[i] =0;
				break;
			}
		}
	}

	int vst = 0;
	while(1){
		vst =0;
		for(int i = 0; i< NUM_TASKS ; i++){
			if(visited[i] ==0 && check_succ(visited,i) ==1){
				int min = 0;
				for (int j =0; j< NUM_TASKS; j++){
					if(workloadDependencies[j][i] == 1){
						min = min <= as[j] ? min : as[j];
					}	
				}
				al[i] = min-1;
				visited[i] =1;
				vst = 1;
			}
		}
		if(vst == 0) break;
	}
	return as;
}

int check_pred(int [] visted, int i){
	for(int j =0 ; j< NUM_TASKS; j++){
		if( workloadDependencies[i][j] == 1 && visited[j]==0){
			return 0;
		}
	}
	return 1;
}

int check_succ(int [] visted, int i){
	for(int j =0 ; j< NUM_TASKS; j++){
		if( workloadDependencies[j][i] == 1 && visited[j]==0){
			return 0;
		}
	}
	return 1;
}

// learn_workloads(SharedVariable* v):
// This function is called at the start part of the program before actual scheduling
// - Parameters

// sv: The variable which is shared for every function over all threads
void learn_workloads(SharedVariable *v)
{
	// TODO: Fill the body
	// This function is executed before the scheduling simulation.
	// You need to calculate the execution time of each thread here.
	//
	// Thread functions:
	// thread_button, thread_big, thread_encoder, thread_obstacle,
	// thread_twocolor, thread_rgbcolor, thread_aled, thread_buzzer

	// Tip 1. You can call each workload function here like:
	// thread_button();

	// Tip 2. You can get the current time here like:
	// long long curTime = get_current_time_us();

	long long start, end;

	start = get_current_time_us();
	thread_button();
	end = get_current_time_us();
	v->workload[0] = end - start;

	start = get_current_time_us();
	thread_big();
	end = get_current_time_us();
	v->workload[1] = end - start;

	start = get_current_time_us();
	thread_encoder();
	end = get_current_time_us();
	v->workload[2] = end - start;

	start = get_current_time_us();
	thread_obstacle();
	end = get_current_time_us();
	v->workload[3] = end - start;

	start = get_current_time_us();
	thread_twocolor();
	end = get_current_time_us();
	v->workload[4] = end - start;

	start = get_current_time_us();
	thread_rgbcolor();
	end = get_current_time_us();
	v->workload[5] = end - start;

	start = get_current_time_us();
	thread_aled();
	end = get_current_time_us();
	v->workload[6] = end - start;

	start = get_current_time_us();
	thread_buzzer();
	end = get_current_time_us();
	v->workload[7] = end - start;

	int [] as = asap();
	int [] al = alap();
	for(int i=0; i< NUM_TASKS ;i++){
		v->mobil[i] = al[i] - as[i];
	}
}

// select_task(SharedVariable* sv, const int* aliveTasks):
// This function is called while runnning the actual scheduler
// - Parameters
// sv: The variable which is shared for every function over all threads
// aliveTasks: an array where each element indicates whether the corresponed task is alive(1) or not(0).
// idleTime: a time duration in microsecond. You can know how much time was waiting without any workload
//           (i.e., it's larger than 0 only when all threads are finished and not reach the next preiod.)
// - Return value
// TaskSelection structure which indicates the scheduled task and the CPU frequency
TaskSelection select_task(SharedVariable *sv, const int *aliveTasks, long long idleTime)
{
	// TODO: Fill the body
	// This function is executed inside of the scheduling simulation.
	// You need to implement a list scheduler.

	// Goal: Select a task that
	//      - Satisfy the dependencies
	//      - Has the highest priority (min mobility)
	//      - If multiple tasks have the same priority, pick the one with the earliest deadline

	// Tip 1. You may get the current time elapsed in the scheduler here like:
	// long long curTime = get_scheduler_elapsed_time_us();

	// Also, do not make any interruptable / IO tasks in this function.
	// You can use printfDBG instead of printf.

	// Sample scheduler: Round robin
	// It selects a next thread using aliveTasks.

	int sets[NUM_TASKS];
	for (i = 0; i < NUM_TASKS; i++){
		if (aliveTasks[i] == 1){
			sets[i] == 1;
			// Check for dependency
			for (int j = 0; j < NUM_TASKS; j++){
				if (workloadDependencies[i][j] == 1 && aliveTasks[j] == 1){
					sets[i] == 0;
				}
			}
		}
	}

	int index = 0;
	int mob = 100000; 
	for(int i=0 ; i< NUM_TASKS; i++){
		if(sets[i] ==1){
			if (sv -> mobil[i] < mob){
				index = i;
				mob = sv -> mobil[i];
			}else if(sv -> mobil[i] == mob){
				index = workloadDeadlines[i] < workloadDeadlines[index] ? i : index;
			}
		}
	}

	// The retun value can be specified like this:
	TaskSelection sel;
	sel.task = index; // The thread ID which will be scheduled. i.e., 0(BUTTON) ~ 7(BUZZER)
	sel.freq = 1;			   // Request the maximum frequency (if you want the minimum frequency, use 0 instead.)

	return sel;
}


