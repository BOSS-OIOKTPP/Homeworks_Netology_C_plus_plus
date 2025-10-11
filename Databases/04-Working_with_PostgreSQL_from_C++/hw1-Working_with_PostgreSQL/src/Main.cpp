#include <iostream>
#include <windows.h>
#include <string>
#include <pqxx/pqxx>
#include "ClientUtil.h"



int main()
{
    // Установили кодировку
    SetConsoleCP(1251);       // 65001
    SetConsoleOutputCP(1251); // 65001
  

    std::locale::global(std::locale(""));

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
    
    // Строка с текстом ошибки 
    std::string err{};

    // Создаем объект для работы с базой данных
    ClientUtil Util(connection_string);
    if (Util.Сonnect(err)) {
        std::cout << "Соединение с базой данных установлено:" << std::endl;
        std::cout << Util.GetDatabaseInfo() << std::endl;
        std::cout << std::endl;
    }
    else {
        std::cout << "Не удалось подключится к базе данных: " << err << std::endl;
        return 1;
    }
    
    // 1. Создаем таблицы - если не получилось, выходим
    if (Util.CreateTables(err)) {
        std::cerr << "1. Таблицы успешно созданы. " << std::endl;
        std::cout << std::endl;
    }
    else {
        std::cerr << "1. ОШИБКА. Не удалось создать таблицы. " << err << std::endl;
        std::cout << std::endl;
        return 1;
    }

    // 2. Добавляем первого клиента без телефонов
    int client_id_1{0};
    if (Util.AddClient("Иван", "Иванов", "ivan@mail.com", {}, client_id_1, err)) {
        std::cerr << "2. Добавлен первый клиент, идентификатор " << client_id_1 << "." << std::endl;
        std::cout << std::endl;
    }
    else {
        std::cerr << "2. ОШИБКА. Не удалось добавить клиента 1. " << err << std::endl;
        std::cout << std::endl;
        //return 1;
    }

    // 3. Добавляем телефон первому клиенту
    std::string phone_number_str{ "+74951234567" };
    if (Util.AddPhoneNumber(client_id_1, phone_number_str, err)) {
        std::cerr << "3. Добавлен номер телефона +74951234567 клиенту с идентификатором " << client_id_1 << "." << std::endl;
        std::cout << std::endl;
    }
    else {
        std::cerr << "3. ОШИБКА. Не удалось добавить новый номер телефона клиенту с идентификатором " << client_id_1 << "." << std::endl;
        std::cout << std::endl;
        //return 1;
    }

    // 4. Изменяем клиента 1           "Иван", "Иванов", "ivan@mail.com"
    if (Util.UpdateClient(client_id_1, "", "Петров", "ivan.new@mail.com", err)) {
        std::cerr << "4. Изменили фамилию и почту клиента с идентификатором " << client_id_1 << " на Петров и ivan.new@mail.com соответственно." << std::endl;
        std::cout << std::endl;
    }
    else {
        std::cerr << "4. ОШИБКА. Не удалось внести изменения клиенту с идентификатором " << client_id_1 << ". " << err << std::endl;
        std::cout << std::endl;
        //return 1;
    }

    // 5. Добавляем второго клиента с телефонами
    std::vector<std::string> phone_number_2 = { "+79161234567", "+79164567123" };
    int client_id_2{ 0 };
    if (Util.AddClient("Мария", "Иванова", "maria@mail.com", phone_number_2, client_id_2, err)) {
        std::cerr << "5. Добавлен второй клиент, идентификатор " << client_id_2 << "." << std::endl;
        std::cout << std::endl;
    }
    else {
        std::cerr << "5. ОШИБКА. Не удалось добавить клиента 2. " << err << std::endl;
        std::cout << std::endl;
        //return 1;
    }

    // 6. Удаляем у второго клиента первый телефон 
    if (Util.DeletePhoneNumber(client_id_2, "+79161234567", err)) {
        std::cerr << "6. Удалили телефон +79161234567 у второго клиент" << std::endl;
        std::cout << std::endl;
    }
    else {
        std::cerr << "6. ОШИБКА. Не удалось удалить телефон. " << err << std::endl;
        std::cout << std::endl;
        //return 1;
    }  

    // 7. Добавляем третьего клиента с телефонами
    std::vector<std::string> phone_number_3 = { "+79161987567", "+79004567123" };
    int client_id_3{ 0 };
    if (Util.AddClient("Алексей", "Козлов", "alex@mail.com", phone_number_3, client_id_3, err)) {
        std::cerr << "7. Добавлен третий клиент, идентификатор " << client_id_3 << "." << std::endl;
        std::cout << std::endl;
    }
    else {
        std::cerr << "7. ОШИБКА. Не удалось добавить клиента 3. " << err << std::endl;
        std::cout << std::endl;
        //return 1;
    }

    // 8. Удаляем третьего клиента, телефоны удаляются каскадно базой данных
    if (Util.DeleteClient(client_id_3, err)) {
        std::cerr << "8. Удален третий клиент с идентификатором " << client_id_3 << "." << std::endl;
        std::cout << std::endl;
    }
    else {
        std::cerr << "8. ОШИБКА. Не удалось удалить клиента с идентификатором " << client_id_3 << ". " << err << std::endl;
        std::cout << std::endl;
        //return 1;
    }


    // 9. Поиск по полям - ТОЧНОЕ СОВПАДЕНИЕ ЗНАЧЕНИЙ
    int client_id_find{ 0 };
    if (Util.FindClient("","","","+79164567123", client_id_find, err)) {
        std::cerr << "9. Найден клиент с номером +79164567123 и идентификатором " << client_id_find << "." << std::endl;
        std::cout << std::endl;
    }
    else {
        std::cerr << "9. Не удалось найти клиента по номеру +79164567123. " << err << std::endl;
        std::cout << std::endl;
        //return 1;
    }

    
    // 10. Поиск по полям - ТОЧНОЕ СОВПАДЕНИЕ ЗНАЧЕНИЙ
    client_id_find=0;
    if (Util.FindClient("", "", "ivan.new@mail.com", "", client_id_find, err)) {
        std::cerr << "10. Найден клиент с email=ivan.new@mail.com и идентификатором " << client_id_find << "." << std::endl;
        std::cout << std::endl;
    }
    else {
        std::cerr << "10. Не удалось найти клиента email=ivan.new@mail.com. " << err << std::endl;
        std::cout << std::endl;
        //return 1;
    }


    system("pause");

    return EXIT_SUCCESS;
}