/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkMesh_h
#define __mitkMesh_h

#include "mitkDataObject.h"
#include "mitkGeometryTypes.h"

/// mitkMesh - an abstract class for mesh types
///////////////////////////////////////////////////////////////////////////
/// mitkMesh is an abstract class for mesh types which are used to represent
/// 3D objects with their surfaces.
/// \see mitkTriangleMesh
/// \see mitkHEMesh
/// \see mitkHETriangleMesh
class MITK_COMMON_API mitkMesh : public mitkDataObject
{
public:
    MITK_TYPE(mitkMesh, mitkDataObject)

    virtual void PrintSelf(ostream &os);

    ///////////////////////////////////////////////////////////////////////////
    /// Delete the allocated memory (if any) and initialize to default status.
    /// \note Pure virtual function. Its concrete subclass must implement
    /// this function.
    ///////////////////////////////////////////////////////////////////////////
    virtual void Initialize();

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
    /// Copy the contents from another mesh. It is used to transfer between
    /// different concrete mesh type, i.e. in-core mesh <=> out-of-core mesh.
    /// \param src the mesh copy from
    /// \return Return true if success, otherwise return false.
    ///////////////////////////////////////////////////////////////////////////
    bool CopyMesh(mitkMesh *src);

    ///////////////////////////////////////////////////////////////////////////
    /// Return what type of data object this is.
    /// \return Return the type of this data object.
    ///////////////////////////////////////////////////////////////////////////
    virtual int GetDataObjectType() const { return MITK_MESH; }

    ///////////////////////////////////////////////////////////////////////////
    /// Set the mesh's vertices' number and allocate memory.
    /// \param number the number of vertices
    ///////////////////////////////////////////////////////////////////////////
    virtual void SetVertexNumber(size_type number) = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// Get the mesh's vertex number.
    /// \return Return the number of vertices.
    ///////////////////////////////////////////////////////////////////////////
    virtual size_type GetVertexNumber() const = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// Set the mesh's faces' number and allocate memory.
    /// \param number the number of faces
    ///////////////////////////////////////////////////////////////////////////
    virtual void SetFaceNumber(size_type number) = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// Get the mesh's face number.
    /// \return Return the number of faces.
    ///////////////////////////////////////////////////////////////////////////
    virtual size_type GetFaceNumber() const = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// Get data pointer of this vertex data. 
    /// \return Return a float pointer to the vertex data.
    /// \warning This function is obsolete. It is provided to keep old codes 
    ///          working. We strongly advise against using it in new codes. 
    ///////////////////////////////////////////////////////////////////////////
    virtual float* GetVertexData() = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// Get data pointer of this face data.
    /// \return Return a unsigned int pointer to the face data (indices to vertices).
    /// \warning This function is obsolete. It is provided to keep old codes 
    ///          working. We strongly advise against using it in new codes. 
    ///////////////////////////////////////////////////////////////////////////
    virtual index_type* GetFaceData() = 0;

    ///////////////////////////////////////////////////////////////////////
    /// Get the bounds for this mesh data as (Xmin,Xmax,Ymin,Ymax,Zmin,Zmax).
    /// \return Return a float array which contains Xmin, Xmax, Ymin, Ymax, 
    ///         Zmin and Zmax in turn.
    ///////////////////////////////////////////////////////////////////////
    float const * GetBoundingBox() { return m_BoundingBox; }

    ///////////////////////////////////////////////////////////////////////
    /// Get the bounds for this mesh data as (Xmin,Xmax,Ymin,Ymax,Zmin,Zmax).
    /// \param minX return minimum coordinate value in x-axis
    /// \param maxX return maximum coordinate value in x-axis
    /// \param minY return minimum coordinate value in y-axis
    /// \param maxY return maximum coordinate value in y-axis
    /// \param minZ return minimum coordinate value in z-axis
    /// \param maxZ return maximum coordinate value in z-axis
    ///////////////////////////////////////////////////////////////////////
    void GetBoundingBox(float &minX, float &maxX, float &minY, float &maxY, float &minZ, float &maxZ);

    ///////////////////////////////////////////////////////////////////////
    /// Get the bounds for this mesh data as (Xmin,Xmax,Ymin,Ymax,Zmin,Zmax).
    /// \param bounds[0] return minimum coordinate value in x-axis
    /// \param bounds[1] return maximum coordinate value in x-axis
    /// \param bounds[2] return minimum coordinate value in y-axis
    /// \param bounds[3] return maximum coordinate value in y-axis
    /// \param bounds[4] return minimum coordinate value in z-axis
    /// \param bounds[5] return maximum coordinate value in z-axis
    ///////////////////////////////////////////////////////////////////////
    void GetBoundingBox(float bounds[6]);

    ///////////////////////////////////////////////////////////////////////
    /// Set the bounds for this mesh data as (Xmin,Xmax,Ymin,Ymax,Zmin,Zmax).
    /// \param minX minimum coordinate value in x-axis
    /// \param maxX maximum coordinate value in x-axis
    /// \param minY minimum coordinate value in y-axis
    /// \param maxY maximum coordinate value in y-axis
    /// \param minZ minimum coordinate value in z-axis
    /// \param maxZ maximum coordinate value in z-axis
    ///////////////////////////////////////////////////////////////////////
    void SetBoundingBox(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);

    ///////////////////////////////////////////////////////////////////////
    /// Set the bounds for this mesh data as (Xmin,Xmax,Ymin,Ymax,Zmin,Zmax).
    /// \param bounds[0] minimum coordinate value in x-axis
    /// \param bounds[1] maximum coordinate value in x-axis
    /// \param bounds[2] minimum coordinate value in y-axis
    /// \param bounds[3] maximum coordinate value in y-axis
    /// \param bounds[4] minimum coordinate value in z-axis
    /// \param bounds[5] maximum coordinate value in z-axis
    ///////////////////////////////////////////////////////////////////////
    void SetBoundingBox(float bounds[6]);

    ///////////////////////////////////////////////////////////////////////////
    /// Indicate if the normals are reversed.
    /// \return Return true if the normals are reversed, otherwise return false.
    ///////////////////////////////////////////////////////////////////////////
    bool IsNormalReversed() const { return m_IsNormalReversed; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the orientation of front-facing polygons.
    /// \return Return true if selects clockwise polygons as front-facing.
    ///////////////////////////////////////////////////////////////////////////
    bool IsClockwise() const { return m_IsClockwise; }

    ///////////////////////////////////////////////////////////////////////////
    /// Set the orientation of front-facing polygons to isClockwise.
    /// \param isClockwise if selects clockwise polygons as front-facing
    ///////////////////////////////////////////////////////////////////////////
    void SetClockwise(bool isClockwise = true) { m_IsClockwise = isClockwise; }

    ///////////////////////////////////////////////////////////////////////////
    /// Test the orientation of front-facing polygons.
    /// \return Return true if the orientation of front-facing polygons is clockwise,
    ///         otherwise return false.
    ///////////////////////////////////////////////////////////////////////////
    virtual bool TestClockwise() = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// Reverse normals.
    ///////////////////////////////////////////////////////////////////////////
    virtual void ReverseNormals() {};

    ///////////////////////////////////////////////////////////////////////////
    /// A general interface for adding a vertex.
    /// \param vert the vertex to add
    /// \return Return the index of the vertex added.
    /// \note The struct Vertex3f is equal to follows:
    /// \code
    /// struct Point3f
    /// {
    ///     union
    ///     {
    ///         struct { float x, y, z; };
    ///         float coord[3];
    ///     };
    /// };
    ///
    /// struct Vertex3f
    /// {
    ///     Point3f point;
    ///     Point3f normal;
    /// };
    /// \endcode
    /// \see mitkGeometryTypes.h
    ///////////////////////////////////////////////////////////////////////////
    index_type AddVertex(Vertex3f &vert) { return this->_addVertex(vert); }
    
    ///////////////////////////////////////////////////////////////////////////
    /// A general interface for adding a face.
    /// \param face the face to add
    /// \return Return the index of the face added.
    /// \note The template struct _face_type is defined as follows in mitkGeometryTypes.h:
    /// \code
    /// template <typename IndexType, unsigned int indexNum>
    /// struct _face_type
    /// {
    ///     enum { vertNum = indexNum };
    ///     IndexType verts[indexNum];
    /// };
    /// \endcode
    /// \warning Each index in the ``verts'' array of the face must be valid, i.e. represents
    ///          a existent vertex in the mesh (has been added before).
    /// \see mitkGeometryTypes.h
    ///////////////////////////////////////////////////////////////////////////
    template <typename IndexType, unsigned int indexNum>
    index_type AddFace(_face_type<IndexType, indexNum> &face) { return this->_addFace(face.vertNum, face.verts); }

    ///////////////////////////////////////////////////////////////////////////
    /// An explicit instantiation of AddFace().
    ///////////////////////////////////////////////////////////////////////////
    index_type AddFace(TriangleFace &face) { return this->_addFace(face.vertNum, face.verts); }

    ///////////////////////////////////////////////////////////////////////////
    /// A general interface for getting a vertex.
    /// \param vertIdx the index of the vertex to get
    /// \param vert contain the returned vertex
    /// \return Return true if success, otherwise return false.
    ///////////////////////////////////////////////////////////////////////////
    bool GetVertex(index_type vertIdx, Vertex3f &vert)
    {
        if (vertIdx<0 || vertIdx>=this->GetVertexNumber()) return false;
        Vertex3f const *v = this->_getVertex(vertIdx);
        if (v==NULL) return false;
        vert = *v; return true;
    }

    ///////////////////////////////////////////////////////////////////////////
    /// A general interface for getting a set of vertices.
    /// \param startIdx the index of the first vertex to get
    /// \param num the number of vertices to get
    /// \param verts contain the returned vertices (from startIdx to startIdx+num-1)
    /// \return Return the actual number of gotten vertices.
    ///////////////////////////////////////////////////////////////////////////
    size_type GetVertices(index_type startIdx, size_type num, Vertex3f *verts)
    {
        if (startIdx<0 || startIdx>=this->GetVertexNumber()) return 0;
        return this->_getVertices(startIdx, num, verts);
    }

    ///////////////////////////////////////////////////////////////////////////
    /// A general interface for getting a face.
    /// \param faceIdx the index of the face to get
    /// \param face contain the returned face
    /// \return Return true if success, otherwise return false.
    ///////////////////////////////////////////////////////////////////////////
    template <typename IndexType, unsigned int indexNum>
    bool GetFace(index_type faceIdx, _face_type<IndexType, indexNum> &face)
    {
        if (faceIdx<0 || faceIdx>=this->GetFaceNumber()) return false;
        index_type const *vi = this->_getFace(faceIdx);
        if (vi==NULL) return false;
        for (int i=0; i<face.vertNum; ++i) face.verts[i] = vi[i];
        return true;
    }

    ///////////////////////////////////////////////////////////////////////////
    /// An explicit instantiation of GetFace().
    ///////////////////////////////////////////////////////////////////////////
    bool GetFace(index_type faceIdx, TriangleFace &face)
    {
        if (faceIdx<0 || faceIdx>=this->GetFaceNumber()) return false;
        index_type const *vi = this->_getFace(faceIdx);
        if (vi==NULL) return false;
        face.verts[0] = vi[0];
        face.verts[1] = vi[1];
        face.verts[2] = vi[2];
        return true;
    }

    ///////////////////////////////////////////////////////////////////////////
    /// A general interface for getting a set of triangle faces.
    /// \param startIdx the index of the first face to get
    /// \param num the number of faces to get
    /// \param faces contain the returned faces (from startIdx to startIdx+num-1)
    /// \return Return the actual number of gotten faces.
    ///////////////////////////////////////////////////////////////////////////
    size_type GetTriangleFaces(index_type startIdx, size_type num, TriangleFace *faces)
    {
        if (startIdx<0 || startIdx>=this->GetFaceNumber()) return 0;
        return this->_getTriangleFaces(startIdx, num, faces);
    }

    ///////////////////////////////////////////////////////////////////////////
    /// A general interface for getting all the vertices of  a set of triangle faces.
    /// \param startIdx the index of the first face to get
    /// \param num the number of faces to get
    /// \param verts contain the vertices of the triangle faces to get (3 vertices for each face)
    /// \return Return the actual number of gotten faces.
    ///////////////////////////////////////////////////////////////////////////
    size_type GetTriangleFaces(index_type startIdx, size_type num, Vertex3f *verts)
    {
        if (startIdx<0 || startIdx>=this->GetFaceNumber()) return 0;
        return this->_getTriangleFaces(startIdx, num, verts);
    }

    ///////////////////////////////////////////////////////////////////////////
    /// A general interface for setting a vertex.
    /// \param vertIdx the index of the vertex to set
    /// \param vert the vertex to set
    /// \return Return true if success, otherwise return false.
    ///////////////////////////////////////////////////////////////////////////
    bool SetVertex(index_type vertIdx, Vertex3f const &vert)
    {
        if (vertIdx<0 || vertIdx>=this->GetVertexNumber()) return false;
        Vertex3f *v = this->_getVertexForWrite(vertIdx);
        if (v==NULL) return false;
        *v = vert; return true;
    }

    ///////////////////////////////////////////////////////////////////////////
    /// A general interface for setting a face.
    /// \param faceIdx the index of the face to set
    /// \param face the face to set
    /// \return Return true if success, otherwise return false.
    ///////////////////////////////////////////////////////////////////////////
    template <typename IndexType, unsigned int indexNum>
    bool SetFace(index_type faceIdx, _face_type<IndexType, indexNum> &face) 
    { 
        if (faceIdx<0 || faceIdx>=this->GetFaceNumber()) return false;
        return this->_setFace(faceIdx, face.vertNum, face.verts);
    }

    ///////////////////////////////////////////////////////////////////////////
    /// An explicit instantiation of SetFace().
    ///////////////////////////////////////////////////////////////////////////
    bool SetFace(index_type faceIdx, TriangleFace &face)
    {
        if (faceIdx<0 || faceIdx>=this->GetFaceNumber()) return false;
        return this->_setFace(faceIdx, face.vertNum, face.verts);
    }

protected:
    enum Orientation { CLOCKWISE, ANTICLOCKWISE, DEGENERATIVE };

    mitkMesh();
    virtual ~mitkMesh();

    virtual index_type _addVertex(Vertex3f &vert) = 0;
    virtual index_type _addFace(unsigned int num, index_type *verts) = 0;
    virtual Vertex3f const* _getVertex(index_type vertIdx) = 0;
    virtual index_type const* _getFace(index_type faceIdx) = 0;
    virtual Vertex3f* _getVertexForWrite(index_type vertIdx) = 0;
    virtual index_type* _getFaceForWrite(index_type faceIdx) = 0;

    // default version, should be overrided in out-of-core mesh
    virtual size_type _getVertices(index_type startIdx, size_type num, Vertex3f *verts);
    virtual size_type _getTriangleFaces(index_type startIdx, size_type num, TriangleFace *faces);
    virtual size_type _getTriangleFaces(index_type startIdx, size_type num, Vertex3f *verts);
    virtual bool _setFace(index_type faceIdx, unsigned int num, index_type *verts);

    float m_BoundingBox[6];
    bool  m_IsClockwise;
    bool  m_IsNormalReversed;

private:
    mitkMesh(const mitkMesh&);
    void operator = (const mitkMesh&);

};

inline void mitkMesh::GetBoundingBox(float &minX, float &maxX, float &minY, float &maxY, float &minZ, float &maxZ)
{
    minX = m_BoundingBox[0];
    maxX = m_BoundingBox[1];
    minY = m_BoundingBox[2];
    maxY = m_BoundingBox[3];
    minZ = m_BoundingBox[4];
    maxZ = m_BoundingBox[5];
}

inline void mitkMesh::GetBoundingBox(float bounds[6])
{ this->GetBoundingBox(bounds[0], bounds[1], bounds[2], bounds[3], bounds[4], bounds[5]); }

inline void mitkMesh::SetBoundingBox(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
    m_BoundingBox[0] = minX;
    m_BoundingBox[1] = maxX;
    m_BoundingBox[2] = minY;
    m_BoundingBox[3] = maxY;
    m_BoundingBox[4] = minZ;
    m_BoundingBox[5] = maxZ;
}

inline void mitkMesh::SetBoundingBox(float bounds[6])
{ this->SetBoundingBox(bounds[0], bounds[1], bounds[2], bounds[3], bounds[4], bounds[5]); }


//#define DEFINED_mitkMesh



#endif

