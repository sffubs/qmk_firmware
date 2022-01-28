/* Copyright 2019
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"


#define LAYOUT( \
  lm00, lm01, lm02, lm03, lm04, rm00, rm01, rm02, rm03, rm04, rm05, \
  lm10, lm11, lm12, lm13, lm14, rm10, rm11, rm12, rm13, rm14, rm15, \
  lm20, lm21, lm22, lm23, lm24, rm20, rm21, rm22, rm23, rm24, rm25, \
                    lt00, lt01, rt00, rt01,	                    \
                    lt10, lt11, rt10, rt11,                         \
                    lt20, lt21, rt20, rt21                          \
) {							            \
  {KC_NO, lm00, lm01, lm02, lm03, lm04}, \
  {KC_NO, lm10, lm11, lm12, lm13, lm14}, \
  {KC_NO, lm20, lm21, lm22, lm23, lm24}, \
  {lt20,  lt21, lt10, lt11, lt00, lt01}, \
  {rm05,  rm04, rm03, rm02, rm01, rm00}, \
  {rm15,  rm14, rm13, rm12, rm11, rm10}, \
  {rm25,  rm24, rm23, rm22, rm21, rm20}, \
  {rt21,  rt20, rt11, rt10, rt01, rt00}}
