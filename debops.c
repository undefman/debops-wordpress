// Let's assume this program is called popen-test
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int runcmd(char * command){

   //char * command = "ping google.com -c 1";
   /*
      char *buffer;
      char command[1024]; // Make it large enough.
      strcpy(command, "ping");
      for(int i = 1; i<= 10; i++) {
      if (argv[i] != NULL) {
         buffer = malloc(strlen(argv[i]) + 5);
         strcpy(buffer, argv[i]);
         strcat(command, " ");
         strcat(command, buffer);
         free(buffer);
      } else {
         break;
      }
      }


      printf("command: %s\n", command);
   */

   FILE *stream;
   char string[ 256 ] = { 0 };
   int term_status;
   // printf( "[popen-test] start\n" );
   // be sure to include the full path in your command
   // here the pipe will be opened for reading and stream will be read-only

   stream = popen( command, "r" );
   if( NULL == stream )
   {
      fprintf( stderr, "Failed to run command!\n" );
      return EXIT_FAILURE;
   }
   // here you can read from the command you executed until it ends
   while( NULL != fgets( string, sizeof( string ) - 1, stream ) )
   {
      // note the '\n' character will be stored in string[]
      // the parentheses are used as a delimiter
      printf( "%s", string );
   }
   // since fgets returned NULL there are 2 options: EOF was found or an error
   // occured (use ferror for the latter)
   if( feof( stream ) )
   {
      printf( "\n\nCommand finished normally!\n" );
   }
   // even though stream is a FILE, don't use flcose
   term_status = pclose( stream );
   if( -1 != term_status )
   {
      // WEXITSTATUS can be used to get the command's exit status
      printf( "Command's exit status: %d\n", WEXITSTATUS( term_status ) );
   }
   else
   {
      fprintf( stderr, "Command close failed\n" );
      return EXIT_FAILURE;
   }
   printf( "Done\n" );
   return EXIT_SUCCESS;

}

int main( int argc, char *argv[] )
{

   if (strcmp(argv[1], "1") == 0) {
   	char *hosts_file = "./inventory/hosts";
   	printf("Stage #1\n");
   	remove(hosts_file);
   	if (argv[2] == NULL) {
   		printf("Please specify your host!\n");
   		exit(1);
   	}

   	char hosts_data[512];
   	sprintf(hosts_data, "[debops_all_hosts]\n%s\n[wordpress]\n%s\n", argv[2], argv[2]);
   	printf("%s", hosts_data);

   	FILE *opening = fopen(hosts_file, "w");
   	fprintf(opening, "%s", hosts_data);
   	fclose(opening);

   	exit(0);

   } else if (strcmp(argv[1], "2") == 0) {
   	printf("Stage #2\n");


   } else if (strcmp(argv[1], "3") == 0) {
   	printf("Stage #3\n");


   } else {
   	printf("Unknown command!\n");
   	exit(1);
   }

}
