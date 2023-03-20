/*Программа состоит из двух функций: Square и Sort. Функция Square просто умножает два числа и возвращает результат. Функция Sort сортирует массив целых
чисел по возрастанию методом пузырьковой сортировки. Это значит, что она проходит по всем элементам массива несколько раз и меняет местами соседние элементы,
если они не упорядочены. Этот алгоритм имеет сложность O(n^2), где n - размер массива.*/

extern "C" float Square(float A, float B);         
extern "C" int * Sort(int * array);       

float Square(float A, float B)
{
    return A*B;
}

int* Sort(int* array)
{
    for (int i = 1; i < array[0] + 1; ++i)
    {
        for (int j = 1; j < array[0]; ++j)
        {
            if (array[j] > array[j + 1])
            {
                int a = array[j];
                array[j] = array[j + 1];
                array[j + 1] = a;
            }
        }
    }
    return array;
}
