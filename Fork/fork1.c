#include <stdio.h>
#include <unistd.h>

int main()
{
        int n;

        for (n = 0; n < 10; n++) {
                printf("my pid = %d, n = %d\n", getpid(), n);
                sleep(1);
        //        if (fork() != 0) {
          //              exit(0);
            //    }
        }
        
        return 0;
}
