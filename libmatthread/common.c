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
 * @file common.c
 * @author Ekaitz Zarraga <ekaitz.zarraga@gmail.com>
 *
 * @brief Common utilities for matrix_t elements.
 *
 * This file contains generic utilities for matrix_t element manipulation.
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include"common.h"

matrix_t matinit(){
    matrix_t matrix;
    matrix.data=NULL;
    matrix.width=0;
    matrix.height=0;
    return matrix;
}

int matcmp( matrix_t a, matrix_t b ){

    if(a.width != b.width){
        return -1;
    }
    if(a.height != b.height){
        return -1;
    }

    int i;
    for( i=0; i<a.width * a.height ; i++ ){
        if( a.data[i] != b.data[i] ){
            return -1;
        }
    }
    return 0;
}

void matprint( matrix_t matrix ){
    int i,j;
    for( i=0; i < matrix.height; i++){
        for( j=0; j < matrix.width; j++)
            printf("%Lf\t", MATRIX(matrix, i, j));
        putc('\n', stdout);
    }
}

int matalloc(matrix_t * matrix, size_t width, size_t height){
    if( matrix->data != NULL )  //If it's not empty, free it and reallocate.
        matfree(matrix);
    matrix->data=malloc(sizeof(long double) * width * height);
    if(matrix->data==NULL){
       fprintf(stderr, "Unable to allocate data");
       return -1;
    }
    matrix->width=width;
    matrix->height=height;
    return 0;
}

void matfree(matrix_t * matrix){
    free(matrix->data);
    matrix->width=0;
    matrix->height=0;
}

int matcpy(matrix_t * dest, matrix_t * src){

    //First check if size is the same, if it isn't reallocate dest.
    //If size is 0 it's not initialized, don't free.
    if( !(dest->height == src->height && dest->width == src->width) ){
        if( matalloc(dest, src->width, src->height) )
            return -1;
    }

    int i;
    for( i=0; i < dest->width * dest->height; i++){
        dest->data[i] = src->data[i];
    }
    return 0;
}
