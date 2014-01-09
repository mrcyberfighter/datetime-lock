/******************************************************************************/
/*                                                                            */
/* datetime-lock and datetime-config denies physical access to your system.   */  
/* Copyright (C) 2013 Bruggeman Eddie.                                        */
/*                                                                            */
/* This file is part of datetime-lock.                                        */
/* datetime-lock is a free software:                                          */ 
/* you can redistribute it and/or modify it under the terms of                */
/* the GNU General Public License as published by                             */
/* the Free Software Foundation, either version 3 of the License, or          */  
/* (at your option) any later version.                                        */ 
/*                                                                            */ 
/* datetime-lock is distributed in the hope that it will be useful,           */
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
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include <stdbool.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#include "get_datetime_opts.c"
#include "compute_opts_values.c"
#include "handle_datas_files.c"
#include "message_printer.c"
#include "logger.c"

#define true 1
#define false 0

int check_timestamps(int from_date[3],int to_date[3],int from_time[3],int to_time[3],int weekdays[7]) ;
int check_is_config_weekdays(int weekdays[7]) ;

int main(int argc, char *argv[]) {

  char *user=getenv("USER") ;
  if ( strcmp(user,"root") != 0) {
      /** datetime-lock must be run as root */
      print_help(argv[0]) ;
      print_wrong_user(argv[0]) ; 
      exit(EXIT_FAILURE) ;
  }
  
  struct tm *start_datetime ; //needed for summary displaying with strftime()
  struct tm *end_datetime   ; //needed for summary displaying with strftime()
  
  start_datetime =  malloc(sizeof(struct tm ))   ;
  end_datetime   =  malloc(sizeof(struct tm ))   ;
  
  int from_date[3] ;            // Table of int to store the date from wenn to block the system, who will be stored in a file.
  memset(&from_date,0,3*4) ;
  
  int to_date[3]   ;            // Table of int to store the date to wenn to block the system, who will be stored in a file.
  memset(&to_date,0,3*4) ;
  
  int days_of_week[7] ;         // Table of int to store the days wenn to block the system, who will be stored in a file. 
  memset(&days_of_week,0,7*4) ; // Start index 0 represent the sunday 	andthe other sthe followings week-days.
  
  
  
  int from_time[3] ;
  memset(&from_time,0,3*4) ;
  
  int to_time[3]   ;
  memset(&to_time,0,3*4) ;
  
  int block_during[3] ;
  memset(&block_during,0,3*4) ;
  
  /** Boolean values for options checking if thye configuration of the block time not be from different sort:
   * - With an from date and an to date OR week-day(s).
   * - With an from time and an to time OR from-timer what means to set an start time and the during of the block
   * */
  _Bool from_date_is_set=false ;
  _Bool to_date_is_set=false ;
  _Bool from_timer_during=false ;
  _Bool from_time_is_set=false ;
  _Bool to_time_is_set=false ;
  _Bool is_weekday_config=false ;
  _Bool reset=false ;
  
  int c ;
  int ret_opt_setting ;
  struct option my_opts[]={{"today",no_argument,0,0},{"every-day",no_argument,0,2},{"week-days",no_argument,0,4},{"weekend-days",no_argument,0,6},{"from-date",required_argument,0,8},{"to-date",required_argument,0,10},{"days",required_argument,0,12},{"from-time",required_argument,0,1},{"to-time",required_argument,0,3},{"from-timer",required_argument,0,5},{"time-slice",required_argument,0,7},{"disable",no_argument,0,20},{"help",no_argument,0,21},{"display-logs",no_argument,0,22},{0,0,0,0}} ;
  
  while ((c=getopt_long(argc, argv, "h",my_opts, NULL)) != -1) {
    switch(c) {
      /*******************************************************/
      /* date settings options have c = even value && [0-12] */ 
      /* time settings options have c = odd  value && [1-7]  */
      /* disable blocking option have c == 20 value          */
      /* help display     option have c == 21 value          */
      /* log display      option have c == 22 value          */
      /*******************************************************/
      
      
      /** Start of the date settings options **/ 
      case 0 :
	
	
	/** --today
	 * The block is effectiv for only today
	 * *************************************/
	
	if ( (! from_date_is_set) && (! to_date_is_set) ) {
	  
	  today_arg(from_date,to_date) ;
	  from_date_is_set = to_date_is_set = true ;
	}
	else {
	  print_help(argv[0]) ;
	  exit(EXIT_FAILURE) ;
	}
	break ;
	
      case 2 : 
	
	/** --every-day
	 * The block is effectiv every day of the week
         **********************************************/
	
	if ( (! from_date_is_set ) && (! to_date_is_set) ) {
	  for ( c=0 ; c < 7 ; c++) {
	    memset(&days_of_week[c],1,1) ;
	  }
	  from_date_is_set = to_date_is_set = is_weekday_config = true ;
	  
	}
	  
	else {
	  print_help(argv[0]) ;
	  exit(EXIT_FAILURE) ;
	}
	
	break ;	
	
      case 4 :
	
	/** --week-days
	 * The block is effectiv only the week days, exclusiv the week-end days: saturday and sunday.
	 *********************************************************************************************/ 
	
	if ((! from_date_is_set ) && (! to_date_is_set) ) {
	  for (c=1; c < 6; c++) {
	    memset(&days_of_week[c],1,1) ;
	  }
	  from_date_is_set = to_date_is_set = is_weekday_config = true ;
	}
	else {
	  print_help(argv[0]) ;
	  exit(EXIT_FAILURE) ;
	}
	
	break ;	
	
      case 6 :
	
	/** --weekend-days
	 * The block is effectiv only the week-end days: saturday and sunday.
	 * *******************************************************************/
	
	if ( (! from_date_is_set ) && (! to_date_is_set) ) {
	  memset(&days_of_week[0],1,1) ;
	  memset(&days_of_week[6],1,1) ;
	  from_date_is_set = to_date_is_set = is_weekday_config =true ;
	}
	else {
	  print_help(argv[0]) ;
	  exit(EXIT_FAILURE) ;
	}
	
	
	break ;
      	
      case 8 :
	
	/** --from-date
	 * Let the user set the start block date in form dd/mm/yyyy
	 * *********************************************************/
	
	if (! from_date_is_set) {
	  ret_opt_setting=from_date_arg(optarg,from_date) ;
	  if (ret_opt_setting == -1) {
	    /** return code is an scanf() error **/
	    print_help(argv[0]) ;
	    print_err_msg(1,0,0,1,0) ; /** Print an error message generated with the print_err_msg() function arguments !!! 	sea: message_printer.c */ 
	    exit(EXIT_FAILURE) ;
	  }
	  
	  else if (ret_opt_setting < -1 && ret_opt_setting > -5 ) {
	    /** return code is an error code: values out of range. 	sea: get_datetime_opts.c **/
	    print_help(argv[0]) ;
	    print_err_msg(1,0,0,0,ret_opt_setting) ; /** Print an error message generated with the print_err_msg() function arguments !!! 	sea: message_printer.c */ 
	    exit(EXIT_FAILURE) ;
	  }
	  from_date_is_set=true ;
	}
	else {
	  print_help(argv[0]) ;
	  exit(EXIT_FAILURE) ;
	}
	break ;	
	
      case 10 :
	
	/** --to-date
	 * Let the user set the block end date in form dd/mm/yyyy
	 * *******************************************************/
	
	if (! to_date_is_set) {
	  ret_opt_setting=to_date_arg(optarg,to_date) ;
	  if (ret_opt_setting == -1) {
	    /** return code is an error code from sscanf() detected. 	sea: get_datetime_opts.c **/
	    print_help(argv[0]) ;
	    print_err_msg(1,0,0,1,0) ; /** Print an error message generated with the print_err_msg() function arguments !!! 	sea: message_printer.c */ 
	    exit(EXIT_FAILURE) ;
	  }
	  
	  else if (ret_opt_setting < -1 && ret_opt_setting > -5 ) {
	    /** return code is an error code: values out of range. 	sea: get_datetime_opts.c **/
	    print_help(argv[0]) ;
	    print_err_msg(1,0,0,0,ret_opt_setting) ; /** Print an error message generated with the print_err_msg() function arguments !!! 	sea: message_printer.c */ 
	    exit(EXIT_FAILURE) ;
	  }

	  to_date_is_set=true ;
	}
	else {
	  print_help(argv[0]) ;
	  exit(EXIT_FAILURE) ;
	}
	break ;
      
      case 12 :
	
	/** --days
	 * Let the user choice the days wenn he want ot block the system: 
	 * in form of [sun,mon,tue,wed,thu,fri,sat] values comma separated
	 * ****************************************************************/
	
	if ( (! from_date_is_set ) && (! to_date_is_set) ) {
	  ret_opt_setting=days_arg(optarg,days_of_week) ;
	  if (ret_opt_setting == -1) {
	    /** return code is an error code: wrong values given. 	sea: get_datetime_opts.c **/
	    print_help(argv[0]) ;
	    print_err_msg(0,0,0,0,0) ; /** Print an error message generated with the print_err_msg() function arguments !!! 	sea: message_printer.c */ 
	    exit(EXIT_FAILURE) ;
	  }
	  else {
	  from_date_is_set = to_date_is_set = is_weekday_config = true ;
	  }
	}
	else {
	  print_help(argv[0]) ;
	  exit(EXIT_FAILURE) ;
	}
	break ;
      	
      /** Start of the time settings options **/ 	
      case 1 :
	
	/** --from-time
	 * Let the user set the start time blocking time of the system in form: hh:mm:ss
	 ****************************************************************************/ 
	
	if (! from_time_is_set) {
	  ret_opt_setting=from_time_arg(optarg,from_time) ;
	  if (ret_opt_setting == -1) {
	    /** return code is an error code from sscanf() detected. 	sea: get_datetime_opts.c **/
	    print_help(argv[0]) ;
	    print_err_msg(0,1,0,1,0) ;
	    exit(EXIT_FAILURE) ;
	  }
	  
	  else if (ret_opt_setting < -1 && ret_opt_setting > -5 ) {
	    /** return code is an error code: values out of range. 	sea: get_datetime_opts.c **/
	    print_help(argv[0]) ;
	    print_err_msg(0,1,0,0,ret_opt_setting) ; /** Print an error message generated with the print_err_msg() function arguments !!! 	sea: message_printer.c */ 
	    exit(EXIT_FAILURE) ;
	  }
	  from_time_is_set=true ;
	}
	else {
	  print_help(argv[0]) ;
	  exit(EXIT_FAILURE) ;
	}
	break ;	
	
      case 3 :
	
	/** --to-time
	 * Let the user set the end blocking time of the system in form: hh:mm:ss
	 * ***********************************************************************/
	
	if (! to_time_is_set) {
	  ret_opt_setting=to_time_arg(optarg,to_time) ;
	  if (ret_opt_setting == -1) {
	    /** return code is an error code from sscanf() detected. 	sea: get_datetime_opts.c **/
	    print_help(argv[0]) ;
	    print_err_msg(0,1,0,1,0) ;
	    exit(EXIT_FAILURE) ;
	  }
	  
	  else if (ret_opt_setting < -1 && ret_opt_setting > -5 ) {
	    /** return code is an error code: values out of range. 	sea: get_datetime_opts.c **/
	    print_help(argv[0]) ;
	    print_err_msg(0,1,0,0,ret_opt_setting) ; /** Print an error message generated with the print_err_msg() function arguments !!! 	sea: message_printer.c */ 
	    exit(EXIT_FAILURE) ;
	  }
	  to_time_is_set=true ;
	}
	else {
	  print_help(argv[0]) ;
	  exit(EXIT_FAILURE) ;
	}
	break ;
      	
	
      case 5 :
	
	/** --from-timer
	 * Let the user set the start blocking time and a during 
	 * in form of [Start-time]-[During] : hh:mm:ss-hh:mm:ss
	 ********************************************************/ 
	
	if (! from_time_is_set) {
	  ret_opt_setting=from_timer(optarg,from_time,block_during) ;
	  if (ret_opt_setting == -1) {
	    /** return code is an error code from sscanf() detected. 	sea: get_datetime_opts.c **/
	    print_help(argv[0]) ;
	    print_err_msg(0,0,1,1,0) ;
	    exit(EXIT_FAILURE) ;
	  }
	  
	  else if (ret_opt_setting < -1 && ret_opt_setting > -5 ) {
	    /** return code is an error code: values out of range. 	sea: get_datetime_opts.c **/
	    print_help(argv[0]) ;
	    print_err_msg(0,0,1,0,ret_opt_setting) ; /** Print an error message generated with the print_err_msg() function arguments !!! 	sea: message_printer.c */ 
	    exit(EXIT_FAILURE) ;
	  }
	  from_time_is_set = to_time_is_set = from_timer_during = true ;
	}
	else {
	  print_help(argv[0]) ;
	  exit(EXIT_FAILURE) ;
	}
	break ;
      	
      case 7 :
	
	/** --time-slice
	 * Let the user set a time slice wenn to blocking the system,
	 * if form of [Start-time]-[End-time] : hh:mm:ss-hh:mm:ss
	 * BUGFIX: the End-time cannot be littler than the start time what by
	 *         night settings with after midnight settings is not an good implementation .
	 ************************************************************************************/
	
	if (! from_time_is_set && ! to_time_is_set) {
	  ret_opt_setting=timer_slice(optarg,from_time,to_time) ;
	  if (ret_opt_setting == -1) {
	    /** return code is an error code from sscanf() detected. 	sea: get_datetime_opts.c **/
	    print_help(argv[0]) ;
	    print_err_msg(0,0,1,2,0) ;
	    exit(EXIT_FAILURE) ;
	  }
	  
	  else if (ret_opt_setting < -1 && ret_opt_setting > -5 ) {
	    /** return code is an error code: values out of range. 	sea: get_datetime_opts.c **/
	    print_help(argv[0]) ;
	    print_err_msg(0,1,0,0,ret_opt_setting) ; /** Print an error message generated with the print_err_msg() function arguments !!! 	sea: message_printer.c */ 
	    exit(EXIT_FAILURE) ;
	  }
	  else {
	    from_time_is_set=true ;
	    to_time_is_set=true ;
	  }
	}
	else {
	  print_help(argv[0]) ;
	  exit(EXIT_FAILURE) ;
	}
	break ;
	
      
      case 20 :
	
	/** --disable
	 * We set all the date and time tables on 0 values what disable the blocking.
	 *****************************************************************************/
	
	reset=true ;
        break ;	
      
      case 21 :
	
	/** --help
	 * Print help message and exit.
	 *******************************/
	
	print_help(argv[0]) ;
	exit(EXIT_FAILURE) ;
	break ;
	
      case 22 :
	
	/** --display-logs
	 * Display the system attemp logs if there are some.
	 ****************************************************/
	
	read_logs() ;
	exit(EXIT_SUCCESS) ;
	break ;
	
      case 'h' :
	
	/** -h
	 * Print help message and exit.
	 *******************************/
	
	print_help(argv[0]) ;
	exit(EXIT_FAILURE) ;
	break ;
      
      default :
	
	/** default case.
	 * Print help message and exit.
	 *******************************/
	
	print_help(argv[0]) ;
	exit(EXIT_FAILURE) ;
	break ;
    }
  }
  
  // If some variable set the call is an setting operation
  if ( from_date_is_set || to_date_is_set || from_time_is_set || to_time_is_set || reset )  {
    /** Check if the configuration of the blocking is complete with the --from-* && --to-* arguments. */
    if (! from_date_is_set && ! reset) {
      print_help(argv[0]) ;
      print_options_incomplete(0) ; /** Print an error message append at the end from the help display. 	sea: message_printer.c */
      exit(EXIT_FAILURE) ;
    }
    else if (! to_date_is_set && ! reset) {
      print_help(argv[0]) ;
      print_options_incomplete(1) ; /** Print an error message append at the end from the help display. 	sea: message_printer.c */
      exit(EXIT_FAILURE) ;
    }
    else if (! from_time_is_set && ! reset) {
      print_help(argv[0]) ;
      print_options_incomplete(2) ; /** Print an error message append at the end from the help display. 	sea: message_printer.c */
      exit(EXIT_FAILURE) ;
    }
    else if (! to_time_is_set && ! reset) {
      print_help(argv[0]) ;
      print_options_incomplete(3) ; /** Print an error message append at the end from the help display. 	sea: message_printer.c */
      exit(EXIT_FAILURE) ;
    }
    else {
      if ( reset ) {
	set_blocking_datetime(from_date,to_date,from_time,to_time,days_of_week,reset) ;
	print_blocking_disable_confirm() ; /** Print an lock disable confirmation message.			sea: message_printer.c */
	exit(EXIT_SUCCESS) ;
      }
      if (from_timer_during) {
	compute_during_to_time(from_date,from_time,to_date,to_time,block_during) ; /** Compute the lock during in case of --from-timer argument given.	sea: compute_opts_values.c */
      }
       
      if ( is_weekday_config ) {
	 if ( check_weekdays_valid_interval(from_time,to_time) < 0 ) {
	   print_help(argv[0]) ;
	   print_err_endtime_is_lt_start_time() ; /** Print an error message in case wrong time settings by weekdays configuration.				sea: message_printer.c */
	   exit(EXIT_FAILURE) ;
	 }
      }
       
      set_blocking_datetime(from_date,to_date,from_time,to_time,days_of_week,reset) ; /** Set the blocking datas in the configuration files. 		sea: handle_datas_files.c */
      
      get_datetime_for_summary(start_datetime,end_datetime,from_date,to_date,from_time,to_time) ; /** Compute the datas for generating the summary. 	sea: get_datetime_for_summary.c */
      
      if ( is_weekday_config ) {
	print_summary_weekdays(start_datetime,end_datetime,days_of_week) ; /** Print summary */
	exit(EXIT_SUCCESS) ;
      }
      else {
	print_summary_from_to(start_datetime,end_datetime) ; /** Print summary */
	exit(EXIT_SUCCESS) ;
      }
    }
  }
  
  else {
    get_blocking_datetime(from_date,to_date,from_time,to_time,days_of_week) ; /** Fetch the blocking configuration 		sea: handle_datas_files.c */
    if (check_timestamps(from_date,to_date,from_time,to_time,days_of_week) ) {
      system("shutdown -h now") ; // Shut the system down if the localtime timestamp is in range of the stored start & stops settings timestamps
      log_access_attemp() ;       // Log an system attemps if it occurs.
      
      //system("echo \'it works\' >> ~/test_programm.txt") ; // you can used this system call instead, in case of tests. 
    }
    exit(EXIT_SUCCESS) ;
  }
  print_help(argv[0]) ;
  exit(EXIT_SUCCESS) ;
 
}

int check_timestamps(int from_date[3],int to_date[3],int from_time[3],int to_time[3],int weekdays[7]) {
    
    /** Return only 1 (true) if the registered settings converted to timestamps
     *  are in the slice of the localtime.
     *  What has the effect to activate the blocking. 
     * *************************************************************************/
    
    int is_weekdays_config=check_is_config_weekdays(weekdays) ;
    
    int start_md    ;
    int start_mon   ; 
    int start_yyyy  ; 
    
    int end_md    ; 
    int end_mon   ; 
    int end_yyyy  ; 
    
    _Bool is_wday_today=false ;
    
    struct tm *start_timer ;
    struct tm *end_timer   ;
    
    struct tm *now_timer   ;
    
    start_timer =  malloc(sizeof(struct tm ))   ;
    end_timer   =  malloc(sizeof(struct tm ))   ;
    
    now_timer   =  malloc(sizeof(struct tm ))   ;
  
    time_t start_timestamp = (time_t) malloc(sizeof(time_t)) ; // memory allocation needed for mktime()
    time_t end_timestamp   = (time_t) malloc(sizeof(time_t)) ; // memory allocation needed for mktime()
  
    time_t now ;
    time(&now) ;
    now_timer=localtime(&now); //call needed for keeping update the now_timer struct
    
    int isdst=-1 ; //mktime() auto-compute the summertime offset ;
    

    if ( is_weekdays_config ) {
      // wday is configured we check if today is selected
      if ( weekdays[now_timer->tm_wday] ) {
	start_md    = now_timer->tm_mday ;
	start_mon   = now_timer->tm_mon  ;
	start_yyyy  = now_timer->tm_year ;
	end_md      = now_timer->tm_mday ;
	end_mon     = now_timer->tm_mon  ;
	end_yyyy    = now_timer->tm_year ;
	is_wday_today=true ;             // wday is selected for blocking
      }
    }
    else {
      
      start_md    = from_date[0] ;
      start_mon   = from_date[1]-1 ;
      start_yyyy  = from_date[2]-1900 ; // years are set relative to 1900 
      
      end_md      = to_date[0] ;
      end_mon     = to_date[1]-1 ;
      end_yyyy    = to_date[2]-1900 ;   // years are set relative to 1900 
      
      is_wday_today=true ;              // wday is selected for blocking
      
    }
    
    start_timer->tm_sec  = from_time[2] ;
    start_timer->tm_min  = from_time[1] ;
    start_timer->tm_hour = from_time[0] ;
    start_timer->tm_mday = start_md     ;
    start_timer->tm_mon  = start_mon    ;
    start_timer->tm_year = start_yyyy   ; // years are set relative to 1900 
    start_timer->tm_wday=0 ;
    start_timer->tm_yday=0 ;
    start_timer->tm_isdst=isdst ;
    

    end_timer->tm_sec  = to_time[2] ;
    end_timer->tm_min  = to_time[1] ;
    end_timer->tm_hour = to_time[0] ;
    end_timer->tm_mday = end_md     ;
    end_timer->tm_mon  = end_mon    ;
    end_timer->tm_year = end_yyyy   ; // years are set relative to 1900 
    end_timer->tm_wday=0 ;
    end_timer->tm_yday=0 ;
    end_timer->tm_isdst=isdst ;
    
    if ((start_timestamp=mktime(start_timer)) == -1) { ;
      char *errmsg ;
      errmsg=strerror(errno) ;
      // [DEBUG: printf("timestamp computing error: %s\n",errmsg) ;
      return -1 ;
    }
    
    if ((end_timestamp=mktime(end_timer)) == -1) { ;
      char *errmsg ;
      errmsg=strerror(errno) ;
      // [DEBUG: printf("timestamp computing error: %s\n",errmsg) ;
      return -1 ;
    }
    
    
    if ( is_wday_today == false ) {
	return 0 ;
    }  
    time(&now) ;
    now_timer=localtime(&now); //call needed for keeping update the now_timer struct
    
    unsigned int start_cmp_timestamp=(unsigned int) start_timestamp ;
    unsigned int end_cmp_timestamp=(unsigned int) end_timestamp ;
    unsigned int now_cmp_timestamp=(unsigned int) now ;
    if ( start_cmp_timestamp <=  now_cmp_timestamp && now_cmp_timestamp <= end_cmp_timestamp  ) {
      return 1 ;
      
    }
    return 0 ;
}

int check_is_config_weekdays(int weekdays[7]) {
  /** Check if the configuration is from type weekdays. **/ 
  int c ;
  int ret=0 ;
  for (c=0 ; c < 7 ; c++) {
    if ( weekdays[c] == 1 ) {
      ret=1 ;
      break ;
    }
  }
  return ret ;
}
