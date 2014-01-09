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

/*****************************************************/
/* This file is used for logging of systems attemps. */
/*****************************************************/

void log_access_attemp(void) {
  char *msg=malloc(96) ;
  
  time_t now ;
  time(&now) ;
  struct tm *log_time=malloc(sizeof(struct tm)) ;
  log_time=localtime(&now) ;
  
  /* generate the log string */
  strftime(msg,96,"datetime-lock: System attempt the %d/%m/%y at %T\n",log_time) ;
  write_log(msg) ; //
  return  ;
}

  
