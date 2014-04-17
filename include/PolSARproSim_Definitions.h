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
 * Module      : PolSARproSim_Definitions.h
 * Revision    : Version C1b 
 * Date        : September, 2007
 * Notes       : Definitions for PolSARproSim
 */
#ifndef __POLSARPROSIM_DEFINITIONS_H__
#define __POLSARPROSIM_DEFINITIONS_H__

#define	NO_POLSARPROSIM_ERRORS					0		/* Good result return value										*/
#define POLSARPROSIM_MAX_PROGRESS				15		/* Maximum value reached by the progress indicator accumulator	*/

#define	POLSARPRO_CONVENTION							/* Controls filenames, output format and calling convention		*/
#define	POLSARPROSIM_ROTATED_IMAGES						/* Rotates images if defined when POLSARPRO_CONVENTION is OFF	*/

/****************************/
/* Tree species enumeration */
/****************************/

#define POLSARPROSIM_NULL_SPECIES				99		/* Not a tree type, just an initialisation value				*/

/**************************************/
/* Tree species allometric parameters */
/**************************************/

#define	TREE_STDDEV_FACTOR                           0.050	/* Standard deviation as a fraction of the mean for Guassian variables	*/

/*******************************/
/* Scene generation parameters */
/*******************************/

#define	RESOLUTION_GAP_SIZE						10.0	/* Amount of SAR image border specified in mean resolutions				*/
//--Modified by Razi to have lots of empty bare surface next to the trees
//#define	RESOLUTION_GAP_SIZE						40.0	/* Amount of SAR image border specified in mean resolutions				*/

/*****************************************/
/* Large scale ground surface generation */
/*****************************************/

#define	POLSARPROSIM_GROUND_FOURIER_MOMENTS		10

/*********************************/
/* Surface parameter calculation */
/*********************************/

/*************************************/
/* New trial surface roughness model */
/*************************************/

#define	POLSARPROSIM_MINRDB                    -0.4
#define	POLSARPROSIM_MIDRDB                    -6.4
#define	POLSARPROSIM_MAXRDB                    -22.4

/*#define	POLSARPROSIM_MINRDB						-6.4	*/
/* Increased this to -6.4 from -10.4 whilst debugging PolInSAR response */
/*#define	POLSARPROSIM_MAXRDB						-22.4	*/

#define	POLSARPROSIM_DEFAULT_SURFACE_ALPHA		 0.06
#define	POLSARPROSIM_DEFAULT_SIGMA0HH          -28.0

#define	POLSARPROSIM_SIGMA0HHL45               -28.0
#define	POLSARPROSIM_SIGMA0HHP45               -38.0
#define	POLSARPROSIM_LBAND                     1.3000
#define	POLSARPROSIM_PBAND                     0.4333
#define	POLSARPROSIM_DELTAS0HHDB               3.00

/****************************/
/* Tree location generation */
/****************************/

#define	TREE_DISC_SHUFFLE_RADIUS_FACTOR			0.95
#define	TREE_LOCATION_NEAREST_NEIGHBOURS       6
#define	TREE_DISC_SHUFFLE_FACTOR               0.8
#define	TREE_DISC_ACCEPTANCE_RATE              0.90
#define	TREE_DISC_ILOOP_MAX                    2000
#define  TREE_DISC_JLOOP_MAX                    1
#define	TREE_DISC_TEMP_FACTOR                  1.0
#define	TREE_DISC_TEMP_ALPHA                   9.0
#define	TREE_DISC_ROTATION_ANGLE               22.5
#define	TREE_DISC_NIMAGES                      1

/*********************************************/
/* Short vegetation layer default parameters */
/*********************************************/
#define  SHORT_VEGI_FLAG_ENABLE                 1
#define  SHORT_VEGI_FLAG_DISABLE                0
#define  SHORT_VEGI_FLAG_DEFAULT                0

#define	DEFAULT_SHORT_VEGI_DEPTH               0.30
#define	DEFAULT_SHORT_VEGI_STEM_VOL_FRAC       0.004
#define	DEFAULT_SHORT_VEGI_LEAF_VOL_FRAC       0.0005

#define POLSARPROSIM_SHORTV_STEM_LENGTH			0.30
#define POLSARPROSIM_SHORTV_STEM_RADIUS			0.0025

#define POLSARPROSIM_SHORTV_LEAF_LENGTH			0.05
#define POLSARPROSIM_SHORTV_LEAF_WIDTH          0.033
#define POLSARPROSIM_SHORTV_LEAF_THICKNESS		0.002

//************************************/
/* Graphic image rendering controls */
/************************************/

//#define	FOREST_GRAPHIC_NY						512
#define	FOREST_GRAPHIC_NY                      2048
#define	FOREST_NEAR_PLANE_FACTOR               3
//#define	FOREST_GRAPHIC_IMAGE_SIZE_FACTOR		1.2
#define	FOREST_GRAPHIC_IMAGE_SIZE_FACTOR       1.0
#define	FOREST_LIGHT_POLAR_ANGLE               30.0
#define	FOREST_LIGHT_AZIMUTH_ANGLE             45.0
#define	FOREST_GRAPHIC_AMBIENT_INTENSITY       0.2
#define	FOREST_GRAPHIC_INCIDENT_INTENSITY		0.8
#define	FOREST_GRAPHIC_DEPTH_CUE
#define	FOREST_GRAPHIC_MIN_CUE                 0.5f
#define	FOREST_GRAPHIC_CROWN_ALPHA_BLEND       0.2
#define	FOREST_GRAPHIC_SHORTV_ALPHA_BLEND		0.2
#define	FOREST_GRAPHIC_SHORTV_FACTOR           10
#define	FOREST_GRAPHIC_SHORTV_STEM_FRACTION		0.5			/* Used in drawing of short vegetation layer elements	*/
#define  FOREST_GRAPHIC_TERTIARY_NUMBER			200			/* The max number of tertiaries per crown drawing		*/
#define	FOREST_GRAPHIC_HEDGE_TERTIARY_SCALING	10			/* More if the hedge is being drawn						*/

#define	FOREST_GRAPHIC_BACKGROUND_RED          128
#define	FOREST_GRAPHIC_BACKGROUND_GREEN			128
#define	FOREST_GRAPHIC_BACKGROUND_BLUE			255

/*************************************/
/* Graphic image material properties */
/*************************************/

#define	FOREST_GRAPHIC_GROUND_KA				1.0
#define	FOREST_GRAPHIC_GROUND_KD				1.0
#define	FOREST_GRAPHIC_GROUND_KS				5.0
#define	FOREST_GRAPHIC_GROUND_SR				0.65
#define	FOREST_GRAPHIC_GROUND_SG				1.0
#define	FOREST_GRAPHIC_GROUND_SB				0.65

#define	FOREST_GRAPHIC_SHORTV_KA				1.0
#define	FOREST_GRAPHIC_SHORTV_KD				1.0
#define	FOREST_GRAPHIC_SHORTV_KS				5.0
#define	FOREST_GRAPHIC_SHORTV_SR				0.85
#define	FOREST_GRAPHIC_SHORTV_SG				0.65
#define	FOREST_GRAPHIC_SHORTV_SB				1.0

#define	FOREST_GRAPHIC_BRANCH_KA				1.0
#define	FOREST_GRAPHIC_BRANCH_KD				1.0
#define	FOREST_GRAPHIC_BRANCH_KS				5.0
#define	FOREST_GRAPHIC_BRANCH_SR				1.0
#define	FOREST_GRAPHIC_BRANCH_SG				0.95
#define	FOREST_GRAPHIC_BRANCH_SB				0.5

#define	FOREST_GRAPHIC_LCROWN_KA				1.0
#define	FOREST_GRAPHIC_LCROWN_KD				1.0
#define	FOREST_GRAPHIC_LCROWN_KS				1.0
#define	FOREST_GRAPHIC_LCROWN_SR				1.0
#define	FOREST_GRAPHIC_LCROWN_SG				0.5
#define	FOREST_GRAPHIC_LCROWN_SB				0.5

#define	FOREST_GRAPHIC_DCROWN_KA				1.0
#define	FOREST_GRAPHIC_DCROWN_KD				1.0
#define	FOREST_GRAPHIC_DCROWN_KS				5.0
#define	FOREST_GRAPHIC_DCROWN_SR				0.5
#define	FOREST_GRAPHIC_DCROWN_SG				0.5
#define	FOREST_GRAPHIC_DCROWN_SB				0.5

#define	FOREST_GRAPHIC_LEAF_KA					1.0
#define	FOREST_GRAPHIC_LEAF_KD					1.0
#define	FOREST_GRAPHIC_LEAF_KS					5.0
#define	FOREST_GRAPHIC_LEAF_SR					0.5
#define	FOREST_GRAPHIC_LEAF_SG					1.0
#define	FOREST_GRAPHIC_LEAF_SB					0.3

/*********************************/
/* Graphic image tree parameters */
/*********************************/

#define FOREST_GRAPHIC_MIN_BRANCH_SIDES			6
#define FOREST_GRAPHIC_MAX_BRANCH_SIDES			12
#define FOREST_GRAPHIC_MIN_BRANCH_SECTIONS		6
#define FOREST_GRAPHIC_MAX_BRANCH_SECTIONS		12
#define FOREST_GRAPHIC_MIN_CROWN_SIDES          12
#define FOREST_GRAPHIC_MAX_CROWN_SIDES          24
#define FOREST_GRAPHIC_MIN_CROWN_SECTIONS       12
#define FOREST_GRAPHIC_MAX_CROWN_SECTIONS       24

/*****************/
/* Miscellaneous */
/*****************/

#define	ROUNDING_ERROR                         FLT_EPSILON			/* Used in the ray intersection routines for branch creation	*/
#define	LIGHT_SPEED                            0.299792458			/* The speed of light in vacuum in convenient units of 10^9m/s	*/

/***************************************/
/* Ground surface description controls */
/***************************************/

#define	DEFAULT_GROUND_MV                      0.25				/* Default soil volumetric warer content						*/
#define	INPUT_GROUND_MV												/* Read soil moisture model from input file if #defined			*/
#define	MIN_GROUND_MV                          0.1					/* Minimum permissible soil moisture value						*/
#define	MAX_GROUND_MV                          0.3					/* Maximum permissible soil moisture value						*/

/******************************/
/* Attenuation and scattering */
/******************************/

#define	POLSARPROSIM_SHORT_VEGI_NTHETA         51
#define	POLSARPROSIM_SHORT_VEGI_NPHI           101
#define	POLSARPROSIM_ATTENUATION_TREES         50
#define	POLSARPROSIM_TERTIARY_NTHETA           51
#define	POLSARPROSIM_TERTIARY_NPHI             101
#define	GRG_VALIDITY_FACTOR                    0.1         /* Used to decide scattering model for tertiary branches		*/
#define	AMAP_RESOLUTION_FACTOR                 1.0         /* Determines the size of the attenuation map grid				*/
#define	AMAP_VERTICAL_RESOLUTION               1.0         /* Determines the vertical resolution of the attenuation map grid				*/
#define	AMAP_SHORT_VEGI_NZ                     10          /* Length of short vegi attenuation depth look-up table			*/
#define	NO_DIRECT_ATTENUATION_LOOKUP_ERRORS    0           /* Good return value when looking up direct attenuation values	*/
//#define  ENABLE_ATTENUATION_FROM_STEMS                       /* To enable attenuation from stems, this will slow it down   */

/*************************/
/* SAR image calculation */
/*************************/

#define  DEFAULT_RESOLUTION_SAMPLING_FACTOR		0.6667               /* Ratio of pixel dimension to resolution, default 2/3               */
#define	POWER_AT_PSF_EDGE                      0.0001               /* Helps fix the extent to which the PSF is calculated               */
//#define  POLSARPROSIM_PSF_GAUSSIAN                                 /* If this is defined a Gaussain PSF will be used                    */
#define  PSF_OVERSAMPLING_FACTOR                100                  /* to determine the resolution of the PSF lookup tables              */
#define  PSF_SHOULDER                           1.1                  /* extra samples on either side of the PSF vectors                   */
#define  PSF_INCIDENCE_ANGLE_RESOLUTION         1                    /* resolution of incidence angles for PSF in ground range (degrees)  */

/**********************************************/
/* Direct ground surface backscatter controls */
/**********************************************/

//#define	POLSARPROSIM_DIRECTGROUND_SPECKLE_FACTOR	2            /* Controls how many facets there are per resolution cell: n = 4f^2, f=2, n=16	*/
#define	POLSARPROSIM_DIRECTGROUND_SPECKLE_FACTOR     2            /* Controls how many facets there are per resolution cell: n = 4f^2, f=2, n=16	*/ 
//#define	POLSARPROSIM_DIRECTGROUND_DELTAB_FACTOR		15.0         /* Beta rotation angle factor for increased entropy	(range 0-100, default 33.0)	*/
#define	POLSARPROSIM_DIRECTGROUND_DELTAB_FACTOR		0.1         /* Beta rotation angle factor for increased entropy	(range 0-100, default 33.0)	*/ 
#define  POLSARPROSIM_DIRECTGROUND_FACETS             8           /* number of facets in a direct ground pixel */
/*****************************/
/* Short vegetation controls */
/*****************************/

#define	POLSARPROSIM_SHORT_VEGI_REALISATIONS		30               /* Number of short vegi elements realised in each resolution cell by species	*/

/***************************************/
/* Rayleigh reflection roughness model */
/***************************************/

#define	POLSARPROSIM_RAYLEIGH_ROUGHNESS_MODEL		2                /* 0: Large-scale only, 1: Small-sacle only, 2: Combined						*/

/*******************/
/* Forest controls */
/*******************/

#define	POLSARPROSIM_SAR_BRANCH_FACTOR					0.5			/* Controls the length of branch subdivisions in calculating SAR images			*/
#define	POLSARPROSIM_SAR_GRG_TERTIARY_BRANCHES			0			/* Flag values for choice of scattering model					*/
#define	POLSARPROSIM_SAR_INF_TERTIARY_BRANCHES			1

/*******************************/
/* Acceptance testing controls */
/*******************************/

#define	SWITCH_ATTENUATION_ON
/* No attenuation effects if undefined							*/
/*#define	RAYLEIGH_LEAF										*/
/* Rayleigh scattering for short vegi and foliage if defined	*/

/*****************************************************************/
/* Commented-out definitions collected here to ease compilation  */
/*****************************************************************/

/*#define	VERBOSE_POLSARPROSIM								*/
#define	VERBOSE_POLSARPROSIM
/* Lots of output to stdout if this is defined					*/

/****************************************************/
/* Graphic image rendering (ground is always drawn) */
/****************************************************/
#define  DRAW_FOREST_IMAGE                            1
#define	FOREST_GRAPHIC_DRAW_STEM
/* Draw tree stems in graphic image if defined			*/
//#define	FOREST_GRAPHIC_DRAW_CROWN
/* Draw tree crowns in graphic image if defined			*/
#define  FOREST_GRAPHIC_DRAW_PRIMARY

/*#define	FOREST_GRAPHIC_DRAW_SHORTV_ELEMENTS					*/
/* Draw a few leaves and stems in the understorey				*/
/*#define	FOREST_GRAPHIC_DRAW_SHORTV_SURFACE					*/
/* Draw the surface of the short vegetation layer				*/
 #define	FOREST_GRAPHIC_DRAW_SECONDARY						   
/* Draw secondary branches in graphic image if defined			*/
#define	FOREST_GRAPHIC_DRAW_TERTIARY						
/* Draw tertiary elements in graphic image if defined			*/
#define	FOREST_GRAPHIC_DRAW_FOLIAGE							
/* Draw foliage elements in graphic image if defined			*/

/*******************/
/* Forest controls */
/*******************/

/*#define	POLSARPROSIM_VERBOSE_TERTIARY						*/
/* Details hybrid method RCS scalings if defined				*/
/*#define	POLSARPROSIM_VERBOSE_FOLIAGE						*/
/* Details hybrid method RCS scalings if defined				*/
//#define	POLSARPROSIM_VERBOSE_TERTIARY
//#define	POLSARPROSIM_VERBOSE_FOLIAGE
/* Details hybrid method RCS scalings if defined				*/

/*******************/
/* DEBUGGING FLAGS */
/*******************/

//#define	FLAT_DEM											
/* Leaves the ground tilted but flat if defined					*/
/*#define	NO_TREE_SHUFFLING									*/
/* Leaves the tree locations on the initial grid if defined		*/
/*#define	FORCE_GRG_CYLINDERS									*/
/* Much faster when debugging									*/
/*#define	NO_SHORT_LEAVES										*/
/* Switch off short vegi leaf contribution						*/
/*#define	NO_SHORT_STEMS										*/
/* Switch off short vegi leaf contribution						*/
/*#define	POLSARPROSIM_NO_SAR_STEMS							*/
/* No stem scattering if defined								*/
/*#define	POLSARPROSIM_NO_SAR_PRIMARIES						*/
/* No primary scattering if defined								*/
/*#define	POLSARPROSIM_NO_SAR_SECONDARIES						*/
/* No secondary scattering if defined							*/
/*#define	POLSARPROSIM_NO_SAR_TERTIARIES						*/
/* No tertiary scattering if defined							*/
/*#define	POLSARPROSIM_NO_SAR_FOLIAGE							*/
/* No foliage scattering if defined								*/

/*****************************/
/* Stage 3 development flags */
/*****************************/

/*#define		POLSARPROSIM_STAGE3								*/
/* Required when setting up tree parameters						*/

#define	POLSARPROSIM_CROWN_OVERLAP_FACTOR		0.892489		
/* Increases the maximum permissible number of trees and permits crowns to overlap					*/
/* Note there is a link between this parameter and POLSARPROSIM_PINE001_TCRSCALE in Allometrics.h	*/

/*************************************/
/* Control for writing output layers */
/*************************************/
/* Will turn off the facility to ouput GRI format images if defined */
//#define		POLSARPROSIM_NOGRIOUTPUT
/* Will turn off the facility to ouput SIM format images if defined */
//#define		POLSARPROSIM_NOSIMOUTPUT
/* Will turn on the facility to compute and output statistics of temporal change profiles */
#define  OUTPUT_CHANGE_STATS_ON
/* Will turn on the output of DEM surface normals  */
#define  OUTPUT_SURFACE_NORMALS_ON
/* Will turn on the output of lookvectors */
#define  OUTPUT_LOOKVECTORS_ON
/* Will turn on the output of DEM */
#define  OUTPUT_DEM_ON
/* Will turn on the output of Max Heights */
#define  OUTPUT_MAX_HEIGHTS_ON
/* Will turn on the output of Shadow Map */
#define  OUTPUT_SHADOW_MAP_ON

/****************************************/
/* Optional flat earth phase correction */
/****************************************/

#define  POLSARPROSIM_FLATEARTH							
/* Will scale images by exp (-j 2kr) if defined						*/

/***********************************************/
/* Stem subdivision control for low-resolution */
/***********************************************/

#define	POLSARPROSIM_MIN_STEM_SEG_NUM             10

/****************************************************/
/* Forest Definition Control                        */
/****************************************************/

#define EXTERNAL_FOREST_DEFINITION                 1 /* Forest primitives read from file */

/****************************************************/
/* External DEM Control                            */
/****************************************************/

#define READ_EXTERNAL_DEM                          1 /* DEM is read from file */

/***************************************************/
/* Multi-processor support                         */
/***************************************************/
/* if this is defined hyperthreading is enabled    */
//#define  ENABLE_THREADS

/***************************************************/
/* Include Thermal Noise                           */
/***************************************************/
/* if this is defined Gaussian noise will be added */
//#define  ADD_THERMAL_NOISE

/***************************************************/
/* Temporal Decorrelation Model                    */
/***************************************************/
#define  CHANGE_REFERENCE_GROUND             0        /* use ground as reference height for change models */
#define  CHANGE_REFERENCE_CANOPY             1        /* use canopy bottom as reference height for change models */
#define  CHANGE_MODEL_NONE                   0        /* model type none - no changes */
#define  CHANGE_MODEL_POLYNOMIAL             1        /* polynomial, i.e change = A * h.^2 + B * h + C */
#define  CHANGE_MODEL_EXPONENTIAL            2        /* exponential, i.e. change = A * exp(B * h) + C */
#define  CHANGE_PROFILE_BINS                 100      /* no. of bins in height profile */
#define  CHANGE_HEIGHT_DELTA                 2.0      /* if branch grows taller than this delta, recompute change parameters */
#define  CHANGE_MOISTURE_MIN                 0.0      /* minimum value of the gravimetric moisture content */
#define  CHANGE_MOISTURE_MAX                 0.7      /* maximum value of the gravimetric moisture content, (see Ulaby, El-Rayes 1987) */
#define  CHANGE_MOISTURE_STDEV_FACTOR        0.1      /* stdev of applied moisture change = (mean applied offset ) * this factor */

/***************************************************/
/* Separation of Scattering Mechanisms             */
/***************************************************/
#define  SSM_ENABLE                          1
#define  SSM_DISABLE                         0
#define  SSM_ACCUM_TOTAL                     0
#define  SSM_ACCUM_GND                       1
#define  SSM_ACCUM_VOL                       2

/**********************************************/
/* PARAMETER FILE MIN/MAX/DEFAULTS            */
/**********************************************/

#define  TRACK_NUMBER_MIN              1
#define  TRACK_NUMBER_MAX              INT_MAX
#define  TRACK_NUMBER_DEFAULT          1

#define  SLANT_RANGE_MIN               0.0
#define  SLANT_RANGE_MAX               DBL_MAX
#define  SLANT_RANGE_DEFAULT           14000.0        /* for a default height of 12km */

#define  INC_ANGLE_MIN                 0.0
#define  INC_ANGLE_MAX                 90.0           /* Maximum Incidence angle */
#define  INC_ANGLE_DEFAULT             40.0           /* Default Incidence angle */

#define  RADAR_FREQUENCY_MIN           0.03           /* Minimum Radar frequency */
#define  RADAR_FREQUENCY_MAX           10.0           /* Maximum Radar frequency */
#define  RADAR_FREQUENCY_DEFAULT       1.25           /* Default at L-band       */

#define  AZIMUTH_RESOLUTION_MIN        0.01           
#define  AZIMUTH_RESOLUTION_MAX        DBL_MAX
#define  AZIMUTH_RESOLUTION_DEFAULT    1.0            /* 1m default resolution   */

#define  RANGE_RESOLUTION_MIN          0.01           
#define  RANGE_RESOLUTION_MAX          DBL_MAX
#define  RANGE_RESOLUTION_DEFAULT      1.0            /* 1m default resolution   */

#define  DEM_MODEL_MIN                 0              /* smoothest               */
#define  DEM_MODEL_MAX                 10             /* roughest                */
#define  DEM_MODEL_DEFAULT             5              /* medium roughness        */

#define  SLOPE_MIN                     0.0
#define  SLOPE_MAX                     1.0
#define  SLOPE_DEFAULT                 0.01

#define  SEED_MIN                      0
#define  SEED_MAX                      INT_MAX
#define  SEED_DEFAULT                  42             /* answer to life, Adams et al. 1980  */

#define  GLOBAL_SPECIES_MIN            0
#define  GLOBAL_SPECIES_MAX            INT_MAX        /* ideally one can have a lot of species defined */
#define  GLOBAL_SPECIES_DEFAULT        2

#define  GLOBAL_TREE_HEIGHT_MIN        1.0
#define  GLOBAL_TREE_HEIGHT_MAX        115.72         /* Hyperion, circa 2006, a Sequoia sempervirens */
#define  GLOBAL_TREE_HEIGHT_DEFAULT    30.0

#define  STAND_AREA_MIN                0.0
#define  STAND_AREA_MAX                DBL_MAX
#define  STAND_AREA_DEFAULT            10000          /* one hectare */

#define  STEM_DENSITY_MIN              0
#define  STEM_DENSITY_MAX              INT_MAX
#define  STEM_DENSITY_DEFAULT          100           

#define  PSF_ETA_MIN                   0.0            /* Hann */
#define  PSF_ETA_MAX                   1.0            /* Uniform */
#define  PSF_ETA_DEFAULT               1.0            /* Uniform weight as default */

#define  SAMPLING_FACTOR_MIN           0.1            /* posting should be no finer than a tenth of the resolution */
#define  SAMPLING_FACTOR_MAX           1.0            /* posting should be finer than resolution */

#define  GROUND_MOISTURE_MIN           0
#define  GROUND_MOISTURE_MAX           10
#define  GROUND_MOISTURE_DEFAULT       5              /* moderately moist */

#define  INPUT_FOREST_MIN              0              /* make my own forest */
#define  INPUT_FOREST_MAX              1              /* read forest from XML file */
#define  INPUT_FOREST_DEFAULT          1              /* read forest from XML file by default */

#define  DRAW_FOREST_MIN               0              /* don't draw forest */
#define  DRAW_FOREST_MAX               1              /* draw forest and save to output file */
#define  DRAW_FOREST_DEFAULT           0              /* don't draw forest by default */

#define  CHANGE_MODEL_TYPE_MIN         0              /* no change */
#define  CHANGE_MODEL_TYPE_MAX         2              /* 1 = polynomial, 2 = exponential etc... */
#define  CHANGE_MODEL_TYPE_DEFAULT     0              /* no change by default */

#define  CHANGE_REFERENCE_TYPE_MIN     CHANGE_REFERENCE_GROUND              /* ground reference height */
#define  CHANGE_REFERENCE_TYPE_MAX     CHANGE_REFERENCE_CANOPY              /* canopy bottom as reference height */
#define  CHANGE_REFERENCE_TYPE_DEF     CHANGE_REFERENCE_GROUND              /* ground reference by default */

#define  ENABLE_FAST_MODE_MIN          0              
#define  ENABLE_FAST_MODE_MAX          1              
#define  ENABLE_FAST_MODE_DEFAULT      0              /* Fast mode off by default */

#define  EXTERNAL_DEM_MIN              0
#define  EXTERNAL_DEM_MAX              1
#define  EXTERNAL_DEM_DEFAULT          0              /* No external dem by default */
#define  DEM_NX_MIN                    0
#define  DEM_NX_MAX                    INT_MAX
#define  DEM_NX_DEFAULT                200
#define  DEM_NY_MIN                    0
#define  DEM_NY_MAX                    INT_MAX
#define  DEM_NY_DEFAULT                200
#define  DEM_DX_MIN                    0.0
#define  DEM_DX_MAX                    DBL_MAX
#define  DEM_DX_DEFAULT                1.0
#define  DEM_DY_MIN                    0.0
#define  DEM_DY_MAX                    DBL_MAX
#define  DEM_DY_DEFAULT                1.0

#define  NOISE_POWER_MIN               -65.0          /* Minimum allowable Noise equivalent sigma nought */
#define  NOISE_POWER_MAX               0.0            /* Maximum allowable NESZ  */
#define  NOISE_POWER_DEFAULT           -30.0          /* default NESZ */

#define  SSMFLAG_MIN                   SSM_DISABLE    /* no separations of scattering mechamisms (SSM) into GV+DG, DV */
#define  SSMFLAG_MAX                   SSM_ENABLE     /* separate accumulators for GV+DG, DV */
#define  SSMFLAG_DEFAULT               SSM_DISABLE    /* No SSM by default */

/****************************************/
/* CORNER REFLECTOR CONTROLS            */
/****************************************/
//#define  ENABLE_CORNER_REFLECTORS
#define  NUMBER_OF_CORNER_REFLECTORS   5
#define  CORNER_REFLECTOR_LENGTH       4             /* length of one side of the corner reflector (in meters)    */

/****************************************/
/* FAST FOREST SCATTERING MODE CONTROLS */
/****************************************/
/* in this mode scattering matrix isnt recomputed for each track, just the geometries, saving some time */
#define  FOREST_FAST_MODE_OFF          0              /* turn fast compute mode off */
#define  FOREST_FAST_MODE_ON           1              /* turn fast compute mode on */

/****************/
/* DEM CONTROLS */
/****************/
//#define  DEM_RESAMPLE_NEAREST_NEIGHBOR
#define  DEM_RESAMPLE_BILINEAR
#define  DEFAULT_DEM_HEIGHT            0.0


#endif
