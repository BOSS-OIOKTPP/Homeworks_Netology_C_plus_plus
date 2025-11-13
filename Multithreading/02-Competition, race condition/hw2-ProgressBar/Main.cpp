#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <iomanip>
#include <random>


const int MAX_THREADS = 7;
const int BASE_CALC_COUNT = 100;

const  int width_N = 3;
const  int width_Id = 6;
const  int width_ProgressBar = 22;
const  int width_Time = 10;
const  int width_CalcCount = 10;
const  int width_Space = 2;

std::mutex m;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void SetColor(int text, int background);  // Установка цвета шрифта в консоле
void SetPosition(int x, int y);           // Установка позиции курсора в консоле

void calculate(int num_thread); // Имитация расчета




int main() {
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

	// Инициализируем генератор случайных чисел, чтобы при каждом запуске генерировались разные числа
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	// Устанавливаем фиксированный формат вывода с 7 знаками после запятой
	std::cout << std::fixed << std::setprecision(7);

	// Делаем шапку 
	std::cout << std::setw(width_N)           << std::left << "#"            << std::setw(width_Space) << ""
			  << std::setw(width_Id)          << std::left << "Id"           << std::setw(width_Space) << ""
			  << std::setw(width_ProgressBar) << std::left << "Progress Bar" << std::setw(width_Space) << ""
			  << std::setw(width_Time)        << std::left << "Time"		 << std::setw(width_Space) << ""
		      << std::setw(width_CalcCount)   << std::left << "Calc count"
			  << std::endl << std::endl;

	// Массив потоков
	std::thread* t = new std::thread[MAX_THREADS];
	
	// Создаем потоки
	for (int i = 0; i < MAX_THREADS; ++i)
		t[i] = std::thread(calculate, i);

	// Ожидаем выполнения потоков
	for (int i = 0; i < MAX_THREADS; ++i)
		t[i].join();

	// завершаем программу
	SetPosition(0, 2 + MAX_THREADS + 1);
	std::cout << "Все потоки завершены.";
	
	// удаляем массив
	delete[] t;

	std::cout << std::endl << std::endl;
	system("pause");


    return EXIT_SUCCESS;
}



void SetColor(int text, int background)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void SetPosition(int x, int y)
{
	COORD point;
	point.X = x;
	point.Y = y;
	SetConsoleCursorPosition(hStdOut, point);
}

// Имитация расчета
void calculate(int num_thread) {
	// старт времени
	auto start_time = std::chrono::steady_clock::now();

	// координаты курсора по умолчанию
	int col{ 0 };               // текущий столбец 	
	int row{ 2 + num_thread };  // текущая строка
	// переменные для отслеживания прогресса
	int progress_bar_last_pos = -1; // последняя позиция в прогресс баре
	int progress_bar_start_col = width_N + width_Space + width_Id + width_Space + 1; // начало прогресс бара (после '[')
	int progress_bar_total_pos = width_ProgressBar - 2; // количество позиций для заполнения, -2 это скобки []


	// создаем генератор случайных чисел
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> multiplier_dist(1, 7);                          // коэффициент для вычисления количества расчетов
	std::uniform_int_distribution<int> error_chance_dist(1, 100);                      // процент для задания ошибки
	std::uniform_int_distribution<int> error_pos_dist(0, progress_bar_total_pos - 1);  // позиция ошибки


	// для моделирования работы для каждого потока получаем случайное количество итераций относительно базового
	// так получается более наглядно, чем изменение задержки
	int multiplier = multiplier_dist(gen);
	int thread_calc_count = BASE_CALC_COUNT * multiplier;


	// рисуем первые три поля
	m.lock(); {
		// записываем номер потока
		SetPosition(col, row);  std::cout << std::setw(width_N) << std::left << num_thread;
		// записываем идентификатор потока
		col = width_N + width_Space;
		SetPosition(col, row);  std::cout << std::setw(width_Id) << std::left << std::this_thread::get_id();
		// рисуем область прогресс-бара
		col = width_N + width_Space + width_Id + width_Space;
		SetPosition(col, row);  std::cout << "[" << std::string(progress_bar_total_pos, ' ') << "]";
	}
	m.unlock();


	// запускаем процесс моделирования работы
	for (int i = 0; i < thread_calc_count; ++i) {
		// делаем задержку, для имитации вычислений
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		// вычисляем текущую позицию в прогресс-баре
		double progress = static_cast<double>(i + 1) / thread_calc_count;
		int current_progress_pos = static_cast<int>(progress * progress_bar_total_pos + 0.5);

		// контролируем правую границу 
		if (current_progress_pos > progress_bar_total_pos - 1) {
			current_progress_pos = progress_bar_total_pos - 1;
		}

		// выводим только если позиция изменилась
		if (current_progress_pos != progress_bar_last_pos) {
			m.lock(); {
				// устанавливаем позицию внутри прогресс-бара
				col = progress_bar_start_col + current_progress_pos;
				SetPosition(col, row);

				// проверяем каждую позицию на ошибки
				int err_proc = error_chance_dist(gen);
				bool is_error_position = (err_proc <= 10); // 10% вероятность ошибки для этой позиции

				// если это ошибка
				if (is_error_position) {
					// выводим красный символ ошибки
					SetColor(12, 0);                      // красный текст
					SetConsoleOutputCP(437);              // временно переключаем на кодовую страницу 437 для псевдографики
					std::cout << static_cast<char>(178);  // печатаем символ ▓
					SetConsoleOutputCP(1251);             // возвращаем обратно кодовую страницу
					SetColor(7, 0);                       // возвращаем белый цвет
				}
				else {
					// Обычный вывод
					SetConsoleOutputCP(437);              // временно переключаем на кодовую страницу 437 для псевдографики
					std::cout << static_cast<char>(178);  // печатаем символ ▓
					SetConsoleOutputCP(1251);             // возвращаем обратно кодовую страницу
				}

				// запоминаем позицию
				progress_bar_last_pos = current_progress_pos;
			}
			m.unlock();
		}
	}

	// вычисляем время работы потока
	auto end_time = std::chrono::steady_clock::now();
	std::chrono::duration<double> duration = end_time - start_time;

	// записываем оставшиеся поля
	m.lock(); {
		col = width_N + width_Space + width_Id + width_Space + width_ProgressBar + width_Space;
		SetPosition(col, row);
		std::cout << duration.count();

		col = col + width_Time + width_Space;
		SetPosition(col, row);
		std::cout << thread_calc_count;
	}
	m.unlock();
}