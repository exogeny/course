/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkICTriangleMesh_h
#define __mitkICTriangleMesh_h

#include "mitkTriangleMesh.h"

/// mitkICTriangleMesh - a concrete class for in-core triangle meshes
///////////////////////////////////////////////////////////////////////////
/// mitkICTriangleMesh is a concrete implementation of triangle mesh, for
/// representation of a in-core 3D object (can be loaded to the main memory
/// entirely). It is made up of triangle faces.
/// \see mitkOoCTriangleMesh for out-of-core implementation of triangle mesh
class MITK_COMMON_API mitkICTriangleMesh : public mitkTriangleMesh
{
public:
    MITK_TYPE(mitkICTriangleMesh, mitkTriangleMesh)

    virtual void PrintSelf(ostream& os);

    ///////////////////////////////////////////////////////////////////////////
    /// Default constructor of this class.
    ///////////////////////////////////////////////////////////////////////////
    mitkICTriangleMesh();

    ///////////////////////////////////////////////////////////////////////////
    /// Return what type of data object this is.
    /// \return Return the type of this data object.
    ///////////////////////////////////////////////////////////////////////////
    virtual int GetDataObjectType() const { return MITK_IC_TRIANGLE_MESH; }

    ///////////////////////////////////////////////////////////////////////////
    /// Make the output data ready for new data to be inserted.
    ///////////////////////////////////////////////////////////////////////////
    virtual void Initialize();

    ///////////////////////////////////////////////////////////////////////////
    /// Get the actual size of the data in bytes.
    /// \return Return the actual size of the data in bytes.
    ///////////////////////////////////////////////////////////////////////////
    virtual unsigned long long GetActualMemorySize() const;

    ///////////////////////////////////////////////////////////////////////////
    /// Shallowcopy.
    /// \param src pointer to the source mitkDataObject
    ///////////////////////////////////////////////////////////////////////////
    virtual void ShallowCopy(mitkDataObject *src);

    ///////////////////////////////////////////////////////////////////////////
    /// Deep copy.
    /// \param src pointer to the source mitkDataObject
    ///////////////////////////////////////////////////////////////////////////
    virtual void DeepCopy(mitkDataObject *src);

    ///////////////////////////////////////////////////////////////////////////
    /// Set the mesh's vertices' number and allocate memory.
    /// \param number the number of vertices
    ///////////////////////////////////////////////////////////////////////////
    virtual void SetVertexNumber(size_type number);

    ///////////////////////////////////////////////////////////////////////////
    /// Set the mesh's faces' number and allocate memory.
    /// \param number the number of faces
    ///////////////////////////////////////////////////////////////////////////
    virtual void SetFaceNumber(size_type number);

    ///////////////////////////////////////////////////////////////////////////
    /// Get data pointer of this vertex data. 
    /// \return Return a float pointer to the vertex data.
    ///////////////////////////////////////////////////////////////////////////
    virtual float* GetVertexData() { return ((float *)m_VertexData); }

    ///////////////////////////////////////////////////////////////////////////
    /// Get data pointer of this face data.
    /// \return Return a unsigned int pointer to the face data (indices to vertices).
    ///////////////////////////////////////////////////////////////////////////
    virtual index_type* GetFaceData() { return ((index_type *)m_FaceData); }

    ///////////////////////////////////////////////////////////////////////////
    /// Reverse normals.
    ///////////////////////////////////////////////////////////////////////////
    virtual void ReverseNormals();

    ///////////////////////////////////////////////////////////////////////////
    /// Test the orientation of front-facing triangles.
    /// \return Return true if the orientation of front-facing triangles is clockwise,
    ///         otherwise return false.
    ///////////////////////////////////////////////////////////////////////////
    virtual bool TestClockwise();


protected:
    virtual ~mitkICTriangleMesh();

    virtual index_type _addVertex(Vertex3f &vert);
    virtual index_type _addFace(unsigned int num, index_type *verts);
    virtual Vertex3f const* _getVertex(index_type vertIdx);
    virtual index_type const* _getFace(index_type faceIdx);
    virtual Vertex3f* _getVertexForWrite(index_type vertIdx);
    virtual index_type* _getFaceForWrite(index_type faceIdx);

    //helper to test triangle orientation 
    Orientation _testOrientation(index_type faceIdx) const;

    Vertex3f *m_VertexData;
    TriangleFace *m_FaceData;

private:
    mitkICTriangleMesh(const mitkICTriangleMesh&);
    void operator=(const mitkICTriangleMesh&);

};

#endif

