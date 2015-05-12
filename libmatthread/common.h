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
 * @brief initialize matrix_t element with 0s.
 * @returns start value for matrix_t element.
 * Call it when creating new matrix_t, it initializes values.
 */
matrix_t matinit();

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

/**
 * @brief Copy two matrix_t elements
 * @param src,dest Copy src in dest
 * @returns 0 if ok, -1 if error
 */
int matcpy(matrix_t * dest, matrix_t * src);

/**
 * @brief Join two matrixes horizontally
 * @param[in] first which matrix goes first
 * @param[in] second which goes second
 * @returns the joined matrix
 */
matrix_t matjoinh( matrix_t first, matrix_t second );

/**
 * @brief Join two matrixes vertically
 * @param[in] first which matrix goes first
 * @param[in] second which goes second
 * @returns the joined matrix
 */
matrix_t matjoinv( matrix_t first, matrix_t second );

/**
 * @brief Swap columns
 * @param[in] matrix,col1,col2 matrix and columns to swap
 * @returns -1 if columns out of matrix, 0 if ok.
 */
int matswapcol(matrix_t matrix, size_t col1, size_t col2);

/**
 * @brief Swap rows
 * @param[in] matrix,row1,row2 matrix and columns to swap
 * @returns -1 if rows out of matrix, 0 if ok.
 */
int matswaprow(matrix_t matrix, size_t row1, size_t row2);

#endif //MATTHREAD_COMMONH
