/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/



#ifndef __mitkHistogram2D_h
#define __mitkHistogram2D_h

#include "mitkObject.h"
#include "mitkRCPtr.h"
#include "mitkVolume.h"

/// mitkHistogram2D - a tool to generate a 2D histogram from two volumes
///////////////////////////////////////////////////////////////////////////
/// mitkHistogram2D is a tool to generate a 2D histogram from two volumes
class MITK_COMMON_API mitkHistogram2D:public mitkObject
{
public:
    MITK_TYPE(mitkHistogram2D, mitkObject)
    mitkHistogram2D();
    ///////////////////////////////////////////////////////////////////////
    /// Set the first volume (the X-Axial volume)
    /// \param vol Specify pointer to the volume
    /// \param chIdx Specify the channel of the the histogram, if the value
    /// is greater or equal than the number of channel present, an average of 
    /// all channels will be genrated.
    /// \param extent Specify (optionally) the region of the volume to generate
    /// the histogram. NULL means to take the whole volume into consideration.
    ///////////////////////////////////////////////////////////////////////
    void SetSourceVolumeX(mitkVolume *vol, int chIdx=1,unsigned int *extent=NULL);
    ///////////////////////////////////////////////////////////////////////
    /// Set the second volume (the Y-Axial volume)
    /// \param vol Specify pointer to the volume
    /// \param chIdx Specify the channel of the the histogram, if the value
    /// is greater or equal than the number of channel present, an average of 
    /// all channels will be genrated.
    /// \param extent Specify (optionally) the region of the volume to generate
    /// the histogram. NULL means to take the whole volume into consideration.
    ///////////////////////////////////////////////////////////////////////
    void SetSourceVolumeY(mitkVolume *vol, int chIdx=1,unsigned int *extent=NULL);
    ///////////////////////////////////////////////////// //////////////////
    /// Set the value range and interval where to calculate statistics,
    /// this will allocate memory for statistics
    /// \param minX Specify the min value of the histogram's X-Axial
    /// \param maxX Specify the max value of the histogram's X-Axial
    /// \param intervalNum Specify number of intervals between minX and maxX
    /// \param minY Specify the min value of the histogram's Y-Axial
    /// \param maxY Specify the max value of the histogram's Y-Axial
    /// \param intervalNum Specify number of intervals between minY and maxY
    ///////////////////////////////////////////////////////////////////////
    void SetRange(double minX,double maxX,unsigned int intervalNumX,
                    double minY,double maxY,unsigned int intervalNumY);
    ///////////////////////////////////////////////////// //////////////////
    /// Get the value range and interval where statistics are calculated,
    /// \param minX Receive the min value of the histogram's X-Axial
    /// \param maxX Receive the max value of the histogram's X-Axial
    /// \param intervalNum Receive number of intervals between minX and maxX
    /// \param minY Receive the min value of the histogram's Y-Axial
    /// \param maxY Receive the max value of the histogram's Y-Axial
    /// \param intervalNum Receive number of intervals between minY and maxY
    ///////////////////////////////////////////////////////////////////////
    void GetRange(double &minX,double &maxX,unsigned int &intervalNumX,
                    double &minY,double &maxY,unsigned int &intervalNumY)
    {
        minX=m_minX;
        maxX=m_maxX;
        intervalNumX=m_intervalNumX;
        minY=m_minY;
        maxY=m_maxY;
        intervalNumY=m_intervalNumY;
    }
    ///////////////////////////////////////////////////////////////////////
    /// Get the maximum pixel value within the specified extent of VolumeX
    /// \return Return the maximum pixel value within the specified extent
    ///////////////////////////////////////////////////////////////////////
    double GetMaxPixValX() ;
    ///////////////////////////////////////////////////////////////////////
    /// Get the minimum pixel value within the specified extent of VolumeX
    /// this will trigger the calculation
    /// \return Return the minimum pixel value within the specified extent
    ///////////////////////////////////////////////////////////////////////
    double GetMinPixValX() ;
    ///////////////////////////////////////////////////////////////////////
    /// Get the maximum pixel value within the specified extent of VolumeY
    /// \return Return the maximum pixel value within the specified extent
    ///////////////////////////////////////////////////////////////////////
    double GetMaxPixValY() ;
    ///////////////////////////////////////////////////////////////////////
    /// Get the minimum pixel value within the specified extent of VolumeY
    /// this will trigger the calculation
    /// \return Return the minimum pixel value within the specified extent
    ///////////////////////////////////////////////////////////////////////
    double GetMinPixValY() ;
    ///////////////////////////////////////////////////////////////////////
    /// Get the average pixel value within the specified extent of VolumeX,
    /// this will trigger the calculation
    /// \return Return the average pixel value within the specified extent
    ///////////////////////////////////////////////////////////////////////
    double GetMeanPixValX() ;
    ///////////////////////////////////////////////////////////////////////
    /// Get the average pixel value within the specified extent of VolumeY,
    /// this will trigger the calculation
    /// \return Return the average pixel value within the specified extent
    ///////////////////////////////////////////////////////////////////////
    double GetMeanPixValY() ;
    ///////////////////////////////////////////////////////////////////////
    /// Get the standard deviation of pixel value within the specified extent,
    /// of VolumeX, this will trigger the calculation
    /// \return Return the standard deviation of pixel value within the specified extent
    ///////////////////////////////////////////////////////////////////////
    double GetStandardDeviationX() ;
    ///////////////////////////////////////////////////////////////////////
    /// Get the standard deviation of pixel value within the specified extent,
    /// of VolumeY, this will trigger the calculation
    /// \return Return the standard deviation of pixel value within the specified extent
    ///////////////////////////////////////////////////////////////////////
    double GetStandardDeviationY() ;
    ///////////////////////////////////////////////////////////////////////
    /// Get the total number of pixels within the specified extent
    /// \return Return the total number of pixels within the specified extent
    ///////////////////////////////////////////////////////////////////////
    unsigned long GetTotalPixels() ;
    ///////////////////////////////////////////////////////////////////////
    /// Get histogram statistics, this will trigger the calculation
    /// \return Return the histogram statistics, the array is as large as 
    /// intervalNumX*intervalNumY
    ///////////////////////////////////////////////////////////////////////
    unsigned long* GetStatistics();

    ///////////////////////////////////////////////////////////////////////
    /// Get the modified status of the histogram
    /// \return whether the histogram is modified after last call to 
    /// SetUnmodified()
    ///////////////////////////////////////////////////////////////////////
    bool IsModified();
    ///////////////////////////////////////////////////////////////////////
    /// Set the modified status the false
    ///////////////////////////////////////////////////////////////////////
    void SetUnmodified();

    ///////////////////////////////////////////////////////////////////////
    /// Get the first volume (the X-Axial volume)
    /// \return Return the first volume
    ///////////////////////////////////////////////////////////////////////
    mitkVolume *GetSourceVolumeX() { return m_volumeX;}
    ///////////////////////////////////////////////////////////////////////
    /// Get the second volume (the Y-Axial volume)
    /// \return Return the second volume
    ///////////////////////////////////////////////////////////////////////
    mitkVolume *GetSourceVolumeY() { return m_volumeY;}
    
protected:
    virtual ~mitkHistogram2D();
    void _calculateHist();

    mitkRCPtr<mitkVolume> m_volumeX;
    mitkRCPtr<mitkVolume> m_volumeY;

    int m_chIdxX;
    int m_chIdxY;

    unsigned int m_extentX[6];
    unsigned int m_extentY[6];

    double m_minX;  // range min
    double m_maxX;  // range max
    
    double m_minY;  // range min
    double m_maxY;  // range max

    unsigned int m_intervalNumX; 
    unsigned int m_intervalNumY; 

    bool m_calculated;
    bool m_modified;

    unsigned long* m_statistics;

    double m_MaxPixValX; // min value within extent
    double m_MinPixValX; // max value within extent
    double m_MeanPixValX; 
    double m_StdDevX; 

    double m_MaxPixValY; // min value within extent
    double m_MinPixValY; // max value within extent
    double m_MeanPixValY; 
    double m_StdDevY; 

    unsigned long m_TotalPixels;

};

#endif

