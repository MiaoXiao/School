/**
 * minigl.cpp
 * -------------------------------
 * Implement miniGL here.
 * Do not use any additional files
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <stack>
#include "minigl.h"

using namespace std;


//triangles or quads
int CURRMODE = -1;
//holds matrixes for transofmrations
stack<vector<MGLfloat> > MATRIX;
//current color
MGLpixel CURRCOLOR;

//converts a mglfloat *matrix to its vector counterpart
vector<MGLfloat> convertMGLfloattoVector(const MGLfloat *matrix)
{
	vector<MGLfloat> v;
	for (unsigned i = 0; i < 4; ++i)
	{
		for (unsigned j = 0; j < 4; ++j)
		{
			v.push_back(matrix[i + (j * 4)]);
		}
	}
	return v;
}

//return identity matrix
vector<MGLfloat> returnIdentityMatrix()
{
	vector<MGLfloat> v;
	//first row
	v.push_back(1);
	v.push_back(0);
	v.push_back(0);
	v.push_back(0);
	//second row
	v.push_back(0);
	v.push_back(1);
	v.push_back(0);
	v.push_back(0);
	//third row
	v.push_back(0);
	v.push_back(0);
	v.push_back(1);
	v.push_back(0);
	//fourth row
	v.push_back(0);
	v.push_back(0);
	v.push_back(0);
	v.push_back(1);
	return v;
}

/**
 * Standard macro to report errors
 */
inline void MGL_ERROR(const char* description) {
    printf("%s\n", description);
    exit(1);
}

/**
 * Read pixel data starting with the pixel at coordinates
 * (0, 0), up to (width,  height), into the array
 * pointed to by data.  The boundaries are lower-inclusive,
 * that is, a call with width = height = 1 would just read
 * the pixel at (0, 0).
 *
 * Rasterization and z-buffering should be performed when
 * this function is called, so that the data array is filled
 * with the actual pixel values that should be displayed on
 * the two-dimensional screen.
 */
void mglReadPixels(MGLsize width,
                   MGLsize height,
                   MGLpixel *data)
{
	for (unsigned int i = 0; i != '\0'; ++i)
	{
		MGL_SET_RED(0, 255);
		data[i] = MGL_GET_RED(255);
		cout << "reading " << i << endl;
	}
}

/**
 * Start specifying the vertices for a group of primitives,
 * whose type is specified by the given mode.
 */
void mglBegin(MGLpoly_mode mode)
{
    CURRMODE = mode;
}

/**
 * Stop specifying the vertices for a group of primitives.
 */
void mglEnd()
{
    CURRMODE = -1;
}

/**
 * Specify a two-dimensional vertex; the x- and y-coordinates
 * are explicitly specified, while the z-coordinate is assumed
 * to be zero.  Must appear between calls to mglBegin() and
 * mglEnd().
 */
void mglVertex2(MGLfloat x,
                MGLfloat y)
{
	if (CURRMODE != -1)
	{
		
	}
}

/**
 * Specify a three-dimensional vertex.  Must appear between
 * calls to mglBegin() and mglEnd().
 */
void mglVertex3(MGLfloat x,
                MGLfloat y,
                MGLfloat z)
{
	if (CURRMODE != -1)
	{
		
	}
}

/**
 * Set the current matrix mode (modelview or projection).
 */
void mglMatrixMode(MGLmatrix_mode mode)
{
	if (mode == 0)
	{
		
	}
	else if (mode == 1)
	{
		
	}
}

/**
 * Push a copy of the current matrix onto the stack for the
 * current matrix mode.
 */
void mglPushMatrix()
{
	//check if stack is not empty before pushing copy of top into matrix again
	if (!MATRIX.empty())
	{
		MATRIX.push(MATRIX.top());
	}
	else cerr << "Cannot push matrix, matrix empty." << endl;
}

/**
 * Pop the top matrix from the stack for the current matrix
 * mode.
 */
void mglPopMatrix()
{
	//only use this func to pop if stack is not empty
	MATRIX.pop();
}

/**
 * Replace the current matrix with the identity.
 */
void mglLoadIdentity()
{
	if (!MATRIX.empty()) mglPopMatrix();
	MATRIX.push(returnIdentityMatrix());
}

/**
 * Replace the current matrix with an arbitrary 4x4 matrix,
 * specified in column-major order.  That is, the matrix
 * is stored as:
 *
 *   ( a0  a4  a8  a12 )
 *   ( a1  a5  a9  a13 )
 *   ( a2  a6  a10 a14 )
 *   ( a3  a7  a11 a15 )
 *
 * where ai is the i'th entry of the array.
 */
void mglLoadMatrix(const MGLfloat *matrix)
{
	if (!MATRIX.empty())
	{
		mglPopMatrix();
		MATRIX.push(convertMGLfloattoVector(matrix));
	}
}

/**
 * Multiply the current matrix by an arbitrary 4x4 matrix,
 * specified in column-major order.  That is, the matrix
 * is stored as:
 *
 *   ( a0  a4  a8  a12 )
 *   ( a1  a5  a9  a13 )
 *   ( a2  a6  a10 a14 )
 *   ( a3  a7  a11 a15 )
 *
 * where ai is the i'th entry of the array.
 */
void mglMultMatrix(const MGLfloat *matrix)
{
	vector<MGLfloat> v;
	vector<MGLfloat> current;
	vector<MGLfloat> top;
	if (!MATRIX.empty()) 
	{
		top = MATRIX.top();
		mglPopMatrix();
		
		current = convertMGLfloattoVector(matrix);
		
		//now use crossproduct to multiply the vectors
		for (unsigned int i = 0; i < 4; ++i)
		{
			int row = 0;
			int column = 0;
			int componentsum = 0;
			for (unsigned int j = 0; j < 4; ++j)
			{
				componentsum += (top[row + i] * current[column + i]);
				column += 4;
				row++;
			}
		}
	}
}

/**
 * Multiply the current matrix by the translation matrix
 * for the translation vector given by (x, y, z).
 */
void mglTranslate(MGLfloat x,
                  MGLfloat y,
                  MGLfloat z)
{
}

/**
 * Multiply the current matrix by the rotation matrix
 * for a rotation of (angle) degrees about the vector
 * from the origin to the point (x, y, z).
 */
void mglRotate(MGLfloat angle,
               MGLfloat x,
               MGLfloat y,
               MGLfloat z)
{
}

/**
 * Multiply the current matrix by the scale matrix
 * for the given scale factors.
 */
void mglScale(MGLfloat x,
              MGLfloat y,
              MGLfloat z)
{
}

/**
 * Multiply the current matrix by the perspective matrix
 * with the given clipping plane coordinates.
 */
void mglFrustum(MGLfloat left,
                MGLfloat right,
                MGLfloat bottom,
                MGLfloat top,
                MGLfloat near,
                MGLfloat far)
{
}

/**
 * Multiply the current matrix by the orthographic matrix
 * with the given clipping plane coordinates.
 */
void mglOrtho(MGLfloat left,
              MGLfloat right,
              MGLfloat bottom,
              MGLfloat top,
              MGLfloat near,
              MGLfloat far)
{
}

/**
 * Set the current color for drawn shapes.
 */
void mglColor(MGLbyte red,
              MGLbyte green,
              MGLbyte blue)
{
	MGL_SET_RED(CURRCOLOR, red);
	MGL_SET_GREEN(CURRCOLOR, green);
	MGL_SET_BLUE(CURRCOLOR, blue);
}
