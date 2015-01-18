/****************************************************************************
**
** Copyright (c) 2009-2014 C.B. Barber. All rights reserved.
** $Id: //main/2011/qhull/src/libqhullcpp/QhullHyperplane.cpp#10 $$Change: 1797 $
** $DateTime: 2014/12/15 17:23:41 $$Author: bbarber $
**
****************************************************************************/

#include "QhullHyperplane.h"

#include "Qhull.h"
#include "QhullPoint.h"

#include <iostream>


#ifdef _MSC_VER  // Microsoft Visual C++ -- warning level 4
#endif

namespace orgQhull {

#//!\name Constructors

QhullHyperplane::
QhullHyperplane(const Qhull &q) 
: hyperplane_coordinates(0)
, hyperplane_dimension(0)
, hyperplane_offset(0.0)
, qh_qh(q.qh())
{
}

QhullHyperplane::
QhullHyperplane(const Qhull &q, int hyperplaneDimension, coordT *c, coordT hyperplaneOffset) 
: hyperplane_coordinates(c)
, hyperplane_dimension(hyperplaneDimension)
, hyperplane_offset(hyperplaneOffset)
, qh_qh(q.qh())
{
}

#//!\name Conversions

// See qt-qhull.cpp for QList conversions

#ifndef QHULL_NO_STL
std::vector<coordT> QhullHyperplane::
toStdVector() const
{
    QhullHyperplaneIterator i(*this);
    std::vector<coordT> fs;
    while(i.hasNext()){
        fs.push_back(i.next());
    }
    fs.push_back(hyperplane_offset);
    return fs;
}//toStdVector
#endif //QHULL_NO_STL

#//!\name GetSet

bool QhullHyperplane::
operator==(const QhullHyperplane &other) const
{
    if(hyperplane_dimension!=other.hyperplane_dimension){
        return false;
    }
    double d= fabs(hyperplane_offset-other.hyperplane_offset);
    if(d>qh_qh->distanceEpsilon()){
        return false;
    }
    const coordT *c= hyperplane_coordinates;
    const coordT *c2= other.hyperplane_coordinates;
    if(c==c2){
        return true;
    }
    double dist2= 0.0;
    for(int k= hyperplane_dimension; k--; ){
        double diff= *c++ - *c2++;
        dist2 += diff*diff;
    }
    if(dist2 > qh_qh->angleEpsilon()){
        return false;
    }
    return true;
}//operator==

#//!\name Methods

//! Return distance from point to hyperplane.
//!   If greater than zero, the point is above the facet (i.e., outside).
// qh_distplane [geom_r.c], QhullFacet::distance, and QhullHyperplane::distance are copies
//    Does not support RANDOMdist or logging
double QhullHyperplane::
distance(const QhullPoint &p) const
{
    const coordT *point= p.coordinates();
    int dim= p.dimension();
    QHULL_ASSERT(dim==dimension());
    const coordT *normal= coordinates();
    double dist;

    switch (dim){
  case 2:
      dist= offset() + point[0] * normal[0] + point[1] * normal[1];
      break;
  case 3:
      dist= offset() + point[0] * normal[0] + point[1] * normal[1] + point[2] * normal[2];
      break;
  case 4:
      dist= offset()+point[0]*normal[0]+point[1]*normal[1]+point[2]*normal[2]+point[3]*normal[3];
      break;
  case 5:
      dist= offset()+point[0]*normal[0]+point[1]*normal[1]+point[2]*normal[2]+point[3]*normal[3]+point[4]*normal[4];
      break;
  case 6:
      dist= offset()+point[0]*normal[0]+point[1]*normal[1]+point[2]*normal[2]+point[3]*normal[3]+point[4]*normal[4]+point[5]*normal[5];
      break;
  case 7:
      dist= offset()+point[0]*normal[0]+point[1]*normal[1]+point[2]*normal[2]+point[3]*normal[3]+point[4]*normal[4]+point[5]*normal[5]+point[6]*normal[6];
      break;
  case 8:
      dist= offset()+point[0]*normal[0]+point[1]*normal[1]+point[2]*normal[2]+point[3]*normal[3]+point[4]*normal[4]+point[5]*normal[5]+point[6]*normal[6]+point[7]*normal[7];
      break;
  default:
      dist= offset();
      for (int k=dim; k--; )
          dist += *point++ * *normal++;
      break;
    }
    return dist;
}//distance

double QhullHyperplane::
norm() const {
    double d= 0.0;
    const coordT *c= coordinates();
    for (int k=dimension(); k--; ){
        d += *c * *c;
        ++c;
    }
    return sqrt(d);
}//norm

}//namespace orgQhull

#//!\name Global functions

using std::ostream;
using orgQhull::QhullHyperplane;

#//!\name GetSet<<

ostream &
operator<<(ostream &os, const QhullHyperplane &p)
{
    os << p.print();
    return os;
}

ostream &
operator<<(ostream &os, const QhullHyperplane::PrintHyperplane &pr)
{
    if(pr.print_message){
        os << pr.print_message;
    }
    QhullHyperplane p= *pr.hyperplane;
    const realT *c= p.coordinates();
    for(int k=p.dimension(); k--; ){
        realT r= *c++;
        if(pr.print_message){
            os << " " << r; // FIXUP QH11010 %8.4g
        }else{
            os << " " << r; // FIXUP QH11010 qh_REAL_1
        }
    }
    if(pr.hyperplane_offset_message){
        os << pr.hyperplane_offset_message << " " << p.offset();
    }else{
        os << " " << p.offset();
    }
    os << std::endl;
    return os;
}//PrintHyperplane

