/************************************************************************/
/*                                                                      */
/* PolSARproSim Version C1b  Forest Synthetic Aperture Radar Simulation	*/
/* Copyright (C) 2007 Mark L. Williams                                  */
/*                                                                      */
/* This program is free software; you may redistribute it and/or        */
/* modify it under the terms of the GNU General Public License          */
/* as published by the Free Software Foundation; either version 2       */
/* of the License, or (at your option) any later version.               */
/*                                                                      */
/* This program is distributed in the hope that it will be useful,      */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of       */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                 */
/* See the GNU General Public License for more details.                 */
/*                                                                      */
/* You should have received a copy of the GNU General Public License    */
/* along with this program; if not, write to the Free Software          */
/* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,           */
/* MA  02110-1301, USA. (http://www.gnu.org/copyleft/gpl.html)          */
/*                                                                      */
/************************************************************************/
/*
 * Author      : Razi Ahmed
 * Module      : read_parfile.h
 * Revision    : Version 1.0 
 * Date        : July, 2012
 * Notes       : Procedure prototype for reading parameter file by keyword
 */

#ifndef _read_parfile_h
#define _read_parfile_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAX(a,b)  ( ( (a) > (b) ) ? (a) : (b) )
#define MAX_STR  256

int read_cflag       (FILE *pinF, char *key, char *str1);
int read_string      (FILE *pinF, char *key, char *str);
int read_integer     (FILE *pinF, char *key, int *val, int min, int max, int Default);
int read_double      (FILE *pinF, char *key, double *dbl_val, double min, double max, double Default);
int read_float       (FILE *pinF, char *key, float *);
int read_fvector     (FILE *pinF, char *key, float *flt, int nv);
int read_dvector     (FILE *pinF, char *key, double *dbl, int nv);



#endif
