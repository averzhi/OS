#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// struct func_args
// {
//     int arg1;
//     int arg2;
// } *args;

// void* pop(void* arguments)
// {
//     int n = args->arg1;
//     int f = args->arg2;
//     int n2;
//     n2 = n/2;
//     printf("Hello t1! and n/2 = %d %d \n",n2,f);
//     return 0;    
// }

// int main() 
// {
//   pthread_t t1;

//    // int a[8] = {3,4,5,6,7,3,5,9}; 

//     args->arg1 = 8;
//     args->arg2 = 3;

//     pthread_create(&t1, NULL, &pop, args);
//     pthread_join(t1, NULL);

//     return 0;


//     // Создание массива из n чисел
//     int n = fgets; 
//     int a[n] = {3,4,5,6,7,3,5,9}; 

//     // Вывод элементов массива до сортировки
//     for (int i = 0; i<8; i++)
//        printf("%d ", a[i]);
//     printf("\n");

//   int a1[]

//     pthread_create(&t1, NULL, &merge, a1);
//     pthread_create(&t2, NULL, &merge, a2);
//     pthread_join(t1, NULL);
//     pthread_join(t2, NULL);
    

//     //merge(a); // вызов функции сортировки

//     // Вывод элементов массива после сортировки
//     for (int i = 0; i<8; i++)
//         printf("%d ", a[i]);

//     printf("\n");
//     // getchar();
//     return 0;

//         // Заполнение массива с клавиатуры
//     // for (int i = 0; i<8; i++)
//     // {
//     //     scanf("%d",&a[i]);
//     // }

// }

  // int mid = n / 2; // Находим середину сортируемой последовательности
  // if (n % 2 == 1)
  //   mid++; 

  // // Создаем два массива из одного - правый и левый
  //   int a_right[mid+1];
  //   int i = 0;                   
  //   while(i <= mid)
  //   {
  //     a_right[i] = a[i];
  //   }

  //   int a_left[sizeof a];
  //   int j = 0;
  //   while(j <= mid)
  //   {
  //     a_left[j] = a[j];
  //   }
