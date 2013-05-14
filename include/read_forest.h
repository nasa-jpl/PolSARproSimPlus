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
 * Module      : read_forest.h
 * Revision    : Version 1.0 
 * Date        : July, 2012
 * Notes       : Procedure prototype for reading parameter file by keyword
 */


#ifndef _read_forest_h
#define _read_forest_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include "PolSARproSim_Structures.h"
#include "PolSARproSim_Definitions.h"
#include "Trig.h"
#include <ctype.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "read_allometry.h"

#define FOREST_XMLTAG             "forest"
#define META_XMLTAG               "meta"
#define TREE_XMLTAG               "tree"
#define META_TREES_XMLTAG         "num_trees"
#define META_BIOME_XMLTAG         "biome"
#define TREE_HEIGHT_XMLTAG        "tree_height"
#define CANOPY_RADIUS_XMLTAG      "canopy_radius"
#define STEM_DIAMETER_XMLTAG      "stem_diameter"
#define X_LOCATION_XMLTAG         "x_location"
#define Y_LOCATION_XMLTAG         "y_location"
#define CANOPY_DEPTH_XMLTAG       "canopy_depth"
#define CANOPY_DRY_DEPTH_XMLTAG   "dry_depth"
#define TREE_SPECIES_XMLTAG       "species"


#define FOREST_READLINE_BUFFER 256



int		Input_PolSARproSim_Forest     (PolSARproSim_Record *pPR);
int		Check_PolSARproSim_Forest     (PolSARproSim_Record *pPR);
char     *trimwhitespace               (char *str);
void     parse_XML_meta_tag            (xmlDocPtr doc, xmlNodePtr cur, PolSARproSim_Record *pPR);
void     parse_XML_tree_tag            (xmlDocPtr doc, xmlNodePtr cur, PolSARproSim_Record *pPR, int itree);

#endif
