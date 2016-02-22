#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//State machine function prototypes
void stateA(void);
void stateB(void);
void stateC(void);
void stateD(void);

//Defines the valid states for the state machine
typedef enum{
	STATE_A,
	STATE_B,
	STATE_C,
	STATE_D,
	NUM_STATES
}StateType;

//Type definition used to define the state machine table structure
typedef struct{
	StateType * state;
	void (*func)(void);
}StateMachineType;

StateMachineType StateMachine[]={
	{ STATE_A, stateA },
	{ STATE_B, stateB },
	{ STATE_C, stateC },
	{ STATE_D, stateD }
};
//A table that defines the valid states of the state machine and the function that should be executed for each state

//Stores the current state of the state machine
StateType SmState=STATE_A;

//This function is called by the state machine for State A
void stateA(void){
	//Run state machine code
	
	//Move to next state
	SmState=STATE_B;
}

//This function is called by the state machine for State B
void stateB(void){
	//Run state machine code
	
	//Move to next state
	SmState=STATE_D;
}

//This function is called by the state machine for State C
void stateC(void){
	//Run state machine code
	
	//Move to next state
	SmState=STATE_A;
}

//This function is called by the state machine for State D
void stateD(void){
	//Run state machine code
	
	//Move to next state
	SmState=STATE_C;
}

//Call this function to run the state machine
void sm_run(void){
	//Check to make sure that the state that is being entered is valid
	if(SmState < NUM_STATES){
		//Call the function for the state
		(*StateMachine[SmState].func) ();
	}
	else{
		//Throw an exception
	}
}

int main(void){
	return 0;
}












