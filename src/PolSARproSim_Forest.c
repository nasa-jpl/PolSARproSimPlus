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
 * Module      : PolSARproSim_Forest.c
 * Revision    : Version C1b 
 * Date        : September, 2007
 * Notes       : Forest interferometric SAR image calculation for PolSARproSim
 */
#include	"PolSARproSim_Forest.h"
#include  <time.h>
/*************************/
/* SAR geometry routines */
/*************************/

void	Zero_SG_Accumulators			(SarGeometry *pSG)
{
   pSG->Sigma0HH			= 0.0;
   pSG->Sigma0HV			= 0.0;
   pSG->Sigma0VH			= 0.0;
   pSG->Sigma0VV			= 0.0;
   Polar_Assign_Complex (&(pSG->AvgShhvv), 0.0, 0.0);
   pSG->Sigma0_count		= 0.0;
   return;
}

int		Initialise_SAR_Geometry			(SarGeometry *pSG, PolSARproSim_Record *pPR, int track)
{
   int               rtn_value;
   double				std_h;
   double				k0z, k0z2, k02, kro2, kro;
   Complex           k22, k2, k2z2, k2z, koz2, kez2, koz, kez, ke2, ke, kiz, k12, k1;
   Complex           Rhh, Rvv, delta;
   double				gf, Rg;
   /************************************/
   /* Determine mean surface roughness */
   /************************************/
   switch (POLSARPROSIM_RAYLEIGH_ROUGHNESS_MODEL) {
      case 0:	std_h	= pPR->large_scale_height_stdev; break;
      case 1:	std_h	= pPR->small_scale_height_stdev; break;
      case 2:	std_h	= pPR->small_scale_height_stdev + pPR->large_scale_height_stdev; break;
      default:	std_h	= pPR->small_scale_height_stdev + pPR->large_scale_height_stdev; break;
   }
   /****************************************************************************************/
   /* general track variable, used to point Accumulate_SAR_Contribution to the right track */
   /****************************************************************************************/
   pSG->track        = track;
   /*********************************/
   /* Direct backscatter quantities */
   /*********************************/
   pSG->Pi           = 4.0*atan(1.0);
   pSG->thetai       = pPR->incidence_angle[track];
   pSG->cos_thetai	= cos(pSG->thetai);
   pSG->sin_thetai	= sin(pSG->thetai);
   pSG->p_srange		= pPR->slant_range[track];
   pSG->p_thetai		= pPR->incidence_angle[track];
   pSG->p_height		= pSG->p_srange*cos(pSG->p_thetai);
   pSG->p_grange		= pSG->p_srange*sin(pSG->p_thetai);
   rtn_value			= Initialise_Standard_Jnlookup (&(pSG->Jtable));
   rtn_value			= Initialise_Standard_Ynlookup (&(pSG->Ytable));
   pSG->ki           = Cartesian_Assign_d3Vector (0.0,  pPR->k0*pSG->sin_thetai, -pPR->k0*pSG->cos_thetai);
   pSG->ks           = Cartesian_Assign_d3Vector (0.0,  -pPR->k0*pSG->sin_thetai, pPR->k0*pSG->cos_thetai);
   pSG->ch           = Assign_c3Vector (xy_complex(-1.0, 0.0), xy_complex(0.0, 0.0), xy_complex(0.0, 0.0));
   pSG->cv           = Assign_c3Vector (xy_complex(0.0, 0.0), xy_complex(-pSG->cos_thetai, 0.0), xy_complex(-pSG->sin_thetai, 0.0));
   /*********************************/
   /* Bounce backscatter quantities */
   /*********************************/
   pSG->n				= Cartesian_Assign_d3Vector (-pPR->slope_x, -pPR->slope_y, 1.0);
   d3Vector_insitu_normalise (&(pSG->n));
   pSG->z				= Cartesian_Assign_d3Vector (0.0, 0.0, 1.0);
   /********************/
   /* FSA wave vectors */
   /********************/
   pSG->kr           = d3Vector_reflect (pSG->ki, pSG->n);
   pSG->krm          = d3Vector_double_multiply (pSG->kr, -1.0);
   /****************************/
   /* FSA polarisation vectors */
   /****************************/
   rtn_value         = Polarisation_Vectors (pSG->ki,  pSG->z, &(pSG->hi),  &(pSG->vi));
   rtn_value         = Polarisation_Vectors (pSG->ks,  pSG->z, &(pSG->hs),  &(pSG->vs));
   rtn_value         = Polarisation_Vectors (pSG->kr,  pSG->z, &(pSG->hr),  &(pSG->vr));
   rtn_value         = Polarisation_Vectors (pSG->krm, pSG->z, &(pSG->hrm), &(pSG->vrm));
   rtn_value         = Polarisation_Vectors (pSG->ki,  pSG->n, &(pSG->hil),  &(pSG->vil));
   rtn_value         = Polarisation_Vectors (pSG->ks,  pSG->n, &(pSG->hsl),  &(pSG->vsl));
   rtn_value         = Polarisation_Vectors (pSG->kr,  pSG->n, &(pSG->hrl),  &(pSG->vrl));
   rtn_value         = Polarisation_Vectors (pSG->krm, pSG->n, &(pSG->hrlm), &(pSG->vrlm));
   pSG->chi          = d3V2c3V (pSG->hi);
   pSG->cvi          = d3V2c3V (pSG->vi);
   pSG->chs          = d3V2c3V (pSG->hs);
   pSG->cvs          = d3V2c3V (pSG->vs);
   pSG->chr          = d3V2c3V (pSG->hr);
   pSG->cvr          = d3V2c3V (pSG->vr);
   pSG->chrm         = d3V2c3V (pSG->hrm);
   pSG->cvrm         = d3V2c3V (pSG->vrm);
   pSG->chil         = d3V2c3V (pSG->hil);
   pSG->cvil         = d3V2c3V (pSG->vil);
   pSG->chsl         = d3V2c3V (pSG->hsl);
   pSG->cvsl         = d3V2c3V (pSG->vsl);
   pSG->chrl         = d3V2c3V (pSG->hrl);
   pSG->cvrl         = d3V2c3V (pSG->vrl);
   pSG->chrlm        = d3V2c3V (pSG->hrlm);
   pSG->cvrlm        = d3V2c3V (pSG->vrlm);
   /*********************************/
   /* Local reflection coefficients */
   /*********************************/
   k0z		= d3Vector_scalar_product (pSG->kr, pSG->n);
   k0z2		= k0z*k0z;
   k02		= pPR->k0*pPR->k0;
   kro2		= k02 - k0z2;
   kro		= sqrt(kro2);
   k22		= complex_rmul (pPR->ground_eps[track], k02);
   k2			= complex_sqrt (k22);
   k2z2		= complex_sub  (k22, xy_complex (kro2, 0.0));
   k2z		= complex_sqrt (k2z2);
   koz2		= Copy_Complex (&(pPR->koz2_short));
   kez2		= Copy_Complex (&(pPR->kez2_short));
   koz		= Copy_Complex (&(pPR->koz_short));
   kez		= Copy_Complex (&(pPR->kez_short));
   ke2		= complex_add  (kez2, xy_complex (kro2, 0.0));
   ke			= complex_sqrt (ke2);
   kiz		= xy_complex   (k0z, 0.0);
   k12		= complex_rmul (pPR->e11_short, k02);
   k1			= complex_sqrt (k12);
   Rhh		= complex_div (complex_sub (koz, k2z), complex_add (koz, k2z));
   delta		= complex_add (complex_mul (kez, k22), complex_mul (k2z, k12));
   Rvv		= complex_div (complex_sub (complex_mul (kez, k22), complex_mul(k2z, k12)), delta);
//   fprintf (pPR->pLogFile, "|Rhh|^2\t= %lf  \n", Rhh.r*Rhh.r);
//   fprintf (pPR->pLogFile, "|Rvv|^2\t= %lf  \n", Rvv.r*Rvv.r);
   gf			= 4.0*std_h*std_h*k0z2;
   Rg			= exp(-gf/2.0);
//   fprintf (pPR->pLogFile, "gf\t\t= %lf  \n", gf);
//   fprintf (pPR->pLogFile, "Rg\t\t= %lf  \n", Rg);
   Rhh		= complex_rmul (Rhh, Rg);
   Rvv		= complex_rmul (Rvv, Rg);
//   fprintf (pPR->pLogFile, "|Rhh|^2\t= %lf  \n", Rhh.r*Rhh.r);
//   fprintf (pPR->pLogFile, "|Rvv|^2\t= %lf  \n", Rvv.r*Rvv.r);
   pSG->R1	= c33Matrix_Complex_product (c3Vector_dyadic_product (pSG->chrl, pSG->chil), Rhh);
   pSG->R1	= c33Matrix_sum (pSG->R1, c33Matrix_Complex_product (c3Vector_dyadic_product (pSG->cvrl, pSG->cvil), Rvv));
   pSG->R2	= c33Matrix_Complex_product (c3Vector_dyadic_product (pSG->chsl, pSG->chrlm), Rhh);
   pSG->R2	= c33Matrix_sum (pSG->R2, c33Matrix_Complex_product (c3Vector_dyadic_product (pSG->cvsl, pSG->cvrlm), Rvv));
   /******************/
   /* RCS estimators */
   /******************/
   Zero_SG_Accumulators (pSG);
   return (rtn_value);
}

int		Initialise_Local_Geometry			(LocalGeometry *pLG, PolSARproSim_Record *pPR, int track, double x, double y)
{
   int               rtn_value;
   double				std_h;
   double				k0z, k0z2, k02, kro2, kro;
   Complex           k22, k2, k2z2, k2z, koz2, kez2, koz, kez, ke2, ke, kiz, k12, k1;
   Complex           Rhh, Rvv, delta;
   double				gf, Rg;
   /************************************/
   /* Determine mean surface roughness */
   /************************************/
   switch (POLSARPROSIM_RAYLEIGH_ROUGHNESS_MODEL) {
      case 0:	std_h	= pPR->large_scale_height_stdev; break;
      case 1:	std_h	= pPR->small_scale_height_stdev; break;
      case 2:	std_h	= pPR->small_scale_height_stdev + pPR->large_scale_height_stdev; break;
      default:	std_h	= pPR->small_scale_height_stdev + pPR->large_scale_height_stdev; break;
   }
   /****************************************************************************************/
   /* general track variable, used to point Accumulate_SAR_Contribution to the right track */
   /****************************************************************************************/
   pLG->track        = track;
   /*********************************/
   /* Direct backscatter quantities */
   /*********************************/
   pLG->Pi           = 4.0*atan(1.0);
   pLG->thetai       = pPR->incidence_angle[track];
   pLG->cos_thetai	= cos(pLG->thetai);
   pLG->sin_thetai	= sin(pLG->thetai);
   pLG->p_srange		= pPR->slant_range[track];
   pLG->p_thetai		= pPR->incidence_angle[track];
   pLG->p_height		= pLG->p_srange*cos(pLG->p_thetai);
   pLG->p_grange		= pLG->p_srange*sin(pLG->p_thetai);
   pLG->ki           = Cartesian_Assign_d3Vector (0.0,  pPR->k0*pLG->sin_thetai, -pPR->k0*pLG->cos_thetai);
   pLG->ks           = Cartesian_Assign_d3Vector (0.0,  -pPR->k0*pLG->sin_thetai, pPR->k0*pLG->cos_thetai);
   pLG->ch           = Assign_c3Vector (xy_complex(-1.0, 0.0), xy_complex(0.0, 0.0), xy_complex(0.0, 0.0));
   pLG->cv           = Assign_c3Vector (xy_complex(0.0, 0.0), xy_complex(-pLG->cos_thetai, 0.0), xy_complex(-pLG->sin_thetai, 0.0));
   /*********************************/
   /* Bounce backscatter quantities */
   /*********************************/
   //pLG->n				= Cartesian_Assign_d3Vector (-pPR->slope_x, -pPR->slope_y, 1.0);
   pLG->n            = Lookup_Surface_Normal (pPR, x,y);
   pLG->z				= Cartesian_Assign_d3Vector (0.0, 0.0, 1.0);
   /********************/
   /* FSA wave vectors */
   /********************/
   pLG->kr           = d3Vector_reflect (pLG->ki, pLG->n);
   pLG->krm          = d3Vector_double_multiply (pLG->kr, -1.0);
   /****************************/
   /* FSA polarisation vectors */
   /****************************/
   rtn_value         = Polarisation_Vectors (pLG->ki,  pLG->z, &(pLG->hi),  &(pLG->vi));
   rtn_value         = Polarisation_Vectors (pLG->ks,  pLG->z, &(pLG->hs),  &(pLG->vs));
   rtn_value         = Polarisation_Vectors (pLG->kr,  pLG->z, &(pLG->hr),  &(pLG->vr));
   rtn_value         = Polarisation_Vectors (pLG->krm, pLG->z, &(pLG->hrm), &(pLG->vrm));
   rtn_value         = Polarisation_Vectors (pLG->ki,  pLG->n, &(pLG->hil),  &(pLG->vil));
   rtn_value         = Polarisation_Vectors (pLG->ks,  pLG->n, &(pLG->hsl),  &(pLG->vsl));
   rtn_value         = Polarisation_Vectors (pLG->kr,  pLG->n, &(pLG->hrl),  &(pLG->vrl));
   rtn_value         = Polarisation_Vectors (pLG->krm, pLG->n, &(pLG->hrlm), &(pLG->vrlm));
   pLG->chi          = d3V2c3V (pLG->hi);
   pLG->cvi          = d3V2c3V (pLG->vi);
   pLG->chs          = d3V2c3V (pLG->hs);
   pLG->cvs          = d3V2c3V (pLG->vs);
   pLG->chr          = d3V2c3V (pLG->hr);
   pLG->cvr          = d3V2c3V (pLG->vr);
   pLG->chrm         = d3V2c3V (pLG->hrm);
   pLG->cvrm         = d3V2c3V (pLG->vrm);
   pLG->chil         = d3V2c3V (pLG->hil);
   pLG->cvil         = d3V2c3V (pLG->vil);
   pLG->chsl         = d3V2c3V (pLG->hsl);
   pLG->cvsl         = d3V2c3V (pLG->vsl);
   pLG->chrl         = d3V2c3V (pLG->hrl);
   pLG->cvrl         = d3V2c3V (pLG->vrl);
   pLG->chrlm        = d3V2c3V (pLG->hrlm);
   pLG->cvrlm        = d3V2c3V (pLG->vrlm);
   /*********************************/
   /* Local reflection coefficients */
   /*********************************/
   k0z		= d3Vector_scalar_product (pLG->kr, pLG->n);
   k0z2		= k0z*k0z;
   k02		= pPR->k0*pPR->k0;
   kro2		= k02 - k0z2;
   kro		= sqrt(kro2);
   k22		= complex_rmul (pPR->ground_eps[track], k02);
   k2			= complex_sqrt (k22);
   k2z2		= complex_sub  (k22, xy_complex (kro2, 0.0));
   k2z		= complex_sqrt (k2z2);
   koz2		= Copy_Complex (&(pPR->koz2_short));
   kez2		= Copy_Complex (&(pPR->kez2_short));
   koz		= Copy_Complex (&(pPR->koz_short));
   kez		= Copy_Complex (&(pPR->kez_short));
   ke2		= complex_add  (kez2, xy_complex (kro2, 0.0));
   ke			= complex_sqrt (ke2);
   kiz		= xy_complex   (k0z, 0.0);
   k12		= complex_rmul (pPR->e11_short, k02);
   k1			= complex_sqrt (k12);
   Rhh		= complex_div (complex_sub (koz, k2z), complex_add (koz, k2z));
   delta		= complex_add (complex_mul (kez, k22), complex_mul (k2z, k12));
   Rvv		= complex_div (complex_sub (complex_mul (kez, k22), complex_mul(k2z, k12)), delta);
   gf			= 4.0*std_h*std_h*k0z2;
   Rg			= exp(-gf/2.0);
   Rhh		= complex_rmul (Rhh, Rg);
   Rvv		= complex_rmul (Rvv, Rg);
   pLG->R1	= c33Matrix_Complex_product (c3Vector_dyadic_product (pLG->chrl, pLG->chil), Rhh);
   pLG->R1	= c33Matrix_sum (pLG->R1, c33Matrix_Complex_product (c3Vector_dyadic_product (pLG->cvrl, pLG->cvil), Rvv));
   pLG->R2	= c33Matrix_Complex_product (c3Vector_dyadic_product (pLG->chsl, pLG->chrlm), Rhh);
   pLG->R2	= c33Matrix_sum (pLG->R2, c33Matrix_Complex_product (c3Vector_dyadic_product (pLG->cvsl, pLG->cvrlm), Rvv));
   return (rtn_value);
}


int		Delete_SAR_Geometry			(SarGeometry *pSG)
{
   int		rtn_value;
   
   rtn_value	= Delete_Jnlookup		(&(pSG->Jtable));
   rtn_value	= Delete_Ynlookup		(&(pSG->Ytable));
   return (rtn_value);
}

/***********************************************************************/
/* Temporal Decorrelation Model implementation for branches and leaves */
/***********************************************************************/
int      Model_Change        (Tree *pT, PolSARproSim_Record *pPR, int current_track, d3Vector *motion, double *moisture, double obj_z, unsigned short *pseed)
{
   double      tree_altitude  = pT->base.x[2];           /* tree altitutde (this includes ground height) */
   /* parameters to be computed */
   double      delta_x, delta_y, delta_z;                /* motion offsets */
   double      change_stdev;                             /* standard deviation of the amount of change */
   double      change_mean;                              /* mean of the amount of change */
   double      obj_height;                               /* height of cylinder (branch approximation) that needs to be moved */
   double      motion_damping_factor, moisture_damping_factor; /* damp the motion and moisture */     
   Crown       *pC            = pT->CrownVolume.head;


   if(pPR->Change_Height_Reference == CHANGE_REFERENCE_GROUND){
      obj_height     = obj_z - tree_altitude; 
   }else{
      obj_height     = obj_z - tree_altitude - pC->base.x[2];
   }
   if(obj_height < 0){ 
      obj_height = 0.0;
   }
      
      
   //seed the random number generator
   //this is deliberately keep thread-unsafe to preserve randomness of applied change between tracks
   //srand(rand());

   /* set the damping factor for motion and moisture */
   motion_damping_factor = pPR->SpeciesDataBase[pT->species].branch_rigidity_factor;
   moisture_damping_factor = 1;
   
   /* no change on reference track */
   if(current_track == 0){
      *motion     = Cartesian_Assign_d3Vector	(0.0, 0.0, 0.0);
      *moisture   = 0.0;
   }else{
   
      /***********************************/
      /* Compute components of 3D motion */
      /***********************************/ 
      if(pPR->Position_Change_Model[current_track]       == CHANGE_MODEL_NONE){
         change_stdev   = 0.0;
      }else if(pPR->Position_Change_Model[current_track] == CHANGE_MODEL_POLYNOMIAL){
         change_stdev   = (pPR->motion_coeff_A[current_track] * obj_height * obj_height + pPR->motion_coeff_B[current_track] * obj_height + pPR->motion_coeff_C[current_track]) * motion_damping_factor;
      }else if(pPR->Position_Change_Model[current_track] == CHANGE_MODEL_EXPONENTIAL){
         change_stdev   = (pPR->motion_coeff_A[current_track] * exp(pPR->motion_coeff_B[current_track] * obj_height) + pPR->motion_coeff_C[current_track]) * motion_damping_factor;
      }else{
         change_stdev = 0.0;
      }
      /* realize position change */
      delta_x  = Gaussian_drand_r(0.0, change_stdev, -9*change_stdev, 9*change_stdev, pseed);
      delta_y  = Gaussian_drand_r(0.0, change_stdev, -9*change_stdev, 9*change_stdev, pseed);      
      delta_z  = Gaussian_drand_r(0.0, change_stdev, -9*change_stdev, 9*change_stdev, pseed);
      *motion  = Cartesian_Assign_d3Vector	(delta_x, delta_y, delta_z);
      
      /***************************/
      /* Compute moisture change */
      /***************************/
      if(pPR->Moisture_Change_Model[current_track]       == CHANGE_MODEL_NONE){
         change_mean   = 0.0;
      }else if(pPR->Moisture_Change_Model[current_track] == CHANGE_MODEL_POLYNOMIAL){
         change_mean   = (pPR->moisture_coeff_A[current_track] * obj_height * obj_height + pPR->moisture_coeff_B[current_track] * obj_height + pPR->moisture_coeff_C[current_track]) * moisture_damping_factor;
      }else if(pPR->Moisture_Change_Model[current_track] == CHANGE_MODEL_EXPONENTIAL){
         change_mean   = (pPR->moisture_coeff_A[current_track] * exp(pPR->moisture_coeff_B[current_track] * obj_height) + pPR->moisture_coeff_C[current_track]) * moisture_damping_factor;
      }else{
         change_mean = 0.0;
      }
      if(change_mean > CHANGE_MOISTURE_MAX){
         change_mean = CHANGE_MOISTURE_MAX;
      }
      if(change_mean < CHANGE_MOISTURE_MIN){
         change_mean = CHANGE_MOISTURE_MIN;
      }
      change_stdev   = change_mean * CHANGE_MOISTURE_STDEV_FACTOR;
      /*realize moisture change */
      //*moisture = (drand() - 0.5)*change_stdev*normalizestd + change_mean;
      *moisture = Gaussian_drand_r(change_mean, change_stdev, change_mean-5*change_stdev, change_mean+5*change_stdev, pseed);
   }
   return(NO_POLSARPROSIM_FOREST_ERRORS);
}



/************************************************************/
/* Applying moisture and position changes to cylinders      */
/************************************************************/
double      Change_Cylinder      (Cylinder *pC, Branch *pB, PolSARproSim_Record *pPR, d3Vector motion_offset, double moisture_offset, int current_track)
{
   d3Vector          new_base;
   double            moisture;
   Complex           permittivity;
   d3Vector          orig_base, applied_offset;
#ifdef OUTPUT_CHANGE_STATS_ON
   d3Vector          cyl_centre              = d3Vector_sum (pC->base, d3Vector_double_multiply (pC->axis, 0.5*pC->length));
   double            cyl_x                   = cyl_centre.x[0];
   double            cyl_y                   = cyl_centre.x[1];
   double            cyl_original_height		= cyl_centre.x[2];
   int               change_profile_bin_index;
   int               change_profile_bin_count;
   double            motion_profile_mean;
   double            motion_profile_var;
   double            moisture_profile_mean;
   double            moisture_profile_var;
   double            gnd_hgt;
#endif

   Create_d3Vector(&orig_base);
   Create_d3Vector(&applied_offset);

   /* apply moisture change */
   moisture          = pB->moisture + moisture_offset;
   permittivity      = vegetation_permittivity (moisture, pPR->frequency);
   pC->permittivity	= Copy_Complex (&permittivity);
   
   /* apply position change */
   Copy_d3Vector     (&orig_base, &(pC->base));
   new_base          = d3Vector_sum (pC->base, motion_offset);
   Copy_d3Vector     (&(pC->base), &(new_base));
   applied_offset    = d3Vector_difference (pC->base, orig_base);
   
#ifdef OUTPUT_CHANGE_STATS_ON  
   /* calculate first two moments of the vertical change profiles */
   gnd_hgt                    = ground_height(pPR, cyl_x, cyl_y);
   change_profile_bin_index   = (int)((cyl_original_height-gnd_hgt)/pPR->max_tree_height*(CHANGE_PROFILE_BINS-1));
   if(change_profile_bin_index > (CHANGE_PROFILE_BINS-1)){
      change_profile_bin_index = (CHANGE_PROFILE_BINS-1);
   }
   if(change_profile_bin_index < 0){
      change_profile_bin_index = 0;
   }
   change_profile_bin_index   = change_profile_bin_index*pPR->Tracks+current_track;
   
   //pthread_mutex_lock         (&PolSARproSim_Statmutex);
      /* motion */
      change_profile_bin_count   = pPR->motion_profile_count[change_profile_bin_index];
      motion_profile_mean        = pPR->motion_profile_mean[change_profile_bin_index];
      motion_profile_var         = pPR->motion_profile_var [change_profile_bin_index];
      pPR->motion_profile_mean [change_profile_bin_index] = motion_profile_mean + (applied_offset.x[0] - motion_profile_mean)/(double)(change_profile_bin_count+1);
      pPR->motion_profile_var  [change_profile_bin_index] = motion_profile_var  + (applied_offset.x[0] - motion_profile_mean) * (applied_offset.x[0] - pPR->motion_profile_mean[change_profile_bin_index]); 
      pPR->motion_profile_count[change_profile_bin_index]++;
      /* moisture */
      change_profile_bin_count   = pPR->moisture_profile_count[change_profile_bin_index];
      moisture_profile_mean      = pPR->moisture_profile_mean[change_profile_bin_index];
      moisture_profile_var       = pPR->moisture_profile_var [change_profile_bin_index];
      pPR->moisture_profile_mean [change_profile_bin_index] = moisture_profile_mean + (moisture_offset - moisture_profile_mean)/(double)(change_profile_bin_count+1);
      pPR->moisture_profile_var  [change_profile_bin_index] = moisture_profile_var  + (moisture_offset - moisture_profile_mean) * (moisture_offset - pPR->moisture_profile_mean[change_profile_bin_index]); 
      pPR->moisture_profile_count[change_profile_bin_index]++;
   //pthread_mutex_unlock       (&PolSARproSim_Statmutex);

#endif 

   return(NO_POLSARPROSIM_FOREST_ERRORS);
}

/************************************************************/
/* Applying moisture and position changes to a leaf         */
/************************************************************/
double      Change_Leaf      (Leaf *pL, PolSARproSim_Record *pPR, d3Vector motion_offset, double moisture_offset, int current_track)
{
   d3Vector          new_base;
   double            moisture;
   Complex           permittivity;
   d3Vector          orig_base, applied_offset;
#ifdef OUTPUT_CHANGE_STATS_ON
   double            leaf_x                     = pL->cl.x[0];
   double            leaf_y                     = pL->cl.x[1];
   double            leaf_original_height			= pL->cl.x[2];
   int               change_profile_bin_index;
   int               change_profile_bin_count;
   double            motion_profile_mean;
   double            motion_profile_var;
   double            moisture_profile_mean;
   double            moisture_profile_var;
   double            gnd_hgt;
#endif

   Create_d3Vector(&orig_base);
   Create_d3Vector(&applied_offset);

   /* apply moisture change */
   moisture          = pL->moisture + moisture_offset;
   pL->moisture      = moisture;
   permittivity      = vegetation_permittivity (moisture, pPR->frequency);
   pL->permittivity	= Copy_Complex (&permittivity);
   
   /* apply position change */
   Copy_d3Vector     (&orig_base, &(pL->cl));
   new_base          = d3Vector_sum (pL->cl, motion_offset);
   Copy_d3Vector     (&(pL->cl), &(new_base));
   applied_offset    = d3Vector_difference (pL->cl, orig_base);
   
#ifdef OUTPUT_CHANGE_STATS_ON  
   /* calculate first two moments of the vertical change profiles */
   /* motion */
   gnd_hgt                    = ground_height(pPR, leaf_x, leaf_y);
   pthread_mutex_lock         (&PolSARproSim_Statmutex);
   change_profile_bin_index   = (int)((leaf_original_height-gnd_hgt)/pPR->max_tree_height*CHANGE_PROFILE_BINS-1);
   if(change_profile_bin_index > CHANGE_PROFILE_BINS-1){
      change_profile_bin_index = CHANGE_PROFILE_BINS-1;
   }
   if(change_profile_bin_index < 0){
      change_profile_bin_index = 0;
   }
   change_profile_bin_index   = change_profile_bin_index*pPR->Tracks+current_track;
   change_profile_bin_count   = pPR->motion_profile_count[change_profile_bin_index];
   motion_profile_mean        = pPR->motion_profile_mean[change_profile_bin_index];
   motion_profile_var         = pPR->motion_profile_var [change_profile_bin_index];
   pPR->motion_profile_mean [change_profile_bin_index] = motion_profile_mean + (applied_offset.x[0] - motion_profile_mean)/(double)(change_profile_bin_count+1);
   pPR->motion_profile_var  [change_profile_bin_index] = motion_profile_var  + (applied_offset.x[0] - motion_profile_mean) * (applied_offset.x[0] - pPR->motion_profile_mean[change_profile_bin_index]); 
   pPR->motion_profile_count[change_profile_bin_index]++;
   /* moisture */
   change_profile_bin_count   = pPR->moisture_profile_count[change_profile_bin_index];
   moisture_profile_mean      = pPR->moisture_profile_mean[change_profile_bin_index];
   moisture_profile_var       = pPR->moisture_profile_var [change_profile_bin_index];
   pPR->moisture_profile_mean [change_profile_bin_index] = moisture_profile_mean + (moisture_offset - moisture_profile_mean)/(double)(change_profile_bin_count+1);
   pPR->moisture_profile_var  [change_profile_bin_index] = moisture_profile_var  + (moisture_offset - moisture_profile_mean) * (moisture_offset - pPR->moisture_profile_mean[change_profile_bin_index]); 
   pPR->moisture_profile_count[change_profile_bin_index]++;
   pthread_mutex_unlock       (&PolSARproSim_Statmutex);
#endif 

   return(NO_POLSARPROSIM_FOREST_ERRORS);
}


/***********************************************************/
/* Forest interferometric SAR image calculation definition */
/***********************************************************/

double		Image_Cylinder_Direct	(Cylinder *pC, SarGeometry *pSG, PolSARproSim_Record *pPR, double Sa_scaling, int flag, c4Vector *pSVec)
{
   c33Matrix			Scyl;
   c3Vector          Eh, Ev;
   Complex           Shh, Shv, Svh, Svv;
   d3Vector          cyl_centre			= d3Vector_sum (pC->base, d3Vector_double_multiply (pC->axis, 0.5*pC->length));
#ifdef SWITCH_ATTENUATION_ON
   double				gH, gV;
   int               rtn_lookup;
#endif
   double				cyl_x, cyl_y, cyl_grange, cyl_srange, cyl_height;
   double				focus_x, focus_y, focus_grange, focus_srange, focus_height, focus_angle;
   double				weight_average;
   d3Vector          tip;
   /************************/
   /* Mark cylinder centre */
   /************************/
   cyl_x             = cyl_centre.x[0];
   cyl_y             = cyl_centre.x[1];
   cyl_height			= cyl_centre.x[2];
   /***************************************/
   /* Equivalent upward pointing cylinder */
   /***************************************/
   if(pPR->ForestFastMode[pSG->track] == FOREST_FAST_MODE_OFF){
      if (pC->axis.theta > DPI_RAD/2.0) {
         tip		= d3Vector_sum (pC->base, d3Vector_double_multiply (pC->axis, pC->length));
         pC->axis	= d3Vector_double_multiply (pC->axis, -1.0);
         Assign_Cylinder (pC, pC->length, pC->radius, pC->permittivity, pC->axis, tip);
      }
      /************************************************/
      /* Calculate the cylinder scattering amplitudes */
      /************************************************/
      if (flag == POLSARPROSIM_SAR_INF_TERTIARY_BRANCHES) {
         Scyl				= InfCylSav2	(pC, &(pSG->ks), &(pSG->ki), &(pSG->Ytable), &(pSG->Jtable));
      } else {
         Scyl				= GrgCylSa		(pC, &(pSG->ks), &(pSG->ki));
      }
      Eh					= c33Matrix_c3Vector_product	(Scyl, pSG->ch);
      Ev					= c33Matrix_c3Vector_product	(Scyl, pSG->cv);
      Shh				= c3Vector_scalar_product	(pSG->ch, Eh);
      Shv				= c3Vector_scalar_product	(pSG->ch, Ev);
      Svh				= c3Vector_scalar_product	(pSG->cv, Eh);
      Svv				= c3Vector_scalar_product	(pSG->cv, Ev);
      /***********************************/
      /* Incorporate attenuation effects */
      /***********************************/
#ifdef SWITCH_ATTENUATION_ON
      rtn_lookup		= Lookup_Direct_Attenuation (cyl_centre, pPR, &gH, &gV);
      Shh				= complex_rmul (Shh, gH*gH);
      Shv				= complex_rmul (Shv, gH*gV);
      Svh				= complex_rmul (Svh, gV*gH);
      Svv				= complex_rmul (Svv, gV*gV);
#endif
      /*****************************************/
      /* Incorporate stochastic scaling factor */
      /*****************************************/
      Shh				= complex_rmul (Shh, Sa_scaling);
      Shv				= complex_rmul (Shv, Sa_scaling);
      Svh				= complex_rmul (Svh, Sa_scaling);
      Svv				= complex_rmul (Svv, Sa_scaling);
      if(pSG->track == 0){
         *pSVec      = Assign_c4Vector (Shh, Shv, Svh, Svv);
      }
   }else{
      Shh            = pSVec->z[0];
      Shv            = pSVec->z[1];
      Svh            = pSVec->z[2];
      Svv            = pSVec->z[3];
   }
   /**************************************/
   /* Monitor backscattering coefficient */
   /**************************************/
   pSG->Sigma0HH		+= Shh.r*Shh.r;
   pSG->Sigma0HV		+= Shv.r*Shv.r;
   pSG->Sigma0VH		+= Svh.r*Svh.r;
   pSG->Sigma0VV		+= Svv.r*Svv.r;
   Polar_Assign_Complex (&(pSG->zhhvv), Shh.r*Svv.r, Shh.phi-Svv.phi);
   pSG->AvgShhvv		= complex_add (pSG->AvgShhvv, pSG->zhhvv);
   /******************************************/
   /* Calculate the cylinder centre of focus */
   /******************************************/
   cyl_grange			= pSG->p_grange + cyl_y;
   cyl_srange			= sqrt ((pSG->p_height-cyl_height)*(pSG->p_height-cyl_height) + cyl_grange*cyl_grange);
   focus_grange		= sqrt (cyl_srange*cyl_srange - pSG->p_height*pSG->p_height);
   focus_x           = cyl_x;
   focus_y           = focus_grange - pSG->p_grange;
   focus_height		= 0.0;
   focus_srange		= sqrt ((pSG->p_height-focus_height)*(pSG->p_height-focus_height) + (pSG->p_grange+focus_y)*(pSG->p_grange+focus_y));
   focus_angle       = atan2 (focus_grange, pSG->p_height);
   /***************************************************/
   /* Combine contribution into SAR image accumulator */
   /***************************************************/
   weight_average	= Accumulate_SAR_Contribution (focus_x, focus_y, focus_srange, Shh, Shv, Svv, pPR, pSG->track, focus_angle, (int)SSM_ACCUM_VOL);
   /*****************************/
   /* populate Max Height image */
   /*****************************/
   if(pSG->track == 0){
//      Max_Height_Generation     (focus_x, focus_y, cyl_height, pPR);
      Max_Height_Generation     (cyl_x, cyl_y, cyl_height, pPR);
   }
   return (weight_average);
}

double		Image_Foliage_Direct	(Leaf *pL, SarGeometry *pSG, PolSARproSim_Record *pPR, double Sa_scaling, d3Vector *pLeaf_Depolarization, c4Vector *pSVec)
{
   c33Matrix			Sflg;
   c3Vector			Eh, Ev;
   Complex			Shh, Shv, Svh, Svv;
#ifdef SWITCH_ATTENUATION_ON
   double				gH, gV;
   int				rtn_lookup;
#endif
   double				flg_x, flg_y, flg_grange, flg_srange, flg_height;
   double				focus_x, focus_y, focus_grange, focus_srange, focus_height, focus_angle;
   double				weight_average;
   /*******************************/
   /* Mark foliage element centre */
   /*******************************/
   flg_x				= pL->cl.x[0];
   flg_y				= pL->cl.x[1];
   flg_height			= pL->cl.x[2];
   /***********************************************/
   /* Calculate the foliage scattering amplitudes */
   /***********************************************/
//#ifndef RAYLEIGH_LEAF
//   Sflg				= Leaf_Scattering_Matrix (pL, pPR->Tertiary_leafL1, pPR->Tertiary_leafL2, pPR->Tertiary_leafL3, &(pSG->ki), &(pSG->ks));
//#else
//   Sflg				= Leaf_Scattering_Matrix (pL, pPR->Tertiary_leafL1, pPR->Tertiary_leafL2, pPR->Tertiary_leafL3, &(pSG->ki));
//#endif
   if(pPR->ForestFastMode[pSG->track] == FOREST_FAST_MODE_OFF){
#ifndef RAYLEIGH_LEAF
      Sflg				= Leaf_Scattering_Matrix (pL, pLeaf_Depolarization->x[0], pLeaf_Depolarization->x[1], pLeaf_Depolarization->x[2], &(pSG->ki), &(pSG->ks));
#else
      Sflg				= Leaf_Scattering_Matrix (pL, pLeaf_Depolarization->x[0], pLeaf_Depolarization->x[1], pLeaf_Depolarization->x[2], &(pSG->ki));
#endif
      
      Eh             = c33Matrix_c3Vector_product	(Sflg, pSG->ch);
      Ev             = c33Matrix_c3Vector_product	(Sflg, pSG->cv);
      Shh				= c3Vector_scalar_product	(pSG->ch, Eh);
      Shv				= c3Vector_scalar_product	(pSG->ch, Ev);
      Svh				= c3Vector_scalar_product	(pSG->cv, Eh);
      Svv				= c3Vector_scalar_product	(pSG->cv, Ev);
      /***********************************/
      /* Incorporate attenuation effects */
      /***********************************/
#ifdef SWITCH_ATTENUATION_ON
      rtn_lookup		= Lookup_Direct_Attenuation (pL->cl, pPR, &gH, &gV);
      Shh				= complex_rmul (Shh, gH*gH);
      Shv				= complex_rmul (Shv, gH*gV);
      Svh				= complex_rmul (Svh, gV*gH);
      Svv				= complex_rmul (Svv, gV*gV);
#endif
      /*****************************************/
      /* Incorporate stochastic scaling factor */
      /*****************************************/
      Shh				= complex_rmul (Shh, Sa_scaling);
      Shv				= complex_rmul (Shv, Sa_scaling);
      Svh				= complex_rmul (Svh, Sa_scaling);
      Svv				= complex_rmul (Svv, Sa_scaling);
      if(pSG->track == 0){
         *pSVec      = Assign_c4Vector (Shh, Shv, Svh, Svv);
      }
   }else{
      Shh            = pSVec->z[0];
      Shv            = pSVec->z[1];
      Svh            = pSVec->z[2];
      Svv            = pSVec->z[3];
   }
   /**************************************/
   /* Monitor backscattering coefficient */
   /**************************************/
   pSG->Sigma0HH		+= Shh.r*Shh.r;
   pSG->Sigma0HV		+= Shv.r*Shv.r;
   pSG->Sigma0VH		+= Svh.r*Svh.r;
   pSG->Sigma0VV		+= Svv.r*Svv.r;
   Polar_Assign_Complex (&(pSG->zhhvv), Shh.r*Svv.r, Shh.phi-Svv.phi);
   pSG->AvgShhvv		= complex_add (pSG->AvgShhvv, pSG->zhhvv);
   /******************************************/
   /* Calculate the cylinder centre of focus */
   /******************************************/
   flg_grange			= pSG->p_grange + flg_y;
   flg_srange			= sqrt ((pSG->p_height-flg_height)*(pSG->p_height-flg_height) + flg_grange*flg_grange);
   focus_grange		= sqrt (flg_srange*flg_srange - pSG->p_height*pSG->p_height);
   focus_x           = flg_x;
   focus_y           = focus_grange - pSG->p_grange;
   focus_height		= 0.0;
   focus_srange		= sqrt ((pSG->p_height-focus_height)*(pSG->p_height-focus_height) + (pSG->p_grange+focus_y)*(pSG->p_grange+focus_y));
   focus_angle       = atan2 (focus_grange, pSG->p_height);
   /***************************************************/
   /* Combine contribution into SAR image accumulator */
   /***************************************************/
   weight_average	= Accumulate_SAR_Contribution (focus_x, focus_y, focus_srange, Shh, Shv, Svv, pPR, pSG->track, focus_angle, (int)SSM_ACCUM_VOL);
   /*****************************/
   /* populate Max Height image */
   /*****************************/
   if(pSG->track == 0){
//      Max_Height_Generation     (focus_x, focus_y, flg_height, pPR);
      Max_Height_Generation     (flg_x, flg_y, flg_height, pPR);
   }
   return (weight_average);
}


/*****************************/
/* Ground-volume imaging ... */
/*****************************/

double		Image_Foliage_Bounce	(Leaf *pL, SarGeometry *pSG, PolSARproSim_Record *pPR, double Sa_scaling, d3Vector *pLeaf_Depolarization, c4Vector *pSVec)
{
   d3Vector			flg_centre;
#ifdef SWITCH_ATTENUATION_ON
   int				rtn_lookup;
   double			gHi, gVi, gHr, gVr, gHs, gVs;
#endif
   c33Matrix		Gi	= Idem_c33Matrix ();
   c33Matrix		Gr	= Idem_c33Matrix ();
   c33Matrix		Gs	= Idem_c33Matrix ();
   c3Vector			Eh, Ev;
   Complex			Shh, Shv, Svh, Svv;
   Complex			zhhvv;
   double			flg_x, flg_y, flg_height;
   double			focus_x, focus_y, focus_grange, focus_srange, focus_height, focus_angle;
   double			weight_average	= 0.0;
   Plane				Pg;
   d3Vector			g;
   d3Vector			nm	= d3Vector_double_multiply (pSG->n, -1.0);
   Ray				Rb;
   d3Vector			eff_bounce_centre;
   double			bounce_distance;
   d3Vector			specular_point;
   double			specular_distance;
   double			eff_grange, eff_srange;
   d3Vector			a;
   c33Matrix		Sflg1, Sflg2, SflgT;
   int				rtn_value;
   LocalGeometry  LG;
   d3Vector       snorm_flg;
   /***********************/
   /* Mark foliage centre */
   /***********************/
   Copy_d3Vector	(&flg_centre, &(pL->cl));
   flg_x				= flg_centre.x[0];
   flg_y				= flg_centre.x[1];
   flg_height		= flg_centre.x[2];
   /*****************************************/
   /* Calculate the reflection plane origin */
   /*****************************************/
   g					= Cartesian_Assign_d3Vector (flg_x, flg_y, ground_height(pPR, flg_x, flg_y));
   if (flg_height > g.x[2]) {
      snorm_flg   = Lookup_Surface_Normal (pPR, flg_x,flg_y);
      //Assign_Plane (&Pg, &g, pPR->slope_x, pPR->slope_y);
      Assign_Plane (&Pg, &g, -snorm_flg.x[0]/snorm_flg.x[2], -snorm_flg.x[1]/snorm_flg.x[2]);
      Assign_Ray_d3V (&Rb, &flg_centre, &nm);
      rtn_value			= RayPlaneIntersection (&Rb, &Pg, &eff_bounce_centre, &bounce_distance);
      if ((rtn_value == 1) && (bounce_distance >= 0.0)) {
         a					= d3Vector_normalise (pSG->krm);
         Assign_Ray_d3V (&Rb, &flg_centre, &a);
         rtn_value			= RayPlaneIntersection (&Rb, &Pg, &specular_point, &specular_distance);
         if ((rtn_value == 1) && (specular_distance >= 0.0)) {
            /*********************************************/
            /* Calculate the ground-stem centre of focus */
            /*********************************************/
            eff_grange		= pSG->p_grange + eff_bounce_centre.x[1];
            eff_srange		= sqrt ((pSG->p_height-eff_bounce_centre.x[2])*(pSG->p_height-eff_bounce_centre.x[2]) + eff_grange*eff_grange);
            focus_grange	= sqrt (eff_srange*eff_srange - pSG->p_height*pSG->p_height);
            focus_x			= eff_bounce_centre.x[0];
            focus_y			= focus_grange - pSG->p_grange;
            focus_height	= 0.0;
            focus_srange	= sqrt ((pSG->p_height-focus_height)*(pSG->p_height-focus_height) + (pSG->p_grange+focus_y)*(pSG->p_grange+focus_y));
            focus_angle    = atan2 (focus_grange, pSG->p_height);
            Initialise_Local_Geometry(&LG, pPR, pSG->track, focus_x, focus_y);
            if(pPR->ForestFastMode[pSG->track] == FOREST_FAST_MODE_OFF){
               /******************************************/
               /* Calculate the stem scattering matrices */
               /******************************************/
               //#ifndef RAYLEIGH_LEAF
               //            Sflg1			= Leaf_Scattering_Matrix (pL, pPR->Tertiary_leafL1, pPR->Tertiary_leafL2, pPR->Tertiary_leafL3, &(pSG->kr), &(pSG->ks));
               //            Sflg2			= Leaf_Scattering_Matrix (pL, pPR->Tertiary_leafL1, pPR->Tertiary_leafL2, pPR->Tertiary_leafL3, &(pSG->ki), &(pSG->krm));
               //#else
               //            Sflg1			= Leaf_Scattering_Matrix (pL, pPR->Tertiary_leafL1, pPR->Tertiary_leafL2, pPR->Tertiary_leafL3, &(pSG->kr));
               //            Sflg2			= Leaf_Scattering_Matrix (pL, pPR->Tertiary_leafL1, pPR->Tertiary_leafL2, pPR->Tertiary_leafL3, &(pSG->ki));
               //#endif
#ifndef RAYLEIGH_LEAF
               Sflg1			= Leaf_Scattering_Matrix (pL, pLeaf_Depolarization->x[0],  pLeaf_Depolarization->x[1], pLeaf_Depolarization->x[2], &(LG.kr), &(LG.ks));
               Sflg2			= Leaf_Scattering_Matrix (pL, pLeaf_Depolarization->x[0],  pLeaf_Depolarization->x[1], pLeaf_Depolarization->x[2], &(LG.ki), &(LG.krm));
#else
               Sflg1			= Leaf_Scattering_Matrix (pL, pLeaf_Depolarization->x[0],  pLeaf_Depolarization->x[1], pLeaf_Depolarization->x[2], &(LG.kr));
               Sflg2			= Leaf_Scattering_Matrix (pL, pLeaf_Depolarization->x[0],  pLeaf_Depolarization->x[1], pLeaf_Depolarization->x[2], &(LG.ki));
#endif
               
               /**********************************/
               /* Calculate attenuation matrices */
               /**********************************/
#ifdef SWITCH_ATTENUATION_ON
               rtn_lookup		= Lookup_Direct_Attenuation (specular_point, pPR, &gHi, &gVi);
               rtn_lookup		= Lookup_Bounce_Attenuation (flg_centre,     pPR, &gHr, &gVr);
               rtn_lookup		= Lookup_Direct_Attenuation (flg_centre,     pPR, &gHs, &gVs);
               Gi				= c33Matrix_Complex_product (c3Vector_dyadic_product (LG.chi, LG.chi), xy_complex (gHi, 0.0));
               Gi				= c33Matrix_sum (Gi, c33Matrix_Complex_product (c3Vector_dyadic_product (LG.cvi, LG.cvi), xy_complex (gVi, 0.0)));
               Gr				= c33Matrix_Complex_product (c3Vector_dyadic_product (LG.chr, LG.chr), xy_complex (gHr, 0.0));
               Gr				= c33Matrix_sum (Gr, c33Matrix_Complex_product (c3Vector_dyadic_product (LG.cvr, LG.cvr), xy_complex (gVr, 0.0)));
               Gs				= c33Matrix_Complex_product (c3Vector_dyadic_product (LG.chs, LG.chs), xy_complex (gHs, 0.0));
               Gs				= c33Matrix_sum (Gs, c33Matrix_Complex_product (c3Vector_dyadic_product (LG.cvs, LG.cvs), xy_complex (gVs, 0.0)));
#endif
               /*******************************************************************/
               /* Incorporate reflection and attenuation into scattering matrices */
               /*******************************************************************/
               Sflg1			= c33Matrix_product (Gs, Sflg1);
               Sflg1			= c33Matrix_product (Sflg1, Gr);
               Sflg1			= c33Matrix_product (Sflg1, LG.R1);
               Sflg1			= c33Matrix_product (Sflg1, Gi);
               Sflg2			= c33Matrix_product (Sflg2, Gs);
               Sflg2			= c33Matrix_product (Gr, Sflg2);
               Sflg2			= c33Matrix_product (LG.R2, Sflg2);
               Sflg2			= c33Matrix_product (Gi, Sflg2);
               SflgT			= c33Matrix_sum     (Sflg1, Sflg2);
               /**************************************************/
               /* Calculate the scatterimg amplitudes in the FSA */
               /**************************************************/
               Eh				= c33Matrix_c3Vector_product (SflgT, LG.chi);
               Ev				= c33Matrix_c3Vector_product (SflgT, LG.cvi);
               Shh				= c3Vector_scalar_product (LG.chs, Eh);
               Shv				= c3Vector_scalar_product (LG.chs, Ev);
               Svh				= c3Vector_scalar_product (LG.cvs, Eh);
               Svv				= c3Vector_scalar_product (LG.cvs, Ev);
               /*****************************************/
               /* Incorporate stochastic scaling factor */
               /*****************************************/
               Shh				= complex_rmul (Shh, Sa_scaling);
               Shv				= complex_rmul (Shv, Sa_scaling);
               Svh				= complex_rmul (Svh, Sa_scaling);
               Svv				= complex_rmul (Svv, Sa_scaling);
               /************************************************/
               /* Convert the scattering amplitudes to the BSA */
               /************************************************/
               Shh				= complex_rmul (Shh, -1.0);
               Shv				= complex_rmul (Shv, -1.0);
               if(pSG->track == 0){
                  *pSVec      = Assign_c4Vector (Shh, Shv, Svh, Svv);
               }
            }else{
               Shh            = pSVec->z[0];
               Shv            = pSVec->z[1];
               Svh            = pSVec->z[2];
               Svv            = pSVec->z[3];
            }
            /**************************************/
            /* Monitor backscattering coefficient */
            /**************************************/
            pSG->Sigma0HH	+= Shh.r*Shh.r;
            pSG->Sigma0HV	+= Shv.r*Shv.r;
            pSG->Sigma0VH	+= Svh.r*Svh.r;
            pSG->Sigma0VV	+= Svv.r*Svv.r;
            Polar_Assign_Complex (&zhhvv, Shh.r*Svv.r, Shh.phi-Svv.phi);
            pSG->AvgShhvv	= complex_add (pSG->AvgShhvv, zhhvv);
            /***************************************************/
            /* Combine contribution into SAR image accumulator */
            /***************************************************/
            weight_average	= Accumulate_SAR_Contribution (focus_x, focus_y, focus_srange, Shh, Shv, Svv, pPR, pSG->track, focus_angle, (int)SSM_ACCUM_GND);
            /*****************************/
            /* populate Max Height image */
            /*****************************/
            if(pSG->track == 0){
//               Max_Height_Generation     (focus_x, focus_y, flg_height, pPR);
               Max_Height_Generation     (flg_x, flg_y, flg_height, pPR);
            }
         }
      }
   }
   /*****************************/
   /* Return to calling routine */
   /*****************************/
   return		(weight_average);
}

double		Image_Cylinder_Bounce	(Cylinder *pC, SarGeometry *pSG, PolSARproSim_Record *pPR, double Sa_scaling, int flag, c4Vector *pSVec)
{
   d3Vector			cyl_centre			= d3Vector_sum (pC->base, d3Vector_double_multiply (pC->axis, 0.5*pC->length));
#ifdef SWITCH_ATTENUATION_ON
   int				rtn_lookup;
   double			gHi, gVi, gHr, gVr, gHs, gVs;
#endif
   c33Matrix		Gi	= Idem_c33Matrix ();
   c33Matrix		Gr	= Idem_c33Matrix ();
   c33Matrix		Gs	= Idem_c33Matrix ();
   c3Vector			Eh, Ev;
   Complex			Shh, Shv, Svh, Svv;
   Complex			zhhvv;
   double			cyl_x, cyl_y, cyl_height;
   double			focus_x, focus_y, focus_grange, focus_srange, focus_height, focus_angle;
   double			weight_average	= 0.0;
   Plane				Pg;
   d3Vector			g;
   d3Vector			nm	= d3Vector_double_multiply (pSG->n, -1.0);
   Ray				Rb;
   d3Vector			eff_bounce_centre;
   double			bounce_distance;
   d3Vector			specular_point;
   double			specular_distance;
   double			eff_grange, eff_srange;
   d3Vector			a;
   c33Matrix		Scyl1, Scyl2, ScylT;
   int				rtn_value;
   d3Vector       snorm_cyl;
   d3Vector			tip;
   d3Vector			hil,  vil,  hsl,  vsl;
   d3Vector			hrpl, vrpl, hrml, vrml;
   c3Vector			chil,  cvil,  chsl,  cvsl;
   c3Vector			chrpl, cvrpl, chrml, cvrml;
   Complex			fhhml, fhvml, fvhml, fvvml;
   Complex			fhhpl, fhvpl, fvhpl, fvvpl;
   LocalGeometry  LG;
   /************************/
   /* Mark cylinder centre */
   /************************/
   cyl_x				= cyl_centre.x[0];
   cyl_y				= cyl_centre.x[1];
   cyl_height		= cyl_centre.x[2];
   /***************************************/
   /* Equivalent upward pointing cylinder */
   /***************************************/
   if (pC->axis.theta > DPI_RAD/2.0) {
      tip		= d3Vector_sum (pC->base, d3Vector_double_multiply (pC->axis, pC->length));
      pC->axis	= d3Vector_double_multiply (pC->axis, -1.0);
      Assign_Cylinder (pC, pC->length, pC->radius, pC->permittivity, pC->axis, tip);
   }
   /*****************************************/
   /* Calculate the reflection plane origin */
   /*****************************************/
   g					= Cartesian_Assign_d3Vector (cyl_x, cyl_y, ground_height(pPR, cyl_x, cyl_y));
   if (cyl_height > g.x[2]) {
      snorm_cyl   = Lookup_Surface_Normal (pPR, cyl_x,cyl_y);
      //Assign_Plane (&Pg, &g, pPR->slope_x, pPR->slope_y);
      Assign_Plane (&Pg, &g, -snorm_cyl.x[0]/snorm_cyl.x[2], -snorm_cyl.x[1]/snorm_cyl.x[2]);
      Assign_Ray_d3V (&Rb, &cyl_centre, &nm);
      rtn_value			= RayPlaneIntersection (&Rb, &Pg, &eff_bounce_centre, &bounce_distance);
      if ((rtn_value == 1) && (bounce_distance >= 0.0)) {
         a					= d3Vector_normalise (pSG->krm);
         Assign_Ray_d3V (&Rb, &cyl_centre, &a);
         rtn_value			= RayPlaneIntersection (&Rb, &Pg, &specular_point, &specular_distance);
         if ((rtn_value == 1) && (specular_distance >= 0.0)) {
            /*********************************************/
            /* Calculate the ground-stem centre of focus */
            /*********************************************/
            eff_grange		= pSG->p_grange + eff_bounce_centre.x[1];
            eff_srange		= sqrt ((pSG->p_height-eff_bounce_centre.x[2])*(pSG->p_height-eff_bounce_centre.x[2]) + eff_grange*eff_grange);
            focus_grange	= sqrt (eff_srange*eff_srange - pSG->p_height*pSG->p_height);
            focus_x			= eff_bounce_centre.x[0];
            focus_y			= focus_grange - pSG->p_grange;
            focus_height	= 0.0;
            focus_srange	= sqrt ((pSG->p_height-focus_height)*(pSG->p_height-focus_height) + (pSG->p_grange+focus_y)*(pSG->p_grange+focus_y));
            focus_angle    = atan2 (focus_grange, pSG->p_height);
            Initialise_Local_Geometry(&LG, pPR, pSG->track, focus_x, focus_y);
            if(pPR->ForestFastMode[pSG->track] == FOREST_FAST_MODE_OFF){
               /***********************************************************/
               /* Additional wave and cylinder local polarisation vectors */
               /***********************************************************/
               rtn_value		= Polarisation_Vectors (LG.ki,  pC->axis, &hil,   &vil);
               rtn_value		= Polarisation_Vectors (LG.ks,  pC->axis, &hsl,   &vsl);
               rtn_value		= Polarisation_Vectors (LG.kr,  pC->axis, &hrpl,  &vrpl);
               rtn_value		= Polarisation_Vectors (LG.krm, pC->axis, &hrml,  &vrml);
               chil           = d3V2c3V (hil);
               cvil           = d3V2c3V (vil);
               chsl           = d3V2c3V (hsl);
               cvsl           = d3V2c3V (vsl);
               chrpl          = d3V2c3V (hrpl);
               cvrpl          = d3V2c3V (vrpl);
               chrml          = d3V2c3V (hrml);
               cvrml          = d3V2c3V (vrml);
               /******************************************/
               /* Calculate the stem scattering matrices */
               /******************************************/
               if (flag == POLSARPROSIM_SAR_INF_TERTIARY_BRANCHES) {
                  Scyl2			= InfCylSav3	(pC, &(LG.krm), &(LG.ki), &(pSG->Ytable), &(pSG->Jtable), &fhhml, &fhvml, &fvhml, &fvvml);
                  fhhpl			= Copy_Complex (&fhhml);
                  fhvpl			= complex_rmul (fvhml, -1.0);
                  fvhpl			= complex_rmul (fhvml, -1.0);
                  fvvpl			= Copy_Complex (&fvvml);
                  Scyl1			= c33Matrix_Complex_product (c3Vector_dyadic_product (chsl, chrpl), fhhpl);
                  Scyl1			= c33Matrix_sum  (Scyl1, c33Matrix_Complex_product (c3Vector_dyadic_product (chsl, cvrpl), fhvpl));
                  Scyl1			= c33Matrix_sum  (Scyl1, c33Matrix_Complex_product (c3Vector_dyadic_product (cvsl, chrpl), fvhpl));
                  Scyl1			= c33Matrix_sum  (Scyl1, c33Matrix_Complex_product (c3Vector_dyadic_product (cvsl, cvrpl), fvvpl));
               } else {
                  Scyl1			= GrgCylSa		(pC, &(LG.ks),  &(LG.kr));
                  Scyl2			= GrgCylSa		(pC, &(LG.krm), &(LG.ki));
               }
               /**********************************/
               /* Calculate attenuation matrices */
               /**********************************/
#ifdef SWITCH_ATTENUATION_ON
               rtn_lookup		= Lookup_Direct_Attenuation (specular_point, pPR, &gHi, &gVi);
               rtn_lookup		= Lookup_Bounce_Attenuation (cyl_centre,     pPR, &gHr, &gVr);
               rtn_lookup		= Lookup_Direct_Attenuation (cyl_centre,     pPR, &gHs, &gVs);
               Gi             = c33Matrix_Complex_product (c3Vector_dyadic_product (LG.chi, LG.chi), xy_complex (gHi, 0.0));
               Gi             = c33Matrix_sum (Gi, c33Matrix_Complex_product (c3Vector_dyadic_product (LG.cvi, LG.cvi), xy_complex (gVi, 0.0)));
               Gr             = c33Matrix_Complex_product (c3Vector_dyadic_product (LG.chr, LG.chr), xy_complex (gHr, 0.0));
               Gr             = c33Matrix_sum (Gr, c33Matrix_Complex_product (c3Vector_dyadic_product (LG.cvr, LG.cvr), xy_complex (gVr, 0.0)));
               Gs             = c33Matrix_Complex_product (c3Vector_dyadic_product (LG.chs, LG.chs), xy_complex (gHs, 0.0));
               Gs             = c33Matrix_sum (Gs, c33Matrix_Complex_product (c3Vector_dyadic_product (LG.cvs, LG.cvs), xy_complex (gVs, 0.0)));
#endif
               /*******************************************************************/
               /* Incorporate reflection and attenuation into scattering matrices */
               /*******************************************************************/
               Scyl1          = c33Matrix_product (Gs, Scyl1);
               Scyl1          = c33Matrix_product (Scyl1, Gr);
               Scyl1          = c33Matrix_product (Scyl1, LG.R1);
               Scyl1          = c33Matrix_product (Scyl1, Gi);
               Scyl2          = c33Matrix_product (Scyl2, Gs);
               Scyl2          = c33Matrix_product (Gr, Scyl2);
               Scyl2          = c33Matrix_product (LG.R2, Scyl2);
               Scyl2          = c33Matrix_product (Gi, Scyl2);
               ScylT          = c33Matrix_sum     (Scyl1, Scyl2);
               /**************************************************/
               /* Calculate the scatterimg amplitudes in the FSA */
               /**************************************************/
               Eh             = c33Matrix_c3Vector_product (ScylT, LG.chi);
               Ev             = c33Matrix_c3Vector_product (ScylT, LG.cvi);
               Shh				= c3Vector_scalar_product (LG.chs, Eh);
               Shv				= c3Vector_scalar_product (LG.chs, Ev);
               Svh				= c3Vector_scalar_product (LG.cvs, Eh);
               Svv				= c3Vector_scalar_product (LG.cvs, Ev);
               /*****************************************/
               /* Incorporate stochastic scaling factor */
               /*****************************************/
               Shh				= complex_rmul (Shh, Sa_scaling);
               Shv				= complex_rmul (Shv, Sa_scaling);
               Svh				= complex_rmul (Svh, Sa_scaling);
               Svv				= complex_rmul (Svv, Sa_scaling);
               /************************************************/
               /* Convert the scattering amplitudes to the BSA */
               /************************************************/
               Shh				= complex_rmul (Shh, -1.0);
               Shv				= complex_rmul (Shv, -1.0);
               if(pSG->track == 0){
                  *pSVec      = Assign_c4Vector (Shh, Shv, Svh, Svv);
               }
            }else{
               Shh            = pSVec->z[0];
               Shv            = pSVec->z[1];
               Svh            = pSVec->z[2];
               Svv            = pSVec->z[3];
            }
            /**************************************/
            /* Monitor backscattering coefficient */
            /**************************************/
            pSG->Sigma0HH	+= Shh.r*Shh.r;
            pSG->Sigma0HV	+= Shv.r*Shv.r;
            pSG->Sigma0VH	+= Svh.r*Svh.r;
            pSG->Sigma0VV	+= Svv.r*Svv.r;
            Polar_Assign_Complex (&zhhvv, Shh.r*Svv.r, Shh.phi-Svv.phi);
            pSG->AvgShhvv	= complex_add (pSG->AvgShhvv, zhhvv);
            /***************************************************/
            /* Combine contribution into SAR image accumulator */
            /***************************************************/
            weight_average	= Accumulate_SAR_Contribution (focus_x, focus_y, focus_srange, Shh, Shv, Svv, pPR, pSG->track, focus_angle, (int)SSM_ACCUM_GND);
            /*****************************/
            /* populate Max Height image */
            /*****************************/            
            if(pSG->track == 0){
               //Max_Height_Generation     (focus_x, focus_y, cyl_height, pPR);
               Max_Height_Generation     (cyl_x, cyl_y, cyl_height, pPR);
            }
         }
      }
   }
   /*****************************/
   /* Return to calling routine */
   /*****************************/
   return		(weight_average);
}

//int		Image_Tree_Bounce		(Tree *pT, SarGeometry *pSG, PolSARproSim_Record *pPR)
//{
//   const double		bsecl	=	POLSARPROSIM_SAR_BRANCH_FACTOR*(pPR->azimuth_resolution + pPR->slant_range_resolution);
//   long              iBranch;
//   Branch            *pB;
//   int               Nsections;
//   int               i_section;
//   double            deltat, deltar;
//   Cylinder          cyl1;
//   double            weight_sum;
//   double            weight_count;
//   double            weight_avg;
//   int               rtn_value;
//   int               Cscatt_Flag;
//   double            tb_scaling;
//   double            flg_scaling;
//   long              iLeaf;
//   Leaf              *pL;
//   double            leafL1, leafL2, leafL3;       //to calculate leaf depolarization factors
//   d3Vector          Ldvec;
//   c4Vector          Sbounce;             //bounce scattering vectors S = [Shh, Shv, Svh, Svv]
//   /************************************
//    ** This part edited out along with **
//    ** the Tertiary imaging section    **
//    ** code                  --RAedit  **
//    #ifndef POLSARPROSIM_NO_SAR_TERTIARIES
//    Branch				tertiary_branch;
//    double				tertiary_branch_length, tertiary_branch_radius;
//    long         n_Tertiary;
//    double				tertiary_moisture;
//    Complex			tertiary_permittivity;
//    #endif
//    ************************************/
//   /************************************
//    ** This part edited out along with **
//    ** the Foliage imaging section     **
//    ** code                  --RAedit  **
//    #ifndef POLSARPROSIM_NO_SAR_FOLIAGE
//    long           n_Leaves;
//    int            L_species;
//    double         leaf_d1, leaf_d2, leaf_d3;
//    double         L_moisture;
//    Complex        L_permittivity;
//    Leaf           tree_leaf;
//    #endif
//    ************************************/
//   
//   /************************/
//   /* Initialise variables */
//   /************************/
//   Create_Cylinder (&cyl1);
//   Create_d3Vector (&Ldvec);
//   Create_c4Vector (&Sbounce);
//#ifndef FORCE_GRG_CYLINDERS
//   Cscatt_Flag	= POLSARPROSIM_SAR_INF_TERTIARY_BRANCHES;
//#else
//   Cscatt_Flag	= POLSARPROSIM_SAR_GRG_TERTIARY_BRANCHES;
//#endif
//   /*******************/
//   /* Image the stems */
//   /*******************/
//#ifndef POLSARPROSIM_NO_SAR_STEMS
//   if (pT->Stem.head != NULL_PTR2BRANCH_LIST){ /* Image stem if it exists */  
//      pB			= pT->Stem.head;
//      weight_sum	= 0.0;
//      weight_count	= 0.0;
//      for (iBranch=0L; iBranch < pT->Stem.n; iBranch++) {
//         Nsections	= (int) (pB->l/bsecl) + 1;
//         deltat		= 1.0 / (double) Nsections;
//         deltar		= (pB->start_radius - pB->end_radius) / (double) Nsections;
//         for (i_section = 0; i_section < Nsections; i_section++) {
//            rtn_value		= Cylinder_from_Branch (&cyl1, pB, i_section, Nsections);
//            weight_sum		+= Image_Cylinder_Bounce (&cyl1, pSG, pPR, 1.0, Cscatt_Flag, &Sbounce);
//            weight_count	+= 1.0;
//         }
//         pB			= pB->next;
//      }
//      weight_avg	= weight_sum/weight_count;
//   }
//#endif
//   /**************************/
//   /* Image primary branches */
//   /**************************/
//#ifndef POLSARPROSIM_NO_SAR_PRIMARIES
//   /****** Image the dry part ********/
//    if(pT->Dry.head != NULL_PTR2BRANCH_LIST) { /* Only image the dry crown if it exists. Checking this way removes reliance on species definition  --RAedit  */
//      pB           = pT->Dry.head;
//      weight_sum	= 0.0;
//      weight_count	= 0.0;
//      for (iBranch=0L; iBranch < pT->Dry.n; iBranch++) {
//         Nsections	= (int) (pB->l/bsecl) + 1;
//         deltat		= 1.0 / (double) Nsections;
//         deltar		= (pB->start_radius - pB->end_radius) / (double) Nsections;
//         for (i_section = 0; i_section < Nsections; i_section++) {
//            rtn_value		= Cylinder_from_Branch (&cyl1, pB, i_section, Nsections);
//            weight_sum		+= Image_Cylinder_Bounce (&cyl1, pSG, pPR, 1.0, Cscatt_Flag, &Sbounce);
//            weight_count	+= 1.0;
//         }
//         pB			= pB->next;
//      }
//      weight_avg	= weight_sum/weight_count;
//   }
//   /****** Image the live part *****/
//   if(pT->Primary.head != NULL_PTR2BRANCH_LIST){ /* Image wet primary branches only if they exist   */
//      pB			= pT->Primary.head;
//      weight_sum	= 0.0;
//      weight_count	= 0.0;
//      for (iBranch=0L; iBranch < pT->Primary.n; iBranch++) {
//         Nsections	= (int) (pB->l/bsecl) + 1;
//         deltat		= 1.0 / (double) Nsections;
//         deltar		= (pB->start_radius - pB->end_radius) / (double) Nsections;
//         for (i_section = 0; i_section < Nsections; i_section++) {
//            rtn_value		= Cylinder_from_Branch (&cyl1, pB, i_section, Nsections);
//            weight_sum		+= Image_Cylinder_Bounce (&cyl1, pSG, pPR, 1.0, Cscatt_Flag, &Sbounce);
//            weight_count	+= 1.0;
//         }
//         pB			= pB->next;
//      }
//      weight_avg	= weight_sum/weight_count;
//   }
//#endif
//   /****************************/
//   /* Image secondary branches */
//   /****************************/
//#ifndef POLSARPROSIM_NO_SAR_SECONDARIES
//   if(pT->Secondary.head != NULL_PTR2BRANCH){ /* Image secondary branches only if they exist  */
//      pB			= pT->Secondary.head;
//      weight_sum	= 0.0;
//      weight_count	= 0.0;
//      for (iBranch=0L; iBranch < pT->Secondary.n; iBranch++) {
//         Nsections	= (int) (pB->l/bsecl) + 1;
//         deltat		= 1.0 / (double) Nsections;
//         deltar		= (pB->start_radius - pB->end_radius) / (double) Nsections;
//         for (i_section = 0; i_section < Nsections; i_section++) {
//            rtn_value		= Cylinder_from_Branch (&cyl1, pB, i_section, Nsections);
//            weight_sum		+= Image_Cylinder_Bounce (&cyl1, pSG, pPR, 1.0, Cscatt_Flag, &Sbounce);
//            weight_count	+= 1.0;
//         }
//         pB			= pB->next;
//      }
//      weight_avg	= weight_sum/weight_count;
//   }
//#endif
//   /***************************/
//   /* Image tertiary branches */
//   /***************************/
//#ifndef POLSARPROSIM_NO_SAR_TERTIARIES
//#ifndef FORCE_GRG_CYLINDERS
//   if (pPR->Grg_Flag == 0) {
//      Cscatt_Flag	=    POLSARPROSIM_SAR_GRG_TERTIARY_BRANCHES;
//   } else {
//      Cscatt_Flag	=    POLSARPROSIM_SAR_INF_TERTIARY_BRANCHES;
//   }
//#endif
//   
//   /***************************************************
//    ** This part is commented out so tertiaries from  **
//    ** the link-list created by Realise_Tertiaries()  **
//    ** are imaged instead of being regenerated here.  **
//    ** This removes the dependence of imaging code    **
//    ** on tree species.                               **
//    **                                       --RAedit **
//    ****************************************************
//    
//    tb_scaling				= Estimate_SAR_Tertiaries (pT, pPR, &n_Tertiary, &tertiary_branch_length, &tertiary_branch_radius);
//    weight_sum				= 0.0;
//    weight_count			= 0.0;
//    pB						= &tertiary_branch;
//    Create_Branch (pB);
//    tertiary_moisture		= Tertiary_Branch_Moisture (pT->species);
//    tertiary_permittivity	= vegetation_permittivity (tertiary_moisture, pPR->frequency);
//    for (iBranch=0L; iBranch < n_Tertiary; iBranch++) {
//    if (pT->species != POLSARPROSIM_HEDGE) {
//    tertiary_moisture		= Tertiary_Branch_Moisture (pT->species);
//    tertiary_permittivity	= vegetation_permittivity (tertiary_moisture, pPR->frequency);
//    }
//    rtn_value				= Realise_Tertiary_Branch (pT, pPR, pB, tertiary_branch_length, tertiary_branch_radius, tertiary_moisture, tertiary_permittivity);
//    if (rtn_value == NO_RAYCROWN_ERRORS) {
//    Nsections			= (int) (pB->l/bsecl) + 1;
//    deltat				= 1.0 / (double) Nsections;
//    deltar				= (pB->start_radius - pB->end_radius) / (double) Nsections;
//    for (i_section = 0; i_section < Nsections; i_section++) {
//    rtn_value			 = Cylinder_from_Branch (&cyl1, pB, i_section, Nsections);
//    weight_sum			+= Image_Cylinder_Bounce (&cyl1, pSG, pPR, tb_scaling, Cscatt_Flag);
//    weight_count		+= 1.0;
//    }
//    pB = pB->next;
//    }
//    }
//    weight_avg		= weight_sum/weight_count;
//    Destroy_Branch (pB);
//    *****************************************--RAedit**/
//   
//   if(pT->Tertiary.head != NULL_PTR2BRANCH){
//      weight_sum				= 0.0;
//      weight_count			= 0.0;
//      pB                = pT->Tertiary.head;
//      tb_scaling        = pT->Tertiary.scale_factor;  /* New addition to the Branch_list structure --RAedit */
//      
//      for (iBranch=0L; iBranch < pT->Tertiary.n; iBranch++) {
//         Nsections       = (int) (pB->l/bsecl) + 1;
//         deltat          = 1.0 / (double) Nsections;
//         deltar          = (pB->start_radius - pB->end_radius) / (double) Nsections;
//         for (i_section = 0; i_section < Nsections; i_section++) {
//            rtn_value			= Cylinder_from_Branch (&cyl1, pB, i_section, Nsections);
//            weight_sum			+= Image_Cylinder_Bounce (&cyl1, pSG, pPR, tb_scaling, Cscatt_Flag, &Sbounce);
//            weight_count		+= 1.0;
//         }
//         pB = pB->next;
//      }
//      weight_avg		= weight_sum/weight_count;
//   }
//#endif
//   
//   /*****************/
//   /* Image foliage */
//   /*****************/
//#ifndef POLSARPROSIM_NO_SAR_FOLIAGE
//   /***************************************************
//    ** This part is commented out so leaves from      **
//    ** the link-list created by Realise_Foliage()     **
//    ** are imaged instead of being regenerated here.  **
//    ** This removes the dependence of imaging code    **
//    ** on tree species.                               **
//    **                                       --RAedit **
//    ****************************************************
//    
//    L_species		= Leaf_Species		(pT->species);
//    leaf_d1		= Leaf_Dimension_1	(pT->species);
//    leaf_d2		= Leaf_Dimension_2	(pT->species);
//    leaf_d3		= Leaf_Dimension_3	(pT->species);
//    L_moisture		= Leaf_Moisture		(pT->species);
//    L_permittivity	= vegetation_permittivity (L_moisture, pPR->frequency);
//    pL				= &tree_leaf;
//    Create_Leaf (pL);
//    flg_scaling	= Estimate_SAR_Foliage (pT, pPR, &n_Leaves);
//    weight_sum		= 0.0;
//    weight_count	= 0.0;
//    printf("No of Imaging Leaves: %ld\n", n_Leaves);
//    for (iLeaf=0L; iLeaf < n_Leaves; iLeaf++) {
//    if (pT->species != POLSARPROSIM_HEDGE) {
//    L_moisture		= Leaf_Moisture	(pT->species);
//    L_permittivity	= vegetation_permittivity (L_moisture, pPR->frequency);
//    }
//    rtn_value		= Realise_Foliage_Element (pT, pPR, pL, L_species, leaf_d1, leaf_d2, leaf_d3, L_moisture, L_permittivity);
//    if (rtn_value == NO_RAYCROWN_ERRORS) {
//    weight_sum	+= Image_Foliage_Bounce (pL, pSG, pPR, flg_scaling);
//    weight_count	+= 1.0;
//    }
//    }
//    Destroy_Leaf (pL);
//    *****************************************--RAedit**/
//   
//   if(pT->Foliage.head != NULL_PTR2LEAF_LIST){
//      weight_sum		= 0.0;
//      weight_count	= 0.0;
//      pL           = pT->Foliage.head;
//      flg_scaling  = pT->Foliage.scale_factor;
//      for (iLeaf=0L; iLeaf < pT->Foliage.n; iLeaf++) {
//         Leaf_Depolarization_Factors (pL, &leafL1, &leafL2, &leafL3);
////         pPR->Tertiary_leafL1	= leafL1;
////         pPR->Tertiary_leafL2	= leafL2;
////         pPR->Tertiary_leafL3	= leafL3;
//         Ldvec = Cartesian_Assign_d3Vector(leafL1, leafL2, leafL3);
//         weight_sum          += Image_Foliage_Bounce (pL, pSG, pPR, flg_scaling, &Ldvec, &Sbounce);
//         weight_count        += 1.0;
//         pL                   = pL->next;
//      }
//   }
//   
//#endif
//   /***************/
//   /* Tidy up ... */
//   /***************/
//   Destroy_Cylinder (&cyl1);
//   /*****************************/
//   /* Return to calling routine */
//   /*****************************/
//   return (NO_POLSARPROSIM_FOREST_ERRORS);
//}
//
//int		PolSARproSim_Forest_Bounce		(PolSARproSim_Record *pPR)
//{
//   Tree			tree1;
//   int			itree;
//   SarGeometry	SG1;
//   int			rtn_value;
//   /**********************/
//   /* Imaging the forest */
//   /**********************/
//#ifdef VERBOSE_POLSARPROSIM
//   printf ("\n");
//   printf ("Call to PolSARproSim_Forest_Bounce ... \n");
//   printf ("\n");
//#endif
//   fprintf (pPR->pLogFile, "Call to PolSARproSim_Forest_Bounce ...\n");
//   fflush  (pPR->pLogFile);
//   /**********************************/
//   /* Set up the SAR geometry record */
//   /**********************************/
//   rtn_value	= Initialise_SAR_Geometry (&SG1, pPR, pPR->current_track);
//   /********************************/
//   /* Seed random number generator */
//   /********************************/
//   srand (pPR->seed);
//   /**************************/
//   /* Main tree imaging loop */
//   /**************************/
//   Create_Tree (&tree1);
//   for (itree=0; itree<pPR->Trees; itree++) {
//      Realise_Tree		(&tree1, itree, pPR);
//      Image_Tree_Bounce	(&tree1, &SG1, pPR);
//   }
//   Destroy_Tree (&tree1);
//   /***********************/
//   /* Monitor performance */
//   /***********************/
//   SG1.Sigma0_count	 = pPR->Lx*pPR->Ly;
//   SG1.Sigma0HH		/= SG1.Sigma0_count;
//   SG1.Sigma0HV		/= SG1.Sigma0_count;
//   SG1.Sigma0VH		/= SG1.Sigma0_count;
//   SG1.Sigma0VV		/= SG1.Sigma0_count;
//   SG1.AvgShhvv		= complex_rmul (SG1.AvgShhvv, 1.0/SG1.Sigma0_count);
//   fprintf (pPR->pLogFile, "Bounce Forest HH backscattering coefficient\t= %lf dB\n", 10.0*log10(SG1.Sigma0HH));
//   fprintf (pPR->pLogFile, "Bounce Forest HV backscattering coefficient\t= %lf dB\n", 10.0*log10(SG1.Sigma0HV));
//   fprintf (pPR->pLogFile, "Bounce Forest VH backscattering coefficient\t= %lf dB\n", 10.0*log10(SG1.Sigma0VH));
//   fprintf (pPR->pLogFile, "Bounce Forest VV backscattering coefficient\t= %lf dB\n", 10.0*log10(SG1.Sigma0VV));
//   fprintf (pPR->pLogFile, "Bounce Forest HHVV correlation magnitude   \t= %lf dB\n", 10.0*log10(SG1.AvgShhvv.r));
//   fprintf (pPR->pLogFile, "Bounce Forest HHVV correlation phase       \t= %lf rads.\n", SG1.AvgShhvv.phi);
//   fflush  (pPR->pLogFile);
//   /***********/
//   /* Tidy up */
//   /***********/
//   Delete_SAR_Geometry (&SG1);
//   /**********************************************/
//   /* Report progress if running in VERBOSE mode */
//   /**********************************************/
//#ifdef VERBOSE_POLSARPROSIM
//   printf ("\n");
//   printf ("... Returning from call to PolSARproSim_Forest_Bounce\n");
//   printf ("\n");
//#endif
//   fprintf (pPR->pLogFile, "... Returning from call to PolSARproSim_Forest_Bounce\n\n");
//   fflush  (pPR->pLogFile);
//   /********************************/
//   /* Increment progress indicator */
//   /********************************/
//   pPR->progress++;
//   /********************************/
//   /* Report progress if requested */
//   /********************************/
//#ifdef POLSARPROSIM_MAX_PROGRESS
//   PolSARproSim_indicate_progress (pPR);
//#endif
//   /*****************************/
//   /* Return to calling routine */
//   /*****************************/
//   return (NO_POLSARPROSIM_FOREST_ERRORS);
//}
//
//
//int		Image_Tree_Direct		(Tree *pT, SarGeometry *pSG, PolSARproSim_Record *pPR)
//{
//   const double		bsecl	=	POLSARPROSIM_SAR_BRANCH_FACTOR*(pPR->azimuth_resolution + pPR->slant_range_resolution);
//   long             iBranch;
//   Branch           *pB;
//   int              Nsections;
//   int              i_section;
//   double           deltat, deltar;
//   Cylinder         cyl1;
//   double           weight_sum;
//   double           weight_count;
//   double           weight_avg;
//   int              rtn_value;
//   double           tb_scaling;
//   double           flg_scaling;
//   long             iLeaf;
//   Leaf             *pL;
//   int              Cscatt_Flag;
//   double           leafL1, leafL2, leafL3; //to calculate leaf depolarization factors
//   d3Vector         Ldvec;
//   c4Vector         Sdirect;             // direct scattering vector S = [Shh, Shv, Svh, Svv]
//   /************************************
//    ** This part edited out along with **
//    ** the Tertiary imaging section    **
//    ** code                  --RAedit  **
//    #ifndef POLSARPROSIM_NO_SAR_TERTIARIES
//    Branch				tertiary_branch;
//    double				tertiary_branch_length, tertiary_branch_radius;
//    long         n_Tertiary;
//    double				tertiary_moisture;
//    Complex			tertiary_permittivity;
//    #endif
//    ************************************/
//   
//   /************************************
//    ** This part edited out along with **
//    ** the Foliage imaging section     **
//    ** code                  --RAedit  **
//    #ifndef POLSARPROSIM_NO_SAR_FOLIAGE
//    long           n_Leaves;
//    int            L_species;
//    double         leaf_d1, leaf_d2, leaf_d3;
//    double         L_moisture;
//    Complex        L_permittivity;
//    Leaf           tree_leaf;
//    #endif
//    ************************************/
//   
//   /************************/
//   /* Initialise variables */
//   /************************/
//   Create_Cylinder (&cyl1);
//   Create_d3Vector (&Ldvec);
//   Create_c4Vector(&Sdirect);
//
//#ifndef FORCE_GRG_CYLINDERS
//   Cscatt_Flag	= POLSARPROSIM_SAR_INF_TERTIARY_BRANCHES;
//#else
//   Cscatt_Flag	= POLSARPROSIM_SAR_GRG_TERTIARY_BRANCHES;
//#endif
//   /*******************/
//   /* Image the stems */
//   /*******************/
//#ifndef POLSARPROSIM_NO_SAR_STEMS
//    if(pT->Stem.head != NULL_PTR2BRANCH_LIST){ /* Image Stem only if it exists                 */
//      pB			= pT->Stem.head;
//      weight_sum	= 0.0;
//      weight_count	= 0.0;
//      for (iBranch=0L; iBranch < pT->Stem.n; iBranch++) {
//         Nsections	= (int) (pB->l/bsecl) + 1;
//         deltat		= 1.0 / (double) Nsections;
//         deltar		= (pB->start_radius - pB->end_radius) / (double) Nsections;
//         for (i_section = 0; i_section < Nsections; i_section++) {
//            rtn_value	= Cylinder_from_Branch (&cyl1, pB, i_section, Nsections);
//            weight_sum	+= Image_Cylinder_Direct (&cyl1, pSG, pPR, 1.0, Cscatt_Flag, &Sdirect);
//            weight_count	+= 1.0;
//         }
//         pB			= pB->next;
//      }
//      weight_avg	= weight_sum/weight_count;
//   }
//#endif
//   /**************************/
//   /* Image primary branches */
//   /**************************/
//#ifndef POLSARPROSIM_NO_SAR_PRIMARIES
//   if(pT->Dry.head != NULL_PTR2BRANCH_LIST) {       /* Image Dry Primary branches onl if they exist                                      --RAedit */
//      pB			= pT->Dry.head;
//      weight_sum	= 0.0;
//      weight_count	= 0.0;
//      for (iBranch=0L; iBranch < pT->Dry.n; iBranch++) {
//         Nsections	= (int) (pB->l/bsecl) + 1;
//         deltat		= 1.0 / (double) Nsections;
//         deltar		= (pB->start_radius - pB->end_radius) / (double) Nsections;
//         for (i_section = 0; i_section < Nsections; i_section++) {
//            rtn_value	= Cylinder_from_Branch (&cyl1, pB, i_section, Nsections);
//            weight_sum	+= Image_Cylinder_Direct (&cyl1, pSG, pPR, 1.0, Cscatt_Flag, &Sdirect);
//            weight_count	+= 1.0;
//         }
//         pB			= pB->next;
//      }
//      weight_avg	= weight_sum/weight_count;
//   }
//   if(pT->Primary.head != NULL_PTR2BRANCH_LIST) { /* Image live primaries only if they exist  */
//      pB			= pT->Primary.head;
//      weight_sum	= 0.0;
//      weight_count	= 0.0;
//      for (iBranch=0L; iBranch < pT->Primary.n; iBranch++) {
//         Nsections	= (int) (pB->l/bsecl) + 1;
//         deltat		= 1.0 / (double) Nsections;
//         deltar		= (pB->start_radius - pB->end_radius) / (double) Nsections;
//         for (i_section = 0; i_section < Nsections; i_section++) {
//            rtn_value	= Cylinder_from_Branch (&cyl1, pB, i_section, Nsections);
//            weight_sum	+= Image_Cylinder_Direct (&cyl1, pSG, pPR, 1.0, Cscatt_Flag, &Sdirect);
//            weight_count	+= 1.0;
//         }
//         pB			= pB->next;
//      }
//      weight_avg	= weight_sum/weight_count;
//   }
//#endif
//   /****************************/
//   /* Image secondary branches */
//   /****************************/
//#ifndef POLSARPROSIM_NO_SAR_SECONDARIES
//   if(pT->Secondary.head != NULL_PTR2BRANCH_LIST) { /* Image secondaries only if they exist        */
//      pB			= pT->Secondary.head;
//      weight_sum	= 0.0;
//      weight_count	= 0.0;
//      for (iBranch=0L; iBranch < pT->Secondary.n; iBranch++) {
//         Nsections	= (int) (pB->l/bsecl) + 1;
//         deltat		= 1.0 / (double) Nsections;
//         deltar		= (pB->start_radius - pB->end_radius) / (double) Nsections;
//         for (i_section = 0; i_section < Nsections; i_section++) {
//            rtn_value	= Cylinder_from_Branch (&cyl1, pB, i_section, Nsections);
//            weight_sum	+= Image_Cylinder_Direct (&cyl1, pSG, pPR, 1.0, Cscatt_Flag, &Sdirect);
//            weight_count	+= 1.0;
//         }
//         pB			= pB->next;
//      }
//      weight_avg	= weight_sum/weight_count;
//   }
//#endif
//   /***************************/
//   /* Image tertiary branches */
//   /***************************/
//#ifndef POLSARPROSIM_NO_SAR_TERTIARIES
//#ifndef FORCE_GRG_CYLINDERS
//   if (pPR->Grg_Flag == 0) {
//      Cscatt_Flag	=    POLSARPROSIM_SAR_GRG_TERTIARY_BRANCHES;
//   } else {
//      Cscatt_Flag	=    POLSARPROSIM_SAR_INF_TERTIARY_BRANCHES;
//   }
//#endif
//   /***************************************************
//    ** This part is commented out so tertiaries from  **
//    ** the link-list created by Realise_Tertiaries()  **
//    ** are imaged instead of being regenerated here.  **
//    ** This removes the dependence of imaging code    **
//    ** on tree species.                               **
//    **                                       --RAedit **
//    ****************************************************
//    
//    tb_scaling				= Estimate_SAR_Tertiaries (pT, pPR, &n_Tertiary, &tertiary_branch_length, &tertiary_branch_radius);
//    weight_sum				= 0.0;
//    weight_count			= 0.0;
//    pB						= &tertiary_branch;
//    Create_Branch (pB);
//    tertiary_moisture		= Tertiary_Branch_Moisture (pT->species);
//    tertiary_permittivity	= vegetation_permittivity (tertiary_moisture, pPR->frequency);
//    for (iBranch=0L; iBranch < n_Tertiary; iBranch++) {
//    if (pT->species != POLSARPROSIM_HEDGE) {
//    tertiary_moisture		= Tertiary_Branch_Moisture (pT->species);
//    tertiary_permittivity	= vegetation_permittivity (tertiary_moisture, pPR->frequency);
//    }
//    rtn_value				= Realise_Tertiary_Branch (pT, pPR, pB, tertiary_branch_length, tertiary_branch_radius, tertiary_moisture, tertiary_permittivity);
//    if (rtn_value == NO_RAYCROWN_ERRORS) {
//    Nsections			= (int) (pB->l/bsecl) + 1;
//    deltat				= 1.0 / (double) Nsections;
//    deltar				= (pB->start_radius - pB->end_radius) / (double) Nsections;
//    for (i_section = 0; i_section < Nsections; i_section++) {
//    rtn_value			 = Cylinder_from_Branch (&cyl1, pB, i_section, Nsections);
//    weight_sum			+= Image_Cylinder_Direct (&cyl1, pSG, pPR, tb_scaling, Cscatt_Flag);
//    weight_count		+= 1.0;
//    }
//    }
//    }
//    weight_avg		= weight_sum/weight_count;
//    Destroy_Branch (pB);
//    ***************************************************/
//   if(pT->Tertiary.head != NULL_PTR2BRANCH_LIST){
//      weight_sum				= 0.0;
//      weight_count			= 0.0;
//      pB                = pT->Tertiary.head;
//      tb_scaling        = pT->Tertiary.scale_factor; /* New addition to the Branch_list structure --RAedit */
//      
//      for (iBranch=0L; iBranch < pT->Tertiary.n; iBranch++) {
//         Nsections       = (int) (pB->l/bsecl) + 1;
//         deltat          = 1.0 / (double) Nsections;
//         deltar          = (pB->start_radius - pB->end_radius) / (double) Nsections;
//         for (i_section = 0; i_section < Nsections; i_section++) {
//            rtn_value     = Cylinder_from_Branch (&cyl1, pB, i_section, Nsections);
//            weight_sum		+= Image_Cylinder_Direct (&cyl1, pSG, pPR, tb_scaling, Cscatt_Flag, &Sdirect);
//            weight_count	+= 1.0;
//         }
//         pB              = pB->next;
//      }
//      weight_avg        = weight_sum/weight_count;
//   }
//#endif
//   
//   /*****************/
//   /* Image foliage */
//   /*****************/
//#ifndef POLSARPROSIM_NO_SAR_FOLIAGE
//   /***************************************************
//    ** This part is commented out so leaves from      **
//    ** the link-list created by Realise_Foliage()     **
//    ** are imaged instead of being regenerated here.  **
//    ** This removes the dependence of imaging code    **
//    ** on tree species.                               **
//    **                                       --RAedit **
//    ****************************************************
//    L_species		= Leaf_Species		(pT->species);
//    leaf_d1		= Leaf_Dimension_1	(pT->species);
//    leaf_d2		= Leaf_Dimension_2	(pT->species);
//    leaf_d3		= Leaf_Dimension_3	(pT->species);
//    L_moisture		= Leaf_Moisture		(pT->species);
//    L_permittivity	= vegetation_permittivity (L_moisture, pPR->frequency);
//    pL				= &tree_leaf;
//    Create_Leaf (pL);
//    flg_scaling	= Estimate_SAR_Foliage (pT, pPR, &n_Leaves);
//    weight_sum		= 0.0;
//    weight_count	= 0.0;
//    printf("No of Imaging Leaves: %ld\n", n_Leaves);
//    for (iLeaf=0L; iLeaf < n_Leaves; iLeaf++) {
//    if (pT->species != POLSARPROSIM_HEDGE) {
//    L_moisture		= Leaf_Moisture	(pT->species);
//    L_permittivity	= vegetation_permittivity (L_moisture, pPR->frequency);
//    }
//    rtn_value		= Realise_Foliage_Element (pT, pPR, pL, L_species, leaf_d1, leaf_d2, leaf_d3, L_moisture, L_permittivity);
//    if (rtn_value == NO_RAYCROWN_ERRORS) {
//    weight_sum	+= Image_Foliage_Direct (pL, pSG, pPR, flg_scaling);
//    weight_count	+= 1.0;
//    }
//    }
//    Destroy_Leaf (pL);
//    *****************************************--RAedit*/
//   if(pT->Foliage.head != NULL_PTR2LEAF_LIST){
//      weight_sum		= 0.0;
//      weight_count	= 0.0;
//      pL             = pT->Foliage.head;
//      flg_scaling    = pT->Foliage.scale_factor;
//      for (iLeaf=0L; iLeaf < pT->Foliage.n; iLeaf++) {
//         Leaf_Depolarization_Factors (pL, &leafL1, &leafL2, &leafL3);
//         Ldvec = Cartesian_Assign_d3Vector(leafL1, leafL2, leafL3);
////         pPR->Tertiary_leafL1	= leafL1;
////         pPR->Tertiary_leafL2	= leafL2;
////         pPR->Tertiary_leafL3	= leafL3;
//         weight_sum           += Image_Foliage_Direct (pL, pSG, pPR, flg_scaling, &Ldvec, &Sdirect);
//         weight_count         += 1.0;
//         pL = pL->next;
//      }
//   }
//#endif
//   /***************/
//   /* Tidy up ... */
//   /***************/
//   Destroy_Cylinder (&cyl1);
//   /********************/
//   /* ... and go home. */
//   /********************/
//   return (NO_POLSARPROSIM_FOREST_ERRORS);
//}
//
//int		PolSARproSim_Forest_Direct		(PolSARproSim_Record *pPR)
//{
//   Tree			tree1;
//   int			itree;
//   SarGeometry	SG1;
//   int			rtn_value;
//   /**********************/
//   /* Imaging the forest */
//   /**********************/
//#ifdef VERBOSE_POLSARPROSIM
//   printf ("\n");
//   printf ("Call to PolSARproSim_Forest_Direct ... \n");
//   printf ("\n");
//#endif
//   fprintf (pPR->pLogFile, "Call to PolSARproSim_Forest_Direct ... \n");
//   fflush  (pPR->pLogFile);
//   /**********************************/
//   /* Set up the SAR geometry record */
//   /**********************************/
//   rtn_value	= Initialise_SAR_Geometry (&SG1, pPR, pPR->current_track);
//   /********************************/
//   /* Seed random number generator */
//   /********************************/
//   srand (pPR->seed);
//   /**************************/
//   /* Main tree imaging loop */
//   /**************************/
//   Create_Tree (&tree1);
//   for (itree=0; itree<pPR->Trees; itree++) {
//      Realise_Tree		(&tree1, itree, pPR);
//      Image_Tree_Direct	(&tree1, &SG1, pPR);  
//   }
//   Destroy_Tree (&tree1);
//   /***********************/
//   /* Monitor performance */
//   /***********************/
//   SG1.Sigma0_count	 = pPR->Lx*pPR->Ly;
//   SG1.Sigma0HH		/= SG1.Sigma0_count;
//   SG1.Sigma0HV		/= SG1.Sigma0_count;
//   SG1.Sigma0VH		/= SG1.Sigma0_count;
//   SG1.Sigma0VV		/= SG1.Sigma0_count;
//   SG1.AvgShhvv		= complex_rmul (SG1.AvgShhvv, 1.0/SG1.Sigma0_count);
//   fprintf (pPR->pLogFile, "Direct Forest HH backscattering coefficient\t= %lf dB\n", 10.0*log10(SG1.Sigma0HH));
//   fprintf (pPR->pLogFile, "Direct Forest HV backscattering coefficient\t= %lf dB\n", 10.0*log10(SG1.Sigma0HV));
//   fprintf (pPR->pLogFile, "Direct Forest VH backscattering coefficient\t= %lf dB\n", 10.0*log10(SG1.Sigma0VH));
//   fprintf (pPR->pLogFile, "Direct Forest VV backscattering coefficient\t= %lf dB\n", 10.0*log10(SG1.Sigma0VV));
//   fprintf (pPR->pLogFile, "Direct Forest HHVV correlation magnitude   \t= %lf dB\n", 10.0*log10(SG1.AvgShhvv.r));
//   fprintf (pPR->pLogFile, "Direct Forest HHVV correlation phase       \t= %lf rads.\n", SG1.AvgShhvv.phi);
//   fflush  (pPR->pLogFile);
//   /***********/
//   /* Tidy up */
//   /***********/
//   Delete_SAR_Geometry (&SG1);
//   /**********************************************/
//   /* Report progress if running in VERBOSE mode */
//   /**********************************************/
//#ifdef VERBOSE_POLSARPROSIM
//   printf ("\n");
//   printf ("... Returning from call to PolSARproSim_Forest_Direct\n");
//   printf ("\n");
//#endif
//   fprintf (pPR->pLogFile, "... Returning from call to PolSARproSim_Forest_Direct\n\n");
//   fflush  (pPR->pLogFile);
//   /********************************/
//   /* Increment progress indicator */
//   /********************************/
//   pPR->progress++;
//   /********************************/
//   /* Report progress if requested */
//   /********************************/
//#ifdef POLSARPROSIM_MAX_PROGRESS
//   PolSARproSim_indicate_progress (pPR);
//#endif
//   /*****************************/
//   /* Return to calling routine */
//   /*****************************/
//   return (NO_POLSARPROSIM_FOREST_ERRORS);
//}

/************************************/
/* Image all tree components        */
/************************************/
int		Image_Tree		(Tree *pT, SarGeometry *pSGdirect, SarGeometry *pSGbounce, PolSARproSim_Record *pPR)
{
   const double		bsecl	=	POLSARPROSIM_SAR_BRANCH_FACTOR*(pPR->azimuth_resolution + pPR->slant_range_resolution);
   long              iBranch;
   Branch            *pB;
   int               Nsections;
   int               i_section;
   double            deltat, deltar;
   Cylinder          cyl1;
   double            weight_sum;
   double            weight_count;
   int               rtn_value;
   double            tb_scaling;
   double            flg_scaling;
   long              iLeaf;
   Leaf              *pL;
   int               Cscatt_Flag;
   double            leafL1, leafL2, leafL3;       //to calculate leaf depolarization factors
   d3Vector          Ldvec;   // leaf depolarization vector
   double            weight_sum2;
   int               track;                        // to loop over tracks
   d3Vector          motion_offset;                // offset for adding motion to a cylinder/leaf 
   double            moisture_offset;              // offset for adding moisture to a cylinder/leaf
   double            change_start_height;          // to allow re-computation of offsets to preserve vertical profiles
   c4Vector          *Sdirect, *Sbounce;
   unsigned short    seed[3];                      // seed for re-entrantly safe random number generators
   seed[0]           = (unsigned short)(pPR->seed);
  
   /************************/
   /* Initialise variables */
   /************************/
   Create_Cylinder (&cyl1);
#ifndef FORCE_GRG_CYLINDERS
   Cscatt_Flag	= POLSARPROSIM_SAR_INF_TERTIARY_BRANCHES;
#else
   Cscatt_Flag	= POLSARPROSIM_SAR_GRG_TERTIARY_BRANCHES;
#endif
   Create_d3Vector(&motion_offset);
   Create_d3Vector(&Ldvec);
   /*******************/
   /* Image the stems */
   /*******************/
#ifndef POLSARPROSIM_NO_SAR_STEMS
   if(pT->Stem.head != NULL_PTR2BRANCH_LIST){ 
      pB			= pT->Stem.head;
      weight_sum	= 0.0;
      weight_sum2	= 0.0;
      weight_count	= 0.0;
      for (iBranch=0L; iBranch < pT->Stem.n; iBranch++) {
         Nsections	= (int) (pB->l/bsecl) + 1;
         deltat		= 1.0 / (double) Nsections;
         deltar		= (pB->start_radius - pB->end_radius) / (double) Nsections;
         Sdirect     = (c4Vector *)calloc(Nsections, sizeof(c4Vector));
         Sbounce     = (c4Vector *)calloc(Nsections, sizeof(c4Vector));
         change_start_height  = pB->b0.x[2];
         for (track=0;track<pPR->Tracks;track++){
            /* compute initial change in branch properties (position and moisture) */
            Model_Change (pT, pPR, track, &motion_offset, &moisture_offset, change_start_height, &(seed[0]));
            for (i_section = 0; i_section < Nsections; i_section++) {
               rtn_value	= Cylinder_from_Branch (&cyl1, pB, i_section, Nsections);
               /* recompute changed properties if branch exceed a height level */
               if(cyl1.base.x[2] > change_start_height + pPR->change_height_delta) {
                  Model_Change (pT, pPR, track, &motion_offset, &moisture_offset, cyl1.base.x[2], &(seed[0]));
                  change_start_height = cyl1.base.x[2];
               }
               /* change the cylinder properties */
               Change_Cylinder (&cyl1, pB, pPR, motion_offset, moisture_offset, track);
               /* image cylinders */
               weight_sum	+= Image_Cylinder_Direct (&cyl1, &(pSGdirect[track]), pPR, 1.0, Cscatt_Flag, &(Sdirect[i_section]));
               weight_sum2	+= Image_Cylinder_Bounce (&cyl1, &(pSGbounce[track]), pPR, 1.0, Cscatt_Flag, &(Sbounce[i_section]));                  
               weight_count	+= 1.0;
            }
         }
         free(Sdirect);
         free(Sbounce);
         pB			= pB->next;
      }
   }
#endif
   /**************************/
   /* Image primary branches */
   /**************************/
#ifndef POLSARPROSIM_NO_SAR_PRIMARIES
   if(pT->Dry.head != NULL_PTR2BRANCH_LIST) {     
      pB			= pT->Dry.head;
      weight_sum	= 0.0;
      weight_count	= 0.0;
      for (iBranch=0L; iBranch < pT->Dry.n; iBranch++) {
         Nsections	= (int) (pB->l/bsecl) + 1;
         deltat		= 1.0 / (double) Nsections;
         deltar		= (pB->start_radius - pB->end_radius) / (double) Nsections;
         Sdirect     = (c4Vector *)calloc(Nsections, sizeof(c4Vector));
         Sbounce     = (c4Vector *)calloc(Nsections, sizeof(c4Vector));
         change_start_height  = pB->b0.x[2];
         for (track=0;track<pPR->Tracks;track++){
            /* compute initial change in branch properties (position and moisture) */
            Model_Change (pT, pPR, track, &motion_offset, &moisture_offset, change_start_height, &(seed[0]));
            for (i_section = 0; i_section < Nsections; i_section++) {
               rtn_value	= Cylinder_from_Branch (&cyl1, pB, i_section, Nsections);
               /* recompute changed properties if branch exceed a height level */
               if(cyl1.base.x[2] > change_start_height + pPR->change_height_delta) {
                  Model_Change (pT, pPR, track, &motion_offset, &moisture_offset, cyl1.base.x[2], &(seed[0]));
                  change_start_height = cyl1.base.x[2];
               }
               /* change the cylinder properties */
               Change_Cylinder (&cyl1, pB, pPR, motion_offset, moisture_offset, track); 
               /* image cylinders */
               weight_sum	+= Image_Cylinder_Direct (&cyl1, &(pSGdirect[track]), pPR, 1.0, Cscatt_Flag, &(Sdirect[i_section]));
               weight_sum2	+= Image_Cylinder_Bounce (&cyl1, &(pSGbounce[track]), pPR, 1.0, Cscatt_Flag, &(Sbounce[i_section]));
               weight_count	+= 1.0;
            }
         }
         free(Sdirect);
         free(Sbounce);
         pB			= pB->next;
      }
   }
   if(pT->Primary.head != NULL_PTR2BRANCH_LIST) { /* Image live primaries only if they exist  */
      pB			= pT->Primary.head;
      weight_sum	= 0.0;
      weight_count	= 0.0;
      for (iBranch=0L; iBranch < pT->Primary.n; iBranch++) {
         Nsections	= (int) (pB->l/bsecl) + 1;
         deltat		= 1.0 / (double) Nsections;
         deltar		= (pB->start_radius - pB->end_radius) / (double) Nsections;
         Sdirect     = (c4Vector *)calloc(Nsections, sizeof(c4Vector));
         Sbounce     = (c4Vector *)calloc(Nsections, sizeof(c4Vector));
         change_start_height  = pB->b0.x[2];
         for (track=0;track<pPR->Tracks;track++){
            /* compute initial change in branch properties (position and moisture) */
            Model_Change (pT, pPR, track, &motion_offset, &moisture_offset, change_start_height, &(seed[0]));
            for (i_section = 0; i_section < Nsections; i_section++) {
               rtn_value	= Cylinder_from_Branch (&cyl1, pB, i_section, Nsections);
               /* recompute changed properties if branch exceed a height level */
               if(cyl1.base.x[2] > change_start_height + pPR->change_height_delta) {
                  Model_Change (pT, pPR, track, &motion_offset, &moisture_offset, cyl1.base.x[2], &(seed[0]));
                  change_start_height = cyl1.base.x[2];
               }
               /* change the cylinder properties */
               Change_Cylinder (&cyl1, pB, pPR, motion_offset, moisture_offset, track); 
               /* image cylinders */
               weight_sum	+= Image_Cylinder_Direct (&cyl1, &(pSGdirect[track]), pPR, 1.0, Cscatt_Flag, &(Sdirect[i_section]));
               weight_sum2	+= Image_Cylinder_Bounce (&cyl1, &(pSGbounce[track]), pPR, 1.0, Cscatt_Flag, &(Sbounce[i_section]));
               weight_count	+= 1.0;
            }
         }
         free(Sdirect);
         free(Sbounce);
         pB			= pB->next;
      }
   }
#endif
   /****************************/
   /* Image secondary branches */
   /****************************/
#ifndef POLSARPROSIM_NO_SAR_SECONDARIES
   if(pT->Secondary.head != NULL_PTR2BRANCH_LIST) { /* Image secondaries only if they exist        */
      pB			= pT->Secondary.head;
      weight_sum	= 0.0;
      weight_count	= 0.0;
      for (iBranch=0L; iBranch < pT->Secondary.n; iBranch++) {
         Nsections	= (int) (pB->l/bsecl) + 1;
         deltat		= 1.0 / (double) Nsections;
         deltar		= (pB->start_radius - pB->end_radius) / (double) Nsections;
         Sdirect     = (c4Vector *)calloc(Nsections, sizeof(c4Vector));
         Sbounce     = (c4Vector *)calloc(Nsections, sizeof(c4Vector));
         change_start_height  = pB->b0.x[2];
         for (track=0;track<pPR->Tracks;track++){
            /* compute initial change in branch properties (position and moisture) */
            Model_Change (pT, pPR, track, &motion_offset, &moisture_offset, change_start_height, &(seed[0]));
            for (i_section = 0; i_section < Nsections; i_section++) {
               rtn_value	= Cylinder_from_Branch (&cyl1, pB, i_section, Nsections);
               /* recompute changed properties if branch exceed a height level */
               if(cyl1.base.x[2] > change_start_height + pPR->change_height_delta) {
                  Model_Change (pT, pPR, track, &motion_offset, &moisture_offset, cyl1.base.x[2], &(seed[0]));
                  change_start_height = cyl1.base.x[2];
               }
               /* change the cylinder properties */
               Change_Cylinder (&cyl1, pB, pPR, motion_offset, moisture_offset, track); 
               /* image cylinders */
               weight_sum	+= Image_Cylinder_Direct (&cyl1, &(pSGdirect[track]), pPR, 1.0, Cscatt_Flag, &(Sdirect[i_section]));
               weight_sum2	+= Image_Cylinder_Bounce (&cyl1, &(pSGbounce[track]), pPR, 1.0, Cscatt_Flag, &(Sbounce[i_section]));
               weight_count	+= 1.0;
            }
         }
         free(Sdirect);
         free(Sbounce);
         pB			= pB->next;
      }
   }
#endif
   /***************************/
   /* Image tertiary branches */
   /***************************/
#ifndef POLSARPROSIM_NO_SAR_TERTIARIES
#ifndef FORCE_GRG_CYLINDERS
   if (pPR->Grg_Flag == 0) {
      Cscatt_Flag	=    POLSARPROSIM_SAR_GRG_TERTIARY_BRANCHES;
   } else {
      Cscatt_Flag	=    POLSARPROSIM_SAR_INF_TERTIARY_BRANCHES;
   }
#endif
   if(pT->Tertiary.head != NULL_PTR2BRANCH_LIST){
      weight_sum				= 0.0;
      weight_count			= 0.0;
      pB                   = pT->Tertiary.head;
      tb_scaling           = pT->Tertiary.scale_factor; /* New addition to the Branch_list structure --RAedit */
      for (iBranch=0L; iBranch < pT->Tertiary.n; iBranch++) {
         Nsections   = (int) (pB->l/bsecl) + 1;
         deltat      = 1.0 / (double) Nsections;
         deltar      = (pB->start_radius - pB->end_radius) / (double) Nsections;
         Sdirect     = (c4Vector *)calloc(Nsections, sizeof(c4Vector));
         Sbounce     = (c4Vector *)calloc(Nsections, sizeof(c4Vector));
         change_start_height  = pB->b0.x[2];
         for (track=0;track<pPR->Tracks;track++){
            /* compute initial change in branch properties (position and moisture) */
            Model_Change (pT, pPR, track, &motion_offset, &moisture_offset, change_start_height, &(seed[0]));
            for (i_section = 0; i_section < Nsections; i_section++) {
               rtn_value     = Cylinder_from_Branch (&cyl1, pB, i_section, Nsections);
               /* recompute changed properties if branch exceed a height level */
               if(cyl1.base.x[2] > change_start_height + pPR->change_height_delta) {
                  Model_Change (pT, pPR, track, &motion_offset, &moisture_offset, cyl1.base.x[2], &(seed[0]));
                  change_start_height = cyl1.base.x[2];
               }
               /* change the cylinder properties */
               Change_Cylinder (&cyl1, pB, pPR, motion_offset, moisture_offset, track); 
               /* image cylinders */
               weight_sum		+= Image_Cylinder_Direct (&cyl1, &(pSGdirect[track]), pPR, tb_scaling, Cscatt_Flag, &(Sdirect[i_section]));
               weight_sum2		+= Image_Cylinder_Bounce (&cyl1, &(pSGbounce[track]), pPR, tb_scaling, Cscatt_Flag, &(Sbounce[i_section]));
               weight_count	+= 1.0;
            }
         }
         free(Sdirect);
         free(Sbounce);
         pB              = pB->next;
      }
   }
#endif
   
   /*****************/
   /* Image foliage */
   /*****************/
#ifndef POLSARPROSIM_NO_SAR_FOLIAGE
   if(pT->Foliage.head != NULL_PTR2LEAF_LIST){
      weight_sum		= 0.0;
      weight_count	= 0.0;
      pL             = pT->Foliage.head;
      flg_scaling    = pT->Foliage.scale_factor;
      Leaf_Depolarization_Factors (pL, &leafL1, &leafL2, &leafL3);
      Ldvec = Cartesian_Assign_d3Vector(leafL1, leafL2, leafL3);
      Sdirect     = (c4Vector *)calloc(1, sizeof(c4Vector));
      Sbounce     = (c4Vector *)calloc(1, sizeof(c4Vector));
      for (iLeaf=0L; iLeaf < pT->Foliage.n; iLeaf++) {
         for (track=0;track<pPR->Tracks;track++){
            Model_Change (pT, pPR, track, &motion_offset, &moisture_offset, pL->cl.x[2], &(seed[0]));
            Change_Leaf  (pL, pPR, motion_offset, moisture_offset, track); 
            weight_sum           += Image_Foliage_Direct (pL, &(pSGdirect[track]), pPR, flg_scaling, &Ldvec, &(Sdirect[0]));
            weight_sum2          += Image_Foliage_Bounce (pL, &(pSGbounce[track]), pPR, flg_scaling, &Ldvec, &(Sbounce[0]));
            weight_count         += 1.0;
         }
         pL = pL->next;
      }
   }
#endif
   /***************/
   /* Tidy up ... */
   /***************/
   Destroy_Cylinder (&cyl1);
   Destroy_Tree(pT);
   free(Sdirect);
   free(Sbounce);
   return (NO_POLSARPROSIM_FOREST_ERRORS);
}

/************************************/
/* Simulate Forest scattering       */
/************************************/
int		PolSARproSim_Forest		(PolSARproSim_Record *pPR)
{
   Tree			tree1;
   int			itree, track;
   SarGeometry	*SGdirect;
   SarGeometry *SGbounce;
   int			rtn_value;
#ifdef OUTPUT_CHANGE_STATS_ON 
   int i,j,index;
#endif

   /**********************/
   /* Imaging the forest */
   /**********************/
#ifdef VERBOSE_POLSARPROSIM
   printf ("\n");
   printf ("Call to PolSARproSim_Forest ... \n");
   printf ("\n");
#endif
   fprintf (pPR->pLogFile, "Call to PolSARproSim_Forest ... \n");
   fflush  (pPR->pLogFile);
   
   /* initialize SAR geometry variables*/
   SGdirect   = (SarGeometry*) calloc (pPR->Tracks, sizeof (SarGeometry));
   SGbounce   = (SarGeometry*) calloc (pPR->Tracks, sizeof (SarGeometry));
   /**********************************/
   /* Set up the SAR geometry record */
   /**********************************/
   for (track = 0; track < pPR->Tracks; track++) {
      rtn_value	= Initialise_SAR_Geometry (&SGdirect[track], pPR, track);
      rtn_value	= Initialise_SAR_Geometry (&SGbounce[track], pPR, track);
      printf("Geometries Initialized for track %d\n", track);
   }
   /********************************/
   /* Seed random number generator */
   /********************************/
   srand (pPR->seed);
   /**************************/
   /* Main tree imaging loop */
   /**************************/
   Create_Tree (&tree1);
   for (itree=0; itree<pPR->Trees; itree++) {
      Realise_Tree		(&tree1, itree, pPR);
      printf("Realized tree %d\n", itree);
      Image_Tree        (&tree1, &(SGdirect[0]), &(SGbounce[0]), pPR);  
      printf("Imaged tree %d\n", itree);
   }
   
   /* write out some average backscattering coefficients */    
   for (track = 0; track < pPR->Tracks; track++) {
      fprintf(pPR->pLogFile, "Forest Statistics for track %d\n", track);
      /******************************/
      /* Monitor Direct performance */
      /******************************/
      SGdirect[track].Sigma0_count	 = pPR->Lx*pPR->Ly;
      SGdirect[track].Sigma0HH		/= SGdirect[track].Sigma0_count;
      SGdirect[track].Sigma0HV		/= SGdirect[track].Sigma0_count;
      SGdirect[track].Sigma0VH		/= SGdirect[track].Sigma0_count;
      SGdirect[track].Sigma0VV		/= SGdirect[track].Sigma0_count;
      SGdirect[track].AvgShhvv		= complex_rmul (SGdirect[track].AvgShhvv, 1.0/SGdirect[track].Sigma0_count);
      fprintf (pPR->pLogFile, "Direct Forest HH backscattering coefficient\t= %lf dB\n", 10.0*log10(SGdirect[track].Sigma0HH));
      fprintf (pPR->pLogFile, "Direct Forest HV backscattering coefficient\t= %lf dB\n", 10.0*log10(SGdirect[track].Sigma0HV));
      fprintf (pPR->pLogFile, "Direct Forest VH backscattering coefficient\t= %lf dB\n", 10.0*log10(SGdirect[track].Sigma0VH));
      fprintf (pPR->pLogFile, "Direct Forest VV backscattering coefficient\t= %lf dB\n", 10.0*log10(SGdirect[track].Sigma0VV));
      fprintf (pPR->pLogFile, "Direct Forest HHVV correlation magnitude   \t= %lf dB\n", 10.0*log10(SGdirect[track].AvgShhvv.r));
      fprintf (pPR->pLogFile, "Direct Forest HHVV correlation phase       \t= %lf rads.\n", SGdirect[track].AvgShhvv.phi);
      fflush  (pPR->pLogFile);
      /******************************/
      /* Monitor Bounce performance */
      /******************************/
      SGbounce[track].Sigma0_count	 = pPR->Lx*pPR->Ly;
      SGbounce[track].Sigma0HH		/= SGbounce[track].Sigma0_count;
      SGbounce[track].Sigma0HV		/= SGbounce[track].Sigma0_count;
      SGbounce[track].Sigma0VH		/= SGbounce[track].Sigma0_count;
      SGbounce[track].Sigma0VV		/= SGbounce[track].Sigma0_count;
      SGbounce[track].AvgShhvv		= complex_rmul (SGbounce[track].AvgShhvv, 1.0/SGbounce[track].Sigma0_count);
      fprintf (pPR->pLogFile, "Bounce Forest HH backscattering coefficient\t= %lf dB\n", 10.0*log10(SGbounce[track].Sigma0HH));
      fprintf (pPR->pLogFile, "Bounce Forest HV backscattering coefficient\t= %lf dB\n", 10.0*log10(SGbounce[track].Sigma0HV));
      fprintf (pPR->pLogFile, "Bounce Forest VH backscattering coefficient\t= %lf dB\n", 10.0*log10(SGbounce[track].Sigma0VH));
      fprintf (pPR->pLogFile, "Bounce Forest VV backscattering coefficient\t= %lf dB\n", 10.0*log10(SGbounce[track].Sigma0VV));
      fprintf (pPR->pLogFile, "Bounce Forest HHVV correlation magnitude   \t= %lf dB\n", 10.0*log10(SGbounce[track].AvgShhvv.r));
      fprintf (pPR->pLogFile, "Bounce Forest HHVV correlation phase       \t= %lf rads.\n", SGbounce[track].AvgShhvv.phi);
      fflush  (pPR->pLogFile);

   }
   /***************************************************************************/
   /* Report statistics of changes applied to scatterer position and moisture */
   /***************************************************************************/
#ifdef OUTPUT_CHANGE_STATS_ON 
   fprintf (pPR->pLogFile, "\nMotion Offset Profile (x-axis only): Height [m], mean [line 0], variance [line 0], count [line 0], mean [line 1], variance [line 1]..... \n");
   for(i=0;i<CHANGE_PROFILE_BINS;i++){
      fprintf(pPR->pLogFile, "%f",  (double)(i*pPR->change_profile_bin_res));
      for(j=0;j<pPR->Tracks;j++){
         index = i * pPR->Tracks + j;
         if(pPR->motion_profile_count[index] > 2){
            /* this is what the statistics should really be */
            fprintf (pPR->pLogFile, "\t%f\t%f\t%d", pPR->motion_profile_mean[index], 
                   (double)(pPR->motion_profile_var[index]/(pPR->motion_profile_count[index]-1)), 
                   pPR->motion_profile_count[index]);
         }else{
            /* this is just to avoid divide by zero, may be inaccurate */
            fprintf (pPR->pLogFile, "\t%f\t%f\t%d", pPR->motion_profile_mean[i+j], 
                   (double)(pPR->motion_profile_var[index]/(pPR->motion_profile_count[index]+1)),
                   pPR->motion_profile_count[index]);
         }
      }
      fprintf (pPR->pLogFile, "\n");
   }
   fprintf (pPR->pLogFile, "\nMoisture Offset Profile: Height [m], mean [line 0], variance [line 0], mean [line 1], count [line 0], variance [line 1]..... \n");
   for(i=0;i<CHANGE_PROFILE_BINS;i++){
      fprintf(pPR->pLogFile, "%f",  (double)(i*pPR->change_profile_bin_res));
      for(j=0;j<pPR->Tracks;j++){
         index = i * pPR->Tracks + j;
         if(pPR->moisture_profile_count[index] > 2){
            /* this is what the statistics should really be */
            fprintf (pPR->pLogFile, "\t%f\t%f\t%d", pPR->moisture_profile_mean[index], 
                   (double)(pPR->moisture_profile_var[index]/(pPR->moisture_profile_count[index]-1)), 
                   pPR->moisture_profile_count[index]);
         }else{
            /* this is just to avoid divide by zero, may be inaccurate */
            fprintf (pPR->pLogFile, "\t%f\t%f\t%d", pPR->moisture_profile_mean[i+j], 
                   (double)(pPR->moisture_profile_var[index]/(pPR->moisture_profile_count[index]+1)),
                   pPR->moisture_profile_count[index]);
         }
      }
      fprintf (pPR->pLogFile, "\n");
   }
#endif
   /***********/
   /* Tidy up */
   /***********/
   for (track=0;track<pPR->Tracks;track++){
      Delete_SAR_Geometry (&SGdirect[track]);
      Delete_SAR_Geometry (&SGbounce[track]);
   }
   Destroy_Tree (&tree1);
   /**********************************************/
   /* Report progress if running in VERBOSE mode */
   /**********************************************/
#ifdef VERBOSE_POLSARPROSIM
   printf ("\n");
   printf ("... Returning from call to PolSARproSim_Forest_Direct\n");
   printf ("\n");
#endif
   fprintf (pPR->pLogFile, "... Returning from call to PolSARproSim_Forest_Direct\n\n");
   fflush  (pPR->pLogFile);
   /********************************/
   /* Increment progress indicator */
   /********************************/
   pPR->progress++;
   /********************************/
   /* Report progress if requested */
   /********************************/
#ifdef POLSARPROSIM_MAX_PROGRESS
   PolSARproSim_indicate_progress (pPR);
#endif
   /*****************************/
   /* Return to calling routine */
   /*****************************/
   return (NO_POLSARPROSIM_FOREST_ERRORS);
}




/* multi-threaded version of the image tree function */
void		*Image_Tree_SMP		(void *threadarg)
{
   /* variables for hyperthreading */
   ImageTree_Thread_Arg       *pTA;
   PolSARproSim_Record        *pPR;
   Tree                       *pT;
   SarGeometry                *pSGdirect;
   SarGeometry                *pSGbounce;
   int                        itree;
   /* do some assignments */
   pTA         = (ImageTree_Thread_Arg *)threadarg;
   pPR         = pTA->pPR;  /* pointer to Master_Record */
   pT          = &(pTA->tree1);
   pSGdirect   = pTA->pSGdirect;
   pSGbounce   = pTA->pSGbounce;
   itree       = pTA->itree;
   
   const double		bsecl	=	POLSARPROSIM_SAR_BRANCH_FACTOR*(pPR->azimuth_resolution + pPR->slant_range_resolution);
   long              iBranch;
   Branch            *pB;
   int               Nsections;
   int               i_section;
   double            deltat, deltar;
   Cylinder          cyl1;
   double            weight_sum;
   double            weight_count;
   int               rtn_value;
   double            tb_scaling;
   double            flg_scaling;
   long              iLeaf;
   Leaf              *pL;
   int               Cscatt_Flag;
   double            leafL1, leafL2, leafL3;       //to calculate leaf depolarization factors
   d3Vector          Ldvec;   // leaf depolarization vector
   double            weight_sum2;
   int               track;                        // to loop over tracks
   d3Vector          motion_offset;                // offset for adding motion to a cylinder/leaf 
   double            moisture_offset;              // offset for adding moisture to a cylinder/leaf
   double            change_start_height;          // to allow re-computation of offsets to preserve vertical profiles
   c4Vector          *Sdirect, *Sbounce;
   unsigned short    seed[3];                      // seed for re-entrantly safe random number generators
   seed[0]           = (unsigned short)(itree+pPR->seed);
   /************************/
   /* Initialise variables */
   /************************/
   Create_Cylinder (&cyl1);
#ifndef FORCE_GRG_CYLINDERS
   Cscatt_Flag	= POLSARPROSIM_SAR_INF_TERTIARY_BRANCHES;
#else
   Cscatt_Flag	= POLSARPROSIM_SAR_GRG_TERTIARY_BRANCHES;
#endif
   Create_d3Vector(&motion_offset);
   Create_d3Vector(&Ldvec);
   /*******************/
   /* Image the stems */
   /*******************/
#ifndef POLSARPROSIM_NO_SAR_STEMS
   if(pT->Stem.head != NULL_PTR2BRANCH_LIST){ 
      pB			= pT->Stem.head;
      weight_sum	= 0.0;
      weight_sum2	= 0.0;
      weight_count	= 0.0;
      for (iBranch=0L; iBranch < pT->Stem.n; iBranch++) {
         Nsections	= (int) (pB->l/bsecl) + 1;
         deltat		= 1.0 / (double) Nsections;
         deltar		= (pB->start_radius - pB->end_radius) / (double) Nsections;
         Sdirect     = (c4Vector *)calloc(Nsections, sizeof(c4Vector));
         Sbounce     = (c4Vector *)calloc(Nsections, sizeof(c4Vector));
         change_start_height  = pB->b0.x[2];
         for (track=0;track<pPR->Tracks;track++){
            /* compute initial change in branch properties (position and moisture) */
            Model_Change (pT, pPR, track, &motion_offset, &moisture_offset, change_start_height, &(seed[0]));
            for (i_section = 0; i_section < Nsections; i_section++) {
               rtn_value	= Cylinder_from_Branch (&cyl1, pB, i_section, Nsections);
               /* recompute changed properties if branch exceed a height level */
               if(cyl1.base.x[2] > change_start_height + pPR->change_height_delta) {
                  Model_Change (pT, pPR, track, &motion_offset, &moisture_offset, cyl1.base.x[2], &(seed[0]));
                  change_start_height = cyl1.base.x[2];
               }
               /* change the cylinder properties */
               Change_Cylinder (&cyl1, pB, pPR, motion_offset, moisture_offset, track);
               /* image cylinders */
               weight_sum	+= Image_Cylinder_Direct (&cyl1, &(pSGdirect[track]), pPR, 1.0, Cscatt_Flag, &(Sdirect[i_section]));
               weight_sum2	+= Image_Cylinder_Bounce (&cyl1, &(pSGbounce[track]), pPR, 1.0, Cscatt_Flag, &(Sbounce[i_section]));                  
               weight_count	+= 1.0;
            }
         }
         free(Sdirect);
         free(Sbounce);
         pB			= pB->next;
      }
   }
#endif
   /**************************/
   /* Image primary branches */
   /**************************/
#ifndef POLSARPROSIM_NO_SAR_PRIMARIES
   if(pT->Dry.head != NULL_PTR2BRANCH_LIST) {     
      pB			= pT->Dry.head;
      weight_sum	= 0.0;
      weight_count	= 0.0;
      for (iBranch=0L; iBranch < pT->Dry.n; iBranch++) {
         Nsections	= (int) (pB->l/bsecl) + 1;
         deltat		= 1.0 / (double) Nsections;
         deltar		= (pB->start_radius - pB->end_radius) / (double) Nsections;
         Sdirect     = (c4Vector *)calloc(Nsections, sizeof(c4Vector));
         Sbounce     = (c4Vector *)calloc(Nsections, sizeof(c4Vector));
         change_start_height  = pB->b0.x[2];
         for (track=0;track<pPR->Tracks;track++){
            /* compute initial change in branch properties (position and moisture) */
            Model_Change (pT, pPR, track, &motion_offset, &moisture_offset, change_start_height, &(seed[0]));
            for (i_section = 0; i_section < Nsections; i_section++) {
               rtn_value	= Cylinder_from_Branch (&cyl1, pB, i_section, Nsections);
               /* recompute changed properties if branch exceed a height level */
               if(cyl1.base.x[2] > change_start_height + pPR->change_height_delta) {
                  Model_Change (pT, pPR, track, &motion_offset, &moisture_offset, cyl1.base.x[2], &(seed[0]));
                  change_start_height = cyl1.base.x[2];
               }
               /* change the cylinder properties */
               Change_Cylinder (&cyl1, pB, pPR, motion_offset, moisture_offset, track); 
               /* image cylinders */
               weight_sum	+= Image_Cylinder_Direct (&cyl1, &(pSGdirect[track]), pPR, 1.0, Cscatt_Flag, &(Sdirect[i_section]));
               weight_sum2	+= Image_Cylinder_Bounce (&cyl1, &(pSGbounce[track]), pPR, 1.0, Cscatt_Flag, &(Sbounce[i_section]));
               weight_count	+= 1.0;
            }
         }
         free(Sdirect);
         free(Sbounce);
         pB			= pB->next;
      }
   }
   if(pT->Primary.head != NULL_PTR2BRANCH_LIST) { /* Image live primaries only if they exist  */
      pB			= pT->Primary.head;
      weight_sum	= 0.0;
      weight_count	= 0.0;
      for (iBranch=0L; iBranch < pT->Primary.n; iBranch++) {
         Nsections	= (int) (pB->l/bsecl) + 1;
         deltat		= 1.0 / (double) Nsections;
         deltar		= (pB->start_radius - pB->end_radius) / (double) Nsections;
         Sdirect     = (c4Vector *)calloc(Nsections, sizeof(c4Vector));
         Sbounce     = (c4Vector *)calloc(Nsections, sizeof(c4Vector));
         change_start_height  = pB->b0.x[2];
         for (track=0;track<pPR->Tracks;track++){
            /* compute initial change in branch properties (position and moisture) */
            Model_Change (pT, pPR, track, &motion_offset, &moisture_offset, change_start_height, &(seed[0]));
            for (i_section = 0; i_section < Nsections; i_section++) {
               rtn_value	= Cylinder_from_Branch (&cyl1, pB, i_section, Nsections);
               /* recompute changed properties if branch exceed a height level */
               if(cyl1.base.x[2] > change_start_height + pPR->change_height_delta) {
                  Model_Change (pT, pPR, track, &motion_offset, &moisture_offset, cyl1.base.x[2], &(seed[0]));
                  change_start_height = cyl1.base.x[2];
               }
               /* change the cylinder properties */
               Change_Cylinder (&cyl1, pB, pPR, motion_offset, moisture_offset, track); 
               /* image cylinders */
               weight_sum	+= Image_Cylinder_Direct (&cyl1, &(pSGdirect[track]), pPR, 1.0, Cscatt_Flag, &(Sdirect[i_section]));
               weight_sum2	+= Image_Cylinder_Bounce (&cyl1, &(pSGbounce[track]), pPR, 1.0, Cscatt_Flag, &(Sbounce[i_section]));
               weight_count	+= 1.0;
            }
         }
         free(Sdirect);
         free(Sbounce);
         pB			= pB->next;
      }
   }
#endif
   /****************************/
   /* Image secondary branches */
   /****************************/
#ifndef POLSARPROSIM_NO_SAR_SECONDARIES
   if(pT->Secondary.head != NULL_PTR2BRANCH_LIST) { /* Image secondaries only if they exist        */
      pB			= pT->Secondary.head;
      weight_sum	= 0.0;
      weight_count	= 0.0;
      for (iBranch=0L; iBranch < pT->Secondary.n; iBranch++) {
         Nsections	= (int) (pB->l/bsecl) + 1;
         deltat		= 1.0 / (double) Nsections;
         deltar		= (pB->start_radius - pB->end_radius) / (double) Nsections;
         Sdirect     = (c4Vector *)calloc(Nsections, sizeof(c4Vector));
         Sbounce     = (c4Vector *)calloc(Nsections, sizeof(c4Vector));
         change_start_height  = pB->b0.x[2];
         for (track=0;track<pPR->Tracks;track++){
            /* compute initial change in branch properties (position and moisture) */
            Model_Change (pT, pPR, track, &motion_offset, &moisture_offset, change_start_height, &(seed[0]));
            for (i_section = 0; i_section < Nsections; i_section++) {
               rtn_value	= Cylinder_from_Branch (&cyl1, pB, i_section, Nsections);
               /* recompute changed properties if branch exceed a height level */
               if(cyl1.base.x[2] > change_start_height + pPR->change_height_delta) {
                  Model_Change (pT, pPR, track, &motion_offset, &moisture_offset, cyl1.base.x[2], &(seed[0]));
                  change_start_height = cyl1.base.x[2];
               }
               /* change the cylinder properties */
               Change_Cylinder (&cyl1, pB, pPR, motion_offset, moisture_offset, track); 
               /* image cylinders */
               weight_sum	+= Image_Cylinder_Direct (&cyl1, &(pSGdirect[track]), pPR, 1.0, Cscatt_Flag, &(Sdirect[i_section]));
               weight_sum2	+= Image_Cylinder_Bounce (&cyl1, &(pSGbounce[track]), pPR, 1.0, Cscatt_Flag, &(Sbounce[i_section]));
               weight_count	+= 1.0;
            }
         }
         free(Sdirect);
         free(Sbounce);
         pB			= pB->next;
      }
   }
#endif
   /***************************/
   /* Image tertiary branches */
   /***************************/
#ifndef POLSARPROSIM_NO_SAR_TERTIARIES
#ifndef FORCE_GRG_CYLINDERS
   if (pPR->Grg_Flag == 0) {
      Cscatt_Flag	=    POLSARPROSIM_SAR_GRG_TERTIARY_BRANCHES;
   } else {
      Cscatt_Flag	=    POLSARPROSIM_SAR_INF_TERTIARY_BRANCHES;
   }
#endif
   if(pT->Tertiary.head != NULL_PTR2BRANCH_LIST){
      weight_sum				= 0.0;
      weight_count			= 0.0;
      pB                   = pT->Tertiary.head;
      tb_scaling           = pT->Tertiary.scale_factor; /* New addition to the Branch_list structure --RAedit */
      for (iBranch=0L; iBranch < pT->Tertiary.n; iBranch++) {
         Nsections   = (int) (pB->l/bsecl) + 1;
         deltat      = 1.0 / (double) Nsections;
         deltar      = (pB->start_radius - pB->end_radius) / (double) Nsections;
         Sdirect     = (c4Vector *)calloc(Nsections, sizeof(c4Vector));
         Sbounce     = (c4Vector *)calloc(Nsections, sizeof(c4Vector));
         change_start_height  = pB->b0.x[2];
         for (track=0;track<pPR->Tracks;track++){
            /* compute initial change in branch properties (position and moisture) */
            Model_Change (pT, pPR, track, &motion_offset, &moisture_offset, change_start_height, &(seed[0]));
            for (i_section = 0; i_section < Nsections; i_section++) {
               rtn_value     = Cylinder_from_Branch (&cyl1, pB, i_section, Nsections);
               /* recompute changed properties if branch exceed a height level */
               if(cyl1.base.x[2] > change_start_height + pPR->change_height_delta) {
                  Model_Change (pT, pPR, track, &motion_offset, &moisture_offset, cyl1.base.x[2], &(seed[0]));
                  change_start_height = cyl1.base.x[2];
               }
               /* change the cylinder properties */
               Change_Cylinder (&cyl1, pB, pPR, motion_offset, moisture_offset, track); 
               /* image cylinders */
               weight_sum		+= Image_Cylinder_Direct (&cyl1, &(pSGdirect[track]), pPR, tb_scaling, Cscatt_Flag, &(Sdirect[i_section]));
               weight_sum2		+= Image_Cylinder_Bounce (&cyl1, &(pSGbounce[track]), pPR, tb_scaling, Cscatt_Flag, &(Sbounce[i_section]));
               weight_count	+= 1.0;
            }
         }
         free(Sdirect);
         free(Sbounce);
         pB              = pB->next;
      }
   }
#endif
   
   /*****************/
   /* Image foliage */
   /*****************/
#ifndef POLSARPROSIM_NO_SAR_FOLIAGE
   if(pT->Foliage.head != NULL_PTR2LEAF_LIST){
      weight_sum		= 0.0;
      weight_count	= 0.0;
      pL             = pT->Foliage.head;
      flg_scaling    = pT->Foliage.scale_factor;
      Leaf_Depolarization_Factors (pL, &leafL1, &leafL2, &leafL3);
      Ldvec = Cartesian_Assign_d3Vector(leafL1, leafL2, leafL3);
//            pPR->Tertiary_leafL1	= leafL1;
//            pPR->Tertiary_leafL2	= leafL2;
//            pPR->Tertiary_leafL3	= leafL3;
      Sdirect     = (c4Vector *)calloc(1, sizeof(c4Vector));
      Sbounce     = (c4Vector *)calloc(1, sizeof(c4Vector));
      for (iLeaf=0L; iLeaf < pT->Foliage.n; iLeaf++) {
         for (track=0;track<pPR->Tracks;track++){
            Model_Change (pT, pPR, track, &motion_offset, &moisture_offset, pL->cl.x[2], &(seed[0]));
            Change_Leaf  (pL, pPR, motion_offset, moisture_offset, track); 
            weight_sum           += Image_Foliage_Direct (pL, &(pSGdirect[track]), pPR, flg_scaling, &Ldvec, &(Sdirect[0]));
            weight_sum2          += Image_Foliage_Bounce (pL, &(pSGbounce[track]), pPR, flg_scaling, &Ldvec, &(Sbounce[0]));
            weight_count         += 1.0;
         }
         pL = pL->next;
      }
   }
#endif
   /***************/
   /* Tidy up ... */
   /***************/
   Destroy_Cylinder (&cyl1);
   Destroy_Tree(pT);
   free(Sdirect);
   free(Sbounce);
   /********************/
   /* ... and go home. */
   /********************/
   pthread_exit(NULL);
}


/* Multithreaded version of Forest Scattering */
int		PolSARproSim_Forest_SMP		(PolSARproSim_Record *pPR)
{
   int                     itree;
   SarGeometry             *SGdirect;
   SarGeometry             *SGbounce;
   int                     rtn_value;
   int                     track;
   /* some variables for hyperthreading */
   ImageTree_Thread_Arg    *threadarg; /* pointer to array of thread arguments   */
   pthread_t               *threads;   /* pointer to arry of thread ids          */
   pthread_attr_t          attr;       /* a global thread attribute              */
   int                     rc;         /* thread return code                     */
   void                    *status;    /* thread status                          */
#ifdef OUTPUT_CHANGE_STATS_ON 
   int i,j,index;
#endif

   
   /* initialize thread variables */
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
   /* allocate memory */
   threadarg = (ImageTree_Thread_Arg *)calloc(pPR->Trees,sizeof(ImageTree_Thread_Arg));
   threads   = (pthread_t *)calloc(pPR->Trees,sizeof(pthread_t));

   /* initialize SAR geometry variables*/
   SGdirect   = (SarGeometry*) calloc (pPR->Tracks, sizeof (SarGeometry));
   SGbounce   = (SarGeometry*) calloc (pPR->Tracks, sizeof (SarGeometry));
   /**********************************/
   /* Set up the SAR geometry record */
   /**********************************/
   for (track = 0; track < pPR->Tracks; track++) {
      rtn_value	= Initialise_SAR_Geometry (&SGdirect[track], pPR, track);
      rtn_value	= Initialise_SAR_Geometry (&SGbounce[track], pPR, track);
   }


   /**********************/
   /* Imaging the forest */
   /**********************/
#ifdef VERBOSE_POLSARPROSIM
   printf ("\n");
   printf ("Call to PolSARproSim_Forest_SMP ... \n");
   printf ("\n");
#endif
   fprintf (pPR->pLogFile, "Call to PolSARproSim_Forest_SMP ... \n");
   fflush  (pPR->pLogFile);
      
   /********************************/
   /* Seed random number generator */
   /********************************/
   srand (pPR->seed);
   /**************************/
   /* Main tree imaging loop */
   /**************************/
   for (itree=0; itree<pPR->Trees; itree++) {
      /* assign thread arguments */
      Create_Tree                (&(threadarg[itree].tree1));
      Realise_Tree               (&(threadarg[itree].tree1), itree, pPR);
      threadarg[itree].pPR       = pPR;
      threadarg[itree].itree     = itree;      
      threadarg[itree].pSGdirect = SGdirect;
      threadarg[itree].pSGbounce = SGbounce;
      /* create threads */
      rc=pthread_create(&threads[itree], &attr, Image_Tree_SMP, (void *)&threadarg[itree]);
      if(rc){
         printf("Oops! Thread for tree %d was not created in PolSARproSim_Forest_SMP, (ERR code: %d)\n", itree, rc);
         exit(-1);
      }
   }
   /* loop over the trees to join threads */
   for (itree=0; itree<pPR->Trees; itree++) {
      rc=pthread_join(threads[itree], &status);
      if(rc){
         printf("ERR: unable to join thread for tree no. %d in in PolSARproSim_Forest_SMP, code: %d\n", itree,rc);
         exit(-1);
      }
   }
      
   /* write out some average backscattering coefficients */    
   for (track = 0; track < pPR->Tracks; track++) {
      fprintf(pPR->pLogFile, "Forest Statistics for track %d\n", track);
      /******************************/
      /* Monitor Direct performance */
      /******************************/
      SGdirect[track].Sigma0_count	 = pPR->Lx*pPR->Ly;
      SGdirect[track].Sigma0HH		/= SGdirect[track].Sigma0_count;
      SGdirect[track].Sigma0HV		/= SGdirect[track].Sigma0_count;
      SGdirect[track].Sigma0VH		/= SGdirect[track].Sigma0_count;
      SGdirect[track].Sigma0VV		/= SGdirect[track].Sigma0_count;
      SGdirect[track].AvgShhvv		= complex_rmul (SGdirect[track].AvgShhvv, 1.0/SGdirect[track].Sigma0_count);
      fprintf (pPR->pLogFile, "Direct Forest HH backscattering coefficient\t= %lf dB\n", 10.0*log10(SGdirect[track].Sigma0HH));
      fprintf (pPR->pLogFile, "Direct Forest HV backscattering coefficient\t= %lf dB\n", 10.0*log10(SGdirect[track].Sigma0HV));
      fprintf (pPR->pLogFile, "Direct Forest VH backscattering coefficient\t= %lf dB\n", 10.0*log10(SGdirect[track].Sigma0VH));
      fprintf (pPR->pLogFile, "Direct Forest VV backscattering coefficient\t= %lf dB\n", 10.0*log10(SGdirect[track].Sigma0VV));
      fprintf (pPR->pLogFile, "Direct Forest HHVV correlation magnitude   \t= %lf dB\n", 10.0*log10(SGdirect[track].AvgShhvv.r));
      fprintf (pPR->pLogFile, "Direct Forest HHVV correlation phase       \t= %lf rads.\n", SGdirect[track].AvgShhvv.phi);
      fflush  (pPR->pLogFile);
      /******************************/
      /* Monitor Bounce performance */
      /******************************/
      SGbounce[track].Sigma0_count	 = pPR->Lx*pPR->Ly;
      SGbounce[track].Sigma0HH		/= SGbounce[track].Sigma0_count;
      SGbounce[track].Sigma0HV		/= SGbounce[track].Sigma0_count;
      SGbounce[track].Sigma0VH		/= SGbounce[track].Sigma0_count;
      SGbounce[track].Sigma0VV		/= SGbounce[track].Sigma0_count;
      SGbounce[track].AvgShhvv		= complex_rmul (SGbounce[track].AvgShhvv, 1.0/SGbounce[track].Sigma0_count);
      fprintf (pPR->pLogFile, "Bounce Forest HH backscattering coefficient\t= %lf dB\n", 10.0*log10(SGbounce[track].Sigma0HH));
      fprintf (pPR->pLogFile, "Bounce Forest HV backscattering coefficient\t= %lf dB\n", 10.0*log10(SGbounce[track].Sigma0HV));
      fprintf (pPR->pLogFile, "Bounce Forest VH backscattering coefficient\t= %lf dB\n", 10.0*log10(SGbounce[track].Sigma0VH));
      fprintf (pPR->pLogFile, "Bounce Forest VV backscattering coefficient\t= %lf dB\n", 10.0*log10(SGbounce[track].Sigma0VV));
      fprintf (pPR->pLogFile, "Bounce Forest HHVV correlation magnitude   \t= %lf dB\n", 10.0*log10(SGbounce[track].AvgShhvv.r));
      fprintf (pPR->pLogFile, "Bounce Forest HHVV correlation phase       \t= %lf rads.\n", SGbounce[track].AvgShhvv.phi);
      fflush  (pPR->pLogFile);

   }

   /***********/
   /* Tidy up */
   /***********/
   for (track=0;track<pPR->Tracks;track++){
      Delete_SAR_Geometry (&SGdirect[track]);
      Delete_SAR_Geometry (&SGbounce[track]);
   }
   free(threadarg);

   /***************************************************************************/
   /* Report statistics of changes applied to scatterer position and moisture */
   /***************************************************************************/
#ifdef OUTPUT_CHANGE_STATS_ON 
   fprintf (pPR->pLogFile, "\nMotion Offset Profile (x-axis only): Height [m], mean [line 0], variance [line 0], count [line 0], mean [line 1], variance [line 1]..... \n");
   for(i=0;i<CHANGE_PROFILE_BINS;i++){
      fprintf(pPR->pLogFile, "%f",  (double)(i*pPR->change_profile_bin_res));
      for(j=0;j<pPR->Tracks;j++){
         index = i * pPR->Tracks + j;
         if(pPR->motion_profile_count[index] > 2){
            /* this is what the statistics should really be */
            fprintf (pPR->pLogFile, "\t%f\t%f\t%d", pPR->motion_profile_mean[index], 
                   (double)(pPR->motion_profile_var[index]/(pPR->motion_profile_count[index]-1)), 
                   pPR->motion_profile_count[index]);
         }else{
            /* this is just to avoid divide by zero, may be inaccurate */
            fprintf (pPR->pLogFile, "\t%f\t%f\t%d", pPR->motion_profile_mean[i+j], 
                   (double)(pPR->motion_profile_var[index]/(pPR->motion_profile_count[index]+1)),
                   pPR->motion_profile_count[index]);
         }
      }
      fprintf (pPR->pLogFile, "\n");
   }
   fprintf (pPR->pLogFile, "\nMoisture Offset Profile: Height [m], mean [line 0], variance [line 0], mean [line 1], count [line 0], variance [line 1]..... \n");
   for(i=0;i<CHANGE_PROFILE_BINS;i++){
      fprintf(pPR->pLogFile, "%f",  (double)(i*pPR->change_profile_bin_res));
      for(j=0;j<pPR->Tracks;j++){
         index = i * pPR->Tracks + j;
         if(pPR->moisture_profile_count[index] > 2){
            /* this is what the statistics should really be */
            fprintf (pPR->pLogFile, "\t%f\t%f\t%d", pPR->moisture_profile_mean[index], 
                   (double)(pPR->moisture_profile_var[index]/(pPR->moisture_profile_count[index]-1)), 
                   pPR->moisture_profile_count[index]);
         }else{
            /* this is just to avoid divide by zero, may be inaccurate */
            fprintf (pPR->pLogFile, "\t%f\t%f\t%d", pPR->moisture_profile_mean[i+j], 
                   (double)(pPR->moisture_profile_var[index]/(pPR->moisture_profile_count[index]+1)),
                   pPR->moisture_profile_count[index]);
         }
      }
      fprintf (pPR->pLogFile, "\n");
   }
#endif 

   /**********************************************/
   /* Report progress if running in VERBOSE mode */
   /**********************************************/
#ifdef VERBOSE_POLSARPROSIM
   printf ("\n");
   printf ("... Returning from call to PolSARproSim_Forest_SMP\n");
   printf ("\n");
#endif
   fprintf (pPR->pLogFile, "... Returning from call to PolSARproSim_Forest_SMP\n\n");
   fflush  (pPR->pLogFile);
   /********************************/
   /* Increment progress indicator */
   /********************************/
   pPR->progress++;
   /********************************/
   /* Report progress if requested */
   /********************************/
#ifdef POLSARPROSIM_MAX_PROGRESS
   PolSARproSim_indicate_progress (pPR);
#endif
   /*****************************/
   /* Return to calling routine */
   /*****************************/
   return (NO_POLSARPROSIM_FOREST_ERRORS);
}