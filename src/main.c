/**
 * @file main.c
 * @author Robin MENEUST
 * @brief Solve second and third degree real equations
 * @version 0.1
 * @date 2022-12-05
 */

#include <stdio.h>
#include <stdlib.h>
#include "equation.h"

/**
 * @brief Display this program help page
 */

void displayHelp()
{
	printf("\nNAME\n");
	printf("\tTD9_Structures\n\n");
	printf("SYNOPSIS\n");
	printf("\tTD9_Structures a b c [d]\n\n");
	printf("DESCRIPTION\n");
	printf("\tSolve the equation : a x^2 + b x + c or a x^2 + b x + c + d\n\ta can't be equal to 0\n");
}


/**
 * @brief Get an integer from stdin and check if it was correctly got
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

/**
 * @brief Get a string from the stdin and check if it was correctly got
 * 
 * @param text Array were the resulting string will be stored
 * @param size Maximum size of this array
 */

void getString(char* text, int size)
{
	int i = 0; // Index used to move in the array named text

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
	double a; // Coefficient of the highest degree of the polynomial (for x^2 or x^3)
	double b; // Coefficient of the second highest degree of the polynomial (for x or x^2)
	double c; // Coefficient of the third highest degree of the polynomial (for 1 or x)
	double d; // Coefficient of the lowest degree of the polynomial (for 1)
	solutionEqu2D sol2D; // Solution(s) of a second degree polynomial equation
	solutionEqu3D sol3D; // Solution(s) of a third degree polynomial equation

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
		if(a == 0){
			fprintf(stderr, "ERROR: d was provided but a is null so it's not a third degree equation\n");
			exit(EXIT_FAILURE);
		}

		d = strtod(argv[4], NULL);
		sol3D = solveEq3D(a, b, c, d);
		printf("Roots of %lf X^3 + %lf X^2 + %lf X + %lf:\n", a, b, c, d);
		displaySolutionEqu3D(sol3D);
	}
	return 0;
}