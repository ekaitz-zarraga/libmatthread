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
#include<structures.h>
#include<octaveIO.h>
#include<convolution.h>
#include<stdio.h>

int main ( int argc, char * argv [] ){

    matrix_t A, B, C;

    loadByName("testfiles/input.mat", "a", &A);
    loadByName("testfiles/input.mat", "b", &B);

    int n;
    printf("Matriz A:\n");
    for (n=0; n< A.width; n++){
        printf("%Lf\t", A.data[n]);
    }
    putchar('\n');

    printf("Matriz B:\n");
    for (n=0; n< B.width; n++){
        printf("%Lf\t", B.data[n]);
    }
    putchar('\n');
    if( convolution(A,B,&C)){
        return 1;
    }

    printf("\nMatriz C:\n");
    for (n=0; n< C.width; n++){
        printf("%.17Lf\t", C.data[n]);
    }
    putchar('\n');

    saveByName("testfiles/output.mat", "c", &C);

    unload(&A);
    unload(&B);
    unload(&C);

    return 0;
}
