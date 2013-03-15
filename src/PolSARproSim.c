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
 * Module      : PolSARproSim.c
 * Revision    : Version C1b 
 * Date        : September, 2007
 * Notes       : Coherent Forest SAR Simulation for PolSARPro.
 */
#include	"PolSARproSim.h"

int main(int argv, char *argc[])
{
   /**************************************/
   /* Miscellaneous variable definitions */
   /**************************************/
   char                 *passed_input_directory_plus_prefix;
   char                 *passed_master_directory;
   char                 *input_directory;
   char                 *master_directory;
#ifdef _WIN32
   const char				ddlim	= '\\';
#else 
   const char				ddlim	= '/';
#endif
   char                 *prefix;
   int                  n,nmax,i,ilen;
   char                 *input_string;
   char                 *output_string;
   char                 *logfile_string;
   char                 *call_string;
   FILE                 *pCF;
   /*********************/
   /* The master record */
   /*********************/
   PolSARproSim_Record		Master_Record;
   /* Some variables for testing cpu-time */
   time_t                  startgndsv, stopgndsv; 
   time_t                  startmuamap, stopmuamap;
   time_t                  startforest, stopforest;
   time_t                  starttotal, stoptotal;
   /*******************************************/
   /* Check command line argument list length */
   /*******************************************/
      
   if (argv < 3) {
      printf ("\nUse: pspsim_dev <input_directory_plus_prefix> <data_directory> \n");
      printf ("\te.g. pspsim_dev ./run1 slcs/ \n");
      printf ("\nCAUTION: This version of PolSARproSim has been heavily edited\n");
      printf ("\t if it doesn't work, its not Mark Williams' fault. Good luck!\n");
      printf ("\t\t\t\t\t--Razi Ahmed\n\n");
      exit (1);
   } else {
      passed_input_directory_plus_prefix			= argc[1];
      passed_master_directory                   = argc[2];
   }
   
   /* start total time counter */
   time(&starttotal);
   
   /***********************/
   /* Generate file names */
   /***********************/
   
   /***********************************************/
   /* Parse string arguments for TCLTK convention */
   /***********************************************/
   
   tcltk_parser	(passed_input_directory_plus_prefix);
   tcltk_parser	(passed_master_directory);
   
   /***************************/
   /* Extract filename prefix */
   /***************************/
   
   i		= 0;
   nmax	= strlen (passed_input_directory_plus_prefix);
   for (n=0; n<nmax; n++) {
      if (passed_input_directory_plus_prefix[n] == ddlim) {
         i = n;
      }
   }
   ilen	= nmax - i;
   ilen++;
   prefix	= (char*) calloc (ilen, sizeof(char));
   strcpy (prefix, &(passed_input_directory_plus_prefix[i+1]));
   
   /************************************************/
   /* Extract delimiter terminated Input directory */
   /************************************************/
   
   input_directory	= (char*) calloc (i+2, sizeof(char));
   strncat (input_directory, passed_input_directory_plus_prefix, i+1);
   input_directory[i+1]	= '\0';
   
   /*************************************************/
   /* Extract delimiter terminated Master directory */
   /*************************************************/
   
   nmax	= strlen (passed_master_directory);
   if (passed_master_directory[nmax-1] == ddlim) {
      master_directory	= (char*) calloc (nmax+1, sizeof(char));
      strcpy  (master_directory, passed_master_directory);
   } else {
      master_directory	= (char*) calloc (nmax+2, sizeof(char));
      strcpy  (master_directory, passed_master_directory);
      master_directory[nmax]	= ddlim;
   }
   
   /************************/
   /* Calculate file names */
   /************************/
   
   input_string	= (char*) calloc (strlen(input_directory)+strlen(prefix)+6, sizeof(char));
   strcpy  (input_string, input_directory);
   strncat (input_string, prefix, strlen(prefix));
   strncat (input_string, ".sar", 4);
   output_string	= (char*) calloc (strlen(master_directory)+strlen(prefix)+6, sizeof(char));
   strcpy  (output_string, master_directory);
   strncat (output_string, prefix, strlen(prefix));
   strncat (output_string, ".out", 4);
   logfile_string	= (char*) calloc (strlen(master_directory)+strlen(prefix)+6, sizeof(char));
   strcpy  (logfile_string, master_directory);
   strncat (logfile_string, prefix, strlen(prefix));
   strncat (logfile_string, ".log", 4);
   Master_Record.pFilenamePrefix	= prefix;
   Master_Record.pInputDirectory	= input_directory;
   Master_Record.pMasterDirectory	= master_directory;
   call_string	= (char*) calloc (strlen(master_directory)+strlen(prefix)+11, sizeof(char));
   strcpy  (call_string, master_directory);
   strncat (call_string, prefix, strlen(prefix));
   strncat (call_string, "_call.txt", 9);
      
   /********************/
   /* Report filenames */
   /********************/
   
   if ((pCF = fopen(call_string, "w")) == NULL) {
      printf ("Unable to open call file %s.\n", call_string);
      return (!NO_POLSARPROSIM_ERRORS);
   } else {
      fprintf (pCF, "\nArguments:\n%s\n%s\n%s\n", argc[1], argc[2], argc[3]);
      fprintf (pCF, "\nInput_directory     %s\n", input_directory);
      fprintf (pCF, "\nMaster_directory    %s\n", master_directory);
      fprintf (pCF, "\nReading input from  %s\n", input_string);
      fprintf (pCF, "\nWriting output to   %s\n", output_string);
      fprintf (pCF, "\nWriting log to      %s\n\n", logfile_string);
      fclose (pCF);
   }
   
#ifdef VERBOSE_POLSARPROSIM
   printf ("\nArguments:\n%s\n%s\n%s\n", argc[1], argc[2], argc[3]);
   printf ("\nInput_directory     %s\n", input_directory);
   printf ("\nMaster_directory    %s\n", master_directory);
   printf ("\nReading input from  %s\n", input_string);
   printf ("\nWriting output to   %s\n", output_string);
   printf ("\nWriting log to      %s\n", logfile_string);
   
#endif
      
   /********************************/
   /* Attempt to open output files */
   /********************************/
   
   if ((Master_Record.pOutputFile = fopen(output_string, "w")) == NULL) {
      printf ("Unable to open output file %s.\n", output_string);
      return (!NO_POLSARPROSIM_ERRORS);
   }
   if ((Master_Record.pLogFile = fopen(logfile_string, "w")) == NULL) {
      printf ("Unable to open log file %s.\n", logfile_string);
      return (!NO_POLSARPROSIM_ERRORS);
   }
   
   /**********************/
   /* The simulation ... */
   /**********************/
   
   PolSARproSim_notice (Master_Record.pOutputFile);
   PolSARproSim_notice (Master_Record.pLogFile);
   fprintf (Master_Record.pOutputFile, "\nReading parameters from file %s.\n", input_string);
   fprintf (Master_Record.pLogFile,    "\nReading parameters from file %s.\n", input_string);
   fflush (Master_Record.pOutputFile);
   fflush (Master_Record.pLogFile);
      
   /******************************/
   /* Report compilation options */
   /******************************/
   
   PolSARproSim_compile_options     (Master_Record.pLogFile);
   
   /**********************************************/
   /* Report type sizes for consistency checking */
   /**********************************************/
   
   Report_SIM_Type_Sizes            (Master_Record.pLogFile);
   
   /************************************************/
   /* Read the input file to setup the simulations */
   /************************************************/
   
   Input_PolSARproSim_Record        (input_string, &Master_Record);
   
         
#ifdef POLSARPROSIM_MAX_PROGRESS
   PolSARproSim_indicate_progress   (&Master_Record);
#endif
   
   /****************************************************/
   /* Stage 1: Create the 3D description of the forest */
   /****************************************************/
   
   /*************************************************************/
   /* Generate ground height map on ground range - azimuth grid */
   /*************************************************************/
   Create_SIM_Record                (&(Master_Record.Ground_Height));
   Ground_Surface_Generation        (&Master_Record);
#ifndef POLSARPROSIM_NOSIMOUTPUT
   Write_SIM_Record_As_POLSARPRO_BINARY        (&(Master_Record.Ground_Height));
#endif
   
   /****************************************************/
   /* Initialize Max Height and Surface Normal Layers  */
   /****************************************************/
   Initialize_Max_Height_Map        (&Master_Record);
   Initialize_Surface_Normal_Layers (&Master_Record);
   
   
   /****************************************************/
   /* Generate tree stem position and height database. */
   /****************************************************/
   
   if(Master_Record.ForestInput_Flag != EXTERNAL_FOREST_DEFINITION){
      printf("Forest locations being generated\n");
      Tree_Location_Generation      (&Master_Record);
      Write_Forest_XML              (&Master_Record);
   }
   
   /********************************/
   /* Increment progress indicator */
   /********************************/
   
   Master_Record.progress++;
   
   /********************************/
   /* Report progress if requested */
   /********************************/
   
#ifdef POLSARPROSIM_MAX_PROGRESS
   PolSARproSim_indicate_progress   (&Master_Record);
#endif
   
   /**************************************************************************/
   /* Create a graphic image of the forest from the perspective of the radar */
   /**************************************************************************/
   if(Master_Record.ForestDraw_Flag == DRAW_FOREST_IMAGE){
      Forest_Graphic                (&Master_Record);
   }
   /*************************************************************/
   /* Stage 2: Calculate the electrical proprties of the forest */
   /*************************************************************/

   time(&startmuamap);
   /*****************************************************/
   /* Calculate the vegetation effective permittivities */
   /*****************************************************/
#ifdef ENABLE_THREADS
   Effective_Permittivities_SMP     (&Master_Record);
#else
   Effective_Permittivities         (&Master_Record);
#endif

   /***************************************************/
   /* Calculate the spatial attenuation look-up table */
   /***************************************************/

#ifdef ENABLE_THREADS
   Attenuation_Map_SMP              (&Master_Record);
#else
   Attenuation_Map                  (&Master_Record);
#endif

   time(&stopmuamap);
   printf("Finished Effective Permittivities and Attenuation Map in about %f seconds. \n", difftime(stopmuamap, startmuamap));

   /***********************************************/
   /* Initialise the stack of SAR image variables */
   /***********************************************/

   Initialise_SAR_Stack             (&Master_Record);

   /*****************************************************/
   /* Stage 3: Calculate the interferometric SAR images */
   /*****************************************************/
   
   for (Master_Record.current_track = 0; Master_Record.current_track < Master_Record.Tracks; Master_Record.current_track++) {
      time(&startgndsv); 

      /********************************************/
      /* Calculate the direct ground contribution */
      /********************************************/
#ifdef ENABLE_THREADS
      PolSARproSim_Direct_Ground_SMP            (&Master_Record);
#else
      PolSARproSim_Direct_Ground                (&Master_Record);
#endif      
      /***********************************************/
      /* Calculate the short vegetation contribution */
      /***********************************************/
#ifdef ENABLE_THREADS
      PolSARproSim_Short_Vegetation_Direct_SMP  (&Master_Record);
      PolSARproSim_Short_Vegetation_Bounce_SMP  (&Master_Record);
#else
      PolSARproSim_Short_Vegetation_Direct      (&Master_Record);
      PolSARproSim_Short_Vegetation_Bounce      (&Master_Record);
#endif


      /*************************************/
      /* Calculate the volume contribution */
      /*************************************/
#ifndef ENABLE_THREADS
      PolSARproSim_Forest_Direct                (&Master_Record);
      PolSARproSim_Forest_Bounce                (&Master_Record);
#endif
      
      /*****************************************/
      /* Put a corner reflector or two for fun */
      /*****************************************/
#ifdef   ENABLE_CORNER_REFLECTORS
//      Image_Corner_Reflectors_Direct            (&Master_Record);
#endif
      
      /***********/
      /* Time it */
      /***********/
      time(&stopgndsv);
      printf("Finished track %d in about %f seconds. \n",Master_Record.current_track, difftime(stopgndsv, startgndsv));

   }
   
   /*************************************/
   /* Calculate the volume contribution */
   /*************************************/
#ifdef ENABLE_THREADS
   time(&startforest);
   PolSARproSim_Forest_SMP                   (&Master_Record);
   time(&stopforest);
   printf("Finished Imaging forest about %f seconds. \n",difftime(stopforest, startforest));
#endif

   /****************************************/
   /* Optional flat earth phase correction */
   /****************************************/
#ifdef	POLSARPROSIM_FLATEARTH
   Flat_Earth_Phase_Removal                  (&Master_Record);
#endif

   /**********************************************/
   /* Output the SAR images for the entire stack */
   /**********************************************/
   Write_SAR_Stack                              (&Master_Record);
   Write_Stack_LookVectors                      (&Master_Record);
   Write_SIM_Record_As_POLSARPRO_BINARY         (&(Master_Record.Max_Height));
   Write_SIM_Record_As_POLSARPRO_BINARY         (&(Master_Record.Surface_Normal_X));
   Write_SIM_Record_As_POLSARPRO_BINARY         (&(Master_Record.Surface_Normal_Y));
   Write_SIM_Record_As_POLSARPRO_BINARY         (&(Master_Record.Surface_Normal_Z));
   /******************************/
   /* Tidy up before leaving     */
   /******************************/

   Destroy_SAR_Stack                (&Master_Record);
   free                             (input_string);
   free                             (output_string);
   free                             (logfile_string);
   free                             (call_string);
   fclose                           (Master_Record.pOutputFile);
   fclose                           (Master_Record.pLogFile);
   Destroy_SIM_Record               (&(Master_Record.Ground_Height));
   Destroy_SIM_Record               (&(Master_Record.Max_Height));
   
   
   
   /***********/
   /* Time it */
   /***********/   
   time(&stoptotal);
   printf("Finished everything about %f seconds. \n",difftime(stoptotal, starttotal));

   /***************/
   /* End of Main */
   /***************/
   
   return (NO_POLSARPROSIM_ERRORS);
}
