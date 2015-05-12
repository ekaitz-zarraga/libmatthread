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
#include"signals.h"


matrix_t convolution(matrix_t f, matrix_t g){

    int n, m;
    matrix_t fg;
    fg.height=1;
    fg.width=f.width+g.width-1;
    if( matalloc( &fg, fg.width, fg.height) ){
        fg.height=0;
        fg.width=0;
        return fg;
    }
    memset(fg.data, 0, sizeof(long double) * fg.width);

    for (n=0; n < fg.width; n++){
        for(m=0; m < g.width; m++){
            if(n-m>=0 && n-m<f.width)
                fg.data[n]+=f.data[n-m]*g.data[m];
        }
    }

    return fg;
}
