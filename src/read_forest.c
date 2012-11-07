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
 * Module      : read_forest.c
 * Revision    : Version 1.1 
 * Date        : July, 2012
 * Notes       : Reading in forest data from a text file
 * Addition    : Added reading of XML forest description file, August 13 2012
 */


#include "read_forest.h"

///********************************************************/ 
///* This routine reads forest primitives from            */
///* the tab delimited (TDF) version of the input file    */
///*  -- deprecated August 2012                           */
///********************************************************/
///* note: in its current form, cannot input hedge        */
//int		Input_PolSARproSim_Forest_TDF		(PolSARproSim_Record *pPR)
//{
//   FILE        *pFin;
//   char        line[FOREST_READLINE_BUFFER];
//   /******************/
//   /* File structure */
//   /******************/
//   int         species;                /* species number 0:hedge, 1-3 Pine, 4 Deciduous   */
//   double      tree_x;                 /* x coordinate location of tree                   */
//   double      tree_y;                 /* y-coordinate locaiton of tree                   */
//   double      tree_height;            /* max tree height [m]                             */
//   double      canopy_radius;          /* canopy radius in x-y plane [m]                  */
//   double      canopy_depth;           /* canopy depth [m]                                */
//   double      canopy_dry_depth;       /* canopy dry depth [m]                            */
//   int         lad;                    /* leaf angle distribution (lidar leftover)        */
//   double      leaf_size;              /* mean leaf diameter                              */
//   double      dbh;                    /* diameter at breast height for tree              */
//   
//   int         itree;                  /* tree count variable */
//   double      mean_tree_height  = 0;       
//   double      mean_crown_radius = 0;
//   double      max_tree_y        = 0;
//   double      max_tree_x        = 0;
//   double      max_tree_height   = 0;
//   
//#ifdef VERBOSE_POLSARPROSIM
//   printf("Reading tree canopy primitives from file: %s\n", pPR->ForestData);
//#endif
//   fprintf(pPR->pLogFile, "Forest primitives read from: %s\n", pPR->ForestData);   
//   
//   /* Attempt to open the file */
//   if ((pFin = fopen(pPR->ForestData, "r")) == NULL) {
//#ifdef VERBOSE_POLSARPROSIM
//      printf("Unable to open canopy data file: %s\n", pPR->ForestData);
//#endif
//      fprintf(pPR->pLogFile, "ERROR: Unable to open canopy data file: %s\n", pPR->ForestData);
//      return(!NO_POLSARPROSIM_ERRORS);
//   }
//   
//   itree=0;
//   /* Loop through the lines to estimate number of trees in the input file         */
//   while ( fgets(line, sizeof line, pFin) != NULL){    
//      /* parse the string */ 
//      sscanf(line, "%d %lf %lf %lf %lf %lf %lf %d %lf %lf", &species, &tree_x, &tree_y, &tree_height, &canopy_radius, &canopy_depth, &canopy_dry_depth, &lad, &leaf_size, &dbh);
//      itree++;
//   }
//   /* Update tree count variable in master record in case  */
//   /* number of lines in file was less than pPR->Trees     */
//   pPR->Trees  = itree;
//   printf("The total number of trees in file are: %d\n", pPR->Trees); 
//   
//   /* Now allocate space in memory */
//   pPR->Tree_Location      = (TreeLoc*) calloc (pPR->Trees, sizeof(TreeLoc));
//   
//   /* Rewind file pointer */
//   rewind(pFin);
//   
//   /* Second run gets the actual tree data */
//   itree=0;
//   while ( fgets(line, sizeof line, pFin) != NULL){    
//      
//      /* read and parse string */
//      sscanf(line, "%d %lf %lf %lf %lf %lf %lf %d %lf %lf", &species, &tree_x, &tree_y, &tree_height, &canopy_radius, &canopy_depth, &canopy_dry_depth, &lad, &leaf_size, &dbh);    
//      //printf("%d) %d\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%d\t%lf\t%lf\n", itree, species, tree_x, tree_y, tree_height, canopy_radius, canopy_depth, lai, lad, leaf_size, dbh);
//      /* Populate the Tree_Location structure in Master Record */
//      pPR->Tree_Location[itree].x                 = tree_x;
//      pPR->Tree_Location[itree].y                 = tree_y;
//      pPR->Tree_Location[itree].species           = species;
//      pPR->Tree_Location[itree].height            = tree_height;
//      pPR->Tree_Location[itree].dbh               = dbh;
//      pPR->Tree_Location[itree].radius            = canopy_radius;
//      pPR->Tree_Location[itree].canopy_depth      = canopy_depth;
//      pPR->Tree_Location[itree].canopy_dry_depth  = canopy_dry_depth;
//      
//      /**********************************************************/
//      /* Estimate mean crown radius, mean tree height,          */
//      /* stand area, stand radius                               */
//      /**********************************************************/
//      
//      mean_crown_radius     = mean_crown_radius + pPR->Tree_Location[itree].radius;
//      mean_tree_height      = mean_tree_height  + pPR->Tree_Location[itree].height;
//      max_tree_y            = MAX(max_tree_y, fabs(pPR->Tree_Location[itree].y));
//      max_tree_x            = MAX(max_tree_x, fabs(pPR->Tree_Location[itree].x));   
//      max_tree_height       = MAX(max_tree_height,pPR->Tree_Location[itree].height);
//      
//      itree++;
//   }
//   
//   /**********************************************************/
//   /* Fill in the Forest attributes section of Master Record */
//   /**********************************************************/
//   
//   pPR->max_tree_height    = max_tree_height; /* Added this field for Attenuation Map changes */
//   pPR->mean_tree_height   = mean_tree_height/pPR->Trees;
//   pPR->mean_crown_radius  = mean_crown_radius/pPR->Trees;
//   pPR->Stand_Radius       = MAX(max_tree_y, max_tree_x);
//   pPR->Stand_Area         = DPI_RAD * pPR->Stand_Radius * pPR->Stand_Radius;
//   
//   pPR->Layover_Distance   = pPR->max_tree_height / tan(pPR->incidence_angle[0]);
//   pPR->Shadow_Distance    = pPR->max_tree_height * tan(pPR->incidence_angle[0]);
//   pPR->Gap_Distance       = RESOLUTION_GAP_SIZE * (pPR->azimuth_resolution + pPR->ground_range_resolution[0])/2.0;
//   
//   pPR->Lx                 = 2.0*(pPR->Stand_Radius+pPR->Gap_Distance+pPR->mean_crown_radius);
//   pPR->Ly                 = pPR->Lx + pPR->Layover_Distance+pPR->Shadow_Distance;
//   pPR->Area               = pPR->Lx*pPR->Ly;
//   pPR->Hectares						= pPR->Area/10000.0;
//   
//   
//   /**********************************/
//   /* Calculate SAR image dimensions */
//   /**********************************/
//   
//   pPR->nx                 = (int) (pPR->Lx / pPR->deltax) + 1;
//   pPR->nx                 = 2*((int)(pPR->nx/2))+1;
//   pPR->deltax             = pPR->Lx/pPR->nx;
//   pPR->ny                 = (int) (pPR->Ly / pPR->deltay) + 1;
//   pPR->ny                 = 2*((int)(pPR->ny/2))+1;
//   pPR->deltay             = pPR->Ly/pPR->ny;
//   
//   printf("Done reading canopy primitives from file: %s\n",pPR->ForestData); 
//   fclose(pFin);
//   return(NO_POLSARPROSIM_ERRORS);
//}

/******************************************************/
/* This routine checks forest primitives read from    */
/* the input file titled: $prefix_canopy.txt          */
/* using Input_PolSARproSim_Forest()                  */
/******************************************************/
int		Check_PolSARproSim_Forest		(PolSARproSim_Record *pPR)
{
   int itree;
   
#ifdef VERBOSE_POLSARPROSIM
   printf("\nTree#)\t\tspecies\t\tx-loc\t\ty-loc\t\theight\t\tdbh\t\tradius\t\tdepth\t\tdry depth\n");  
#endif
   fprintf(pPR->pLogFile, "\nTree#)\t\tspecies\t\tx-loc\t\ty-loc\t\theight\t\tdbh\t\tradius\t\tdepth\t\tdry depth\n");  
   
   
   for(itree=0;itree<pPR->Trees;itree++){
      
      /******************************************************/    
      /* Print the Forest primitives to stdout and logfile. */
      /* If not read from file, this printing is performed  */
      /* in shuffle.c                                       */
      /******************************************************/
      
#ifdef VERBOSE_POLSARPROSIM
      /* print forest primitives to stdout */
      printf("%4d)\t\t%d\t\t%.3lf\t\t%.3lf\t\t%.3lf\t\t%.3lf\t\t%.3lf\t\t%.3lf\t\t%.3lf\n", itree, pPR->Tree_Location[itree].species, pPR->Tree_Location[itree].x, pPR->Tree_Location[itree].y, pPR->Tree_Location[itree].height, pPR->Tree_Location[itree].dbh, pPR->Tree_Location[itree].radius, pPR->Tree_Location[itree].canopy_depth,pPR->Tree_Location[itree].canopy_dry_depth);
#endif
      /* print forest primitives to logfile */
      fprintf(pPR->pLogFile, "%4d)\t\t%d\t\t%.3lf\t\t%.3lf\t\t%.3lf\t\t%.3lf\t\t%.3lf\t\t%.3lf\t\t%.3lf\n", itree, pPR->Tree_Location[itree].species, pPR->Tree_Location[itree].x, pPR->Tree_Location[itree].y, pPR->Tree_Location[itree].height, pPR->Tree_Location[itree].dbh, pPR->Tree_Location[itree].radius, pPR->Tree_Location[itree].canopy_depth, pPR->Tree_Location[itree].canopy_dry_depth);  
      
      
      /* Some sensible checks on forest primitives    */ 
      
      if(fabs(pPR->Tree_Location[itree].x) > fabs(pPR->Lx/2) ){
         printf("ERROR: Bad Tree description (x-position outside image) for tree no.: %d\n", itree);
         exit(0); /* these errors should be bad enough to quit program */
      }
      if(fabs(pPR->Tree_Location[itree].y) > fabs(pPR->Ly/2) ){
         printf("ERROR: Bad Tree description (y-position outside image) for tree no.: %d\n", itree);
         exit(0); /* these errors should be bad enough to quit program */
      }
      if(pPR->Tree_Location[itree].height < DBL_EPSILON)  {
         printf("ERROR: Bad Tree description (height <=0) for tree no.: %d\n", itree);
         exit(0); /* these errors should be bad enough to quit program */
      }
      if(pPR->Tree_Location[itree].radius < DBL_EPSILON)  {
         printf("ERROR: Bad Tree description (canopy radius <=0) for tree no.: %d\n", itree);
         exit(0); /* these errors should be bad enough to quit program */
      }
      if(pPR->Tree_Location[itree].canopy_depth < DBL_EPSILON)  {
         printf("ERROR: Bad Tree description (canopy depth<=0) for tree no.: %d\n", itree);
         exit(0); /* these errors should be bad enough to quit program */
      }
      if(pPR->Tree_Location[itree].canopy_depth+pPR->Tree_Location[itree].canopy_dry_depth > pPR->Tree_Location[itree].height)  {
         printf("ERROR: Bad Tree description (canopy depth  + canopy dry depth > tree height) for tree no.: %d\n", itree);
         exit(0); /* these errors should be bad enough to quit program */
      }
      if(pPR->Tree_Location[itree].species < 0 || pPR->Tree_Location[itree].species > 4)  { /* For now keep it to 4, should change to > pPR->Nspecies once all is integrated */ 
         printf("ERROR: Bad Tree description (species < 1 or >4) for tree no.: %d\n", itree);
         exit(0); /* these errors should be bad enough to quit program */
      }
      if(pPR->Tree_Location[itree].dbh < DBL_EPSILON)  {
         printf("ERROR: Bad Tree description (dbh <=0) for tree no.: %d\n", itree);
         exit(0); /* these errors should be bad enough to quit program */
      }
   }
   return(NO_POLSARPROSIM_ERRORS);
}

/********************************************************/ 
/* This routine reads forest primitives from            */
/* the XML version of the input file                    */
/********************************************************/
int		Input_PolSARproSim_Forest		(PolSARproSim_Record *pPR)
{
	xmlDocPtr 	doc;
	xmlNodePtr 	cur;
	int         treecnt       = 0;
   int         meta_errflag  = 0;
   int         itree;
   
   double      mean_tree_height  = 0;       
   double      mean_crown_radius = 0;
   double      max_tree_y        = 0;
   double      max_tree_x        = 0;
   double      max_tree_height   = 0;
   double      max_crown_radius  = 0;
   
   
   
   /* Read in the XML file */
	doc = xmlParseFile(pPR->ForestData);
	
	if (doc == NULL ) {
		fprintf(stderr,"ERROR: Forest XML file not parsed successfully. \n");
		exit(0);
	}
	
   /* get the root element */
	cur = xmlDocGetRootElement(doc);
	/* exit PolSARproSim if XML document is empty */
	if (cur == NULL) {
		fprintf(stderr,"ERROR: Empty XML Forest file\n");
		xmlFreeDoc(doc);
		exit(0);
	}
	/* exit PolSARproSim if root tag isn't <forest> */
	if (xmlStrcmp(cur->name, (const xmlChar *)FOREST_XMLTAG)) {
		fprintf(stderr,"ERROR: Forest XML file of the wrong type, root node != forest\n");
		xmlFreeDoc(doc);
		exit(0);
	}
	/* Parse the meta data tag <meta> */
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {	
		if ((!xmlStrcmp(cur->name, (const xmlChar *)META_XMLTAG))){
         parse_XML_meta_tag (doc, cur, pPR);
         meta_errflag  = 1;
		}
      cur=cur->next;
   }
   
   /* Exit PolSARproSim if <meta> tag not found */
   if(!meta_errflag) {
      fprintf(stderr, "ERROR: <meta> tag not found in forest XML file. \n");
      exit(0);
   }
   
   
   /* Allocate space in memory for Tree_Location structure*/
   pPR->Tree_Location      = (TreeLoc*) calloc (pPR->Trees, sizeof(TreeLoc));
   
   /* Parse the tree tags <tree> */
   cur = xmlDocGetRootElement(doc);
	cur = cur->xmlChildrenNode;
   /* Read the first N trees, where N = pPR->Trees, set by <num_trees> in <meta> */
   while (cur != NULL && treecnt < pPR->Trees) {	
      if ((!xmlStrcmp(cur->name, (const xmlChar *)TREE_XMLTAG))){
         /* printf("Tree number %d\n", treecnt); */
         parse_XML_tree_tag (doc, cur, pPR, treecnt);
         treecnt++;
      }
		cur = cur->next;
	}
   
   /* Okay this will not happen, but check it anyway */
	if(treecnt < pPR->Trees) {
		printf("WARNING: metadata tree count and number of tree entries in forest XML file do not match\n");
		printf("Updating tree count to %d\n", treecnt);
		pPR->Trees = treecnt;
	}		 
   
   /* Compute supplementary parameters */
   for (itree=0; itree<pPR->Trees; itree++) {
      
      /**********************************************************/
      /* Estimate mean crown radius, mean tree height,          */
      /* stand area, stand radius                               */
      /**********************************************************/
      
      mean_crown_radius     = mean_crown_radius + pPR->Tree_Location[itree].radius;
      mean_tree_height      = mean_tree_height  + pPR->Tree_Location[itree].height;
      max_tree_y            = MAX(max_tree_y, fabs(pPR->Tree_Location[itree].y));
      max_tree_x            = MAX(max_tree_x, fabs(pPR->Tree_Location[itree].x));   
      max_tree_height       = MAX(max_tree_height,pPR->Tree_Location[itree].height);
      max_crown_radius      = MAX(max_crown_radius, pPR->Tree_Location[itree].radius);
      
   }
   
   /**********************************************************/
   /* Fill in the Forest attributes section of Master Record */
   /**********************************************************/
   
   pPR->max_tree_height    = max_tree_height; /* Added this field for Attenuation Map changes */
   pPR->mean_tree_height   = mean_tree_height/pPR->Trees;
   pPR->mean_crown_radius  = mean_crown_radius/pPR->Trees;
   pPR->Stand_Radius       = MAX(max_tree_y, max_tree_x);
   pPR->Stand_Area         = DPI_RAD * pPR->Stand_Radius * pPR->Stand_Radius;
   
   pPR->Layover_Distance   = pPR->max_tree_height / tan(pPR->incidence_angle[0]);
   pPR->Shadow_Distance    = pPR->max_tree_height * tan(pPR->incidence_angle[0]);
   pPR->Gap_Distance       = RESOLUTION_GAP_SIZE * (pPR->azimuth_resolution + pPR->ground_range_resolution[0])/2.0;
  // pPR->Lx                 = 2.0*(pPR->Stand_Radius+pPR->Gap_Distance+pPR->mean_crown_radius);
  /* if the forest has a massive crown at the edge and the rest of the crowns are tiny, the above  */
  /* statement causes gap problems, so have to rely on max_crown_radius instead                    */
   pPR->Lx                 = 2.0*(pPR->Stand_Radius+pPR->Gap_Distance+max_crown_radius);
   pPR->Ly                 = pPR->Lx + pPR->Layover_Distance+pPR->Shadow_Distance;
   pPR->Area               = pPR->Lx*pPR->Ly;
   pPR->Hectares				= pPR->Area/10000.0;
   
   
   /**********************************/
   /* Calculate SAR image dimensions */
   /**********************************/
   
   pPR->nx                 = (int) (pPR->Lx / pPR->deltax) + 1;
   pPR->nx                 = 2*((int)(pPR->nx/2))+1;
   pPR->deltax             = pPR->Lx/pPR->nx;
   pPR->ny                 = (int) (pPR->Ly / pPR->deltay) + 1;
   pPR->ny                 = 2*((int)(pPR->ny/2))+1;
   pPR->deltay             = pPR->Ly/pPR->ny;
   
   printf("Done reading canopy primitives from file: %s\n",pPR->ForestData); 
   
	xmlFreeDoc(doc);
   return(NO_POLSARPROSIM_ERRORS);
   
}


/****************************************************************/
/* Removes leading and trailing white spaces from text string   */
/*                                                              */
/* copied from the internet                                     */
/****************************************************************/
char  *trimwhitespace (char *str)
{
   char *end;
   
   /* Trim leading space         */
   while(isspace(*str)) str++;
   if(*str == 0)  /* All spaces? */
      return str;
   /* Trim trailing space        */
   end = str + strlen(str) - 1;
   while(end > str && isspace(*end)) end--;
   /* Write new null terminator  */
   *(end+1) = 0;
   return str;
}

/****************************************************************/
/* Parses the Meta tag in the forest XML file                   */
/*                                                              */
/****************************************************************/
void  parse_XML_meta_tag    (xmlDocPtr doc, xmlNodePtr cur, PolSARproSim_Record *pPR) 
{
	xmlChar *key;
   int num_trees_errflag =0;
   
   /* Allocate space for the biome field in the Master Record */  
	pPR->biome = (char*) calloc (80, sizeof(char));
   
	cur = cur->xmlChildrenNode;
   /* loop through the tags in <meta> and read values */
	while (cur != NULL) {
      /* Read the number of trees in forest form <trees> tag */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)META_TREES_XMLTAG))) {
         key               = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         pPR->Trees        = (int)atoi((const char*)key);
         num_trees_errflag = 1;
         xmlFree(key);
      }
      /* Read the forest biome from the <biome> tag */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)META_BIOME_XMLTAG))) {
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         strcpy(pPR->biome, trimwhitespace((char*)key));
         xmlFree(key);
      }
      cur = cur->next;
	}
   
   if(!num_trees_errflag){
      fprintf(stderr, "ERROR: <num_trees> tag not found in Forest XML file. \n");
      exit(0);
   }
   return;
}

/****************************************************************/
/* Parses the tree tag in the forest XML file                   */
/*                                                              */
/****************************************************************/
void  parse_XML_tree_tag    (xmlDocPtr doc, xmlNodePtr cur, PolSARproSim_Record *pPR, int itree) 
{
	xmlChar *key;
   
   /* Parameters */
   int      species_code;           /* species number 0:hedge, 1-3 Pine, 4 Deciduous   */
   char     species_name[SPECNAME_MAX_STRSIZE];   /* species name, e.g. ACRU for Acer Rubrum         */
   double   tree_x;                 /* x coordinate location of tree                   */
   double   tree_y;                 /* y-coordinate locaiton of tree                   */
   double   tree_height;            /* max tree height [m]                             */
   double   canopy_radius;          /* canopy radius in x-y plane [m]                  */
   double   canopy_depth;           /* canopy depth [m]                                */
   double   canopy_dry_depth;       /* canopy dry depth [m]                            */
   double   dbh;                    /* diameter at breast height for tree              */
   int      ispecies;               /* species loop variable                           */
   
   /* ERROR FLAGS */
   int    tree_height_errflag       = 0;
   int    tree_species_errflag      = 0;
   int    x_location_errflag        = 0;
   int    y_location_errflag        = 0;
   int    canopy_radius_errflag     = 0;
   int    canopy_depth_errflag      = 0;
   int    canopy_dry_depth_errflag  = 0;
   int    stem_diameter_errflag     = 0;
   
   
   /* go to the right XML tag -- all tags inside <tree> in this case   */
	cur = cur->xmlChildrenNode;
   /* go through the tags inside <tree> and read the values            */
	while (cur != NULL) 
   {
      /* Get tree heights from <tree_height> tag    */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)TREE_HEIGHT_XMLTAG))) {
         key                     = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         tree_height             = (double)atof((const char*)key);
         tree_height_errflag     = 1;
         //printf("\tTree Height\t%9.3f\t[m]\n", atof((const char*)key));
         xmlFree(key);
      }
      
      /* Get canopy radius from <canopy_radis> tag  */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)CANOPY_RADIUS_XMLTAG))) {
         key                     = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         canopy_radius           = (double)atof((const char*)key);
         canopy_radius_errflag   = 1;
         //printf("\tCanopy Radius\t%9.3f\t[m]\n", atof((const char*)key));
         xmlFree(key);
      }
      /* How it ought to be -- note species must be a string that one looks up in a separate file */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)TREE_SPECIES_XMLTAG))) {
         key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         //printf("\tSpecies\t%9s\n", trimwhitespace((char*)key));
         strcpy(species_name, trimwhitespace((char*)key));
         tree_species_errflag  = 1;
         xmlFree(key);
      }
      /* Get x-axis location of tree from <x-location> tag  */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)X_LOCATION_XMLTAG))) {
         key                   = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         tree_x                = (double)atof((const char*)key);
         x_location_errflag    = 1;
         /* printf("\tX-Location\t%9.3f\t[m]\n", atof((const char*)key)); */
         xmlFree(key);
         
      }
      /* Get y-axis location of tree from <y-location> tag  */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)Y_LOCATION_XMLTAG))) {
         key                   = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         tree_y                = (double)atof((const char*)key);
         y_location_errflag    = 1;
         /*printf("\tY-Location\t%9.3f\t[m]\n", atof((const char*)key));*/
         xmlFree(key);
         
      }
      /* Get stem diameter of tree from <stem_diameter> tag */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)STEM_DIAMETER_XMLTAG))) {
         key                   = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         dbh                   = (double) atof((const char*)key);
         stem_diameter_errflag = 1;
         /* printf("\tStem Diameter\t%9.3f\t[m]\n", atof((const char*)key)); */
         xmlFree(key);
         
      }
      /* Get the live canopy depth of tree from <canopy_depth> tag  */ 
      if ((!xmlStrcmp(cur->name, (const xmlChar *)CANOPY_DEPTH_XMLTAG))) {
         key                   = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         canopy_depth          = (double) atof((const char*)key);
         canopy_depth_errflag  = 1;
         /* printf("\tCanopy Depth\t%9.3f\t[m]\n", atof((const char*)key)); */
         xmlFree(key);
         
      }
      /* Get the dead/dry canopy depth of tree from <canopy_dry_depth> tag */
      if ((!xmlStrcmp(cur->name, (const xmlChar *)CANOPY_DRY_DEPTH_XMLTAG))) {
         key                   = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
         canopy_dry_depth      = (double) atof((const char*)key);
         canopy_dry_depth_errflag  = 1;
         /* printf("\tCanopy Dry-depth%9.3f\t[m]\n", atof((const char*)key)); */
         xmlFree(key);
         
      }
      cur = cur->next;
	}
   /* exit the program if one of the entries in a tree does not exist */
   if(!(canopy_dry_depth_errflag && tree_height_errflag && tree_species_errflag && canopy_depth_errflag && canopy_radius_errflag && stem_diameter_errflag && x_location_errflag && y_location_errflag)){
      printf("ERROR: Forest XML file does not contain one or more necessary parameters in tree # %d\n", itree);
      exit(0);
   }
   
   /******************************************************/
   /* search the species database for this species name  */
   /* and assign that index as the species code in the   */
   /* tree location structure. This connects the two     */
   /* databases (Tree_Location and SpeciesDataBase)      */
   /******************************************************/
   tree_species_errflag = 0;
   for(ispecies = 0; ispecies<pPR->Nspecies;ispecies++){
      if(!strcmp(species_name, pPR->SpeciesDataBase[ispecies].species_name)){
         species_code = ispecies;
         pPR->SpeciesDataBase[ispecies].Trees++;
         tree_species_errflag = 1;
      }
   }
   /* exit the program if the tree species in forest data is not found in species database */
   if(!tree_species_errflag){
      fprintf(stderr, "ERROR: Information for species of tree # %d (%s) not found in species database\n", itree,species_name);
      fprintf(stderr, "\tEither check the spelling or at least provide this information for %s in %s\n", species_name, pPR->SpeciesData);
      fprintf(stderr, "\t\t<%s>\t<category> [deciduous/coniferous/etc.] </category>\t</%s>\n\n", species_name, species_name);
      exit(0);
   } 
   
   /* Populate the Tree_Location structure with the parsed values */
   pPR->Tree_Location[itree].x                 = tree_x;
   pPR->Tree_Location[itree].y                 = tree_y;
   pPR->Tree_Location[itree].species           = species_code;
   pPR->Tree_Location[itree].height            = tree_height;
   pPR->Tree_Location[itree].dbh               = dbh;
   pPR->Tree_Location[itree].radius            = canopy_radius;
   pPR->Tree_Location[itree].canopy_depth      = canopy_depth;
   pPR->Tree_Location[itree].canopy_dry_depth  = canopy_dry_depth;
   
   
   return;
}









