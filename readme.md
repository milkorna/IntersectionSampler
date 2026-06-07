# Intersection Sampler

Программа считывает из входного файла описание секущей плоскости и геометрического объекта (`cone` или `cylinder`), после чего формирует наборы точек для визуализации:

1. точки плоскости;
2. точки объекта;
3. точки кривой пересечения плоскости и объекта.

## Геометрические ограничения

* координаты входных точек должны лежать в диапазоне `[-10.0, 10.0]`;
* радиус должен лежать в диапазоне `[0.0, 5.0]`;
* плоскость считается бесконечной;
* цилиндр считается прямым круговым цилиндром;
* конус считается прямым круговым конусом.

## Примечание

Программа формирует дискретный набор точек для визуализации. Точное аналитическое представление кривой пересечения не строится.

## Требования

* C++17;
* CMake версии 3.16 или выше;
* сторонние C++ библиотеки не требуются;
* для визуализации требуется Python 3 и библиотека `plotly`.

## Формат входного файла

Формат входных данных `data.txt`:

```txt
plane
x1 y1 z1
x2 y2 z2
x3 y3 z3
cone/cylinder
x1 y1 z1
x2 y2 z2
radius
```

Для конуса:

* первая точка объекта — центр основания;
* вторая точка объекта — вершина конуса.

Для цилиндра:

* первая точка объекта — центр первого основания;
* вторая точка объекта — центр второго основания.

## Сборка из командной строки

Из корня проекта:

```bash
cmake -S . -B build
cmake --build build
```

## Запуск из командной строки

Программа принимает два аргумента:

```bash
./IntersectionSampler <input_file> <output_directory>
```

Например, из папки `build`:

```bash
./IntersectionSampler ../data.txt ../result
```

После запуска в указанной папке будут созданы выходные файлы:

```txt
result/plane_points.txt
result/intersection_points.txt
result/shape_cone_points.txt
```

или для цилиндра:

```txt
result/shape_cylinder_points.txt
```

## Запуск в Visual Studio

Проект можно открыть в Visual Studio:

```txt
File → Open → Folder...
```

После открытия Visual Studio должна автоматически сконфигурировать CMake-проект. Для сборки можно использовать:

```txt
Build → Build All
```

или выбрать target `IntersectionSampler.exe` и собрать его отдельно.

Для запуска программы нужно указать аргументы командной строки:

```txt
data.txt result
```

Если используется `launch.vs.json`, конфигурация может выглядеть примерно так:

```json
{
  "version": "0.2.1",
  "defaults": {},
  "configurations": [
    {
      "type": "default",
      "project": "CMakeLists.txt",
      "projectTarget": "IntersectionSampler.exe",
      "name": "IntersectionSampler",
      "args": [
        "data.txt",
        "result"
      ],
      "currentDir": "${workspaceRoot}"
    }
  ]
}
```

## Визуализация

Для отладки можно использовать Python-скрипт `plot_debug_scene.py`.

Установить зависимость:

```bash
pip install plotly
```

Для конуса:

```bash
python3 plot_debug_scene.py \
  --shape result/shape_cone_points.txt \
  --plane result/plane_points.txt \
  --intersection result/intersection_points.txt
```

Для цилиндра:

```bash
python3 plot_debug_scene.py \
  --shape result/shape_cylinder_points.txt \
  --plane result/plane_points.txt \
  --intersection result/intersection_points.txt
```

Скрипт создаёт HTML-файл `debug_scene.html`, который можно открыть в браузере. В нём отображаются четыре 3D-сцены:

1. объект;
2. плоскость;
3. кривая пересечения;
4. всё вместе.


