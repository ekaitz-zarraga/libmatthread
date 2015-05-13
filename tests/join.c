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

    matalloc(&A, 2, 4);
    matalloc(&B, 2, 4);

    int i;
    for (i=0; i<(A.width*A.height); i++){
        A.data[i]=i;
    }
    for (i=0; i<(B.width*B.height); i++){
        B.data[i]=i;
    }
    matprint(A);
    matprint(B);

    matrix_t C=matjoinh(A,B);
    matprint(C);
    matrix_t D=matjoinv(A,B);
    matprint(D);

    printf("\n\nTranspose test on B\n");
    matprint(B);
    mattranspose(&B);
    matprint(B);

    matfree(&A);
    matfree(&B);
    matfree(&C);
    matfree(&D);
    return 0;
}
