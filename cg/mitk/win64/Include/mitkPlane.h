/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkPlane_h
#define __mitkPlane_h

#include "mitkObject.h"
#include "mitkMatrix.h"

/// mitkPlane - a class to represent a plane
///////////////////////////////////////////////////////////////////////////
/// mitkPlane is a class to represenet a plane
class MITK_COMMON_API mitkPlane : public mitkObject
{
public:
    MITK_TYPE(mitkPlane,mitkObject)

    virtual void PrintSelf(ostream& os);

    mitkPlane();    

    ///////////////////////////////////////////////////////////////////////////
    /// 
    ///////////////////////////////////////////////////////////////////////////
    float Evaluate(float x[3]);
    float Evaluate(float x, float y, float z);  

    ///////////////////////////////////////////////////////////////////////////
    /// 
    ///////////////////////////////////////////////////////////////////////////
    void SetNormal(float nx, float ny, float nz) {m_Normal->ele[0] = nx; m_Normal->ele[1] = ny; m_Normal->ele[2] = nz; m_Normal->Normalize();}
    void SetNormal(float normal[3]) {m_Normal->ele[0] = normal[0]; m_Normal->ele[1] = normal[1]; m_Normal->ele[2] = normal[2]; m_Normal->Normalize();}
    void GetNormal(float &nx, float &ny, float &nz) {nx = m_Normal->ele[0]; ny = m_Normal->ele[1]; nz = m_Normal->ele[2];}  
    const mitkVector* GetNormal(void)  {return m_Normal;}

    ///////////////////////////////////////////////////////////////////////////
    /// 
    ///////////////////////////////////////////////////////////////////////////
    void SetOrigin(float x, float y, float z) {m_Origin->ele[0] = x; m_Origin->ele[1] = y; m_Origin->ele[2] = z;}
    void SetOrigin(float origin[3]) {m_Origin->ele[0] = origin[0]; m_Origin->ele[1] = origin[1]; m_Origin->ele[2] = origin[2];}
    void GetOrigin(float &x, float &y, float &z) {x = m_Origin->ele[0]; y = m_Origin->ele[1]; z = m_Origin->ele[2];}    
    const mitkVector* GetOrigin(void)  {return m_Origin;}
    
    ///////////////////////////////////////////////////////////////////////////
    /// 
    ///////////////////////////////////////////////////////////////////////////
    void TranslateTowardNormal(float distance);

    ///////////////////////////////////////////////////////////////////////////
    /// 
    ///////////////////////////////////////////////////////////////////////////
    void ProjectPoint(float x[3], float xproj[3]);
    void ProjectPoint(const mitkVector &srcPoint, mitkVector &projPoint); 

    ///////////////////////////////////////////////////////////////////////////
    /// 
    ///////////////////////////////////////////////////////////////////////////
    float DistanceToPlane(float x[3]);
    float DistanceToPlane(const mitkVector &srcPoint);

    ///////////////////////////////////////////////////////////////////////////
    /// 
    ///////////////////////////////////////////////////////////////////////////
    int IntersectWithLine(float p1[3], float p2[3], float& t, float x[3]);
    int IntersectWithLine(const mitkVector &point1, const mitkVector &point2, float &t, mitkVector &intersectedPoint);


protected:
    mitkVector *m_Normal;
    mitkVector *m_Origin;  

    virtual ~mitkPlane();

private:
    mitkPlane(const mitkPlane&);
    void operator=(const mitkPlane&);  
};

inline float mitkPlane::Evaluate(float x[3])
{
    mitkVector point(x[0], x[1], x[2]);
    point -= *m_Origin;
    return *m_Normal * point;
}

inline float mitkPlane::Evaluate(float x, float y, float z)
{
    mitkVector point(x, y, z);
    point -= *m_Origin;
    return *m_Normal * point;
}

inline float mitkPlane::DistanceToPlane(float x[3])
{
    mitkVector point(x[0], x[1], x[2]);
    point -= *m_Origin;
    return fabsf(*m_Normal * point);  
}

inline float mitkPlane::DistanceToPlane(const mitkVector &srcPoint)
{
    mitkVector point = srcPoint;
    point -= *m_Origin;
    return fabsf(*m_Normal * point);  
}


//#define DEFINED_mitkPlane



#endif




