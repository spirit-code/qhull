/****************************************************************************
**
** Copyright (c) 2008-2012 C.B. Barber. All rights reserved.
** $Id: //main/2011/qhull/src/libqhullpcpp/QhullError.h#3 $$Change: 1710 $
** $DateTime: 2014/03/28 22:23:20 $$Author: bbarber $
**
****************************************************************************/

#ifndef QHULLERROR_H
#define QHULLERROR_H

#include "RoadError.h"
// No dependencies on libqhull

#include <assert.h>
#include <stdexcept>
#include <string>

namespace orgQhull {

#//!\name Types
    //! QhullError -- std::exception class for Qhull
    class QhullError;

class QhullError : public RoadError {

public:
#//!\name Constants
    enum {
        QHULLfirstError= 10000, //MSG_QHULL_ERROR in Qhull's user.h
        QHULLlastError= 10073,
        NOthrow= 1 //! For flag to UsingLibQhull()
    };

#//!\name Constructors
    // default constructors
    QhullError() : RoadError() {};
    QhullError(const QhullError &other) : RoadError(other) {}
    QhullError(int code, const std::string &message) : RoadError(code, message) {};
    QhullError(int code, const char *fmt) : RoadError(code, fmt) {};
    QhullError(int code, const char *fmt, int d) : RoadError(code, fmt, d) {};
    QhullError(int code, const char *fmt, int d, int d2) : RoadError(code, fmt, d, d2) {};
    QhullError(int code, const char *fmt, int d, int d2, float f) : RoadError(code, fmt, d, d2, f) {};
    QhullError(int code, const char *fmt, int d, int d2, float f, const char *s) : RoadError(code, fmt, d, d2, f, s) {};
    QhullError(int code, const char *fmt, int d, int d2, float f, const void *x) : RoadError(code, fmt, d, d2, f, x) {};
    QhullError(int code, const char *fmt, int d, int d2, float f, int i) : RoadError(code, fmt, d, d2, f, i) {};
    QhullError(int code, const char *fmt, int d, int d2, float f, long long i) : RoadError(code, fmt, d, d2, f, i) {};
    QhullError(int code, const char *fmt, int d, int d2, float f, double e) : RoadError(code, fmt, d, d2, f, e) {};
    QhullError &operator=(const QhullError &other) { this->RoadError::operator=(other); return *this; }
    ~QhullError() throw() {}

};//class QhullError

#ifndef QHULL_1
    #define QHULL_ASSERT assert

#endif

}//namespace orgQhull

#//!\name Global

inline std::ostream &operator<<(std::ostream &os, const orgQhull::QhullError &e) { return os << e.what(); }

#endif // QHULLERROR_H
