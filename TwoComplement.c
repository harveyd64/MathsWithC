#include <stdio.h> // the libraries that are required
#include <math.h>
#include <stdlib.h>
#include <string.h>
 
int main()
{
    char signMagA[] = "00000000";  // declare strings for the sign magnitude inputs
    char signMagB[] = "00000000";
    char resultBin[8] = "0"; // declare string for final binary result
    int decA, decB, digit, result, absResult = 0; // integer variables for different components
    int power = 6;

    printf("Enter the first 8-bit sign magnitude number: "); // take input for both binary numbers
    scanf("%s", signMagA);
    printf("Enter the second 8-bit sign magnitude number: ");
    scanf("%s", signMagB); 

    int binToDec(long int binary){ // function to convert input binary to decimal
    	long int remainder,decimal = 0;
    	int base = 1;    
    	while (binary > 0)  
    	{  
        	remainder = round(binary % 10);   // converts by checking divisibility by 10 
        	decimal = remainder * base + decimal;  // and incrementing the number by 2^n based on divisibility
            binary = binary / 10; 
        	base = base * 2;  
        } 
	    return decimal;
    }

    int negative(int sign, int decimal){ // function to make decimal number negative if sign = 1 from input
        if(sign == 1){
	    decimal = decimal*-1;};
	    return decimal;
    }

    decA = binToDec(atoi(signMagA+1));  // calls function and assigns to variables
    decB = binToDec(atoi(signMagB+1));  //atoi function converts string to integer
 
 	decA=negative(signMagA[0] - '0',decA); // calls negative function
	decB=negative(signMagB[0] - '0',decB);
	
	result = decA + decB;  // calculates the decimal addition or subtraction
    absResult = abs(result);
    if (result<0){
        absResult -= 1; // reduces the absolute value of result by 1 for two's complement
    };
    if (absResult>127){ // gets rid of overflow digits
        absResult-=128;
    };
	
    while (power >= 0){ // converts decimal result into a binary number
        if ((absResult) - pow(2,power) >=0){
        strcat(resultBin,"1");
        absResult -= pow(2,power);}  // uses string concatenation to combine binary
        else{
            strcat(resultBin,"0"); 
        };
        power -= 1;  // reduces condition
    }

 	if (result<0){ // swaps all 0s with 1s if negative to achieve correct two's complement
    for (digit=0;digit<8;digit++){
        if(resultBin[digit]=='0'){
        resultBin[digit]='1';}
        else{
        resultBin[digit]='0';};
        }
    }
     
    printf("The result in Two's Complement is: %s\n", resultBin);
    return 0;
}
