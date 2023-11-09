#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int status = 0;

void *print_child(void *arg){ 
int i=0;

for(i=0;i<11;i++){ 
sleep(2);
 printf("Child Thread. Iterations %d \n ",i);
}
return NULL;
}

int main()
{   int i;
    pthread_t child;
    if(pthread_create(&child, NULL, &print_child, NULL)!= 0){
        perror("Не вдалося створити потік");
        return EXIT_FAILURE;
    }

   
    for(i=0;i<11;i++){
    sleep(2);
    printf("Main thread. Iterations %d \n",i);
   
    }
    if (pthread_join(child, NULL)!= 0)
    {
        printf("ERROR");
        return EXIT_FAILURE;
    }
    return 0;
}