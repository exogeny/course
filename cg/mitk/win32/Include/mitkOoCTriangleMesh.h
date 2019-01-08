/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkOoCTriangleMesh_h
#define __mitkOoCTriangleMesh_h

#include "mitkTriangleMesh.h"

class VertexStorage;
class FaceStorage;

/// mitkOoCTriangleMesh - a concrete class for out-of-core triangle meshes
///////////////////////////////////////////////////////////////////////////
/// mitkOoCTriangleMesh is a concrete implementation of triangle mesh, for
/// representation of a very large (out-of-core) 3D object 
/// (can NOT be loaded to the main memory entirely).
/// \see mitkICTriangleMesh for in-core implementation of triangle mesh
class MITK_COMMON_API mitkOoCTriangleMesh : public mitkTriangleMesh
{
public:
    MITK_TYPE(mitkOoCTriangleMesh, mitkTriangleMesh)

    virtual void PrintSelf(ostream &os);

    ///////////////////////////////////////////////////////////////////////////
    /// Default constructor.
    ///////////////////////////////////////////////////////////////////////////
    mitkOoCTriangleMesh();

    ///////////////////////////////////////////////////////////////////////////
    /// Set the size of the vertex block (number of vertices of one block).
    /// \param vn the number of vertices of one block
    ///////////////////////////////////////////////////////////////////////////
    void SetVertexBlockSize(unsigned int vn);

    ///////////////////////////////////////////////////////////////////////////
    /// Set the size of the face block (number of triangles of one block).
    /// \param fn the number of triangles of one block
    ///////////////////////////////////////////////////////////////////////////
    void SetFaceBlockSize(unsigned int fn);

    ///////////////////////////////////////////////////////////////////////////
    /// Return what type of data object this is.
    /// \return Return the type of this data object.
    ///////////////////////////////////////////////////////////////////////////
    virtual int GetDataObjectType() const {return MITK_OOC_TRIANGLE_MESH;};

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
    virtual void SetVertexNumber(size_type number) {}

    ///////////////////////////////////////////////////////////////////////////
    /// Set the mesh's faces' number and allocate memory.
    /// \param number the number of faces
    ///////////////////////////////////////////////////////////////////////////
    virtual void SetFaceNumber(size_type number) {}

    ///////////////////////////////////////////////////////////////////////////
    /// You can not get a permanent pointer to the entire vertex data since
    /// it can not be loaded to the main memory all together, so do not call
    /// this function when using a mitkOoCTriangleMesh object, and it will always
    /// return NULL.
    /// \return Return NULL.
    /// \warning Do not call this function to get vertex data. Use mitkMesh::GetVertex()
    ///          or mitkMesh::GetVertices() instead.
    ///////////////////////////////////////////////////////////////////////////
    virtual float* GetVertexData() { return NULL; }

    ///////////////////////////////////////////////////////////////////////////
    /// You can not get a permanent pointer to the entire face data since
    /// it can not be loaded to the main memory all together, so do not call
    /// this function when using a mitkOoCTriangleMesh object, and it will always
    /// return NULL.
    /// \return Return NULL.
    /// \warning Do not call this function to get face data. Use mitkMesh::GetFace()
    ///          or mitkMesh::GetTriangleFaces() instead.
    ///////////////////////////////////////////////////////////////////////////
    virtual index_type* GetFaceData() { return NULL; }

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

    ///////////////////////////////////////////////////////////////////////////
    /// Set the size of the memory buffer for containing cached vertex blocks.
    /// \param s the size of the buffer in bytes
    /// \note When calling this function, the number of buffered vertex blocks is also
    ///       calculated by (buffer size) / (vertex block size), so it is unnecessary
    ///       to call SetBufferedVertexBlockNum() again.
    ///////////////////////////////////////////////////////////////////////////
    void SetVertexBufferSize(size_type s);

    ///////////////////////////////////////////////////////////////////////////
    /// Set the size of the memory buffer for containing cached face blocks.
    /// \param s the size of the buffer in bytes
    /// \note When calling this function, the number of buffered slice is also
    ///       calculated by (buffer size) / (face block size), so it is unnecessary
    ///       to call SetBufferedFaceBlockNum() again.
    ///////////////////////////////////////////////////////////////////////////
    void SetFaceBufferSize(size_type s);

    ///////////////////////////////////////////////////////////////////////////
    /// Set the number of buffered vertex blocks in memory.
    /// \param n the number of buffered vertex blocks
    /// \note When calling this function, the buffer size is also calculated
    ///       by (vertex block size) * (vertex block number), so it is unnecessary to call
    ///       SetVertexBufferSize() again.
    ///////////////////////////////////////////////////////////////////////////
    void SetBufferedVertexBlockNum(unsigned int n);

    ///////////////////////////////////////////////////////////////////////////
    /// Get the number of buffered vertex blocks in memory.
    /// \return Return the number of buffered vertex blocks.
    ///////////////////////////////////////////////////////////////////////////
    unsigned int GetBufferedVertexBlockNum();

    ///////////////////////////////////////////////////////////////////////////
    /// Set the number of buffered face blocks in memory.
    /// \param n the number of buffered face blocks
    /// \note When calling this function, the buffer size is also calculated
    ///       by (face block size) * (face block number), so it is unnecessary to call
    ///       SetFaceBufferSize() again.
    ///////////////////////////////////////////////////////////////////////////
    void SetBufferedFaceBlockNum(unsigned int n);

    ///////////////////////////////////////////////////////////////////////////
    /// Get the number of buffered face blocks in memory.
    /// \return Return the number of buffered face blocks.
    ///////////////////////////////////////////////////////////////////////////
    unsigned int GetBufferedFaceBlockNum();

    ///////////////////////////////////////////////////////////////////////////
    /// Set the full path of the disk buffer to contain all the data of the mesh.
    /// \param path the full path of the disk buffer
    ///////////////////////////////////////////////////////////////////////////
    void SetPathOfDiskBuffer(char const *path);

    ///////////////////////////////////////////////////////////////////////////
    /// Get the full path of the disk buffer which contains all the data of the
    /// mesh.
    /// \return Return the full path of the disk buffer.
    ///////////////////////////////////////////////////////////////////////////
    char const* GetPathOfDiskBuffer();

protected:
    virtual ~mitkOoCTriangleMesh();

    virtual index_type _addVertex(Vertex3f &vert);
    virtual index_type _addFace(unsigned int num, index_type *verts);
    virtual Vertex3f const* _getVertex(index_type vertIdx);
    virtual index_type const* _getFace(index_type faceIdx);
    virtual Vertex3f* _getVertexForWrite(index_type vertIdx);
    virtual index_type* _getFaceForWrite(index_type faceIdx);
    virtual size_type _getVertices(index_type startIdx, size_type num, Vertex3f *verts);
    virtual size_type _getTriangleFaces(index_type startIdx, size_type num, TriangleFace *faces);
    virtual size_type _getTriangleFaces(index_type startIdx, size_type num, Vertex3f *verts);

    //helper to test triangle orientation 
    Orientation _testOrientation(index_type faceIdx);

    void _flushVertexTempBuffer();
    void _flushFaceTempBuffer();
    void _flushTempBuffer();


    VertexStorage *m_VertStor;
    FaceStorage *m_FaceStor;

    index_type m_CurVertBlkIdx;
    index_type m_CurFaceBlkIdx;
    Vertex3f *m_CurVertBlk;
    TriangleFace *m_CurFaceBlk;

    size_type m_VertBlkSize;
    size_type m_FaceBlkSize;

    index_type m_VertIdxMask;
    unsigned int m_VertIdxLen;
    index_type m_VertBlkMask;
    index_type m_FaceIdxMask;
    unsigned int m_FaceIdxLen;
    index_type m_FaceBlkMask;

private:
    mitkOoCTriangleMesh(const mitkOoCTriangleMesh&);
    void operator = (const mitkOoCTriangleMesh&);

};


//#define DEFINED_mitkOoCTriangleMesh



#endif

