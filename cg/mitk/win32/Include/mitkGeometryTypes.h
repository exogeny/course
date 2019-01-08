/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkGeometryTypes_h
#define __mitkGeometryTypes_h

#include "mitkGlobal.h"

template <typename T>
struct _3d_point_type
{
    union
    {
        struct { T x, y, z; };
        T coord[3];
    };
};

template <typename PointType, typename NormalType>
struct _3d_vertex_type
{
    _3d_point_type<PointType> point;
    _3d_point_type<NormalType> normal;
};

template <typename IndexType, unsigned int indexNum>
struct _face_type
{
    enum { vertNum = indexNum };
    IndexType verts[indexNum];
};

typedef _3d_point_type<float> Point3f;
typedef _3d_vertex_type<float, float> Vertex3f;
typedef _face_type<index_type, 3> TriangleFace;

const index_type INVALID_INDEX = -1;//MITK_UNSIGNED_INT_MAX;

#endif

