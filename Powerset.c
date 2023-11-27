#include <stdio.h>
#include <math.h>

int main()
{
	int powerSet(float *set, int setLength){	/* Function for printing the power set */
		int powerLength = pow(2, setLength); /* Sets variable to be number of sets in power set */
		int powerLoop;
		int setLoop;

		for(powerLoop = 0; powerLoop < powerLength; powerLoop++){ /* Runs a loop for every set in the power set */
			printf("[");
			for(setLoop = 0; setLoop < setLength; setLoop++){ /* Runs a second loop for each element in the set */			
				if((1<<setLoop) & powerLoop){ /* Performs a left shift on 1 and checks if the value is in both sets */
					printf(" %f", set[setLoop]);};} /* If it is then prints the value for this subset */
					printf(" ]\n");} 
		return 0;}

	float lengthF;  /* Takes length input as float */
    int length;   
    printf("Enter the size of your set, between 1 and 8: "); 
    scanf("%f", &lengthF); 
    length=roundf(lengthF); /* After taking input, round, prevents decimal inputs leading to weird results */
	if (length>8){
		printf("Since your input is larger than 8, it will be set to 8."); /* Forces length to be between 1 and 8 */
    	length = 8;};
	if (length<1){
		printf("Since your input is less than 1, it will be set to 1.");
    	length=1;};
	printf("Your set will be %d elements long.\n",length);


    int inputLoop = 0; /* Declare new variables for controlling set inputs */
	int comparisonLoop = 0;
	float tempElement = 0;
	int flag = 0;
    float set[length]; 
	while (inputLoop < length) { /* Loop to allow numerical inputs into set */
	flag = 0;
    printf("Enter set element %d: ", inputLoop+1); 
    scanf("%f", &tempElement); 
	for(int comparisonLoop = 0; comparisonLoop < inputLoop; comparisonLoop++){
		if (tempElement == set[comparisonLoop]){ /* Sets a flag if element appears twice in set */
			flag = 1;
		};
	};	
	if (flag == 0){ /* Only adds element to set if it is unique */
		set[inputLoop] = tempElement;
		inputLoop += 1;
	}
	else{printf("You cannot have the same element twice.\n");};
	};

	powerSet(set, length); /* Calls function to print powerset */
	return 0;
}
