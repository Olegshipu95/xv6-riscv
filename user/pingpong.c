//
// Created by oleg on 14.09.23.
//
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
    const char* PING  = "ping";
    const char* PONG  = "pong";
    int ping_fd[2];
    int pong_fd[2];
    int ping_size = sizeof(PING);
    int pong_size = sizeof(PONG);
    if (pipe(ping_fd) == -1) {
        fprintf(1, "error with pipe", 15);
        exit(1);
    }
    if (pipe(pong_fd) == -1) {
        fprintf(1, "error with pipe", 15);
        exit(1);
    }
    if (fork() == 0) {
        char readBuffer[ping_size];
        int pid = getpid();
        close(ping_fd[1]);
        close(pong_fd[0]);

        if (read(ping_fd[0], readBuffer, ping_size) != ping_size){
            fprintf(1, "error with read ping");
            exit(1);
        }
        fprintf(0, "pid %d: got %s \n", pid, readBuffer);
        close(ping_fd[0]);

        write(pong_fd[1], PONG, pong_size);
        close(pong_fd[1]);
    } else {
        char readBuffer[pong_size];
        int pid = getpid();
        close(ping_fd[0]);
        close(pong_fd[1]);

        write(ping_fd[1], PING, ping_size);
        close(ping_fd[1]);

        if(read(pong_fd[0], readBuffer, pong_size)!=pong_size){
            fprintf(1, "error with read pong");
            exit(1);
        }
        close(pong_fd[0]);
        fprintf(0, "pid %d: got %s\n", pid, readBuffer);
    }
    return 0;
}