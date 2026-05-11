#pragma once

#include <iostream>

class task
{
public:
    virtual ~task() = default;

    virtual void execute() = 0;

protected:
    virtual void print(std::ostream& stream) const = 0;

    friend std::ostream&
    operator<<(std::ostream& stream,
               const task& t);
};
