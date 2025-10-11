#pragma once

#include <pqxx/pqxx>
#include <string>
#include <vector>


struct Client {
    int client_id;
    std::string first_name;
    std::string last_name;
    std::string email;
    std::vector<std::string> phones;
};

class ClientUtil {
private:
    std::string fconnection_string;
    std::unique_ptr<pqxx::connection> fconnection;
public:
    ClientUtil(const std::string& connection_string);

    // �������� ���������� � ��
    bool �onnect(std::string& err);

    // �������� ���������� � ��
    bool isConnected() const;

    // ��������� ����������
    void Disconnect();

    

    // ������� �������
    bool CreateTables(std::string& err);

    // ��������� �������
    bool AddClient(const std::string& first_name, const std::string& last_name,
        const std::string& email, const std::vector<std::string>& phone_number, int& out_client_id, std::string& err);

    // �������� �������
    bool UpdateClient(int client_id, const std::string& first_name, const std::string& last_name, 
        const std::string& email, std::string& err);

    // ������� �������
    bool DeleteClient(int client_id, std::string& err);

    // ��������� �������
    bool AddPhoneNumber(int client_id, const std::string& phone_number, std::string& err);

    // ������� �������
    bool DeletePhoneNumber(int client_id, const std::string& phone_number, std::string& err);

    // ����� �������
    bool FindClient(const std::string& first_name, const std::string& last_name,
        const std::string& email, const std::string& phone_number, int& client_id, std::string& err);



    // ���������� � ���� ������
    std::string GetDatabaseInfo() const;
};

