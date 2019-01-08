/*=========================================================================

  Program:   Medical Imaging Toolkit
  Date:      $Date: 2012-1-6 14:00:00 +0800$
  Version:   $Version: 2.3.3 $
  Copyright: MIPG, Institute of Automation, Chinese Academy of Sciences


=========================================================================*/



#ifndef __mitkNeighborhood_h
#define __mitkNeighborhood_h

#include "mitkCommonIncludes.h"
#include "mitk_nl/mitk_nl_vector.h"
#include <vector>
#include <stdlib.h>
#include <string.h>

/** \class mitkNeighborhood
* \brief A light-weight container object for storing an N-dimensional
* neighborhood of values.
*
* A mitkNeighborhood has an N-dimensional \em radius.  The radius is defined
* separately for each dimension as the number of pixels that the neighborhood
* extends outward from the center pixel.  For example, a 2D Neighborhood
* object with a radius of 2x3 has sides of length 5x7.  Neighborhood objects
* always have an unambiguous center because their side lengths are always odd.
*
*/
//  [8/18/2010 Xiuli Li]

class MITK_COMMON_API mitkNeighborhood
{
public:
    /** Standard class typedefs. */
    typedef mitkNeighborhood Self;

    typedef mitk_nl_vector<int> VectorIndexType;
    typedef mitk_nl_vector<VectorIndexType> OffsetType;

    mitkNeighborhood();
    mitkNeighborhood(unsigned int dimension);

    /** Default constructor. */
    ~mitkNeighborhood() {}

    /** Copy constructor. */
    mitkNeighborhood(const Self& other);

    /** Assignment operator. */
    void operator=(const Self& other);

    /** Comparison operator. */
    /*bool
        operator==(const Self& other) const
    {
        return ((m_Radius == other.m_Radius) &&
            (m_Size   == other.m_Size) &&
            (m_OffsetTable == other.m_OffsetTable));
    }*/

    /** Not Equal operator. */
    /*bool operator!=(const Self& other) const
    {
        return ((m_Radius != other.m_Radius) ||
            (m_Size   != other.m_Size) ||
            (m_OffsetTable != other.m_OffsetTable));
    }*/

    ///////////////////////////////////////////////////////////////////////////
    /// Set data type of this Neighborhood. MITK supports various data type.
    /// \param data_type Its valid value and meaning is shown as follows:\n
    /// MITK_CHAR            The data type is char \n
    /// MITK_UNSIGNED_CHAR   The data type is unsigned char \n
    /// MITK_SHORT           The data type is short \n
    /// MITK_UNSIGNED_SHORT  The data type is unsigned short \n
    /// MITK_INT             The data type is int \n
    /// MITK_UNSIGNED_INT    The data type is unsigned int \n
    /// MITK_LONG            The data type is long \n
    /// MITK_UNSIGNED_LONG   The data type is unsigned long \n
    /// MITK_FLOAT           The data type is float \n
    /// MITK_DOUBLE          The data type is double \n
    ///////////////////////////////////////////////////////////////////////////
    void SetDataType(int data_type);

    ///////////////////////////////////////////////////////////////////////////
    /// Get data type of this Neighborhood. MITK supports various data type.
    /// \return All of the return values and their meaning are shown as follows:\n
    /// MITK_CHAR            The data type is char \n
    /// MITK_UNSIGNED_CHAR   The data type is unsigned char \n
    /// MITK_SHORT           The data type is short \n
    /// MITK_UNSIGNED_SHORT  The data type is unsigned short \n
    /// MITK_INT             The data type is int \n
    /// MITK_UNSIGNED_INT    The data type is unsigned int \n
    /// MITK_LONG            The data type is long \n
    /// MITK_UNSIGNED_LONG   The data type is unsigned long \n
    /// MITK_FLOAT           The data type is float \n
    /// MITK_DOUBLE          The data type is double \n
    ///////////////////////////////////////////////////////////////////////////
    int GetDataType() const { return m_DataType; }

    void SetRadius(VectorIndexType& radius);

    VectorIndexType GetRadius() const { return m_Radius;}

    VectorIndexType GetSize();

    VectorIndexType GetStrideTable();

    OffsetType GetOffsetTable();

//  virtual unsigned int GetNeighborhoodIndex(const OffsetType &) const;

    unsigned int GetCenterNeighborhoodIndex() const
    {
        return  m_OffsetTable.size()/2;
    }
    
protected:
    unsigned int m_Dimension;
    int   m_DataType;

    VectorIndexType m_Radius;
    VectorIndexType m_Size;
    VectorIndexType m_StrideTable;

    VectorIndexType m_Offset;
    OffsetType m_OffsetTable;
private:
};

#endif
