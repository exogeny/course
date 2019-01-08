/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/




#ifndef __mitkVolumeCropFilter_h
#define __mitkVolumeCropFilter_h

#include "mitkVolumeToVolumeFilter.h"


/// mitkVolumeCropFilter - A concrete Filter class to crop a volume
///////////////////////////////////////////////////////////////////////////
/// mitkVolumeCropFilter is a concrete filter class which inherits from 
/// mitkVolumeToVolumeFilter to cut out a given volume.
/// This filter needs a volume input and generates a volume output.
/// So you should first input a volume using public member functin SetInput(),
/// then you should set crop parameters using 
/// SetCropPosition(int xbeginp, int ybeginp, int zbeginp, int xendp, int yendp, int zendp),
/// (xbeginp, ybeginp, zbeginp) represents one vertex of the needed crop volume, 
/// (xendp, yendp, zendp) represents the diagonal vertexes of the needed crop volume. 
/// So you only need to set any pair coordinates of the four diagonal vertexs of
/// the needed crop volume. You can also use 
/// SetCropRegion(int xbeginp, int ybeginp, int zbeginp, int xlength, int ylength, int zlength ),
/// (xbeginp, ybeginp, zbeginp) represents one vertex of the needed crop volume, 
/// xlength, ylength, zlength represents 3 corresponding lengths from this vertex to the diagonal one. 
/// The length can be positive or negative but no zero.
/// Two examples using mitkResizeFilter are given below. \n
/// Example 1: If you want to crop volume using SetCropPosition()  
/// the code snippet is:
/// \code
/// mitkVolumeCropFilter *filter = new mitkVolumeCropFilter;
/// filter->SetInput(inVolume);
/// filter->SetCropPosition(xbeginp,ybeginp,zbeginp,xendp,yendp,zendp);
/// if (filter->Run())
/// {
///       mitkVolume *outVolume = filter->GetOutput(); 
///       Using  outVolume...
/// } 
/// \endcode
/// Example 2: If you want to crop volume using SetCropRegion()  
/// the code snippet is:
/// \code
/// mitkResizeFilter *filter = new mitkResizeFilter;
/// filter->SetInput(InVolume);
/// filter->SetCropRegion(xbeginp,ybeginp,zbeginp,xlength,ylength,zlength);
/// if (filter->Run())
/// {
///     mitkVolume * outVolume = filter->GetOutput();
///      Using  outVolume...
/// }
/// \endcode
/// \note The cropping volume must be valid ,that is,
///       the specified cropping volume must overlap with the original volume.
class MITK_COMMON_API mitkVolumeCropFilter : public mitkVolumeToVolumeFilter
{
public:
    MITK_TYPE(mitkVolumeCropFilter, mitkVolumeToVolumeFilter)

    virtual void PrintSelf(ostream &os);

    mitkVolumeCropFilter(); 

    ///////////////////////////////////////////////////////////////////////////
    /// Set crop parameters using a pair of diagonal vertexes.
    /// The vertex coordinate can be out of the definition area(0 ~ width-1,0 ~ height-1,0 ~ imagenember-1).
    /// \param xbeginp The x coordinate of one vertex(corresponding to the (x+1) column pixel in width dimension)
    /// \param ybeginp The y coordinate of one vertex(corresponding to the (y+1) row pixel in height dimension)
    /// \param zbeginp The z coordinate of one vertex(corresponding to the (z+1) vertical pixel in image number dimension)
    /// \param xendp The x coordinate of the other vertex(corresponding to the (x+1) column pixel in width dimension)
    /// \param yendp The y coordinate of the other vertex(corresponding to the (y+1) row pixel in height dimension)
    /// \param zendp The z coordinate of the other vertex(corresponding to the (z+1) vertical pixel in image number dimension)
    /////////////////////////////////////////////////////////////////////////// 
    void SetCropPosition(int xbeginp,int ybeginp,int zbeginp,int xendp,int yendp,int zendp);

    ///////////////////////////////////////////////////////////////////////////
    /// Set crop parameters using one vertex and the length from this vertex to the diagonal one .
    /// The vertex coordinate can be out of the definition area(0 ~ width-1,0 ~ height-1,0 ~ imagenember-1).
    /// And the length can be positive or negative.
    /// \param xbeginp The x coordinate of one vertex(corresponding to the (x+1) column pixel in width dimension)
    /// \param ybeginp The y coordinate of one vertex(corresponding to the (y+1) row pixel in height dimension)
    /// \param zbeginp The z coordinate of one vertex(corresponding to the (z+1) vertical pixel in image number dimension)
    /// \param xlength The distance from this vertex to the other in x axis(has xlength pixel units )
    /// \param ylength The distance from this vertex to the other in y axis(has ylength pixel units )
    /// \param zlength The distance from this vertex to the other in z axis(has zlength pixel units )
    /////////////////////////////////////////////////////////////////////////// 
    void SetCropRegion(int xbeginp,int ybeginp,int zbeginp,int xlength,int ylength,int zlength );

protected:
    virtual ~mitkVolumeCropFilter();
    virtual bool Execute();

    int m_XBeginPoint, m_YBeginPoint,m_ZBeginPoint;
    int m_XLength,m_YLength,m_ZLength;
    bool flag;
//  int m_InDataNumberOfChannel;
//  float m_InDataSpacings[3];
//  int m_InDataIncrement[3];
//  int m_OutDataIncrement[3];
//  int m_InDataDataType;

private:
    mitkVolumeCropFilter(const mitkVolumeCropFilter&);
    void operator = (const mitkVolumeCropFilter&);

};


//#define DEFINED_mitkVolumeCropFilter



#endif

