/******************************************************************************/
/*                                                                            */
/* datetime-lock and datetime-config denies physical access to your system.   */  
/* Copyright (C) 2013 Bruggeman Eddie.                                        */
/*                                                                            */
/* This file is part of datetime-config.                                      */
/* datetime-config is a free software:                                        */ 
/* you can redistribute it and/or modify it under the terms of                */
/* the GNU General Public License as published by                             */
/* the Free Software Foundation, either version 3 of the License, or          */  
/* (at your option) any later version.                                        */ 
/*                                                                            */ 
/* datetime-config is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of             */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               */
/* GNU General Public License for more details.                               */ 
/*                                                                            */
/* You should have received a copy of the GNU General Public License          */
/* along with datetime-lock and datetime-config.                              */ 
/* If not, see <http://www.gnu.org/licenses/>                                 */    
/*                                                                            */ 
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#define _XOPEN_SOURCE 
#include <time.h>


void print_help(const char *prg_name) ;

int main(int argc,char *argv[]) {
  int argument ;
  FILE *date ;
  date=popen("date +%d/%m/%Y", "r");
  char *date_string=malloc(12) ;
  fscanf(date, "%s", date_string) ;
  pclose(date);
  
  struct tm *end_time ;
  time_t now ;
  
  unsigned int duree_to_add ;
  unsigned int hrs_to_add ;
  unsigned int sec_to_add ;
  unsigned int min_to_add ;
  
  char *end_time_string=malloc(12) ;

  if (argc == 1) {
    print_help(argv[0]) ;
    exit(EXIT_FAILURE) ;
  }
  while ((argument=getopt(argc,argv,"hst:d:")) != -1 ) {
    switch (argument) {
      case 's' :
        fprintf(stdout, "%s", date_string) ;
	exit(EXIT_SUCCESS) ;
	break ;
      case 't' :
	
	if (sscanf(optarg,"%2d:%2d:%2d",&hrs_to_add,&min_to_add,&sec_to_add) != 3) { 
	  fprintf(stdout,"	Wrong time format, use the fomart hh:mm:ss !!!		\n") ;
	  fprintf(stdout,"\n") ;
	  exit(EXIT_FAILURE) ;
	}
	duree_to_add=sec_to_add + (min_to_add * 60) + (hrs_to_add *60*60)  ;

        time(&now) ;
	end_time=localtime(&now);
	now += duree_to_add ;
	
	end_time=localtime(&now);

	strftime(end_time_string, (size_t) 9,"%T" ,end_time);
	fprintf(stdout,"%s",end_time_string) ;
	free(end_time_string) ;
	exit(EXIT_SUCCESS) ;
	break ;
     case 'd' :
	
	if (sscanf(optarg,"%2d:%2d:%2d",&hrs_to_add,&min_to_add,&sec_to_add) != 3) { 
	  print_help(argv[0]) ;
	  fprintf(stdout,"	Wrong date format, use the fomart hh:mm:ss !!!		\n") ;
	  fprintf(stdout,"\n") ;
	  exit(EXIT_FAILURE) ;
	}
	duree_to_add=sec_to_add + (min_to_add * 60) + (hrs_to_add *60*60)  ;
	
        time(&now) ;
	end_time=localtime(&now);
	now += duree_to_add ;
	
	end_time=localtime(&now);
	strftime(end_time_string, (size_t) 13,"%d/%m/%Y" ,end_time);
	fprintf(stdout,"%s",end_time_string) ;
	free(end_time_string) ;
	exit(EXIT_SUCCESS) ;
	break ;	
	
     case 'h' :
       print_help(argv[0]) ;
       exit(EXIT_SUCCESS) ;
       break ;
     default :
       print_help(argv[0]) ;
       exit(EXIT_FAILURE) ;
       break ;
    }
  }
  exit(EXIT_SUCCESS) ;
}

void print_help(const char *prg_name) {
  fprintf(stdout,"\n") ;
  fprintf(stdout,"	usage %s [-s|-d hh:mm:ss|-t hh:mm:ss]				\n",prg_name) ;
  fprintf(stdout,"\n") ;
  fprintf(stdout,"	An little utlity to help datetime-lock regular configuration.	\n") ;
  fprintf(stdout,"\n") ;
  fprintf(stdout,"	Options:  -s	[start] return the actual date for the	      	\n") ;
  fprintf(stdout,"	                        --from-date option.           		\n") ;
  fprintf(stdout,"	          -d    [date]  return the computing date from his    \n") ;
  fprintf(stdout,"	                        given argument duree: 			\n") ;
  fprintf(stdout,"				 in format hh:mm:ss. 			\n") ;
  fprintf(stdout,"	                        For the configuration from the 	\n") ;
  fprintf(stdout,"	                        --to-date option. 		 	\n") ;
  fprintf(stdout,"	          -t    [time]  return the computing time from his	\n") ;
  fprintf(stdout,"	                        given argument duree:			\n") ;
  fprintf(stdout,"				 in format hh:mm:ss. 			\n") ;
  fprintf(stdout,"	                        For the configuration from the 	\n") ;
  fprintf(stdout,"	                         --to-time option. 		 	\n") ;
  fprintf(stdout,"\n") ;
  fprintf(stdout,"	Use the substitution operator $() for format the 		\n") ;
  fprintf(stdout,"	configuration of datetime-lock in case of regular use.		\n") ;
  fprintf(stdout,"\n") ;
  return ;
}
  
