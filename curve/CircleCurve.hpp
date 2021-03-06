/*  MoTo - Motion Toolkit
    Copyright (c) 2016 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef CV_CIRCLECURVE_HPP
#define CV_CIRCLECURVE_HPP

#include "Curve.hpp"

namespace cv
{
    class CircleCurve
        : public Curve
    {
    public:
        CircleCurve(const Vector3& center, Scalar radius)
            : mCenter(center)
            , mRadius(radius)
        {}

        virtual DualVector3 eval(Scalar param) const OVERRIDE;

    private:
        Vector3 mCenter;
        Scalar mRadius;
    };
}


#endif
