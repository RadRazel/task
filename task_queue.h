#pragma once

#include "task.h"

class task_queue
{
private:
    static const int MAX_SIZE = 100;

    struct node
    {
        task* ptr;
        int priority;
    };

    node arr[MAX_SIZE];

    int sz;

    void heapifyUp(int index);

    void heapifyDown(int index);

public:
    task_queue();

    ~task_queue();

    bool empty() const;

    bool full() const;

    void Push(task* ptr,
              int priority);

    task* Pop();

    void executeFirst();

    void executeAll();
};
