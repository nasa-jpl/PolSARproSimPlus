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
 * Module      : Realisation.c
 * Revision    : Version C1b 
 * Date        : September, 2007
 *
 */
#include	"Realisation.h"

/***************************************/
/* Plant element polar angle generator */
/***************************************/

double		vegi_polar_angle				(void)
{
   double		theta	= acos (2.0*drand () - 1.0);
   return (theta);
}

// re-entrant version of vegi_polar_angle
double		vegi_polar_angle_r         (double randn)
{
   double		theta	= acos (2.0*randn - 1.0);
   return (theta);
}


/*****************************/
/* Tree realisation routines */
/*****************************/

void		Realise_Crown (Tree *pT, PolSARproSim_Record *pPR)
{
   Crown       c;
   int         live_crown_shape;    /* live crown shape  */
   int         dry_crown_shape;     /* dry crown shape   */
   double      l;       /* crown depth                   */
   double      r;       /* crown radius                  */
   double      e;     
   double		beta;    /* internal crown angle          */
   double		d1;      /* semi major axis of the crown  */
   double		d2;      /* semi minor axis of the crown  */
   double      d3;      /* truncation length of crown    */
   double      live_crown_depth_factor; /* canopy depth factor      */
   double      dry_crown_depth_factor;
   double      dry_crown_offset_factor;
   double      offset;
   d3Vector    base;    /* location of crown base */
   d3Vector    axis;    /* crown axis */
   
   /* initialise the crown */
   Create_Crown		(&c);

   /* read in species primitives */
   live_crown_shape        = pPR->SpeciesDataBase[pT->species].live_crown_shape; /* shape of live crown  */
   dry_crown_shape         = pPR->SpeciesDataBase[pT->species].dry_crown_shape;  /* shape of dry crown   */
   live_crown_depth_factor = pPR->SpeciesDataBase[pT->species].live_crown_depth_factor; /* cdf * depth = height of max radius */
   dry_crown_depth_factor  = pPR->SpeciesDataBase[pT->species].dry_crown_depth_factor; /* cdf * depth = height of max radius */
   dry_crown_offset_factor = pPR->SpeciesDataBase[pT->species].dry_crown_offset_factor; /* 0 = begin at end of dry crown, 1 = sit on the ground */
   /* determine the axis of the stem */
   axis  = Stem_Direction (pT, pPR);

   /******************************/
   /* Realise the living crown   */
   /******************************/
   
   /* read in living crown parameters */
   if(pPR->ForestInput_Flag == EXTERNAL_FOREST_DEFINITION) {
      l     = pT->canopy_depth;
   } else {
      l     = Realise_Living_Crown_Depth (pT, pPR);
      pT->canopy_depth = l;
   }
   r     = pT->radius;        /* canopy radius in meters       */
   
   d3    = l;
   d1    = live_crown_depth_factor * l;
   e     = sqrt (r*r + d1*d1);
   beta	= atan2 (r,d1);
   d1		= e*cos(beta);
   d2		= e*sin(beta);
      
   Create_d3Vector	(&base);
   base              = d3Vector_sum (pT->base, d3Vector_double_multiply (axis, pT->height-d3));
   Assign_Crown		(&c, live_crown_shape, beta, d1, d2, d3, base, axis, pPR->slope_x, pPR->slope_y);

   /* if crown shape is valid, add this crown to the head of the list */
   if(live_crown_shape != CROWN_NULL_SHAPE) {
      Crown_head_add	(&(pT->CrownVolume), &c);
   }

   /******************************/
   /* Realise the dry crown      */
   /******************************/
   
   /* read in dry crown parameters */
   if(pPR->ForestInput_Flag == EXTERNAL_FOREST_DEFINITION) {
      l          = pT->canopy_dry_depth;
   } else {
      l          = Crown_Fractional_Dry_Depth (pT, pPR)*(pT->height-l);
      if(dry_crown_shape != CROWN_NULL_SHAPE) {  
         pT->canopy_dry_depth = l;
      }else{
         pT->canopy_dry_depth = 0;
      }
   }
   r  = pT->radius;           /* canopy radius in meters -- maybe later this will be dry_canopy_radius */  

   d3    = l;
   d1    = dry_crown_depth_factor * l;
   e     = sqrt (r*r + d1*d1);
   beta	= atan2 (r,d1);
   d1		= e*cos(beta);
   d2		= e*sin(beta);
   
   base              = d3Vector_sum (pT->base, d3Vector_double_multiply (axis, pT->height-c.d3-d3));
   /* compute the offset for dry crown */
   offset            = dry_crown_offset_factor * (base.x[2] - pT->base.x[2]);
   base.x[2]         = base.x[2] - offset;
   Assign_Crown		(&c, dry_crown_shape, beta, d1, d2, d3, base, axis, pPR->slope_x, pPR->slope_y);

   /* if crown shape is valid, add this crown to the tail of the list */
   if(dry_crown_shape != CROWN_NULL_SHAPE) {  
      Crown_tail_add		(&(pT->CrownVolume), &c);
   }else{
      pT->CrownVolume.tail = NULL_PTR2CROWN;
   }
   Destroy_Crown		(&c);
   return;
}


void		Realise_Stem (Tree *pT, PolSARproSim_Record *pPR)
{
   const double	PI	= DPI_RAD;
   double			sr, er;
   d3Vector       z0;
   d3Vector       b0;
   Ray            r0;
   int            rtn_value;
   d3Vector       s1, s2;
   double			alpha1, alpha2;
   double			dp;
   double			phix, phiy, phicx, phicy;
   double			lamdacx, lamdacy, gamma;
   double			moisture;
   Complex        permittivity;
   Branch			Stem;
   d3Vector       p0;
   d3Vector       c1;
   double			p0dotz0;
   double			fp;
   double			ldenom;
   double			l;
   d3Vector       bt;
   d3Vector       adirn;
   
   sr             = Stem_Start_Radius			(pT, pPR);
   er             = Stem_End_Radius          (pT, pPR); 
   dp             = Stem_Tropism_Factor      (pT, pPR);
   fp             = dp/(2.0*sqrt(1.0-dp*dp));
   lamdacx        = Stem_Lamdacx             (pT, pPR);
   lamdacy        = Stem_Lamdacy             (pT, pPR);
   gamma          = Stem_Gamma               (pT, pPR);
   moisture       = Stem_Moisture				(pT, pPR);
   p0             = Stem_Tropism_Direction	(pT, pPR);
   permittivity	= vegetation_permittivity	(moisture, pPR->frequency);
   phix           = 2.0*PI*drand ();
   phiy           = 2.0*PI*drand ();
   phicx          = 2.0*PI*drand ();
   phicy          = 2.0*PI*drand ();
   Copy_d3Vector	(&z0, &(pT->CrownVolume.head->axis));
   Copy_d3Vector	(&b0, &(pT->base));
   adirn          = d3Vector_sum (z0, d3Vector_double_multiply (p0, fp));
   d3Vector_insitu_normalise (&adirn);
   Assign_Ray_d3V	(&r0, &b0, &adirn);
   rtn_value      = RayCrownIntersection (&r0, pT->CrownVolume.head, &s1, &alpha1, &s2, &alpha2);
   p0dotz0        = d3Vector_scalar_product (p0, z0);
   ldenom         = 1.0+fp*p0dotz0;
   if (rtn_value == NO_RAYCROWN_ERRORS) {
      if (s1.x[2] > s2.x[2]) {
         l        = d3Vector_scalar_product (d3Vector_difference (s1, b0), z0)/ldenom; 
      } else {
         l        = d3Vector_scalar_product (d3Vector_difference (s2, b0), z0)/ldenom;
      }
   } else {
      l           = pT->height;
   }
   Assign_Branch	(&Stem, sr, er, b0, z0, p0, dp, phix, phiy, phicx, phicy, lamdacx,
                   lamdacy, gamma, moisture, l, permittivity, (int) (pT->Stem.n + 1L), 0);
   /*****************/
   /* Test solution */
   /*****************/
   c1             = Branch_Crookedness (&Stem, 1.0);
   bt             = Branch_Centre (&Stem ,1.0);
   /**************************************/
   /* Add the stem to the tree stem list */
   /**************************************/
   Branch_head_add (&(pT->Stem), &Stem);
   return;
}

void		Realise_Primaries	(Tree *pT, PolSARproSim_Record *pPR)
{
   /***************************************************/
   /* Primary branch realisations for a generic tree  */
   /* based on parameters in the species xml file     */
   /***************************************************/
   Crown       *pC;
   int         Nlayers, i_layer;
   int         Nsections, i_section;
   double		t0, t1;
   double		delta_t, tb;
   d3Vector    b0;
   double		theta;
   double		delta_phi, phi;
   d3Vector    z0;
   double		sr, er;
   double		dp;
   double		lamdacx, lamdacy, gamma;
   double		phix, phiy, phicx, phicy;
   Complex     permittivity;
   d3Vector    p0;
   double		moisture;
   Ray         r0;
   int         rtn_value;
   d3Vector    s1, s2;
   double		alpha1, alpha2;
   Branch		Primary;
   d3Vector    c1;
   double		p0dotz0;
   double		fp;
   double		ldenom;
   double		l;
   d3Vector    bt;
   d3Vector    adirn;
   double		tbar;
   d3Vector    tree_top;
   double		max_height;
   double		pmy_height;
   double		dry_l;
   double		azimuth_offset;
   double      az_factor;
   double		theta_avg, theta_dlt;
   
   /**********************/
   /* Populate DRY crown */
   /**********************/
   
   
   if(pPR->SpeciesDataBase[pT->species].dry_crown_shape != CROWN_NULL_SHAPE){
 
      /* point to the dry crown parameters */
      pC          = pT->CrownVolume.tail;
 
      t0          = (pC->base.x[2]-pT->base.x[2])/pT->height;
      t1          = t0 + pC->d3/pT->height;

      /* read polar angle statistics from species database */
      theta_avg   = DEG_TO_RAD * pPR->SpeciesDataBase[pT->species].primary_dry_avg_polar_angle; 
      theta_dlt   = DEG_TO_RAD * pPR->SpeciesDataBase[pT->species].primary_dry_std_polar_angle;
      //theta       = theta_avg + theta_dlt; //basically the primary maximum polar angle so I don't have to code extra parameters
 
      
      /* calculate the number of layers based on layer density */
      Nlayers     = (int) (pPR->SpeciesDataBase[pT->species].primary_dry_density * pC->d3);
      if (Nlayers < 1) {
         Nlayers	= 1;
      }
      
      /* read the number of sections from species database */
      Nsections   = (int) pPR->SpeciesDataBase[pT->species].primary_dry_sections;
   
      /* read the azimuth angle scale factor */
      az_factor   = DEG_TO_RAD * pPR->SpeciesDataBase[pT->species].primary_azimuth_factor;
      
      delta_t     = (t1-t0)/Nlayers;
      tbar        = 0.5*(t0+t1);
      delta_phi	= 2.0*DPI_RAD/Nsections;
      dry_l       = pC->d2/cos(theta-DPI_RAD/2.0);
      for (i_layer=0; i_layer<Nlayers; i_layer++) {
         azimuth_offset	= 2.0*DPI_RAD*drand();
         for (i_section=0; i_section<Nsections; i_section++) {
            tb             = t0 + (i_layer+1)*delta_t - drand()*delta_t;
            b0             = Branch_Centre (pT->Stem.head, tb);
            theta          = theta_avg;
            theta          += (tbar-tb)*theta_dlt/(tbar-t0);
            phi            = i_section*delta_phi + delta_phi/2.0;
            //phi          += POLSARPROSIM_PINE001_PRIMARY_AZIMUTH_FACTOR*delta_phi*(drand()-0.5);
            phi            += az_factor*delta_phi*(drand()-0.5);
            phi            += azimuth_offset;
            z0             = Polar_Assign_d3Vector       (1.0, theta, phi);
            sr             = Primary_Radius              (pT, pPR, tb);                      
            er             = sr*pT->Stem.head->end_radius/pT->Stem.head->start_radius;
            dp             = Primary_Tropism_Factor      (pT, pPR);
            fp             = dp/(2.0*sqrt(1.0-dp*dp));
            p0             = Primary_Tropism_Direction	(pT, pPR);
            lamdacx        = Primary_Lamdacx             (pT, pPR);
            lamdacy        = Primary_Lamdacy             (pT, pPR);
            gamma          = Primary_Gamma               (pT, pPR);
            moisture       = Primary_Dry_Moisture        (pT, pPR);
            permittivity	= vegetation_permittivity     (moisture, pPR->frequency);
            phix           = 2.0*DPI_RAD*drand ();
            phiy           = 2.0*DPI_RAD*drand ();
            phicx          = 2.0*DPI_RAD*drand ();
            phicy          = 2.0*DPI_RAD*drand ();
            adirn          = d3Vector_sum (z0, d3Vector_double_multiply (p0, fp));
            d3Vector_insitu_normalise (&adirn);
            Assign_Ray_d3V	(&r0, &b0, &adirn);
            rtn_value      = RayCrownIntersection (&r0, pC, &s1, &alpha1, &s2, &alpha2);
            p0dotz0        = d3Vector_scalar_product (p0, z0);
            ldenom         = 1.0+fp*p0dotz0;
            if (rtn_value == NO_RAYCROWN_ERRORS) {
               if (alpha1 >= 0.0) {
                  l		= d3Vector_scalar_product (d3Vector_difference (s1, b0), z0)/ldenom;
               } else {
                  if (alpha2 >= 0.0) {
                     l		= d3Vector_scalar_product (d3Vector_difference (s2, b0), z0)/ldenom;
                  } else {
                     l = dry_l;
                  }
               }
            } else {
               l = dry_l;
            }
            Assign_Branch	(&Primary, sr, er, b0, z0, p0, dp, phix, phiy, phicx, phicy, lamdacx,
                            lamdacy, gamma, moisture, l, permittivity, (int) (pT->Stem.n + pT->Dry.n + 1L), 1);
            c1             = Branch_Crookedness (&Primary, 1.0);
            bt             = Branch_Centre (&Primary ,1.0);
            pmy_height     = d3Vector_scalar_product (bt, pT->Stem.head->z0);
            Branch_head_add (&(pT->Dry), &Primary);
         }
      }
   }
   /***************************/
   /* Populate living crown   */
   /***************************/
   
   if(pPR->SpeciesDataBase[pT->species].live_crown_shape != CROWN_NULL_SHAPE){
      /* point to the living crown parameters */
      pC          = pT->CrownVolume.head;   

      t0          = (pC->base.x[2]-pT->base.x[2])/pT->height;
      t1          = 1.0;

      /* read polar angle statistics from species database */
      theta_avg   = DEG_TO_RAD * pPR->SpeciesDataBase[pT->species].primary_avg_polar_angle; 
      theta_dlt   = DEG_TO_RAD * pPR->SpeciesDataBase[pT->species].primary_std_polar_angle;
      
      /* calculate the number of layers based on layer density */
      Nlayers     = (int) ((t1-t0) * pPR->SpeciesDataBase[pT->species].primary_layer_density * pC->d3);
      if (Nlayers < 1) {
         Nlayers	= 1;
      }
      /* read the number of primary sections */
      Nsections   = (int) pPR->SpeciesDataBase[pT->species].primary_avg_sections;
      
      /* read the azimuth angle scale factor */
      az_factor   = DEG_TO_RAD * pPR->SpeciesDataBase[pT->species].primary_azimuth_factor;
      
      delta_phi	= 2.0*DPI_RAD/Nsections;
      tbar        = 0.5*(t0+t1);
      delta_t     = (t1-t0)/Nlayers;
      tree_top    = Branch_Centre (pT->Stem.head, 1.0);
      max_height	= d3Vector_scalar_product (tree_top, pT->Stem.head->z0);
      
      /* loop through the layers and sections to populate the crown */
      for (i_layer=0; i_layer<Nlayers; i_layer++) {
         azimuth_offset    = 2.0*DPI_RAD*drand();
         for (i_section=0; i_section<Nsections; i_section++) {
            tb             = t0 + (i_layer+1)*delta_t - drand()*delta_t;
            b0             = Branch_Centre (pT->Stem.head, tb);
            theta          = theta_avg;
            theta          += (tbar-tb)*theta_dlt/(tbar-t0);
            phi            = i_section*delta_phi + delta_phi/2.0;
            phi            += az_factor*delta_phi*(drand()-0.5);
            phi            += azimuth_offset;
            z0             = Polar_Assign_d3Vector       (1.0, theta, phi);
            sr             = Primary_Radius              (pT, pPR, tb);       
            er             = sr*pT->Stem.head->end_radius/pT->Stem.head->start_radius;
            dp             = Primary_Tropism_Factor      (pT, pPR);
            fp             = dp/(2.0*sqrt(1.0-dp*dp));
            p0             = Primary_Tropism_Direction	(pT, pPR);
            lamdacx        = Primary_Lamdacx             (pT, pPR);
            lamdacy        = Primary_Lamdacy             (pT, pPR);
            gamma          = Primary_Gamma               (pT, pPR);
            moisture       = Primary_Moisture            (pT, pPR);
            permittivity	= vegetation_permittivity (moisture, pPR->frequency);
            phix           = 2.0*DPI_RAD*drand ();
            phiy           = 2.0*DPI_RAD*drand ();
            phicx          = 2.0*DPI_RAD*drand ();
            phicy          = 2.0*DPI_RAD*drand ();
            adirn          = d3Vector_sum (z0, d3Vector_double_multiply (p0, fp));
            d3Vector_insitu_normalise (&adirn);
            Assign_Ray_d3V	(&r0, &b0, &adirn);
            rtn_value      = RayCrownIntersection (&r0, pC, &s1, &alpha1, &s2, &alpha2);
            p0dotz0        = d3Vector_scalar_product (p0, z0);
            ldenom         = 1.0+fp*p0dotz0;
            if (rtn_value == NO_RAYCROWN_ERRORS) {
               if (alpha1*alpha2 < 0.0) {
                  if (alpha1 > 0.0) {
                     l		= d3Vector_scalar_product (d3Vector_difference (s1, b0), z0)/ldenom;
                  } else {
                     l		= d3Vector_scalar_product (d3Vector_difference (s2, b0), z0)/ldenom;
                  }
                  Assign_Branch	(&Primary, sr, er, b0, z0, p0, dp, phix, phiy, phicx, phicy, lamdacx, lamdacy, gamma,
                                  moisture, l, permittivity, (int) (pT->Stem.n + pT->Dry.n + pT->Primary.n + 1L), 1);
                  c1          = Branch_Crookedness (&Primary, 1.0);
                  bt          = Branch_Centre (&Primary ,1.0);
                  pmy_height	= d3Vector_scalar_product (bt, pT->Stem.head->z0);
                  if (pmy_height < max_height) {
                     Branch_head_add (&(pT->Primary), &Primary);
                  }
               }
            }
         }
      }
   }
   return;
}


void		Realise_Secondaries	(Tree *pT, PolSARproSim_Record *pPR)
{
   Branch		*pPrimary;
   int         i_primary, Nprimary;
   d3Vector    b0, b1;
   d3Vector    xp, yp, zp;
   double		theta, phi;
   double		primary_length;
   double		primary_start_radius;
   double		primary_end_radius;
   int         Ns;
   double		tmin, tmax;
   double		deltat, dt;
   double		l;
   double		subBeta;
   double		Cl			= POLSARPROSIM_PINE001_CLS;
   int         subShape;
   double		d1, d2, d3;
   Crown       subC;
   int         iSecondary;
   double		ts;
   d3Vector    z0;
   double		sr;
   double		er;
   double		dp, fp;
   d3Vector    p0;
   double		lamdacx, lamdacy;
   double		gamma;
   double		moisture;
   Complex     permittivity;
   double		phix, phiy, phicx, phicy;
   d3Vector    adirn;
   Ray         rb;
   int         rtn_value;
   d3Vector    s1, s2;
   double		alpha1, alpha2;
   double		p0dotz0, ldenom;
   Branch		secondary;
   d3Vector    ct, bt;
   double      thetas_avg, thetas_std;
   
   Crown       *pC;
   pC          = pT->CrownVolume.head; 
   subShape    = pC->shape;
   
   /******************/
   /* Initialisation */
   /******************/
   
   Create_Crown (&subC);
   
   /*************************************************/
   /* Populate living crown with secondary branches */
   /*************************************************/
   
   pPrimary	= pT->Primary.head;
   Nprimary	= pT->Primary.n;
   
   /* loop over primary branches */
   for (i_primary = 0; i_primary < Nprimary; i_primary++) {
      Copy_d3Vector (&b0, &(pPrimary->b0));
      b1                   = Branch_Centre (pPrimary, 1.0);
      zp                   = d3Vector_difference (b1, b0);
      primary_length       = zp.r;
      primary_start_radius	= pPrimary->start_radius;
      primary_end_radius	= pPrimary->end_radius;
      d3Vector_insitu_normalise (&zp);
      theta                = zp.theta;
      phi                  = zp.phi;
      yp                   = Cartesian_Assign_d3Vector (-sin(phi), cos(phi), 0.0);
      xp                   = Cartesian_Assign_d3Vector (-cos(theta)*cos(phi), -cos(theta)*sin(phi), sin(theta));
      
      tmin                 = pPR->SpeciesDataBase[pT->species].secondary_offset_fraction;
      tmax                 = MAX_SECONDARY_OFFSET_FRACTION;
      Ns                   = (int)((tmax - tmin)*Number_of_Secondaries (pT, pPR, primary_length));
       
      if (Ns >= 1) {
         deltat				= (tmax - tmin)/(double) Ns;
         dt                = 0.5*deltat;  
         thetas_avg        = DEG_TO_RAD * pPR->SpeciesDataBase[pT->species].secondary_avg_polar_angle;
         thetas_std        = DEG_TO_RAD * pPR->SpeciesDataBase[pT->species].secondary_std_polar_angle;
         
         /* compute parameters for the "sub-crown" of secondary branches */
         theta             = Gaussian_drand (thetas_avg, thetas_std, thetas_avg-thetas_std, thetas_avg+thetas_std);
         subBeta           = atan2 (Cl*sin(theta), 1.0-Cl*cos(theta));
         d1                = primary_length;
         d3                = d1;
         d2                = primary_length*sin(subBeta);
         Assign_Crown		(&subC, subShape, subBeta, d1, d2, d3, b0, zp, 0.0, 0.0);   
         
         /* loop over secondary branches */
         for (iSecondary = 0; iSecondary < Ns; iSecondary++) {
            ts					= tmin + iSecondary*deltat + (drand()-0.5)*dt;
            theta          = Gaussian_drand (thetas_avg, thetas_std, thetas_avg-thetas_std, thetas_avg+thetas_std);
            phi				= 2.0*DPI_RAD*drand();
            b0					= Branch_Centre (pPrimary, ts);
            z0					= d3Vector_double_multiply (zp, cos(theta));
            z0					= d3Vector_sum (z0, d3Vector_double_multiply (yp, sin(theta)*cos(phi)));
            z0					= d3Vector_sum (z0, d3Vector_double_multiply (xp, sin(theta)*sin(phi)));
            sr             = pPR->SpeciesDataBase[pT->species].secondary_radius_factor * Branch_Radius(pPrimary, ts);
            er					= 0.9205 * primary_end_radius;
            dp					= Secondary_Tropism_Factor (pT, pPR);
            fp					= dp/(2.0*sqrt(1.0-dp*dp));
            p0					= Secondary_Tropism_Direction	(pT, pPR);
            p0dotz0			= d3Vector_scalar_product (p0, z0);
            ldenom			= 1.0+fp*p0dotz0;
            lamdacx			= Secondary_Lamdacx (pT, pPR);
            lamdacy			= Secondary_Lamdacy (pT, pPR);
            gamma				= Secondary_Gamma (pT, pPR);
            moisture			= pPrimary->moisture;
            permittivity	= Copy_Complex (&(pPrimary->permittivity));
            phix				= 2.0*DPI_RAD*drand ();
            phiy				= 2.0*DPI_RAD*drand ();
            phicx				= 2.0*DPI_RAD*drand ();
            phicy				= 2.0*DPI_RAD*drand ();
            adirn				= d3Vector_sum (z0, d3Vector_double_multiply (p0, fp));
            d3Vector_insitu_normalise (&adirn);
            Assign_Ray_d3V	(&rb, &b0, &adirn);
            rtn_value		= RayCrownIntersection (&rb, &subC, &s1, &alpha1, &s2, &alpha2);
            if (rtn_value == NO_RAYCROWN_ERRORS) {
               if ((alpha1 > 0.0) && (alpha2 > 0.0)) {
                  if (alpha1 < alpha2) {
                     l		= d3Vector_scalar_product (d3Vector_difference (s1, b0), z0)/ldenom;
                  } else {
                     l		= d3Vector_scalar_product (d3Vector_difference (s2, b0), z0)/ldenom;
                  }
               } else {
                  if (alpha1 > 0.0) {
                     l		= d3Vector_scalar_product (d3Vector_difference (s1, b0), z0)/ldenom;
                  } else {
                     if (alpha2 > 0.0) {
                        l  = d3Vector_scalar_product (d3Vector_difference (s2, b0), z0)/ldenom;
                     }
                  }
               }
               if (!((alpha1 <= 0.0) && (alpha2 <= 0.0))) {
                  Assign_Branch	(&secondary, sr, er, b0, z0, p0, dp, phix, phiy, phicx, phicy,
                                  lamdacx, lamdacy, gamma, moisture, l, permittivity, 
                                  (int) (pT->Stem.n + pT->Dry.n + pT->Primary.n + pT->Secondary.n + 1L), pPrimary->id);
                  ct			= Branch_Crookedness (&secondary, 1.0);
                  bt			= Branch_Centre (&secondary ,1.0);
                  Branch_head_add (&(pT->Secondary), &secondary);
               }
            }
         }
      }
      pPrimary	= pPrimary->next;
   }
   Destroy_Crown (&subC);
   return;
}


void		Realise_Tertiaries (Tree *pT, PolSARproSim_Record *pPR)
{
   double         tertiary_branch_length;
   double         tertiary_branch_radius;
   long           n_Tertiary;
   int            tbn;
   Branch         tertiary_branch;
   double         theta, phi;
   d3Vector       z0;
   double         sr, er;
   double         dp;
   double         lamdacx, lamdacy, gamma;
   double         phix, phiy, phicx, phicy;
   Complex        permittivity;
   d3Vector       p0;
   double         moisture;
   Crown          *pC;
   long           iBranch;
   int            rtn_value;
   d3Vector       b0;
   double         scale_factor; /* for tertiary branch backscatter scaling */
   
   pC	= pT->CrownVolume.head;

   /* Estimating number of tertiaries based on this function instead, copied form Image_Tree_Direct/Bounce(); --RAedit */
   scale_factor               = Estimate_SAR_Tertiaries (pT, pPR, &n_Tertiary, &tertiary_branch_length, &tertiary_branch_radius);
   tbn                        = (int)n_Tertiary;
   pT->Tertiary.scale_factor  = scale_factor; /* to allow scaling when estimating backscatter */
   
   /***************************************/
   /* Loop to create tertiary branch list */
   /***************************************/
   Create_Branch (&tertiary_branch);
   for (iBranch=0L; iBranch < tbn; iBranch++) {
      /***********************************/
      /* Create and draw random branches */
      /***********************************/
      rtn_value         = Random_Crown_Location (pC, &b0);
      if (rtn_value == NO_RAYCROWN_ERRORS) {
         phi            = 2.0*DPI_RAD*drand();
         theta          = vegi_polar_angle ();
         z0             = Polar_Assign_d3Vector (1.0, theta, phi);
         sr             = tertiary_branch_radius;
         er             = tertiary_branch_radius;
         dp             = 0.0;
         p0             = Polar_Assign_d3Vector (1.0, theta, phi);
         lamdacx        = 1.0;
         lamdacy        = 1.0;
         gamma          = 0.0;
         moisture       = Tertiary_Branch_Moisture (pT, pPR);
         permittivity	= vegetation_permittivity (moisture, pPR->frequency);
         phix           = 0.0;
         phiy           = 0.0;
         phicx          = 0.0;
         phicy          = 0.0;
         b0             = d3Vector_sum (b0, d3Vector_double_multiply (z0, -tertiary_branch_length/2.0));
         Assign_Branch (&tertiary_branch, sr, er, b0, z0, p0, dp, phix, phiy, phicx, phicy, 
                        lamdacx, lamdacy, gamma, moisture, tertiary_branch_length, permittivity, 
                        (int) (pT->Stem.n + pT->Dry.n + pT->Primary.n + pT->Secondary.n +pT->Tertiary.n + 1L), 0);
         Branch_head_add (&(pT->Tertiary), &tertiary_branch);
      }
   }
   Destroy_Branch (&tertiary_branch);
   return;
}


void		Realise_Foliage (Tree *pT, PolSARproSim_Record *pPR)
{
   int			species;
   Crown			*pC;
   double		leaf_d1, leaf_d2, leaf_d3;
   double		theta, phi;
   double		moisture;
   d3Vector		cl;
   Complex		permittivity;
   Leaf        leaf1;
   int         ln;
   int         iLeaf;
   int         rtn_value;
   double      flg_scaling; /* for the Foliage MC scale factor --RAedit */
   long        n_Leaves;
   
   /* use the living crown */
   pC                         = pT->CrownVolume.head; 
   /* read in the leaf species (needle or broadleaf) */  
   species                    = Leaf_Species(pT->species, pPR);
   /* Estimate the number of leaves to realize (fewer than the actual no. of leaves) */
   flg_scaling                = Estimate_SAR_Foliage (pT, pPR, &n_Leaves);
   ln                         = (int)n_Leaves;
   pT->Foliage.scale_factor   = flg_scaling; /* MC scaling factor, needed for imaging later on */
   
   for (iLeaf=0L; iLeaf < ln; iLeaf++) {
      rtn_value		= Random_Crown_Location (pC, &cl);
      if (rtn_value == NO_RAYCROWN_ERRORS) {
         Leaf_Size      (pT, pPR, &leaf_d1, &leaf_d2, &leaf_d3);
         phi            = 2.0*DPI_RAD*drand();
         theta          = vegi_polar_angle ();
         moisture       = Leaf_Moisture (pT->species, pPR);
         permittivity	= vegetation_permittivity (moisture, pPR->frequency);
         Assign_Leaf    (&leaf1, species, leaf_d1, leaf_d2, leaf_d3, theta, phi, moisture, permittivity, cl);
         Leaf_head_add  (&(pT->Foliage), &leaf1);
      }
   }
   Destroy_Leaf (&leaf1);
   return;
}


void		Realise_Tree (Tree *pT, int i, PolSARproSim_Record *pPR)
{
   double			z;
   /**************************************************************/
   /* Resetting random number generator using srand (seed + i)	  */
   /* ensures that the ith tree is always realised the same way. */
   /**************************************************************/
   srand (pPR->seed + i);
   /***********************/
   /* Make a new tree ... */
   /***********************/
   Destroy_Tree (pT);
   /***********************/
   /* Initial assignments */
   /***********************/
   if(pPR->ForestInput_Flag == EXTERNAL_FOREST_DEFINITION) {
      pT->species           = pPR->Tree_Location[i].species;
      pT->dbh               = pPR->Tree_Location[i].dbh;              /* added this to allow external definition of stem diameter     */
      pT->canopy_depth      = pPR->Tree_Location[i].canopy_depth;     /* added this to allow external definition of canopy depth      */
      pT->canopy_dry_depth  = pPR->Tree_Location[i].canopy_dry_depth; /* added this to allow external definition of canopy dry depth  */
   } else {
      pT->species	= pPR->species; /* a homogenous stand */
   }
   pT->height		= pPR->Tree_Location[i].height;
   pT->radius		= pPR->Tree_Location[i].radius;
   z              = ground_height (pPR, pPR->Tree_Location[i].x, pPR->Tree_Location[i].y);
   pT->base       = Cartesian_Assign_d3Vector (pPR->Tree_Location[i].x, pPR->Tree_Location[i].y, z);
   /*************************/
   /* Create a global crown */
   /*************************/
   Crown_init_list	(&(pT->CrownVolume));
   /* This function is not restricted to the five tree species --RAedit*/
   Realise_Crown(pT, pPR);
   /****************************************************************************************/
   /* Main stem: use the tree base and global crown definition to construct the main stem  */
   /****************************************************************************************/
   Realise_Stem (pT, pPR);
   /********************************************************************************/
   /* Primary branches: use stems and the tree global crown to construct primaries */
   /********************************************************************************/
   Realise_Primaries (pT, pPR);
   /**********************************************************************************/
   /* Secondary branches: use stems and the tree global crown to construct primaries */
   /**********************************************************************************/
   Realise_Secondaries (pT, pPR);
   /***********************************************************************************/
   /* Tertiary branches: populate the tree global crown with random tertiary branches */
   /***********************************************************************************/
   Realise_Tertiaries (pT, pPR);
   /*************************************************************************/
   /* Foliage: populate the tree global crown with random leaves or needles */
   /*************************************************************************/
   Realise_Foliage (pT, pPR);
   /***********/
   /* Return  */
   /***********/
   return;
}

void		Realise_Tree_Crown_Only (Tree *pT, int i, PolSARproSim_Record *pPR)
{
   double			z;
   /***********************/
   /* Make a new tree ... */
   /***********************/
   Destroy_Tree (pT);
   /***********************/
   /* Initial assignments */
   /***********************/
   if(pPR->ForestInput_Flag == EXTERNAL_FOREST_DEFINITION) {
      pT->species             = pPR->Tree_Location[i].species;
      pT->dbh                 = pPR->Tree_Location[i].dbh;  
      pT->canopy_depth        = pPR->Tree_Location[i].canopy_depth;     /* added this to allow external definition of canopy depth      */
      pT->canopy_dry_depth    = pPR->Tree_Location[i].canopy_dry_depth; /* added this to allow external definition of canopy dry depth  */
      
   } else {
      pT->species             = pPR->species; /* a homogenous stand */
   }
   pT->height		= pPR->Tree_Location[i].height;
   pT->radius		= pPR->Tree_Location[i].radius;
   z              = ground_height (pPR, pPR->Tree_Location[i].x, pPR->Tree_Location[i].y);
   pT->base       = Cartesian_Assign_d3Vector (pPR->Tree_Location[i].x, pPR->Tree_Location[i].y, z);
   /*************************/
   /* Create a global crown */
   /*************************/
   Crown_init_list	(&(pT->CrownVolume));
   Realise_Crown(pT, pPR);
#ifdef ENABLE_ATTENUATION_FROM_STEMS   
   Realise_Stem(pT, pPR);
#endif
   return;
}

/************************************/
/* Random crown location generation */
/************************************/

int		Random_Crown_Location			(Crown *p_cwn, d3Vector *s)
{
   Plane       p;
   double		phi;
   d3Vector    d;
   Ray         r;
   d3Vector    s1, s2;
   double		alpha1, alpha2;
   int         rtn_value;
   double		alpha;
   
   *s          = d3Vector_sum (p_cwn->base, d3Vector_double_multiply (p_cwn->axis, (p_cwn->d3-ROUNDING_ERROR)*drand()+ROUNDING_ERROR/2.0));
   Assign_Plane (&p, s, p_cwn->sx, p_cwn->sy);
   phi         = 2.0*DPI_RAD*drand();
   d           = d3Vector_double_multiply (p.xp, cos(phi));
   d           = d3Vector_sum (d, d3Vector_double_multiply (p.yp, sin(phi)));
   Assign_Ray_d3V (&r, s, &d);
   rtn_value	= RayCrownIntersection (&r, p_cwn, &s1, &alpha1, &s2, &alpha2);
   if (rtn_value == NO_RAYCROWN_ERRORS) {
      if (alpha1*alpha2 < 0.0) {
         if (alpha1 > alpha2) {
            alpha	=	sqrt (alpha1*alpha1*drand());
         } else {
            alpha	=	sqrt (alpha2*alpha2*drand());
         }
         *s       = d3Vector_sum (*s, d3Vector_double_multiply (d, alpha));
      }
   }
   return (rtn_value);
}
