/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkHETriangleMesh_h
#define __mitkHETriangleMesh_h

#include "mitkHEMesh.h"

class mitkTriangleMesh;

/// mitkHETriangleMesh - an abstract class for triangle meshes represented by Half Edges
///////////////////////////////////////////////////////////////////////////
/// mitkHETriangleMesh is an abstract class for triangle meshes represented 
/// by Half Edges. This implementation of half edge references to 
/// OpenMesh written by Computer Graphics Group, RWTH Aachen.
/// \see mitkHEMesh, mitkHEICTriangleMesh (for in-core storage)
///      and mitkOoCTriangleMesh (for out-of-core storage)
class MITK_COMMON_API mitkHETriangleMesh : public mitkHEMesh
{
public:
    MITK_TYPE(mitkHETriangleMesh, mitkHEMesh)

    virtual void PrintSelf(ostream &os);

    ///////////////////////////////////////////////////////////////////////
    /// Default constructor.
    ///////////////////////////////////////////////////////////////////////
    mitkHETriangleMesh();

    ///////////////////////////////////////////////////////////////////////
    /// Create mitkHETriangleMesh object from a mitkTriangleMesh object which
    /// is not based on half edge structure.
    /// \param mesh the pointer to a mitkTriangleMesh object this mitkHETriangleMesh
    ///        object is created from
    /// \return Return true if this operation succeed, otherwise return false.
    ///////////////////////////////////////////////////////////////////////
    bool CreateFrom(mitkTriangleMesh *mesh);

    ///////////////////////////////////////////////////////////////////////
    /// Create mitkHETriangleMesh object from the arrays of vertices and faces.
    /// \param vertNum number of vertices in the vertex array
    /// \param verts the vertex array
    /// \param faceNum number of faces in the face array
    /// \param faces the face array
    /// \param boundingBox the 6-float array for bounding box
    /// \return Return true if this operation succeed, otherwise return false.
    /// \note Each Vertex3f struct contains 3 float values for coordinates
    ///       and 3 float values for normal. Each TriangleFace struct contains
    ///       3 indices to vertex array. If boundingBox is NULL, this function
    ///       will calculate the actual bounding box itself.
    ///////////////////////////////////////////////////////////////////////
    bool CreateFrom(size_type vertNum, Vertex3f const *verts,
                    size_type faceNum, TriangleFace const *faces,
                    float const *boundingBox = NULL);
    
    ///////////////////////////////////////////////////////////////////////////
    /// Return what type of data object this is.
    /// \return Return the type of this data object.
    ///////////////////////////////////////////////////////////////////////////
    virtual int GetDataObjectType() {return MITK_HE_TRIANGLE_MESH;};

    ///////////////////////////////////////////////////////////////////////
    /// Make the output data ready for new data to be inserted.
    ///////////////////////////////////////////////////////////////////////
    virtual void Initialize();

    ///////////////////////////////////////////////////////////////////////////
    /// Deep copy.
    /// \param src pointer to the source mitkDataObject
    ///////////////////////////////////////////////////////////////////////////
    //virtual void DeepCopy(mitkDataObject *src);

    ///////////////////////////////////////////////////////////////////////
    /// Add face.
    /// \param v0 the handle of the first vertex
    /// \param v1 the handle of the second vertex
    /// \param v2 the handle of the third vertex
    /// \return Return the handle of the face added.
    /// \warning Each VertexHandle must be valid, i.e. represents
    ///          a existent vertex in the mesh (has been ``Add*''ed before).
    ///////////////////////////////////////////////////////////////////////
    FaceHandle AddFace(VertexHandle v0, VertexHandle v1, VertexHandle v2)
    {   
        VertexHandle v[3];
        v[0] = v0; v[1] = v1; v[2] = v2;
        return mitkHEMesh::AddFace(3, v);
    }
    
    ///////////////////////////////////////////////////////////////////////
    /// Add face.
    /// \param vertices[0] the handle of the first vertex
    /// \param vertices[1] the handle of the second vertex
    /// \param vertices[2] the handle of the third vertex
    /// \return Return the handle of the face added.
    /// \warning Each VertexHandle must be valid, i.e. represents
    ///          a existent vertex in the mesh (has been ``Add*''ed before).
    ///////////////////////////////////////////////////////////////////////
    FaceHandle AddFace(VertexHandle vertices[3])
    { return mitkHEMesh::AddFace(3, vertices); }

    ///////////////////////////////////////////////////////////////////////
    /// Check whether collapsing half edge he is ok or would lead to
    /// topological inconsistencies.
    /// \param he the handle of the half edge to be tested
    /// \return Return true if collapsing is ok, otherwise return false.
    ///////////////////////////////////////////////////////////////////////
    bool IsCollapseOk(HalfEdgeHandle he);

    ///////////////////////////////////////////////////////////////////////
    /// Collapse the from-vertex of a half edge into its to-vertex.
    /// \param he the handle of the half edge to be collapsed
    /// \return Return the handle of the vertex the half edge collapsed into.
    ///////////////////////////////////////////////////////////////////////
    VertexHandle Collapse(HalfEdgeHandle he);

    ///////////////////////////////////////////////////////////////////////
    /// Split vertex v1 into edge v0v1. It is the inverse operation to Collapse().
    /// \param v0 the handle of a new vertex
    /// \param v1 the handle of the vertex to be splited
    /// \param vL the handle of the vertex to the left hand of the splited vertex
    /// \param vL the handle of the vertex to the right hand of the splited vertex
    /// \return Return the handle of the half edge from v0 to v1.
    /// \warning v0 must be valid, i.e. represents
    ///          a existent vertex in the mesh (has been ``Add*''ed before).
    ///////////////////////////////////////////////////////////////////////
    HalfEdgeHandle VertexSplit(VertexHandle v0, VertexHandle v1, VertexHandle vL, VertexHandle vR);

    ///////////////////////////////////////////////////////////////////////
    /// Split vertex v1 into edge v0v1. It is the inverse operation to Collapse().
    /// \param v0 a new vertex
    /// \param v1 the handle of the vertex to be splited
    /// \param vL the handle of the vertex to the left hand of the splited vertex
    /// \param vL the handle of the vertex to the right hand of the splited vertex
    /// \return Return the handle of the half edge from v0 to v1.
    ///////////////////////////////////////////////////////////////////////
    HalfEdgeHandle VertexSplit(Vertex &vert, VertexHandle v1, VertexHandle vL, VertexHandle vR)
    { return VertexSplit(AddVertex(vert),v1,vL,vR); }

    ///////////////////////////////////////////////////////////////////////
    /// Check whether flipping edge is topologically correct.
    /// \param edge the handle of the edge to be flipped
    /// \return Return true if flipping is ok, otherwise return false.
    ///////////////////////////////////////////////////////////////////////
    bool IsFlipOk(EdgeHandle edge) const;

    ///////////////////////////////////////////////////////////////////////
    /// Flip edge.
    /// \param edge the handle of the edge to be flipped
    ///////////////////////////////////////////////////////////////////////
    void Flip(EdgeHandle edge);

protected:
    virtual ~mitkHETriangleMesh();
    
    // Helper for halfedge collapse.
    void _removeEdge(HalfEdgeHandle he);
    void _removeLoop(HalfEdgeHandle he);

    // Helper for vertex split.
    HalfEdgeHandle _insertLoop(HalfEdgeHandle he);
    HalfEdgeHandle _insertEdge(VertexHandle v, HalfEdgeHandle h0, HalfEdgeHandle h1);

    // for compatible with mitkTriangleMesh which is used frequently
    //Vertex3f *m_VertArray;
    //TriangleFace *m_FaceArray;

private:
    mitkHETriangleMesh(const mitkHETriangleMesh&);
    void operator = (const mitkHETriangleMesh&);

};


#endif

