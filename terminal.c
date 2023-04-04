#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    // char stroke[256];
    // scanf("%s", stroke);
    // if (strstr(stroke, "ls") != NULL) {
    //     if (fork() == 0)
    //         wait(0);
    //     else
    //         execlp("/bin/ls", "ls", (char *)NULL);
    // }
    // if (strstr(stroke, "cat") != NULL) {
    //     char *filename = strstr(stroke, "cat") + 4;
    //     if (fork() == 0)
    //         wait(0);
    //     else
    //         execlp("/bin/cat", "cat", *filename, (char *)NULL);
    // }

    char command[256];
    char *args[3];

    while (1) {
        printf("Введите команду: ");
        fgets(command, 256, stdin);

        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "ls") == 0) {
            args[0] = "ls";
            args[1] = (char *)NULL;
        } else if (strncmp(command, "cat", 3) == 0) {
            args[0] = "cat";
            args[1] = command + 4;
            args[2] = (char *)NULL;
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("Неверная команда\n");
            continue;
        }

        pid_t pid = fork();
        if (pid == 0) {
            // Дочерний процесс
            execvp(args[0], args);
            printf("Ошибка при запуске процесса\n");
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            // Ошибка при создании процесса
            printf("Ошибка при создании процесса\n");
            exit(EXIT_FAILURE);
        } else {
            // Родительский процесс
            wait(NULL);
            printf("\n");
        }
    }

    return 0;
}