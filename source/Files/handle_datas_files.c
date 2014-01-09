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
/* This file is used for all file operations:                        */
/* Writing a log string into the log file.                           */
/* and set the blocking settings into files.                         */
/*********************************************************************/

#define SET_0000  0000
#define SET_WRITE S_IWUSR
#define SET_READ  S_IRUSR
#define SET_EXE   S_IXUSR

#define DIR_PATH             "/usr/share/datetime-lock/"


#define BLOCK_FROM_DATE_FILE  DIR_PATH"from_date"
#define BLOCK_TO_DATE_FILE    DIR_PATH"to_date"
#define BLOCK_FROM_TIME_FILE  DIR_PATH"from_time"
#define BLOCK_TO_TIME_FILE    DIR_PATH"to_time"
#define BLOCK_WEEK_DAYS       DIR_PATH"week_days"

#define LOG_FILE              DIR_PATH"logs"

int dir_exist(int read)  {
  /* check if dir DIR_PATH exit and create it if not exist */
  
  DIR *dir_fp ;
  
  if ((dir_fp=opendir(DIR_PATH)) == NULL ) {
    if (! read) {
      if (mkdir(DIR_PATH,SET_WRITE | SET_READ | SET_EXE ) == -1) {
	char *errmsg ;
	errmsg=strerror(errno) ;
	fprintf(stderr,"%s : %s\n",errmsg,DIR_PATH) ;
	return 1 ;
	}
      else {
	return 0 ;
      }
    }
    else {
      return 1 ;
    }
  }
  else {
    closedir(dir_fp);
    return 0 ;
  }
}
  

int write_log(char *msg) {
  FILE *fp_log_file ;
  
  if (dir_exist(0)) {
    // Create directory DIR_PATH if not exit 
    
  }
  
  if (chmod(LOG_FILE,SET_WRITE) == -1 ) {
    //return -1 ;
    }
  if ((fp_log_file=fopen(LOG_FILE,"a")) == NULL) {
    char *errmsg ;
    errmsg=strerror(errno) ;
    fprintf(stderr,"%s : %s\n",errmsg,LOG_FILE) ;
    return -1 ;
    }
  else {
    fputs(msg,fp_log_file); // setting the, from date, serialized data in file.
    fclose(fp_log_file) ;
    chmod(LOG_FILE,SET_0000) ;
    }
  return 0 ;  
}

int read_logs(void) {
  FILE *fp_log_file ; 
  
  if (dir_exist(1)) {
    // Check if directory DIR_PATH if exist  
    return -1 ;
  }
  
  if (chmod(LOG_FILE,SET_READ) == -1 ) {
    //return -1 ;
    }
  if ((fp_log_file=fopen(LOG_FILE,"r")) == NULL) {
    fp_log_file=fopen(LOG_FILE,"w") ;
    }
  
  char *msg=malloc(256) ;
  int c=0 ;
  while (fgets(msg,256,fp_log_file) != NULL) {
    printf("%s",msg); // printing log file content 
    c++ ;
  }
  if ( c == 0 ) {
    printf("No logs registered\n"); // printing error message
  }
  fclose(fp_log_file) ;
  chmod(LOG_FILE,SET_0000) ;
    
  return 0 ;  
}

int set_blocking_datetime(int from_date[3],int to_date[3],int from_time[3],int to_time[3],int weekdays[7],int reset) {
  FILE *fp_from_date ;
  FILE *fp_to_date ;
  FILE *fp_from_time ;
  FILE *fp_to_time ;
  FILE *fp_weekdays ;
  
  if (dir_exist(0)) {
    // Create directory DIR_PATH if not exit 
    return -12 ;
  }
  
  char *right="w" ; // File default open mode, only set to "a" if file not exist 
  
  if ( reset ) {
    // Reset all tables before writing them in files
    
    memset(from_date,0,3*4) ;
    memset(to_date,0,3*4) ;
    memset(from_time,0,3*4) ;
    memset(to_time,0,3*4) ;
    
    memset(weekdays,0,7*4) ;
  }
  
  if (chmod(BLOCK_FROM_DATE_FILE,SET_WRITE) == -1 ) {
    right="a" ;
    }
  if ((fp_from_date=fopen(BLOCK_FROM_DATE_FILE,right)) == NULL) {
    char *errmsg ;
    errmsg=strerror(errno) ;
    fprintf(stderr,"%s : %s\n",errmsg,BLOCK_FROM_DATE_FILE) ;
    return -2 ;
    }
  else {
    fwrite(from_date,3 *4,1,fp_from_date); // setting the, from date, serialized data in file.
    fclose(fp_from_date) ;
    chmod(BLOCK_FROM_DATE_FILE,SET_0000) ;
    }
  
  if (chmod(BLOCK_TO_DATE_FILE,SET_WRITE) == -1 ) {
    right="a" ;
    }
  if ((fp_to_date=fopen(BLOCK_TO_DATE_FILE,right)) == NULL) {
    char *errmsg ;
    errmsg=strerror(errno) ;
    fprintf(stderr,"%s : %s\n",errmsg,BLOCK_TO_DATE_FILE) ;
    return -4 ;
    }
  else {
    fwrite(to_date,3 *4,1,fp_to_date); // setting the, from date, serialized data in file.
    fclose(fp_to_date) ;
    chmod(BLOCK_TO_DATE_FILE,SET_0000) ;
    }
  
  if (chmod(BLOCK_FROM_TIME_FILE,SET_WRITE) == -1 ) {
    right="a" ;
    }
  if ((fp_from_time=fopen(BLOCK_FROM_TIME_FILE,right)) == NULL) {
    char *errmsg ;
    errmsg=strerror(errno) ;
    fprintf(stderr,"%s : %s\n",errmsg,BLOCK_FROM_TIME_FILE) ;
    return -6 ;
    }
  else {
    fwrite(from_time,3 *4,1,fp_from_time); // setting the, from date, serialized data in file.
    fclose(fp_from_time) ;
    chmod(BLOCK_FROM_TIME_FILE,SET_0000) ;
    }
  
  if (chmod(BLOCK_TO_TIME_FILE,SET_WRITE) == -1 ) {
    right="a" ;
    }
  if ((fp_to_time=fopen(BLOCK_TO_TIME_FILE,right)) == NULL) {
    char *errmsg ;
    errmsg=strerror(errno) ;
    fprintf(stderr,"%s : %s\n",errmsg,BLOCK_TO_TIME_FILE) ;
    return -8 ;
    }
  else {
    fwrite(to_time,3 *4,1,fp_to_time); // setting the, from date, serialized data in file.
    fclose(fp_to_time) ;
    chmod(BLOCK_TO_TIME_FILE,SET_0000) ;
    }
  
  if (chmod(BLOCK_WEEK_DAYS,SET_WRITE) == -1 ) {
    right="a" ;
    }
  if ((fp_weekdays=fopen(BLOCK_WEEK_DAYS,right)) == NULL) {
    char *errmsg ;
    errmsg=strerror(errno) ;
    fprintf(stderr,"%s : %s\n",errmsg,BLOCK_WEEK_DAYS) ;
    return -10 ;
    }
  else {
    fwrite(weekdays,7 *4,1,fp_weekdays); // setting the, from date, serialized data in file.
    fclose(fp_weekdays) ;
    chmod(BLOCK_WEEK_DAYS,SET_0000) ;
  }
  return 0 ;
}
  
  
int get_blocking_datetime(int from_date[3],int to_date[3],int from_time[3],int to_time[3],int weekdays[7]) {
  /* Fetch the datas from serialized files */
  
  FILE *fp_from_date ;
  FILE *fp_to_date ;
  FILE *fp_from_time ;
  FILE *fp_to_time ;
  FILE *fp_weekdays ;
  
  if (dir_exist(1)) {
    // Check if directory DIR_PATH if exist  
    return -12 ;
  }
  
  if (chmod(BLOCK_FROM_DATE_FILE,SET_READ) == -1 ) {
    char *errmsg ;
    errmsg=strerror(errno) ;
    fprintf(stderr,"%s : %s\n",errmsg,BLOCK_FROM_DATE_FILE) ;
    return -2 ;
    }
  if ((fp_from_date=fopen(BLOCK_FROM_DATE_FILE,"r")) == NULL) {
    char *errmsg ;
    errmsg=strerror(errno) ;
    fprintf(stderr,"%s : %s\n",errmsg,BLOCK_FROM_DATE_FILE) ;
    return -2 ;
    }
  else {
    fread(from_date,3 *4,1,fp_from_date); // getting the, from date, serialized data in file.
    fclose(fp_from_date) ;
    chmod(BLOCK_FROM_DATE_FILE,SET_0000) ;
    }
  
  if (chmod(BLOCK_TO_DATE_FILE,SET_READ) == -1 ) {
    char *errmsg ;
    errmsg=strerror(errno) ;
    fprintf(stderr,"%s : %s\n",errmsg,BLOCK_TO_DATE_FILE) ;
    return -4 ;
    }
  if ((fp_to_date=fopen(BLOCK_TO_DATE_FILE,"r")) == NULL) {
    char *errmsg ;
    errmsg=strerror(errno) ;
    fprintf(stderr,"%s : %s\n",errmsg,BLOCK_TO_DATE_FILE) ;
    return -4 ;
    }
  else {
    fread(to_date,3 *4,1,fp_to_date); // getting the, from date, serialized data in file.
    fclose(fp_to_date) ;
    chmod(BLOCK_TO_DATE_FILE,SET_0000) ;
    }
  
  if (chmod(BLOCK_FROM_TIME_FILE,SET_READ) == -1 ) {
    char *errmsg ;
    errmsg=strerror(errno) ;
    fprintf(stderr,"%s : %s\n",errmsg,BLOCK_FROM_TIME_FILE) ;
    return -6 ;
    }
  if ((fp_from_time=fopen(BLOCK_FROM_TIME_FILE,"r")) == NULL) {
    char *errmsg ;
    errmsg=strerror(errno) ;
    fprintf(stderr,"%s : %s\n",errmsg,BLOCK_FROM_TIME_FILE) ;
    return -6 ;
    }
  else {
    fread(from_time,3 *4,1,fp_from_time); // getting the, from date, serialized data in file.
    fclose(fp_from_time) ;
    chmod(BLOCK_FROM_TIME_FILE,SET_0000) ;
    }
  
  if (chmod(BLOCK_TO_TIME_FILE,SET_READ) == -1 ) {
    char *errmsg ;
    errmsg=strerror(errno) ;
    fprintf(stderr,"%s : %s\n",errmsg,BLOCK_TO_TIME_FILE) ;
    return -8 ;
    }
  if ((fp_to_time=fopen(BLOCK_TO_TIME_FILE,"r")) == NULL) {
    char *errmsg ;
    errmsg=strerror(errno) ;
    fprintf(stderr,"%s : %s\n",errmsg,BLOCK_TO_TIME_FILE) ;
    return -8 ;
    }
  else {
    fread(to_time,3 *4,1,fp_to_time); // getting the, from date, serialized data in file.
    fclose(fp_to_time) ;
    chmod(BLOCK_TO_TIME_FILE,SET_0000) ;
    }
  
  if (chmod(BLOCK_WEEK_DAYS,SET_READ) == -1 ) {
    char *errmsg ;
    errmsg=strerror(errno) ;
    fprintf(stderr,"%s : %s\n",errmsg,BLOCK_WEEK_DAYS) ;
    return -10 ;
    }
  if ((fp_weekdays=fopen(BLOCK_WEEK_DAYS,"r")) == NULL) {
    char *errmsg ;
    errmsg=strerror(errno) ;
    fprintf(stderr,"%s : %s\n",errmsg,BLOCK_WEEK_DAYS) ;
    return -10 ;
    }
  else {
    fread(weekdays,7 *4,1,fp_weekdays); // getting the, from date, serialized data in file.
    fclose(fp_weekdays) ;
    chmod(BLOCK_WEEK_DAYS,SET_0000) ;
  }
  return 0 ;
}
    
  
    
int check_config_weekdays(int weekdays[7]) {
  /* Check if an weekdays configuration is set */
  
  FILE *fp_weekdays ;
  
  if (chmod(BLOCK_WEEK_DAYS,SET_READ) == -1 ) {
    char *errmsg ;
    errmsg=strerror(errno) ;
    fprintf(stderr,"%s : %s\n",errmsg,BLOCK_WEEK_DAYS) ;
    return -10 ;
    }
  if ((fp_weekdays=fopen(BLOCK_WEEK_DAYS,"r")) == NULL) {
    char *errmsg ;
    errmsg=strerror(errno) ;
    fprintf(stderr,"%s : %s\n",errmsg,BLOCK_WEEK_DAYS) ;
    return -10 ;
    }
  else {
    fread(weekdays,7 *4,1,fp_weekdays); // setting the, from date, serialized data in file.
    fclose(fp_weekdays) ;
    chmod(BLOCK_WEEK_DAYS,SET_0000) ;
  }
  
  int c ;
  int result=0 ;   // Used as return code 
  for (c=0 ; c < 7 ; c++) {
    if (weekdays[c] == 1) {
      result = 1 ; // weekdays configured return 1
      break ;
    }
  }
  
  return result ;
}

