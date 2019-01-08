/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkMatrix_h
#define __mitkMatrix_h

#include <math.h>
//#include "mitkGlobal.h"
#include "mitkSIMD.h"

#ifdef USE_SIMD
#pragma pack(push,16)    /* Must ensure class & union 16-B aligned */
#endif

/// mitkMatrix - an encapsulation of a matrix
///////////////////////////////////////////////////////////////////////////
/// mitkMatrix provides an encapsulation of matrix operations. It is used
/// in volume rendering algorithm, which requires intensive matrix calculations.
/// The interface of mitkMatrix provides many common matrix operations.
class MITK_COMMON_API mitkMatrix
{
public:

#ifdef USE_SIMD
    union
    {
        struct
        {
            __m128 r1, r2, r3, r4;
        };
        struct
        {
            float ele[16];
        };
    };

    static void* operator new(size_t size)
    {
        return _aligned_malloc(size, 16);
    }

    static void operator delete(void *p)
    {
        _aligned_free(p);
    }

    static void* operator new[](size_t size)
    {
        return _aligned_malloc(size, 16);
    }

    static void operator delete[](void *p)
    {
        _aligned_free(p);
    }
#else
    float ele[16];
#endif

    mitkMatrix() {}
    mitkMatrix(const mitkMatrix &m)
    {
    #ifdef USE_SIMD
        r1 = m.r1;
        r2 = m.r2;
        r3 = m.r3;
        r4 = m.r4;
    #else
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
    #endif
    }

    mitkMatrix(float e0, float e1, float e2, float e3,
               float e4, float e5, float e6, float e7,
               float e8, float e9, float e10, float e11,
               float e12, float e13, float e14, float e15)
    {
    #ifdef USE_SIMD
        r1 = _mm_setr_ps(e0, e1, e2, e3);
        r2 = _mm_setr_ps(e4, e5, e6, e7);
        r3 = _mm_setr_ps(e8, e9, e10, e11);
        r4 = _mm_setr_ps(e12, e13, e14, e15);
    #else
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
    #endif
    }   

    mitkMatrix& operator = (const mitkMatrix &m) 
    {
    #ifdef USE_SIMD
        r1 = m.r1;
        r2 = m.r2;
        r3 = m.r3;
        r4 = m.r4;
    #else
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
    #endif
        return *this;
    }

    friend mitkMatrix operator * (const mitkMatrix&, const mitkMatrix&);
    friend mitkMatrix operator + (const mitkMatrix&, const mitkMatrix&);
    friend mitkMatrix operator - (const mitkMatrix&, const mitkMatrix&);
    friend mitkMatrix operator + (const mitkMatrix&);
    friend mitkMatrix operator - (const mitkMatrix&);
    friend mitkMatrix operator * (const mitkMatrix&, const float);
    friend mitkMatrix operator * (const float, const mitkMatrix&);

    mitkMatrix& operator *= (const mitkMatrix &);
    mitkMatrix& operator *= (const float);
    mitkMatrix& operator += (const mitkMatrix &);
    mitkMatrix& operator -= (const mitkMatrix &);

    operator const float* () const { return ele; }  
    operator float* () { return ele; }

    //////////////////////////////////////////////////////////////////////////
    /// Transposes the matrix   
    //////////////////////////////////////////////////////////////////////////
    void    Transpose();    
    
    //////////////////////////////////////////////////////////////////////////
    /// Inverses the matrix and returns the determinant
    //////////////////////////////////////////////////////////////////////////
    float   Inverse();      

    //////////////////////////////////////////////////////////////////////////
    /// Returns the determinant
    //////////////////////////////////////////////////////////////////////////  
    float   Determinant();  

    //////////////////////////////////////////////////////////////////////////
    /// Adjoint matrix
    //////////////////////////////////////////////////////////////////////////
    void    Adjoint();

    //////////////////////////////////////////////////////////////////////////
    /// Returns the minimum absolute value of the matrix
    //////////////////////////////////////////////////////////////////////////
    float   MinValue();     

    //////////////////////////////////////////////////////////////////////////
    /// Returns the maximum absolute value of the matrix
    //////////////////////////////////////////////////////////////////////////
    float   MaxValue();     

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
    void TranslateMatrix(const float dx, const float dy, const float dz);

    //////////////////////////////////////////////////////////////////////////
    /// Scale transformation
    //////////////////////////////////////////////////////////////////////////
    void ScaleMatrix(const float a, const float b, const float c);

    //////////////////////////////////////////////////////////////////////////
    /// Uniform scale transformation
    //////////////////////////////////////////////////////////////////////////
    void ScaleMatrix(const float a);

    //////////////////////////////////////////////////////////////////////////
    /// Rotation around x axis
    //////////////////////////////////////////////////////////////////////////
    void RotateXMatrix(const float angle);

    //////////////////////////////////////////////////////////////////////////
    /// Rotation around y axis  
    //////////////////////////////////////////////////////////////////////////
    void RotateYMatrix(const float angle);

    //////////////////////////////////////////////////////////////////////////
    /// Rotation around z axis
    //////////////////////////////////////////////////////////////////////////
    void RotateZMatrix(const float angle);

    //////////////////////////////////////////////////////////////////////////
    /// Translate current matrix
    //////////////////////////////////////////////////////////////////////////
    void Translate(const float dx, const float dy, const float dz);

    //////////////////////////////////////////////////////////////////////////
    /// Scale current matrix
    //////////////////////////////////////////////////////////////////////////
    void Scale(const float a, const float b, const float c);

    //////////////////////////////////////////////////////////////////////////
    /// Rotate current matrix around arbitrary axis
    //////////////////////////////////////////////////////////////////////////
    void Rotate(const float angle, const float x, const float y, const float z);

    //////////////////////////////////////////////////////////////////////////
    /// Rotate current matrix around x axis
    //////////////////////////////////////////////////////////////////////////
    void RotateX(const float angle);

    //////////////////////////////////////////////////////////////////////////
    /// Rotate current matrix around y axis
    //////////////////////////////////////////////////////////////////////////
    void RotateY(const float angle);

    //////////////////////////////////////////////////////////////////////////
    /// Rotate current matrix around z axis
    //////////////////////////////////////////////////////////////////////////
    void RotateZ(const float angle);
};

/// mitkVector - an encapsulation of a 4-element vector
///////////////////////////////////////////////////////////////////////////
/// mitkVector provides an encapsulation of vector operations. 
class MITK_COMMON_API mitkVector
{
public:
#ifdef USE_SIMD
    union
    {
        __m128 vec;
        struct
        { 
            float   ele[4];
        };
    };

    static void* operator new(size_t size)
    {
        return _aligned_malloc(size, 16);
    }

    static void operator delete(void *p)
    {
        _aligned_free(p);
    }

    static void* operator new[](size_t size)
    {
        return _aligned_malloc(size, 16);
    }

    static void operator delete[](void *p)
    {
        _aligned_free(p);
    }
#else
    float ele[4];
#endif

    mitkVector()
    {
    #ifdef USE_SIMD
            vec = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
    #else
            ele[0] = 0.0f;
            ele[1] = 0.0f;
            ele[2] = 0.0f;
            ele[3] = 1.0f;
    #endif
    }

    mitkVector(const mitkVector &v)
    {
    #ifdef USE_SIMD
            vec = v.vec;
    #else
            ele[0] = v.ele[0];
            ele[1] = v.ele[1];
            ele[2] = v.ele[2];
            ele[3] = v.ele[3];
    #endif
    }

    mitkVector(const float x, const float y, const float z, const float w = 1.0f)
    {
    #ifdef USE_SIMD
        vec = _mm_setr_ps(x, y, z, w);
    #else
            ele[0] = x;
            ele[1] = y;
            ele[2] = z;
            ele[3] = w;
    #endif
    }

    mitkVector(const float srcVector[4])
    {
        ele[0] = srcVector[0];
        ele[1] = srcVector[1];
        ele[2] = srcVector[2];
        ele[3] = srcVector[3];
    }   

    
    operator float* () { return ele; }  
    operator const float* () const { return ele; }

    mitkVector& operator = (const mitkVector &a)
    {
    #ifdef USE_SIMD
        vec = a.vec;
    #else
        ele[0] = a.ele[0];
        ele[1] = a.ele[1];
        ele[2] = a.ele[2];
        ele[3] = a.ele[3];
    #endif
        return *this; 
    }
    
    friend mitkVector operator * (const mitkVector&, const mitkMatrix&);
    friend float operator * (const mitkVector &, const mitkVector &);           // Dot Product
    friend mitkVector operator % (const mitkVector &, const mitkVector &);      // Cross Product
    friend mitkVector operator * (const mitkVector &, const float);
    friend mitkVector operator * (const float, const mitkVector &);
    friend mitkVector operator + (const mitkVector&);
    friend mitkVector operator + (const mitkVector&, const mitkVector&);
    friend mitkVector operator - (const mitkVector&);
    friend mitkVector operator - (const mitkVector&, const mitkVector&);
    friend mitkVector operator ~ (const mitkVector&);                           // Normalize

    mitkVector& operator *= (const mitkMatrix &);
    mitkVector& operator *= (const float);
    mitkVector& operator += (const mitkVector &);
    mitkVector& operator -= (const mitkVector &);

    float Length();
    float Length2();
    void Normalize();
};

#ifdef USE_SIMD
#define _mm_ror_ps(vec,i)   \
    (((i)%4) ? (_mm_shuffle_ps(vec,vec, _MM_SHUFFLE((unsigned char)(i+3)%4,(unsigned char)(i+2)%4,(unsigned char)(i+1)%4,(unsigned char)(i+0)%4))) : (vec))
#define _mm_rol_ps(vec,i)   \
    (((i)%4) ? (_mm_shuffle_ps(vec,vec, _MM_SHUFFLE((unsigned char)(7-i)%4,(unsigned char)(6-i)%4,(unsigned char)(5-i)%4,(unsigned char)(4-i)%4))) : (vec))
const float _NEGMASK = 0.0f * -1.0f;
const __m128 _MASKSIGN_ = _mm_set_ps(_NEGMASK, _NEGMASK, _NEGMASK, _NEGMASK);
#define _mm_abs_ps(vec)     _mm_andnot_ps(_MASKSIGN_,vec)
#define _mm_neg_ps(vec)     _mm_xor_ps(_MASKSIGN_,vec)

#pragma pack(pop)
#endif

//----------------------------------------------------------------------------
inline void mitkMatrix::ZeroMatrix() 
{
#ifdef USE_SIMD
    r1 = _mm_setzero_ps();
    r2 = _mm_setzero_ps();
    r3 = _mm_setzero_ps();
    r4 = _mm_setzero_ps();
#else
    ele[0] = ele[1] = ele[2] = ele[3] = 0.0f;
    ele[4] = ele[5] = ele[6] = ele[7] = 0.0f;
    ele[8] = ele[9] = ele[10] = ele[11] = 0.0f;
    ele[12] = ele[13] = ele[14] = ele[15] = 0.0f;
#endif
}
//----------------------------------------------------------------------------
inline void mitkMatrix::IdentityMatrix() 
{
#ifdef USE_SIMD
    r1 = _mm_setr_ps(1.0f, 0.0f, 0.0f, 0.0f);
    r2 = _mm_setr_ps(0.0f, 1.0f, 0.0f, 0.0f);
    r3 = _mm_setr_ps(0.0f, 0.0f, 1.0f, 0.0f);
    r4 = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
#else
    ele[0] = ele[5] = ele[10] = ele[15] = 1.0f;
    ele[1] = ele[2] = ele[3] = ele[4] = 0.0f;
    ele[6] = ele[7] = ele[8] = ele[9] = 0.0f;
    ele[11] = ele[12] = ele[13] = ele[14] = 0.0f;
#endif
}
//----------------------------------------------------------------------------
inline mitkMatrix operator * (const mitkMatrix &A, const mitkMatrix &B) 
{
    mitkMatrix Res;

#ifdef USE_SIMD

    __m128 Result;  

    Result = _mm_mul_ps(_mm_set_ps1(B.ele[0]), A.r1);
    Result = _mm_add_ps(Result, _mm_mul_ps(_mm_set_ps1(B.ele[1]), A.r2));
    Result = _mm_add_ps(Result, _mm_mul_ps(_mm_set_ps1(B.ele[2]), A.r3));
    Result = _mm_add_ps(Result, _mm_mul_ps(_mm_set_ps1(B.ele[3]), A.r4));
    Res.r1 = Result;
    
    Result = _mm_mul_ps(_mm_set_ps1(B.ele[4]), A.r1);
    Result = _mm_add_ps(Result, _mm_mul_ps(_mm_set_ps1(B.ele[5]), A.r2));
    Result = _mm_add_ps(Result, _mm_mul_ps(_mm_set_ps1(B.ele[6]), A.r3));
    Result = _mm_add_ps(Result, _mm_mul_ps(_mm_set_ps1(B.ele[7]), A.r4));
    Res.r2 = Result;
    
    Result = _mm_mul_ps(_mm_set_ps1(B.ele[8]), A.r1);
    Result = _mm_add_ps(Result, _mm_mul_ps(_mm_set_ps1(B.ele[9]), A.r2));
    Result = _mm_add_ps(Result, _mm_mul_ps(_mm_set_ps1(B.ele[10]), A.r3));
    Result = _mm_add_ps(Result, _mm_mul_ps(_mm_set_ps1(B.ele[11]), A.r4));
    Res.r3 = Result;
    
    Result = _mm_mul_ps(_mm_set_ps1(B.ele[12]), A.r1);
    Result = _mm_add_ps(Result, _mm_mul_ps(_mm_set_ps1(B.ele[13]), A.r2));
    Result = _mm_add_ps(Result, _mm_mul_ps(_mm_set_ps1(B.ele[14]), A.r3));
    Result = _mm_add_ps(Result, _mm_mul_ps(_mm_set_ps1(B.ele[15]), A.r4));
    Res.r4 = Result;    
        
    return Res;
    
#else
    
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
    
#endif
}
//----------------------------------------------------------------------------
inline mitkMatrix& mitkMatrix::operator *= (const mitkMatrix &B) 
{
#ifdef USE_SIMD

    __m128 Result1, Result2, Result3, Result4;  

    Result1 = _mm_mul_ps(_mm_set_ps1(B.ele[0]), r1);
    Result1 = _mm_add_ps(Result1, _mm_mul_ps(_mm_set_ps1(B.ele[1]), r2));
    Result1 = _mm_add_ps(Result1, _mm_mul_ps(_mm_set_ps1(B.ele[2]), r3));
    Result1 = _mm_add_ps(Result1, _mm_mul_ps(_mm_set_ps1(B.ele[3]), r4));
            
    Result2 = _mm_mul_ps(_mm_set_ps1(B.ele[4]), r1);
    Result2 = _mm_add_ps(Result2, _mm_mul_ps(_mm_set_ps1(B.ele[5]), r2));
    Result2 = _mm_add_ps(Result2, _mm_mul_ps(_mm_set_ps1(B.ele[6]), r3));
    Result2 = _mm_add_ps(Result2, _mm_mul_ps(_mm_set_ps1(B.ele[7]), r4));
            
    Result3 = _mm_mul_ps(_mm_set_ps1(B.ele[8]), r1);
    Result3 = _mm_add_ps(Result3, _mm_mul_ps(_mm_set_ps1(B.ele[9]), r2));
    Result3 = _mm_add_ps(Result3, _mm_mul_ps(_mm_set_ps1(B.ele[10]), r3));
    Result3 = _mm_add_ps(Result3, _mm_mul_ps(_mm_set_ps1(B.ele[11]), r4));
            
    Result4 = _mm_mul_ps(_mm_set_ps1(B.ele[12]), r1);
    Result4 = _mm_add_ps(Result4, _mm_mul_ps(_mm_set_ps1(B.ele[13]), r2));
    Result4 = _mm_add_ps(Result4, _mm_mul_ps(_mm_set_ps1(B.ele[14]), r3));
    Result4 = _mm_add_ps(Result4, _mm_mul_ps(_mm_set_ps1(B.ele[15]), r4));

    r1 = Result1;
    r2 = Result2;
    r3 = Result3;
    r4 = Result4;               
    return *this;

#else

    mitkMatrix Res;
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
    
#endif
}
//----------------------------------------------------------------------------
inline mitkMatrix operator * (const mitkMatrix &A, const float s) 
{
    mitkMatrix Res;

#ifdef USE_SIMD

    __m128 S = _mm_set_ps1(s);
    Res.r1 = _mm_mul_ps(A.r1, S);
    Res.r2 = _mm_mul_ps(A.r2, S);
    Res.r3 = _mm_mul_ps(A.r3, S);
    Res.r4 = _mm_mul_ps(A.r4, S);   
    return Res;

#else

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

#endif
}
//----------------------------------------------------------------------------
inline mitkMatrix operator * (const float s, const mitkMatrix &A) 
{
    mitkMatrix Res;

#ifdef USE_SIMD

    __m128 S = _mm_set_ps1(s);
    Res.r1 = _mm_mul_ps(A.r1, S);
    Res.r2 = _mm_mul_ps(A.r2, S);
    Res.r3 = _mm_mul_ps(A.r3, S);
    Res.r4 = _mm_mul_ps(A.r4, S);   
    return Res;

#else

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

#endif
}
//----------------------------------------------------------------------------
inline mitkMatrix& mitkMatrix::operator *= (const float s) 
{
#ifdef USE_SIMD
    __m128 S = _mm_set_ps1(s);
    r1 = _mm_mul_ps(r1, S);
    r2 = _mm_mul_ps(r2, S);
    r3 = _mm_mul_ps(r3, S);
    r4 = _mm_mul_ps(r4, S); 
    return *this;
#else
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
#endif
}
//----------------------------------------------------------------------------
inline mitkMatrix operator + (const mitkMatrix &A, const mitkMatrix &B) 
{
    mitkMatrix Res;

#ifdef USE_SIMD

    Res.r1 = _mm_add_ps(A.r1, B.r1);
    Res.r2 = _mm_add_ps(A.r2, B.r2);
    Res.r3 = _mm_add_ps(A.r3, B.r3);
    Res.r4 = _mm_add_ps(A.r4, B.r4);
    return Res;

#else

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

#endif
}
//----------------------------------------------------------------------------
inline mitkMatrix & mitkMatrix::operator += (const mitkMatrix &B) 
{
#ifdef USE_SIMD
    r1 = _mm_add_ps(r1, B.r1);
    r2 = _mm_add_ps(r2, B.r2);
    r3 = _mm_add_ps(r3, B.r3);
    r4 = _mm_add_ps(r4, B.r4);
    return *this;
#else
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
#endif
}
//----------------------------------------------------------------------------
inline mitkMatrix operator - (const mitkMatrix &A, const mitkMatrix &B) 
{
    mitkMatrix Res;

#ifdef USE_SIMD

    Res.r1 = _mm_sub_ps(A.r1, B.r1);
    Res.r2 = _mm_sub_ps(A.r2, B.r2);
    Res.r3 = _mm_sub_ps(A.r3, B.r3);
    Res.r4 = _mm_sub_ps(A.r4, B.r4);
    return Res;
    
#else
    
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

#endif
}
//----------------------------------------------------------------------------
inline mitkMatrix operator - (const mitkMatrix &A)
{
    mitkMatrix Res;

#ifdef USE_SIMD

    Res.r1 = _mm_neg_ps(A.r1);
    Res.r2 = _mm_neg_ps(A.r2);
    Res.r3 = _mm_neg_ps(A.r3);
    Res.r4 = _mm_neg_ps(A.r4);
    return Res;

#else

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

#endif
}
//----------------------------------------------------------------------------
inline mitkMatrix & mitkMatrix::operator -= (const mitkMatrix &B) 
{
#ifdef USE_SIMD
    r1 = _mm_add_ps(r1, B.r1);
    r2 = _mm_add_ps(r2, B.r2);
    r3 = _mm_add_ps(r3, B.r3);
    r4 = _mm_add_ps(r4, B.r4);
    return *this;
#else   
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
#endif
}
//----------------------------------------------------------------------------
inline mitkVector operator * (const mitkVector& Vec, const mitkMatrix& Mat) 
{
    mitkVector Res;

#ifdef USE_SIMD

        mitkVector temp;

        temp.vec = _mm_mul_ps(Vec.vec, Mat.r1);
        Res.ele[0] = temp.ele[0] + temp.ele[1] + temp.ele[2] + temp.ele[3];

        temp.vec = _mm_mul_ps(Vec.vec, Mat.r2);
        Res.ele[1] = temp.ele[0] + temp.ele[1] + temp.ele[2] + temp.ele[3];

        temp.vec = _mm_mul_ps(Vec.vec, Mat.r3);
        Res.ele[2] = temp.ele[0] + temp.ele[1] + temp.ele[2] + temp.ele[3];

        temp.vec = _mm_mul_ps(Vec.vec, Mat.r4);
        Res.ele[3] = temp.ele[0] + temp.ele[1] + temp.ele[2] + temp.ele[3];
        return Res;

#else
    
    Res.ele[0] = Mat.ele[0]*Vec.ele[0] + Mat.ele[1]*Vec.ele[1] + Mat.ele[2]*Vec.ele[2] + Mat.ele[3]*Vec.ele[3]; 
    Res.ele[1] = Mat.ele[4]*Vec.ele[0] + Mat.ele[5]*Vec.ele[1] + Mat.ele[6]*Vec.ele[2] + Mat.ele[7]*Vec.ele[3]; 
    Res.ele[2] = Mat.ele[8]*Vec.ele[0] + Mat.ele[9]*Vec.ele[1] + Mat.ele[10]*Vec.ele[2] + Mat.ele[11]*Vec.ele[3]; 
    Res.ele[3] = Mat.ele[12]*Vec.ele[0] + Mat.ele[13]*Vec.ele[1] + Mat.ele[14]*Vec.ele[2] + Mat.ele[15]*Vec.ele[3]; 
    return Res; 
    
#endif
}
//----------------------------------------------------------------------------
inline mitkVector operator * (const mitkMatrix& Mat, mitkVector& Vec) 
{
    mitkVector Res;

#ifdef USE_SIMD

    Res.vec = _mm_mul_ps(Mat.r1, _mm_set_ps1(Vec.ele[0]));
    Res.vec = _mm_add_ps(Res.vec, _mm_mul_ps(Mat.r2, _mm_set_ps1(Vec.ele[1])));
    Res.vec = _mm_add_ps(Res.vec, _mm_mul_ps(Mat.r3, _mm_set_ps1(Vec.ele[2])));
    Res.vec = _mm_add_ps(Res.vec, _mm_mul_ps(Mat.r4, _mm_set_ps1(Vec.ele[3])));             
    return Res;

#else
    
    Res.ele[0] = Mat.ele[0]*Vec.ele[0] + Mat.ele[4]*Vec.ele[1] + Mat.ele[8]*Vec.ele[2] + Mat.ele[12]*Vec.ele[3]; 
    Res.ele[1] = Mat.ele[1]*Vec.ele[0] + Mat.ele[5]*Vec.ele[1] + Mat.ele[9]*Vec.ele[2] + Mat.ele[13]*Vec.ele[3]; 
    Res.ele[2] = Mat.ele[2]*Vec.ele[0] + Mat.ele[6]*Vec.ele[1] + Mat.ele[10]*Vec.ele[2] + Mat.ele[14]*Vec.ele[3]; 
    Res.ele[3] = Mat.ele[3]*Vec.ele[0] + Mat.ele[7]*Vec.ele[1] + Mat.ele[11]*Vec.ele[2] + Mat.ele[15]*Vec.ele[3]; 
    return Res; 
    
#endif
}
//----------------------------------------------------------------------------
inline mitkVector& mitkVector::operator *= (const mitkMatrix& Mat) 
{
#ifdef USE_SIMD

        __m128 temp;
        temp = _mm_mul_ps(Mat.r1, _mm_set_ps1(ele[0]));
        temp = _mm_add_ps(temp, _mm_mul_ps(Mat.r2, _mm_set_ps1(ele[1])));
        temp = _mm_add_ps(temp, _mm_mul_ps(Mat.r3, _mm_set_ps1(ele[2])));
        temp = _mm_add_ps(temp, _mm_mul_ps(Mat.r4, _mm_set_ps1(ele[3])));               
        vec  = temp;
        return *this;

#else
    
    float temp[4];
    temp[0] = Mat.ele[0]*ele[0] + Mat.ele[4]*ele[1] + Mat.ele[8]*ele[2] + Mat.ele[12]*ele[3]; 
    temp[1] = Mat.ele[1]*ele[0] + Mat.ele[5]*ele[1] + Mat.ele[9]*ele[2] + Mat.ele[13]*ele[3]; 
    temp[2] = Mat.ele[2]*ele[0] + Mat.ele[6]*ele[1] + Mat.ele[10]*ele[2] + Mat.ele[14]*ele[3]; 
    temp[3] = Mat.ele[3]*ele[0] + Mat.ele[7]*ele[1] + Mat.ele[11]*ele[2] + Mat.ele[15]*ele[3]; 
    ele[0] = temp[0];
    ele[1] = temp[1];
    ele[2] = temp[2];
    ele[3] = temp[3];   
    return *this;

#endif
}
//----------------------------------------------------------------------------
inline float operator * (const mitkVector& A, const mitkVector& B) 
{
#ifdef USE_SIMD
    mitkVector r;
    r.vec = _mm_mul_ps(A.vec, B.vec);
    return r.ele[0] + r.ele[1] + r.ele[2];
#else
    return A.ele[0]*B.ele[0] + A.ele[1]*B.ele[1] + A.ele[2]*B.ele[2];
#endif
}

//----------------------------------------------------------------------------
inline mitkVector operator % (const mitkVector& A, const mitkVector& B) 
{
    mitkVector Res;

#ifdef USE_SIMD
    __m128 l1, l2, m1, m2;
    l1 = _mm_shuffle_ps(A.vec,A.vec, _MM_SHUFFLE(3,1,0,2));
    l2 = _mm_shuffle_ps(B.vec,B.vec, _MM_SHUFFLE(3,0,2,1));
    m2 = _mm_mul_ps(l1, l2);

    l1 = _mm_shuffle_ps(A.vec,A.vec, _MM_SHUFFLE(3,0,2,1));
    l2 = _mm_shuffle_ps(B.vec,B.vec, _MM_SHUFFLE(3,1,0,2));
    m1 = _mm_mul_ps(l1, l2);

    Res.vec = _mm_sub_ps(m1, m2);       
    return Res;
#else
    Res.ele[0] = A.ele[1] * B.ele[2] - A.ele[2] * B.ele[1]; 
    Res.ele[1] = A.ele[2] * B.ele[0] - A.ele[0] * B.ele[2]; 
    Res.ele[2] = A.ele[0] * B.ele[1] - A.ele[1] * B.ele[0]; 
    Res.ele[3] = 0.0f;
    return Res;
#endif
}
//----------------------------------------------------------------------------
inline mitkVector operator * (const mitkVector &V, const float s) 
{
    mitkVector Res;
#ifdef USE_SIMD
    Res.vec = _mm_mul_ps(V.vec, _mm_set_ps1(s));
    return Res;
#else
    Res.ele[0] = V.ele[0] * s;
    Res.ele[1] = V.ele[1] * s;
    Res.ele[2] = V.ele[2] * s;
    Res.ele[3] = V.ele[3] * s;  
    return Res;
#endif
}
//----------------------------------------------------------------------------
inline mitkVector operator * (const float s, const mitkVector &V) 
{
    mitkVector Res;
#ifdef USE_SIMD
    Res.vec = _mm_mul_ps(V.vec, _mm_set_ps1(s));
    return Res;
#else
    Res.ele[0] = V.ele[0] * s;
    Res.ele[1] = V.ele[1] * s;
    Res.ele[2] = V.ele[2] * s;
    Res.ele[3] = V.ele[3] * s;  
    return Res;
#endif
}
//----------------------------------------------------------------------------
inline mitkVector& mitkVector::operator *= (const float s) 
{
#ifdef USE_SIMD
    vec = _mm_mul_ps(vec, _mm_set_ps1(s));
    return *this;
#else
    ele[0] *= s;
    ele[1] *= s;
    ele[2] *= s;
    ele[3] *= s;    
    return *this;
#endif
}
//----------------------------------------------------------------------------
inline mitkVector operator + (const mitkVector& A, const mitkVector& B) 
{
    mitkVector Res;
#ifdef USE_SIMD
    Res.vec = _mm_add_ps(A.vec, B.vec);
    return Res;
#else
    Res.ele[0] = A.ele[0] + B.ele[0];
    Res.ele[1] = A.ele[1] + B.ele[1];
    Res.ele[2] = A.ele[2] + B.ele[2];
    Res.ele[3] = A.ele[3] + B.ele[3];
    return Res;
#endif
}
//----------------------------------------------------------------------------
inline mitkVector operator - (const mitkVector& A, const mitkVector& B) 
{
    mitkVector Res;
#ifdef USE_SIMD
    Res.vec = _mm_sub_ps(A.vec, B.vec);
    return Res;
#else
    Res.ele[0] = A.ele[0] - B.ele[0];
    Res.ele[1] = A.ele[1] - B.ele[1];
    Res.ele[2] = A.ele[2] - B.ele[2];
    Res.ele[3] = A.ele[3] - B.ele[3];
    return Res;
#endif
}
//----------------------------------------------------------------------------
inline mitkVector operator - (const mitkVector& A)
{
    mitkVector Res;
#ifdef USE_SIMD
    Res.vec = _mm_neg_ps(A.vec);
    return Res;
#else
    Res.ele[0] = - A.ele[0];
    Res.ele[1] = - A.ele[1];
    Res.ele[2] = - A.ele[2];
    Res.ele[3] = - A.ele[3];
    return Res;
#endif
}
//----------------------------------------------------------------------------
inline mitkVector & mitkVector::operator += (const mitkVector &B) 
{
#ifdef USE_SIMD
    vec = _mm_add_ps(vec, B.vec);
    return *this;
#else
    ele[0] += B.ele[0];
    ele[1] += B.ele[1];
    ele[2] += B.ele[2];
    ele[3] += B.ele[3];
    return *this;
#endif
}
//----------------------------------------------------------------------------
inline mitkVector & mitkVector::operator -= (const mitkVector &B) 
{
#ifdef USE_SIMD
    vec = _mm_sub_ps(vec, B.vec);
    return *this;
#else
    ele[0] -= B.ele[0];
    ele[1] -= B.ele[1];
    ele[2] -= B.ele[2];
    ele[3] -= B.ele[3];
    return *this;
#endif
}
//----------------------------------------------------------------------------
inline float mitkVector::Length()
{
#ifdef USE_SIMD
    __m128 r = _mm_mul_ps(vec, vec);
    r = _mm_add_ss(_mm_movehl_ps(r, r), r);
    r = _mm_add_ss(_mm_shuffle_ps(r, r, 1), r);
    r = _mm_sqrt_ss(r);     
    return *(float *)&r;
#else
    return sqrtf(ele[0]*ele[0] + ele[1]*ele[1] + ele[2]*ele[2]);
#endif
}
//----------------------------------------------------------------------------
inline float mitkVector::Length2()
{
#ifdef USE_SIMD
    __m128 r = _mm_mul_ps(vec, vec);
    r = _mm_add_ss(_mm_movehl_ps(r, r), r);
    r = _mm_add_ss(_mm_shuffle_ps(r, r, 1), r);
    return *(float *)&r;
#else
    return (ele[0]*ele[0] + ele[1]*ele[1] + ele[2]*ele[2]);
#endif
}
//----------------------------------------------------------------------------
inline void mitkVector::Normalize() 
{
#ifdef USE_SIMD
    __m128 r = _mm_mul_ps(vec, vec);
    r = _mm_add_ps(_mm_movehl_ps(r, r), r);
    r = _mm_add_ss(_mm_shuffle_ps(r, r, 1), r);
    r = _mm_rsqrt_ps(r);
    vec = _mm_mul_ps(vec, _mm_shuffle_ps(r, r, 0)); 
#else   
    float vecLenInv = 1.0f / sqrtf(ele[0]*ele[0] + ele[1]*ele[1] + ele[2]*ele[2]);
    ele[0] *= vecLenInv;
    ele[1] *= vecLenInv;
    ele[2] *= vecLenInv;
#endif
}
//----------------------------------------------------------------------------
#endif

