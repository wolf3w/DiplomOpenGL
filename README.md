# Diplom OpenGL

## О проекте

Данный репозиторий хранит программу выпускной квалификационной работы (ВКР) бакалавра по специальности 09.03.03 "Прикладная информатика".  
Тема ВКР: **Численное решение задач нелинейных уравнений Клейна-Гордона и их визуализация с помощью OpenGL**  
Автор: Чумаков А.А.

Программа писалась на IDE QtCreator. Код связанный с OpenGL написан по статьям [Joey De Vries](https://joeydevries.com/#about) и их переводу на хабре.
В качестве библиотеки векторной алгебры использовался GLM. Разностная схема для рассчета нелинейного уравнения Клейна-Гордона была взята из книги Додда,
Эйлбека, Гиббона, Морриса "Солитоны и нелинейные волновые уравнения", схема под номером (10.6.9).

## Состав

Программа состоит из:

+ Класс Camera (camera.h, camera.cpp) - реализация простейшей камеры. Управление: перемещение на WASD, поворот камеры щелчком и движением мыши.
Упраление задается в классе OGLWidget
+ Класс MainWindow (mainwindow.h, mainwindow.cpp, mainwindow.ui) - окно
+ Класс Shader (shader.h, shader.cpp) - создание вершинного и фрагментного шейдеров и возврат шейдерной программы
+ Класс OGLWidget (oglwidget.hpp, oglwidget.cpp) - виджет в который происходит графический вывод. Унаследован от QOpenGLWidget.
В качестве полей содержит классы Camera, KGFEquation
+ Класс KGFEquation (kgfequation.h, kgfequation.cpp) - реализуется численный метод решения НУКГ для пространств x и y
+ Вершинный шейдер (vshader.vert) - вывод точек и их преобразование с помощью матрицы LookAt из GLM
+ Фрагментный шейдер (fshader.frag) - вывод цвета
+ Файл настроек Qt (DiplomOpenGL.pro) - для компилятора указан уровень оптимизации -O2 

## Ссылки

Статьи по Core OpenGL (оригинал): https://learnopengl.com/  
Перевод статей: https://habr.com/ru/post/310790/  
OpenGL Mathematics: https://glm.g-truc.net/0.9.9/index.html  
Выбор цвета для OpenGL: http://www.rgbtool.com/  

## Благодарность

Выражаю благодарность за помощь в создании программы научному руководителю Салимову Р.К.
