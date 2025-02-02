# ConsoleTaskManager

![C++](https://img.shields.io/badge/C++-17%2B-blue)
![CMake](https://img.shields.io/badge/CMake-3.10%2B-brightgreen)

Простое консольное приложение для управления задачами с сохранением данных в файл.

## Особенности

- 📝 Добавление задач с названием и описанием
- ✅ Отметка выполненных задач
- 🗑️ Удаление задач
- 💾 Автосохранение в файл `tasks.txt`
- 🖥️ Консольный интерфейс с меню

## Установка

1. Клонируйте репозиторий:
```bash
git clone https://github.com/yourusername/task-manager.git
```

2. Соберите проект с помощью CMake:
```bash
mkdir build && cd build
cmake ..
cmake --build .
```

3. Запустите программу:
```bash
./TaskManager
```

## Использование

Главное меню:
```
=== Менеджер задач ===
1. Показать задачи
2. Добавить задачу
3. Отметить задачу как выполненную
4. Удалить задачу
5. Выход
```

Пример работы:
1. Выберите "Добавить задачу"
2. Введите название и описание
3. Просмотрите список задач
4. Сохраняйте изменения автоматически

## Известные проблемы и решения

### Проблема с русским языком

В некоторых окружениях (особенно в Windows) могут наблюдаться:
- Искаженные символы в консоли
- Некорректное сохранение в файл
- Ошибки кодировки

**Решения:**
1. Для Windows:
   - Используйте [Windows Terminal](https://aka.ms/terminal)
   - В свойствах консоли:
     - Выберите шрифт "Consolas" или "Lucida Console"
     - Включите опцию "Использовать Юникод (UTF-8)"
   - Запустите команду перед стартом программы:
     ```bash
     chcp 65001
     ```

2. Для всех систем:
   - Убедитесь что файлы сохранены в кодировке **UTF-8 без BOM**
   - Используйте современные терминалы (iTerm2, GNOME Terminal)

3. В редакторе кода:
   - Для VS Code добавьте в `settings.json`:
     ```json
     "files.encoding": "utf8",
     "files.autoGuessEncoding": true
     ```

## Структура проекта
```
.
├── CMakeLists.txt
├── src
│   └── main.cpp
├── tasks.txt (создается автоматически)
└── README.md
```

## Разработка

Требования:
- Компилятор C++ с поддержкой C++11
- CMake 3.10+

Сборка для разработки:
```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
```