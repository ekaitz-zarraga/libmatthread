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
 * @file signals.c
 * @author Ekaitz Zarraga <ekaitz.zarraga@gmail.com>
 *
 * @brief Utilities for matrix_t elements when used as a signal.
 *
 * This file contains utilities for matrix_t element manipulation when they
 * are used to contain discrete signals.
 *
 */

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>
#include"common.h"
#include"matrices.h"

matrix_t matmult(matrix_t a, matrix_t b, int threads){
    matrix_t c=matinit();
    if(a.width!=b.height){
        fprintf(stderr,"\nSize does not match on multiply\n");
        return c;
    }
    if(matalloc(&c, b.width, a.height))
        return c;

    // Multiply
    int i, j, k;
    for(i=0; i<a.height; i++){
        for(j=0; j<b.width; j++){
            for(k=0; k<a.width; k++){
                MATRIX(c,i,j) += MATRIX(a,i,k)*MATRIX(b,k,j);
            }
        }
    }

    return c;
}
