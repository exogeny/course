/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkVolumeResliceFilter_h
#define __mitkVolumeResliceFilter_h

#include "mitkVolumeToVolumeFilter.h"
#include "mitkRCPtr.h"
#include "mitkPlane.h"

/// mitkRectPlane - an encapsulation of a rectangle in 3D space
///////////////////////////////////////////////////////////////////////////
/// mitkRectPlane is an encapsulation of a rectangle in 3D space. The
/// rectangle is decided by its three points: left-bottom point, right-bottom
/// point and left-top point.
class MITK_COMMON_API mitkRectPlane
{
public:
    typedef double coord_type;

    mitkRectPlane()
    {
        v0[0] = coord_type(0), v0[1] = coord_type(0); v0[2] = coord_type(0); v0[3] = coord_type(0);
        v1[0] = coord_type(1), v1[1] = coord_type(0); v1[2] = coord_type(0); v1[3] = coord_type(0);
        v2[0] = coord_type(2), v2[1] = coord_type(0); v2[2] = coord_type(0); v2[3] = coord_type(0);
    }

    mitkRectPlane(coord_type pv0[4], coord_type pv1[4], coord_type pv2[4])
    {
        v0[0] = pv0[0], v0[1] = pv0[1]; v0[2] = pv0[2]; v0[3] = pv0[3];
        v1[0] = pv1[0], v1[1] = pv1[1]; v1[2] = pv1[2]; v1[3] = pv1[3];
        v2[0] = pv2[0], v2[1] = pv2[1]; v2[2] = pv2[2]; v2[3] = pv2[3];
    }

    mitkRectPlane(coord_type v0x, coord_type v0y, coord_type v0z,
                  coord_type v1x, coord_type v1y, coord_type v1z,
                  coord_type v2x, coord_type v2y, coord_type v2z)
    {
        v0[0] = v0x, v0[1] = v0y; v0[2] = v0z; v0[3] = 1.0;
        v1[0] = v1x, v1[1] = v1y; v1[2] = v1z; v1[3] = 1.0;
        v2[0] = v2x, v2[1] = v2y; v2[2] = v2z; v2[3] = 1.0;
    }

    ~mitkRectPlane() {};

    mitkRectPlane& operator=(mitkRectPlane const &p)
    {
        v0[0] = p.v0[0]; v0[1] = p.v0[1]; v0[2] = p.v0[2]; v0[3] = p.v0[3];
        v1[0] = p.v1[0]; v1[1] = p.v1[1]; v1[2] = p.v1[2]; v1[3] = p.v1[3];
        v2[0] = p.v2[0]; v2[1] = p.v2[1]; v2[2] = p.v2[2]; v2[3] = p.v2[3];
        return *this;
    }

    mitkRectPlane(mitkRectPlane const &p)
    {
        v0[0] = p.v0[0]; v0[1] = p.v0[1]; v0[2] = p.v0[2]; v0[3] = p.v0[3];
        v1[0] = p.v1[0]; v1[1] = p.v1[1]; v1[2] = p.v1[2]; v1[3] = p.v1[3];
        v2[0] = p.v2[0]; v2[1] = p.v2[1]; v2[2] = p.v2[2]; v2[3] = p.v2[3];
    }

    ///////////////////////////////////////////////////////////////////////
    /// Check the validity of the rectangle, i.e. if
    /// \f$(\vec{v}_1-\vec{v}_0)\bot (\vec{v}_2-\vec{v}_0)\f$
    /// \return Return true if the rectangle is valid, otherwise return false.
    ///////////////////////////////////////////////////////////////////////
    bool CheckValidity()
    {
        double x1 = v1[0]-v0[0];
        double y1 = v1[1]-v0[1];
        double z1 = v1[2]-v0[2];
        double x2 = v2[0]-v0[0];
        double y2 = v2[1]-v0[1];
        double z2 = v2[2]-v0[2];
        double d = fabs(x1*x2 + y1*y2 + z1*z2) / (sqrt(x1*x1+y1*y1+z1*z1)*sqrt(x2*x2+y2*y2+z2*z2));

        if (d<1e-6) return true;
        else return false;      
    }

public:
    coord_type v0[4]; //left-bottom
    coord_type v1[4]; //right-bottom
    coord_type v2[4]; //left-top
};

/// mitkVolumeResliceFilter - a volume re-slice filter
///////////////////////////////////////////////////////////////////////////
/// mitkVolumeResliceFilter is a volume re-slice filter. It can reconstruct
/// one slice or all slices of the input volume data along an arbitrary
/// direction. It use a rectangle plane to scan the volume data from a 
/// start position (specified by a start plane) to a stop position
/// (specified by a stop point), and reconstruct the slices equidistantly.
class MITK_COMMON_API mitkVolumeResliceFilter : public mitkVolumeToVolumeFilter
{
public:
    MITK_TYPE(mitkVolumeResliceFilter, mitkVolumeToVolumeFilter)

    virtual void PrintSelf(ostream &os);

    ///////////////////////////////////////////////////////////////////////
    /// The default constructor.
    ///////////////////////////////////////////////////////////////////////
    mitkVolumeResliceFilter();

    ///////////////////////////////////////////////////////////////////////
    /// Set the plane where the reconstruction start.
    /// \param p the reference to a const mitkRectPlane object which specify
    ///        the start rectangle plane.
    ///////////////////////////////////////////////////////////////////////
    void SetStartPlane(mitkRectPlane const &p) { m_StartPlane = p; }

    ///////////////////////////////////////////////////////////////////////
    /// Set the point where the reconstruction stop.
    /// \param x the x-coordinate of the stop point
    /// \param y the y-coordinate of the stop point
    /// \param z the z-coordinate of the stop point
    ///////////////////////////////////////////////////////////////////////
    void SetStopPoint(double x, double y, double z) 
    {
        m_StopPoint[0] = x;
        m_StopPoint[1] = y;
        m_StopPoint[2] = z;
        m_StopPoint[3] = 1.0;
    }

    ///////////////////////////////////////////////////////////////////////
    /// Set the image width of the reconstructed slices.
    /// \param w the image width of the reconstructed slices
    ///////////////////////////////////////////////////////////////////////
    void SetSliceWidth(int w) { m_SliceWidth = w; m_SpacingXFirst = false; }

    ///////////////////////////////////////////////////////////////////////
    /// Set the image height of the reconstructed slices.
    /// \param h the image height of the reconstructed slices
    ///////////////////////////////////////////////////////////////////////
    void SetSliceHeight(int h) { m_SliceHeight = h; m_SpacingYFirst = false; }
    
    ///////////////////////////////////////////////////////////////////////
    /// Set the number of the reconstructed slices.
    /// \param num the number of the reconstructed slices
    ///////////////////////////////////////////////////////////////////////
    void SetSliceNumber(int num) { m_SliceNum = num; m_SpacingZFirst = false; }

    ///////////////////////////////////////////////////////////////////////
    /// Set spacing information in x axis, the unit is mm.
    /// \param sx the spacing (mm) in two adjacent voxels in x axis.
    ///////////////////////////////////////////////////////////////////////
    void SetSpacingX(double sx) { m_SpacingX = fabs(sx); m_SpacingXFirst = true; }
    
    ///////////////////////////////////////////////////////////////////////
    /// Set spacing information in y axis, the unit is mm.
    /// \param sy the spacing (mm) in two adjacent voxels in y axis.
    ///////////////////////////////////////////////////////////////////////
    void SetSpacingY(double sy) { m_SpacingY = fabs(sy); m_SpacingYFirst = true; }
    
    ///////////////////////////////////////////////////////////////////////
    /// Set spacing information in z axis, the unit is mm.
    /// \param sz the spacing (mm) in two adjacent voxels in z axis.
    ///////////////////////////////////////////////////////////////////////
    void SetSpacingZ(double sz) { m_SpacingZ = fabs(sz); m_SpacingZFirst = true; }
    
protected:
    virtual ~mitkVolumeResliceFilter();
    
    virtual bool Execute();

    mitkRectPlane m_StartPlane;

    double m_StopPoint[4];

    double m_SpacingX;
    double m_SpacingY;
    double m_SpacingZ;

    int m_SliceWidth;
    int m_SliceHeight;
    int m_SliceNum;

    bool m_SpacingXFirst;
    bool m_SpacingYFirst;
    bool m_SpacingZFirst;

private:
    mitkVolumeResliceFilter(const mitkVolumeResliceFilter&);
    void operator = (const mitkVolumeResliceFilter&);

};


//#define DEFINED_mitkVolumeResliceFilter



#endif

