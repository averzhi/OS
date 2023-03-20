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
