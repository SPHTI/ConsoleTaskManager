#define NOMINMAX
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <windows.h>

using namespace std;

struct Task {
    string title;
    string description;
    bool completed;
};

void printTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "Список задач пуст.\n";
        return;
    }

    cout << "\nСписок задач:\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << i + 1 << ". "
             << "[" << (tasks[i].completed ? "X" : " ") << "] "
             << tasks[i].title << "\n   "
             << tasks[i].description << "\n\n";
    }
}

vector<Task> loadTasksFromFile(const string& filename) {
    vector<Task> tasks;
    ifstream file(filename, ios::binary);

    if (file.is_open()) {
        // Пропускаем BOM для UTF-8
        if (file.get() != 0xEF || file.get() != 0xBB || file.get() != 0xBF) {
            file.seekg(0);
        }

        Task task;
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            
            task.title = line;
            
            if (!getline(file, line)) break;
            task.description = line;
            
            if (!getline(file, line)) break;
            task.completed = (line == "1");
            
            tasks.push_back(task);
            
            // Пропускаем разделитель
            getline(file, line);
        }
        file.close();
    }
    return tasks;
}

void saveTasksToFile(const vector<Task>& tasks, const string& filename) {
    ofstream file(filename, ios::binary | ios::trunc);
    if (file.is_open()) {
        // Добавляем BOM для UTF-8
        file << "\xEF\xBB\xBF";
        
        for (const auto& task : tasks) {
            file << task.title << "\n"
                 << task.description << "\n"
                 << (task.completed ? "1" : "0") << "\n\n";
        }
        file.close();
    }
    else {
        cerr << "Ошибка при сохранении задач!\n";
    }
}

void addTask(vector<Task>& tasks) {
    Task newTask;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Введите название задачи: ";
    if (!getline(cin, newTask.title) || newTask.title.empty()) {
        cout << "Ошибка: название задачи не может быть пустым!\n";
        return;
    }

    cout << "Введите описание задачи: ";
    if (!getline(cin, newTask.description)) {
        cout << "Ошибка ввода описания!\n";
        return;
    }

    newTask.completed = false;
    tasks.push_back(newTask);
    cout << "Задача успешно добавлена!\n";
}

void markTaskCompleted(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "Список задач пуст.\n";
        return;
    }

    printTasks(tasks);
    cout << "Введите номер задачи для отметки: ";
    size_t index;
    if (!(cin >> index)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка: введите число!\n";
        return;
    }

    if (index > 0 && index <= tasks.size()) {
        tasks[index - 1].completed = true;
        cout << "Задача успешно отмечена как выполненная!\n";
    }
    else {
        cout << "Неверный номер задачи!\n";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void deleteTask(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "Список задач пуст.\n";
        return;
    }

    printTasks(tasks);
    cout << "Введите номер задачи для удаления: ";
    size_t index;
    if (!(cin >> index)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка: введите число!\n";
        return;
    }

    if (index > 0 && index <= tasks.size()) {
        tasks.erase(tasks.begin() + index - 1);
        cout << "Задача успешно удалена!\n";
    }
    else {
        cout << "Неверный номер задачи!\n";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    // Настройки кодировки для Windows
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    system("chcp 65001 > nul");  // Принудительная установка UTF-8

    const string filename = "tasks.txt";
    vector<Task> tasks = loadTasksFromFile(filename);
    int choice;

    do {
        cout << "\n=== Менеджер задач ===\n"
             << "1. Показать задачи\n"
             << "2. Добавить задачу\n"
             << "3. Отметить задачу как выполненную\n"
             << "4. Удалить задачу\n"
             << "5. Выход\n"
             << "Выберите действие: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода! Попробуйте снова.\n";
            continue;
        }

        switch (choice) {
            case 1:
                printTasks(tasks);
                break;
            case 2:
                addTask(tasks);
                saveTasksToFile(tasks, filename);
                break;
            case 3:
                markTaskCompleted(tasks);
                saveTasksToFile(tasks, filename);
                break;
            case 4:
                deleteTask(tasks);
                saveTasksToFile(tasks, filename);
                break;
            case 5:
                cout << "Выход из программы...\n";
                break;
            default:
                cout << "Неверный выбор! Попробуйте снова.\n";
        }
    } while (choice != 5);

    return 0;
}