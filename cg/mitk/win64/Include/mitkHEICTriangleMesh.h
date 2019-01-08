/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkHEICTriangleMesh_h
#define __mitkHEICTriangleMesh_h

#include "mitkHETriangleMesh.h"

/// mitkHEICTriangleMesh - a concrete class for in-core triangle meshes represented by Half Edges
///////////////////////////////////////////////////////////////////////////
/// mitkHEICTriangleMesh is a concrete class for in-core triangle meshes 
/// represented by Half Edges. It supports in-core data sets which can be
/// loaded into the main memory entirely.
/// \see mitkHEMesh and mitkHETriangleMesh for access interfaces
/// \see mitkHEOoCTriangleMesh for out-of-core data set
class MITK_COMMON_API mitkHEICTriangleMesh : public mitkHETriangleMesh
{
public:
    MITK_TYPE(mitkHEICTriangleMesh, mitkHETriangleMesh)

    virtual void PrintSelf(ostream &os);

    ///////////////////////////////////////////////////////////////////////////
    /// Default constructor.
    ///////////////////////////////////////////////////////////////////////////
    mitkHEICTriangleMesh();

    ///////////////////////////////////////////////////////////////////////////
    /// Return what type of data object this is.
    /// \return Return the type of this data object.
    ///////////////////////////////////////////////////////////////////////////
    virtual int GetDataObjectType() const { return MITK_HE_IC_TRIANGLE_MESH; }

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
    virtual Vertex& GetVertex(VertexHandle v) const
    { assert(this->IsValid(v)); return m_Vertices[v.Idx()]; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get edge by handle.
    /// \param e the handle of the required edge
    /// \return Return the reference to the  required edge.
    ///////////////////////////////////////////////////////////////////////////
    virtual Edge& GetEdge(EdgeHandle e) const
    { assert(this->IsValid(e)); return m_Edges[e.Idx()]; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get edge by half edge handle.
    /// \param he one half edge handle of the required edge
    /// \return Return the reference to the required edge.
    /// \note An edge is composed by two opposite half edges.
    ///////////////////////////////////////////////////////////////////////////
    virtual Edge& GetEdge(HalfEdgeHandle he) const
    { assert(this->IsValid(he)); return m_Edges[(he.Idx()>>1)]; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get half edge by handle.
    /// \param he the handle of the required half edge
    /// \return Return the reference to the required half edge.
    ///////////////////////////////////////////////////////////////////////////
    virtual HalfEdge& GetHalfEdge(HalfEdgeHandle he) const
    { assert(this->IsValid(he)); return m_Edges[he.Idx()>>1].halfEdge[he.Idx()%2]; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get face by handle.
    /// \param f the handle of the required face
    /// \return Return the reference to the required face.
    ///////////////////////////////////////////////////////////////////////////
    virtual Face& GetFace(FaceHandle f) const
    { assert(this->IsValid(f)); return m_Faces[f.Idx()]; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the handle of a vertex.
    /// \param vert the reference to the vertex
    /// \return Return the handle of the vertex.
    ///////////////////////////////////////////////////////////////////////////
    virtual VertexHandle GetHandle(Vertex const &vert) const
    { return VertexHandle(&vert-m_Vertices); }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the handle of an edge.
    /// \param edge the reference to the edge
    /// \return Return the handle of the edge.
    ///////////////////////////////////////////////////////////////////////////
    virtual EdgeHandle GetHandle(Edge const &edge) const
    { return EdgeHandle(&edge-m_Edges); }

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
    virtual FaceHandle GetHandle(Face const &face) const
    { return FaceHandle(&face-m_Faces); }

    ///////////////////////////////////////////////////////////////////////
    /// Get data pointer of this vertex data. This is for compatibility with
    /// mitkTriangleMesh which is used more frequently.
    /// \return Return a float pointer to the vertex data.
    /// \warning This function is obsolete. It is provided to keep old codes 
    ///          working. We strongly advise against using it in new codes. 
    ///////////////////////////////////////////////////////////////////////
    virtual float* GetVertexData();

    ///////////////////////////////////////////////////////////////////////
    /// Get data pointer of this face data. This is for compatibility with
    /// mitkTriangleMesh which is used more frequently.
    /// \return Return a unsigned int pointer to the face data (indices to vertices).
    /// \warning \li This function is obsolete. It is provided to keep old codes 
    ///              working. We strongly advise against using it in new codes; 
    ///          \li DO NOT delete the pointer you got from this function.
    ///              If you must release the memory, call ClearTempVertArray()
    ///              to do this.
    ///////////////////////////////////////////////////////////////////////
    virtual index_type* GetFaceData();

    ///////////////////////////////////////////////////////////////////////
    /// Clear the temporary memory allocated in the function GetVertexData().
    /// \warning Do not call this function until you no longer use the
    ///          vertex data gotten from GetVertexData();
    ///////////////////////////////////////////////////////////////////////
    void ClearTempVertArray();

    ///////////////////////////////////////////////////////////////////////
    /// Clear the temporary memory allocated in the function GetFaceData().
    /// \warning Do not call this function until you no longer use the
    ///          face data gotten from GetFaceData();
    ///////////////////////////////////////////////////////////////////////
    void ClearTempFaceArray();

protected:
    virtual ~mitkHEICTriangleMesh();
    
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

    
    size_type m_Increment;

    Vertex *m_Vertices;
    Edge *m_Edges;
    Face *m_Faces;

    // for compatible with mitkTriangleMesh which is used frequently
    Vertex3f *m_VertArray;
    TriangleFace *m_FaceArray;

private:
    mitkHEICTriangleMesh(const mitkHEICTriangleMesh&);
    void operator = (const mitkHEICTriangleMesh&);

};


#endif

