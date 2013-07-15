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
 * Module      : Allometrics.c
 * Revision    : Version C1b 
 * Date        : September, 2007
 *
 */
#include	"Allometrics.h"

/***********************************/
/* Tree allometric implementations */
/***********************************/

int			Number_of_Secondaries			(Tree *pT, PolSARproSim_Record *pPR, double primary_length)
{
   int		Ns;
   double	m, C;
   m        = pPR->SpeciesDataBase[pT->species].secondary_number_slope;
   C        = pPR->SpeciesDataBase[pT->species].secondary_number_intercept;
   
   Ns			= (int) (m*primary_length + C);
   if (Ns < 0) Ns = 0;
   return		(Ns);
}

double		Crown_Fractional_Living_Depth	(Tree *pT, PolSARproSim_Record *pPR)
{
   double		fL;
   
   fL = pPR->SpeciesDataBase[pT->species].crown_live_alpha;
   return (fL);
}

double		Realise_Living_Crown_Depth		(Tree *pT, PolSARproSim_Record *pPR)
{
   double   height   = pT->height;
   double   a_bar    = height * Crown_Fractional_Living_Depth(pT, pPR);
   double	a_std    = TREE_STDDEV_FACTOR*a_bar;
   double	l        = 100.0*height;
   while (l > height) {
      l              = Gaussian_drand (a_bar, a_std, a_bar-a_std, a_bar+a_std);
   }
   return (l);
}

double		Crown_Fractional_Dry_Depth	(Tree *pT, PolSARproSim_Record *pPR)
{
   double		fD;
   fD = pPR->SpeciesDataBase[pT->species].crown_dry_alpha;
   return (fD);
}


/* Left these three functions to allow automatic generation of tree parameters   */
/* which will happen if the forest xml definition file is not used               */

double		Crown_Fractional_Radius				(int species, PolSARproSim_Record *pPR)
{
   double		fR;
   fR = pPR->SpeciesDataBase[species].crown_radius_factor;
   
   return (fR);
}

double		Mean_Tree_Crown_Radius				(int species, double height, PolSARproSim_Record *pPR)
{
   double		a	= height * Crown_Fractional_Radius (species, pPR);
   return (a);
}

double		Realise_Tree_Crown_Radius			(int species, double height, PolSARproSim_Record *pPR)
{
   double	a_bar	= height * Crown_Fractional_Radius (species, pPR);
   double	a_std	= TREE_STDDEV_FACTOR*a_bar;
   return (Gaussian_drand (a_bar, a_std, a_bar-a_std, a_bar+a_std));
}

double		Realise_Tree_Height				(double mean_height)
{
   double h_std	= TREE_STDDEV_FACTOR*mean_height;
   double	h_max	= mean_height + h_std;
   double h_min	= mean_height - h_std;
   double	height	= Gaussian_drand (mean_height, h_std, h_min, h_max);
   return (height);
}

/************************************************************/
/************************************************************/

double      Stem_Start_Radius          (Tree *pT, PolSARproSim_Record *pPR) /* keep this to allow forest generation */
{
   double		sr;
   double      height   = pT->height;
   
   
   if(pPR->ForestInput_Flag == EXTERNAL_FOREST_DEFINITION) {   /* if reading the forest input externally   */ 
      sr          = pT->dbh/2;                                     /* for now derive it directly from the dbh  */
   } else {
      sr       = pPR->SpeciesDataBase[pT->species].stem_start_radius_factor * height/100.0;
      pT->dbh  = sr*2;
   }
   return (sr);
}

double		Stem_End_Radius					(Tree *pT, PolSARproSim_Record *pPR)
{
   double		er;
   double      height                  = pT->height;
   double      stem_end_radius_factor  = pPR->SpeciesDataBase[pT->species].stem_end_radius_factor;
   er = stem_end_radius_factor * height/1000.0;
   return (er);
}

d3Vector	Stem_Direction					(Tree *pT, PolSARproSim_Record *pPR)
{
   d3Vector    z0 = Zero_d3Vector ();
   double		min_cospolar;
   double		theta;
   double		phi;
   min_cospolar   = cos(pPR->SpeciesDataBase[pT->species].stem_max_angle * DEG_TO_RAD);
   
   theta          = acos (min_cospolar + drand()*(1.0-min_cospolar));
   phi            = 2.0*DPI_RAD*drand();
   z0             =  Polar_Assign_d3Vector (1.0, theta, phi);
   return (z0);
}

double		Stem_Tropism_Factor				(Tree *pT, PolSARproSim_Record *pPR)
{
   double	dp;
   dp = pPR->SpeciesDataBase[pT->species].stem_tropism_factor;
   return (dp);
}

d3Vector	Stem_Tropism_Direction			(Tree *pT, PolSARproSim_Record *pPR)
{
   d3Vector	p;
   double   stem_tropism_theta   = pPR->SpeciesDataBase[pT->species].stem_tropism_theta   * DEG_TO_RAD;
   double   stem_tropism_phi     = pPR->SpeciesDataBase[pT->species].stem_tropism_phi     * DEG_TO_RAD;
   double   stem_trop_x, stem_trop_y, stem_trop_z;
   
   stem_trop_x = sin(stem_tropism_theta) * cos(stem_tropism_phi);
   stem_trop_y = sin(stem_tropism_theta) * sin(stem_tropism_phi);
   stem_trop_z = cos(stem_tropism_theta);
   
   p = Cartesian_Assign_d3Vector (stem_trop_x, stem_trop_y, stem_trop_z);
   return (p);
}

double		Stem_Lamdacx					(Tree *pT, PolSARproSim_Record *pPR)
{
   double		lamdacx;
   double      stdev    = pPR->SpeciesDataBase[pT->species].stem_lamdacx_stdev;
   double      mean     = pPR->SpeciesDataBase[pT->species].stem_lamdacx_mean;
   lamdacx     = mean + stdev*drand();
   return (lamdacx);
}

double		Stem_Lamdacy					(Tree *pT, PolSARproSim_Record *pPR)
{
   double		lamdacy;
   double      stdev    = pPR->SpeciesDataBase[pT->species].stem_lamdacy_stdev;
   double      mean     = pPR->SpeciesDataBase[pT->species].stem_lamdacy_mean;
   lamdacy     = mean + stdev*drand();
   return (lamdacy);
}

double		Stem_Gamma						(Tree *pT, PolSARproSim_Record *pPR)
{
   double		gamma;
   double      stdev    = pPR->SpeciesDataBase[pT->species].stem_gamma_stdev;
   double      mean     = pPR->SpeciesDataBase[pT->species].stem_gamma_mean;
   gamma       = mean + stdev*drand();
   return (gamma);
}

double      Stem_Moisture              (Tree *pT, PolSARproSim_Record *pPR)
{
   double		moisture;
   double      spec_moisture = pPR->SpeciesDataBase[pT->species].stem_moisture;
   moisture    = spec_moisture + spec_moisture * 0.1* (drand ()-0.5);
   return (moisture);
}

Complex		vegetation_permittivity			(double moisture, double frequency)
{
   /*****************************************************/
   /* Following Ulaby and El-Rayes (1987) 0.3GHz-1.3GHz */
   /*****************************************************/
   double			eps_r		= 1.7 - 0.74*moisture + 6.16*moisture*moisture;
   double			vfw		= moisture*(0.55*moisture-0.076);
   double			vb			= 4.64*moisture*moisture/(1.0+7.36*moisture*moisture);
   double			g			= 0.0012*frequency*frequency+0.0019*frequency;
   Complex        eps_fw;
   Complex        eps_bw;
   Complex        er;
   eps_fw			= complex_div	(xy_complex (E0_FW-EPSINF_FW,0.0), xy_complex (1.0, frequency/F0_FW));
   eps_fw			= complex_add	(eps_fw, xy_complex (EPSINF_FW, -g*TWOPIE0_INV*SIGMA_FW/frequency));
   eps_bw			= complex_sqrt	(xy_complex (0.0, frequency/F0_BW));
   eps_bw			= complex_add	(xy_complex (1.0, 0.0), eps_bw);
   eps_bw			= complex_div	(xy_complex (E0_BW-EPSINF_BW, 0.0), eps_bw);
   eps_bw			= complex_add	(xy_complex (EPSINF_BW, 0.0), eps_bw);
   er             = complex_add	(xy_complex (eps_r, 0.0), complex_rmul(eps_fw, vfw));
   er             = complex_add	(er, complex_rmul (eps_bw, vb));
   return (er);
}

/*****************************/
/* Primary branch generation */
/*****************************/

double    Primary_Radius              (Tree *pT, PolSARproSim_Record *pPR, double t)
{
   double		R  = 0.0;
   double		A, B, C;
   double      sr0;
   Branch      *pStem;
   
   pStem       = pT->Stem.head;
   sr0         = pStem->start_radius;
   
   A = pPR->SpeciesDataBase[pT->species].primary_radius_A;
   B = pPR->SpeciesDataBase[pT->species].primary_radius_B;
   C = pPR->SpeciesDataBase[pT->species].primary_radius_C;
   
   if (t<0.0) {
      t	= 0.0;
   } else {
      if (t>1.0) {
         t	= 1.0;
      }
   }
   R		= sr0*(A*t*t+B*t+C);
   return (R);
}

double		Primary_Tropism_Factor				(Tree *pT, PolSARproSim_Record *pPR)
{
   double	dp;
   dp       = pPR->SpeciesDataBase[pT->species].primary_tropism_factor;
   return (dp);
}

d3Vector	Primary_Tropism_Direction			(Tree *pT, PolSARproSim_Record *pPR)
{
   d3Vector	p;
   
   double   primary_tropism_theta   = pPR->SpeciesDataBase[pT->species].primary_tropism_theta   * DEG_TO_RAD;
   double   primary_tropism_phi     = pPR->SpeciesDataBase[pT->species].primary_tropism_phi     * DEG_TO_RAD;
   double   primary_trop_x, primary_trop_y, primary_trop_z;
   
   primary_trop_x = sin(primary_tropism_theta) * cos(primary_tropism_phi);
   primary_trop_y = sin(primary_tropism_theta) * sin(primary_tropism_phi);
   primary_trop_z = cos(primary_tropism_theta);
   
   p = Cartesian_Assign_d3Vector (primary_trop_x, primary_trop_y, primary_trop_z);
   
   return (p);
}

double		Primary_Lamdacx					(Tree *pT, PolSARproSim_Record *pPR)
{
   double		lamdacx;
   double      stdev    = pPR->SpeciesDataBase[pT->species].primary_lamdacx_stdev;
   double      mean     = pPR->SpeciesDataBase[pT->species].primary_lamdacx_mean;
   lamdacx     = mean + stdev*drand (); 
   return (lamdacx);
}

double		Primary_Lamdacy					(Tree *pT, PolSARproSim_Record *pPR)
{
   double		lamdacy;
   double      stdev    = pPR->SpeciesDataBase[pT->species].primary_lamdacy_stdev;
   double      mean     = pPR->SpeciesDataBase[pT->species].primary_lamdacy_mean;
   lamdacy     = mean + stdev*drand ();
   return (lamdacy);
}

double		Primary_Gamma					(Tree *pT, PolSARproSim_Record *pPR)
{
   double		gamma;
   double      stdev    = pPR->SpeciesDataBase[pT->species].primary_gamma_stdev;
   double      mean     = pPR->SpeciesDataBase[pT->species].primary_gamma_mean;
   gamma       = mean + stdev*drand ();
   return (gamma);
}

double		Primary_Moisture				(Tree *pT, PolSARproSim_Record *pPR)
{
   double		moisture;
   double      spec_moisture  = pPR->SpeciesDataBase[pT->species].primary_live_moisture;
   moisture    = spec_moisture + spec_moisture * 0.1 * (drand ()-0.5);
   return (moisture);
}

double		Primary_Dry_Moisture			(Tree *pT, PolSARproSim_Record *pPR)
{
   double		moisture;
   double      spec_moisture  = pPR->SpeciesDataBase[pT->species].primary_dry_moisture;
   
   moisture = spec_moisture + spec_moisture * 0.1 * (drand ()-0.5);
   return (moisture);
}

/*******************************/
/* Secondary branch generation */
/*******************************/

double		Secondary_Tropism_Factor		(Tree *pT, PolSARproSim_Record *pPR)
{
   double	dp;
   dp = pPR->SpeciesDataBase[pT->species].secondary_tropism_factor;
   return (dp);
}

d3Vector	Secondary_Tropism_Direction		(Tree *pT, PolSARproSim_Record *pPR)
{
   d3Vector	p;
   double   secondary_tropism_theta   = pPR->SpeciesDataBase[pT->species].secondary_tropism_theta   * DEG_TO_RAD;
   double   secondary_tropism_phi     = pPR->SpeciesDataBase[pT->species].secondary_tropism_phi     * DEG_TO_RAD;
   double   secondary_trop_x, secondary_trop_y, secondary_trop_z;
   
   secondary_trop_x = sin(secondary_tropism_theta) * cos(secondary_tropism_phi);
   secondary_trop_y = sin(secondary_tropism_theta) * sin(secondary_tropism_phi);
   secondary_trop_z = cos(secondary_tropism_theta);
   
   p = Cartesian_Assign_d3Vector (secondary_trop_x, secondary_trop_y, secondary_trop_z);
   
   return (p);
}

double		Secondary_Lamdacx				(Tree *pT, PolSARproSim_Record *pPR)
{
   double		lamdacx;
   double      stdev    = pPR->SpeciesDataBase[pT->species].secondary_lamdacx_stdev;
   double      mean     = pPR->SpeciesDataBase[pT->species].secondary_lamdacx_mean;
   
   lamdacx	= mean + stdev * drand (); 
   
   return (lamdacx);
}

double		Secondary_Lamdacy				(Tree *pT, PolSARproSim_Record *pPR)
{
   double		lamdacy;
   double      stdev    = pPR->SpeciesDataBase[pT->species].secondary_lamdacy_stdev;
   double      mean     = pPR->SpeciesDataBase[pT->species].secondary_lamdacy_mean;
   lamdacy	= mean + stdev * drand (); 
   return (lamdacy);
}

double		Secondary_Gamma					(Tree *pT, PolSARproSim_Record *pPR)
{
   double		gamma;
   double      stdev    = pPR->SpeciesDataBase[pT->species].secondary_gamma_stdev;
   double      mean     = pPR->SpeciesDataBase[pT->species].secondary_gamma_mean;
   gamma    = mean + stdev * drand();
   return (gamma);
}

/*********************/
/* Tertiary elements */
/*********************/

double		Tertiary_Branch_Volume_Fraction	(Tree *pT, PolSARproSim_Record *pPR)
{
   double		vf;
   vf = pPR->SpeciesDataBase[pT->species].tertiary_volume_fraction;
   return		(vf);
}

double		Tertiary_Branch_Moisture				(Tree *pT, PolSARproSim_Record *pPR)
{
   double		moisture;
   double      spec_moisture  = pPR->SpeciesDataBase[pT->species].tertiary_moisture;
   moisture = spec_moisture + spec_moisture * 0.1* (drand ()-0.5);
   return (moisture);
}

/***********/
/* Foliage */
/***********/

int			Leaf_Species			(int species, PolSARproSim_Record *pPR)
{
   int Lspecies;
   
   /* this should eventually change to pPR->SpeciesDatabase[pT->species].leaf_shape */
   Lspecies = pPR->SpeciesDataBase[species].leaf_shape;
   
   return (Lspecies);
}

double		Leaf_Volume_Fraction	(int species, PolSARproSim_Record *pPR)
{
   double		vf;
   vf = pPR->SpeciesDataBase[species].leaf_volume_fraction;
   return		(vf);
}

void      Leaf_Size               (Tree *pT, PolSARproSim_Record *pPR, double *d1, double *d2, double *d3)
{
   int i, j;
   double leaf_dim[3];
   double leaf_width_mean, leaf_height_mean, leaf_thickness_mean;
   double leaf_width_stdev,leaf_height_stdev, leaf_thickness_stdev;
   double temp;
   
   /* read in the species specific values */
   leaf_width_mean      = pPR->SpeciesDataBase[pT->species].leaf_width_mean;
   leaf_width_stdev     = pPR->SpeciesDataBase[pT->species].leaf_width_stdev;
   leaf_height_mean     = pPR->SpeciesDataBase[pT->species].leaf_height_mean;
   leaf_height_stdev    = pPR->SpeciesDataBase[pT->species].leaf_height_stdev;
   leaf_thickness_mean  = pPR->SpeciesDataBase[pT->species].leaf_thickness_mean;
   leaf_thickness_stdev = pPR->SpeciesDataBase[pT->species].leaf_thickness_stdev;
   
   /* realize the width, height and thickness */
   leaf_dim[0]          = leaf_width_mean       + leaf_width_stdev      * (drand()-0.5);
   leaf_dim[1]          = leaf_height_mean      + leaf_height_stdev     * (drand()-0.5);
   leaf_dim[2]          = leaf_thickness_mean   + leaf_thickness_stdev  * (drand()-0.5);
   
   if(leaf_dim[0]<0) leaf_dim[0]=leaf_width_mean;
   if(leaf_dim[1]<0) leaf_dim[1]=leaf_height_mean;
   if(leaf_dim[2]<0) leaf_dim[2]=leaf_thickness_mean;
   
   /* sort so that d1 > d2 > d3 */
   /* we lose all meaning of width, height and thickness here, but whatever */
   for (i = 2; i > 0; i--) {
      for (j = 1; j <= i; j++) {
         if (leaf_dim[j-1] > leaf_dim[j]) {
            temp           = leaf_dim[j-1];
            leaf_dim[j-1]  = leaf_dim[j];
            leaf_dim[j]    = temp;
         }
      }
   }
   
   *d1 = leaf_dim[2];
   *d2 = leaf_dim[1];
   *d3 = leaf_dim[0];
   
   return; 
}   

double		Leaf_Moisture				(int species, PolSARproSim_Record *pPR)
{
   double		moisture;
   double      spec_moisture = pPR->SpeciesDataBase[species].leaf_moisture;
   moisture	= spec_moisture + spec_moisture * 0.1* (drand ()-0.5); 
   return (moisture);
}

// re-entrant (thread-safe) version of Leaf_Moisture
double		Leaf_Moisture_r				(int species, PolSARproSim_Record *pPR, double randn)
{
   double		moisture;
   double      spec_moisture = pPR->SpeciesDataBase[species].leaf_moisture;
   moisture	= spec_moisture + spec_moisture * 0.1* (randn-0.5); 
   return (moisture);
}


