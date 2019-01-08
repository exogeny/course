/*
-----------------------------------------------------------------------
This source file is part of "cgcourse-examples"
(Examples for Computer Graphics Course of CCCE GUCAS.)
Copyright (C) 2011 Xue Jian (jian.xue.cn@gmail.com)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------
*/

#ifndef __quaternion_h
#define __quaternion_h

#include <assert.h>
#include "matrix.h"

template <typename T> class Quaternion
{
public:
    typedef FloatTraits<T> TraitsType;

    // quaternion representation (w, xi, yj, zk)
    T   x,y,z,w;

    ///////////////////////////////////////////////////////////////////////////
    /// Default constructor. Construct a quaternion with zero rotation.
    ///////////////////////////////////////////////////////////////////////////
    Quaternion()
    {
        this->Identity();
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Construct a quaternion from given values. Quat will 
    /// be normalized. Will perform a valid check.
    ///////////////////////////////////////////////////////////////////////////
    Quaternion(T const x, T const y, T const z, T const w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;

        this->Normalize();
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Construct a quaternion from euler angles in degrees.
    /// \param x rotation around x-axis in degrees
    /// \param y rotation around y-axis in degrees
    /// \param z rotation around z-axis in degrees
    ///////////////////////////////////////////////////////////////////////////
    Quaternion(T const x, T const y, T const z)
    {
        this->EulerDegToQuat(x, y, z);
    }

    //////////////////////////////////////////////////////////////////////////
    /// "=" operator.
    //////////////////////////////////////////////////////////////////////////
    Quaternion& operator=(Quaternion const &q)  
    {
        x = q.x;
        y = q.y;
        z = q.z;
        w = q.w;
        return (*this); 
    }

    //////////////////////////////////////////////////////////////////////////
    /// Copy constructor.
    //////////////////////////////////////////////////////////////////////////
    Quaternion(Quaternion const &q)                    
    {
        x = q.x;
        y = q.y;
        z = q.z;
        w = q.w;
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Set this quaternion to the identity quaternion.
    ///////////////////////////////////////////////////////////////////////////
    void Identity()
    {
        x   = 0.0f;
        y   = 0.0f;
        z   = 0.0f;
        w   = 1.0f;
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Normalize this quaternion.
    ///////////////////////////////////////////////////////////////////////////
    void Normalize()
    {
        double norm = this->_norm();

        if(norm <= 0.0)    norm = 1.0;

        x = T(x / norm);
        y = T(y / norm);
        z = T(z / norm);
        w = T(w / norm);
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the values of this quaternion.
    ///////////////////////////////////////////////////////////////////////////
    void GetValues(T &x, T &y, T &z, T &w) const
    {
        x = this->x;
        y = this->y;
        z = this->z;

        w = this->w;
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Convert an axis angle to quaternion, angle is in radians.
    /// \param ax the x-coordinate of rotation axis
    /// \param ay the y-coordinate of rotation axis
    /// \param az the z-coordinate of rotation axis
    /// \param angle the angle of rotation in radians
    ///////////////////////////////////////////////////////////////////////////
    void AxisRadToQuat(T const ax, T const ay, T const az, T const angle)
    {
        T xx,yy,zz;         // temp vars of vector
        double rad, scale;      // temp vars
        double length;

        length = sqrt( SQR(ax) + SQR(ay) + SQR(az));

        if (TraitsType::FLOAT_EQ(0.0,length))           // if axis is zero, then return quaternion (1,0,0,0)
        {
            w   = T(1);
            x   = T(0);
            y   = T(0);
            z   = T(0);

            return;
        }

        if(TraitsType::FLOAT_EQ(1.0,length))
        {
            xx = ax;
            yy = ay;
            zz = az;
        }
        else
        {
            xx = ax / T(length);
            yy = ay / T(length);
            zz = az / T(length);
        }

        rad     = angle / 2;

        w       = T(cos(rad));

        scale   = sin(rad);

        x = T(xx * scale);
        y = T(yy * scale);
        z = T(zz * scale);

        this->Normalize();      // make sure a unit quaternion turns up

        return;
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Convert an axis angle to quaternion, angle is in degrees.
    /// \param ax the x-coordinate of rotation axis
    /// \param ay the y-coordinate of rotation axis
    /// \param az the z-coordinate of rotation axis
    /// \param angle the angle of rotation in degrees
    ///////////////////////////////////////////////////////////////////////////
    void AxisDegToQuat(T const ax, T const ay, T const az, T const angle)
    {
        T redAng = T(DEGTORAD(angle - (int)(angle / 360.0) * 360.0));
        this->AxisRadToQuat(ax, ay, az, redAng);    
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Get an axis angle from this quaternion, angle is returned in radians.
    /// \param ax return the x-coordinate of rotation axis
    /// \param ay return the y-coordinate of rotation axis
    /// \param az return the z-coordinate of rotation axis
    /// \param angle return the angle of rotation in radians
    ///////////////////////////////////////////////////////////////////////////
    void GetAxisRad(T &ax, T &ay, T &az, T &angle) const
    {
        double  temp_angle;     // temp angle
        double  scale;          // temp vars
        double  length;

        temp_angle = acos(w);

        //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        // Another version where scale is sqrt (x2 + y2 + z2)
        //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        //  scale = (float)sqrt(SQR(x) + SQR(y) + SQR(z));
        scale = sin(temp_angle);

        assert(0 <= temp_angle);        // make sure angle is 0 - PI
        assert(FloatTraits<double>::PI() >= temp_angle);

        if (TraitsType::FLOAT_EQ(0.0, scale))       // angle is 0 or 360 so just simply set axis to 0,0,1 with angle 0
        {
            angle = T(0);

            // any axis will do
            ax = T(0);
            ay = T(0);
            az = T(1);
        }
        else
        {
            angle = T(temp_angle * 2.0);        // angle in radians

            ax = T(x / scale);
            ay = T(y / scale);
            az = T(z / scale);
            length = sqrt(SQR(ax) + SQR(ay) + SQR(az));
            if(length <= 0.0)    length = 1.0;
            ax = ax / T(length);
            ay = ay / T(length);
            az = az / T(length);

            assert(0.0f <= angle);          // make sure rotation around axis is 0 - 360
            assert(2*TraitsType::PI() >= angle);
            //        angle = (float)RADTODEG(angle);
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Get an axis angle from this quaternion, angle is returned in degrees.
    /// \param ax return the x-coordinate of rotation axis
    /// \param ay return the y-coordinate of rotation axis
    /// \param az return the z-coordinate of rotation axis
    /// \param angle return the angle of rotation in degrees
    ///////////////////////////////////////////////////////////////////////////
    void GetAxisDeg(T &ax, T &ay, T &az, T &angle) const
    {
        this->GetAxisRad(ax, ay, az, angle);
        angle = (float)RADTODEG(angle);
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Convert euler angles to quaternion, euler angles are in radians.
    /// \param xr rotation around x-axis in radians
    /// \param yr rotation around y-axis in radians
    /// \param zr rotation around z-axis in radians
    ///////////////////////////////////////////////////////////////////////////
    void EulerRadToQuat(T const xr, T const yr, T const zr)
    {
        double  ex, ey, ez;     // temp half euler angles
        double  cr, cp, cy, sr, sp, sy, cpcy, spsy;     // temp vars in roll,pitch yaw

        ex = xr / 2.0;  // convert to rads and half them
        ey = yr / 2.0;
        ez = zr / 2.0;

        cr = cos(ex);
        cp = cos(ey);
        cy = cos(ez);

        sr = sin(ex);
        sp = sin(ey);
        sy = sin(ez);

        cpcy = cp * cy;
        spsy = sp * sy;

        this->w = T(cr * cpcy + sr * spsy);

        this->x = T(sr * cpcy - cr * spsy);
        this->y = T(cr * sp * cy + sr * cp * sy);
        this->z = T(cr * cp * sy - sr * sp * cy);

        this->Normalize();
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Convert euler angles to quaternion, euler angles are in degrees.
    /// \param xd rotation around x-axis in degrees
    /// \param yd rotation around y-axis in degrees
    /// \param zd rotation around z-axis in degrees
    ///////////////////////////////////////////////////////////////////////////
    void EulerDegToQuat(T const xd, T const yd, T const zd)
    {
        this->EulerRadToQuat(DEGTORAD(xd - (int)(xd / 360.0) * 360.0), 
            DEGTORAD(yd - (int)(yd / 360.0) * 360.0), 
            DEGTORAD(zd - (int)(zd / 360.0) * 360.0));
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Get euler angles from this quaternion, angle is returned in radians.
    /// \param xr return the rotation around x-axis in radians
    /// \param yr return the rotation around y-axis in radians
    /// \param zr return the rotation around z-axis in radians
    ///////////////////////////////////////////////////////////////////////////
    void GetEulerRad(T &xr, T &yr, T &zr) const
    {
        double sqx = SQR(x);
        double sqy = SQR(y);
        double sqz = SQR(z);
        double sqw = SQR(w);

        xr = T(atan2(2.0*(y*z + x*w), sqz+sqw-sqx-sqy));
        yr = T(asin(2.0*(y*w - x*z)));
        zr = T(atan2(2.0*(x*y + z*w), sqx-sqy-sqz+sqw));
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Get euler angles from this quaternion, angle is returned in degrees.
    /// \param xd return the rotation around x-axis in degrees
    /// \param yd return the rotation around y-axis in degrees
    /// \param zd return the rotation around z-axis in degrees
    ///////////////////////////////////////////////////////////////////////////
    void GetEulerDeg(T &xd, T &yd, T &zd) const
    {
        this->GetEulerRad(xd, yd, zd);
        xd = RADTODEG(xd);
        yd = RADTODEG(yd);
        zd = RADTODEG(zd);
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the 4x4 rotation matrix representation of this quaternion.
    /// \param mat return the rotation matrix.
    ///////////////////////////////////////////////////////////////////////////
    void BuildMatrix(Matrix<T> &mat) const  // get the 4x4 rotation matrix representation of this quaternion
    {
        T *m = mat;

        m[0]  = T(1) - T(2) * (y*y + z*z);
        m[1]  = T(2) * (x*y + z*w);
        m[2]  = T(2) * (z*x - y*w);
        m[3]  = T(0);

        m[4]  = T(2) * (x*y - z*w);
        m[5]  = T(1) - T(2) * (z*z + x*x);
        m[6]  = T(2) * (y*z + x*w);
        m[7]  = T(0);

        m[8]  = T(2) * (z*x + y*w);
        m[9]  = T(2) * (y*z - x*w);
        m[10] = T(1) - T(2) * (x*x + y*y);
        m[11] = T(0);

        m[12] = T(0);
        m[13] = T(0);
        m[14] = T(0);
        m[15] = T(1);
    }

private:
    // get the norm N^2
    inline double _norm() { return(sqrt( SQR(x) + SQR(y) + SQR(z) + SQR(w))); } 

};

template <typename T> Quaternion<T> operator * (Quaternion<T> const &p, Quaternion<T> const &q)
{
    Quaternion<T> res;

    res.w   = p.w*q.w - p.x*q.x - p.y*q.y - p.z*q.z;

    res.x   = p.w*q.x + p.x*q.w + p.y*q.z - p.z*q.y;
    res.y   = p.w*q.y + p.y*q.w + p.z*q.x - p.x*q.z;
    res.z   = p.w*q.z + p.z*q.w + p.x*q.y - p.y*q.x;

    return res;
}

typedef Quaternion<float> Quaternionf;
typedef Quaternion<double> Quaterniond;

#endif
