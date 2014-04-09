/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-    */
/* ex: set filetype=cpp softtabstop=4 shiftwidth=4 tabstop=4 cindent expandtab: */
/*
  $Id: osaConstraintPlane.h 4626 2013-12-19 14:56:58Z adeguet1 $

  Author(s):  Simon Leonard
  Created on: 2013

  (C) Copyright 2013 Johns Hopkins University (JHU), All Rights Reserved.

--- begin cisst license - do not edit ---

This software is provided "as is" under an open source license, with
no warranty.  The complete license can be found in license.txt and
http://www.cisst.org/cisst/license.txt.

--- end cisst license ---
*/

#ifndef _osaConstraintPlane_h
#define _osaConstraintPlane_h

#include <cisstVector/vctTransformationTypes.h>
#include <sawControllers/osaConstraintInequality.h>
#include <sawControllers/sawControllersExport.h>

class osaConstraintPlane : public osaConstraintInequality {

private:

protected:

public:
    osaConstraintPlane( const std::string& name,
                        const vctFixedSizeVector<double,4>& abcd,
                        osaEquation::Status status = osaEquation::ACTIVE ) :
        osaConstraintInequality( name, status ){
        SetPlane( abcd );
    }
    osaConstraintPlane( const std::string& name,
                        const vctFrame4x4<double>& Rt,
                        osaEquation::Status status = osaEquation::ACTIVE ) :
        osaConstraintInequality( name, status ){
        SetPlane( Rt );
    }

    virtual ~osaConstraintPlane(){};

    void SetPlane( const vctFrame4x4<double>& Rt ){
        vctFixedSizeVector<double,3> xyz = Rt.Translation();
        vctFixedSizeVector<double,4> abcd( 0.0 );
        abcd[0] = Rt[0][2];
        abcd[1] = Rt[1][2];
        abcd[2] = Rt[2][2];
        abcd[3] = ( abcd[0]*xyz[0] + abcd[1]*xyz[1] + abcd[2]*xyz[2] );
        SetPlane( abcd );
    }

    void SetPlane( const vctFixedSizeVector<double,4>& abcd ){
        vctDynamicMatrix<double> n( 1, 3, VCT_COL_MAJOR );
        n[0][0] = abcd[0]; n[0][1] = abcd[1]; n[0][2] = abcd[2];
        SetCoefficientMatrix( n );
        SetRHSV( vctDynamicVector<double>( 1, abcd[3] ) );
    }

};

#endif
