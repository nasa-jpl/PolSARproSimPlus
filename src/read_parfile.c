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
 * Author      : Razi Ahmed
 * Module      : read_parfile.c
 * Revision    : Version 1.0 
 * Date        : July, 2012
 * Notes       : Reading input parameter files by keyword 
 */

#include "read_parfile.h"


/******************************************/
/* function to read a char flag specified */
/* by a keyword in a tabbed text file     */
/******************************************/
int     read_cflag     (FILE *pinF, char *key, char *str1){
   static int ns,nc, nb, i;
   static char *string1,*string2,eol[3], *par;
   static char string3[MAX_STR];
   
   eol[0]='\n';                  /* new line */
   eol[1]=';';                   /* semicolon */
   eol[2]='\0';
   
   /* determine number of bytes in the parameter file */
   fseek(pinF, (off_t)0L, SEEK_END);                    
   nb = (int)ftell(pinF);
   rewind(pinF);
   
   /* allocate space for parameter file data */
   par = (char*)malloc((nb + 1) * sizeof(char));              
   if (par == NULL) {
      fprintf(stderr, "\nERROR: memory allocation failure for parameter file buffer\n\n");
      exit(-1);
   }
   
   /* initialize parameter file array */
   for (i = 0; i <= nb; i++)par[i] = 0;                       
   /* read in the parameter file */
   fread((char *)par, sizeof(char), nb, pinF);       
   
   /* determine number of characters in key */
   ns = strlen(key);
   /*string1 = sstr(par,nb,key,ns);*/
   string1=strstr(par, key);
   
   if (string1 == NULL){
      printf("WARNING: subroutine read_string, keyword not found: %s\n",key);
      str1[0] = '\0';
      return -1;
   }
   string1 += ns;
   /* remove leading spaces, tabs, and colons */
   while ((*string1 == ' ') || (*string1 == '\t') || (*string1 == ':') || (*string1 == '"'))string1++;    
   /* last location of the valid string */
   string2 = strpbrk(string1,eol)-1;                
   /* remove trailing spaces, tabs, and returns */
   while ((*string2 == ' ') || (*string2 == '\t') || (*string2 == '\r') || (*string2 == '"'))string2--;   
   /* number of characters of the string, check for whitespace or NULL string */
   nc = MAX(string2-string1+1,0);          
   
   if(nc > 0){
      /* destination, source , number of characters */
      strncpy(string3,string1,nc);                         
      /* null terminate copied string */
      string3[nc]='\0';                                        
      if(sscanf(string3,"%c",str1) != 1){
         printf("WARNING read_cflag: corrupted data value with key: %s  value: %s\n",key,string3);
         return -1;
      }
      return 0;
   }
   else {
      printf("WARNING read_cflag: no value given for data with key: %s\n",key);
      return -1;
   }
}



/******************************************/
/* function to read a string specified    */
/* by a keyword in a tabbed text file     */
/******************************************/
int     read_string     (FILE *pinF, char *key, char *str1){
   static int ns,nc, nb, i;
   static char *string1,*string2,eol[3], *par;
   
   eol[0]='\n';                  /* new line */
   eol[1]=';';                   /* semicolon */
   eol[2]='\0';
   
   /* determine number of bytes in the parameter file */
   fseek(pinF, (off_t)0L, SEEK_END);                    
   nb = (int)ftell(pinF);
   rewind(pinF);
   
   /* allocate space for parameter file data */
   par = (char*)malloc((nb + 1) * sizeof(char));              
   if (par == NULL) {
      fprintf(stderr, "\nERROR: memory allocation failure for parameter file buffer\n\n");
      exit(-1);
   }
   
   /* initialize parameter file array */
   for (i = 0; i <= nb; i++)par[i] = 0;                       
   /* read in the parameter file */
   fread((char *)par, sizeof(char), nb, pinF);       
   
   /* determine number of characters in key */
   ns = strlen(key);
   /*string1 = sstr(par,nb,key,ns);*/
   string1=strstr(par, key);
   
   if (string1 == NULL){
      printf("WARNING: subroutine read_string, keyword not found: %s\n",key);
      str1[0] = '\0';
      return -1;
   }
   string1 += ns;
   /* remove leading spaces, tabs, and colons */
   while ((*string1 == ' ') || (*string1 == '\t') || (*string1 == ':') || (*string1 == '"'))string1++;    
   /* last location of the valid string */
   string2 = strpbrk(string1,eol)-1;                
   /* remove trailing spaces, tabs, and returns */
   while ((*string2 == ' ') || (*string2 == '\t') || (*string2 == '\r') || (*string2 == '"'))string2--;   
   /* number of characters of the string, check for whitespace or NULL string */
   nc = MAX(string2-string1+1,0);          
   
   /* destination, source, number of characters */
   strncpy(str1,string1,nc);                          
   /* null terminate copied string */
   str1[nc]='\0';                                
   return 0;
}

/******************************************/
/* function to read an integer specified  */
/* by a keyword in a tabbed text file     */
/******************************************/
int     read_integer    (FILE *pinF, char *key, int *val, int min, int max, int Default){
   static int ns,nc, nb, i;
   static char *string1,*string2,eol[3], *par;
   static char string3[MAX_STR];
   
   eol[0]='\n';                  /* new line */
   eol[1]=';';                   /* semicolon */
   eol[2]='\0';
   *val = 0;
   
   /* determine number of bytes in the parameter file */
   fseek(pinF, (off_t)0L, SEEK_END);                    
   nb = (int)ftell(pinF);
   rewind(pinF);
   
   /* allocate space for parameter file data */
   par = (char*)malloc((nb + 1) * sizeof(char));              
   if (par == NULL) {
      fprintf(stderr, "\nERROR: memory allocation failure for parameter file buffer\n\n");
      exit(-1);
   }
   
   /* initialize parameter file array */
   for (i = 0; i <= nb; i++)par[i] = 0;                       
   /* read in the parameter file */
   fread((char *)par, sizeof(char), nb, pinF);       
   
   
   ns = strlen(key);
   string1 = strstr(par, key);
   if (string1 == NULL){
      printf("WARNING: subroutine read_integer, keyword not found: %s\n",key); 
      *val  = Default;
      return -1;
   }
   string1 += ns;
   
   /* remove leading spaces, tabs, and colons */
   while ((*string1 == ' ') || (*string1 == '\t') || (*string1 == ':') || (*string1 == '"'))string1++;   
   /* last location of the valid string */
   string2 = strpbrk(string1,eol)-1;                                       
   /* remove trailing spaces, tabs, and returns */
   while ((*string2 == ' ') || (*string2 == '\t') || (*string2 == '\r') || (*string2 == '"'))string2--;  
   /* number of characters of the string, check for null string */
   nc = MAX(string2-string1+1, 0);                         
   
   if(nc > 0){
      /* destination, source , number of characters */
      strncpy(string3,string1,nc);                         
      /* null terminate copied string */
      string3[nc]='\0';                                        
      if(sscanf(string3,"%d",val) != 1){
         printf("WARNING read_integer: corrupted data value with key: %s  value: %s\n",key,string3);
         *val  = Default;
         return -1;
      }
      if(*val < min || *val > max){
         printf("WARNING value (%d) for %s is out of bounds [%d,%d]\n",*val, key, min, max);
         *val  = Default;
         return -1;
      }
      return 0;
   }
   else {
      printf("WARNING read_integer: no value given for data with key: %s\n",key);
      *val  = Default;
      return -1;
   }
   
}

/******************************************/
/* function to read a double specified    */
/* by a keyword in a tabbed text file     */
/******************************************/
int     read_double     (FILE *pinF, char *key, double *dbl_val, double min, double max, double Default){
   static int ns,nc, nb, i;
   static char *string1,*string2,eol[3], *par;
   static char string3[MAX_STR];
   
   eol[0]='\n';                  /* new line */
   eol[1]=';';                   /* semicolon */
   eol[2]='\0';
   *dbl_val =0.0;
   
   /* determine number of bytes in the parameter file */
   fseek(pinF, (off_t)0L, SEEK_END);                    
   nb = (int)ftell(pinF);
   rewind(pinF);
   
   /* allocate space for parameter file data */
   par = (char*)malloc((nb + 1) * sizeof(char));              
   if (par == NULL) {
      fprintf(stderr, "\nERROR: memory allocation failure for parameter file buffer\n\n");
      exit(-1);
   }
   
   /* initialize parameter file array */
   for (i = 0; i <= nb; i++)par[i] = 0;                       
   /* read in the parameter file */
   fread((char *)par, sizeof(char), nb, pinF);       
   
   ns = strlen(key);
   string1 = strstr(par, key);
   if (string1 == NULL){printf("WARNING: subroutine read_double, keyword not found: %s\n",key); return -1;}
   string1 += ns;
   
   /* remove leading spaces, tabs, and colons */
   while ((*string1 == ' ') || (*string1 == '\t') || (*string1 == ':') || (*string1 == '"'))string1++;   
   /* last location of the valid string */
   string2 = strpbrk(string1,eol)-1;                                       
   /* remove trailing spaces, tabs, and returns */
   while ((*string2 == ' ') || (*string2 == '\t') || (*string2 == '\r') || (*string2 == '"'))string2--;   
   /* number of characters of the string, check for null string */
   nc = MAX(string2-string1+1, 0);                         
   
   if(nc > 0){
      /* destination, source , number of characters */
      strncpy(string3,string1,nc);                         
      /* null terminate copied string */
      string3[nc]='\0';                               
      if(sscanf(string3,"%le",dbl_val) != 1){
         printf("WARNING read_double: corrupted data value with key: %s  value: %s\n",key,string3);
         *dbl_val  = Default;
         return -1;
      }
      if(*dbl_val < min || *dbl_val > max){
         printf("WARNING value (%f) for %s is out of bounds [%e,%e]\n",*dbl_val, key, min, max);
         *dbl_val  = Default;
         return -1;
      }       
      return 0;
   }
   else {
      printf("WARNING read_double: no value given for data with key: %s\n",key);
      *dbl_val  = Default;
      return -1;
   }
}

/******************************************/
/* function to read a float specified     */
/* by a keyword in a tabbed text file     */
/******************************************/
int     read_float  (FILE *pinF, char *key, float *flt_val){
   static int ns,nc, nb, i;
   static char *string1,*string2,eol[3], *par;
   static char string3[MAX_STR];
   
   eol[0]='\n';                  /* new line */
   eol[1]=';';                   /* semicolon */
   eol[2]='\0';
   *flt_val = 0.0;
   
   /* determine number of bytes in the parameter file */
   fseek(pinF, (off_t)0L, SEEK_END);                    
   nb = (int)ftell(pinF);
   rewind(pinF);
   
   /* allocate space for parameter file data */
   par = (char*)malloc((nb + 1) * sizeof(char));              
   if (par == NULL) {
      fprintf(stderr, "\nERROR: memory allocation failure for parameter file buffer\n\n");
      exit(-1);
   }
   
   /* initialize parameter file array */
   for (i = 0; i <= nb; i++)par[i] = 0;                       
   /* read in the parameter file */
   fread((char *)par, sizeof(char), nb, pinF);       
   
   
   ns = strlen(key);
   string1 = strstr(par, key);
   if (string1 == NULL){printf("WARNING: subroutine read_float, keyword not found: %s\n",key); return -1;}
   string1 += ns;
   
   /* remove leading spaces, tabs, and colons */
   while ((*string1 == ' ') || (*string1 == '\t') || (*string1 == ':') || (*string1 == '"'))string1++;  
   /* last location of the valid string */
   string2 = strpbrk(string1,eol)-1;                                       
   /* remove trailing spaces, tabs, and returns */
   while ((*string2 == ' ') || (*string2 == '\t') || (*string2 == '\r') || (*string2 == '"'))string2--;  
   /* number of characters of the string, check for null string */
   nc = MAX(string2-string1+1, 0);                         
   
   if(nc > 0){
      /* destination, source , number of characters */
      strncpy(string3,string1,nc);                          
      /* null terminate copied string */
      string3[nc]='\0';                                        
      if(sscanf(string3,"%e",flt_val) != 1){
         printf("WARNING read_float: corrupted data value with key: %s  value: %s\n",key,string3);
         return -1;
      }
      return 0;
   }
   else {
      printf("WARNING read_float: no value given for data with key: %s\n",key);
      return -1;
   }
}


/******************************************/
/* function to read a vector of floats    */
/* specified by a keyword in a tabbed     */
/* text file                              */
/******************************************/
int     read_fvector (FILE *pinF, char *key, float *flt, int nv){
   int ns,nc,j, nb, i;
   char *string1,*string2,*string3,*s4,*par;
   char eol[3],sep[4];
   
   string3 = (char *)malloc(MAX_STR);
   if(string3 == NULL){fprintf(stderr,"\nERROR: memory allocation error in subroutine rd_vec\n\n"); exit(-1);}
   
   eol[0]='\n';                  /* new line */
   eol[1]=';';                   /* semicolon */
   eol[2]='\0';
   sep[0]=' ';                   /* valid separators */
   sep[1]=',';
   sep[2]='\t';                  /* tab */
   sep[3]='\0';
   for (j=0; j < nv; j++)flt[j] = 0.0;           /* initialize data */
   
   /* determine number of bytes in the parameter file */
   fseek(pinF, (off_t)0L, SEEK_END);                    
   nb = (int)ftell(pinF);
   rewind(pinF);
   
   /* allocate space for parameter file data */
   par = (char*)malloc((nb + 1) * sizeof(char));              
   if (par == NULL) {
      fprintf(stderr, "\nERROR: memory allocation failure for parameter file buffer\n\n");
      exit(-1);
   }
   
   /* initialize parameter file array */
   for (i = 0; i <= nb; i++)par[i] = 0;                       
   /* read in the parameter file */
   fread((char *)par, sizeof(char), nb, pinF);       
   
   ns = strlen(key);
   string1 = strstr(par, key);
   if (string1 == NULL){printf("WARNING: subroutine read_vector, keyword not found: %s\n",key); return -1;}
   string1 += ns;
   
   /* remove leading spaces, tabs, and colons */
   while ((*string1 == ' ') || (*string1 == '\t') || (*string1 == ':') || (*string1 == '"'))string1++;    
   /* last location of the valid string */
   string2 = strpbrk(string1,eol)-1;                                       
   /* remove trailing spaces, tabs, and returns */
   while ((*string2 == ' ') || (*string2 == '\t') || (*string2 == '\r') || (*string2 == '"'))string2--;   
   /* number of characters of the string */
   nc = string2-string1+1;                                 
   /* destination, source, number of characters */
   strncpy(string3,string1,nc);                            
   /* null terminate copied string */
   string3[nc] = '\0';                                
   
   for (j=0; j < nv; j++){
      s4 = strtok(string3,sep);
      /* continue scanning for next token */
      string3=(char *)NULL;                            
      if(s4 == NULL){
         printf("WARNING read_fvector: insufficient number of values: %d    key: %s\n",nv,key);
         return -1;
      }
      if (sscanf(s4,"%f",flt+j) != 1){
         printf("WARNING read_fvector: invalid entry for data with key: %s    value: %s\n",key,s4);
         return -1;
      }
   }
   free(string3);
   return 0;
}




/******************************************/
/* function to read a vector of doubles   */
/* specified by a keyword in a tabbed     */
/* text file                              */
/******************************************/
int     read_dvector (FILE *pinF, char *key, double *dbl, int nv){
   int ns,nc,j, nb, i;
   char *string1,*string2,*string3,*s4,*par;
   char eol[3],sep[4];
   
   string3 = (char *)malloc(MAX_STR);
   if(string3 == NULL){fprintf(stderr,"\nERROR: memory allocation error in subroutine rd_vec\n\n"); exit(-1);}
   
   eol[0]='\n';                  /* new line */
   eol[1]=';';                   /* semicolon */
   eol[2]='\0';
   sep[0]=' ';                   /* valid separators */
   sep[1]=',';
   sep[2]='\t';                  /* tab */
   sep[3]='\0';
   for (j=0; j < nv; j++)dbl[j] = 0.0;           /* initialize data */
   
   /* determine number of bytes in the parameter file */
   fseek(pinF, (off_t)0L, SEEK_END);                    
   nb = (int)ftell(pinF);
   rewind(pinF);
   
   /* allocate space for parameter file data */
   par = (char*)malloc((nb + 1) * sizeof(char));              
   if (par == NULL) {
      fprintf(stderr, "\nERROR: memory allocation failure for parameter file buffer\n\n");
      exit(-1);
   }
   
   /* initialize parameter file array */
   for (i = 0; i <= nb; i++)par[i] = 0;                       
   /* read in the parameter file */
   fread((char *)par, sizeof(char), nb, pinF);       
   
   ns = strlen(key);
   string1 = strstr(par, key);
   if (string1 == NULL){printf("WARNING: subroutine read_vector, keyword not found: %s\n",key); return -1;}
   string1 += ns;
   
   /* remove leading spaces, tabs, and colons */
   while ((*string1 == ' ') || (*string1 == '\t') || (*string1 == ':') || (*string1 == '"'))string1++;    
   /* last location of the valid string */
   string2 = strpbrk(string1,eol)-1;                                       
   /* remove trailing spaces, tabs, and returns */
   while ((*string2 == ' ') || (*string2 == '\t') || (*string2 == '\r') || (*string2 == '"'))string2--;   
   /* number of characters of the string */
   nc = string2-string1+1;                                 
   /* destination, source, number of characters */
   strncpy(string3,string1,nc);                            
   /* null terminate copied string */
   string3[nc] = '\0';                                
   
   for (j=0; j < nv; j++){
      s4 = strtok(string3,sep);
      /* continue scanning for next token */
      string3=(char *)NULL;                            
      if(s4 == NULL){
         printf("WARNING read_vector: insufficient number of values: %d    key: %s\n",nv,key);
         return -1;
      }
      if (sscanf(s4,"%le",dbl+j) != 1){
         printf("WARNING read_vector: invalid entry for data with key: %s    value: %s\n",key,s4);
         return -1;
      }
   }
   free(string3);
   return 0;
}
