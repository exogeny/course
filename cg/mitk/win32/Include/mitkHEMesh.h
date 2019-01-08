/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkHEMesh_h
#define __mitkHEMesh_h

#include "mitkMesh.h"
#include "mitkHalfEdgeStructures.h"

/// mitkHEMesh - a concrete class for polygon meshes represented by Half Edges
///////////////////////////////////////////////////////////////////////////
/// mitkHEMesh is a concrete class for polygon meshes which are represented
/// by Half Edge Type. This implementation of half edge references to 
/// OpenMesh written by Computer Graphics Group, RWTH Aachen. 
/// \par Some Structs Used in this Class
/// 
/// \par HEVertex
/// Besides the point coordinates and normal of the vertex, Vertex struct
/// also contains the handle of outgoing half edge. It is defined as follows:
/// \code
/// struct HEVertex : public _flag_base
/// {
///     union
///     {
///         Vertex3f vert;
///         struct 
///         {
///             Point3f point;
///             Point3f normal;
///         };
///     };
///     HEHalfEdgeHandle outHalfEdge; // handle of outgoing half edge   
/// };
/// \endcode
/// 
/// \par HEHalfEdge
/// It contains the handles of its end vertex, opposite half edge, next half edge,
/// previous half edge and adjacent face. It is defined as follows:
/// \code
/// struct HEHalfEdge
/// {
///     HEVertexHandle endVertex;      // handle of end vertex
///     HEHalfEdgeHandle pairHalfEdge; // handle of opposite half edge
///     HEHalfEdgeHandle nextHalfEdge; // handle of next half edge
///     HEHalfEdgeHandle prevHalfEdge; // handle of previous half edge
///     HEFaceHandle face;
/// };
/// \endcode
/// 
/// \par HEEdge
/// It contains two opposite half edges, defined as follows:
/// \code
/// struct HEEdge : public _flag_base
/// {
///     HEHalfEdge halfEdge[2];
/// };
/// \endcode
/// 
/// \par HEFace
/// It contains the handle of one of its half edges, defined as follows:
/// \code
/// struct _face : public _flag_base
/// {
///     HEHalfEdgeHandle oneHalfEdge; // handle of one half edge
/// };
/// \endcode
/// 
/// \par
/// Furthermore, HEVertex, HEEdge and HEFace are all derived from _flag_base,
/// which provides a set of methods to make some special marks on these items
/// when processing a mitkHEMesh in your algorithm. You can make and unmake 
/// 31 different marks from ``flag0'' to ``flag30'' through the methods
/// _flag_base::SetFlag(FLAGS f) and _flag_base::UnSetFlag(FLAGS f), and test
/// these flags through the method _flag_base::GetFlag(FLAGS f). 
/// _flag_base::SetDeleted(bool del=true) is reserved by MITK, which means
/// some procedures inside MITK will make ``delete'' marks after deleting some
/// items. You can test if an item is deleted by MITK through the method
/// _flag_base::IsDeleted().
/// 
/// \par Handles
/// Handles including HEVertexHandle, HEHalfEdgeHandle, HEEdgeHandle
/// and HEFaceHandle are encapsulations of index. Methods in mitkHEMesh
/// use handles to deal with items instead of using indices directly.
/// You can get index from a handle through the method *Handle::Idx(), and test
/// a handle's validation through the method *Handle::IsValid().
/// 
/// The detailed definition can be found in mitkHalfEdgeStructures.h
/// and mitkGeometryTypes.h.
class MITK_COMMON_API mitkHEMesh : public mitkMesh
{
public:
    typedef HEVertex   Vertex;
    typedef HEHalfEdge HalfEdge;
    typedef HEEdge     Edge;
    typedef HEFace     Face;

    typedef HEVertexPtr   VertexPtr;
    typedef HEHalfEdgePtr HalfEdgePtr;
    typedef HEEdgePtr     EdgePtr;
    typedef HEFacePtr     FacePtr;

    typedef HEVertexHandle   VertexHandle;
    typedef HEHalfEdgeHandle HalfEdgeHandle;
    typedef HEEdgeHandle     EdgeHandle;
    typedef HEFaceHandle     FaceHandle;

    MITK_TYPE(mitkHEMesh, mitkMesh)

    virtual void PrintSelf(ostream &os);

    ///////////////////////////////////////////////////////////////////////////
    /// Default constructor.
    ///////////////////////////////////////////////////////////////////////////
    mitkHEMesh();

    ///////////////////////////////////////////////////////////////////////////
    /// Return what type of data object this is.
    /// \return Return the type of this data object.
    ///////////////////////////////////////////////////////////////////////////
    virtual int GetDataObjectType() const { return MITK_HE_MESH; }

    ///////////////////////////////////////////////////////////////////////////
    /// Make the output data ready for new data to be inserted.
    ///////////////////////////////////////////////////////////////////////////
    virtual void Initialize();

    ///////////////////////////////////////////////////////////////////////////
    /// Get the actual size of the data in bytes.
    /// \return Return the actual size of the data in bytes.
    ///////////////////////////////////////////////////////////////////////////
    //virtual unsigned long long GetActualMemorySize() const;

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
    //virtual void SetVertexNumber(size_type number);

    ///////////////////////////////////////////////////////////////////////////
    /// Get vertex number.
    /// \return Return the number of vertices.
    ///////////////////////////////////////////////////////////////////////////
    virtual size_type GetVertexNumber() const { return m_VertNum;   }

    ///////////////////////////////////////////////////////////////////////////
    /// Set the faces' number and allocate memory.
    /// \param number the number of faces
    /// \warning This function is obsolete. It is provided to keep old codes 
    ///          working. We strongly advise against using it in new codes. 
    ///////////////////////////////////////////////////////////////////////////
    //virtual void SetFaceNumber(size_type number);

    ///////////////////////////////////////////////////////////////////////////
    /// Get face number.
    /// \return Return the number of faces.
    ///////////////////////////////////////////////////////////////////////////
    virtual size_type GetFaceNumber() const { return m_FaceNum; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get edge number.
    /// \return Return the number of edges.
    size_type GetEdgeNumber() const { return m_EdgeNum; }

    ///////////////////////////////////////////////////////////////////////////
    /// Clear the garbage generated by deletion.
    /// \note Call this function before any kinds of iteration.
    ///////////////////////////////////////////////////////////////////////////
    void ClearGarbage();

    ///////////////////////////////////////////////////////////////////////////
    /// Add vertex.
    /// \param vert the vertex to add
    /// \return Return the handle of the vertex added.
    ///////////////////////////////////////////////////////////////////////////
    VertexHandle AddVertex(Vertex const &vert)
    {
        return _addNewVertex(vert.point.x,  vert.point.y,  vert.point.z, 
                             vert.normal.x, vert.normal.y, vert.normal.z,
                             vert.outHalfEdge);
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Add vertex.
    /// \param point the coordinates of the vertex to add
    /// \param normal the normal of the vertex to add
    /// \return Return the handle of the vertex added.
    ///////////////////////////////////////////////////////////////////////////
    VertexHandle AddVertex(Point3f const &point, Point3f const &normal)
    {
        return _addNewVertex(point.x, point.y, point.z, normal.x, normal.y, normal.z);
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Add vertex.
    /// \param x the x-coordinate of the vertex to add
    /// \param y the y-coordinate of the vertex to add
    /// \param z the z-coordinate of the vertex to add
    /// \param nx the x-coordinate of the vertex's normal, the default value is 0.0f
    /// \param ny the y-coordinate of the vertex's normal, the default value is 0.0f
    /// \param nz the z-coordinate of the vertex's normal, the default value is 0.0f
    /// \return Return the handle of the vertex added.
    ///////////////////////////////////////////////////////////////////////////
    VertexHandle AddVertex(float x, float y, float z, 
                               float nx = 0.0f, float ny = 0.0f, float nz = 0.0f)
    {
        return _addNewVertex(x, y, z, nx, ny, nz);
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Add vertex.
    /// \param v[0] the x-coordinate of the vertex to add
    /// \param v[1] the y-coordinate of the vertex to add
    /// \param v[2] the z-coordinate of the vertex to add
    /// \param v[3] the x-coordinate of the vertex's normal
    /// \param v[4] the y-coordinate of the vertex's normal
    /// \param v[5] the z-coordinate of the vertex's normal
    /// \return Return the handle of the vertex added.
    ///////////////////////////////////////////////////////////////////////////
    VertexHandle AddVertex(float v[6])
    {
        return _addNewVertex(v[0], v[1], v[2], v[3], v[4], v[5]);
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Add Face.
    /// \param n the number of vertices of the face to add
    /// \param vertices array of the VertexHandle which compose the face
    /// \return Return the handle of the face added.
    /// \warning Each VertexHandle in the array must be valid, i.e. represents
    ///          a existent vertex in the mesh (has been ``Add*''ed before).
    ///////////////////////////////////////////////////////////////////////////
    FaceHandle AddFace(unsigned int n, VertexHandle *vertices);

    ///////////////////////////////////////////////////////////////////////////
    /// Delete vertex.
    /// \param vert the handle of the vertex to be deleted
    ///////////////////////////////////////////////////////////////////////////
    void DeleteVertex(VertexHandle vert);

    ///////////////////////////////////////////////////////////////////////////
    /// Delete edge.
    /// \param edge the handle of the edge to be deleted
    /// \param deleteIsolatedVertices whether to delete the isolated vertices
    ///        after deleting the edge
    ///////////////////////////////////////////////////////////////////////////
    void DeleteEdge(EdgeHandle edge, bool deleteIsolatedVertices);

    ///////////////////////////////////////////////////////////////////////////
    /// Delete face.
    /// \param face the handle of the face to be deleted
    /// \param deleteIsolatedVertices whether to delete the isolated vertices
    ///        after deleting the face
    ///////////////////////////////////////////////////////////////////////////
    void DeleteFace(FaceHandle face, bool deleteIsolatedVertices);

    ///////////////////////////////////////////////////////////////////////////
    /// Find halfedge from vert0 to vert1.
    /// \param vert0 the handle of the start vertex
    /// \param vert1 the handle of the end vertex
    /// \return Return the handle of the half edge between vert0 and vert1.
    ///         If no half edge is found, the returned handle will be invalid.
    ///         Use HalfEdgeHandle::IsValid() to test it.
    ///////////////////////////////////////////////////////////////////////////
    HalfEdgeHandle FindHalfEdge(VertexHandle vert0, VertexHandle vert1);

    ///////////////////////////////////////////////////////////////////////////
    /// Boundary test for half edge.
    /// \param halfedge the handle of the half edge to be tested
    /// \return Return true if halfedge is a boundary half edge, otherwise return
    ///         false.
    ///////////////////////////////////////////////////////////////////////////
    bool IsBoundary(HalfEdgeHandle halfedge) const { return !(this->IsValid(this->AdjFace(halfedge))); }

    ///////////////////////////////////////////////////////////////////////////
    /// Boundary test for vertex.
    /// \param vert the handle of the vertex to be tested
    /// \return Return true if vert is a boundary vertex, otherwise return
    ///         false.
    ///////////////////////////////////////////////////////////////////////////
    bool IsBoundary(VertexHandle vert) const 
    {
        HalfEdgeHandle edge = this->OutHalfEdge(vert); 
        return ( ! (this->IsValid(edge) && this->IsValid(this->AdjFace(edge))) ); 
    }
    
    ///////////////////////////////////////////////////////////////////////////
    /// Boundary test for edge.
    /// \param edge the handle of the edge to be tested
    /// \return Return true if edge is a boundary edge, otherwise return
    ///         false.
    ///////////////////////////////////////////////////////////////////////////
    bool IsBoundary(EdgeHandle edge) const
    {
        assert(this->IsValid(edge));
        return ( this->IsBoundary(this->GetHandle(this->GetEdge(edge).halfEdge[0])) ||
                 this->IsBoundary(this->GetHandle(this->GetEdge(edge).halfEdge[1])) ); 
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Manifold test for vertex. The vertex is non-manifold if more than one
    /// gap exists, i.e. more than one outgoing boundary halfedge. If one boundary
    /// halfedge exists, the vertex' halfedge must be a boundary halfedge. If 
    /// iterating around the vertex finds another boundary halfedge, the vertex
    /// is non-manifold.
    /// \param vert the handle of the vertex to be tested
    /// \return Return true if the vertex is manifold, otherwise return false.
    ///////////////////////////////////////////////////////////////////////////
    bool IsManifold(VertexHandle vert)
    {
        VertexOHalfedgeIterator ei(this, vert);
        ++ei;
        for ( ; ei; ++ei) if (this->IsBoundary(ei)) return false;
        return true;
    }

    ///////////////////////////////////////////////////////////////////////////
    /// Get vertex by handle.
    /// \param v the handle of the required vertex
    /// \return Return the reference to the required vertex.
    ///////////////////////////////////////////////////////////////////////////
    virtual Vertex& GetVertex(VertexHandle v) const = 0;
    //{ assert(this->IsValid(v)); return m_Vertices[v.Idx()]; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get edge by handle.
    /// \param e the handle of the required edge
    /// \return Return the reference to the  required edge.
    ///////////////////////////////////////////////////////////////////////////
    virtual Edge& GetEdge(EdgeHandle e) const = 0;
    //{ assert(this->IsValid(e)); return m_Edges[e.Idx()]; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get edge by half edge handle.
    /// \param he one half edge handle of the required edge
    /// \return Return the reference to the required edge.
    /// \note An edge is composed by two opposite half edges.
    ///////////////////////////////////////////////////////////////////////////
    virtual Edge& GetEdge(HalfEdgeHandle he) const = 0;
    //{ assert(this->IsValid(he)); return m_Edges[(he.Idx()>>1)]; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get half edge by handle.
    /// \param he the handle of the required half edge
    /// \return Return the reference to the required half edge.
    ///////////////////////////////////////////////////////////////////////////
    virtual HalfEdge& GetHalfEdge(HalfEdgeHandle he) const = 0;
    //{ assert(this->IsValid(he)); return m_Edges[he.Idx()>>1].halfEdge[he.Idx()%2]; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get face by handle.
    /// \param f the handle of the required face
    /// \return Return the reference to the required face.
    ///////////////////////////////////////////////////////////////////////////
    virtual Face& GetFace(FaceHandle f) const = 0;
    //{ assert(this->IsValid(f)); return m_Faces[f.Idx()]; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the handle of a vertex.
    /// \param vert the reference to the vertex
    /// \return Return the handle of the vertex.
    ///////////////////////////////////////////////////////////////////////////
    virtual VertexHandle GetHandle(Vertex const &vert) const = 0;
    //{ return VertexHandle(&vert-m_Vertices); }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the handle of an edge.
    /// \param edge the reference to the edge
    /// \return Return the handle of the edge.
    ///////////////////////////////////////////////////////////////////////////
    virtual EdgeHandle GetHandle(Edge const &edge) const = 0;
    //{ return EdgeHandle(&edge-m_Edges); }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the handle of a half edge.
    /// \param he the reference to the half edge
    /// \return Return the handle of the half edge.
    ///////////////////////////////////////////////////////////////////////////
    virtual HalfEdgeHandle GetHandle(HalfEdge const &he) const = 0;
    //{ return this->PairHalfEdge(he.pairHalfEdge); }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the handle of a face.
    /// \param face the reference to the face
    /// \return Return the handle of the face.
    ///////////////////////////////////////////////////////////////////////////
    virtual FaceHandle GetHandle(Face const &face) const = 0;
    //{ return FaceHandle(&face-m_Faces); }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the handle of an edge by one of its half edge's handle.
    /// \param he one half edge's handle of the edge
    /// \return Return the handle of the edge.
    /// \note An edge is composed by two opposite half edges.
    ///////////////////////////////////////////////////////////////////////////
    EdgeHandle GetEdgeHandle(HalfEdgeHandle he) const
    { return EdgeHandle(he.Idx() >> 1); }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the handle of one half edge's opposite.
    /// \param he the handle of the half edge
    /// \return Return the handle of the opposite half edge.
    ///////////////////////////////////////////////////////////////////////////
    HalfEdgeHandle PairHalfEdge(HalfEdgeHandle he) const
    { return this->GetHalfEdge(he).pairHalfEdge; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the handle of one half edge's next half edge.
    /// \param he the handle of the half edge
    /// \return Return the handle of the next half edge.
    ///////////////////////////////////////////////////////////////////////////
    HalfEdgeHandle NextHalfEdge(HalfEdgeHandle he) const
    { return this->GetHalfEdge(he).nextHalfEdge; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the handle of one half edge's previous half edge.
    /// \param he the handle of the half edge
    /// \return Return the handle of the previous half edge.
    ///////////////////////////////////////////////////////////////////////////
    HalfEdgeHandle PrevHalfEdge(HalfEdgeHandle he) const
    { return this->GetHalfEdge(he).prevHalfEdge; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the handle of one half edge's end vertex.
    /// \param he the handle of the half edge
    /// \return Return the handle of the end vertex.
    ///////////////////////////////////////////////////////////////////////////
    VertexHandle EndVertex(HalfEdgeHandle he) const
    { return this->GetHalfEdge(he).endVertex; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the handle of one half edge's adjacent face.
    /// \param he the handle of the half edge
    /// \return Return the handle of the face.
    /// \note A face is made up of an inner loop of half edges.
    ///////////////////////////////////////////////////////////////////////////
    FaceHandle AdjFace(HalfEdgeHandle he) const
    { return this->GetHalfEdge(he).face; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the handle of one vertex's out half edge.
    /// \param v the handle of the vertex
    /// \return Return the handle of the out half edge.
    ///////////////////////////////////////////////////////////////////////////
    HalfEdgeHandle OutHalfEdge(VertexHandle v) const
    { return this->GetVertex(v).outHalfEdge; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the handle of one half edge in one face.
    /// \param f the handle of the face
    /// \return Return the handle of one of the face's half edges.
    /// \note A face is made up of an inner loop of half edges.
    ///////////////////////////////////////////////////////////////////////////
    HalfEdgeHandle OneHalfEdge(FaceHandle f) const
    { return this->GetFace(f).oneHalfEdge; }

    ///////////////////////////////////////////////////////////////////////////
    /// Test the validity of one vertex handle.
    /// \param v the handle of the vertex to be tested
    /// \return Return true if this handle is valid, otherwise return false.
    ///////////////////////////////////////////////////////////////////////////
    bool IsValid(VertexHandle v) const { return (v.Idx()<m_VertNum && v.Idx()>=0); }

    ///////////////////////////////////////////////////////////////////////////
    /// Test the validity of one edge handle.
    /// \param e the handle of the edge to be tested
    /// \return Return true if this handle is valid, otherwise return false.
    ///////////////////////////////////////////////////////////////////////////
    bool IsValid(EdgeHandle e) const { return (e.Idx()<m_EdgeNum && e.Idx()>=0); }

    ///////////////////////////////////////////////////////////////////////////
    /// Test the validity of one half edge handle.
    /// \param he the handle of the half edge to be tested
    /// \return Return true if this handle is valid, otherwise return false.
    ///////////////////////////////////////////////////////////////////////////
    bool IsValid(HalfEdgeHandle he) const { return (he.Idx()<(m_EdgeNum<<1) && he.Idx()>=0); }

    ///////////////////////////////////////////////////////////////////////////
    /// Test the validity of one face handle.
    /// \param f the handle of the face to be tested
    /// \return Return true if this handle is valid, otherwise return false.
    ///////////////////////////////////////////////////////////////////////////
    bool IsValid(FaceHandle f) const { return (f.Idx()<m_FaceNum && f.Idx()>=0); }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the number of current valid vertices in this mesh.
    /// \return Return the number of the valid vertices.
    /// \note For some reasons of efficiency, deleting some components from the
    ///       mesh does not really remove the components from the memory but just
    ///       make marks on them. Therefore, after the delete operations, the 
    ///       total number of the components in the memory does not equal to the
    ///       number of the valid ones. So, use this function to get the right
    ///       number. Furthermore, ClearGarbage() will remove the deleted components
    ///       from the memory at last.
    ///////////////////////////////////////////////////////////////////////////
    size_type GetValidVertexNumber() const { return m_ValidVertNum; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the number of current valid edges in this mesh.
    /// \return Return the number of the valid edges.
    /// \note For some reasons of efficiency, deleting some components from the
    ///       mesh does not really remove the components from the memory, but just
    ///       make marks on them. Therefore, after the delete operations, the 
    ///       total number of the components in the memory does not equal to the
    ///       number of the valid ones. So, use this function to get the right
    ///       number. Furthermore, ClearGarbage() will remove the deleted components
    ///       from the memory at last.
    ///////////////////////////////////////////////////////////////////////////
    size_type GetValidEdgeNumber() const { return m_ValidEdgeNum; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the number of current valid faces in this mesh.
    /// \return Return the number of the valid faces.
    /// \note For some reasons of efficiency, deleting some components from the
    ///       mesh does not really remove the components from the memory, but just
    ///       make marks on them. Therefore, after the delete operations, the 
    ///       total number of the components in the memory does not equal to the
    ///       number of the valid ones. So, use this function to get the right
    ///       number. Furthermore, ClearGarbage() will remove the deleted components
    ///       from the memory at last.
    ///////////////////////////////////////////////////////////////////////////
    size_type GetValidFaceNumber() const { return m_ValidFaceNum; }

    ///////////////////////////////////////////////////////////////////////////
    /// Test the orientation of front-facing polygons.
    /// \return Return true if the orientation of front-facing polygons is clockwise,
    ///         otherwise return false.
    ///////////////////////////////////////////////////////////////////////////
    virtual bool TestClockwise();

    ///////////////////////////////////////////////////////////////////////////
    /// Clear all the user-set flags except MITK_FLAG_DELETED.
    ///////////////////////////////////////////////////////////////////////////
    void ClearFlags();

protected:
    virtual ~mitkHEMesh();

    void _init();

    virtual index_type _addVertex(Vertex3f &vert);
    virtual index_type _addFace(unsigned int num, index_type *verts);
    virtual Vertex3f const* _getVertex(index_type vertIdx);
    virtual index_type const* _getFace(index_type faceIdx);
    virtual Vertex3f* _getVertexForWrite(index_type vertIdx);
    virtual index_type* _getFaceForWrite(index_type faceIdx);
    virtual bool _setFace(index_type faceIdx, unsigned int num, index_type *verts);

    // Actual method for adding Vertex/Edge/Face.
    // Memory allocation will be done here.
    virtual VertexHandle   _addNewVertex(float x,         float y,         float z, 
                                         float nx = 0.0f, float ny = 0.0f, float nz = 0.0f,
                                         HalfEdgeHandle edge = HalfEdgeHandle()) = 0;
    virtual HalfEdgeHandle _addNewEdge(VertexHandle start, VertexHandle end) = 0;
    virtual FaceHandle     _addNewFace(HalfEdgeHandle halfedge = HalfEdgeHandle()) = 0;
    
    // Adjust the outgoing halfedge of a vertex.
    // To make sure that the halfedge is the boundary halfedge if there is one
    // in this vertex's outgoing halfedges.
    void _adjustOutHalfEdge(VertexHandle vert);

    void _deleteVert(VertexHandle v) { this->GetVertex(v).SetDeleted(true); m_ValidVertNum--; m_NeedClearVert=true; }
    void _deleteEdge(EdgeHandle e) { this->GetEdge(e).SetDeleted(true); m_ValidEdgeNum--; m_NeedClearEdge=true; }
    void _deleteFace(FaceHandle f) { this->GetFace(f).SetDeleted(true); m_ValidFaceNum--; m_NeedClearFace=true; }

    // Helper for clearing garbage.
    virtual void _clearDeletedVertices() = 0;
    virtual void _clearDeletedEdges() = 0;
    virtual void _clearDeletedFaces() = 0;

    VertexPtr _getVertexPtr(index_type idx) const { return &(this->GetVertex(VertexHandle(idx))); }
    EdgePtr _getEdgePtr(index_type idx) const { return &(this->GetEdge(EdgeHandle(idx))); }
    HalfEdgePtr _getHalfEdgePtr(index_type idx) const { return &(this->GetEdge(EdgeHandle(idx>>1)).halfEdge[idx%2]); }
    FacePtr _getFacePtr(index_type idx) const { return &(this->GetFace(FaceHandle(idx))); }
    
    //helper to test triangle orientation 
    Orientation _testOrientation(FaceHandle fh);

    void _clearEdgeFlags();
    void _clearVertFlags();
    void _clearFaceFlags();


    size_type m_VertNum;
    size_type m_EdgeNum;
    size_type m_FaceNum;
    size_type m_ValidVertNum;
    size_type m_ValidEdgeNum;
    size_type m_ValidFaceNum;
    size_type m_MaxVertNum;
    size_type m_MaxEdgeNum;
    size_type m_MaxFaceNum;

//  size_type m_Increment;
//  Vertex *m_Vertices;
//  Edge *m_Edges;
//  Face *m_Faces;

    index_type *m_TempFace;

    bool m_NeedClearVert;
    bool m_NeedClearEdge;
    bool m_NeedClearFace;

private:
    mitkHEMesh(const mitkHEMesh&);
    void operator = (const mitkHEMesh&);

public:
    // for iterators and circulators
    #define CirculatorT  VertexVertexIterT
    #define SourceHandle VertexHandle
    #define TargetHandle VertexHandle
    #define TargetType   Vertex
    #define HANDLE       (_mesh->EndVertex(_current))
    #define TARGET       (_mesh->GetVertex(HANDLE))
    #define START        (_mesh->OutHalfEdge(roundCenter))
    #define NEXT         _current = _mesh->NextHalfEdge(_mesh->PairHalfEdge(_current));
    #define PREV         _current = _mesh->PairHalfEdge(_mesh->PrevHalfEdge(_current));
    #define POSTINIT
    #include "mitkHEMeshCirculatorTemplate.t"
    #undef  CirculatorT
    #undef  SourceHandle
    #undef  TargetHandle
    #undef  TargetType
    #undef  HANDLE
    #undef  TARGET
    #undef  START
    #undef  NEXT
    #undef  PREV
    #undef  POSTINIT

    #define CirculatorT  VertexOHalfedgeIterT
    #define SourceHandle VertexHandle
    #define TargetHandle HalfEdgeHandle
    #define TargetType   HalfEdge
    #define HANDLE       (_current)
    #define TARGET       (_mesh->GetHalfEdge(HANDLE))
    #define START        (_mesh->OutHalfEdge(roundCenter))
    #define NEXT         _current = _mesh->NextHalfEdge(_mesh->PairHalfEdge(_current));
    #define PREV         _current = _mesh->PairHalfEdge(_mesh->PrevHalfEdge(_current));
    #define POSTINIT
    #include "mitkHEMeshCirculatorTemplate.t"
    #undef  CirculatorT
    #undef  SourceHandle
    #undef  TargetHandle
    #undef  TargetType
    #undef  HANDLE
    #undef  TARGET
    #undef  START
    #undef  NEXT
    #undef  PREV
    #undef  POSTINIT

    #define CirculatorT  VertexIHalfedgeIterT
    #define SourceHandle VertexHandle
    #define TargetHandle HalfEdgeHandle
    #define TargetType   HalfEdge
    #define HANDLE       (_current)
    #define TARGET       (_mesh->GetHalfEdge(HANDLE))
    #define START        (_mesh->PairHalfEdge(_mesh->OutHalfEdge(roundCenter)))
    #define NEXT         _current = _mesh->pairHalfEdge(_mesh->nextHalfEdge(_current));
    #define PREV         _current = _mesh->PrevHalfEdge(_mesh->PairHalfEdge(_current));
    #define POSTINIT
    #include "mitkHEMeshCirculatorTemplate.t"
    #undef  CirculatorT
    #undef  SourceHandle
    #undef  TargetHandle
    #undef  TargetType
    #undef  HANDLE
    #undef  TARGET
    #undef  START
    #undef  NEXT
    #undef  PREV
    #undef  POSTINIT

    #define CirculatorT  VertexEdgeIterT
    #define SourceHandle VertexHandle
    #define TargetHandle EdgeHandle
    #define TargetType   Edge
    #define HANDLE       (_mesh->GetEdgeHandle(_current))
    #define TARGET       (_mesh->GetEdge(HANDLE))
    #define START        (_mesh->OutHalfEdge(roundCenter))
    #define NEXT         _current = _mesh->NextHalfEdge(_mesh->PairHalfEdge(_current));
    #define PREV         _current = _mesh->PairHalfEdge(_mesh->PrevHalfEdge(_current));
    #define POSTINIT
    #include "mitkHEMeshCirculatorTemplate.t"
    #undef  CirculatorT
    #undef  SourceHandle
    #undef  TargetHandle
    #undef  TargetType
    #undef  HANDLE
    #undef  TARGET
    #undef  START
    #undef  NEXT
    #undef  PREV
    #undef  POSTINIT

    #define CirculatorT  VertexFaceIterT
    #define SourceHandle VertexHandle
    #define TargetHandle FaceHandle
    #define TargetType   Face
    #define HANDLE       (_mesh->AdjFace(_current))
    #define TARGET       (_mesh->GetFace(HANDLE))
    #define START        (_mesh->OutHalfEdge(roundCenter))
    #define NEXT         do _current = _mesh->NextHalfEdge(_mesh->PairHalfEdge(_current)); while ((this->NotEnd()) && !(HANDLE.IsValid()));
    #define PREV         do _current = _mesh->PairHalfEdge(_mesh->PrevHalfEdge(_current)); while ((this->NotEnd()) && !(HANDLE.IsValid()));
    #define POSTINIT     if (_current.IsValid() && !(HANDLE.IsValid())) this->operator++();
    #include "mitkHEMeshCirculatorTemplate.t"
    #undef  CirculatorT
    #undef  SourceHandle
    #undef  TargetHandle
    #undef  TargetType
    #undef  HANDLE
    #undef  TARGET
    #undef  START
    #undef  NEXT
    #undef  PREV
    #undef  POSTINIT

    #define CirculatorT  FaceVertexIterT
    #define SourceHandle FaceHandle
    #define TargetHandle VertexHandle
    #define TargetType   Vertex
    #define HANDLE       (_mesh->EndVertex(_current))
    #define TARGET       (_mesh->GetVertex(HANDLE))
    #define START        (_mesh->OneHalfEdge(roundCenter))
    #define NEXT         _current = _mesh->NextHalfEdge(_current);
    #define PREV         _current = _mesh->PrevHalfEdge(_current);
    #define POSTINIT
    #include "mitkHEMeshCirculatorTemplate.t"
    #undef  CirculatorT
    #undef  SourceHandle
    #undef  TargetHandle
    #undef  TargetType
    #undef  HANDLE
    #undef  TARGET
    #undef  START
    #undef  NEXT
    #undef  PREV
    #undef  POSTINIT

    #define CirculatorT  FaceHalfedgeIterT
    #define SourceHandle FaceHandle
    #define TargetHandle HalfEdgeHandle
    #define TargetType   HalfEdge
    #define HANDLE       (_current)
    #define TARGET       (_mesh->GetHalfEdge(HANDLE))
    #define START        (_mesh->OneHalfEdge(roundCenter))
    #define NEXT         _current = _mesh->NextHalfEdge(_current);
    #define PREV         _current = _mesh->PrevHalfEdge(_current);
    #define POSTINIT
    #include "mitkHEMeshCirculatorTemplate.t"
    #undef  CirculatorT
    #undef  SourceHandle
    #undef  TargetHandle
    #undef  TargetType
    #undef  HANDLE
    #undef  TARGET
    #undef  START
    #undef  NEXT
    #undef  PREV
    #undef  POSTINIT

    #define CirculatorT  FaceEdgeIterT
    #define SourceHandle FaceHandle
    #define TargetHandle EdgeHandle
    #define TargetType   Edge
    #define HANDLE       (_mesh->GetEdgeHandle(_current))
    #define TARGET       (_mesh->GetEdge(HANDLE))
    #define START        (_mesh->OneHalfEdge(roundCenter))
    #define NEXT         _current = _mesh->NextHalfEdge(_current);
    #define PREV         _current = _mesh->PrevHalfEdge(_current);
    #define POSTINIT
    #include "mitkHEMeshCirculatorTemplate.t"
    #undef  CirculatorT
    #undef  SourceHandle
    #undef  TargetHandle
    #undef  TargetType
    #undef  HANDLE
    #undef  TARGET
    #undef  START
    #undef  NEXT
    #undef  PREV
    #undef  POSTINIT

    #define CirculatorT  FaceFaceIterT
    #define SourceHandle FaceHandle
    #define TargetHandle FaceHandle
    #define TargetType   Face
    #define HANDLE       (_mesh->AdjFace(_mesh->PairHalfEdge(_current)))
    #define TARGET       (_mesh->GetFace(HANDLE))
    #define START        (_mesh->OneHalfEdge(roundCenter))
    #define NEXT         do _current = _mesh->NextHalfEdge(_current); while ((this->NotEnd()) && !(HANDLE.IsValid()));
    #define PREV         do _current = _mesh->PrevHalfEdge(_current); while ((this->NotEnd()) && !(HANDLE.IsValid()));
    #define POSTINIT     if (_current.IsValid() && !(HANDLE.IsValid())) this->operator++();
    #include "mitkHEMeshCirculatorTemplate.t"
    #undef  CirculatorT
    #undef  SourceHandle
    #undef  TargetHandle
    #undef  TargetType
    #undef  HANDLE
    #undef  TARGET
    #undef  START
    #undef  NEXT
    #undef  PREV
    #undef  POSTINIT


    #define IteratorT    VertexIterT
    #define TargetType   Vertex
    #define TargetHandle VertexHandle
    #define HANDLE       (VertexHandle(_current))
    #define TARGETPTR    (_mesh->_getVertexPtr(_current))
    #define TOTAL        (_mesh->GetVertexNumber())
    #include "mitkHEMeshIteratorTemplate.t"
    #undef  IteratorT
    #undef  TargetType
    #undef  TargetHandle
    #undef  HANDLE
    #undef  TARGETPTR
    #undef  TOTAL

    #define IteratorT    EdgeIterT
    #define TargetType   Edge
    #define TargetHandle EdgeHandle
    #define HANDLE       (EdgeHandle(_current))
    #define TARGETPTR    (_mesh->_getEdgePtr(_current))
    #define TOTAL        (_mesh->GetEdgeNumber())
    #include "mitkHEMeshIteratorTemplate.t"
    #undef  IteratorT
    #undef  TargetType
    #undef  TargetHandle
    #undef  HANDLE
    #undef  TARGETPTR
    #undef  TOTAL

    #define IteratorT    FaceIterT
    #define TargetType   Face
    #define TargetHandle FaceHandle
    #define HANDLE       (FaceHandle(_current))
    #define TARGETPTR    (_mesh->_getFacePtr(_current))
    #define TOTAL        (_mesh->GetFaceNumber())
    #include "mitkHEMeshIteratorTemplate.t"
    #undef  IteratorT
    #undef  TargetType
    #undef  TargetHandle
    #undef  HANDLE
    #undef  TARGETPTR
    #undef  TOTAL

    friend class VertexVertexIterT<mitkHEMesh>;
    friend class VertexOHalfedgeIterT<mitkHEMesh>;
    friend class VertexIHalfedgeIterT<mitkHEMesh>;
    friend class VertexEdgeIterT<mitkHEMesh>;
    friend class FaceVertexIterT<mitkHEMesh>;
    friend class FaceHalfedgeIterT<mitkHEMesh>;
    friend class FaceEdgeIterT<mitkHEMesh>;
    friend class FaceFaceIterT<mitkHEMesh>;

    friend class VertexIterT<mitkHEMesh>;
    friend class EdgeIterT<mitkHEMesh>;
    friend class FaceIterT<mitkHEMesh>;

///////////////////////////////////////////////////////////////////////
/// VertexVertexIterator is an iterator class for iterating over all
/// neighboring vertices around a vertex.
/// 
/// The code snippet for using this class:
/// \code
/// // mesh is a pointer to an object of mitkHEMesh
/// // center is the handle of the center vertex
/// mitkHEMesh::VertexVertexIterator iter(mesh, center);
/// for ( ; iter; ++iter)
/// {
///     // iter is the pointer to current neighboring vertex
///     // *iter is the reference to current neighboring vertex
///     // iter.Handle() returns the handle of current neighboring vertex
///     do something with iter, *iter or \e r.Handle();
/// }
/// \endcode
///////////////////////////////////////////////////////////////////////
    typedef VertexVertexIterT<mitkHEMesh> VertexVertexIterator;
    
///////////////////////////////////////////////////////////////////////
/// VertexOHalfedgeIterator is an iterator class for iterating over all
/// outgoing half edges around a vertex.
/// 
/// The code snippet for using this class:
/// \code
/// // mesh is a pointer to an object of mitkHEMesh
/// // center is the handle of the center vertex
/// mitkHEMesh::VertexOHalfedgeIterator iter(mesh, center);
/// for ( ; iter; ++iter)
/// {
///     // iter is the pointer to current outgoing half edge
///     // *iter is the reference to current outgoing half edge
///     // iter.Handle() returns the handle of current outgoing half edge
///     do something with iter, *iter or iter.Handle();
/// }
/// \endcode
///////////////////////////////////////////////////////////////////////
    typedef VertexOHalfedgeIterT<mitkHEMesh> VertexOHalfedgeIterator;

///////////////////////////////////////////////////////////////////////
/// VertexIHalfedgeIterator is an iterator class for iterating over all
/// incoming half edges around a vertex.
/// 
/// The code snippet for using this class:
/// \code
/// // mesh is a pointer to an object of mitkHEMesh
/// // center is the handle of the center vertex
/// mitkHEMesh::VertexIHalfedgeIterator iter(mesh, center);
/// for ( ; iter; ++iter)
/// {
///     // iter is the pointer to current incoming half edge
///     // *iter is the reference to current incoming half edge
///     // iter.Handle() returns the handle of current incoming half edge
///     do something with iter, *iter or iter.Handle();
/// }
/// \endcode
///////////////////////////////////////////////////////////////////////
    typedef VertexIHalfedgeIterT<mitkHEMesh> VertexIHalfedgeIterator;

///////////////////////////////////////////////////////////////////////
/// VertexEdgeIterator is an iterator class for iterating over all
/// incident edges around a vertex.
/// 
/// The code snippet for using this class:
/// \code
/// // mesh is a pointer to an object of mitkHEMesh
/// // center is the handle of the center vertex
/// mitkHEMesh::VertexEdgeIterator iter(mesh, center);
/// for ( ; iter; ++iter)
/// {
///     // iter is the pointer to current incident edge
///     // *iter is the reference to current incident edge
///     // iter.Handle() returns the handle of current incident edge
///     do something with iter, *iter or iter.Handle();
/// }
/// \endcode
///////////////////////////////////////////////////////////////////////
    typedef VertexEdgeIterT<mitkHEMesh> VertexEdgeIterator;

///////////////////////////////////////////////////////////////////////
/// VertexFaceIterator is an iterator class for iterating over all
/// adjacent faces around a vertex.
/// 
/// The code snippet for using this class:
/// \code
/// // mesh is a pointer to an object of mitkHEMesh
/// // center is the handle of the center vertex
/// mitkHEMesh::VertexFaceIterator iter(mesh, center);
/// for ( ; iter; ++iter)
/// {
///     // iter is the pointer to current adjacent face
///     // *iter is the reference to current adjacent face
///     // iter.Handle() returns the handle of current adjacent face
///     do something with iter, *iter or iter.Handle();
/// }
/// \endcode
///////////////////////////////////////////////////////////////////////
    typedef VertexFaceIterT<mitkHEMesh> VertexFaceIterator;

///////////////////////////////////////////////////////////////////////
/// FaceVertexIterator is an iterator class for iterating over a
/// face's vertices.
/// 
/// The code snippet for using this class:
/// \code
/// // mesh is a pointer to an object of mitkHEMesh
/// // center is the handle of the face
/// mitkHEMesh::FaceVertexIterator iter(mesh, center);
/// for ( ; iter; ++iter)
/// {
///     // iter is the pointer to current vertex
///     // *iter is the reference to current vertex
///     // iter.Handle() returns the handle of current vertex
///     do something with iter, *iter or iter.Handle();
/// }
/// \endcode
///////////////////////////////////////////////////////////////////////
    typedef FaceVertexIterT<mitkHEMesh> FaceVertexIterator;

///////////////////////////////////////////////////////////////////////
/// FaceHalfedgeIterator is an iterator class for iterating over a
/// face's half edges.
/// 
/// The code snippet for using this class:
/// \code
/// // mesh is a pointer to an object of mitkHEMesh
/// // center is the handle of the face
/// mitkHEMesh::FaceHalfedgeIterator iter(mesh, center);
/// for ( ; iter; ++iter)
/// {
///     // iter is the pointer to current half edge
///     // *iter is the reference to current half edge
///     // iter.Handle() returns the handle of current half edge
///     do something with iter, *iter or iter.Handle();
/// }
/// \endcode
///////////////////////////////////////////////////////////////////////
    typedef FaceHalfedgeIterT<mitkHEMesh> FaceHalfedgeIterator;

///////////////////////////////////////////////////////////////////////
/// FaceEdgeIterator is an iterator class for iterating over a
/// face's edges.
/// 
/// The code snippet for using this class:
/// \code
/// // mesh is a pointer to an object of mitkHEMesh
/// // center is the handle of the face
/// mitkHEMesh::FaceEdgeIterator iter(mesh, center);
/// for ( ; iter; ++iter)
/// {
///     // iter is the pointer to current edge
///     // *iter is the reference to current edge
///     // iter.Handle() returns the handle of current edge
///     do something with iter, *iter or iter.Handle();
/// }
/// \endcode
///////////////////////////////////////////////////////////////////////
    typedef FaceEdgeIterT<mitkHEMesh> FaceEdgeIterator;

///////////////////////////////////////////////////////////////////////
/// FaceFaceIterator is an iterator class for iterating over a face's all
/// edge-neighboring faces.
/// 
/// The code snippet for using this class:
/// \code
/// // mesh is a pointer to an object of mitkHEMesh
/// // center is the handle of the face
/// mitkHEMesh::FaceFaceIterator iter(mesh, center);
/// for ( ; iter; ++iter)
/// {
///     // iter is the pointer to current edge-neighboring face
///     // *iter is the reference to current edge-neighboring face
///     // iter.Handle() returns the handle of current edge-neighboring face
///     do something with iter, *iter or iter.Handle();
/// }
/// \endcode
///////////////////////////////////////////////////////////////////////
    typedef FaceFaceIterT<mitkHEMesh> FaceFaceIterator;

///////////////////////////////////////////////////////////////////////
/// VertexIterator is an iterator class for iterating over all vertices
/// of a mitkHEMesh object.
///
/// The code snippet for using this class:
/// \code
/// // mesh is a pointer to an object of mitkHEMesh
/// mitkHEMesh::VertexIterator iter(mesh);
/// for ( ; iter; ++iter)
/// {
///     // iter is the pointer to current vertex
///     // *iter is the reference to current vertex
///     // iter.Handle() returns the handle of current vertex
///     do something with iter, *iter or iter.Handle();
/// }
/// \endcode
///////////////////////////////////////////////////////////////////////
    typedef VertexIterT<mitkHEMesh> VertexIterator;

///////////////////////////////////////////////////////////////////////
/// EdgeIterator is an iterator class for iterating over all edges
/// of a mitkHEMesh object.
///
/// The code snippet for using this class:
/// \code
/// // mesh is a pointer to an object of mitkHEMesh
/// mitkHEMesh::EdgeIterator iter(mesh);
/// for ( ; iter; ++iter)
/// {
///     // iter is the pointer to current edge
///     // *iter is the reference to current edge
///     // iter.Handle() returns the handle of current edge
///     do something with iter, *iter or iter.Handle();
/// }
/// \endcode
///////////////////////////////////////////////////////////////////////
    typedef EdgeIterT<mitkHEMesh> EdgeIterator;

///////////////////////////////////////////////////////////////////////
/// FaceIterator is an iterator class for iterating over all faces
/// of a mitkHEMesh object.
///
/// The code snippet for using this class:
/// \code
/// // mesh is a pointer to an object of mitkHEMesh
/// mitkHEMesh::FaceIterator iter(mesh);
/// for ( ; iter; ++iter)
/// {
///     // iter is the pointer to current face
///     // *iter is the reference to current face
///     // iter.Handle() returns the handle of current face
///     do something with iter, *iter or iter.Handle();
/// }
/// \endcode
///////////////////////////////////////////////////////////////////////
    typedef FaceIterT<mitkHEMesh> FaceIterator;

};


#endif

