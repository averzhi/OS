/*Данная программа демонстрирует работу с динамическими библиотеками в Linux. Программа загружает две библиотеки libd1.so и libd2.so с помощью функции dlopen1 и получает указатели на функции Square и Sort из этих библиотек с помощью функции dlsym1. Затем программа запрашивает у пользователя команду и выполняет соответствующую функцию из одной из библиотек. После выполнения команды программа закрывает библиотеку с помощью функции dlclose1 и завершается.*/

// Подключение заголовочных файлов для работы с вводом-выводом и динамическими библиотеками
#include <iostream>
#include <dlfcn.h>

// Объявление типов функций Square и Sort
typedef int (*SquareFunc)(int);
typedef void (*SortFunc)(int*, int);

// Определение константы для имени библиотеки libd1.so
#define LIBD1 "libd1.so"

// Определение константы для имени библиотеки libd2.so
#define LIBD2 "libd2.so"

// Определение константы для размера массива
#define SIZE 10

using namespace std;

int main()
{
    // Объявление переменных для хранения указателей на библиотеки и функции
    void *lib;
    SquareFunc square;
    SortFunc sort;

    // Объявление переменной для хранения команды пользователя
    char command;

    // Вывод сообщения о доступных командах на экран
    cout << "Enter command: s - square, t - sort" << endl;

    // Считывание команды пользователя с клавиатуры
    cin >> command;

    // Выбор действия в зависимости от команды пользователя
    switch (command)
    {
        // Если пользователь ввел 's', то выполнить следующие действия:
        case 's':
            // Загрузить библиотеку libd1.so с помощью функции dlopen и сохранить указатель на нее в переменной lib
            lib = dlopen(LIBD1, RTLD_LAZY);
            // Если загрузка не удалась, то вывести сообщение об ошибке и завершить программу с кодом 1
            if (!lib) {
                cerr << "Cannot load library: " << dlerror() << endl;
                return 1;
            }

            // Получить указатель на функцию Square из библиотеки libd1.so с помощью функции dlsym и сохранить его в переменной square
            square = (SquareFunc) dlsym(lib, "Square");
            // Если получение не удалось, то вывести сообщение об ошибке и завершить программу с кодом 2
            if (!square) {
                cerr << "Cannot load symbol: " << dlerror() << endl;
                return 2;
            }

            // Объявление переменной для хранения числа пользователя
            int num;

            // Вывод сообщения о вводе числа на экран
            cout << "Enter a number: ";

            // Считывание числа пользователя с клавиатуры и сохранение его в переменной num
            cin >> num;

            // Вызов функции square с аргументом num и вывод результата на экран 
            cout << "The square of " << num << " is " << square(num) << endl;

            break; // Прервать выполнение оператора switch

        // Если пользователь ввел 't', то выполнить следующие действия:
        case 't':
             // Загрузить библиотеку libd2.so с помощью функции dlopen и сохранить указатель на нее в переменной lib 
             lib = dlopen(LIBD2, RTLD_LAZY);
             // Если загрузка не удалась, то вывести сообщение об ошибке и завершить программу с кодом 3 
             if (!lib) {
                 cerr << "Cannot load library: " << dlerror() << endl;
                 return 3;
             }

             // Получить указатель на функцию Sort из библиотеки libd2.so с помощью функции dlsym и сохранить его в переменной sort 
             sort = (SortFunc) dlsym(lib, "Sort");
        
             // Если получение не удалось, то вывести сообщение об ошибке и завершить программу с кодом 4
             if (!sort) {
                 cerr << "Cannot load symbol: " << dlerror() << endl;
                 return 4;
             }

             // Объявление массива из SIZE элементов для хранения чисел пользователя
             int arr[SIZE];

             // Вывод сообщения о вводе чисел на экран
             cout << "Enter " << SIZE << " numbers: ";

             // Цикл по всем элементам массива
             for (int i = 0; i < SIZE; i++) {
                 // Считывание очередного числа пользователя с клавиатуры и сохранение его в i-м элементе массива arr
                 cin >> arr[i];
             }

             // Вызов функции sort с аргументами arr и SIZE для сортировки массива по возрастанию 
             sort(arr, SIZE);

             // Вывод сообщения о выводе отсортированного массива на экран 
             cout << "The sorted array is: ";

             // Цикл по всем элементам массива 
             for (int i = 0; i < SIZE; i++) {
                 // Вывод очередного элемента массива на экран с пробелом после него 
                 cout << arr[i] << " ";
             }

             // Перевод курсора на новую строку 
             cout << endl;

            break; // Прервать выполнение оператора switch

        // Если пользователь ввел любую другую команду, то выполнить следующие действия:
        default:
            // Вывод сообщения об ошибке на экран и завершение программы с кодом 5
            cerr << "Invalid command" << endl;
            return 5;
    }

    // Закрытие библиотеки с помощью функции dlclose и проверка результата 
    if (dlclose(lib)) {
        // Если закрытие не удалось, то вывести сообщение об ошибке на экран и завершить программу с кодом 6
        cerr << "Cannot close library: " << dlerror() << endl;
        return 6;
    }

    return 0; // Завершить программу успешно
}
