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

#ifndef __matrix_h
#define __matrix_h

#include <math.h>
//----------------------------------------------------------------------------
template <typename T> struct FloatTraits {};
template <> struct FloatTraits<float>
{
    typedef float float_type;
    static inline float_type PI() { return 3.14159265358979323846f; }
    static inline float_type EPSILON() { return 0.001f; }
    static inline bool FLOAT_EQ(float_type x, float_type y) { return ((y-x<EPSILON()) && (x-y<EPSILON())); }
};
template <> struct FloatTraits<double>
{
    typedef double float_type;
    static inline float_type PI() { return 3.14159265358979323846; }
    static inline float_type EPSILON() { return 1e-6; }
    static inline bool FLOAT_EQ(float_type x, float_type y) { return ((y-x<EPSILON()) && (x-y<EPSILON())); }
};
//----------------------------------------------------------------------------
template <typename T> inline T DEGTORAD(T x) { return ( (x * FloatTraits<T>::PI()) / T(180) ); }
template <typename T> inline T RADTODEG(T x) { return ( (x * T(180)) / FloatTraits<T>::PI() ); }
template <typename T> inline T SQR(T x) { return ( x * x ); }
template <typename T> inline T DET3X3(T a, T b, T c, T d, T e, T f, T g, T h, T i) { return (a*e*i + b*f*g + c*d*h - c*e*g - a*f*h - b*d*i); }
//----------------------------------------------------------------------------
template <typename T> class Matrix
{
public:
    typedef FloatTraits<T> TraitsType;

    T ele[16];

    Matrix() {}
    Matrix(const Matrix &m)
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

    Matrix( T e0,  T e1,  T e2,  T e3,
        T e4,  T e5,  T e6,  T e7,
        T e8,  T e9,  T e10, T e11,
        T e12, T e13, T e14, T e15 )
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

    Matrix& operator = (const Matrix &m) 
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

    Matrix& operator *= (Matrix const &B)
    {
        Matrix Res;
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

    Matrix& operator *= (T const s)
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

    Matrix& operator += (Matrix const &B)
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

    Matrix& operator -= (Matrix const &B)
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

    operator const T* () const { return ele; }
    operator T* () { return ele; }

    //////////////////////////////////////////////////////////////////////////
    /// Transposes the matrix   
    //////////////////////////////////////////////////////////////////////////
    void Transpose()
    {
        T tmp;

        tmp = ele[1];
        ele[1] = ele[4];
        ele[4] = tmp;

        tmp = ele[2];
        ele[2] = ele[8];
        ele[8] = tmp;

        tmp = ele[3];
        ele[3] = ele[12];
        ele[12] = tmp;

        tmp = ele[6];
        ele[6] = ele[9];
        ele[9] = tmp;

        tmp = ele[7];
        ele[7] = ele[13];
        ele[13] = tmp;

        tmp = ele[11];
        ele[11] = ele[14];
        ele[14] = tmp;  
    }

    //////////////////////////////////////////////////////////////////////////
    /// Inverses the matrix and returns the determinant
    //////////////////////////////////////////////////////////////////////////
    T Inverse()
    {
        T a1, a2, a3, a4, b1, b2, b3, b4;
        T c1, c2, c3, c4, d1, d2, d3, d4;       

        a1 = ele[0];
        b1 = ele[1];
        c1 = ele[2];
        d1 = ele[3];

        a2 = ele[4];
        b2 = ele[5];
        c2 = ele[6];
        d2 = ele[7];

        a3 = ele[8];
        b3 = ele[9];
        c3 = ele[10];
        d3 = ele[11];

        a4 = ele[12];
        b4 = ele[13];
        c4 = ele[14];
        d4 = ele[15];

        T det1 = DET3X3( b2, b3, b4, c2, c3, c4, d2, d3, d4);
        T det2 = DET3X3( a2, a3, a4, c2, c3, c4, d2, d3, d4);
        T det3 = DET3X3( a2, a3, a4, b2, b3, b4, d2, d3, d4);
        T det4 = DET3X3( a2, a3, a4, b2, b3, b4, c2, c3, c4);
        T det = a1*det1 - b1*det2 + c1*det3 - d1*det4;  
        if(det == 0)    return T(0);    
        T invdet = T(1) / det;

        ele[0] =  det1*invdet;
        ele[4] = -det2*invdet;
        ele[8] =  det3*invdet;
        ele[12] = -det4*invdet;

        ele[1] = -DET3X3(b1, b3, b4, c1, c3, c4, d1, d3, d4)*invdet;
        ele[5] =  DET3X3(a1, a3, a4, c1, c3, c4, d1, d3, d4)*invdet;
        ele[9] = -DET3X3(a1, a3, a4, b1, b3, b4, d1, d3, d4)*invdet;
        ele[13] =  DET3X3(a1, a3, a4, b1, b3, b4, c1, c3, c4)*invdet;

        ele[2] =  DET3X3(b1, b2, b4, c1, c2, c4, d1, d2, d4)*invdet;
        ele[6] = -DET3X3(a1, a2, a4, c1, c2, c4, d1, d2, d4)*invdet;
        ele[10]=  DET3X3(a1, a2, a4, b1, b2, b4, d1, d2, d4)*invdet;
        ele[14]= -DET3X3(a1, a2, a4, b1, b2, b4, c1, c2, c4)*invdet;

        ele[3]= -DET3X3(b1, b2, b3, c1, c2, c3, d1, d2, d3)*invdet;
        ele[7]=  DET3X3(a1, a2, a3, c1, c2, c3, d1, d2, d3)*invdet;
        ele[11]= -DET3X3(a1, a2, a3, b1, b2, b3, d1, d2, d3)*invdet;
        ele[15]=  DET3X3(a1, a2, a3, b1, b2, b3, c1, c2, c3)*invdet;    

        return det;
    }

    //////////////////////////////////////////////////////////////////////////
    /// Returns the determinant
    //////////////////////////////////////////////////////////////////////////  
    T Determinant()
    {
        T a1, a2, a3, a4, b1, b2, b3, b4;
        T c1, c2, c3, c4, d1, d2, d3, d4;   

        a1 = ele[0];
        b1 = ele[1];
        c1 = ele[2];
        d1 = ele[3];

        a2 = ele[4];
        b2 = ele[5];
        c2 = ele[6];
        d2 = ele[7];

        a3 = ele[8];
        b3 = ele[9];
        c3 = ele[10];
        d3 = ele[11];

        a4 = ele[12];
        b4 = ele[13];
        c4 = ele[14];
        d4 = ele[15];

        return  a1 * DET3X3( b2, b3, b4, c2, c3, c4, d2, d3, d4)
            - b1 * DET3X3( a2, a3, a4, c2, c3, c4, d2, d3, d4)
            + c1 * DET3X3( a2, a3, a4, b2, b3, b4, d2, d3, d4)
            - d1 * DET3X3( a2, a3, a4, b2, b3, b4, c2, c3, c4);
    }

    //////////////////////////////////////////////////////////////////////////
    /// Adjoint matrix
    //////////////////////////////////////////////////////////////////////////
    void Adjoint()
    {
        T a1, a2, a3, a4, b1, b2, b3, b4;
        T c1, c2, c3, c4, d1, d2, d3, d4;   

        a1 = ele[0];
        b1 = ele[1];
        c1 = ele[2];
        d1 = ele[3];

        a2 = ele[4];
        b2 = ele[5];
        c2 = ele[6];
        d2 = ele[7];

        a3 = ele[8];
        b3 = ele[9];
        c3 = ele[10];
        d3 = ele[11];

        a4 = ele[12];
        b4 = ele[13];
        c4 = ele[14];
        d4 = ele[15];

        ele[0] =  DET3X3(b2, b3, b4, c2, c3, c4, d2, d3, d4);
        ele[4] = -DET3X3(a2, a3, a4, c2, c3, c4, d2, d3, d4);
        ele[8] =  DET3X3(a2, a3, a4, b2, b3, b4, d2, d3, d4);
        ele[12] = -DET3X3(a2, a3, a4, b2, b3, b4, c2, c3, c4);

        ele[1] = -DET3X3(b1, b3, b4, c1, c3, c4, d1, d3, d4);
        ele[5] =  DET3X3(a1, a3, a4, c1, c3, c4, d1, d3, d4);
        ele[9] = -DET3X3(a1, a3, a4, b1, b3, b4, d1, d3, d4);
        ele[13] =  DET3X3(a1, a3, a4, b1, b3, b4, c1, c3, c4);

        ele[2] =  DET3X3(b1, b2, b4, c1, c2, c4, d1, d2, d4);
        ele[6] = -DET3X3(a1, a2, a4, c1, c2, c4, d1, d2, d4);
        ele[10]=  DET3X3(a1, a2, a4, b1, b2, b4, d1, d2, d4);
        ele[14]= -DET3X3(a1, a2, a4, b1, b2, b4, c1, c2, c4);

        ele[3]= -DET3X3(b1, b2, b3, c1, c2, c3, d1, d2, d3);
        ele[7]=  DET3X3(a1, a2, a3, c1, c2, c3, d1, d2, d3);
        ele[11]= -DET3X3(a1, a2, a3, b1, b2, b3, d1, d2, d3);
        ele[15]=  DET3X3(a1, a2, a3, b1, b2, b3, c1, c2, c3);   
    }

    //////////////////////////////////////////////////////////////////////////
    /// Returns the minimum absolute value of the matrix
    //////////////////////////////////////////////////////////////////////////
    T MinValue()
    {
        int i;
        T min = fabs(ele[0]);
        T tmp;
        for(i = 1; i < 16; i++)
        {
            tmp = fabs(ele[i]);
            if(tmp < min)
                min = tmp;
        }
        return min;
    }

    //////////////////////////////////////////////////////////////////////////
    /// Returns the maximum absolute value of the matrix
    //////////////////////////////////////////////////////////////////////////
    T MaxValue()
    {
        int i;
        T maxval = fabs(ele[0]);
        T tmp;
        for(i = 1; i < 16; i++)
        {
            tmp = fabsf(ele[i]);
            if(tmp > maxval)
                maxval = tmp;
        }
        return maxval;  
    }

    //////////////////////////////////////////////////////////////////////////
    /// Clean the matrix to zero    
    //////////////////////////////////////////////////////////////////////////
    void ZeroMatrix()
    {
        ele[0] = ele[1] = ele[2] = ele[3] = T(0);
        ele[4] = ele[5] = ele[6] = ele[7] = T(0);
        ele[8] = ele[9] = ele[10] = ele[11] = T(0);
        ele[12] = ele[13] = ele[14] = ele[15] = T(0);
    }

    //////////////////////////////////////////////////////////////////////////
    /// Set the matrix to identity matrix   
    //////////////////////////////////////////////////////////////////////////
    void IdentityMatrix()
    {
        ele[0] = ele[5] = ele[10] = ele[15] = T(1);
        ele[1] = ele[2] = ele[3] = ele[4] = T(0);
        ele[6] = ele[7] = ele[8] = ele[9] = T(0);
        ele[11] = ele[12] = ele[13] = ele[14] = T(0);       
    }

    //////////////////////////////////////////////////////////////////////////
    /// Translate transformation
    //////////////////////////////////////////////////////////////////////////
    void TranslateMatrix(T const dx, T const dy, T const dz)
    {
        this->IdentityMatrix();
        ele[12] = dx;
        ele[13] = dy;
        ele[14] = dz;   
    }

    //////////////////////////////////////////////////////////////////////////
    /// Scale transformation
    //////////////////////////////////////////////////////////////////////////
    void ScaleMatrix(T const a, T const b, T const c)
    {
        this->IdentityMatrix();
        ele[0] = a;
        ele[5] = b;
        ele[10] = c;
    }

    //////////////////////////////////////////////////////////////////////////
    /// Uniform scale transformation
    //////////////////////////////////////////////////////////////////////////
    void ScaleMatrix(T const a)
    {
        this->IdentityMatrix();
        ele[0] = ele[5] = ele[10] = a;

    }

    //////////////////////////////////////////////////////////////////////////
    /// Rotation around x axis
    //////////////////////////////////////////////////////////////////////////
    void RotateXMatrix(T const angle)
    {
        T rads = angle * TraitsType::PI() / T(180);
        this->IdentityMatrix();
        ele[5] = ele[10] = cos(rads);
        ele[6] = sin(rads);
        ele[9] = -ele[6];
    }

    //////////////////////////////////////////////////////////////////////////
    /// Rotation around y axis  
    //////////////////////////////////////////////////////////////////////////
    void RotateYMatrix(T const angle)
    {
        T rads = angle * TraitsType::PI() / T(180);
        this->IdentityMatrix();
        ele[0] = ele[10] = cos(rads);
        ele[8] = sin(rads);
        ele[2] = -ele[8];
    }

    //////////////////////////////////////////////////////////////////////////
    /// Rotation around z axis
    //////////////////////////////////////////////////////////////////////////
    void RotateZMatrix(T const angle)
    {
        T rads = angle * TraitsType::PI() / T(180);
        this->IdentityMatrix();
        ele[0] = ele[5] = cos(rads);
        ele[1] = sin(rads);
        ele[4] = -ele[1];
    }

    //////////////////////////////////////////////////////////////////////////
    /// Translate current matrix
    //////////////////////////////////////////////////////////////////////////
    void Translate(T const dx, T const dy, T const dz)
    {
        Matrix trans;
        trans.TranslateMatrix(dx, dy, dz);
        *this *= trans;
    }

    //////////////////////////////////////////////////////////////////////////
    /// Scale current matrix
    //////////////////////////////////////////////////////////////////////////
    void Scale(T const a, T const b, T const c)
    {
        Matrix scale;
        scale.ScaleMatrix(a, b, c);
        *this *= scale;
    }

    //////////////////////////////////////////////////////////////////////////
    /// Rotate current matrix around arbitrary axis
    //////////////////////////////////////////////////////////////////////////
    void Rotate(T const angle, T const x, T const y, T const z)
    {
        if(x == 0 && y == 0 && z == 0)  return;
        if(x == 0 && y == 0)
        {
            this->RotateZ(angle);
            return;
        }
        if(x == 0 && z == 0)
        {
            this->RotateY(angle);
            return;
        }
        if(z == 0 && y == 0)
        {
            this->RotateX(angle);
            return;
        }

        T a, b, c, d2, d2inv;
        T rads = angle * TraitsType::PI() / T(180);
        T cosa = cos(rads);
        T sina = sin(rads);
        Matrix res;

        T len_inv = T(1) / sqrt(x*x + y*y + z*z);
        a = x * len_inv;
        b = y * len_inv;
        c = z * len_inv;
        d2 = T(1) - a*a;
        d2inv = T(1) / d2;

        res.ele[0] = d2*cosa + T(1) - d2;
        res.ele[1] = a*b*(T(1) - cosa) + c*sina;
        res.ele[2] = a*c*(T(1) - cosa) - b*sina;
        res.ele[3] = T(0);

        res.ele[4] = a*b*(T(1) - cosa) - c*sina;
        res.ele[5] = (a*a*b*b + c*c)*cosa*d2inv + b*b;
        res.ele[6] = b*c*(T(1) - cosa) + a*sina;
        res.ele[7] = T(0);

        res.ele[8] = a*c*(T(1) - cosa) + b*sina;
        res.ele[9] = b*c*(T(1) - cosa) - a*sina;
        res.ele[10] = (a*a*c*c + b*b)*cosa*d2inv + c*c;
        res.ele[11] = T(0);

        res.ele[12] = T(0);
        res.ele[13] = T(0);
        res.ele[14] = T(0);
        res.ele[15] = T(1);

        *this *= res;
    }

    //////////////////////////////////////////////////////////////////////////
    /// Rotate current matrix around x axis
    //////////////////////////////////////////////////////////////////////////
    void RotateX(T const angle)
    {
        Matrix mat;
        mat.RotateXMatrix(angle);
        *this *= mat;
    }

    //////////////////////////////////////////////////////////////////////////
    /// Rotate current matrix around y axis
    //////////////////////////////////////////////////////////////////////////
    void RotateY(T const angle)
    {
        Matrix mat;
        mat.RotateYMatrix(angle);
        *this *= mat;
    }

    //////////////////////////////////////////////////////////////////////////
    /// Rotate current matrix around z axis
    //////////////////////////////////////////////////////////////////////////
    void RotateZ(T const angle)
    {
        Matrix mat;
        mat.RotateZMatrix(angle);
        *this *= mat;
    }
};
//============================================================================
template <typename T> class Vector
{
public:
    T ele[4];

    Vector()
    {
        ele[0] = 0.0f;
        ele[1] = 0.0f;
        ele[2] = 0.0f;
        ele[3] = 1.0f;
    }

    Vector(const Vector &v)
    {
        ele[0] = v.ele[0];
        ele[1] = v.ele[1];
        ele[2] = v.ele[2];
        ele[3] = v.ele[3];      
    }

    Vector(const T x, const T y, const T z, const T w = T(1.0))
    {
        ele[0] = x;
        ele[1] = y;
        ele[2] = z;
        ele[3] = w;
    }

    Vector(const T src[4])
    {
        ele[0] = src[0];
        ele[1] = src[1];
        ele[2] = src[2];
        ele[3] = src[3];
    }   

    operator T* () { return ele; }  
    operator const T* () const { return ele; }

    Vector& operator = (const Vector &a)
    {
        ele[0] = a.ele[0];
        ele[1] = a.ele[1];
        ele[2] = a.ele[2];
        ele[3] = a.ele[3];
        return *this; 
    }

    Vector& operator *= (const Matrix<T> &Mat)
    {
        T temp[4];
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

    Vector& operator *= (T const s)
    {
        ele[0] *= s;
        ele[1] *= s;
        ele[2] *= s;
        ele[3] *= s;    
        return *this;
    }

    Vector& operator += (Vector const &B)
    {
        ele[0] += B.ele[0];
        ele[1] += B.ele[1];
        ele[2] += B.ele[2];
        ele[3] += B.ele[3];
        return *this;
    }

    Vector& operator -= (Vector const &B)
    {
        ele[0] -= B.ele[0];
        ele[1] -= B.ele[1];
        ele[2] -= B.ele[2];
        ele[3] -= B.ele[3];
        return *this;
    }

    T Length() { return sqrt(ele[0]*ele[0] + ele[1]*ele[1] + ele[2]*ele[2]); }

    T Length2() { return (ele[0]*ele[0] + ele[1]*ele[1] + ele[2]*ele[2]); }

    void Normalize()
    {
        T vecLenInv = T(1) / sqrt(ele[0]*ele[0] + ele[1]*ele[1] + ele[2]*ele[2]);
        ele[0] *= vecLenInv;
        ele[1] *= vecLenInv;
        ele[2] *= vecLenInv;
    }
};
//============================================================================
template <typename T> Matrix<T> operator * (Matrix<T> const &A, Matrix<T> const &B) 
{
    Matrix<T> Res;

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
template <typename T> Matrix<T> operator * (Matrix<T> const &A, T const s) 
{
    Matrix<T> Res;

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
template <typename T> Matrix<T> operator * (T const s, Matrix<T> const &A) 
{
    return A*s; 
}
//----------------------------------------------------------------------------
template <typename T> Matrix<T> operator + (Matrix<T> const &A, Matrix<T> const &B) 
{
    Matrix<T> Res;

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
template <typename T> Matrix<T> operator - (Matrix<T> const &A, Matrix<T> const &B) 
{
    Matrix<T> Res;

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
template <typename T> Vector<T> operator * (Vector<T> const &Vec, Matrix<T> const &Mat) 
{
    Vector<T> Res;
    Res.ele[0] = Mat.ele[0]*Vec.ele[0] + Mat.ele[1]*Vec.ele[1] + Mat.ele[2]*Vec.ele[2] + Mat.ele[3]*Vec.ele[3]; 
    Res.ele[1] = Mat.ele[4]*Vec.ele[0] + Mat.ele[5]*Vec.ele[1] + Mat.ele[6]*Vec.ele[2] + Mat.ele[7]*Vec.ele[3]; 
    Res.ele[2] = Mat.ele[8]*Vec.ele[0] + Mat.ele[9]*Vec.ele[1] + Mat.ele[10]*Vec.ele[2] + Mat.ele[11]*Vec.ele[3]; 
    Res.ele[3] = Mat.ele[12]*Vec.ele[0] + Mat.ele[13]*Vec.ele[1] + Mat.ele[14]*Vec.ele[2] + Mat.ele[15]*Vec.ele[3]; 
    return Res;     
}
//----------------------------------------------------------------------------
template <typename T> Vector<T> operator * (Matrix<T> const &Mat, Vector<T> const &Vec) 
{
    Vector<T> Res;
    Res.ele[0] = Mat.ele[0]*Vec.ele[0] + Mat.ele[4]*Vec.ele[1] + Mat.ele[8]*Vec.ele[2] + Mat.ele[12]*Vec.ele[3]; 
    Res.ele[1] = Mat.ele[1]*Vec.ele[0] + Mat.ele[5]*Vec.ele[1] + Mat.ele[9]*Vec.ele[2] + Mat.ele[13]*Vec.ele[3]; 
    Res.ele[2] = Mat.ele[2]*Vec.ele[0] + Mat.ele[6]*Vec.ele[1] + Mat.ele[10]*Vec.ele[2] + Mat.ele[14]*Vec.ele[3]; 
    Res.ele[3] = Mat.ele[3]*Vec.ele[0] + Mat.ele[7]*Vec.ele[1] + Mat.ele[11]*Vec.ele[2] + Mat.ele[15]*Vec.ele[3]; 
    return Res;     
}
//----------------------------------------------------------------------------
template <typename T> T operator * (Vector<T> const &A, Vector<T> const &B) 
{
    return A.ele[0]*B.ele[0] + A.ele[1]*B.ele[1] + A.ele[2]*B.ele[2];   
}
//----------------------------------------------------------------------------
template <typename T> Vector<T> operator % (Vector<T> const &A, Vector<T> const &B) 
{
    Vector<T> Res;
    Res.ele[0] = A.ele[1] * B.ele[2] - A.ele[2] * B.ele[1]; 
    Res.ele[1] = A.ele[2] * B.ele[0] - A.ele[0] * B.ele[2]; 
    Res.ele[2] = A.ele[0] * B.ele[1] - A.ele[1] * B.ele[0]; 
    Res.ele[3] = 0.0f;
    return Res;
}
//----------------------------------------------------------------------------
template <typename T> Vector<T> operator * (Vector<T> const &V, T const s) 
{
    Vector<T> Res;
    Res.ele[0] = V.ele[0] * s;
    Res.ele[1] = V.ele[1] * s;
    Res.ele[2] = V.ele[2] * s;
    Res.ele[3] = V.ele[3] * s;  
    return Res;
}
//----------------------------------------------------------------------------
template <typename T> Vector<T> operator * (T const s, Vector<T> const &V) 
{
    Vector<T> Res;
    Res.ele[0] = V.ele[0] * s;
    Res.ele[1] = V.ele[1] * s;
    Res.ele[2] = V.ele[2] * s;
    Res.ele[3] = V.ele[3] * s;  
    return Res;
}
//----------------------------------------------------------------------------
template <typename T> Vector<T> operator + (Vector<T> const &A, Vector<T> const &B) 
{
    Vector<T> Res;
    Res.ele[0] = A.ele[0] + B.ele[0];
    Res.ele[1] = A.ele[1] + B.ele[1];
    Res.ele[2] = A.ele[2] + B.ele[2];
    Res.ele[3] = A.ele[3] + B.ele[3];
    return Res;
}
//----------------------------------------------------------------------------
template <typename T> Vector<T> operator - (Vector<T> const &A, Vector<T> const &B) 
{
    Vector<T> Res;
    Res.ele[0] = A.ele[0] - B.ele[0];
    Res.ele[1] = A.ele[1] - B.ele[1];
    Res.ele[2] = A.ele[2] - B.ele[2];
    Res.ele[3] = A.ele[3] - B.ele[3];
    return Res;
}
//----------------------------------------------------------------------------
template <typename T> Vector<T> operator - (Vector<T> const &A) 
{
    Vector<T> Res;
    Res.ele[0] = - A.ele[0];
    Res.ele[1] = - A.ele[1];
    Res.ele[2] = - A.ele[2];
    Res.ele[3] = - A.ele[3];
    return Res;
}
//----------------------------------------------------------------------------


typedef Vector<float> Vectorf;
typedef Vector<double> Vectord;
typedef Matrix<float> Matrixf;
typedef Matrix<double> Matrixd;

#endif
