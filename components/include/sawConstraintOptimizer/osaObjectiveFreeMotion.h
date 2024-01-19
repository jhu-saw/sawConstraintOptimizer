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

#ifndef _osaObjectiveFreeMotion_h
#define _osaObjectiveFreeMotion_h

#include <sawConstraintOptimizer/osaObjective.h>
#include <sawConstraintOptimizer/sawConstraintOptimizerExport.h>

class CISST_EXPORT osaObjectiveFreeMotion: public osaObjective
{

 public:

    osaObjectiveFreeMotion(const std::string& name,
                           osaEquation::Status status = osaEquation::ACTIVE):
        osaObjective(name, status)
    {
        SetCoefficientMatrix(vctDynamicMatrix<double>::Eye(3));
        SetRHSV( vctDynamicVector<double>(3, 0.0));
    }

    virtual ~osaObjectiveFreeMotion()
    {}

    void SetObjective(const vctFixedSizeVector<double,3>& t) {
        SetRHSV(vctDynamicVector<double>(3, t[0], t[1], t[2]));
    }
};

#endif
