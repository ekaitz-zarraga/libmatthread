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
 * @file matrices.h
 * @author Ekaitz Zarraga <ekaitz.zarraga@gmail.com>
 *
 * @brief Utilities for matrix_t elements when used as a matrix.
 *
 * This file contains utilities for matrix_t element manipulation when they
 * are used as matrixes.
 *
 */
#ifndef MATTHREAD_MATRIXH
#define MATTHREAD_MATRIXH

/**
 * @brief Multiply matrixes in multiple threads
 * @param[in] a,b matrices to multiply
 * @param[in] threads number of threads to create, if 0 or negative use one per position.
 * @returns matrix_t containing the multiplication. If error, empty matrix.
 */
matrix_t matmultthreads(matrix_t a, matrix_t b, int thread_count);
void * mult(void * param_pointer);
#endif //MATTHREAD_MATRIXH
