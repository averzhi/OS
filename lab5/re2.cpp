extern "C" float Square(float A, float B);   
extern "C" int * Sort(int * array);         
using namespace std;

float Square(float A, float B)
{
    return (A*B)/2;
}

void _sort(int* a, int first, int last)
{
    int i = first, j = last;
    int tmp, x = a[(first + last) / 2];
    do 
    {
        while (a[i] < x)
        {
            i++;
        }
        while (a[j] > x)
        {
            j--;
        }
        if (i <= j) 
        {
            if (i < j)
            {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
            i++;
            j--;
        }
    } while (i <= j);
    if (i < last)
    {
        _sort(a, i, last);
    }
    if (first < j)
    {
        _sort(a, first, j);
    }
}

int* Sort(int* array)
{
    _sort(array, 1, array[0]);
    return array;
}