#include <iostream>
#include <string>
#include <limits>
#include "task_queue.h"

using namespace std;

// ---------- Конкретные задачи ----------

class print_task : public task
{
public:
    print_task(const string& text_)
        : text(text_) {}

    void execute() override
    {
        cout << "Сообщение: " << text << "\n";
    }

protected:
    void print(ostream& stream) const override
    {
        stream << "print_task(\"" << text << "\")";
    }

private:
    string text;
};

class sum_task : public task
{
public:
    sum_task(int a_, int b_)
        : a(a_), b(b_) {}

    void execute() override
    {
        cout << a << " + " << b << " = " << a + b << "\n";
    }

protected:
    void print(ostream& stream) const override
    {
        stream << "sum_task(" << a << ", " << b << ")";
    }

private:
    int a;
    int b;
};

class multiply_task : public task
{
public:
    multiply_task(int a_, int b_)
        : a(a_), b(b_) {}

    void execute() override
    {
        cout << a << " * " << b << " = " << a * b << "\n";
    }

protected:
    void print(ostream& stream) const override
    {
        stream << "multiply_task(" << a << ", " << b << ")";
    }

private:
    int a;
    int b;
};

class countdown_task : public task
{
public:
    countdown_task(int n_)
        : n(n_) {}

    void execute() override
    {
        cout << "Обратный отсчёт: ";
        for (int i = n; i >= 0; --i)
        {
            cout << i;
            if (i > 0) cout << ' ';
        }
        cout << "\n";
    }

protected:
    void print(ostream& stream) const override
    {
        stream << "countdown_task(" << n << ")";
    }

private:
    int n;
};

// ---------- Вспомогательные функции ----------

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void printMenu()
{
    cout << "\n======= ОЧЕРЕДЬ ЗАДАЧ =======\n"
         << "1. Добавить print_task\n"
         << "2. Добавить sum_task\n"
         << "3. Добавить multiply_task\n"
         << "4. Добавить countdown_task\n"
         << "5. Выполнить первую задачу\n"
         << "6. Выполнить все задачи\n"
         << "7. Проверить пустоту очереди\n"
         << "0. Выход\n"
         << "=============================\n"
         << "Выбор: ";
}

int readPriority()
{
    cout << "Приоритет (чем больше — тем раньше выполнится): ";
    int p;
    cin >> p;
    if (cin.fail()) { clearInput(); return -1; }
    return p;
}

// ---------- main ----------

int main()
{
    task_queue q;

    cout << "=== Приоритетная очередь задач ===\n";

    int choice = -1;
    while (choice != 0)
    {
        printMenu();
        cin >> choice;
        if (cin.fail())
        {
            clearInput();
            cout << "Некорректный ввод.\n";
            choice = -1;
            continue;
        }

        try
        {
            switch (choice)
            {
                case 1: {
                    cin.ignore();
                    cout << "Текст сообщения: ";
                    string text;
                    getline(cin, text);
                    int p = readPriority();
                    if (p < 0) { cout << "Некорректный приоритет.\n"; break; }
                    q.Push(new print_task(text), p);
                    cout << "print_task добавлена с приоритетом " << p << ".\n";
                    break;
                }
                case 2: {
                    cout << "Первое число: ";
                    int a, b;
                    cin >> a;
                    if (cin.fail()) { clearInput(); cout << "Некорректный ввод.\n"; break; }
                    cout << "Второе число: ";
                    cin >> b;
                    if (cin.fail()) { clearInput(); cout << "Некорректный ввод.\n"; break; }
                    int p = readPriority();
                    if (p < 0) { cout << "Некорректный приоритет.\n"; break; }
                    q.Push(new sum_task(a, b), p);
                    cout << "sum_task(" << a << ", " << b << ") добавлена с приоритетом " << p << ".\n";
                    break;
                }
                case 3: {
                    cout << "Первое число: ";
                    int a, b;
                    cin >> a;
                    if (cin.fail()) { clearInput(); cout << "Некорректный ввод.\n"; break; }
                    cout << "Второе число: ";
                    cin >> b;
                    if (cin.fail()) { clearInput(); cout << "Некорректный ввод.\n"; break; }
                    int p = readPriority();
                    if (p < 0) { cout << "Некорректный приоритет.\n"; break; }
                    q.Push(new multiply_task(a, b), p);
                    cout << "multiply_task(" << a << ", " << b << ") добавлена с приоритетом " << p << ".\n";
                    break;
                }
                case 4: {
                    cout << "Число для отсчёта: ";
                    int n;
                    cin >> n;
                    if (cin.fail()) { clearInput(); cout << "Некорректный ввод.\n"; break; }
                    int p = readPriority();
                    if (p < 0) { cout << "Некорректный приоритет.\n"; break; }
                    q.Push(new countdown_task(n), p);
                    cout << "countdown_task(" << n << ") добавлена с приоритетом " << p << ".\n";
                    break;
                }
                case 5: {
                    if (q.empty()) { cout << "Очередь пуста.\n"; break; }
                    cout << "Выполнение первой задачи:\n";
                    q.executeFirst();
                    break;
                }
                case 6: {
                    if (q.empty()) { cout << "Очередь пуста.\n"; break; }
                    cout << "Выполнение всех задач:\n";
                    q.executeAll();
                    cout << "Все задачи выполнены.\n";
                    break;
                }
                case 7: {
                    cout << (q.empty() ? "Очередь пуста." : "В очереди есть задачи.") << "\n";
                    break;
                }
                case 0:
                    cout << "Выход из программы.\n";
                    break;
                default:
                    cout << "Неверный пункт меню.\n";
            }
        }
        catch (const exception& e)
        {
            cerr << "Ошибка: " << e.what() << "\n";
        }
    }

    return 0;
}
