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

    matalloc(&A, 4, 5);
    matalloc(&B, 4, 5);

    int i;
    for (i=0; i<A.width*A.height; i++){
        A.data[i]=1.111111111;
    }
    for (i=0; i<B.width*B.height; i++){
        B.data[i]=8.888888888;
    }

    // Test swap
    matrix_t C=matjoinv(A,B);
    matrix_t D=matjoinh(A,B);

    matswaprow(C, 11, 0);
    matswapcol(D, 4, 10);

    printf("\nMATRIZ C: matjoinv\n");
    matprint(C);
    printf("\nMATRIZ D: matjoinh\n");
    matprint(D);

    matfree(&A);
    matfree(&B);
    matfree(&C);
    matfree(&D);
    return 0;
}
