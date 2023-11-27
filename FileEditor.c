#include <stdio.h> // Libraries to include
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

int main(){

int createFile(){ 
    char name[32]; //sets filename length to max 32 characters
    FILE *fptr,*cLog; //initiates file data structures
	printf("Enter the name of the file to be created: "); 
	fgets(name, 32, stdin); //takes input using fgets function
    strcat(name,".txt");    // concatenates the string with .txt so the user does not have to type it themselves
	fptr = fopen(name, "a"); // open in append mode to prevent accidental erasure of file contents
	fclose(fptr); 
    cLog = fopen("ChangeLog.txt", "a"); // writes operation and filename in change log
    fprintf(cLog, "Created: %s\n\n", name); 
	fclose(cLog); 
    return 0;
}

int deleteFile(){
	char name[32]; 
    FILE *fptr, *cLog;
	printf("Enter the name of the file to be deleted: "); 
	fgets(name, 32, stdin); 
    strcat(name,".txt");
	if (remove(name) == 0) { // deletes file, and tells user if it was possible to do so
        printf("The file has been deleted.");}
	else{
		printf("The file could not be deleted. It may not exist."); // if file cannot be deleted, user is alerted
	}
    cLog = fopen("ChangeLog.txt", "a"); 
    fprintf(cLog, "Deleted: %s\n\n", name); 
	fclose(cLog); 
    return 0;
}

int copyFile(){
	FILE *fptrA, *fptrB, *cLog; // generate two files
    char name[32], character;  
    printf("Enter the name of the file to be copied from: \n");
    scanf("%s", name);    
    strcat(name,".txt");
    fptrA = fopen(name, "r"); // first file opened in read and checked to see if it exists
    if (fptrA == NULL){
        printf("This file may not exist. \n");
        return 0;
    }  
    printf("Enter the name of the file to be copied to: \n"); 
    scanf("%s", name);     
    strcat(name,".txt");
    fptrB = fopen(name, "w");  // second file opened in write and cleared to ensure it is a direct copy
    if (fptrB == NULL){
        printf("This file may not exist.\n");
        return 0;
    }  
    character = fgetc(fptrA); // takes each character from the stream in txt file
    while (character != EOF){ // loop condition is before end of file is reached
        fputc(character, fptrB); // puts the selected character into the copy file
        character = fgetc(fptrA); // selects next character in stream
    }  
    printf("\nThe contents have been copied.\n");  
    fclose(fptrA);
    fclose(fptrB);
    cLog = fopen("ChangeLog.txt", "a"); 
    fprintf(cLog, "Copied: %s\n\n", name); 
	fclose(cLog); 
    return 0;
}

int showFile(){
    FILE *fptr, *cLog;  
    char name[32], character;  
    printf("Enter the filename to show: \n");
    fgets(name, 32, stdin); 
    strcat(name,".txt");
    fptr = fopen(name, "r");
    if (fptr == NULL){ // checks file exists
        printf("Cannot open file \n");
        return 0;
    }
    character = fgetc(fptr); // reads contents from file
    while (character != EOF){
        printf ("%c", character); // prints contents from file to CLI
        character = fgetc(fptr);
    }  
    fclose(fptr);
    cLog = fopen("ChangeLog.txt", "a"); 
    fprintf(cLog, "Shown: %s\n\n", name); 
	fclose(cLog); 
    return 0;
}

int appendLine(){
    char name[32];
    char newLine[1000]; 
    FILE *fptr, *cLog;
	printf("Enter the name of the file to be appended: "); 
	fgets(name, 32, stdin); 
    strcat(name,".txt");    
	fptr = fopen(name, "a"); 
	printf("Enter the data to be appended: "); 
	fgets(newLine, 1000, stdin); // uses fgets for an input line up to 1000 characters long
    fprintf(fptr, "%s", newLine); //  fprintf writes directly the previous input straight to file
    fclose(fptr);
    cLog = fopen("ChangeLog.txt", "a"); 
    fprintf(cLog, "Appended: %s\n\n", name); 
	fclose(cLog); 
    return 0;
}

int deleteLine(){
    FILE *fptrA, *fptrB, *cLog;
    char name[32];
    char tempName[37] = "temp"; // generates longer temp name variable in case original name is already 32 characters long
	printf("Enter the name of the file you want to remove a line from: "); 
	fgets(name, 32, stdin); 
    strcat(name,".txt");
    strcat(tempName,name); // concatenates temp with the filename.txt
    char position; // loop variable
    int deleteLine, currentLine = 0;
    printf("Please enter the line number you want to delete: ");
    scanf("%d", &deleteLine);
    fptrA = fopen(name,"r");
    fptrB = fopen(tempName, "w"); // copies file without the one line
    position = getc(fptrA);
    if(position!=EOF) {currentLine = 1;}
    while(1){
      if(deleteLine != currentLine)
        putc(position, fptrB);
        position = getc(fptrA);
        if(position =='\n') {
            currentLine++;
            }
        if(position == EOF) {
            break;
        }
    }
    fclose(fptrA);
    fclose(fptrB);
    remove(name); // deletes original file
    rename(tempName, name);  // renames temp file so it is the same as the original
    cLog = fopen("ChangeLog.txt", "a"); 
    fprintf(cLog, "Deleted line from: %s\n\n", name); 
	fclose(cLog); 
    return 0;
}

int insertLine(){
    FILE *fptrA, *fptrB, *cLog;
    char name[32];
    char tempName[36] = "temp";
    char newLine[1000];
	printf("Enter the name of the file you want to insert a line to: "); 
	fgets(name, 32, stdin); 
    strcat(name,".txt");
    strcat(tempName,name);
    char position;
    char insert[10];    
    int currentLine = 0;
    printf("Please enter the line number you want to insert into: ");
    fgets(insert, 10, stdin); // takes input and converts it to numerical value
    int ins = atoi(insert); // converts char to int
    fptrA = fopen(name,"r");
    fptrB = fopen(tempName, "w");
    position = getc(fptrA);
    if(position!=EOF) {currentLine = 1;}
    while(1){
      if(ins != currentLine){  // copies data from original file into new one
        putc(position, fptrB);
        position = getc(fptrA);}    
    if(ins == currentLine){
        printf("Enter the data to be inserted: "); // when insert line is reached, asks for data
	fgets(newLine, 1000, stdin);
    fprintf(fptrB, "%s", newLine);};
        if(position =='\n') {
            currentLine++;
            }
        if(position == EOF) {
            break;     
    }}
    fclose(fptrA);
    fclose(fptrB);
    remove(name); // removes original and renames new file to name of original
    rename(tempName, name);
    cLog = fopen("ChangeLog.txt", "a"); 
    fprintf(cLog, "Copied: %s\n\n", name); 
	fclose(cLog); 
    return 0;
}

int showLine(){
    FILE *fptr, *cLog;  
    char name[32], character;  
    printf("Enter the filename to open \n");
    fgets(name, 32, stdin); 
    strcat(name,".txt");
    fptr = fopen(name, "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        return 0;
    }  
    char insert[10];
    printf("Please enter the line number you want to see: ");
    fgets(insert, 10, stdin);
    int ins = atoi(insert);
    ins -= 1;
    int currentLine = 0;
    character = fgetc(fptr);
    while (character != EOF)
    {
        if (currentLine == ins){printf ("%c", character);}; // prints line if it is on the correct loop
        character = fgetc(fptr);
        if (character == '\n'){ currentLine += 1;}; // increments loop at new line
    }  
    fclose(fptr);
    printf("\n");
    cLog = fopen("ChangeLog.txt", "a"); 
    fprintf(cLog, "Shown line from: %s\n\n", name); 
	fclose(cLog);     
    return 0;
}

int countLine(){
    FILE *fptr, *cLog;  
    char name[32], character;  
    printf("Enter the filename to open \n");
    fgets(name, 32, stdin); 
    strcat(name,".txt");
    fptr = fopen(name, "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        return 0;
    }  
    int currentLine = 0;
    character = fgetc(fptr);
    while (character != EOF)
    {        
        character = fgetc(fptr);
        if (character == '\n'){currentLine += 1;};        
    }  
    printf("%d",currentLine); // prints the value of the current line variable, which has been incremented by the loop
    fclose(fptr);
    cLog = fopen("ChangeLog.txt", "a"); 
    fprintf(cLog, "Counted lines in: %s\n\n", name); 
	fclose(cLog); 
    return 0;
}

int renameFile(){
    char original[32], new[32]; 
    FILE *cLog; 
    printf("Enter the current filename \n");
    fgets(original, 32, stdin); 
    strcat(original,".txt");
    printf("Enter the new filename \n");
    fgets(new, 32, stdin); 
    strcat(new,".txt");    
    rename(original, new); // renames the files after taking inputs
    cLog = fopen("ChangeLog.txt", "a"); 
    fprintf(cLog, "Renamed: %s\n\n", original); 
	fclose(cLog); 
}

int clearFile(){
    char name[32]; 
    FILE *fptr, *cLog;
	printf("Enter the name of the file to be cleared: "); 
	fgets(name, 32, stdin); 
    strcat(name,".txt");
    
	fptr = fopen(name, "a");  // opens in append mode to check existence
	if(fptr != NULL) { 
        fclose(fptr);		
	    fptr = fopen(name, "w"); // if and only if it exists is it cleared, to not waste space
	} 
	fclose(fptr); 
    cLog = fopen("ChangeLog.txt", "a"); 
    fprintf(cLog, "Cleared: %s\n\n", name); 
	fclose(cLog); 
    return 0;
}

int showChangeLog(){
    FILE *fptr;  
    char character;
    fptr = fopen("ChangeLog.txt", "r");
    character = fgetc(fptr);
    while (character != EOF)
    {
        printf ("%c", character); // displays each line of the changelog
        character = fgetc(fptr);
    }  
    fclose(fptr);
    return 0;
}



int loop = 1;
while (loop=1){
    char input[8];
    int inp;
    printf("\nType the letter to complete the operation:\n    1 - Create File\n    2 - Delete File\n    3 - Copy File\n    4 - Show File\n    5 - Append Line\n    6 - Delete Line \n    7 - Rename File \n    8 - Clear File \n    9 - Show Line \n    10 - Count Line\n    11 - Insert Line \n    12 - Show Change Log\n    13 - Quit\n"); 
    printf("    Do not include the .txt when specifying file names! It is added automatically!\n");
    fgets(input, 8, stdin); 
    inp = atoi(input);
    switch(inp){ // switch case to select each subroutine
            case 1:
            createFile();
            break;

            case 2:
            deleteFile();
            break;

            case 3:
            copyFile();
            break;

            case 4:
            showFile();
            break;

            case 5:
            appendLine();
            break;

            case 6:
            deleteLine();
            break;

            case 7:
            renameFile();
            break;

            case 8:
            clearFile();
            break;

            case 9:
            showLine();
            break;

            case 10:
            countLine();
            break;

            case 11:
            insertLine();
            break;

            case 12:
            showChangeLog();
            break;

            case 13:
            exit(0); // in this case, program ends instantly
            break;        
    }
}
return 0;
}