# Intersection Sampler

Программа считывает из входного файла описание секущей плоскости и геометрического объекта (`cone` или `cylinder`), после чего формирует наборы точек для визуализации:

1. точки плоскости;
2. точки объекта;
3. точки кривой пересечения плоскости и объекта.

Проект написан на C++17, без сторонних C++ библиотек.

## Формат входного файла

Входной файл передаётся первым аргументом командной строки.

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
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

## Запуск из командной строки

Программа принимает два аргумента:

```bash
./IntersectionSampler <input_file> <output_directory>
```

Например, из папки `build`:

```bash
./IntersectionSampler ../data.txt ../out
```

После запуска в указанной папке будут созданы выходные файлы:

```txt
out/plane_points.txt
out/intersection_points.txt
out/shape_cone_points.txt
```

или для цилиндра:

```txt
out/shape_cylinder_points.txt
```

## Запуск в Visual Studio

Проект можно открыть в Visual Studio как CMake-проект:

```txt
File → Open → Folder...
```

После открытия Visual Studio должна автоматически сконфигурировать CMake-проект. Для сборки можно использовать:

```txt
Build → Build All
```

Для запуска программы нужно указать аргументы командной строки:

```txt
data.txt out
```

То есть первый аргумент — путь к входному файлу, второй аргумент — папка для сохранения выходных `.txt` файлов.

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
      "args": ["data.txt", "out"],
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
  --shape out/shape_cone_points.txt \
  --plane out/plane_points.txt \
  --intersection out/intersection_points.txt
```

Для цилиндра:

```bash
python3 plot_debug_scene.py \
  --shape out/shape_cylinder_points.txt \
  --plane out/plane_points.txt \
  --intersection out/intersection_points.txt
```

Скрипт создаёт HTML-файл `debug_scene.html`, который можно открыть в браузере. В нём отображаются четыре 3D-сцены:

1. объект;
2. плоскость;
3. кривая пересечения;
4. всё вместе.

## Геометрические ограничения

* координаты входных точек должны лежать в диапазоне `[-10.0, 10.0]`;
* радиус должен лежать в диапазоне `[0.0, 5.0]`;
* плоскость считается бесконечной;
* цилиндр считается прямым круговым цилиндром;
* конус считается прямым круговым конусом.

## Примечание

Программа формирует дискретный набор точек для визуализации. Точное аналитическое представление кривой пересечения не строится.
