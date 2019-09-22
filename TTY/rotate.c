#include <stdio.h>
#include <ctype.h>
#include <termios.h>
#include <signal.h>

void set_cr_noecho_mode(void);
void tty_mode(int);
void ctrl_c_handler(int);

int main()
{
        int c;
        tty_mode(0);
        set_cr_noecho_mode();
        signal(SIGINT, ctrl_c_handler);
        signal(SIGQUIT, SIG_IGN);
        while ((c = getchar()) != EOF) {
                if (c == 'Q') {
                        tty_mode(1);
                        exit(0);
                }
                if (c == 'z')
                        c = 'a';
                else if (islower(c))
                        c++;
                putchar(c);
        }
        tty_mode(1);
        return 0;
}

void set_cr_noecho_mode()
{
        struct termios ttystate;
        tcgetattr(0, &ttystate);
        ttystate.c_lflag &= ~ICANON;
        ttystate.c_lflag &= ~ECHO;
        ttystate.c_cc[VMIN] = 1;
        tcsetattr(0, TCSANOW, &ttystate);
}

void tty_mode(int how)
{
        static struct termios original_mode;
        if (how == 0)
                tcgetattr(0, &original_mode);
        else
                tcsetattr(0, TCSANOW, &original_mode);
}

void ctrl_c_handler(int signum)
{
        tty_mode(1);
        exit(1);
}
