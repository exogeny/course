/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkMatrixD_h
#define __mitkMatrixD_h

#include <math.h>
#include "mitkGlobal.h"

/// mitkMatrixD - an encapsulation of a matrix
///////////////////////////////////////////////////////////////////////////
/// mitkMatrixD provides an encapsulation of matrix operations. It is used
/// in volume rendering algorithm, which requires intensive matrix calculations.
/// The interface of mitkMatrixD provides many common matrix operations.
class MITK_COMMON_API mitkMatrixD
{
public:
    double ele[16];

    mitkMatrixD() {}
    mitkMatrixD(const mitkMatrixD &m)
    {
        ele[0] =  m.ele[0]; 
        ele[1] =  m.ele[1]; 
        ele[2] =  m.ele[2]; 
        ele[3] =  m.ele[3]; 
        ele[4] =  m.ele[4]; 
        ele[5] =  m.ele[5]; 
        ele[6] =  m.ele[6]; 
        ele[7] =  m.ele[7]; 
        ele[8] =  m.ele[8]; 
        ele[9] =  m.ele[9]; 
        ele[10] = m.ele[10];
        ele[11] = m.ele[11];
        ele[12] = m.ele[12];
        ele[13] = m.ele[13];
        ele[14] = m.ele[14];
        ele[15] = m.ele[15];        
    }

    mitkMatrixD(double e0, double e1, double e2, double e3,
               double e4, double e5, double e6, double e7,
               double e8, double e9, double e10, double e11,
               double e12, double e13, double e14, double e15)
    {
        ele[0] = e0;
        ele[1] = e1;
        ele[2] = e2;
        ele[3] = e3;
        ele[4] = e4;
        ele[5] = e5;
        ele[6] = e6;
        ele[7] = e7;
        ele[8] = e8;
        ele[9] = e9;
        ele[10] = e10;
        ele[11] = e11;
        ele[12] = e12;
        ele[13] = e13;
        ele[14] = e14;
        ele[15] = e15;      
    }   

    mitkMatrixD& operator = (const mitkMatrixD &m) 
    {
        ele[0] =  m.ele[0]; 
        ele[1] =  m.ele[1]; 
        ele[2] =  m.ele[2]; 
        ele[3] =  m.ele[3]; 
        ele[4] =  m.ele[4]; 
        ele[5] =  m.ele[5]; 
        ele[6] =  m.ele[6]; 
        ele[7] =  m.ele[7]; 
        ele[8] =  m.ele[8]; 
        ele[9] =  m.ele[9]; 
        ele[10] = m.ele[10];
        ele[11] = m.ele[11];
        ele[12] = m.ele[12];
        ele[13] = m.ele[13];
        ele[14] = m.ele[14];
        ele[15] = m.ele[15];        
        return *this;
    }

    friend mitkMatrixD operator * (const mitkMatrixD&, const mitkMatrixD&);
    friend mitkMatrixD operator + (const mitkMatrixD&, const mitkMatrixD&);
    friend mitkMatrixD operator - (const mitkMatrixD&, const mitkMatrixD&);
    friend mitkMatrixD operator + (const mitkMatrixD&);
    friend mitkMatrixD operator - (const mitkMatrixD&);
    friend mitkMatrixD operator * (const mitkMatrixD&, const double);
    friend mitkMatrixD operator * (const double, const mitkMatrixD&);

    mitkMatrixD& operator *= (const mitkMatrixD &);
    mitkMatrixD& operator *= (const double);
    mitkMatrixD& operator += (const mitkMatrixD &);
    mitkMatrixD& operator -= (const mitkMatrixD &);

    operator const double* () const { return ele; }
    operator double* () { return ele; }

    //////////////////////////////////////////////////////////////////////////
    /// Transposes the matrix   
    //////////////////////////////////////////////////////////////////////////
    void    Transpose();    
    
    //////////////////////////////////////////////////////////////////////////
    /// Inverses the matrix and returns the determinant
    //////////////////////////////////////////////////////////////////////////
    double  Inverse();      

    //////////////////////////////////////////////////////////////////////////
    /// Returns the determinant
    //////////////////////////////////////////////////////////////////////////  
    double  Determinant();  

    //////////////////////////////////////////////////////////////////////////
    /// Adjoint matrix
    //////////////////////////////////////////////////////////////////////////
    void    Adjoint();

    //////////////////////////////////////////////////////////////////////////
    /// Returns the minimum absolute value of the matrix
    //////////////////////////////////////////////////////////////////////////
    double  MinValue();     

    //////////////////////////////////////////////////////////////////////////
    /// Returns the maximum absolute value of the matrix
    //////////////////////////////////////////////////////////////////////////
    double  MaxValue();     

    //////////////////////////////////////////////////////////////////////////
    /// Clean the matrix to zero    
    //////////////////////////////////////////////////////////////////////////
    void ZeroMatrix();

    //////////////////////////////////////////////////////////////////////////
    /// Set the matrix to identity matrix   
    //////////////////////////////////////////////////////////////////////////
    void IdentityMatrix();

    //////////////////////////////////////////////////////////////////////////
    /// Translate transformation
    //////////////////////////////////////////////////////////////////////////
    void TranslateMatrix(const double dx, const double dy, const double dz);

    //////////////////////////////////////////////////////////////////////////
    /// Scale transformation
    //////////////////////////////////////////////////////////////////////////
    void ScaleMatrix(const double a, const double b, const double c);

    //////////////////////////////////////////////////////////////////////////
    /// Uniform scale transformation
    //////////////////////////////////////////////////////////////////////////
    void ScaleMatrix(const double a);

    //////////////////////////////////////////////////////////////////////////
    /// Rotation around x axis
    //////////////////////////////////////////////////////////////////////////
    void RotateXMatrix(const double angle);

    //////////////////////////////////////////////////////////////////////////
    /// Rotation around y axis  
    //////////////////////////////////////////////////////////////////////////
    void RotateYMatrix(const double angle);

    //////////////////////////////////////////////////////////////////////////
    /// Rotation around z axis
    //////////////////////////////////////////////////////////////////////////
    void RotateZMatrix(const double angle);

    //////////////////////////////////////////////////////////////////////////
    /// Translate current matrix
    //////////////////////////////////////////////////////////////////////////
    void Translate(const double dx, const double dy, const double dz);

    //////////////////////////////////////////////////////////////////////////
    /// Scale current matrix
    //////////////////////////////////////////////////////////////////////////
    void Scale(const double a, const double b, const double c);

    //////////////////////////////////////////////////////////////////////////
    /// Rotate current matrix around arbitrary axis
    //////////////////////////////////////////////////////////////////////////
    void Rotate(const double angle, const double x, const double y, const double z);

    //////////////////////////////////////////////////////////////////////////
    /// Rotate current matrix around x axis
    //////////////////////////////////////////////////////////////////////////
    void RotateX(const double angle);

    //////////////////////////////////////////////////////////////////////////
    /// Rotate current matrix around y axis
    //////////////////////////////////////////////////////////////////////////
    void RotateY(const double angle);

    //////////////////////////////////////////////////////////////////////////
    /// Rotate current matrix around z axis
    //////////////////////////////////////////////////////////////////////////
    void RotateZ(const double angle);
};


class MITK_COMMON_API mitkVectorD
{
public:
    double  ele[4];
    
    mitkVectorD()
    {
        ele[0] = 0.0;
        ele[1] = 0.0;
        ele[2] = 0.0;
        ele[3] = 1.0;
    }
    mitkVectorD(const mitkVectorD &v)
    {
        ele[0] = v.ele[0];
        ele[1] = v.ele[1];
        ele[2] = v.ele[2];
        ele[3] = v.ele[3];      
    }

    mitkVectorD(const double x, const double y, const double z, const double w = 1.0f)
    {
        ele[0] = x;
        ele[1] = y;
        ele[2] = z;
        ele[3] = w;
    }

    mitkVectorD(const double srcVector[4])
    {
        ele[0] = srcVector[0];
        ele[1] = srcVector[1];
        ele[2] = srcVector[2];
        ele[3] = srcVector[3];
    }   
    

    operator double* () { return ele; } 
    operator const double* () const { return ele; }

    mitkVectorD& operator = (const mitkVectorD &a)
    {
        ele[0] = a.ele[0];
        ele[1] = a.ele[1];
        ele[2] = a.ele[2];
        ele[3] = a.ele[3];
        return *this; 
    }
    
    friend mitkVectorD operator * (const mitkVectorD&, const mitkMatrixD&);
    friend double operator * (const mitkVectorD &, const mitkVectorD &);            // Dot Product
    friend mitkVectorD operator % (const mitkVectorD &, const mitkVectorD &);       // Cross Product
    friend mitkVectorD operator * (const mitkVectorD &, const double);
    friend mitkVectorD operator * (const double, const mitkVectorD &);
    friend mitkVectorD operator + (const mitkVectorD&);
    friend mitkVectorD operator + (const mitkVectorD&, const mitkVectorD&);
    friend mitkVectorD operator - (const mitkVectorD&);
    friend mitkVectorD operator - (const mitkVectorD&, const mitkVectorD&);
    friend mitkVectorD operator ~ (const mitkVectorD&);                         // Normalize

    mitkVectorD& operator *= (const mitkMatrixD &);
    mitkVectorD& operator *= (const double);
    mitkVectorD& operator += (const mitkVectorD &);
    mitkVectorD& operator -= (const mitkVectorD &);

    double Length();
    double Length2();
    void Normalize();
};
//----------------------------------------------------------------------------
inline void mitkMatrixD::ZeroMatrix() 
{
    ele[0] = ele[1] = ele[2] = ele[3] = 0.0f;
    ele[4] = ele[5] = ele[6] = ele[7] = 0.0f;
    ele[8] = ele[9] = ele[10] = ele[11] = 0.0f;
    ele[12] = ele[13] = ele[14] = ele[15] = 0.0f;
}
//----------------------------------------------------------------------------
inline void mitkMatrixD::IdentityMatrix() 
{
    ele[0] = ele[5] = ele[10] = ele[15] = 1.0;
    ele[1] = ele[2] = ele[3] = ele[4] = 0.0;
    ele[6] = ele[7] = ele[8] = ele[9] = 0.0;
    ele[11] = ele[12] = ele[13] = ele[14] = 0.0;        
}
//----------------------------------------------------------------------------
inline mitkMatrixD operator * (const mitkMatrixD &A, const mitkMatrixD &B) 
{
    mitkMatrixD Res;
    
    Res.ele[0]   = A.ele[0]*B.ele[0] + A.ele[4]*B.ele[1] + A.ele[8]*B.ele[2] + A.ele[12]*B.ele[3]; 
    Res.ele[1]   = A.ele[1]*B.ele[0] + A.ele[5]*B.ele[1] + A.ele[9]*B.ele[2] + A.ele[13]*B.ele[3]; 
    Res.ele[2]   = A.ele[2]*B.ele[0] + A.ele[6]*B.ele[1] + A.ele[10]*B.ele[2] + A.ele[14]*B.ele[3]; 
    Res.ele[3]   = A.ele[3]*B.ele[0] + A.ele[7]*B.ele[1] + A.ele[11]*B.ele[2] + A.ele[15]*B.ele[3]; 

    Res.ele[4]   = A.ele[0]*B.ele[4] + A.ele[4]*B.ele[5] + A.ele[8]*B.ele[6] + A.ele[12]*B.ele[7]; 
    Res.ele[5]   = A.ele[1]*B.ele[4] + A.ele[5]*B.ele[5] + A.ele[9]*B.ele[6] + A.ele[13]*B.ele[7]; 
    Res.ele[6]   = A.ele[2]*B.ele[4] + A.ele[6]*B.ele[5] + A.ele[10]*B.ele[6] + A.ele[14]*B.ele[7]; 
    Res.ele[7]   = A.ele[3]*B.ele[4] + A.ele[7]*B.ele[5] + A.ele[11]*B.ele[6] + A.ele[15]*B.ele[7]; 

    Res.ele[8]   = A.ele[0]*B.ele[8] + A.ele[4]*B.ele[9] + A.ele[8]*B.ele[10] + A.ele[12]*B.ele[11]; 
    Res.ele[9]   = A.ele[1]*B.ele[8] + A.ele[5]*B.ele[9] + A.ele[9]*B.ele[10] + A.ele[13]*B.ele[11]; 
    Res.ele[10]   = A.ele[2]*B.ele[8] + A.ele[6]*B.ele[9] + A.ele[10]*B.ele[10] + A.ele[14]*B.ele[11]; 
    Res.ele[11]   = A.ele[3]*B.ele[8] + A.ele[7]*B.ele[9] + A.ele[11]*B.ele[10] + A.ele[15]*B.ele[11]; 

    Res.ele[12]   = A.ele[0]*B.ele[12] + A.ele[4]*B.ele[13] + A.ele[8]*B.ele[14] + A.ele[12]*B.ele[15];     
    Res.ele[13]   = A.ele[1]*B.ele[12] + A.ele[5]*B.ele[13] + A.ele[9]*B.ele[14] + A.ele[13]*B.ele[15];     
    Res.ele[14]   = A.ele[2]*B.ele[12] + A.ele[6]*B.ele[13] + A.ele[10]*B.ele[14] + A.ele[14]*B.ele[15];    
    Res.ele[15]   = A.ele[3]*B.ele[12] + A.ele[7]*B.ele[13] + A.ele[11]*B.ele[14] + A.ele[15]*B.ele[15];        
    return Res;         
}
//----------------------------------------------------------------------------
inline mitkMatrixD& mitkMatrixD::operator *= (const mitkMatrixD &B) 
{
    mitkMatrixD Res;
    Res.ele[0]   = ele[0]*B.ele[0] + ele[4]*B.ele[1] + ele[8]*B.ele[2] + ele[12]*B.ele[3]; 
    Res.ele[1]   = ele[1]*B.ele[0] + ele[5]*B.ele[1] + ele[9]*B.ele[2] + ele[13]*B.ele[3]; 
    Res.ele[2]   = ele[2]*B.ele[0] + ele[6]*B.ele[1] + ele[10]*B.ele[2] + ele[14]*B.ele[3]; 
    Res.ele[3]   = ele[3]*B.ele[0] + ele[7]*B.ele[1] + ele[11]*B.ele[2] + ele[15]*B.ele[3]; 

    Res.ele[4]   = ele[0]*B.ele[4] + ele[4]*B.ele[5] + ele[8]*B.ele[6] + ele[12]*B.ele[7]; 
    Res.ele[5]   = ele[1]*B.ele[4] + ele[5]*B.ele[5] + ele[9]*B.ele[6] + ele[13]*B.ele[7]; 
    Res.ele[6]   = ele[2]*B.ele[4] + ele[6]*B.ele[5] + ele[10]*B.ele[6] + ele[14]*B.ele[7]; 
    Res.ele[7]   = ele[3]*B.ele[4] + ele[7]*B.ele[5] + ele[11]*B.ele[6] + ele[15]*B.ele[7]; 

    Res.ele[8]   = ele[0]*B.ele[8] + ele[4]*B.ele[9] + ele[8]*B.ele[10] + ele[12]*B.ele[11]; 
    Res.ele[9]   = ele[1]*B.ele[8] + ele[5]*B.ele[9] + ele[9]*B.ele[10] + ele[13]*B.ele[11]; 
    Res.ele[10]   = ele[2]*B.ele[8] + ele[6]*B.ele[9] + ele[10]*B.ele[10] + ele[14]*B.ele[11]; 
    Res.ele[11]   = ele[3]*B.ele[8] + ele[7]*B.ele[9] + ele[11]*B.ele[10] + ele[15]*B.ele[11]; 

    Res.ele[12]   = ele[0]*B.ele[12] + ele[4]*B.ele[13] + ele[8]*B.ele[14] + ele[12]*B.ele[15];     
    Res.ele[13]   = ele[1]*B.ele[12] + ele[5]*B.ele[13] + ele[9]*B.ele[14] + ele[13]*B.ele[15];     
    Res.ele[14]   = ele[2]*B.ele[12] + ele[6]*B.ele[13] + ele[10]*B.ele[14] + ele[14]*B.ele[15];    
    Res.ele[15]   = ele[3]*B.ele[12] + ele[7]*B.ele[13] + ele[11]*B.ele[14] + ele[15]*B.ele[15];        
    *this = Res;
    return *this;
}
//----------------------------------------------------------------------------
inline mitkMatrixD operator * (const mitkMatrixD &A, const double s) 
{
    mitkMatrixD Res;
    
    Res.ele[0] = A.ele[0] * s;
    Res.ele[1] = A.ele[1] * s;
    Res.ele[2] = A.ele[2] * s;
    Res.ele[3] = A.ele[3] * s;
    Res.ele[4] = A.ele[4] * s;
    Res.ele[5] = A.ele[5] * s;
    Res.ele[6] = A.ele[6] * s;
    Res.ele[7] = A.ele[7] * s;
    Res.ele[8] = A.ele[8] * s;
    Res.ele[9] = A.ele[9] * s;
    Res.ele[10] = A.ele[10] * s;
    Res.ele[11] = A.ele[11] * s;
    Res.ele[12] = A.ele[12] * s;
    Res.ele[13] = A.ele[13] * s;
    Res.ele[14] = A.ele[14] * s;
    Res.ele[15] = A.ele[15] * s;
    return Res; 
}
//----------------------------------------------------------------------------
inline mitkMatrixD operator * (const double s, const mitkMatrixD &A) 
{
    mitkMatrixD Res;
    
    Res.ele[0] = A.ele[0] * s;
    Res.ele[1] = A.ele[1] * s;
    Res.ele[2] = A.ele[2] * s;
    Res.ele[3] = A.ele[3] * s;
    Res.ele[4] = A.ele[4] * s;
    Res.ele[5] = A.ele[5] * s;
    Res.ele[6] = A.ele[6] * s;
    Res.ele[7] = A.ele[7] * s;
    Res.ele[8] = A.ele[8] * s;
    Res.ele[9] = A.ele[9] * s;
    Res.ele[10] = A.ele[10] * s;
    Res.ele[11] = A.ele[11] * s;
    Res.ele[12] = A.ele[12] * s;
    Res.ele[13] = A.ele[13] * s;
    Res.ele[14] = A.ele[14] * s;
    Res.ele[15] = A.ele[15] * s;
    return Res; 
}
//----------------------------------------------------------------------------
inline mitkMatrixD& mitkMatrixD::operator *= (const double s) 
{
    ele[0] *= s;
    ele[1] *= s;
    ele[2] *= s;
    ele[3] *= s;
    ele[4] *= s;
    ele[5] *= s;
    ele[6] *= s;
    ele[7] *= s;
    ele[8] *= s;
    ele[9] *= s;
    ele[10] *= s;
    ele[11] *= s;
    ele[12] *= s;
    ele[13] *= s;
    ele[14] *= s;
    ele[15] *= s;
    return *this;
}
//----------------------------------------------------------------------------
inline mitkMatrixD operator + (const mitkMatrixD &A, const mitkMatrixD &B) 
{
    mitkMatrixD Res;

    Res.ele[0] = A.ele[0] + B.ele[0];
    Res.ele[1] = A.ele[1] + B.ele[1];
    Res.ele[2] = A.ele[2] + B.ele[2];
    Res.ele[3] = A.ele[3] + B.ele[3];
    Res.ele[4] = A.ele[4] + B.ele[4];
    Res.ele[5] = A.ele[5] + B.ele[5];
    Res.ele[6] = A.ele[6] + B.ele[6];
    Res.ele[7] = A.ele[7] + B.ele[7];   
    Res.ele[8] = A.ele[8] + B.ele[8];
    Res.ele[9] = A.ele[9] + B.ele[9];
    Res.ele[10] = A.ele[10] + B.ele[10];
    Res.ele[11] = A.ele[11] + B.ele[11];
    Res.ele[12] = A.ele[12] + B.ele[12];
    Res.ele[13] = A.ele[13] + B.ele[13];
    Res.ele[14] = A.ele[14] + B.ele[14];
    Res.ele[15] = A.ele[15] + B.ele[15];
    return Res;
}
//----------------------------------------------------------------------------
inline mitkMatrixD & mitkMatrixD::operator += (const mitkMatrixD &B) 
{
    ele[0] += B.ele[0];
    ele[1] += B.ele[1];
    ele[2] += B.ele[2];
    ele[3] += B.ele[3];
    ele[4] += B.ele[4];
    ele[5] += B.ele[5];
    ele[6] += B.ele[6];
    ele[7] += B.ele[7];
    ele[8] += B.ele[8];
    ele[9] += B.ele[9];
    ele[10] += B.ele[10];
    ele[11] += B.ele[11];
    ele[12] += B.ele[12];
    ele[13] += B.ele[13];
    ele[14] += B.ele[14];
    ele[15] += B.ele[15];
    return *this;
}
//----------------------------------------------------------------------------
inline mitkMatrixD operator - (const mitkMatrixD &A, const mitkMatrixD &B) 
{
    mitkMatrixD Res;

    Res.ele[0] = A.ele[0] - B.ele[0];
    Res.ele[1] = A.ele[1] - B.ele[1];
    Res.ele[2] = A.ele[2] - B.ele[2];
    Res.ele[3] = A.ele[3] - B.ele[3];
    Res.ele[4] = A.ele[4] - B.ele[4];
    Res.ele[5] = A.ele[5] - B.ele[5];
    Res.ele[6] = A.ele[6] - B.ele[6];
    Res.ele[7] = A.ele[7] - B.ele[7];   
    Res.ele[8] = A.ele[8] - B.ele[8];
    Res.ele[9] = A.ele[9] - B.ele[9];
    Res.ele[10] = A.ele[10] - B.ele[10];
    Res.ele[11] = A.ele[11] - B.ele[11];
    Res.ele[12] = A.ele[12] - B.ele[12];
    Res.ele[13] = A.ele[13] - B.ele[13];
    Res.ele[14] = A.ele[14] - B.ele[14];
    Res.ele[15] = A.ele[15] - B.ele[15];
    return Res;
}
//----------------------------------------------------------------------------
inline mitkMatrixD operator - (const mitkMatrixD &A)
{
    mitkMatrixD Res;

    Res.ele[0] = - A.ele[0];
    Res.ele[1] = - A.ele[1];
    Res.ele[2] = - A.ele[2];
    Res.ele[3] = - A.ele[3];
    Res.ele[4] = - A.ele[4];
    Res.ele[5] = - A.ele[5];
    Res.ele[6] = - A.ele[6];
    Res.ele[7] = - A.ele[7];    
    Res.ele[8] = - A.ele[8];
    Res.ele[9] = - A.ele[9];
    Res.ele[10] = - A.ele[10];
    Res.ele[11] = - A.ele[11];
    Res.ele[12] = - A.ele[12];
    Res.ele[13] = - A.ele[13];
    Res.ele[14] = - A.ele[14];
    Res.ele[15] = - A.ele[15];
    return Res;
}
//----------------------------------------------------------------------------
inline mitkMatrixD & mitkMatrixD::operator -= (const mitkMatrixD &B) 
{
    ele[0] -= B.ele[0];
    ele[1] -= B.ele[1];
    ele[2] -= B.ele[2];
    ele[3] -= B.ele[3];
    ele[4] -= B.ele[4];
    ele[5] -= B.ele[5];
    ele[6] -= B.ele[6];
    ele[7] -= B.ele[7];
    ele[8] -= B.ele[8];
    ele[9] -= B.ele[9];
    ele[10] -= B.ele[10];
    ele[11] -= B.ele[11];
    ele[12] -= B.ele[12];
    ele[13] -= B.ele[13];
    ele[14] -= B.ele[14];
    ele[15] -= B.ele[15];
    return *this;
}
//----------------------------------------------------------------------------
inline mitkVectorD operator * (const mitkVectorD& Vec, const mitkMatrixD& Mat) 
{
    mitkVectorD Res;
    Res.ele[0] = Mat.ele[0]*Vec.ele[0] + Mat.ele[1]*Vec.ele[1] + Mat.ele[2]*Vec.ele[2] + Mat.ele[3]*Vec.ele[3]; 
    Res.ele[1] = Mat.ele[4]*Vec.ele[0] + Mat.ele[5]*Vec.ele[1] + Mat.ele[6]*Vec.ele[2] + Mat.ele[7]*Vec.ele[3]; 
    Res.ele[2] = Mat.ele[8]*Vec.ele[0] + Mat.ele[9]*Vec.ele[1] + Mat.ele[10]*Vec.ele[2] + Mat.ele[11]*Vec.ele[3]; 
    Res.ele[3] = Mat.ele[12]*Vec.ele[0] + Mat.ele[13]*Vec.ele[1] + Mat.ele[14]*Vec.ele[2] + Mat.ele[15]*Vec.ele[3]; 
    return Res;     
}
//----------------------------------------------------------------------------
inline mitkVectorD operator * (const mitkMatrixD& Mat, mitkVectorD& Vec) 
{
    mitkVectorD Res;
    Res.ele[0] = Mat.ele[0]*Vec.ele[0] + Mat.ele[4]*Vec.ele[1] + Mat.ele[8]*Vec.ele[2] + Mat.ele[12]*Vec.ele[3]; 
    Res.ele[1] = Mat.ele[1]*Vec.ele[0] + Mat.ele[5]*Vec.ele[1] + Mat.ele[9]*Vec.ele[2] + Mat.ele[13]*Vec.ele[3]; 
    Res.ele[2] = Mat.ele[2]*Vec.ele[0] + Mat.ele[6]*Vec.ele[1] + Mat.ele[10]*Vec.ele[2] + Mat.ele[14]*Vec.ele[3]; 
    Res.ele[3] = Mat.ele[3]*Vec.ele[0] + Mat.ele[7]*Vec.ele[1] + Mat.ele[11]*Vec.ele[2] + Mat.ele[15]*Vec.ele[3]; 
    return Res;     
}
//----------------------------------------------------------------------------
inline mitkVectorD& mitkVectorD::operator *= (const mitkMatrixD& Mat) 
{
    double temp[4];
    temp[0] = Mat.ele[0]*ele[0] + Mat.ele[4]*ele[1] + Mat.ele[8]*ele[2] + Mat.ele[12]*ele[3]; 
    temp[1] = Mat.ele[1]*ele[0] + Mat.ele[5]*ele[1] + Mat.ele[9]*ele[2] + Mat.ele[13]*ele[3]; 
    temp[2] = Mat.ele[2]*ele[0] + Mat.ele[6]*ele[1] + Mat.ele[10]*ele[2] + Mat.ele[14]*ele[3]; 
    temp[3] = Mat.ele[3]*ele[0] + Mat.ele[7]*ele[1] + Mat.ele[11]*ele[2] + Mat.ele[15]*ele[3]; 
    ele[0] = temp[0];
    ele[1] = temp[1];
    ele[2] = temp[2];
    ele[3] = temp[3];   
    return *this;
}
//----------------------------------------------------------------------------
inline double operator * (const mitkVectorD& A, const mitkVectorD& B) 
{
    return A.ele[0]*B.ele[0] + A.ele[1]*B.ele[1] + A.ele[2]*B.ele[2];   
}
//----------------------------------------------------------------------------
inline mitkVectorD operator % (const mitkVectorD& A, const mitkVectorD& B) 
{
    mitkVectorD Res;
    Res.ele[0] = A.ele[1] * B.ele[2] - A.ele[2] * B.ele[1]; 
    Res.ele[1] = A.ele[2] * B.ele[0] - A.ele[0] * B.ele[2]; 
    Res.ele[2] = A.ele[0] * B.ele[1] - A.ele[1] * B.ele[0]; 
    Res.ele[3] = 0.0f;
    return Res;
}
//----------------------------------------------------------------------------
inline mitkVectorD operator * (const mitkVectorD &V, const double s) 
{
    mitkVectorD Res;
    Res.ele[0] = V.ele[0] * s;
    Res.ele[1] = V.ele[1] * s;
    Res.ele[2] = V.ele[2] * s;
    Res.ele[3] = V.ele[3] * s;  
    return Res;
}
//----------------------------------------------------------------------------
inline mitkVectorD operator * (const double s, const mitkVectorD &V) 
{
    mitkVectorD Res;
    Res.ele[0] = V.ele[0] * s;
    Res.ele[1] = V.ele[1] * s;
    Res.ele[2] = V.ele[2] * s;
    Res.ele[3] = V.ele[3] * s;  
    return Res;
}
//----------------------------------------------------------------------------
inline mitkVectorD& mitkVectorD::operator *= (const double s) 
{
    ele[0] *= s;
    ele[1] *= s;
    ele[2] *= s;
    ele[3] *= s;    
    return *this;
}
//----------------------------------------------------------------------------
inline mitkVectorD operator + (const mitkVectorD& A, const mitkVectorD& B) 
{
    mitkVectorD Res;
    Res.ele[0] = A.ele[0] + B.ele[0];
    Res.ele[1] = A.ele[1] + B.ele[1];
    Res.ele[2] = A.ele[2] + B.ele[2];
    Res.ele[3] = A.ele[3] + B.ele[3];
    return Res;
}
//----------------------------------------------------------------------------
inline mitkVectorD operator - (const mitkVectorD& A, const mitkVectorD& B) 
{
    mitkVectorD Res;
    Res.ele[0] = A.ele[0] - B.ele[0];
    Res.ele[1] = A.ele[1] - B.ele[1];
    Res.ele[2] = A.ele[2] - B.ele[2];
    Res.ele[3] = A.ele[3] - B.ele[3];
    return Res;
}
//----------------------------------------------------------------------------
inline mitkVectorD operator - (const mitkVectorD& A)
{
    mitkVectorD Res;
    Res.ele[0] = - A.ele[0];
    Res.ele[1] = - A.ele[1];
    Res.ele[2] = - A.ele[2];
    Res.ele[3] = - A.ele[3];
    return Res;
}
//----------------------------------------------------------------------------
inline mitkVectorD & mitkVectorD::operator += (const mitkVectorD &B) 
{
    ele[0] += B.ele[0];
    ele[1] += B.ele[1];
    ele[2] += B.ele[2];
    ele[3] += B.ele[3];
    return *this;
}
//----------------------------------------------------------------------------
inline mitkVectorD & mitkVectorD::operator -= (const mitkVectorD &B) 
{
    ele[0] -= B.ele[0];
    ele[1] -= B.ele[1];
    ele[2] -= B.ele[2];
    ele[3] -= B.ele[3];
    return *this;
}
//----------------------------------------------------------------------------
inline double mitkVectorD::Length()
{
    return sqrt(ele[0]*ele[0] + ele[1]*ele[1] + ele[2]*ele[2]);
}
//----------------------------------------------------------------------------
inline double mitkVectorD::Length2()
{
    return (ele[0]*ele[0] + ele[1]*ele[1] + ele[2]*ele[2]);
}
//----------------------------------------------------------------------------
inline void mitkVectorD::Normalize() 
{
    double vecLenInv = 1.0 / sqrt(ele[0]*ele[0] + ele[1]*ele[1] + ele[2]*ele[2]);
    ele[0] *= vecLenInv;
    ele[1] *= vecLenInv;
    ele[2] *= vecLenInv;
}

   
#endif

