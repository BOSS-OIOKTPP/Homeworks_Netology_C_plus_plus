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

    // ��� ������
    std::string toString() const {
        std::stringstream ss;
        ss << "�������������: " << client_id
           << ", ���: " << first_name << " " << last_name
           << ", Email: " << email
           << ", ��������: ";

        if (phones.empty()) {
            ss << "���";
        }
        else {
            for (size_t i = 0; i < phones.size(); ++i) {
                if (i > 0) ss << ", ";
                ss << phones[i];
            }
        }

        return ss.str();
    }
};

class ClientUtil {
private:
    std::string fconnection_string;
    std::unique_ptr<pqxx::connection> fconnection;
public:
    ClientUtil(const std::string& connection_string);

    // �������� ���������� � ��
    void �onnect();

    // �������� ���������� � ��
    bool isConnected() const;

    // ��������� ����������
    void Disconnect();

    

    // ������� �������
    void CreateTables();

    // ��������� �������
    int AddClient(const std::string& first_name, const std::string& last_name,
        const std::string& email, const std::vector<std::string>& phone_number);

    // �������� �������
    void UpdateClient(int client_id, const std::string& first_name, const std::string& last_name, const std::string& email);

    // ������� �������
    void DeleteClient(int client_id);

    // ��������� �������
    void AddPhoneNumber(int client_id, const std::string& phone_number);

    // ������� �������
    void DeletePhoneNumber(int client_id, const std::string& phone_number);

    // ����� �������
    std::vector<Client> FindClient(const int client_id, const std::string& first_name, const std::string& last_name,
        const std::string& email, const std::string& phone_number);

    // ����� ���������
    std::vector<std::string> GetClientPhones(int client_id);

    // ���������� � ���� ������
    std::string GetDatabaseInfo() const;
};

