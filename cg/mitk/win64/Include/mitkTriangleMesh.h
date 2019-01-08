/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkTriangleMesh_h
#define __mitkTriangleMesh_h

#include "mitkMesh.h"

class mitkHETriangleMesh;

/// mitkTriangleMesh - an abstract class for triangle meshes
///////////////////////////////////////////////////////////////////////////
/// mitkTriangleMesh is an abstract class for triangle meshes.
/// \see mitkICTriangleMesh and mitkOoCTriangleMesh
class MITK_COMMON_API mitkTriangleMesh : public mitkMesh
{
public:
    MITK_TYPE(mitkTriangleMesh, mitkMesh)

    virtual void PrintSelf(ostream& os);

    ///////////////////////////////////////////////////////////////////////////
    /// Default constructor of this class.
    ///////////////////////////////////////////////////////////////////////////
    mitkTriangleMesh();

    ///////////////////////////////////////////////////////////////////////
    /// Create mitkTriangleMesh object from a mitkHETriangleMesh object which
    /// is based on half edge structure.
    /// \param mesh the pointer to a mitkHETriangleMesh object this mitkTriangleMesh
    ///        object is created from
    /// \return Return true if this operation succeed, otherwise return false.
    ///////////////////////////////////////////////////////////////////////
    bool CreateFrom(mitkHETriangleMesh *mesh);
    
    ///////////////////////////////////////////////////////////////////////////
    /// Return what type of data object this is.
    /// \return Return the type of this data object.
    ///////////////////////////////////////////////////////////////////////////
    virtual int GetDataObjectType() const { return MITK_TRIANGLE_MESH; }

    ///////////////////////////////////////////////////////////////////////////
    /// Make the output data ready for new data to be inserted.
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
    /// Get the mesh's vertex number.
    /// \return Return the number of vertices.
    ///////////////////////////////////////////////////////////////////////////
    virtual size_type GetVertexNumber() const { return m_VertNum; }

    ///////////////////////////////////////////////////////////////////////////
    /// Get the mesh's face number.
    /// \return Return the number of faces.
    ///////////////////////////////////////////////////////////////////////////
    virtual size_type GetFaceNumber() const { return m_FaceNum; }

    ///////////////////////////////////////////////////////////////////////////
    /// Add a triangle face.
    /// \param face the face to add
    /// \return Return the index of the face added.
    /// \note The struct TriangleFace is equal to follows:
    /// \code
    /// struct TriangleFace
    /// {
    ///     enum { vertNum = 3 };
    ///     index_type verts[vertNum];
    /// };
    /// \endcode
    /// \warning Each index in the ``verts'' array of the face must be valid, i.e. represents
    ///          a existent vertex in the mesh (has been added before).
    /// \see mitkGeometryTypes.h
    ///////////////////////////////////////////////////////////////////////////
    index_type AddFace(TriangleFace &face) { return this->_addFace(face.vertNum, face.verts); }


protected:
    virtual ~mitkTriangleMesh();

    size_type m_VertNum;
    size_type m_FaceNum;
    size_type m_MaxVertNum;
    size_type m_MaxFaceNum;

private:
    mitkTriangleMesh(const mitkTriangleMesh&);
    void operator=(const mitkTriangleMesh&);

};



//#define DEFINED_mitkTriangleMesh



#endif

