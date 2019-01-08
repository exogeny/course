/*
-----------------------------------------------------------------------
This source file is part of "cgcourse-examples"
(Examples for Computer Graphics Course of CCCE GUCAS.)
Copyright (C) 2011 Xue Jian (jian.xue.cn@gmail.com)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------
*/

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
