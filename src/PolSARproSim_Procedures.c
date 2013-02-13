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
 * Module      : PolSARproSim_Procedures.c
 * Revision    : Version C1b 
 * Date        : September, 2007
 * Notes       : Procedure implementations for PolSARproSim
 */
#include	"PolSARproSim_Procedures.h"

/*****************/
/* House keeping */
/*****************/

void	PolSARproSim_notice			(FILE *fp)
{
   fprintf (fp, "\n");
   fprintf (fp, "************************************************************************\n");
   fprintf (fp, "*                                                                      *\n");
   fprintf (fp, "* PolSARproSim Version C1b  Forest Synthetic Aperture Radar Simulation *\n");
   fprintf (fp, "* Copyright (C) 2007 Mark L. Williams (mark.williams@physics.org)      *\n");
   fprintf (fp, "*                                                                      *\n");
   fprintf (fp, "* PolSARproSim Version C1b  is free software; you may redistribute it  *\n");
   fprintf (fp, "* and/or modify it under the terms of the GNU General Public License   *\n");
   fprintf (fp, "* as published by the Free Software Foundation; either version 2       *\n");
   fprintf (fp, "* of the License, or (at your option) any later version.               *\n");
   fprintf (fp, "*                                                                      *\n");
   fprintf (fp, "* PolSARproSim Version C1b  is distributed in the hope that it will be *\n");
   fprintf (fp, "* useful,but WITHOUT ANY WARRANTY; without even the implied warranty   *\n");
   fprintf (fp, "* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.              *\n");
   fprintf (fp, "* See the GNU General Public License for more details.                 *\n");
   fprintf (fp, "*                                                                      *\n");
   fprintf (fp, "* You should have received a copy of the GNU General Public License    *\n");
   fprintf (fp, "* along with this program; if not, write to the Free Software          *\n");
   fprintf (fp, "* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,           *\n");
   fprintf (fp, "* MA  02110-1301, USA. (http://www.gnu.org/copyleft/gpl.html)          *\n");
   fprintf (fp, "*                                                                      *\n");
   fprintf (fp, "************************************************************************\n");
   fprintf (fp, "\n");
   fflush  (fp);
   return;
}

void	PolSARproSim_compile_options (FILE *fp)
{
   int	i;
   double	d;
   float	f;
   /********************************/
   /* Housekeeping and conventions */
   /********************************/
   fprintf (fp, "\nCompile options report ...\n\n");
   i		= NO_POLSARPROSIM_ERRORS;
   fprintf (fp, "NO_POLSARPROSIM_ERRORS\t%d\n", i);
#ifdef	VERBOSE_POLSARPROSIM
   fprintf (fp, "VERBOSE_POLSARPROSIM\n");
#endif
#ifdef POLSARPROSIM_MAX_PROGRESS
   i		= POLSARPROSIM_MAX_PROGRESS;
   fprintf (fp, "POLSARPROSIM_MAX_PROGRESS\t\t%d\n", i);
#endif
#ifdef POLSARPRO_CONVENTION
   fprintf (fp, "POLSARPRO_CONVENTION\n");
#endif
#ifdef POLSARPROSIM_ROTATED_IMAGES
   fprintf (fp, "POLSARPROSIM_ROTATED_IMAGES\n\n");
#endif
   /**************************************/
   /* Tree species allometric parameters */
   /**************************************/
   d		= 	TREE_STDDEV_FACTOR;
   fprintf (fp, "TREE_STDDEV_FACTOR\t\t\t\t\t%lf\n", d);
   /*******************************/
   /* Scene generation parameters */
   /*******************************/
   d		= 	RESOLUTION_GAP_SIZE;
   fprintf (fp, "RESOLUTION_GAP_SIZE\t%lf\n\n", d);
   /*****************************************/
   /* Large scale ground surface generation */
   /*****************************************/
   i		= POLSARPROSIM_GROUND_FOURIER_MOMENTS;
   fprintf (fp, "POLSARPROSIM_GROUND_FOURIER_MOMENTS\t%d\n\n", i);
   /*********************************/
   /* Surface parameter calculation */
   /*********************************/
   d		= 	POLSARPROSIM_MINRDB;
   fprintf (fp, "POLSARPROSIM_MINRDB\t%lf\n", d);
   d		= 	POLSARPROSIM_MAXRDB;
   fprintf (fp, "POLSARPROSIM_MAXRDB\t%lf\n", d);
   d		= 	POLSARPROSIM_DEFAULT_SURFACE_ALPHA;
   fprintf (fp, "POLSARPROSIM_DEFAULT_SURFACE_ALPHA\t%lf\n", d);
   d		= 	POLSARPROSIM_DEFAULT_SIGMA0HH;
   fprintf (fp, "POLSARPROSIM_DEFAULT_SIGMA0HH\t%lf\n", d);
   d		= 	POLSARPROSIM_SIGMA0HHL45;
   fprintf (fp, "POLSARPROSIM_SIGMA0HHL45\t%lf\n", d);
   d		= 	POLSARPROSIM_SIGMA0HHP45;
   fprintf (fp, "POLSARPROSIM_SIGMA0HHP45\t%lf\n", d);
   d		= 	POLSARPROSIM_LBAND;
   fprintf (fp, "POLSARPROSIM_LBAND\t%lf\n", d);
   d		= 	POLSARPROSIM_PBAND;
   fprintf (fp, "POLSARPROSIM_PBAND\t%lf\n", d);
   d		= 	POLSARPROSIM_DELTAS0HHDB;
   fprintf (fp, "POLSARPROSIM_DELTAS0HHDB\t%lf\n", d);
   /****************************/
   /* Tree location generation */
   /****************************/
   d		= 	TREE_DISC_SHUFFLE_RADIUS_FACTOR;
   fprintf (fp, "TREE_DISC_SHUFFLE_RADIUS_FACTOR\t%lf\n", d);
   i		= 	TREE_LOCATION_NEAREST_NEIGHBOURS;
   fprintf (fp, "TREE_LOCATION_NEAREST_NEIGHBOURS\t%d\n", i);
   d		= 	TREE_DISC_SHUFFLE_FACTOR;
   fprintf (fp, "TREE_DISC_SHUFFLE_FACTOR\t\t%lf\n", d);
   d		= 	TREE_DISC_ACCEPTANCE_RATE;
   fprintf (fp, "TREE_DISC_ACCEPTANCE_RATE\t\t%lf\n", d);
   i		= 	TREE_DISC_ILOOP_MAX;
   fprintf (fp, "TREE_DISC_ILOOP_MAX\t\t\t%d\n", i);
   i		=	TREE_DISC_JLOOP_MAX;
   fprintf (fp, "TREE_DISC_JLOOP_MAX\t\t\t%d\n", i);
   d		= 	TREE_DISC_TEMP_FACTOR;
   fprintf (fp, "TREE_DISC_TEMP_FACTOR\t\t\t%lf\n", d);
   d		= 	TREE_DISC_TEMP_ALPHA;
   fprintf (fp, "TREE_DISC_TEMP_ALPHA\t\t\t%lf\n", d);
   d		= 	TREE_DISC_ROTATION_ANGLE;
   fprintf (fp, "TREE_DISC_ROTATION_ANGLE\t\t%lf\n", d);
   i		= 	TREE_DISC_NIMAGES;
   fprintf (fp, "TREE_DISC_NIMAGES\t\t\t\t%d\n\n", i);
   /*****************************************/
   /* Short vegetation realisation controls */
   /*****************************************/
   d		=	DEFAULT_SHORT_VEGI_DEPTH;
   fprintf (fp, "DEFAULT_SHORT_VEGI_DEPTH\t\t%lf\n", d);
   d		=	DEFAULT_SHORT_VEGI_STEM_VOL_FRAC;
   fprintf (fp, "DEFAULT_SHORT_VEGI_STEM_VOL_FRAC\t\t%lf\n", d);
   d		=	DEFAULT_SHORT_VEGI_LEAF_VOL_FRAC;
   fprintf (fp, "DEFAULT_SHORT_VEGI_LEAF_VOL_FRAC\t\t%lf\n", d);
   d		=	POLSARPROSIM_SHORTV_STEM_LENGTH;
   fprintf (fp, "POLSARPROSIM_SHORTV_STEM_LENGTH\t\t%lf\n", d);
   d		=	POLSARPROSIM_SHORTV_STEM_RADIUS;
   fprintf (fp, "POLSARPROSIM_SHORTV_STEM_RADIUS\t\t%lf\n", d);
   d		=	POLSARPROSIM_SHORTV_LEAF_LENGTH;
   fprintf (fp, "POLSARPROSIM_SHORTV_LEAF_LENGTH\t\t%lf\n", d);
   d		=	POLSARPROSIM_SHORTV_LEAF_WIDTH;
   fprintf (fp, "POLSARPROSIM_SHORTV_LEAF_WIDTH\t\t%lf\n", d);
   d		=	POLSARPROSIM_SHORTV_LEAF_THICKNESS;
   fprintf (fp, "POLSARPROSIM_SHORTV_LEAF_THICKNESS\t\t%lf\n\n", d);
   /****************************************************/
   /* Graphic image rendering (ground is always drawn) */
   /****************************************************/
#ifdef	FOREST_GRAPHIC_DRAW_SHORTV_ELEMENTS
   fprintf (fp, "FOREST_GRAPHIC_DRAW_SHORTV_ELEMENTS\n");
#endif
#ifdef	FOREST_GRAPHIC_DRAW_SHORTV_SURFACE
   fprintf (fp, "FOREST_GRAPHIC_DRAW_SHORTV_SURFACE\n");
#endif
#ifdef	FOREST_GRAPHIC_DRAW_STEM
   fprintf (fp, "FOREST_GRAPHIC_DRAW_STEM\n");
#endif
#ifdef	FOREST_GRAPHIC_DRAW_PRIMARY
   fprintf (fp, "FOREST_GRAPHIC_DRAW_PRIMARY\n");
#endif
#ifdef	FOREST_GRAPHIC_DRAW_SECONDARY
   fprintf (fp, "FOREST_GRAPHIC_DRAW_SECONDARY\n");
#endif
#ifdef	FOREST_GRAPHIC_DRAW_TERTIARY
   fprintf (fp, "FOREST_GRAPHIC_DRAW_TERTIARY\n");
#endif
#ifdef	FOREST_GRAPHIC_DRAW_FOLIAGE
   fprintf (fp, "FOREST_GRAPHIC_DRAW_FOLIAGE\n");
#endif
#ifdef	FOREST_GRAPHIC_DRAW_CROWN
   fprintf (fp, "FOREST_GRAPHIC_DRAW_CROWN\n\n");
#endif
   /************************************/
   /* Graphic image rendering controls */
   /************************************/
   i		=	FOREST_GRAPHIC_NY;
   fprintf (fp, "FOREST_GRAPHIC_NY\t%d\n", i);
   i		=	FOREST_NEAR_PLANE_FACTOR;
   fprintf (fp, "FOREST_NEAR_PLANE_FACTOR\t\t\t%d\n", i);
   d		=	FOREST_GRAPHIC_IMAGE_SIZE_FACTOR;
   fprintf (fp, "FOREST_GRAPHIC_IMAGE_SIZE_FACTOR\t\t%lf\n", d);
   d		=	FOREST_LIGHT_POLAR_ANGLE;
   fprintf (fp, "FOREST_LIGHT_POLAR_ANGLE\t\t\t%lf\n", d);
   d		=	FOREST_LIGHT_AZIMUTH_ANGLE;
   fprintf (fp, "FOREST_LIGHT_AZIMUTH_ANGLE\t\t\t%lf\n", d);
   d		=	FOREST_GRAPHIC_AMBIENT_INTENSITY;
   fprintf (fp, "FOREST_GRAPHIC_AMBIENT_INTENSITY\t\t%lf\n", d);
   d		=	FOREST_GRAPHIC_INCIDENT_INTENSITY;
   fprintf (fp, "FOREST_GRAPHIC_INCIDENT_INTENSITY\t\t%lf\n", d);
#ifdef	FOREST_GRAPHIC_DEPTH_CUE
   fprintf (fp, "FOREST_GRAPHIC_DEPTH_CUE\n");
#endif
   f		=	FOREST_GRAPHIC_MIN_CUE;
   fprintf (fp, "FOREST_GRAPHIC_MIN_CUE\t\t\t\t%f\n", f);
   d		=	FOREST_GRAPHIC_CROWN_ALPHA_BLEND;
   fprintf (fp, "FOREST_GRAPHIC_CROWN_ALPHA_BLEND\t\t%lf\n", d);
   d		=	FOREST_GRAPHIC_SHORTV_ALPHA_BLEND;
   fprintf (fp, "FOREST_GRAPHIC_SHORTV_ALPHA_BLEND\t\t%lf\n", d);
   i		=	FOREST_GRAPHIC_SHORTV_FACTOR;
   fprintf (fp, "FOREST_GRAPHIC_SHORTV_FACTOR\t\t\t%d\n", i);
   d		= 	FOREST_GRAPHIC_SHORTV_STEM_FRACTION;
   fprintf (fp, "FOREST_GRAPHIC_SHORTV_STEM_FRACTION\t\t%lf\n", d);
   i		=	FOREST_GRAPHIC_TERTIARY_NUMBER;
   fprintf (fp, "FOREST_GRAPHIC_TERTIARY_NUMBER\t\t%d\n", i);
   i		=	FOREST_GRAPHIC_HEDGE_TERTIARY_SCALING;
   fprintf (fp, "FOREST_GRAPHIC_HEDGE_TERTIARY_SCALING\t%d\n", i);
   i		=	FOREST_GRAPHIC_BACKGROUND_RED;
   fprintf (fp, "FOREST_GRAPHIC_BACKGROUND_RED\t\t\t%d\n", i);
   i		=	FOREST_GRAPHIC_BACKGROUND_GREEN;
   fprintf (fp, "FOREST_GRAPHIC_BACKGROUND_GREEN\t\t%d\n", i);
   i		=	FOREST_GRAPHIC_BACKGROUND_BLUE;
   fprintf (fp, "FOREST_GRAPHIC_BACKGROUND_BLUE\t\t%d\n\n", i);
   /*************************************/
   /* Graphic image material properties */
   /*************************************/
   d		=	FOREST_GRAPHIC_GROUND_KA;
   fprintf (fp, "FOREST_GRAPHIC_GROUND_KA\t%lf\n", d);
   d		=	FOREST_GRAPHIC_GROUND_KD;
   fprintf (fp, "FOREST_GRAPHIC_GROUND_KD\t%lf\n", d);
   d		=	FOREST_GRAPHIC_GROUND_KS;
   fprintf (fp, "FOREST_GRAPHIC_GROUND_KS\t%lf\n", d);
   d		=	FOREST_GRAPHIC_GROUND_SR;
   fprintf (fp, "FOREST_GRAPHIC_GROUND_SR\t%lf\n", d);
   d		=	FOREST_GRAPHIC_GROUND_SG;
   fprintf (fp, "FOREST_GRAPHIC_GROUND_SG\t%lf\n", d);
   d		=	FOREST_GRAPHIC_GROUND_SB;
   fprintf (fp, "FOREST_GRAPHIC_GROUND_SB\t%lf\n", d);
   d		=	FOREST_GRAPHIC_SHORTV_KA;
   fprintf (fp, "FOREST_GRAPHIC_SHORTV_KA\t%lf\n", d);
   d		=	FOREST_GRAPHIC_SHORTV_KD;
   fprintf (fp, "FOREST_GRAPHIC_SHORTV_KD\t%lf\n", d);
   d		=	FOREST_GRAPHIC_SHORTV_KS;
   fprintf (fp, "FOREST_GRAPHIC_SHORTV_KS\t%lf\n", d);
   d		=	FOREST_GRAPHIC_SHORTV_SR;
   fprintf (fp, "FOREST_GRAPHIC_SHORTV_SR\t%lf\n", d);
   d		=	FOREST_GRAPHIC_SHORTV_SG;
   fprintf (fp, "FOREST_GRAPHIC_SHORTV_SG\t%lf\n", d);
   d		=	FOREST_GRAPHIC_SHORTV_SB;
   fprintf (fp, "FOREST_GRAPHIC_SHORTV_SB\t%lf\n", d);
   d		=	FOREST_GRAPHIC_BRANCH_KA;
   fprintf (fp, "FOREST_GRAPHIC_BRANCH_KA\t%lf\n", d);
   d		=	FOREST_GRAPHIC_BRANCH_KD;
   fprintf (fp, "FOREST_GRAPHIC_BRANCH_KD\t%lf\n", d);
   d		=	FOREST_GRAPHIC_BRANCH_KS;
   fprintf (fp, "FOREST_GRAPHIC_BRANCH_KS\t%lf\n", d);
   d		=	FOREST_GRAPHIC_BRANCH_SR;
   fprintf (fp, "FOREST_GRAPHIC_BRANCH_SR\t%lf\n", d);
   d		=	FOREST_GRAPHIC_BRANCH_SG;
   fprintf (fp, "FOREST_GRAPHIC_BRANCH_SG\t%lf\n", d);
   d		=	FOREST_GRAPHIC_BRANCH_SB;
   fprintf (fp, "FOREST_GRAPHIC_BRANCH_SB\t%lf\n", d);
   d		=	FOREST_GRAPHIC_LCROWN_KA;
   fprintf (fp, "FOREST_GRAPHIC_LCROWN_KA\t%lf\n", d);
   d		=	FOREST_GRAPHIC_LCROWN_KD;
   fprintf (fp, "FOREST_GRAPHIC_LCROWN_KD\t%lf\n", d);
   d		=	FOREST_GRAPHIC_LCROWN_KS;
   fprintf (fp, "FOREST_GRAPHIC_LCROWN_KS\t%lf\n", d);
   d		=	FOREST_GRAPHIC_LCROWN_SR;
   fprintf (fp, "FOREST_GRAPHIC_LCROWN_SR\t%lf\n", d);
   d		=	FOREST_GRAPHIC_LCROWN_SG;
   fprintf (fp, "FOREST_GRAPHIC_LCROWN_SG\t%lf\n", d);
   d		=	FOREST_GRAPHIC_LCROWN_SB;
   fprintf (fp, "FOREST_GRAPHIC_LCROWN_SB\t%lf\n", d);
   d		=	FOREST_GRAPHIC_DCROWN_KA;
   fprintf (fp, "FOREST_GRAPHIC_DCROWN_KA\t%lf\n", d);
   d		=	FOREST_GRAPHIC_DCROWN_KD;
   fprintf (fp, "FOREST_GRAPHIC_DCROWN_KD\t%lf\n", d);
   d		=	FOREST_GRAPHIC_DCROWN_KS;
   fprintf (fp, "FOREST_GRAPHIC_DCROWN_KS\t%lf\n", d);
   d		=	FOREST_GRAPHIC_DCROWN_SR;
   fprintf (fp, "FOREST_GRAPHIC_DCROWN_SR\t%lf\n", d);
   d		=	FOREST_GRAPHIC_DCROWN_SG;
   fprintf (fp, "FOREST_GRAPHIC_DCROWN_SG\t%lf\n", d);
   d		=	FOREST_GRAPHIC_DCROWN_SB;
   fprintf (fp, "FOREST_GRAPHIC_DCROWN_SB\t%lf\n", d);
   d		=	FOREST_GRAPHIC_LEAF_KA;
   fprintf (fp, "FOREST_GRAPHIC_LEAF_KA\t\t%lf\n", d);
   d		=	FOREST_GRAPHIC_LEAF_KD;
   fprintf (fp, "FOREST_GRAPHIC_LEAF_KD\t\t%lf\n", d);
   d		=	FOREST_GRAPHIC_LEAF_KS;
   fprintf (fp, "FOREST_GRAPHIC_LEAF_KS\t\t%lf\n", d);
   d		=	FOREST_GRAPHIC_LEAF_SR;
   fprintf (fp, "FOREST_GRAPHIC_LEAF_SR\t\t%lf\n", d);
   d		=	FOREST_GRAPHIC_LEAF_SG;
   fprintf (fp, "FOREST_GRAPHIC_LEAF_SG\t\t%lf\n", d);
   d		=	FOREST_GRAPHIC_LEAF_SB;
   fprintf (fp, "FOREST_GRAPHIC_LEAF_SB\t\t%lf\n\n", d);
   /*********************************/
   /* Graphic image tree parameters */
   /*********************************/
   i		=	FOREST_GRAPHIC_MIN_BRANCH_SIDES;
   fprintf (fp, "FOREST_GRAPHIC_MIN_BRANCH_SIDES\t%d\n", i);
   i		=	FOREST_GRAPHIC_MAX_BRANCH_SIDES;
   fprintf (fp, "FOREST_GRAPHIC_MAX_BRANCH_SIDES\t%d\n", i);
   i		=	FOREST_GRAPHIC_MIN_BRANCH_SECTIONS;
   fprintf (fp, "FOREST_GRAPHIC_MIN_BRANCH_SECTIONS\t%d\n", i);
   i		=	FOREST_GRAPHIC_MAX_BRANCH_SECTIONS;
   fprintf (fp, "FOREST_GRAPHIC_MAX_BRANCH_SECTIONS\t%d\n", i);
   i		=	FOREST_GRAPHIC_MIN_CROWN_SIDES;
   fprintf (fp, "FOREST_GRAPHIC_MIN_CROWN_SIDES\t%d\n", i);
   i		=	FOREST_GRAPHIC_MAX_CROWN_SIDES;
   fprintf (fp, "FOREST_GRAPHIC_MAX_CROWN_SIDES\t%d\n", i);
   i		=	FOREST_GRAPHIC_MIN_CROWN_SECTIONS;
   fprintf (fp, "FOREST_GRAPHIC_MIN_CROWN_SECTIONS\t%d\n", i);
   i		=	FOREST_GRAPHIC_MAX_CROWN_SECTIONS;
   fprintf (fp, "FOREST_GRAPHIC_MAX_CROWN_SECTIONS\t%d\n\n", i);
   /********************************/
   /* Ray intersection definitions */
   /********************************/
   i		=	NO_RAYPLANE_ERRORS;
   fprintf (fp, "NO_RAYPLANE_ERRORS\t%d\n", i);
   i		=	NO_RAYCYLINDER_ERRORS;
   fprintf (fp, "NO_RAYCYLINDER_ERRORS\t%d\n", i);
   i		=	NO_RAYCONE_ERRORS;
   fprintf (fp, "NO_RAYCONE_ERRORS\t\t%d\n", i);
   i		=	NO_RAYSPHEROID_ERRORS;
   fprintf (fp, "NO_RAYSPHEROID_ERRORS\t%d\n", i);
   i		=	NO_RAYCROWN_ERRORS;
   fprintf (fp, "NO_RAYCROWN_ERRORS\t%d\n\n", i);
   /*****************/
   /* Miscellaneous */
   /*****************/
   d		=	ROUNDING_ERROR;
   fprintf (fp, "ROUNDING_ERROR\t\t%13.6e\n", d);
   d		=	LIGHT_SPEED;
   fprintf (fp, "LIGHT_SPEED\t\t\t%lf\n\n", d);
   /***************************************/
   /* Ground surface description controls */
   /***************************************/
   d		=	DEFAULT_GROUND_MV;
   fprintf (fp, "DEFAULT_GROUND_MV\t\t%lf\n", d);
#ifdef INPUT_GROUND_MV
   fprintf (fp, "INPUT_GROUND_MV\n");
#endif
   d		=	MIN_GROUND_MV;
   fprintf (fp, "MIN_GROUND_MV\t\t%lf\n", d);
   d		=	MAX_GROUND_MV;
   fprintf (fp, "MAX_GROUND_MV\t\t%lf\n\n", d);
   /******************************/
   /* Attenuation and scattering */
   /******************************/
   i		=	POLSARPROSIM_SHORT_VEGI_NTHETA;
   fprintf (fp, "POLSARPROSIM_SHORT_VEGI_NTHETA\t%d\n", i);
   i		=	POLSARPROSIM_SHORT_VEGI_NPHI;
   fprintf (fp, "POLSARPROSIM_SHORT_VEGI_NPHI\t\t%d\n", i);
   i		=	POLSARPROSIM_ATTENUATION_TREES;
   fprintf (fp, "POLSARPROSIM_ATTENUATION_TREES\t%d\n", i);
   i		=	POLSARPROSIM_TERTIARY_NTHETA;
   fprintf (fp, "POLSARPROSIM_TERTIARY_NTHETA\t\t%d\n", i);
   i		=	POLSARPROSIM_TERTIARY_NPHI;
   fprintf (fp, "POLSARPROSIM_TERTIARY_NPHI\t\t%d\n", i);
   d		=	GRG_VALIDITY_FACTOR;
   fprintf (fp, "GRG_VALIDITY_FACTOR\t\t\t%lf\n", d);
   d		=	AMAP_RESOLUTION_FACTOR;
   fprintf (fp, "AMAP_RESOLUTION_FACTOR\t\t\t%lf\n", d);
   d		=	AMAP_VERTICAL_RESOLUTION;
   fprintf (fp, "AMAP_VERTICAL_RESOLUTION\t\t\t%lf\n", d);
   i		= AMAP_SHORT_VEGI_NZ;
   fprintf (fp, "AMAP_SHORT_VEGI_NZ\t\t\t%d\n", i);
   i		= NO_DIRECT_ATTENUATION_LOOKUP_ERRORS;
   fprintf (fp, "NO_DIRECT_ATTENUATION_LOOKUP_ERRORS\t%d\n\n", i);
   /*************************/
   /* SAR image calculation */
   /*************************/
   d		=	DEFAULT_RESOLUTION_SAMPLING_FACTOR;
   fprintf (fp, "DEFAULT_RESOLUTION_SAMPLING_FACTOR\t\t%lf\n", d);
   d		=	POWER_AT_PSF_EDGE;
   fprintf (fp, "POWER_AT_PSF_EDGE\t\t\t\t\t%lf\n", d);
   /**********************************************/
   /* Direct ground surface backscatter controls */
   /**********************************************/
   i		= POLSARPROSIM_DIRECTGROUND_SPECKLE_FACTOR;
   fprintf (fp, "POLSARPROSIM_DIRECTGROUND_SPECKLE_FACTOR\t%d\n", i);
   d		= POLSARPROSIM_DIRECTGROUND_DELTAB_FACTOR;
   fprintf (fp, "POLSARPROSIM_DIRECTGROUND_DELTAB_FACTOR\t%lf\n", d);
   /*****************************/
   /* Short vegetation controls */
   /*****************************/
   i		=	POLSARPROSIM_SHORT_VEGI_REALISATIONS;
   fprintf (fp, "POLSARPROSIM_SHORT_VEGI_REALISATIONS\t%d\n", i);
   /***************************************/
   /* Rayleigh reflection roughness model */
   /***************************************/
   i		=	POLSARPROSIM_RAYLEIGH_ROUGHNESS_MODEL;
   fprintf (fp, "POLSARPROSIM_RAYLEIGH_ROUGHNESS_MODEL\t%d\n\n", i);
   /*******************/
   /* Forest controls */
   /*******************/
#ifdef	POLSARPROSIM_SAR_BRANCH_FACTOR
   d		= POLSARPROSIM_SAR_BRANCH_FACTOR;
   fprintf (fp, "POLSARPROSIM_SAR_BRANCH_FACTOR\t%lf\n", d);
#endif
#ifdef	POLSARPROSIM_SAR_GRG_TERTIARY_BRANCHES
   i		= POLSARPROSIM_SAR_GRG_TERTIARY_BRANCHES;
   fprintf (fp, "POLSARPROSIM_SAR_GRG_TERTIARY_BRANCHES\t%d\n", i);
#endif
#ifdef	POLSARPROSIM_SAR_INF_TERTIARY_BRANCHES
   i		= POLSARPROSIM_SAR_INF_TERTIARY_BRANCHES;
   fprintf (fp, "POLSARPROSIM_SAR_INF_TERTIARY_BRANCHES\t%d\n", i);
#endif
#ifdef	POLSARPROSIM_VERBOSE_TERTIARY
   fprintf (fp, "POLSARPROSIM_VERBOSE_TERTIARY\n");
#endif
#ifdef	POLSARPROSIM_VERBOSE_FOLIAGE
   fprintf (fp, "POLSARPROSIM_VERBOSE_FOLIAGE\n\n");
#endif
   /*******************/
   /* Debugging Flags */
   /*******************/
#ifdef	SWITCH_ATTENUATION_ON
   fprintf (fp, "SWITCH_ATTENUATION_ON\n");
#endif
#ifdef	FLAT_DEM
   fprintf (fp, "FLAT_DEM\n");
#endif
#ifdef	NO_TREE_SHUFFLING
   fprintf (fp, "NO_TREE_SHUFFLING\n");
#endif
#ifdef	FORCE_GRG_CYLINDERS
   fprintf (fp, "FORCE_GRG_CYLINDERS\n");
#endif
#ifdef	RAYLEIGH_LEAF
   fprintf (fp, "RAYLEIGH_LEAF\n");
#endif
#ifdef	NO_SHORT_LEAVES
   fprintf (fp, "NO_SHORT_LEAVES\n");
#endif
#ifdef	NO_SHORT_STEMS
   fprintf (fp, "NO_SHORT_STEMS\n");
#endif
#ifdef	POLSARPROSIM_NO_SAR_STEMS
   fprintf (fp, "POLSARPROSIM_NO_SAR_STEMS\n");
#endif
#ifdef	POLSARPROSIM_NO_SAR_PRIMARIES
   fprintf (fp, "POLSARPROSIM_NO_SAR_PRIMARIES\n");
#endif
#ifdef	POLSARPROSIM_NO_SAR_SECONDARIES
   fprintf (fp, "POLSARPROSIM_NO_SAR_SECONDARIES\n");
#endif
#ifdef	POLSARPROSIM_NO_SAR_TERTIARIES
   fprintf (fp, "POLSARPROSIM_NO_SAR_TERTIARIES\n");
#endif
#ifdef	POLSARPROSIM_NO_SAR_FOLIAGE
   fprintf (fp, "POLSARPROSIM_NO_SAR_FOLIAGE\n");
#endif
#ifdef	POLSARPROSIM_STAGE3
   fprintf (fp, "POLSARPROSIM_STAGE3\n");
#endif
#ifdef	POLSARPROSIM_CROWN_OVERLAP_FACTOR
   d		= POLSARPROSIM_CROWN_OVERLAP_FACTOR;
   fprintf (fp, "POLSARPROSIM_CROWN_OVERLAP_FACTOR\t%lf\n", d);
#endif
   fprintf (fp, "\n");
   fflush (fp);
   return;
}

/*********************************/
/* Surface parameter calculation */
/*********************************/

double		ratio_from_delta	(double d)
{
   /*************************************************/
   /* Find r as a solution of r^2exp(1-r^2) - d = 0 */
   /*************************************************/
   double		x0	= d;
   double		f, fp, delta;
   int         i;
   const int	imax	= 5;
   for (i=0; i<imax; i++) {
      f			= x0*exp(1.0-x0) - d;
      fp       = (1.0-x0)*exp(1.0-x0);
      delta		= -f/fp;
      x0       = x0 + delta;
   }
   return (sqrt(fabs(x0)));
}

void		Surface_Parameters (PolSARproSim_Record *pPR, int DEM_model)
{
   double	alpha       = POLSARPROSIM_DEFAULT_SURFACE_ALPHA;
   double	minRdB		= POLSARPROSIM_MINRDB;
   double	midRdB		= POLSARPROSIM_MIDRDB;
   double	maxRdB		= POLSARPROSIM_MAXRDB;
   double	pi          = 4.0*atan(1.0);
   double	thetai		= pi/4.0;
   double	wavelength	= pPR->wavelength;
   double	cos_thetai	= cos(thetai);
   double	sin_thetai	= sin(thetai);
   double	k           = 2.0*pi/wavelength;
   double	sigma_s		= alpha/(k*cos_thetai);
   double	er          = pPR->ground_eps.r;
   double	Bhh			= (cos_thetai-sqrt(er-sin_thetai*sin_thetai))/(cos_thetai+sqrt(er-sin_thetai*sin_thetai));
   double	lamda_s_max	= 1.0/(k*sin_thetai);
   double	gamma       = 4.0*cos_thetai*cos_thetai*cos_thetai*cos_thetai*Bhh*Bhh;
   double	beta        = sin_thetai*sin_thetai;
   double	fs2			= k*k*sigma_s*sigma_s;
   double	flmax_2		= k*k*lamda_s_max*lamda_s_max;
   double	sigma0_max	= 10.0*log10(gamma*fs2*flmax_2*exp(-beta*flmax_2));
   double	delta;
   double	r;
   double	lamda_s;
   double	fl2;
   double	sigma0;
   double	Rt2dB, Rt2, sigma_l;
   double	deltaf;
   double	Sigma0HH;
   
   double	x, aRdB, bRdB;
   
   /******************************************************/
   /* Requested ground brightness is frequency dependent */
   /******************************************************/
   
   if (pPR->frequency > POLSARPROSIM_LBAND) {
      deltaf	= 1.0;
   } else {
      if (pPR->frequency < POLSARPROSIM_PBAND) {
         deltaf	= 0.0;
      } else {
         deltaf	= (pPR->frequency-POLSARPROSIM_PBAND)/(POLSARPROSIM_LBAND-POLSARPROSIM_PBAND);
      }
   }
   Sigma0HH	= deltaf*POLSARPROSIM_SIGMA0HHL45 + (1.0-deltaf)*POLSARPROSIM_SIGMA0HHP45;
   
   /****************************************************************/
   /* Small-scale parameters may be influenced by DEM model choice */
   /****************************************************************/
   
   Sigma0HH	+= ((DEM_model - 5)/5) * POLSARPROSIM_DELTAS0HHDB;
   
   /***************************************************/
   /* It may not be possible to realise the requested */
   /* brightness and still satisfy SPM validity.      */
   /***************************************************/
   
   if (Sigma0HH > sigma0_max) {
      delta		= 1.0;
      lamda_s	= lamda_s_max;
      fl2		= flmax_2;
   } else {
      delta		= sigma0_max - Sigma0HH;
      delta		= pow (10.0, -delta/10.0);
      r			= ratio_from_delta (delta);
      lamda_s	= r/(k*sin_thetai);
      fl2		= k*k*lamda_s*lamda_s;
   }
   sigma0		= 10.0*log10(gamma*fs2*fl2*exp(-beta*fl2));
   
   /*************************/
   /* Large scale roughness */
   /*************************/
   
   /*****************/
   /* New model ... */
   /*****************/
   /*
    Rt2dB		= minRdB - ((double) DEM_model) * (minRdB - maxRdB) / 10.0;
    Rt2		= pow (10.0, Rt2dB/10.0);
    sigma_l	= sqrt (-log(Rt2))/(2.0*k*cos(pPR->incidence_angle[0])) - sigma_s;
    */
   x			= ((double) DEM_model)/10.0;
   bRdB		= 2.0*(maxRdB - 2.0*midRdB + minRdB);
   aRdB		= maxRdB - minRdB - bRdB;
   Rt2dB		= minRdB + aRdB*x + bRdB*x*x;
   Rt2		= pow (10.0, Rt2dB/10.0);
   sigma_l	= sqrt (-log(Rt2))/(2.0*k*cos(pPR->incidence_angle[0])) - sigma_s;
   if (sigma_l < 0.0) {
      sigma_l	= 0.0;
   }
   
#ifdef FLAT_DEM
   pPR->large_scale_height_stdev		= 0.0;
#else
   pPR->large_scale_height_stdev		= sigma_l;
#endif
   pPR->large_scale_length          = 3.0*pPR->mean_crown_radius;
   pPR->small_scale_height_stdev		= sigma_s;
   pPR->small_scale_length          = lamda_s;
   fprintf (pPR->pLogFile, "Small-scale RMS height\t= %lf\n", pPR->small_scale_height_stdev);
   fprintf (pPR->pLogFile, "Small-scale cor length\t= %lf\n", pPR->small_scale_length);
   fprintf (pPR->pLogFile, "Large-scale RMS height\t= %lf\n", pPR->large_scale_height_stdev);
   fprintf (pPR->pLogFile, "Large-scale cor length\t= %lf\n", pPR->large_scale_length);
   return;
}

/****************************************************************************/
/* Pre-compute the Point Spread Functions and populate PSF lookup tables    */
/****************************************************************************/
void	Generate_PSF_Lookup_Tables	(PolSARproSim_Record *pPR)
{
   double         psfx, psfy, offset, psfsum;
   int            PSFx_length, PSFy_length, PSFt_length, ipix, i, j, k, t, ulim, llim;
   double         *PSFazvec, *PSFsrvec;
   double         thetamin, thetamax, grmax, grmin, tmin, tmax, p_height, inc_angle;
   
   /* compute the minimum and maximum incidence angles for all tracks */ 
   p_height       = pPR->slant_range[0]*cos(pPR->incidence_angle[0]);
   tmin           = pPR->incidence_angle[0];
   tmax           = pPR->incidence_angle[0];
   for(i=0;i<pPR->Tracks;i++){
      grmin       = pPR->slant_range[i]*sin(pPR->incidence_angle[i]) - pPR->Ly/2;
      grmax       = pPR->slant_range[i]*sin(pPR->incidence_angle[i]) + pPR->Ly/2;
      thetamin    = atan2(grmin, p_height);
      thetamax    = atan2(grmax, p_height);
      if(tmin > thetamin){
         tmin     = thetamin;
      }
      if(tmax < thetamax){
         tmax     = thetamax;
      }
   }
   PSFt_length    = (int)rint((tmax-tmin)*RAD_TO_DEG)+1; 
   pPR->min_inc_angle      = tmin;
   pPR->deltax_OS          = pPR->deltax/PSF_OVERSAMPLING_FACTOR;
   pPR->deltay_OS          = pPR->deltay/PSF_OVERSAMPLING_FACTOR;
   PSFx_length             = (int)(2*(pPR->PSFnx + PSF_SHOULDER)*PSF_OVERSAMPLING_FACTOR)+1;
   PSFy_length             = (int)(2*(pPR->PSFny + PSF_SHOULDER)*PSF_OVERSAMPLING_FACTOR)+1;
   /* allocate memory for PSF vectors and lookup tables */
   PSFazvec                = (double*) calloc (PSFx_length, sizeof (double));
   PSFsrvec                = (double*) calloc (PSFy_length, sizeof (double));
   pPR->PSFazmat           = (double*) calloc ((2*pPR->PSFnx + 1)*(PSF_OVERSAMPLING_FACTOR +1), sizeof (double));//
   pPR->PSFgrmat           = (double**) calloc ((2*pPR->PSFny + 1)*(PSF_OVERSAMPLING_FACTOR +1), sizeof (double));
   for(i =0;i<(2*pPR->PSFny + 1)*(PSF_OVERSAMPLING_FACTOR +1);i++){
      pPR->PSFgrmat[i]  = (double*) calloc (PSFt_length, sizeof (double));
   }
   
   /************************************************/
   /* Azimuth PSF calculation                      */
   /************************************************/
   /* populate the azimuth spread function vector */
   for (i = 0; i<PSFx_length; i++){
      psfx           = - (pPR->PSFnx + PSF_SHOULDER) * pPR->deltax + i*pPR->deltax_OS;
      if(fabs(1-(psfx/pPR->deltax)*(psfx/pPR->deltax)) < DBL_EPSILON){
         PSFazvec[i] = 0.0;
      }else{
         PSFazvec[i]    = Sinc(DPI_RAD * psfx/pPR->deltax) + 1/DPI_RAD*(1-pPR->PSFeta)/(1+pPR->PSFeta)*sin(DPI_RAD*psfx/pPR->deltax)*(psfx/pPR->deltax)/(1-(psfx/pPR->deltax)*(psfx/pPR->deltax));
      }
   }
   /* integrate the azimuth point spread function and store it in the Azimuth PSF lookup table */
   for (i = 0; i < (2*pPR->PSFnx + 1); i++) {
      ipix    = i - pPR->PSFnx;
      for (j = 0; j < (PSF_OVERSAMPLING_FACTOR + 1); j++) {
         offset   = j * pPR->deltax_OS - pPR->deltax/2;
         /* determine integration limits */
         llim     = (int)(PSFx_length/2) + (int)(offset/pPR->deltax_OS) - (int)(PSF_OVERSAMPLING_FACTOR/2) + (int)(ipix*PSF_OVERSAMPLING_FACTOR)-1;
         ulim     = (int)(PSFx_length/2) + (int)(offset/pPR->deltax_OS) + (int)(PSF_OVERSAMPLING_FACTOR/2) + (int)(ipix*PSF_OVERSAMPLING_FACTOR)-1;
         psfsum   = 0;
         /* integrate the Point Spread Function */
         for (k = llim; k <= ulim; k++) {
            psfsum  +=PSFazvec[k];
         }
         pPR->PSFazmat[i*(PSF_OVERSAMPLING_FACTOR + 1) + j] = psfsum;
      }
   }

   /************************************************/
   /* Ground range PSF calculation                 */
   /************************************************/
   /* compute a PSF lookup table for each incidence angle */
   for (t = 0; t< PSFt_length; t ++){
      inc_angle  = tmin + PSF_INCIDENCE_ANGLE_RESOLUTION * DEG_TO_RAD * t;
      /* populate the ground-range point spread function vector */
      for (i = 0; i<PSFy_length; i++){
         psfy           = - (pPR->PSFny + PSF_SHOULDER) * pPR->deltay + i*pPR->deltay_OS;
         psfy           = psfy / sin(inc_angle);
         if(fabs(1-(psfy/pPR->deltay)*(psfy/pPR->deltay)) < DBL_EPSILON){
            PSFsrvec[i] = 0.0;
         }else{
            PSFsrvec[i] = Sinc(DPI_RAD * psfy/pPR->deltay) + 1/DPI_RAD*(1-pPR->PSFeta)/(1+pPR->PSFeta)*sin(DPI_RAD*psfy/pPR->deltay)*(psfy/pPR->deltay)/(1-(psfy/pPR->deltay)*(psfy/pPR->deltay));
         }
      }
      /* integrate the slant range point spread function and store it in array */
      for (i = 0; i < (2*pPR->PSFny + 1); i++) {
         ipix    = i - pPR->PSFny;
         for (j = 0; j < (PSF_OVERSAMPLING_FACTOR + 1); j++) {
            offset    = j * pPR->deltay_OS - pPR->deltay/2;
            /* determine integration limits */
            llim      = (int)(PSFy_length/2) + (int)(offset/pPR->deltay_OS) - (int)(PSF_OVERSAMPLING_FACTOR/2) + (int)(ipix*PSF_OVERSAMPLING_FACTOR)-1;
            ulim      = (int)(PSFy_length/2) + (int)(offset/pPR->deltay_OS) + (int)(PSF_OVERSAMPLING_FACTOR/2) + (int)(ipix*PSF_OVERSAMPLING_FACTOR)-1;
            psfsum = 0;
            /* integrate the Point Spread Function */
            for (k = llim; k <= ulim; k++) {
               psfsum  +=PSFsrvec[k];
            }
            //pPR->PSFsrmat[i*(PSF_OVERSAMPLING_FACTOR + 1) + j] = psfsum;
            pPR->PSFgrmat[i*(PSF_OVERSAMPLING_FACTOR + 1) + j][t] = psfsum;
         }
      }
   }

}

/*************************************************/
/* Read the input file with the setup parameters */
/*************************************************/

int		Input_PolSARproSim_Record		(const char *filename, PolSARproSim_Record *pPR)
{
   const double	max_packing_fraction	= DPI_RAD/(2.0*sqrt(3.0));
   int            i;
   double			image_width, image_height;
   FILE           *pInputFile;
   
   /* required by module read_parfile */
   static char    buff[MAX_STR];   
   double         baseline[2];
   int            change_model_type;
   double         model_coeffs[3];
   double         master_track_height;
   double         master_track_ground_range;
   double         slave_height;
   double         slave_ground_range;
   /*********************/
   /* Ground properties */
   /*********************/
   
   const double	sand_fraction	= 0.0502;
   const double	clay_fraction	= 0.4738;
   const double	dry_density		= 2.56;
   const double	ground_pf		= 0.50;
   int            DEM_model;
#ifdef INPUT_GROUND_MV
   int            GMV_model;
#endif
   double			ground_mv		= DEFAULT_GROUND_MV;
   double			psf_azextent;
   double			psf_srextent;
   
   /**********************************/
   /* Attempt to open the input file */
   /**********************************/
   
   if ((pInputFile = fopen(filename, "r")) == NULL) {
      fprintf (pPR->pLogFile, "Unable to open input file %s.\n", filename);
      fprintf (pPR->pOutputFile, "Unable to open input file %s.\n", filename);
      fflush (pPR->pLogFile);
      fflush (pPR->pOutputFile);
      return (!NO_POLSARPROSIM_ERRORS);
   }
   
   /********************/
   /* Input parameters */
   /********************/
   
   fprintf (pPR->pLogFile, "\nInputs using keyword driven searches in parameter file ...\n\n");
   read_integer   (pInputFile,    "tracks",                   &(pPR->Tracks));
   /* Initialize Track dependent inputs */
   pPR->slant_range                 = (double *)calloc (pPR->Tracks, sizeof (double));
   pPR->incidence_angle             = (double *)calloc (pPR->Tracks, sizeof (double));
   /* read in the geometry */
   read_double   (pInputFile,    "center_slant_range_master",  &(pPR->slant_range[0]));
   read_double   (pInputFile,    "incidence_angle_master",     &(pPR->incidence_angle[0]));
   pPR->incidence_angle[0] *=DEG_TO_RAD; /* convert to radians */
   master_track_height        = pPR->slant_range[0]*cos(pPR->incidence_angle[0]);
   master_track_ground_range  = pPR->slant_range[0]*sin(pPR->incidence_angle[0]);
   for (i = 1; i < pPR->Tracks; i++) {
      sprintf(buff,                 "baseline_track_%d", i);
      read_dvector   (pInputFile,   buff,                      (double *)&baseline,2);
      slave_ground_range      = master_track_ground_range + baseline[0];
      slave_height            = master_track_height + baseline[1];
      pPR->slant_range[i]     = sqrt(slave_height*slave_height + slave_ground_range*slave_ground_range);
      pPR->incidence_angle[i] = atan2(slave_ground_range, slave_height);
      printf("%d)\tSlant Range %f\tIncidence Angle: %f, Bperp with 0: %f\n", i, pPR->slant_range[i], pPR->incidence_angle[i]*RAD_TO_DEG, sqrt(baseline[0]*baseline[0]+baseline[1]*baseline[1])*cos(pPR->incidence_angle[0]));
   }
   read_double    (pInputFile,   "radar_frequency",            &(pPR->frequency));
   read_double    (pInputFile,   "azimuth_resolution",         &(pPR->azimuth_resolution));
   read_double    (pInputFile,   "slant_range_resolution",     &(pPR->slant_range_resolution));
   read_integer   (pInputFile,   "DEM_model",                  &(DEM_model));
   read_double    (pInputFile,   "ground_slope_azimuth",       &(pPR->slope_x));   
   read_double    (pInputFile,   "ground_slope_range",         &(pPR->slope_y));
   read_integer   (pInputFile,   "randn_seed",                 &(pPR->seed));             
   read_integer   (pInputFile,   "global_tree_species",        &(pPR->species));              
   read_double    (pInputFile,   "global_tree_height",         &(pPR->mean_tree_height));
   read_double    (pInputFile,   "forest_stand_area",          &(pPR->Stand_Area)); 
   read_integer   (pInputFile,   "stem_density",               &(pPR->req_trees_per_hectare));   
   read_double    (pInputFile,   "PSF_broadening_factor",      &(pPR->PSFeta));
#ifdef INPUT_GROUND_MV
   read_integer   (pInputFile,    "ground_moisture",           &GMV_model);
#endif
   read_integer   (pInputFile,    "input_forest",              &(pPR->ForestInput_Flag)); /* whether to input forest primitives --RAedit */
   if(pPR->ForestInput_Flag!=EXTERNAL_FOREST_DEFINITION){pPR->ForestInput_Flag=0;}        /* set flag to 0 by default           --RAedit */
   read_integer   (pInputFile,    "draw_forest",              &(pPR->ForestDraw_Flag));   /* whether to draw forest             --RAedit */
   if(pPR->ForestDraw_Flag!=DRAW_FOREST_IMAGE){pPR->ForestDraw_Flag=0;}                   /* set flag to 0 by default           --RAedit */
   pPR->ForestData = (char *)calloc(MAX_STR, sizeof(char));                               /* Initialize the string containing the path & filename of forest input */
   read_string    (pInputFile,    "forest_file",               pPR->ForestData);          /* Read the filename from parameter file */
   pPR->SpeciesData = (char *)calloc(MAX_STR, sizeof(char));                              /* Initialize the string containing the path & filename of species database */
   read_string    (pInputFile,    "allometry_file",            pPR->SpeciesData);         /* Read the fileanme form parameter file */
   if(pPR->ForestInput_Flag != EXTERNAL_FOREST_DEFINITION){
      pPR->ForestOutput = (char *)calloc(MAX_STR, sizeof(char));                          /* Initialize the string containing the path & filename of forest output */
      read_string    (pInputFile, "forest_output",             pPR->ForestOutput);        /* Read the filename from parameter file */
      printf("READ FOREST OUTPUT STRING: --%s--\n", pPR->ForestOutput);  
   }
   /* Read in track dependent temporal change parameters for modeling temporal decorrelation */
   /* Allocate Memory and initialzie all to zero */
   pPR->Position_Change_Model       = (int *)calloc(pPR->Tracks, sizeof(int));   
   pPR->Moisture_Change_Model       = (int *)calloc(pPR->Tracks, sizeof(int)); 
   pPR->motion_coeff_A              = (double *)calloc(pPR->Tracks, sizeof(double));
   pPR->motion_coeff_B              = (double *)calloc(pPR->Tracks, sizeof(double));
   pPR->motion_coeff_C              = (double *)calloc(pPR->Tracks, sizeof(double));
   pPR->moisture_coeff_A            = (double *)calloc(pPR->Tracks, sizeof(double));
   pPR->moisture_coeff_B            = (double *)calloc(pPR->Tracks, sizeof(double));
   pPR->moisture_coeff_C            = (double *)calloc(pPR->Tracks, sizeof(double));
   for (i = 0; i < pPR->Tracks; i++) {
      pPR->Position_Change_Model[i]    = 0;
      pPR->Moisture_Change_Model[i]    = 0;
      pPR->motion_coeff_A[i]           = 0.0;
      pPR->motion_coeff_B[i]           = 0.0;
      pPR->motion_coeff_C[i]           = 0.0;
      pPR->moisture_coeff_A[i]         = 0.0;
      pPR->moisture_coeff_B[i]         = 0.0;
      pPR->moisture_coeff_C[i]         = 0.0;
   }
   /* read the input file */
   for (i = 1; i < pPR->Tracks; i++) {
      /* position change e.g. due to wind */
      sprintf(buff,                 "position_change_model_track_%d", i);
      if(read_integer   (pInputFile,   buff,     &change_model_type)!= -1){
         pPR->Position_Change_Model[i] = change_model_type;
         sprintf(buff,                 "position_change_coeff_track_%d", i);
         read_dvector   (pInputFile,   buff, (double *)&model_coeffs,3); 
         pPR->motion_coeff_A[i]        = model_coeffs[0];
         pPR->motion_coeff_B[i]        = model_coeffs[1];
         pPR->motion_coeff_C[i]        = model_coeffs[2];
      }else{
         printf("(Default) No position changes to track %d\n", i);
      }
      /* moisture change, e.g. due to rain */
      sprintf(buff,                 "moisture_change_model_track_%d", i);
      if(read_integer   (pInputFile,   buff,     &change_model_type)!= -1){
         pPR->Moisture_Change_Model[i] = change_model_type;
         sprintf(buff,                 "moisture_change_coeff_track_%d", i);
         read_dvector   (pInputFile,   buff, (double *)&model_coeffs,3); 
         pPR->moisture_coeff_A[i]      = model_coeffs[0];
         pPR->moisture_coeff_B[i]      = model_coeffs[1];
         pPR->moisture_coeff_C[i]      = model_coeffs[2];
      }else{
         printf("(Default) No moisture changes to track %d\n", i);
      }
   }
   for (i = 0; i < pPR->Tracks; i++) {
      printf ("%d\t\t\t/* Position Change Model Type for track %d\t*/\n", pPR->Position_Change_Model[i],i);
      printf ("%.3f,%.3f,%.3f\t/* Position Change Model Coefficients for track %d\t*/\n", pPR->motion_coeff_A[i], pPR->motion_coeff_B[i], pPR->motion_coeff_C[i], i);
      printf ("%d\t\t\t/* Moisture Change Model Type for track %d\t*/\n", pPR->Moisture_Change_Model[i],i);
      printf ("%.3f,%.3f,%.3f\t/* Moisture Change Model Coefficients for track %d\t*/\n", pPR->moisture_coeff_A[i], pPR->moisture_coeff_B[i], pPR->moisture_coeff_C[i], i);
   }

   
   /************************/
   /* Close the input file */
   /************************/
   
   fclose (pInputFile);
   
   /***************************/
   /* Report input parameters */
   /***************************/
   
   fprintf (pPR->pLogFile, "\nInput parameter report ...\n\n");
   fprintf (pPR->pLogFile, "%d\t\t\t/* The number of requested tracks \t*/\n", pPR->Tracks);
   for (i = 0; i < pPR->Tracks; i++) {
      fprintf (pPR->pLogFile, "%lf\t\t/* Slant range (broadside platform to scene centre) in metres \t*/\n", pPR->slant_range[i]);
      fprintf (pPR->pLogFile, "%lf\t\t/* Incidence angle in degrees \t*/\n", 45.0*pPR->incidence_angle[i]/atan(1.0));
   }
   fprintf (pPR->pLogFile, "%lf\t\t/* Centre frequency in GHz \t*/\n", pPR->frequency);
   fprintf (pPR->pLogFile, "%lf\t\t/* Azimuth resolution (width at half-height power) in metres \t*/\n", pPR->azimuth_resolution);
   fprintf (pPR->pLogFile, "%lf\t\t/* Slant range resolution (width at half-height power) in metres \t*/\n", pPR->slant_range_resolution);
   fprintf (pPR->pLogFile, "%d\t\t\t/* Ground model: 0 = smoothest … 10 = roughest \t*/\n",  DEM_model);
   fprintf (pPR->pLogFile, "%lf\t\t/* Ground slope in azimuth direction (dimensionless) \t*/\n", pPR->slope_x);
   fprintf (pPR->pLogFile, "%lf\t\t/* Ground slope in ground range direction (dimensionless) \t*/\n", pPR->slope_y);
   fprintf (pPR->pLogFile, "%d\t\t\t/* Random number generator seed \t*/\n",  pPR->seed);
   fprintf (pPR->pLogFile, "%d\t\t\t/* Tree species: 0 = HEDGE, 1,2,3 = PINE, 4 = DECIDUOUS \t*/\n",  pPR->species);
   fprintf (pPR->pLogFile, "%lf\t\t/* Mean tree height in metres \t*/\n", pPR->mean_tree_height);
   fprintf (pPR->pLogFile, "%lf\t\t/* Area of the forest stand in square metres \t*/\n", pPR->Stand_Area);
   fprintf (pPR->pLogFile, "%d\t\t\t/* Desired stand density in stems per hectare \t*/\n",  pPR->req_trees_per_hectare);
#ifdef INPUT_GROUND_MV
   fprintf (pPR->pLogFile, "%d\t\t\t/* Ground moisture content model: 0 = dry ... 10  = wet \t*/\n", GMV_model);
#endif
   fprintf (pPR->pLogFile, "%s\t\t\t/* Forest input File \t*/\n", pPR->ForestData);
   fprintf (pPR->pLogFile, "%s\t\t\t/* Species input File \t*/\n\n", pPR->SpeciesData);
   for (i = 0; i < pPR->Tracks; i++) {
      fprintf (pPR->pLogFile, "%d\t\t\t/* Position Change Model Type for track %d\t*/\n", pPR->Position_Change_Model[i],i);
      fprintf (pPR->pLogFile, "%.3f,%.3f,%.3f\t/* Position Change Model Coefficients for track %d\t*/\n", pPR->motion_coeff_A[i], pPR->motion_coeff_B[i], pPR->motion_coeff_C[i], i);
      fprintf (pPR->pLogFile, "%d\t\t\t/* Moisture Change Model Type for track %d\t*/\n", pPR->Moisture_Change_Model[i],i);
      fprintf (pPR->pLogFile, "%.3f,%.3f,%.3f\t/* Moisture Change Model Coefficients for track %d\t*/\n", pPR->moisture_coeff_A[i], pPR->moisture_coeff_B[i], pPR->moisture_coeff_C[i], i);
   }

   
   fflush (pPR->pLogFile);
   
   fprintf (pPR->pOutputFile, "\nInput parameter report ...\n\n");
   fprintf (pPR->pOutputFile, "%d\t\t\t/* The number of requested tracks \t*/\n", pPR->Tracks);
   for (i = 0; i < pPR->Tracks; i++) {
      fprintf (pPR->pOutputFile, "%lf\t\t/* Slant range (broadside platform to scene centre) in metres \t*/\n", pPR->slant_range[i]);
      fprintf (pPR->pOutputFile, "%lf\t\t/* Incidence angle in degrees \t*/\n", 45.0*pPR->incidence_angle[i]/atan(1.0));
   }
   fprintf (pPR->pOutputFile, "%lf\t\t/* Centre frequency in GHz \t*/\n", pPR->frequency);
   fprintf (pPR->pOutputFile, "%lf\t\t/* Azimuth resolution (width at half-height power) in metres \t*/\n", pPR->azimuth_resolution);
   fprintf (pPR->pOutputFile, "%lf\t\t/* Slant range resolution (width at half-height power) in metres \t*/\n", pPR->slant_range_resolution);
   fprintf (pPR->pOutputFile, "%d\t\t\t/* Ground model: 0 = smoothest, 10 = roughest \t*/\n",  DEM_model);
   fprintf (pPR->pOutputFile, "%lf\t\t/* Ground slope in azimuth direction (dimensionless) \t*/\n", pPR->slope_x);
   fprintf (pPR->pOutputFile, "%lf\t\t/* Ground slope in ground range direction (dimensionless) \t*/\n", pPR->slope_y);
   fprintf (pPR->pOutputFile, "%d\t\t\t/* Random number generator seed \t*/\n",  pPR->seed);
   fprintf (pPR->pOutputFile, "%d\t\t\t/* Tree species: 0 = HEDGE, 1,2,3 = PINE, 4 = DECIDUOUS \t*/\n",  pPR->species);
   fprintf (pPR->pOutputFile, "%lf\t\t/* Mean tree height in metres \t*/\n", pPR->mean_tree_height);
   fprintf (pPR->pOutputFile, "%lf\t\t/* Area of the forest stand in square metres \t*/\n", pPR->Stand_Area);
   fprintf (pPR->pOutputFile, "%d\t\t\t/* Desired stand density in stems per hectare \t*/\n",  pPR->req_trees_per_hectare);
#ifdef INPUT_GROUND_MV
   fprintf (pPR->pOutputFile, "%d\t\t\t/* Ground moisture content model: 0 = dry ... 10  = wet \t*/\n\n", GMV_model);
#endif
   fprintf (pPR->pOutputFile, "%s\t\t\t/* Forest input File \t*/\n", pPR->ForestData);
   fprintf (pPR->pOutputFile, "%s\t\t\t/* Species input File \t*/\n\n", pPR->SpeciesData);
   if(pPR->ForestInput_Flag != EXTERNAL_FOREST_DEFINITION){
      fprintf (pPR->pOutputFile, "%s\t\t\t/* Forest output File \t*/\n", pPR->ForestOutput);
   }
   for (i = 0; i < pPR->Tracks; i++) {
      fprintf (pPR->pOutputFile, "%d\t\t\t/* Position Change Model Type for track %d\t*/\n", pPR->Position_Change_Model[i],i);
      fprintf (pPR->pOutputFile, "%.3f,%.3f,%.3f\t/* Position Change Model Coefficients for track %d\t*/\n", pPR->motion_coeff_A[i], pPR->motion_coeff_B[i], pPR->motion_coeff_C[i], i);
      fprintf (pPR->pOutputFile, "%d\t\t\t/* Moisture Change Model Type for track %d\t*/\n", pPR->Moisture_Change_Model[i],i);
      fprintf (pPR->pOutputFile, "%.3f,%.3f,%.3f\t/* Moisture Change Model Coefficients for track %d\t*/\n", pPR->moisture_coeff_A[i], pPR->moisture_coeff_B[i], pPR->moisture_coeff_C[i], i);
   }

   fflush (pPR->pOutputFile);
   
   /**************************************/
   /* Initialise random number generator */
   /**************************************/
   
   srand (pPR->seed);
   
   /*************************************/
   /* Central wavelength and wavenumber */
   /*************************************/
   
   pPR->wavelength                  = LIGHT_SPEED/pPR->frequency;
   pPR->k0                          = 2.0*DPI_RAD/pPR->wavelength;
   
   /******************************************************/
   /* Resolution, sampling and impulse response function */
   /******************************************************/
   
   pPR->f_azimuth                   = DEFAULT_RESOLUTION_SAMPLING_FACTOR;
   pPR->deltax                      = pPR->azimuth_resolution*pPR->f_azimuth;
   pPR->ground_range_resolution		= (double*) calloc (pPR->Tracks, sizeof (double));
   for (pPR->current_track  = 0; pPR->current_track < pPR->Tracks; pPR->current_track++) {
      pPR->ground_range_resolution[pPR->current_track]	= pPR->slant_range_resolution/sin(pPR->incidence_angle[pPR->current_track]);
   }
   pPR->f_ground_range              = DEFAULT_RESOLUTION_SAMPLING_FACTOR;
   pPR->deltay                      = pPR->ground_range_resolution[0]*pPR->f_ground_range;
   
   /******************************************************/
   /* Read and report the species specific parameters    */
   /******************************************************/
   
   Input_PolSARproSim_Allometry(pPR);     /* Read in the species database first */
   Report_PolSARproSim_Allometry(pPR);    /* Report the Specie Database         */
   
   
   /******************************************************/
   /* If input_forest flag of Master Record is set       */
   /* read forest primitives from file and               */
   /* calculate image size parameters from them          */
   /******************************************************/
   
   if(pPR->ForestInput_Flag == EXTERNAL_FOREST_DEFINITION) {
      
      Input_PolSARproSim_Forest (pPR);       /* Read in the forest primitives next */  
      Check_PolSARproSim_Forest (pPR);       /* Check and report the forest parameters */
      
   } else {
      
      /* first check if the species specified in the parameter file is valid */
      if(pPR->species > pPR->Nspecies || pPR->species < 0){
         fprintf(stderr, "Global species identifier, %d, is not valid. Either species code in the SAR input file is wrong or that number of species aren't defined in the species database file\n", pPR->species);
         exit(0);
      }
      
      /******************************************************/
      /* User supplies area, for trees this is assumed much */
      /* greater than a crown area, but for the hedge ...   */
      /******************************************************/
      
      pPR->mean_crown_radius			= Mean_Tree_Crown_Radius (pPR->species, pPR->mean_tree_height, pPR);
      
      pPR->Layover_Distance	= pPR->mean_tree_height / tan(pPR->incidence_angle[0]);
      pPR->Shadow_Distance		= pPR->mean_tree_height * tan(pPR->incidence_angle[0]);
      pPR->Gap_Distance			= RESOLUTION_GAP_SIZE * (pPR->azimuth_resolution + pPR->ground_range_resolution[0])/2.0;
      pPR->Stand_Radius			= sqrt(pPR->Stand_Area/DPI_RAD);
      pPR->Lx                 = 2.0*(pPR->Stand_Radius+pPR->Gap_Distance+pPR->mean_crown_radius);
      pPR->Ly                 = pPR->Lx + pPR->Layover_Distance+pPR->Shadow_Distance;
      pPR->Area               = pPR->Lx*pPR->Ly;
      pPR->Hectares           = pPR->Area/10000.0;
      
      /************************/
      /* SAR image dimensions */
      /************************/
      
      pPR->nx                 = (int) (pPR->Lx / pPR->deltax) + 1;
      pPR->nx                 = 2*((int)(pPR->nx/2))+1;
      pPR->deltax             = pPR->Lx/pPR->nx;
      pPR->ny                 = (int) (pPR->Ly / pPR->deltay) + 1;
      pPR->ny                 = 2*((int)(pPR->ny/2))+1;
      pPR->deltay             = pPR->Ly/pPR->ny;
      
      /*********/
      /* Trees */
      /*********/
      
      pPR->max_tree_height             = pPR->mean_tree_height; /* This is added to make changes in Attenuation_Map backward compatible --RAedit */
      pPR->max_tree_number             = (int) (max_packing_fraction*pPR->Area/(POLSARPROSIM_CROWN_OVERLAP_FACTOR*POLSARPROSIM_CROWN_OVERLAP_FACTOR*DPI_RAD*pPR->mean_crown_radius*pPR->mean_crown_radius));
      
      printf("Mean crown radius: %f\n", pPR->mean_crown_radius);
      pPR->max_trees_per_hectare			= (int) ((double) pPR->max_tree_number/pPR->Hectares);
      if (pPR->req_trees_per_hectare > pPR->max_trees_per_hectare) {
         fprintf (pPR->pLogFile, "\nRequested stand density of %d Trees/Ha is too great.\n", pPR->req_trees_per_hectare);
         fprintf (pPR->pLogFile, "Resetting stand density to %d Trees/Ha.\n\n", pPR->max_trees_per_hectare);
         fflush  (pPR->pLogFile);
         fprintf (pPR->pOutputFile, "\nRequested stand density of %d Trees/Ha is too great.\n", pPR->req_trees_per_hectare);
         fprintf (pPR->pOutputFile, "Resetting stand density to %d Trees/Ha.\n\n", pPR->max_trees_per_hectare);
         fflush  (pPR->pOutputFile);
         pPR->req_trees_per_hectare		= pPR->max_trees_per_hectare;
      }
      pPR->trees_per_100m           = sqrt((double)pPR->req_trees_per_hectare);
      pPR->nTreex                   = (int) ((pPR->Lx*pPR->trees_per_100m/100.0)+1.0);
      pPR->nTreey                   = (int) ((pPR->Ly*pPR->trees_per_100m/100.0)+1.0);
      pPR->Trees                    = pPR->nTreex*pPR->nTreey;
      pPR->deltaTreex               = pPR->Lx/(double)pPR->nTreex;
      pPR->deltaTreey               = pPR->Ly/(double)pPR->nTreey;
      pPR->close_packing_radius     = sqrt (max_packing_fraction*pPR->Area/(DPI_RAD*pPR->Trees));
      
      /*************************************/
      /* Initialise tree heights and radii */
      /*************************************/
      
      pPR->Tree_Location               = (TreeLoc*) calloc (pPR->Trees, sizeof(TreeLoc));
      for (i=0; i<pPR->Trees; i++) {
         pPR->Tree_Location[i].height	= Realise_Tree_Height(pPR->mean_tree_height);
         pPR->Tree_Location[i].radius	= Realise_Tree_Crown_Radius (pPR->species, pPR->Tree_Location[i].height, pPR);
         pPR->Tree_Location[i].x       = 0.0;
         pPR->Tree_Location[i].y       = 0.0;
      }
   }
   
   /***************************/
   /* Graphic image variables */
   /***************************/
   
   image_height		= pPR->Ly*cos(pPR->incidence_angle[0]) + pPR->mean_tree_height*sin(pPR->incidence_angle[0]);
   image_width       = pPR->Lx;
   pPR->gny          = FOREST_GRAPHIC_NY;
   pPR->gnx          = (int) (((double)pPR->gny*image_width)/((double)image_height));
   
   /***********************************************************/
   /* Short vegetation layer variables not under user control */
   /***********************************************************/
   
   pPR->shrt_vegi_depth          = DEFAULT_SHORT_VEGI_DEPTH;
   pPR->shrt_vegi_stem_vol_frac	= DEFAULT_SHORT_VEGI_STEM_VOL_FRAC;
   pPR->shrt_vegi_leaf_vol_frac	= DEFAULT_SHORT_VEGI_LEAF_VOL_FRAC;
   
   /********************************/
   /* Ground electrical properties */
   /********************************/
   
#ifdef INPUT_GROUND_MV
   ground_mv			= MIN_GROUND_MV + ((double) GMV_model)*(MAX_GROUND_MV-MIN_GROUND_MV)/10.0;
#endif
   
   pPR->ground_eps   = ground_permittivity (dry_density, ground_pf, sand_fraction, 
                                            clay_fraction, ground_mv, pPR->frequency);
   
   /**************************************************/
   /* Large scale and small scale surface parameters */
   /**************************************************/
   
   Surface_Parameters (pPR, DEM_model);
   
   /**********************************************/
   /* Report derived simulation parameter vaules */
   /**********************************************/
   
   fprintf (pPR->pLogFile, "Derived parameter values ...\n\n");
   fprintf (pPR->pLogFile, "Wavelength\t\t\t\t=\t%lf metres\n", pPR->wavelength);
   fprintf (pPR->pLogFile, "Wavenumber\t\t\t\t=\t%lf inv. metres\n", pPR->k0);
   fprintf (pPR->pLogFile, "Azimuth resolution\t\t=\t%lf metres\n", pPR->azimuth_resolution);
   for (pPR->current_track = 0; pPR->current_track < pPR->Tracks; pPR->current_track++) {
      fprintf (pPR->pLogFile, "Ground range resolution[%d]\t=\t%lf metres\n", pPR->current_track, pPR->ground_range_resolution[pPR->current_track]);
   }
   fprintf (pPR->pLogFile, "Large-scale height stdev\t=\t%lf metres\n", pPR->large_scale_height_stdev);
   fprintf (pPR->pLogFile, "Large-scale length\t\t=\t%lf metres\n", pPR->large_scale_length);
   fprintf (pPR->pLogFile, "Small-scale height stdev\t=\t%lf metres\n", pPR->small_scale_height_stdev);
   fprintf (pPR->pLogFile, "Small-scale length\t\t=\t%lf metres\n", pPR->small_scale_length);
   fprintf (pPR->pLogFile, "Layover distance\t\t\t=\t%lf metres\n", pPR->Layover_Distance);
   fprintf (pPR->pLogFile, "Shadow distance\t\t\t=\t%lf metres\n", pPR->Shadow_Distance);
   fprintf (pPR->pLogFile, "Gap distance\t\t\t=\t%lf metres\n", pPR->Gap_Distance);
   fprintf (pPR->pLogFile, "Stand radius\t\t\t=\t%lf metres\n", pPR->Stand_Radius);
   fprintf (pPR->pLogFile, "Lx\t\t\t\t\t=\t%lf metres\n", pPR->Lx);
   fprintf (pPR->pLogFile, "Ly\t\t\t\t\t=\t%lf metres\n", pPR->Ly);
   fprintf (pPR->pLogFile, "Area\t\t\t\t\t=\t%lf square metres\n", pPR->Area);
   fprintf (pPR->pLogFile, "Hectares\t\t\t\t=\t%lf Ha\n", pPR->Hectares);
   fprintf (pPR->pLogFile, "There are %d pixels in azimuth of width %lf metres\n", pPR->nx, pPR->deltax);
   fprintf (pPR->pLogFile, "There are %d pixels in ground range of width %lf metres\n", pPR->ny, pPR->deltay);
   fprintf (pPR->pLogFile, "\n*******************************************************************\n\n");
   fflush  (pPR->pLogFile);
   
   fprintf (pPR->pOutputFile, "Derived parameter values ...\n\n");
   fprintf (pPR->pOutputFile, "Wavelength\t\t\t\t=\t%lf metres\n", pPR->wavelength);
   fprintf (pPR->pOutputFile, "Wavenumber\t\t\t\t=\t%lf inv. metres\n", pPR->k0);
   fprintf (pPR->pOutputFile, "Azimuth resolution\t\t=\t%lf metres\n", pPR->azimuth_resolution);
   for (pPR->current_track = 0; pPR->current_track < pPR->Tracks; pPR->current_track++) {
      fprintf (pPR->pOutputFile, "Ground range resolution[%d]\t=\t%lf metres\n", pPR->current_track, pPR->ground_range_resolution[pPR->current_track]);
   }
   fprintf (pPR->pOutputFile, "Large-scale height stdev\t=\t%lf metres\n", pPR->large_scale_height_stdev);
   fprintf (pPR->pOutputFile, "Large-scale length\t\t=\t%lf metres\n", pPR->large_scale_length);
   fprintf (pPR->pOutputFile, "Small-scale height stdev\t=\t%lf metres\n", pPR->small_scale_height_stdev);
   fprintf (pPR->pOutputFile, "Small-scale length\t\t=\t%lf metres\n", pPR->small_scale_length);
   fprintf (pPR->pOutputFile, "Layover distance\t\t\t=\t%lf metres\n", pPR->Layover_Distance);
   fprintf (pPR->pOutputFile, "Shadow distance\t\t\t=\t%lf metres\n", pPR->Shadow_Distance);
   fprintf (pPR->pOutputFile, "Gap distance\t\t\t=\t%lf metres\n", pPR->Gap_Distance);
   fprintf (pPR->pOutputFile, "Stand radius\t\t\t=\t%lf metres\n", pPR->Stand_Radius);
   fprintf (pPR->pOutputFile, "Lx\t\t\t\t\t=\t%lf metres\n", pPR->Lx);
   fprintf (pPR->pOutputFile, "Ly\t\t\t\t\t=\t%lf metres\n", pPR->Ly);
   fprintf (pPR->pOutputFile, "Area\t\t\t\t\t=\t%lf square metres\n", pPR->Area);
   fprintf (pPR->pOutputFile, "Hectares\t\t\t\t=\t%lf Ha\n", pPR->Hectares);
   fprintf (pPR->pOutputFile, "There are %d pixels in azimuth of width %lf metres\n", pPR->nx, pPR->deltax);
   fprintf (pPR->pOutputFile, "There are %d pixels in ground range of width %lf metres\n", pPR->ny, pPR->deltay);
   fprintf (pPR->pOutputFile, "\n*******************************************************************\n\n");
   fflush  (pPR->pOutputFile);
   
//   /************************************/
//   /* Initialise SAR imagery variables */
//   /************************************/
//   
//   Create_SIM_Record (&(pPR->HHimage));
//   Create_SIM_Record (&(pPR->HVimage));
//   Create_SIM_Record (&(pPR->VVimage));
//   
//   Initialise_SIM_Record	(&(pPR->HHimage), "", pPR->nx, pPR->ny, SIM_COMPLEX_FLOAT_TYPE, pPR->Lx, pPR->Ly, 
//                            "PolSARproSim HH image file");
//   Initialise_SIM_Record	(&(pPR->HVimage), "", pPR->nx, pPR->ny, SIM_COMPLEX_FLOAT_TYPE, pPR->Lx, pPR->Ly, 
//                            "PolSARproSim HV image file");
//   Initialise_SIM_Record	(&(pPR->VVimage), "", pPR->nx, pPR->ny, SIM_COMPLEX_FLOAT_TYPE, pPR->Lx, pPR->Ly, 
//                            "PolSARproSim VV image file");
   
   /******************************************************/
   /* Store xmid and ymid in the master record structure */
   /******************************************************/
   
   pPR->xmid		= (pPR->nx/2)*pPR->deltax;
   pPR->ymid		= (pPR->ny/2)*pPR->deltay;

#ifdef POLSARPROSIM_PSF_GAUSSIAN
   pPR->psfaaz    = 4.0*log(sqrt(2.0))/(pPR->azimuth_resolution*pPR->azimuth_resolution);
   pPR->psfagr    = (double*) calloc (pPR->Tracks, sizeof (double));
   for (pPR->current_track = 0; pPR->current_track < pPR->Tracks; pPR->current_track++) {
      pPR->psfagr[pPR->current_track]	= 4.0*log(sqrt(2.0))/(pPR->ground_range_resolution[pPR->current_track]*pPR->ground_range_resolution[pPR->current_track]);
   }
   pPR->psfasr    = 4.0*log(sqrt(2.0))/(pPR->slant_range_resolution*pPR->slant_range_resolution);
   psf_azextent	= sqrt(-log(sqrt(POWER_AT_PSF_EDGE))/pPR->psfaaz);
   psf_srextent	= sqrt(-log(sqrt(POWER_AT_PSF_EDGE))/pPR->psfasr);

   pPR->PSFnx		= (int) (psf_azextent/pPR->deltax) + 1;
   pPR->PSFnx		= 2*(pPR->PSFnx/2)+1;
   pPR->PSFny		= (int) (psf_srextent/(pPR->deltay*sin(pPR->incidence_angle[0]))) + 1;
   pPR->PSFny		= 2*(pPR->PSFny/2)+1;


#else
   pPR->psfaaz    = 4.0*log(sqrt(2.0))/(pPR->azimuth_resolution*pPR->azimuth_resolution);
   pPR->psfagr    = (double*) calloc (pPR->Tracks, sizeof (double));
   for (pPR->current_track = 0; pPR->current_track < pPR->Tracks; pPR->current_track++) {
      pPR->psfagr[pPR->current_track]	= 4.0*log(sqrt(2.0))/(pPR->ground_range_resolution[pPR->current_track]*pPR->ground_range_resolution[pPR->current_track]);
   }
   pPR->psfasr    = 4.0*log(sqrt(2.0))/(pPR->slant_range_resolution*pPR->slant_range_resolution);
   psf_azextent	= sqrt(-log(sqrt(POWER_AT_PSF_EDGE))/pPR->psfaaz);
   psf_srextent	= sqrt(-log(sqrt(POWER_AT_PSF_EDGE))/pPR->psfasr);

//   psf_azextent   = 3 * pPR->deltax;
//   psf_srextent   = 3 * pPR->deltay * sin(pPR->incidence_angle[0]);

   pPR->PSFnx		= (int) (psf_azextent/pPR->deltax) + 1;
   pPR->PSFnx		= 2*(pPR->PSFnx/2)+1;
   pPR->PSFny		= (int) (psf_srextent/(pPR->deltay*sin(pPR->incidence_angle[0]))) + 1;
   pPR->PSFny		= 2*(pPR->PSFny/2)+1;

   /* generate point spread function lookup tables */
   Generate_PSF_Lookup_Tables	(pPR);
#endif

   

   
   /*********************************************/
   /* Report SAR imaging parameters to log file */
   /*********************************************/
   
   fprintf (pPR->pLogFile, "\nxmid is %lf metres\n", pPR->xmid);
   fprintf (pPR->pLogFile, "ymid is %lf metres\n", pPR->ymid);
   fprintf (pPR->pLogFile, "PSF azimuth factor is %lf metres^-2\n", pPR->psfaaz);
   for (pPR->current_track = 0; pPR->current_track < pPR->Tracks; pPR->current_track++) {
      fprintf (pPR->pLogFile, "PSF ground range factor for track %d is %lf metres^-2\n", pPR->current_track, pPR->psfagr[pPR->current_track]);
   }
   fprintf (pPR->pLogFile, "PSF slant range factor is %lf metres^-2\n", pPR->psfasr);
   fprintf (pPR->pLogFile, "PSF azimuth     extent is %lf metres\n", psf_azextent);
   fprintf (pPR->pLogFile, "PSF slant range extent is %lf metres\n", psf_srextent);
   fprintf (pPR->pLogFile, "PSF azimuth     extent is %d pixels\n", pPR->PSFnx);
   fprintf (pPR->pLogFile, "PSF slant range extent is %d pixels\n", pPR->PSFny);
   fflush  (pPR->pLogFile);

   /***********************************/
   /* Initialise PSF scaling to unity */
   /***********************************/
   
   pPR->PSFamp	= 1.0;
   fprintf (pPR->pLogFile, "Initial PSF scaling is %lf\n", pPR->PSFamp);
   fflush  (pPR->pLogFile);
   
   /***********************************************/
   /* Initialize Temporal decorrelation Variables */
   /***********************************************/
   pPR->change_height_delta         = CHANGE_HEIGHT_DELTA;
   pPR->change_profile_bin_res      = pPR->max_tree_height/CHANGE_PROFILE_BINS;
#ifdef OUTPUT_CHANGE_STATS_ON
   pPR->motion_profile_mean         = (double *)calloc(CHANGE_PROFILE_BINS*pPR->Tracks, sizeof(double));
   pPR->motion_profile_var          = (double *)calloc(CHANGE_PROFILE_BINS*pPR->Tracks, sizeof(double));
   pPR->motion_profile_count        = (int    *)calloc(CHANGE_PROFILE_BINS*pPR->Tracks, sizeof(int));
   pPR->moisture_profile_mean       = (double *)calloc(CHANGE_PROFILE_BINS*pPR->Tracks, sizeof(double));
   pPR->moisture_profile_var        = (double *)calloc(CHANGE_PROFILE_BINS*pPR->Tracks, sizeof(double));
   pPR->moisture_profile_count      = (int    *)calloc(CHANGE_PROFILE_BINS*pPR->Tracks, sizeof(int));

   for(i=0; i<CHANGE_PROFILE_BINS*pPR->Tracks; i++){
      pPR->motion_profile_count[i]     = 0;
      pPR->motion_profile_mean[i]      = 0.0;
      pPR->motion_profile_var[i]       = 0.0;
      pPR->moisture_profile_count[i]   = 0;
      pPR->moisture_profile_mean[i]    = 0.0;
      pPR->moisture_profile_var[i]     = 0.0;
   }
#endif
   /*********************************/
   /* Initialise progress indicator */
   /*********************************/
   
   pPR->progress	= 0;
   
   /**************************/
   /* Return to main program */
   /**************************/
   
   return (NO_POLSARPROSIM_ERRORS);
}

/***********************************************/
/* Generating the underlying ground height map */
/***********************************************/

void	Ground_Surface_Generation	(PolSARproSim_Record *pPR)
{
   double			Lx			= pPR->Lx;
   double			Ly			= pPR->Ly;
   int            nx			= pPR->nx;
   int            ny			= pPR->ny;
   double			sx			= pPR->slope_x;
   double			sy			= pPR->slope_y;
   double			length	= pPR->large_scale_length;
   double			height_std	= pPR->large_scale_height_stdev;
   SIM_Record		*pSR		= &(pPR->Ground_Height);
   SIM_Record     *pSRHgt  = &(pPR->Max_Height);
   int            N			= POLSARPROSIM_GROUND_FOURIER_MOMENTS;
   const double	PI			= DPI_RAD;
   double			alphax	= sqrt(1.0+sx*sx);
   double			alphay	= sqrt(1.0+sy*sy);
   double			alpha		= sqrt(1.0+sx*sx+sy*sy);
   double			deltax	= Lx/(double)nx;
   double			deltay	= Ly/(double)ny;
   double			Lxp		= alphax*Lx;
   double			Lyp		= alphay*Ly;
   double			deltaxp	= alphax*deltax;
   double			deltayp	= alphay*deltay;
   int            i,j;
   sim_pixel		p;
   double			xi, yj;
   double			mean_height;
   double			stdd_height;
   char           *ground_height_filename;
#ifndef	FLAT_DEM
   int            m,n;
   double			xip, yjp;
   double			arg;
   double			km, kn;
   double			height_factor;
   double			*C;
   Complex        *H;
   Complex        carg;
   Complex        hxy;
   Complex        *f;
   Complex        *F;
#endif
   
   /******************************************/
   /* Report call if running in VERBOSE mode */
   /******************************************/
   
#ifdef VERBOSE_POLSARPROSIM
   printf ("\n");
   printf ("Call to Ground_Surface_Generation ... \n");
   printf ("\n");
#endif
   fprintf (pPR->pLogFile, "Call to Ground_Surface_Generation ... \n");
   fflush  (pPR->pLogFile);
   
   /********************************/
   /* Seed random number generator */
   /********************************/
   
   srand (pPR->seed);
   
   /*****************************************/
   /* Initialise ground height map variable */
   /*****************************************/
   
   ground_height_filename	= (char*) calloc (strlen(pPR->pMasterDirectory)+strlen("ground_height.bin")+1, sizeof(char));
   strcpy  (ground_height_filename, pPR->pMasterDirectory);
   strcat  (ground_height_filename, "ground_height.bin");
   
   Destroy_SIM_Record (pSR);
   Create_SIM_Record (pSR);
   Initialise_SIM_Record (pSR, ground_height_filename, nx, ny, SIM_FLOAT_TYPE, 
                          Lx, Ly, "PolSARproSim ground height map");
   p.simpixeltype	= pSR->pixel_type;
   free (ground_height_filename);
   
   ground_height_filename	= (char*) calloc (strlen(pPR->pMasterDirectory)+strlen("max_height.bin")+1, sizeof(char));
   strcpy  (ground_height_filename, pPR->pMasterDirectory);
   strcat  (ground_height_filename, "max_height.bin");
   
   Destroy_SIM_Record (pSRHgt);
   Create_SIM_Record (pSRHgt);
   Initialise_SIM_Record (pSRHgt, ground_height_filename, nx, ny, SIM_FLOAT_TYPE, 
                          Lx, Ly, "PolSARproSim maximum height map");
   p.simpixeltype	= pSRHgt->pixel_type;
   free (ground_height_filename);
   
   
#ifndef FLAT_DEM
   
   /**********************************/
   /* Stage 1: generate random field */
   /**********************************/
   
   f	= (Complex*) calloc (nx*ny, sizeof(Complex));
   for (m=0;m<nx;m++) {
      for (n=0;n<ny;n++) {
         f[n*nx+m]	= rp_complex(drand(), 2.0*PI*drand());
      }
   }
   
   /**********************************************/
   /* Stage 2: Calculate moments of random field */
   /**********************************************/
   
   F	= (Complex*) calloc ((2*N+1)*(2*N+1), sizeof(Complex));
   for (m=0;m<=2*N;m++) {
      for (n=0;n<=2*N;n++) {
         F[n*(2*N+1)+m]	= xy_complex (0.0, 0.0);
         for (i=0; i<nx; i++) {
            xi	= i*deltaxp - (Lxp - deltaxp)/2.0;
            xip	= 2.0*PI*xi/Lxp;
            for (j=0; j<ny; j++) {
               yj		= j*deltayp - (Lyp - deltayp)/2.0;
               yj		= -yj;
               yjp	= 2.0*PI*yj/Lyp;
               arg	= -((m*xip)+(n*yjp));
               carg	= rp_complex (1.0, arg);
               F[n*(2*N+1)+m]	= complex_add (F[n*(2*N+1)+m], complex_mul (carg, f[j*nx+i]));
            }
         }
      }
   }
   
   /**********************************************/
   /* Stage 3: Calculate the correlation moments */
   /**********************************************/
   
   C	= (double*) calloc ((2*N+1)*(2*N+1), sizeof(double));
   for (m=0;m<=2*N;m++) {
      km	 = (double) m - (double) N;
      km	*= 2.0*PI/Lxp;
      for (n=0;n<=2*N;n++) {
         kn	 = (double) n - (double)N;
         kn	*= 2.0*PI/Lyp;
         C[n*(2*N+1)+m]	= 0.5*length*length*exp(-km*km*length*length/8.0)*exp(-kn*kn*length*length/8.0);
      }
   }
   
   /*******************************************/
   /* Stage 4: Multiply in the Fourier domain */
   /*******************************************/
   
   H	= (Complex*) calloc ((2*N+1)*(2*N+1), sizeof(Complex));
   for (m=0;m<=2*N;m++) {
      for (n=0;n<=2*N;n++) {
         H[n*(2*N+1)+m]	= complex_rmul (F[n*(2*N+1)+m], C[n*(2*N+1)+m]);
      }
   }
   
   /************************************************/
   /* Stage 5: Form the surface in the real domain */
   /************************************************/
   
   for (i=0; i<nx; i++) {
      xi	= i*deltaxp - (Lxp - deltaxp)/2.0;
      for (j=0; j<ny; j++) {
         yj	= j*deltayp - (Lyp - deltayp)/2.0;
         yj	= -yj;
         hxy	= xy_complex (0.0, 0.0);
         for (m=0;m<=2*N;m++) {
            km	 = (double) m - (double) N;
            km	*= 2.0*PI/Lxp;
            for (n=0;n<=2*N;n++) {
               kn		= (double) n - (double)N;
               kn		*= 2.0*PI/Lyp;
               arg	= km*xi+kn*yj;
               carg	= rp_complex (1.0, arg);
               hxy	= complex_add (hxy, complex_mul (H[n*(2*N+1)+m], carg));
            }
         }
         p.data.f	= (float) complex_real (hxy);
         putSIMpixel_periodic (pSR, p, i, j);
         putSIMpixel_periodic (pSRHgt, p, i, j);
      }
   }
   
   /**********************************************************/
   /* Stage 6: Zero mean height and scale standard deviation */
   /**********************************************************/
   
   mean_height	= 0.0;
   stdd_height		= 0.0;
   for (i=0; i<nx; i++) {
      for (j=0; j<ny; j++) {
         p	= getSIMpixel_periodic (pSR, i, j);
         mean_height	+= (double) p.data.f;
      }
   }
   mean_height	/=	(double) (nx*ny);
   for (i=0; i<nx; i++) {
      for (j=0; j<ny; j++) {
         p			 = getSIMpixel_periodic (pSR, i, j);
         p.data.f		-= (float) mean_height;
         putSIMpixel_periodic (pSR, p, i, j);
         stdd_height	+= (double) p.data.f * p.data.f;
      }
   }
   stdd_height	/=	(double) (nx*ny);
   stdd_height	 = sqrt(stdd_height);
   height_factor	 = height_std/stdd_height;
   for (i=0; i<nx; i++) {
      for (j=0; j<ny; j++) {
         p			 = getSIMpixel_periodic (pSR, i, j);
         p.data.f		*= (float) height_factor;
         putSIMpixel_periodic (pSR, p, i, j);
         putSIMpixel_periodic (pSRHgt, p, i, j);
      }
   }
   
   /*************************************************/
   /* Stage 7: Project into SAR image plane heights */
   /*************************************************/
   
   for (i=0; i<nx; i++) {
      xi	= i*deltax - (Lx - deltax)/2.0;
      for (j=0; j<ny; j++) {
         yj	= j*deltay - (Ly - deltay)/2.0;
         yj	= -yj;
         p	= getSIMpixel_periodic (pSR, i, j);
         p.data.f	= (float) (sx*xi+sy*yj+p.data.f*alpha);
         putSIMpixel_periodic (pSR, p, i, j);
         putSIMpixel_periodic (pSRHgt, p, i, j);
      }
   }
   
#else
   
   for (i=0; i<nx; i++) {
      xi	= i*deltax - (Lx - deltax)/2.0;
      for (j=0; j<ny; j++) {
         yj	= j*deltay - (Ly - deltay)/2.0;
         yj	= -yj;
         p.data.f	= (float) (sx*xi+sy*yj);
         putSIMpixel (pSR, p, i, j);
         putSIMpixel (pSRHgt, p, i, j);
      }
   }
   
#endif
   
   /***********************************************************/
   /* Stage 8: Report the properties of the generated surface */
   /***********************************************************/
   
   mean_height	= 0.0;
   stdd_height	= 0.0;
   for (i=0; i<nx; i++) {
      xi	= i*deltax - (Lx - deltax)/2.0;
      for (j=0; j<ny; j++) {
         yj	= j*deltay - (Ly - deltay)/2.0;
         yj	= -yj;
         p	= getSIMpixel_periodic (pSR, i, j);
         mean_height	+= ((double) p.data.f) - (sx*xi+sy*yj);
      }
   }
   mean_height	/= (double) (nx*ny);
   for (i=0; i<nx; i++) {
      xi	= i*deltax - (Lx - deltax)/2.0;
      for (j=0; j<ny; j++) {
         yj	= j*deltay - (Ly - deltay)/2.0;
         yj	= -yj;
         p	= getSIMpixel_periodic (pSR, i, j);
         stdd_height	+= (((double) p.data.f) - (sx*xi+sy*yj))*(((double) p.data.f) - (sx*xi+sy*yj));
      }
   }
   stdd_height	/= (double) (nx*ny);
   stdd_height	 = sqrt(stdd_height);
   
   fprintf (pPR->pLogFile, "\n");
   fprintf (pPR->pLogFile, "Ground surface mean height above terrain slope\t= %12.5em.\n", mean_height);
   fprintf (pPR->pLogFile, "Ground surface stdd height above terrain slope\t= %12.5em.\n", stdd_height);
   fprintf (pPR->pLogFile, "\n");
   fflush  (pPR->pLogFile);
   
   /***********/
   /* Tidy up */
   /***********/
   
#ifndef FLAT_DEM
   free (f);
   free (F);
   free (C);
   free (H);
#endif
   
   /******************************************/
   /* Report call if running in VERBOSE mode */
   /******************************************/
   
#ifdef VERBOSE_POLSARPROSIM
   printf ("\n");
   printf ("... Returning from call to Ground_Surface_Generation\n");
   printf ("\n");
#endif
   fprintf (pPR->pLogFile, "... Returning from call to Ground_Surface_Generation\n\n");
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
   
   return;
}

/**************************/
/* Line input termination */
/**************************/

void	EndOfLine		(FILE *fp)
{
   char ch;
   do {
      ch = (char) fgetc(fp);
   } while ((ch != '\n') && (ch != EOF));
   return;
}

/**************************************************/
/* Calculate various attenuation contributions    */
/* and generate spatial attenuation look-up table */
/**************************************************/

int			Cylinder_from_Branch		(Cylinder *pC, Branch *pB, int i_seg, int n_segments)
{
   double		length, radius, tm, tp, deltat;
   d3Vector	z, bm, bp;
   
   deltat	= 1.0/(double) n_segments;
   tm			= i_seg*deltat;
   tp			= (i_seg+1)*deltat;
   bm			= Branch_Centre (pB, tm);
   bp			= Branch_Centre (pB, tp);
   radius	= Branch_Radius (pB, 0.5*(tm+tp));
   z			= d3Vector_difference (bp, bm);
   length	= z.r;
   d3Vector_insitu_normalise (&z);
   Assign_Cylinder (pC, length, radius, pB->permittivity, z, bm);
   return (NO_POLSARPROSIM_ERRORS);
}

c33Matrix	CylinderPolarisability	(Cylinder *pC, d3Vector *pkix, d3Vector *pkiy, d3Vector *pkiz, Yn_Lookup *pYtable, Jn_Lookup *pJtable)
{
   c33Matrix		Alpha;
   const double	sfac	= 1.0/2.0;
   
#ifdef FORCE_GRG_CYLINDERS
   Alpha		= GrgCylP (pC, pkix);
   Alpha		= c33Matrix_sum (Alpha, GrgCylP (pC, pkiy));
   Alpha		= c33Matrix_sum (Alpha, GrgCylP (pC, pkiz));
   Alpha		= c33Matrix_Complex_product (Alpha, xy_complex (sfac, 0.0));
#else
   Alpha		= InfCylP (pC, pkix, pYtable, pJtable);
   Alpha		= c33Matrix_sum (Alpha, InfCylP (pC, pkiy, pYtable, pJtable));
   Alpha		= c33Matrix_sum (Alpha, InfCylP (pC, pkiz, pYtable, pJtable));
   Alpha		= c33Matrix_Complex_product (Alpha, xy_complex (sfac, 0.0));
#endif
   return (Alpha);
}

//void		Effective_Permittivities_Orig	(PolSARproSim_Record *pPR)
//{
//   const double	bsecl	=	POLSARPROSIM_SAR_BRANCH_FACTOR*(pPR->azimuth_resolution + pPR->slant_range_resolution);
//   double			dsecl;
//   Leaf           leaf1;
//   double			costheta, theta, phi;
//   double			d_costheta, d_phi;
//   int            i_costheta, i_phi;
//   int            Ntheta, Nphi;
//   d3Vector       leaf_centre	= Zero_d3Vector ();
//   d3Vector       stem_centre	= Zero_d3Vector ();
//   double			leaf_d1, leaf_d2, leaf_d3;
//   int            leaf_species;
//   double			leaf_moisture;
//   Complex        leaf_permittivity, leaf_epsm1;
//   double			stem_d1, stem_d2, stem_d3;
//   int            stem_species;
//   double			stem_moisture;
//   Complex        stem_permittivity, stem_epsm1;
//   c33Matrix		Alpha             = Zero_c33Matrix ();
//   c33Matrix		Alpha_Stem_Sum		= Zero_c33Matrix ();
//   c33Matrix		Alpha_Leaf_Sum		= Zero_c33Matrix ();
//   Complex        scale_factor;
//   c33Matrix		ShortVegi_EpsEff	= Idem_c33Matrix ();
//   double			stemL1, stemL2, stemL3;
//   double			leafL1, leafL2, leafL3;
//   c33Matrix		CrownTert_EpsEff	= Idem_c33Matrix ();
//   Tree           tree1;
//   int            itree;
//   int            Ntrees;
//   double			primary_branch_length;
//   double			primary_branch_radius;
//   double			primary_branch_count;
//   double			secondary_branch_length;
//   double			secondary_branch_radius;
//   double			secondary_branch_count;
//   double			tertiary_branch_length;
//   double			tertiary_branch_radius;
//   Branch			*pB;
//   long           iBranch;
//   double			tertiary_branch_vol_frac;
//   double			tertiary_leaf_vol_frac;
//   c33Matrix		Alpha_Trunk_Sum				= Zero_c33Matrix ();
//   c33Matrix		Alpha_Primary_Sum          = Zero_c33Matrix ();
//   c33Matrix		Alpha_Secondary_Sum			= Zero_c33Matrix ();
//   c33Matrix		Alpha_Dry_Sum              = Zero_c33Matrix ();
//   c33Matrix		CrownTrunk_EpsEff          = Idem_c33Matrix ();
//   c33Matrix		CrownPrimary_EpsEff			= Idem_c33Matrix ();
//   c33Matrix		CrownSecondary_EpsEff		= Idem_c33Matrix ();
//   c33Matrix		CrownDry_EpsEff				= Idem_c33Matrix ();
//   c33Matrix		CrownLiving_EpsEff			= Idem_c33Matrix ();
//   double			crown_trunk_vol_frac       = 0.0;
//   double			crown_primary_vol_frac		= 0.0;
//   double			crown_secondary_vol_frac	= 0.0;
//   double			crown_dry_vol_frac			= 0.0;
//   double			crown_volume, dry_crown_volume;
//   double			trunk_length, trunk_count, trunk_volume, trunk_number_density;
//   double			primary_length, primary_count, primary_volume, primary_number_density;
//   double			secondary_length, secondary_count, secondary_volume, secondary_number_density;
//   double			dry_length, dry_count, dry_volume, dry_number_density;
//   int            n_segments, i_seg;
//   int            rtn_value;
//   Cylinder       Cyl1;
//   d3Vector       ki, kix, ksx, kiy, ksy, kiz, ksz;
//   double			thetai, phii, thetas, phis;
//   Yn_Lookup		Ytable;
//   Jn_Lookup		Jtable;
//   Complex        e, ez;
//   double         kro2;
//   Complex        ko2, koz2, koz;
//   Complex        ke2, kez2, kez;
//   double			rfac, aoverlamda;
//   d3Vector       t_axis, t_base;
//   double			tertiary_branch_volume;
//   Complex        tbvinv;
//   
//   Tree           *pT;
//   
//   /******************************************/
//   /* Report call if running in VERBOSE mode */
//   /******************************************/
//#ifdef VERBOSE_POLSARPROSIM
//   printf ("\n");
//   printf ("Call to Effective_Permittivities ... \n");
//   printf ("\n");
//#endif
//   fprintf (pPR->pLogFile, "Call to Effective_Permittivities ... \n");
//   fflush  (pPR->pLogFile);
//   /**************/
//   /* Initialise */
//   /**************/
//   Create_Leaf		(&leaf1);
//   Create_Tree		(&tree1);
//   Create_Cylinder	(&Cyl1);
//   /*********************************************/
//   /* Initialise Bessel function look-up tables */
//   /*********************************************/
//   rtn_value	= Initialise_Standard_Jnlookup (&Jtable);
//   rtn_value	= Initialise_Standard_Ynlookup (&Ytable);
//   /**************************/
//   /* Establish wave vectors */
//   /**************************/
//   ki			= Polar_Assign_d3Vector (pPR->k0, pPR->incidence_angle[0], 0.0);
//   thetai	= 2.0*atan(1.0);
//   phii		= 0.0;
//   thetas	= thetai;
//   phis		= phii;
//   kix		= Polar_Assign_d3Vector (pPR->k0, thetai, phii);
//   ksx		= Polar_Assign_d3Vector (pPR->k0, thetas, phis);
//   thetai	= 2.0*atan(1.0);
//   phii		= 2.0*atan(1.0);
//   thetas	= thetai;
//   phis		= phii;
//   kiy		= Polar_Assign_d3Vector (pPR->k0, thetai, phii);
//   ksy		= Polar_Assign_d3Vector (pPR->k0, thetas, phis);
//   thetai	= 0.0;
//   phii		= 0.0;
//   thetas	= thetai;
//   phis		= phii;
//   kiz		= Polar_Assign_d3Vector (pPR->k0, thetai, phii);
//   ksz		= Polar_Assign_d3Vector (pPR->k0, thetas, phis);
//   /****************************************************/
//   /* No trunks, primaries or secondaries in the HEDGE */
//   /****************************************************/
//   if (pPR->species != POLSARPROSIM_HEDGE) {
//      /*********************************************/
//      /* Living crown trunk, primary and secondary */
//      /*********************************************/
//#ifdef VERBOSE_POLSARPROSIM
//      printf ("\n");
//      printf ("Calculating dry, trunk, primary and secondary effective permittivities  ... \n");
//      printf ("\n");
//#endif
//      fprintf (pPR->pLogFile, "Calculating dry, trunk, primary and secondary effective permittivities  ... \n");
//      fflush  (pPR->pLogFile);
//      Ntrees            = POLSARPROSIM_ATTENUATION_TREES;
//      trunk_count       = 0.0;
//      primary_count		= 0.0;
//      secondary_count	= 0.0;
//      dry_count			= 0.0;
//      crown_volume		= 0.0;
//      dry_crown_volume	= 0.0;
//      for (itree = 0; itree < Ntrees; itree++) {
//         Realise_Tree	(&tree1, itree, pPR);
//         /****************************/
//         /* Stem subdivision control */
//         /****************************/
////         dsecl				 = POLSARPROSIM_SAR_BRANCH_FACTOR*tree1.CrownVolume.tail->d3;
////         if (dsecl < FLT_EPSILON) {
////            dsecl				 = bsecl;
////         }
//         pT = &tree1;
//         /* if ((pPR->species != POLSARPROSIM_DECIDUOUS001) && (pPR->species != POLSARPROSIM_NULL_SPECIES)) { */ /* The old way, --RAedit */
//         //if ((tree1.species != POLSARPROSIM_DECIDUOUS001) && (tree1.species != POLSARPROSIM_NULL_SPECIES)) {
//         if(pT->CrownVolume.tail != NULL_PTR2CROWN) { //changed this because I set the tail pointer to NULL in realise_crown();
//            dsecl				 = POLSARPROSIM_SAR_BRANCH_FACTOR*tree1.CrownVolume.tail->d3;
//            if (dsecl < FLT_EPSILON) {
//               dsecl				 = bsecl;
//            }
//
//            /**********************************/
//            /* Stem contribution to dry crown */
//            /**********************************/
//            dry_crown_volume	+= tree1.CrownVolume.tail->volume;
//            pB					 = tree1.Stem.head;
//            trunk_length		 = pB->l;
//            if (bsecl < dsecl) {
//               n_segments			 = (int) (trunk_length / bsecl);
//            } else {
//               n_segments			 = (int) (trunk_length / dsecl);
//            }
//            if (n_segments < POLSARPROSIM_MIN_STEM_SEG_NUM) {
//               n_segments	= POLSARPROSIM_MIN_STEM_SEG_NUM;
//            }
//            for (i_seg=0; i_seg<n_segments; i_seg++) {
//               rtn_value	= Cylinder_from_Branch (&Cyl1, pB, i_seg, n_segments);
//               if (Cyl1.base.x[2] > tree1.CrownVolume.tail->base.x[2]) {
//                  if (Cyl1.base.x[2] < tree1.CrownVolume.tail->base.x[2]+tree1.CrownVolume.tail->d3) {
//                     Alpha                = CylinderPolarisability (&Cyl1, &kix, &kiy, &kiz, &Ytable, &Jtable);
//                     Alpha_Dry_Sum        = c33Matrix_sum (Alpha_Dry_Sum, Alpha);
//                     dry_volume           = DPI_RAD*Cyl1.radius*Cyl1.radius*Cyl1.length;
//                     crown_dry_vol_frac   += dry_volume;
//                     dry_count            += 1.0;
//                  }
//               }
//            }
//            /*************************************/
//            /* Primary contribution to dry crown */
//            /*************************************/
//            pB	= tree1.Dry.head;
//            for (iBranch=0L; iBranch < tree1.Dry.n; iBranch++) {
//               dry_length		= pB->l;
//               n_segments		= (int) (dry_length / bsecl);
//               if (n_segments < 1) {
//                  n_segments	= 1;
//               }
//               for (i_seg=0; i_seg<n_segments; i_seg++) {
//                  rtn_value				= Cylinder_from_Branch (&Cyl1, pB, i_seg, n_segments);
//                  Alpha                = CylinderPolarisability (&Cyl1, &kix, &kiy, &kiz, &Ytable, &Jtable);
//                  Alpha_Dry_Sum			= c33Matrix_sum (Alpha_Dry_Sum, Alpha);
//                  dry_volume           = DPI_RAD*Cyl1.radius*Cyl1.radius*Cyl1.length;
//                  crown_dry_vol_frac	+= dry_volume;
//                  dry_count				+= 1.0;
//               }
//               pB	= pB->next;
//            }
//         }
//         /****************/
//         /* Living crown */
//         /****************/
//         crown_volume		+= tree1.CrownVolume.head->volume;
//         /* loop through the stem sections */
//         pB				 = tree1.Stem.head;
//         trunk_length		 = pB->l;
//         if (bsecl < dsecl) {
//            n_segments			 = (int) (trunk_length / bsecl);
//         } else {
//            n_segments			 = (int) (trunk_length / dsecl);
//         }
//         if (n_segments < POLSARPROSIM_MIN_STEM_SEG_NUM) {
//            n_segments	= POLSARPROSIM_MIN_STEM_SEG_NUM;
//         }
//         for (i_seg=0; i_seg<n_segments; i_seg++) {
//            rtn_value	= Cylinder_from_Branch (&Cyl1, pB, i_seg, n_segments);
//            if (Cyl1.base.x[2] > tree1.CrownVolume.head->base.x[2]) {
//               Alpha                   = CylinderPolarisability (&Cyl1, &kix, &kiy, &kiz, &Ytable, &Jtable);
//               Alpha_Trunk_Sum         = c33Matrix_sum (Alpha_Trunk_Sum, Alpha);
//               trunk_volume            = DPI_RAD*Cyl1.radius*Cyl1.radius*Cyl1.length;
//               crown_trunk_vol_frac    += trunk_volume;
//               trunk_count             += 1.0;
//            }
//         }
//         /* loop through primary branches */
//         pB	= tree1.Primary.head;
//         for (iBranch=0L; iBranch < tree1.Primary.n; iBranch++) {
//            primary_length	= pB->l;
//            n_segments		= (int) (primary_length / bsecl);
//            if (n_segments < 1) {
//               n_segments	= 1;
//            }
//            for (i_seg=0; i_seg<n_segments; i_seg++) {
//               rtn_value               = Cylinder_from_Branch (&Cyl1, pB, i_seg, n_segments);
//               Alpha                   = CylinderPolarisability (&Cyl1, &kix, &kiy, &kiz, &Ytable, &Jtable);
//               Alpha_Primary_Sum       = c33Matrix_sum (Alpha_Primary_Sum, Alpha);
//               primary_volume          = DPI_RAD*Cyl1.radius*Cyl1.radius*Cyl1.length;
//               crown_primary_vol_frac	+= primary_volume;
//               primary_count           += 1.0;
//            }
//            pB	= pB->next;
//         }
//         /* loop through secondary branches */
//         pB	= tree1.Secondary.head;
//         for (iBranch=0L; iBranch < tree1.Secondary.n; iBranch++) {
//            secondary_length	= pB->l;
//            n_segments		= (int) (secondary_length / bsecl);
//            if (n_segments < 1) {
//               n_segments	= 1;
//            }
//            for (i_seg=0; i_seg<n_segments; i_seg++) {
//               rtn_value                  = Cylinder_from_Branch (&Cyl1, pB, i_seg, n_segments);
//               Alpha                      = CylinderPolarisability (&Cyl1, &kix, &kiy, &kiz, &Ytable, &Jtable);
//               Alpha_Secondary_Sum        = c33Matrix_sum (Alpha_Secondary_Sum, Alpha);
//               secondary_volume           = DPI_RAD*Cyl1.radius*Cyl1.radius*Cyl1.length;
//               crown_secondary_vol_frac	+= secondary_volume;
//               secondary_count            += 1.0;
//            }
//            pB	= pB->next;
//         }
//      } /* end for loop on trees */
//      
//      
//      /*if ((pPR->species != POLSARPROSIM_DECIDUOUS001) && (pPR->species != POLSARPROSIM_NULL_SPECIES)) { */
//      if(dry_count > 0){ /* Use dry_count to avoid using pPR->species as a check --RAedit  */
//         crown_dry_vol_frac		/= dry_crown_volume;
//         dry_number_density		 = dry_count / dry_crown_volume;
//         scale_factor				 = xy_complex (dry_number_density/dry_count, 0.0);
//         CrownDry_EpsEff			 = c33Matrix_sum (CrownDry_EpsEff, c33Matrix_Complex_product (Alpha_Dry_Sum, scale_factor));
//      } else {
//         crown_dry_vol_frac		= 0.0;
//         dry_number_density		= 0.0;
//         dry_count				= 0.0;
//         dry_crown_volume			= 0.0;
//      }
//      crown_trunk_vol_frac		/= crown_volume;
//      trunk_number_density		 = trunk_count / crown_volume;
//      scale_factor				 = xy_complex (trunk_number_density/trunk_count, 0.0);
//      CrownTrunk_EpsEff			 = c33Matrix_sum (CrownTrunk_EpsEff, c33Matrix_Complex_product (Alpha_Trunk_Sum, scale_factor));
//      crown_primary_vol_frac	/= crown_volume;
//      primary_number_density	 = primary_count / crown_volume;
//      scale_factor				 = xy_complex (primary_number_density/primary_count, 0.0);
//      CrownPrimary_EpsEff		 = c33Matrix_sum (CrownPrimary_EpsEff, c33Matrix_Complex_product (Alpha_Primary_Sum, scale_factor));
//      crown_secondary_vol_frac	/= crown_volume;
//      secondary_number_density	 = secondary_count / crown_volume;
//      scale_factor				 = xy_complex (secondary_number_density/secondary_count, 0.0);
//      CrownSecondary_EpsEff		 = c33Matrix_sum (CrownSecondary_EpsEff, c33Matrix_Complex_product (Alpha_Secondary_Sum, scale_factor));
//      /*****************************/
//      /* Output results to logfile */
//      /*****************************/
//      fprintf (pPR->pLogFile, "\n");
//      fprintf (pPR->pLogFile, "Crown trunk volume fraction\t\t= %10.3e\n", crown_trunk_vol_frac);
//      fprintf (pPR->pLogFile, "Crown trunk segment number\t\t= %10.3e\n", trunk_count);
//      fprintf (pPR->pLogFile, "Crown volume\t\t\t\t= %10.3e m^3\n", crown_volume);
//      fprintf (pPR->pLogFile, "Crown trunk segment number density\t= %10.3e\n", trunk_number_density);
//      fprintf (pPR->pLogFile, "Crown trunk effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownTrunk_EpsEff.m[0].x, fabs(CrownTrunk_EpsEff.m[0].y));
//      fprintf (pPR->pLogFile, "Crown trunk effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownTrunk_EpsEff.m[4].x, fabs(CrownTrunk_EpsEff.m[4].y));
//      fprintf (pPR->pLogFile, "Crown trunk effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownTrunk_EpsEff.m[8].x, fabs(CrownTrunk_EpsEff.m[8].y));
//      fprintf (pPR->pLogFile, "\n");
//      fprintf (pPR->pLogFile, "\n");
//      fprintf (pPR->pLogFile, "Crown primary volume fraction\t\t= %10.3e\n", crown_primary_vol_frac);
//      fprintf (pPR->pLogFile, "Crown primary segment number\t\t= %10.3e\n", primary_count);
//      fprintf (pPR->pLogFile, "Crown volume\t\t\t\t= %10.3e m^3\n", crown_volume);
//      fprintf (pPR->pLogFile, "Crown primary segment number density\t= %10.3e\n", primary_number_density);
//      fprintf (pPR->pLogFile, "Crown primary effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownPrimary_EpsEff.m[0].x, fabs(CrownPrimary_EpsEff.m[0].y));
//      fprintf (pPR->pLogFile, "Crown primary effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownPrimary_EpsEff.m[4].x, fabs(CrownPrimary_EpsEff.m[4].y));
//      fprintf (pPR->pLogFile, "Crown primary effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownPrimary_EpsEff.m[8].x, fabs(CrownPrimary_EpsEff.m[8].y));
//      fprintf (pPR->pLogFile, "\n");
//      fprintf (pPR->pLogFile, "\n");
//      fprintf (pPR->pLogFile, "Crown secondary volume fraction\t\t= %10.3e\n", crown_secondary_vol_frac);
//      fprintf (pPR->pLogFile, "Crown secondary segment number\t\t= %10.3e\n", secondary_count);
//      fprintf (pPR->pLogFile, "Crown volume\t\t\t\t= %10.3e m^3\n", crown_volume);
//      fprintf (pPR->pLogFile, "Crown secondary segment number density\t= %10.3e\n", secondary_number_density);
//      fprintf (pPR->pLogFile, "Crown secondary effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownSecondary_EpsEff.m[0].x, fabs(CrownSecondary_EpsEff.m[0].y));
//      fprintf (pPR->pLogFile, "Crown secondary effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownSecondary_EpsEff.m[4].x, fabs(CrownSecondary_EpsEff.m[4].y));
//      fprintf (pPR->pLogFile, "Crown secondary effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownSecondary_EpsEff.m[8].x, fabs(CrownSecondary_EpsEff.m[8].y));
//      fprintf (pPR->pLogFile, "\n");
//      fprintf (pPR->pLogFile, "\n");
//      fprintf (pPR->pLogFile, "Crown dry volume fraction\t\t= %10.3e\n", crown_dry_vol_frac);
//      fprintf (pPR->pLogFile, "Crown dry segment number\t\t= %10.3e\n", dry_count);
//      fprintf (pPR->pLogFile, "Crown dry volume\t\t\t= %10.3e m^3\n", dry_crown_volume);
//      fprintf (pPR->pLogFile, "Crown dry segment number density\t= %10.3e\n", dry_number_density);
//      fprintf (pPR->pLogFile, "Crown dry effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownDry_EpsEff.m[0].x, fabs(CrownDry_EpsEff.m[0].y));
//      fprintf (pPR->pLogFile, "Crown dry effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownDry_EpsEff.m[4].x, fabs(CrownDry_EpsEff.m[4].y));
//      fprintf (pPR->pLogFile, "Crown dry effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownDry_EpsEff.m[8].x, fabs(CrownDry_EpsEff.m[8].y));
//      fprintf (pPR->pLogFile, "\n");
//   }
//   
//   /*********************************************************/
//   /* Isotropic short vegetation layer: uses GRG model only */
//   /*********************************************************/
//   
//#ifdef VERBOSE_POLSARPROSIM
//   printf ("\n");
//   printf ("Calculating short vegetation effective permittivity  ... \n");
//   printf ("\n");
//#endif
//   fprintf (pPR->pLogFile, "Calculating short vegetation effective permittivity  ... \n");
//   fflush  (pPR->pLogFile);
//   theta				= 0.0;
//   phi				= 0.0;
//   /********************************************/
//   /* Realise a stem (needle) to find L values */
//   /********************************************/
//   stem_species	= POLSARPROSIM_PINE_NEEDLE;
//   stem_d1			= POLSARPROSIM_SHORTV_STEM_LENGTH;
//   stem_d2			= POLSARPROSIM_SHORTV_STEM_RADIUS;
//   stem_d3			= POLSARPROSIM_SHORTV_STEM_RADIUS;
//   stem_moisture		= Leaf_Moisture	(pPR->species, pPR);
//   stem_permittivity	= vegetation_permittivity (stem_moisture, pPR->frequency);
//   Assign_Leaf		(&leaf1, stem_species, stem_d1, stem_d2, stem_d3, theta, phi, stem_moisture, stem_permittivity, stem_centre);
//   Leaf_Depolarization_Factors (&leaf1, &stemL1, &stemL2, &stemL3);
//   pPR->ShortVegi_stemL1	= stemL1;
//   pPR->ShortVegi_stemL2	= stemL2;
//   pPR->ShortVegi_stemL3	= stemL3;
//   /***********************************/
//   /* Realise a leaf to find L values */
//   /***********************************/
//   leaf_species		= POLSARPROSIM_DECIDUOUS_LEAF;
//   leaf_d1			= POLSARPROSIM_SHORTV_LEAF_LENGTH;
//   leaf_d2			= POLSARPROSIM_SHORTV_LEAF_WIDTH;
//   leaf_d3			= POLSARPROSIM_SHORTV_LEAF_THICKNESS;
//   leaf_moisture		= Leaf_Moisture	(pPR->species, pPR);
//   leaf_permittivity	= vegetation_permittivity (leaf_moisture, pPR->frequency);
//   Assign_Leaf	(&leaf1, leaf_species, leaf_d1, leaf_d2, leaf_d3, theta, phi, leaf_moisture, leaf_permittivity, leaf_centre);
//   Leaf_Depolarization_Factors (&leaf1, &leafL1, &leafL2, &leafL3);
//   pPR->ShortVegi_leafL1	= leafL1;
//   pPR->ShortVegi_leafL2	= leafL2;
//   pPR->ShortVegi_leafL3	= leafL3;
//   /****************************************************/
//   /* Average polarisabilities over orientation angles */
//   /****************************************************/
//   Ntheta				= POLSARPROSIM_SHORT_VEGI_NTHETA;
//   Nphi				= POLSARPROSIM_SHORT_VEGI_NPHI;
//   d_costheta			= 2.0/Ntheta;
//   d_phi				= 2.0*DPI_RAD/Nphi;
//   for (i_costheta = 0; i_costheta < Ntheta; i_costheta++) {
//      costheta	= i_costheta*d_costheta + d_costheta/2.0 - 1.0;
//      theta		= acos(costheta);
//      for (i_phi = 0; i_phi < Nphi; i_phi++) {
//         phi	= i_phi*d_phi + d_phi/2.0;
//         /**********************/
//         /* Stem contribution  */
//         /**********************/
//         stem_moisture		= Leaf_Moisture	(pPR->species, pPR);
//         stem_permittivity	= vegetation_permittivity (stem_moisture, pPR->frequency);
//         stem_epsm1			= xy_complex (stem_permittivity.x-1.0, stem_permittivity.y);
//         Assign_Leaf	(&leaf1, stem_species, stem_d1, stem_d2, stem_d3, theta, phi, stem_moisture, stem_permittivity, stem_centre);
//         Alpha				= Leaf_Polarisability (&leaf1, stemL1, stemL2, stemL3);
//         Alpha_Stem_Sum		= c33Matrix_sum (Alpha_Stem_Sum, c33Matrix_Complex_product (Alpha, stem_epsm1));
//         /*********************/
//         /* Leaf contribution */
//         /*********************/
//         leaf_moisture		= Leaf_Moisture	(pPR->species, pPR);
//         leaf_permittivity	= vegetation_permittivity (leaf_moisture, pPR->frequency);
//         leaf_epsm1			= xy_complex (leaf_permittivity.x-1.0, leaf_permittivity.y);
//         Assign_Leaf	(&leaf1, leaf_species, leaf_d1, leaf_d2, leaf_d3, theta, phi, leaf_moisture, leaf_permittivity, leaf_centre);
//         Alpha				= Leaf_Polarisability (&leaf1, leafL1, leafL2, leafL3);
//         Alpha_Leaf_Sum		= c33Matrix_sum (Alpha_Leaf_Sum, c33Matrix_Complex_product (Alpha, leaf_epsm1));
//      }
//   }
//   scale_factor			= xy_complex (pPR->shrt_vegi_stem_vol_frac/(Ntheta*Nphi), 0.0);
//   ShortVegi_EpsEff		= c33Matrix_sum (ShortVegi_EpsEff, c33Matrix_Complex_product (Alpha_Stem_Sum, scale_factor));
//   scale_factor			= xy_complex (pPR->shrt_vegi_leaf_vol_frac/(Ntheta*Nphi), 0.0);
//   ShortVegi_EpsEff		= c33Matrix_sum (ShortVegi_EpsEff, c33Matrix_Complex_product (Alpha_Leaf_Sum, scale_factor));
//   /******************************************************/
//   /* Ensure perfect isotropy with this minor correction */
//   /******************************************************/
//   e						= complex_add (complex_add (ShortVegi_EpsEff.m[0], ShortVegi_EpsEff.m[4]), ShortVegi_EpsEff.m[8]);
//   e						= complex_rmul (e, 1.0/3.0);
//   ShortVegi_EpsEff		= Zero_c33Matrix ();
//   ShortVegi_EpsEff.m[0]	= e;
//   ShortVegi_EpsEff.m[4]	= e;
//   ShortVegi_EpsEff.m[8]	= e;
//   /*****************************/
//   /* Output results to logfile */
//   /*****************************/
//   fprintf (pPR->pLogFile, "\n");
//   fprintf (pPR->pLogFile, "Short vegetation effective permittivity = %10.3e + j %10.3e  ... \n", ShortVegi_EpsEff.m[0].x, fabs(ShortVegi_EpsEff.m[0].y));
//   fprintf (pPR->pLogFile, "Short vegetation effective permittivity = %10.3e + j %10.3e  ... \n", ShortVegi_EpsEff.m[4].x, fabs(ShortVegi_EpsEff.m[4].y));
//   fprintf (pPR->pLogFile, "Short vegetation effective permittivity = %10.3e + j %10.3e  ... \n", ShortVegi_EpsEff.m[8].x, fabs(ShortVegi_EpsEff.m[8].y));
//   fprintf (pPR->pLogFile, "\n");
//   
//   
//   /*************************/
//   /* Living crown tertiary */
//   /*************************/
//   
//#ifdef VERBOSE_POLSARPROSIM
//   printf ("\n");
//   printf ("Calculating crown tertiary effective permittivity  ... \n");
//   printf ("\n");
//#endif
//   fprintf (pPR->pLogFile, "Calculating crown tertiary effective permittivity  ... \n");
//   fflush  (pPR->pLogFile);
//   /**************************************/
//   /* Establish the tertiary branch size */
//   /**************************************/
//   if (pPR->species == POLSARPROSIM_HEDGE) {
//      tertiary_branch_length		= POLSARPROSIM_HEDGE_TERTIARY_BRANCH_LENGTH;
//      tertiary_branch_radius		= POLSARPROSIM_HEDGE_TERTIARY_BRANCH_RADIUS;
//      pPR->primary_branch_length	= 0.0;
//      pPR->primary_branch_radius	= 0.0;
//      pPR->secondary_branch_length	= 0.0;
//      pPR->secondary_branch_radius	= 0.0;
//      pPR->tertiary_branch_length	= tertiary_branch_length;
//      pPR->tertiary_branch_radius	= tertiary_branch_radius;
//   } else {
//      if (pPR->Trees > POLSARPROSIM_ATTENUATION_TREES) {
//         Ntrees	= POLSARPROSIM_ATTENUATION_TREES;
//      } else {
//         Ntrees	= pPR->Trees;
//      }
//      primary_branch_length		= 0.0;
//      primary_branch_radius		= 0.0;
//      primary_branch_count		= 0.0;
//      secondary_branch_length	= 0.0;
//      secondary_branch_radius	= 0.0;
//      secondary_branch_count	= 0.0;
//      for (itree = 0; itree < Ntrees; itree++) {
//         Realise_Tree	(&tree1, itree, pPR);
//         pB	= tree1.Primary.head;
//         for (iBranch=0L; iBranch < tree1.Primary.n; iBranch++) {
//            primary_branch_length	+= pB->l;
//            primary_branch_radius	+= 0.5*(pB->start_radius + pB->end_radius);
//            primary_branch_count	+= 1.0;
//            pB	= pB->next;
//         }
//         pB	= tree1.Secondary.head;
//         for (iBranch=0L; iBranch < tree1.Secondary.n; iBranch++) {
//            secondary_branch_length	+= pB->l;
//            secondary_branch_radius	+= 0.5*(pB->start_radius + pB->end_radius);
//            secondary_branch_count	+= 1.0;
//            pB	= pB->next;
//         }
//      }
//      primary_branch_length			/= primary_branch_count;
//      primary_branch_radius			/= primary_branch_count;
//      secondary_branch_length       /= secondary_branch_count;
//      secondary_branch_radius       /= secondary_branch_count;
//      tertiary_branch_length        = secondary_branch_length*secondary_branch_length/primary_branch_length;
//      tertiary_branch_radius        = secondary_branch_radius*secondary_branch_radius/primary_branch_radius;
//      pPR->primary_branch_length    = primary_branch_length;
//      pPR->primary_branch_radius    = primary_branch_radius;
//      pPR->secondary_branch_length	= secondary_branch_length;
//      pPR->secondary_branch_radius	= secondary_branch_radius;
//      pPR->tertiary_branch_length	= tertiary_branch_length;
//      pPR->tertiary_branch_radius	= tertiary_branch_radius;
//   }
//   /***************************************************************************/
//   /* Make a choice of scattering model for tertiary branches based upon size */
//   /***************************************************************************/
//   pPR->Grg_Flag		= 0;
//   aoverlamda			= pPR->tertiary_branch_radius / pPR->wavelength;
//   stem_moisture		= Tertiary_Branch_Moisture	(&tree1, pPR);
//   stem_permittivity	= vegetation_permittivity	(stem_moisture, pPR->frequency);
//   rfac				= GRG_VALIDITY_FACTOR/(4.0*DPI_RAD*sqrt(stem_permittivity.r));
//   if (aoverlamda > rfac) {
//      pPR->Grg_Flag		= 1;
//   }
//   /*******************************************/
//   /* Report tertiary branch scattering model */
//   /*******************************************/
//   if (pPR->Grg_Flag == 0) {
//      fprintf (pPR->pLogFile, "\nUsing GRG model for tertiary branches.\n");
//   } else {
//      fprintf (pPR->pLogFile, "\nUsing INF model for tertiary branches.\n");
//   }
//   /*******************************************************************************/
//   /* Now find effective permittivity by averaging polarisabilities as before ... */
//   /*******************************************************************************/
//   Ntheta				= POLSARPROSIM_TERTIARY_NTHETA;
//   Nphi				= POLSARPROSIM_TERTIARY_NPHI;
//   d_costheta			= 2.0/Ntheta;
//   d_phi				= 2.0*DPI_RAD/Nphi;
//   stem_d1			= tertiary_branch_length;
//   stem_d2			= tertiary_branch_radius;
//   stem_d3			= stem_d2;
//   stem_moisture		= Tertiary_Branch_Moisture	(&tree1, pPR); //--RAedit
//   stem_permittivity	= vegetation_permittivity	(stem_moisture, pPR->frequency);
//   theta				= 0.0;
//   phi				= 0.0;
//   Assign_Leaf	(&leaf1, stem_species, stem_d1, stem_d2, stem_d3, theta, phi, stem_moisture, stem_permittivity, stem_centre);
//   Leaf_Depolarization_Factors (&leaf1, &stemL1, &stemL2, &stemL3);
//   pPR->Tertiary_branchL1	= stemL1;
//   pPR->Tertiary_branchL2	= stemL2;
//   pPR->Tertiary_branchL3	= stemL3;
//   Alpha_Stem_Sum			= Zero_c33Matrix ();
//   t_base					= Cartesian_Assign_d3Vector (0.0, 0.0, 0.0);
//   tertiary_branch_volume	= DPI_RAD*tertiary_branch_radius*tertiary_branch_radius*tertiary_branch_length;
//   tbvinv					= xy_complex (1.0/tertiary_branch_volume, 0.0);
//   
//   /********************************/
//   /* Tertiary branch contribution */
//   /********************************/
//   
//   for (i_costheta = 0; i_costheta < Ntheta; i_costheta++) {
//      costheta	= i_costheta*d_costheta + d_costheta/2.0 - 1.0;
//      theta		= acos(costheta);
//      for (i_phi = 0; i_phi < Nphi; i_phi++) {
//         phi	= i_phi*d_phi + d_phi/2.0;
//         stem_moisture		= Tertiary_Branch_Moisture	(&tree1,pPR);
//         stem_permittivity	= vegetation_permittivity	(stem_moisture, pPR->frequency);
//         if (pPR->Grg_Flag == 0) {
//            /*********************************/
//            /* Small branches uses GRG model */
//            /*********************************/
//            stem_epsm1			= xy_complex (stem_permittivity.x-1.0, stem_permittivity.y);
//            Assign_Leaf	(&leaf1, stem_species, stem_d1, stem_d2, stem_d3, theta, phi, stem_moisture, stem_permittivity, stem_centre);
//            Alpha				= Leaf_Polarisability (&leaf1, stemL1, stemL2, stemL3);
//            Alpha_Stem_Sum		= c33Matrix_sum (Alpha_Stem_Sum, c33Matrix_Complex_product (Alpha, stem_epsm1));
//         } else {
//            /************************************************************/
//            /* Large branches use the truncated infinite cylinder model */
//            /************************************************************/
//            t_axis				= Polar_Assign_d3Vector (1.0, theta, phi);
//            Assign_Cylinder (&Cyl1, tertiary_branch_length, tertiary_branch_radius, stem_permittivity, t_axis, t_base);
//            Alpha				= CylinderPolarisability (&Cyl1, &kix, &kiy, &kiz, &Ytable, &Jtable);
//            Alpha_Stem_Sum		= c33Matrix_sum (Alpha_Stem_Sum, c33Matrix_Complex_product (Alpha, tbvinv));
//         }
//      }
//   }
//   switch (pPR->species) {
//      case POLSARPROSIM_HEDGE:			tertiary_branch_vol_frac	= POLSARPROSIM_HEDGE_TERTIARY_BRANCH_VOL_FRAC;			break;
//      case POLSARPROSIM_PINE001:		tertiary_branch_vol_frac	= POLSARPROSIM_PINE001_TERTIARY_BRANCH_VOL_FRAC;		break;
//      case POLSARPROSIM_PINE002:		tertiary_branch_vol_frac	= POLSARPROSIM_PINE001_TERTIARY_BRANCH_VOL_FRAC;		break;
//      case POLSARPROSIM_PINE003:		tertiary_branch_vol_frac	= POLSARPROSIM_PINE001_TERTIARY_BRANCH_VOL_FRAC;		break;
//      case POLSARPROSIM_DECIDUOUS001:	tertiary_branch_vol_frac	= POLSARPROSIM_DECIDUOUS001_TERTIARY_BRANCH_VOL_FRAC;	break;
//      default:							tertiary_branch_vol_frac	= 0.0;	break;
//   }
//   scale_factor			= xy_complex (tertiary_branch_vol_frac/(Ntheta*Nphi), 0.0);
//   CrownTert_EpsEff		= c33Matrix_sum (CrownTert_EpsEff, c33Matrix_Complex_product (Alpha_Stem_Sum, scale_factor));
//   
//   /*********************/
//   /* Leaf contribution */
//   /*********************/
//   
//   leaf_species	= Leaf_Species       (pPR->species, pPR);
//   leaf_d1			= Leaf_Dimension_1	(pPR->species);
//   leaf_d2			= Leaf_Dimension_2	(pPR->species);
//   leaf_d3			= Leaf_Dimension_3	(pPR->species);
//   leaf_centre		= Cartesian_Assign_d3Vector (0.0, 0.0, 0.0);
//   theta				= 0.0;
//   phi				= 0.0;
//   leaf_moisture		= Leaf_Moisture		(pPR->species, pPR);
//   leaf_permittivity	= vegetation_permittivity (leaf_moisture, pPR->frequency);
//   Assign_Leaf	(&leaf1, leaf_species, leaf_d1, leaf_d2, leaf_d3, theta, phi, leaf_moisture, leaf_permittivity, leaf_centre);
//   Leaf_Depolarization_Factors (&leaf1, &leafL1, &leafL2, &leafL3);
//   pPR->Tertiary_leafL1	= leafL1;
//   pPR->Tertiary_leafL2	= leafL2;
//   pPR->Tertiary_leafL3	= leafL3;
//   Alpha_Leaf_Sum		= Zero_c33Matrix ();
//   printf("Leaves in Epseff: %ld\n", (long)(Ntheta*Nphi)); 
//   for (i_costheta = 0; i_costheta < Ntheta; i_costheta++) {
//      costheta	= i_costheta*d_costheta + d_costheta/2.0 - 1.0;
//      theta		= acos(costheta);
//      for (i_phi = 0; i_phi < Nphi; i_phi++) {
//         phi	= i_phi*d_phi + d_phi/2.0;
//         leaf_moisture		= Leaf_Moisture	(pPR->species, pPR);
//         leaf_permittivity	= vegetation_permittivity	(leaf_moisture, pPR->frequency);
//         leaf_epsm1			= xy_complex (leaf_permittivity.x-1.0, leaf_permittivity.y);
//         Assign_Leaf	(&leaf1, leaf_species, leaf_d1, leaf_d2, leaf_d3, theta, phi, leaf_moisture, leaf_permittivity, leaf_centre);
//         Alpha				= Leaf_Polarisability (&leaf1, leafL1, leafL2, leafL3);
//         Alpha_Leaf_Sum		= c33Matrix_sum (Alpha_Leaf_Sum, c33Matrix_Complex_product (Alpha, leaf_epsm1));
//      }
//   }
//   switch (pPR->species) {
//      case POLSARPROSIM_HEDGE:			tertiary_leaf_vol_frac	= POLSARPROSIM_HEDGE_FOLIAGE_VOL_FRAC;			break;
//      case POLSARPROSIM_PINE001:		tertiary_leaf_vol_frac	= POLSARPROSIM_PINE001_FOLIAGE_VOL_FRAC;		break;
//      case POLSARPROSIM_PINE002:		tertiary_leaf_vol_frac	= POLSARPROSIM_PINE001_FOLIAGE_VOL_FRAC;		break;
//      case POLSARPROSIM_PINE003:		tertiary_leaf_vol_frac	= POLSARPROSIM_PINE001_FOLIAGE_VOL_FRAC;		break;
//      case POLSARPROSIM_DECIDUOUS001:	tertiary_leaf_vol_frac	= POLSARPROSIM_DECIDUOUS001_FOLIAGE_VOL_FRAC;	break;
//      default:							tertiary_leaf_vol_frac	= 0.0;	break;
//   }
//   scale_factor			= xy_complex (tertiary_leaf_vol_frac/(Ntheta*Nphi), 0.0);
//   CrownTert_EpsEff		= c33Matrix_sum (CrownTert_EpsEff, c33Matrix_Complex_product (Alpha_Leaf_Sum, scale_factor));
//   /********************/
//   /* Enforce isotropy */
//   /********************/
//   e						= complex_add (complex_add (CrownTert_EpsEff.m[0], CrownTert_EpsEff.m[4]), CrownTert_EpsEff.m[8]);
//   e						= complex_rmul (e, 1.0/3.0);
//   CrownTert_EpsEff		= Zero_c33Matrix ();
//   CrownTert_EpsEff.m[0]	= e;
//   CrownTert_EpsEff.m[4]	= e;
//   CrownTert_EpsEff.m[8]	= e;
//   /******************************/
//   /* Output results to log file */
//   /******************************/
//   fprintf (pPR->pLogFile, "\n");
//   fprintf (pPR->pLogFile, "Crown tertiary effective permittivity = %10.3e + j %10.3e  ... \n", CrownTert_EpsEff.m[0].x, fabs(CrownTert_EpsEff.m[0].y));
//   fprintf (pPR->pLogFile, "Crown tertiary effective permittivity = %10.3e + j %10.3e  ... \n", CrownTert_EpsEff.m[4].x, fabs(CrownTert_EpsEff.m[4].y));
//   fprintf (pPR->pLogFile, "Crown tertiary effective permittivity = %10.3e + j %10.3e  ... \n", CrownTert_EpsEff.m[8].x, fabs(CrownTert_EpsEff.m[8].y));
//   fprintf (pPR->pLogFile, "\n");
//   /******************************************/
//   /* Combine contributions for living crown */
//   /******************************************/
//   CrownLiving_EpsEff		= c33Matrix_sum (CrownLiving_EpsEff, c33Matrix_difference (CrownTrunk_EpsEff, Idem_c33Matrix ()));
//   CrownLiving_EpsEff		= c33Matrix_sum (CrownLiving_EpsEff, c33Matrix_difference (CrownPrimary_EpsEff, Idem_c33Matrix ()));
//   CrownLiving_EpsEff		= c33Matrix_sum (CrownLiving_EpsEff, c33Matrix_difference (CrownSecondary_EpsEff, Idem_c33Matrix ()));
//   CrownLiving_EpsEff		= c33Matrix_sum (CrownLiving_EpsEff, c33Matrix_difference (CrownTert_EpsEff, Idem_c33Matrix ()));
//   /************************************************/
//   /* Rationalise effective permittivity estimates */
//   /* Calculate and store effective wavenumbers.   */
//   /************************************************/
//   e						 = complex_rmul (complex_add (CrownDry_EpsEff.m[0], CrownDry_EpsEff.m[4]), 0.5);
//   ez						 = CrownDry_EpsEff.m[8];
//   CrownDry_EpsEff		 = Idem_c33Matrix ();
//   CrownDry_EpsEff.m[0]	 = e;
//   CrownDry_EpsEff.m[4]	 = e;
//   CrownDry_EpsEff.m[8]	 = ez;
//   pPR->e11_dry			 = e;
//   pPR->e33_dry			 = ez;
//   kro2					 = pPR->k0*sin(pPR->incidence_angle[0]);
//   kro2					*= kro2;
//   ko2					 = complex_rmul (e, pPR->k0*pPR->k0);
//   koz2					 = xy_complex (ko2.x-kro2, ko2.y);
//   koz					 = complex_sqrt (koz2);
//   ke2					 = complex_rmul (ez, pPR->k0*pPR->k0);
//   kez2					 = xy_complex (ke2.x-kro2, ke2.y);
//   kez2					 = complex_mul (kez2, complex_div (e ,ez));
//   kez					 = complex_sqrt(kez2);
//   ke2					 = complex_add (kez2, xy_complex (kro2, 0.0));
//   pPR->ko2_dry			 = ko2;
//   pPR->koz2_dry			 = koz2;
//   pPR->koz_dry			 = koz;
//   pPR->ke2_dry			 = ke2;
//   pPR->kez2_dry			 = kez2;
//   pPR->kez_dry			 = kez;
//   e						 = complex_rmul (complex_add (CrownLiving_EpsEff.m[0], CrownLiving_EpsEff.m[4]), 0.5);
//   ez						 = CrownLiving_EpsEff.m[8];
//   CrownLiving_EpsEff		 = Idem_c33Matrix ();
//   CrownLiving_EpsEff.m[0] = e;
//   CrownLiving_EpsEff.m[4] = e;
//   CrownLiving_EpsEff.m[8] = ez;
//   pPR->e11_living		 = e;
//   pPR->e33_living		 = ez;
//   kro2					 = pPR->k0*sin(pPR->incidence_angle[0]);
//   kro2					*= kro2;
//   ko2					 = complex_rmul (e, pPR->k0*pPR->k0);
//   koz2					 = xy_complex (ko2.x-kro2, ko2.y);
//   koz					 = complex_sqrt (koz2);
//   ke2					 = complex_rmul (ez, pPR->k0*pPR->k0);
//   kez2					 = xy_complex (ke2.x-kro2, ke2.y);
//   kez2					 = complex_mul (kez2, complex_div (e ,ez));
//   kez					 = complex_sqrt(kez2);
//   ke2					 = complex_add (kez2, xy_complex (kro2, 0.0));
//   pPR->ko2_living		 = ko2;
//   pPR->koz2_living		 = koz2;
//   pPR->koz_living		 = koz;
//   pPR->ke2_living		 = ke2;
//   pPR->kez2_living		 = kez2;
//   pPR->kez_living		 = kez;
//   e						 = complex_rmul (complex_add (ShortVegi_EpsEff.m[0], ShortVegi_EpsEff.m[4]), 0.5);
//   ez						 = ShortVegi_EpsEff.m[8];
//   ShortVegi_EpsEff		 = Idem_c33Matrix ();
//   ShortVegi_EpsEff.m[0]	 = e;
//   ShortVegi_EpsEff.m[4]	 = e;
//   ShortVegi_EpsEff.m[8]	 = ez;
//   pPR->e11_short			 = e;
//   pPR->e33_short			 = ez;
//   kro2					 = pPR->k0*sin(pPR->incidence_angle[0]);
//   kro2					*= kro2;
//   ko2					 = complex_rmul (e, pPR->k0*pPR->k0);
//   koz2					 = xy_complex (ko2.x-kro2, ko2.y);
//   koz					 = complex_sqrt (koz2);
//   ke2					 = complex_rmul (ez, pPR->k0*pPR->k0);
//   kez2					 = xy_complex (ke2.x-kro2, ke2.y);
//   kez2					 = complex_mul (kez2, complex_div (e ,ez));
//   kez					 = complex_sqrt(kez2);
//   ke2					 = complex_add (kez2, xy_complex (kro2, 0.0));
//   pPR->ko2_short			 = ko2;
//   pPR->koz2_short		 = koz2;
//   pPR->koz_short			 = koz;
//   pPR->ke2_short			 = ke2;
//   pPR->kez2_short		 = kez2;
//   pPR->kez_short			 = kez;
//   /******************************/
//   /* Output results to log file */
//   /******************************/
//   fprintf (pPR->pLogFile, "\n");
//   fprintf (pPR->pLogFile, "Consolidated effective permittivities:");
//   fprintf (pPR->pLogFile, "\n");
//   fprintf (pPR->pLogFile, "\n");
//   fprintf (pPR->pLogFile, "Crown dry effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownDry_EpsEff.m[0].x, fabs(CrownDry_EpsEff.m[0].y));
//   fprintf (pPR->pLogFile, "Crown dry effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownDry_EpsEff.m[4].x, fabs(CrownDry_EpsEff.m[4].y));
//   fprintf (pPR->pLogFile, "Crown dry effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownDry_EpsEff.m[8].x, fabs(CrownDry_EpsEff.m[8].y));
//   fprintf (pPR->pLogFile, "\n");
//   fprintf (pPR->pLogFile, "\n");
//   fprintf (pPR->pLogFile, "Crown living effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownLiving_EpsEff.m[0].x, fabs(CrownLiving_EpsEff.m[0].y));
//   fprintf (pPR->pLogFile, "Crown living effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownLiving_EpsEff.m[4].x, fabs(CrownLiving_EpsEff.m[4].y));
//   fprintf (pPR->pLogFile, "Crown living effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownLiving_EpsEff.m[8].x, fabs(CrownLiving_EpsEff.m[8].y));
//   fprintf (pPR->pLogFile, "\n");
//   fprintf (pPR->pLogFile, "\n");
//   fprintf (pPR->pLogFile, "Short vegetation effective permittivity = %10.3e + j %10.3e  ... \n", ShortVegi_EpsEff.m[0].x, fabs(ShortVegi_EpsEff.m[0].y));
//   fprintf (pPR->pLogFile, "Short vegetation effective permittivity = %10.3e + j %10.3e  ... \n", ShortVegi_EpsEff.m[4].x, fabs(ShortVegi_EpsEff.m[4].y));
//   fprintf (pPR->pLogFile, "Short vegetation effective permittivity = %10.3e + j %10.3e  ... \n", ShortVegi_EpsEff.m[8].x, fabs(ShortVegi_EpsEff.m[8].y));
//   fprintf (pPR->pLogFile, "\n");
//   /***********/
//   /* Tidy up */
//   /***********/
//   Destroy_Tree		(&tree1);
//   Destroy_Leaf		(&leaf1);
//   Destroy_Cylinder	(&Cyl1);
//   rtn_value	= Delete_Jnlookup		(&Jtable);
//   rtn_value	= Delete_Ynlookup		(&Ytable);
//   /******************************************/
//   /* Report call if running in VERBOSE mode */
//   /******************************************/
//#ifdef VERBOSE_POLSARPROSIM
//   printf ("\n");
//   printf ("... Returning from call to Effective_Permittivities\n");
//   printf ("\n");
//#endif
//   fprintf (pPR->pLogFile, "... Returning from call to Effective_Permittivities\n\n");
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
//   return;
//}

void		Effective_Permittivities	(PolSARproSim_Record *pPR)
{
   const double	bsecl	=	POLSARPROSIM_SAR_BRANCH_FACTOR*(pPR->azimuth_resolution + pPR->slant_range_resolution);
   double			dsecl;
   Leaf           leaf1;
   double			costheta, theta, phi;
   double			d_costheta, d_phi;
   int            i_costheta, i_phi;
   int            Ntheta, Nphi;
   d3Vector       leaf_centre	= Zero_d3Vector ();
   d3Vector       stem_centre	= Zero_d3Vector ();
   double			leaf_d1, leaf_d2, leaf_d3;
   int            leaf_species;
   double			leaf_moisture;
   Complex        leaf_permittivity, leaf_epsm1;
   double			stem_d1, stem_d2, stem_d3;
   int            stem_species;
   double			stem_moisture;
   Complex        stem_permittivity, stem_epsm1;
   Complex        scale_factor;
   c33Matrix		ShortVegi_EpsEff	= Idem_c33Matrix ();
   double			stemL1, stemL2, stemL3;
   double			leafL1, leafL2, leafL3;
   Tree           tree1;
   int            itree;
   int            Ntrees;
   Branch			*pB;
   long           iBranch;
   
   c33Matrix		Alpha_Trunk_Sum				= Zero_c33Matrix ();
   c33Matrix		Alpha_Primary_Sum          = Zero_c33Matrix ();
   c33Matrix		Alpha_Secondary_Sum			= Zero_c33Matrix ();
   c33Matrix		Alpha_Tertiary_Sum         = Zero_c33Matrix ();
   c33Matrix		Alpha_Leaf_Sum             = Zero_c33Matrix ();
   c33Matrix		Alpha_Dry_Sum              = Zero_c33Matrix ();
   c33Matrix		Alpha                      = Zero_c33Matrix ();
   c33Matrix		Alpha_Stem_Sum             = Zero_c33Matrix ();
   
   c33Matrix		CrownTrunk_EpsEff          = Idem_c33Matrix ();
   c33Matrix		CrownPrimary_EpsEff			= Idem_c33Matrix ();
   c33Matrix		CrownSecondary_EpsEff		= Idem_c33Matrix ();
   c33Matrix		CrownTert_EpsEff           = Idem_c33Matrix ();
   c33Matrix		CrownDry_EpsEff				= Idem_c33Matrix ();
   c33Matrix		CrownLiving_EpsEff			= Idem_c33Matrix ();
   
   double			crown_trunk_vol_frac       = 0.0;
   double			crown_primary_vol_frac		= 0.0;
   double			crown_secondary_vol_frac	= 0.0;
   double			crown_dry_vol_frac			= 0.0;
   double			crown_volume, dry_crown_volume;
   double			trunk_length, trunk_count, trunk_volume, trunk_number_density;
   double			primary_length, primary_count, primary_volume, primary_number_density;
   double			secondary_length, secondary_count, secondary_volume, secondary_number_density;
   
   /* for treating tertiaries as cylinders instead of leaves */
   double         tertiary_length, tertiary_count, tertiary_volume, tertiary_number_density;
   double         crown_tertiary_vol_frac    = 0.0;
   int            number_of_tertiaries;
   
   /* for using already realized leaves */
   int            number_of_leaves;
   double         crown_foliage_vol_frac     = 0.0;
   double         foliage_number_density, leaf_volume, leaf_count;
   
   double			dry_length, dry_count, dry_volume, dry_number_density;
   int            n_segments, i_seg;
   int            rtn_value;
   Cylinder       Cyl1;
   d3Vector       ki, kix, ksx, kiy, ksy, kiz, ksz;
   double			thetai, phii, thetas, phis;
   Yn_Lookup		Ytable;
   Jn_Lookup		Jtable;
   Complex        e, ez;
   double         kro2;
   Complex        ko2, koz2, koz;
   Complex        ke2, kez2, kez;
   
   Tree           *pT;
   Leaf           *pL;
   long           iLeaf;
   
   int            ispecies;
   int            treeindex[POLSARPROSIM_ATTENUATION_TREES];
   int            index_count;
   
   /******************************************/
   /* Report call if running in VERBOSE mode */
   /******************************************/
#ifdef VERBOSE_POLSARPROSIM
   printf ("\n");
   printf ("Call to Effective_Permittivities ... \n");
   printf ("\n");
#endif
   fprintf (pPR->pLogFile, "Call to Effective_Permittivities ... \n");
   fflush  (pPR->pLogFile);
   /**************/
   /* Initialise */
   /**************/
   Create_Leaf		(&leaf1);
   Create_Tree		(&tree1);
   Create_Cylinder	(&Cyl1);
   /*********************************************/
   /* Initialise Bessel function look-up tables */
   /*********************************************/
   rtn_value	= Initialise_Standard_Jnlookup (&Jtable);
   rtn_value	= Initialise_Standard_Ynlookup (&Ytable);
   /**************************/
   /* Establish wave vectors */
   /**************************/
   ki			= Polar_Assign_d3Vector (pPR->k0, pPR->incidence_angle[0], 0.0);
   thetai	= 2.0*atan(1.0);
   phii		= 0.0;
   thetas	= thetai;
   phis		= phii;
   kix		= Polar_Assign_d3Vector (pPR->k0, thetai, phii);
   ksx		= Polar_Assign_d3Vector (pPR->k0, thetas, phis);
   thetai	= 2.0*atan(1.0);
   phii		= 2.0*atan(1.0);
   thetas	= thetai;
   phis		= phii;
   kiy		= Polar_Assign_d3Vector (pPR->k0, thetai, phii);
   ksy		= Polar_Assign_d3Vector (pPR->k0, thetas, phis);
   thetai	= 0.0;
   phii		= 0.0;
   thetas	= thetai;
   phis		= phii;
   kiz		= Polar_Assign_d3Vector (pPR->k0, thetai, phii);
   ksz		= Polar_Assign_d3Vector (pPR->k0, thetas, phis);
   
   /* Initialize the global effective wave vectors */
   pPR->koz_living   = (Complex *) calloc(pPR->Nspecies, sizeof(Complex));
   pPR->koz_dry      = (Complex *) calloc(pPR->Nspecies, sizeof(Complex));
   pPR->kez_living   = (Complex *) calloc(pPR->Nspecies, sizeof(Complex));
   pPR->kez_dry      = (Complex *) calloc(pPR->Nspecies, sizeof(Complex));
   
   /*********************************************/
   /* Estimate the wavevectors for each species */
   /*********************************************/
   for (ispecies=0;ispecies<pPR->Nspecies;ispecies++){
      
#ifdef VERBOSE_POLSARPROSIM
      printf ("\n");
      printf ("Calculating dry, trunk, primary, secondary, tertiary and foliage effective permittivities for %s ... \n", pPR->SpeciesDataBase[ispecies].species_name);
      printf ("\n");
#endif
      fprintf (pPR->pLogFile, "Calculating dry, trunk, primary, secondary, tertiary and foliage effective permittivities for %s ... \n", pPR->SpeciesDataBase[ispecies].species_name);
      fflush  (pPR->pLogFile);
      
      /* determine how many trees to average over for this species */
      if(pPR->SpeciesDataBase[ispecies].Trees < POLSARPROSIM_ATTENUATION_TREES) {
         Ntrees = pPR->SpeciesDataBase[ispecies].Trees;
      } else{
         Ntrees = POLSARPROSIM_ATTENUATION_TREES;
      }
      
      /* determine which trees to average over */
      itree = 0;
      index_count = 0;
      while(index_count<Ntrees){
         if(pPR->Tree_Location[itree].species == ispecies) {
            treeindex[index_count] = itree;
            index_count++;
         }
         itree++;
      }
      
      /* zero out the counters */
      trunk_count                = 0.0;
      primary_count              = 0.0;
      secondary_count            = 0.0;
      tertiary_count             = 0.0;
      leaf_count                 = 0.0;
      dry_count                  = 0.0;
      crown_volume               = 0.0;
      dry_crown_volume           = 0.0;
      /* zero out the volume fractions */
      crown_trunk_vol_frac       = 0.0;
      crown_primary_vol_frac		= 0.0;
      crown_secondary_vol_frac	= 0.0;
      crown_dry_vol_frac			= 0.0;
      /* zero out the polarizability tensors */
      Alpha_Trunk_Sum				= Zero_c33Matrix ();
      Alpha_Primary_Sum          = Zero_c33Matrix ();
      Alpha_Secondary_Sum			= Zero_c33Matrix ();
      Alpha_Dry_Sum              = Zero_c33Matrix ();
      Alpha_Tertiary_Sum         = Zero_c33Matrix ();
      Alpha_Leaf_Sum             = Zero_c33Matrix ();
      /* zero out the permittivity tensors */
      CrownTrunk_EpsEff          = Idem_c33Matrix ();
      CrownPrimary_EpsEff			= Idem_c33Matrix ();
      CrownSecondary_EpsEff		= Idem_c33Matrix ();
      CrownTert_EpsEff           = Idem_c33Matrix ();
      CrownDry_EpsEff				= Idem_c33Matrix ();
      CrownLiving_EpsEff			= Idem_c33Matrix ();
      
      for (itree = 0; itree < Ntrees; itree++) {
         fflush(stderr);
         Realise_Tree(&tree1, treeindex[itree], pPR);
         pT = &tree1;
         
         /***************************/
         /* Dry crown contribution  */
         /***************************/
         /* if dry crown exists, then estimate dry parameters */
         if(pT->CrownVolume.tail != NULL_PTR2CROWN) {
            dsecl				 = POLSARPROSIM_SAR_BRANCH_FACTOR*tree1.CrownVolume.tail->d3;
            if (dsecl < FLT_EPSILON) {
               dsecl				 = bsecl;
            }
            dry_crown_volume	+= tree1.CrownVolume.tail->volume;
            /**********************************/
            /* Stem contribution to dry crown */
            /**********************************/
            if (pT->Stem.head != NULL_PTR2BRANCH_LIST) {
               pB                = tree1.Stem.head;
               trunk_length      = pB->l;
               if (bsecl < dsecl) {
                  n_segments     = (int) (trunk_length / bsecl);
               } else {
                  n_segments		= (int) (trunk_length / dsecl);
               }
               if (n_segments < POLSARPROSIM_MIN_STEM_SEG_NUM) {
                  n_segments	= POLSARPROSIM_MIN_STEM_SEG_NUM;
               }
               for (i_seg=0; i_seg<n_segments; i_seg++) {
                  rtn_value	= Cylinder_from_Branch (&Cyl1, pB, i_seg, n_segments);
                  if (Cyl1.base.x[2] > tree1.CrownVolume.tail->base.x[2]) {
                     if (Cyl1.base.x[2] < tree1.CrownVolume.tail->base.x[2]+tree1.CrownVolume.tail->d3) {
                        Alpha                = CylinderPolarisability (&Cyl1, &kix, &kiy, &kiz, &Ytable, &Jtable);
                        Alpha_Dry_Sum        = c33Matrix_sum (Alpha_Dry_Sum, Alpha);
                        dry_volume           = DPI_RAD*Cyl1.radius*Cyl1.radius*Cyl1.length;
                        crown_dry_vol_frac   += dry_volume;
                        dry_count            += 1.0;
                     }
                  }
               }
            }
            /*************************************/
            /* Primary contribution to dry crown */
            /*************************************/
            if(pT->Dry.head != NULL_PTR2BRANCH_LIST) { 
               pB	= tree1.Dry.head;
               for (iBranch=0L; iBranch < tree1.Dry.n; iBranch++) {
                  dry_length		= pB->l;
                  n_segments		= (int) (dry_length / bsecl);
                  if (n_segments < 1) {
                     n_segments	= 1;
                  }
                  for (i_seg=0; i_seg<n_segments; i_seg++) {
                     rtn_value				= Cylinder_from_Branch (&Cyl1, pB, i_seg, n_segments);
                     Alpha                = CylinderPolarisability (&Cyl1, &kix, &kiy, &kiz, &Ytable, &Jtable);
                     Alpha_Dry_Sum			= c33Matrix_sum (Alpha_Dry_Sum, Alpha);
                     dry_volume           = DPI_RAD*Cyl1.radius*Cyl1.radius*Cyl1.length;
                     crown_dry_vol_frac	+= dry_volume;
                     dry_count				+= 1.0;
                  }
                  pB	= pB->next;
               }
            }
         }
         
         /************************************/
         /* Living crown, wich always exists */
         /************************************/
         crown_volume		+= tree1.CrownVolume.head->volume;
         
         /* loop through the stem sections */
         if (pT->Stem.head != NULL_PTR2BRANCH_LIST){ 
            pB				 = tree1.Stem.head;
            trunk_length		 = pB->l;
            if (bsecl < dsecl) {
               n_segments			 = (int) (trunk_length / bsecl);
            } else {
               n_segments			 = (int) (trunk_length / dsecl);
            }
            if (n_segments < POLSARPROSIM_MIN_STEM_SEG_NUM) {
               n_segments	= POLSARPROSIM_MIN_STEM_SEG_NUM;
            }
            for (i_seg=0; i_seg<n_segments; i_seg++) {
               rtn_value	= Cylinder_from_Branch (&Cyl1, pB, i_seg, n_segments);
               if (Cyl1.base.x[2] > tree1.CrownVolume.head->base.x[2]) {
                  Alpha                   = CylinderPolarisability (&Cyl1, &kix, &kiy, &kiz, &Ytable, &Jtable);
                  Alpha_Trunk_Sum         = c33Matrix_sum (Alpha_Trunk_Sum, Alpha);
                  trunk_volume            = DPI_RAD*Cyl1.radius*Cyl1.radius*Cyl1.length;
                  crown_trunk_vol_frac    += trunk_volume;
                  trunk_count             += 1.0;
               }
            }
         }
         
         /* loop through primary branches */
         if (pT->Primary.head != NULL_PTR2BRANCH_LIST){   
            pB	= tree1.Primary.head;
            for (iBranch=0L; iBranch < tree1.Primary.n; iBranch++) {
               primary_length	= pB->l;
               n_segments		= (int) (primary_length / bsecl);
               if (n_segments < 1) {
                  n_segments	= 1;
               }
               for (i_seg=0; i_seg<n_segments; i_seg++) {
                  rtn_value               = Cylinder_from_Branch (&Cyl1, pB, i_seg, n_segments);
                  Alpha                   = CylinderPolarisability (&Cyl1, &kix, &kiy, &kiz, &Ytable, &Jtable);
                  Alpha_Primary_Sum       = c33Matrix_sum (Alpha_Primary_Sum, Alpha);
                  primary_volume          = DPI_RAD*Cyl1.radius*Cyl1.radius*Cyl1.length;
                  crown_primary_vol_frac	+= primary_volume;
                  primary_count           += 1.0;
               }
               pB	= pB->next;
            }
         }
         
         /* loop through secondary branches */
         if (pT->Secondary.head != NULL_PTR2BRANCH_LIST){ 
            pB	= tree1.Secondary.head;
            for (iBranch=0L; iBranch < tree1.Secondary.n; iBranch++) {
               secondary_length	= pB->l;
               n_segments		= (int) (secondary_length / bsecl);
               if (n_segments < 1) {
                  n_segments	= 1;
               }
               for (i_seg=0; i_seg<n_segments; i_seg++) {
                  rtn_value                  = Cylinder_from_Branch (&Cyl1, pB, i_seg, n_segments);
                  Alpha                      = CylinderPolarisability (&Cyl1, &kix, &kiy, &kiz, &Ytable, &Jtable);
                  Alpha_Secondary_Sum        = c33Matrix_sum (Alpha_Secondary_Sum, Alpha);
                  secondary_volume           = DPI_RAD*Cyl1.radius*Cyl1.radius*Cyl1.length;
                  crown_secondary_vol_frac	+= secondary_volume;
                  secondary_count            += 1.0;
               }
               pB	= pB->next;
            }
         }
         
         /* loop through tertiary branches */
         if(pT->Tertiary.head != NULL_PTR2BRANCH_LIST) {
            pB = tree1.Tertiary.head;
            number_of_tertiaries = tree1.Tertiary.n;
            for (iBranch=0L; iBranch < number_of_tertiaries; iBranch++) {
               tertiary_length	= pB->l;
               n_segments        = (int) (tertiary_length / bsecl);
               if (n_segments < 1) {
                  n_segments	= 1;
               }
               for (i_seg=0; i_seg<n_segments; i_seg++) {
                  rtn_value                  = Cylinder_from_Branch (&Cyl1, pB, i_seg, n_segments);
                  Alpha                      = CylinderPolarisability (&Cyl1, &kix, &kiy, &kiz, &Ytable, &Jtable);
                  Alpha_Tertiary_Sum         = c33Matrix_sum (Alpha_Tertiary_Sum, Alpha);
                  tertiary_volume            = DPI_RAD*Cyl1.radius*Cyl1.radius*Cyl1.length;
                  crown_tertiary_vol_frac   += tertiary_volume;
                  tertiary_count            += 1.0;
               }
               pB	= pB->next;
            }
         } 
         
         /* loop through leaves */
         if(pT->Foliage.head != NULL_PTR2LEAF_LIST) {
            pL = tree1.Foliage.head;
            number_of_leaves = tree1.Foliage.n;
            for (iLeaf=0L; iLeaf < number_of_leaves; iLeaf++){
               Leaf_Depolarization_Factors (pL, &leafL1, &leafL2, &leafL3);
               leaf_moisture           = pL->moisture; //Leaf_Moisture	(pPR->species, pPR);
               leaf_permittivity       = pL->permittivity; //vegetation_permittivity	(leaf_moisture, pPR->frequency);
               leaf_epsm1              = xy_complex (leaf_permittivity.x-1.0, leaf_permittivity.y);
               Alpha                   = Leaf_Polarisability (pL, leafL1, leafL2, leafL3);
               Alpha_Leaf_Sum          = c33Matrix_sum (Alpha_Leaf_Sum, c33Matrix_Complex_product (Alpha, leaf_epsm1));
               leaf_volume             = Leaf_Volume (pL);
               crown_foliage_vol_frac  += leaf_volume;
               leaf_count              += 1.0;
               pL = pL->next; 
            }
         }
         
      } /* end for loop on trees */
      
      
      if(dry_count > 0){ /* Use dry_count to avoid using pPR->species as a check --RAedit  */
         crown_dry_vol_frac         /= dry_crown_volume;
         dry_number_density         = dry_count / dry_crown_volume;
         scale_factor               = xy_complex (dry_number_density/dry_count, 0.0);
         CrownDry_EpsEff            = c33Matrix_sum (CrownDry_EpsEff, c33Matrix_Complex_product (Alpha_Dry_Sum, scale_factor));
      } else {
         crown_dry_vol_frac         = 0.0;
         dry_number_density         = 0.0;
         dry_count                  = 0.0;
         dry_crown_volume           = 0.0;
      }
      if(trunk_count > 0) {
         crown_trunk_vol_frac       /= crown_volume;
         trunk_number_density       = trunk_count / crown_volume;
         scale_factor               = xy_complex (trunk_number_density/trunk_count, 0.0);
         CrownTrunk_EpsEff          = c33Matrix_sum (CrownTrunk_EpsEff, c33Matrix_Complex_product (Alpha_Trunk_Sum, scale_factor));
      }
      if(primary_count > 0) {   
         crown_primary_vol_frac     /= crown_volume;
         primary_number_density     = primary_count / crown_volume;
         scale_factor               = xy_complex (primary_number_density/primary_count, 0.0);
         CrownPrimary_EpsEff        = c33Matrix_sum (CrownPrimary_EpsEff, c33Matrix_Complex_product (Alpha_Primary_Sum, scale_factor));
      }
      if(secondary_count > 0) {
         crown_secondary_vol_frac	/= crown_volume;
         secondary_number_density   = secondary_count / crown_volume;
         scale_factor               = xy_complex (secondary_number_density/secondary_count, 0.0);
         CrownSecondary_EpsEff      = c33Matrix_sum (CrownSecondary_EpsEff, c33Matrix_Complex_product (Alpha_Secondary_Sum, scale_factor));
      }
      if(tertiary_count > 0) {
         crown_tertiary_vol_frac    /= crown_volume;
         tertiary_number_density    = tertiary_count / crown_volume;
         scale_factor               = xy_complex (tertiary_number_density/tertiary_count, 0.0);
         CrownTert_EpsEff           = c33Matrix_sum (CrownTert_EpsEff, c33Matrix_Complex_product (Alpha_Tertiary_Sum, scale_factor));
      }
      if(leaf_count > 0) {
         crown_foliage_vol_frac    /= crown_volume;
         foliage_number_density     = leaf_count / crown_volume;
         /* I'm not quite sure what the right scale factor should be --RA */
         //scale_factor               = xy_complex (foliage_number_density/leaf_count, 0.0);
         //scale_factor               = xy_complex (crown_foliage_vol_frac, 0.0);
         scale_factor               = xy_complex (Leaf_Volume_Fraction(ispecies, pPR)/leaf_count, 0.0);
         CrownTert_EpsEff           = c33Matrix_sum (CrownTert_EpsEff, c33Matrix_Complex_product (Alpha_Leaf_Sum, scale_factor));
      }
      /******************************************/
      /* Enforce isotropy in leaves and foliage */
      /******************************************/
      e                          = complex_add (complex_add (CrownTert_EpsEff.m[0], CrownTert_EpsEff.m[4]), CrownTert_EpsEff.m[8]);
      e                          = complex_rmul (e, 1.0/3.0);
      CrownTert_EpsEff           = Zero_c33Matrix ();
      CrownTert_EpsEff.m[0]      = e;
      CrownTert_EpsEff.m[4]      = e;
      CrownTert_EpsEff.m[8]      = e;
      
      /*****************************/
      /* Output results to logfile */
      /*****************************/
      fprintf (pPR->pLogFile, "\n");
      fprintf (pPR->pLogFile, "Crown trunk volume fraction\t\t= %10.3e\n", crown_trunk_vol_frac);
      fprintf (pPR->pLogFile, "Crown trunk segment number\t\t= %10.3e\n", trunk_count);
      fprintf (pPR->pLogFile, "Crown volume\t\t\t\t= %10.3e m^3\n", crown_volume);
      fprintf (pPR->pLogFile, "Crown trunk segment number density\t= %10.3e\n", trunk_number_density);
      fprintf (pPR->pLogFile, "Crown trunk effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownTrunk_EpsEff.m[0].x, fabs(CrownTrunk_EpsEff.m[0].y));
      fprintf (pPR->pLogFile, "Crown trunk effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownTrunk_EpsEff.m[4].x, fabs(CrownTrunk_EpsEff.m[4].y));
      fprintf (pPR->pLogFile, "Crown trunk effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownTrunk_EpsEff.m[8].x, fabs(CrownTrunk_EpsEff.m[8].y));
      fprintf (pPR->pLogFile, "\n");
      fprintf (pPR->pLogFile, "\n");
      fprintf (pPR->pLogFile, "Crown primary volume fraction\t\t= %10.3e\n", crown_primary_vol_frac);
      fprintf (pPR->pLogFile, "Crown primary segment number\t\t= %10.3e\n", primary_count);
      fprintf (pPR->pLogFile, "Crown volume\t\t\t\t= %10.3e m^3\n", crown_volume);
      fprintf (pPR->pLogFile, "Crown primary segment number density\t= %10.3e\n", primary_number_density);
      fprintf (pPR->pLogFile, "Crown primary effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownPrimary_EpsEff.m[0].x, fabs(CrownPrimary_EpsEff.m[0].y));
      fprintf (pPR->pLogFile, "Crown primary effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownPrimary_EpsEff.m[4].x, fabs(CrownPrimary_EpsEff.m[4].y));
      fprintf (pPR->pLogFile, "Crown primary effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownPrimary_EpsEff.m[8].x, fabs(CrownPrimary_EpsEff.m[8].y));
      fprintf (pPR->pLogFile, "\n");
      fprintf (pPR->pLogFile, "\n");
      fprintf (pPR->pLogFile, "Crown secondary volume fraction\t\t= %10.3e\n", crown_secondary_vol_frac);
      fprintf (pPR->pLogFile, "Crown secondary segment number\t\t= %10.3e\n", secondary_count);
      fprintf (pPR->pLogFile, "Crown volume\t\t\t\t= %10.3e m^3\n", crown_volume);
      fprintf (pPR->pLogFile, "Crown secondary segment number density\t= %10.3e\n", secondary_number_density);
      fprintf (pPR->pLogFile, "Crown secondary effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownSecondary_EpsEff.m[0].x, fabs(CrownSecondary_EpsEff.m[0].y));
      fprintf (pPR->pLogFile, "Crown secondary effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownSecondary_EpsEff.m[4].x, fabs(CrownSecondary_EpsEff.m[4].y));
      fprintf (pPR->pLogFile, "Crown secondary effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownSecondary_EpsEff.m[8].x, fabs(CrownSecondary_EpsEff.m[8].y));
      fprintf (pPR->pLogFile, "\n");
      fprintf (pPR->pLogFile, "\n");
      fprintf (pPR->pLogFile, "Crown tertiary volume fraction\t\t= %10.3e\n", crown_tertiary_vol_frac);
      fprintf (pPR->pLogFile, "Crown tertiary segment number\t\t= %10.3e\n", tertiary_count);
      fprintf (pPR->pLogFile, "Crown volume\t\t\t\t= %10.3e m^3\n", crown_volume);
      fprintf (pPR->pLogFile, "Crown tertiary effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownTert_EpsEff.m[0].x, fabs(CrownTert_EpsEff.m[0].y));
      fprintf (pPR->pLogFile, "Crown tertiary effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownTert_EpsEff.m[4].x, fabs(CrownTert_EpsEff.m[4].y));
      fprintf (pPR->pLogFile, "Crown tertiary effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownTert_EpsEff.m[8].x, fabs(CrownTert_EpsEff.m[8].y));
      fprintf (pPR->pLogFile, "\n");
      fprintf (pPR->pLogFile, "\n");
      fprintf (pPR->pLogFile, "Crown dry volume fraction\t\t= %10.3e\n", crown_dry_vol_frac);
      fprintf (pPR->pLogFile, "Crown dry segment number\t\t= %10.3e\n", dry_count);
      fprintf (pPR->pLogFile, "Crown dry volume\t\t\t= %10.3e m^3\n", dry_crown_volume);
      fprintf (pPR->pLogFile, "Crown dry segment number density\t= %10.3e\n", dry_number_density);
      fprintf (pPR->pLogFile, "Crown dry effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownDry_EpsEff.m[0].x, fabs(CrownDry_EpsEff.m[0].y));
      fprintf (pPR->pLogFile, "Crown dry effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownDry_EpsEff.m[4].x, fabs(CrownDry_EpsEff.m[4].y));
      fprintf (pPR->pLogFile, "Crown dry effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownDry_EpsEff.m[8].x, fabs(CrownDry_EpsEff.m[8].y));
      fprintf (pPR->pLogFile, "\n");
      
      /******************************************/
      /* Combine contributions for living crown */
      /******************************************/
      CrownLiving_EpsEff         = c33Matrix_sum (CrownLiving_EpsEff, c33Matrix_difference (CrownTrunk_EpsEff, Idem_c33Matrix ()));
      CrownLiving_EpsEff         = c33Matrix_sum (CrownLiving_EpsEff, c33Matrix_difference (CrownPrimary_EpsEff, Idem_c33Matrix ()));
      CrownLiving_EpsEff         = c33Matrix_sum (CrownLiving_EpsEff, c33Matrix_difference (CrownSecondary_EpsEff, Idem_c33Matrix ()));
      CrownLiving_EpsEff         = c33Matrix_sum (CrownLiving_EpsEff, c33Matrix_difference (CrownTert_EpsEff, Idem_c33Matrix ()));
      /************************************************/
      /* Rationalise effective permittivity estimates */
      /* Calculate and store effective wavenumbers.   */
      /************************************************/
      e                          = complex_rmul (complex_add (CrownDry_EpsEff.m[0], CrownDry_EpsEff.m[4]), 0.5);
      ez                         = CrownDry_EpsEff.m[8];
      CrownDry_EpsEff            = Idem_c33Matrix ();
      CrownDry_EpsEff.m[0]       = e;
      CrownDry_EpsEff.m[4]       = e;
      CrownDry_EpsEff.m[8]       = ez;
      pPR->e11_dry               = e;
      pPR->e33_dry               = ez;
      kro2                       = pPR->k0*sin(pPR->incidence_angle[0]);
      kro2                       *= kro2;
      ko2                        = complex_rmul (e, pPR->k0*pPR->k0);
      koz2                       = xy_complex (ko2.x-kro2, ko2.y);
      koz                        = complex_sqrt (koz2);
      ke2                        = complex_rmul (ez, pPR->k0*pPR->k0);
      kez2                       = xy_complex (ke2.x-kro2, ke2.y);
      kez2                       = complex_mul (kez2, complex_div (e ,ez));
      kez                        = complex_sqrt(kez2);
      ke2                        = complex_add (kez2, xy_complex (kro2, 0.0));
      pPR->ko2_dry               = ko2;
      pPR->koz2_dry              = koz2;
      pPR->koz_dry[ispecies]     = koz; // used in Attenuation_map
      pPR->ke2_dry               = ke2;
      pPR->kez2_dry              = kez2;
      pPR->kez_dry[ispecies]     = kez; // used in Attenuation_map
      e                          = complex_rmul (complex_add (CrownLiving_EpsEff.m[0], CrownLiving_EpsEff.m[4]), 0.5);
      ez                         = CrownLiving_EpsEff.m[8];
      CrownLiving_EpsEff         = Idem_c33Matrix ();
      CrownLiving_EpsEff.m[0]    = e;
      CrownLiving_EpsEff.m[4]    = e;
      CrownLiving_EpsEff.m[8]    = ez;
      pPR->e11_living            = e;
      pPR->e33_living            = ez;
      kro2                       = pPR->k0*sin(pPR->incidence_angle[0]);
      kro2                       *= kro2;
      ko2                        = complex_rmul (e, pPR->k0*pPR->k0);
      koz2                       = xy_complex (ko2.x-kro2, ko2.y);
      koz                        = complex_sqrt (koz2);
      ke2                        = complex_rmul (ez, pPR->k0*pPR->k0);
      kez2                       = xy_complex (ke2.x-kro2, ke2.y);
      kez2                       = complex_mul (kez2, complex_div (e ,ez));
      kez                        = complex_sqrt(kez2);
      ke2                        = complex_add (kez2, xy_complex (kro2, 0.0));
      pPR->ko2_living            = ko2;
      pPR->koz2_living           = koz2;
      pPR->koz_living[ispecies]  = koz; // used in Attenuation_map
      pPR->ke2_living            = ke2;
      pPR->kez2_living           = kez2;
      pPR->kez_living[ispecies]  = kez; // used in Attenuation_map
      
      fprintf (pPR->pLogFile, "\n");
      fprintf (pPR->pLogFile, "Consolidated effective permittivities:");
      fprintf (pPR->pLogFile, "\n");
      fprintf (pPR->pLogFile, "\n");
      fprintf (pPR->pLogFile, "Crown dry effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownDry_EpsEff.m[0].x, fabs(CrownDry_EpsEff.m[0].y));
      fprintf (pPR->pLogFile, "Crown dry effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownDry_EpsEff.m[4].x, fabs(CrownDry_EpsEff.m[4].y));
      fprintf (pPR->pLogFile, "Crown dry effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownDry_EpsEff.m[8].x, fabs(CrownDry_EpsEff.m[8].y));
      fprintf (pPR->pLogFile, "\n");
      fprintf (pPR->pLogFile, "\n");
      fprintf (pPR->pLogFile, "Crown living effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownLiving_EpsEff.m[0].x, fabs(CrownLiving_EpsEff.m[0].y));
      fprintf (pPR->pLogFile, "Crown living effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownLiving_EpsEff.m[4].x, fabs(CrownLiving_EpsEff.m[4].y));
      fprintf (pPR->pLogFile, "Crown living effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownLiving_EpsEff.m[8].x, fabs(CrownLiving_EpsEff.m[8].y));
      fprintf (pPR->pLogFile, "\n");
   }
   
   /*********************************************************/
   /* Isotropic short vegetation layer: uses GRG model only */
   /*********************************************************/
   
#ifdef VERBOSE_POLSARPROSIM
   printf ("\n");
   printf ("Calculating short vegetation effective permittivity  ... \n");
   printf ("\n");
#endif
   fprintf (pPR->pLogFile, "Calculating short vegetation effective permittivity  ... \n");
   fflush  (pPR->pLogFile);
   theta				= 0.0;
   phi				= 0.0;
   Alpha                      = Zero_c33Matrix ();
   Alpha_Stem_Sum             = Zero_c33Matrix ();
   Alpha_Leaf_Sum             = Zero_c33Matrix ();
   /********************************************/
   /* Realise a stem (needle) to find L values */
   /********************************************/
   stem_species            = POLSARPROSIM_PINE_NEEDLE;
   stem_d1                 = POLSARPROSIM_SHORTV_STEM_LENGTH;
   stem_d2                 = POLSARPROSIM_SHORTV_STEM_RADIUS;
   stem_d3                 = POLSARPROSIM_SHORTV_STEM_RADIUS;
   stem_moisture           = Leaf_Moisture	(pPR->species, pPR);
   stem_permittivity       = vegetation_permittivity (stem_moisture, pPR->frequency);
   Assign_Leaf (&leaf1, stem_species, stem_d1, stem_d2, stem_d3, theta, phi, stem_moisture, stem_permittivity, stem_centre);
   Leaf_Depolarization_Factors (&leaf1, &stemL1, &stemL2, &stemL3);
   pPR->ShortVegi_stemL1	= stemL1;
   pPR->ShortVegi_stemL2	= stemL2;
   pPR->ShortVegi_stemL3	= stemL3;
   /***********************************/
   /* Realise a leaf to find L values */
   /***********************************/
   leaf_species            = POLSARPROSIM_DECIDUOUS_LEAF;
   leaf_d1                 = POLSARPROSIM_SHORTV_LEAF_LENGTH;
   leaf_d2                 = POLSARPROSIM_SHORTV_LEAF_WIDTH;
   leaf_d3                 = POLSARPROSIM_SHORTV_LEAF_THICKNESS;
   leaf_moisture           = Leaf_Moisture	(pPR->species, pPR);
   leaf_permittivity       = vegetation_permittivity (leaf_moisture, pPR->frequency);
   Assign_Leaf	(&leaf1, leaf_species, leaf_d1, leaf_d2, leaf_d3, theta, phi, leaf_moisture, leaf_permittivity, leaf_centre);
   Leaf_Depolarization_Factors (&leaf1, &leafL1, &leafL2, &leafL3);
   pPR->ShortVegi_leafL1	= leafL1;
   pPR->ShortVegi_leafL2	= leafL2;
   pPR->ShortVegi_leafL3	= leafL3;
   /****************************************************/
   /* Average polarisabilities over orientation angles */
   /****************************************************/
   Ntheta                  = POLSARPROSIM_SHORT_VEGI_NTHETA;
   Nphi                    = POLSARPROSIM_SHORT_VEGI_NPHI;
   d_costheta              = 2.0/Ntheta;
   d_phi                   = 2.0*DPI_RAD/Nphi;
   for (i_costheta = 0; i_costheta < Ntheta; i_costheta++) {
      costheta	= i_costheta*d_costheta + d_costheta/2.0 - 1.0;
      theta		= acos(costheta);
      for (i_phi = 0; i_phi < Nphi; i_phi++) {
         phi	= i_phi*d_phi + d_phi/2.0;
         /**********************/
         /* Stem contribution  */
         /**********************/
         stem_moisture		= Leaf_Moisture (pPR->species, pPR);
         stem_permittivity	= vegetation_permittivity (stem_moisture, pPR->frequency);
         stem_epsm1			= xy_complex (stem_permittivity.x-1.0, stem_permittivity.y);
         Assign_Leaf (&leaf1, stem_species, stem_d1, stem_d2, stem_d3, theta, phi, stem_moisture, stem_permittivity, stem_centre);
         Alpha             = Leaf_Polarisability (&leaf1, stemL1, stemL2, stemL3);
         Alpha_Stem_Sum		= c33Matrix_sum (Alpha_Stem_Sum, c33Matrix_Complex_product (Alpha, stem_epsm1));
         /*********************/
         /* Leaf contribution */
         /*********************/
         leaf_moisture		= Leaf_Moisture (pPR->species, pPR);
         leaf_permittivity	= vegetation_permittivity (leaf_moisture, pPR->frequency);
         leaf_epsm1			= xy_complex (leaf_permittivity.x-1.0, leaf_permittivity.y);
         Assign_Leaf (&leaf1, leaf_species, leaf_d1, leaf_d2, leaf_d3, theta, phi, leaf_moisture, leaf_permittivity, leaf_centre);
         Alpha             = Leaf_Polarisability (&leaf1, leafL1, leafL2, leafL3);
         Alpha_Leaf_Sum		= c33Matrix_sum (Alpha_Leaf_Sum, c33Matrix_Complex_product (Alpha, leaf_epsm1));
      }
   }
   scale_factor            = xy_complex (pPR->shrt_vegi_stem_vol_frac/(Ntheta*Nphi), 0.0);
   ShortVegi_EpsEff        = c33Matrix_sum (ShortVegi_EpsEff, c33Matrix_Complex_product (Alpha_Stem_Sum, scale_factor));
   scale_factor            = xy_complex (pPR->shrt_vegi_leaf_vol_frac/(Ntheta*Nphi), 0.0);
   ShortVegi_EpsEff        = c33Matrix_sum (ShortVegi_EpsEff, c33Matrix_Complex_product (Alpha_Leaf_Sum, scale_factor));
   /******************************************************/
   /* Ensure perfect isotropy with this minor correction */
   /******************************************************/
   e                       = complex_add (complex_add (ShortVegi_EpsEff.m[0], ShortVegi_EpsEff.m[4]), ShortVegi_EpsEff.m[8]);
   e                       = complex_rmul (e, 1.0/3.0);
   ShortVegi_EpsEff        = Zero_c33Matrix ();
   ShortVegi_EpsEff.m[0]	= e;
   ShortVegi_EpsEff.m[4]	= e;
   ShortVegi_EpsEff.m[8]	= e;
   /*****************************/
   /* Output results to logfile */
   /*****************************/
   fprintf (pPR->pLogFile, "\n");
   fprintf (pPR->pLogFile, "Short vegetation effective permittivity = %10.3e + j %10.3e  ... \n", ShortVegi_EpsEff.m[0].x, fabs(ShortVegi_EpsEff.m[0].y));
   fprintf (pPR->pLogFile, "Short vegetation effective permittivity = %10.3e + j %10.3e  ... \n", ShortVegi_EpsEff.m[4].x, fabs(ShortVegi_EpsEff.m[4].y));
   fprintf (pPR->pLogFile, "Short vegetation effective permittivity = %10.3e + j %10.3e  ... \n", ShortVegi_EpsEff.m[8].x, fabs(ShortVegi_EpsEff.m[8].y));
   fprintf (pPR->pLogFile, "\n");
   
   e                       = complex_rmul (complex_add (ShortVegi_EpsEff.m[0], ShortVegi_EpsEff.m[4]), 0.5);
   ez                      = ShortVegi_EpsEff.m[8];
   ShortVegi_EpsEff        = Idem_c33Matrix ();
   ShortVegi_EpsEff.m[0]	= e;
   ShortVegi_EpsEff.m[4]	= e;
   ShortVegi_EpsEff.m[8]	= ez;
   pPR->e11_short          = e;
   pPR->e33_short          = ez;
   kro2                    = pPR->k0*sin(pPR->incidence_angle[0]);
   kro2                    *= kro2;
   ko2                     = complex_rmul (e, pPR->k0*pPR->k0);
   koz2                    = xy_complex (ko2.x-kro2, ko2.y);
   koz                     = complex_sqrt (koz2);
   ke2                     = complex_rmul (ez, pPR->k0*pPR->k0);
   kez2                    = xy_complex (ke2.x-kro2, ke2.y);
   kez2                    = complex_mul (kez2, complex_div (e ,ez));
   kez                     = complex_sqrt(kez2);
   ke2                     = complex_add (kez2, xy_complex (kro2, 0.0));
   pPR->ko2_short          = ko2;
   pPR->koz2_short         = koz2;
   pPR->koz_short          = koz;
   pPR->ke2_short          = ke2;
   pPR->kez2_short         = kez2;
   pPR->kez_short          = kez;
   
   /***********/
   /* Tidy up */
   /***********/
   Destroy_Tree		(&tree1);
   Destroy_Leaf		(&leaf1);
   Destroy_Cylinder	(&Cyl1);
   rtn_value	= Delete_Jnlookup		(&Jtable);
   rtn_value	= Delete_Ynlookup		(&Ytable);
   /******************************************/
   /* Report call if running in VERBOSE mode */
   /******************************************/
#ifdef VERBOSE_POLSARPROSIM
   printf ("\n");
   printf ("... Returning from call to Effective_Permittivities\n");
   printf ("\n");
#endif
   fprintf (pPR->pLogFile, "... Returning from call to Effective_Permittivities\n\n");
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
   return;
}
/***************************************/
/* Computes the polarizability tensor  */
/* 'Alpha' for components of a tree    */
/* needed for an multi-processor ver.  */
/* of the Effective_Permittivity() fn. */
/***************************************/
void     *Compute_Alphas   (void *threadarg) 
{
   
   int                  itree;
   EffPerm_Thread_Arg   *pTA;
   PolSARproSim_Record  *pPR;
   Tree                 tree1;
   Tree                 *pT;
   double               bsecl;
   double               dsecl;
   double               crown_trunk_vol_frac       = 0.0;
   double               crown_primary_vol_frac		= 0.0;
   double               crown_secondary_vol_frac	= 0.0;
   double               crown_tertiary_vol_frac    = 0.0;
   double               crown_foliage_vol_frac     = 0.0;
   double               crown_dry_vol_frac			= 0.0;
   double               crown_volume, dry_crown_volume;
   double               trunk_length, trunk_count, trunk_volume;
   double               primary_length, primary_count, primary_volume;
   double               secondary_length, secondary_count, secondary_volume;
   double               dry_length, dry_count, dry_volume;
   double               tertiary_length, tertiary_count, tertiary_volume;
   int                  number_of_tertiaries;
   double               leafL1, leafL2, leafL3;
   double               leaf_moisture;
   Complex              leaf_permittivity, leaf_epsm1;
   int                  number_of_leaves;
   double               leaf_volume, leaf_count;
   int                  n_segments, i_seg;
   int                  rtn_value;
   Cylinder             Cyl1;
   Branch               *pB;
   long                 iBranch;
   double               thetai, phii, thetas, phis;
   d3Vector             ki, kix, ksx, kiy, ksy, kiz, ksz;
   Yn_Lookup            Ytable;
   Jn_Lookup            Jtable;
   Leaf                 leaf1;
   Leaf                 *pL;
   long                 iLeaf;
   
   
   c33Matrix            Alpha_Trunk_Sum				= Zero_c33Matrix ();
   c33Matrix            Alpha_Primary_Sum          = Zero_c33Matrix ();
   c33Matrix            Alpha_Secondary_Sum			= Zero_c33Matrix ();
   c33Matrix            Alpha_Tertiary_Sum         = Zero_c33Matrix ();
   c33Matrix            Alpha_Leaf_Sum             = Zero_c33Matrix ();
   c33Matrix            Alpha_Dry_Sum              = Zero_c33Matrix ();
   c33Matrix            Alpha                      = Zero_c33Matrix ();
   c33Matrix            c33Zero                    = Zero_c33Matrix ();
   
   /* do some assignments */
   pTA         = (EffPerm_Thread_Arg *)threadarg;
   itree       = pTA->itree;
   pPR         = pTA->pPR;  // address to Master_Record   
   
   /**************/
   /* Initialise */
   /**************/
   Create_Leaf       (&leaf1);
   Create_Tree       (&tree1);
   Create_Cylinder	(&Cyl1);
   /*********************************************/
   /* Initialise Bessel function look-up tables */
   /*********************************************/
   rtn_value	= Initialise_Standard_Jnlookup (&Jtable);
   rtn_value	= Initialise_Standard_Ynlookup (&Ytable);
   /**************************/
   /* Establish wave vectors */
   /**************************/
   ki			= Polar_Assign_d3Vector (pPR->k0, pPR->incidence_angle[0], 0.0);
   thetai	= 2.0*atan(1.0);
   phii		= 0.0;
   thetas	= thetai;
   phis		= phii;
   kix		= Polar_Assign_d3Vector (pPR->k0, thetai, phii);
   ksx		= Polar_Assign_d3Vector (pPR->k0, thetas, phis);
   thetai	= 2.0*atan(1.0);
   phii		= 2.0*atan(1.0);
   thetas	= thetai;
   phis		= phii;
   kiy		= Polar_Assign_d3Vector (pPR->k0, thetai, phii);
   ksy		= Polar_Assign_d3Vector (pPR->k0, thetas, phis);
   thetai	= 0.0;
   phii		= 0.0;
   thetas	= thetai;
   phis		= phii;
   kiz		= Polar_Assign_d3Vector (pPR->k0, thetai, phii);
   ksz		= Polar_Assign_d3Vector (pPR->k0, thetas, phis);
   /* branch length control */
   bsecl       =	POLSARPROSIM_SAR_BRANCH_FACTOR*(pPR->azimuth_resolution + pPR->slant_range_resolution);
   
   /* zero out the counters */
   trunk_count                = 0.0;
   primary_count              = 0.0;
   secondary_count            = 0.0;
   tertiary_count             = 0.0;
   leaf_count                 = 0.0;
   dry_count                  = 0.0;
   crown_volume               = 0.0;
   dry_crown_volume           = 0.0;
   /* zero out the volume fractions */
   crown_trunk_vol_frac       = 0.0;
   crown_primary_vol_frac		= 0.0;
   crown_secondary_vol_frac	= 0.0;
   crown_tertiary_vol_frac    = 0.0;
   crown_dry_vol_frac			= 0.0;
   
   Realise_Tree(&tree1, itree, pPR);
   pT = &tree1;
   
   /***************************/
   /* Dry crown contribution  */
   /***************************/
   /* if dry crown exists, then estimate dry parameters */
   if(pT->CrownVolume.tail != NULL_PTR2CROWN) {
      dsecl				 = POLSARPROSIM_SAR_BRANCH_FACTOR*tree1.CrownVolume.tail->d3;
      if (dsecl < FLT_EPSILON) {
         dsecl				 = bsecl;
      }
      dry_crown_volume	+= tree1.CrownVolume.tail->volume;
      /**********************************/
      /* Stem contribution to dry crown */
      /**********************************/
      if (pT->Stem.head != NULL_PTR2BRANCH_LIST) {
         pB                = tree1.Stem.head;
         trunk_length      = pB->l;
         if (bsecl < dsecl) {
            n_segments     = (int) (trunk_length / bsecl);
         } else {
            n_segments		= (int) (trunk_length / dsecl);
         }
         if (n_segments < POLSARPROSIM_MIN_STEM_SEG_NUM) {
            n_segments	= POLSARPROSIM_MIN_STEM_SEG_NUM;
         }
         for (i_seg=0; i_seg<n_segments; i_seg++) {
            rtn_value	= Cylinder_from_Branch (&Cyl1, pB, i_seg, n_segments);
            if (Cyl1.base.x[2] > tree1.CrownVolume.tail->base.x[2]) {
               if (Cyl1.base.x[2] < tree1.CrownVolume.tail->base.x[2]+tree1.CrownVolume.tail->d3) {
                  Alpha                = CylinderPolarisability (&Cyl1, &kix, &kiy, &kiz, &Ytable, &Jtable);
                  Alpha_Dry_Sum        = c33Matrix_sum (Alpha_Dry_Sum, Alpha);
                  dry_volume           = DPI_RAD*Cyl1.radius*Cyl1.radius*Cyl1.length;
                  crown_dry_vol_frac   += dry_volume;
                  dry_count            += 1.0;
               }
            }
         }
      }
      /*************************************/
      /* Primary contribution to dry crown */
      /*************************************/
      if(pT->Dry.head != NULL_PTR2BRANCH_LIST) { 
         pB	= tree1.Dry.head;
         for (iBranch=0L; iBranch < tree1.Dry.n; iBranch++) {
            dry_length		= pB->l;
            n_segments		= (int) (dry_length / bsecl);
            if (n_segments < 1) {
               n_segments	= 1;
            }
            for (i_seg=0; i_seg<n_segments; i_seg++) {
               rtn_value				= Cylinder_from_Branch (&Cyl1, pB, i_seg, n_segments);
               Alpha                = CylinderPolarisability (&Cyl1, &kix, &kiy, &kiz, &Ytable, &Jtable);
               Alpha_Dry_Sum			= c33Matrix_sum (Alpha_Dry_Sum, Alpha);
               dry_volume           = DPI_RAD*Cyl1.radius*Cyl1.radius*Cyl1.length;
               crown_dry_vol_frac	+= dry_volume;
               dry_count				+= 1.0;
            }
            pB	= pB->next;
         }
      }
   }
   
   /************************************/
   /* Living crown, wich always exists */
   /************************************/
   crown_volume		+= tree1.CrownVolume.head->volume;
   
   /* loop through the stem sections */
   if (pT->Stem.head != NULL_PTR2BRANCH_LIST){ 
      pB				 = tree1.Stem.head;
      trunk_length		 = pB->l;
      if (bsecl < dsecl) {
         n_segments			 = (int) (trunk_length / bsecl);
      } else {
         n_segments			 = (int) (trunk_length / dsecl);
      }
      if (n_segments < POLSARPROSIM_MIN_STEM_SEG_NUM) {
         n_segments	= POLSARPROSIM_MIN_STEM_SEG_NUM;
      }
      for (i_seg=0; i_seg<n_segments; i_seg++) {
         rtn_value	= Cylinder_from_Branch (&Cyl1, pB, i_seg, n_segments);
         if (Cyl1.base.x[2] > tree1.CrownVolume.head->base.x[2]) {
            Alpha                   = CylinderPolarisability (&Cyl1, &kix, &kiy, &kiz, &Ytable, &Jtable);
            Alpha_Trunk_Sum         = c33Matrix_sum (Alpha_Trunk_Sum, Alpha);
            trunk_volume            = DPI_RAD*Cyl1.radius*Cyl1.radius*Cyl1.length;
            crown_trunk_vol_frac    += trunk_volume;
            trunk_count             += 1.0;
         }
      }
   }
   
   /* loop through primary branches */
   if (pT->Primary.head != NULL_PTR2BRANCH_LIST){   
      pB	= tree1.Primary.head;
      for (iBranch=0L; iBranch < tree1.Primary.n; iBranch++) {
         primary_length	= pB->l;
         n_segments		= (int) (primary_length / bsecl);
         if (n_segments < 1) {
            n_segments	= 1;
         }
         for (i_seg=0; i_seg<n_segments; i_seg++) {
            rtn_value               = Cylinder_from_Branch (&Cyl1, pB, i_seg, n_segments);
            Alpha                   = CylinderPolarisability (&Cyl1, &kix, &kiy, &kiz, &Ytable, &Jtable);
            Alpha_Primary_Sum       = c33Matrix_sum (Alpha_Primary_Sum, Alpha);
            primary_volume          = DPI_RAD*Cyl1.radius*Cyl1.radius*Cyl1.length;
            crown_primary_vol_frac	+= primary_volume;
            primary_count           += 1.0;
         }
         pB	= pB->next;
      }
   }
   
   /* loop through secondary branches */
   if (pT->Secondary.head != NULL_PTR2BRANCH_LIST){ 
      pB	= tree1.Secondary.head;
      for (iBranch=0L; iBranch < tree1.Secondary.n; iBranch++) {
         secondary_length	= pB->l;
         n_segments		= (int) (secondary_length / bsecl);
         if (n_segments < 1) {
            n_segments	= 1;
         }
         for (i_seg=0; i_seg<n_segments; i_seg++) {
            rtn_value                  = Cylinder_from_Branch (&Cyl1, pB, i_seg, n_segments);
            Alpha                      = CylinderPolarisability (&Cyl1, &kix, &kiy, &kiz, &Ytable, &Jtable);
            Alpha_Secondary_Sum        = c33Matrix_sum (Alpha_Secondary_Sum, Alpha);
            secondary_volume           = DPI_RAD*Cyl1.radius*Cyl1.radius*Cyl1.length;
            crown_secondary_vol_frac	+= secondary_volume;
            secondary_count            += 1.0;
         }
         pB	= pB->next;
      }
   }
   
   /* loop through tertiary branches */
   if(pT->Tertiary.head != NULL_PTR2BRANCH_LIST) {
      pB = tree1.Tertiary.head;
      number_of_tertiaries = tree1.Tertiary.n;
      for (iBranch=0L; iBranch < number_of_tertiaries; iBranch++) {
         tertiary_length	= pB->l;
         n_segments        = (int) (tertiary_length / bsecl);
         if (n_segments < 1) {
            n_segments	= 1;
         }
         for (i_seg=0; i_seg<n_segments; i_seg++) {
            rtn_value                  = Cylinder_from_Branch (&Cyl1, pB, i_seg, n_segments);
            Alpha                      = CylinderPolarisability (&Cyl1, &kix, &kiy, &kiz, &Ytable, &Jtable);
            Alpha_Tertiary_Sum         = c33Matrix_sum (Alpha_Tertiary_Sum, Alpha);
            tertiary_volume            = DPI_RAD*Cyl1.radius*Cyl1.radius*Cyl1.length;
            crown_tertiary_vol_frac   += tertiary_volume;
            tertiary_count            += 1.0;
         }
         pB	= pB->next;
      }
   } 
   
   /* loop through leaves */
   if(pT->Foliage.head != NULL_PTR2LEAF_LIST) {
      pL = tree1.Foliage.head;
      number_of_leaves = tree1.Foliage.n;
      for (iLeaf=0L; iLeaf < number_of_leaves; iLeaf++){
         Leaf_Depolarization_Factors (pL, &leafL1, &leafL2, &leafL3);
         leaf_moisture           = pL->moisture; 
         leaf_permittivity       = pL->permittivity; 
         leaf_epsm1              = xy_complex (leaf_permittivity.x-1.0, leaf_permittivity.y);
         Alpha                   = Leaf_Polarisability (pL, leafL1, leafL2, leafL3);
         Alpha_Leaf_Sum          = c33Matrix_sum (Alpha_Leaf_Sum, c33Matrix_Complex_product (Alpha, leaf_epsm1));
         leaf_volume             = Leaf_Volume (pL);
         crown_foliage_vol_frac  += leaf_volume;
         leaf_count              += 1.0;
         pL = pL->next; 
      }
   }
   
   /*********************/
   /* Assign Outputs    */
   /*********************/
   
   pTA->dry_crown_volume           = dry_crown_volume;
   pTA->dry_count                  = dry_count;
   pTA->crown_dry_vol_frac         = crown_dry_vol_frac;
   pTA->Alpha_Dry_Sum              = c33Matrix_sum (Alpha_Dry_Sum, c33Zero);
   pTA->crown_volume               = crown_volume;
   pTA->trunk_count                = trunk_count;
   pTA->crown_trunk_vol_frac       = crown_trunk_vol_frac;   
   pTA->Alpha_Trunk_Sum            = c33Matrix_sum (Alpha_Trunk_Sum, c33Zero); 
   pTA->primary_count              = primary_count;
   pTA->crown_primary_vol_frac     = crown_primary_vol_frac;
   pTA->Alpha_Primary_Sum          = c33Matrix_sum (Alpha_Primary_Sum, c33Zero); 
   pTA->secondary_count            = secondary_count;  
   pTA->crown_secondary_vol_frac   = crown_secondary_vol_frac;
   pTA->Alpha_Secondary_Sum        = c33Matrix_sum (Alpha_Secondary_Sum, c33Zero);
   pTA->tertiary_count             = tertiary_count;
   pTA->crown_tertiary_vol_frac    = crown_tertiary_vol_frac;
   pTA->Alpha_Tertiary_Sum         = c33Matrix_sum (Alpha_Tertiary_Sum, c33Zero); 
   pTA->leaf_count                 = leaf_count;
   pTA->crown_foliage_vol_frac     = crown_foliage_vol_frac;
   pTA->Alpha_Leaf_Sum             = c33Matrix_sum (Alpha_Leaf_Sum, c33Zero);
   
   /* exit */
   pthread_exit(NULL);
   
}

/******************************************/
/* A multi-processor version of the code  */
/* that computes effective permittivities */
/******************************************/
void		Effective_Permittivities_SMP	(PolSARproSim_Record *pPR)
{
   Leaf           leaf1;
   double			costheta, theta, phi;
   double			d_costheta, d_phi;
   int            i_costheta, i_phi;
   int            Ntheta, Nphi;
   d3Vector       leaf_centre	= Zero_d3Vector ();
   d3Vector       stem_centre	= Zero_d3Vector ();
   double			leaf_d1, leaf_d2, leaf_d3;
   int            leaf_species;
   double			leaf_moisture;
   Complex        leaf_permittivity, leaf_epsm1;
   double			stem_d1, stem_d2, stem_d3;
   int            stem_species;
   double			stem_moisture;
   Complex        stem_permittivity, stem_epsm1;
   Complex        scale_factor;
   c33Matrix		ShortVegi_EpsEff	= Idem_c33Matrix ();
   double			stemL1, stemL2, stemL3;
   double			leafL1, leafL2, leafL3;
   int            itree;
   int            Ntrees;
   
   /* some variables for hyperthreading */
   EffPerm_Thread_Arg   *threadarg; /* pointer to array of thread arguments   */
   pthread_t            *threads;   /* pointer to arry of thread ids          */
   pthread_attr_t       attr;       /* a global thread attribute              */
   int                  rc;         /* thread return code                     */
   void                 *status;    /* thread status                          */
   /* initialize thread variables */
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

   
   c33Matrix		Alpha_Trunk_Sum				= Zero_c33Matrix ();
   c33Matrix		Alpha_Primary_Sum          = Zero_c33Matrix ();
   c33Matrix		Alpha_Secondary_Sum			= Zero_c33Matrix ();
   c33Matrix		Alpha_Tertiary_Sum         = Zero_c33Matrix ();
   c33Matrix		Alpha_Leaf_Sum             = Zero_c33Matrix ();
   c33Matrix		Alpha_Dry_Sum              = Zero_c33Matrix ();
   c33Matrix		Alpha                      = Zero_c33Matrix ();
   c33Matrix		Alpha_Stem_Sum             = Zero_c33Matrix ();
   
   c33Matrix		CrownTrunk_EpsEff          = Idem_c33Matrix ();
   c33Matrix		CrownPrimary_EpsEff			= Idem_c33Matrix ();
   c33Matrix		CrownSecondary_EpsEff		= Idem_c33Matrix ();
   c33Matrix		CrownTert_EpsEff           = Idem_c33Matrix ();
   c33Matrix		CrownDry_EpsEff				= Idem_c33Matrix ();
   c33Matrix		CrownLiving_EpsEff			= Idem_c33Matrix ();
   
   double			crown_trunk_vol_frac       = 0.0;
   double			crown_primary_vol_frac		= 0.0;
   double			crown_secondary_vol_frac	= 0.0;
   double			crown_dry_vol_frac			= 0.0;
   double         crown_tertiary_vol_frac    = 0.0;
   double         crown_foliage_vol_frac     = 0.0;
   double			crown_volume, dry_crown_volume;
   double			trunk_count, trunk_number_density;
   double			primary_count, primary_number_density;
   double			secondary_count, secondary_number_density;
   /* for treating tertiaries as cylinders instead of leaves */
   double         tertiary_count, tertiary_number_density;
   /* for using already realized leaves */
   double         foliage_number_density, leaf_count;
   double			dry_count, dry_number_density;
   
   Complex        e, ez;
   double         kro2;
   Complex        ko2, koz2, koz;
   Complex        ke2, kez2, kez;
      
   int            ispecies;
   int            treeindex[POLSARPROSIM_ATTENUATION_TREES];
   int            index_count;
   
   /******************************************/
   /* Report call if running in VERBOSE mode */
   /******************************************/
#ifdef VERBOSE_POLSARPROSIM
   printf ("\n");
   printf ("Call to Effective_Permittivities ... \n");
   printf ("\n");
#endif
   fprintf (pPR->pLogFile, "Call to Effective_Permittivities ... \n");
   fflush  (pPR->pLogFile);
   
   /* Initialize the global effective wave vectors */
   pPR->koz_living   = (Complex *) calloc(pPR->Nspecies, sizeof(Complex));
   pPR->koz_dry      = (Complex *) calloc(pPR->Nspecies, sizeof(Complex));
   pPR->kez_living   = (Complex *) calloc(pPR->Nspecies, sizeof(Complex));
   pPR->kez_dry      = (Complex *) calloc(pPR->Nspecies, sizeof(Complex));
   
   /*********************************************/
   /* Estimate the wavevectors for each species */
   /*********************************************/
   for (ispecies=0;ispecies<pPR->Nspecies;ispecies++){
      
#ifdef VERBOSE_POLSARPROSIM
      printf ("\n");
      printf ("Calculating dry, trunk, primary, secondary, tertiary and foliage effective permittivities for %s ... \n", pPR->SpeciesDataBase[ispecies].species_name);
      printf ("\n");
#endif
      fprintf (pPR->pLogFile, "Calculating dry, trunk, primary, secondary, tertiary and foliage effective permittivities for %s ... \n", pPR->SpeciesDataBase[ispecies].species_name);
      fflush  (pPR->pLogFile);
      
      /* determine how many trees to average over for this species */
      if(pPR->SpeciesDataBase[ispecies].Trees < POLSARPROSIM_ATTENUATION_TREES) {
         Ntrees = pPR->SpeciesDataBase[ispecies].Trees;
      } else{
         Ntrees = POLSARPROSIM_ATTENUATION_TREES;
      }
      
      /* for threads */
      threadarg = (EffPerm_Thread_Arg *)calloc(Ntrees,sizeof(EffPerm_Thread_Arg));
      threads   = (pthread_t *)calloc(Ntrees,sizeof(pthread_t));
      
      /* determine which trees to average over */
      itree = 0;
      index_count = 0;
      while(index_count<Ntrees){
         if(pPR->Tree_Location[itree].species == ispecies) {
            treeindex[index_count] = itree;
            index_count++;
         }
         itree++;
      }
      
      /* zero out the counters */
      crown_volume               = 0.0;
      dry_crown_volume           = 0.0;
      trunk_count                = 0.0;
      primary_count              = 0.0;
      secondary_count            = 0.0;
      tertiary_count             = 0.0;
      leaf_count                 = 0.0;
      dry_count                  = 0.0;
      /* zero out the volume fractions */
      crown_trunk_vol_frac       = 0.0;
      crown_primary_vol_frac		= 0.0;
      crown_secondary_vol_frac	= 0.0;
      crown_foliage_vol_frac     = 0.0;
      crown_dry_vol_frac			= 0.0;
      /* zero out the polarizability tensors */
      Alpha_Trunk_Sum				= Zero_c33Matrix ();
      Alpha_Primary_Sum          = Zero_c33Matrix ();
      Alpha_Secondary_Sum			= Zero_c33Matrix ();
      Alpha_Dry_Sum              = Zero_c33Matrix ();
      Alpha_Tertiary_Sum         = Zero_c33Matrix ();
      Alpha_Leaf_Sum             = Zero_c33Matrix ();
      /* zero out the permittivity tensors */
      CrownTrunk_EpsEff          = Idem_c33Matrix ();
      CrownPrimary_EpsEff			= Idem_c33Matrix ();
      CrownSecondary_EpsEff		= Idem_c33Matrix ();
      CrownTert_EpsEff           = Idem_c33Matrix ();
      CrownDry_EpsEff				= Idem_c33Matrix ();
      CrownLiving_EpsEff			= Idem_c33Matrix ();
      
      for (itree = 0; itree < Ntrees; itree++) {
         /* set the thread argument */
         threadarg[itree].itree   = treeindex[itree];
         threadarg[itree].pPR     = pPR;
         /* create threads */
         rc=pthread_create(&threads[itree], &attr, Compute_Alphas, (void *)&threadarg[itree]);
         if(rc){
            printf("Oops! Thread for tree/species %d/%d was not created in Effective_Permittivities\n", itree,ispecies);
            exit(-1);
         }
      }
      /* loop to join the created threads (runs blocking) */
      for (itree = 0; itree < Ntrees; itree++) {
         rc=pthread_join(threads[itree], &status);
         if(rc){
            printf("ERR: unable to join thread for tree/species %d/%d in Effective Permittivities, code: %d\n", itree,ispecies,rc);
            exit(-1);
         }
      }
      /* loop to add results */
      for (itree = 0; itree < Ntrees; itree++) {
         /* add volumes */
         dry_crown_volume          += threadarg[itree].dry_crown_volume;
         crown_volume              += threadarg[itree].crown_volume;
         /* add dry crown contributions */
         dry_count                 += threadarg[itree].dry_count;
         crown_dry_vol_frac        += threadarg[itree].crown_dry_vol_frac;
         Alpha_Dry_Sum              = c33Matrix_sum (Alpha_Dry_Sum, threadarg[itree].Alpha_Dry_Sum);
         /* add trunk contributions */
         trunk_count               += threadarg[itree].trunk_count;
         crown_trunk_vol_frac      += threadarg[itree].crown_trunk_vol_frac;
         Alpha_Trunk_Sum            = c33Matrix_sum (Alpha_Trunk_Sum, threadarg[itree].Alpha_Trunk_Sum);
         /* add primary contributions */
         primary_count             += threadarg[itree].primary_count;
         crown_primary_vol_frac    += threadarg[itree].crown_primary_vol_frac;
         Alpha_Primary_Sum          = c33Matrix_sum (Alpha_Primary_Sum, threadarg[itree].Alpha_Primary_Sum);
         /* add secondary contributions */
         secondary_count           += threadarg[itree].secondary_count;
         crown_secondary_vol_frac  += threadarg[itree].crown_secondary_vol_frac;
         Alpha_Secondary_Sum        = c33Matrix_sum (Alpha_Secondary_Sum, threadarg[itree].Alpha_Secondary_Sum);
         /* add tertiary contributions */
         tertiary_count            += threadarg[itree].tertiary_count;
         crown_tertiary_vol_frac   += threadarg[itree].crown_tertiary_vol_frac;
         Alpha_Tertiary_Sum         = c33Matrix_sum (Alpha_Tertiary_Sum, threadarg[itree].Alpha_Tertiary_Sum);
         /* add foliage contributions */
         leaf_count                += threadarg[itree].leaf_count;
         crown_foliage_vol_frac    += threadarg[itree].crown_foliage_vol_frac;
         Alpha_Leaf_Sum             = c33Matrix_sum (Alpha_Leaf_Sum, threadarg[itree].Alpha_Leaf_Sum);

      }
      
      if(dry_count > 0){ /* Use dry_count to avoid using pPR->species as a check --RAedit  */
         crown_dry_vol_frac         /= dry_crown_volume;
         dry_number_density         = dry_count / dry_crown_volume;
         scale_factor               = xy_complex (dry_number_density/dry_count, 0.0);
         CrownDry_EpsEff            = c33Matrix_sum (CrownDry_EpsEff, c33Matrix_Complex_product (Alpha_Dry_Sum, scale_factor));
      } else {
         crown_dry_vol_frac         = 0.0;
         dry_number_density         = 0.0;
         dry_count                  = 0.0;
         dry_crown_volume           = 0.0;
      }
      if(trunk_count > 0) {
         crown_trunk_vol_frac       /= crown_volume;
         trunk_number_density       = trunk_count / crown_volume;
         scale_factor               = xy_complex (trunk_number_density/trunk_count, 0.0);
         CrownTrunk_EpsEff          = c33Matrix_sum (CrownTrunk_EpsEff, c33Matrix_Complex_product (Alpha_Trunk_Sum, scale_factor));
      }
      if(primary_count > 0) {   
         crown_primary_vol_frac     /= crown_volume;
         primary_number_density     = primary_count / crown_volume;
         scale_factor               = xy_complex (primary_number_density/primary_count, 0.0);
         CrownPrimary_EpsEff        = c33Matrix_sum (CrownPrimary_EpsEff, c33Matrix_Complex_product (Alpha_Primary_Sum, scale_factor));
      }
      if(secondary_count > 0) {
         crown_secondary_vol_frac	/= crown_volume;
         secondary_number_density   = secondary_count / crown_volume;
         scale_factor               = xy_complex (secondary_number_density/secondary_count, 0.0);
         CrownSecondary_EpsEff      = c33Matrix_sum (CrownSecondary_EpsEff, c33Matrix_Complex_product (Alpha_Secondary_Sum, scale_factor));
      }
      if(tertiary_count > 0) {
         crown_tertiary_vol_frac    /= crown_volume;
         tertiary_number_density    = tertiary_count / crown_volume;
         scale_factor               = xy_complex (tertiary_number_density/tertiary_count, 0.0);
         CrownTert_EpsEff           = c33Matrix_sum (CrownTert_EpsEff, c33Matrix_Complex_product (Alpha_Tertiary_Sum, scale_factor));
      }
      if(leaf_count > 0) {
         crown_foliage_vol_frac    /= crown_volume;
         foliage_number_density     = leaf_count / crown_volume;
         /* I'm not quite sure what the right scale factor should be --RA */
         //scale_factor               = xy_complex (foliage_number_density/leaf_count, 0.0);
         //scale_factor               = xy_complex (crown_foliage_vol_frac, 0.0);
         scale_factor               = xy_complex (Leaf_Volume_Fraction(ispecies, pPR)/leaf_count, 0.0);
         CrownTert_EpsEff           = c33Matrix_sum (CrownTert_EpsEff, c33Matrix_Complex_product (Alpha_Leaf_Sum, scale_factor));
      }
      /******************************************/
      /* Enforce isotropy in leaves and foliage */
      /******************************************/
      e                          = complex_add (complex_add (CrownTert_EpsEff.m[0], CrownTert_EpsEff.m[4]), CrownTert_EpsEff.m[8]);
      e                          = complex_rmul (e, 1.0/3.0);
      CrownTert_EpsEff           = Zero_c33Matrix ();
      CrownTert_EpsEff.m[0]      = e;
      CrownTert_EpsEff.m[4]      = e;
      CrownTert_EpsEff.m[8]      = e;
      
      /*****************************/
      /* Output results to logfile */
      /*****************************/
      fprintf (pPR->pLogFile, "\n");
      fprintf (pPR->pLogFile, "Crown trunk volume fraction\t\t= %10.3e\n", crown_trunk_vol_frac);
      fprintf (pPR->pLogFile, "Crown trunk segment number\t\t= %10.3e\n", trunk_count);
      fprintf (pPR->pLogFile, "Crown volume\t\t\t\t= %10.3e m^3\n", crown_volume);
      fprintf (pPR->pLogFile, "Crown trunk segment number density\t= %10.3e\n", trunk_number_density);
      fprintf (pPR->pLogFile, "Crown trunk effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownTrunk_EpsEff.m[0].x, fabs(CrownTrunk_EpsEff.m[0].y));
      fprintf (pPR->pLogFile, "Crown trunk effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownTrunk_EpsEff.m[4].x, fabs(CrownTrunk_EpsEff.m[4].y));
      fprintf (pPR->pLogFile, "Crown trunk effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownTrunk_EpsEff.m[8].x, fabs(CrownTrunk_EpsEff.m[8].y));
      fprintf (pPR->pLogFile, "\n");
      fprintf (pPR->pLogFile, "\n");
      fprintf (pPR->pLogFile, "Crown primary volume fraction\t\t= %10.3e\n", crown_primary_vol_frac);
      fprintf (pPR->pLogFile, "Crown primary segment number\t\t= %10.3e\n", primary_count);
      fprintf (pPR->pLogFile, "Crown volume\t\t\t\t= %10.3e m^3\n", crown_volume);
      fprintf (pPR->pLogFile, "Crown primary segment number density\t= %10.3e\n", primary_number_density);
      fprintf (pPR->pLogFile, "Crown primary effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownPrimary_EpsEff.m[0].x, fabs(CrownPrimary_EpsEff.m[0].y));
      fprintf (pPR->pLogFile, "Crown primary effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownPrimary_EpsEff.m[4].x, fabs(CrownPrimary_EpsEff.m[4].y));
      fprintf (pPR->pLogFile, "Crown primary effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownPrimary_EpsEff.m[8].x, fabs(CrownPrimary_EpsEff.m[8].y));
      fprintf (pPR->pLogFile, "\n");
      fprintf (pPR->pLogFile, "\n");
      fprintf (pPR->pLogFile, "Crown secondary volume fraction\t\t= %10.3e\n", crown_secondary_vol_frac);
      fprintf (pPR->pLogFile, "Crown secondary segment number\t\t= %10.3e\n", secondary_count);
      fprintf (pPR->pLogFile, "Crown volume\t\t\t\t= %10.3e m^3\n", crown_volume);
      fprintf (pPR->pLogFile, "Crown secondary segment number density\t= %10.3e\n", secondary_number_density);
      fprintf (pPR->pLogFile, "Crown secondary effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownSecondary_EpsEff.m[0].x, fabs(CrownSecondary_EpsEff.m[0].y));
      fprintf (pPR->pLogFile, "Crown secondary effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownSecondary_EpsEff.m[4].x, fabs(CrownSecondary_EpsEff.m[4].y));
      fprintf (pPR->pLogFile, "Crown secondary effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownSecondary_EpsEff.m[8].x, fabs(CrownSecondary_EpsEff.m[8].y));
      fprintf (pPR->pLogFile, "\n");
      fprintf (pPR->pLogFile, "\n");
      fprintf (pPR->pLogFile, "Crown tertiary volume fraction\t\t= %10.3e\n", crown_tertiary_vol_frac);
      fprintf (pPR->pLogFile, "Crown tertiary segment number\t\t= %10.3e\n", tertiary_count);
      fprintf (pPR->pLogFile, "Crown volume\t\t\t\t= %10.3e m^3\n", crown_volume);
      fprintf (pPR->pLogFile, "Crown tertiary effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownTert_EpsEff.m[0].x, fabs(CrownTert_EpsEff.m[0].y));
      fprintf (pPR->pLogFile, "Crown tertiary effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownTert_EpsEff.m[4].x, fabs(CrownTert_EpsEff.m[4].y));
      fprintf (pPR->pLogFile, "Crown tertiary effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownTert_EpsEff.m[8].x, fabs(CrownTert_EpsEff.m[8].y));
      fprintf (pPR->pLogFile, "\n");
      fprintf (pPR->pLogFile, "\n");
      fprintf (pPR->pLogFile, "Crown dry volume fraction\t\t= %10.3e\n", crown_dry_vol_frac);
      fprintf (pPR->pLogFile, "Crown dry segment number\t\t= %10.3e\n", dry_count);
      fprintf (pPR->pLogFile, "Crown dry volume\t\t\t= %10.3e m^3\n", dry_crown_volume);
      fprintf (pPR->pLogFile, "Crown dry segment number density\t= %10.3e\n", dry_number_density);
      fprintf (pPR->pLogFile, "Crown dry effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownDry_EpsEff.m[0].x, fabs(CrownDry_EpsEff.m[0].y));
      fprintf (pPR->pLogFile, "Crown dry effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownDry_EpsEff.m[4].x, fabs(CrownDry_EpsEff.m[4].y));
      fprintf (pPR->pLogFile, "Crown dry effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownDry_EpsEff.m[8].x, fabs(CrownDry_EpsEff.m[8].y));
      fprintf (pPR->pLogFile, "\n");
      
      /******************************************/
      /* Combine contributions for living crown */
      /******************************************/
      CrownLiving_EpsEff         = c33Matrix_sum (CrownLiving_EpsEff, c33Matrix_difference (CrownTrunk_EpsEff, Idem_c33Matrix ()));
      CrownLiving_EpsEff         = c33Matrix_sum (CrownLiving_EpsEff, c33Matrix_difference (CrownPrimary_EpsEff, Idem_c33Matrix ()));
      CrownLiving_EpsEff         = c33Matrix_sum (CrownLiving_EpsEff, c33Matrix_difference (CrownSecondary_EpsEff, Idem_c33Matrix ()));
      CrownLiving_EpsEff         = c33Matrix_sum (CrownLiving_EpsEff, c33Matrix_difference (CrownTert_EpsEff, Idem_c33Matrix ()));
      /************************************************/
      /* Rationalise effective permittivity estimates */
      /* Calculate and store effective wavenumbers.   */
      /************************************************/
      e                          = complex_rmul (complex_add (CrownDry_EpsEff.m[0], CrownDry_EpsEff.m[4]), 0.5);
      ez                         = CrownDry_EpsEff.m[8];
      CrownDry_EpsEff            = Idem_c33Matrix ();
      CrownDry_EpsEff.m[0]       = e;
      CrownDry_EpsEff.m[4]       = e;
      CrownDry_EpsEff.m[8]       = ez;
      pPR->e11_dry               = e;
      pPR->e33_dry               = ez;
      kro2                       = pPR->k0*sin(pPR->incidence_angle[0]);
      kro2                       *= kro2;
      ko2                        = complex_rmul (e, pPR->k0*pPR->k0);
      koz2                       = xy_complex (ko2.x-kro2, ko2.y);
      koz                        = complex_sqrt (koz2);
      ke2                        = complex_rmul (ez, pPR->k0*pPR->k0);
      kez2                       = xy_complex (ke2.x-kro2, ke2.y);
      kez2                       = complex_mul (kez2, complex_div (e ,ez));
      kez                        = complex_sqrt(kez2);
      ke2                        = complex_add (kez2, xy_complex (kro2, 0.0));
      pPR->ko2_dry               = ko2;
      pPR->koz2_dry              = koz2;
      pPR->koz_dry[ispecies]     = koz; // used in Attenuation_map
      pPR->ke2_dry               = ke2;
      pPR->kez2_dry              = kez2;
      pPR->kez_dry[ispecies]     = kez; // used in Attenuation_map
      e                          = complex_rmul (complex_add (CrownLiving_EpsEff.m[0], CrownLiving_EpsEff.m[4]), 0.5);
      ez                         = CrownLiving_EpsEff.m[8];
      CrownLiving_EpsEff         = Idem_c33Matrix ();
      CrownLiving_EpsEff.m[0]    = e;
      CrownLiving_EpsEff.m[4]    = e;
      CrownLiving_EpsEff.m[8]    = ez;
      pPR->e11_living            = e;
      pPR->e33_living            = ez;
      kro2                       = pPR->k0*sin(pPR->incidence_angle[0]);
      kro2                       *= kro2;
      ko2                        = complex_rmul (e, pPR->k0*pPR->k0);
      koz2                       = xy_complex (ko2.x-kro2, ko2.y);
      koz                        = complex_sqrt (koz2);
      ke2                        = complex_rmul (ez, pPR->k0*pPR->k0);
      kez2                       = xy_complex (ke2.x-kro2, ke2.y);
      kez2                       = complex_mul (kez2, complex_div (e ,ez));
      kez                        = complex_sqrt(kez2);
      ke2                        = complex_add (kez2, xy_complex (kro2, 0.0));
      pPR->ko2_living            = ko2;
      pPR->koz2_living           = koz2;
      pPR->koz_living[ispecies]  = koz; // used in Attenuation_map
      pPR->ke2_living            = ke2;
      pPR->kez2_living           = kez2;
      pPR->kez_living[ispecies]  = kez; // used in Attenuation_map
      
      fprintf (pPR->pLogFile, "\n");
      fprintf (pPR->pLogFile, "Consolidated effective permittivities:");
      fprintf (pPR->pLogFile, "\n");
      fprintf (pPR->pLogFile, "\n");
      fprintf (pPR->pLogFile, "Crown dry effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownDry_EpsEff.m[0].x, fabs(CrownDry_EpsEff.m[0].y));
      fprintf (pPR->pLogFile, "Crown dry effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownDry_EpsEff.m[4].x, fabs(CrownDry_EpsEff.m[4].y));
      fprintf (pPR->pLogFile, "Crown dry effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownDry_EpsEff.m[8].x, fabs(CrownDry_EpsEff.m[8].y));
      fprintf (pPR->pLogFile, "\n");
      fprintf (pPR->pLogFile, "\n");
      fprintf (pPR->pLogFile, "Crown living effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownLiving_EpsEff.m[0].x, fabs(CrownLiving_EpsEff.m[0].y));
      fprintf (pPR->pLogFile, "Crown living effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownLiving_EpsEff.m[4].x, fabs(CrownLiving_EpsEff.m[4].y));
      fprintf (pPR->pLogFile, "Crown living effective permittivity\t= %10.3e + j %10.3e  ... \n", CrownLiving_EpsEff.m[8].x, fabs(CrownLiving_EpsEff.m[8].y));
      fprintf (pPR->pLogFile, "\n");
   }
   
   /*********************************************************/
   /* Isotropic short vegetation layer: uses GRG model only */
   /*********************************************************/
   
#ifdef VERBOSE_POLSARPROSIM
   printf ("\n");
   printf ("Calculating short vegetation effective permittivity  ... \n");
   printf ("\n");
#endif
   fprintf (pPR->pLogFile, "Calculating short vegetation effective permittivity  ... \n");
   fflush  (pPR->pLogFile);
   theta				= 0.0;
   phi				= 0.0;
   Alpha                      = Zero_c33Matrix ();
   Alpha_Stem_Sum             = Zero_c33Matrix ();
   Alpha_Leaf_Sum             = Zero_c33Matrix ();
   /********************************************/
   /* Realise a stem (needle) to find L values */
   /********************************************/
   stem_species            = POLSARPROSIM_PINE_NEEDLE;
   stem_d1                 = POLSARPROSIM_SHORTV_STEM_LENGTH;
   stem_d2                 = POLSARPROSIM_SHORTV_STEM_RADIUS;
   stem_d3                 = POLSARPROSIM_SHORTV_STEM_RADIUS;
   stem_moisture           = Leaf_Moisture	(pPR->species, pPR);
   stem_permittivity       = vegetation_permittivity (stem_moisture, pPR->frequency);
   Assign_Leaf (&leaf1, stem_species, stem_d1, stem_d2, stem_d3, theta, phi, stem_moisture, stem_permittivity, stem_centre);
   Leaf_Depolarization_Factors (&leaf1, &stemL1, &stemL2, &stemL3);
   pPR->ShortVegi_stemL1	= stemL1;
   pPR->ShortVegi_stemL2	= stemL2;
   pPR->ShortVegi_stemL3	= stemL3;
   /***********************************/
   /* Realise a leaf to find L values */
   /***********************************/
   leaf_species            = POLSARPROSIM_DECIDUOUS_LEAF;
   leaf_d1                 = POLSARPROSIM_SHORTV_LEAF_LENGTH;
   leaf_d2                 = POLSARPROSIM_SHORTV_LEAF_WIDTH;
   leaf_d3                 = POLSARPROSIM_SHORTV_LEAF_THICKNESS;
   leaf_moisture           = Leaf_Moisture	(pPR->species, pPR);
   leaf_permittivity       = vegetation_permittivity (leaf_moisture, pPR->frequency);
   Assign_Leaf	(&leaf1, leaf_species, leaf_d1, leaf_d2, leaf_d3, theta, phi, leaf_moisture, leaf_permittivity, leaf_centre);
   Leaf_Depolarization_Factors (&leaf1, &leafL1, &leafL2, &leafL3);
   pPR->ShortVegi_leafL1	= leafL1;
   pPR->ShortVegi_leafL2	= leafL2;
   pPR->ShortVegi_leafL3	= leafL3;
   /****************************************************/
   /* Average polarisabilities over orientation angles */
   /****************************************************/
   Ntheta                  = POLSARPROSIM_SHORT_VEGI_NTHETA;
   Nphi                    = POLSARPROSIM_SHORT_VEGI_NPHI;
   d_costheta              = 2.0/Ntheta;
   d_phi                   = 2.0*DPI_RAD/Nphi;
   for (i_costheta = 0; i_costheta < Ntheta; i_costheta++) {
      costheta	= i_costheta*d_costheta + d_costheta/2.0 - 1.0;
      theta		= acos(costheta);
      for (i_phi = 0; i_phi < Nphi; i_phi++) {
         phi	= i_phi*d_phi + d_phi/2.0;
         /**********************/
         /* Stem contribution  */
         /**********************/
         stem_moisture		= Leaf_Moisture (pPR->species, pPR);
         stem_permittivity	= vegetation_permittivity (stem_moisture, pPR->frequency);
         stem_epsm1			= xy_complex (stem_permittivity.x-1.0, stem_permittivity.y);
         Assign_Leaf (&leaf1, stem_species, stem_d1, stem_d2, stem_d3, theta, phi, stem_moisture, stem_permittivity, stem_centre);
         Alpha             = Leaf_Polarisability (&leaf1, stemL1, stemL2, stemL3);
         Alpha_Stem_Sum		= c33Matrix_sum (Alpha_Stem_Sum, c33Matrix_Complex_product (Alpha, stem_epsm1));
         /*********************/
         /* Leaf contribution */
         /*********************/
         leaf_moisture		= Leaf_Moisture (pPR->species, pPR);
         leaf_permittivity	= vegetation_permittivity (leaf_moisture, pPR->frequency);
         leaf_epsm1			= xy_complex (leaf_permittivity.x-1.0, leaf_permittivity.y);
         Assign_Leaf (&leaf1, leaf_species, leaf_d1, leaf_d2, leaf_d3, theta, phi, leaf_moisture, leaf_permittivity, leaf_centre);
         Alpha             = Leaf_Polarisability (&leaf1, leafL1, leafL2, leafL3);
         Alpha_Leaf_Sum		= c33Matrix_sum (Alpha_Leaf_Sum, c33Matrix_Complex_product (Alpha, leaf_epsm1));
      }
   }
   scale_factor            = xy_complex (pPR->shrt_vegi_stem_vol_frac/(Ntheta*Nphi), 0.0);
   ShortVegi_EpsEff        = c33Matrix_sum (ShortVegi_EpsEff, c33Matrix_Complex_product (Alpha_Stem_Sum, scale_factor));
   scale_factor            = xy_complex (pPR->shrt_vegi_leaf_vol_frac/(Ntheta*Nphi), 0.0);
   ShortVegi_EpsEff        = c33Matrix_sum (ShortVegi_EpsEff, c33Matrix_Complex_product (Alpha_Leaf_Sum, scale_factor));
   /******************************************************/
   /* Ensure perfect isotropy with this minor correction */
   /******************************************************/
   e                       = complex_add (complex_add (ShortVegi_EpsEff.m[0], ShortVegi_EpsEff.m[4]), ShortVegi_EpsEff.m[8]);
   e                       = complex_rmul (e, 1.0/3.0);
   ShortVegi_EpsEff        = Zero_c33Matrix ();
   ShortVegi_EpsEff.m[0]	= e;
   ShortVegi_EpsEff.m[4]	= e;
   ShortVegi_EpsEff.m[8]	= e;
   /*****************************/
   /* Output results to logfile */
   /*****************************/
   fprintf (pPR->pLogFile, "\n");
   fprintf (pPR->pLogFile, "Short vegetation effective permittivity = %10.3e + j %10.3e  ... \n", ShortVegi_EpsEff.m[0].x, fabs(ShortVegi_EpsEff.m[0].y));
   fprintf (pPR->pLogFile, "Short vegetation effective permittivity = %10.3e + j %10.3e  ... \n", ShortVegi_EpsEff.m[4].x, fabs(ShortVegi_EpsEff.m[4].y));
   fprintf (pPR->pLogFile, "Short vegetation effective permittivity = %10.3e + j %10.3e  ... \n", ShortVegi_EpsEff.m[8].x, fabs(ShortVegi_EpsEff.m[8].y));
   fprintf (pPR->pLogFile, "\n");
   
   e                       = complex_rmul (complex_add (ShortVegi_EpsEff.m[0], ShortVegi_EpsEff.m[4]), 0.5);
   ez                      = ShortVegi_EpsEff.m[8];
   ShortVegi_EpsEff        = Idem_c33Matrix ();
   ShortVegi_EpsEff.m[0]	= e;
   ShortVegi_EpsEff.m[4]	= e;
   ShortVegi_EpsEff.m[8]	= ez;
   pPR->e11_short          = e;
   pPR->e33_short          = ez;
   kro2                    = pPR->k0*sin(pPR->incidence_angle[0]);
   kro2                    *= kro2;
   ko2                     = complex_rmul (e, pPR->k0*pPR->k0);
   koz2                    = xy_complex (ko2.x-kro2, ko2.y);
   koz                     = complex_sqrt (koz2);
   ke2                     = complex_rmul (ez, pPR->k0*pPR->k0);
   kez2                    = xy_complex (ke2.x-kro2, ke2.y);
   kez2                    = complex_mul (kez2, complex_div (e ,ez));
   kez                     = complex_sqrt(kez2);
   ke2                     = complex_add (kez2, xy_complex (kro2, 0.0));
   pPR->ko2_short          = ko2;
   pPR->koz2_short         = koz2;
   pPR->koz_short          = koz;
   pPR->ke2_short          = ke2;
   pPR->kez2_short         = kez2;
   pPR->kez_short          = kez;
   
   /***********/
   /* Tidy up */
   /***********/
   Destroy_Leaf		(&leaf1);
   /******************************************/
   /* Report call if running in VERBOSE mode */
   /******************************************/
#ifdef VERBOSE_POLSARPROSIM
   printf ("\n");
   printf ("... Returning from call to Effective_Permittivities\n");
   printf ("\n");
#endif
   fprintf (pPR->pLogFile, "... Returning from call to Effective_Permittivities\n\n");
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
   return;
}


/*******************************/
/* Attenuation lookup routines */
/*******************************/

int			Lookup_Direct_Attenuation		(d3Vector r, PolSARproSim_Record *pPR, double *gH, double *gV)
{
   const double		x		= r.x[0];
   const double		y		= r.x[1];
   const double		z		= r.x[2];
   const double		Gxy		= ground_height (pPR, x, y);
   const double		Deltaz	= z - Gxy;
   int				i;
   int				j;
   int				k;
   int				invol;
   long				l;
   int				n;
   
   *gH	= 1.0;
   *gV	= 1.0;
   i		= (int) ((x + (pPR->Amap.Ax/2.0))/pPR->Amap.dx);
   j		= (int) (((pPR->Ly/2.0) - pPR->Gap_Distance - y)/pPR->Amap.dy);
   k		= (int) (Deltaz/pPR->Amap.dz);
   if (k < 0) {
      k = 0;
   }
   invol	= 0;
   if ((i >= 0) && (i < pPR->Amap.Nx)) {
      if ((j >= 0) && (j < pPR->Amap.Ny)) {
         if (k < pPR->Amap.Nz) {
            invol	= !invol;
         }
      }
   }
   if (invol != 0) {
      l		= i + j*pPR->Amap.Nx + k*pPR->Amap.Nx*pPR->Amap.Ny;
      *gH	= pPR->Amap.pDirectH[l];
      *gV	= pPR->Amap.pDirectV[l];
   } else {
      if (Deltaz < pPR->Amap.Ads) {
         n	= (int) ((pPR->Amap.Ads - Deltaz)/pPR->Amap.dds);
         if (n < 0) {
            n	= 0;
         } else {
            if (n > pPR->Amap.Nds - 1) {
               n	= pPR->Amap.Nds - 1;
            }
         }
         *gH	= pPR->Amap.pDirectShortH[n];
         *gV	= pPR->Amap.pDirectShortV[n];
      }
   }
   return (NO_DIRECT_ATTENUATION_LOOKUP_ERRORS);
}

int			Lookup_Bounce_Attenuation		(d3Vector r, PolSARproSim_Record *pPR, double *gH, double *gV)
{
   const double		x		= r.x[0];
   const double		y		= r.x[1];
   const double		z		= r.x[2];
   const double		Gxy		= ground_height (pPR, x, y);
   const double		Deltaz	= z - Gxy;
   int				i;
   int				j;
   int				k;
   int				invol;
   long				l;
   int				n;
   
   *gH	= 1.0;
   *gV	= 1.0;
   i		= (int) ((x + (pPR->Amap.Ax/2.0))/pPR->Amap.dx);
   j		= (int) (((pPR->Ly/2.0) - pPR->Gap_Distance - y)/pPR->Amap.dy);
   k		= (int) (Deltaz/pPR->Amap.dz);
   if (k < 0) {
      k = 0;
   }
   invol	= 0;
   if ((i >= 0) && (i < pPR->Amap.Nx)) {
      if ((j >= 0) && (j < pPR->Amap.Ny)) {
         if (k < pPR->Amap.Nz) {
            invol	= !invol;
         }
      }
   }
   if (invol != 0) {
      l		= i + j*pPR->Amap.Nx + k*pPR->Amap.Nx*pPR->Amap.Ny;
      *gH	= pPR->Amap.pBounceH[l];
      *gV	= pPR->Amap.pBounceV[l];
   } else {
      n	= (int) (Deltaz/pPR->Amap.dds);
      if (n < 0) {
         n	= 0;
      } else {
         if (n > pPR->Amap.Nds - 1) {
            n	= pPR->Amap.Nds - 1;
         }
      }
      *gH	= pPR->Amap.pDirectShortH[n];
      *gV	= pPR->Amap.pDirectShortV[n];
   }
   return (NO_DIRECT_ATTENUATION_LOOKUP_ERRORS);
}

/************************************/
/* Attenuation grid mapping routine */
/************************************/

void		Attenuation_Map					(PolSARproSim_Record *pPR)
{
   int         i, j, k;
   double		Sr			= pPR->Stand_Radius;
   double		Cr			= pPR->mean_crown_radius;
   double		Ls			= pPR->Shadow_Distance;
   double		Hs			= pPR->max_tree_height; /* --RAedit */
   double		Gp			= pPR->Gap_Distance;
   double		Ll			= pPR->Layover_Distance;
   double		Lx			= pPR->Lx;
   double		Ly			= pPR->Ly;
   double		x, y, z;
   d3Vector    r;
   d3Vector    a;
   Ray         ray1;
   double		G, zed;
   double		GammaH, GammaV;
   int         itree;
   Tree        tree1;
   Crown       *pC;
   d3Vector    sa1, sa2;
   double		alpha1, alpha2;
   int         rtn_value;
   double		path_length;
   double		cos_theta	= cos(pPR->incidence_angle[0]);
   double		sin_theta	= sin(pPR->incidence_angle[0]);
   long        l;
   double		gHmin, gHmax;
   double		gVmin, gVmax;
   double		f1, f2;
   SIM_Record	Amap_Image;
   sim_pixel	p;
   int         px, py;
   d3Vector    n;
   d3Vector    ar;
   d3Vector    kihat, krhat;
   double		kidotn;
   char        *AmapFilename;
   double		dk;
   Tree        *pT; //--RAedit
   
   /* to get stem shadows --RAedit */
#ifdef ENABLE_ATTENUATION_FROM_STEMS
   Branch      *pB; 
   Cylinder    cyl1; 
   int         nsegments, isegment, cylinder_value;
   d3Vector		s_cyl1;
   double		alpha_cyl1;
   d3Vector		s_cyl2;
   double		alpha_cyl2;
#endif
   
   /******************************************/
   /* Report call if running in VERBOSE mode */
   /******************************************/
   
#ifdef VERBOSE_POLSARPROSIM
   printf ("\n");
   printf ("Call to Attenuation_Map ... \n");
   printf ("\n");
#endif
   fprintf (pPR->pLogFile, "Call to Attenuation_Map ... \n");
   fflush  (pPR->pLogFile);

   pPR->Amap.Ax	= Lx - 2.0*Gp;
   pPR->Amap.Ay	= Ly - Ll - 2.0*Gp;
   pPR->Amap.Az	= Hs;
   pPR->Amap.Nx	= 2*(((int)(pPR->Amap.Ax / (AMAP_RESOLUTION_FACTOR*pPR->azimuth_resolution)))/2)+1;
   if (pPR->Amap.Nx < 3) {
      pPR->Amap.Nx	= 3;
   }
   pPR->Amap.Ny	= 2*(((int)(pPR->Amap.Ay / (AMAP_RESOLUTION_FACTOR*pPR->ground_range_resolution[0])))/2)+1;
   if (pPR->Amap.Ny < 3) {
      pPR->Amap.Ny	= 3;
   }
   pPR->Amap.dx	= pPR->Amap.Ax/(double)(pPR->Amap.Nx-1);
   pPR->Amap.dy	= pPR->Amap.Ay/(double)(pPR->Amap.Ny-1);
   pPR->Amap.dz   = AMAP_VERTICAL_RESOLUTION;  /* set to a default resolution */ 
   pPR->Amap.Nz	= 2*(((int)(pPR->Amap.Az / pPR->Amap.dz))/2)+1;
   if (pPR->Amap.Nz < 3) {
      pPR->Amap.Nz	= 3;
   }
   pPR->Amap.dz	= pPR->Amap.Az/(double)(pPR->Amap.Nz-1);
   pPR->Amap.n    = pPR->Amap.Nx*pPR->Amap.Ny*pPR->Amap.Nz;
   
   pPR->Amap.Nds	= AMAP_SHORT_VEGI_NZ;
   pPR->Amap.Ads	= pPR->shrt_vegi_depth;
   pPR->Amap.dds	= pPR->Amap.Ads / (double) (pPR->Amap.Nds - 1);
   
   /**********************************/
   /* Report attenuation map details */
   /**********************************/
   
   fprintf (pPR->pLogFile, "\n");
   fprintf (pPR->pLogFile, "Stand_Radius     \t=\t%12.5e\n", Sr);
   fprintf (pPR->pLogFile, "Mean_crown_radius\t=\t%12.5e\n", Cr);
   fprintf (pPR->pLogFile, "Shadow_Distance  \t=\t%12.5e\n", Ls);
   fprintf (pPR->pLogFile, "mean_tree_height \t=\t%12.5e\n", Hs);
   fprintf (pPR->pLogFile, "Attenuation map width \t=\t%12.5em\n", pPR->Amap.Ax);
   fprintf (pPR->pLogFile, "Attenuation map length\t=\t%12.5em\n", pPR->Amap.Ay);
   fprintf (pPR->pLogFile, "Attenuation map depth \t=\t%12.5em\n", pPR->Amap.Az);
   fprintf (pPR->pLogFile, "Attenuation map dimensions:\t%5d\t%5d\t%5d\n", pPR->Amap.Nx, pPR->Amap.Ny, pPR->Amap.Nz);
   fprintf (pPR->pLogFile, "\n");
   fflush  (pPR->pLogFile);
   
   /***************************************/
   /* Allocate attenuation factor storage */
   /***************************************/
   
   pPR->Amap.pDirectH			= (double*) calloc (pPR->Amap.n, sizeof (double));
   pPR->Amap.pDirectV			= (double*) calloc (pPR->Amap.n, sizeof (double));
   pPR->Amap.pBounceH			= (double*) calloc (pPR->Amap.n, sizeof (double));
   pPR->Amap.pBounceV			= (double*) calloc (pPR->Amap.n, sizeof (double));
   pPR->Amap.pDirectShortH	= (double*) calloc (AMAP_SHORT_VEGI_NZ, sizeof(double));
   pPR->Amap.pDirectShortV	= (double*) calloc (AMAP_SHORT_VEGI_NZ, sizeof(double));
   
   /*******************************************************************/
   /* For each attenuation grid location calculate BOUNCE attenuation */
   /*******************************************************************/
   
   
   /* just testing, deleteme */
   Create_Tree (&tree1);
   
#ifdef ENABLE_ATTENUATION_FROM_STEMS
   Create_Cylinder	(&cyl1);
   printf("Estimating Attenunation from Stems as well. Go get a coffee, this may take some time\n");
#endif
   
   
   gHmin	=  1.0e+30;
   gHmax	= -1.0e+30;
   gVmin	=  1.0e+30;
   gVmax	= -1.0e+30;
   Create_Tree (&tree1);
   kihat	= Cartesian_Assign_d3Vector (0.0, sin_theta, -cos_theta);
   n		= Cartesian_Assign_d3Vector (-pPR->slope_x, -pPR->slope_y, 1.0);
   d3Vector_insitu_normalise (&n);
   kidotn	= d3Vector_scalar_product (kihat, n);
   krhat	= d3Vector_difference (kihat, d3Vector_double_multiply (n, 2.0*kidotn));
   a		= d3Vector_double_multiply (kihat, -1.0);
   ar		= d3Vector_double_multiply (krhat, -1.0);
   for (i=0; i<pPR->Amap.Nx; i++) {
      x		= ((double)i*pPR->Amap.dx) - pPR->Amap.Ax/2.0;
      for (j=0; j<pPR->Amap.Ny; j++) {
         y	=  (Ly/2.0) - Gp - ((double)j*pPR->Amap.dy);
         for (k=0; k<pPR->Amap.Nz; k++) {
            G	= ground_height (pPR, x, y);
            zed	= ((double)k*pPR->Amap.dz);
            z	= G + zed;
            r	= Cartesian_Assign_d3Vector (x, y, z);
            Assign_Ray_d3V (&ray1, &r, &ar);
            /***************************************************/
            /* Calculate total attenuation for this grid point */
            /***************************************************/
            GammaH	= 1.0;
            GammaV	= 1.0;
            /*****************************/
            /* Short veggie contribution */
            /*****************************/
            if (zed < pPR->shrt_vegi_depth) {
               GammaH	*= exp(-fabs(pPR->koz_short.y)*zed);
               GammaV	*= exp(-fabs(pPR->kez_short.y)*zed);
            } else {
               GammaH	*= exp(-fabs(pPR->koz_short.y)*pPR->shrt_vegi_depth);
               GammaV	*= exp(-fabs(pPR->kez_short.y)*pPR->shrt_vegi_depth);
               /*****************************/
               /* Living crown contribution */
               /*****************************/
               for (itree=0; itree<pPR->Trees; itree++) {
                  if (fabs (x-pPR->Tree_Location[itree].x) <= pPR->Tree_Location[itree].radius) {
                     if (y > (pPR->Tree_Location[itree].y - pPR->Tree_Location[itree].radius)) {
                        /***********************************************/
                        /* Look for ray intersection with living crown */
                        /***********************************************/
                        Realise_Tree_Crown_Only (&tree1, itree, pPR);
                        pC          = tree1.CrownVolume.head;
                        rtn_value	= RayCrownIntersection (&ray1, pC, &sa1, &alpha1, &sa2, &alpha2);
                        /**********************************************************************/
                        /* Additional check for solution above crown apex for conical crowns  */
                        /**********************************************************************/
                        if ((rtn_value == NO_RAYCROWN_ERRORS) && (pC->shape == CROWN_CONE)) {
                           f1	= d3Vector_scalar_product (pC->axis, d3Vector_difference (sa1, pC->base));
                           f2	= d3Vector_scalar_product (pC->axis, d3Vector_difference (sa2, pC->base));
                           if ((f1 > pC->d3) || (f2 > pC->d3)) {
                              rtn_value = !NO_RAYCROWN_ERRORS;
                           }
                        }
                        path_length	= 0.0;
                        if (rtn_value == NO_RAYCROWN_ERRORS) {
                           if (alpha1 >= 0.0) {
                              if (alpha2 >= 0.0) {
                                 path_length	= fabs(alpha1 - alpha2);
                              } else {
                                 path_length	= fabs(alpha1);
                              }
                           } else {
                              if (alpha2 >= 0.0) {
                                 path_length	= fabs(alpha2);
                              } else {
                                 path_length	= 0.0;
                              }
                           }
                        }
                        GammaH	*= exp(-fabs(pPR->koz_living[tree1.species].y)*cos_theta*path_length);
                        GammaV	*= exp(-fabs(pPR->kez_living[tree1.species].y)*cos_theta*path_length);
                        
#ifdef ENABLE_ATTENUATION_FROM_STEMS
                        /******* look for stem intersection ******/
                        pB        = tree1.Stem.head;
                        nsegments = (int)(pC->base.x[2]/pPR->Amap.dz);
                        if(y < (pC->base.x[2]/sin_theta*cos_theta + pPR->Tree_Location[itree].y)){
                           for (isegment=0; isegment<nsegments; isegment++) {
                              Cylinder_from_Branch(&cyl1,pB,isegment,nsegments);
                              cylinder_value		= RayCylinderIntersection (&ray1, &cyl1, &s_cyl1, &alpha_cyl1, &s_cyl2, &alpha_cyl2);
                              if (cylinder_value == NO_RAYCYLINDER_ERRORS) {
                                 if(alpha_cyl1 >= 0 || alpha_cyl2 >= 0){
                                    GammaH       *=0;
                                    GammaV       *=0;
                                 }
                              }
                           }
                        }
#endif
                        
                     }
                  }
               }
               /**************************************/
               /* Dry crown contribution if required */
               /**************************************/
               
               for (itree=0; itree<pPR->Trees; itree++) {
                  if (fabs (x-pPR->Tree_Location[itree].x) <= pPR->Tree_Location[itree].radius) {
                     if (y > (pPR->Tree_Location[itree].y - pPR->Tree_Location[itree].radius)) {
                        /***********************************************/
                        /* Look for ray intersection with living crown */
                        /***********************************************/
                        Realise_Tree_Crown_Only (&tree1, itree, pPR);
                        pT = &tree1;
                        if(pT->CrownVolume.tail != NULL_PTR2CROWN){
                           pC			= tree1.CrownVolume.tail;
                           rtn_value	= RayCrownIntersection (&ray1, pC, &sa1, &alpha1, &sa2, &alpha2);
                           path_length	= 0.0;
                           if (rtn_value == NO_RAYCROWN_ERRORS) {
                              if (alpha1 >= 0.0) {
                                 if (alpha2 >= 0.0) {
                                    path_length	= fabs(alpha1 - alpha2);
                                 } else {
                                    path_length	= fabs(alpha1);
                                 }
                              } else {
                                 if (alpha2 >= 0.0) {
                                    path_length	= fabs(alpha2);
                                 } else {
                                    path_length	= 0.0;
                                 }
                              }
                           }
                           GammaH	*= exp(-fabs(pPR->koz_dry[tree1.species].y)*cos_theta*path_length);
                           GammaV	*= exp(-fabs(pPR->kez_dry[tree1.species].y)*cos_theta*path_length);
                        }
                     }
                  }
               }
            }
            /******************************************************/
            /* Store the attenuation factors in the look-up table */
            /******************************************************/
            l	= i + j*pPR->Amap.Nx + k*pPR->Amap.Nx*pPR->Amap.Ny;
            pPR->Amap.pBounceH[l]		= GammaH;
            pPR->Amap.pBounceV[l]		= GammaV;
            if (GammaH < gHmin) gHmin	= GammaH;
            if (GammaH > gHmax) gHmax	= GammaH;
            if (GammaV < gVmin) gVmin	= GammaV;
            if (GammaV > gVmax) gVmax	= GammaV;
         }
      }
   }
   Destroy_Tree (&tree1);
   
   
   /*********************************/
   /* Report attenuation map values */
   /*********************************/
   
   fprintf (pPR->pLogFile, "\nOne-way bounce amplitude attenuation extrema:\n\n"); 
   fprintf (pPR->pLogFile, "Min H-pol:\t%12.5e\n", gHmin);
   fprintf (pPR->pLogFile, "Min V-pol:\t%12.5e\n", gVmin);
   fprintf (pPR->pLogFile, "Max H-pol:\t%12.5e\n", gHmax);
   fprintf (pPR->pLogFile, "Max V-pol:\t%12.5e\n", gVmax);
   fflush  (pPR->pLogFile);
   
   /*******************************************************************/
   /* For each attenuation grid location calculate DIRECT attenuation */
   /*******************************************************************/
   
   gHmin	=  1.0e+30;
   gHmax	= -1.0e+30;
   gVmin	=  1.0e+30;
   gVmax	= -1.0e+30;
   
   Create_Tree (&tree1);
   a	= Cartesian_Assign_d3Vector (0.0, -sin_theta, cos_theta);
   for (i=0; i<pPR->Amap.Nx; i++) {
      x		= ((double)i*pPR->Amap.dx) - pPR->Amap.Ax/2.0;
      for (j=0; j<pPR->Amap.Ny; j++) {
         y	=  (Ly/2.0) - Gp - ((double)j*pPR->Amap.dy);
         for (k=0; k<pPR->Amap.Nz; k++) {
            G	= ground_height (pPR, x, y);
            zed	= ((double)k*pPR->Amap.dz);
            z	= G + zed;
            r	= Cartesian_Assign_d3Vector (x, y, z);
            Assign_Ray_d3V (&ray1, &r, &a);
            /***************************************************/
            /* Calculate total attenuation for this grid point */
            /***************************************************/
            GammaH	= 1.0;
            GammaV	= 1.0;
            /*****************************/
            /* Short veggie contribution */
            /*****************************/
            if (zed < pPR->shrt_vegi_depth) {
               GammaH	*= exp(-fabs(pPR->koz_short.y)*(pPR->shrt_vegi_depth-zed));
               GammaV	*= exp(-fabs(pPR->kez_short.y)*(pPR->shrt_vegi_depth-zed));
            }
            /*****************************/
            /* Living crown contribution */
            /*****************************/
            for (itree=0; itree<pPR->Trees; itree++) {
               if (fabs (x-pPR->Tree_Location[itree].x) <= pPR->Tree_Location[itree].radius) {
                  if (y > (pPR->Tree_Location[itree].y - pPR->Tree_Location[itree].radius)) {
                     /***********************************************/
                     /* Look for ray intersection with living crown */
                     /***********************************************/
                     Realise_Tree_Crown_Only (&tree1, itree, pPR);
                     pC          = tree1.CrownVolume.head;
                     rtn_value	= RayCrownIntersection (&ray1, pC, &sa1, &alpha1, &sa2, &alpha2);
                     /**********************************************************************/
                     /* Additional check for solution above crown apex for conical crowns  */
                     /**********************************************************************/
                     if ((rtn_value == NO_RAYCROWN_ERRORS) && (pC->shape == CROWN_CONE)) {
                        f1	= d3Vector_scalar_product (pC->axis, d3Vector_difference (sa1, pC->base));
                        f2	= d3Vector_scalar_product (pC->axis, d3Vector_difference (sa2, pC->base));
                        if ((f1 > pC->d3) || (f2 > pC->d3)) {
                           rtn_value = !NO_RAYCROWN_ERRORS;
                        }
                     }
                     path_length	= 0.0;
                     if (rtn_value == NO_RAYCROWN_ERRORS) {
                        if (alpha1 >= 0.0) {
                           if (alpha2 >= 0.0) {
                              path_length	= fabs(alpha1 - alpha2);
                           } else {
                              path_length	= fabs(alpha1);
                           }
                        } else {
                           if (alpha2 >= 0.0) {
                              path_length	= fabs(alpha2);
                           } else {
                              path_length	= 0.0;
                           }
                        }
                     }
                     GammaH	*= exp(-fabs(pPR->koz_living[tree1.species].y)*cos_theta*path_length);
                     GammaV	*= exp(-fabs(pPR->kez_living[tree1.species].y)*cos_theta*path_length);
                     
#ifdef ENABLE_ATTENUATION_FROM_STEMS
                     /******* look for stem intersection ******/
                     pB = tree1.Stem.head;
                     nsegments = (int)(pC->base.x[2]/pPR->Amap.dz);
                     if(y < (pC->base.x[2]/sin_theta*cos_theta + pPR->Tree_Location[itree].y)){
                        for (isegment=0; isegment<nsegments; isegment++) {
                           Cylinder_from_Branch(&cyl1,pB,isegment,nsegments);
                           cylinder_value		= RayCylinderIntersection (&ray1, &cyl1, &s_cyl1, &alpha_cyl1, &s_cyl2, &alpha_cyl2);
                           if (cylinder_value == NO_RAYCYLINDER_ERRORS) {
                              if(alpha_cyl1 >= 0 || alpha_cyl2 >= 0){
                                 GammaH *=0;
                                 GammaV *=0;
                              }
                           }
                        }
                     }
#endif
                     
                  }
               }
            }
            /**************************************/
            /* Dry crown contribution if required */
            /**************************************/
                        
            for (itree=0; itree<pPR->Trees; itree++) {
               if (fabs (x-pPR->Tree_Location[itree].x) <= pPR->Tree_Location[itree].radius) {
                  if (y > (pPR->Tree_Location[itree].y - pPR->Tree_Location[itree].radius)) {
                     /***********************************************/
                     /* Look for ray intersection with living crown */
                     /***********************************************/
                     Realise_Tree_Crown_Only (&tree1, itree, pPR);
                     pT = &tree1;
                     if(pT->CrownVolume.tail != NULL_PTR2CROWN){
                        pC			= tree1.CrownVolume.tail;
                        rtn_value	= RayCrownIntersection (&ray1, pC, &sa1, &alpha1, &sa2, &alpha2);
                        path_length	= 0.0;
                        if (rtn_value == NO_RAYCROWN_ERRORS) {
                           if (alpha1 >= 0.0) {
                              if (alpha2 >= 0.0) {
                                 path_length	= fabs(alpha1 - alpha2);
                              } else {
                                 path_length	= fabs(alpha1);
                              }
                           } else {
                              if (alpha2 >= 0.0) {
                                 path_length	= fabs(alpha2);
                              } else {
                                 path_length	= 0.0;
                              }
                           }
                        }
                        GammaH	*= exp(-fabs(pPR->koz_dry[tree1.species].y)*cos_theta*path_length);
                        GammaV	*= exp(-fabs(pPR->kez_dry[tree1.species].y)*cos_theta*path_length);
                     }
                  }
               }
            }
            /******************************************************/
            /* Store the attenuation factors in the look-up table */
            /******************************************************/
            l	= i + j*pPR->Amap.Nx + k*pPR->Amap.Nx*pPR->Amap.Ny;
            pPR->Amap.pDirectH[l]		= GammaH;
            pPR->Amap.pDirectV[l]		= GammaV;
            if (GammaH < gHmin) gHmin	= GammaH;
            if (GammaH > gHmax) gHmax	= GammaH;
            if (GammaV < gVmin) gVmin	= GammaV;
            if (GammaV > gVmax) gVmax	= GammaV;
         }
      }
   }
   Destroy_Tree (&tree1);
   
#ifdef ENABLE_ATTENUATION_FROM_STEMS
   Destroy_Cylinder(&cyl1);
#endif
   
   /*********************************/
   /* Report attenuation map values */
   /*********************************/
   
   fprintf (pPR->pLogFile, "\nOne-way direct amplitude attenuation extrema:\n\n"); 
   fprintf (pPR->pLogFile, "Min H-pol:\t%12.5e\n", gHmin);
   fprintf (pPR->pLogFile, "Min V-pol:\t%12.5e\n", gVmin);
   fprintf (pPR->pLogFile, "Max H-pol:\t%12.5e\n", gHmax);
   fprintf (pPR->pLogFile, "Max V-pol:\t%12.5e\n", gVmax);
   fflush  (pPR->pLogFile);
   
   /****************************************************/
   /* Short vegetation layer attenuation look up array */
   /****************************************************/
   
   fprintf (pPR->pLogFile, "\nOne-way direct amplitude attenuation by depth in short vegetation ...\n\n"); 
   fprintf (pPR->pLogFile, "\tdepth\t\tGammaH\tGammaV\n\n");
   for (k=0; k<pPR->Amap.Nds; k++) {
      dk		= k*pPR->Amap.dds;
      GammaH	= exp(-fabs(pPR->koz_short.y)*dk);
      GammaV	= exp(-fabs(pPR->kez_short.y)*dk);
      pPR->Amap.pDirectShortH[k]	= GammaH;
      pPR->Amap.pDirectShortV[k]	= GammaV;
      fprintf (pPR->pLogFile, "\t%lf\t%lf\t%lf\n", dk, pPR->Amap.pDirectShortH[k], pPR->Amap.pDirectShortV[k]);
   }
   fprintf (pPR->pLogFile, "\n");
   fflush  (pPR->pLogFile);
   
   /************************************************/
   /* Create and ouptut attenuation map SIM images */
   /************************************************/
   
   Create_SIM_Record	(&Amap_Image);
   
   AmapFilename	= (char*) calloc (strlen(pPR->pMasterDirectory)+strlen("AmapDirectH.sim")+1, sizeof(char));
   strcpy  (AmapFilename, pPR->pMasterDirectory);
   strcat  (AmapFilename, "AmapDirectH.sim");
   
   char  text[50];
   sprintf(text, "PolSARproSim attenuation map, Nz = %d",pPR->Amap.Nz); 
   //   Initialise_SIM_Record (&Amap_Image, AmapFilename, pPR->Amap.Nx, pPR->Amap.Ny*pPR->Amap.Nz, SIM_FLOAT_TYPE, 
   //                          pPR->Lx, pPR->Ly*pPR->Amap.Nz, "PolSARproSim attenuation map");
   Initialise_SIM_Record (&Amap_Image, AmapFilename, pPR->Amap.Nx, pPR->Amap.Ny*pPR->Amap.Nz, SIM_FLOAT_TYPE, 
                          pPR->Lx, pPR->Ly*pPR->Amap.Nz, text);
   
   p.simpixeltype	= Amap_Image.pixel_type;
   for (i=0; i<pPR->Amap.Nx; i++) {
      for (j=0; j<pPR->Amap.Ny; j++) {
         for (k=0; k<pPR->Amap.Nz; k++) {
            l			= i + j*pPR->Amap.Nx + k*pPR->Amap.Nx*pPR->Amap.Ny;
            GammaH		= pPR->Amap.pDirectH[l];
            p.data.f	= (float) GammaH;
            px			= i;
            py			= j + pPR->Amap.Ny*k;
            putSIMpixel (&Amap_Image, p, px, py);
         }
      }
   }
   
#ifndef POLSARPROSIM_NOSIMOUTPUT
   Write_SIM_Record	(&Amap_Image);
#endif
   
   free (AmapFilename);
   AmapFilename	= (char*) calloc (strlen(pPR->pMasterDirectory)+strlen("AmapDirectV.sim")+1, sizeof(char));
   strcpy  (AmapFilename, pPR->pMasterDirectory);
   strcat  (AmapFilename, "AmapDirectV.sim");
   Rename_SIM_Record (&Amap_Image, AmapFilename);
   
   for (i=0; i<pPR->Amap.Nx; i++) {
      for (j=0; j<pPR->Amap.Ny; j++) {
         for (k=0; k<pPR->Amap.Nz; k++) {
            l			= i + j*pPR->Amap.Nx + k*pPR->Amap.Nx*pPR->Amap.Ny;
            GammaV		= pPR->Amap.pDirectV[l];
            p.data.f	= (float) GammaV;
            px			= i;
            py			= j + pPR->Amap.Ny*k;
            putSIMpixel (&Amap_Image, p, px, py);
         }
      }
   }
   
#ifndef POLSARPROSIM_NOSIMOUTPUT
   Write_SIM_Record	(&Amap_Image);
#endif
   
   free (AmapFilename);
   AmapFilename	= (char*) calloc (strlen(pPR->pMasterDirectory)+strlen("AmapBounceH.sim")+1, sizeof(char));
   strcpy  (AmapFilename, pPR->pMasterDirectory);
   strcat  (AmapFilename, "AmapBounceH.sim");
   Rename_SIM_Record (&Amap_Image, AmapFilename);
   
   for (i=0; i<pPR->Amap.Nx; i++) {
      for (j=0; j<pPR->Amap.Ny; j++) {
         for (k=0; k<pPR->Amap.Nz; k++) {
            l			= i + j*pPR->Amap.Nx + k*pPR->Amap.Nx*pPR->Amap.Ny;
            GammaV		= pPR->Amap.pBounceH[l];
            p.data.f	= (float) GammaV;
            px			= i;
            py			= j + pPR->Amap.Ny*k;
            putSIMpixel (&Amap_Image, p, px, py);
         }
      }
   }
   
#ifndef POLSARPROSIM_NOSIMOUTPUT
   Write_SIM_Record	(&Amap_Image);
#endif
   
   free (AmapFilename);
   AmapFilename	= (char*) calloc (strlen(pPR->pMasterDirectory)+strlen("AmapBounceV.sim")+1, sizeof(char));
   strcpy  (AmapFilename, pPR->pMasterDirectory);
   strcat  (AmapFilename, "AmapBounceV.sim");
   Rename_SIM_Record (&Amap_Image, AmapFilename);
   
   for (i=0; i<pPR->Amap.Nx; i++) {
      for (j=0; j<pPR->Amap.Ny; j++) {
         for (k=0; k<pPR->Amap.Nz; k++) {
            l			= i + j*pPR->Amap.Nx + k*pPR->Amap.Nx*pPR->Amap.Ny;
            GammaV		= pPR->Amap.pBounceV[l];
            p.data.f	= (float) GammaV;
            px			= i;
            py			= j + pPR->Amap.Ny*k;
            putSIMpixel (&Amap_Image, p, px, py);
         }
      }
   }
   
#ifndef POLSARPROSIM_NOSIMOUTPUT
   Write_SIM_Record	(&Amap_Image);
#endif
   
   free (AmapFilename);
   
   Destroy_SIM_Record (&Amap_Image);
   
   /******************************************/
   /* Report call if running in VERBOSE mode */
   /******************************************/
   
#ifdef VERBOSE_POLSARPROSIM
   printf ("\n");
   printf ("... Returning from call to Attenuation_Map\n");
   printf ("\n");
#endif
   fprintf (pPR->pLogFile, "... Returning from call to Attenuation_Map\n\n");
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
   
   return;
}

/************************************************/
/* Computes the attenuation factor Gamma for    */
/* double bounce scattering from all trees that */
/* affect an x,y,z location. This routine is    */
/* called by Attenuation_Map_SMP() as a thread  */
/* for every z location                         */
/************************************************/
void     *Compute_Bounce_Gamma            (void *threadarg)
{
   double               x,y,z;
   int                  k;
   d3Vector             r;
   d3Vector             ar;
   Ray                  ray1;
   double               G, zed;
   double               GammaH, GammaV;
   int                  itree;
   Crown                *pC;
   Tree                 tree1;
   Tree                 *pT;
   d3Vector             sa1, sa2;
   double               alpha1, alpha2;
   int                  rtn_value;
   double               path_length;
   double               cos_theta, sin_theta;
   double               f1, f2;
   
   Amap_Thread_Arg      *pTA;
   PolSARproSim_Record  *pPR;
   
#ifdef ENABLE_ATTENUATION_FROM_STEMS
   Branch      *pB; 
   Cylinder    cyl1; 
   int         nsegments, isegment, cylinder_value;
   d3Vector		s_cyl1;
   double		alpha_cyl1;
   d3Vector		s_cyl2;
   double		alpha_cyl2;
#endif
   
   
   /* do some assignments */
   pTA         = (Amap_Thread_Arg *)threadarg;
   x           = pTA->x;    /* x-axis location */
   y           = pTA->y;    /* y-axis location */
   k           = pTA->k;    /* z-axis index (also thread index) */
   ar          = pTA->ar;   /* ray direction */
   pPR         = pTA->pPR;  /* pointer to Master_Record */
   cos_theta	= cos(pPR->incidence_angle[0]);
   sin_theta	= sin(pPR->incidence_angle[0]);
   
#ifdef ENABLE_ATTENUATION_FROM_STEMS
   Create_Cylinder	(&cyl1);
#endif
   Create_Tree (&tree1); 
   
   G     = ground_height (pPR, x, y);
   zed	= ((double)k*pPR->Amap.dz);
   z     = G + zed;
   r     = Cartesian_Assign_d3Vector (x, y, z);
   Assign_Ray_d3V (&ray1, &r, &ar);
   /***************************************************/
   /* Calculate total attenuation for this grid point */
   /***************************************************/
   GammaH	= 1.0;
   GammaV	= 1.0;
   /*****************************/
   /* Short veggie contribution */
   /*****************************/
   if (zed < pPR->shrt_vegi_depth) {
      GammaH	*= exp(-fabs(pPR->koz_short.y)*zed);
      GammaV	*= exp(-fabs(pPR->kez_short.y)*zed);
   } else {
      GammaH	*= exp(-fabs(pPR->koz_short.y)*pPR->shrt_vegi_depth);
      GammaV	*= exp(-fabs(pPR->kez_short.y)*pPR->shrt_vegi_depth);
      /*****************************/
      /* Living crown contribution */
      /*****************************/
      for (itree=0; itree<pPR->Trees; itree++) {
         if (fabs (x-pPR->Tree_Location[itree].x) <= pPR->Tree_Location[itree].radius) {
            if (y > (pPR->Tree_Location[itree].y - pPR->Tree_Location[itree].radius)) {
               /***********************************************/
               /* Look for ray intersection with living crown */
               /***********************************************/
               Realise_Tree_Crown_Only (&tree1, itree, pPR);
               pC          = tree1.CrownVolume.head;
               rtn_value	= RayCrownIntersection (&ray1, pC, &sa1, &alpha1, &sa2, &alpha2);
               /**********************************************************************/
               /* Additional check for solution above crown apex for conical crowns  */
               /**********************************************************************/
               if ((rtn_value == NO_RAYCROWN_ERRORS) && (pC->shape == CROWN_CONE)) {
                  f1	= d3Vector_scalar_product (pC->axis, d3Vector_difference (sa1, pC->base));
                  f2	= d3Vector_scalar_product (pC->axis, d3Vector_difference (sa2, pC->base));
                  if ((f1 > pC->d3) || (f2 > pC->d3)) {
                     rtn_value = !NO_RAYCROWN_ERRORS;
                  }
               }
               path_length	= 0.0;
               if (rtn_value == NO_RAYCROWN_ERRORS) {
                  if (alpha1 >= 0.0) {
                     if (alpha2 >= 0.0) {
                        path_length	= fabs(alpha1 - alpha2);
                     } else {
                        path_length	= fabs(alpha1);
                     }
                  } else {
                     if (alpha2 >= 0.0) {
                        path_length	= fabs(alpha2);
                     } else {
                        path_length	= 0.0;
                     }
                  }
               }
               GammaH	*= exp(-fabs(pPR->koz_living[tree1.species].y)*cos_theta*path_length);
               GammaV	*= exp(-fabs(pPR->kez_living[tree1.species].y)*cos_theta*path_length);
               
#ifdef ENABLE_ATTENUATION_FROM_STEMS
               /******* look for stem intersection ******/
               pB        = tree1.Stem.head;
               nsegments = (int)(pC->base.x[2]/pPR->Amap.dz);
               if(y < (pC->base.x[2]/sin_theta*cos_theta + pPR->Tree_Location[itree].y)){
                  for (isegment=0; isegment<nsegments; isegment++) {
                     Cylinder_from_Branch(&cyl1,pB,isegment,nsegments);
                     cylinder_value		= RayCylinderIntersection (&ray1, &cyl1, &s_cyl1, &alpha_cyl1, &s_cyl2, &alpha_cyl2);
                     if (cylinder_value == NO_RAYCYLINDER_ERRORS) {
                        if(alpha_cyl1 >= 0 || alpha_cyl2 >= 0){
                           GammaH       *=0;
                           GammaV       *=0;
                        }
                     }
                  }
               }
#endif
               /**************************************/
               /* Dry crown contribution if required */
               /**************************************/
               pT = &tree1;
               if(pT->CrownVolume.tail != NULL_PTR2CROWN){
                  pC			= tree1.CrownVolume.tail;
                  rtn_value	= RayCrownIntersection (&ray1, pC, &sa1, &alpha1, &sa2, &alpha2);
                  path_length	= 0.0;
                  if (rtn_value == NO_RAYCROWN_ERRORS) {
                     if (alpha1 >= 0.0) {
                        if (alpha2 >= 0.0) {
                           path_length	= fabs(alpha1 - alpha2);
                        } else {
                           path_length	= fabs(alpha1);
                        }
                     } else {
                        if (alpha2 >= 0.0) {
                           path_length	= fabs(alpha2);
                        } else {
                           path_length	= 0.0;
                        }
                     }
                  }
                  GammaH	*= exp(-fabs(pPR->koz_dry[tree1.species].y)*cos_theta*path_length);
                  GammaV	*= exp(-fabs(pPR->kez_dry[tree1.species].y)*cos_theta*path_length);
               }/* end dry crown contribution */
            }/* end condition on range pixels in shadow */
         }/* end condition on azimuth pixels in shadow */
      }/* end loop on trees */
   }/* end condition on height above short veg depth */
   
   /* assign return variables */
   pTA->GammaH = GammaH;
   pTA->GammaV = GammaV;
   
   /* clean up */
   Destroy_Tree (&tree1);
#ifdef ENABLE_ATTENUATION_FROM_STEMS
   Destroy_Cylinder(&cyl1);
#endif
   
   pthread_exit(NULL);
}
/************************************************/
/* Computes the attenuation factor Gamma for    */
/* direct scattering from all trees that        */
/* affect an x,y,z location. This routine is    */
/* called by Attenuation_Map_SMP() as a thread  */
/* for every z location                         */
/************************************************/
void     *Compute_Direct_Gamma            (void *threadarg)
{
   double               x,y,z;
   int                  k;
   d3Vector             r;
   d3Vector             ar;
   Ray                  ray1;
   double               G, zed;
   double               GammaH, GammaV;
   int                  itree;
   Crown                *pC;
   Tree                 tree1;
   Tree                 *pT;
   d3Vector             sa1, sa2;
   double               alpha1, alpha2;
   int                  rtn_value;
   double               path_length;
   double               cos_theta, sin_theta;
   double               f1, f2;
   
   Amap_Thread_Arg      *pTA;
   PolSARproSim_Record  *pPR;
   
#ifdef ENABLE_ATTENUATION_FROM_STEMS
   Branch      *pB; 
   Cylinder    cyl1; 
   int         nsegments, isegment, cylinder_value;
   d3Vector		s_cyl1;
   double		alpha_cyl1;
   d3Vector		s_cyl2;
   double		alpha_cyl2;
#endif
   
   /* do some assignments */
   pTA         = (Amap_Thread_Arg *)threadarg;
   x           = pTA->x;    // x-axis location
   y           = pTA->y;    // y-axis location
   k           = pTA->k;    // z-axis index (also thread index)
   ar          = pTA->ar;   // ray direction
   pPR         = pTA->pPR;  // address to Master_Record
   cos_theta	= cos(pPR->incidence_angle[0]);
   sin_theta	= sin(pPR->incidence_angle[0]);
   
#ifdef ENABLE_ATTENUATION_FROM_STEMS
   Create_Cylinder	(&cyl1);
#endif
   Create_Tree (&tree1); 
   G	= ground_height (pPR, x, y);
   zed	= ((double)k*pPR->Amap.dz);
   z	= G + zed;
   r	= Cartesian_Assign_d3Vector (x, y, z);
   Assign_Ray_d3V (&ray1, &r, &ar);
   /***************************************************/
   /* Calculate total attenuation for this grid point */
   /***************************************************/
   GammaH	= 1.0;
   GammaV	= 1.0;
   /*****************************/
   /* Short veggie contribution */
   /*****************************/
   if (zed < pPR->shrt_vegi_depth) {
      GammaH	*= exp(-fabs(pPR->koz_short.y)*(pPR->shrt_vegi_depth-zed));
      GammaV	*= exp(-fabs(pPR->kez_short.y)*(pPR->shrt_vegi_depth-zed));
   }
   /*****************************/
   /* Living crown contribution */
   /*****************************/
   for (itree=0; itree<pPR->Trees; itree++) {
       if (fabs (x-pPR->Tree_Location[itree].x) <= pPR->Tree_Location[itree].radius) {
         if (y > (pPR->Tree_Location[itree].y - pPR->Tree_Location[itree].radius)) {
            /***********************************************/
            /* Look for ray intersection with living crown */
            /***********************************************/
            Realise_Tree_Crown_Only (&tree1, itree, pPR);
            pC          = tree1.CrownVolume.head;
            rtn_value	= RayCrownIntersection (&ray1, pC, &sa1, &alpha1, &sa2, &alpha2);
            /**********************************************************************/
            /* Additional check for solution above crown apex for conical crowns  */
            /**********************************************************************/
            if ((rtn_value == NO_RAYCROWN_ERRORS) && (pC->shape == CROWN_CONE)) {
               f1	= d3Vector_scalar_product (pC->axis, d3Vector_difference (sa1, pC->base));
               f2	= d3Vector_scalar_product (pC->axis, d3Vector_difference (sa2, pC->base));
               if ((f1 > pC->d3) || (f2 > pC->d3)) {
                  rtn_value = !NO_RAYCROWN_ERRORS;
               }
            }
            path_length	= 0.0;
            if (rtn_value == NO_RAYCROWN_ERRORS) {
               if (alpha1 >= 0.0) {
                  if (alpha2 >= 0.0) {
                     path_length	= fabs(alpha1 - alpha2);
                  } else {
                     path_length	= fabs(alpha1);
                  }
               } else {
                  if (alpha2 >= 0.0) {
                     path_length	= fabs(alpha2);
                  } else {
                     path_length	= 0.0;
                  }
               }
            }
            GammaH	*= exp(-fabs(pPR->koz_living[tree1.species].y)*cos_theta*path_length);
            GammaV	*= exp(-fabs(pPR->kez_living[tree1.species].y)*cos_theta*path_length);
            
#ifdef ENABLE_ATTENUATION_FROM_STEMS
            /******* look for stem intersection ******/
            pB = tree1.Stem.head;
            nsegments = (int)(pC->base.x[2]/pPR->Amap.dz);
            if(y < (pC->base.x[2]/sin_theta*cos_theta + pPR->Tree_Location[itree].y)){
               for (isegment=0; isegment<nsegments; isegment++) {
                  Cylinder_from_Branch(&cyl1,pB,isegment,nsegments);
                  cylinder_value		= RayCylinderIntersection (&ray1, &cyl1, &s_cyl1, &alpha_cyl1, &s_cyl2, &alpha_cyl2);
                  if (cylinder_value == NO_RAYCYLINDER_ERRORS) {
                     if(alpha_cyl1 >= 0 || alpha_cyl2 >= 0){
                        GammaH *=0;
                        GammaV *=0;
                     }
                  }
               }
            }
#endif
            /**************************************/
            /* Dry crown contribution if required */
            /**************************************/
            pT = &tree1;
            if(pT->CrownVolume.tail != NULL_PTR2CROWN){
               pC          = tree1.CrownVolume.tail;
               rtn_value	= RayCrownIntersection (&ray1, pC, &sa1, &alpha1, &sa2, &alpha2);
               path_length	= 0.0;
               if (rtn_value == NO_RAYCROWN_ERRORS) {
                  if (alpha1 >= 0.0) {
                     if (alpha2 >= 0.0) {
                        path_length	= fabs(alpha1 - alpha2);
                     } else {
                        path_length	= fabs(alpha1);
                     }
                  } else {
                     if (alpha2 >= 0.0) {
                        path_length	= fabs(alpha2);
                     } else {
                        path_length	= 0.0;
                     }
                  }
               }
               GammaH	*= exp(-fabs(pPR->koz_dry[tree1.species].y)*cos_theta*path_length);
               GammaV	*= exp(-fabs(pPR->kez_dry[tree1.species].y)*cos_theta*path_length);
            }/* end condition on dry crown contribution */
         }/* end condition on range pixels in shadow */
      }/* end condition on azimuth pixels in shadow */
   }/* end loop on trees */
   
   /* assignment return variables */
   pTA->GammaH = GammaH;
   pTA->GammaV = GammaV;
   
   /* clean up */
   Destroy_Tree (&tree1);
#ifdef ENABLE_ATTENUATION_FROM_STEMS
   Destroy_Cylinder(&cyl1);
#endif
   /* exit */
   pthread_exit(NULL);
}


/******************************************/
/* Multi-processor version of the routine */
/* Attenuation_Map()                      */
/******************************************/
void		Attenuation_Map_SMP					(PolSARproSim_Record *pPR)
{
   int         i, j, k;
   double		Sr			= pPR->Stand_Radius;
   double		Cr			= pPR->mean_crown_radius;
   double		Ls			= pPR->Shadow_Distance;
   double		Hs			= pPR->max_tree_height; /* --RAedit */
   double		Gp			= pPR->Gap_Distance;
   double		Ll			= pPR->Layover_Distance;
   double		Lx			= pPR->Lx;
   double		Ly			= pPR->Ly;
   double		x, y;
   d3Vector    a;
   double		GammaH, GammaV;
   double		cos_theta	= cos(pPR->incidence_angle[0]);
   double		sin_theta	= sin(pPR->incidence_angle[0]);
   long        l;
   double		gHmin, gHmax;
   double		gVmin, gVmax;
   SIM_Record	Amap_Image;
   sim_pixel	p;
   int         px, py;
   d3Vector    n;
   d3Vector    ar;
   d3Vector    kihat, krhat;
   double		kidotn;
   char        *AmapFilename;
   double		dk;
      
   /* some variables for hyperthreading */
   Amap_Thread_Arg      *threadarg; /* pointer to array of thread arguments   */
   pthread_t            *threads;   /* pointer to arry of thread ids          */
   pthread_attr_t       attr;       /* a global thread attribute              */
   int                  rc;         /* thread return code                     */
   void                 *status;    /* thread status                          */
   /* initialize thread variables */
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
   
   /******************************************/
   /* Report call if running in VERBOSE mode */
   /******************************************/
   
#ifdef VERBOSE_POLSARPROSIM
   printf ("\n");
   printf ("Call to Attenuation_Map ... \n");
   printf ("\n");
#endif
   fprintf (pPR->pLogFile, "Call to Attenuation_Map ... \n");
   fflush  (pPR->pLogFile);
   
   pPR->Amap.Ax	= Lx - 2.0*Gp;
   pPR->Amap.Ay	= Ly - Ll - 2.0*Gp;
   pPR->Amap.Az	= Hs;
   pPR->Amap.Nx	= 2*(((int)(pPR->Amap.Ax / (AMAP_RESOLUTION_FACTOR*pPR->azimuth_resolution)))/2)+1;
   if (pPR->Amap.Nx < 3) {
      pPR->Amap.Nx	= 3;
   }
   pPR->Amap.Ny	= 2*(((int)(pPR->Amap.Ay / (AMAP_RESOLUTION_FACTOR*pPR->ground_range_resolution[0])))/2)+1;
   if (pPR->Amap.Ny < 3) {
      pPR->Amap.Ny	= 3;
   }
   pPR->Amap.dx	= pPR->Amap.Ax/(double)(pPR->Amap.Nx-1);
   pPR->Amap.dy	= pPR->Amap.Ay/(double)(pPR->Amap.Ny-1);
   pPR->Amap.dz   = AMAP_VERTICAL_RESOLUTION;  /* set to a predefined resolution */ 
   pPR->Amap.Nz	= 2*(((int)(pPR->Amap.Az / pPR->Amap.dz))/2)+1;
   if (pPR->Amap.Nz < 3) {
      pPR->Amap.Nz	= 3;
   }
   pPR->Amap.dz	= pPR->Amap.Az/(double)(pPR->Amap.Nz-1);
   pPR->Amap.n    = pPR->Amap.Nx*pPR->Amap.Ny*pPR->Amap.Nz;
   
   pPR->Amap.Nds	= AMAP_SHORT_VEGI_NZ;
   pPR->Amap.Ads	= pPR->shrt_vegi_depth;
   pPR->Amap.dds	= pPR->Amap.Ads / (double) (pPR->Amap.Nds - 1);
   
   /**********************************/
   /* Report attenuation map details */
   /**********************************/
   
   fprintf (pPR->pLogFile, "\n");
   fprintf (pPR->pLogFile, "Stand_Radius     \t=\t%12.5e\n", Sr);
   fprintf (pPR->pLogFile, "Mean_crown_radius\t=\t%12.5e\n", Cr);
   fprintf (pPR->pLogFile, "Shadow_Distance  \t=\t%12.5e\n", Ls);
   fprintf (pPR->pLogFile, "mean_tree_height \t=\t%12.5e\n", Hs);
   fprintf (pPR->pLogFile, "Attenuation map width \t=\t%12.5em\n", pPR->Amap.Ax);
   fprintf (pPR->pLogFile, "Attenuation map length\t=\t%12.5em\n", pPR->Amap.Ay);
   fprintf (pPR->pLogFile, "Attenuation map depth \t=\t%12.5em\n", pPR->Amap.Az);
   fprintf (pPR->pLogFile, "Attenuation map dimensions:\t%5d\t%5d\t%5d\n", pPR->Amap.Nx, pPR->Amap.Ny, pPR->Amap.Nz);
   fprintf (pPR->pLogFile, "\n");
   fflush  (pPR->pLogFile);
   
   /***************************************/
   /* Allocate attenuation factor storage */
   /***************************************/
   
   pPR->Amap.pDirectH			= (double*) calloc (pPR->Amap.n, sizeof (double));
   pPR->Amap.pDirectV			= (double*) calloc (pPR->Amap.n, sizeof (double));
   pPR->Amap.pBounceH			= (double*) calloc (pPR->Amap.n, sizeof (double));
   pPR->Amap.pBounceV			= (double*) calloc (pPR->Amap.n, sizeof (double));
   pPR->Amap.pDirectShortH    = (double*) calloc (AMAP_SHORT_VEGI_NZ, sizeof(double));
   pPR->Amap.pDirectShortV    = (double*) calloc (AMAP_SHORT_VEGI_NZ, sizeof(double));
   /* for threads */
   threadarg = (Amap_Thread_Arg *)calloc(pPR->Amap.Nz,sizeof(Amap_Thread_Arg));
   threads   = (pthread_t *)calloc(pPR->Amap.Nz,sizeof(pthread_t));
   
   /*******************************************************************/
   /* For each attenuation grid location calculate BOUNCE attenuation */
   /*******************************************************************/
   
   gHmin    =  1.0e+30;
   gHmax    = -1.0e+30;
   gVmin    =  1.0e+30;
   gVmax    = -1.0e+30;
   kihat    = Cartesian_Assign_d3Vector (0.0, sin_theta, -cos_theta);
   n        = Cartesian_Assign_d3Vector (-pPR->slope_x, -pPR->slope_y, 1.0);
   d3Vector_insitu_normalise (&n);
   kidotn	= d3Vector_scalar_product (kihat, n);
   krhat    = d3Vector_difference (kihat, d3Vector_double_multiply (n, 2.0*kidotn));
   a        = d3Vector_double_multiply (kihat, -1.0);
   ar       = d3Vector_double_multiply (krhat, -1.0);
   for (i=0; i<pPR->Amap.Nx; i++) {
      x		= ((double)i*pPR->Amap.dx) - pPR->Amap.Ax/2.0;
      for (j=0; j<pPR->Amap.Ny; j++) {
         y	=  (Ly/2.0) - Gp - ((double)j*pPR->Amap.dy);
         /* loop to create threads */
         for (k=0; k<pPR->Amap.Nz; k++) {
            /* set the thread argument */
            threadarg[k].k    = k;
            threadarg[k].x    = x;
            threadarg[k].y    = y;
            Copy_d3Vector(&(threadarg[k].ar), &ar);
            threadarg[k].pPR  = pPR;
            /* create threads */
            rc=pthread_create(&threads[k], &attr, Compute_Bounce_Gamma, (void *)&threadarg[k]);
            if(rc){
               printf("Oops! Thread for height level %d was not created by pthread_create()\n", k);
               exit(-1);
            }
         }
         /* loop to join the created threads (runs blocking) */
         for (k=0; k<pPR->Amap.Nz; k++) {
            rc=pthread_join(threads[k], &status);
            if(rc){
               printf("ERR: unable to join thread %d (also height level) in Attenuation_Map_SMP()[bounce], code: %d\n", k,rc);
               exit(-1);
            }
         }
         /* loop to store results */
         for (k=0; k<pPR->Amap.Nz; k++) {
            /******************************************************/
            /* Store the attenuation factors in the look-up table */
            /******************************************************/
            l                          = i + j*pPR->Amap.Nx + k*pPR->Amap.Nx*pPR->Amap.Ny;
            GammaH                     = threadarg[k].GammaH;
            GammaV                     = threadarg[k].GammaV;
            pPR->Amap.pBounceH[l]		= GammaH;
            pPR->Amap.pBounceV[l]		= GammaV;
            if (GammaH < gHmin) gHmin	= GammaH;
            if (GammaH > gHmax) gHmax	= GammaH;
            if (GammaV < gVmin) gVmin	= GammaV;
            if (GammaV > gVmax) gVmax	= GammaV;
         }
       }/* end loop on y-dimension */
   }/* end loop on x-dimension */
      
   /*********************************/
   /* Report attenuation map values */
   /*********************************/
   
   fprintf (pPR->pLogFile, "\nOne-way bounce amplitude attenuation extrema:\n\n"); 
   fprintf (pPR->pLogFile, "Min H-pol:\t%12.5e\n", gHmin);
   fprintf (pPR->pLogFile, "Min V-pol:\t%12.5e\n", gVmin);
   fprintf (pPR->pLogFile, "Max H-pol:\t%12.5e\n", gHmax);
   fprintf (pPR->pLogFile, "Max V-pol:\t%12.5e\n", gVmax);
   fflush  (pPR->pLogFile);
   
   /*******************************************************************/
   /* For each attenuation grid location calculate DIRECT attenuation */
   /*******************************************************************/
   
   gHmin	=  1.0e+30;
   gHmax	= -1.0e+30;
   gVmin	=  1.0e+30;
   gVmax	= -1.0e+30;
   
   a	= Cartesian_Assign_d3Vector (0.0, -sin_theta, cos_theta);
   for (i=0; i<pPR->Amap.Nx; i++) {
      x		= ((double)i*pPR->Amap.dx) - pPR->Amap.Ax/2.0;
      for (j=0; j<pPR->Amap.Ny; j++) {
         y	=  (Ly/2.0) - Gp - ((double)j*pPR->Amap.dy);
         /* loop to create threads */
         for (k=0; k<pPR->Amap.Nz; k++) {
            /* set the thread argument */
            threadarg[k].k    = k;
            threadarg[k].x    = x;
            threadarg[k].y    = y;
            Copy_d3Vector(&(threadarg[k].ar), &a);
            threadarg[k].pPR  = pPR;
            /* create threads */
            rc = pthread_create(&threads[k], &attr, Compute_Direct_Gamma, (void *)&threadarg[k]);
            if(rc){
               printf("Oops! Thread for height level %d was not created by pthread_create()\n", k);
               exit(-1);
            }
         }
         /* loop to join the created threads */
         for (k=0; k<pPR->Amap.Nz; k++) {
            rc=pthread_join(threads[k], &status);
            if(rc){
               printf("ERR: unable to join thread %d (also height level) in Attenuation_Map_SMP()[direct], code: %d\n", k,rc);
               exit(-1);
            }
         }
         /* loop to store results */
         for (k=0; k<pPR->Amap.Nz; k++) {
            /******************************************************/
            /* Store the attenuation factors in the look-up table */
            /******************************************************/
            l                          = i + j*pPR->Amap.Nx + k*pPR->Amap.Nx*pPR->Amap.Ny;
            GammaH                     = threadarg[k].GammaH;
            GammaV                     = threadarg[k].GammaV;
            pPR->Amap.pDirectH[l]		= GammaH;
            pPR->Amap.pDirectV[l]		= GammaV;
            if (GammaH < gHmin) gHmin	= GammaH;
            if (GammaH > gHmax) gHmax	= GammaH;
            if (GammaV < gVmin) gVmin	= GammaV;
            if (GammaV > gVmax) gVmax	= GammaV;
         }
      }/* end loop on y-dimension */
   }/* end loop on x-dimension */
      
   /*********************************/
   /* Report attenuation map values */
   /*********************************/
   
   fprintf (pPR->pLogFile, "\nOne-way direct amplitude attenuation extrema:\n\n"); 
   fprintf (pPR->pLogFile, "Min H-pol:\t%12.5e\n", gHmin);
   fprintf (pPR->pLogFile, "Min V-pol:\t%12.5e\n", gVmin);
   fprintf (pPR->pLogFile, "Max H-pol:\t%12.5e\n", gHmax);
   fprintf (pPR->pLogFile, "Max V-pol:\t%12.5e\n", gVmax);
   fflush  (pPR->pLogFile);
   
   /****************************************************/
   /* Short vegetation layer attenuation look up array */
   /****************************************************/
   
   fprintf (pPR->pLogFile, "\nOne-way direct amplitude attenuation by depth in short vegetation ...\n\n"); 
   fprintf (pPR->pLogFile, "\tdepth\t\tGammaH\tGammaV\n\n");
   for (k=0; k<pPR->Amap.Nds; k++) {
      dk                         = k*pPR->Amap.dds;
      GammaH                     = exp(-fabs(pPR->koz_short.y)*dk);
      GammaV                     = exp(-fabs(pPR->kez_short.y)*dk);
      pPR->Amap.pDirectShortH[k]	= GammaH;
      pPR->Amap.pDirectShortV[k]	= GammaV;
      fprintf (pPR->pLogFile, "\t%lf\t%lf\t%lf\n", dk, pPR->Amap.pDirectShortH[k], pPR->Amap.pDirectShortV[k]);
   }
   fprintf (pPR->pLogFile, "\n");
   fflush  (pPR->pLogFile);
   
   /************************************************/
   /* Create and ouptut attenuation map SIM images */
   /************************************************/
   
   Create_SIM_Record	(&Amap_Image);
   
   AmapFilename	= (char*) calloc (strlen(pPR->pMasterDirectory)+strlen("AmapDirectH.sim")+1, sizeof(char));
   strcpy  (AmapFilename, pPR->pMasterDirectory);
   strcat  (AmapFilename, "AmapDirectH.sim");
   
   char  text[50];
   sprintf(text, "PolSARproSim attenuation map, Nz = %d",pPR->Amap.Nz); 
   //   Initialise_SIM_Record (&Amap_Image, AmapFilename, pPR->Amap.Nx, pPR->Amap.Ny*pPR->Amap.Nz, SIM_FLOAT_TYPE, 
   //                          pPR->Lx, pPR->Ly*pPR->Amap.Nz, "PolSARproSim attenuation map");
   Initialise_SIM_Record (&Amap_Image, AmapFilename, pPR->Amap.Nx, pPR->Amap.Ny*pPR->Amap.Nz, SIM_FLOAT_TYPE, 
                          pPR->Lx, pPR->Ly*pPR->Amap.Nz, text);
   
   p.simpixeltype	= Amap_Image.pixel_type;
   for (i=0; i<pPR->Amap.Nx; i++) {
      for (j=0; j<pPR->Amap.Ny; j++) {
         for (k=0; k<pPR->Amap.Nz; k++) {
            l			= i + j*pPR->Amap.Nx + k*pPR->Amap.Nx*pPR->Amap.Ny;
            GammaH		= pPR->Amap.pDirectH[l];
            p.data.f	= (float) GammaH;
            px			= i;
            py			= j + pPR->Amap.Ny*k;
            putSIMpixel (&Amap_Image, p, px, py);
         }
      }
   }
   
#ifndef POLSARPROSIM_NOSIMOUTPUT
   Write_SIM_Record	(&Amap_Image);
#endif
   
   free (AmapFilename);
   AmapFilename	= (char*) calloc (strlen(pPR->pMasterDirectory)+strlen("AmapDirectV.sim")+1, sizeof(char));
   strcpy  (AmapFilename, pPR->pMasterDirectory);
   strcat  (AmapFilename, "AmapDirectV.sim");
   Rename_SIM_Record (&Amap_Image, AmapFilename);
   
   for (i=0; i<pPR->Amap.Nx; i++) {
      for (j=0; j<pPR->Amap.Ny; j++) {
         for (k=0; k<pPR->Amap.Nz; k++) {
            l			= i + j*pPR->Amap.Nx + k*pPR->Amap.Nx*pPR->Amap.Ny;
            GammaV		= pPR->Amap.pDirectV[l];
            p.data.f	= (float) GammaV;
            px			= i;
            py			= j + pPR->Amap.Ny*k;
            putSIMpixel (&Amap_Image, p, px, py);
         }
      }
   }
   
#ifndef POLSARPROSIM_NOSIMOUTPUT
   Write_SIM_Record	(&Amap_Image);
#endif
   
   free (AmapFilename);
   AmapFilename	= (char*) calloc (strlen(pPR->pMasterDirectory)+strlen("AmapBounceH.sim")+1, sizeof(char));
   strcpy  (AmapFilename, pPR->pMasterDirectory);
   strcat  (AmapFilename, "AmapBounceH.sim");
   Rename_SIM_Record (&Amap_Image, AmapFilename);
   
   for (i=0; i<pPR->Amap.Nx; i++) {
      for (j=0; j<pPR->Amap.Ny; j++) {
         for (k=0; k<pPR->Amap.Nz; k++) {
            l			= i + j*pPR->Amap.Nx + k*pPR->Amap.Nx*pPR->Amap.Ny;
            GammaV		= pPR->Amap.pBounceH[l];
            p.data.f	= (float) GammaV;
            px			= i;
            py			= j + pPR->Amap.Ny*k;
            putSIMpixel (&Amap_Image, p, px, py);
         }
      }
   }
   
#ifndef POLSARPROSIM_NOSIMOUTPUT
   Write_SIM_Record	(&Amap_Image);
#endif
   
   free (AmapFilename);
   AmapFilename	= (char*) calloc (strlen(pPR->pMasterDirectory)+strlen("AmapBounceV.sim")+1, sizeof(char));
   strcpy  (AmapFilename, pPR->pMasterDirectory);
   strcat  (AmapFilename, "AmapBounceV.sim");
   Rename_SIM_Record (&Amap_Image, AmapFilename);
   
   for (i=0; i<pPR->Amap.Nx; i++) {
      for (j=0; j<pPR->Amap.Ny; j++) {
         for (k=0; k<pPR->Amap.Nz; k++) {
            l			= i + j*pPR->Amap.Nx + k*pPR->Amap.Nx*pPR->Amap.Ny;
            GammaV		= pPR->Amap.pBounceV[l];
            p.data.f	= (float) GammaV;
            px			= i;
            py			= j + pPR->Amap.Ny*k;
            putSIMpixel (&Amap_Image, p, px, py);
         }
      }
   }
   
#ifndef POLSARPROSIM_NOSIMOUTPUT
   Write_SIM_Record	(&Amap_Image);
#endif
   
   free (AmapFilename);
   
   Destroy_SIM_Record (&Amap_Image);
   
   /******************************************/
   /* Report call if running in VERBOSE mode */
   /******************************************/
   
#ifdef VERBOSE_POLSARPROSIM
   printf ("\n");
   printf ("... Returning from call to Attenuation_Map\n");
   printf ("\n");
#endif
   fprintf (pPR->pLogFile, "... Returning from call to Attenuation_Map\n\n");
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
   
   return;
}


/*****************************/
/* SPM Scattering Amplitudes */
/*****************************/

Complex Bhh (double theta, Complex epsilon)
{
   double		sintheta	= sin(theta);
   double		costheta	= cos(theta);
   Complex	w			= complex_sqrt	(xy_complex (epsilon.x-sintheta*sintheta, epsilon.y));
   Complex	Rhh			= xy_complex	(costheta-w.x, -w.y);
   Rhh			= complex_div	(Rhh, xy_complex (costheta+w.x, w.y));
   return (Rhh);
}

Complex Bvv (double theta, Complex epsilon)
{
   double		sintheta	= sin(theta);
   double		costheta	= cos(theta);
   Complex	u			= xy_complex	(epsilon.x-1.0, epsilon.y);
   Complex	v			= complex_sub	(xy_complex (sintheta*sintheta, 0.0), complex_rmul (epsilon, 1.0+sintheta*sintheta));
   Complex	w			= complex_rmul	(epsilon, costheta);
   Complex	z			= complex_sqrt	(xy_complex (epsilon.x-sintheta*sintheta, epsilon.y));
   Complex	Rvv			= complex_mul	(u, v);
   z			= complex_add	(w, z);
   z			= complex_mul	(z, z);
   Rvv			= complex_div	(Rvv, z);
   return (Rvv);
}


/*************************/
/* SAR image calculation */
/*************************/

double		Point_Spread_Function			(double dx, double dy, PolSARproSim_Record *pPR, int track, double inc_angle)
{
   /****************************************************************************/
   /* Note that dx is azimuth displacement and dy is ground range displacement */
   /****************************************************************************/
   double		ax		= pPR->psfaaz;
   double		ay		= pPR->psfagr[track];
   double		psf;

   psf   		= pPR->PSFamp * exp (-(ax*dx*dx+ay*dy*dy));
   return (psf);
}

double		Lookup_PSF_value              (int ioffx, int ioffy, int inx, int iny, int itheta, PolSARproSim_Record *pPR)
{
   /****************************************************************************/
   /* Note that dx is azimuth displacement and dy is ground range displacement */
   /****************************************************************************/
   double		psf, psfaz, psfgr;

   psfaz       = pPR->PSFazmat[inx*(PSF_OVERSAMPLING_FACTOR + 1) + ioffx];
   psfgr       = pPR->PSFgrmat[iny*(PSF_OVERSAMPLING_FACTOR + 1) + ioffy][itheta];

   
   psf         = pPR->PSFamp* psfgr * psfaz;
   
   return (psf);
}

 
double		Accumulate_SAR_Contribution		(double focus_x, double focus_y, double focus_srange,
                                              Complex Shh, Complex Shv, Complex Svv, PolSARproSim_Record *pPR, int track, double focus_angle)
{
   double		dx		= pPR->deltax;
   double		dy		= pPR->deltay;
   double		xmid	= pPR->xmid;
   double		ymid	= pPR->ymid;
   double		k		= pPR->k0;
   /**************************************************************/
   /* Find pixel coordinates for pixel closest to point of focus */
   /**************************************************************/
//   int         ix		= (int) ((xmid+focus_x)/dx);
//   int         jy		= (int) ((ymid-focus_y)/dy);
   int         ix		= (int)rint ((xmid+focus_x)/dx);
   int         jy		= (int)rint ((ymid-focus_y)/dy);
   double      off_x = focus_x - (ix * dx - xmid);
   double      off_y = focus_y - (ymid - jy * dy);
   int         ioffx = (int)((off_x+pPR->deltax/2)/pPR->deltax_OS);
   int         ioffy = (int)((off_y+pPR->deltay/2)/pPR->deltay_OS);
   int         itheta = (int)((focus_angle - pPR->min_inc_angle)*RAD_TO_DEG);
   /***********************************************/
   /* Find extent of loop for pixel contributions */
   /***********************************************/
   int         nxmin	= ix - pPR->PSFnx;
   int         nxmax	= ix + pPR->PSFnx;
   int         nymin	= jy - pPR->PSFny;
   int         nymax	= jy + pPR->PSFny;
   int         ipx, jpy;
   double		px, py;
   double		daz;
   double		phi;
   double		weight;
   Complex     cweight;
   sim_pixel	spix;
   sim_pixel   gpix;
   Complex     cvalue;
   double		weight_sum	= 0.0;
      
   spix.simpixeltype	= pPR->HHstack[track].Image.pixel_type;
   gpix.simpixeltype	= pPR->HHstack[track].Image.pixel_type;
   /**************************************************/
   /* Add contribution if it overlaps the image area */
   /**************************************************/
   if (nxmax >= 0) {
      if (nxmin < pPR->nx) {
         if (nymax >= 0) {
            if (nymin < pPR->ny) {
               /***************************************/
               /* Determine the extent of the overlap */
               /***************************************/
               if (nxmin < 0) nxmin = 0;
               if (nxmax > pPR->nx-1) nxmax = pPR->nx-1;
               if (nymin < 0) nymin = 0;
               if (nymax > pPR->ny-1) nymax = pPR->ny-1;
               /********************/
               /* Loop over pixels */
               /********************/
               for (ipx=nxmin; ipx<=nxmax; ipx++) {
                  px	= ipx * dx - xmid;
                  daz	= px - focus_x;
                  phi	= 2.0*k*focus_srange + k*daz*daz/focus_srange; //Interferometric phase
                  for (jpy=nymin; jpy<=nymax; jpy++) {
                     py				= ymid - jpy * dy;
#ifdef   POLSARPROSIM_PSF_GAUSSIAN
                     weight			= Point_Spread_Function (daz, py-focus_y, pPR, track, focus_angle);
#else                     
                     weight			= Lookup_PSF_value (ioffx, ioffy, ipx-ix+pPR->PSFnx, jpy-jy+pPR->PSFny, itheta, pPR);
#endif
                     weight_sum		+= weight*weight;
                     Polar_Assign_Complex (&cweight, weight, phi);
                     /* HH channel write */
                     cvalue			= complex_mul (cweight, Shh);
                     spix.data.cf.x	= (float) cvalue.x;
                     spix.data.cf.y	= (float) cvalue.y;
#ifdef ENABLE_THREADS
                     pthread_mutex_lock   (&PolSARproSim_HHmutex);
                     gpix				= getSIMpixel (&(pPR->HHstack[track].Image), ipx, jpy);
                     spix.data.cf.x	+= gpix.data.cf.x;
                     spix.data.cf.y	+= gpix.data.cf.y;
                     putSIMpixel (&(pPR->HHstack[track].Image), spix, ipx, jpy);
                     pthread_mutex_unlock (&PolSARproSim_HHmutex);
#else
                     gpix				= getSIMpixel (&(pPR->HHstack[track].Image), ipx, jpy);
                     spix.data.cf.x	+= gpix.data.cf.x;
                     spix.data.cf.y	+= gpix.data.cf.y;
                     putSIMpixel (&(pPR->HHstack[track].Image), spix, ipx, jpy);
#endif
                     /* HV channel write */
                     cvalue			= complex_mul (cweight, Shv);
                     spix.data.cf.x	= (float) cvalue.x;
                     spix.data.cf.y	= (float) cvalue.y;
#ifdef ENABLE_THREADS
                     pthread_mutex_lock   (&PolSARproSim_HVmutex);
                     gpix				= getSIMpixel (&(pPR->HVstack[track].Image), ipx, jpy);
                     spix.data.cf.x	+= gpix.data.cf.x;
                     spix.data.cf.y	+= gpix.data.cf.y;
                     putSIMpixel (&(pPR->HVstack[track].Image), spix, ipx, jpy);
                     pthread_mutex_unlock (&PolSARproSim_HVmutex);
#else
                     gpix				= getSIMpixel (&(pPR->HVstack[track].Image), ipx, jpy);
                     spix.data.cf.x	+= gpix.data.cf.x;
                     spix.data.cf.y	+= gpix.data.cf.y;
                     putSIMpixel (&(pPR->HVstack[track].Image), spix, ipx, jpy);
#endif
                     /* VV channel write */
                     cvalue			= complex_mul (cweight, Svv);
                     spix.data.cf.x	= (float) cvalue.x;
                     spix.data.cf.y	= (float) cvalue.y;
#ifdef ENABLE_THREADS
                     pthread_mutex_lock   (&PolSARproSim_VVmutex);
                     gpix				= getSIMpixel (&(pPR->VVstack[track].Image), ipx, jpy);
                     spix.data.cf.x	+= gpix.data.cf.x;
                     spix.data.cf.y	+= gpix.data.cf.y;
                     putSIMpixel (&(pPR->VVstack[track].Image), spix, ipx, jpy);
                     pthread_mutex_unlock (&PolSARproSim_VVmutex);
#else
                     gpix				= getSIMpixel (&(pPR->VVstack[track].Image), ipx, jpy);
                     spix.data.cf.x	+= gpix.data.cf.x;
                     spix.data.cf.y	+= gpix.data.cf.y;
                     putSIMpixel (&(pPR->VVstack[track].Image), spix, ipx, jpy);
#endif
                  }
               }
            }
         }
      }
   }
   return (weight_sum);
}

void        Max_Height_Generation     (double  focus_x, double focus_y, double height, PolSARproSim_Record *pPR)
{
   double         dx    = pPR->deltax;
   double         dy		= pPR->deltay;
   double         xmid	= pPR->xmid;
   double         ymid	= pPR->ymid;
   /**************************************************************/
   /* Find pixel coordinates for pixel closest to point of focus */
   /**************************************************************/
   int         ix		= (int) ((xmid+focus_x)/dx);
   int         jy		= (int) ((ymid-focus_y)/dy);
   sim_pixel	spix;
   sim_pixel   gpix;
      
   spix.simpixeltype	= pPR->Max_Height.pixel_type;
   gpix.simpixeltype	= pPR->Max_Height.pixel_type;

   pthread_mutex_lock   (&PolSARproSim_MaxHgtmutex);
   gpix				= getSIMpixel (&(pPR->Max_Height), ix, jy);
   if(gpix.data.f < height){
      spix.data.f    = height;
      putSIMpixel (&(pPR->Max_Height), spix, ix, jy);
   }
   pthread_mutex_unlock (&PolSARproSim_MaxHgtmutex);

}


int			Polarisation_Vectors			(d3Vector k, d3Vector n, d3Vector *ph, d3Vector *pv)
{
   double		ndotk;
   double		hx, hy, hz;
   double		vx, vy, vz;
   
   d3Vector_insitu_normalise (&k);
   d3Vector_insitu_normalise (&n);
   ndotk		= d3Vector_scalar_product (n, k);
   if (fabs(fabs(ndotk)-1.0) < FLT_EPSILON) {
      *ph		= Cartesian_Assign_d3Vector (-sin(k.phi), cos(k.phi), 0.0);
      *pv		= Cartesian_Assign_d3Vector (cos(k.theta)*cos(k.phi), cos(k.theta)*sin(k.phi), -sin(k.theta));
   } else {
      hx		= n.x[1]*k.x[2] - n.x[2]*k.x[1];
      hy		= n.x[2]*k.x[0] - n.x[0]*k.x[2];
      hz		= n.x[0]*k.x[1] - n.x[1]*k.x[0];
      *ph		= Cartesian_Assign_d3Vector (hx, hy, hz);
      d3Vector_insitu_normalise (ph);
      vx		= ph->x[1]*k.x[2] - ph->x[2]*k.x[1];
      vy		= ph->x[2]*k.x[0] - ph->x[0]*k.x[2];
      vz		= ph->x[0]*k.x[1] - ph->x[1]*k.x[0];
      *pv		= Cartesian_Assign_d3Vector (vx, vy, vz);
   }
   return (NO_POLSARPROSIM_ERRORS);
}

c3Vector	d3V2c3V	(d3Vector v)
{
   c3Vector	c;
   c	= Assign_c3Vector (xy_complex (v.x[0], 0.0), xy_complex (v.x[1], 0.0), xy_complex (v.x[2], 0.0)); 
   return (c);
}

//#ifndef POLSARPRO_CONVENTION
//void		Create_SAR_Filenames			(PolSARproSim_Record *pPR, const char *master_directory, const char *slave_directory, const char *prefix)
//#else
//void		Create_SAR_Filenames			(PolSARproSim_Record *pPR, const char *master_directory, const char *slave_directory)
//#endif
//{
//#ifndef POLSARPRO_CONVENTION
//   if (pPR->current_track == 0) {
//      pPR->HH_string	= (char*) calloc (strlen(master_directory)+strlen(prefix)+8, sizeof(char));
//      strcpy  (pPR->HH_string, master_directory);
//   } else {
//      free (pPR->HH_string);
//      pPR->HH_string	= (char*) calloc (strlen(slave_directory)+strlen(prefix)+8, sizeof(char));
//      strcpy  (pPR->HH_string, slave_directory);
//   }
//   strncat (pPR->HH_string, prefix, strlen(prefix));
//   strncat (pPR->HH_string, "HH.sim", 6);
//   if (pPR->current_track == 0) {
//      pPR->HV_string	= (char*) calloc (strlen(master_directory)+strlen(prefix)+8, sizeof(char));
//      strcpy  (pPR->HV_string, master_directory);
//   } else {
//      free (pPR->HV_string);
//      pPR->HV_string	= (char*) calloc (strlen(slave_directory)+strlen(prefix)+8, sizeof(char));
//      strcpy  (pPR->HV_string, slave_directory);
//   }
//   strncat (pPR->HV_string, prefix, strlen(prefix));
//   strncat (pPR->HV_string, "HV.sim", 6);
//   if (pPR->current_track == 0) {
//      pPR->VV_string	= (char*) calloc (strlen(master_directory)+strlen(prefix)+8, sizeof(char));
//      strcpy  (pPR->VV_string, master_directory);
//   } else {
//      free (pPR->VV_string);
//      pPR->VV_string	= (char*) calloc (strlen(slave_directory)+strlen(prefix)+8, sizeof(char));
//      strcpy  (pPR->VV_string, slave_directory);
//   }
//   strncat (pPR->VV_string, prefix, strlen(prefix));
//   strncat (pPR->VV_string, "VV.sim", 6);
//   if (pPR->current_track == 0) {
//      pPR->VH_string	= (char*) calloc (strlen(master_directory)+strlen(prefix)+8, sizeof(char));
//      strcpy  (pPR->VH_string, master_directory);
//   } else {
//      free (pPR->VH_string);
//      pPR->VH_string	= (char*) calloc (strlen(slave_directory)+strlen(prefix)+8, sizeof(char));
//      strcpy  (pPR->VH_string, slave_directory);
//   }
//   strncat (pPR->VH_string, prefix, strlen(prefix));
//   strncat (pPR->VH_string, "VH.sim", 6);
//#else
//   if (pPR->current_track == 0) {
//      pPR->HH_string	= (char*) calloc (strlen(master_directory)+9, sizeof(char));
//      strcpy  (pPR->HH_string, master_directory);
//   } else {
//      free (pPR->HH_string);
//      pPR->HH_string	= (char*) calloc (strlen(slave_directory)+9, sizeof(char));
//      strcpy  (pPR->HH_string, slave_directory);
//   }
//   strncat (pPR->HH_string, "s11.bin", 7);
//   if (pPR->current_track == 0) {
//      pPR->HV_string	= (char*) calloc (strlen(master_directory)+9, sizeof(char));
//      strcpy  (pPR->HV_string, master_directory);
//   } else {
//      free (pPR->HV_string);
//      pPR->HV_string	= (char*) calloc (strlen(slave_directory)+9, sizeof(char));
//      strcpy  (pPR->HV_string, slave_directory);
//   }
//   strncat (pPR->HV_string, "s12.bin", 7);
//   if (pPR->current_track == 0) {
//      pPR->VV_string	= (char*) calloc (strlen(master_directory)+9, sizeof(char));
//      strcpy  (pPR->VV_string, master_directory);
//   } else {
//      free (pPR->VV_string);
//      pPR->VV_string	= (char*) calloc (strlen(slave_directory)+9, sizeof(char));
//      strcpy  (pPR->VV_string, slave_directory);
//   }
//   strncat (pPR->VV_string, "s22.bin", 7);
//   if (pPR->current_track == 0) {
//      pPR->VH_string	= (char*) calloc (strlen(master_directory)+9, sizeof(char));
//      strcpy  (pPR->VH_string, master_directory);
//   } else {
//      free (pPR->VH_string);
//      pPR->VH_string	= (char*) calloc (strlen(slave_directory)+9, sizeof(char));
//      strcpy  (pPR->VH_string, slave_directory);
//   }
//   strncat (pPR->VH_string, "s21.bin", 7);
//#endif
//   return;
//}

void		Create_SAR_Filenames			(PolSARproSim_Record *pPR, int track)
{      
      char trackid[10];
      char polname[10];
      
      sprintf(trackid, "track%03d",track); 
      
      sprintf(polname, "HH.bin");
      pPR->HH_string	= (char*) calloc (strlen(pPR->pMasterDirectory)+strlen(pPR->pFilenamePrefix)+1+strlen(trackid)+1+strlen(polname), sizeof(char));
      strcpy (pPR->HH_string, pPR->pMasterDirectory);
      strncat(pPR->HH_string, pPR->pFilenamePrefix, strlen(pPR->pFilenamePrefix));
      strncat(pPR->HH_string, "_",1);
      strncat(pPR->HH_string, trackid, strlen(trackid));
      strncat(pPR->HH_string, "_",1);
      strncat(pPR->HH_string, polname, strlen(polname));
      
      sprintf(polname, "HV.bin");
      pPR->HV_string	= (char*) calloc (strlen(pPR->pMasterDirectory)+strlen(pPR->pFilenamePrefix)+1+strlen(trackid)+1+strlen(polname), sizeof(char));
      strcpy (pPR->HV_string, pPR->pMasterDirectory);
      strncat(pPR->HV_string, pPR->pFilenamePrefix, strlen(pPR->pFilenamePrefix));
      strncat(pPR->HV_string, "_",1);
      strncat(pPR->HV_string, trackid, strlen(trackid));
      strncat(pPR->HV_string, "_",1);
      strncat(pPR->HV_string, polname, strlen(polname));

      sprintf(polname, "VH.bin");
      pPR->VH_string	= (char*) calloc (strlen(pPR->pMasterDirectory)+strlen(pPR->pFilenamePrefix)+1+strlen(trackid)+1+strlen(polname), sizeof(char));
      strcpy (pPR->VH_string, pPR->pMasterDirectory);
      strncat(pPR->VH_string, pPR->pFilenamePrefix, strlen(pPR->pFilenamePrefix));
      strncat(pPR->VH_string, "_",1);
      strncat(pPR->VH_string, trackid, strlen(trackid));
      strncat(pPR->VH_string, "_",1);
      strncat(pPR->VH_string, polname, strlen(polname));

      sprintf(polname, "VV.bin");
      pPR->VV_string	= (char*) calloc (strlen(pPR->pMasterDirectory)+strlen(pPR->pFilenamePrefix)+1+strlen(trackid)+1+strlen(polname), sizeof(char));
      strcpy (pPR->VV_string, pPR->pMasterDirectory);
      strncat(pPR->VV_string, pPR->pFilenamePrefix, strlen(pPR->pFilenamePrefix));
      strncat(pPR->VV_string, "_",1);
      strncat(pPR->VV_string, trackid, strlen(trackid));
      strncat(pPR->VV_string, "_",1);
      strncat(pPR->VV_string, polname, strlen(polname));

   return;
}

//void		Clean_SAR_Images				(PolSARproSim_Record *pPR)
//{
//   Destroy_SIM_Record (&(pPR->HHimage));
//   Destroy_SIM_Record (&(pPR->HVimage));
//   Destroy_SIM_Record (&(pPR->VVimage));
//   Initialise_SIM_Record	(&(pPR->HHimage), pPR->HH_string, pPR->nx, pPR->ny, SIM_COMPLEX_FLOAT_TYPE,
//                            pPR->Lx, pPR->Ly, "PolSARproSim HH image file");
//   Initialise_SIM_Record	(&(pPR->HVimage), pPR->HV_string, pPR->nx, pPR->ny, SIM_COMPLEX_FLOAT_TYPE,
//                            pPR->Lx, pPR->Ly, "PolSARproSim HV image file");
//   Initialise_SIM_Record	(&(pPR->VVimage), pPR->VV_string, pPR->nx, pPR->ny, SIM_COMPLEX_FLOAT_TYPE,
//                            pPR->Lx, pPR->Ly, "PolSARproSim VV image file");
//   return;
//}


void		Initialise_SAR_Stack				(PolSARproSim_Record *pPR)
{
   int         itrack;
   
   pPR->HHstack	= (SIM_Stack*) calloc (pPR->Tracks, sizeof (SIM_Stack));
   pPR->HVstack	= (SIM_Stack*) calloc (pPR->Tracks, sizeof (SIM_Stack));
   pPR->VVstack	= (SIM_Stack*) calloc (pPR->Tracks, sizeof (SIM_Stack));
      
   for (itrack = 0; itrack<pPR->Tracks;itrack++){
      Destroy_SIM_Record      (&(pPR->HHstack[itrack].Image));
      Destroy_SIM_Record      (&(pPR->HVstack[itrack].Image));
      Destroy_SIM_Record      (&(pPR->VVstack[itrack].Image));
      Create_SAR_Filenames		(pPR, itrack);
      Initialise_SIM_Record	(&(pPR->HHstack[itrack].Image), pPR->HH_string, pPR->nx, pPR->ny, SIM_COMPLEX_FLOAT_TYPE,
                               pPR->Lx, pPR->Ly, "PolSARproSim HH image file");
      Initialise_SIM_Record	(&(pPR->HVstack[itrack].Image), pPR->HV_string, pPR->nx, pPR->ny, SIM_COMPLEX_FLOAT_TYPE,
                               pPR->Lx, pPR->Ly, "PolSARproSim HV image file");
      Initialise_SIM_Record	(&(pPR->VVstack[itrack].Image), pPR->VV_string, pPR->nx, pPR->ny, SIM_COMPLEX_FLOAT_TYPE,
                               pPR->Lx, pPR->Ly, "PolSARproSim VV image file");
   }
   return;
}

void		Destroy_SAR_Stack				(PolSARproSim_Record *pPR)
{
   int         itrack;
   
   for (itrack = 0; itrack<pPR->Tracks;itrack++){
      Destroy_SIM_Record      (&(pPR->HHstack[itrack].Image));
      Destroy_SIM_Record      (&(pPR->HVstack[itrack].Image));
      Destroy_SIM_Record      (&(pPR->VVstack[itrack].Image));
   }
   return;
}


/***********************************************************/
/* SAR imaging algorithm crown tertiary branch realisation */
/***********************************************************/

//double		Estimate_SAR_Tertiaries			(Tree *pT, PolSARproSim_Record *pPR, long *nt, double *tbl, double *tbr)
//{
//   double      primary_branch_length, secondary_branch_length, tertiary_branch_length;
//   double		primary_branch_radius, secondary_branch_radius, tertiary_branch_radius;
//   double		tertiary_branch_volume;
//   double		tertiary_branch_vf;
//   long			tertiary_branch_number;
//   long			stbn; 
//   Crown			*pC;
//   Branch		*pB;
//   long			iBranch;
//   double		stbn_factor;
//   double		crown_area;
//   double		Sa_scaling;
//   
//   /********************************/
//   /* Initialise the crown pointer */
//   /********************************/
//   pC							= pT->CrownVolume.head;
//   crown_area					= 4.0*atan(1.0)*pC->d2*pC->d2;
//   /***********************************/
//   /* Empty the current tertiary list */
//   /***********************************/
//   Branch_empty_list (&(pT->Tertiary));
//   /*********************************************/
//   /* Determine dimensions of tertiary branches */
//   /*********************************************/
//   if (pT->species == POLSARPROSIM_HEDGE) {
//      tertiary_branch_length	= POLSARPROSIM_HEDGE_TERTIARY_BRANCH_LENGTH;
//      tertiary_branch_radius	= POLSARPROSIM_HEDGE_TERTIARY_BRANCH_RADIUS;
//   } else {
//      primary_branch_length		= 0.0;
//      primary_branch_radius		= 0.0;
//      pB	= pT->Primary.head;
//      for (iBranch=0L; iBranch < pT->Primary.n; iBranch++) {
//         primary_branch_length	+= pB->l;
//         primary_branch_radius	+= 0.5*(pB->start_radius + pB->end_radius);
//         pB	= pB->next;
//      }
//      primary_branch_length		/= (double) pT->Primary.n;
//      primary_branch_radius		/= (double) pT->Primary.n;
//      secondary_branch_length	= 0.0;
//      secondary_branch_radius	= 0.0;
//      pB	= pT->Secondary.head;
//      for (iBranch=0L; iBranch < pT->Secondary.n; iBranch++) {
//         secondary_branch_length	+= pB->l;
//         secondary_branch_radius	+= 0.5*(pB->start_radius + pB->end_radius);
//         pB	= pB->next;
//      }
//      secondary_branch_length	/= (double) pT->Secondary.n;
//      secondary_branch_radius	/= (double) pT->Secondary.n;
//      tertiary_branch_length	= secondary_branch_length*secondary_branch_length/primary_branch_length;
//      tertiary_branch_radius	= secondary_branch_radius*secondary_branch_radius/primary_branch_radius;
//   }
//   /***********************************************************/
//   /* Determine the actual number of tertiaries in this crown */
//   /***********************************************************/
//   tertiary_branch_volume		= DPI_RAD*tertiary_branch_radius*tertiary_branch_radius*tertiary_branch_length;
//   tertiary_branch_vf			= Tertiary_Branch_Volume_Fraction (pT, pPR);
//   tertiary_branch_number		= (long) (tertiary_branch_vf*pC->volume/tertiary_branch_volume);
//#ifdef POLSARPROSIM_VERBOSE_TERTIARY
//   fprintf (pPR->pLogFile, "\nTertiary branch number for this crown is %ld\n", tertiary_branch_number);
//#endif
//   /*********************************************************/
//   /* Determine the number of desired tertiary realisations */
//   /*********************************************************/
//   switch (pT->species) {
//      case	POLSARPROSIM_HEDGE:		stbn_factor	= POLSARPROSIM_HEDGE_SAR_TERTIARY_FACTOR;			break;
//      case	POLSARPROSIM_PINE001:		stbn_factor	= POLSARPROSIM_PINE001_SAR_TERTIARY_FACTOR;			break;
//      case	POLSARPROSIM_PINE002:		stbn_factor	= POLSARPROSIM_PINE002_SAR_TERTIARY_FACTOR;			break;
//      case	POLSARPROSIM_PINE003:		stbn_factor	= POLSARPROSIM_PINE003_SAR_TERTIARY_FACTOR;			break;
//      case	POLSARPROSIM_DECIDUOUS001:	stbn_factor	= POLSARPROSIM_DECIDUOUS001_SAR_TERTIARY_FACTOR;		break;
//      default:				stbn_factor	= POLSARPROSIM_PINE001_SAR_TERTIARY_FACTOR;			break;
//   }
//   stbn						= (int) (stbn_factor*crown_area/(pPR->azimuth_resolution*pPR->ground_range_resolution[0]));
//   stbn++;
//#ifdef POLSARPROSIM_VERBOSE_TERTIARY
//   fprintf (pPR->pLogFile, "Tertiary branch realisations for this crown: %ld\n", stbn);
//#endif
//   /*****************************************/
//   /* Choose the smaller of the two numbers */
//   /*****************************************/
//   if (stbn > tertiary_branch_number) {
//      stbn	= tertiary_branch_number;
//   }
//   /******************************************************************/
//   /* Determine the scattering amplitude scale factor for this crown */
//   /******************************************************************/
//   Sa_scaling					= sqrt (((double)tertiary_branch_number)/((double)stbn));
//#ifdef POLSARPROSIM_VERBOSE_TERTIARY
//   fprintf (pPR->pLogFile, "Tertiary branch scattering amplitude scaling =  %lf\n", Sa_scaling);
//#endif
//   /*****************************/
//   /* Pass relevant information */
//   /*****************************/
//   *nt						= (long) stbn;
//   *tbl						= tertiary_branch_length;
//   *tbr						= tertiary_branch_radius;
//   /*******************************************/
//   /* Return to caller with amplitude scaling */
//   /*******************************************/
//      
//   return (Sa_scaling);
//}

double		Estimate_SAR_Tertiaries			(Tree *pT, PolSARproSim_Record *pPR, long *nt, double *tbl, double *tbr)
{
   double      primary_branch_length, secondary_branch_length, tertiary_branch_length;
   double		primary_branch_radius, secondary_branch_radius, tertiary_branch_radius;
   double		tertiary_branch_volume;
   double		tertiary_branch_vf;
   long			tertiary_branch_number;
   long			stbn; 
   Crown			*pC;
   Branch		*pB;
   long			iBranch;
   double		stbn_factor;
   double		crown_area;
   double		Sa_scaling;
   double      tertiary_min_radius, tertiary_min_length;            
   
   /********************************/
   /* Initialise the crown pointer */
   /********************************/
   pC                      = pT->CrownVolume.head;
   crown_area					= 4.0*atan(1.0)*pC->d2*pC->d2;
   /***********************************/
   /* Empty the current tertiary list */
   /***********************************/
   Branch_empty_list (&(pT->Tertiary));
   /*********************************************/
   /* Determine dimensions of tertiary branches */
   /*********************************************/
   
   /* read in the minimum values from the species database */
   tertiary_min_length	= pPR->SpeciesDataBase[pT->species].tertiary_min_length;
   tertiary_min_radius	= pPR->SpeciesDataBase[pT->species].tertiary_min_radius;
   
   /* initialize */
   primary_branch_length		= 0.0;
   primary_branch_radius		= 0.0;
   secondary_branch_length    = 0.0;
   secondary_branch_radius    = 0.0;
   tertiary_branch_length     = 0.0;
   tertiary_branch_radius     = 0.0;
   
   /* compute mean secondary radius/length */
   if(pT->Secondary.n > 0){
      pB	= pT->Secondary.head;
      for (iBranch=0L; iBranch < pT->Secondary.n; iBranch++) {
         secondary_branch_length	+= pB->l;
         secondary_branch_radius	+= 0.5*(pB->start_radius + pB->end_radius);
         pB	= pB->next;
      }
      secondary_branch_length	/= (double) pT->Secondary.n;
      secondary_branch_radius	/= (double) pT->Secondary.n;
   }
   /* compute mean primary radius/length */
   if(pT->Primary.n > 0){      
      pB	= pT->Primary.head;
      for (iBranch=0L; iBranch < pT->Primary.n; iBranch++) {
         primary_branch_length	+= pB->l;
         primary_branch_radius	+= 0.5*(pB->start_radius + pB->end_radius);
         pB	= pB->next;
      }
      primary_branch_length		/= (double) pT->Primary.n;
      primary_branch_radius		/= (double) pT->Primary.n;
      
      /* calculate the mean tertiary branch size */
      tertiary_branch_length	= secondary_branch_length*secondary_branch_length/primary_branch_length;
      tertiary_branch_radius	= secondary_branch_radius*secondary_branch_radius/primary_branch_radius;
   }
   
   /* choose the minimum length/radius if larger than the computed length/radius */
   if(tertiary_min_length > tertiary_branch_length){
      tertiary_branch_length  = tertiary_min_length;
   }
   if(tertiary_min_radius > tertiary_branch_radius){
      tertiary_branch_radius  = tertiary_min_radius;
   }
   
   /***********************************************************/
   /* Determine the actual number of tertiaries in this crown */
   /***********************************************************/
   tertiary_branch_volume		= DPI_RAD*tertiary_branch_radius*tertiary_branch_radius*tertiary_branch_length;
   tertiary_branch_vf			= Tertiary_Branch_Volume_Fraction (pT, pPR);
   tertiary_branch_number		= (long) (tertiary_branch_vf*pC->volume/tertiary_branch_volume);
#ifdef POLSARPROSIM_VERBOSE_TERTIARY
   fprintf (pPR->pLogFile, "\nTertiary branch number for this crown is %ld\n", tertiary_branch_number);
#endif
   /*********************************************************/
   /* Determine the number of desired tertiary realisations */
   /*********************************************************/
   stbn_factor          = pPR->SpeciesDataBase[pT->species].tertiary_number_factor;
   stbn						= (int) (stbn_factor*crown_area/(pPR->azimuth_resolution*pPR->ground_range_resolution[0]));
   stbn++;
#ifdef POLSARPROSIM_VERBOSE_TERTIARY
   fprintf (pPR->pLogFile, "Tertiary branch realisations for this crown: %ld\n", stbn);
#endif
   /*****************************************/
   /* Choose the smaller of the two numbers */
   /*****************************************/
   if (stbn > tertiary_branch_number) {
      stbn	= tertiary_branch_number;
   }
   /******************************************************************/
   /* Determine the scattering amplitude scale factor for this crown */
   /******************************************************************/
   Sa_scaling					= sqrt (((double)tertiary_branch_number)/((double)stbn));
#ifdef POLSARPROSIM_VERBOSE_TERTIARY
   fprintf (pPR->pLogFile, "Tertiary branch scattering amplitude scaling =  %lf\n", Sa_scaling);
#endif
   /*****************************/
   /* Pass relevant information */
   /*****************************/
   *nt						= (long) stbn;
   *tbl						= tertiary_branch_length;
   *tbr						= tertiary_branch_radius;
   /*******************************************/
   /* Return to caller with amplitude scaling */
   /*******************************************/
   
   return (Sa_scaling);
}

//int		Realise_Tertiary_Branch			(Tree *pT, PolSARproSim_Record *pPR, Branch *pB, 
//                                        double tertiary_branch_length, double tertiary_branch_radius,
//                                        double moisture, Complex permittivity)
//{
//   Crown			*pC;
//   d3Vector		 b0, p0, z0;
//   double			 theta, phi;
//   int			 rtn_value;
//   
//   pC				= pT->CrownVolume.head;
//   Destroy_Branch (pB);
//   rtn_value		= Random_Crown_Location (pC, &b0);
//   if (rtn_value == NO_RAYCROWN_ERRORS) {
//      phi			= 2.0*DPI_RAD*drand();
//      theta			= vegi_polar_angle ();
//      z0			= Polar_Assign_d3Vector (1.0, theta, phi);
//      p0			= Polar_Assign_d3Vector (1.0, theta, phi);
//      b0			= d3Vector_sum (b0, d3Vector_double_multiply (z0, -tertiary_branch_length/2.0));
//      Assign_Branch (pB, tertiary_branch_radius, tertiary_branch_radius, b0, z0, p0, 0.0, 0.0, 0.0, 0.0, 0.0, 
//                     1.0, 1.0, 0.0, moisture, tertiary_branch_length, permittivity, 0, 0);
//   }
//   return (rtn_value);
//}
//
//double		Realise_SAR_Tertiaries			(Tree *pT, PolSARproSim_Record *pPR)
//{
//   double				primary_branch_length, secondary_branch_length, tertiary_branch_length;
//   double				primary_branch_radius, secondary_branch_radius, tertiary_branch_radius;
//   double				tertiary_branch_volume;
//   double				tertiary_branch_vf;
//   long				tertiary_branch_number;
//   //int				stbn; //razi-edit 04/30/2012
//   long				stbn; 
//   Branch				tertiary_branch;
//   double				theta, phi;
//   d3Vector			z0;
//   double				sr, er;
//   double				dp;
//   double				lamdacx, lamdacy, gamma;
//   double				phix, phiy, phicx, phicy;
//   Complex			permittivity;
//   d3Vector			p0;
//   double				moisture;
//   Crown				*pC;
//   Branch				*pB;
//   long				iBranch;
//   int				rtn_value;
//   d3Vector			b0;
//   double				stbn_factor;
//   double				crown_area;
//   double				Sa_scaling;
//   
//   /********************************/
//   /* Initialise the crown pointer */
//   /********************************/
//   pC							= pT->CrownVolume.head;
//   crown_area					= 4.0*atan(1.0)*pC->d2*pC->d2;
//   /***********************************/
//   /* Empty the current tertiary list */
//   /***********************************/
//   Branch_empty_list (&(pT->Tertiary));
//   /*********************************************/
//   /* Determine dimensions of tertiary branches */
//   /*********************************************/
//   if (pT->species == POLSARPROSIM_HEDGE) {
//      tertiary_branch_length	= POLSARPROSIM_HEDGE_TERTIARY_BRANCH_LENGTH;
//      tertiary_branch_radius	= POLSARPROSIM_HEDGE_TERTIARY_BRANCH_RADIUS;
//   } else {
//      primary_branch_length		= 0.0;
//      primary_branch_radius		= 0.0;
//      pB	= pT->Primary.head;
//      for (iBranch=0L; iBranch < pT->Primary.n; iBranch++) {
//         primary_branch_length	+= pB->l;
//         primary_branch_radius	+= 0.5*(pB->start_radius + pB->end_radius);
//         pB	= pB->next;
//      }
//      primary_branch_length		/= (double) pT->Primary.n;
//      primary_branch_radius		/= (double) pT->Primary.n;
//      secondary_branch_length	= 0.0;
//      secondary_branch_radius	= 0.0;
//      pB	= pT->Secondary.head;
//      for (iBranch=0L; iBranch < pT->Secondary.n; iBranch++) {
//         secondary_branch_length	+= pB->l;
//         secondary_branch_radius	+= 0.5*(pB->start_radius + pB->end_radius);
//         pB	= pB->next;
//      }
//      secondary_branch_length	/= (double) pT->Secondary.n;
//      secondary_branch_radius	/= (double) pT->Secondary.n;
//      tertiary_branch_length	= secondary_branch_length*secondary_branch_length/primary_branch_length;
//      tertiary_branch_radius	= secondary_branch_radius*secondary_branch_radius/primary_branch_radius;
//   }
//   /***********************************************************/
//   /* Determine the actual number of tertiaries in this crown */
//   /***********************************************************/
//   tertiary_branch_volume		= DPI_RAD*tertiary_branch_radius*tertiary_branch_radius*tertiary_branch_length;
//   tertiary_branch_vf			= Tertiary_Branch_Volume_Fraction (pT, pPR);
//   tertiary_branch_number		= (long) (tertiary_branch_vf*pC->volume/tertiary_branch_volume);
//#ifdef POLSARPROSIM_VERBOSE_TERTIARY
//   fprintf (pPR->pLogFile, "\nTertiary branch number for this crown is %ld\n", tertiary_branch_number);
//#endif
//   /********************************************************/
//   /* Determine the number of actual tertiary realisations */
//   /********************************************************/
//   switch (pT->species) {
//      case	POLSARPROSIM_HEDGE:			stbn_factor	= POLSARPROSIM_HEDGE_SAR_TERTIARY_FACTOR;			break;
//      case	POLSARPROSIM_PINE001:		stbn_factor	= POLSARPROSIM_PINE001_SAR_TERTIARY_FACTOR;			break;
//      case	POLSARPROSIM_PINE002:		stbn_factor	= POLSARPROSIM_PINE002_SAR_TERTIARY_FACTOR;			break;
//      case	POLSARPROSIM_PINE003:		stbn_factor	= POLSARPROSIM_PINE003_SAR_TERTIARY_FACTOR;			break;
//      case	POLSARPROSIM_DECIDUOUS001:	stbn_factor	= POLSARPROSIM_DECIDUOUS001_SAR_TERTIARY_FACTOR;	break;
//      default:							stbn_factor	= POLSARPROSIM_PINE001_SAR_TERTIARY_FACTOR;			break;
//   }
//   stbn						= (int) (stbn_factor*crown_area/(pPR->azimuth_resolution*pPR->ground_range_resolution[0]));
//   stbn++;
//#ifdef POLSARPROSIM_VERBOSE_TERTIARY
//   fprintf (pPR->pLogFile, "Tertiary branch realisations for this crown: %ld\n", stbn);
//#endif
//   /******************************************************************/
//   /* Determine the scattering amplitude scale factor for this crown */
//   /******************************************************************/
//   Sa_scaling					= sqrt (((double)tertiary_branch_number)/((double)stbn));
//#ifdef POLSARPROSIM_VERBOSE_TERTIARY
//   fprintf (pPR->pLogFile, "Tertiary branch scattering amplitude scaling =  %lf\n", Sa_scaling);
//#endif
//   /***************************************/
//   /* Loop to create tertiary branch list */
//   /***************************************/
//   Create_Branch (&tertiary_branch);
//   dp							= 0.0;
//   lamdacx					= 1.0;
//   lamdacy					= 1.0;
//   gamma						= 0.0;
//   phix						= 0.0;
//   phiy						= 0.0;
//   phicx						= 0.0;
//   phicy						= 0.0;
//   sr							= tertiary_branch_radius;
//   er							= tertiary_branch_radius;
//   for (iBranch=0L; iBranch < stbn; iBranch++) {
//      /************************************/
//      /* Create and store random branches */
//      /************************************/
//      rtn_value		= Random_Crown_Location (pC, &b0);
//      if (rtn_value == NO_RAYCROWN_ERRORS) {
//         phi			= 2.0*DPI_RAD*drand();
//         theta		= vegi_polar_angle ();
//         z0			= Polar_Assign_d3Vector (1.0, theta, phi);
//         p0			= Polar_Assign_d3Vector (1.0, theta, phi);
//         b0			= d3Vector_sum (b0, d3Vector_double_multiply (z0, -tertiary_branch_length/2.0));
//         moisture		= Tertiary_Branch_Moisture (pT, pPR);
//         permittivity	= vegetation_permittivity (moisture, pPR->frequency);
//         Assign_Branch (&tertiary_branch, sr, er, b0, z0, p0, dp, phix, phiy, phicx, phicy, 
//                        lamdacx, lamdacy, gamma, moisture, tertiary_branch_length, permittivity,
//                        (int) (pT->Stem.n + pT->Dry.n + pT->Primary.n + pT->Secondary.n + pT->Tertiary.n + 1L), 0);
//         Branch_head_add (&(pT->Tertiary), &tertiary_branch);
//      }
//   }
//   Destroy_Branch (&tertiary_branch);
//#ifdef POLSARPROSIM_VERBOSE_TERTIARY
//   fprintf (pPR->pLogFile, "Created %ld tertiary branches for this crown.\n\n", pT->Tertiary.n);
//#endif
//   return (Sa_scaling);
//}

/***************************************************/
/* SAR imaging algorithm crown foliage realisation */
/***************************************************/

double		Estimate_SAR_Foliage (Tree *pT, PolSARproSim_Record *pPR, long *nf)
{
   int            species;
   Crown          *pC;
   double			leaf_d1, leaf_d2, leaf_d3;
   double			theta, phi;
   double			moisture;
   d3Vector       cl;
   Complex        permittivity;
   double			leafvol;
   Leaf           leaf1;
   double			leaf_vf;
   long           leaf_number;
   double			Sa_scaling	= 1.0;
   double			crown_area;
   long           sfgn;
   double			sfgn_factor;
   /********************************/
   /* Initialise the crown pointer */
   /********************************/
   pC             = pT->CrownVolume.head;
   crown_area     = 4.0*atan(1.0)*pC->d2*pC->d2;
   /***********************************/
   /* Empty the existing foliage list */
   /***********************************/
   Leaf_empty_list (&(pT->Foliage));
   /***************************************/
   /* Find the foliage element dimensions */
   /***************************************/
   species        = Leaf_Species       (pT->species, pPR);
   Leaf_Size      (pT, pPR, &leaf_d1, &leaf_d2, &leaf_d3);
   cl             = Cartesian_Assign_d3Vector (0.0, 0.0, 0.0);
   theta          = 0.0;
   phi            = 0.0;
   moisture       = Leaf_Moisture		(pT->species, pPR);
   permittivity	= vegetation_permittivity (moisture, pPR->frequency);
   Create_Leaf    (&leaf1);
   Assign_Leaf    (&leaf1, species, leaf_d1, leaf_d2, leaf_d3, theta, phi, moisture, permittivity, cl);
   leafvol        = Leaf_Volume (&leaf1);
   leaf_vf        = Leaf_Volume_Fraction (pT->species, pPR);
   /*****************************************************************/
   /* Determine the actual number of foliage elements in this crown */
   /*****************************************************************/
   leaf_number	= (long) (leaf_vf*pC->volume/leafvol);
#ifdef POLSARPROSIM_VERBOSE_FOLIAGE
   fprintf (pPR->pLogFile, "\nFoliage element number for this crown is %ld\n", leaf_number);
#endif
   /****************************************************************/
   /* Determine the number of desired foliage element realisations */
   /****************************************************************/
   sfgn_factor = pPR->SpeciesDataBase[pT->species].leaf_number_factor;
   sfgn			= (long) (sfgn_factor*crown_area/(pPR->azimuth_resolution*pPR->ground_range_resolution[0]));
   sfgn++;
#ifdef POLSARPROSIM_VERBOSE_FOLIAGE
   fprintf (pPR->pLogFile, "Foliage element realisations for this crown: %ld\n", sfgn);
#endif
   /*****************************************/
   /* Choose the smaller of the two numbers */
   /*****************************************/
   if (sfgn > leaf_number) {
      sfgn	= leaf_number;
   }
   /******************************************************************/
   /* Determine the scattering amplitude scale factor for this crown */
   /******************************************************************/
   Sa_scaling		= sqrt (((double)leaf_number)/((double)sfgn));
#ifdef POLSARPROSIM_VERBOSE_FOLIAGE
   fprintf (pPR->pLogFile, "Foliage element scattering amplitude scaling =  %lf\n\n", Sa_scaling);
#endif
   /*****************************/
   /* Pass relevant information */
   /*****************************/
   *nf			= (long) sfgn;
   /*******************************************/
   /* Return to caller with amplitude scaling */
   /*******************************************/
   Destroy_Leaf (&leaf1);
   return (Sa_scaling);
}

//int		Realise_Foliage_Element			(Tree *pT, PolSARproSim_Record *pPR, Leaf *pL, 
//                                        int species, double leaf_d1, double leaf_d2, double leaf_d3, 
//                                        double moisture, Complex permittivity)
//{
//   Crown			*pC;
//   d3Vector		 cl;
//   int			 rtn_value;
//   double			 theta, phi;
//   
//   Destroy_Leaf (pL);
//   pC				= pT->CrownVolume.head;
//   rtn_value		= Random_Crown_Location (pC, &cl);
//   if (rtn_value == NO_RAYCROWN_ERRORS) {
//      phi			= 2.0*DPI_RAD*drand();
//      theta		= vegi_polar_angle ();
//      Assign_Leaf	(pL, species, leaf_d1, leaf_d2, leaf_d3, theta, phi, moisture, permittivity, cl);
//   }
//   return (rtn_value);
//}

//double		Realise_SAR_Foliage (Tree *pT, PolSARproSim_Record *pPR)
//{
//   int			species;
//   Crown			*pC;
//   double			leaf_d1, leaf_d2, leaf_d3;
//   double			theta, phi;
//   double			moisture;
//   d3Vector		cl;
//   Complex		permittivity;
//   double			leafvol;
//   Leaf			leaf1;
//   double			leaf_vf;
//   long			leaf_number;
//   int			iLeaf;
//   int			rtn_value;
//   double			Sa_scaling	= 1.0;
//   double			crown_area;
//   long			sfgn;
//   double			sfgn_factor;
//   /********************************/
//   /* Initialise the crown pointer */
//   /********************************/
//   pC							= pT->CrownVolume.head;
//   crown_area					= 4.0*atan(1.0)*pC->d2*pC->d2;
//   /***********************************/
//   /* Empty the existing foliage list */
//   /***********************************/
//   Leaf_empty_list (&(pT->Foliage));
//   /***************************************/
//   /* Find the foliage element dimensions */
//   /***************************************/
//   species		= Leaf_Species		(pT->species);
//   leaf_d1		= Leaf_Dimension_1	(pT->species);
//   leaf_d2		= Leaf_Dimension_2	(pT->species);
//   leaf_d3		= Leaf_Dimension_3	(pT->species);
//   cl				= Cartesian_Assign_d3Vector (0.0, 0.0, 0.0);
//   theta			= 0.0;
//   phi			= 0.0;
//   moisture		= Leaf_Moisture		(pT->species);
//   permittivity	= vegetation_permittivity (moisture, pPR->frequency);
//   Create_Leaf (&leaf1);
//   Assign_Leaf	(&leaf1, species, leaf_d1, leaf_d2, leaf_d3, theta, phi, moisture, permittivity, cl);
//   leafvol		= Leaf_Volume (&leaf1);
//   leaf_vf		= Leaf_Volume_Fraction (pT->species);
//   /*****************************************************************/
//   /* Determine the actual number of foliage elements in this crown */
//   /*****************************************************************/
//   leaf_number	= (long) (leaf_vf*pC->volume/leafvol);
//#ifdef POLSARPROSIM_VERBOSE_FOLIAGE
//   fprintf (pPR->pLogFile, "\nFoliage element number for this crown is %ld\n", leaf_number);
//#endif
//   /********************************************************/
//   /* Determine the number of foliage element realisations */
//   /********************************************************/
//   switch (pT->species) {
//      case	POLSARPROSIM_HEDGE:			sfgn_factor	= POLSARPROSIM_HEDGE_SAR_FOLIAGE_FACTOR;			break;
//      case	POLSARPROSIM_PINE001:		sfgn_factor	= POLSARPROSIM_PINE001_SAR_FOLIAGE_FACTOR;			break;
//      case	POLSARPROSIM_PINE002:		sfgn_factor	= POLSARPROSIM_PINE002_SAR_FOLIAGE_FACTOR;			break;
//      case	POLSARPROSIM_PINE003:		sfgn_factor	= POLSARPROSIM_PINE003_SAR_FOLIAGE_FACTOR;			break;
//      case	POLSARPROSIM_DECIDUOUS001:	sfgn_factor	= POLSARPROSIM_DECIDUOUS001_SAR_FOLIAGE_FACTOR;		break;
//      default:							sfgn_factor	= POLSARPROSIM_PINE001_SAR_FOLIAGE_FACTOR;			break;
//   }
//   sfgn			= (long) (sfgn_factor*crown_area/(pPR->azimuth_resolution*pPR->ground_range_resolution[0]));
//   sfgn++;
//#ifdef POLSARPROSIM_VERBOSE_FOLIAGE
//   fprintf (pPR->pLogFile, "Foliage element realisations for this crown: %ld\n", sfgn);
//#endif
//   /******************************************************************/
//   /* Determine the scattering amplitude scale factor for this crown */
//   /******************************************************************/
//   Sa_scaling		= sqrt (((double)leaf_number)/((double)sfgn));
//#ifdef POLSARPROSIM_VERBOSE_FOLIAGE
//   fprintf (pPR->pLogFile, "Foliage element scattering amplitude scaling =  %lf\n\n", Sa_scaling);
//#endif
//   /***************************************/
//   /* Loop to create foliage element list */
//   /***************************************/
//   for (iLeaf=0L; iLeaf < sfgn; iLeaf++) {
//      rtn_value		= Random_Crown_Location (pC, &cl);
//      if (rtn_value == NO_RAYCROWN_ERRORS) {
//         phi			= 2.0*DPI_RAD*drand();
//         theta		= vegi_polar_angle ();
//         moisture		= Leaf_Moisture		(pT->species);
//         permittivity	= vegetation_permittivity (moisture, pPR->frequency);
//         Assign_Leaf	(&leaf1, species, leaf_d1, leaf_d2, leaf_d3, theta, phi, moisture, permittivity, cl);
//         Leaf_head_add (&(pT->Foliage), &leaf1);
//      }
//   }
//   Destroy_Leaf (&leaf1);
//   return (Sa_scaling);
//}

/**********************************************************/
/* SAR image output routine for compliance with PolSARPro */
/**********************************************************/

/*************************************************/
/* Binary format output for POLSARPro compliance */
/*************************************************/

int		Write_SIM_Record_As_POLSARPRO_BINARY	(SIM_Record *pSIMR)
{
   SIM_Complex_Float	*column     = (SIM_Complex_Float*) calloc (pSIMR->ny, sizeof (SIM_Complex_Float));
   float             *column_f   = (float *) calloc(pSIMR->ny, sizeof(float));
   FILE              *pSBF;
   int				i, j;
   sim_pixel			sp;
   
   pSBF	= fopen (pSIMR->filename, "wb");
   for (i=0; i<pSIMR->nx; i++) {
      for (j=0; j<pSIMR->ny; j++) {
         sp	= getSIMpixel (pSIMR, i, pSIMR->ny-j-1);
         switch (sp.simpixeltype) {
            case SIM_BYTE_TYPE:              column_f[j]	= (float) sp.data.b;		break;
            case SIM_WORD_TYPE:              column_f[j]	= (float) sp.data.w;		break;
            case SIM_DWORD_TYPE:             column_f[j]	= (float) sp.data.dw;	break;
            case SIM_FLOAT_TYPE:             column_f[j]	= (float) sp.data.f;		break;
            case SIM_DOUBLE_TYPE:            column_f[j]	= (float) sp.data.d;		break;
            case SIM_COMPLEX_FLOAT_TYPE:		column[j].x	= (float) sp.data.cf.x;		column[j].y	= (float) -sp.data.cf.y;		break;
            case SIM_COMPLEX_DOUBLE_TYPE:		column[j].x	= (float) sp.data.cd.x;		column[j].y	= (float) -sp.data.cd.y;		break;
         }
      }
      if(sp.simpixeltype == SIM_COMPLEX_FLOAT_TYPE || sp.simpixeltype == SIM_COMPLEX_DOUBLE_TYPE){
         fwrite (column, sizeof (SIM_Complex_Float), pSIMR->ny, pSBF);
      }else{
         fwrite (column_f, sizeof (float), pSIMR->ny, pSBF);
      }
   }
   fclose (pSBF);
   free (column);
   free (column_f);
   return (NO_SIMPRIMITIVE_ERRORS);
}




/***************************************************************/
/* SAR image output with optional choice of SIM format imagery */
/***************************************************************/

//void		Write_SAR_Images				(PolSARproSim_Record *pPR)
//{
//#ifndef POLSARPRO_CONVENTION
//#ifdef POLSARPROSIM_ROTATED_IMAGES
//   SIM_Record			RotImage;
//   Create_SIM_Record	(&RotImage);
//   Rotate_SIM_Record	(&(pPR->HHimage), &RotImage);
//   Write_SIM_Record	(&RotImage);
//   Rotate_SIM_Record	(&(pPR->HVimage), &RotImage);
//   Write_SIM_Record	(&RotImage);
//   Rename_SIM_Record	(&RotImage, pPR->VH_string);
//   Write_SIM_Record	(&RotImage);
//   Rotate_SIM_Record	(&(pPR->VVimage), &RotImage);
//   Write_SIM_Record	(&RotImage);
//   Destroy_SIM_Record	(&RotImage);
//#else
//   Write_SIM_Record	(&(pPR->HHimage));
//   Write_SIM_Record	(&(pPR->HVimage));
//   Write_SIM_Record	(&(pPR->VVimage));
//   Rename_SIM_Record	(&(pPR->HVimage), pPR->VH_string);
//   Write_SIM_Record	(&(pPR->HVimage));
//   Rename_SIM_Record	(&(pPR->HVimage), pPR->HV_string);
//#endif
//#else
//   Write_SIM_Record_As_POLSARPRO_BINARY (&(pPR->HHimage));
//   Write_SIM_Record_As_POLSARPRO_BINARY (&(pPR->HVimage));
//   Write_SIM_Record_As_POLSARPRO_BINARY (&(pPR->VVimage));
//   Rename_SIM_Record (&(pPR->HVimage), pPR->VH_string);
//   Write_SIM_Record_As_POLSARPRO_BINARY (&(pPR->HVimage));
//   Rename_SIM_Record (&(pPR->HVimage), pPR->HV_string);
//#endif
//   return;
//}

void		Write_SAR_Stack				(PolSARproSim_Record *pPR)
{
   int itrack;
   
   for (itrack = 0; itrack<pPR->Tracks; itrack++){      
   
      Create_SAR_Filenames		(pPR, itrack);
#ifndef POLSARPRO_CONVENTION
#ifdef POLSARPROSIM_ROTATED_IMAGES
      SIM_Record			RotImage;
      Create_SIM_Record	(&RotImage);
      Rotate_SIM_Record	(&(pPR->HHstack[itrack].Image), &RotImage);
      Write_SIM_Record	(&RotImage);
      Rotate_SIM_Record	(&(pPR->HVstack[itrack].Image), &RotImage);
      Write_SIM_Record	(&RotImage);
      Rename_SIM_Record	(&RotImage, pPR->VH_string);
      Write_SIM_Record	(&RotImage);
      Rotate_SIM_Record	(&(pPR->VVstack[itrack].Image), &RotImage);
      Write_SIM_Record	(&RotImage);
      Destroy_SIM_Record	(&RotImage);
#else
      Write_SIM_Record	(&(pPR->HHstack[itrack].Image));
      Write_SIM_Record	(&(pPR->HVstack[itrack].Image));
      Write_SIM_Record	(&(pPR->VVstack[itrack].Image));
      Rename_SIM_Record	(&(pPR->HVstack[itrack].Image), pPR->VH_string);
      Write_SIM_Record	(&(pPR->HVstack[itrack].Image));
      Rename_SIM_Record	(&(pPR->HVstack[itrack].Image), pPR->HV_string);
#endif
#else
      Write_SIM_Record_As_POLSARPRO_BINARY (&(pPR->HHstack[itrack].Image));
      Write_SIM_Record_As_POLSARPRO_BINARY (&(pPR->HVstack[itrack].Image));
      Write_SIM_Record_As_POLSARPRO_BINARY (&(pPR->VVstack[itrack].Image));
      Rename_SIM_Record (&(pPR->HVstack[itrack].Image), pPR->VH_string);
      Write_SIM_Record_As_POLSARPRO_BINARY (&(pPR->HVstack[itrack].Image));
      Rename_SIM_Record (&(pPR->HVstack[itrack].Image), pPR->HV_string);
#endif
   }
   return;
}


//void		Destroy_SAR_Images				(PolSARproSim_Record *pPR)
//{
//   Destroy_SIM_Record (&(pPR->HHimage));
//   Destroy_SIM_Record (&(pPR->HVimage));
//   Destroy_SIM_Record (&(pPR->VVimage));
//   return;
//}

/************************/
/* TCLTK string parsing */
/************************/

void		tcltk_parser					(char *pString)
{
#ifdef _WIN32
   const char	good	= '\\';
   const char	bad		= '/';
#else 
   const char	good	= '/';
   const char	bad		= '\\';
#endif
   int i = 0;
   while (pString[i] != '\0') {
      if (pString[i] == bad) {
         pString[i] = good;
      }
      i++;
   }
   return;
}

/****************************************/
/* Optional flat earth phase correction */
/****************************************/

#ifdef	POLSARPROSIM_FLATEARTH

void		Flat_Earth_Phase_Removal		(PolSARproSim_Record *pPR)
{
   double			dx			= pPR->deltax;
   double			dy			= pPR->deltay;
   double			xmid		= pPR->xmid;
   double			ymid		= pPR->ymid;
   double			k			= pPR->k0;
//   const double	p_srange	= pPR->slant_range[track];
//   const double	thetai		= pPR->incidence_angle[track];
//   const double	p_height	= p_srange*cos(thetai);
//   const double	p_height2	= p_height*p_height;
//   const double	p_grange	= p_srange*sin(thetai);
   double         p_srange;
   double         thetai;
   double         p_height;
   double         p_height2;
   double         p_grange;
   int            i, j;
   double			x, y, gr, sr;
   double			phase;
   Complex        c_phase;
   sim_pixel		s;
   Complex        cs;
   int            track;
   
   /* loop over tracks */
   for (track = 0; track < pPR->Tracks; track++) {
      p_srange    = pPR->slant_range[track];
      thetai		= pPR->incidence_angle[track];
      p_height    = p_srange*cos(thetai);
      p_height2	= p_height*p_height;
      p_grange    = p_srange*sin(thetai);
      
      /* loop over range pixels */
      for (j = 0; j < pPR->ny; j++) {
         y		= ymid - j * dy;
         gr	= p_grange + y;
         sr	= sqrt (gr*gr + p_height2);
         phase	= 2.0*k*sr;
         Polar_Assign_Complex (&c_phase, 1.0, -phase);
         /* loop over azimuth pixels */
         for (i = 0; i < pPR->nx; i++) {
            x			= i * dx - xmid;
            /* remove phase from HH image */
            s			= getSIMpixel (&(pPR->HHstack[track].Image), i, j);
            cs			= xy_complex (s.data.cf.x, s.data.cf.y);
            cs			= complex_mul (cs, c_phase);
            s.data.cf.x	= (float) cs.x;
            s.data.cf.y	= (float) cs.y;
            putSIMpixel (&(pPR->HHstack[track].Image), s, i, j);
            /* remove phase from HV image */
            s			= getSIMpixel (&(pPR->HVstack[track].Image), i, j);
            cs			= xy_complex (s.data.cf.x, s.data.cf.y);
            cs			= complex_mul (cs, c_phase);
            s.data.cf.x	= (float) cs.x;
            s.data.cf.y	= (float) cs.y;
            putSIMpixel (&(pPR->HVstack[track].Image), s, i, j);
            /* remove phase from VV image */
            s			= getSIMpixel (&(pPR->VVstack[track].Image), i, j);
            cs			= xy_complex (s.data.cf.x, s.data.cf.y);
            cs			= complex_mul (cs, c_phase);
            s.data.cf.x	= (float) cs.x;
            s.data.cf.y	= (float) cs.y;
            putSIMpixel (&(pPR->VVstack[track].Image), s, i, j);
            
         }
         
      }
   }
   return;
}

#endif

/******************************************/
/* Output the internally generated forest */
/******************************************/

void     Write_Forest_XML      (PolSARproSim_Record *pPR)
{
   FILE     *pForestXMLFile;
   int      itree;
   Tree     tree1;
   
   if ((pForestXMLFile = fopen(pPR->ForestOutput, "w")) == NULL) {
      printf ("ERROR: Unable to open forest xml output file %s.\n", pPR->ForestOutput);
      exit (0);
   }
   /* print the preamble */
   fprintf(pForestXMLFile, "<?xml version=\"1.0\" encoding=\"ISO-8859-15\"?>\n");
   fprintf(pForestXMLFile, "<?xml-stylesheet type=\"text/xsl\" href=\"forest.xsl\"?>\n");
   /* the main forest tag */
   fprintf(pForestXMLFile, "<forest>\n");
   /* meta tag */
   fprintf(pForestXMLFile, "\t<meta>\n");
   fprintf(pForestXMLFile, "\t\t<num_trees\tunits=\"none\">%12d\t</num_trees>\t\t<!-- The total number of trees in this file\t\t\t-->\n", pPR->Trees);
   fprintf(pForestXMLFile, "\t</meta>\n");
   Create_Tree (&tree1);
   for (itree=0; itree<pPR->Trees; itree++) {
      fprintf(pForestXMLFile, "\t<tree>\n");
      Realise_Tree		(&tree1, itree, pPR);
      fprintf(pForestXMLFile, "\t\t<species\tunits=\"none\">%12s\t</species>\t\t<!-- Species name (see allometry file)\t\t\t\t-->\n", pPR->SpeciesDataBase[tree1.species].species_name);
      fprintf(pForestXMLFile, "\t\t<x_location\tunits=\"meters\">%12f\t</x_location>\t\t<!-- X-axis location of tree, scene center is 0.00\t\t-->\n", tree1.base.x[0]);
      fprintf(pForestXMLFile, "\t\t<y_location\tunits=\"meters\">%12f\t</y_location>\t\t<!-- Y-axis location of tree, scene center is 0.00\t\t-->\n", tree1.base.x[1]);
      fprintf(pForestXMLFile, "\t\t<tree_height\tunits=\"meters\">%12f\t</tree_height>\t\t<!-- Vertical extent from tree base to canopy top\t\t-->\n", tree1.height);
      fprintf(pForestXMLFile, "\t\t<canopy_radius\tunits=\"meters\">%12f\t</canopy_radius>\t<!-- The largest horizontal radius of the canopy\t\t-->\n", tree1.radius);
      fprintf(pForestXMLFile, "\t\t<canopy_depth\tunits=\"meters\">%12f\t</canopy_depth>\t\t<!-- The depth of the live part of the canopy\t\t\t-->\n", tree1.canopy_depth);
      fprintf(pForestXMLFile, "\t\t<dry_depth\tunits=\"meters\">%12f\t</dry_depth>\t\t<!-- The depth of the dry part of the canopy\t\t\t-->\n", tree1.canopy_dry_depth);
      fprintf(pForestXMLFile, "\t\t<stem_diameter\tunits=\"meters\">%12f\t</stem_diameter>\t<!-- Diameter of trunk at breast height (dbh)\t\t\t-->\n", tree1.dbh);
      fprintf(pForestXMLFile, "\t</tree>\n");
   }
   
   fprintf(pForestXMLFile, "</forest>\n");   
   
   printf("Successfully opened forest output file\n");
   
   /* clean up */
   Destroy_Tree (&tree1);
   fclose(pForestXMLFile);

}

/************************************/
/* Write out the radar look vectors */
/************************************/

void		Write_Stack_LookVectors				(PolSARproSim_Record *pPR)
{
   int      itrack, ix, jy;
   double   x, y;
   char     trackid[10];
   char     postfix[9];
   char     *filename;
   FILE     *pLOSfile;
   double   Lx       = pPR->Lx;
   double   Ly       = pPR->Ly;
   double   p_slant_range;
   double   p_incidence_angle;
   double   p_ground_range;
   double   p_height;
   double   S,C,H; /* along-track (S), cross track (C), height (C) components of look vector */
   
   sprintf(postfix, "los.dat");
   for (itrack = 0; itrack<pPR->Tracks; itrack++){      
      
      /* compute file name */ 
      sprintf(trackid, "track%03d",itrack); 
      filename = (char*) calloc (strlen(pPR->pMasterDirectory)+strlen(pPR->pFilenamePrefix)+1+strlen(trackid)+1+strlen(postfix), sizeof(char));
      strcpy (filename, pPR->pMasterDirectory);
      strncat(filename, pPR->pFilenamePrefix, strlen(pPR->pFilenamePrefix));
      strncat(filename, "_",1);
      strncat(filename, trackid, strlen(trackid));
      strncat(filename, "_",1);
      strncat(filename, postfix, strlen(postfix));
      /* try to open the file */
      if ((pLOSfile = fopen(filename, "wb")) == NULL) {
         printf ("ERROR: Unable to open LOS output file %s.\n", filename);
         exit (0);
      }
      /* compute geometry for center pixel */
      p_slant_range        = pPR->slant_range[itrack];
      p_incidence_angle    = pPR->incidence_angle[itrack];
      p_ground_range       = p_slant_range * sin(p_incidence_angle);
      p_height             = p_slant_range * cos(p_incidence_angle);
      
      for (ix = 0; ix<pPR->nx; ix++){
         x = ix * pPR->deltax - Lx/2;
         for(jy = 0; jy<pPR->ny; jy++){
            y = jy * pPR->deltay - Ly/2;
            /* compute the look vector components for this particular pixel */
            S = 0;                                          /* there is no along track component   */
            C = y + p_ground_range;                         /* cross track component               */
            H = -1 * (p_height - ground_height(pPR, x, y)); /* so the look vector points downward  */
            fwrite (&S, sizeof(double), 1, pLOSfile);
            fwrite (&C, sizeof(double), 1, pLOSfile);
            fwrite (&H, sizeof(double), 1, pLOSfile);
         } 
      }
      fclose(pLOSfile);
   }   
   return;
}

