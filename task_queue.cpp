#include "task_queue.h"

#include <iostream>
#include <stdexcept>

using namespace std;


ostream& operator<<(ostream& stream,
                    const task& t)
{
    t.print(stream);

    return stream;
}


task_queue::task_queue()
    : sz(0) {}

task_queue::~task_queue()
{
    while (sz > 0)
    {
        delete arr[0].ptr;

        arr[0] = arr[sz - 1];

        --sz;

        heapifyDown(0);
    }
}

bool task_queue::empty() const
{
    return sz == 0;
}

bool task_queue::full() const
{
    return sz == MAX_SIZE;
}

void task_queue::heapifyUp(int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;

        if (arr[parent].priority >=
            arr[index].priority)
        {
            break;
        }

        swap(arr[parent],
             arr[index]);

        index = parent;
    }
}

void task_queue::heapifyDown(int index)
{
    while (true)
    {
        int left = 2 * index + 1;

        int right = 2 * index + 2;

        int largest = index;

        if (left < sz &&
            arr[left].priority >
            arr[largest].priority)
        {
            largest = left;
        }

        if (right < sz &&
            arr[right].priority >
            arr[largest].priority)
        {
            largest = right;
        }

        if (largest == index)
        {
            break;
        }

        swap(arr[index],
             arr[largest]);

        index = largest;
    }
}

void task_queue::Push(task* ptr,
                      int priority)
{
    if (full())
    {
        throw runtime_error(
            "Push: queue is full");
    }

    arr[sz].ptr = ptr;

    arr[sz].priority = priority;

    heapifyUp(sz);

    ++sz;
}

task* task_queue::Pop()
{
    if (empty())
    {
        throw runtime_error(
            "Pop: queue is empty");
    }

    task* result = arr[0].ptr;

    arr[0] = arr[sz - 1];

    --sz;

    heapifyDown(0);

    return result;
}

void task_queue::executeFirst()
{
    task* ptr = Pop();

    cout << "Execute: "
         << *ptr << '\n';

    ptr->execute();

    delete ptr;
}

void task_queue::executeAll()
{
    while (!empty())
    {
        executeFirst();
    }
}
