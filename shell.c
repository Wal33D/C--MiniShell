//Waleed Gudah
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>


#define MAX_BUFFER 1024 // max line buffer
#define MAX_ARGS 64 // max # args
#define SEPARATORS " \t\n" // token sparators

int argc; 
char ** argv;
extern char **environ; //env variables
pid_t pid; // process ID
int status; // status for fork/exec process
int in, out, input, output, append; // I/O redirection parameters
char *inputFile, *outputFile; // I/O input and output files
FILE *fp; //pointer to file for ouput file

void cd(char *d){
	
  char * name = "PWD"; //string PWD
  char cwd[256]; // holder for current directory
  char * newCurrent = getcwd(cwd, sizeof(cwd)); //get the current dir and put it in cwd
  
	chdir(d); // change the directory
  
	setenv(name, newCurrent,1); //set new pwd

}

// get the environment variables
void env(char **e){
  
char **env = e;
  // IO redirection
  if (output == 1){

    fp = fopen(outputFile, "w");

  }

  else if (append == 1){

    fp = fopen(outputFile, "a");

  }
  
  //if ouput or append then fprintf
  if (output == 1 || append == 1){

    while(*env){

      fprintf(fp,"%s\n", *env++);

    }

    fclose(fp);

  }
  //otherwise just print to screen

  else{

    while(*env){

      printf("%s\n", *env++);

    }

  }

}

// check the command for any I/O redirection
void checkIO(char **args){
  // reset input and output and append
  input = 0;
  output = 0;
  append = 0;

  int i = 0;

  // loop through the command line input
  while(args[i] != NULL){

    if (!strcmp(args[i], "<")){ //check for input <

      strcpy(args[i], "\0");
      inputFile = args[i+1];
      input = 1;

    }


    else if (!strcmp(args[i], ">")){ //check for output >

      outputFile = args[i+1];
      args[i] = NULL;
      output = 1;
      break;

    }

    else if (!strcmp(args[i], ">>")){ //check for append output >>

      outputFile = args[i+1];
      args[i] = NULL;
      append = 1;
      break;

    }

    i++;

  }
}

//find the last non whitespace character and check if that is an ampersand
//if there is an ampersand then make dont_wait = 1
int checkBackground(char **args){

  int i =0;
  int dont_wait=0;

  while(args[i] != NULL){

    if (!strcmp(args[i], "&")){

      dont_wait = 1;

      args[i] = NULL; //remove the & and set to NULL so that the commmand will work

    }

    i++;

  }

  return dont_wait;

}

//set the shell environment variable to the <homepath>/myshell
void setMyShellEnv(){

  char home_path[1024];

  getcwd(home_path, 1024);

  strcat(home_path, "/myshell");

  setenv("shell", home_path, 1);
}

// the main function - where all the magic happens
void shell(){
	
  char buf[MAX_BUFFER];
  char * args[MAX_ARGS];
  char ** arg;
  char * prompt = "Waleed's Shell:";
  int dont_wait =0;
  int status;

 
  setMyShellEnv(); // get the shell environment

  //check access first
  if(argc > 1) {
	
    freopen(argv[1], "r", stdin);

  }

  while(!feof(stdin)){
	
    fputs(prompt, stdout);

    if(fgets(buf, MAX_BUFFER, stdin)){
	
      arg = args;
      *arg++ = strtok(buf,SEPARATORS);

      while ((*arg++ = strtok(NULL,SEPARATORS)));

      checkIO(args); //check i/o redirections

      dont_wait = checkBackground(args); // check for background execution (that is &)

      if (args[0]) {
        // if there was an input redirection (<)
        if (input == 1){
	
          if(!access(inputFile, R_OK)){ //check access

            freopen(inputFile, "r", stdin); // replace the stdin with the file
        
			}

        }

        // INTERNAL COMMAND HERE:

        if (!strcmp(args[0],"cd")) { //change directory
          cd(args[1]); //call the helper function
          continue;
        }

        //print out all args after echo - disregard white space and tabs
        if (!strcmp(args[0],"echo")) {
	
          pid = getpid(); // get process id
          switch(pid = fork()){
	
            case 0:
              setenv("parent", getenv("shell"), 1); //set parent

              //i/o redirection for output files
              if(output == 1)

                freopen(outputFile, "w", stdout);

              else if(append == 1)

                freopen(outputFile, "a+", stdout);

              execvp (args[0], args); //execute in the child thread
             

            default:

              if (!dont_wait) //determine background execution wait (&)

                waitpid(pid, &status, WUNTRACED);
          }
          continue;
        }

               if (!strcmp(args[0],"exit")) {
	
          break; //break the loop so the program returns and ends

        }

        // no more internal commands
        // from here we run external commands
        else{
	
          pid = getpid();

          switch (pid = fork ()) {
    
	        case 0:
	
              setenv("parent", getenv("shell"), 1); //set parent
              //i/o redirection
              if(output == 1)

                freopen(outputFile, "w", stdout);

              else if(append == 1)

                freopen(outputFile, "a+", stdout);

              execvp (args[0], args); //execute in child thread
            
            default:

              if (!dont_wait) //determine background execution wait (&)

                waitpid(pid, &status, WUNTRACED);

        }

          continue;

        }


      }

	}

  }

}



