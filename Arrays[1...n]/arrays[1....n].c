#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

int main(){
srand(time(NULL));
int i,sum,n=5,a[5];
int N=0;
double average;

for(int i=0;i<n;i++){
a[i]=rand()%10-4;
sum +=a[i];
average=sum/5.00;

printf("%d ",a[i]);
}
for(int i=0;i<n;i++){
   if(a[i]>average){
        N++;
}
}
int sum1= 0;
int foundNegative = 0; // Флаг, що показує, чи було знайдено від'ємне число

    // Проходимо по масиву та рахуємо суму модулей
    for (int i = 0; i < n; i++) {
        if (foundNegative) {
            sum1 += abs(a[i]); // abs() - функція для обчислення модуля числа
        } else if (a[i] < 0) {
            foundNegative = 1; // Знайдено перше від'ємне число
        }
    }
printf("\n");
printf("Sum: %d\n",sum);
printf("Average: %.2f\n",average);
printf("Count elements: %d\n ",N);
printf("Sum mod: %d\n",sum1);

    return 0;
}