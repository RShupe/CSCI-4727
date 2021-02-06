#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct {
    int number;
    char payload[sizeof(char) * 21];
} Message;

int main(int argc, char **argv) {
    Message msg;
    int file_desc[2], status;
    pid_t pid;

    // super-lazy check of argument count--program will not continue if no arguments given...
    assert(argc >= 1);

    if (pipe(file_desc) == -1) {
        perror("pipe() failed. Exiting...");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork() failed. Exiting...");
        exit(EXIT_FAILURE);
    }

    // child code
    if (pid == 0) {
        close(file_desc[1]);    // close unused write end

        while (read(file_desc[0], (char*)&msg, sizeof(Message)) > 0)
            printf("Argument #%d: %s\n", msg.number, msg.payload);

        close(file_desc[0]);    // close read end
        _exit(EXIT_SUCCESS);    // exit IMMEDIATELY
    }
        // parent code
    else {
        close(file_desc[0]);    // close unused read end

        // write all messages
        for (int i = 1; i < argc; ++i) {
            msg.number = i;
            if (strlen(argv[i]) < sizeof(msg.payload)) {
                strncpy(msg.payload, argv[i], strlen(argv[i]));
                msg.payload[strlen(argv[i])] = '\0';
            } else {
                strcpy(msg.payload, "Argument too long!");
            }

            write(file_desc[1], (char*) &msg, sizeof(Message));
        }
        close(file_desc[1]);    // EOF to child
        wait(&status);          // wait on child to terminate
        exit(EXIT_SUCCESS);
    }
}
