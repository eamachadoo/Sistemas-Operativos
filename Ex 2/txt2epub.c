#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/wait.h>

void converter(char *fname)
{
    char *command = "pandoc";
    char *setting = "-o";
    char *setting2 = "--quiet";
    char *arg1 = fname;
    char *arg2 = strdup(fname);
    int len = strlen(arg1);
    arg2[len - 4] = '\0';
    strcat(arg2, ".epub");
    execlp(command, command, fname, setting, arg2, setting2, (char *)0);
}

void createConverterChild(char *fname)
{
    int pid;

    /*
     *  Get a child process
     */
    if ((pid = fork()) < 0)
    {
        printf("[%d] converting %s \n", pid, fname);
        perror("fork: ");
        exit(EXIT_FAILURE);
    }

    /*
     *  The child executes the program
     */
    if (pid == 0)
    {
        converter(fname);
        perror("execlp: ");
        exit(EXIT_FAILURE);
    }

    /*
     *  The parent process just waits
     */
    if (pid >= 1)
    {
        printf("[%d] converting %s \n", pid, fname);
    }
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        createConverterChild(argv[i]);
    }
    for (int i = 1; i < argc; i++)
    {
        int status = 0;
        wait(&status);
    }
    system("zip ebooks *.epub");
    return (EXIT_SUCCESS);
}