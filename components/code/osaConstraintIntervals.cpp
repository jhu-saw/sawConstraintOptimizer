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

#include <sawConstraintOptimizer/osaConstraintIntervals.h>

osaConstraintIntervals::osaConstraintIntervals
( const std::string& name,
  const vctDynamicVector<double>& min,
  const vctDynamicVector<double>& max,
  osaEquation::Status status ) :
    osaConstraintInequality( name, status ){
    SetIntervals( min, max );
}


osaConstraintIntervals::Errno
osaConstraintIntervals::SetIntervals
( const vctDynamicVector<double>& min,
  const vctDynamicVector<double>& max ){

    if( min.size() != max.size() ) { return osaConstraintIntervals::EFAILURE; }

    vctDynamicMatrix<double> A( 2 * min.size(), min.size(), 0.0 );
    vctDynamicVector<double> b( 2 * min.size(), 0.0 );

    for( size_t i=0; i<min.size(); i++ ){
        A[i*2+0][i] =  1.0;    b[i*2+0] = min[i];
        A[i*2+1][i] = -1.0;    b[i*2+1] = -max[i];
    }

    SetCoefficientMatrix( A );
    SetRHSV( b );

    return osaConstraintIntervals::ESUCCESS;

}
