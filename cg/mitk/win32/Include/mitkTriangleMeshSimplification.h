/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkTriangleMeshSimplification_h
#define __mitkTriangleMeshSimplification_h

#include "mitkMeshToMeshFilter.h"

class mitkHETriangleMesh;

/// mitkTriangleMeshSimplification - abstract class for triangle mesh simplification algorithms
///////////////////////////////////////////////////////////////////////////
/// mitkTriangleMeshSimplification is an abstract class for triangle mesh
/// simplification algorithms. The subclasses which implement concrete
/// triangle mesh simplification algorithms should override the pure
/// virual function _simplificationProcess() and put the implementation
/// in it. Use the parameter ``mesh'' which is a pointer to a mitkHETriangleMesh
/// object prepared and transfered by this class to do simplification,
/// because mitkHETriangleMesh (designed based on half edge structure) is
/// more suitable for mesh processing algorithms. The Execute() function
/// of this class will generate the right mitkHETriangleMesh object for you,
/// and call _simplificationProcess() with the object as parameter to perform
/// real simplification, so do not override Execute() in your subclasses. 
class MITK_COMMON_API mitkTriangleMeshSimplification : public mitkMeshToMeshFilter
{
public:
    MITK_TYPE(mitkTriangleMeshSimplification, mitkMeshToMeshFilter)

    virtual void PrintSelf(ostream &os);

    ///////////////////////////////////////////////////////////////////////
    /// Set the target face number of simplification.
    /// \param num the target face number
    ///////////////////////////////////////////////////////////////////////
    void SetTargetFaceNumber(size_type num) { m_TargetFaceNumber = num; }


protected:
    mitkTriangleMeshSimplification();
    virtual ~mitkTriangleMeshSimplification();

    virtual mitkMesh* _createOutMesh();

    virtual bool _simplificationProcess(mitkHETriangleMesh *mesh) = 0;

    virtual bool Execute();

    size_type m_TargetFaceNumber;

private:
    mitkTriangleMeshSimplification(const mitkTriangleMeshSimplification&);
    void operator = (const mitkTriangleMeshSimplification&);

};


//#define DEFINED_mitkTriangleMeshSimplification



#endif

