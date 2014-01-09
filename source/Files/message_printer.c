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

/********************************************/
/* This file is used for all the:           */
/* -> errors                                */ 
/* -> summary                               */
/* displaying functions.                    */
/********************************************/

void print_err_msg(int date,int time,int timer,int format,int value) {
  
  /* *****************************************************************/
  /* Print an error message append at the end from the help display. */
  /* in case of data | time settings errors from type:               */
  /* format : the format of settings is wrong.                       */ 
  /* value  : the value is not a date | time valid value.            */
  /* *****************************************************************/
  
  if (date  && format ) {
    printf("\n\t\t\tWrong date format !!!\n\t\t\tRight date format is: dd/mm/yyyy\n\n") ;

    return ;
  }
  if (time && format) {
    printf("\n\t\t\tWrong time format !!!\n\t\t\tRight time format is: hh:mm:ss\n\n") ; 
    return ;
  }
  if (timer && format) {
    printf("\n\t\t\tWrong timer format !!!\n\t\t\tRight timer format is: hh:mm:ss-hh:mm:ss\n\t\t\t                       %s\n\n",(format == 1) ? "[start_time-during]" : "[start_time-stop_time]") ; 
    return ;
  }
    
  if (date  && ( -1 > value && value > -5) ) {
    printf("\n\t\t\tWrong date value !!!\n\t\t\tRight date value is: %s \n\n",((value == -2) || (value == -3)) ? ((value == -2) ? "for days [1-31]" : "for month [1-12]") : "for years [2013-2037]") ;

    return ;
  }
  if (time  && ( -1 > value && value > -5) ) {
    printf("\n\t\t\tWrong time value !!!\n\t\t\tRight time value is: %s \n\n",((value == -2) || (value == -3)) ? ((value == -2) ? "for hours [0-23]" : "for minutes [0-59]") : "for seconds [0-59]") ;

    return ;
  }
  if (timer  && ( -1 > value && value > -5) ) {
    printf("\n\t\t\tWrong timer value !!!\n\t\t\tRight timer value is: %s \n\n",((value == -2) || (value == -3)) ? ((value == -2) ? "for hours [0-23]" : "for minutes [0-59]") : "for seconds [0-59]") ;

    return ;
  }
  else {
    printf("\n\t\t\tWrong day selection format !!!\n\t\t\tRight day selection format is: [mon,tue,wed,thu,sat,fri,sat,sun]\n\n") ;
  }
}


void print_summary_from_to(struct tm *start,struct tm *end) {
  
  /***********************************************************/
  /* Print an summary in case of not regular block settings: */
  /* from an date & time                                     */
  /* to   an date & time                                     */
  /***********************************************************/
  
  char *start_time_display=malloc(80+1) ;  // Terminal width == 80 char
  char *end_time_display=malloc(80+1) ;    // Terminal width == 80 char  
  char *little_sep=malloc(80+1) ;          // Terminal width == 80 char
  char *big_sep=malloc(80+1) ;             // Terminal width == 80 char
  
  /* set the separators lines */
  strcpy(big_sep," +=========================================================================+\n") ;
  strcpy(little_sep," +------+-----------------------------------------+------------------------+\n") ;
  
  /* format start && end block time for presenting to the user */
  /*********************************************************************************************/
  /* bugfix: the compilator display an warning by the field length use for:                    */
  /*         the day of week: %9A                                                              */
  /*         the month      : %9B                                                              */
  /*         by using the strftime() function.                                                 */
  /*********************************************************************************************/
  strftime(start_time_display, 80, " | From | %9A %2d %9B %Y at %H:%M:%S | %2d/%2m/%Y at %H:%M:%S |\n",start);
  strftime(end_time_display, 80,   " | To   | %9A %2d %9B %Y at %H:%M:%S | %2d/%2m/%Y at %H:%M:%S |\n",end);
  
  /* print summary display */
  printf("\n\n") ;
  printf(" %s",big_sep) ;
  printf("  |                                %s                             |\n","System lock ") ;
  printf(" %s",big_sep) ;
  printf("  |                                                                         |\n") ;
  printf(" %s",little_sep) ; 
  printf(" %s",start_time_display) ;
  printf(" %s",little_sep) ; 
  printf(" %s",end_time_display) ;
  printf(" %s",little_sep) ;
  printf("  |                                                                         |\n") ;
  printf(" %s",big_sep) ;
  printf("\n\n") ;
   
  free(start_time_display) ;
  free(end_time_display) ;
  free(little_sep) ;
  free(big_sep) ;
}

void print_blocking_disable_confirm(void) {
   /***********************************************************/
   /* Print an lock disable confirmation message              */
   /***********************************************************/
   
   char *little_sep=malloc(80+1) ;          // Terminal width == 80 char
   char *big_sep=malloc(80+1) ;             // Terminal width == 80 char  
   
   /* set the separators lines */
   strcpy(big_sep," +=========================================================================+\n") ;
   strcpy(little_sep," +-------+--------------+----------+-------------------+-------------------+\n") ;
   
    printf("\n\n") ;
    printf(" %s",big_sep) ;
    printf("  |                            %s                         |\n","System lock disabled") ;
    printf(" %s",big_sep) ;
    printf("\n\n") ;
}
void print_summary_weekdays(struct tm *start,struct tm *end,int weekdays[7]) {
  char weekdays_print[7][10]={"Sunday","Monday","Thuesday","Wednesday","Thursday","Friday","Saturday"} ;

  char *from_time=malloc(10+1) ;
  char *to_time=malloc(10+1) ;
  char *little_sep=malloc(80+1) ;          // Terminal width == 80 char
  char *big_sep=malloc(80+1) ;             // Terminal width == 80 char
  
  /* set the separators lines */
  strcpy(big_sep," +=========================================================================+\n") ;
  strcpy(little_sep," +-------+--------------+----------+-------------------+-------------------+\n") ;
  
  /* Generate the from and to lock time strings */
  /* format start && end block time for presenting to the user */
  strftime(from_time, 10, "%H:%M:%S",start);
  strftime(to_time,10,"%H:%M:%S",end);
  
  /* print summary display */
  printf("\n\n") ;
  printf(" %s",big_sep) ;
  printf("  |                                %s                             |\n","System lock ") ;
  printf(" %s",big_sep) ;
  printf("  |                                                                         |\n") ;
  printf(" %s",little_sep) ; 
  int c ;
  for ( c=0 ; c < 7 ; c++) {
    // Check if weekday is set 
    if (weekdays[c]) {
      // Print string for this occurence 
      printf("  | Every |   %9s  |  Locked  |  From:  %s  |   To:  %s   |\n",weekdays_print[c],from_time,to_time) ;
      printf(" %s",little_sep) ; 
    }
  }
  printf("  |                                                                         |\n") ;
  printf(" %s",big_sep) ;
  printf("\n\n") ;
   
  free(from_time) ;
  free(to_time) ;
  free(little_sep) ;
  free(big_sep) ;
}

void print_help(char *prg_name) {
  printf("\n\tusage: %s [date-option(s)] [time-option(s)]\n\n",prg_name) ;
  printf(" Date settings options:\n") ;
  printf(" --from-date     \tSet the date since the blocking is activ.\n") ;
  printf("                 \tIn format: dd/mm/yyyy.\n") ;
  printf(" --to-date       \tSet the date wenn the blocking end.\n") ;
  printf("                 \tIn format: dd/mm/yyyy.\n") ;
  printf(" --today         \tSet the blocking only for today.\n") ;
  printf(" --days          \tSet the days wenn the blocking is activ.\n") ;
  printf("                 \tIn format: [mon,tue,wed,thu,fri,sat,sun].\n") ;
  printf("                 \tYou can set one ore more days from the list,\n") ;
  printf("                 \tseparate with an comma.\n") ;
  printf(" --every-day     \tThe block is active every day.\n") ;
  printf("                 \tthis is an shortcut for:\n") ;
  printf("                 \t--days mon,thue,wed,thu,fri,sat,sun\n") ;
  printf(" --week-days     \tThe block is active every week day.\n") ;
  printf("                 \tThis is an shortcut for:\n") ;
  printf("                 \t--days mon,thue,wed,thu,fri.\n") ;
  printf(" --weekend-days  \tThe block is active every weekend day.\n") ;
  printf("                 \tThis is an shortcut for:\n") ;
  printf("                 \t--days sat,sun.\n") ;
  printf(" Time settings options:\n") ;
  printf(" --from-time     \tSet the time since the blocking is activ.\n") ;
  printf("                 \tIn format: hh:mm:ss.\n") ;
  printf(" --to-time       \tSet the time wenn the blocking end.\n") ;
  printf("                 \tIn format: hh:mm:ss.\n") ;
  printf(" --time-slice    \tSet the start time and the end time of the block.\n") ;
  printf("                 \tIn format [Start-time]-[End-time].\n") ;
  printf("                 \tThis is an shortcut for:\n") ;
  printf("                 \t--from-time hh:mm:ss --to-time hh:mm:ss.\n") ;
  printf("                 \tin format hh:mm:ss-hh:mm:ss.\n") ;
  printf(" --from-timer    \tSet an start time and the during of the block.\n") ;
  printf("                 \tIn format [Start-time]-[During].\n") ;
  printf("                 \tIn format hh:mm:ss-hh:mm:ss.\n") ;
  printf(" Managing option:\n") ;
  printf(" --disable       \tReset the actual blocking settings.\n") ;
  printf(" --display-logs  \tDisplay the logged system attemps.\n") ;
  printf(" --help          \tDisplay this help message.\n") ;
  printf("\n") ;
  
}

void print_options_incomplete(int opt) {
  
  /* *****************************************************************/
  /* Print an error message append at the end from the help display. */
  /* in case of data | time settings missing:                        */
  /* *****************************************************************/
  
  if (opt == 0) {
    printf("Error: No Start date specify use : --from-date to set the blocking start date.\n") ;
  }
  else if (opt == 1) {
    printf("Error: No end date specify use   : --to-date to set the blocking release date.\n") ;
  }
  else if (opt == 2) {
    printf("Error: No start time specify use : --from-time to set the blocking start time.\n") ;
  }
  else if (opt == 3) {
    printf("Error: No end time specify use   : --to-time to set the blocking end time.\n") ;
  }
  
    
}

void print_err_endtime_is_lt_start_time(void) {
  
  /* *****************************************************************/
  /* Print an error message append at the end from the help display. */
  /* in case of data | time settings missing:                        */
  /* *****************************************************************/
  printf("\nError: Wrong time settings, stop blocking time littler than start blocking time.\n\n") ;
  printf("This error can occurs by setting midnight...                            \nBecause 0:0:0 o'clock is the first second from the current days.\n\n") ;
  return ;  
}

void print_wrong_user(char *prg_name) {
  
  /* *****************************************************************/
  /* Print an error message append at the end from the help display. */
  /* in case of not as root user programm launching.                 */
  /* *****************************************************************/
  
  char *name ;
  if ((name=strrchr(prg_name, '/')) != NULL) {
    printf("\n\t\t\t%s must be run as root\n\n",++name) ;
  }
  else {
    printf("\n\t\t\t%s must be run as root\n\n",prg_name) ;
  }
}

void get_datetime_for_summary(struct tm *start_timer,struct tm *end_timer,int from_date[3],int to_date[3],int from_time[3],int to_time[3]) {
    
    /* Compute the time settings for summary displaying values used */
    
    time_t start_timestamp = (time_t) malloc(sizeof(time_t)) ; // memory allocation needed for mktime()
    time_t end_timestamp   = (time_t) malloc(sizeof(time_t)) ; // memory allocation needed for mktime()
    
    start_timer->tm_sec  = from_time[2] ;
    start_timer->tm_min  = from_time[1] ;
    start_timer->tm_hour = from_time[0] ;
    start_timer->tm_mday = from_date[0]        ;
    start_timer->tm_mon  = from_date[1]-1      ; // in from_date table january == 1 
    start_timer->tm_year = from_date[2]-1900   ; // years are set relative to 1900 
    start_timer->tm_wday=0   ;  // auto-compute by the mktime function()
    start_timer->tm_yday=0   ;  // auto-compute by the mktime function()
    start_timer->tm_isdst=-1 ;  // auto-compute by the mktime function()
    

    end_timer->tm_sec  = to_time[2] ;
    end_timer->tm_min  = to_time[1] ;
    end_timer->tm_hour = to_time[0] ;
    end_timer->tm_mday = to_date[0]       ;
    end_timer->tm_mon  = to_date[1]-1     ; // in to_date table january == 1 
    end_timer->tm_year = to_date[2]-1900  ; // years are set relative to 1900 
    end_timer->tm_wday=0   ;  // auto-compute by the mktime function()
    end_timer->tm_yday=0   ;  // auto-compute by the mktime function()
    end_timer->tm_isdst=-1 ;  // auto-compute by the mktime function()
    
    if ((start_timestamp=mktime(start_timer)) == -1) { ;
      char *errmsg ;
      errmsg=strerror(errno) ;
      printf("timestamp computing error: %s\n",errmsg) ;
      return ;
    }
   
   if ((end_timestamp=mktime(end_timer)) == -1) { ;
      char *errmsg ;
      errmsg=strerror(errno) ;
      printf("timestamp computing error: %s\n",errmsg) ;
      return  ;
    }
    return  ;
}
   
