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

//Standard matrices.
#define IDENTITY(i, j) ((i == j) ? 1 : 0)
#define UPTRIANGLE(i, j) ((i <= j) ? 1 : 0)
#define DOWNTRIANGLE(i, j) ((i >= j) ? 1 : 0)

//A macro to emulate a 2d array. Works just like matrix[row][col].
#define PMATRIX(matrix, row, col) matrix->data[row * matrix->width + col]
#define MATRIX(matrix, row, col) matrix.data[row * matrix.width + col]


typedef struct{
    long double * data;
    size_t height;
    size_t width;
} matrix_t;

typedef struct {
        size_t row;
        size_t col;
} m_pos_t;
#define POSITIONINC(position, width) position.col==width-1 ? position.row++, position.col=0 : position.col++;
#define PPOSITIONINC(position, width) position->col==width-1 ? position->row++, position->col=0 : position->col++;

/**
 * @brief initialize matrix_t element with 0s.
 * Call it when creating new matrix_t, it initializes values.
 * @returns start value for matrix_t element.
 * @see matalloc
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
 * @see matfree,matinit
 */
int matalloc(matrix_t * matrix, size_t width, size_t height);

/**
 * @brief Free allocated matrix_t
 * @param[in] matrix matrix_t element to free
 * @see matalloc
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
 * @returns the joined matrix_t element, needs to be freed later
 * @see matjoinv
 */
matrix_t matjoinh( matrix_t first, matrix_t second );

/**
 * @brief Join two matrixes vertically
 * @param[in] first which matrix goes first
 * @param[in] second which goes second
 * @returns the joined matrix_t element, needs to be freed later
 * @see matjoinh
 */
matrix_t matjoinv( matrix_t first, matrix_t second );

/**
 * @brief Swap columns
 * @param[in] matrix,col1,col2 matrix and columns to swap
 * @returns -1 if columns out of matrix, 0 if ok.
 * @see matswaprow
 */
int matswapcol(matrix_t matrix, size_t col1, size_t col2);

/**
 * @brief Swap rows
 * @param[in] matrix,row1,row2 matrix and columns to swap
 * @returns -1 if rows out of matrix, 0 if ok.
 * @see matswapcol
 */
int matswaprow(matrix_t matrix, size_t row1, size_t row2);

/**
 * @brief Matrix transpose
 * @param[in] matrix matrix to transpose
 */
void mattranspose( matrix_t * matrix );

/**
 * @brief Create matrix_t full of zeros
 * @param[in] width,height Size of the new matrix_t
 * @returns allocated matrix_t element full of ones, needs to be freed later.
 * @see matzeros
 */
matrix_t matones(size_t width, size_t height);

/**
 * @brief Create matrix_t full of ones
 * @param[in] width,height Size of the new matrix_t
 * @returns allocated matrix_t element full of zeros, needs to be freed later.
 * @see matones
 */
matrix_t matzeros(size_t width, size_t height);

/**
 * @brief Multiply matrix_t with a scalar, element by element
 * @param[in] matrix matrix_t to multiply
 * @param[in] scalar scalar to multiply
 */
void matmultscalar(matrix_t matrix, long double scalar);

/**
 * @brief Get matrix_t elements row
 * @param[in] matrix element to take row from
 * @param[in] row row position
 * @returns allocated matrix_t element with with the content of the row, needs to be freed later.
 * @see matgetcol
 */
matrix_t matgetrow(matrix_t matrix, size_t row);

/**
 * @brief Get matrix_t elements column
 * @param[in] matrix element to take column from
 * @param[in] col column position
 * @returns allocated matrix_t element with with the content of the col, needs to be freed later.
 * @see matgetrow
 */
matrix_t matgetcol(matrix_t matrix, size_t col);

/**
 * @brief Set matrix_t elements row
 * @param[in] matrix set row here
 * @param[in] matrow values
 * @param[in] row row position to overwrite
 * @returns -1 if error, 0 if ok.
 * @see matsetcol,matgetrow
 */
int matsetrow(matrix_t matrix, matrix_t matrow, size_t row);

/**
 * @brief Set matrix_t elements column
 * @param[in] matrix set column here
 * @param[in] matcol values
 * @param[in] col column position to overwrite
 * @returns -1 if error, 0 if ok.
 * @see matsetrow,matgetcol
 */
int matsetcol(matrix_t matrix, matrix_t matcol, size_t col);

/**
 * @brief increment a in b, element by element
 * @param[in] a,b matrix_t elements to add
 * @param[out] a set the result in a.
 * @returns -1 if error, 0 if ok.
 * @see matadd
 */
int matinc(matrix_t a, matrix_t b);

/**
 * @brief add a and b, element by element
 * @param[in] a,b matrix_t elements to add
 * @returns a+b need to be freed later
 * @see matinc
 */
matrix_t matadd(matrix_t a, matrix_t b);

#endif //MATTHREAD_COMMONH
