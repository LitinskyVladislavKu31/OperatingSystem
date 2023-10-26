#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
char command [64];
char command1 [64];
char *token;
int exitCode;
int ch;
while(1){
printf("1 Виконати команду(з параметрами)\n2.Виконати кілька команд: \n3.Вихід\n");
scanf("%d",&ch);
getchar();

switch(ch){
case 1:
printf("Enter command: ");
fgets(command, sizeof(command1), stdin); 
strcpy(command1,command);
printf("%c",system(command1));
break;

case 2:
printf("Введіть декілька команд: \n");
 fgets(command, sizeof(command), stdin);

    // Видалення символу нового рядка з введеного рядка
    command[strcspn(command, "\n")] = 0;
    token = strtok(command, ";");

    // Отримання першого елемента

    // Перебір усіх елементів
    while (token != NULL) {
        printf("Виконання команди: %s\n", token);
        exitCode = system(token);
        sleep(10);
        printf("Код завершення: %d\n", exitCode);
        token = strtok(NULL, ";");  // Отримання наступного елемента
    }

break;

case 3:
printf("До зустрічі!");
exit(0);

default:
printf("Error");
break;
}


}
return 0;

}


   