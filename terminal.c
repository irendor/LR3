#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void onCtrlC() {
    printf("Остановка программы...\n");
    system("ps -e");
    printf("Введите идентификатор процесса, который нужно остановить: ");
    pid_t pid;
    scanf("%d", &pid);
    kill(pid, SIGTERM);
    exit(0);
}

int main() {
    char command[256];
    char *args[3];
    signal(SIGINT, onCtrlC);
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
            execvp(args[0], args);
            printf("Ошибка при запуске процесса\n");
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            printf("Ошибка при создании процесса\n");
            exit(EXIT_FAILURE);
        } else {
            wait(NULL);
            printf("\n");
        }
    }

    return 0;
}