/*Эта программа является решением задачи RE1 с сайта SPOJ1. Она использует библиотеку регулярных выражений C++2 для поиска и замены подстрок в тексте.
Программа считывает из стандартного ввода строку-шаблон, которая содержит два регулярных выражения и строку-замену, разделенные символом ‘/’. 
Затем программа считывает текст до конца ввода и применяет к нему шаблон: все подстроки, соответствующие первому регулярному выражению, заменяются на строку-замену
с учетом второго регулярного выражения. Результат выводится на стандартный вывод.
Например, если шаблон имеет вид /a(b*)c/$1/, то это означает, что нужно найти все подстроки, начинающиеся с ‘a’, заканчивающиеся на ‘c’ и содержащие любое
количество ‘b’ между ними (например, “abc”, “abbc”, “ac”), и заменить их на то же количество ‘b’, что было между ‘a’ и ‘c’ (например, “b”, “bb”, “”). 
Если текст имеет вид abc abbc ac, то результат будет b bb .*/

// Подключение заголовочного файла regex, который содержит классы и функции для работы с регулярными выражениями
#include <regex>

// Подключение заголовочного файла iostream, который содержит классы и функции для ввода-вывода данных
#include <iostream>

// Объявление пространства имен std для удобства использования стандартных классов и функций без указания префикса std::
using namespace std;

// Объявление главной функции программы
int main() {
    // Объявление переменной s типа string для хранения строки-шаблона
    string s;

    // Считывание строки-шаблона из стандартного ввода (клавиатуры) и сохранение ее в переменную s
    cin >> s;

    // Объявление переменной pos типа size_t для хранения позиции символа '/' в строке-шаблоне
    size_t pos = 0;

    // Вызов метода find у объекта s с аргументом '/', который возвращает позицию первого вхождения символа '/' в строке s или специальное значение npos, если такого символа нет
    pos = s.find('/');

    // Объявление переменной re1 типа regex для хранения первого регулярного выражения из строки-шаблона
    regex re1;

    // Вызов конструктора класса regex с аргументом s.substr(0, pos), который создает объект re1 на основе подстроки s от начала до позиции pos (не включая ее)
    re1 = regex(s.substr(0, pos));

    // Уменьшение значения переменной pos на 1 для перехода к следующему символу после '/'
    pos--;

    // Вызов метода find у объекта s с аргументами '/', pos + 2 и npos, который возвращает позицию первого вхождения символа '/' в строке s после позиции pos + 2 или специальное значение npos, если такого символа нет 
    pos = s.find('/', pos + 2);

    // Объявление переменной re2 типа regex для хранения второго регулярного выражения из строки-шаблона 
    regex re2;

     // Вызов конструктора класса regex с аргументом s.substr(pos - 1), который создает объект re2 на основе подстроки s от позиции pos - 1 до конца строки 
     re2 = regex(s.substr(pos - 1));

     // Объявление переменной format типа string для хранения строки-замены из строки-шаблона 
     string format;

     // Присваивание значения подстроки s от позиции pos + 1 до конца строки переменной format 
     format = s.substr(pos + 1);

     // Объявление переменной line типа string для хранения очередной строки текста 
     string line;

     // Цикл по всем строкам текста до конца стандартного ввода 
     while (getline(cin, line)) {
         // Вывод на стандартный вывод (экран) результата применения функции regex_replace к строке line с аргументами re1, format и re2,
         // которая заменяет все подстроки line, соответствующие регулярному выражению re1,
         // на строку format с учетом регулярного выражения re2 
         cout << regex_replace(line, re1, format) << endl;
     }

     return 0; // Завершение программы успешно 
}
