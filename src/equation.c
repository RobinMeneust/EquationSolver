#include "equation.h"

complexNumber complexDivisionByReal(complexNumber a, double b)
{
	complexNumber result;
	result.real = a.real / b;
	result.im = a.im / b;
	return result;
}

complexNumber complexSum(complexNumber a, complexNumber b)
{
	complexNumber result;
	result.real = a.real + b.real;
	result.im = a.im + b.im;
	return result;
}

solutionEqu2D solveEq2D(double a, double b, double c)
{
	solutionEqu2D solution;
	double delta = b * b - 4 * a * c;
	complexNumber deltaRoot;
	complexNumber temp;

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

void displaySolutionEqu2D(solutionEqu2D sol)
{
	if (sol.nbSol == 1)
	{
		printf("x0 = %lf\n", sol.root1.real);
	}
	else if (sol.nbSol == 2)
	{
		printf("x1 = %lf", sol.root1.real);
		if (sol.root1.im != 0)
		{
			if (sol.root1.im > 0)
			{
				printf(" + %lf i", sol.root1.im);
			}
			else
			{
				printf(" %lf i", sol.root1.im);
			}
		}

		printf("\nx2 = %lf", sol.root2.real);
		if (sol.root2.im != 0)
		{
			if (sol.root2.im > 0)
			{
				printf(" + %lf i", sol.root2.im);
			}
			else
			{
				printf(" %lf i", sol.root2.im);
			}
		}
		printf("\n");
	}
	else
	{
		fprintf(stderr, "ERROR: This solution has not been solved\n");
	}
}

double min(double a, double b, double c, double d)
{
	if (a < b)
	{
		if (c < d)
		{
			if (a < c)
			{
				return a;
			}
			else
			{
				return c;
			}
		}
		else
		{
			if (a < d)
			{
				return a;
			}
			else
			{
				return d;
			}
		}
	}
	else
	{
		if (c < d)
		{
			if (b < c)
			{
				return b;
			}
			else
			{
				return c;
			}
		}
		else
		{
			if (b < d)
			{
				return b;
			}
			else
			{
				return d;
			}
		}
	}
}

double approxSol3D(double a, double b, double c, double d, double eps)
{
	int iter = 0;
	double f = 0;
	double fDeriv = 0;
	double x = min(a, b, c, d) - 100;

	/*
	NEWTON'S METHOD
	*/
	do
	{
		fDeriv = 3 * a * x * x + 2 * b * x + c;
		f = a * x * x * x + b * x * x + c * x + d;
		x -= f / fDeriv;
		iter++;
	} while ((f > eps || f < -eps) && iter < 10000);

	return x;
}

// Here deg(q) = 1 and deg(p) = 3
Polynomial3D divPolynomial3D(Polynomial3D p, Polynomial1D q)
{
	Polynomial3D result;

	result.b = p.a / q.a;
	p.b -= q.b * result.b;

	result.c = p.b / q.a;
	p.c -= q.b * result.c;

	result.d = p.c / q.a;

	return result;
}

solutionEqu3D solveEq3D(double a, double b, double c, double d)
{
	solutionEqu2D solution2D;
	solutionEqu3D solution3D;
	Polynomial3D p;
	Polynomial1D q;
	Polynomial3D eq2D;

	if (a == 0)
	{
		solution2D = solveEq2D(b, c, d);
		solution3D.nbSol = 2;
		solution3D.root1 = solution2D.root1;
		solution3D.root2 = solution2D.root2;

		return solution3D;
	}
	p.a = a;
	p.b = b;
	p.c = c;

	q.a = 1;
	q.b = -approxSol3D(a, b, c, d, 0.001);

	eq2D = divPolynomial3D(p, q);
	solution2D = solveEq2D(eq2D.b, eq2D.c, eq2D.d);

	solution3D.nbSol = 1 + solution2D.nbSol;
	solution3D.root1.real = -q.b;
	solution3D.root1.im = 0;
	solution3D.root2 = solution2D.root1;
	solution3D.root3 = solution2D.root2;

	return solution3D;
}

void displaySolutionEqu3D(solutionEqu3D sol)
{
	solutionEqu2D equ2D;
	equ2D.nbSol = sol.nbSol - 1;
	equ2D.root1 = sol.root2;
	equ2D.root2 = sol.root3;

	printf("x0 = %lf\n", sol.root1.real);
	displaySolutionEqu2D(equ2D);
}