#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Author: Benjamin Uleau
//SWE 300 01 Project 3 -- C implementation

//State machine function prototypes
void startState(void);
void intState(void);
void decimalState(void);
void endState(void);

//Defines the valid states for the machine
typedef enum{
	START_STATE,
	INT_STATE,
	DECIMAL_STATE,
	END_STATE,
	NUM_STATES
}State;

//Type definition of a state -- Structure called StateMachine that has a pointer to a state and a mapping between states 
//and their functions
typedef struct{
	State * state;
	void (*func)(void);
}StateMachine;

StateMachine StateMapping[]={
	{START_STATE, startState},
	{INT_STATE, intState},
	{DECIMAL_STATE, decimalState},
	{END_STATE, endState}
};

//Stores the current state
State currentState=START_STATE;
int strIndex=0;
char string[]="102.45";
double value=0;
double place=0.1;

void startState(void){
	if(string[strIndex]=='1'){
		currentState=INT_STATE;
	}
	currentState=END_STATE;
}

void intState(void){
	printf("IN INT_STATE");
}

void decimalState(void){
	
}

void endState(void){
	
}

void execute(void){
	if(currentState<NUM_STATES){
		(*StateMapping[currentState].func) ();
	}
	else{
		printf("%s\n", "OUT OF BOUNDS");
	}
}
//Main method
int main(void){
	return 0;
}