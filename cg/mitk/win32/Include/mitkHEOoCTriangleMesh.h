/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkHEOoCTriangleMesh_h
#define __mitkHEOoCTriangleMesh_h

#include "mitkHETriangleMesh.h"

class HEVertexStorage;
class HEEdgeStorage;
class HEFaceStorage;

/// mitkHEOoCTriangleMesh - a concrete class for out-of-core triangle meshes represented by Half Edges
///////////////////////////////////////////////////////////////////////////
/// mitkHEOoCTriangleMesh is a concrete class for out-of-core triangle
/// meshes represented by Half Edges. It can hold an out-of-core data
/// set and provide the same access interfaces as mitkHETriangleMesh.
/// \see mitkHEMesh and mitkHETriangleMesh for access interfaces
/// \see mitkHEICTriangleMesh for in-core data set
class MITK_COMMON_API mitkHEOoCTriangleMesh : public mitkHETriangleMesh
{
public:
    MITK_TYPE(mitkHEOoCTriangleMesh, mitkHETriangleMesh)

    virtual void PrintSelf(ostream &os);

    ///////////////////////////////////////////////////////////////////////////
    /// Default constructor.
    ///////////////////////////////////////////////////////////////////////////
    mitkHEOoCTriangleMesh();

    ///////////////////////////////////////////////////////////////////////////
    /// Set the size of the vertex block (number of vertices of one block).
    /// \param vn the number of vertices of one block
    ///////////////////////////////////////////////////////////////////////////
    void SetVertexBlockSize(unsigned int vn);

    ///////////////////////////////////////////////////////////////////////////
    /// Set the size of the edge block (number of edges of one block).
    /// \param en the number of edges of one block
    ///////////////////////////////////////////////////////////////////////////
    void SetEdgeBlockSize(unsigned int en);

    ///////////////////////////////////////////////////////////////////////////
    /// Set the size of the face block (number of triangles of one block).
    /// \param fn the number of triangles of one block
    ///////////////////////////////////////////////////////////////////////////
    void SetFaceBlockSize(unsigned int fn);

    ///////////////////////////////////////////////////////////////////////////
    /// Set the size of the memory buffer for containing cached vertex blocks.
    /// \param s the size of the buffer in bytes
    /// \note When calling this function, the number of buffered vertex blocks is also
    ///       calculated by (buffer size) / (vertex block size), so it is unnecessary
    ///       to call SetBufferedVertexBlockNum() again.
    ///////////////////////////////////////////////////////////////////////////
    void SetVertexBufferSize(size_type s);

    ///////////////////////////////////////////////////////////////////////////
    /// Set the size of the memory buffer for containing cached edge blocks.
    /// \param s the size of the buffer in bytes
    /// \note When calling this function, the number of buffered edge blocks is also
    ///       calculated by (buffer size) / (edge block size), so it is unnecessary
    ///       to call SetBufferedEdgeBlockNum() again.
    ///////////////////////////////////////////////////////////////////////////
    void SetEdgeBufferSize(size_type s);

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
    /// Set the number of buffered edge blocks in memory.
    /// \param n the number of buffered edge blocks
    /// \note When calling this function, the buffer size is also calculated
    ///       by (edge block size) * (vertex block number), so it is unnecessary to call
    ///       SetEdgeBufferSize() again.
    ///////////////////////////////////////////////////////////////////////////
    void SetBufferedEdgeBlockNum(unsigned int n);

    ///////////////////////////////////////////////////////////////////////////
    /// Get the number of buffered edge blocks in memory.
    /// \return Return the number of buffered vertex blocks.
    ///////////////////////////////////////////////////////////////////////////
    unsigned int GetBufferedEdgeBlockNum();

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

    ///////////////////////////////////////////////////////////////////////////
    /// Return what type of data object this is.
    /// \return Return the type of this data object.
    ///////////////////////////////////////////////////////////////////////////
    virtual int GetDataObjectType() const { return MITK_HE_OOC_TRIANGLE_MESH; }

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
    /// Set the vertices' number and allocate memory.
    /// \param number the number of vertices
    /// \note This function is obsolete. It is provided to keep old codes 
    ///          working. We strongly advise against using it in new codes. 
    ///////////////////////////////////////////////////////////////////////////
    virtual void SetVertexNumber(size_type number);

    ///////////////////////////////////////////////////////////////////////////
    /// Set the faces' number and allocate memory.
    /// \param number the number of faces
    /// \warning This function is obsolete. It is provided to keep old codes 
    ///          working. We strongly advise against using it in new codes. 
    ///////////////////////////////////////////////////////////////////////////
    virtual void SetFaceNumber(size_type number);

    ///////////////////////////////////////////////////////////////////////////
    /// Get vertex by handle.
    /// \param v the handle of the required vertex
    /// \return Return the reference to the required vertex.
    ///////////////////////////////////////////////////////////////////////////
    virtual Vertex& GetVertex(VertexHandle v) const;

    ///////////////////////////////////////////////////////////////////////////
    /// Get edge by handle.
    /// \param e the handle of the required edge
    /// \return Return the reference to the  required edge.
    ///////////////////////////////////////////////////////////////////////////
    virtual Edge& GetEdge(EdgeHandle e) const;

    ///////////////////////////////////////////////////////////////////////////
    /// Get edge by half edge handle.
    /// \param he one half edge handle of the required edge
    /// \return Return the reference to the required edge.
    /// \note An edge is composed by two opposite half edges.
    ///////////////////////////////////////////////////////////////////////////
    virtual Edge& GetEdge(HalfEdgeHandle he) const;

    ///////////////////////////////////////////////////////////////////////////
    /// Get half edge by handle.
    /// \param he the handle of the required half edge
    /// \return Return the reference to the required half edge.
    ///////////////////////////////////////////////////////////////////////////
    virtual HalfEdge& GetHalfEdge(HalfEdgeHandle he) const;

    ///////////////////////////////////////////////////////////////////////////
    /// Get face by handle.
    /// \param f the handle of the required face
    /// \return Return the reference to the required face.
    ///////////////////////////////////////////////////////////////////////////
    virtual Face& GetFace(FaceHandle f) const;

    ///////////////////////////////////////////////////////////////////////////
    /// Get vertex by handle for read only.
    /// \param v the handle of the required vertex
    /// \return Return the reference to the required vertex.
    ///////////////////////////////////////////////////////////////////////////
    virtual Vertex const& GetVertexForRead(VertexHandle v) const;

    ///////////////////////////////////////////////////////////////////////////
    /// Get edge by handle for read only.
    /// \param e the handle of the required edge
    /// \return Return the reference to the  required edge.
    ///////////////////////////////////////////////////////////////////////////
    virtual Edge const& GetEdgeForRead(EdgeHandle e) const;

    ///////////////////////////////////////////////////////////////////////////
    /// Get edge by half edge handle for read only.
    /// \param he one half edge handle of the required edge
    /// \return Return the reference to the required edge.
    /// \note An edge is composed by two opposite half edges.
    ///////////////////////////////////////////////////////////////////////////
    virtual Edge const& GetEdgeForRead(HalfEdgeHandle he) const;

    ///////////////////////////////////////////////////////////////////////////
    /// Get half edge by handle for read only.
    /// \param he the handle of the required half edge
    /// \return Return the reference to the required half edge.
    ///////////////////////////////////////////////////////////////////////////
    virtual HalfEdge const& GetHalfEdgeForRead(HalfEdgeHandle he) const;

    ///////////////////////////////////////////////////////////////////////////
    /// Get face by handle for read only.
    /// \param f the handle of the required face
    /// \return Return the reference to the required face.
    ///////////////////////////////////////////////////////////////////////////
    virtual Face const& GetFaceForRead(FaceHandle f) const;

    ///////////////////////////////////////////////////////////////////////////
    /// Get the handle of a vertex.
    /// \param vert the reference to the vertex
    /// \return Return the handle of the vertex.
    ///////////////////////////////////////////////////////////////////////////
    virtual VertexHandle GetHandle(Vertex const &vert) const;

    ///////////////////////////////////////////////////////////////////////////
    /// Get the handle of an edge.
    /// \param edge the reference to the edge
    /// \return Return the handle of the edge.
    ///////////////////////////////////////////////////////////////////////////
    virtual EdgeHandle GetHandle(Edge const &edge) const;

    ///////////////////////////////////////////////////////////////////////////
    /// Get the handle of a half edge.
    /// \param he the reference to the half edge
    /// \return Return the handle of the half edge.
    ///////////////////////////////////////////////////////////////////////////
    virtual HalfEdgeHandle GetHandle(HalfEdge const &he) const
    { return this->PairHalfEdge(he.pairHalfEdge); }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the handle of a face.
    /// \param face the reference to the face
    /// \return Return the handle of the face.
    ///////////////////////////////////////////////////////////////////////////
    virtual FaceHandle GetHandle(Face const &face) const;

    ///////////////////////////////////////////////////////////////////////
    /// Get data pointer of this vertex data. This is for compatibility with
    /// mitkTriangleMesh which is used more frequently. For out-of-core data
    /// sets, it will always return NULL, because the impossibility of fitting
    /// an out-of-core data set into the main memory.
    /// \return Always return NULL.
    /// \warning This function is obsolete and does nothing in this class.
    ///          We strongly advise against using it in new codes. 
    ///////////////////////////////////////////////////////////////////////
    virtual float* GetVertexData() { return NULL; }

    ///////////////////////////////////////////////////////////////////////
    /// Get data pointer of this face data. This is for compatibility with
    /// mitkTriangleMesh which is used more frequently. For out-of-core data
    /// sets, it will always return NULL, because the impossibility of fitting
    /// an out-of-core data set into the main memory.
    /// \return Always return NULL.
    /// \warning This function is obsolete and does nothing in this class.
    ///          We strongly advise against using it in new codes; 
    ///////////////////////////////////////////////////////////////////////
    virtual index_type* GetFaceData() { return NULL; }

protected:
    virtual ~mitkHEOoCTriangleMesh();

    virtual size_type _getVertices(index_type startIdx, size_type num, Vertex3f *verts);
    virtual size_type _getTriangleFaces(index_type startIdx, size_type num, TriangleFace *faces);
    virtual size_type _getTriangleFaces(index_type startIdx, size_type num, Vertex3f *verts);

    // Actual method for adding Vertex/Edge/Face.
    // Memory allocation will be done here.
    virtual VertexHandle   _addNewVertex(float x,         float y,         float z, 
                                         float nx = 0.0f, float ny = 0.0f, float nz = 0.0f,
                                         HalfEdgeHandle edge = HalfEdgeHandle());
    virtual HalfEdgeHandle _addNewEdge(VertexHandle start, VertexHandle end);
    virtual FaceHandle     _addNewFace(HalfEdgeHandle halfedge = HalfEdgeHandle());

    // Helper for clearing garbage.
    virtual void _clearDeletedVertices();
    virtual void _clearDeletedEdges();
    virtual void _clearDeletedFaces();

    size_type _getVertexBlock(index_type blkIdx, Vertex3f *verts);
    size_type _getTriangleFaceBlock(index_type blkIdx, TriangleFace *faces);
    size_type _getTriangleFaceBlock(index_type blkIdx, Vertex3f *verts);
    
    HEVertexStorage *m_VertStor;
    HEEdgeStorage *m_EdgeStor;
    HEFaceStorage *m_FaceStor;

    size_type m_VertBlkSize;
    size_type m_EdgeBlkSize;
    size_type m_FaceBlkSize;

    index_type m_VertIdxMask;
    unsigned int m_VertIdxLen;
    index_type m_VertBlkMask;
    index_type m_EdgeIdxMask;
    unsigned int m_EdgeIdxLen;
    index_type m_EdgeBlkMask;
    index_type m_FaceIdxMask;
    unsigned int m_FaceIdxLen;
    index_type m_FaceBlkMask;


private:
    mitkHEOoCTriangleMesh(const mitkHEOoCTriangleMesh&);
    void operator = (const mitkHEOoCTriangleMesh&);

};

#endif

