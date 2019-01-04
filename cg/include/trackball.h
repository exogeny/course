#ifndef __trackball_h
#define __trackball_h

/// Hacked into C++ from SGI's trackball.h & trackball.cpp
///        ---see copyright at end.

#include "quaternion.h"

unsigned int const RENORMCOUNT = 97;

template <typename T> class TrackBall
{
public:
    TrackBall(T const ballsize = T(0.6)) : ball_size(ballsize), count(0) {};

    void Start(T x, T y)
    {
        last_x = x;
        last_y = y;

        last_quat.Identity();
    }

    void Update(Quaternion<T> q)
    {
        cur_quat = q * cur_quat;
        if (++count > RENORMCOUNT)
        {
            count = 0;
            cur_quat.Normalize();
        }
    }

    void Update(T x, T y)
    {
        Vector<T> a; /* Axis of rotation */
        Vector<T> p1, p2, d;
        T phi;  /* how much to rotate about axis */
        T t;

        //  Might just be able to return here.
        if (last_x == x && last_y == y) 
        {
            /* Zero rotation */
            last_quat.Identity();
            return;
        }

        /*
        * First, figure out z-coordinates for projection of P1 and P2 to
        * deformed sphere
        */
        p1.ele[0] = last_x;
        p1.ele[1] = last_y;
        p1.ele[2] = TrackBall<T>::_projectToSphere(ball_size, last_x, last_y);

        p2.ele[0] = x;
        p2.ele[1] = y;
        p2.ele[2] = TrackBall<T>::_projectToSphere(ball_size, x, y);

        /*
        *  Now, we want the cross product of P1 and P2
        */
        a = p1 % p2;

        /*
        *  Figure out how much to rotate around that axis.
        */
        d = p1 - p2;
        t = d.Length() / (T(2.0) * ball_size);

        /*
        * Avoid problems with out-of-control values...
        */
        if (t > T(1.0)) t = T(1.0);
        if (t < T(-1.0)) t = T(-1.0);
        phi = T(2.0) * asin(t);

        last_quat.AxisRadToQuat(a[0], a[1], a[2], phi);

        last_x = x;
        last_y = y;

        Update(last_quat);
    }

    void BuildRotMatrix(Matrix<T> &mat)
    {
        cur_quat.BuildMatrix(mat);
    }

    Quaternion<T> const& GetCurrentQuat() const { return cur_quat; }
    Quaternion<T> const& GetUpdateQuat() const { return last_quat; }
    //Quaternion<T>& GetCurrentQuat() { return cur_quat; }
    //Quaternion<T>& GetUpdateQuat() { return last_quat; }


private:
    static T _projectToSphere(T r, T x, T y)
    {
        T d, z;

        d = x*x + y*y;
        if (d < r * r * T(0.5)) // d < r / sqrt(2) --> inside sphere
        {
            z = sqrt(r*r - d);
        }
        else // On hyperbola
        {
            z = T(0.5) * r * r / sqrt(d);
        }

        return z;
    }

    T ball_size;
    unsigned int count;

    Quaternion<T> cur_quat;
    Quaternion<T> last_quat;

    T last_x;
    T last_y;
};

typedef TrackBall<float> TrackBallf;
typedef TrackBall<double> TrackBalld;

/*
 * (c) Copyright 1993, 1994, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 * Permission to use, copy, modify, and distribute this software for
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission.
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * US Government Users Restricted Rights
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 *
 * OpenGL(TM) is a trademark of Silicon Graphics, Inc.
 */

#endif
