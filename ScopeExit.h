#pragma once

namespace PortableRuntime
{

namespace Detail
{

template<typename Lambda>
class Scope_exit
{
    Lambda m_lambda;
    bool m_execute_lambda{true};

    Scope_exit(const Scope_exit&) = delete;
    Scope_exit& operator=(const Scope_exit&) = delete;
    Scope_exit& operator=(Scope_exit&&) noexcept = delete;

public:
    explicit Scope_exit(Lambda&& lambda) noexcept :
        m_lambda(std::move(lambda))
    {
    }

    Scope_exit(Scope_exit&& Scope_exit) noexcept :
        m_lambda(std::move(Scope_exit.m_lambda)),
        m_execute_lambda(true)
    {
        Scope_exit.m_execute_lambda = false;
    }

    ~Scope_exit() noexcept
    {
        operator()();
    }

    void operator()() noexcept
    {
        if(m_execute_lambda)
        {
            m_lambda();
            m_execute_lambda = false;
        }
    }

    void release() noexcept
    {
        m_execute_lambda = false;
    }
};

}

// This exists to allow the template argument to be deduced automatically when used.
template<typename Lambda>
Detail::Scope_exit<Lambda> Scope_exit(Lambda&& lambda)
{
    return Detail::Scope_exit<Lambda>(std::move(lambda));
}

}

