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

/*********************************************************************/
/* This file is used to compute the blocking in case of use from the */
/* option --from-timer option.                                       */
/* and set the blocking settings                                     */
/*********************************************************************/

int compute_during_to_time(int from_date[3],int from_time[3],int to_date[3],int to_time[3],int during[3]) {
  
  /**************************************************************************/
  /* function needed by the --from-timer option to compute the lock during  */
  /* for setting the lock start date & time and the lock stop date & time.  */
  /**************************************************************************/
  
  struct tm *start_timer ;
  start_timer =  malloc(sizeof(struct tm ))   ;
  struct tm *end_timer ;
  end_timer   =  malloc(sizeof(struct tm ))   ;
  
  time_t start_timestamp = (time_t) malloc(sizeof(time_t)) ; // memory allocation needed for mktime()
  time_t end_timestamp   = (time_t) malloc(sizeof(time_t)) ; // memory allocation needed for mktime()
  
  int isdst=-1 ; //mktime() auto-compute the summertime offset ;
  
  start_timer->tm_sec  = from_time[2] ;
  start_timer->tm_min  = from_time[1] ;
  start_timer->tm_hour = from_time[0] ;
  start_timer->tm_mday = from_date[0]      ; 
  start_timer->tm_mon  = from_date[1]-1    ; // in from_date table january == 1 
  start_timer->tm_year = from_date[2]-1900 ; // years are set relative to 1900 
  start_timer->tm_wday = 0    ; // auto-compute by the mktime function()
  start_timer->tm_yday = 0    ; // auto-compute by the mktime function()
  start_timer->tm_isdst=isdst ; // auto-compute by the mktime function()
  
  end_timer->tm_sec  = start_timer->tm_sec  + during[2] ;
  end_timer->tm_min  = start_timer->tm_min  + during[1] ;
  end_timer->tm_hour = start_timer->tm_hour + during[0] ;
  end_timer->tm_mday = to_date[0]       ;
  end_timer->tm_mon  = to_date[1]-1     ; // in to_date table january == 1 
  end_timer->tm_year = to_date[2]-1900  ; // years are set relative to 1900 
  end_timer->tm_wday = 0    ; // auto-compute by the mktime function()
  end_timer->tm_yday = 0    ; // auto-compute by the mktime function()
  end_timer->tm_isdst=isdst ; // auto-compute by the mktime function()
  
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

   end_timer=localtime(&end_timestamp);

   to_date[0]=end_timer->tm_mday      ;
   to_date[1]=end_timer->tm_mon+1     ; // in to_date table january == 1 
   to_date[2]=end_timer->tm_year+1900 ; // years are set relative to 1900 
   
   to_time[0]=end_timer->tm_hour ;
   to_time[1]=end_timer->tm_min  ;
   to_time[2]=end_timer->tm_sec  ;
   return 0 ;
   
}
      
  
  
int check_weekdays_valid_interval(int from_time[3],int to_time[3]) {
  
  /**************************************************************************/
  /* function needed by the --from-timer option to compute the lock during  */
  /* for setting the lock start date & time and the lock stop date & time.  */
  /**************************************************************************/
  
  struct tm *start_timer ;
  start_timer =  malloc(sizeof(struct tm ))   ;
  struct tm *end_timer ;
  end_timer   =  malloc(sizeof(struct tm ))   ;
  
  time_t start_timestamp = (time_t) malloc(sizeof(time_t)) ; // memory allocation needed for mktime()
  time_t end_timestamp   = (time_t) malloc(sizeof(time_t)) ; // memory allocation needed for mktime()
  
  struct tm *now_timer ;
  now_timer   =  malloc(sizeof(struct tm ))   ;
  time_t now ;
  time(&now) ;
  now_timer=localtime(&now); //call needed for keeping update the now_timer struct
  
  int isdst=-1 ; //mktime() auto-compute the summertime offset ;
  
  start_timer->tm_sec  = from_time[2] ;
  start_timer->tm_min  = from_time[1] ;
  start_timer->tm_hour = from_time[0] ;
  start_timer->tm_mday = now_timer->tm_mday      ; 
  start_timer->tm_mon  = now_timer->tm_mon       ; // in from_date table january == 1 
  start_timer->tm_year = now_timer->tm_mday      ; // years are set relative to 1900 
  start_timer->tm_wday = 0 ;
  start_timer->tm_yday = 0 ;
  start_timer->tm_isdst=isdst ;
  
  end_timer->tm_sec  = to_time[2] ;
  end_timer->tm_min  = to_time[1] ;
  end_timer->tm_hour = to_time[0] ;
  end_timer->tm_mday = now_timer->tm_mday      ; 
  end_timer->tm_mon  = now_timer->tm_mon       ; // in from_date table january == 1 
  end_timer->tm_year = now_timer->tm_mday      ; // years are set relative to 1900 
  end_timer->tm_wday = 0 ;
  end_timer->tm_yday = 0 ;
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
   

   
   return difftime(end_timestamp,start_timestamp) ;
   
}
      
    