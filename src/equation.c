/**
 * @file equation.c
 * @author Robin MENEUST
 * @brief Functions used to solve second and third degree real equations
 * @version 0.1
 * @date 2022-12-05
 */

#include "equation.h"

/**
 * @brief Divide a complex number by a real number
 * 
 * @param a Dividend (complex number)
 * @param b Divisor (real number)
 * @return Result of the division
 */

complexNumber complexDivisionByReal(complexNumber a, double b)
{
	complexNumber result; // Result of the division

	result.real = a.real / b;
	result.im = a.im / b;
	return result;
}

/**
 * @brief Sum 2 complex numbers
 * 
 * @param a First summed complex number
 * @param b Second summed complex number
 * @return Result of the sum
 */

complexNumber complexSum(complexNumber a, complexNumber b)
{
	complexNumber result; // Result of the sum

	result.real = a.real + b.real;
	result.im = a.im + b.im;
	return result;
}

/**
 * @brief Solve a second degree equation ax^2 + bx + c
 * 
 * @param a // Coefficient of x^2
 * @param b // Coefficient of x
 * @param c // Coefficient of 1
 * @return Structure containing the solutions of the equation
 */

solutionEqu2D solveEq2D(double a, double b, double c)
{
	solutionEqu2D solution; // Structure containing the solutions of the equation ax^2 + bx + c
	double delta = b * b - 4 * a * c; // Delta used to calculate roots
	complexNumber deltaRoot; // Square root of delta
	complexNumber temp; // Temporary complex number used to calculate the sum of b and deltaRoot

	if(a == 0){
		fprintf(stderr, "ERROR: This is not a second degree polynomial equation\n");
		exit(EXIT_FAILURE);
	}

	solution.root1.real = 0;
	solution.root1.im = 0;
	solution.root2.real = 0;
	solution.root2.im = 0;
	deltaRoot.real = 0;
	deltaRoot.im = 0;

	if (delta > 0)
	{
		solution.nbSol = 2;
		deltaRoot.real = sqrt(delta);
		solution.root1.real = (-b - deltaRoot.real) / (2 * a);
		solution.root2.real = (-b + deltaRoot.real) / (2 * a);
	}
	else if (delta == 0)
	{
		solution.nbSol = 1;
		solution.root1.real = (-b) / (2 * a);
	}
	else
	{
		solution.nbSol = 2;
		deltaRoot.im = -sqrt(-delta);
		temp.real = -b;
		temp.im = 0;
		solution.root1 = complexDivisionByReal(complexSum(temp, deltaRoot), (2 * a));
		deltaRoot.im *= -1;
		solution.root2 = complexDivisionByReal(complexSum(temp, deltaRoot), (2 * a));
	}

	return solution;
}

/**
 * @brief Display the roots contained in the parameter sol
 * 
 * @param sol Structure containing the solutions of a second degree equation
 */

void displaySolutionEqu2D(solutionEqu2D sol)
{
	if (sol.nbSol == 1){
		printf("x1 = %lf\n", sol.root1.real);
	}
	else if (sol.nbSol == 2){
		printf("x1 = ");
		displayComplexNumber(sol.root1);
		printf("\nx2 = ");
		displayComplexNumber(sol.root2);
		printf("\n");
	}
	else
	{
		fprintf(stderr, "ERROR: This solution has not been solved\n");
	}
}

/**
 * @brief Get an approximation of one root of the given third degree equation ax^3 + bx^2 + cx + d = 0
 * 
 * @param a Coefficient of x^3
 * @param b Coefficient of x^2
 * @param c Coefficient of x
 * @param d Coefficient of 1
 * @param eps Precision of the solution
 * @return Approximation of a root of the given equation
 */

double approxSol3D(double a, double b, double c, double d, double eps)
{
	int iter = 0; // Number of iterations in the do while loop. It's used to prevent us from having an infinite loop
	double f = 0; // Value of f(x) = ax^3 + bx^2 + cx + d
	double fDeriv = 0; // Value of f'(x)
	double x = 0; // Current value of x
	double fPrev = 0; // Temporary value containing the value of f(x_{n-1}), used to avoid an infinite loop
	double fPrevPrev = 1; // Temporary value containing the value of f(x_{n-2}), used to avoid an infinite loop

	/*
	NEWTON'S METHOD
	Tangent of f going from (xn; f(xn)) to (xn+1; 0):
	
	f'(xn) = (f(xn) - 0) / (xn - xn+1)
==> xn - xn+1 = f(xn)/f'(xn)
==> xn+1 = xn - f(xn)/f'(xn)	
	*/
	do
	{
		fDeriv = 3 * a * x * x + 2 * b * x + c;
		f = a * x * x * x + b * x * x + c * x + d;
		if(fDeriv == 0){
			if(f == 0){
				// We found a root
				break;
			}
			else{
				// We are at a local minimum or maximum but it's not a root so we have to move
				x++;
			}
		}
		else{
			// We are not at a local minimum so we move

			// We are stuck between 2 tangents and thus inside an infinite loop. e.g with -3x^3 + -5x^2 + x + 1
			if(f == fPrevPrev){
				x -= f / (4*fDeriv);
			}
			else{
				x -= f / fDeriv;
			}
		}
		iter++;
		fPrevPrev = fPrev;
		fPrev = f;
	}while ((f > eps || f < -eps) && iter < 10000);

	return x;
}


/**
 * @brief Divide a third degree polynomial by a one degree polynomial
 * 
 * @param dividend Divided polynomial. It's a third degree polynomial
 * @param divisor Polynomial used to divide the dividend. It's a polynomial of degree 1
 * @return Result of the division (a 2D polynomial)
 */

polynomial3D divPolynomial3D(polynomial3D dividend, polynomial1D divisor)
{
	/*
	Example :
	  X³ + 2X² + 2X + 1 		| X + 1
	     	    				|_______
	-(X³ + X²)					| X² + X + 1
	__________					|
       		X²					|
     		-(X² + X)			|
     		.__________			|
     	    		X + 1		|
     	  			-(X + 1)	|
     	  			________	|
     	  					0	|

		We return X² + X + 1
			
	*/

	polynomial3D result; // Result of the division

	if(divisor.a == 0){
		fprintf(stderr, "ERROR: the divisor must be a second degree polynomial (a not null) in divPolynomial3D\n");
		exit(EXIT_FAILURE);
	}

	result.a = 0;

	result.b = dividend.a / divisor.a;
	dividend.b -= divisor.b * result.b;

	result.c = dividend.b / divisor.a;
	dividend.c -= divisor.b * result.c;

	result.d = dividend.c / divisor.a;

	return result;
}

/**
 * @brief Solve a third degree equation ax^3 + bx^2 + cx + d
 * 
 * @param a // Coefficient of x^3
 * @param b // Coefficient of x^2
 * @param c // Coefficient of x
 * @param d // Coefficient of 1
 * @return Structure containing the roots of the equation
 */

solutionEqu3D solveEq3D(double a, double b, double c, double d)
{
	solutionEqu2D solution2D; // Solution of the polynomial equation after being divided by (X - x0) with x0 its first root
	solutionEqu3D solution3D; // Final solution of the polynomial equation
	polynomial3D polynomialDividend; // Polynomial ax^3 + bx^2 + cx + d
	polynomial1D polynomialDivisor; // Polynomial (X - x0) where x0 is the first root of the equation
	polynomial3D eq2D; // Result of the division of polynomialDividend by polynomialDivisor

	polynomialDividend.a = a;
	polynomialDividend.b = b;
	polynomialDividend.c = c;

	polynomialDivisor.a = 1;
	polynomialDivisor.b = -approxSol3D(a, b, c, d, 1e-20);

	eq2D = divPolynomial3D(polynomialDividend, polynomialDivisor);

	solution2D = solveEq2D(eq2D.b, eq2D.c, eq2D.d);


	solution3D.root3.real = -polynomialDivisor.b; // First calculated solution
	solution3D.root3.im = 0;

	if(areEqualComplexNumber(solution2D.root1, solution3D.root3) || (solution2D.nbSol == 2 && areEqualComplexNumber(solution2D.root2, solution3D.root3))){
		solution3D.nbSol = solution2D.nbSol;
	}
	else{
		solution3D.nbSol = 1 + solution2D.nbSol;
	}

	solution3D.root1 = solution2D.root1;
	solution3D.root2 = solution2D.root2;

	adjustRootValue(&solution3D.root1);
	adjustRootValue(&solution3D.root2);
	adjustRootValue(&solution3D.root3);

	return solution3D;
}

/**
 * @brief Display the roots contained in the parameter sol
 * 
 * @param sol Structure containing the solutions of a third degree equation
 */

void displaySolutionEqu3D(solutionEqu3D sol)
{
	solutionEqu2D equ2D; // Contains the 2 last solutions of sol. It's used to call displaySolutionEqu2

	equ2D.nbSol = sol.nbSol;
	if(sol.nbSol == 3){
		equ2D.nbSol--;
		printf("x0 = %lf\n", sol.root3.real);
	}
	
	equ2D.root1 = sol.root1;
	equ2D.root2 = sol.root2;
	displaySolutionEqu2D(equ2D);
}

/**
 * @brief Check if 2 complex numbers are equal
 * 
 * @param a First complex number
 * @param b Second complex number
 * @return 1 if they are equal, else returns 0
 */

int areEqualComplexNumber(complexNumber a, complexNumber b)
{
	return (a.im == b.im && a.real == b.real);
}

/**
 * @brief Set to 0 values equal to 0. It's used to fix values displayed as -0.0 instead of 0.0
 * 
 * @param x Complex number adjusted
 */
void adjustRootValue(complexNumber *x){
	if(x->im == 0){
		x->im = 0;
	}
	if(x->real == 0){
		x->real = 0;
	}
}

/**
 * @brief Display the given complex number
 * 
 * @param x Complex number displayed
 */

void displayComplexNumber(complexNumber x)
{
	if(x.real != 0){
		printf("%lf", x.real);
		if(x.im != 0){
			printf(" + ");
		}
	}
	if(x.im != 0){
		if(x.im == 1){
			printf("i");
		}
		else{
			printf("%lf i", x.im);
		}
	}
	else if(x.real == 0){
		// x is equal to 0 + 0i
		printf("%lf", x.real);
	}
}