#include <stdio.h>
#include <math.h>

int main()
{
    float aF; // take original input as float in case of decimal input
    float bF;
    int a; // integer variables to hold rounded floats
    int b;

    printf("If you input a decimal number, it will be rounded to the nearest integer.\n");

    printf("Enter integer A:"); // ask for inputs for 2 integers
    scanf("%f", &aF); // sets the input to be a float
    a=roundf(aF); // rounds the float

    printf("Enter integer B:");
    scanf("%f", &bF); 
    b=roundf(bF);

    while (b != 0)   // while loop condition fails only when b=0
    {  
        printf("Our numbers currently are %d and %d.\n",a,b);
                     
        if (a > b)  // if a is greater than b, a is reduced
            {  
            printf("Since %d is larger than %d, %d will be reduced.\n",a,b,a);
            a = a-b;   // reduces a if its bigger
            }   

        else if(a<b) // if b is greater than a, b is reduced
            {  
            printf("Since %d is larger than %d, %d will be reduced.\n",b,a,b);
            b=b-a;  
            } 

        else{
            b=b-a; // if the numbers are equal, this sets b to be 0, so loop is broken
            }    
                  
    }   
    printf("Since they are the same, the GCD of two numbers is %d.\n", a); // outputs GCD 
    return 0;
}