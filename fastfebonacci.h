#ifndef FASTFEBONACCI_H
#define FASTFEBONACCI_H

namespace Algo {

    template <int T>
    class FastFebonacci
    {
    public:
        enum
        {
            value = (int)FastFebonacci<T-1>::value + (int)FastFebonacci<T-2>::value
        };
    };

    template <>
    class FastFebonacci<1>
    {
    public:
        enum
        {
            value = 1
        };
    };

    template <>
    class FastFebonacci<0>
    {
    public:
        enum
        {
            value = 0
        };
    };
}

#endif // FASTFEBONACCI_H

