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
 * Module      : Allometrics.h
 * Revision    : Version C1b 
 * Date        : September, 2007
 * Notes       : Allometric definitions for PolSARproSim
 */
#ifndef __ALLOMETRICS_H__
#define __ALLOMETRICS_H__

#include	"Attenuation.h"
#include	"bmpDefinitions.h"
#include	"Branch.h"
#include	"c33Matrix.h"
#include	"c3Vector.h"
#include	"Complex.h"
#include	"Cone.h"
#include	"Crown.h"
#include	"Cylinder.h"
#include	"d33Matrix.h"
#include	"d3Vector.h"
#include	"Facet.h"
#include	"GraphicIMage.h"
#include	"GrgCyl.h"
#include	"Ground.h"
#include	"InfCyl.h"
#include	"JLkp.h"
#include	"Jnz.h"
#include	"Leaf.h"
#include	"LightingMaterials.h"
#include	"MonteCarlo.h"
#include	"Perspective.h"
#include	"Plane.h"
#include	"PolSARproSim_Definitions.h"
#include	"PolSARproSim_Procedures.h"
#include	"PolSARproSim_Progress.h"
#include	"PolSARproSim_Structures.h"
#include	"Ray.h"
#include	"RayCrownIntersection.h"
#include	"Realisation.h"
#include	"SarIMage.h"
#include	"Sinc.h"
#include	"soilsurface.h"
#include	"Spheroid.h"
#include	"Tree.h"
#include	"Trig.h"
#include	"YLkp.h"

/***************************/
/* Good event return value */
/***************************/

#define	NO_ALLOMETRICS_ERRORS										0

/********************************/
/* PERMITTIVITY MODEL CONSTANTS */
/********************************/

#define		VTF0													7.5
#define		VDTF0													2.5
#define		TEMP													20.0
#define		EPSINF_FW											4.9
#define		SIGMA_FW												1.27
#define		TWOPIE0_INV											17.97548488
#define		EPSINF_BW											2.9
#define		E0_BW													57.9
#define		F0_BW													0.18
#define		E0_FW													80.0888
#define		TWOPITAU_FW											0.0582852
#define		F0_FW													17.15701413

/***********************************/
/* Tree allometric implementations */
/***********************************/

double		Crown_Fractional_Living_Depth	(Tree *pT, PolSARproSim_Record *pPR);
double		Crown_Fractional_Dry_Depth		(Tree *pT, PolSARproSim_Record *pPR);
double		Crown_Fractional_Radius			(int species, PolSARproSim_Record *pPR);
double		Realise_Living_Crown_Depth		(Tree *pT, PolSARproSim_Record *pPR);	/* Generates living crown depth from a normal distribution				*/
double		Realise_Tree_Crown_Radius		(int species, double height,PolSARproSim_Record *pPR);/* Generate a tree crown radius estimate based on species */
double		Realise_Tree_Height				(double mean_height);                  /* Generate a tree height from a truncated normal distribution			*/
double		Mean_Tree_Crown_Radius			(int species, double height, PolSARproSim_Record *pPR);          /* Returns the mean tree crown radius according to species allometric	*/

double		Stem_Start_Radius             (Tree *pT, PolSARproSim_Record *pPR);
double      Stem_End_Radius               (Tree *pT, PolSARproSim_Record *pPR);
d3Vector    Stem_Direction                (Tree *pT, PolSARproSim_Record *pPR);
double      Stem_Tropism_Factor           (Tree *pT, PolSARproSim_Record *pPR);
d3Vector    Stem_Tropism_Direction			(Tree *pT, PolSARproSim_Record *pPR);
double		Stem_Lamdacx                  (Tree *pT, PolSARproSim_Record *pPR);
double		Stem_Lamdacy                  (Tree *pT, PolSARproSim_Record *pPR);
double		Stem_Gamma                    (Tree *pT, PolSARproSim_Record *pPR);
double		Stem_Moisture                 (Tree *pT, PolSARproSim_Record *pPR);


Complex		vegetation_permittivity			(double moisture, double frequency);

double      Primary_Radius                (Tree *pT, PolSARproSim_Record *pPR, double t);
double		Primary_Tropism_Factor			(Tree *pT, PolSARproSim_Record *pPR);
d3Vector    Primary_Tropism_Direction		(Tree *pT, PolSARproSim_Record *pPR);
double		Primary_Lamdacx					(Tree *pT, PolSARproSim_Record *pPR);
double		Primary_Lamdacy					(Tree *pT, PolSARproSim_Record *pPR);
double		Primary_Gamma                 (Tree *pT, PolSARproSim_Record *pPR);
double		Primary_Moisture              (Tree *pT, PolSARproSim_Record *pPR);
double		Primary_Dry_Moisture          (Tree *pT, PolSARproSim_Record *pPR);

int			Number_of_Secondaries			(Tree *pT, PolSARproSim_Record *pPR, double primary_length);
double		Secondary_Tropism_Factor		(Tree *pT, PolSARproSim_Record *pPR);
d3Vector    Secondary_Tropism_Direction	(Tree *pT, PolSARproSim_Record *pPR);
double		Secondary_Lamdacx             (Tree *pT, PolSARproSim_Record *pPR);
double		Secondary_Lamdacy             (Tree *pT, PolSARproSim_Record *pPR);
double		Secondary_Gamma					(Tree *pT, PolSARproSim_Record *pPR);

double		Tertiary_Branch_Volume_Fraction	(Tree *pT, PolSARproSim_Record *pPR);
double		Tertiary_Branch_Moisture         (Tree *pT, PolSARproSim_Record *pPR);

int			Leaf_Species					(int species, PolSARproSim_Record *pPR);
double		Leaf_Volume_Fraction			(int species, PolSARproSim_Record *pPR);
double		Leaf_Moisture					(int species, PolSARproSim_Record *pPR);
double		Leaf_Moisture_r				(int species, PolSARproSim_Record *pPR, unsigned int *pseed);
void        Leaf_Size                  (Tree *pT, PolSARproSim_Record *pPR, double *d1, double *d2, double *d3);

/****************************************/
/* LEFTOVER PARAMETRIC MODEL PARAMETERS */
/****************************************/

#define		POLSARPROSIM_PINE001_CLS		0.3910


#endif
