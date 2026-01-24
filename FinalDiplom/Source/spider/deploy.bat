@echo off
::chcp 1251 > nul

:: === Удаляем старый дистрибутив ===
if exist "..\..\Distributiv" rmdir /S /Q "..\..\Distributiv"

:: === Создаём папку дистрибутива ===
mkdir "..\..\Distributiv"

:: === Копируем исполняемый файл ===
copy "x64\Release\spider.exe" "..\..\Distributiv\" /Y

:: === Копируем config.ini ===
copy "config.ini" "..\..\Distributiv\" /Y

:: === Копируем DLL из vcpkg ===
copy "C:\Tools\vcpkg\installed\x64-windows\bin\pqxx.dll" "..\..\Distributiv\pqxx.dll" /Y
copy "C:\Tools\vcpkg\installed\x64-windows\bin\libssl-3-x64.dll" "..\..\Distributiv\libssl.dll" /Y
copy "C:\Tools\vcpkg\installed\x64-windows\bin\libcrypto-3-x64.dll" "..\..\Distributiv\libcrypto.dll" /Y

:: === Копируем libpq.dll из PostgreSQL ===
copy "C:\Program Files\PostgreSQL\17\bin\libpq.dll" "..\..\Distributiv\" /Y

::echo.
::echo ?? Дистрибутив собран в: ..\..\Distributiv
::pause