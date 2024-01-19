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

#ifndef _osaEquation_h
#define _osaEquation_h

#include <cisstVector/vctDynamicMatrix.h>
#include <cisstVector/vctDynamicVector.h>
#include <sawConstraintOptimizer/sawConstraintOptimizerExport.h>

class osaEquation{

public:

    enum Errno{ ESUCCESS, EFAILURE };

    enum Status{ ACTIVE, INACTIVE };

private:

    std::string name;
    Status status;
    vctDynamicMatrix<double> coefficients;
    vctDynamicVector<double> rhsv;

public:

    osaEquation( const std::string& name, Status status = ACTIVE ) :
        name( name ), status( status ){}
    virtual ~osaEquation(){}

    std::string GetName() const { return name; }

    bool IsActive() const { return status == ACTIVE; }
    void Activate() { status = ACTIVE; }
    void DeActivate() { status = INACTIVE; }

    size_t GetNumEquations() const { return coefficients.rows(); }
    size_t GetDimension() const { return coefficients.cols(); }

    virtual vctDynamicMatrix<double> GetCoefficientMatrix() const
    { return coefficients; }
    virtual void SetCoefficientMatrix( const vctDynamicMatrix<double>& C )
    { coefficients = C; }

    virtual vctDynamicVector<double> GetRHSV() const { return rhsv; }
    virtual void SetRHSV( const vctDynamicVector<double>& v )
    { rhsv = v; }

    vctDynamicVector<double> Residuals( const vctDynamicVector<double>& x ) const
    { return coefficients * x - rhsv; }

};

#endif
