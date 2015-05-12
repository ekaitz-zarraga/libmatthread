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
#include<common.h>
#include<octaveIO.h>
#include<signals.h>
#include<stdio.h>

int main ( int argc, char * argv [] ){

    matrix_t A=matinit();
    matrix_t B=matinit();
    matrix_t C=matinit();

    loadByName("testfiles/input.mat", "a", &A);
    loadByName("testfiles/input.mat", "b", &B);

    printf("Matriz A:\n");
    matprint(A);
    putchar('\n');

    printf("Matriz B:\n");
    matprint(B);
    putchar('\n');
    C=convolution(A,B);
    if( C.height==0 ){
        return 1;
    }

    printf("\nMatriz C:\n");
    matprint(C);
    putchar('\n');

    saveByName("testfiles/output.mat", "c", &C);

    //TEST probar si funciona el copiar:
    matrix_t D = matinit();
    D.height=0;
    D.width=0;
    matcpy(&D, &C);
    printf("\nMatriz D:\n");
    matprint(D);
    matfree(&D);

    matfree(&C);
    matfree(&A);
    matfree(&B);

    return 0;
}
