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
    printf("\nMATRIX: height-> %d width->%d\n",(int) matrix.height, (int)matrix.width);
    for( i=0; i < matrix.height; i++){
        for( j=0; j < matrix.width; j++)
            printf("%Lg\t", MATRIX(matrix, i, j));
        putc('\n', stdout);
    }
}

int matalloc(matrix_t * matrix, size_t width, size_t height){
    if( matrix->data != NULL )  //If it's not empty, free it and reallocate.
        matfree(matrix);
    matrix->data=malloc(sizeof(long double) * width * height);
    if(matrix->data==NULL){
       fprintf(stderr, "\nUnable to allocate data\n");
       return -1;
    }
    matrix->width=width;
    matrix->height=height;
    return 0;
}

void matfree(matrix_t * matrix){
    free(matrix->data);
    matrix->data=NULL;
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

matrix_t matjoinh( matrix_t first, matrix_t second ){
    matrix_t joined = matinit();
    if( first.height !=  second.height){
        fprintf(stderr, "\nMatrix height does not match\n");
        return joined;
    }
    if( matalloc(&joined, first.width + second.width, first.height) )
        return joined;
    int i, j;
    for(i=0; i<joined.height; i++){
        for(j=0; j<joined.width; j++){
            if(j<first.width){
                MATRIX(joined, i, j)= MATRIX(first, i, j);
            }else{
                MATRIX(joined, i, j)= MATRIX(second, i, (j-first.width));
            }
        }
    }
    return joined;
}

matrix_t matjoinv( matrix_t first, matrix_t second ){
    matrix_t joined = matinit();
    if( first.width !=  second.width){
        fprintf(stderr, "\nMatrix width does not match\n");
        return joined;
    }
    if( matalloc(&joined, first.width, first.height+second.height))
        return joined;
    int i,j;
    for(i=0; i<joined.height; i++){
        for(j=0; j<joined.width; j++){
            if(i<first.height){
                MATRIX(joined, i, j)= MATRIX(first, i, j);
            }else{
                MATRIX(joined, i, j)= MATRIX(second, (i-first.height), j);
            }
        }
    }
    return joined;
}

int matswapcol(matrix_t matrix, size_t col1, size_t col2){
    if( col1>=matrix.width || col2>=matrix.width ){
        fprintf(stderr,"\nColumns out of of matrix on column swap\n");
        return -1;
    }
    double long swap;
    int i;
    for( i=0; i<matrix.height; i++ ){
        swap = MATRIX(matrix, i, col1);
        MATRIX(matrix, i, col1) = MATRIX(matrix, i, col2);
        MATRIX(matrix, i, col2) = swap;
    }
    return 0;
}

int matswaprow(matrix_t matrix, size_t row1, size_t row2){
    if( row1>=matrix.height || row2>=matrix.height ){
        fprintf(stderr,"\nRows out of of matrix on row swap\n");
        return -1;
    }
    double long swap;
    int i;
    for( i=0; i<matrix.width; i++ ){
        swap = MATRIX(matrix, row1, i);
        MATRIX(matrix, row1, i) = MATRIX(matrix, row2, i);
        MATRIX(matrix, row2, i) = swap;
    }
    return 0;
}

void mattranspose( matrix_t * matrix ){
    matrix_t transposed=matinit();
    matalloc(&transposed, matrix->height, matrix->width); // invert height-width
    int i,j;
    for( i=0; i<matrix->height; i++){
        for( j=0; j<matrix->width; j++){
            MATRIX(transposed,j,i)=PMATRIX(matrix,i,j);
        }
    }
    matfree(matrix);
    matrix->data=transposed.data;
    matrix->height=transposed.height;
    matrix->width=transposed.width;
}

matrix_t matones(size_t width, size_t height){
    matrix_t ones=matinit();
    if( matalloc(&ones, width, height) )
        return ones;
    int i;
    for(i=0; i<width*height; i++)
        ones.data[i]=1;
    return ones;
}

matrix_t matzeros(size_t width, size_t height){
    matrix_t ones=matinit();
    if( matalloc(&ones, width, height) )
        return ones;
    int i;
    for(i=0; i<width*height; i++)
        ones.data[i]=0;
    return ones;
}

void matmultscalar(matrix_t matrix, long double scalar){
    int i;
    for(i=0; i<matrix.width*matrix.height; i++)
        matrix.data[i]=matrix.data[i]*scalar;
}


matrix_t matgetrow(matrix_t matrix, size_t row){
    matrix_t matrow=matinit();
    if( row >= matrix.height){
        fprintf(stderr,"\nAsking for a row out of matrix, returning uninitialized matrix_t\n");
        return matrow;
    }
    if(matalloc(&matrow, matrix.width, 1))
        return matrow;
    int j;
    for(j=0; j<matrix.width; j++)
        MATRIX(matrow, 0, j)=MATRIX(matrix, row, j);
    return matrow;
}

matrix_t matgetcol(matrix_t matrix, size_t col){
    matrix_t matcol=matinit();
    if( col >= matrix.width){
        fprintf(stderr,"\nAsking for a column out of matrix, returning uninitialized matrix_t\n");
        return matcol;
    }
    if(matalloc(&matcol, 1, matrix.height))
        return matcol;
    int i;
    for(i=0; i<matrix.height; i++)
        MATRIX(matcol, i, 0)=MATRIX(matrix, i, col);
    return matcol;
}

int matsetrow(matrix_t matrix, matrix_t matrow, size_t row){
    if(matrow.height!=1){
        fprintf(stderr, "\nIntroduced row has height!=1\n");
        return -1;
    }
    if(matrow.width!=matrix.width){
        fprintf(stderr, "\nIntroduced row and matrix have different width\n");
        return -1;
    }
    if(row>=matrix.height){
        fprintf(stderr, "\nSetting row out of matrix\n");
        return -1;
    }
    int j;
    for(j=0; j<matrix.width; j++){
        MATRIX(matrix, row, j)=MATRIX(matrow, 0, j);
    }
    return 0;
}

int matsetcol(matrix_t matrix, matrix_t matcol, size_t col){
    if(matcol.width!=1){
        fprintf(stderr, "\nIntroduced col has width!=1\n");
        return -1;
    }
    if(matcol.height!=matrix.height){
        fprintf(stderr, "\nIntroduced row and matrix have different heigth\n");
        return -1;
    }
    if(col>=matrix.width){
        fprintf(stderr, "\nSetting col out of matrix\n");
        return -1;
    }
    int i;
    for(i=0; i<matrix.height; i++){
        MATRIX(matrix, i, col)=MATRIX(matcol, i, 0);
    }
    return 0;
}

int matinc(matrix_t a, matrix_t b){
    if(a.height!=b.height || a.width != b.width){
        fprintf(stderr, "\nMatrix sizes do not match on matadd\n");
        return -1;
    }
    int i;
    for(i=0; i<a.height*a.width; i++)
        a.data[i]=a.data[i]+b.data[i];
    return 0;
}

matrix_t matadd(matrix_t a, matrix_t b){
    matrix_t c=matinit();
    if(matcpy(&c,&a))
        return c;
    matinc(c,b);
    return c;
}
