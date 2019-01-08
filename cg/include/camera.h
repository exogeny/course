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

#ifndef __camera_h
#define __camera_h

#include "glinc.h"
#include "matrix.h"

template <typename T> class Camera
{
public:
	Camera()
	{
		view.IdentityMatrix();
		inv_view.IdentityMatrix();
		proj.IdentityMatrix();
		inv_proj.IdentityMatrix();

		//para_proj = true;
	}

	Matrix<T> const & GetViewMatrix() const { return view; }
	Matrix<T> & GetViewMatrix() { return view; }

	Matrix<T> const & GetInverseOfViewMatrix() const { return inv_view; }
	Matrix<T> & GetInverseOfViewMatrix() { return inv_view; }

	Matrix<T> const & GetProjectionMatrix() const { return proj; }
	Matrix<T> & GetProjectionMatrix() { return proj; }

	Matrix<T> const & GetInverseOfProjectionMatrix() const { return inv_proj; }
	Matrix<T> & GetInverseOfProjectionMatrix() { return inv_proj; }

	bool IsParallelProjection() { return para_proj; }

	void LookAt(T const eyex, T const eyey, T const eyez,
		T const centerx, T const centery, T const centerz,
		T const upx, T const upy, T const upz)
	{
		//-z axis
		Vector<T> minusz(centerx - eyex, centery - eyey, centerz - eyez);
		Vector<T> x;  //x axis
		Vector<T> y(upx, upy, upz);    //(y axis)    

		/* Viewing matrix
		x0		x1			x2			-eye Dot x
		y0		y1			y2			-eye Dot y
		z0		z1			z2			-eye Dot z
		0		0			0			1
		*/

		/* Inverse of viewing matrix
		x0		y0			z0			eyex
		x1		y1			z1			eyey
		x2		y2			z2			eyez
		0		0			0			1
		*/

		minusz.Normalize();

		// x = -z cross y
		x = minusz % y;
		x.Normalize();

		// Recompute y: y = x cross -z
		y = x % minusz;

		view.IdentityMatrix();	
		view.ele[0] = x.ele[0];
		view.ele[1] = y.ele[0];
		view.ele[2] = -minusz.ele[0];
		view.ele[4] = x.ele[1];
		view.ele[5] = y.ele[1];
		view.ele[6] = -minusz.ele[1];
		view.ele[8] = x.ele[2];
		view.ele[9] = y.ele[2];
		view.ele[10] = -minusz.ele[2];    
		view.Translate(-eyex, -eyey, -eyez);

		inv_view.ele[0] = x.ele[0];
		inv_view.ele[1] = x.ele[1];
		inv_view.ele[2] = x.ele[2];
		inv_view.ele[3] = T(0);

		inv_view.ele[4] = y.ele[0];
		inv_view.ele[5] = y.ele[1];
		inv_view.ele[6] = y.ele[2];
		inv_view.ele[7] = T(0);

		inv_view.ele[8] = -minusz.ele[0];
		inv_view.ele[9] = -minusz.ele[1];
		inv_view.ele[10] = -minusz.ele[2];
		inv_view.ele[11] = T(0);

		inv_view.ele[12] = eyex;
		inv_view.ele[13] = eyey;
		inv_view.ele[14] = eyez;
		inv_view.ele[15] = T(1);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		this->_glMultMatrix(view);
	}

	void Ortho(T const left, T const right, T const bottom, T const top, T const znear, T const zfar)
	{
		T rl = T(1) / (right - left);
		T tb = T(1) / (top - bottom);
		T fn = T(1) / (zfar - znear);

		/* Projection matrix
		2/(r-l)	0			0			-(r+l)/(r-l)
		0		2/(t-b)		0			-(t+b)/(t-b)
		0		0			-2/(f-n)	-(f+n)/(f-n)
		0		0			0			1
		*/

		/* Inverse of projection matrix
		(r-l)/2	0			0			(r+l)/2
		0		(t-b)/2		0			(t+b)/2
		0		0			(f-n)/(-2)	-(f+n)/2
		0		0			0			1
		*/

		proj.ele[0] = T(2) * rl;
		proj.ele[1] = T(0);
		proj.ele[2] = T(0);
		proj.ele[3] = T(0);

		proj.ele[4] = T(0);
		proj.ele[5] = T(2) * tb;
		proj.ele[6] = T(0);
		proj.ele[7] = T(0);

		proj.ele[8] = T(0);
		proj.ele[9] = T(0);
		proj.ele[10] = T(-2) * fn;
		proj.ele[11] = T(0);

		proj.ele[12] = -(right + left) * rl;
		proj.ele[13] = -(top + bottom) * tb;
		proj.ele[14] = -(zfar + znear) * fn;
		proj.ele[15] = T(1);

		inv_proj.ele[0] = (right - left) * T(0.5);
		inv_proj.ele[1] = T(0);
		inv_proj.ele[2] = T(0);
		inv_proj.ele[3] = T(0);

		inv_proj.ele[4] = T(0);
		inv_proj.ele[5] = (top - bottom) * T(0.5);
		inv_proj.ele[6] = T(0);
		inv_proj.ele[7] = T(0);

		inv_proj.ele[8] = T(0);
		inv_proj.ele[9] = T(0);
		inv_proj.ele[10] = (znear - zfar) * T(0.5);
		inv_proj.ele[11] = T(0);

		inv_proj.ele[12] = (right + left) * T(0.5);
		inv_proj.ele[13] = (top   + bottom) * T(0.5);
		inv_proj.ele[14] = (zfar + znear) * (-T(0.5));
		inv_proj.ele[15] = T(1);

		para_proj = true;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		this->_glMultMatrix(proj);
	}

	void Frustum(T const left, T const right, T const bottom, T const top, T const znear, T const zfar)
	{
		T rl = T(1) / (right - left);
		T tb = T(1) / (top - bottom);
		T fn = T(1) / (zfar - znear);

		/* Projection matrix
		2n/(r-l)	0			(r+l)/(r-l)			0
		0		2n/(t-b)	(t+b)/(t-b)			0
		0		0			-(f+n)/(f-n)		-2fn/(f-n)
		0		0			-1					0
		*/

		/* Inverse of projection matrix
		(r-l)/2n	0			0					(r+l)/2n
		0		(t-b)/2n	0					(t+b)/2n
		0		0			0					-1
		0		0			-(f-n)/2fn			(f+n)/2fn
		*/

		proj.ele[0] = T(2) * znear * rl;
		proj.ele[1] = T(0);
		proj.ele[2] = T(0);
		proj.ele[3] = T(0);

		proj.ele[4] = T(0);
		proj.ele[5] = T(2) * znear * tb;
		proj.ele[6] = T(0);
		proj.ele[7] = T(0);

		proj.ele[8] = (right + left) * rl;
		proj.ele[9] = (top   + bottom) * tb;
		proj.ele[10] = -(zfar + znear) * fn;
		proj.ele[11] = -T(1);

		proj.ele[12] = T(0);
		proj.ele[13] = T(0);
		proj.ele[14] = T(-2) * zfar * znear * fn;
		proj.ele[15] = T(0);

		T inv2n  = 0.5f / znear;
		T inv2fn = inv2n / zfar; 
		inv_proj.ele[0] = (right - left) * inv2n;
		inv_proj.ele[1] = T(0);
		inv_proj.ele[2] = T(0);
		inv_proj.ele[3] = T(0);

		inv_proj.ele[4] = T(0);
		inv_proj.ele[5] = (top - bottom) * inv2n;
		inv_proj.ele[6] = T(0);
		inv_proj.ele[7] = T(0);

		inv_proj.ele[8] = T(0);
		inv_proj.ele[9] = T(0);
		inv_proj.ele[10] = T(0);
		inv_proj.ele[11] = (znear - zfar) * inv2fn;

		inv_proj.ele[12] = (right + left) * inv2n;
		inv_proj.ele[13] = (top   + bottom) * inv2n;
		inv_proj.ele[14] = T(-1);
		inv_proj.ele[15] = (zfar + znear) * inv2fn;

		para_proj = false;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		this->_glMultMatrix(proj);
	}

	void Perspective(T const fovy, T const aspect, T const znear, T const zfar)
	{
		T tanangle = tan(fovy*T(0.00872664625997)); //fovy/2 * PI / 180	
		T cotangle = T(1) / tanangle;
		T fn = T(1) / (zfar - znear);

		/* Projection matrix
		ctg(fovy/2)/aspect	0				0				0
		0					ctg(fovy/2)		0				0
		0					0				-(f+n)/(f-n)	-2fn/(f-n)
		0					0				-1					0
		*/

		/* Inverse of projection matrix
		aspect/ctg(fovy/2)	0				0				0
		0					1/ctg(fovy/2)	0				0
		0					0				0				-1
		0					0				-(f-n)/2fn	    (f+n)/2fn
		*/

		proj.ele[0] = cotangle / aspect;
		proj.ele[1] = T(0);
		proj.ele[2] = T(0);
		proj.ele[3] = T(0);

		proj.ele[4] = T(0);
		proj.ele[5] = cotangle;
		proj.ele[6] = T(0);
		proj.ele[7] = T(0);

		proj.ele[8] = T(0);
		proj.ele[9] = T(0);
		proj.ele[10] = -(zfar + znear) * fn;
		proj.ele[11] = T(-1);

		proj.ele[12] = T(0);
		proj.ele[13] = T(0);
		proj.ele[14] = T(-2) * zfar * znear * fn;
		proj.ele[15] = T(0);

		T inv2fn = T(0.5)/(znear*zfar);
		inv_proj.ele[0] = aspect * tanangle;
		inv_proj.ele[1] = T(0);
		inv_proj.ele[2] = T(0);
		inv_proj.ele[3] = T(0);

		inv_proj.ele[4] = T(0);
		inv_proj.ele[5] = tanangle;
		inv_proj.ele[6] = T(0);
		inv_proj.ele[7] = T(0);

		inv_proj.ele[8] = T(0);
		inv_proj.ele[9] = T(0);
		inv_proj.ele[10] = T(0);
		inv_proj.ele[11] = (znear - zfar) * inv2fn;

		inv_proj.ele[12] = T(0);
		inv_proj.ele[13] = T(0);
		inv_proj.ele[14] = T(-1);
		inv_proj.ele[15] = (zfar + znear) * inv2fn;

		para_proj = false;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		this->_glMultMatrix(proj);
	}

	void WorldToCamera(Vector<T> const &world_point, Vector<T> &camera_point)
	{
		camera_point = view * world_point;
	}

	void CameraToView(Vector<T> const &camera_point, Vector<T> &view_point)
	{
		view_point = proj * camera_point;
		if (!para_proj)
		{
			view_point *= (T(1) / view_point.ele[3]);
			view_point.ele[3] = T(1);
		}
	}

	void WorldToView(Vector<T> const &world_point, Vector<T> &view_point)
	{
		view_point = view * world_point;
		view_point *= proj;
		if (!para_proj)
		{
			view_point *= (T(1) / view_point.ele[3]);
			view_point.ele[3] = T(1);
		}
	}

	void ViewToCamera(Vector<T> const &view_point, Vector<T> &camera_point)
	{
		camera_point = inv_proj * view_point;
		if (!para_proj)
		{
			camera_point *= (T(1) / camera_point.ele[3]);
			camera_point.ele[3] = T(1);
		}
	}

	void CameraToWorld(Vector<T> const &camera_point, Vector<T> &world_point)
	{
		world_point = inv_view * camera_point;
	}

	void ViewToWorld(Vector<T> const &view_point, Vector<T> &world_point)
	{
		world_point = inv_proj * view_point;
		if (!para_proj)
		{
			world_point *= (T(1) / world_point.ele[3]);
			world_point.ele[3] = T(1);
		}
		world_point *= inv_view;
	}


protected:
	void _glMultMatrix(Matrix<T> &mat);

	Matrix<T> view;
	Matrix<T> proj;
	Matrix<T> inv_view;
	Matrix<T> inv_proj;

	bool para_proj;

};

template <> void Camera<float>::_glMultMatrix(Matrix<float> &mat)
{
	glMultMatrixf(mat);
}

template <> void Camera<double>::_glMultMatrix(Matrix<double> &mat)
{
	glMultMatrixd(mat);
}

typedef Camera<float> Cameraf;
typedef Camera<double> Camerad;

#endif
