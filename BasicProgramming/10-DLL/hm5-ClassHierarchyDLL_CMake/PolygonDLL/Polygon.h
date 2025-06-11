#pragma once

#ifdef POLYGONDLL_EXPORTS
    #define POLYGON_API __declspec(dllexport)
#else
    #define POLYGON_API __declspec(dllimport)
#endif

#include <string>

// ������� �����
class TPolygon {
protected:
    int FSides;         // ���������� ������
    std::string FName;  // �������� ������
public:
    POLYGON_API TPolygon();

    POLYGON_API int GetSides();
    POLYGON_API std::string GetName();

    POLYGON_API virtual void Print();
};

