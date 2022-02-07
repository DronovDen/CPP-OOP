#pragma once
#include <string>
#include <sstream>
#include <typeinfo>

#include "Exceptions.h"

//Converting string (that was get from vector) to definite type
template <typename T>
T toType(std::string str)
{
    if constexpr (std::is_same_v<T, std::string>)
    {
        return str;
    }
    T value;
    if (!(std::stringstream(str) >> value))
    { //strigstream is able to convert string to int
        throw my_exception("Wrong field type");
    }
    return value;
};

// Converting vector of strings to tuple
template <size_t N, typename T>
struct ToTuple
{
    static void convert(T &t, std::vector<std::string> &stringsVect)
    {
        using elemT = typename std::tuple_element<N - 1, T>::type; //type of definite element in tuple
        std::get<N - 1>(t) = toType<elemT>(stringsVect[N - 1]);    //get(t) returns reference to selected element in tuple
        ToTuple<N - 1, T>::convert(t, stringsVect);
    }
};

template <typename T>
struct ToTuple<0, T>
{
    static void convert(T &, std::vector<std::string> &) {}
};

template <typename... Args>
std::tuple<Args...> toTuple(std::vector<std::string> &stringsVect)
{
    std::tuple<Args...> tuple;
    ToTuple<sizeof...(Args), std::tuple<Args...>>::convert(tuple, stringsVect);
    return tuple;
}

// Overloading the output operator for tuple
template <size_t N, typename T>
struct PrintTuple
{
    static void print(std::ostream &out, const T &tuple)
    {
        PrintTuple<N - 1, T>::print(out, tuple);
        out << (N == 1 ? "" : ", ") << std::get<N - 1>(tuple);
    }
};

template <typename T>
struct PrintTuple<0, T>
{
    static void print(std::ostream &os, const T &tuple) {}
};

template <typename... Args>
std::ostream &operator<<(std::ostream &out, const std::tuple<Args...> &tuple)
{
    out << "[";
    PrintTuple<sizeof...(Args), std::tuple<Args...>>::print(out, tuple); //sizeof... (Args) mean args number (5)
    out << "]";
    return out;
};
