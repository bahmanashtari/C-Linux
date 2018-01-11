/* Author(s): Bahman Ashtari. Section 2.
 *
 * This is a csc60mshell.c
 * This program serves as a skeleton for starting for lab 8.
 * Student is required to use this program to build a mini shell
 * using the specification as documented in direction.
 * Date: Spring 2016
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXLINE 80
#define MAXARGS 20
#define MAX_PATH_LENGTH 50

/* function prototypes */
void process_input(int argc, char **argv);
int parseline(char *cmdline, char **argv);
void handle_redir(int count, char *argv[]);

/* ----------------------------------------------------------------- */
/*                  The main program starts here                     */
/* ----------------------------------------------------------------- */
int main(void)
{
    char cmdline[MAXLINE];
    char *argv[MAXARGS];
    int argc;
    int status;
    pid_t pid;

    /* Loop forever to wait and process commands */
    while (1) {
        /* Print your shell name: csc60mshell (m for mini shell) */
        printf("csc60mshell> ");
        fgets(cmdline, MAXLINE, stdin);

        /* Call parseline to build argc/argv: their limits declared above */
        argc = parseline(cmdline, argv);
        /* If user hits enter key without a command, continue to loop again at the beginning */
        /*  Hint: if argc is zero, no command declared */
        /*  Hint: look up for the keyword "continue" in C */
        if (argc == 0)
        {
            continue;
        }
        /* Handle build-in command: exit, pwd, or cd  */
        if ( (strcmp(argv[0], "exit") == 0) && argc == 1) //exit
        {
            exit(0);
        }
        else if ( (strcmp(argv[0], "pwd") == 0) && argc == 1) //pwd
        {
            char* wd; //working directory
            char* wdb = NULL; //wd buffer (for the purpose of function use only)
            wd = getcwd(wdb, MAX_PATH_LENGTH);
            printf("%s\n", wd);
            continue;
        }
        else if ( (strcmp(argv[0], "cd") == 0))
        {
            if (argc == 1 || //cd
                (argc == 2 && strcmp(argv[1], "~") == 0)) //cd ~
            {
                char* homeEnv = getenv("HOME");
                chdir(homeEnv);
                continue;
            }
            else //cd (directory path)
            {
                chdir(argv[1]);
                continue;
            }
        }
        /* Else, fork off a process */
        else
        {
            pid = fork();
            switch(pid)
            {
                case -1:
                    perror("Shell Program fork error");
                    exit(1);
                case 0:
                    /* I am child process. I will execute the command, call: execvp */
                    process_input(argc, argv);
                    break;
                default:
                    /* I am parent process */
                    if (wait(&status) == -1)
                        perror("Shell Program error");
                    else
                        printf("Child returned status: %d\n",status);
                    break;
            } /* end of the switch */
        }/* end of if */
    } /* end of the while */
} /* end of main */
/* ----------------------------------------------------------------- */
/*                  parseline                                        */
/* ----------------------------------------------------------------- */
/* parse input line into argc/argv format */
int parseline(char *cmdline, char **argv)
{
    int count = 0;
    char *separator = " \n\t";
 
    argv[count] = strtok(cmdline, separator);
    while ((argv[count] != NULL) && (count+1 < MAXARGS))
        argv[++count] = strtok((char *) 0, separator);
    return count;
}
/* ---------------------------------------------------------------- */
/*                  process_input                                   */
/* ---------------------------------------------------------------- */
void process_input(int argc, char **argv)
{
    /* Step 1: Call handle_redir to deal with operators:            */
    /* < , or  >, or both                                           */
    handle_redir(argc, argv);
    /* Step 2: perform system call execvp to execute command        */
    /* Hint: Please be sure to review execvp.c sample program       */
    /* if (........ == -1) {                                        */
    /*  perror("Shell Program");                                    */
    /*  _exit(-1);                                                  */
    /* }                                                            */
    char *cmd[] = {argv[0], 0};
    if (execvp(cmd[0], argv) == -1) {
        perror("Shell Program error");
        _exit(-1);
    }
    exit(0);
}
/* ----------------------------------------------------------------- */
/*                   handle_redir                                    */
/* ----------------------------------------------------------------- */
void handle_redir(int count, char *argv[])
{
    int in_redir_idx = 0;   //index position for < input redirection
    int out_redir_idx = 0;  //index position for > output redirection
    
    //counting redirection signs
    for (int i=0; i<count; i++) {
        if ( strcmp(argv[i], "<") == 0) { //finding input redirection
            if (in_redir_idx != 0) {
                fprintf(stderr, "trying to open more than one file per redirect \n");
                _exit(-1);
            }
            if (i == 0) {
                fprintf(stderr, "no command for redirection \n");
                _exit(-1);
            }
            in_redir_idx = i; //setting up the index position
        }
        if ( strcmp(argv[i], ">") == 0) { //finding output redirection
            if (out_redir_idx != 0) {
                fprintf(stderr, "trying to open more than one file per redirect \n");
                _exit(-1);
            }
            if (i == 0) {
                fprintf(stderr, "no command for redirection \n");
                _exit(-1);
            }
            out_redir_idx = i; //setting up the index position
        }
    }
    //input redirection
    if (in_redir_idx != 0) {
        int fd0; //file descriptor for input redirection
        if ((fd0 = open(argv[in_redir_idx+1], O_RDONLY)) < 0)
            fprintf(stderr, "error opening the file %s \n", argv[in_redir_idx+1]);
        dup2(fd0, 0); // 0 = stdin
        close(fd0);
        argv[in_redir_idx] = NULL;
    }
    //output redirection
    if (out_redir_idx != 0) {
        int fd1; //file descriptor for output redirection
        if ((fd1 = open(argv[out_redir_idx+1], O_RDWR | O_CREAT | O_TRUNC,
                                                S_IRUSR | S_IWUSR)) < 0)
            fprintf(stderr, "error opening the file %s \n", argv[out_redir_idx+1]);
        dup2(fd1, 1); // 1 = stdout
        close(fd1);
        argv[out_redir_idx] = NULL;
    }
}
/* ----------------------------------------------------------------- */
