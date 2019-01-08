/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkEuclideanDistanceTransformFilter_h
#define __mitkEuclideanDistanceTransformFilter_h

#include "mitkVolumeToVolumeFilter.h"

/// mitkEuclideanDistanceTransformFilter - computes 3D Euclidean DT using Meijster's Linear Time Algorithm
///////////////////////////////////////////////////////////////////////////
/// mitkDistanceTransformSaito implements the Euclidean DT using
/// Meijster's Linear Time Algorithm. 
class MITK_COMMON_API mitkEuclideanDistanceTransformFilter : public mitkVolumeToVolumeFilter
{
public:
    MITK_TYPE(mitkEuclideanDistanceTransformFilter,mitkVolumeToVolumeFilter)

    mitkEuclideanDistanceTransformFilter();

    ///////////////////////////////////////////////////////////////////////////
    /// Set the low threshold of the target area
    /// \param d the low threshold of the target area
    ///////////////////////////////////////////////////////////////////////////
    void SetLowThreshValue(double d){this->m_LowThresh = d;}
    ///////////////////////////////////////////////////////////////////////////
    /// Return the low threshold of the target area
    /// \return the low threshold of the target area
    ///////////////////////////////////////////////////////////////////////////
    int GetLowThreshValue(){return this->m_LowThresh;}
    ///////////////////////////////////////////////////////////////////////////
    /// Set the high threshold of the target area
    /// \param d the high threshold of the target area
    ///////////////////////////////////////////////////////////////////////////
    void SetHighThreshValue(double d){this->m_HighThresh = d;}
    ///////////////////////////////////////////////////////////////////////////
    /// Return the high threshold of the target area
    /// \return the high threshold of the target area
    ///////////////////////////////////////////////////////////////////////////
    int GetHighThreshValue(){return this->m_HighThresh;}

    ///////////////////////////////////////////////////////////////////////////
    /// Set whether use square distance to represent the result
    /// \param sd true for square distance; false for linear distance.
    ///////////////////////////////////////////////////////////////////////////
    void SetSquareDistance(bool sd) { m_SquareDistance=sd;}

    ///////////////////////////////////////////////////////////////////////////
    /// See whether the filter is using square distance to represent the result
    /// \return true for square distance; false for linear distance.
    ///////////////////////////////////////////////////////////////////////////
    bool UsingSquareDistance() { return m_SquareDistance;}

    ///////////////////////////////////////////////////////////////////////////
    /// Set whether use background mode. In background mode, the areas where value is 
    /// outside the threshold range is consider to be the target.
    /// \param bm true for background mode; false for foreground mode.
    ///////////////////////////////////////////////////////////////////////////
    void SetBackgroundMode(bool bm=true) {m_BackgroundMode=bm;}

protected:
    virtual ~mitkEuclideanDistanceTransformFilter();

    virtual bool Execute();

    double m_LowThresh;
    double m_HighThresh;

    bool m_SquareDistance;
    bool m_BackgroundMode;

private:
    mitkEuclideanDistanceTransformFilter(const mitkEuclideanDistanceTransformFilter&);
    void operator=(const mitkEuclideanDistanceTransformFilter&);

};

#endif
