/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-    */
/* ex: set filetype=cpp softtabstop=4 shiftwidth=4 tabstop=4 cindent expandtab: */
/*
  $Id: osaConstraintIntervals.h 4605 2013-12-12 21:37:52Z adeguet1 $

  Author(s):  Simon Leonard
  Created on: 2013

  (C) Copyright 2013 Johns Hopkins University (JHU), All Rights Reserved.

--- begin cisst license - do not edit ---

This software is provided "as is" under an open source license, with
no warranty.  The complete license can be found in license.txt and
http://www.cisst.org/cisst/license.txt.

--- end cisst license ---
*/

#ifndef _osaConstraintIntervals_h
#define _osaConstraintIntervals_h

#include <sawConstraintController/osaConstraintInequality.h>
#include <sawConstraintController/sawConstraintControllerExport.h>

class osaConstraintIntervals : public osaConstraintInequality {

private:

protected:

public:

    osaConstraintIntervals( const std::string& name,
                            const vctDynamicVector<double>& min,
                            const vctDynamicVector<double>& max,
                            osaEquation::Status status = osaEquation::ACTIVE );

    Errno SetIntervals( const vctDynamicVector<double>& min,
                        const vctDynamicVector<double>& max );

};

#endif