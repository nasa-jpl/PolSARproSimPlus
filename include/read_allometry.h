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
 * Module      : read_allometry.h
 * Revision    : Version 1.0 
 * Date        : August, 2012
 * Notes       : Procedure prototype for reading allometry database file
 */


#ifndef _read_allometry_h
#define _read_allometry_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <ctype.h>
#include <math.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "PolSARproSim_Structures.h"
#include "PolSARproSim_Definitions.h"
#include "Trig.h"
#include "read_forest.h"
#include "Crown.h"
#include "Leaf.h"


#define SPECNAME_MAX_STRSIZE                 80  /* A species name should not exceed this limit */

/* XML TAG for the Data Base File */
#define ALLOMETRY_XMLTAG                     "allometry"

/* level 1 XML TAGS */
#define SPECIES_LIST_XMLTAG                  "species_list"    /* XML TAG for the species list */
#define CATEGORY_LIST_XMLTAG                 "category_list"   /* XML TAG for the category list */

/* level 2 XML TAGS */

#define SPECIES_LIST_NAME_XMLTAG             "name"   /* XML TAG for species names inside the species_list */
#define CATEGORY_LIST_NAME_XMLTAG            "name"  /* XML TAG for species names inside the species_list */

/* XML TAGS for species properties */
#define  CATEGORY_XMLTAG                     "category"
/* crown parameters */
#define  LIVE_CROWN_SHAPE_XMLTAG             "crown_live_shape"
#define  DRY_CROWN_SHAPE_XMLTAG              "crown_dry_shape"
#define  LIVE_CROWN_DEPTH_FACTOR_XMLTAG      "crown_live_depth_factor"
#define  DRY_CROWN_DEPTH_FACTOR_XMLTAG       "crown_dry_depth_factor"
#define  CROWN_LIVE_ALPHA_XMLTAG             "crown_live_alpha"
#define  CROWN_DRY_ALPHA_XMLTAG              "crown_dry_alpha"
#define  CROWN_RADIUS_FACTOR_XMLTAG          "crown_radius_factor"
/* stem parameters */
#define  STEM_START_RADIUS_FACTOR_XMLTAG     "stem_start_radius_factor"
#define  STEM_MAX_POLAR_ANGLE_XMLTAG         "stem_maximum_polar_angle"
#define  STEM_END_RADIUS_FACTOR_XMLTAG       "stem_radius_end_factor"
#define  STEM_TROPISM_FACTOR_XMLTAG          "stem_tropism_factor"
#define  STEM_LAMDACX_STDEV_XMLTAG           "stem_lamdacx_stdev"
#define  STEM_LAMDACX_MEAN_XMLTAG            "stem_lamdacx_mean"
#define  STEM_LAMDACY_STDEV_XMLTAG           "stem_lamdacy_stdev"
#define  STEM_LAMDACY_MEAN_XMLTAG            "stem_lamdacy_mean"
#define  STEM_GAMMA_STDEV_XMLTAG             "stem_gamma_stdev"
#define  STEM_GAMMA_MEAN_XMLTAG              "stem_gamma_mean"
#define  STEM_MOISTURE_XMLTAG                "stem_moisture"
#define  STEM_TROPISM_DIR_THETA_XMLTAG       "stem_tropism_polar_angle"
#define  STEM_TROPISM_DIR_PHI_XMLTAG         "stem_tropism_azimuth_angle"
/* primary parameters */
#define  PRIMARY_AVG_POLAR_ANGLE_XMLTAG      "primary_polar_angle_mean"
#define  PRIMARY_STD_POLAR_ANGLE_XMLTAG      "primary_polar_angle_stdev"
#define  PRIMARY_LAYER_DENSITY_XMLTAG        "primary_layer_density"
#define  PRIMARY_AVG_SECTIONS_XMLTAG         "primary_sections"
#define  PRIMARY_AZIMUTH_FACTOR_XMLTAG       "primary_azimuth_factor"
#define  PRIMARY_RADIUS_A_XMLTAG             "primary_radius_quadratic_coeff"
#define  PRIMARY_RADIUS_B_XMLTAG             "primary_radius_linear_coeff"
#define  PRIMARY_RADIUS_C_XMLTAG             "primary_radius_constant_coeff"
#define  PRIMARY_TROPISM_FACTOR_XMLTAG       "primary_tropism_factor"
#define  PRIMARY_TROPISM_DIR_THETA_XMLTAG    "primary_tropism_polar_angle"
#define  PRIMARY_TROPISM_DIR_PHI_XMLTAG      "primary_tropism_azimuth_angle"
#define  PRIMARY_LAMDACX_STDEV_XMLTAG        "primary_lamdacx_stdev"
#define  PRIMARY_LAMDACX_MEAN_XMLTAG         "primary_lamdacx_mean"
#define  PRIMARY_LAMDACY_STDEV_XMLTAG        "primary_lamdacy_stdev"
#define  PRIMARY_LAMDACY_MEAN_XMLTAG         "primary_lamdacy_mean"
#define  PRIMARY_GAMMA_STDEV_XMLTAG          "primary_gamma_stdev"
#define  PRIMARY_GAMMA_MEAN_XMLTAG           "primary_gamma_mean"
#define  PRIMARY_LIVE_MOISTURE_XMLTAG        "primary_live_moisture"
#define  PRIMARY_DRY_MOISTURE_XMLTAG         "primary_dry_moisture"
#define  PRIMARY_DRY_LAYER_DENSITY_XMLTAG    "primary_dry_layer_density"
#define  PRIMARY_DRY_SECTIONS_XMLTAG         "primary_dry_sections"
/* secondary parameters */
#define  SECONDARY_NUMBER_SLOPE_XMLTAG       "secondary_number_slope"
#define  SECONDARY_NUMBER_INTERCEPT_XMLTAG   "secondary_number_intercept"
#define  SECONDARY_OFFSET_FRACTION_XMLTAG    "secondary_offset_fraction"
#define  SECONDARY_AVG_POLAR_ANGLE_XMLTAG    "secondary_polar_angle_mean"
#define  SECONDARY_STD_POLAR_ANGLE_XMLTAG    "secondary_polar_angle_stdev"
#define  SECONDARY_RADIUS_FACTOR_XMLTAG      "secondary_radius_factor"
#define  SECONDARY_TROPISM_FACTOR_XMLTAG     "secondary_tropism_factor"
#define  SECONDARY_TROPISM_DIR_THETA_XMLTAG  "secondary_tropism_polar_angle"
#define  SECONDARY_TROPISM_DIR_PHI_XMLTAG    "secondary_tropism_azimuth_angle"
#define  SECONDARY_LAMDACX_STDEV_XMLTAG      "secondary_lamdacx_stdev"
#define  SECONDARY_LAMDACX_MEAN_XMLTAG       "secondary_lamdacx_mean"
#define  SECONDARY_LAMDACY_STDEV_XMLTAG      "secondary_lamdacy_stdev"
#define  SECONDARY_LAMDACY_MEAN_XMLTAG       "secondary_lamdacy_mean"
#define  SECONDARY_GAMMA_STDEV_XMLTAG        "secondary_gamma_stdev"
#define  SECONDARY_GAMMA_MEAN_XMLTAG         "secondary_gamma_mean"
/* tertiary parameters */
#define  TERTIARY_MIN_RADIUS_XMLTAG          "tertiary_minimum_radius"
#define  TERTIARY_MIN_LENGTH_XMLTAG          "tertiary_minimum_length"
#define  TERTIARY_VOLUME_FRACTION_XMLTAG     "tertiary_volume_fraction"
#define  TERTIARY_NUMBER_FACTOR_XMLTAG       "tertiary_number_factor"
#define  TERTIARY_MOISTURE_XMLTAG            "tertiary_moisture"
/* foliage parameters */
#define  LEAF_SHAPE_XMLTAG                   "leaf_shape"
#define  LEAF_WIDTH_MEAN_XMLTAG              "leaf_width_mean"
#define  LEAF_WIDTH_STDEV_XMLTAG             "leaf_width_stdev"
#define  LEAF_HEIGHT_MEAN_XMLTAG             "leaf_height_mean"
#define  LEAF_HEIGHT_STDEV_XMLTAG            "leaf_height_stdev"
#define  LEAF_THICKNESS_MEAN_XMLTAG          "leaf_thickness_mean"
#define  LEAF_THICKNESS_STDEV_XMLTAG         "leaf_thickness_stdev"
#define  LEAF_VOLUME_FRACTION_XMLTAG         "leaf_volume_fraction"
#define  LEAF_NUMBER_FACTOR_XMLTAG           "leaf_number_factor"
#define  LEAF_MOISTURE_XMLTAG                "leaf_moisture"

/* text values for various XML tags */
/* crown shapes */
#define  CROWN_CYLINDER_XMLID                "cylindrical"
#define  CROWN_CONE_XMLID                    "conical"
#define  CROWN_SPHERE_XMLID                  "spheroid"
#define  CROWN_NONE_XMLID                    "none"
/* leaf shapes */
#define  LEAF_SHAPE_NEEDLE_XMLID             "needle"
#define  LEAF_SHAPE_BROADLEAF_XMLID          "broadleaf"

/* XML Read error values */
#define XML_READ_ERROR                    0
#define XML_READ_SUCCESS                  1
#define NULL_CATEGORY                     -1

/* range of allowed values */
#define MIN_LIVE_CROWN_DEPTH_FACTOR       0.0
#define MAX_LIVE_CROWN_DEPTH_FACTOR       1.0
#define MIN_DRY_CROWN_DEPTH_FACTOR        0.0
#define MAX_DRY_CROWN_DEPTH_FACTOR        1.0
#define MIN_CROWN_LIVE_ALPHA              0.0
#define MAX_CROWN_LIVE_ALPHA              1.0
#define MIN_CROWN_DRY_ALPHA               0.0
#define MAX_CROWN_DRY_ALPHA               1.0
#define MIN_CROWN_RADIUS_FACTOR           0.0
#define MAX_CROWN_RADIUS_FACTOR           1.0
#define MIN_STEM_START_RADIUS_FACTOR      0.0
#define MAX_STEM_START_RADIUS_FACTOR      1.0
#define MIN_STEM_ANGLE                    0.0
#define MAX_STEM_ANGLE                    90.0
#define MIN_STEM_END_RADIUS_FACTOR        0.0
#define MAX_STEM_END_RADIUS_FACTOR        1.0
#define MIN_STEM_TROPISM_FACTOR           0.0
#define MAX_STEM_TROPISM_FACTOR           1.0
#define MIN_STEM_LAMDACX_STDEV            0.0
#define MAX_STEM_LAMDACX_STDEV            1.0
#define MIN_STEM_LAMDACX_MEAN             0.0
#define MAX_STEM_LAMDACX_MEAN             1.0
#define MIN_STEM_LAMDACY_STDEV            0.0
#define MAX_STEM_LAMDACY_STDEV            1.0
#define MIN_STEM_LAMDACY_MEAN             0.0
#define MAX_STEM_LAMDACY_MEAN             1.0
#define MIN_STEM_GAMMA_STDEV              0.0
#define MAX_STEM_GAMMA_STDEV              1.0
#define MIN_STEM_GAMMA_MEAN               0.0
#define MAX_STEM_GAMMA_MEAN               1.0
#define MIN_STEM_MOISTURE                 0.0
#define MAX_STEM_MOISTURE                 0.7
#define MIN_STEM_TROPISM_THETA            0.0
#define MAX_STEM_TROPISM_THETA            180.0
#define MIN_STEM_TROPISM_PHI              0.0
#define MAX_STEM_TROPISM_PHI              360.0
#define MIN_PRIMARY_AVG_POLAR_ANGLE       0.0
#define MAX_PRIMARY_AVG_POLAR_ANGLE       180.0
#define MIN_PRIMARY_STD_POLAR_ANGLE       0.0
#define MAX_PRIMARY_STD_POLAR_ANGLE       90.0
#define MIN_PRIMARY_LAYER_DENSITY         0.0
#define MAX_PRIMARY_LAYER_DENSITY         100.
#define MIN_PRIMARY_AVERAGE_SECTIONS      0.0
#define MAX_PRIMARY_AVERAGE_SECTIONS      10.0
#define MIN_PRIMARY_AZIMUTH_FACTOR        0.0
#define MAX_PRIMARY_AZIMUTH_FACTOR        360.0
#define MIN_PRIMARY_RADIUS_A              -1.0
#define MAX_PRIMARY_RADIUS_A              1.0
#define MIN_PRIMARY_RADIUS_B              -1.0
#define MAX_PRIMARY_RADIUS_B              1.0
#define MIN_PRIMARY_RADIUS_C              -1.0
#define MAX_PRIMARY_RADIUS_C              1.0
#define MIN_PRIMARY_TROPISM_FACTOR        0.0
#define MAX_PRIMARY_TROPISM_FACTOR        1.0
#define MIN_PRIMARY_TROPISM_THETA         0.0
#define MAX_PRIMARY_TROPISM_THETA         180.0
#define MIN_PRIMARY_TROPISM_PHI           0.0
#define MAX_PRIMARY_TROPISM_PHI           360.0
#define MIN_PRIMARY_LAMDACX_STDEV         0.0
#define MAX_PRIMARY_LAMDACX_STDEV         1.0
#define MIN_PRIMARY_LAMDACX_MEAN          0.0
#define MAX_PRIMARY_LAMDACX_MEAN          1.0
#define MIN_PRIMARY_LAMDACY_STDEV         0.0
#define MAX_PRIMARY_LAMDACY_STDEV         1.0
#define MIN_PRIMARY_LAMDACY_MEAN          0.0
#define MAX_PRIMARY_LAMDACY_MEAN          1.0
#define MIN_PRIMARY_GAMMA_STDEV           0.0
#define MAX_PRIMARY_GAMMA_STDEV           1.0
#define MIN_PRIMARY_GAMMA_MEAN            0.0
#define MAX_PRIMARY_GAMMA_MEAN            1.0
#define MIN_PRIMARY_LIVE_MOISTURE         0.0
#define MAX_PRIMARY_LIVE_MOISTURE         0.7
#define MIN_PRIMARY_DRY_MOISTURE          0.0
#define MAX_PRIMARY_DRY_MOISTURE          0.7
#define MIN_PRIMARY_DRY_LAYER_DENSITY     0.0
#define MAX_PRIMARY_DRY_LAYER_DENSITY     10.0
#define MIN_PRIMARY_DRY_SECTIONS          0.0
#define MAX_PRIMARY_DRY_SECTIONS          10.0
#define MIN_SECONDARY_NUMBER_SLOPE        -20.0
#define MAX_SECONDARY_NUMBER_SLOPE        20.0
#define MIN_SECONDARY_NUMBER_INTERCEPT    -5.0
#define MAX_SECONDARY_NUMBER_INTERCEPT    5.0
#define MIN_SECONDARY_OFFSET_FRACTION     0.0
#define MAX_SECONDARY_OFFSET_FRACTION     0.95
#define MIN_SECONDARY_AVG_POLAR_ANGLE     0.0
#define MAX_SECONDARY_AVG_POLAR_ANGLE     180.0
#define MIN_SECONDARY_STD_POLAR_ANGLE     0.0
#define MAX_SECONDARY_STD_POLAR_ANGLE     90.0
#define MIN_SECONDARY_RADIUS_FACTOR       0.0
#define MAX_SECONDARY_RADIUS_FACTOR       1.0
#define MIN_SECONDARY_TROPISM_FACTOR      0.0
#define MAX_SECONDARY_TROPISM_FACTOR      1.0
#define MIN_SECONDARY_TROPISM_THETA       0.0
#define MAX_SECONDARY_TROPISM_THETA       180.0
#define MIN_SECONDARY_TROPISM_PHI         0.0
#define MAX_SECONDARY_TROPISM_PHI         360.0
#define MIN_SECONDARY_LAMDACX_STDEV       0.0
#define MAX_SECONDARY_LAMDACX_STDEV       1.0
#define MIN_SECONDARY_LAMDACX_MEAN        0.0
#define MAX_SECONDARY_LAMDACX_MEAN        1.0
#define MIN_SECONDARY_LAMDACY_STDEV       0.0
#define MAX_SECONDARY_LAMDACY_STDEV       1.0
#define MIN_SECONDARY_LAMDACY_MEAN        0.0
#define MAX_SECONDARY_LAMDACY_MEAN        1.0
#define MIN_SECONDARY_GAMMA_STDEV         0.0
#define MAX_SECONDARY_GAMMA_STDEV         1.0
#define MIN_SECONDARY_GAMMA_MEAN          0.0
#define MAX_SECONDARY_GAMMA_MEAN          1.0
#define MIN_TERTIARY_MIN_RADIUS           0.0
#define MAX_TERTIARY_MIN_RADIUS           1.0
#define MIN_TERTIARY_MIN_LENGTH           0.0
#define MAX_TERTIARY_MIN_LENGTH           10.0
#define MIN_TERTIARY_VOLUME_FRACTION      0.0
#define MAX_TERTIARY_VOLUME_FRACTION      1.0
#define MIN_TERTIARY_NUMBER_FACTOR        0.0
#define MAX_TERTIARY_NUMBER_FACTOR        200.0
#define MIN_TERTIARY_MOISTURE             0.0
#define MAX_TERTIARY_MOISTURE             0.7
#define MIN_LEAF_WIDTH_MEAN               0.0
#define MAX_LEAF_WIDTH_MEAN               10.0
#define MIN_LEAF_WIDTH_STDEV              0.0
#define MAX_LEAF_WIDTH_STDEV              10.0
#define MIN_LEAF_HEIGHT_MEAN              0.0
#define MAX_LEAF_HEIGHT_MEAN              10.0
#define MIN_LEAF_HEIGHT_STDEV             0.0
#define MAX_LEAF_HEIGHT_STDEV             10.0
#define MIN_LEAF_THICKNESS_MEAN           0.0
#define MAX_LEAF_THICKNESS_MEAN           10.0
#define MIN_LEAF_THICKNESS_STDEV          0.0
#define MAX_LEAF_THICKNESS_STDEV          10.0
#define MIN_LEAF_VOLUME_FRACTION          0.0
#define MAX_LEAF_VOLUME_FRACTION          1.0
#define MIN_LEAF_NUMBER_FACTOR            0.0
#define MAX_LEAF_NUMBER_FACTOR            200.0
#define MIN_LEAF_MOISTURE                 0.0
#define MAX_LEAF_MOISTURE                 0.7



void Input_PolSARproSim_Allometry   (PolSARproSim_Record *pPR);
void Report_PolSARproSim_Allometry  (PolSARproSim_Record *pPR);
void getCategoryList                (xmlDocPtr doc, xmlNodePtr cur, PolSARproSim_Record *pPR);
void getCategoryData                (xmlDocPtr doc, xmlNodePtr cur, PolSARproSim_Record *pPR, int icategories);
void getSpeciesList                 (xmlDocPtr doc, xmlNodePtr cur, PolSARproSim_Record *pPR);
void getSpeciesData                 (xmlDocPtr doc, xmlNodePtr cur, PolSARproSim_Record *pPR, int ispecies);

#endif
