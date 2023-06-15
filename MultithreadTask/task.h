#ifndef TASK_H
#define TASK_H

#include <tuple>
#include <memory>
#include <functional>

class AbstractTask
{
public:
    virtual void execute() = 0;
    virtual ~AbstractTask() {}
};

template<typename Fn, typename ... Args>
class Task : public AbstractTask
{

    using removedPointerFn = std::remove_pointer_t<Fn> ;
    using _tup = std::tuple<std::decay_t<removedPointerFn>, std::decay_t<Args>...>;
public:
    explicit Task(Fn func, Args ...args): tup{ std::make_unique<_tup >(std::forward<removedPointerFn>(func), std::forward<Args>(args)...) }
    {}
    ~Task() {}
    void execute() override
    {
        getExecute(std::make_index_sequence<1 + sizeof...(Args)>{});
    }
private:
    template<std::size_t ...Indices>
    void getExecute(std::index_sequence<Indices...>)
    {
        _tup& refTup = *tup.get();
        std::invoke(std::move(std::get<Indices>(refTup))...);
    }
private:
    std::unique_ptr<_tup> tup;
};
#endif
