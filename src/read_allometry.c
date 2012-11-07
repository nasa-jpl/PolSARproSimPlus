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
 * Module      : read_allometry.c
 * Revision    : Version 1.1 
 * Date        : August, 2012
 * Notes       : Reading in species characteristics from an XML database
 */


#include "read_allometry.h"

/*********************************/
/* Reads in species primitives   */
/* from XML database file        */
/*********************************/
void getSpeciesData (xmlDocPtr doc, xmlNodePtr cur, PolSARproSim_Record *pPR, int ispecies) {
   
   xmlChar  *key;
   
   char     *category_string;
   int      category                   = NULL_CATEGORY;
   int      icategories                = 0;
   
   int      live_crown_shape           = CROWN_NULL_SHAPE;
   int      dry_crown_shape            = CROWN_NULL_SHAPE;
   double   live_crown_depth_factor    = 1;
   double   dry_crown_depth_factor     = 1;
   double   crown_live_alpha           = 0.4693;
   double   crown_dry_alpha            = 0.4147;
   double   crown_radius_factor        = 0.4221;
   double   stem_start_radius_factor   = 0.5721;
   double   stem_max_angle             = 0;
   double   stem_end_radius_factor     = 0.5;
   double   stem_tropism_factor        = 0.0;
   double   stem_lamdacx_stdev         = 0.5;
   double   stem_lamdacx_mean          = 0.5;
   double   stem_lamdacy_stdev         = 0.5;
   double   stem_lamdacy_mean          = 0.5;
   double   stem_gamma_stdev           = 0.0075;
   double   stem_gamma_mean            = 0.0025;
   double   stem_moisture              = 0.370;
   double   stem_tropism_theta         = 0.0;
   double   stem_tropism_phi           = 0.0;
   double   primary_avg_polar_angle    = 90.0;
   double   primary_std_polar_angle    = 10.0;
   double   primary_layer_density      = 4.015;
   int      primary_avg_sections       = 6;
   double   primary_azimuth_factor     = 0.5;
   double   primary_radius_A           = -0.51532;
   double   primary_radius_B           = 0.53288;
   double   primary_radius_C           = 0.038638;
   double   primary_tropism_factor     = 0.3;
   double   primary_tropism_theta      = 0.0;
   double   primary_tropism_phi        = 0.0;
   double   primary_lamdacx_stdev      = 0.25;
   double   primary_lamdacx_mean       = 0.75;
   double   primary_lamdacy_stdev      = 0.25;
   double   primary_lamdacy_mean       = 0.75;
   double   primary_gamma_stdev        = 0.0075;
   double   primary_gamma_mean         = 0.0025;
   double   primary_live_moisture      = 0.424;
   double   primary_dry_moisture       = 0.100;
   double   primary_dry_density        = 4.015;
   int      primary_dry_sections       = 4;
   double   secondary_number_intercept = -4.26094;
   double   secondary_number_slope     = 18.95864;
   double   secondary_offset_fraction  = 0.08;
   double   secondary_avg_polar_angle  = 90.0;
   double   secondary_std_polar_angle  = 10.0;
   double   secondary_radius_factor    = 0.5;
   double   secondary_tropism_factor   = 0.6;
   double   secondary_tropism_theta    = 0.0;
   double   secondary_tropism_phi      = 0.0;
   double   secondary_lamdacx_stdev    = 0.25;
   double   secondary_lamdacx_mean     = 0.75;
   double   secondary_lamdacy_stdev    = 0.25;
   double   secondary_lamdacy_mean     = 0.75;
   double   secondary_gamma_stdev      = 0.075;
   double   secondary_gamma_mean       = 0.025;
   double   tertiary_min_radius        = 0.011;
   double   tertiary_min_length        = 1.5;
   double   tertiary_volume_fraction   = 0.00025;
   double   tertiary_number_factor     = 120.0;
   double   tertiary_moisture          = 0.4735;
   int      leaf_shape                 = POLSARPROSIM_PINE_NEEDLE;
   double   leaf_width_mean            = 0.020;
   double   leaf_width_stdev           = 0.002;
   double   leaf_height_mean           = 0.001;
   double   leaf_height_stdev          = 0.0001;
   double   leaf_thickness_mean        = 0.001;
   double   leaf_thickness_stdev       = 0.0001;
   double   leaf_moisture              = 0.550;
   double   leaf_number_factor         = 30.0;
   double   leaf_volume_fraction       = 0.00025;
   
   /* Error flags, set by default */
   int      category_errflag                    = XML_READ_ERROR;
   int      live_crown_shape_errflag            = XML_READ_ERROR;
   int      dry_crown_shape_errflag             = XML_READ_ERROR;
   int      lcrown_depthfactor_errflag          = XML_READ_ERROR;
   int      dcrown_depthfactor_errflag          = XML_READ_ERROR;
   int      crown_live_alpha_errflag            = XML_READ_ERROR;
   int      crown_dry_alpha_errflag             = XML_READ_ERROR;
   int      crown_radius_factor_errflag         = XML_READ_ERROR;
   int      stem_start_radius_factor_errflag    = XML_READ_ERROR;
   int      stem_max_angle_errflag              = XML_READ_ERROR;
   int      stem_end_radius_factor_errflag      = XML_READ_ERROR;
   int      stem_tropism_factor_errflag         = XML_READ_ERROR;
   int      stem_lamdacx_stdev_errflag          = XML_READ_ERROR;
   int      stem_lamdacx_mean_errflag           = XML_READ_ERROR;
   int      stem_lamdacy_stdev_errflag          = XML_READ_ERROR;
   int      stem_lamdacy_mean_errflag           = XML_READ_ERROR;
   int      stem_gamma_stdev_errflag            = XML_READ_ERROR;
   int      stem_gamma_mean_errflag             = XML_READ_ERROR;
   int      stem_moisture_errflag               = XML_READ_ERROR;
   int      stem_tropism_theta_errflag          = XML_READ_ERROR;
   int      stem_tropism_phi_errflag            = XML_READ_ERROR;
   int      primary_avg_polar_angle_errflag     = XML_READ_ERROR;
   int      primary_std_polar_angle_errflag     = XML_READ_ERROR;
   int      primary_layer_density_errflag       = XML_READ_ERROR;
   int      primary_avg_sections_errflag        = XML_READ_ERROR;
   int      primary_azimuth_factor_errflag      = XML_READ_ERROR;
   int      primary_radius_A_errflag            = XML_READ_ERROR;
   int      primary_radius_B_errflag            = XML_READ_ERROR;
   int      primary_radius_C_errflag            = XML_READ_ERROR;
   int      primary_tropism_factor_errflag      = XML_READ_ERROR;
   int      primary_tropism_theta_errflag       = XML_READ_ERROR;
   int      primary_tropism_phi_errflag         = XML_READ_ERROR;
   int      primary_lamdacx_stdev_errflag       = XML_READ_ERROR;
   int      primary_lamdacx_mean_errflag        = XML_READ_ERROR;
   int      primary_lamdacy_stdev_errflag       = XML_READ_ERROR;
   int      primary_lamdacy_mean_errflag        = XML_READ_ERROR;
   int      primary_gamma_stdev_errflag         = XML_READ_ERROR;
   int      primary_gamma_mean_errflag          = XML_READ_ERROR;
   int      primary_live_moisture_errflag       = XML_READ_ERROR;
   int      primary_dry_moisture_errflag        = XML_READ_ERROR;
   int      primary_dry_density_errflag         = XML_READ_ERROR;
   int      primary_dry_sections_errflag        = XML_READ_ERROR;
   int      secondary_number_intercept_errflag  = XML_READ_ERROR;
   int      secondary_number_slope_errflag      = XML_READ_ERROR;
   int      secondary_offset_fraction_errflag   = XML_READ_ERROR;
   int      secondary_avg_polar_angle_errflag   = XML_READ_ERROR;
   int      secondary_std_polar_angle_errflag   = XML_READ_ERROR;
   int      secondary_radius_factor_errflag     = XML_READ_ERROR;
   int      secondary_tropism_factor_errflag    = XML_READ_ERROR;
   int      secondary_tropism_theta_errflag     = XML_READ_ERROR;
   int      secondary_tropism_phi_errflag       = XML_READ_ERROR;
   int      secondary_lamdacx_stdev_errflag     = XML_READ_ERROR;
   int      secondary_lamdacx_mean_errflag      = XML_READ_ERROR;
   int      secondary_lamdacy_stdev_errflag     = XML_READ_ERROR;
   int      secondary_lamdacy_mean_errflag      = XML_READ_ERROR;
   int      secondary_gamma_stdev_errflag       = XML_READ_ERROR;
   int      secondary_gamma_mean_errflag        = XML_READ_ERROR;
   int      tertiary_min_radius_errflag         = XML_READ_ERROR;
   int      tertiary_min_length_errflag         = XML_READ_ERROR;
   int      tertiary_volume_fraction_errflag    = XML_READ_ERROR;
   int      tertiary_number_factor_errflag      = XML_READ_ERROR;
   int      tertiary_moisture_errflag           = XML_READ_ERROR;
   int      leaf_shape_errflag                  = XML_READ_ERROR;
   int      leaf_width_mean_errflag             = XML_READ_ERROR;
   int      leaf_width_stdev_errflag            = XML_READ_ERROR;
   int      leaf_height_mean_errflag            = XML_READ_ERROR;
   int      leaf_height_stdev_errflag           = XML_READ_ERROR;
   int      leaf_thickness_mean_errflag         = XML_READ_ERROR;
   int      leaf_thickness_stdev_errflag        = XML_READ_ERROR;
   int      leaf_moisture_errflag               = XML_READ_ERROR;
   int      leaf_number_factor_errflag          = XML_READ_ERROR;
   int      leaf_volume_fraction_errflag        = XML_READ_ERROR;

   cur = cur->xmlChildrenNode;
   while (cur != NULL) {
      /* look for species category */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)CATEGORY_XMLTAG))) {
         category_errflag = XML_READ_SUCCESS; /* Found it, disable error flag */
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         category_string = (char *)calloc(SPECNAME_MAX_STRSIZE,sizeof(char));
         strcpy(category_string,trimwhitespace((char*)key));
         for(icategories=0;icategories<pPR->Ncategories;icategories++){
            if (!strcmp(category_string, pPR->CategoryDataBase[icategories].species_name)){
               category = icategories;
            }
         }
         xmlFree(key);
      }
      /* look for live crown shape */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)LIVE_CROWN_SHAPE_XMLTAG))) {
         live_crown_shape_errflag = XML_READ_SUCCESS; /* found it! disable error flag */
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         if (!strcmp(trimwhitespace((char*)key),         CROWN_CYLINDER_XMLID)){
            live_crown_shape =                           CROWN_CYLINDER;
         }else if (!strcmp(trimwhitespace((char*)key),   CROWN_CONE_XMLID)){
            live_crown_shape =                           CROWN_CONE;
         }else if (!strcmp(trimwhitespace((char*)key),   CROWN_SPHERE_XMLID)){
            live_crown_shape =                           CROWN_SPHEROID;
         }else{
            live_crown_shape_errflag = XML_READ_ERROR; /* did not recognize, set error flag */
         }
         xmlFree(key);
      }
      /* look for dry crown shape */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)DRY_CROWN_SHAPE_XMLTAG))) {
         dry_crown_shape_errflag = XML_READ_SUCCESS; /* found it! disable error flag */
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         if(!strcmp(trimwhitespace((char*)key),          CROWN_CYLINDER_XMLID)){
            dry_crown_shape =                            CROWN_CYLINDER;
         }else if(!strcmp(trimwhitespace((char*)key),    CROWN_CONE_XMLID)){
            dry_crown_shape =                            CROWN_CONE;
         }else if(!strcmp(trimwhitespace((char*)key),    CROWN_SPHERE_XMLID)){
            dry_crown_shape =                            CROWN_SPHEROID;
         }else if (!strcmp(trimwhitespace((char*)key),   CROWN_NONE_XMLID)){
            dry_crown_shape =                            CROWN_NULL_SHAPE;
         }else{
            dry_crown_shape_errflag = XML_READ_ERROR; /* did not recognize, set error flag */
         }
         xmlFree(key);
      }
      /* look for live crown depth factor */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)LIVE_CROWN_DEPTH_FACTOR_XMLTAG))) {
         lcrown_depthfactor_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         live_crown_depth_factor = (double) atof((const char*)key);
         if(live_crown_depth_factor > MAX_LIVE_CROWN_DEPTH_FACTOR || live_crown_depth_factor < MIN_LIVE_CROWN_DEPTH_FACTOR){
            lcrown_depthfactor_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for dry crown depth factor */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)DRY_CROWN_DEPTH_FACTOR_XMLTAG))) {
         dcrown_depthfactor_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         dry_crown_depth_factor = (double) atof((const char*)key);
         if(dry_crown_depth_factor > MAX_DRY_CROWN_DEPTH_FACTOR || dry_crown_depth_factor < MIN_DRY_CROWN_DEPTH_FACTOR){
            dcrown_depthfactor_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for live crown alpha, to estimate crown depth itself, unused if crown depth specified in forest description */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)CROWN_LIVE_ALPHA_XMLTAG))) {
         crown_live_alpha_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         crown_live_alpha = (double) atof((const char*)key);
         if(crown_live_alpha > MAX_CROWN_LIVE_ALPHA || crown_live_alpha < MIN_CROWN_LIVE_ALPHA){
            crown_live_alpha_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for dry crown alpha, to estimate crown depth itself, unused if crown depth specified in forest description */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)CROWN_DRY_ALPHA_XMLTAG))) {
         crown_dry_alpha_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         crown_dry_alpha = (double) atof((const char*)key);
         if(crown_dry_alpha > MAX_CROWN_DRY_ALPHA || crown_dry_alpha < MIN_CROWN_DRY_ALPHA){
            crown_dry_alpha_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for crown radius factor */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)CROWN_RADIUS_FACTOR_XMLTAG))) {
         crown_radius_factor_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         crown_radius_factor = (double) atof((const char*)key);
         if(crown_radius_factor > MAX_CROWN_RADIUS_FACTOR || crown_radius_factor < MIN_CROWN_RADIUS_FACTOR){
            crown_radius_factor_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for stem start radius factor */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)STEM_START_RADIUS_FACTOR_XMLTAG))) {
         stem_start_radius_factor_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         stem_start_radius_factor = (double) atof((const char*)key);
         if(stem_start_radius_factor > MAX_STEM_START_RADIUS_FACTOR || stem_start_radius_factor < MIN_STEM_START_RADIUS_FACTOR){
            stem_start_radius_factor_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for minimum stem angle */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)STEM_MAX_POLAR_ANGLE_XMLTAG))) {
         stem_max_angle_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         stem_max_angle = (double) atof((const char*)key);
         if(stem_max_angle > MAX_STEM_ANGLE || stem_max_angle < MIN_STEM_ANGLE){
            stem_max_angle_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for stem end radius factor */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)STEM_END_RADIUS_FACTOR_XMLTAG))) {
         stem_end_radius_factor_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         stem_end_radius_factor = (double) atof((const char*)key);
         if(stem_end_radius_factor > MAX_STEM_END_RADIUS_FACTOR || stem_end_radius_factor < MIN_STEM_END_RADIUS_FACTOR){
            stem_end_radius_factor_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for stem tropism factor */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)STEM_TROPISM_FACTOR_XMLTAG))) {
         stem_tropism_factor_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         stem_tropism_factor = (double) atof((const char*)key);
         if(stem_tropism_factor > MAX_STEM_TROPISM_FACTOR || stem_tropism_factor < MIN_STEM_TROPISM_FACTOR){
            stem_tropism_factor_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for stem lamdacx stdev  */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)STEM_LAMDACX_STDEV_XMLTAG))) {
         stem_lamdacx_stdev_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         stem_lamdacx_stdev = (double) atof((const char*)key);
         if(stem_lamdacx_stdev > MAX_STEM_LAMDACX_STDEV || stem_lamdacx_stdev < MIN_STEM_LAMDACX_STDEV){
            stem_lamdacx_stdev_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for stem lamdacx mean */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)STEM_LAMDACX_MEAN_XMLTAG))) {
         stem_lamdacx_mean_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         stem_lamdacx_mean = (double) atof((const char*)key);
         if(stem_lamdacx_mean > MAX_STEM_LAMDACX_MEAN || stem_lamdacx_mean < MIN_STEM_LAMDACX_MEAN){
            stem_lamdacx_mean_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for stem lamdacy stdev  */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)STEM_LAMDACY_STDEV_XMLTAG))) {
         stem_lamdacy_stdev_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         stem_lamdacy_stdev = (double) atof((const char*)key);
         if(stem_lamdacy_stdev > MAX_STEM_LAMDACY_STDEV || stem_lamdacy_stdev < MIN_STEM_LAMDACY_STDEV){
            stem_lamdacy_stdev_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for stem lamdacy mean */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)STEM_LAMDACY_MEAN_XMLTAG))) {
         stem_lamdacy_mean_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         stem_lamdacy_mean = (double) atof((const char*)key);
         if(stem_lamdacy_mean > MAX_STEM_LAMDACY_MEAN || stem_lamdacy_mean < MIN_STEM_LAMDACY_MEAN){
            stem_lamdacy_mean_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
     /* look for stem gamma stdev  */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)STEM_GAMMA_STDEV_XMLTAG))) {
         stem_gamma_stdev_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         stem_gamma_stdev = (double) atof((const char*)key);
         if(stem_gamma_stdev > MAX_STEM_GAMMA_STDEV || stem_gamma_stdev < MIN_STEM_GAMMA_STDEV){
            stem_gamma_stdev_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for stem gamma mean */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)STEM_GAMMA_MEAN_XMLTAG))) {
         stem_gamma_mean_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         stem_gamma_mean = (double) atof((const char*)key);
         if(stem_gamma_mean > MAX_STEM_GAMMA_MEAN || stem_gamma_mean < MIN_STEM_GAMMA_MEAN){
            stem_gamma_mean_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for stem moisture */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)STEM_MOISTURE_XMLTAG))) {
         stem_moisture_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         stem_moisture = (double) atof((const char*)key);
         if(stem_moisture > MAX_STEM_MOISTURE || stem_moisture < MIN_STEM_MOISTURE){
            stem_moisture_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for stem tropism angle theta */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)STEM_TROPISM_DIR_THETA_XMLTAG))) {
         stem_tropism_theta_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         stem_tropism_theta = (double) atof((const char*)key);
         if(stem_tropism_theta > MAX_STEM_TROPISM_THETA || stem_tropism_theta < MIN_STEM_TROPISM_THETA){
            stem_tropism_theta_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for stem tropism angle phi */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)STEM_TROPISM_DIR_PHI_XMLTAG))) {
         stem_tropism_phi_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         stem_tropism_phi = (double) atof((const char*)key);
         if(stem_tropism_phi > MAX_STEM_TROPISM_PHI || stem_tropism_phi < MIN_STEM_TROPISM_PHI){
            stem_tropism_phi_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for average secondary polar angle, theta */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_AVG_POLAR_ANGLE_XMLTAG))) {
         primary_avg_polar_angle_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_avg_polar_angle = (double) atof((const char*)key);
         if(primary_avg_polar_angle > MAX_PRIMARY_AVG_POLAR_ANGLE || primary_avg_polar_angle < MIN_PRIMARY_AVG_POLAR_ANGLE){
            primary_avg_polar_angle_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for the standard deviation of the primary polar angle (theta) */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_STD_POLAR_ANGLE_XMLTAG))) {
         primary_std_polar_angle_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_std_polar_angle = (double) atof((const char*)key);
         if(primary_std_polar_angle > MAX_PRIMARY_STD_POLAR_ANGLE || primary_std_polar_angle < MIN_PRIMARY_STD_POLAR_ANGLE){
            primary_std_polar_angle_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for the primary layer density */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_LAYER_DENSITY_XMLTAG))) {
         primary_layer_density_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_layer_density = (double) atof((const char*)key);
         if(primary_layer_density > MAX_PRIMARY_LAYER_DENSITY || primary_layer_density < MIN_PRIMARY_LAYER_DENSITY){
            primary_layer_density_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for the average primary sections */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_AVG_SECTIONS_XMLTAG))) {
         primary_avg_sections_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_avg_sections = (double) atoi((const char*)key);
         if(primary_avg_sections > MAX_PRIMARY_AVERAGE_SECTIONS || primary_avg_sections < MIN_PRIMARY_AVERAGE_SECTIONS){
            primary_avg_sections_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for the primary azimuth factor */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_AZIMUTH_FACTOR_XMLTAG))) {
         primary_azimuth_factor_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_azimuth_factor = (double) atof((const char*)key);
         if(primary_azimuth_factor > MAX_PRIMARY_AZIMUTH_FACTOR || primary_azimuth_factor < MIN_PRIMARY_AZIMUTH_FACTOR){
            primary_azimuth_factor_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for the quadratic coefficient of the primary radius function */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_RADIUS_A_XMLTAG))) {
         primary_radius_A_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_radius_A = (double) atof((const char*)key);
         if(primary_radius_A > MAX_PRIMARY_RADIUS_A || primary_radius_A < MIN_PRIMARY_RADIUS_A){
            primary_radius_A_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for the linear coefficient of the primary radius function */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_RADIUS_B_XMLTAG))) {
         primary_radius_B_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_radius_B = (double) atof((const char*)key);
         if(primary_radius_B > MAX_PRIMARY_RADIUS_B || primary_radius_B < MIN_PRIMARY_RADIUS_B){
            primary_radius_B_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for the constant coefficient of the primary radius function */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_RADIUS_C_XMLTAG))) {
         primary_radius_C_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_radius_C = (double) atof((const char*)key);
         if(primary_radius_C > MAX_PRIMARY_RADIUS_C || primary_radius_C < MIN_PRIMARY_RADIUS_C){
            primary_radius_C_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for primary tropism factor */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_TROPISM_FACTOR_XMLTAG))) {
         primary_tropism_factor_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_tropism_factor = (double) atof((const char*)key);
         if(primary_tropism_factor > MAX_PRIMARY_TROPISM_FACTOR || primary_tropism_factor < MIN_PRIMARY_TROPISM_FACTOR){
            primary_tropism_factor_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for primary tropism angle theta */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_TROPISM_DIR_THETA_XMLTAG))) {
         primary_tropism_theta_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_tropism_theta = (double) atof((const char*)key);
         if(primary_tropism_theta > MAX_PRIMARY_TROPISM_THETA || primary_tropism_theta < MIN_PRIMARY_TROPISM_THETA){
            primary_tropism_theta_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for primary tropism angle phi */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_TROPISM_DIR_PHI_XMLTAG))) {
         primary_tropism_phi_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_tropism_phi = (double) atof((const char*)key);
         if(primary_tropism_phi > MAX_PRIMARY_TROPISM_PHI || primary_tropism_phi < MIN_PRIMARY_TROPISM_PHI){
            primary_tropism_phi_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for primary lamdacx stdev  */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_LAMDACX_STDEV_XMLTAG))) {
         primary_lamdacx_stdev_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_lamdacx_stdev = (double) atof((const char*)key);
         if(primary_lamdacx_stdev > MAX_PRIMARY_LAMDACX_STDEV || primary_lamdacx_stdev < MIN_PRIMARY_LAMDACX_STDEV){
            primary_lamdacx_stdev_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for primary lamdacx mean */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_LAMDACX_MEAN_XMLTAG))) {
         primary_lamdacx_mean_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_lamdacx_mean = (double) atof((const char*)key);
         if(primary_lamdacx_mean > MAX_PRIMARY_LAMDACX_MEAN || primary_lamdacx_mean < MIN_PRIMARY_LAMDACX_MEAN){
            primary_lamdacx_mean_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for primary lamdacy stdev  */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_LAMDACY_STDEV_XMLTAG))) {
         primary_lamdacy_stdev_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_lamdacy_stdev = (double) atof((const char*)key);
         if(primary_lamdacy_stdev > MAX_PRIMARY_LAMDACY_STDEV || primary_lamdacy_stdev < MIN_PRIMARY_LAMDACY_STDEV){
            primary_lamdacy_stdev_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for primary lamdacy mean */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_LAMDACY_MEAN_XMLTAG))) {
         primary_lamdacy_mean_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_lamdacy_mean = (double) atof((const char*)key);
         if(primary_lamdacy_mean > MAX_PRIMARY_LAMDACY_MEAN || primary_lamdacy_mean < MIN_PRIMARY_LAMDACY_MEAN){
            primary_lamdacy_mean_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
     /* look for primary gamma stdev  */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_GAMMA_STDEV_XMLTAG))) {
         primary_gamma_stdev_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_gamma_stdev = (double) atof((const char*)key);
         if(primary_gamma_stdev > MAX_PRIMARY_GAMMA_STDEV || primary_gamma_stdev < MIN_PRIMARY_GAMMA_STDEV){
            primary_gamma_stdev_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for primary gamma mean */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_GAMMA_MEAN_XMLTAG))) {
         primary_gamma_mean_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_gamma_mean = (double) atof((const char*)key);
         if(primary_gamma_mean > MAX_PRIMARY_GAMMA_MEAN || primary_gamma_mean < MIN_PRIMARY_GAMMA_MEAN){
            primary_gamma_mean_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for fractional moisture content of living primary branches */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_LIVE_MOISTURE_XMLTAG))) {
         primary_live_moisture_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_live_moisture = (double) atof((const char*)key);
         if(primary_live_moisture > MAX_PRIMARY_LIVE_MOISTURE || primary_live_moisture < MIN_PRIMARY_LIVE_MOISTURE){
            primary_live_moisture_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for fractional moisture content of dry primary branches */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_DRY_MOISTURE_XMLTAG))) {
         primary_dry_moisture_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_dry_moisture = (double) atof((const char*)key);
         if(primary_dry_moisture > MAX_PRIMARY_DRY_MOISTURE || primary_dry_moisture < MIN_PRIMARY_DRY_MOISTURE){
            primary_dry_moisture_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for the dry primary layer density */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_DRY_LAYER_DENSITY_XMLTAG))) {
         primary_dry_density_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_dry_density = (double) atof((const char*)key);
         if(primary_dry_density > MAX_PRIMARY_DRY_LAYER_DENSITY || primary_dry_density < MIN_PRIMARY_DRY_LAYER_DENSITY){
            primary_dry_density_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for the number of dry primary sections */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_DRY_SECTIONS_XMLTAG))) {
         primary_dry_sections_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_dry_sections = (double) atoi((const char*)key);
         if(primary_dry_sections > MAX_PRIMARY_DRY_SECTIONS || primary_dry_sections < MIN_PRIMARY_DRY_SECTIONS){
            primary_dry_sections_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for the slope of the linear function to determine number of secondary branches */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_NUMBER_SLOPE_XMLTAG))) {
         secondary_number_slope_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_number_slope = (double) atof((const char*)key);
         if(secondary_number_slope > MAX_SECONDARY_NUMBER_SLOPE || secondary_number_slope < MIN_SECONDARY_NUMBER_SLOPE){
            secondary_number_slope_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for the intercept of the linear function to determine number of secondary branches */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_NUMBER_INTERCEPT_XMLTAG))) {
         secondary_number_intercept_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_number_intercept = (double) atof((const char*)key);
         if(secondary_number_intercept > MAX_SECONDARY_NUMBER_INTERCEPT || secondary_number_intercept < MIN_SECONDARY_NUMBER_INTERCEPT){
            secondary_number_intercept_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for the fractional offset of the secondary start location (tmin) */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_OFFSET_FRACTION_XMLTAG))) {
         secondary_offset_fraction_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_offset_fraction = (double) atof((const char*)key);
         if(secondary_offset_fraction > MAX_SECONDARY_OFFSET_FRACTION || secondary_offset_fraction < MIN_SECONDARY_OFFSET_FRACTION){
            secondary_offset_fraction_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for average secondary polar angle, theta */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_AVG_POLAR_ANGLE_XMLTAG))) {
         secondary_avg_polar_angle_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_avg_polar_angle = (double) atof((const char*)key);
         if(secondary_avg_polar_angle > MAX_SECONDARY_AVG_POLAR_ANGLE || secondary_avg_polar_angle < MIN_SECONDARY_AVG_POLAR_ANGLE){
            secondary_avg_polar_angle_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for the standard deviation of the secondary polar angle (theta) */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_STD_POLAR_ANGLE_XMLTAG))) {
         secondary_std_polar_angle_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_std_polar_angle = (double) atof((const char*)key);
         if(secondary_std_polar_angle > MAX_SECONDARY_STD_POLAR_ANGLE || secondary_std_polar_angle < MIN_SECONDARY_STD_POLAR_ANGLE){
            secondary_std_polar_angle_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for the secondary radius factor */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_RADIUS_FACTOR_XMLTAG))) {
         secondary_radius_factor_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_radius_factor = (double) atof((const char*)key);
         if(secondary_radius_factor > MAX_SECONDARY_RADIUS_FACTOR || secondary_radius_factor < MIN_SECONDARY_RADIUS_FACTOR){
            secondary_radius_factor_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
     /* look for secondary tropism factor */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_TROPISM_FACTOR_XMLTAG))) {
         secondary_tropism_factor_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_tropism_factor = (double) atof((const char*)key);
         if(secondary_tropism_factor > MAX_SECONDARY_TROPISM_FACTOR || secondary_tropism_factor < MIN_SECONDARY_TROPISM_FACTOR){
            secondary_tropism_factor_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for secondary tropism angle theta */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_TROPISM_DIR_THETA_XMLTAG))) {
         secondary_tropism_theta_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_tropism_theta = (double) atof((const char*)key);
         if(secondary_tropism_theta > MAX_SECONDARY_TROPISM_THETA || secondary_tropism_theta < MIN_SECONDARY_TROPISM_THETA){
            secondary_tropism_theta_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for secondary tropism angle phi */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_TROPISM_DIR_PHI_XMLTAG))) {
         secondary_tropism_phi_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_tropism_phi = (double) atof((const char*)key);
         if(secondary_tropism_phi > MAX_SECONDARY_TROPISM_PHI || secondary_tropism_phi < MIN_SECONDARY_TROPISM_PHI){
            secondary_tropism_phi_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for secondary lamdacx stdev  */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_LAMDACX_STDEV_XMLTAG))) {
         secondary_lamdacx_stdev_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_lamdacx_stdev = (double) atof((const char*)key);
         if(secondary_lamdacx_stdev > MAX_SECONDARY_LAMDACX_STDEV || secondary_lamdacx_stdev < MIN_SECONDARY_LAMDACX_STDEV){
            secondary_lamdacx_stdev_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for secondary lamdacx mean */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_LAMDACX_MEAN_XMLTAG))) {
         secondary_lamdacx_mean_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_lamdacx_mean = (double) atof((const char*)key);
         if(secondary_lamdacx_mean > MAX_SECONDARY_LAMDACX_MEAN || secondary_lamdacx_mean < MIN_SECONDARY_LAMDACX_MEAN){
            secondary_lamdacx_mean_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for secondary lamdacy stdev  */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_LAMDACY_STDEV_XMLTAG))) {
         secondary_lamdacy_stdev_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_lamdacy_stdev = (double) atof((const char*)key);
         if(secondary_lamdacy_stdev > MAX_SECONDARY_LAMDACY_STDEV || secondary_lamdacy_stdev < MIN_SECONDARY_LAMDACY_STDEV){
            secondary_lamdacy_stdev_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for secondary lamdacy mean */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_LAMDACY_MEAN_XMLTAG))) {
         secondary_lamdacy_mean_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_lamdacy_mean = (double) atof((const char*)key);
         if(secondary_lamdacy_mean > MAX_SECONDARY_LAMDACY_MEAN || secondary_lamdacy_mean < MIN_SECONDARY_LAMDACY_MEAN){
            secondary_lamdacy_mean_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
     /* look for secondary gamma stdev  */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_GAMMA_STDEV_XMLTAG))) {
         secondary_gamma_stdev_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_gamma_stdev = (double) atof((const char*)key);
         if(secondary_gamma_stdev > MAX_SECONDARY_GAMMA_STDEV || secondary_gamma_stdev < MIN_SECONDARY_GAMMA_STDEV){
            secondary_gamma_stdev_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for secondary gamma mean */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_GAMMA_MEAN_XMLTAG))) {
         secondary_gamma_mean_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_gamma_mean = (double) atof((const char*)key);
         if(secondary_gamma_mean > MAX_SECONDARY_GAMMA_MEAN || secondary_gamma_mean < MIN_SECONDARY_GAMMA_MEAN){
            secondary_gamma_mean_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for minimum tertiary radius */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)TERTIARY_MIN_RADIUS_XMLTAG))) {
         tertiary_min_radius_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         tertiary_min_radius = (double) atof((const char*)key);
         if(tertiary_min_radius > MAX_TERTIARY_MIN_RADIUS || tertiary_min_radius < MIN_TERTIARY_MIN_RADIUS){
            tertiary_min_radius_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for minimum tertiary length */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)TERTIARY_MIN_LENGTH_XMLTAG))) {
         tertiary_min_length_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         tertiary_min_length = (double) atof((const char*)key);
         if(tertiary_min_length > MAX_TERTIARY_MIN_LENGTH || tertiary_min_length < MIN_TERTIARY_MIN_LENGTH){
            tertiary_min_length_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for tertiary volume fraction */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)TERTIARY_VOLUME_FRACTION_XMLTAG))) {
         tertiary_volume_fraction_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         tertiary_volume_fraction = (double) atof((const char*)key);
         if(tertiary_volume_fraction > MAX_TERTIARY_VOLUME_FRACTION || tertiary_volume_fraction < MIN_TERTIARY_VOLUME_FRACTION){
            tertiary_volume_fraction_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for tertiary number factor */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)TERTIARY_NUMBER_FACTOR_XMLTAG))) {
         tertiary_number_factor_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         tertiary_number_factor = (double) atof((const char*)key);
         if(tertiary_number_factor > MAX_TERTIARY_NUMBER_FACTOR || tertiary_number_factor < MIN_TERTIARY_NUMBER_FACTOR){
            tertiary_number_factor_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for fractional moisture content of tertiary branches */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)TERTIARY_MOISTURE_XMLTAG))) {
         tertiary_moisture_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         tertiary_moisture = (double) atof((const char*)key);
         if(tertiary_moisture > MAX_TERTIARY_MOISTURE || tertiary_moisture < MIN_TERTIARY_MOISTURE){
            tertiary_moisture_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for leaf shape */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)LEAF_SHAPE_XMLTAG))) {
         leaf_shape_errflag = XML_READ_SUCCESS; /* found it! disable error flag */
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         if (!strcmp(trimwhitespace((char*)key),         LEAF_SHAPE_BROADLEAF_XMLID)){
            leaf_shape  =                                POLSARPROSIM_DECIDUOUS_LEAF;
         }else if (!strcmp(trimwhitespace((char*)key),   LEAF_SHAPE_NEEDLE_XMLID)){
            leaf_shape  =                                POLSARPROSIM_PINE_NEEDLE;
         }else{
            leaf_shape_errflag = XML_READ_ERROR; /* did not recognize, set error flag */
         }
         xmlFree(key);
      }
      /* look for mean leaf width */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)LEAF_WIDTH_MEAN_XMLTAG))) {
         leaf_width_mean_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         leaf_width_mean = (double) atof((const char*)key);
         if(leaf_width_mean > MAX_LEAF_WIDTH_MEAN || leaf_width_mean < MIN_LEAF_WIDTH_MEAN){
            leaf_width_mean_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for leaf width stdev */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)LEAF_WIDTH_STDEV_XMLTAG))) {
         leaf_width_stdev_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         leaf_width_stdev = (double) atof((const char*)key);
         if(leaf_width_stdev > MAX_LEAF_WIDTH_STDEV || leaf_width_stdev < MIN_LEAF_WIDTH_STDEV){
            leaf_width_stdev_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for mean leaf height */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)LEAF_HEIGHT_MEAN_XMLTAG))) {
         leaf_height_mean_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         leaf_height_mean = (double) atof((const char*)key);
         if(leaf_height_mean > MAX_LEAF_HEIGHT_MEAN || leaf_height_mean < MIN_LEAF_HEIGHT_MEAN){
            leaf_height_mean_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for leaf height stdev */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)LEAF_HEIGHT_STDEV_XMLTAG))) {
         leaf_height_stdev_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         leaf_height_stdev = (double) atof((const char*)key);
         if(leaf_height_stdev > MAX_LEAF_HEIGHT_STDEV || leaf_height_stdev < MIN_LEAF_HEIGHT_STDEV){
            leaf_height_stdev_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for mean leaf thickness */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)LEAF_THICKNESS_MEAN_XMLTAG))) {
         leaf_thickness_mean_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         leaf_thickness_mean = (double) atof((const char*)key);
         if(leaf_thickness_mean > MAX_LEAF_THICKNESS_MEAN || leaf_thickness_mean < MIN_LEAF_THICKNESS_MEAN){
            leaf_thickness_mean_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for leaf thickness stdev */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)LEAF_THICKNESS_STDEV_XMLTAG))) {
         leaf_thickness_stdev_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         leaf_thickness_stdev = (double) atof((const char*)key);
         if(leaf_thickness_stdev > MAX_LEAF_THICKNESS_STDEV || leaf_thickness_stdev < MIN_LEAF_THICKNESS_STDEV){
            leaf_thickness_stdev_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for leaf volume fraction */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)LEAF_VOLUME_FRACTION_XMLTAG))) {
         leaf_volume_fraction_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         leaf_volume_fraction = (double) atof((const char*)key);
         if(leaf_volume_fraction > MAX_LEAF_VOLUME_FRACTION || leaf_volume_fraction < MIN_LEAF_VOLUME_FRACTION){
            leaf_volume_fraction_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for leaf number factor */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)LEAF_NUMBER_FACTOR_XMLTAG))) {
         leaf_number_factor_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         leaf_number_factor = (double) atof((const char*)key);
         if(leaf_number_factor > MAX_LEAF_NUMBER_FACTOR || leaf_number_factor < MIN_LEAF_NUMBER_FACTOR){
            leaf_number_factor_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for fractional moisture content of leaf  */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)LEAF_MOISTURE_XMLTAG))) {
         leaf_moisture_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         leaf_moisture = (double) atof((const char*)key);
         if(leaf_moisture > MAX_LEAF_MOISTURE || leaf_moisture < MIN_LEAF_MOISTURE){
            leaf_moisture_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }


   
      cur = cur->next;
   }
   
   /* exit the program if species category flag does not exist or the value is unrecognized */
   if(category_errflag == XML_READ_ERROR || category == NULL_CATEGORY){
      printf("ERROR: Unrecognized/Missing category (coniferous/deciduous) associated with %s in the Species database file\n", pPR->SpeciesDataBase[ispecies].species_name);
      exit(0);
   }
   /************************************/
   /* Read default values if the       */
   /* attributes were not specified    */
   /************************************/
   if(live_crown_shape_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Live crown shape not specified or unrecognized for species '%s' in Species database file, reading in default value from the %s category\n", pPR->SpeciesDataBase[ispecies].species_name, category_string);
      /* read from the default category database */
      live_crown_shape = pPR->CategoryDataBase[category].live_crown_shape;
   }
   if(dry_crown_shape_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Dry crown shape not specified or unrecognized for species '%s' in Species database file, reading in default value from the %s category\n", pPR->SpeciesDataBase[ispecies].species_name, category_string);
      dry_crown_shape = pPR->CategoryDataBase[category].dry_crown_shape;
   }
   if(lcrown_depthfactor_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Live crown depth factor not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_LIVE_CROWN_DEPTH_FACTOR, MAX_LIVE_CROWN_DEPTH_FACTOR, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      live_crown_depth_factor = pPR->CategoryDataBase[category].live_crown_depth_factor;
   }
   if(dcrown_depthfactor_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Dry crown depth factor not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_DRY_CROWN_DEPTH_FACTOR, MAX_DRY_CROWN_DEPTH_FACTOR, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      dry_crown_depth_factor = pPR->CategoryDataBase[category].dry_crown_depth_factor;
   }
   if(crown_live_alpha_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Live crown alpha not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_CROWN_LIVE_ALPHA, MAX_CROWN_LIVE_ALPHA, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      crown_live_alpha = pPR->CategoryDataBase[category].crown_live_alpha;
   }
   if(crown_dry_alpha_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: dry crown alpha not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_CROWN_DRY_ALPHA, MAX_CROWN_DRY_ALPHA, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      crown_dry_alpha = pPR->CategoryDataBase[category].crown_dry_alpha;
   }
   if(crown_radius_factor_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Crown radius factor not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_CROWN_RADIUS_FACTOR, MAX_CROWN_RADIUS_FACTOR, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      crown_radius_factor = pPR->CategoryDataBase[category].crown_radius_factor;
   }
   if(stem_start_radius_factor_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Stem start radius factor not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_STEM_START_RADIUS_FACTOR, MAX_STEM_START_RADIUS_FACTOR, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      stem_start_radius_factor = pPR->CategoryDataBase[category].stem_start_radius_factor;
   }
   if(stem_max_angle_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Stem maximum angle not specified or not between %f and %f degrees for species '%s' in Species database file, reading in default value from the %s category\n", MIN_STEM_ANGLE, MAX_STEM_ANGLE, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      stem_max_angle = pPR->CategoryDataBase[category].stem_max_angle;
   }
   if(stem_end_radius_factor_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Stem end radius factor not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_STEM_END_RADIUS_FACTOR, MAX_STEM_END_RADIUS_FACTOR, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      stem_end_radius_factor = pPR->CategoryDataBase[category].stem_end_radius_factor;
   }
   if(stem_tropism_factor_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Stem tropism not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_STEM_TROPISM_FACTOR, MAX_STEM_TROPISM_FACTOR, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      stem_tropism_factor = pPR->CategoryDataBase[category].stem_tropism_factor;
   }
   if(stem_lamdacx_stdev_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: stdev of stem curvature wavelength (lamdacx) function not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_STEM_LAMDACX_STDEV, MAX_STEM_LAMDACX_STDEV, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      stem_lamdacx_stdev = pPR->CategoryDataBase[category].stem_lamdacx_stdev;
   }
   if(stem_lamdacx_mean_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: mean of stem curvature wavelength (lamdacx) function not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_STEM_LAMDACX_MEAN, MAX_STEM_LAMDACX_MEAN, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      stem_lamdacx_mean = pPR->CategoryDataBase[category].stem_lamdacx_mean;
   }
   if(stem_lamdacy_stdev_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: stdev of stem curvature wavelength (lamdacy) function not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_STEM_LAMDACY_STDEV, MAX_STEM_LAMDACY_STDEV, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      stem_lamdacy_stdev = pPR->CategoryDataBase[category].stem_lamdacy_stdev;
   }
   if(stem_lamdacy_mean_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: mean of stem curvature wavelength (lamdacy) function not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_STEM_LAMDACY_MEAN, MAX_STEM_LAMDACY_MEAN, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      stem_lamdacy_mean = pPR->CategoryDataBase[category].stem_lamdacy_mean;
   }
   if(stem_gamma_stdev_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: stdev of stem curvature scale-factor (gamma) function not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_STEM_GAMMA_STDEV, MAX_STEM_GAMMA_STDEV, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      stem_gamma_stdev = pPR->CategoryDataBase[category].stem_gamma_stdev;
   }
   if(stem_gamma_mean_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: mean of stem curvature scale-factor (gamma) function not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_STEM_GAMMA_MEAN, MAX_STEM_GAMMA_MEAN, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      stem_gamma_mean = pPR->CategoryDataBase[category].stem_gamma_mean;
   }
   if(stem_moisture_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Stem moisture not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_STEM_GAMMA_MEAN, MAX_STEM_GAMMA_MEAN, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      stem_moisture = pPR->CategoryDataBase[category].stem_moisture;
   }
   if(stem_tropism_theta_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Stem tropism polar angle (theta) not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_STEM_TROPISM_THETA, MAX_STEM_TROPISM_THETA , pPR->SpeciesDataBase[ispecies].species_name, category_string);
      stem_tropism_theta = pPR->CategoryDataBase[category].stem_tropism_theta;
   }
   if(stem_tropism_phi_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Stem tropism RADIUSal angle (phi) not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_STEM_TROPISM_PHI, MAX_STEM_TROPISM_PHI, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      stem_tropism_phi = pPR->CategoryDataBase[category].stem_tropism_phi;
   }
   if(primary_avg_polar_angle_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Average primary polar angle (theta) not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_PRIMARY_AVG_POLAR_ANGLE, MAX_PRIMARY_AVG_POLAR_ANGLE, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      primary_avg_polar_angle = pPR->CategoryDataBase[category].primary_avg_polar_angle;
   }
   if(primary_std_polar_angle_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Std. of Primary polar angle (theta) not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_PRIMARY_STD_POLAR_ANGLE, MAX_PRIMARY_STD_POLAR_ANGLE, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      primary_std_polar_angle = pPR->CategoryDataBase[category].primary_std_polar_angle;
   }
   if(primary_layer_density_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Primary layer density not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_PRIMARY_LAYER_DENSITY, MAX_PRIMARY_LAYER_DENSITY, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      primary_layer_density = pPR->CategoryDataBase[category].primary_layer_density;
   }
   if(primary_avg_sections_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Primary average sections not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_PRIMARY_AVERAGE_SECTIONS, MAX_PRIMARY_AVERAGE_SECTIONS, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      primary_avg_sections = pPR->CategoryDataBase[category].primary_avg_sections;
   }
   if(primary_azimuth_factor_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Primary azimuth factor not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_PRIMARY_AZIMUTH_FACTOR, MAX_PRIMARY_AZIMUTH_FACTOR, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      primary_azimuth_factor = pPR->CategoryDataBase[category].primary_azimuth_factor;
   }
   if(primary_radius_A_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Quadratic coefficient of primary radius function not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_PRIMARY_RADIUS_A, MAX_PRIMARY_RADIUS_A, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      primary_radius_A = pPR->CategoryDataBase[category].primary_radius_A;
   }
   if(primary_radius_B_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Linear coefficient of primary radius function not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_PRIMARY_RADIUS_B, MAX_PRIMARY_RADIUS_B, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      primary_radius_B = pPR->CategoryDataBase[category].primary_radius_B;
   }
   if(primary_radius_C_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Constant coefficient of primary radius function not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_PRIMARY_RADIUS_C, MAX_PRIMARY_RADIUS_C, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      primary_radius_C = pPR->CategoryDataBase[category].primary_radius_C;
   }
   if(primary_tropism_factor_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Primary tropism factor not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_PRIMARY_TROPISM_FACTOR, MAX_PRIMARY_TROPISM_FACTOR, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      primary_tropism_factor = pPR->CategoryDataBase[category].primary_tropism_factor;
   }
   if(primary_tropism_theta_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Primary tropism polar angle (theta) not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_PRIMARY_TROPISM_THETA, MAX_PRIMARY_TROPISM_THETA , pPR->SpeciesDataBase[ispecies].species_name, category_string);
      primary_tropism_theta = pPR->CategoryDataBase[category].primary_tropism_theta;
   }
   if(primary_tropism_phi_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Primary tropism azimuthal angle (phi) not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_PRIMARY_TROPISM_PHI, MAX_PRIMARY_TROPISM_PHI, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      primary_tropism_phi = pPR->CategoryDataBase[category].primary_tropism_phi;
   }
   if(primary_lamdacx_stdev_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: stdev of primary curvature wavelength (lamdacx) function not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_PRIMARY_LAMDACX_STDEV, MAX_PRIMARY_LAMDACX_STDEV, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      primary_lamdacx_stdev = pPR->CategoryDataBase[category].primary_lamdacx_stdev;
   }
   if(primary_lamdacx_mean_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: mean of primary curvature wavelength (lamdacx) function not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_PRIMARY_LAMDACX_MEAN, MAX_PRIMARY_LAMDACX_MEAN, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      primary_lamdacx_mean = pPR->CategoryDataBase[category].primary_lamdacx_mean;
   }
   if(primary_lamdacy_stdev_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: stdev of primary curvature wavelength (lamdacy) function not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_PRIMARY_LAMDACY_STDEV, MAX_PRIMARY_LAMDACY_STDEV, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      primary_lamdacy_stdev = pPR->CategoryDataBase[category].primary_lamdacy_stdev;
   }
   if(primary_lamdacy_mean_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: mean of primary curvature wavelength (lamdacy) function not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_PRIMARY_LAMDACY_MEAN, MAX_PRIMARY_LAMDACY_MEAN, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      primary_lamdacy_mean = pPR->CategoryDataBase[category].primary_lamdacy_mean;
   }
   if(primary_gamma_stdev_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: stdev of primary curvature scale-factor (gamma) function not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_PRIMARY_GAMMA_STDEV, MAX_PRIMARY_GAMMA_STDEV, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      primary_gamma_stdev = pPR->CategoryDataBase[category].primary_gamma_stdev;
   }
   if(primary_gamma_mean_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: mean of primary curvature scale-factor (gamma) function not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_PRIMARY_GAMMA_MEAN, MAX_PRIMARY_GAMMA_MEAN, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      primary_gamma_mean = pPR->CategoryDataBase[category].primary_gamma_mean;
   }
   if(primary_live_moisture_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Live primary moisture not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_PRIMARY_LIVE_MOISTURE, MAX_PRIMARY_LIVE_MOISTURE, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      primary_live_moisture = pPR->CategoryDataBase[category].primary_live_moisture;
   }
   if(primary_dry_moisture_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Dry primary moisture not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_PRIMARY_DRY_MOISTURE, MAX_PRIMARY_DRY_MOISTURE, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      primary_dry_moisture = pPR->CategoryDataBase[category].primary_dry_moisture;
   }
   if(primary_dry_density_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Dry Primary layer density not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_PRIMARY_DRY_LAYER_DENSITY, MAX_PRIMARY_DRY_LAYER_DENSITY, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      primary_dry_density = pPR->CategoryDataBase[category].primary_dry_density;
   }
   if(primary_dry_sections_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Dry Primary sections not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_PRIMARY_DRY_SECTIONS, MAX_PRIMARY_DRY_SECTIONS, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      primary_dry_sections = pPR->CategoryDataBase[category].primary_dry_sections;
   }
   if(secondary_number_slope_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Slope of function to determine number of secondaries not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_SECONDARY_NUMBER_SLOPE, MAX_SECONDARY_NUMBER_SLOPE, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      secondary_number_slope = pPR->CategoryDataBase[category].secondary_number_slope;
   }
   if(secondary_number_intercept_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Intercept of function to determine number of secondaries not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_SECONDARY_NUMBER_INTERCEPT, MAX_SECONDARY_NUMBER_INTERCEPT, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      secondary_number_intercept = pPR->CategoryDataBase[category].secondary_number_intercept;
   }
   if(secondary_offset_fraction_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Secondary branch offset fraction not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_SECONDARY_OFFSET_FRACTION, MAX_SECONDARY_OFFSET_FRACTION, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      secondary_offset_fraction = pPR->CategoryDataBase[category].secondary_offset_fraction;
   }
   if(secondary_avg_polar_angle_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Average secondary polar angle (theta) not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_SECONDARY_AVG_POLAR_ANGLE, MAX_SECONDARY_AVG_POLAR_ANGLE, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      secondary_avg_polar_angle = pPR->CategoryDataBase[category].secondary_avg_polar_angle;
   }
   if(secondary_std_polar_angle_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Std. of secondary polar angle (theta) not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_SECONDARY_STD_POLAR_ANGLE, MAX_SECONDARY_STD_POLAR_ANGLE, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      secondary_std_polar_angle = pPR->CategoryDataBase[category].secondary_std_polar_angle;
   }
   if(secondary_radius_factor_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: Secondary radius factor not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_SECONDARY_RADIUS_FACTOR, MAX_SECONDARY_RADIUS_FACTOR, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      secondary_radius_factor = pPR->CategoryDataBase[category].secondary_radius_factor;
   }
   if(secondary_tropism_factor_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: secondary tropism factor not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_SECONDARY_TROPISM_FACTOR, MAX_SECONDARY_TROPISM_FACTOR, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      secondary_tropism_factor = pPR->CategoryDataBase[category].secondary_tropism_factor;
   }
   if(secondary_tropism_theta_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: secondary tropism polar angle (theta) not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_SECONDARY_TROPISM_THETA, MAX_SECONDARY_TROPISM_THETA , pPR->SpeciesDataBase[ispecies].species_name, category_string);
      secondary_tropism_theta = pPR->CategoryDataBase[category].secondary_tropism_theta;
   }
   if(secondary_tropism_phi_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: secondary tropism azimuthal angle (phi) not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_SECONDARY_TROPISM_PHI, MAX_SECONDARY_TROPISM_PHI, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      secondary_tropism_phi = pPR->CategoryDataBase[category].secondary_tropism_phi;
   }
   if(secondary_lamdacx_stdev_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: stdev of secondary curvature wavelength (lamdacx) function not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_SECONDARY_LAMDACX_STDEV, MAX_SECONDARY_LAMDACX_STDEV, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      secondary_lamdacx_stdev = pPR->CategoryDataBase[category].secondary_lamdacx_stdev;
   }
   if(secondary_lamdacx_mean_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: mean of secondary curvature wavelength (lamdacx) function not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_SECONDARY_LAMDACX_MEAN, MAX_SECONDARY_LAMDACX_MEAN, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      secondary_lamdacx_mean = pPR->CategoryDataBase[category].secondary_lamdacx_mean;
   }
   if(secondary_lamdacy_stdev_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: stdev of secondary curvature wavelength (lamdacy) function not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_SECONDARY_LAMDACY_STDEV, MAX_SECONDARY_LAMDACY_STDEV, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      secondary_lamdacy_stdev = pPR->CategoryDataBase[category].secondary_lamdacy_stdev;
   }
   if(secondary_lamdacy_mean_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: mean of secondary curvature wavelength (lamdacy) function not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_SECONDARY_LAMDACY_MEAN, MAX_SECONDARY_LAMDACY_MEAN, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      secondary_lamdacy_mean = pPR->CategoryDataBase[category].secondary_lamdacy_mean;
   }
   if(secondary_gamma_stdev_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: stdev of secondary curvature scale-factor (gamma) function not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_SECONDARY_GAMMA_STDEV, MAX_SECONDARY_GAMMA_STDEV, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      secondary_gamma_stdev = pPR->CategoryDataBase[category].secondary_gamma_stdev;
   }
   if(secondary_gamma_mean_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: mean of secondary curvature scale-factor (gamma) function not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_SECONDARY_GAMMA_MEAN, MAX_SECONDARY_GAMMA_MEAN, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      secondary_gamma_mean = pPR->CategoryDataBase[category].secondary_gamma_mean;
   }
   if(tertiary_min_radius_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: tertiary minimum radius not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_TERTIARY_MIN_RADIUS, MAX_TERTIARY_MIN_RADIUS, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      tertiary_min_radius = pPR->CategoryDataBase[category].tertiary_min_radius;
   }
   if(tertiary_min_length_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: tertiary minimum length not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_TERTIARY_MIN_LENGTH, MAX_TERTIARY_MIN_LENGTH, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      tertiary_min_length = pPR->CategoryDataBase[category].tertiary_min_length;
   }
   if(tertiary_volume_fraction_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: tertiary volume fraction not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_TERTIARY_VOLUME_FRACTION, MAX_TERTIARY_VOLUME_FRACTION, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      tertiary_volume_fraction = pPR->CategoryDataBase[category].tertiary_volume_fraction;
   }
   if(tertiary_number_factor_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: tertiary number factor not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_TERTIARY_NUMBER_FACTOR, MAX_TERTIARY_NUMBER_FACTOR, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      tertiary_number_factor = pPR->CategoryDataBase[category].tertiary_number_factor;
   }
   if(tertiary_moisture_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: tertiary moisture not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_TERTIARY_MOISTURE, MAX_TERTIARY_MOISTURE, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      tertiary_moisture = pPR->CategoryDataBase[category].tertiary_moisture;
   }
   if(leaf_shape_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: leaf shape not specified or not recognized for species '%s' in Species database file, reading in default value from the %s category\n", pPR->SpeciesDataBase[ispecies].species_name, category_string);
      leaf_shape = pPR->CategoryDataBase[category].leaf_shape;
   }
   if(leaf_width_mean_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: mean leaf width not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_LEAF_WIDTH_MEAN, MAX_LEAF_WIDTH_MEAN, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      leaf_width_mean = pPR->CategoryDataBase[category].leaf_width_mean;
   }
   if(leaf_width_stdev_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: leaf width stdev not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_LEAF_WIDTH_STDEV, MAX_LEAF_WIDTH_STDEV, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      leaf_width_stdev = pPR->CategoryDataBase[category].leaf_width_stdev;
   }
   if(leaf_height_mean_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: mean leaf height not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_LEAF_HEIGHT_MEAN, MAX_LEAF_HEIGHT_MEAN, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      leaf_height_mean = pPR->CategoryDataBase[category].leaf_height_mean;
   }
   if(leaf_height_stdev_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: leaf height stdev not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_LEAF_HEIGHT_STDEV, MAX_LEAF_HEIGHT_STDEV, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      leaf_height_stdev = pPR->CategoryDataBase[category].leaf_height_stdev;
   }
   if(leaf_thickness_mean_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: mean leaf thickness not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_LEAF_THICKNESS_MEAN, MAX_LEAF_THICKNESS_MEAN, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      leaf_thickness_mean = pPR->CategoryDataBase[category].leaf_thickness_mean;
   }
   if(leaf_thickness_stdev_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: leaf thickness stdev not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_LEAF_THICKNESS_STDEV, MAX_LEAF_THICKNESS_STDEV, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      leaf_thickness_stdev = pPR->CategoryDataBase[category].leaf_thickness_stdev;
   }
   if(leaf_volume_fraction_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: leaf volume fraction not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_LEAF_VOLUME_FRACTION, MAX_LEAF_VOLUME_FRACTION, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      leaf_volume_fraction = pPR->CategoryDataBase[category].leaf_volume_fraction;
   }
   if(leaf_number_factor_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: leaf number factor not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_LEAF_NUMBER_FACTOR, MAX_LEAF_NUMBER_FACTOR, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      leaf_number_factor = pPR->CategoryDataBase[category].leaf_number_factor;
   }
   if(leaf_moisture_errflag == XML_READ_ERROR){
      fprintf(pPR->pLogFile,"WARNING: leaf moisture not specified or not between %f and %f for species '%s' in Species database file, reading in default value from the %s category\n", MIN_LEAF_MOISTURE, MAX_LEAF_MOISTURE, pPR->SpeciesDataBase[ispecies].species_name, category_string);
      leaf_moisture = pPR->CategoryDataBase[category].leaf_moisture;
   }


   
   /* Populate the actual Database */
   /* remember that the species_name is written in the species_list tag reading routine */
   pPR->SpeciesDataBase[ispecies].Trees                        = 0; /* initialize the number of trees here, update when reading forest */
   pPR->SpeciesDataBase[ispecies].category                     = category;
   pPR->SpeciesDataBase[ispecies].live_crown_shape             = live_crown_shape;
   pPR->SpeciesDataBase[ispecies].dry_crown_shape              = dry_crown_shape;
   pPR->SpeciesDataBase[ispecies].live_crown_depth_factor      = live_crown_depth_factor;
   pPR->SpeciesDataBase[ispecies].dry_crown_depth_factor       = dry_crown_depth_factor;
   pPR->SpeciesDataBase[ispecies].crown_live_alpha             = crown_live_alpha;
   pPR->SpeciesDataBase[ispecies].crown_dry_alpha              = crown_dry_alpha;
   pPR->SpeciesDataBase[ispecies].crown_radius_factor          = crown_radius_factor;
   pPR->SpeciesDataBase[ispecies].stem_start_radius_factor     = stem_start_radius_factor;
   pPR->SpeciesDataBase[ispecies].stem_max_angle               = stem_max_angle;
   pPR->SpeciesDataBase[ispecies].stem_end_radius_factor       = stem_end_radius_factor;
   pPR->SpeciesDataBase[ispecies].stem_tropism_factor          = stem_tropism_factor;
   pPR->SpeciesDataBase[ispecies].stem_lamdacx_stdev           = stem_lamdacx_stdev;
   pPR->SpeciesDataBase[ispecies].stem_lamdacx_mean            = stem_lamdacx_mean;
   pPR->SpeciesDataBase[ispecies].stem_lamdacy_stdev           = stem_lamdacy_stdev;
   pPR->SpeciesDataBase[ispecies].stem_lamdacy_mean            = stem_lamdacy_mean;
   pPR->SpeciesDataBase[ispecies].stem_gamma_stdev             = stem_gamma_stdev;
   pPR->SpeciesDataBase[ispecies].stem_gamma_mean              = stem_gamma_mean;
   pPR->SpeciesDataBase[ispecies].stem_moisture                = stem_moisture;
   pPR->SpeciesDataBase[ispecies].stem_tropism_theta           = stem_tropism_theta;
   pPR->SpeciesDataBase[ispecies].stem_tropism_phi             = stem_tropism_phi;
   pPR->SpeciesDataBase[ispecies].primary_avg_polar_angle      = primary_avg_polar_angle;
   pPR->SpeciesDataBase[ispecies].primary_std_polar_angle      = primary_std_polar_angle;
   pPR->SpeciesDataBase[ispecies].primary_layer_density        = primary_layer_density;
   pPR->SpeciesDataBase[ispecies].primary_avg_sections         = primary_avg_sections;
   pPR->SpeciesDataBase[ispecies].primary_azimuth_factor       = primary_azimuth_factor;
   pPR->SpeciesDataBase[ispecies].primary_radius_A             = primary_radius_A;
   pPR->SpeciesDataBase[ispecies].primary_radius_B             = primary_radius_B;
   pPR->SpeciesDataBase[ispecies].primary_radius_C             = primary_radius_C;
   pPR->SpeciesDataBase[ispecies].primary_tropism_factor       = primary_tropism_factor;
   pPR->SpeciesDataBase[ispecies].primary_tropism_theta        = primary_tropism_theta;
   pPR->SpeciesDataBase[ispecies].primary_tropism_phi          = primary_tropism_phi;
   pPR->SpeciesDataBase[ispecies].primary_lamdacx_stdev        = primary_lamdacx_stdev;
   pPR->SpeciesDataBase[ispecies].primary_lamdacx_mean         = primary_lamdacx_mean;
   pPR->SpeciesDataBase[ispecies].primary_lamdacy_stdev        = primary_lamdacy_stdev;
   pPR->SpeciesDataBase[ispecies].primary_lamdacy_mean         = primary_lamdacy_mean;
   pPR->SpeciesDataBase[ispecies].primary_gamma_stdev          = primary_gamma_stdev;
   pPR->SpeciesDataBase[ispecies].primary_gamma_mean           = primary_gamma_mean;
   pPR->SpeciesDataBase[ispecies].primary_live_moisture        = primary_live_moisture;
   pPR->SpeciesDataBase[ispecies].primary_dry_moisture         = primary_dry_moisture;
   pPR->SpeciesDataBase[ispecies].primary_dry_density          = primary_dry_density;
   pPR->SpeciesDataBase[ispecies].primary_dry_sections         = primary_dry_sections;
   pPR->SpeciesDataBase[ispecies].secondary_number_slope       = secondary_number_slope;
   pPR->SpeciesDataBase[ispecies].secondary_number_intercept   = secondary_number_intercept;
   pPR->SpeciesDataBase[ispecies].secondary_offset_fraction    = secondary_offset_fraction;
   pPR->SpeciesDataBase[ispecies].secondary_avg_polar_angle    = secondary_avg_polar_angle;
   pPR->SpeciesDataBase[ispecies].secondary_std_polar_angle    = secondary_std_polar_angle;
   pPR->SpeciesDataBase[ispecies].secondary_radius_factor      = secondary_radius_factor;
   pPR->SpeciesDataBase[ispecies].secondary_tropism_factor     = secondary_tropism_factor;
   pPR->SpeciesDataBase[ispecies].secondary_tropism_theta      = secondary_tropism_theta;
   pPR->SpeciesDataBase[ispecies].secondary_tropism_phi        = secondary_tropism_phi;
   pPR->SpeciesDataBase[ispecies].secondary_lamdacx_stdev      = secondary_lamdacx_stdev;
   pPR->SpeciesDataBase[ispecies].secondary_lamdacx_mean       = secondary_lamdacx_mean;
   pPR->SpeciesDataBase[ispecies].secondary_lamdacy_stdev      = secondary_lamdacy_stdev;
   pPR->SpeciesDataBase[ispecies].secondary_lamdacy_mean       = secondary_lamdacy_mean;
   pPR->SpeciesDataBase[ispecies].secondary_gamma_stdev        = secondary_gamma_stdev;
   pPR->SpeciesDataBase[ispecies].secondary_gamma_mean         = secondary_gamma_mean;
   pPR->SpeciesDataBase[ispecies].tertiary_min_radius          = tertiary_min_radius;
   pPR->SpeciesDataBase[ispecies].tertiary_min_length          = tertiary_min_length;
   pPR->SpeciesDataBase[ispecies].tertiary_volume_fraction     = tertiary_volume_fraction;
   pPR->SpeciesDataBase[ispecies].tertiary_number_factor       = tertiary_number_factor;
   pPR->SpeciesDataBase[ispecies].tertiary_moisture            = tertiary_moisture;
   pPR->SpeciesDataBase[ispecies].leaf_shape                   = leaf_shape;
   pPR->SpeciesDataBase[ispecies].leaf_width_mean              = leaf_width_mean;
   pPR->SpeciesDataBase[ispecies].leaf_width_stdev             = leaf_width_stdev;
   pPR->SpeciesDataBase[ispecies].leaf_height_mean             = leaf_height_mean;
   pPR->SpeciesDataBase[ispecies].leaf_height_stdev            = leaf_height_stdev;
   pPR->SpeciesDataBase[ispecies].leaf_thickness_mean          = leaf_thickness_mean;
   pPR->SpeciesDataBase[ispecies].leaf_thickness_stdev         = leaf_thickness_stdev;
   pPR->SpeciesDataBase[ispecies].leaf_volume_fraction         = leaf_volume_fraction;
   pPR->SpeciesDataBase[ispecies].leaf_number_factor           = leaf_number_factor;
   pPR->SpeciesDataBase[ispecies].leaf_moisture                = leaf_moisture;


   return;
}


/***************************************/
/* Reads <species_list tag in the XML  */
/* database file for species names     */
/***************************************/
void getSpeciesList (xmlDocPtr doc, xmlNodePtr cur, PolSARproSim_Record *pPR) {
   
   xmlChar     *key;
   xmlNodePtr  orig;
   int         ispecies = 0;
   int         jspecies = 0;
   int         Nspecies;         /* number of species in species_list tag, may be non-unique */
   char        **name_list;      /* list of species names  */
   int         *unique_index;    /* an array of flags size of Nspecies */
   int         uflag = 0;        /* uniqueness flag   */
   int         unique_count = 0; /* no. of unique species names */
   
   
   orig      = cur;  /* keep a copy of the original pointer */
   cur       = cur->xmlChildrenNode;   /* set current pointer to the children of the current tags */
   Nspecies  = 0;
   
   
   /* Find number of entries  */
   while (cur != NULL) {
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SPECIES_LIST_NAME_XMLTAG))) {
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         xmlFree(key);
         Nspecies++;
      }
      cur = cur->next;
   }
   
   /* Allocate memory for the list of names */
   name_list = (char**)calloc(Nspecies, sizeof(char**));
   if (name_list == NULL) {
      printf("Error allocating filename array\n");
      exit(1);
   }
   
   /* Populate the list of names */
   cur = orig->xmlChildrenNode;
   while (cur != NULL) {
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SPECIES_LIST_NAME_XMLTAG))) {
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         name_list[ispecies] = (char *)calloc(SPECNAME_MAX_STRSIZE,sizeof(char));
         strcpy(name_list[ispecies], trimwhitespace((char*)key));
         xmlFree(key);
         ispecies++;
      }
      cur = cur->next;
   }
   
   /* Its possible that the species_list data has repeated entries   */
   /* so we look for the unique entries only                         */
   unique_index  = (int *)calloc(Nspecies, sizeof(int));
   unique_count  = Nspecies;
   for(ispecies = 0;ispecies<Nspecies;ispecies++){
      for(jspecies=0;jspecies<ispecies;jspecies++){
         if(!strcmp(name_list[ispecies], name_list[jspecies])){
            fprintf(pPR->pLogFile,"WARNING: Species name: %s, repeated in <species_list>, it will not be added\n", name_list[ispecies]);
            unique_count--;
            jspecies=ispecies;
            uflag = 1;
         }
      }
      if(!uflag){
         unique_index[ispecies]=1;
      }else{
         unique_index[ispecies]=0;
         uflag=0;
      }
   }
   
   /**************************************/
   /* Update the Master Record Entries   */
   /**************************************/
   
   /* Update the No. of species in Master Record with the unique species found in <species_list> tag */
   pPR->Nspecies=unique_count;
   /* Allocate memory for the Allometry Database */
   pPR->SpeciesDataBase = (Allometry*) calloc (pPR->Nspecies, sizeof(Allometry));
   
   /* Put the species names in the Allometry Database */
   unique_count = 0;
   for(ispecies=0;ispecies<Nspecies;ispecies++){
      if(unique_index[ispecies]){
         pPR->SpeciesDataBase[unique_count].species_name = (char *)calloc(SPECNAME_MAX_STRSIZE,sizeof(char));
         strcpy(pPR->SpeciesDataBase[unique_count].species_name, name_list[ispecies]);
         unique_count++;
      }
   }
   
   return;
}

/***************************************/
/* Reads <category_list tag in the XML */
/* database file for category names    */
/***************************************/
void getCategoryList (xmlDocPtr doc, xmlNodePtr cur, PolSARproSim_Record *pPR) {
   
   xmlChar     *key;
   xmlNodePtr  orig;
   int         icategories = 0;
   int         jcategories = 0;
   int         Ncategories;      /* number of categories in category_list tag, may be non-unique */
   char        **name_list;      /* list of categories names  */
   int         *unique_index;    /* an array of flags size of Ncategories */
   int         uflag = 0;        /* uniqueness flag   */
   int         unique_count = 0; /* no. of unique categories names */
   
   
   orig      = cur;  /* keep a copy of the original pointer */
   cur       = cur->xmlChildrenNode;   /* set current pointer to the children of the current tags */
   Ncategories  = 0;
   
   
   /* Find number of entries  */
   while (cur != NULL) {
      if ((!xmlStrcmp(cur->name, (const xmlChar *)CATEGORY_LIST_NAME_XMLTAG))) {
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         xmlFree(key);
         Ncategories++;
      }
      cur = cur->next;
   }
   
   /* Allocate memory for the list of names */
   name_list = (char**)calloc(Ncategories, sizeof(char**));
   if (name_list == NULL) {
      printf("Error allocating array of Category names\n");
      exit(1);
   }
   
   /* Populate the list of names */
   cur = orig->xmlChildrenNode;
   while (cur != NULL) {
      if ((!xmlStrcmp(cur->name, (const xmlChar *)CATEGORY_LIST_NAME_XMLTAG))) {
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         name_list[icategories] = (char *)calloc(SPECNAME_MAX_STRSIZE,sizeof(char));
         strcpy(name_list[icategories], trimwhitespace((char*)key));
         xmlFree(key);
         icategories++;
      }
      cur = cur->next;
   }
   
   /* Its possible that the categories_list data has repeated entries   */
   /* so we look for the unique entries only                         */
   unique_index  = (int *)calloc(Ncategories, sizeof(int));
   unique_count  = Ncategories;
   for(icategories = 0;icategories<Ncategories;icategories++){
      for(jcategories=0;jcategories<icategories;jcategories++){
         if(!strcmp(name_list[icategories], name_list[jcategories])){
            fprintf(pPR->pLogFile,"WARNING: Category name: %s, repeated in <category_list>, it will not be added\n", name_list[icategories]);
            unique_count--;
            jcategories=icategories;
            uflag = 1;
         }
      }
      if(!uflag){
         unique_index[icategories]=1;
      }else{
         unique_index[icategories]=0;
         uflag=0;
      }
   }
   
   /**************************************/
   /* Update the Master Record Entries   */
   /**************************************/
   
   /* Update the No. of categories in Master Record with the unique categories found in <category_list> tag */
   pPR->Ncategories=unique_count;
   /* Allocate memory for the Allometry Database */
   pPR->CategoryDataBase = (Allometry*) calloc (pPR->Ncategories, sizeof(Allometry));
   
   /* Put the categories names in the Allometry Database */
   unique_count = 0;
   for(icategories=0;icategories<Ncategories;icategories++){
      if(unique_index[icategories]){
         pPR->CategoryDataBase[unique_count].species_name = (char *)calloc(SPECNAME_MAX_STRSIZE,sizeof(char));
         strcpy(pPR->CategoryDataBase[unique_count].species_name, name_list[icategories]);
         unique_count++;
      }
   }
   
   return;
}

/*********************************/
/* Reads in species primitives   */
/* from XML database file        */
/*********************************/
void getCategoryData (xmlDocPtr doc, xmlNodePtr cur, PolSARproSim_Record *pPR, int icategories) {
   
   xmlChar  *key;
   
   /* the fields of the Allometry XML file */
   int      live_crown_shape           = CROWN_NULL_SHAPE;
   int      dry_crown_shape            = CROWN_NULL_SHAPE;
   double   live_crown_depth_factor    = 1;
   double   dry_crown_depth_factor     = 1;
   double   crown_live_alpha           = 0.4693;
   double   crown_dry_alpha            = 0.4147;
   double   crown_radius_factor        = 0.4221;
   double   stem_start_radius_factor   = 0.5721;
   double   stem_max_angle             = 0;
   double   stem_end_radius_factor     = 0.5;
   double   stem_tropism_factor        = 0.0;
   double   stem_lamdacx_stdev         = 0.5;
   double   stem_lamdacx_mean          = 0.5;
   double   stem_lamdacy_stdev         = 0.5;
   double   stem_lamdacy_mean          = 0.5;
   double   stem_gamma_stdev           = 0.0075;
   double   stem_gamma_mean            = 0.0025;
   double   stem_moisture              = 0.370;
   double   stem_tropism_theta         = 0.0;
   double   stem_tropism_phi           = 0.0;
   double   primary_avg_polar_angle    = 90.0;
   double   primary_std_polar_angle    = 10.0;
   double   primary_layer_density      = 4.015;
   int      primary_avg_sections       = 6;
   double   primary_azimuth_factor     = 0.5;
   double   primary_radius_A           = -0.51532;
   double   primary_radius_B           = 0.53288;
   double   primary_radius_C           = 0.038638;
   double   primary_tropism_factor     = 0.3;
   double   primary_tropism_theta      = 0.0;
   double   primary_tropism_phi        = 0.0;
   double   primary_lamdacx_stdev      = 0.25;
   double   primary_lamdacx_mean       = 0.75;
   double   primary_lamdacy_stdev      = 0.25;
   double   primary_lamdacy_mean       = 0.75;
   double   primary_gamma_stdev        = 0.0075;
   double   primary_gamma_mean         = 0.0025;
   double   primary_live_moisture      = 0.424;
   double   primary_dry_moisture       = 0.100;
   double   primary_dry_density        = 4.015;
   int      primary_dry_sections       = 4;
   double   secondary_number_slope     = 18.95864;
   double   secondary_number_intercept = -4.26094;
   double   secondary_offset_fraction  = 0.08;
   double   secondary_avg_polar_angle  = 90.0;
   double   secondary_std_polar_angle  = 10.0;
   double   secondary_radius_factor    = 0.5;
   double   secondary_tropism_factor   = 0.6;
   double   secondary_tropism_theta    = 0.0;
   double   secondary_tropism_phi      = 0.0;
   double   secondary_lamdacx_stdev    = 0.25;
   double   secondary_lamdacx_mean     = 0.75;
   double   secondary_lamdacy_stdev    = 0.25;
   double   secondary_lamdacy_mean     = 0.75;
   double   secondary_gamma_stdev      = 0.075;
   double   secondary_gamma_mean       = 0.025;
   double   tertiary_min_radius        = 0.011;
   double   tertiary_min_length        = 1.5;
   double   tertiary_volume_fraction   = 0.00025;
   double   tertiary_number_factor     = 120.0;
   double   tertiary_moisture          = 0.4735;
   int      leaf_shape                 = POLSARPROSIM_PINE_NEEDLE;
   double   leaf_width_mean            = 0.020;
   double   leaf_width_stdev           = 0.002;
   double   leaf_height_mean           = 0.001;
   double   leaf_height_stdev          = 0.0001;
   double   leaf_thickness_mean        = 0.001;
   double   leaf_thickness_stdev       = 0.0001;
   double   leaf_moisture              = 0.550;
   double   leaf_number_factor         = 30.0;
   double   leaf_volume_fraction       = 0.00025;

   /* Error flags, set by default */
   int      live_crown_shape_errflag            = XML_READ_ERROR;
   int      dry_crown_shape_errflag             = XML_READ_ERROR;
   int      lcrown_depthfactor_errflag          = XML_READ_ERROR;
   int      dcrown_depthfactor_errflag          = XML_READ_ERROR;
   int      crown_live_alpha_errflag            = XML_READ_ERROR;
   int      crown_dry_alpha_errflag             = XML_READ_ERROR;
   int      crown_radius_factor_errflag         = XML_READ_ERROR;
   int      stem_start_radius_factor_errflag    = XML_READ_ERROR;
   int      stem_max_angle_errflag              = XML_READ_ERROR;
   int      stem_end_radius_factor_errflag      = XML_READ_ERROR;
   int      stem_tropism_factor_errflag         = XML_READ_ERROR;
   int      stem_lamdacx_stdev_errflag          = XML_READ_ERROR;
   int      stem_lamdacx_mean_errflag           = XML_READ_ERROR;
   int      stem_lamdacy_stdev_errflag          = XML_READ_ERROR;
   int      stem_lamdacy_mean_errflag           = XML_READ_ERROR;
   int      stem_gamma_stdev_errflag            = XML_READ_ERROR;
   int      stem_gamma_mean_errflag             = XML_READ_ERROR;
   int      stem_moisture_errflag               = XML_READ_ERROR;
   int      stem_tropism_theta_errflag          = XML_READ_ERROR;
   int      stem_tropism_phi_errflag            = XML_READ_ERROR;
   int      primary_avg_polar_angle_errflag     = XML_READ_ERROR;
   int      primary_std_polar_angle_errflag     = XML_READ_ERROR;
   int      primary_layer_density_errflag       = XML_READ_ERROR;
   int      primary_avg_sections_errflag        = XML_READ_ERROR;
   int      primary_azimuth_factor_errflag      = XML_READ_ERROR;
   int      primary_radius_A_errflag            = XML_READ_ERROR;
   int      primary_radius_B_errflag            = XML_READ_ERROR;
   int      primary_radius_C_errflag            = XML_READ_ERROR;
   int      primary_tropism_factor_errflag      = XML_READ_ERROR;
   int      primary_tropism_theta_errflag       = XML_READ_ERROR;
   int      primary_tropism_phi_errflag         = XML_READ_ERROR;
   int      primary_lamdacx_stdev_errflag       = XML_READ_ERROR;
   int      primary_lamdacx_mean_errflag        = XML_READ_ERROR;
   int      primary_lamdacy_stdev_errflag       = XML_READ_ERROR;
   int      primary_lamdacy_mean_errflag        = XML_READ_ERROR;
   int      primary_gamma_stdev_errflag         = XML_READ_ERROR;
   int      primary_gamma_mean_errflag          = XML_READ_ERROR;
   int      primary_live_moisture_errflag       = XML_READ_ERROR;
   int      primary_dry_moisture_errflag        = XML_READ_ERROR;
   int      primary_dry_density_errflag         = XML_READ_ERROR;
   int      primary_dry_sections_errflag        = XML_READ_ERROR;
   int      secondary_number_slope_errflag      = XML_READ_ERROR;
   int      secondary_number_intercept_errflag  = XML_READ_ERROR;
   int      secondary_offset_fraction_errflag   = XML_READ_ERROR;
   int      secondary_avg_polar_angle_errflag   = XML_READ_ERROR;
   int      secondary_std_polar_angle_errflag   = XML_READ_ERROR;
   int      secondary_radius_factor_errflag     = XML_READ_ERROR;
   int      secondary_tropism_factor_errflag    = XML_READ_ERROR;
   int      secondary_tropism_theta_errflag     = XML_READ_ERROR;
   int      secondary_tropism_phi_errflag       = XML_READ_ERROR;
   int      secondary_lamdacx_stdev_errflag     = XML_READ_ERROR;
   int      secondary_lamdacx_mean_errflag      = XML_READ_ERROR;
   int      secondary_lamdacy_stdev_errflag     = XML_READ_ERROR;
   int      secondary_lamdacy_mean_errflag      = XML_READ_ERROR;
   int      secondary_gamma_stdev_errflag       = XML_READ_ERROR;
   int      secondary_gamma_mean_errflag        = XML_READ_ERROR;
   int      tertiary_min_radius_errflag         = XML_READ_ERROR;
   int      tertiary_min_length_errflag         = XML_READ_ERROR;
   int      tertiary_volume_fraction_errflag    = XML_READ_ERROR;
   int      tertiary_number_factor_errflag      = XML_READ_ERROR;
   int      tertiary_moisture_errflag           = XML_READ_ERROR;
   int      leaf_shape_errflag                  = XML_READ_ERROR;
   int      leaf_width_mean_errflag             = XML_READ_ERROR;
   int      leaf_width_stdev_errflag            = XML_READ_ERROR;
   int      leaf_height_mean_errflag            = XML_READ_ERROR;
   int      leaf_height_stdev_errflag           = XML_READ_ERROR;
   int      leaf_thickness_mean_errflag         = XML_READ_ERROR;
   int      leaf_thickness_stdev_errflag        = XML_READ_ERROR;
   int      leaf_moisture_errflag               = XML_READ_ERROR;
   int      leaf_number_factor_errflag          = XML_READ_ERROR;
   int      leaf_volume_fraction_errflag        = XML_READ_ERROR;

   cur = cur->xmlChildrenNode;
   while (cur != NULL) {
      /* look for live crown shape */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)LIVE_CROWN_SHAPE_XMLTAG))) {
         live_crown_shape_errflag = XML_READ_SUCCESS; /* found it! disable error flag */
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         if (!strcmp(trimwhitespace((char*)key),         CROWN_CYLINDER_XMLID)){
            live_crown_shape =                           CROWN_CYLINDER;
         }else if (!strcmp(trimwhitespace((char*)key),   CROWN_CONE_XMLID)){
            live_crown_shape =                           CROWN_CONE;
         }else if (!strcmp(trimwhitespace((char*)key),   CROWN_SPHERE_XMLID)){
            live_crown_shape =                           CROWN_SPHEROID;
         }else{
            live_crown_shape_errflag = XML_READ_ERROR; /* did not recognize, set error flag */
         }
         xmlFree(key);
      }
      /* look for dry crown shape */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)DRY_CROWN_SHAPE_XMLTAG))) {
         dry_crown_shape_errflag = XML_READ_SUCCESS; /* found it! disable error flag */
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         if(!strcmp(trimwhitespace((char*)key),          CROWN_CYLINDER_XMLID)){
            dry_crown_shape =                            CROWN_CYLINDER;
         }else if(!strcmp(trimwhitespace((char*)key),    CROWN_CONE_XMLID)){
            dry_crown_shape =                            CROWN_CONE;
         }else if(!strcmp(trimwhitespace((char*)key),    CROWN_SPHERE_XMLID)){
            dry_crown_shape =                            CROWN_SPHEROID;
         }else if (!strcmp(trimwhitespace((char*)key),   CROWN_NONE_XMLID)){
            dry_crown_shape =                            CROWN_NULL_SHAPE;
         }else{
            dry_crown_shape_errflag = XML_READ_ERROR; /* did not recognize, set error flag */
         }
         xmlFree(key);
      }
      /* look for live crown depth factor */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)LIVE_CROWN_DEPTH_FACTOR_XMLTAG))) {
         lcrown_depthfactor_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         live_crown_depth_factor = (double) atof((const char*)key);
         if(live_crown_depth_factor > MAX_LIVE_CROWN_DEPTH_FACTOR || live_crown_depth_factor < MIN_LIVE_CROWN_DEPTH_FACTOR){
            lcrown_depthfactor_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for dry crown depth factor */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)DRY_CROWN_DEPTH_FACTOR_XMLTAG))) {
         dcrown_depthfactor_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         dry_crown_depth_factor = (double) atof((const char*)key);
         if(dry_crown_depth_factor > MAX_DRY_CROWN_DEPTH_FACTOR || dry_crown_depth_factor < MIN_DRY_CROWN_DEPTH_FACTOR){
            dcrown_depthfactor_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for live crown alpha, to estimate crown depth itself, unused if crown depth specified in forest description */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)CROWN_LIVE_ALPHA_XMLTAG))) {
         crown_live_alpha_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         crown_live_alpha = (double) atof((const char*)key);
         if(crown_live_alpha > MAX_CROWN_LIVE_ALPHA || crown_live_alpha < MIN_CROWN_LIVE_ALPHA){
            crown_live_alpha_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for dry crown alpha, to estimate crown depth itself, unused if crown depth specified in forest description */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)CROWN_DRY_ALPHA_XMLTAG))) {
         crown_dry_alpha_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         crown_dry_alpha = (double) atof((const char*)key);
         if(crown_dry_alpha > MAX_CROWN_DRY_ALPHA || crown_dry_alpha < MIN_CROWN_DRY_ALPHA){
            crown_dry_alpha_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for crown radius factor */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)CROWN_RADIUS_FACTOR_XMLTAG))) {
         crown_radius_factor_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         crown_radius_factor = (double) atof((const char*)key);
         if(crown_radius_factor > MAX_CROWN_RADIUS_FACTOR || crown_radius_factor < MIN_CROWN_RADIUS_FACTOR){
            crown_radius_factor_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for stem start radius factor */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)STEM_START_RADIUS_FACTOR_XMLTAG))) {
         stem_start_radius_factor_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         stem_start_radius_factor = (double) atof((const char*)key);
         if(stem_start_radius_factor > MAX_STEM_START_RADIUS_FACTOR || stem_start_radius_factor < MIN_STEM_START_RADIUS_FACTOR){
            stem_start_radius_factor_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }

      /* look for minimum stem angle */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)STEM_MAX_POLAR_ANGLE_XMLTAG))) {
         stem_max_angle_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         stem_max_angle = (double) atof((const char*)key);
         if(stem_max_angle > MAX_STEM_ANGLE || stem_max_angle < MIN_STEM_ANGLE){
            stem_max_angle_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for stem end radius factor */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)STEM_END_RADIUS_FACTOR_XMLTAG))) {
         stem_end_radius_factor_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         stem_end_radius_factor = (double) atof((const char*)key);
         if(stem_end_radius_factor > MAX_STEM_END_RADIUS_FACTOR || stem_end_radius_factor < MIN_STEM_END_RADIUS_FACTOR){
            stem_end_radius_factor_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for stem tropism factor */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)STEM_TROPISM_FACTOR_XMLTAG))) {
         stem_tropism_factor_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         stem_tropism_factor = (double) atof((const char*)key);
         if(stem_tropism_factor > MAX_STEM_TROPISM_FACTOR || stem_tropism_factor < MIN_STEM_TROPISM_FACTOR){
            stem_tropism_factor_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for stem lamdacx stdev  */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)STEM_LAMDACX_STDEV_XMLTAG))) {
         stem_lamdacx_stdev_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         stem_lamdacx_stdev = (double) atof((const char*)key);
         if(stem_lamdacx_stdev > MAX_STEM_LAMDACX_STDEV || stem_lamdacx_stdev < MIN_STEM_LAMDACX_STDEV){
            stem_lamdacx_stdev_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for stem lamdacx mean */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)STEM_LAMDACX_MEAN_XMLTAG))) {
         stem_lamdacx_mean_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         stem_lamdacx_mean = (double) atof((const char*)key);
         if(stem_lamdacx_mean > MAX_STEM_LAMDACX_MEAN || stem_lamdacx_mean < MIN_STEM_LAMDACX_MEAN){
            stem_lamdacx_mean_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for stem lamdacy stdev  */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)STEM_LAMDACY_STDEV_XMLTAG))) {
         stem_lamdacy_stdev_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         stem_lamdacy_stdev = (double) atof((const char*)key);
         if(stem_lamdacy_stdev > MAX_STEM_LAMDACY_STDEV || stem_lamdacy_stdev < MIN_STEM_LAMDACY_STDEV){
            stem_lamdacy_stdev_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for stem lamdacy mean */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)STEM_LAMDACY_MEAN_XMLTAG))) {
         stem_lamdacy_mean_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         stem_lamdacy_mean = (double) atof((const char*)key);
         if(stem_lamdacy_mean > MAX_STEM_LAMDACY_MEAN || stem_lamdacy_mean < MIN_STEM_LAMDACY_MEAN){
            stem_lamdacy_mean_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for stem gamma stdev  */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)STEM_GAMMA_STDEV_XMLTAG))) {
         stem_gamma_stdev_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         stem_gamma_stdev = (double) atof((const char*)key);
         if(stem_gamma_stdev > MAX_STEM_GAMMA_STDEV || stem_gamma_stdev < MIN_STEM_GAMMA_STDEV){
            stem_gamma_stdev_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for stem gamma mean */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)STEM_GAMMA_MEAN_XMLTAG))) {
         stem_gamma_mean_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         stem_gamma_mean = (double) atof((const char*)key);
         if(stem_gamma_mean > MAX_STEM_GAMMA_MEAN || stem_gamma_mean < MIN_STEM_GAMMA_MEAN){
            stem_gamma_mean_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for stem moisture */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)STEM_MOISTURE_XMLTAG))) {
         stem_moisture_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         stem_moisture = (double) atof((const char*)key);
         if(stem_moisture > MAX_STEM_MOISTURE || stem_moisture < MIN_STEM_MOISTURE){
            stem_moisture_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for stem tropism angle theta */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)STEM_TROPISM_DIR_THETA_XMLTAG))) {
         stem_tropism_theta_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         stem_tropism_theta = (double) atof((const char*)key);
         if(stem_tropism_theta > MAX_STEM_TROPISM_THETA || stem_tropism_theta < MIN_STEM_TROPISM_THETA){
            stem_tropism_theta_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for stem tropism angle phi */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)STEM_TROPISM_DIR_PHI_XMLTAG))) {
         stem_tropism_phi_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         stem_tropism_phi = (double) atof((const char*)key);
         if(stem_tropism_phi > MAX_STEM_TROPISM_PHI || stem_tropism_phi < MIN_STEM_TROPISM_PHI){
            stem_tropism_phi_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for average primary polar angle, theta */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_AVG_POLAR_ANGLE_XMLTAG))) {
         primary_avg_polar_angle_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_avg_polar_angle = (double) atof((const char*)key);
         if(primary_avg_polar_angle > MAX_PRIMARY_AVG_POLAR_ANGLE || primary_avg_polar_angle < MIN_PRIMARY_AVG_POLAR_ANGLE){
            primary_avg_polar_angle_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for the standard deviation of the primary polar angle (theta) */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_STD_POLAR_ANGLE_XMLTAG))) {
         primary_std_polar_angle_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_std_polar_angle = (double) atof((const char*)key);
         if(primary_std_polar_angle > MAX_PRIMARY_STD_POLAR_ANGLE || primary_std_polar_angle < MIN_PRIMARY_STD_POLAR_ANGLE){
            primary_std_polar_angle_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for the primary layer density */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_LAYER_DENSITY_XMLTAG))) {
         primary_layer_density_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_layer_density = (double) atof((const char*)key);
         if(primary_layer_density > MAX_PRIMARY_LAYER_DENSITY || primary_layer_density < MIN_PRIMARY_LAYER_DENSITY){
            primary_layer_density_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for the number of average primary sections */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_AVG_SECTIONS_XMLTAG))) {
         primary_avg_sections_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_avg_sections = (double) atoi((const char*)key);
         if(primary_avg_sections > MAX_PRIMARY_AVERAGE_SECTIONS || primary_avg_sections < MIN_PRIMARY_AVERAGE_SECTIONS){
            primary_avg_sections_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for the primary azimuth factor */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_AZIMUTH_FACTOR_XMLTAG))) {
         primary_azimuth_factor_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_azimuth_factor = (double) atof((const char*)key);
         if(primary_azimuth_factor > MAX_PRIMARY_AZIMUTH_FACTOR || primary_azimuth_factor < MIN_PRIMARY_AZIMUTH_FACTOR){
            primary_azimuth_factor_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for the quadratic coefficient of the primary radius function */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_RADIUS_A_XMLTAG))) {
         primary_radius_A_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_radius_A = (double) atof((const char*)key);
         if(primary_radius_A > MAX_PRIMARY_RADIUS_A || primary_radius_A < MIN_PRIMARY_RADIUS_A){
            primary_radius_A_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for the linear coefficient of the primary radius function */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_RADIUS_B_XMLTAG))) {
         primary_radius_B_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_radius_B = (double) atof((const char*)key);
         if(primary_radius_B > MAX_PRIMARY_RADIUS_B || primary_radius_B < MIN_PRIMARY_RADIUS_B){
            primary_radius_B_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for the constant coefficient of the primary radius function */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_RADIUS_C_XMLTAG))) {
         primary_radius_C_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_radius_C = (double) atof((const char*)key);
         if(primary_radius_C > MAX_PRIMARY_RADIUS_C || primary_radius_C < MIN_PRIMARY_RADIUS_C){
            primary_radius_C_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for primary tropism factor */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_TROPISM_FACTOR_XMLTAG))) {
         primary_tropism_factor_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_tropism_factor = (double) atof((const char*)key);
         if(primary_tropism_factor > MAX_PRIMARY_TROPISM_FACTOR || primary_tropism_factor < MIN_PRIMARY_TROPISM_FACTOR){
            primary_tropism_factor_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for primary tropism angle theta */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_TROPISM_DIR_THETA_XMLTAG))) {
         primary_tropism_theta_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_tropism_theta = (double) atof((const char*)key);
         if(primary_tropism_theta > MAX_PRIMARY_TROPISM_THETA || primary_tropism_theta < MIN_PRIMARY_TROPISM_THETA){
            primary_tropism_theta_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for primary tropism angle phi */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_TROPISM_DIR_PHI_XMLTAG))) {
         primary_tropism_phi_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_tropism_phi = (double) atof((const char*)key);
         if(primary_tropism_phi > MAX_PRIMARY_TROPISM_PHI || primary_tropism_phi < MIN_PRIMARY_TROPISM_PHI){
            primary_tropism_phi_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for primary lamdacx stdev  */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_LAMDACX_STDEV_XMLTAG))) {
         primary_lamdacx_stdev_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_lamdacx_stdev = (double) atof((const char*)key);
         if(primary_lamdacx_stdev > MAX_PRIMARY_LAMDACX_STDEV || primary_lamdacx_stdev < MIN_PRIMARY_LAMDACX_STDEV){
            primary_lamdacx_stdev_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for primary lamdacx mean */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_LAMDACX_MEAN_XMLTAG))) {
         primary_lamdacx_mean_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_lamdacx_mean = (double) atof((const char*)key);
         if(primary_lamdacx_mean > MAX_PRIMARY_LAMDACX_MEAN || primary_lamdacx_mean < MIN_PRIMARY_LAMDACX_MEAN){
            primary_lamdacx_mean_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for primary lamdacy stdev  */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_LAMDACY_STDEV_XMLTAG))) {
         primary_lamdacy_stdev_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_lamdacy_stdev = (double) atof((const char*)key);
         if(primary_lamdacy_stdev > MAX_PRIMARY_LAMDACY_STDEV || primary_lamdacy_stdev < MIN_PRIMARY_LAMDACY_STDEV){
            primary_lamdacy_stdev_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for primary lamdacy mean */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_LAMDACY_MEAN_XMLTAG))) {
         primary_lamdacy_mean_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_lamdacy_mean = (double) atof((const char*)key);
         if(primary_lamdacy_mean > MAX_PRIMARY_LAMDACY_MEAN || primary_lamdacy_mean < MIN_PRIMARY_LAMDACY_MEAN){
            primary_lamdacy_mean_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
     /* look for primary gamma stdev  */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_GAMMA_STDEV_XMLTAG))) {
         primary_gamma_stdev_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_gamma_stdev = (double) atof((const char*)key);
         if(primary_gamma_stdev > MAX_PRIMARY_GAMMA_STDEV || primary_gamma_stdev < MIN_PRIMARY_GAMMA_STDEV){
            primary_gamma_stdev_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for primary gamma mean */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_GAMMA_MEAN_XMLTAG))) {
         primary_gamma_mean_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_gamma_mean = (double) atof((const char*)key);
         if(primary_gamma_mean > MAX_PRIMARY_GAMMA_MEAN || primary_gamma_mean < MIN_PRIMARY_GAMMA_MEAN){
            primary_gamma_mean_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for primary moisture */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_LIVE_MOISTURE_XMLTAG))) {
         primary_live_moisture_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_live_moisture = (double) atof((const char*)key);
         if(primary_live_moisture > MAX_PRIMARY_LIVE_MOISTURE || primary_live_moisture < MIN_PRIMARY_LIVE_MOISTURE){
            primary_live_moisture_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for fractional moisture content of dry primary branches */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_DRY_MOISTURE_XMLTAG))) {
         primary_dry_moisture_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_dry_moisture = (double) atof((const char*)key);
         if(primary_dry_moisture > MAX_PRIMARY_DRY_MOISTURE || primary_dry_moisture < MIN_PRIMARY_DRY_MOISTURE){
            primary_dry_moisture_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for the dry primary layer density */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_DRY_LAYER_DENSITY_XMLTAG))) {
         primary_dry_density_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_dry_density = (double) atof((const char*)key);
         if(primary_dry_density > MAX_PRIMARY_DRY_LAYER_DENSITY || primary_dry_density < MIN_PRIMARY_DRY_LAYER_DENSITY){
            primary_dry_density_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for the number of dry primary sections */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)PRIMARY_DRY_SECTIONS_XMLTAG))) {
         primary_dry_sections_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         primary_dry_sections = (double) atoi((const char*)key);
         if(primary_dry_sections > MAX_PRIMARY_DRY_SECTIONS || primary_dry_sections < MIN_PRIMARY_DRY_SECTIONS){
            primary_dry_sections_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for the slope of the linear function to determine number of secondary branches */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_NUMBER_SLOPE_XMLTAG))) {
         secondary_number_slope_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_number_slope = (double) atof((const char*)key);
         if(secondary_number_slope > MAX_SECONDARY_NUMBER_SLOPE || secondary_number_slope < MIN_SECONDARY_NUMBER_SLOPE){
            secondary_number_slope_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for the intercept of the linear function to determine number of secondary branches */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_NUMBER_INTERCEPT_XMLTAG))) {
         secondary_number_intercept_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_number_intercept = (double) atof((const char*)key);
         if(secondary_number_intercept > MAX_SECONDARY_NUMBER_INTERCEPT || secondary_number_intercept < MIN_SECONDARY_NUMBER_INTERCEPT){
            secondary_number_intercept_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for the fractional offset of the secondary start location (tmin) */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_OFFSET_FRACTION_XMLTAG))) {
         secondary_offset_fraction_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_offset_fraction = (double) atof((const char*)key);
         if(secondary_offset_fraction > MAX_SECONDARY_OFFSET_FRACTION || secondary_offset_fraction < MIN_SECONDARY_OFFSET_FRACTION){
            secondary_offset_fraction_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for average secondary polar angle, theta */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_AVG_POLAR_ANGLE_XMLTAG))) {
         secondary_avg_polar_angle_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_avg_polar_angle = (double) atof((const char*)key);
         if(secondary_avg_polar_angle > MAX_SECONDARY_AVG_POLAR_ANGLE || secondary_avg_polar_angle < MIN_SECONDARY_AVG_POLAR_ANGLE){
            secondary_avg_polar_angle_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for the standard deviation of the secondary polar angle (theta) */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_STD_POLAR_ANGLE_XMLTAG))) {
         secondary_std_polar_angle_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_std_polar_angle = (double) atof((const char*)key);
         if(secondary_std_polar_angle > MAX_SECONDARY_STD_POLAR_ANGLE || secondary_std_polar_angle < MIN_SECONDARY_STD_POLAR_ANGLE){
            secondary_std_polar_angle_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for the secondary radius factor */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_RADIUS_FACTOR_XMLTAG))) {
         secondary_radius_factor_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_radius_factor = (double) atof((const char*)key);
         if(secondary_radius_factor > MAX_SECONDARY_RADIUS_FACTOR || secondary_radius_factor < MIN_SECONDARY_RADIUS_FACTOR){
            secondary_radius_factor_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
     /* look for secondary tropism factor */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_TROPISM_FACTOR_XMLTAG))) {
         secondary_tropism_factor_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_tropism_factor = (double) atof((const char*)key);
         if(secondary_tropism_factor > MAX_SECONDARY_TROPISM_FACTOR || secondary_tropism_factor < MIN_SECONDARY_TROPISM_FACTOR){
            secondary_tropism_factor_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for secondary tropism angle theta */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_TROPISM_DIR_THETA_XMLTAG))) {
         secondary_tropism_theta_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_tropism_theta = (double) atof((const char*)key);
         if(secondary_tropism_theta > MAX_SECONDARY_TROPISM_THETA || secondary_tropism_theta < MIN_SECONDARY_TROPISM_THETA){
            secondary_tropism_theta_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for secondary tropism angle phi */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_TROPISM_DIR_PHI_XMLTAG))) {
         secondary_tropism_phi_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_tropism_phi = (double) atof((const char*)key);
         if(secondary_tropism_phi > MAX_SECONDARY_TROPISM_PHI || secondary_tropism_phi < MIN_SECONDARY_TROPISM_PHI){
            secondary_tropism_phi_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for secondary lamdacx stdev  */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_LAMDACX_STDEV_XMLTAG))) {
         secondary_lamdacx_stdev_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_lamdacx_stdev = (double) atof((const char*)key);
         if(secondary_lamdacx_stdev > MAX_SECONDARY_LAMDACX_STDEV || secondary_lamdacx_stdev < MIN_SECONDARY_LAMDACX_STDEV){
            secondary_lamdacx_stdev_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for secondary lamdacx mean */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_LAMDACX_MEAN_XMLTAG))) {
         secondary_lamdacx_mean_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_lamdacx_mean = (double) atof((const char*)key);
         if(secondary_lamdacx_mean > MAX_SECONDARY_LAMDACX_MEAN || secondary_lamdacx_mean < MIN_SECONDARY_LAMDACX_MEAN){
            secondary_lamdacx_mean_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for secondary lamdacy stdev  */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_LAMDACY_STDEV_XMLTAG))) {
         secondary_lamdacy_stdev_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_lamdacy_stdev = (double) atof((const char*)key);
         if(secondary_lamdacy_stdev > MAX_SECONDARY_LAMDACY_STDEV || secondary_lamdacy_stdev < MIN_SECONDARY_LAMDACY_STDEV){
            secondary_lamdacy_stdev_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for secondary lamdacy mean */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_LAMDACY_MEAN_XMLTAG))) {
         secondary_lamdacy_mean_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_lamdacy_mean = (double) atof((const char*)key);
         if(secondary_lamdacy_mean > MAX_SECONDARY_LAMDACY_MEAN || secondary_lamdacy_mean < MIN_SECONDARY_LAMDACY_MEAN){
            secondary_lamdacy_mean_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
     /* look for secondary gamma stdev  */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_GAMMA_STDEV_XMLTAG))) {
         secondary_gamma_stdev_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_gamma_stdev = (double) atof((const char*)key);
         if(secondary_gamma_stdev > MAX_SECONDARY_GAMMA_STDEV || secondary_gamma_stdev < MIN_SECONDARY_GAMMA_STDEV){
            secondary_gamma_stdev_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for secondary gamma mean */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SECONDARY_GAMMA_MEAN_XMLTAG))) {
         secondary_gamma_mean_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         secondary_gamma_mean = (double) atof((const char*)key);
         if(secondary_gamma_mean > MAX_SECONDARY_GAMMA_MEAN || secondary_gamma_mean < MIN_SECONDARY_GAMMA_MEAN){
            secondary_gamma_mean_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for minimum tertiary radius */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)TERTIARY_MIN_RADIUS_XMLTAG))) {
         tertiary_min_radius_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         tertiary_min_radius = (double) atof((const char*)key);
         if(tertiary_min_radius > MAX_TERTIARY_MIN_RADIUS || tertiary_min_radius < MIN_TERTIARY_MIN_RADIUS){
            tertiary_min_radius_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for minimum tertiary length */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)TERTIARY_MIN_LENGTH_XMLTAG))) {
         tertiary_min_length_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         tertiary_min_length = (double) atof((const char*)key);
         if(tertiary_min_length > MAX_TERTIARY_MIN_LENGTH || tertiary_min_length < MIN_TERTIARY_MIN_LENGTH){
            tertiary_min_length_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for tertiary volume fraction */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)TERTIARY_VOLUME_FRACTION_XMLTAG))) {
         tertiary_volume_fraction_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         tertiary_volume_fraction = (double) atof((const char*)key);
         if(tertiary_volume_fraction > MAX_TERTIARY_VOLUME_FRACTION|| tertiary_volume_fraction < MIN_TERTIARY_VOLUME_FRACTION){
            tertiary_volume_fraction_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
       /* look for tertiary number factor */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)TERTIARY_NUMBER_FACTOR_XMLTAG))) {
         tertiary_number_factor_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         tertiary_number_factor = (double) atof((const char*)key);
         if(tertiary_number_factor > MAX_TERTIARY_NUMBER_FACTOR || tertiary_number_factor < MIN_TERTIARY_NUMBER_FACTOR){
            tertiary_number_factor_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for fractional moisture content of tertiary branches */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)TERTIARY_MOISTURE_XMLTAG))) {
         tertiary_moisture_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         tertiary_moisture = (double) atof((const char*)key);
         if(tertiary_moisture > MAX_TERTIARY_MOISTURE || tertiary_moisture < MIN_TERTIARY_MOISTURE){
            tertiary_moisture_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
       /* look for leaf shape */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)LEAF_SHAPE_XMLTAG))) {
         leaf_shape_errflag = XML_READ_SUCCESS; /* found it! disable error flag */
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         if (!strcmp(trimwhitespace((char*)key),         LEAF_SHAPE_BROADLEAF_XMLID)){
            leaf_shape  =                                POLSARPROSIM_DECIDUOUS_LEAF;
         }else if (!strcmp(trimwhitespace((char*)key),   LEAF_SHAPE_NEEDLE_XMLID)){
            leaf_shape  =                                POLSARPROSIM_PINE_NEEDLE;
         }else{
            leaf_shape_errflag = XML_READ_ERROR; /* did not recognize, set error flag */
         }
         xmlFree(key);
      }
      /* look for mean leaf width */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)LEAF_THICKNESS_MEAN_XMLTAG))) {
         leaf_width_mean_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         leaf_width_mean = (double) atof((const char*)key);
         if(leaf_width_mean > MAX_LEAF_WIDTH_MEAN || leaf_width_mean < MIN_LEAF_WIDTH_MEAN){
            leaf_width_mean_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for leaf width stdev */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)LEAF_WIDTH_STDEV_XMLTAG))) {
         leaf_width_stdev_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         leaf_width_stdev = (double) atof((const char*)key);
         if(leaf_width_stdev > MAX_LEAF_WIDTH_STDEV || leaf_width_stdev < MIN_LEAF_WIDTH_STDEV){
            leaf_width_stdev_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for mean leaf height */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)LEAF_HEIGHT_MEAN_XMLTAG))) {
         leaf_height_mean_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         leaf_height_mean = (double) atof((const char*)key);
         if(leaf_height_mean > MAX_LEAF_HEIGHT_MEAN || leaf_height_mean < MIN_LEAF_HEIGHT_MEAN){
            leaf_height_mean_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for leaf height stdev */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)LEAF_HEIGHT_STDEV_XMLTAG))) {
         leaf_height_stdev_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         leaf_height_stdev = (double) atof((const char*)key);
         if(leaf_height_stdev > MAX_LEAF_HEIGHT_STDEV || leaf_height_stdev < MIN_LEAF_HEIGHT_STDEV){
            leaf_height_stdev_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for mean leaf thickness */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)LEAF_THICKNESS_MEAN_XMLTAG))) {
         leaf_thickness_mean_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         leaf_thickness_mean = (double) atof((const char*)key);
         if(leaf_thickness_mean > MAX_LEAF_THICKNESS_MEAN || leaf_thickness_mean < MIN_LEAF_THICKNESS_MEAN){
            leaf_thickness_mean_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for leaf thickness stdev */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)LEAF_THICKNESS_STDEV_XMLTAG))) {
         leaf_thickness_stdev_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         leaf_thickness_stdev = (double) atof((const char*)key);
         if(leaf_thickness_stdev > MAX_LEAF_THICKNESS_STDEV || leaf_thickness_stdev < MIN_LEAF_THICKNESS_STDEV){
            leaf_thickness_stdev_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for leaf volume fraction */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)LEAF_VOLUME_FRACTION_XMLTAG))) {
         leaf_volume_fraction_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         leaf_volume_fraction = (double) atof((const char*)key);
         if(leaf_volume_fraction > MAX_LEAF_VOLUME_FRACTION || leaf_volume_fraction < MIN_LEAF_VOLUME_FRACTION){
            leaf_volume_fraction_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for leaf number factor */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)LEAF_NUMBER_FACTOR_XMLTAG))) {
         leaf_number_factor_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         leaf_number_factor = (double) atof((const char*)key);
         if(leaf_number_factor > MAX_LEAF_NUMBER_FACTOR || leaf_number_factor < MIN_LEAF_NUMBER_FACTOR){
            leaf_number_factor_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }
      /* look for fractional moisture content of leaf  */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)LEAF_MOISTURE_XMLTAG))) {
         leaf_moisture_errflag = XML_READ_SUCCESS;
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         leaf_moisture = (double) atof((const char*)key);
         if(leaf_moisture > MAX_LEAF_MOISTURE || leaf_moisture < MIN_LEAF_MOISTURE){
            leaf_moisture_errflag = XML_READ_ERROR;
         }
         xmlFree(key);
      }



      cur = cur->next;
   }
   
   /* exit the program if any of the category fields do not exist */
   if(live_crown_shape_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Live crown shape not specified or unrecongized for category '%s' in Species database file\n", pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(dry_crown_shape_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Dry crown shape not specified or unrecognized for category '%s' in Species database file\n", pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(lcrown_depthfactor_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Live crown depth factor not specified or not between %f and %f for category '%s' in Species database file\n", MIN_LIVE_CROWN_DEPTH_FACTOR, MAX_LIVE_CROWN_DEPTH_FACTOR, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(dcrown_depthfactor_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Dry crown depth factor not specified or not between %f and %f for category '%s' in Species database file\n", MIN_DRY_CROWN_DEPTH_FACTOR, MAX_DRY_CROWN_DEPTH_FACTOR, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(crown_live_alpha_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Live crown alpha not specified or not between %f and %f for category '%s' in Species database file\n", MIN_CROWN_LIVE_ALPHA, MAX_CROWN_LIVE_ALPHA, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(crown_dry_alpha_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Dry crown alpha not specified or not between %f and %f for category '%s' in Species database file\n", MIN_CROWN_DRY_ALPHA, MAX_CROWN_DRY_ALPHA, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(crown_radius_factor_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Crown radius factor not specified or not between %f and %f for category '%s' in Species database file\n", MIN_CROWN_RADIUS_FACTOR, MAX_CROWN_RADIUS_FACTOR, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(stem_start_radius_factor_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Stem start radius factor not specified or not between %f and %f for category '%s' in Species database file\n", MIN_STEM_START_RADIUS_FACTOR, MAX_STEM_START_RADIUS_FACTOR, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(stem_max_angle_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Stem maximum angle not specified or not between %f and %f for category '%s' in Species database file\n", MIN_STEM_ANGLE, MAX_STEM_ANGLE, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(stem_end_radius_factor_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Stem end radius factor not specified or not between %f and %f for category '%s' in Species database file\n", MIN_STEM_END_RADIUS_FACTOR, MAX_STEM_END_RADIUS_FACTOR, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(stem_tropism_factor_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Stem tropism factor not specified or not between %f and %f for category '%s' in Species database file\n", MIN_STEM_TROPISM_FACTOR, MAX_STEM_TROPISM_FACTOR, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(stem_lamdacx_stdev_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: stdev of stem curvature wavelength (lamdacx) function not specified or not between %f and %f for category '%s' in Species database file\n", MIN_STEM_LAMDACX_STDEV, MAX_STEM_LAMDACX_STDEV, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(stem_lamdacx_mean_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: mean of stem curvature wavelength (lamdacx) function not specified or not between %f and %f for category '%s' in Species database file\n", MIN_STEM_LAMDACX_MEAN, MAX_STEM_LAMDACX_MEAN, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(stem_lamdacy_stdev_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: stdev of stem curvature wavelength (lamdacy) function not specified or not between %f and %f for category '%s' in Species database file\n", MIN_STEM_LAMDACY_STDEV, MAX_STEM_LAMDACY_STDEV, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(stem_lamdacy_mean_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: mean of stem curvature wavelength (lamdacy) function not specified or not between %f and %f for category '%s' in Species database file\n", MIN_STEM_LAMDACY_MEAN, MAX_STEM_LAMDACY_MEAN, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(stem_gamma_stdev_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: stdev of stem curvature scale-factor (gamma) function not specified or not between %f and %f for category '%s' in Species database file\n", MIN_STEM_GAMMA_STDEV, MAX_STEM_GAMMA_STDEV, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(stem_gamma_mean_errflag == XML_READ_ERROR){
      fprintf(stderr,"WARNING: mean of stem curvature scale-factor(gamma) function not specified or not between %f and %f for category '%s' in Species database file\n", MIN_STEM_GAMMA_MEAN, MAX_STEM_GAMMA_MEAN, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(stem_moisture_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Stem moisture not specified or not between %f and %f for category '%s' in Species database file\n", MIN_STEM_MOISTURE, MAX_STEM_MOISTURE, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(stem_tropism_theta_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Stem tropism polar angle (theta) not specified or not between %f and %f for category '%s' in Species database file\n", MIN_STEM_TROPISM_THETA, MAX_STEM_TROPISM_THETA , pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(stem_tropism_phi_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Stem tropism azimuthal angle (phi) not specified or not between %f and %f for category '%s' in Species database file\n", MIN_STEM_TROPISM_PHI, MAX_STEM_TROPISM_PHI, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(primary_avg_polar_angle_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Average primary polar angle (theta) not specified or not between %f and %f for category '%s' in Species database file\n", MIN_PRIMARY_AVG_POLAR_ANGLE, MAX_PRIMARY_AVG_POLAR_ANGLE, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(primary_std_polar_angle_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Std. of Primary polar angle (theta) not specified or not between %f and %f for category '%s' in Species database file\n", MIN_PRIMARY_STD_POLAR_ANGLE, MAX_PRIMARY_STD_POLAR_ANGLE, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(primary_layer_density_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Primary layer density not specified or not between %f and %f for category '%s' in Species database file\n", MIN_PRIMARY_LAYER_DENSITY, MAX_PRIMARY_LAYER_DENSITY, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(primary_avg_sections_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Primary average sections not specified or not between %f and %f for category '%s' in Species database file\n", MIN_PRIMARY_AVERAGE_SECTIONS, MAX_PRIMARY_AVERAGE_SECTIONS, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(primary_azimuth_factor_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Primary azimuth factor not specified or not between %f and %f for category '%s' in Species database file\n", MIN_PRIMARY_AZIMUTH_FACTOR, MAX_PRIMARY_AZIMUTH_FACTOR, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(primary_radius_A_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Quadratic coefficient of primary radius function not specified or not between %f and %f for category '%s' in Species database file\n", MIN_PRIMARY_RADIUS_A, MAX_PRIMARY_RADIUS_A, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(primary_radius_B_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Linear coefficient of primary radius function not specified or not between %f and %f for category '%s' in Species database file\n", MIN_PRIMARY_RADIUS_B, MAX_PRIMARY_RADIUS_B, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(primary_radius_C_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Constant coefficient of primary radius function not specified or not between %f and %f for category '%s' in Species database file\n", MIN_PRIMARY_RADIUS_C, MAX_PRIMARY_RADIUS_C, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(primary_tropism_factor_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Primary tropism factor not specified or not between %f and %f for category '%s' in Species database file\n", MIN_PRIMARY_TROPISM_FACTOR, MAX_PRIMARY_TROPISM_FACTOR, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(primary_tropism_theta_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Primary tropism polar angle (theta) not specified or not between %f and %f for category '%s' in Species database file\n", MIN_PRIMARY_TROPISM_THETA, MAX_PRIMARY_TROPISM_THETA , pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(primary_tropism_phi_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Primary tropism azimuthal angle (phi) not specified or not between %f and %f for category '%s' in Species database file\n", MIN_PRIMARY_TROPISM_PHI, MAX_PRIMARY_TROPISM_PHI, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(primary_tropism_theta_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Primary tropism polar angle (theta) not specified or not between %f and %f for category '%s' in Species database file\n", MIN_PRIMARY_TROPISM_THETA, MAX_PRIMARY_TROPISM_THETA , pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(primary_tropism_phi_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Primary tropism azimuthal angle (phi) not specified or not between %f and %f for category '%s' in Species database file\n", MIN_PRIMARY_TROPISM_PHI, MAX_PRIMARY_TROPISM_PHI, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(primary_lamdacx_stdev_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: stdev of primary curvature wavelength (lamdacx) function not specified or not between %f and %f for category '%s' in Species database file\n", MIN_PRIMARY_LAMDACX_STDEV, MAX_PRIMARY_LAMDACX_STDEV, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(primary_lamdacx_mean_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: mean of primary curvature wavelength (lamdacx) function not specified or not between %f and %f for category '%s' in Species database file\n", MIN_PRIMARY_LAMDACX_MEAN, MAX_PRIMARY_LAMDACX_MEAN, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(primary_lamdacy_stdev_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: stdev of primary curvature wavelength (lamdacy) function not specified or not between %f and %f for category '%s' in Species database file\n", MIN_PRIMARY_LAMDACY_STDEV, MAX_PRIMARY_LAMDACY_STDEV, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(primary_lamdacy_mean_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: mean of primary curvature wavelength (lamdacy) function not specified or not between %f and %f for category '%s' in Species database file\n", MIN_PRIMARY_LAMDACY_MEAN, MAX_PRIMARY_LAMDACY_MEAN, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(primary_gamma_stdev_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: stdev of primary curvature scale-factor (gamma) function not specified or not between %f and %f for category '%s' in Species database file\n", MIN_PRIMARY_GAMMA_STDEV, MAX_PRIMARY_GAMMA_STDEV, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(primary_gamma_mean_errflag == XML_READ_ERROR){
      fprintf(stderr,"WARNING: mean of primary curvature scale-factor(gamma) function not specified or not between %f and %f for category '%s' in Species database file\n", MIN_PRIMARY_GAMMA_MEAN, MAX_PRIMARY_GAMMA_MEAN, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(primary_live_moisture_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Live primary moisture not specified or not between %f and %f for category '%s' in Species database file\n", MIN_PRIMARY_LIVE_MOISTURE, MAX_PRIMARY_LIVE_MOISTURE, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(primary_dry_moisture_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Dry primary moisture not specified or not between %f and %f for category '%s' in Species database file\n", MIN_PRIMARY_DRY_MOISTURE, MAX_PRIMARY_DRY_MOISTURE, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(primary_dry_density_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Dry Primary layer density not specified or not between %f and %f for category '%s' in Species database file\n", MIN_PRIMARY_DRY_LAYER_DENSITY, MAX_PRIMARY_DRY_LAYER_DENSITY, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(primary_dry_sections_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Dry primary sections not specified or not between %f and %f for category '%s' in Species database file\n", MIN_PRIMARY_DRY_SECTIONS, MAX_PRIMARY_DRY_SECTIONS, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(secondary_number_slope_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Slope of function to determine number of secondary branches not specified or not between %f and %f for category '%s' in Species database file\n", MIN_SECONDARY_NUMBER_SLOPE, MAX_SECONDARY_NUMBER_SLOPE, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(secondary_number_intercept_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Intercept of function to determine number of secondary branches not specified or not between %f and %f for category '%s' in Species database file\n", MIN_SECONDARY_NUMBER_INTERCEPT, MAX_SECONDARY_NUMBER_INTERCEPT, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(secondary_offset_fraction_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Secondary branch offset fraction not specified or not between %f and %f for category '%s' in Species database file\n", MIN_SECONDARY_OFFSET_FRACTION, MAX_SECONDARY_OFFSET_FRACTION, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(secondary_radius_factor_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Secondary radius factor not specified or not between %f and %f for category '%s' in Species database file\n", MIN_SECONDARY_RADIUS_FACTOR, MAX_SECONDARY_RADIUS_FACTOR, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(secondary_tropism_factor_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Primary tropism factor not specified or not between %f and %f for category '%s' in Species database file\n", MIN_SECONDARY_TROPISM_FACTOR, MAX_SECONDARY_TROPISM_FACTOR, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(secondary_tropism_theta_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Primary tropism polar angle (theta) not specified or not between %f and %f for category '%s' in Species database file\n", MIN_SECONDARY_TROPISM_THETA, MAX_SECONDARY_TROPISM_THETA , pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(secondary_tropism_phi_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Primary tropism azimuthal angle (phi) not specified or not between %f and %f for category '%s' in Species database file\n", MIN_SECONDARY_TROPISM_PHI, MAX_SECONDARY_TROPISM_PHI, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(secondary_tropism_theta_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Primary tropism polar angle (theta) not specified or not between %f and %f for category '%s' in Species database file\n", MIN_SECONDARY_TROPISM_THETA, MAX_SECONDARY_TROPISM_THETA , pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(secondary_tropism_phi_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: Primary tropism azimuthal angle (phi) not specified or not between %f and %f for category '%s' in Species database file\n", MIN_SECONDARY_TROPISM_PHI, MAX_SECONDARY_TROPISM_PHI, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(secondary_lamdacx_stdev_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: stdev of secondary curvature wavelength (lamdacx) function not specified or not between %f and %f for category '%s' in Species database file\n", MIN_SECONDARY_LAMDACX_STDEV, MAX_SECONDARY_LAMDACX_STDEV, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(secondary_lamdacx_mean_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: mean of secondary curvature wavelength (lamdacx) function not specified or not between %f and %f for category '%s' in Species database file\n", MIN_SECONDARY_LAMDACX_MEAN, MAX_SECONDARY_LAMDACX_MEAN, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(secondary_lamdacy_stdev_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: stdev of secondary curvature wavelength (lamdacy) function not specified or not between %f and %f for category '%s' in Species database file\n", MIN_SECONDARY_LAMDACY_STDEV, MAX_SECONDARY_LAMDACY_STDEV, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(secondary_lamdacy_mean_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: mean of secondary curvature wavelength (lamdacy) function not specified or not between %f and %f for category '%s' in Species database file\n", MIN_SECONDARY_LAMDACY_MEAN, MAX_SECONDARY_LAMDACY_MEAN, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(secondary_gamma_stdev_errflag == XML_READ_ERROR){
      fprintf(stderr,"ERROR: stdev of secondary curvature scale-factor (gamma) function not specified or not between %f and %f for category '%s' in Species database file\n", MIN_SECONDARY_GAMMA_STDEV, MAX_SECONDARY_GAMMA_STDEV, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(secondary_gamma_mean_errflag == XML_READ_ERROR){
      fprintf(stderr,"WARNING: mean of secondary curvature scale-factor(gamma) function not specified or not between %f and %f for category '%s' in Species database file\n", MIN_SECONDARY_GAMMA_MEAN, MAX_SECONDARY_GAMMA_MEAN, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(tertiary_min_radius_errflag == XML_READ_ERROR){
      fprintf(stderr,"WARNING: minimum tertiary radius not specified or not between %f and %f for category '%s' in Species database file\n", MIN_TERTIARY_MIN_RADIUS, MAX_TERTIARY_MIN_RADIUS, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(tertiary_volume_fraction_errflag == XML_READ_ERROR){
      fprintf(stderr,"WARNING: tertiary volume fraction not specified or not between %f and %f for category '%s' in Species database file\n", MIN_TERTIARY_VOLUME_FRACTION, MAX_TERTIARY_VOLUME_FRACTION, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(tertiary_number_factor_errflag == XML_READ_ERROR){
      fprintf(stderr,"WARNING: tertiary number factor not specified or not between %f and %f for category '%s' in Species database file\n", MIN_TERTIARY_NUMBER_FACTOR, MAX_TERTIARY_NUMBER_FACTOR, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(tertiary_moisture_errflag == XML_READ_ERROR){
      fprintf(stderr,"WARNING: tertiary moisture not specified or not between %f and %f for category '%s' in Species database file\n", MIN_TERTIARY_MOISTURE, MAX_TERTIARY_MOISTURE, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(leaf_shape_errflag == XML_READ_ERROR){
      fprintf(stderr,"WARNING: leaf shape not specified or not recognized for category '%s' in Species database file\n", pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(leaf_width_mean_errflag == XML_READ_ERROR){
      fprintf(stderr,"WARNING: mean leaf width not specified or not between %f and %f for category '%s' in Species database file\n", MIN_LEAF_WIDTH_MEAN, MAX_LEAF_WIDTH_MEAN, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(leaf_width_stdev_errflag == XML_READ_ERROR){
      fprintf(stderr,"WARNING: leaf width standard deviation not specified or not between %f and %f for category '%s' in Species database file\n", MIN_LEAF_WIDTH_STDEV, MAX_LEAF_WIDTH_STDEV, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(leaf_height_mean_errflag == XML_READ_ERROR){
      fprintf(stderr,"WARNING: mean leaf height not specified or not between %f and %f for category '%s' in Species database file\n", MIN_LEAF_HEIGHT_MEAN, MAX_LEAF_HEIGHT_MEAN, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(leaf_height_stdev_errflag == XML_READ_ERROR){
      fprintf(stderr,"WARNING: leaf height standard deviation not specified or not between %f and %f for category '%s' in Species database file\n", MIN_LEAF_HEIGHT_STDEV, MAX_LEAF_HEIGHT_STDEV, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(leaf_thickness_mean_errflag == XML_READ_ERROR){
      fprintf(stderr,"WARNING: mean leaf thickness not specified or not between %f and %f for category '%s' in Species database file\n", MIN_LEAF_THICKNESS_MEAN, MAX_LEAF_THICKNESS_MEAN, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(leaf_thickness_stdev_errflag == XML_READ_ERROR){
      fprintf(stderr,"WARNING: leaf thickness standard deviation not specified or not between %f and %f for category '%s' in Species database file\n", MIN_LEAF_THICKNESS_STDEV, MAX_LEAF_THICKNESS_STDEV, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(leaf_volume_fraction_errflag == XML_READ_ERROR){
      fprintf(stderr,"WARNING: leaf volume fraction not specified or not between %f and %f for category '%s' in Species database file\n", MIN_LEAF_VOLUME_FRACTION, MAX_LEAF_VOLUME_FRACTION, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(leaf_number_factor_errflag == XML_READ_ERROR){
      fprintf(stderr,"WARNING: leaf number factor not specified or not between %f and %f for category '%s' in Species database file\n", MIN_LEAF_NUMBER_FACTOR, MAX_LEAF_NUMBER_FACTOR, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }
   if(leaf_moisture_errflag == XML_READ_ERROR){
      fprintf(stderr,"WARNING: leaf moisture not specified or not between %f and %f for category '%s' in Species database file\n", MIN_LEAF_MOISTURE, MAX_LEAF_MOISTURE, pPR->CategoryDataBase[icategories].species_name);
      exit(0);
   }


   /* Populate the actual Database */
   /* remember that the species_name is written in the species_list tag reading routine */
   pPR->CategoryDataBase[icategories].Trees                       = 0; /* initialize the number of trees here, increase when reading forest */
   pPR->CategoryDataBase[icategories].category                    = icategories; /* redundant, but who cares */
   pPR->CategoryDataBase[icategories].live_crown_shape            = live_crown_shape;
   pPR->CategoryDataBase[icategories].dry_crown_shape             = dry_crown_shape;
   pPR->CategoryDataBase[icategories].live_crown_depth_factor     = live_crown_depth_factor;
   pPR->CategoryDataBase[icategories].dry_crown_depth_factor      = dry_crown_depth_factor;
   pPR->CategoryDataBase[icategories].crown_live_alpha            = crown_live_alpha;
   pPR->CategoryDataBase[icategories].crown_dry_alpha             = crown_dry_alpha;
   pPR->CategoryDataBase[icategories].crown_radius_factor         = crown_radius_factor;
   pPR->CategoryDataBase[icategories].stem_start_radius_factor    = stem_start_radius_factor;
   pPR->CategoryDataBase[icategories].stem_max_angle              = stem_max_angle;
   pPR->CategoryDataBase[icategories].stem_end_radius_factor      = stem_end_radius_factor;
   pPR->CategoryDataBase[icategories].stem_tropism_factor         = stem_tropism_factor;
   pPR->CategoryDataBase[icategories].stem_lamdacx_stdev          = stem_lamdacx_stdev;
   pPR->CategoryDataBase[icategories].stem_lamdacx_mean           = stem_lamdacx_mean;
   pPR->CategoryDataBase[icategories].stem_lamdacy_stdev          = stem_lamdacy_stdev;
   pPR->CategoryDataBase[icategories].stem_lamdacy_mean           = stem_lamdacy_mean;
   pPR->CategoryDataBase[icategories].stem_gamma_stdev            = stem_gamma_stdev;
   pPR->CategoryDataBase[icategories].stem_gamma_mean             = stem_gamma_mean;
   pPR->CategoryDataBase[icategories].stem_moisture               = stem_moisture;
   pPR->CategoryDataBase[icategories].stem_tropism_theta          = stem_tropism_theta;
   pPR->CategoryDataBase[icategories].stem_tropism_phi            = stem_tropism_phi;
   pPR->CategoryDataBase[icategories].primary_avg_polar_angle     = primary_avg_polar_angle;
   pPR->CategoryDataBase[icategories].primary_std_polar_angle     = primary_std_polar_angle;
   pPR->CategoryDataBase[icategories].primary_layer_density       = primary_layer_density;
   pPR->CategoryDataBase[icategories].primary_avg_sections        = primary_avg_sections;
   pPR->CategoryDataBase[icategories].primary_azimuth_factor      = primary_azimuth_factor;
   pPR->CategoryDataBase[icategories].primary_radius_A            = primary_radius_A;
   pPR->CategoryDataBase[icategories].primary_radius_B            = primary_radius_B;
   pPR->CategoryDataBase[icategories].primary_radius_C            = primary_radius_C;
   pPR->CategoryDataBase[icategories].primary_tropism_factor      = primary_tropism_factor;
   pPR->CategoryDataBase[icategories].primary_tropism_theta       = primary_tropism_theta;
   pPR->CategoryDataBase[icategories].primary_tropism_phi         = primary_tropism_phi;
   pPR->CategoryDataBase[icategories].primary_lamdacx_stdev       = primary_lamdacx_stdev;
   pPR->CategoryDataBase[icategories].primary_lamdacx_mean        = primary_lamdacx_mean;
   pPR->CategoryDataBase[icategories].primary_lamdacy_stdev       = primary_lamdacy_stdev;
   pPR->CategoryDataBase[icategories].primary_lamdacy_mean        = primary_lamdacy_mean;
   pPR->CategoryDataBase[icategories].primary_gamma_stdev         = primary_gamma_stdev;
   pPR->CategoryDataBase[icategories].primary_gamma_mean          = primary_gamma_mean;
   pPR->CategoryDataBase[icategories].primary_live_moisture       = primary_live_moisture;
   pPR->CategoryDataBase[icategories].primary_dry_moisture        = primary_dry_moisture;
   pPR->CategoryDataBase[icategories].primary_dry_density         = primary_dry_density;
   pPR->CategoryDataBase[icategories].primary_dry_sections        = primary_dry_sections;
   pPR->CategoryDataBase[icategories].secondary_number_slope      = secondary_number_slope;
   pPR->CategoryDataBase[icategories].secondary_number_intercept  = secondary_number_intercept;
   pPR->CategoryDataBase[icategories].secondary_offset_fraction   = secondary_offset_fraction;
   pPR->CategoryDataBase[icategories].secondary_avg_polar_angle   = secondary_avg_polar_angle;
   pPR->CategoryDataBase[icategories].secondary_std_polar_angle   = secondary_std_polar_angle;
   pPR->CategoryDataBase[icategories].secondary_radius_factor     = secondary_radius_factor;
   pPR->CategoryDataBase[icategories].secondary_tropism_factor    = secondary_tropism_factor;
   pPR->CategoryDataBase[icategories].secondary_tropism_theta     = secondary_tropism_theta;
   pPR->CategoryDataBase[icategories].secondary_tropism_phi       = secondary_tropism_phi;
   pPR->CategoryDataBase[icategories].secondary_lamdacx_stdev     = secondary_lamdacx_stdev;
   pPR->CategoryDataBase[icategories].secondary_lamdacx_mean      = secondary_lamdacx_mean;
   pPR->CategoryDataBase[icategories].secondary_lamdacy_stdev     = secondary_lamdacy_stdev;
   pPR->CategoryDataBase[icategories].secondary_lamdacy_mean      = secondary_lamdacy_mean;
   pPR->CategoryDataBase[icategories].secondary_gamma_stdev       = secondary_gamma_stdev;
   pPR->CategoryDataBase[icategories].secondary_gamma_mean        = secondary_gamma_mean;
   pPR->CategoryDataBase[icategories].tertiary_min_radius         = tertiary_min_radius;
   pPR->CategoryDataBase[icategories].tertiary_min_length         = tertiary_min_length;
   pPR->CategoryDataBase[icategories].tertiary_volume_fraction    = tertiary_volume_fraction;
   pPR->CategoryDataBase[icategories].tertiary_number_factor      = tertiary_number_factor;
   pPR->CategoryDataBase[icategories].tertiary_moisture           = tertiary_moisture;
   pPR->CategoryDataBase[icategories].leaf_shape                  = leaf_shape;
   pPR->CategoryDataBase[icategories].leaf_width_mean             = leaf_width_mean;
   pPR->CategoryDataBase[icategories].leaf_width_stdev            = leaf_width_stdev;
   pPR->CategoryDataBase[icategories].leaf_height_mean            = leaf_height_mean;
   pPR->CategoryDataBase[icategories].leaf_height_stdev           = leaf_height_stdev;
   pPR->CategoryDataBase[icategories].leaf_thickness_mean         = leaf_thickness_mean;
   pPR->CategoryDataBase[icategories].leaf_thickness_stdev        = leaf_thickness_stdev;
   pPR->CategoryDataBase[icategories].leaf_volume_fraction        = leaf_volume_fraction;
   pPR->CategoryDataBase[icategories].leaf_number_factor          = leaf_number_factor;
   pPR->CategoryDataBase[icategories].leaf_moisture               = leaf_moisture;


   return;
}


void Input_PolSARproSim_Allometry(PolSARproSim_Record *pPR) {
   
   xmlDocPtr   doc;
   xmlNodePtr  cur;
   int         ispecies                = 0;
   int         icategories             = 0;
   /* XML read error flags */
   int         species_list_errflag    = 0;
   int         category_list_errflag   = 0;
   int         species_errflag         = 0;
   int         category_errflag        = 0;
   
   doc = xmlParseFile(pPR->SpeciesData);
   
   /***************************************/
   /* Some initial file checks            */
   /***************************************/
   
   /* Check to see if XML document exists */
   if (doc == NULL ) {
      fprintf(pPR->pLogFile,  "ERROR: Species database file not parsed successfully. \n");
      fprintf(stderr,         "ERROR: Species database file not parsed successfully. \n");
      exit(0);
   }   
   /* Set the pointer to current document */
   cur = xmlDocGetRootElement(doc);
   /* See if the document actually contains anything */
   if (cur == NULL) {
      fprintf(pPR->pLogFile,"Error: Empty species database document\n");
      fprintf(stderr,"Error: Empty species database document\n");
      xmlFreeDoc(doc);
      exit(0);
   }
   /* see if the root node is correct, must be ALLOMETRY_XMLTAG (see read_allometry.h) */
   if (xmlStrcmp(cur->name, (const xmlChar *)ALLOMETRY_XMLTAG)) {
      fprintf(pPR->pLogFile,  "ERROR: species database file of the wrong type, root node != %s\n", ALLOMETRY_XMLTAG);
      fprintf(stderr,         "ERROR: species database file of the wrong type, root node != %s\n", ALLOMETRY_XMLTAG);
      xmlFreeDoc(doc);
      exit(0);
   }
   
   /***************************************/
   /* Read in the Defaults Database       */
   /***************************************/
   
   /* read the <category_list> data tag for a list of categories */
   cur = xmlDocGetRootElement(doc);
   cur = cur->xmlChildrenNode;
   while (cur != NULL) {
      if ((!xmlStrcmp(cur->name, (const xmlChar *)CATEGORY_LIST_XMLTAG))){
         getCategoryList (doc, cur, pPR);
         category_list_errflag=1;
      }
      cur = cur->next;
   }
   /* Exit if category_list tag not found */
   if(!category_list_errflag) {  
      fprintf(pPR->pLogFile,  "ERROR: <category_list> tag not found in species database file. \n");
      fprintf(stderr,         "ERROR: <category_list> tag not found in species database file. \n");
      exit(0);
   }
   /* Go throug the XML file and populate the Default database for each category */
   for(icategories = 0;icategories<pPR->Ncategories;icategories++){
      cur = xmlDocGetRootElement(doc);
      cur = cur->xmlChildrenNode;
      while (cur != NULL && species_errflag == XML_READ_ERROR){ /* loop through tags until this category is located */
         if ((!xmlStrcmp(cur->name, (const xmlChar *)pPR->CategoryDataBase[icategories].species_name))){
            category_errflag = XML_READ_SUCCESS; /* found it! unset error flag */
            /* this function populates the Default database form XML file or default if not specified */
            getCategoryData(doc, cur, pPR, icategories);
         }
         cur = cur->next;
      }
      if(category_errflag == XML_READ_ERROR){
         fprintf(pPR->pLogFile,  "ERROR: XML tag for category (%s) not found in species database file\n", pPR->CategoryDataBase[icategories].species_name);
         fprintf(stderr,         "ERROR: XML tag for category (%s) not found in species database file\n", pPR->CategoryDataBase[icategories].species_name);
         exit(0);
      }
      category_errflag = XML_READ_ERROR; /* unset the flag for next category */
   }
   
   /***************************************/
   /* Read in the Species Database        */
   /***************************************/
   
   /* read the <species_list> data tag for a list of species */
   cur = xmlDocGetRootElement(doc);
   cur = cur->xmlChildrenNode;
   while (cur != NULL) {
      if ((!xmlStrcmp(cur->name, (const xmlChar *)SPECIES_LIST_XMLTAG))){
         getSpeciesList (doc, cur, pPR);
         species_list_errflag=1;
      }
      cur = cur->next;
   }
   /* Exit if species_list tag not found */
   if(!species_list_errflag) {  
      fprintf(pPR->pLogFile,  "ERROR: <species_list> tag not found in species database file. \n");
      fprintf(stderr,         "ERROR: <species_list> tag not found in species database file. \n");
      exit(0);
   }      
   /* Go throug the XML file and populate the Allometry database for each species */
   for(ispecies = 0;ispecies<pPR->Nspecies;ispecies++){
      cur = xmlDocGetRootElement(doc);
      cur = cur->xmlChildrenNode;
      while (cur != NULL && species_errflag == XML_READ_ERROR){ /* loop through tags until this species is located */
         if ((!xmlStrcmp(cur->name, (const xmlChar *)pPR->SpeciesDataBase[ispecies].species_name))){
            species_errflag = XML_READ_SUCCESS; /* found it! unset error flag */
            /* this function populates the Allometry database form XML file or default if not specified */
            getSpeciesData(doc, cur, pPR, ispecies);
         }
         cur = cur->next;
      }
      if(species_errflag == XML_READ_ERROR){
         fprintf(pPR->pLogFile,  "ERROR: <%s> tag not found in species database file\n", pPR->SpeciesDataBase[ispecies].species_name);
         fprintf(stderr,         "ERROR: <%s> tag not found in species database file\n", pPR->SpeciesDataBase[ispecies].species_name);
         exit(0);
      }
      species_errflag = XML_READ_ERROR; /* unset the flag for next species */
   }   

   /*********************************/
   /* report the species parameters */
   /*********************************/
   /* Put in a reporting procedure  */
   /*********************************/
   // report_SpeciesDatabase(pPR);
   /*********************************/
   
   
   /***************************************/
   /* done reading XML database           */
   /***************************************/
   
   xmlFreeDoc(doc);
   fprintf(pPR->pLogFile, "Done reading species database\n");
   printf("Done reading species database\n");
   return;
}

/******************************************************/
/* Print all the Allometry parameters to the log file */
/******************************************************/
void Report_PolSARproSim_Allometry(PolSARproSim_Record *pPR)
{
   int ispecies;
   
   fprintf(pPR->pLogFile, "\n\nAllometric parameters associated with each species\n");
   
   for(ispecies=0;ispecies<pPR->Nspecies;ispecies++){
      fprintf(pPR->pLogFile, "Species: %s\n", pPR->SpeciesDataBase[ispecies].species_name);
      switch (pPR->SpeciesDataBase[ispecies].live_crown_shape) {
         case CROWN_CYLINDER:    fprintf(pPR->pLogFile, "\tLive Crown Shape:                 \t%12s\n", (char *)CROWN_CYLINDER_XMLID); break;
         case CROWN_CONE:        fprintf(pPR->pLogFile, "\tLive Crown Shape:                 \t%12s\n", (char *)CROWN_CONE_XMLID); break;
         case CROWN_SPHEROID:    fprintf(pPR->pLogFile, "\tLive Crown Shape:                 \t%12s\n", (char *)CROWN_SPHERE_XMLID); break;
         case CROWN_NULL_SHAPE:  fprintf(pPR->pLogFile, "\tLive Crown Shape:                 \t%12s\n", (char *)CROWN_NONE_XMLID); break;
         default:                fprintf(pPR->pLogFile, "\tLive Crown Shape:                 \tBADNESS\n"); break;
      }
      switch (pPR->SpeciesDataBase[ispecies].dry_crown_shape) {
         case CROWN_CYLINDER:    fprintf(pPR->pLogFile, "\tDry Crown Shape:                  \t%12s\n", (char *)CROWN_CYLINDER_XMLID); break;
         case CROWN_CONE:        fprintf(pPR->pLogFile, "\tDry Crown Shape:                  \t%12s\n", (char *)CROWN_CONE_XMLID); break;
         case CROWN_SPHEROID:    fprintf(pPR->pLogFile, "\tDry Crown Shape:                  \t%12s\n", (char *)CROWN_SPHERE_XMLID); break;
         case CROWN_NULL_SHAPE:  fprintf(pPR->pLogFile, "\tDry Crown Shape:                  \t%12s\n", (char *)CROWN_NONE_XMLID); break;
         default:                fprintf(pPR->pLogFile, "\tDry Crown Shape:                  \tBADNESS\n"); break;
      }
      fprintf(pPR->pLogFile, "\tLive Crown Depth Factor:          \t%12f\n", pPR->SpeciesDataBase[ispecies].live_crown_depth_factor);
      fprintf(pPR->pLogFile, "\tDry Crown Depth Factor:           \t%12f\n", pPR->SpeciesDataBase[ispecies].dry_crown_depth_factor);
      fprintf(pPR->pLogFile, "\tLive Crown Alpha:                 \t%12f\n", pPR->SpeciesDataBase[ispecies].crown_live_alpha);
      fprintf(pPR->pLogFile, "\tDry Crown Alpha:                  \t%12f\n", pPR->SpeciesDataBase[ispecies].crown_dry_alpha);
      fprintf(pPR->pLogFile, "\tCrown Radius Factor:              \t%12f\n", pPR->SpeciesDataBase[ispecies].crown_radius_factor);
      fprintf(pPR->pLogFile, "\tStem start radius factor          \t%12f\n", pPR->SpeciesDataBase[ispecies].stem_start_radius_factor);  
      fprintf(pPR->pLogFile, "\tStem Maximum Polar Angle:         \t%12f\n", pPR->SpeciesDataBase[ispecies].stem_max_angle);
      fprintf(pPR->pLogFile, "\tStem End Radius Factor:           \t%12f\n", pPR->SpeciesDataBase[ispecies].stem_end_radius_factor);
      fprintf(pPR->pLogFile, "\tStem Tropism Factor:              \t%12f\n", pPR->SpeciesDataBase[ispecies].stem_tropism_factor);
      fprintf(pPR->pLogFile, "\tStem Tropism Polar Angle:         \t%12f\n", pPR->SpeciesDataBase[ispecies].stem_tropism_theta);
      fprintf(pPR->pLogFile, "\tStem Tropism Az. Angle:           \t%12f\n", pPR->SpeciesDataBase[ispecies].stem_tropism_phi);
      fprintf(pPR->pLogFile, "\tStem Lamdacx Mean:                \t%12f\n", pPR->SpeciesDataBase[ispecies].stem_lamdacx_mean);
      fprintf(pPR->pLogFile, "\tStem Lamdacx Stdev:               \t%12f\n", pPR->SpeciesDataBase[ispecies].stem_lamdacx_stdev);
      fprintf(pPR->pLogFile, "\tStem Lamdacy Mean:                \t%12f\n", pPR->SpeciesDataBase[ispecies].stem_lamdacy_mean);
      fprintf(pPR->pLogFile, "\tStem Lamdacy Stdev:               \t%12f\n", pPR->SpeciesDataBase[ispecies].stem_lamdacy_stdev);
      fprintf(pPR->pLogFile, "\tStem Gamma Mean:                  \t%12f\n", pPR->SpeciesDataBase[ispecies].stem_gamma_mean);
      fprintf(pPR->pLogFile, "\tStem Gamma Stdev:                 \t%12f\n", pPR->SpeciesDataBase[ispecies].stem_gamma_stdev);
      fprintf(pPR->pLogFile, "\tStem Fractional Moisture:         \t%12f\n", pPR->SpeciesDataBase[ispecies].stem_moisture);
      fprintf(pPR->pLogFile, "\tPrimary Polar Angle Mean:         \t%12f\n", pPR->SpeciesDataBase[ispecies].primary_avg_polar_angle);
      fprintf(pPR->pLogFile, "\tPrimary Polar Angle Stdev:        \t%12f\n", pPR->SpeciesDataBase[ispecies].primary_std_polar_angle);
      fprintf(pPR->pLogFile, "\tPrimary Layer Density:            \t%12f\n", pPR->SpeciesDataBase[ispecies].primary_layer_density);
      fprintf(pPR->pLogFile, "\tPrimary Average Sections:         \t%12d\n", pPR->SpeciesDataBase[ispecies].primary_avg_sections);
      fprintf(pPR->pLogFile, "\tPrimary Azimuth Factor:           \t%12f\n", pPR->SpeciesDataBase[ispecies].primary_azimuth_factor);
      fprintf(pPR->pLogFile, "\tPrimary Radius Quadratic Coeff.:  \t%12f\n", pPR->SpeciesDataBase[ispecies].primary_radius_A);
      fprintf(pPR->pLogFile, "\tPrimary Radius Linear Coeff.:     \t%12f\n", pPR->SpeciesDataBase[ispecies].primary_radius_B);
      fprintf(pPR->pLogFile, "\tPrimary Radius Constant Coeff.:   \t%12f\n", pPR->SpeciesDataBase[ispecies].primary_radius_C);
      fprintf(pPR->pLogFile, "\tPrimary Tropism Factor:           \t%12f\n", pPR->SpeciesDataBase[ispecies].primary_tropism_factor);
      fprintf(pPR->pLogFile, "\tPrimary Tropism Polar Angle:      \t%12f\n", pPR->SpeciesDataBase[ispecies].primary_tropism_theta);
      fprintf(pPR->pLogFile, "\tPrimary Tropism Az. Angle:        \t%12f\n", pPR->SpeciesDataBase[ispecies].primary_tropism_phi);
      fprintf(pPR->pLogFile, "\tPrimary Lamdacx Mean:             \t%12f\n", pPR->SpeciesDataBase[ispecies].primary_lamdacx_mean);
      fprintf(pPR->pLogFile, "\tPrimary Lamdacx Stdev:            \t%12f\n", pPR->SpeciesDataBase[ispecies].primary_lamdacx_stdev);
      fprintf(pPR->pLogFile, "\tPrimary Lamdacy Mean:             \t%12f\n", pPR->SpeciesDataBase[ispecies].primary_lamdacy_mean);
      fprintf(pPR->pLogFile, "\tPrimary Lamdacy Stdev:            \t%12f\n", pPR->SpeciesDataBase[ispecies].primary_lamdacy_stdev);
      fprintf(pPR->pLogFile, "\tPrimary Gamma Mean:               \t%12f\n", pPR->SpeciesDataBase[ispecies].primary_gamma_mean);
      fprintf(pPR->pLogFile, "\tPrimary Gamma Stdev:              \t%12f\n", pPR->SpeciesDataBase[ispecies].primary_gamma_stdev);
      fprintf(pPR->pLogFile, "\tPrimary Live Fractional Moisture: \t%12f\n", pPR->SpeciesDataBase[ispecies].primary_live_moisture);
      fprintf(pPR->pLogFile, "\tPrimary Dry Fractional Moisture:  \t%12f\n", pPR->SpeciesDataBase[ispecies].primary_dry_moisture);
      fprintf(pPR->pLogFile, "\tPrimary Dry Layer Density:        \t%12f\n", pPR->SpeciesDataBase[ispecies].primary_dry_density);
      fprintf(pPR->pLogFile, "\tPrimary Dry Layer Sections:       \t%12d\n", pPR->SpeciesDataBase[ispecies].primary_dry_sections);
      fprintf(pPR->pLogFile, "\tSecondary Number Linear Coeff.    \t%12f\n", pPR->SpeciesDataBase[ispecies].secondary_number_slope);
      fprintf(pPR->pLogFile, "\tSecondary Number Constant Coeff.  \t%12f\n", pPR->SpeciesDataBase[ispecies].secondary_number_intercept);
      fprintf(pPR->pLogFile, "\tSecondary Offset Fraction         \t%12f\n", pPR->SpeciesDataBase[ispecies].secondary_offset_fraction);
      fprintf(pPR->pLogFile, "\tSecondary Polar Angle Mean:       \t%12f\n", pPR->SpeciesDataBase[ispecies].secondary_avg_polar_angle);
      fprintf(pPR->pLogFile, "\tSecondary Polar Angle Stdev:      \t%12f\n", pPR->SpeciesDataBase[ispecies].secondary_std_polar_angle);
      fprintf(pPR->pLogFile, "\tSecondary Radius Factor:          \t%12f\n", pPR->SpeciesDataBase[ispecies].secondary_radius_factor);
      fprintf(pPR->pLogFile, "\tSecondary Tropism Factor:         \t%12f\n", pPR->SpeciesDataBase[ispecies].secondary_tropism_factor);
      fprintf(pPR->pLogFile, "\tSecondary Tropism Polar Angle:    \t%12f\n", pPR->SpeciesDataBase[ispecies].secondary_tropism_theta);
      fprintf(pPR->pLogFile, "\tSecondary Tropism Az. Angle:      \t%12f\n", pPR->SpeciesDataBase[ispecies].secondary_tropism_phi);
      fprintf(pPR->pLogFile, "\tSecondary Lamdacx Mean:           \t%12f\n", pPR->SpeciesDataBase[ispecies].secondary_lamdacx_mean);
      fprintf(pPR->pLogFile, "\tSecondary Lamdacx Stdev:          \t%12f\n", pPR->SpeciesDataBase[ispecies].secondary_lamdacx_stdev);
      fprintf(pPR->pLogFile, "\tSecondary Lamdacy Mean:           \t%12f\n", pPR->SpeciesDataBase[ispecies].secondary_lamdacy_mean);
      fprintf(pPR->pLogFile, "\tSecondary Lamdacy Stdev:          \t%12f\n", pPR->SpeciesDataBase[ispecies].secondary_lamdacy_stdev);
      fprintf(pPR->pLogFile, "\tSecondary Gamma Mean:             \t%12f\n", pPR->SpeciesDataBase[ispecies].secondary_gamma_mean);
      fprintf(pPR->pLogFile, "\tSecondary Gamma Stdev:            \t%12f\n", pPR->SpeciesDataBase[ispecies].secondary_gamma_stdev);
      fprintf(pPR->pLogFile, "\tTertiary Minimum Radius:          \t%12f\n", pPR->SpeciesDataBase[ispecies].tertiary_min_radius);
      fprintf(pPR->pLogFile, "\tTertiary Minimum Length:          \t%12f\n", pPR->SpeciesDataBase[ispecies].tertiary_min_length);
      fprintf(pPR->pLogFile, "\tTertiary Volume Fraction:         \t%12f\n", pPR->SpeciesDataBase[ispecies].tertiary_volume_fraction);
      fprintf(pPR->pLogFile, "\tTertiary Number Factor:           \t%12f\n", pPR->SpeciesDataBase[ispecies].tertiary_number_factor);
      fprintf(pPR->pLogFile, "\tTertiary Fractional Moisture:     \t%12f\n", pPR->SpeciesDataBase[ispecies].tertiary_moisture);
      switch (pPR->SpeciesDataBase[ispecies].leaf_shape) {
         case POLSARPROSIM_PINE_NEEDLE:      fprintf(pPR->pLogFile, "\tLeaf Shape:                       \t%12s\n", (char *)LEAF_SHAPE_NEEDLE_XMLID); break;
         case POLSARPROSIM_DECIDUOUS_LEAF:   fprintf(pPR->pLogFile, "\tLeaf Shape:                       \t%12s\n", (char *)LEAF_SHAPE_BROADLEAF_XMLID); break;
         default:                            fprintf(pPR->pLogFile, "\tLeaf Shape:                       \tBADNESS\n"); break;
      }
      fprintf(pPR->pLogFile, "\tLeaf Width Mean:                  \t%12f\n", pPR->SpeciesDataBase[ispecies].leaf_width_mean);
      fprintf(pPR->pLogFile, "\tLeaf Width Stdev:                 \t%12f\n", pPR->SpeciesDataBase[ispecies].leaf_width_stdev);
      fprintf(pPR->pLogFile, "\tLeaf Height Mean:                 \t%12f\n", pPR->SpeciesDataBase[ispecies].leaf_height_mean);
      fprintf(pPR->pLogFile, "\tLeaf Height Stdev:                \t%12f\n", pPR->SpeciesDataBase[ispecies].leaf_height_stdev);
      fprintf(pPR->pLogFile, "\tLeaf Thickness Mean:              \t%12f\n", pPR->SpeciesDataBase[ispecies].leaf_thickness_mean);
      fprintf(pPR->pLogFile, "\tLeaf Thickness Stdev:             \t%12f\n", pPR->SpeciesDataBase[ispecies].leaf_thickness_stdev);
      fprintf(pPR->pLogFile, "\tLeaf Volume Fraction:             \t%12f\n", pPR->SpeciesDataBase[ispecies].leaf_volume_fraction);
      fprintf(pPR->pLogFile, "\tLeaf Number Factor:               \t%12f\n", pPR->SpeciesDataBase[ispecies].leaf_number_factor);
      fprintf(pPR->pLogFile, "\tLeaf Fractional Moisture:         \t%12f\n", pPR->SpeciesDataBase[ispecies].leaf_moisture);

   }
   return;
}   
