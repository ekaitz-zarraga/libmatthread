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
 * @file matrices.c
 * @author Ekaitz Zarraga <ekaitz.zarraga@gmail.com>
 *
 * @brief Utilities for matrix_t elements when used as a matrix.
 *
 * This file contains utilities for matrix_t element manipulation when they
 * are used to contain matrices.
 *
 */
#define _GNU_SOURCE
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>
#include"common.h"
#include"matrices.h"

typedef struct{
    matrix_t * a;
    matrix_t * b;
    matrix_t * c;
    m_pos_t  start_pos;
    size_t pos_count;
    pthread_mutex_t * lock;
} param_t;

matrix_t matmultthreads(matrix_t a, matrix_t b, int thread_count){
    matrix_t c=matinit();
    if(a.width!=b.height){
        fprintf(stderr,"\nSize does not match on multiply\n");
        return c;
    }
    if(matalloc(&c, b.width, a.height))
        return c;

    if(thread_count<1)
        thread_count= c.height * c.width;

    // Thread IDs
    pthread_t * threads;
    threads = malloc(sizeof(pthread_t) * thread_count);
    if(threads==NULL){
        fprintf(stderr, "\nOut of memory, could not allocate thread structures\n");
        return c;
    }
    memset(threads, 0, sizeof(pthread_t) * thread_count);


    // Create parameter array:
    param_t * params;
    params = malloc(sizeof(param_t) * thread_count);
    if(threads==NULL){
        free(threads);
        fprintf(stderr, "\nOut of memory, could not allocate parameter structures\n");
        return c;
    }


    // Create mutex
    pthread_mutex_t general_lock;
    if (pthread_mutex_init(&general_lock, NULL) != 0){
        free(threads);
        free(params);
        fprintf(stderr,"\nMutex intialization failed\n");
        return c;
    }

    // TODO CREATE POSLISTS -> params
    int total_pos= c.width * c.height;
    int extra_pos= total_pos % thread_count; //some threads need to do an extra position because the division might not be integer.
    int pos_per_thread = (total_pos - extra_pos) / thread_count;

    //Create threads
    int i;
    m_pos_t current_pos;
    current_pos.row=0;
    current_pos.col=0;
    for(i=0; i<thread_count; i++){
        params[i].a = &a;
        params[i].b = &b;
        params[i].c = &c;
        params[i].start_pos.row = current_pos.row;
        params[i].start_pos.col = current_pos.col;
        params[i].pos_count = pos_per_thread + ( i<extra_pos ? 1 : 0); // first extra_pos threads need to have an extra_postion
        params[i].lock = &general_lock;

        //Update position for the next thread
        int j;
        for(j=0; j<params[i].pos_count; j++)
            POSITIONINC(current_pos, c.width);

        if(pthread_create( &threads[i], NULL, &mult, &params[i])){
            fprintf(stderr, "\nERROR CREATING THE THREAD\n");
        }
    }

    // Join threads
    for(i=0; i<thread_count; i++){
            pthread_join(threads[i], NULL);
    }
    free(threads);
    free(params);
    return c;
}
void * mult(void * param_pointer){
    double long result;
    param_t *param=(param_t *) param_pointer;
    m_pos_t pos;
    pos.row=param->start_pos.row;
    pos.col=param->start_pos.col;

    fprintf(stderr, "Hola soy el thread\n");
    int j,i;
    for( j=0; j<param->pos_count; j++){
        result=0;
        //sum when multiply left's row by right's col
        for(i=0; i < param->a->width; i++) {
            result += PMATRIX(param->a, pos.row, i) * PMATRIX(param->b, i, pos.col);
        }
        pthread_mutex_lock(param->lock);
        PMATRIX(param->c, pos.row, pos.col) = result;
        pthread_mutex_unlock(param->lock);

        POSITIONINC(pos, param->c->width);
    }
    return NULL;
}
