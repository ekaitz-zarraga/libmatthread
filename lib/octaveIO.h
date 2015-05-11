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
 * @file octaveIO.h
 * @author Ekaitz Zarraga <ekaitz.zarraga@gmail.com>
 *
 * @brief Basic Input Output for Octave .mat files.
 *
 * Read/Write functions for Octave .mat files.
 *
 */

#include<structures.h>

/**
 * @brief Load matrix_t by name from .mat file
 * @returns 0 if ok, -1 if error.
 * @param[in] fileName file to read from.
 * @param[in] name matrix name to read from file.
 * @param[in] matrix matrix to load content in. FIXME Must be uninitialized.
 */
int loadByName(char * fileName, char * name, matrix_t * matrix);

/**
 * @bried Unload allocated matrix_t element.
 * FIXME Move to common.
 */
void unload(matrix_t * matrix);

/**
 * @brief Save matrix_t to .mat file.
 * @returns 0 if ok, -1 if error.
 * @param[in] fileName target file.
 * @param[in] name matrix name to write in file.
 * @param[in] matrix matrix to write.
 * TODO Check if file exists and, if exists, do not put the header.
 */
int saveByName(char * filename, char * name, matrix_t * matrix);
