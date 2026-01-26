@echo off
::chcp 1251 > nul

set OUT_DIR=..\..\Distributiv

:: === Удаляем старый дистрибутив ===
if exist "%OUT_DIR%" rmdir /S /Q "%OUT_DIR%"

:: === Создаём папку дистрибутива ===
mkdir "%OUT_DIR%"

:: Копируем исполняемые файлы
copy /Y "..\x64\Release\spider.exe" "%OUT_DIR%\" >nul
copy /Y "..\x64\Release\search_server.exe" "%OUT_DIR%\" >nul

:: Копируем config.ini из папки spider
copy /Y "..\spider\config.ini" "%OUT_DIR%\" >nul

:: Копируем все DLL
copy /Y "..\x64\Release\*.dll" "%OUT_DIR%\" >nul

::echo.
::echo Дистрибутив готов: %OUT_DIR%
::pause