/*
   Copyright (C) 2015  Ekaitz Zarraga <ekaitz.zarraga@gmail.com>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, see <http://www.gnu.org/licenses/>.

*/

/**
 * @file common.h
 * @author Ekaitz Zarraga <ekaitz.zarraga@gmail.com>
 *
 * @brief Common utilities for matrix_t elements.
 *
 * This file contains generic utilities for matrix_t element manipulation.
 *
 */

#ifndef MATTHREAD_COMMONH
#define MATTHREAD_COMMONH

#include<stddef.h>

// MATRICES
//A macro to emulate a 2d array. Works just like matrix[row][col].
#define PMATRIX(matrix, row, col) matrix->data[row + col * matrix->height]
#define MATRIX(matrix, row, col) matrix.data[row + col * matrix.height]

//A macro to emulate a vector or a signal using the matrix_t element.
#define PVECTOR(matrix, pos) matrix->data[pos]
#define VECTOR(matrix, pos) matrix.data[pos]

typedef struct{
    long double * data;
    size_t height;
    size_t width;
} matrix_t;

typedef struct {
        size_t row;
        size_t col;
} m_pos_t;


/**
 * @brief Compare two matrix_t elements.
 * @returns 0 if equal and -1 if not equal.
 * @param[in] a,b matrix_t elements to compare.
 */
int matcmp( matrix_t a, matrix_t b );


/**
 * @brief Prints matrix_t content to stdout.
 * @param[in] matrix matrix_t element to show.
 */
void matprint( matrix_t matrix );

/**
 * @brief Allocate matrix_t element with given size.
 * @param[in] matrix matrix_t element to allocate
 * @param[in] width,height size of matrix to allocate.
 * @returns 0 if ok, -1 if errors.
 */
int matalloc(matrix_t * matrix, size_t width, size_t height);

/**
 * @brief Free allocated matrix_t
 * @param[in] matrix matrix_t element to free
 */
void matfree(matrix_t * matrix);

#endif //MATTHREAD_COMMONH
