# Задача 2. Исключения в конструкторах

В этом задании вы запретите создавать экземпляры классов геометрических фигур с неправильными данными.

Создайте собственный класс исключения для ошибки создания геометрической фигуры.Подумайте, от какого типа его унаследовать, и не забудьте поместить новый класс в отдельную пару файлов.

Возьмите иерархию классов из предыдущего задания.Теперь при создании экземпляров классов вам нужно проверять аргументы, которые поступают на вход конструктору.Если аргументы не соответствуют ограничениям, объект не должен быть создан, а на консоль должно быть выведено соответствующее сообщение.Причина ошибки должна быть сформулирована на уровне конструктора и выведена на экран при обработке ошибок.

Ограничения:

треугольник(стороны и углы произвольные, количество сторон равно 3, сумма углов равна 180);  
прямоугольный треугольник(угол C всегда равен 90);  
равнобедренный треугольник(стороны a и c равны, углы A и C равны);  
равносторонний треугольник(все стороны равны, все углы равны 60);  
четырёхугольник(стороны и углы произвольные, количество сторон равно 4, сумма углов равна 360);  
прямоугольник(стороны a, c и b, d попарно равны, все углы равны 90);  
квадрат(все стороны равны, все углы равны 90);  
параллелограмм(стороны a, c и b, d попарно равны, углы A, C и B, D попарно равны);  
ромб(все стороны равны, углы A, C и B, D попарно равны).  
Для проверки попробуйте создать разные геометрические фигуры — правильные и неправильные.В случае успешного создания выводите на экран сообщение об успешном создании и параметры фигуры.В случае, если создание не удалось, выведите причину ошибки.  

Пример работы программы  
Консоль  
Прямоугольный треугольник(стороны 3, 4, 5; углы 30, 60, 90) создан  
Ошибка создания фигуры.Причина: сумма углов не равна 180  
