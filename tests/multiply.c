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
#include<matrices.h>
#include<signals.h>
#include<stdio.h>

int main ( int argc, char * argv [] ){

    matrix_t A=matinit();
    matrix_t B=matinit();

    A=matones(2000, 4000);
    B=matones(4000, 2000);

    matmultscalar(B,34);

    matrix_t C;

    C=matmultthreads(A,B,8);
//    matprint(A);
//    matprint(B);
//    matprint(C);

    matfree(&A);
    matfree(&B);
    matfree(&C);
    return 0;
}
