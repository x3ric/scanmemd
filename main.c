#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_CMD_SIZE 512
#define MAX_PARAM_SIZE 64
#define MAX_PATH_SIZE 256
#define DELAY_SECONDS 1
void systemprint(const char *cmd) {
    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        perror("Error executing command");
        return;
    }
    char output[MAX_PARAM_SIZE];
    while (fgets(output, sizeof(output), fp) != NULL) {
        printf("%s", output);
    }
    pclose(fp);
}
int main(int argc, char *argv[]) {
    char *home = argv[1];
    char filePath[MAX_PATH_SIZE];
    snprintf(filePath, sizeof(filePath), "%s/.cache/scanmem", home);
    printf("Input file path: %s\n", filePath);
    char pid[MAX_PARAM_SIZE];
    char cmd[MAX_PARAM_SIZE];
    char buffer[MAX_CMD_SIZE];
    FILE *file;
    while (1) {
        file = fopen(filePath, "r");
        if (!file) {
            perror("Error opening file");
            sleep(DELAY_SECONDS);
            continue;
        }
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        if (fileSize == 0) {
            printf("Input file is empty. Waiting for data...\n");
            fclose(file);
            sleep(DELAY_SECONDS);
            continue;
        }
        rewind(file);
        if (fscanf(file, "%s %s", pid, cmd) == 2) {
            int cmd_length = snprintf(NULL, 0, "sudo scanmem -p %s -c \"%s; exit\"", pid, cmd);
            if (cmd_length >= MAX_CMD_SIZE) {
                fprintf(stderr, "Command too long, skipping execution.\n");
            } else {
                snprintf(buffer, sizeof(buffer), "sudo scanmem -p %s -c \"%s; exit\"", pid, cmd);
                printf("Executing command: %s\n", buffer);
                systemprint(buffer);
                if (freopen(filePath, "w", file) == NULL) {
                    perror("Error clearing file");
                } else {
                    printf("Input file cleared.\n");
                }
            }
        } else {
            fprintf(stderr, "File format error. Ensure the file contains PID and command.\n");
        }
        fclose(file);
        sleep(DELAY_SECONDS);
    }
    return 0;
}
