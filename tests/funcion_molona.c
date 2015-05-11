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
#include<stdio.h>
#include<stdlib.h>
#include<common.h>
#include<octaveIO.h>

void main(int argc, char * argv[] ){
    int i;
    matrix_t A;
    if(argc != 3)
        exit(1);
    loadByName(argv[2], argv[1], &A);
    for(i=0; i<(A.height*A.width); i++){
        printf("%.16Lf ", A.data[i]);
    }
    printf("\n%d\n", i);
    matfree(&A);
}
