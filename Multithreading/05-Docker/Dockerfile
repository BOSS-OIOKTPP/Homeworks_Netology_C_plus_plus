FROM ubuntu:latest

# Копируем исходный код в контейнер
COPY . /usr/src/Dockertest

# Устанавливаем рабочую директорию
WORKDIR /usr/src/Dockertest

# Устанавливаем компиляторы и собираем проект двумя способами
RUN apt update && \  
    apt install -y \
        g++ \
        clang && \
    g++ -o hw1-Months-g++ hw1-Months.cpp && \
    clang++ -o hw1-Months-clang hw1-Months.cpp

# Проверяем результат, запуская по очереди
CMD echo "=== Результат g++ ===" && \
    ./hw1-Months-g++ && \
    echo -e "\n=== Результат clang ===" && \
    ./hw1-Months-clang