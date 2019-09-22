#include <stdio.h>
#include <signal.h>
#include <string.h>

#define QUESTION ("Interrupted! OK to quit")

void f(int);
static int cnt = 0;
static int signums;

int main(int argc, char *argv[])
{
        int i;
        if (argc != 2) {
                fprintf(stderr, "usage: %s <signum>\n", argv[0]);
                exit(1);
        }
        signums = atoi(argv[1]);
        signal(SIGINT, f);
        for (i = 0; i < 100; i++) {
                printf("hello\n");
                sleep(1);
        }
        return 0;
}

void f(int signum)
{
        int c, i;
        int yes_no_flag;
        printf("%s (y/n)", QUESTION);
        while (1) {
            yes_no_flag = 1;
            switch(c = getchar()) {
                    case 'y':
                    case 'Y':
                            if (cnt == signums) {
                                    exit(0);
                            }
                            cnt++;
                            printf("OUCH");
                            for (i = 0; i < cnt; i++) {
                                    printf("!");
                            }
                            printf("\n");
                            break;
                    case 'n':
                    case 'N':
                            break;
                    default:
                            yes_no_flag = 0;
                            break;
            }
            if (yes_no_flag == 1)
                    break;
        }
}
