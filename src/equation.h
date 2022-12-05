#ifndef EQUATION_H
#define EQUATION_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct complexNumber
{
	double real;
	double im;
} complexNumber;

typedef struct solutionEqu2D
{
	complexNumber root1;
	complexNumber root2;
	char nbSol;
} solutionEqu2D;

typedef struct solutionEqu3D
{
	complexNumber root1;
	complexNumber root2;
	complexNumber root3;
	char nbSol;
} solutionEqu3D;

typedef struct Polynomial1D
{
	double a;
	double b;
} Polynomial1D;

typedef struct Polynomial3D
{
	double a;
	double b;
	double c;
	double d;
} Polynomial3D;

complexNumber complexDivisionByReal(complexNumber a, double b);
complexNumber complexSum(complexNumber a, complexNumber b);
solutionEqu2D solveEq2D(double a, double b, double c);
solutionEqu3D solveEq3D(double a, double b, double c, double d);
double approxSol3D(double a, double b, double c, double d, double eps);
void displaySolutionEqu2D(solutionEqu2D sol);
void displaySolutionEqu3D(solutionEqu3D sol);

#endif