/************************************************************************/
/*																		*/
/* PolSARproSim Version C1b  Forest Synthetic Aperture Radar Simulation	*/
/* Copyright (C) 2007 Mark L. Williams									*/
/*																		*/
/* This program is free software; you may redistribute it and/or		*/
/* modify it under the terms of the GNU General Public License			*/
/* as published by the Free Software Foundation; either version 2		*/
/* of the License, or (at your option) any later version.				*/
/*																		*/
/* This program is distributed in the hope that it will be useful,		*/
/* but WITHOUT ANY WARRANTY; without even the implied warranty of		*/
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.					*/
/* See the GNU General Public License for more details.					*/
/*																		*/
/* You should have received a copy of the GNU General Public License	*/
/* along with this program; if not, write to the Free Software			*/
/* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,			*/
/* MA  02110-1301, USA. (http://www.gnu.org/copyleft/gpl.html)			*/
/*																		*/
/************************************************************************/
/*
 * Author      : Mark L. Williams
 * Module      : MonteCarlo.h
 * Revision    : Version C1b 
 * Date        : September, 2007
 *
 */
#ifndef __MONTECARLO_H__
#define __MONTECARLO_H__

#include	<stdio.h>
#include	<stdlib.h>
#include	<math.h>
#include	<float.h>

double		drand                (void);
double		drand_r              (unsigned int *pseed); /* thread safe version of drand() */
double		Gaussian_drand			(double a_bar, double a_std, double a_min, double a_max);
double		Normal_Distribution	(void);
double		Gaussian_drand_r		(double a_bar, double a_std, double a_min, double a_max, unsigned short *pseed); /* thread safe version of Gaussian_drand() */
double      Normal_Distribution_r(unsigned short *pseed); /* thread safe version of Normal_Distribution() */
double		erand                (double x);
double		erand_r              (double x, unsigned int *pseed); /* thread safe version of erand() */

#endif
