#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<sys/utsname.h>

void checkHostName(int hostname){
    if (hostname == -1)
    {
        perror("gethostname");
        exit(1);
    }
}

int main(){
int hostname;
char hostbuffer[256];
struct utsname uts;
 hostname = gethostname(hostbuffer, sizeof(hostbuffer));
 checkHostName(hostname);
 printf("Hostname: %s\n",hostbuffer);

  if (uname(&uts) < 0)
    perror("uname() error");
  else {
    printf("Sysname:  %s\n", uts.sysname);
    printf("Nodename: %s\n", uts.nodename);
    printf("Release:  %s\n", uts.release);
    printf("Version:  %s\n", uts.version);
    printf("Machine:  %s\n", uts.machine);
  }



    return 0;
}