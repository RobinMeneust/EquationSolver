/**
 * @file equation.h
 * @author Robin MENEUST
 * @brief Functions prototypes and types needed by equation.c
 * @version 0.1
 * @date 2022-12-05
 */

#ifndef EQUATION_H
#define EQUATION_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * @struct complexNumber
 * @brief Complex number
 * @remark Number equals to a + i*b, where a and b are real numbers
 */

typedef struct complexNumber
{
	double real; /*!< Real part */
	double im; /*!< Imaginary part */
}complexNumber;

/**
 * @struct solutionEqu2D
 * @brief Solution of a second degree polynomial equation
 */

typedef struct solutionEqu2D
{
	complexNumber root1; /*!< First root */
	complexNumber root2; /*!< Second root */
	char nbSol; /*!< Number of solutions */
}solutionEqu2D;

/**
 * @struct solutionEqu3D
 * @brief Solution of a third degree polynomial equation
 */

typedef struct solutionEqu3D
{
	complexNumber root1; /*!< First root */
	complexNumber root2; /*!< Second root */
	complexNumber root3; /*!< Third root */
	char nbSol;  /*!< Number of solutions */
}solutionEqu3D;

/**
 * @struct polynomial1D
 * @brief A polynomial of degree 1: ax + b
 */

typedef struct polynomial1D
{
	double a; /*!< Coefficient for x */
	double b; /*!< Coefficient for b */
}polynomial1D;

/**
 * @struct polynomial3D
 * @brief A polynomial of degree 3: ax^3 + bx^2 + c + d
 */

typedef struct polynomial3D
{
	double a; /*!< Coefficient for x^3 */
	double b; /*!< Coefficient for x^2 */
	double c; /*!< Coefficient for x */
	double d; /*!< Coefficient for 1 */
}polynomial3D;

complexNumber complexDivisionByReal(complexNumber a, double b);
complexNumber complexSum(complexNumber a, complexNumber b);
solutionEqu2D solveEq2D(double a, double b, double c);
void displaySolutionEqu2D(solutionEqu2D sol);
double approxSol3D(double a, double b, double c, double d, double eps);
polynomial3D divPolynomial3D(polynomial3D dividend, polynomial1D divisor);
solutionEqu3D solveEq3D(double a, double b, double c, double d);
void displaySolutionEqu3D(solutionEqu3D sol);
int areEqualComplexNumber(complexNumber a, complexNumber b);
void adjustRootValue(complexNumber *x);
void displayComplexNumber(complexNumber x);

#endif