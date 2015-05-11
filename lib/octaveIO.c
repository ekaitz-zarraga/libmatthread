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
 * @file octaveIO.c
 * @author Ekaitz Zarraga <ekaitz.zarraga@gmail.com>
 *
 * @brief Basic Input Output for Octave .mat files.
 *
 * Read/Write functions for Octave .mat files.
 *
 */

#include"octaveIO.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int loadByName(char * fileName, char * name, matrix_t * matrix){
    char read;
    char property[128];
    char value[128];

    FILE *file = fopen(fileName, "r");

    if( file == NULL)
    {
        fprintf(stderr,"There is no file by the name %s Closing program\n", fileName);
        return -1;
    }

    for(read=fgetc(file); EOF!=read; read=fgetc(file)){

        if(read=='#'){
            // Arrived to a comment block -> parse it.
            ungetc(read, file);

            // Check name first:
            if(!fscanf(file, "# %s %s", property, value))
                continue;
            if(strcmp(property,"name:"))
                continue;
            if(strcmp(value, name))
                continue;
            // If name ok, parse other properties:
            while(fscanf(file," # %s %s", property, value)){
                if( !strcmp(property,"type:")){}
                else if( !strcmp(property,"rows:") ){
                    sscanf(value, "%zu", &matrix->height);
                }
                else if( !strcmp(property,"columns:") ){
                    sscanf(value, "%zu", &matrix->width);
                }
            }
            // Content
            //TODO allocate memory and get values
            matrix->data = malloc(sizeof(long double) * (matrix->height) * (matrix->width));
            int i;
            for(i=0; i<( matrix->height * matrix->width ); i++){
                fscanf(file, "%Lf", &matrix->data[i]);
            }
            break;
        }
    }

    fclose(file);
    return 0;
}

void unload(matrix_t * matrix){
    free(matrix->data);
}

int saveByName(char * fileName, char * name, matrix_t * matrix){

    FILE *file = fopen(fileName, "w");
    if( file == NULL)
    {
        fprintf(stderr,"There is no file by the name %s Closing program\n", fileName);
        return -1;
    }

    // Write properties:
    /* Octave's way to write them:
    # Created by Octave 3.8.2, Fri May 01 15:44:01 2015 CEST <kaditx@kaditx>
    # name: a
    # type: matrix
    # rows: 1
    # columns: 100
    */

    fprintf(file, "# Created by Libmatthread, %s %s\n","HOLA","HOLA" /* TODO Date and user*/);
    fprintf(file, "# name: %s\n", name);
    fprintf(file, "# type: matrix\n");
    fprintf(file, "# rows: %zu\n", matrix->height);
    fprintf(file, "# columns: %zu\n", matrix->width);
    int i,j;
    for(i=0; i < matrix->height; i++){
        for(j=0; j < matrix->width; j++){
            fprintf(file, "%.16Lf ", PMATRIX(matrix,i,j));
        }
        fputc('\n', file);
    }
    return 0;
}
