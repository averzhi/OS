
#include "functions.h" // Подключение заголовочного файла functions.h
#include <iostream> // Подключение библиотеки iostream
#include <fcntl.h> // Подключение библиотеки fcntl.h
#include <thread> // Подключение библиотеки thread

inline void intro() { // Определение функции intro
    std::cout << "Hello! Welcome to the game \"Bulls and cows\"." << std::endl; // Вывод на экран приветствия
    std::cout << "Have you already account in this game?\n Answer: \"yes\" or \"no\"" << std::endl; // Вывод на экран вопроса
    std::cout << "> "; // Вывод на экран приглашения ввода
    std::cout.flush(); // Очистка буфера вывода
}

void func(int fd,const std::string& login){ // Определение функции func
    while (true){ // Бесконечный цикл
        std::string respond = receive(fd); // Получение ответа от сервера
        std::cout << "\n" << respond << std::endl; // Вывод на экран ответа сервера
        if (respond == "SERVER CLOSED"){ // Если ответ сервера "SERVER CLOSED"
            exit(EXIT_SUCCESS); // Выход из программы
        }
        std::cout << login << ">"; // Вывод на экран логина пользователя
        std::cout.flush(); // Очистка буфера вывода
    }
}

std::pair<std::string, std::string> login() { // Определение функции login
    std::string login, password; // Объявление переменных login и password
    std::cout << "Please enter your login:\n> "; // Вывод на экран приглашения ввода логина
    std::cout.flush(); // Очистка буфера вывода
    std::cin >> login; // Ввод логина
    std::cout << "Please enter your password:\n> "; // Вывод на экран приглашения ввода пароля
    std::cout.flush(); // Очистка буфера вывода
    std::cin >> password; // Ввод пароля
    return std::make_pair(login, SECRET_KEY + password); // Возврат пары значений
}


int connect_to_server() { // Определение функции connect_to_server
    int fd = open(SERVER_INPUT_FILE_NAME, O_RDWR); // Открытие файла SERVER_INPUT_FILE_NAME на чтение и запись
    if (fd == -1) { // Если файл не открыт
        std::cout << "Server doesn't exists" << std::endl; // Вывод на экран сообщения об ошибке
        exit(EXIT_FAILURE); // Выход из программы
    }
    return fd; // Возврат значения
}

void menu() { // Определение функции menu
    std::cout << "\t\t Main menu" << std::endl; // Вывод на экран заголовка
    std::cout << "\t List of commands" << std::endl; // Вывод на экран заголовка
    std::cout << "1) rules" << std::endl; // Вывод на экран команды
    std::cout << "2) create $table_name $game_word" << std::endl; // Вывод на экран команды
    std::cout << "3) connect $table_name" << std::endl; // Вывод на экран команды
    std::cout << "4) quit" << std::endl; // Вывод на экран команды
}


void loading() { // Определение функции loading
    std::cout << "\t\tLoading" << std::endl; // Вывод на экран заголовка
    int width = 50; // Объявление переменной width
    int progress = 0; // Объявление переменной progress
    while (progress <= 100) { // Цикл while
        int now = progress / 2; // Объявление переменной now
        std::cout << "["; // Вывод на экран символа "["
        for (int i = 0; i < width; ++i) { // Цикл for
            if (i < now) { std::cout << "="; } // Если i меньше now, то выводится "="
            else if (i == now) { std::cout << ">"; } // Если i равно now, то выводится ">"
            else { std::cout << " "; } // Иначе выводится пробел
        }
        std::cout << "] " << progress << "%" << std::endl; // Вывод на экран процента загрузки
        progress += 4; // Увеличение значения переменной progress на 4
        usleep(50000); // Приостановка выполнения программы на 50000 микросекунд
    }
}

void rules() { // Определение функции rules
    std::cout << "\t\tRules" << std::endl; // Вывод на экран заголовка
    std::cout << "1) One word is made up" << std::endl; // Вывод на экран правила
    std::cout << "2) Players try to guess the word" << std::endl; // Вывод на экран правила
    std::cout << "3) The server gives response like \"N bulls, M cows\"." << std::endl; // Вывод на экран правила
    std::cout << "4) Server's response means N chars are in the answer and are in their place" << std::endl; // Вывод на экран правила
    std::cout << "5) M chars are in the answer, but aren't in their place" << std::endl; // Вывод на экран правила
}

int main() { // Объявление функции main
    int client_out_fd = connect_to_server(); // Вызов функции connect_to_server и присваивание переменной client_out_fd возвращаемого значения
    intro(); // Вызов функции intro
    std::string answer; // Объявление переменной answer
    std::cin >> answer; // Ввод значения переменной answer
    bool ok = (answer == "yes"); // Присваивание переменной ok значения true, если answer равно "yes", иначе false
    auto pair = login(); // Присваивание переменной pair возвращаемого значения функции login
    std::string password = std::to_string(transform(pair).second); // Присваивание переменной password значения, полученного из функции transform
    std::string login = pair.first; // Присваивание переменной login значения pair.first
    pair.second = ""; // Присваивание pair.second пустого значения
    std::string cmd; // Объявление переменной cmd
    ok ? cmd = "log" : cmd = "reg"; // Присваивание переменной cmd значения "log", если ok равно true, иначе "reg"
    send_to_server(client_out_fd, login, cmd, password); // Вызов функции send_to_server
    std::cout << "Connecting to server" << std::endl; // Вывод на экран сообщения
    loading(); // Вызов функции loading
    int fd = open(pair.first.c_str(), O_RDWR); // Открытие файла с именем pair.first на чтение и запись
    if (fd == -1) { // Если файл не открыт
        perror("Open file"); // Вывод на экран сообщения об ошибке
        exit(EXIT_FAILURE); // Выход из программы с кодом ошибки
    }
    menu(); // Вызов функции menu
    std::string command, data, game, game_word; // Объявление переменных
    int game_fd; // Объявление переменной game_fd
    std::thread thread(func, fd, login); // Создание потока
    while (true) { // Цикл while
        std::cout << "> "; // Вывод на экран символа ">"
        std::cout.flush(); // Очистка буфера
        std::cin >> command; // Ввод значения переменной command
    if (command == "rules") { // Если command равно "rules"
        rules(); // Вызов функции rules
    } else if (command == "create") { // Если command равно "create"
        std::cin >> game >> game_word; // Ввод значений переменных game и game_word
        data = game + "%" + game_word; // Присваивание переменной data значения game + "%" + game_word
        send_to_server(client_out_fd, login, command, data); // Вызов функции send_to_server
    } else if (command == "connect") { // Если command равно "connect"
        std::cin >> game; // Ввод значения переменной game
        data = game; // Присваивание переменной data значения game
        loading(); // Вызов функции loading
        game_fd = open(("game_" + game).c_str(), O_RDWR); // Открытие файла с именем "game_" + game на чтение и запись
        if (game_fd == -1) { // Если файл не открыт
            perror("Open file"); // Вывод на экран сообщения об ошибке
            exit(EXIT_FAILURE); // Выход из программы с кодом ошибки
        }
        send_to_server(game_fd, login, command, data); // Вызов функции send_to_server
        while (true) { // Цикл while
            std::cin >> command; // Ввод значения переменной command
            if (command == "maybe"){ // Если command равно "maybe"
                std::cin >> data; // Ввод значения переменной data
                send_to_server(game_fd, login, command, data); // Вызов функции send_to_server
            } else if (command == "leave"){ // Если command равно "leave"
                send_to_server(game_fd, login, command, data); // Вызов функции send_to_server
                break; // Выход из цикла
            }
            std::cout << "> "; // Вывод на экран символа ">"
            std::cout.flush(); // Очистка буфера
        }
        menu(); // Вызов функции menu
    } else if (command == "quit") { // Если command равно "quit"
        data = ""; // Присваивание переменной data пустого значения
        send_to_server(client_out_fd, login, command, data); // Вызов функции send_to_server
        thread.detach(); // Отсоединение потока
        std::cout << "Thank you for game. Come to us later" << std::endl; // Вывод на экран сообщения
        exit(EXIT_SUCCESS); // Выход из программы с кодом успешного завершения
    } else if (command == "shut_down" and login == ADMIN_NAME){ // Если command равно "shut_down" и login равно ADMIN_NAME
        data = ""; // Присваивание переменной data пустого значения
        send_to_server(client_out_fd, login, command, data); // Вызов функции send_to_server
        thread.detach(); // Отсоединение потока
        std::cout << "Server will be turned off" << std::endl; // Вывод на экран сообщения
        exit(EXIT_SUCCESS); // Выход из программы с кодом успешного завершения
    }
}
