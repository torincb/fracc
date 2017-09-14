#ifndef COMPUTE_H_INC
#define COMPUTE_H_INC

#include <functional>


template <class R, class... Args>
class ComputeCacher
{
public:
    Cacher(std::function<R(Args...)>) : func(func) {}

private:
    std::function<R(Args...)> func;
};


#endif