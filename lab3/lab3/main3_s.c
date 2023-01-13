#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Функция сортировки двухпутевым слиянием
void* merge(int *a)
{
  int n;
  printf("\nPrint n again:\n");
  scanf("%d", &n); 
  printf("\n");

  int mid = n / 2; // находим середину сортируемой последовательности
  if (n % 2 == 1)
    mid++;         //то есть, если в массиве нечетное количество элементов, то 1я половина возьмет в себя на 1 элемент больше: чем правая

  int h = 1; // шаг
  // выделяем память под формируемую последовательность
  int *c = (int*)malloc(n * sizeof(int));
  int step;
  
  while (h < n) 
  {
    step = h;
    int i = 0;   // индекс первого пути
    int j = mid; // индекс второго пути
    int k = 0;   // индекс элемента в результирующей последовательности
    while (step <= mid) 
    {
      while ((i < step) && (j < n) && (j < (mid + step))) 
      { // пока не дошли до конца пути
        // заполняем следующий элемент формируемой последовательности
        // меньшим из двух просматриваемых
        if (a[i] < a[j])  
        {
          c[k] = a[i];
          i++; k++;
        }
        else {
          c[k] = a[j];
          j++; k++;
        }
      }
      while (i < step) 
      { // переписываем оставшиеся элементы первого пути (если второй кончился раньше)
        c[k] = a[i];
        i++; k++;
      }
      while ((j < (mid + step)) && (j<n)) 
      {  // переписываем оставшиеся элементы второго пути (если первый кончился раньше)
        c[k] = a[j];
        j++; k++;
      }
      step = step + h; // переходим к следующему этапу
    }
    h = h * 2;
    // Переносим упорядоченную последовательность (промежуточный вариант) в исходный массив
    for (i = 0; i<n; i++)
      a[i] = c[i];
  }
}

int main() 
{
  pthread_t t1;

    // Создание массива из n чисел
    int n;
    printf("Print n:\n");
    scanf("%d", &n); 
    printf("\n");

    // Заполнение массива с клавиатуры 
     printf("Print numbers:\n");
    int a[n];  // = {3,4,5,6,7,3,5,9}; 

      for (int i = 0; i<n; i++)
    {
        scanf("%d",&a[i]);
    }

    // Вывод элементов массива до сортировки
    printf("Array BEFORE:\n");
    for (int i = 0; i<n; i++)
       printf("%d ", a[i]);
    printf("\n");

    // Потоки
    pthread_create(&t1, NULL, &merge, a);
    pthread_join(t1, NULL);

    //merge(a); // вызов функции сортировки

    printf("Array AFTER:\n");
    // Вывод элементов массива после сортировки
    for (int i = 0; i<n; i++)
        printf("%d ", a[i]);

    printf("\n");
    
    return 0;
}