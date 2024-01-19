/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-    */
/* ex: set filetype=cpp softtabstop=4 shiftwidth=4 tabstop=4 cindent expandtab: */

/*
  Author(s):  Simon Leonard
  Created on: 2013

  (C) Copyright 2013-2024 Johns Hopkins University (JHU), All Rights Reserved.

--- begin cisst license - do not edit ---

This software is provided "as is" under an open source license, with
no warranty.  The complete license can be found in license.txt and
http://www.cisst.org/cisst/license.txt.

--- end cisst license ---
*/

#ifndef _osaConstrainedOptimization_h
#define _osaConstrainedOptimization_h

#include <map>

#include <cisstNumerical/nmrLSEISolver.h>
#include <sawConstraintOptimizer/osaEquation.h>
#include <sawConstraintOptimizer/osaObjective.h>
#include <sawConstraintOptimizer/osaConstraintEquality.h>
#include <sawConstraintOptimizer/osaConstraintInequality.h>
#include <sawConstraintOptimizer/sawConstraintOptimizerExport.h>

class osaConstrainedOptimization{

    enum Errno{ ESUCCESS, EFAILURE, ENEWSYSTEM };

private:

    vctDynamicMatrix<double> A, b;
    std::map< std::string, osaEquation* > objectives;

    vctDynamicMatrix<double> E, f;
    std::map< std::string, osaEquation* > equalities;

    vctDynamicMatrix<double> G, h;
    std::map< std::string, osaEquation* > inequalities;

    nmrLSEISolver lsei;

protected:


    size_t CountActiveObjectives() const;
    size_t CountActiveEqualities() const;
    size_t CountActiveInequalities() const;

    Errno ObjectivesDimension( size_t& dimension ) const;
    Errno EqualitiesDimension( size_t& dimension ) const;
    Errno InequalitiesDimension( size_t& dimension ) const;

    Errno UpdateObjectivesSystem();
    Errno UpdateEqualitiesSystem();
    Errno UpdateInequalitiesSystem();

    Errno UpdateObjectives();
    Errno UpdateEqualities();
    Errno UpdateInequalities();

public:

    osaConstrainedOptimization();

    Errno Evaluate( vctDynamicVector<double>& x );

    Errno Insert( osaEquation* equation );
    Errno Insert( osaObjective* objective );
    Errno Insert( osaConstraintEquality* equality );
    Errno Insert( osaConstraintInequality* inequality );

    Errno Remove( const std::string& name );
    Errno Remove( osaEquation* equation );
    Errno Remove( osaObjective* objective );
    Errno Remove( osaConstraintEquality* equality );
    Errno Remove( osaConstraintInequality* inequality );

    Errno Activate( const std::string& );
    Errno DeActivate( const std::string& );

};

#endif
