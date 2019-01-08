/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkQuaternion_h
#define __mitkQuaternion_h

#include "mitkMatrix.h"

/// mitkQuaternion - it's used to implement 3d rotation
///////////////////////////////////////////////////////////////////////////
/// mitkQuaternion is used to implement 3d rotation
class MITK_COMMON_API mitkQuaternion
{
public:

    ///////////////////////////////////////////////////////////////////////////
    /// Default constructor. Construct a quaternion with zero rotation.
    ///////////////////////////////////////////////////////////////////////////
    mitkQuaternion();

    ///////////////////////////////////////////////////////////////////////////
    /// Construct a quaternion from given values. Quat will 
    /// be normalized. Will perform a valid check.
    ///////////////////////////////////////////////////////////////////////////
    mitkQuaternion(const float x, const float y, const float z, const float w);

    ///////////////////////////////////////////////////////////////////////////
    /// Construct a quaternion from euler angles in degrees.
    /// \param x rotation around x-axis in degrees
    /// \param y rotation around y-axis in degrees
    /// \param z rotation around z-axis in degrees
    ///////////////////////////////////////////////////////////////////////////
    mitkQuaternion(const float x, const float y, const float z);

    //////////////////////////////////////////////////////////////////////////
    /// "=" operator.
    //////////////////////////////////////////////////////////////////////////
    mitkQuaternion& operator=(const mitkQuaternion &q)  
    {
        x = q.x;
        y = q.y;
        z = q.z;
        w = q.w;
        return(*this);  
    }

    //////////////////////////////////////////////////////////////////////////
    /// Copy constructor.
    //////////////////////////////////////////////////////////////////////////
    mitkQuaternion(const mitkQuaternion &q)                    
    {
        x = q.x;
        y = q.y;
        z = q.z;
        w = q.w;
    }
    
    ///////////////////////////////////////////////////////////////////////////
    /// Set this quaternion to the identity quaternion.
    ///////////////////////////////////////////////////////////////////////////
    void Identity(void);

    ///////////////////////////////////////////////////////////////////////////
    /// Normalize this quaternion.
    ///////////////////////////////////////////////////////////////////////////
    void Normalize(void);

    ///////////////////////////////////////////////////////////////////////////
    /// Get the values of this quaternion.
    ///////////////////////////////////////////////////////////////////////////
    void GetValues(float &x, float &y, float &z, float &w) const;

    ///////////////////////////////////////////////////////////////////////////
    /// Convert an axis angle to quaternion, angle is in radians.
    /// \param ax the x-coordinate of rotation axis
    /// \param ay the y-coordinate of rotation axis
    /// \param az the z-coordinate of rotation axis
    /// \param angle the angle of rotation in radians
    ///////////////////////////////////////////////////////////////////////////
    void AxisRadToQuat(const float ax, const float ay, const float az, const float angle);

    ///////////////////////////////////////////////////////////////////////////
    /// Convert an axis angle to quaternion, angle is in degrees.
    /// \param ax the x-coordinate of rotation axis
    /// \param ay the y-coordinate of rotation axis
    /// \param az the z-coordinate of rotation axis
    /// \param angle the angle of rotation in degrees
    ///////////////////////////////////////////////////////////////////////////
    void AxisDegToQuat(const float ax, const float ay, const float az, const float angle);


    ///////////////////////////////////////////////////////////////////////////
    /// Get an axis angle from this quaternion, angle is returned in radians.
    /// \param ax return the x-coordinate of rotation axis
    /// \param ay return the y-coordinate of rotation axis
    /// \param az return the z-coordinate of rotation axis
    /// \param angle return the angle of rotation in radians
    ///////////////////////////////////////////////////////////////////////////
    void GetAxisRad(float &ax, float &ay, float &az, float &angle) const;

    ///////////////////////////////////////////////////////////////////////////
    /// Get an axis angle from this quaternion, angle is returned in degrees.
    /// \param ax return the x-coordinate of rotation axis
    /// \param ay return the y-coordinate of rotation axis
    /// \param az return the z-coordinate of rotation axis
    /// \param angle return the angle of rotation in degrees
    ///////////////////////////////////////////////////////////////////////////
    void GetAxisDeg(float &ax, float &ay, float &az, float &angle) const;

    ///////////////////////////////////////////////////////////////////////////
    /// Convert euler angles to quaternion, euler angles are in radians.
    /// \param xr rotation around x-axis in radians
    /// \param yr rotation around y-axis in radians
    /// \param zr rotation around z-axis in radians
    ///////////////////////////////////////////////////////////////////////////
    void EulerRadToQuat(const float xr, const float yr, const float zr);

    ///////////////////////////////////////////////////////////////////////////
    /// Convert euler angles to quaternion, euler angles are in degrees.
    /// \param xd rotation around x-axis in degrees
    /// \param yd rotation around y-axis in degrees
    /// \param zd rotation around z-axis in degrees
    ///////////////////////////////////////////////////////////////////////////
    void EulerDegToQuat(const float xd, const float yd, const float zd);

    ///////////////////////////////////////////////////////////////////////////
    /// Get euler angles from this quaternion, angle is returned in radians.
    /// \param xr return the rotation around x-axis in radians
    /// \param yr return the rotation around y-axis in radians
    /// \param zr return the rotation around z-axis in radians
    ///////////////////////////////////////////////////////////////////////////
    void GetEulerRad(float &xr, float &yr, float &zr) const;

    ///////////////////////////////////////////////////////////////////////////
    /// Get euler angles from this quaternion, angle is returned in degrees.
    /// \param xd return the rotation around x-axis in degrees
    /// \param yd return the rotation around y-axis in degrees
    /// \param zd return the rotation around z-axis in degrees
    ///////////////////////////////////////////////////////////////////////////
    void GetEulerDeg(float &xd, float &yd, float &zd) const;

    ///////////////////////////////////////////////////////////////////////////
    /// Get the 4x4 rotation matrix representation of this quaternion.
    /// \param mat return the rotation matrix.
    ///////////////////////////////////////////////////////////////////////////
    void BuildMatrix(mitkMatrix &mat) const;    // get the 4x4 rotation matrix representation of this quaternion

    ///////////////////////////////////////////////////////////////////////////
    /// Multiplication
    ///////////////////////////////////////////////////////////////////////////
    friend mitkQuaternion operator * (const mitkQuaternion &p, const mitkQuaternion &q); // multiplication

private:
    // get the norm N^2
    inline double _norm(void); 

    // quaternion representation (w, xi, yj, zk)
    float   x,y,z,w;            



};

inline mitkQuaternion operator * (const mitkQuaternion &p, const mitkQuaternion &q)
{
    mitkQuaternion res;

    res.w   = p.w*q.w - p.x*q.x - p.y*q.y - p.z*q.z;

    res.x   = p.w*q.x + p.x*q.w + p.y*q.z - p.z*q.y;
    res.y   = p.w*q.y + p.y*q.w + p.z*q.x - p.x*q.z;
    res.z   = p.w*q.z + p.z*q.w + p.x*q.y - p.y*q.x;

    return res;
}


#endif


