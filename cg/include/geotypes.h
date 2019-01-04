#ifndef __geotypes_h
#define __geotypes_h

template <typename T>
struct _2d_point_type
{
    union
    {
        struct { T x, y; };
        T coord[2];
    };
};

template <typename T>
struct _3d_point_type
{
    union
    {
        struct { T x, y, z; };
        T coord[3];
    };
};

template <typename IndexType, unsigned int indexNum>
struct _face_type
{
    enum { vertNum = indexNum };
    IndexType verts[indexNum];
};

typedef _2d_point_type<float> Point2f;
typedef _2d_point_type<double> Point2d;

typedef _3d_point_type<float> Point3f;
typedef _3d_point_type<double> Point3d;

typedef _face_type<unsigned int, 3> TriangleFace;

#endif