#include "functions.h"
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <map>
#include <thread>

// Проверка наличия базы данных
void check_data_base() {
    std::ifstream file(DATA_BASE_FILE_NAME); // Открытие файла базы данных
    file.open(DATA_BASE_FILE_NAME);
    if (file.is_open()) { // Если файл открыт
        std::cout << "OK: DATA BASE" << std::endl; // Вывод сообщения об успешном открытии файла
        file.close(); // Закрытие файла
    } else { // Если файл не открыт
        std::ofstream f(DATA_BASE_FILE_NAME); // Создание файла базы данных
        std::string empty_string; // Создание пустой строки
        auto pair = std::make_pair(empty_string, SECRET_KEY + ADMIN_PASSWORD); // Создание пары значений
        std::string pass = std::to_string(transform(pair).second); // Преобразование второго значения пары в строку
        pair.first = ADMIN_NAME; // Присваивание первому значению пары имени администратора
        pair.second = pass; // Присваивание второму значению пары пароля администратора
        auto log_pas = transform(pair); // Преобразование пары значений
        f << log_pas.first << " " << log_pas.second << std::endl; // Запись пары значений в файл
        f.close(); // Закрытие файла
        std::cout << "OK: DATA BASE" << std::endl; // Вывод сообщения об успешном создании файла
    }
}

// Добавление результатов игры в файл
void add_results(const std::string &game_name, const std::string &game_word, const std::string &winner) {
    std::ifstream inp; // Открытие файла с результатами игр
    std::ofstream out; // Открытие файла для записи результатов игры
    inp.open(RESULTS_FILE_NAME); // Открытие файла с результатами игр
    if (inp.is_open()){ // Если файл открыт
        inp.close(); // Закрытие файла
        out.open(RESULTS_FILE_NAME, std::ios::app); // Открытие файла для записи результатов игры
        out << game_name << "\t\t" << game_word << "\t\t" << winner << std::endl; // Запись результатов игры в файл
        out.close(); // Закрытие файла
    } else{ // Если файл не открыт
        out.open(RESULTS_FILE_NAME); // Создание файла для записи результатов игры
        out << "Game name\t\tGame word\t\tWinner" << std::endl; // Запись заголовка таблицы в файл
        out << game_name << "\t\t" << game_word << "\t\t" << winner << std::endl; // Запись результатов игры в файл
        out.close(); // Закрытие файла
    }
    std::cout << "RESULTS UPDATED" << std::endl; // Вывод сообщения об успешном обновлении результатов игры
}

bool check_in_data_base(std::pair<std::string, std::string> &login_password) {
    std::pair<int, int> pair = transform(login_password); // Преобразование пары значений
    std::ifstream file; // Открытие файла базы данных
    file.open(DATA_BASE_FILE_NAME);
    int log, pas;
    while (file >> log >> pas) { // Чтение файла базы данных
        if (log == pair.first) { // Если имя пользователя найдено
            if (pas == pair.second) { // Если пароль пользователя найден
                file.close(); // Закрытие файла базы данных
                return true; // Возвращение значения true
            }
            file.close(); // Закрытие файла базы данных
            return false; // Возвращение значения false
        }
    }
    file.close(); // Закрытие файла базы данных
    return false; // Возвращение значения false
}

bool add_in_data_base(std::pair<std::string, std::string> &login_password) {
    std::pair<int, int> pair = transform(login_password); // Преобразование пары значений
    std::ifstream file; // Открытие файла базы данных
    file.open(DATA_BASE_FILE_NAME, std::ios::in);
    int log, pas;
    while (file >> log >> pas) { // Чтение файла базы данных
        if (log == pair.first) { // Если имя пользователя найдено
            file.close(); // Закрытие файла базы данных
            return false; // Возвращение значения false
        }
    }
    file.close(); // Закрытие файла базы данных
    std::ofstream f(DATA_BASE_FILE_NAME, std::ios::app); // Открытие файла базы данных для записи
    f << pair.first << " " << pair.second << std::endl; // Запись пары значений в файл
    f.close(); // Закрытие файла базы данных
    return true; // Возвращение значения true
}

int create_main_pipe() {
    if (mkfifo(SERVER_INPUT_FILE_NAME, ACCESS_PERMS) == -1) { // Создание канала
        perror("Mkfifo"); // Вывод сообщения об ошибке
        exit(EXIT_FAILURE); // Выход из программы
    }
    int fd = open(SERVER_INPUT_FILE_NAME, O_RDWR); // Открытие канала
    if (fd == -1) { // Если канал не открыт
        perror("Open file"); // Вывод сообщения об ошибке
        exit(EXIT_FAILURE); // Выход из программы
    }
    return fd; // Возвращение дескриптора канала
}

int create_client_pipe(std::string &login) {
    if (mkfifo(login.c_str(), ACCESS_PERMS) == -1) { // Создание канала
        perror("Mkfifo"); // Вывод сообщения об ошибке
        exit(EXIT_FAILURE); // Выход из программы
    }
    int fd = open(login.c_str(), O_RDWR); // Открытие канала
    if (fd == -1) { // Если канал не открыт
        perror("open"); // Вывод сообщения об ошибке
        exit(EXIT_FAILURE); // Выход из программы
    }
    return fd; // Возвращение дескриптора канала
}

int create_game_pipe(const std::string &game_name) {
    if (mkfifo(("game_" + game_name).c_str(), ACCESS_PERMS) == -1) { // Создание канала
        perror("mkfifo"); // Вывод сообщения об ошибке
        exit(EXIT_FAILURE); // Выход из программы
    }
    int fd = open(("game_" + game_name).c_str(), O_RDWR); // Открытие канала
    if (fd == -1) { // Если канал не открыт
        perror("open");
        exit(EXIT_FAILURE);
    }
    return fd;

int check(const std::string &game_word, const std::string &try_word, int &cows, int &bulls) {
    bulls = 0; // Инициализация переменной bulls
    cows = 0; // Инициализация переменной cows
    if (try_word.size() != game_word.size()) { // Если длина слова try_word не равна длине слова game_word
        return -1; // Возвращение значения -1
    }
    if (try_word == game_word) { // Если слова try_word и game_word равны
        return 1; // Возвращение значения 1
    }
    size_t size = game_word.size(); // Присваивание переменной size длины слова game_word
    for (size_t i = 0; i < size; ++i) { // Цикл по длине слова game_word
        for (size_t j = 0; j < size; ++j) { // Цикл по длине слова game_word
            if (game_word[i] == try_word[j]) { // Если символы слова game_word и try_word равны
                if (i == j) { // Если индексы символов равны
                    ++bulls; // Увеличение значения переменной bulls
                } else { // Если индексы символов не равны
                    ++cows; // Увеличение значения переменной cows
                }
            }
        }
    }
    return 0; // Возвращение значения 0
}

void game_func(const std::string &game_name, const std::string &game_word) {
    std::map<std::string, int> players_fd; // Создание словаря players_fd
    int fd = create_game_pipe(game_name); // Создание канала fd
    int cows, bulls; // Инициализация переменных cows и bulls
    std::string game_respond; // Инициализация переменной game_respond
    int game_status; // Инициализация переменной game_status

    std::cout << "START GAME: " << game_name << std::endl; // Вывод сообщения в консоль
    std::string login, cmd, data; // Инициализация переменных login, cmd и data
    while (true) { // Бесконечный цикл
        login = cmd = data = ""; // Присваивание переменным login, cmd и data пустых строк
        receive_from_client(fd, &login, &cmd, &data); // Получение данных от клиента
        if (cmd == "connect") { // Если команда равна "connect"
            players_fd[login] = open(login.c_str(), O_RDWR); // Открытие файла с именем login
            std::cout << "CLIENT " << login << " JOINED THE TABLE " << game_name << std::endl; // Вывод сообщения в консоль
            game_respond =
                    "Welcome to the game " + game_name + "\n" + "Make your guesses with the command \"maybe $word\""; // Присваивание переменной game_respond значения
            send_to_client(players_fd[login], game_respond); // Отправка сообщения клиенту
            game_respond = login + " connected to the game"; // Присваивание переменной game_respond значения
            for (const auto &it: players_fd) { // Цикл по словарю players_fd
                if (it.first != login){
                    send_to_client(it.second, game_respond); // Отправка сообщения клиенту
                }
            }
        } else if (cmd == "maybe") { // Если команда равна "maybe"
            game_status = check(game_word, data, cows, bulls); // Присваивание переменной game_status значения
            if (game_status == -1) { // Если game_status равно -1
                game_respond = "Wrong string size"; // Присваивание переменной game_respond значения
                send_to_client(players_fd[login], game_respond); // Отправка сообщения клиенту
            } else if (game_status == 1) { // Если game_status равно 1
                game_respond = "You won the game"; // Присваивание переменной game_respond значения
                send_to_client(players_fd[login], game_respond); // Отправка сообщения клиенту
                add_results(game_name, game_word, login); // Добавление результата
                game_respond = "Game is over. Winner is " + login + ". Game word is " + game_word + "."; // Присваивание переменной game_respond значения
                std::string annoy = "Please leave from the table. Use command \"leave\"."; // Присваивание переменной annoy значения
                for (const auto &it: players_fd) { // Цикл по словарю players_fd
                    game_respond += annoy; // Присваивание переменной game_respond значения
                    send_to_client(it.second, game_respond); // Отправка сообщения клиенту
                }
                for (const auto &it:players_fd){ // Цикл по словарю players_fd
                    while (true){ // Бесконечный цикл

		for (const auto &it:players_fd){ // Итерируемся по всем игрокам в игре
			while (true){ // Бесконечный цикл
       		 		receive_from_client(fd, &login, &cmd, &data); // Получаем данные от клиента
       				if (cmd == "leave"){ // Если команда - "leave"
            				std::cout << "PLAYER " << login << " LEFT THE TABLE " << game_name << std::endl; // Выводим сообщение о том, что игрок покинул игру
            				break; // Выходим из цикла
        			} else{ // Иначе
            			    	send_to_client(it.second, annoy); // Отправляем данные клиенту
        			}
    			}
		}
		close(fd); // Закрываем файловый дескриптор
		std::cout << "FINISH GAME: " << game_name << std::endl; // Выводим сообщение о том, что игра завершена
		int mainFD = open(SERVER_INPUT_FILE_NAME, O_RDWR); // Открываем файловый дескриптор
		game_respond = "finish"; // Устанавливаем значение переменной
		login = game_name; // Устанавливаем значение переменной
		send_to_server(mainFD, login, game_respond, data); // Отправляем данные на сервер
		return; // Возвращаем значение
	   } else { // Иначе
    		game_respond = "Bulls: " + std::to_string(bulls) + " Cows: " + std::to_string(cows); // Устанавливаем значение переменной
    		send_to_client(players_fd[login], game_respond); // Отправляем данные клиенту
	   }
	} else if (cmd == "leave") { // Иначе, если команда - "leave"
    		players_fd.erase(login); // Удаляем игрока из списка игроков
    		std::cout << "CLIENT " << login << " LEFT FROM THE TABLE " << game_name << std::endl; // Выводим сообщение о том, что игрок покинул игру
	}
    }
}


int main() { // Основная функция
    int fd_rec = create_main_pipe(); // Создаем файловый дескриптор
    std::map<std::string, int> logins_fds; // Создаем словарь
    std::vector<std::thread> games_threads; // Создаем вектор потоков
    std::vector<std::string> games_names; // Создаем вектор имен игр
    std::string game_name, game_word; // Создаем переменные
    std::string login, cmd, data; // Создаем переменные
    check_data_base(); // Проверяем базу данных
    while (true) { // Бесконечный цикл
        login = cmd = data = ""; // Устанавливаем значения переменных
        receive_from_client(fd_rec, &login, &cmd, &data); // Получаем данные от клиента
        if (cmd == "log") { // Если команда - "log"
            std::string password = data; // Устанавливаем значение переменной
            std::pair<std::string, std::string> pair = std::make_pair(login, password); // Создаем пару
            if (check_in_data_base(pair)) { // Если пара есть в базе данных
                std::cout << "NEW CLIENT: " << login << std::endl; // Выводим сообщение о том, что новый клиент подключился
                logins_fds[login] = create_client_pipe(login); // Создаем файловый дескриптор
            }
        } else if (cmd == "reg") { // Иначе, если команда - "reg"
            std::string password = data; // Устанавливаем значение переменной
            std::pair<std::string, std::string> pair = std::make_pair(login, password); // Создаем пару
            if (add_in_data_base(pair)) { // Если пара добавлена в базу данных
                std::cout << "NEW USER: " << login << std::endl; // Выводим сообщение о том, что новый пользователь зарегистрирован
                logins_fds[login] = create_client_pipe(login); // Создаем файловый дескриптор
            }
        } else if (cmd == "create") { // Иначе, если команда - "create"
            game_name = game_word = ""; // Устанавливаем значения переменных
            parse_game_word(data, game_name, game_word); // Парсим данные
            games_names.emplace_back("game_" + game_name); // Добавляем имя игры в вектор имен игр
            games_threads.emplace_back(std::thread(game_func, game_name, game_word)); // Создаем поток
        } else if (cmd == "quit") { // Иначе, если команда - "quit"
            close(logins_fds[login]); // Закрываем файловый дескриптор
            std::remove(login.c_str()); // Удаляем файл
            logins_fds.erase(login); // Удаляем клиента из списка клиентов
            std::cout << "CLIENT " << login << " LEFT THE GAME" << std::endl; // Выводим сообщение о том, что клиент покинул игру
        } else if (cmd == "shut_down" and login == ADMIN_NAME) { // Иначе, если команда - "shut_down" и логин - ADMIN_NAME
            std::string message = "SERVER CLOSED"; // Устанавливаем значение переменной
            for (auto &it: logins_fds) { // Итерируемся по всем клиентам
                send_to_client(it.second, message); // Отправляем сообщение клиенту
                close(it.second); // Закрываем файловый дескриптор
                remove
	    }
		for (size_t i = 0; i < games_threads.size(); ++i) { // Итерируемся по всем потокам
    			std::remove(games_names[i].c_str()); // Удаляем файл
    			games_threads[i].detach(); // Отсоединяем поток
		}
		std::remove(SERVER_INPUT_FILE_NAME); // Удаляем файл
		std::cout << "SERVER OFF" << std::endl; // Выводим сообщение о том, что сервер выключен
		exit(EXIT_SUCCESS); // Выходим из программы
	  }
     }
}
