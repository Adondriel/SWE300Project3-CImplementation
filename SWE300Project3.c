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

//Type definition of a state -- Structure called StateMachine that has a pointer to a state and a mapping between states and their functions
typedef struct{
	State * state;
	void (*func)(void);
}StateMachine;

//The mapping of function pointers to their respective functions
StateMachine StateMapping[]={
	{START_STATE, startState},
	{INT_STATE, intState},
	{DECIMAL_STATE, decimalState},
	{END_STATE, endState}
};

//Stores the current state
State currentState;
//Used to make sure we start in the start state
int goToStart=0;
//Used to know whether or not we're reading after the decimal point
int afterDecimal=0;
//Index of the character array
int strIndex=0;
//Array of characters (that we're converting from
char string[]="232.45";
//The value (that we're converting to)
double value=0;
//What the numbers after the decimal will be multiplied by to make sure they are in the correct place
double divisor=0.1;
//What the numbers before the decimal will be multiplied by to make sure they are in the correct place
int multiplier=1;

//The state the machine starts in
void startState(void){
	printf("%s\n", "IN START STATE");
	//Multiply the multiplier by 10 for each character to the left of the decimal
	//This will allow the characters to be converted to doubles and multiplied by
	//the multiplier so they go in the right place
	int i=1;
	while(string[i]!='.'){
		multiplier=multiplier*10;
		i++;
	}
	execute();
}

void intState(void){
	int charValue=string[strIndex]-'0';
	charValue=charValue*multiplier;
	value=value+charValue;
	printf("%f\n", value);
	printf("%s\n", "IN INT STATE");
	multiplier=multiplier/10;
	strIndex++;
	execute();
}

void decimalState(void){
	double charValue=string[strIndex]-'0';
	charValue=charValue*divisor;
	value=value+charValue;
	divisor=divisor/10;
	printf("%f\n", value);
	printf("%s\n", "IN DECIMAL STATE");
	strIndex++;
	execute();
}

void endState(void){
	printf("%s\n", "IN END STATE");
}

void execute(void){
	if(afterDecimal==0){
		//First, check if the current character is a null terminator, if it is, the machine goes to the end state
		if(string[strIndex]=='0'){
			currentState=END_STATE;
		}
		//If the character is a number, put the machine into the integer state
		else if(string[strIndex]>='0' && string[strIndex]<='9'){
			currentState=INT_STATE;
		}
		//If the character is a ., let the machine know that a decimal has been seen
		else if(string[strIndex]=='.'){
			afterDecimal=1;
			//We don't need to do anything with the decimal point itself, so just skip over it
			strIndex=strIndex+1;
		}
		//If the character is something other than a number or a ., immediately put the machine
		//into the end state
		else{
			currentState=END_STATE;
		}
	}

	//This condition is reached if we've seen a decimal point. I did it this way instead of staying in
	//the decimal state until the end state is reached to prevent repeated code
	if(afterDecimal==1){
		//First, check if the current character is a null terminator, if it is, the machine goes to the end state
		if(string[strIndex]=='\0'){
			currentState=END_STATE;
		}
		//If the character is a number and a decimal point has already been seen, put the machine into the decimal state
		else if(string[strIndex]>='0' && string[strIndex]<='9'){
			currentState=DECIMAL_STATE;
		}
		//If any character other than a number is seen (including a decimal point now that we've already seen one), put the
		//machine in the end state
		else{
			currentState=END_STATE;
		}
	}

	//Used to make sure the machine enters the start state only once
	if(goToStart==0){
		currentState=START_STATE;
		//Mark that the machine has already been in the start state. As long as this is 1, there's no way to get back to start
		goToStart=1;
	}

	//Call the function currently being pointed to
	(*StateMapping[currentState].func) ();
}
//Main method
int main(void){
	//Call this to execute the first time
	execute();
	return EXIT_SUCCESS;
}
