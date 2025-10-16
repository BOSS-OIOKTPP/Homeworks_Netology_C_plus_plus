#include <iostream>
#include <windows.h>
#include <string>
#include <pqxx/pqxx>
#include "ClientUtil.h"


void PrintClients(const std::vector<Client>& clients) {
    if (clients.empty()) {
        std::cout << "Клиенты не найдены" << std::endl;
        return;
    }

    for (const auto& client : clients) {
        std::cout << client.toString() << std::endl;
    }
}


int main()
{
    // Установили кодировку
    SetConsoleCP(1251);       // 65001
    SetConsoleOutputCP(1251); // 65001
  

    //std::locale::global(std::locale(""));


    std::cout << "Проверка библиотеки libpqxx:" << std::endl;

    try {        
        std::cout << "Version: " << PQXX_VERSION << std::endl;
        std::cout << "Готова к работе!" << std::endl << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "ОШИБКА: " << e.what() << std::endl;
        return 1;
    }
    std::cout << std::endl;

    // Строка соединения с базой данной
    std::string connection_string {
        "host=localhost "
        "port=5432 "
        "dbname=client "
        "user=postgres "
        "password=1" 
    };
    
    
    // Создаем объект для работы с базой данных
    ClientUtil Util(connection_string);

    // Соединяемся с базой данных
    try {        
        Util.Сonnect();
    }
    catch (const std::exception& e) {
        std::cout << "Не удалось подключится к базе данных: " << e.what() << std::endl;
        return 1;        
    }

    // Информация о базе данных
    std::cout << "Соединение с базой данных установлено:" << std::endl;
    std::cout << Util.GetDatabaseInfo() << std::endl;
    std::cout << std::endl;

    // 1. Создаем таблицы - если не получилось, выходим
    try {
        Util.CreateTables();
        std::cerr << "1. Таблицы успешно созданы. " << std::endl;
        std::cout << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "1. ОШИБКА. Не удалось создать таблицы. " << e.what() << std::endl;
        std::cout << std::endl;
        return 1;
    }

    // 2. Добавляем первого клиента без телефонов
    int client_id_1{ 0 };
    try {
        client_id_1 = Util.AddClient("Иван", "Иванов", "ivan@mail.com", {});
        std::cerr << "2. Добавлен первый клиент" << std::endl;
        auto find_res = Util.FindClient(client_id_1, "", "", "", "");
        PrintClients(find_res);
        std::cout << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "2. ОШИБКА. Не удалось добавить клиента 1. " << e.what() << std::endl;
        std::cout << std::endl;
        return 1;
    }

    // 3. Добавляем телефон первому клиенту
    std::string phone_number_str{ "+74951234567" };
    try {
        Util.AddPhoneNumber(client_id_1, phone_number_str);
        std::cerr << "3. Добавлен номер телефона +74951234567 первому клиенту"  << std::endl;
        auto find_res = Util.FindClient(client_id_1, "", "", "", "");
        PrintClients(find_res);
        std::cout << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "3. ОШИБКА. Не удалось добавить новый номер телефона +74951234567 клиенту с идентификатором " << client_id_1 << ". " << e.what() << std::endl;
        std::cout << std::endl;
        //return 1;
    }

    // 4. Изменяем клиента 1           "Иван", "Иванов", "ivan@mail.com"
    try {
        Util.UpdateClient(client_id_1, "", "Петров", "ivan.new@mail.com"); 
        std::cerr << "4. Изменили фамилию и почту первого клиента" << std::endl;
        auto find_res = Util.FindClient(client_id_1, "", "", "", "");
        PrintClients(find_res);
        std::cout << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "4. ОШИБКА. Не удалось внести изменения клиенту с идентификатором " << client_id_1 << ". " << e.what() << std::endl;
        std::cout << std::endl;
        //return 1;
    }

    // 5. Добавляем второго клиента с телефонами
    std::vector<std::string> phone_number_2 = { "+79161234567", "+79164567123" };
    int client_id_2{ 0 };
    try {
        client_id_2 = Util.AddClient("Мария", "Иванова", "maria@mail.com", phone_number_2);
        std::cerr << "5. Добавлен второй клиент" << std::endl;
        auto find_res = Util.FindClient(client_id_2, "", "", "", "");
        PrintClients(find_res);
        std::cout << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "5. ОШИБКА. Не удалось добавить клиента 2. " << e.what() << std::endl;
        std::cout << std::endl;
        //return 1;
    }

    // 6. Удаляем у второго клиента первый телефон 
    try {
        Util.DeletePhoneNumber(client_id_2, "+79161234567");
        std::cerr << "6. Удалили телефон +79161234567 у второго клиент" << std::endl;
        auto find_res = Util.FindClient(client_id_2, "", "", "", "");
        PrintClients(find_res);
        std::cout << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "6. ОШИБКА. Не удалось удалить телефон. " << e.what() << std::endl;
        std::cout << std::endl;
        //return 1;
    }  

    // 7. Добавляем третьего клиента с телефонами
    std::vector<std::string> phone_number_3 = { "+79161987567", "+79004567123" };
    int client_id_3{ 0 };
    try {
        client_id_3 = Util.AddClient("Алексей", "Козлов", "alex@mail.com", phone_number_3); 
        std::cerr << "7. Добавлен третий клиент" << std::endl;
        auto find_res = Util.FindClient(client_id_3, "", "", "", "");
        PrintClients(find_res);
        std::cout << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "7. ОШИБКА. Не удалось добавить клиента 3. " << e.what() << std::endl;
        std::cout << std::endl;
        //return 1;
    }

    // 8. Удаляем третьего клиента, телефоны удаляются каскадно базой данных
    try {
        Util.DeleteClient(client_id_3);
        std::cerr << "8. Удален третий клиент с идентификатором " << client_id_3 << "." << std::endl;
        auto find_res = Util.FindClient(client_id_3, "", "", "", "");
        PrintClients(find_res);
        std::cout << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "8. ОШИБКА. Не удалось удалить клиента с идентификатором " << client_id_3 << ". " << e.what() << std::endl;
        std::cout << std::endl;
        //return 1;
    }


    // 9. Поиск по почте
    std::cerr << "9. Поиск по почте 'ivan%'" << std::endl;    
    auto find_res9 = Util.FindClient(0, "", "", "ivan%", "");
    PrintClients(find_res9);
    std::cout << std::endl;

    // 10. Поиск по имени
    std::cerr << "10. Поиск по имени 'Мария'" << std::endl;
    auto find_res10 = Util.FindClient(0, "Мария", "", "", "");
    PrintClients(find_res10);
    std::cout << std::endl;

    system("pause");

    return EXIT_SUCCESS;
}