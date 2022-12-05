#include <stdio.h>
#include <stdlib.h>
#include "equation.h"


void displayHelp()
{
	printf("\nNAME\n");
	printf("\tTD9_Structures\n\n");
	printf("SYNOPSIS\n");
	printf("\tTD9_Structures a b c [d]\n\n");
	printf("DESCRIPTION\n");
	printf("\tSolve the equation : a x^2 + b x + c or a x^2 + b x + c + d if d is given\n");
}


/**
 * @brief Get an integer from the user and check if it was correctly got
 * @return Integer given by user
 */

int getInteger()
{
	int n = 0; // integer given by user
	int cFlush = 0; // integer used to flush stdin
	int testScanf = 0; // value returned by scanf. Used to test if the integer was correctly read
	
	testScanf = scanf("%d", &n);
	while((cFlush = getchar()) != '\n' && cFlush != EOF); // we flush stdin
	if (testScanf != 0)
		return n;
	else{
		fprintf(stderr, "ERROR: this number is not valid\n");
		exit(EXIT_FAILURE);
	}
}

void getString(char* text, int size)
{
	int i = 0;

	if(fgets(text, size, stdin) == NULL){
		fprintf(stderr, "ERROR: this number is not valid\n");
		exit(EXIT_FAILURE);
	}

	while(i<size && text[i]!='\n'){
		i++;
	}
	if(i == size){
		text[size-1] = '\0';
	}
	else{
		text[i] = '\0';
	}
}

/**
 * @brief Main function
 * @param argc Number of arguments
 * @param argv Array of arguments
 * @return Returns 0 if it ends correctly
 */
 
int main(int argc, char **argv)
{
	double a;
	double b;
	double c;
	double d;
	solutionEqu2D sol2D;
	solutionEqu3D sol3D;
	if(argc < 4 || argc > 5){
		displayHelp();
		exit(EXIT_FAILURE);
	}
	
	a = strtod(argv[1], NULL);
	b = strtod(argv[2], NULL);
	c = strtod(argv[3], NULL);
	if(argc == 4){
		sol2D = solveEq2D(a, b, c);
		printf("Roots of %lf X^2 + %lf X + %lf:\n", a, b, c);
		displaySolutionEqu2D(sol2D);
	}
	else{
		d = strtod(argv[4], NULL);
		sol3D = solveEq3D(a, b, c, d);
		printf("Roots of %lf X^3 + %lf X^2 + %lf X + %lf:\n", a, b, c, d);
		displaySolutionEqu3D(sol3D);
	}
	return 0;
}