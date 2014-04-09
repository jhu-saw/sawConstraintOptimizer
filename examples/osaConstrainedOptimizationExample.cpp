/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-    */
/* ex: set filetype=cpp softtabstop=4 shiftwidth=4 tabstop=4 cindent expandtab: */
/*
  $Id: osaConstrainedOptimizationExample.cpp 4605 2013-12-12 21:37:52Z adeguet1 $

  Author(s):  Simon Leonard
  Created on: 2013

  (C) Copyright 2013 Johns Hopkins University (JHU), All Rights Reserved.

--- begin cisst license - do not edit ---

This software is provided "as is" under an open source license, with
no warranty.  The complete license can be found in license.txt and
http://www.cisst.org/cisst/license.txt.

--- end cisst license ---
*/

#include <sawConstraintController/osaConstrainedOptimization.h>
#include <sawConstraintController/osaConstraintIntervals.h>


// Overload objective equations
class Objective : public osaObjective{
public:
    Objective( const std::string& name, osaEquation::Status status ) :
	osaObjective( name, status ){}
};

// Overload equality constraints
class Equality : public osaConstraintEquality{
public:
    Equality( const std::string& name, osaEquation::Status status ) :
	osaConstraintEquality( name, status ){}
};

// Overload inequality constraints
class Inequality : public osaConstraintInequality{
public:
    Inequality( const std::string& name, osaEquation::Status status ) :
	osaConstraintInequality( name, status ){}
};

int main(){

    // create a constrained optimization
    osaConstrainedOptimization co;
    // the solution
    vctDynamicVector<double> x;

    // create the objective1 equations
    Objective objective1( "O1", osaObjective::ACTIVE );
    {
	// declare coeficient matrix
	vctDynamicMatrix<double> A( 3, 4, VCT_COL_MAJOR );
	A[0][0] = 0.9501; A[0][1] = 0.7620; A[0][2] = 0.6153; A[0][3] = 0.4057;
	A[1][0] = 0.2311; A[1][1] = 0.4564; A[1][2] = 0.7919; A[1][3] = 0.9354;
	A[2][0] = 0.6068; A[2][1] = 0.0185; A[2][2] = 0.9218; A[2][3] = 0.9169;

	// set the coefficient matrix of the objective equations
	objective1.SetCoefficientMatrix( A );

	// Right hand side vector
	vctDynamicVector<double> b( 3 );
	b[0] = 0.0578;
	b[1] = 0.3528;
	b[2] = 0.8131;

	// set the rhsv of the equation
	objective1.SetRHSV( b );
    }
    // insert the objective
    co.Insert( &objective1 );


    // create the objective1 equations
    Objective objective2( "O2", osaObjective::ACTIVE );
    {
	// declare coeficient matrix
	vctDynamicMatrix<double> A( 2, 4, VCT_COL_MAJOR );
	A[0][0] = 0.4859; A[0][1] = 0.8214; A[0][2] = 0.7382; A[0][3] = 0.4102;
	A[1][0] = 0.8912; A[1][1] = 0.4447; A[1][2] = 0.1762; A[1][3] = 0.8936;

	// set the coefficient matrix of the objective equations
	objective2.SetCoefficientMatrix( A );

	// Right hand side vector
	vctDynamicVector<double> b( 2 );
	b[0] = 0.0098;
	b[1] = 0.1388;

	// set the rhsv of the equation
	objective2.SetRHSV( b );
    }
    // insert the
    co.Insert( &objective2 );

    // O1 and O2 active
    co.Evaluate( x );
    std::cout << "###############" << std::endl;
    std::cout << "Solution: \n" << x << std::endl;
    std::cout << "Residuals:" << std::endl;
    std::cout << objective1.GetName() << ": "
	      << objective1.Residuals( x ) << std::endl
	      << objective2.GetName() << ": "
	      << objective2.Residuals( x ) << std::endl << std::endl;

    // create the objective3 equations
    Objective objective3( "O3", osaObjective::ACTIVE );
    {
	// declare coeficient matrix
	vctDynamicMatrix<double> A( 5, 4, VCT_COL_MAJOR );
	A[0][0] = 0.9501; A[0][1] = 0.7620; A[0][2] = 0.6153; A[0][3] = 0.4057;
	A[1][0] = 0.2311; A[1][1] = 0.4564; A[1][2] = 0.7919; A[1][3] = 0.9354;
	A[2][0] = 0.6068; A[2][1] = 0.0185; A[2][2] = 0.9218; A[2][3] = 0.9169;
	A[3][0] = 0.4859; A[3][1] = 0.8214; A[3][2] = 0.7382; A[3][3] = 0.4102;
	A[4][0] = 0.8912; A[4][1] = 0.4447; A[4][2] = 0.1762; A[4][3] = 0.8936;

	// set the coefficient matrix of the objective equations
	objective3.SetCoefficientMatrix( A );

	// Right hand side vector
	vctDynamicVector<double> b( 5 );
	b[0] = 0.0578;
	b[1] = 0.3528;
	b[2] = 0.8131;
	b[3] = 0.0098;
	b[4] = 0.1388;

	// set the rhsv of the equation
	objective3.SetRHSV( b );
    }
    // insert the objective
    co.Insert( &objective3 );

    objective1.DeActivate();  // deactivate objective 1
    co.DeActivate( "O2" );    // deactivate objective 2 through the optimizer

    // O3 active
    co.Evaluate( x );
    std::cout << "###############" << std::endl;
    std::cout << "Solution: \n" << x << std::endl;
    std::cout << "Residuals:" << std::endl;
    std::cout << objective3.GetName() << ": "
	      << objective3.Residuals( x ) << std::endl << std::endl;

    // Create an equality constraint with 2 equations
    Equality equality1( "E1", osaObjective::ACTIVE );
    {
	vctDynamicMatrix<double> E( 2, 4, VCT_COL_MAJOR );
	E[0][0] = 0.2027; E[0][1] = 0.2721; E[0][2] = 0.7467; E[0][3] = 0.4659;
	E[1][0] = 0.1987; E[1][1] = 0.1988; E[1][2] = 0.4450; E[1][3] = 0.4186;
	equality1.SetCoefficientMatrix( E );

	vctDynamicVector<double> f( 2 );
	f[0] = 0.5251;
	f[1] = 0.2026;
	equality1.SetRHSV( f );
    }
    co.Insert( &equality1 );

    // Create an equality constraint with 2 equations
    Equality equality2( "E2", osaObjective::INACTIVE );
    {
	vctDynamicMatrix<double> E( 1, 4, VCT_COL_MAJOR );
	E[0][0] = 0.6037; E[0][1] = 0.0152; E[0][2] = 0.9318; E[0][3] = 0.8462;
	equality2.SetCoefficientMatrix( E );

	vctDynamicVector<double> f( 1 );
	f[0] = 0.6721;
	equality2.SetRHSV( f );
    }
    co.Insert( &equality2 );

    // O3, E1 active
    co.Evaluate( x );
    std::cout << "###############" << std::endl;
    std::cout << "Solution: \n" << x << std::endl;
    std::cout << "Residuals:" << std::endl;
    std::cout << objective3.GetName() << ": "
	      << objective3.Residuals( x ) << std::endl
	      << equality1.GetName() << ": "
	      << equality1.Residuals( x ) << std::endl << std::endl;

    // Activate E2
    co.Activate( "E2" );
    co.Evaluate( x );
    std::cout << "###############" << std::endl;
    std::cout << "Solution: \n" << x << std::endl;
    std::cout << "Residuals:" << std::endl;
    std::cout << objective3.GetName() << ": "
	      << objective3.Residuals( x ) << std::endl
	      << equality1.GetName() << ": "
	      << equality1.Residuals( x ) << std::endl
	      << equality2.GetName() << ": "
	      << equality2.Residuals( x ) << std::endl << std::endl;

    // Create an inequality
    Inequality inequality1( "I1", osaObjective::ACTIVE );
    {
	vctDynamicMatrix<double> G( 4, 4, VCT_COL_MAJOR );
	G[0][0] = 1.0; G[0][1] = 0.0; G[0][2] = 0.0; G[0][3] = 0.0;
	G[1][0] = 0.0; G[1][1] = 1.0; G[1][2] = 0.0; G[1][3] = 0.0;
	G[2][0] = 0.0; G[2][1] = 0.0; G[2][2] = 1.0; G[2][3] = 0.0;
	G[3][0] = 0.0; G[3][1] = 0.0; G[3][2] = 0.0; G[3][3] = 1.0;
	inequality1.SetCoefficientMatrix( G );

	vctDynamicVector<double> h( 4, -1.0 );
	inequality1.SetRHSV( h );
    }
    co.Insert( &inequality1 );

    // O3, E1, E2, I1 active
    co.Evaluate( x );
    std::cout << "###############" << std::endl;
    std::cout << "Solution: \n" << x << std::endl;
    std::cout << "Residuals:" << std::endl;
    std::cout << objective3.GetName() << ": "
	      << objective3.Residuals( x ) << std::endl
	      << equality1.GetName() << ": "
	      << equality1.Residuals( x ) << std::endl
	      << equality2.GetName() << ": "
	      << equality2.Residuals( x ) << std::endl
	      << inequality1.GetName() << ": "
	      << inequality1.Residuals( x ) << std::endl << std::endl;

    equality1.DeActivate();
    equality2.DeActivate();
    inequality1.DeActivate();

    vctDynamicVector<double> lo( 4, 3.0 );
    vctDynamicVector<double> hi( 4, 5.0 );
    osaConstraintIntervals intervals( "T", lo, hi, osaObjective::ACTIVE );
    co.Insert( &intervals );
    co.Evaluate( x );
    std::cout << "###############" << std::endl;
    std::cout << "Solution: \n" << x << std::endl;

    return 0;
}
