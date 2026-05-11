#include <iostream>
#include <string>

#include "task_queue.h"

using namespace std;


class print_task : public task
{
public:
    print_task(const string& text_)
        : text(text_) {}

    void execute() override
    {
        cout << "Message: "
             << text << "\n\n";
    }

protected:
    void print(ostream& stream) const override
    {
        stream << "print_task";
    }

private:
    string text;
};


class sum_task : public task
{
public:
    sum_task(int a_,
             int b_)
        : a(a_), b(b_) {}

    void execute() override
    {
        cout << a << " + "
             << b << " = "
             << a + b << "\n\n";
    }

protected:
    void print(ostream& stream) const override
    {
        stream << "sum_task";
    }

private:
    int a;
    int b;
};


class multiply_task : public task
{
public:
    multiply_task(int a_,
                  int b_)
        : a(a_), b(b_) {}

    void execute() override
    {
        cout << a << " * "
             << b << " = "
             << a * b << "\n\n";
    }

protected:
    void print(ostream& stream) const override
    {
        stream << "multiply_task";
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
        for (int i = n;
             i >= 0;
             --i)
        {
            cout << i << ' ';
        }

        cout << "\n\n";
    }

protected:
    void print(ostream& stream) const override
    {
        stream << "countdown_task";
    }

private:
    int n;
};


int main()
{
    task_queue q;

    try
    {
        q.Push(
            new print_task("Hello"),
            1
        );

        q.Push(
            new sum_task(5, 7),
            5
        );

        q.Push(
            new multiply_task(4, 6),
            3
        );

        q.Push(
            new countdown_task(5),
            10
        );

        cout << "Execute first:\n\n";

        q.executeFirst();

        cout << "Execute all:\n\n";

        q.executeAll();
    }

    catch (const exception& e)
    {
        cerr << "Error: "
             << e.what() << '\n';
    }

    return 0;
}
