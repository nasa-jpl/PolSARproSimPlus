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
/* This program is distributed in the hope that it will be useful,		*/
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
 * Author      : Mark L. Williams
 * Module      : PolSARproSim_Structures.h
 * Revision    : Version C1b 
 * Date        : September, 2007
 * Notes       : Structures for PolSARproSim
 */
#ifndef __POLSARPROSIM_STRUCTURES_H__
#define __POLSARPROSIM_STRUCTURES_H__

#include	"SarIMage.h"
#include	"PolSARproSim_Definitions.h"
#include	"Perspective.h"
#include	"LightingMaterials.h"
#include	"d33Matrix.h"
#include	"Complex.h"

/****************************************/
/* Attenuation Map structure definition */
/****************************************/

typedef struct attnmap_tag {
   long           n;
   int            Nx;
   int            Ny;
   int            Nz;
   double			Ax;
   double			Ay;
   double			Az;
   double			dx;
   double			dy;
   double			dz;
   double			*pDirectH;
   double			*pDirectV;
   double			*pBounceH;
   double			*pBounceV;
   int            Nds;
   double			Ads;
   double			dds;
   double			*pDirectShortH;
   double			*pDirectShortV;
} AttenuationMap;

/********************************/
/* TreeLoc structure definition */
/********************************/

typedef struct treeloc_tag {
   double			x;                         /* x-axis location                                             */
   double			y;                         /* x-axis location                                             */
   double			height;                    /* individual tree height                                      */
   double			radius;                    /* individual crown radius                                     */
   int            species;                   /* individual tree species    --RAedit                         */
   double         dbh;                       /* individual tree dbh        --RAedit                         */
   double         canopy_depth;              /* individual canopy depth    --RAedit                         */
   double         canopy_dry_depth;          /* individual dry canopy depth  --RAedit                       */
} TreeLoc;

/**********************************/
/* Allometry structure definition */
/**********************************/

typedef struct allometry_tag {
   char           *species_name;             /* name of species (a text identifier)                         */
   int            category;                  /* Generic species category (coniferous/deciduous)             */
   int            Trees;                     /* the number of trees in the forest of this species           */
   int            live_crown_shape;          /* Shape of the living crown (Conical/Spheroid/cylindrical)    */
   int            dry_crown_shape;           /* Shape fo the dry crown (Conical/Spheroid/Cylindrical)       */
   double         live_crown_depth_factor;   /* fraction of live crown depth at which crown radius is max.  */
   double         dry_crown_depth_factor;    /* fraction of dry crown depth at which crown radius is max.   */
   double         crown_live_alpha;          /* to est. lcdepth as fn of hgt (unused if given in treeloc)   */
   double         crown_dry_alpha;           /* to est. dcdepth as fn of hgt (unused if given in treeloc)   */
   double         crown_radius_factor;       /* to est. cr. rad. as fn of hgt (unused if given in treeloc)  */
   double         stem_start_radius_factor;  /* to est. stem rad. as fn of hgt (unused if given in treeloc) */
   double         stem_max_angle;            /* maximum stem angle (from vertical) in degrees               */
   double         stem_end_radius_factor;    /* determines end radius of tree stem as a function of height  */
   double         stem_tropism_factor;       /* determines the stem tropism                                 */
   double         stem_lamdacx_stdev;        /* stdev of curvature wavelength in x-direction                */
   double         stem_lamdacx_mean;         /* mean of curvature wavelength in x-direction                 */
   double         stem_lamdacy_stdev;        /* stdev of curvature wavelength in y-direction                */
   double         stem_lamdacy_mean;         /* mean of curvature wavelength in y-direction                 */
   double         stem_gamma_stdev;          /* stdev of curvature scale-factor                             */
   double         stem_gamma_mean;           /* mean of curvature scale-factor                              */
   double         stem_moisture;             /* fractional moisture of stem                                 */
   double         stem_tropism_theta;        /* polar angle (theta) of the stem tropism direction           */
   double         stem_tropism_phi;          /* azimuthal angle (phi) of the stem tropism direction         */
   double         primary_avg_polar_angle;   /* mean polar angle (theta) of the primary branches            */
   double         primary_std_polar_angle;   /* standard deviation of primary polar angle                   */
   double         primary_layer_density;     /* number of primary layers per unit canopy depth              */
   int            primary_avg_sections;      /* average number of sections per layer of primary branches    */
   double         primary_azimuth_factor;    /* azimuth angle std factor for primary braches                */
   double         primary_radius_A;          /* quadratic coefficient of primary radius function            */
   double         primary_radius_B;          /* linear coefficient of the primary radius function           */
   double         primary_radius_C;          /* constant coefficient of the primary radius function         */
   double         primary_tropism_factor;    /* determines the primary tropism                              */
   double         primary_tropism_theta;     /* polar angle (theta) of the primary tropism direction        */
   double         primary_tropism_phi;       /* azimuthal angle (phi) of the primary tropism direction      */
   double         primary_lamdacx_stdev;     /* stdev of curvature wavelength in x-direction                */
   double         primary_lamdacx_mean;      /* mean of curvature wavelength in x-direction                 */
   double         primary_lamdacy_stdev;     /* stdev of curvature wavelength in y-direction                */
   double         primary_lamdacy_mean;      /* mean of curvature wavelength in y-direction                 */
   double         primary_gamma_stdev;       /* stdev of primary branch curvature scale-factor              */
   double         primary_gamma_mean;        /* mean of primary branch curvature scale-factor               */
   double         primary_live_moisture;     /* fractional moisture of living primary branches              */
   double         primary_dry_moisture;      /* fractional moisture of dry primary branches                 */
   double         primary_dry_density;       /* number of dry primary layers per unit dry canopy depth      */
   int            primary_dry_sections;      /* number of sections per layer of dry primary branches        */
   double         secondary_number_slope;    /* slope of linear fn. determining no. of secondary branch     */
   double         secondary_number_intercept;/* intercept of linear fn. determining no. of secondary branch */
   double         secondary_offset_fraction; /* fractional offset of secondary start location (tmin)        */
   double         secondary_avg_polar_angle; /* average polar angle of secondary branches                   */
   double         secondary_std_polar_angle; /* std dev of the polar angle of secondary branches            */
   double         secondary_radius_factor;   /* Start radius of secondaries as a factor of secondary radius */
   double         secondary_tropism_factor;  /* determines the secondary tropism                            */
   double         secondary_tropism_theta;   /* polar angle (theta) of the secondary tropism direction      */
   double         secondary_tropism_phi;     /* azimuthal angle (phi) of the secondary tropism direction    */
   double         secondary_lamdacx_stdev;   /* stdev of curvature wavelength in x-direction                */
   double         secondary_lamdacx_mean;    /* mean of curvature wavelength in x-direction                 */
   double         secondary_lamdacy_stdev;   /* stdev of curvature wavelength in y-direction                */
   double         secondary_lamdacy_mean;    /* mean of curvature wavelength in y-direction                 */
   double         secondary_gamma_stdev;     /* stdev of secondary branch curvature scale-factor            */
   double         secondary_gamma_mean;      /* mean of secondary branch curvature scale-factor             */
   double         tertiary_min_radius;       /* minimum radius of tertiary branches                         */
   double         tertiary_min_length;       /* minimum length of tertiary branches                         */
   double         tertiary_volume_fraction;  /* fraction of the crown volume occupied by tertiary branches  */
   double         tertiary_number_factor;    /* scale factor to determine maximum tertiary number           */
   double         tertiary_moisture;         /* fractional moisture in tertiary branches                    */
   int            leaf_shape;                /* leaf shape code, either needle or broadleaf                 */
   double         leaf_width_mean;           /* mean leaf width                                             */
   double         leaf_width_stdev;          /* standard deviation of leaf width                            */
   double         leaf_height_mean;          /* mean leaf height                                            */
   double         leaf_height_stdev;         /* standard deviation of leaf height                           */
   double         leaf_thickness_mean;       /* mean leaf thickness                                         */
   double         leaf_thickness_stdev;      /* standard deviation of leaf thickness                        */
   double         leaf_volume_fraction;      /* fraction of the crown volume occupied by leaves             */
   double         leaf_number_factor;        /* scale factor to determine maximum number of leaves          */
   double         leaf_moisture;             /* fractional moisture in leaves                               */

} Allometry;

/**************************************/
/* Master record structure definition */
/**************************************/

typedef struct polsarprosim_record_tag {
   /****************/
   /* File handles */
   /****************/
   FILE           *pOutputFile;           /* User required output goes here                              */
   FILE           *pLogFile;					/* Log file debugging output goes here                         */
   /*******************************/
   /* Random number sequence seed */
   /*******************************/
   int            seed;                   /* From which all else follows                                 */
   /***************************************************/
   /* Variables governing SAR image area and geometry */
   /***************************************************/
   int            Tracks;						/* Number of tracks requested for interferometry               */
   double			*slant_range;				/* Slant range from aperture centre to scene centre in metres	*/
   double			*incidence_angle;			/* Global incidence angle stored in radians (input in degrees)	*/
   int            current_track;				/* Current track number                                        */
   double			Lx;							/* Extent of SAR image area in azimuth in metres               */
   double			Ly;							/* Extent of SAR image area in ground range in metres          */
   double			Area;                   /* SAR image area in square metres                             */
   double			Stand_Area;					/* Area of forest stand in square metres < LxLy                */
   double			Layover_Distance;			/* L = h/tan_thetai, layover of forest towards radar in metres	*/
   double			Shadow_Distance;			/* S = h*tan_thetai, Shadow distance behind forest in metres	*/
   double			Gap_Distance;				/* This distance in metres leaves a border in the images       */
   double			Stand_Radius;				/* SA = PIR^2, the radius of the area containing trees in m.	*/
   double			Hectares;					/* SAR image area in Hectares                                  */
   int            nx;							/* SAR image dimension in azimuth in pixels                    */
   int            ny;							/* SAR image dimension in ground range in pixels               */
   double			deltax;						/* Azimuth pixel dimension in metres                           */
   double			deltay;						/* Ground range pixel dimension in metres                      */
   /***********************************/
   /* Other SAR instrument properties */
   /***********************************/
   double			wavelength;             /* Wavelength in metres at centre frequency                    */
   double			frequency;              /* Centre frequency in Gigahertz.                              */
   double			k0;                     /* Free space wavenumber in rads. inverse metres               */
   double			azimuth_resolution;		/* Width at half height power of PSF in azimuth in metres      */
   double			slant_range_resolution;	/* Width at half height power of PSF in slant range in metres  */
   double			*ground_range_resolution;	/* Width at half height power of PSF in ground range in metres	*/
   double			f_azimuth;              /* Azimuth sampling frequency (ratio < 1.0)                    */
   double			f_ground_range;         /* Ground range sampling frequency (ratio < 1.0)               */
   /**************************************************/
   /* Variables governing large-scale ground surface */
   /**************************************************/
   double			large_scale_length;		/* Correlation length of large scale surface in metres         */
   double			large_scale_height_stdev;	/* Height standard deviation for large scale ground surface (m)	*/
   double			slope_x;                /* Underlying mean terrain slope in azimuth (ratio)            */
   double			slope_y;                /* Underlying mean terrain slope in ground range (ratio)       */
   SIM_Record     Ground_Height;          /* Float image of ground heights in the SAR frame in metres    */
   /**************************************************/
   /* Variables governing small-scale ground surface */
   /**************************************************/
   double			small_scale_length;			/* Correlation length of small-scale surface in metres      */
   double			small_scale_height_stdev;	/* Height standard deviation for small-scale ground surface (m)	*/
   Complex        ground_eps;             /* Soil dielectric permittivity                                */
   /******************************************/
   /* Variables governing forest description */
   /******************************************/
   char           *biome;                 /* Biome for this forest                               --RAedit*/
   int            species;                /* Species of tree (see PolSARproSim_Definitions.h)            */
   double			mean_tree_height;       /* User requested mean height of trees (allometric basis)      */
   double			mean_crown_radius;		/* Estimated using allometric and mean tree height             */
   double			close_packing_radius;	/* Fractional coverage is 0.907 with this radius               */
   int            max_tree_number;        /* Estimated from close packing fraction                       */
   int            max_trees_per_hectare;	/* Calculated from max_stem_number                             */
   int            req_trees_per_hectare;	/* Stand density requested by the user                         */
   double			trees_per_100m;         /* Number of trees per unit 100m length of forest              */
   TreeLoc        *Tree_Location;         /* List of tree locations, heights and crown radii in forest   */
   int            nTreex;                 /* Number of trees in azimuth direction                        */
   int            nTreey;                 /* Number of trees in ground range direction                   */
   int            Trees;                  /* Number of trees in the SAR image area                       */
   double			deltaTreex;             /* Azimuth tree separation in metres                           */
   double			deltaTreey;             /* Ground range tree separation in metres                      */
   double         max_tree_height;        /* Maximum height of tree in scene, for Attenuation Map DeltZ  */
   Allometry      *SpeciesDataBase;       /* Database of species attributes, read in from an input file  */
   Allometry      *CategoryDataBase;      /* Database of default species attributes, read in from input  */
   int            Nspecies;               /* Number of species in the species database file      --RAedit*/
   int            Ncategories;            /* Number of categories in the species database file   --RAedit*/
   
   /**********************************************/
   /* Variables governing short vegetation layer */
   /**********************************************/
   double			shrt_vegi_depth;        /* Depth of short vegetation layer in metres                   */
   double			shrt_vegi_stem_vol_frac;/* Volume fraction of short vegetation layer stems (ratio)     */
   double			shrt_vegi_leaf_vol_frac;/* Volume fraction of short vegetation layer stems (ratio)     */
   /********************************************/
   /* Variables governing forest graphic image */
   /********************************************/
   int            gnx;
   int            gny;
   /*******************************/
   /* Recovered forest properties */
   /*******************************/
//   double			primary_branch_length;	/* Mean primary branch length estimate in metres               */
//   double			primary_branch_radius;	/* Mean primary branch radius estimate in metres               */
//   double			secondary_branch_length;/* Mean secondary branch length estimate in metres             */
//   double			secondary_branch_radius;/* Mean secondary branch radius estimate in metres             */
//   double			tertiary_branch_length;	/* Mean tertiary branch length estimate in metres              */
//   double			tertiary_branch_radius;	/* Mean tertiary branch radius estimate in metres              */
   double			ShortVegi_stemL1;       /* Short vegetation depolarization factors for stems           */
   double			ShortVegi_stemL2;
   double			ShortVegi_stemL3;
   double			ShortVegi_leafL1;       /* Short vegetation depolarization factors for stems           */
   double			ShortVegi_leafL2;
   double			ShortVegi_leafL3;
//   double			Tertiary_branchL1;      /* Tertiary branch depolarization factors (unused after edits) */
//   double			Tertiary_branchL2;
//   double			Tertiary_branchL3;
   double			Tertiary_leafL1;        /* Tertiary leaf depolarization factors                        */
   double			Tertiary_leafL2;
   double			Tertiary_leafL3;
   /****************************/
   /* Effective permittivities */
   /****************************/
   Complex        e11_dry;
   Complex        e33_dry;
   Complex        e11_living;
   Complex        e33_living;
   Complex        e11_short;
   Complex        e33_short;
   /**************************/
   /* Effective wave vectors */
   /**************************/
   double			kro2;
   double			kro;
   Complex        ko2_living;
   Complex        koz2_living;
   Complex        *koz_living;            /* will be a vector of length pPR->Nspecies                    */
   Complex        ke2_living;
   Complex        kez2_living;
   Complex        *kez_living;            /* will be a vector of length pPR->Nspecies                    */
   Complex        ko2_dry;
   Complex        koz2_dry;
   Complex        *koz_dry;               /* will be a vector of length pPR->Nspecies                    */
   Complex        ke2_dry;
   Complex        kez2_dry;
   Complex        *kez_dry;               /* will be a vector of length pPR->Nspecies                    */
   Complex        ko2_short;
   Complex        koz2_short;
   Complex        koz_short;
   Complex        ke2_short;
   Complex        kez2_short;
   Complex        kez_short;
   /***********************************************************/
   /* Tertiary branch scattering model flag: 0 = GRG, 1 = INF */
   /***********************************************************/
   int            Grg_Flag;
   /*****************************/
   /* Attenuation lookup table  */
   /*****************************/
   AttenuationMap	Amap;
   /***************/
   /* SAR imagery */
   /***************/
   SIM_Record		HHimage;				/* HH SAR images are stored here                                  */
   SIM_Record		HVimage;				/* HV SAR images are stored here                                  */
   SIM_Record		VVimage;				/* VV SAR images are stored here                                  */
   double			xmid;					/* Used to calculate image array indices                          */
   double			ymid;					/* Used to calculate image array indices                          */
   double			psfaaz;           /* Point spread function azimuth parameter                        */
   double			*psfagr;				/* Point spread function ground range parameter                   */
   double			psfasr;				/* Point spread function slant range parameter                    */
   int            PSFnx;            /* Number of azimuth pixels either side of centre in PSF image		*/
   int            PSFny;				/* Number of range   pixels either side of centre in PSF image		*/
   double			HHsf;					/* Normalisation factor recovered from HH DG image                */
   double			HVsf;					/* Normalisation factor recovered from HH DG image                */
   double			VVsf;					/* Normalisation factor recovered from HH DG image                */
   double			PSFamp;				/* Scaling for the PSF to yield m.sq.pxl as backscattering coeff.	*/
   /***********************/
   /* File name variables */
   /***********************/
   char           *pInputDirectory;		/* Name of directory in which input parameter file is located		*/
   char           *pMasterDirectory;	/* Name of directory in which track0 output is written				*/
   char           *pSlaveDirectory;		/* Name of directory in which track1 output is written				*/
   char           *pFilenamePrefix;		/* Filename prefix for input, output and log files                */
   char           *HH_string;				/* Full filename for current track                                */
   char           *HV_string;				/* Full filename for current track                                */
   char           *VH_string;				/* Full filename for current track                                */
   char           *VV_string;				/* Full filename for current track                                */
   char           *ForestData;         /* Full filename for forest input file                            */
   char           *ForestOutput;       /* Full filename for forest output file                           */
   char           *SpeciesData;        /* Full filename for species database file                        */
   /**********************/
   /* Progress indicator */
   /**********************/
   int            progress;             /* Indicates progress of simulation on stdout                     */
   /*******************************************************************************************/
   /* Forest input flag: 0 = generate forest, 1 = input forest from Forest Data File --RAedit */
   /*******************************************************************************************/
   int            ForestInput_Flag;     /* If set to 1 forest parameters will be read from input file     */
   
} PolSARproSim_Record;

/*********************************/
/* TreeDisc structure definition */
/*********************************/

typedef struct treedisc_tag {
   TreeLoc        t;
   double         cost;
   int            nnlist[TREE_LOCATION_NEAREST_NEIGHBOURS];
} TreeDisc;

/**********************************************************/
/* Information for graphic drawing in a drawing structure */
/**********************************************************/

typedef struct drawing_record_tag {
   Perspective       *pP;
   Lighting_Record	*pL;
   d33Matrix         *pRx;
   d3Vector          *pTzy;
} Drawing_Record;

#endif
