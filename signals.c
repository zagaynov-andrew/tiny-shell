#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

void listener(int sig)
{
    // printf("listener\n");
    //очищаем буфер
    // while (getchar() != '\n');
    if (sig == SIGQUIT)
        write(2, "\b\b  \b\b", 6);
    else if (sig == SIGINT)
    {
        printf("\nnforce:/home/nforce/minishell $ ");
    }
}

int main()
{
    char* input, word, shell_prompt[100];

    signal(SIGQUIT, listener);
    signal(SIGINT, listener);
    for(;;)
    {
        // getting the current user's path
        snprintf(shell_prompt, sizeof(shell_prompt), "%s:%s $ ", getenv("USER"), getcwd(NULL, 1024));
        // inputing...
        input = readline(shell_prompt);
        // readline("> ");
        // eof
        if (!input)
            break;
        printf("\"%s\"\n", input);
        // adding the previous input into history
        if (input)
            add_history(input);

        /* do stuff */

        // Т. к. вызов readline() выделяет память, но не освобождает (а возвращает), то эту память нужно вернуть (освободить).
        free(input);
    }
}