#include <stdio.h>    //g++ prog1.cpp -L. -ld1 -o main1 -Wl,-rpath -Wl,.
#include <vector>        //g++ prog1.cpp -L. -ld2 -o main2 -Wl,-rpath -Wl,.

using namespace std;

extern "C" float Square(float A, float B);
extern "C" int* Sort(int* array);

int main()
{
    int command;
    printf("1 for Square, 2 for Sort, 3 for break:\n");
    scanf("%d", &command);
    while (1)
    {
        if (command == 1)
        {
            char c1 = '1', c2 = '1';
            while (c2 != '\n')
            {
                float a, b;
                scanf("%f%c%f%c", &a, &c1, &b, &c2);
                if ((a < 1)||(b < 1))
                {
                    printf("Input error\n");
                }
                else
                {
                printf("%lf\n", Square(a, b));
                }
            }
        }
        if (command == 2)
        {
            int a;
            char c = '1';
            vector<int> v;
            while (c != '\n')
            {
                scanf("%d%c", &a, &c);
                v.push_back(a);
            }
            c = '1';
            int* arr = new int[v.size() + 1];
            arr[0] = v.size();
            for (int i = 0; i < v.size(); ++i)
            {
                arr[i + 1] = v[i];
            }
            Sort(arr);
            for (int i = 1; i < arr[0] + 1; ++i)
            {
                printf("%d ", arr[i]);
            }
            printf("\n");
            delete [] arr;
        }
        if (command == 3)
        {
            break;
        }
        scanf("%d", &command);
    }
    return 0;
}
/*
 g++ -fPIC -c re1.cpp -o d1.o
 g++ -shared d1.o -o libd1.so
 g++ -fPIC -c re2.cpp -o d2.o
 g++ -shared d2.o -o libd2.so
 g++ prog1.cpp -L. -ld1 -o main1 -Wl,-rpath -Wl,.
 g++ prog1.cpp -L. -ld2 -o main2 -Wl,-rpath -Wl,.
*/