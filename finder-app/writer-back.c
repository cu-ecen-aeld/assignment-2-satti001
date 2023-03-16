#include <stdio.h>
#include <syslog.h>
#include <string.h>

// Define Colors for the Syslog Print
#define RED     "\x1b[31m"
#define RESET   "\x1b[0m"


int main(int argc, char *argv[])
{
  if(argc!=3){
    fprintf(stderr, RED"Please Provide two arguments -> USAGE: ./writer filename str\n"RESET);
    openlog(NULL, 0, LOG_USER);
    syslog(LOG_ERR, "Invalid Number of arguments: %d", argc);
    return 1;
  }
  
  /*Openinng File*/
  FILE *openFile = fopen(argv[1], "w");

  /*Handlers for File I/O Errors*/
  if(openFile==NULL){
    fprintf(stderr, RED"The file %s cannot be opened\n"RESET, argv[1]);
    syslog(LOG_ERR, "The file %s cannot be opened", argv[1]);  
    fclose(openFile);
    return 1;
  }

  openlog(NULL, 0, LOG_USER);
  syslog(LOG_USER, "The file %s is opened", argv[1]);  
  
  
  /*Writing the Provided String into File*/
  fwrite(argv[2], 1, strlen(argv[2]), openFile);


  fclose(openFile);
  syslog(LOG_INFO, "Closing the file: %s", argv[1]);  
  
  
  return 0;
}
