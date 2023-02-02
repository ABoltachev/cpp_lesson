#ifndef TEMPLATES_TUPLE_HPP
#define TEMPLATES_TUPLE_HPP

#include <tuple>
#include <stdexcept>

template <typename... Args>
class Tuple;

template <typename Head, typename... Tail>
class Tuple<Head, Tail...> : public Tuple<Tail...> {
public:
    using base_type=Tuple<Tail...>;
    using value_type=Head;
public:
    value_type m_head;
    base_type& base = static_cast<base_type&>(*this);
public:
    Tuple(Head head, Tail... tail) : base_type(tail...), m_head(head) {}

    const value_type& head() const { return m_head; }
};

template <>
class Tuple<>{};

template <size_t Ind, typename... Args>
struct getter;

template <size_t Ind, typename Head, typename... Tail>
struct getter<Ind, Head, Tail...> {
    using return_type=typename getter<Ind - 1, Tail...>::return_type;
    static return_type get(Tuple<Head, Tail...> tuple) {
        return getter<Ind - 1, Tail...>::get(tuple);
    }
};

template <typename Head, typename... Tail>
struct getter<0, Head, Tail...> {
    using return_type=typename Tuple<Head, Tail...>::value_type;
    static return_type get(Tuple<Head, Tail...> tuple) {
        return tuple.head();
    }
};

template <size_t Ind>
struct getter<Ind> {
    using return_type=int;
    static return_type get(Tuple<> tuple) {
        throw std::out_of_range("Index out of range tuple");
    }
};

template <size_t Ind, typename Head, typename... Tail>
using return_type=typename getter<Ind, Head, Tail...>::return_type;

template <size_t Ind, typename Head, typename... Tail>
return_type<Ind, Head, Tail...> get(Tuple<Head, Tail...> tuple) {
    return getter<Ind, Head, Tail...>::get(tuple);
}

template <typename Callable, typename TupleType, bool Enough, size_t TotalArgs, size_t... Ind>
struct call_impl {
    auto static call(Callable func, TupleType &&tuple) {
        return call_impl<Callable, TupleType, TotalArgs == 1 + sizeof...(Ind),
                            TotalArgs, Ind..., sizeof...(Ind)
                        >::call(func, std::forward<TupleType>(tuple));
    }
};

template <typename Callable, typename TupleType, size_t TotalArgs, size_t... Ind>
struct call_impl<Callable, TupleType, true, TotalArgs, Ind...> {
    auto static call(Callable func, TupleType &&tuple) {
        return func(get<Ind>(std::forward<TupleType>(tuple))...);
    }
};

template <typename Callable, typename TupleType>
auto call(Callable func, TupleType &&tuple) {
    using type=typename std::decay<TupleType>::type;
    return call_impl<Callable, TupleType, 0 == std::tuple_size<type>::value, std::tuple_size<type>::value
                    >::call(func, std::forward<TupleType>(tuple));
}

#endif // TEMPLATES_TUPLE_HPP
