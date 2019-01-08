/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/



#ifndef __mitkMeshTransform_h
#define __mitkMeshTransform_h

#include "mitkMeshToMeshFilter.h"
#include "mitkMatrix.h"

class mitkICTriangleMesh;

class MITK_COMMON_API mitkMeshTransform : public mitkMeshToMeshFilter
{
public:
    MITK_TYPE(mitkMeshTransform, mitkMeshToMeshFilter)
    mitkMeshTransform();

    void SetMatrix(const mitkMatrix& matrix) { m_matrix=matrix; }

protected:
    virtual ~mitkMeshTransform();

    virtual mitkMesh* _createOutMesh();

    virtual bool Execute();

private:
    mitkMeshTransform(const mitkMeshTransform&);
    void operator = (const mitkMeshTransform&);

    mitkMatrix m_matrix;

};


#endif