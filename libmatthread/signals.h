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
 * @file signals.h
 * @author Ekaitz Zarraga <ekaitz.zarraga@gmail.com>
 *
 * @brief Utilities for matrix_t elements when used as a signal.
 *
 * This file contains utilities for matrix_t element manipulation when they
 * are used to contain discrete signals.
 *
 */
#ifndef MATTHREAD_SIGNALH
#define MATTHREAD_SIGNALH

/**
 * @brief Discrete convolution of two signals.
 * @returns the convolution of the signals
 * @param[in] f,g input signals
 * @param[out] matrix_t convolution of f and g
 * Discrete convolution of two signals, it allocates output internally. Must free resource later.
 */
matrix_t convolution(matrix_t f, matrix_t g);

#endif //MATTHREAD_SIGNALH
