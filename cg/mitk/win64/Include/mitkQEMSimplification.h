/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkQEMSimplification_h
#define __mitkQEMSimplification_h

#include "mitkTriangleMeshSimplification.h"

/// mitkQEMSimplification - an implementation for the simplification algorithm using Quadric Error Metrics (QEM)
///////////////////////////////////////////////////////////////////////////
/// mitkQEMSimplification is an implementation for the simplification
/// algorithm using Quadric Error Metrics (QEM). The implementation is
/// based on the algorithm presented in following papers written by 
/// Michael Garland and Paul S. Heckbert and their implementation in QSlim
/// Simplification Software:
/// \li Michael Garland and Paul S. Heckbert, 
///     Surface Simplification Using Quadric Error Metrics,
///     in \e Proceedings \e of \e SIGGARPH'97, pp. 209-216, 1997.
/// \li Michael Garland and Paul S. Heckbert,
///     Simplifying Surfaces with Color and Texture using Quadric Error Metrics,
///     in \e Proceedings \e of \e IEEE \e Visualization'98, pp. 263-269, 1998.
///
/// Thanks for their excellent works.
class MITK_COMMON_API mitkQEMSimplification : public mitkTriangleMeshSimplification
{
public:
    MITK_TYPE(mitkQEMSimplification, mitkTriangleMeshSimplification)

    virtual void PrintSelf(ostream &os);

    mitkQEMSimplification();

    ///////////////////////////////////////////////////////////////////////
    /// Set meshing penalty.
    /// The default value is 1.0.
    /// \param mp meshing penalty (>1.0 will enable checks for the mesh penalties)
    ///////////////////////////////////////////////////////////////////////
    void SetMeshingPenalty(double mp) { m_MeshingPenalty = mp; }

    ///////////////////////////////////////////////////////////////////////
    /// Get meshing penalty.
    /// \return Return the meshing penalty.
    ///////////////////////////////////////////////////////////////////////
    double GetMeshingPenalty() { return m_MeshingPenalty; }

    ///////////////////////////////////////////////////////////////////////
    /// Set the limit of the vertex degree after simplification.
    /// The default value is 24.
    /// \param vdl the vertex degree limit
    ///////////////////////////////////////////////////////////////////////
    void SetVertexDegreeLimit(size_type vdl) { m_VertexDegreeLimit = vdl; }

    ///////////////////////////////////////////////////////////////////////
    /// Set the limit of the vertex degree.
    /// \return Return the limit of the vertex degree.
    ///////////////////////////////////////////////////////////////////////
    size_type GetVertexDegreeLimit() { return m_VertexDegreeLimit; }

    ///////////////////////////////////////////////////////////////////////
    /// Set the compactness ratio for triangle compactness check.
    /// The default value is 0.0.
    /// \param cr the compactness ratio
    ///////////////////////////////////////////////////////////////////////
    void SetCompactnessRatio(double cr) { m_CompactnessRatio = cr; }

    ///////////////////////////////////////////////////////////////////////
    /// Get the compactness ratio for triangle compactness check.
    /// \return Return the compactness ratio.
    ///////////////////////////////////////////////////////////////////////
    double GetCompactnessRatio() { return m_CompactnessRatio; }

    ///////////////////////////////////////////////////////////////////////
    /// Set the local validity threshold for local validity check.
    /// The default value is 0.0.
    /// \param lvt the local validity threshold
    ///////////////////////////////////////////////////////////////////////
    void SetLocalValidityThreshold(double lvt) { m_LocalValidityThreshold = lvt; }

    ///////////////////////////////////////////////////////////////////////
    /// Get the local validity threshold for local validity check.
    /// \return Return the local validity threshold.
    ///////////////////////////////////////////////////////////////////////
    double GetLocalValidityThreshold() { return m_LocalValidityThreshold; }

protected:
    virtual ~mitkQEMSimplification();

    virtual bool _simplificationProcess(mitkHETriangleMesh *mesh);

    double m_MeshingPenalty;
    double m_CompactnessRatio;
    double m_LocalValidityThreshold;
    size_type m_VertexDegreeLimit;

private:
    mitkQEMSimplification(const mitkQEMSimplification&);
    void operator = (const mitkQEMSimplification&);

};

#endif

