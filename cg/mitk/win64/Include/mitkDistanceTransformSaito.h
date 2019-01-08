/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkDistanceTransformSaito_h
#define __mitkDistanceTransformSaito_h

#include "mitkVolumeToVolumeFilter.h"
#include "mitkVolume.h"

/// mitkDistanceTransformSaito - computes 3D Euclidean DT
///////////////////////////////////////////////////////////////////////////
/// mitkDistanceTransformSaito implements the Euclidean DT using
/// Saito's algorithm. The distance map produced contains the square of the
/// Euclidean distance values to the nearest zero pixel. Input of this class
/// is a black and white image.
class MITK_COMMON_API mitkDistanceTransformSaito : public mitkVolumeToVolumeFilter
{

public:
    MITK_TYPE(mitkDistanceTransformSaito,mitkVolumeToVolumeFilter)

    ///////////////////////////////////////////////////////////////////////////
    /// Constructor of the class
    ///////////////////////////////////////////////////////////////////////////
    mitkDistanceTransformSaito();

    ///////////////////////////////////////////////////////////////////////////
    /// Set the number of dimensions that you want to compute EDT
    /// \param d              Represent the dimention of the volume, 2 or 3
    ///////////////////////////////////////////////////////////////////////////
    void SetDimension(int d);

    ///////////////////////////////////////////////////////////////////////////
    /// Set the part of the image to compute EDT
    /// \param nIp            1: compute the EDT of the white part
    ///                       2: compute the EDT of the black part
    ///                       3: compute the EDT of both the black and white part.
    ///                          distance of the black part is negtive, those of the
    ///                          white part is positive
    ///////////////////////////////////////////////////////////////////////////
    void SetImagePart(int nIp = 3);

    ///////////////////////////////////////////////////////////////////////////
    /// Get the part of the image to compute EDT
    /// \return               1: the white part of the image is computed
    ///                       2: the black part of the image is computed
    ///                       3: both the black and white parts of the image is computed.
    ///////////////////////////////////////////////////////////////////////////
    int GetImagePart(){return m_Ip;};

protected:
    virtual bool Execute();
    //Compute the x,y,z extent of a volume
    void PermuteExtent(mitkVolume* InputVolume, int nExtent[6]);
    //Compute the x,y,z increment in logical unit
    void PermuteIncrements(mitkVolume* InputVolume, int nInc[3]);
    //Compute the max distance of the volume
    float GetMaximumDistance(mitkVolume* Volume);

protected:
    int m_Dimension;
    int m_CurrentIteration;
    int m_Ip;

    virtual ~mitkDistanceTransformSaito();
private:
    mitkDistanceTransformSaito(const mitkDistanceTransformSaito&);
    void operator=(const mitkDistanceTransformSaito&);  
    
};



#endif

