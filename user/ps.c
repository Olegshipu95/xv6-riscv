#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/ps.h"

int
main(int argc, char *argv[]) {
    int return_status;
    char element;

    if (argc == 1) {
        return_status = procinfo(argc, stub);
    }
    else if (argv[1][0] == 'x') {
        return_status = procinfo(argc, x);
    } else if (argv[1][0] == 'a') {
        return_status = procinfo(argc, a);
    } else if (argv[1][0] == 'h') {
        fprintf(0, "You can write flags :\n x - for all procs\n a - for all procs that bind with your terminal\n");
    } else return_status = procinfo(argc, unknown);

    if (return_status == 1) {
        fprintf(1, "not correct args, you should write ps h\n");
    } else if (return_status == 2) {
        fprintf(1, "args more than 2\n");
    } else if (return_status != 0) {
        fprintf(1, "unknown error\n");
    }
    exit(0);
}
