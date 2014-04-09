/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-    */
/* ex: set filetype=cpp softtabstop=4 shiftwidth=4 tabstop=4 cindent expandtab: */

/*
  $Id: osaConstrainedOptimization.cpp 4605 2013-12-12 21:37:52Z adeguet1 $

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

osaConstrainedOptimization::osaConstrainedOptimization(){}

osaConstrainedOptimization::Errno
osaConstrainedOptimization::Insert
( osaEquation* e ){

    if( e == NULL ){ return osaConstrainedOptimization::EFAILURE; }

    if( e->GetName().empty() ) { return osaConstrainedOptimization::EFAILURE; }

    osaObjective* o = dynamic_cast< osaObjective* >( e );
    if( o != NULL ){ Insert( o ); }

    osaConstraintEquality* ce = dynamic_cast< osaConstraintEquality* >( e );
    if( ce != NULL ){ Insert( ce ); }

    osaConstraintInequality* ci = dynamic_cast< osaConstraintInequality* >( e );
    if( ci != NULL ){ return Insert( ci ); }

    return osaConstrainedOptimization::EFAILURE;

}

osaConstrainedOptimization::Errno
osaConstrainedOptimization::Insert
( osaObjective* o ){
    std::pair< std::map<std::string, osaEquation*>::iterator, bool> r;
    std::pair< std::string, osaEquation* > entry( o->GetName(), o );
    r = objectives.insert( entry );

    if( r.second ) { return osaConstrainedOptimization::ESUCCESS; }
    return osaConstrainedOptimization::EFAILURE;

}

osaConstrainedOptimization::Errno
osaConstrainedOptimization::Insert
( osaConstraintEquality* ce ){
    std::pair< std::map<std::string, osaEquation*>::iterator, bool> r;
    std::pair< std::string, osaEquation* > entry( ce->GetName(), ce );
    r = equalities.insert( entry );

    if( r.second ) { return osaConstrainedOptimization::ESUCCESS; }
    return osaConstrainedOptimization::EFAILURE;

}

osaConstrainedOptimization::Errno
osaConstrainedOptimization::Insert
( osaConstraintInequality* ci ){
    std::pair< std::map<std::string,osaEquation*>::iterator, bool> r;
    std::pair< std::string,osaEquation* > entry( ci->GetName(), ci );
    inequalities.insert( entry );

    if( r.second ) { return osaConstrainedOptimization::ESUCCESS; }
    return osaConstrainedOptimization::EFAILURE;

}

osaConstrainedOptimization::Errno
osaConstrainedOptimization::Remove
( const std::string& name ){
    if( 0 < ( objectives.erase( name ) +
              equalities.erase( name ) +
              inequalities.erase( name ) ) )
        { return osaConstrainedOptimization::ESUCCESS; }
    return osaConstrainedOptimization::EFAILURE;
}


osaConstrainedOptimization::Errno
osaConstrainedOptimization::Remove
( osaEquation* eq )
{ return Remove( eq->GetName() ); }

osaConstrainedOptimization::Errno
osaConstrainedOptimization::Remove
( osaObjective* eq ){
    if( 0 < objectives.erase( eq->GetName() ) )
        { return osaConstrainedOptimization::ESUCCESS; }
    return osaConstrainedOptimization::EFAILURE;
}

osaConstrainedOptimization::Errno
osaConstrainedOptimization::Remove
( osaConstraintEquality* eq ){
    if( 0 < equalities.erase( eq->GetName() ) )
        { return osaConstrainedOptimization::ESUCCESS; }
    return osaConstrainedOptimization::EFAILURE;
}

osaConstrainedOptimization::Errno
osaConstrainedOptimization::Remove
( osaConstraintInequality* eq ){
    if( 0 < inequalities.erase( eq->GetName() ) )
        { return osaConstrainedOptimization::ESUCCESS; }
    return osaConstrainedOptimization::EFAILURE;
}

osaConstrainedOptimization::Errno
osaConstrainedOptimization::Activate
( const std::string& name ){

    std::map< std::string, osaEquation* >::iterator o = objectives.find( name );
    if( o != objectives.end() ) { o->second->Activate(); }

    std::map< std::string, osaEquation* >::iterator e = equalities.find( name );
    if( e != equalities.end() ) { e->second->Activate(); }

    std::map< std::string, osaEquation* >::iterator i = inequalities.find( name );
    if( i != inequalities.end() ) { i->second->Activate(); }

    if( o!=objectives.end() || e!=equalities.end() || i!=inequalities.end() )
        { return osaConstrainedOptimization::ESUCCESS; }
    return osaConstrainedOptimization::EFAILURE;

}

osaConstrainedOptimization::Errno
osaConstrainedOptimization::DeActivate
( const std::string& name ){

    std::map< std::string, osaEquation* >::iterator o = objectives.find( name );
    if( o != objectives.end() ) { o->second->DeActivate(); }

    std::map< std::string, osaEquation* >::iterator e = equalities.find( name );
    if( e != equalities.end() ) { e->second->DeActivate(); }

    std::map< std::string, osaEquation* >::iterator i = inequalities.find( name );
    if( i != inequalities.end() ) { i->second->DeActivate(); }

    if( o!=objectives.end() || e!=equalities.end() || i!=inequalities.end() )
        { return osaConstrainedOptimization::ESUCCESS; }
    return osaConstrainedOptimization::EFAILURE;

}

size_t osaConstrainedOptimization::CountActiveObjectives() const {
    size_t cnt=0;
    std::map<std::string,osaEquation*>::const_iterator oi;
    for( oi=objectives.begin(); oi!=objectives.end(); oi++ ){
        if( oi->second->IsActive() ) { cnt += oi->second->GetNumEquations(); }
    }
    return cnt;
}

size_t osaConstrainedOptimization::CountActiveEqualities() const {
    size_t cnt=0;
    std::map<std::string,osaEquation*>::const_iterator ei;
    for( ei=equalities.begin(); ei!=equalities.end(); ei++ ){
        if( ei->second->IsActive() ) { cnt += ei->second->GetNumEquations(); }
    }
    return cnt;
}

size_t osaConstrainedOptimization::CountActiveInequalities() const {
    size_t cnt=0;
    std::map<std::string,osaEquation*>::const_iterator ii;
    for( ii=inequalities.begin(); ii!=inequalities.end(); ii++ ){
        if( ii->second->IsActive() ) { cnt += ii->second->GetNumEquations(); }
    }
    return cnt;
}

osaConstrainedOptimization::Errno
osaConstrainedOptimization::ObjectivesDimension
( size_t& N ) const {

    N = 0;

    // search for the first active constraint
    std::map<std::string, osaEquation*>::const_iterator oi;
    for( oi=objectives.begin(); oi!=objectives.end(); oi++ ){
        if( oi->second->IsActive() ){
            N = oi->second->GetDimension();
            break;
        }
    }

    // ensure that all active constraints have the same dimension
    for( oi=objectives.begin(); oi!=objectives.end(); oi++ ){
        if( oi->second->IsActive() ){
            if( N != oi->second->GetDimension() )
                { return osaConstrainedOptimization::EFAILURE; }
        }
    }

    return osaConstrainedOptimization::ESUCCESS;

}

osaConstrainedOptimization::Errno
osaConstrainedOptimization::EqualitiesDimension
( size_t& N ) const {

    N = 0;

    // search for the first active constraint
    std::map<std::string, osaEquation*>::const_iterator ei;
    for( ei=equalities.begin(); ei!=equalities.end(); ei++ ){
        if( ei->second->IsActive() ){
            N = ei->second->GetDimension();
            break;
        }
    }

    // ensure that all active constraints have the same dimension
    for( ei=equalities.begin(); ei!=equalities.end(); ei++ ){
        if( ei->second->IsActive() ){
            if( N != ei->second->GetDimension() )
                { return osaConstrainedOptimization::EFAILURE; }
        }
    }

    return osaConstrainedOptimization::ESUCCESS;

}

osaConstrainedOptimization::Errno
osaConstrainedOptimization::InequalitiesDimension
( size_t& N ) const {

    N = 0;

    // search for the first active constraint
    std::map<std::string, osaEquation*>::const_iterator ii;
    for( ii=inequalities.begin(); ii!=inequalities.end(); ii++ ){
        if( ii->second->IsActive() ){
            N = ii->second->GetDimension();
            break;
        }
    }

    // ensure that all active constraints have the same dimension
    for( ii=inequalities.begin(); ii!=inequalities.end(); ii++ ){
        if( ii->second->IsActive() ){
            if( N != ii->second->GetDimension() )
                { return osaConstrainedOptimization::EFAILURE; }
        }
    }

    return osaConstrainedOptimization::ESUCCESS;

}

osaConstrainedOptimization::Errno
osaConstrainedOptimization::UpdateObjectivesSystem(){

    size_t M = CountActiveObjectives();
    if( M == 0 ){
        A = vctDynamicMatrix<double>();
        b = vctDynamicMatrix<double>();
        return osaConstrainedOptimization::ENEWSYSTEM;
    }

    size_t N;
    if( ObjectivesDimension( N ) != osaConstrainedOptimization::ESUCCESS )
        { return osaConstrainedOptimization::EFAILURE; }

    if( N == 0 ){
        A = vctDynamicMatrix<double>();
        b = vctDynamicMatrix<double>();
        return osaConstrainedOptimization::ENEWSYSTEM;
    }

    bool modified=false;
    if( A.rows() != M || A.cols() != N ){
        A.SetSize( M, N, VCT_COL_MAJOR );
        modified=true;
    }
    if( b.rows() != M || b.cols() != 1 ){
        b.SetSize( M, 1, VCT_COL_MAJOR );
        modified=true;
    }

    if( modified ) { return osaConstrainedOptimization::ENEWSYSTEM; }
    return osaConstrainedOptimization::ESUCCESS;

}

osaConstrainedOptimization::Errno
osaConstrainedOptimization::UpdateEqualitiesSystem(){

    size_t M = CountActiveEqualities();

    if( M == 0 ){
        E = vctDynamicMatrix<double>();
        f = vctDynamicMatrix<double>();
        return osaConstrainedOptimization::ENEWSYSTEM;
    }

    size_t N;
    if( EqualitiesDimension( N ) != osaConstrainedOptimization::ESUCCESS )
        { return osaConstrainedOptimization::EFAILURE; }

    if( N == 0 ){
        E = vctDynamicMatrix<double>();
        f = vctDynamicMatrix<double>();
        return osaConstrainedOptimization::ENEWSYSTEM;
    }

    bool modified=false;
    if( E.rows() != M || E.cols() != N ){
        E.SetSize( M, N, VCT_COL_MAJOR );
        modified = true;
    }
    if( f.rows() != M || f.cols() != 1 ){
        f.SetSize( M, 1, VCT_COL_MAJOR );
        modified = true;
    }

    if( modified ) { return osaConstrainedOptimization::ENEWSYSTEM; }
    return osaConstrainedOptimization::ESUCCESS;

}

osaConstrainedOptimization::Errno
osaConstrainedOptimization::UpdateInequalitiesSystem(){

    size_t M = CountActiveInequalities();
    if( M == 0 ){
        G = vctDynamicMatrix<double>();
        h = vctDynamicMatrix<double>();
        return osaConstrainedOptimization::ENEWSYSTEM;
    }

    size_t N;
    if( InequalitiesDimension( N ) != osaConstrainedOptimization::ESUCCESS )
        { return osaConstrainedOptimization::EFAILURE; }

    if( N == 0 ){
        G = vctDynamicMatrix<double>();
        h = vctDynamicMatrix<double>();
        return osaConstrainedOptimization::ENEWSYSTEM;
    }

    bool modified=false;
    if( G.rows() != M || G.cols() != N ){
        G.SetSize( M, N, VCT_COL_MAJOR );
        modified = true;
    }
    if( h.rows() != M || h.cols() != 1 ){
        h.SetSize( M, 1, VCT_COL_MAJOR );
        modified = true;
    }

    if( modified ) { return osaConstrainedOptimization::ENEWSYSTEM; }
    return osaConstrainedOptimization::ESUCCESS;

}

osaConstrainedOptimization::Errno
osaConstrainedOptimization::UpdateObjectives(){

    osaConstrainedOptimization::Errno errNo = UpdateObjectivesSystem();
    if( errNo == osaConstrainedOptimization::EFAILURE ){
        return osaConstrainedOptimization::EFAILURE;
    }

    size_t R = 0;
    std::map<std::string,osaEquation*>::const_iterator oi;
    for( oi=objectives.begin(); oi!=objectives.end(); oi++ ){
        if( oi->second->IsActive() ){
            vctDynamicMatrix<double> Ai = oi->second->GetCoefficientMatrix();
            vctDynamicVector<double> bi = oi->second->GetRHSV();

            for( size_t r=0; r<Ai.rows(); r++, R++ ){
                for( size_t c=0; c<Ai.cols(); c++ )
                    { A[R][c] = Ai[r][c]; }
                b[R] = bi[r];
            }
        }
    }

    return errNo;

}

osaConstrainedOptimization::Errno
osaConstrainedOptimization::UpdateEqualities(){

    osaConstrainedOptimization::Errno errNo = UpdateEqualitiesSystem();
    if( errNo == osaConstrainedOptimization::EFAILURE )
        { return osaConstrainedOptimization::EFAILURE; }

    size_t R = 0;
    std::map<std::string,osaEquation*>::const_iterator ei;
    for( ei=equalities.begin(); ei!=equalities.end(); ei++ ){
        if( ei->second->IsActive() ){
            vctDynamicMatrix<double> Ei = ei->second->GetCoefficientMatrix();
            vctDynamicVector<double> fi = ei->second->GetRHSV();

            for( size_t r=0; r<Ei.rows(); r++, R++ ){
                for( size_t c=0; c<Ei.cols(); c++ )
                    { E[R][c] = Ei[r][c]; }
                f[R] = fi[r];
            }

        }
    }

    return errNo;

}

osaConstrainedOptimization::Errno
osaConstrainedOptimization::UpdateInequalities(){

    osaConstrainedOptimization::Errno errNo = UpdateInequalitiesSystem();
    if( errNo == osaConstrainedOptimization::EFAILURE )
        { return osaConstrainedOptimization::EFAILURE; }

    size_t R = 0;
    std::map<std::string,osaEquation*>::const_iterator ii;
    for( ii=inequalities.begin(); ii!=inequalities.end(); ii++ ){
        if( ii->second->IsActive() ){
            vctDynamicMatrix<double> Gi = ii->second->GetCoefficientMatrix();
            vctDynamicVector<double> hi = ii->second->GetRHSV();

            for( size_t r=0; r<Gi.rows(); r++, R++ ){
                for( size_t c=0; c<Gi.cols(); c++ )
                    { G[R][c] = Gi[r][c]; }
                h[R] = hi[r];
            }
        }
    }

    return errNo;

}


osaConstrainedOptimization::Errno
osaConstrainedOptimization::Evaluate
( vctDynamicVector<double>& x ) {

    osaConstrainedOptimization::Errno errNo1 = UpdateObjectives();
    if( errNo1 == osaConstrainedOptimization::EFAILURE )
        { return osaConstrainedOptimization::EFAILURE; }

    osaConstrainedOptimization::Errno errNo2 = UpdateEqualities();
    if( errNo2 == osaConstrainedOptimization::EFAILURE )
        { return osaConstrainedOptimization::EFAILURE; }

    osaConstrainedOptimization::Errno errNo3 = UpdateInequalities();
    if( errNo3 == osaConstrainedOptimization::EFAILURE )
        { return osaConstrainedOptimization::EFAILURE; }

    if( errNo1 == osaConstrainedOptimization::ENEWSYSTEM ||
        errNo2 == osaConstrainedOptimization::ENEWSYSTEM ||
        errNo3 == osaConstrainedOptimization::ENEWSYSTEM )
        { lsei.Allocate( E, A, G ); }

    lsei.Solve( E, f, A, b, G, h );

    const vctDynamicMatrix<double>& X = lsei.GetX();
    if( x.size() != X.rows() ) { x.SetSize( X.rows() ); }
    for( size_t i=0; i<X.rows(); i++ ) { x[i] = X[i][0]; }

    return osaConstrainedOptimization::ESUCCESS;

}

