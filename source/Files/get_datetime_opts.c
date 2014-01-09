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
/* This file is used to check the given arguments                    */
/* and return an negativ return code used in the message_printer.c   */
/* file for given an error message.                                  */
/* The function return 0 if argument valid                           */
/*********************************************************************/

int today_arg(int from_date[3],int to_date[3]) {
  
  /*************************************************************/
  /* Compute localtime date in case of --today argument given. */
  /* and setting from the from_date and to_date tables.        */
  /*************************************************************/
  
  struct tm *now_timer ;
  now_timer   =  malloc(sizeof(struct tm ))   ;
  time_t now ;
  time(&now) ;
  now_timer=localtime(&now); //call needed for keeping update the now_timer struct
  from_date[0]=to_date[0]=now_timer->tm_mday      ;
  from_date[1]=to_date[1]=now_timer->tm_mon+1     ; // in to_date & from_date table january == 1 
  from_date[2]=to_date[2]=now_timer->tm_year+1900 ;
  return 0 ;
}

int from_date_arg(char *arg,int date[3]) {
  
  /****************************************/
  /* Check the --from-date given argument */
  /****************************************/
  
  int ret ;
  if ((ret=sscanf(arg,"%d/%d/%d",&date[0],&date[1],&date[2])) != 3) {
    /** Wrong --from-date argument format *
     *  from sscanf() detected !          */ 
    return -1 ;
  }
  else {
    /** Wrong --from-date argument format *
     *  arguments out of range.           */ 
    if ( date[0] < 1 || date[0] > 31 ) {
      return -2 ;
    }
    if ( date[1] < 1 || date[1] > 12 ) {
      return -3 ;
    }
    if ( date[2] < 2012 || date[2] > 2037 ) {
      return -4 ;
    }
    return 0 ; /** Arguments OK !!! */
  }
}
  
  
int to_date_arg(char *arg,int date[3]) {
  
  /****************************************/
  /* Check the --to-date given argument   */
  /****************************************/
  
  int ret ;
  if ((ret=sscanf(arg,"%d/%d/%d",&date[0],&date[1],&date[2])) != 3) {
    /** Wrong --to-date argument format    *
     *  from sscanf() detected !           */ 
    return -1 ;
  }
  else {
    /** Wrong --to-date argument format *
    *  arguments out of range.          */ 
    if ( date[0] < 1 || date[0] > 31 ) {
      return -2 ;
    }
    if ( date[1] < 1 || date[1] > 12 ) {
      return -3 ;
    }
    if ( date[2] < 2012 || date[2] > 2037 ) {
      return -4 ;
    }
    return 0 ; /** Arguments OK !!! */
  }
  
}

int days_arg(char *arg,int days[7]) {
  
  /****************************************/
  /* Check the --days given argument      */
  /****************************************/
  
  char *days_str[7]={"sun","mon","tue","wed","thu","fri","sat"} ; // valid --days option arguments
  char *days_get[7] ;
  int match_counter=0 ;
  
  memset(&days_get,'\0',7) ;
  
  // variable declaration used for:
  // parsing the given argument who must be a [day | list of days, separate with an comma]
  // and used for the return code.   
  char *str_to_split=malloc(strlen(arg)+1) ;
  strcpy(str_to_split,arg) ;
  char *token ;
  int index=0 ;
  int occ_counter, occ_ok ;
  occ_counter = occ_ok = 0 ;
  
  while (str_to_split != NULL) {
    /* Parse argument days list */ 
    token=strtok(str_to_split,",") ; 
    if (token == NULL) {
      break ;
      }
    else {
      str_to_split += strlen(token)+1 ; 
      days_get[index]=token ;
      int c ;
      occ_counter++ ;
      for (c=0 ; c < 7 ; c++) {
	if (strncmp(days_get[index],days_str[c],5) == 0 ) {
	  /* check if the given day(s) is valid */
	  
	  memset(&days[c],1,1) ; // setting the given days 
	  match_counter++ ;      // used as return code
	  occ_ok++ ;
	}
      }
    }
  }
    
  if (occ_counter == occ_ok && match_counter) {
    return match_counter ; // an positiv value signify the parser loop find valid value(s)
  }
  else {
    return -1 ;
  }
 }
 
int from_time_arg(char *arg,int time[3]) {
  
  /****************************************/
  /* Check the --from-time given argument */
  /****************************************/
  
  int ret ;
  if ((ret=sscanf(arg,"%d:%d:%d",&time[0],&time[1],&time[2])) != 3) {
    /** Wrong --from-time argument format  *
     *  from sscanf() detected !           */ 
    return -1 ;
  }
  else {
    /** Wrong --from-time argument format  *
    *  arguments out of range.             */ 
    if ( time[0] < 0 || time[0] > 23 ) {
      return -2 ;
    }
    if ( time[1] < 0 || time[1] > 59 ) {
      return -3 ;
    }
    if ( time[2] < 0 || time[2] > 59 ) {
      return -4 ;
    }
    return 0 ; /** Arguments OK !!! */
  }
}
  
  
int to_time_arg(char *arg,int time[3]) {
  
  /****************************************/
  /* Check the --to-time given argument   */
  /****************************************/
  
  int ret ;
  if ((ret=sscanf(arg,"%d:%d:%d",&time[0],&time[1],&time[2])) != 3) {
    /** Wrong --to-time argument format    *
     *  from sscanf() detected !           */ 
    return -1 ;
  }
  else {
    /** Wrong --from-time argument format  *
    *  arguments out of range.             */ 
    if ( time[0] < 0 || time[0] > 23 ) {
      return -2 ;
    }
    if ( time[1] < 0 || time[1] > 59 ) {
      return -3 ;
    }
    if ( time[2] < 0 || time[2] > 59 ) {
      return -4 ;
    }
    return 0 ; /** Arguments OK !!! */
  }
  
}

int from_timer(char *arg,int time[3],int during[3]) {
  
  /*****************************************/
  /* Check the --from-timer given argument */
  /*****************************************/
  
  int ret ;
  if ((ret=sscanf(arg,"%d:%d:%d-%d:%d:%d",&time[0],&time[1],&time[2],&during[0],&during[1],&during[2])) != 6) {
    /** Wrong --from-timer argument format  *
     *  from sscanf() detected !           */ 
    return -1 ;
  }
  else {
    /** Wrong --from-time argument format  *
    *  arguments out of range.             */ 
    if ( time[0] < 0 || time[0] > 23) {
      return -2 ;
    }
    if ( time[1] < 0 || time[1] > 59) {
      return -3 ;
    }
    if ( time[2] < 0 || time[2] > 59 ) {
      return -4 ;
    }
    if ( during[0] < 0 || during[0] > 23 ) {
      return -2 ;
    }
    if ( during[1] < 0 || during[1] > 59 ) {
      return -3 ;
    }
    if ( during[2] < 0 || during[2] > 59 ) {
      return -4 ;
    }
    return 0 ; /** Arguments OK !!! */
  }
}

int timer_slice(char *arg,int time_start[3],int time_end[3]) {
  
  /*****************************************/
  /* Check the --time-slice given argument */
  /*****************************************/
  
  int ret ;
  if ((ret=sscanf(arg,"%d:%d:%d-%d:%d:%d",&time_start[0],&time_start[1],&time_start[2],&time_end[0],&time_end[1],&time_end[2])) != 6) {
    /** Wrong --timer-slice argument format *
     *  from sscanf() detected !            */ 
    return -1 ;
  }
  else {
    /** Wrong --from-time argument format  *
    *  arguments out of range.             */ 
    if ( ( time_start[0] < 0 || time_start[0] > 23) || ( time_end[0] < 0 || time_end[0] > 23) ) {
      return -2 ;
    }
    if ( ( time_start[1] < 0 || time_start[1] > 59 ) || ( time_end[1] < 0 || time_end[1] > 59) ) {
      return -3 ;
    }
    if ( ( time_start[2] < 0 || time_start[2] > 59 ) || ( time_end[2] < 0 || time_end[2] > 59) ) {
      return -4 ;
    }
  }
  return 0 ; /** Arguments OK !!! */
}
  