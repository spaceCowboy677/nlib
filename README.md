# nlib : General Numerical Methods Library

This library is to facilitate fast execution of generalized numerical tasks. 

This library is derived from modern implementations of code listed in "Numerical Recipes in C" by William Press, Brian Flannery, Saul Teukolsky, and William Vetterling. Certain optimizations might not apply for certain architectures. This is also mainly a learning experience for myself so the implemented code might not be the most performant in every situation.

**Installation**

**Functionality**

*Function Evaluation, Interpolation, and Root Finding*
- POLINT: Performs basic polynomial interpolation over a range of values 
- RTSEC:  Find the root of a given function using the secent method 
- ZBRENT: Find the root of a given function using the Van Wijngaarden-Dekker-Brent method
- CHEBFT: Calculates the fitting coefficients for Chebyshev polynomials over a given function
- CHEBEV: Evaluates a Chebyshev polynomial-fit function

*Systems of Equations*
- LUDCMP: Subroutine to determine the LU decomposition of a provided matrix  
- LUBKSB: Solves the linear system Ax = b when A is an LU decomposed matrix
- LUSLV:  Iteratively solves the linear system Ax = b for any nonsingular A

*Differntiation and Integration*
- QGAUS:  Computes the integral of a provided function over range [a,b] by method of Gaussian Quadratures
- CHINT:  Evaluate the integral coefficients of a Chebyshev polynomial-fit function
- CHDER:  Evaluate the derivative coefficients of a Chebyshev polynomial-fit function

*Solution of Ordinary Differential Equations (ODEs)*
- Adaptive step size Runge-Kutta
- LSODA stiff solver 

*Spectral Methods*

*Statistical Methods*
- Linear regression
- Correlation analysis

*Optimization Methods*

*Random Numbers*
- Monte Carlo integration

*Complex Arithmetic*

*Partial Differential Equations and Boundary Value Problems*

*Utilities*
