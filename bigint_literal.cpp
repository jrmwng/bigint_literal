// bigint_literal.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "bigint_literal.h"

#include <iostream>
#include <tuple>
#include <cstdint>
#include <algorithm>
#include <functional>

template <typename Tbigint, typename Tvalue>
constexpr bool bigint_literal_test(Tbigint tBigInt, Tvalue tValue)
{
    return Tvalue(tBigInt) == tValue;
}
template <typename Tbigint, typename... Tvalue, size_t... zuINDEX>
constexpr bool bigint_literal_test(Tbigint tBigInt, std::tuple<Tvalue...> const& tupleValue, std::index_sequence<zuINDEX...>)
{
    bool const abTest[]
    {
        bigint_literal_test(tBigInt, std::get<zuINDEX>(tupleValue))...
    };
    bool bResult = true;
    {
        for (bool bTest : abTest)
        {
            bResult &= bTest;
        }
    }
    return bResult;
}
template <typename Tbigint, typename... Tvalue>
constexpr bool bigint_literal_test(Tbigint tBigInt, std::tuple<Tvalue...> const& tupleValue)
{
    return bigint_literal_test(tBigInt, tupleValue, std::index_sequence_for<Tvalue...>());
}
template <typename... Tbigint, size_t... zuINDEX, typename... Tvalue>
constexpr bool bigint_literal_test(std::tuple<Tbigint...> const& tupleBigInt, std::index_sequence<zuINDEX...>, std::tuple<Tvalue...> const& tupleValue)
{
    bool const abTest[]
    {
        bigint_literal_test(std::get<zuINDEX>(tupleBigInt), tupleValue)...
    };
    bool bResult = true;
    {
        for (bool bTest : abTest)
        {
            bResult &= bTest;
        }
    }
    return bResult;
}
template <typename... Tbigint, typename... Tvalue>
constexpr bool bigint_literal_test(std::tuple<Tbigint...> const& tupleBigInt, std::tuple<Tvalue...> const& tupleValue)
{
    return bigint_literal_test(tupleBigInt, std::index_sequence_for<Tbigint...>(), tupleValue);
}

int main()
{
    static_assert(bigint_literal_test(std::make_tuple(0x0_bigint, 0X0_bigint, 0b0_bigint, 0B0_bigint, 0_bigint), std::tuple<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t>(0, 0, 0, 0, 0, 0, 0, 0)), "ha");
    static_assert(bigint_literal_test(std::make_tuple(0x1_bigint, 0X1_bigint, 0b1_bigint, 0B1_bigint, 01_bigint, 1_bigint), std::tuple<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t>(1, 1, 1, 1, 1, 1, 1, 1)), "ha");
    static_assert(bigint_literal_test(std::make_tuple(0x2_bigint, 0X2_bigint, 0b10_bigint, 0B10_bigint, 02_bigint, 2_bigint), std::tuple<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t>(2, 2, 2, 2, 2, 2, 2, 2)), "ha");
    static_assert(bigint_literal_test(std::make_tuple(0x3_bigint, 0X3_bigint, 0b11_bigint, 0B11_bigint, 03_bigint, 3_bigint), std::tuple<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t>(3, 3, 3, 3, 3, 3, 3, 3)), "ha");
    static_assert(bigint_literal_test(std::make_tuple(0x7_bigint, 0X7_bigint, 0b111_bigint, 0B111_bigint, 07_bigint, 7_bigint), std::tuple<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t>(7, 7, 7, 7, 7, 7, 7, 7)), "ha");
    static_assert(bigint_literal_test(std::make_tuple(0x8_bigint, 0X8_bigint, 0b1000_bigint, 0B1000_bigint, 010_bigint, 8_bigint), std::tuple<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t>(8, 8, 8, 8, 8, 8, 8, 8)), "ha");
    static_assert(bigint_literal_test(std::make_tuple(0x9_bigint, 0X9_bigint, 0b1001_bigint, 0B1001_bigint, 011_bigint, 9_bigint), std::tuple<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t>(9, 9, 9, 9, 9, 9, 9, 9)), "ha");
    static_assert(bigint_literal_test(std::make_tuple(0xF_bigint, 0XF_bigint, 0b1111_bigint, 0B1111_bigint, 017_bigint, 15_bigint), std::tuple<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t>(15, 15, 15, 15, 15, 15, 15, 15)), "ha");
    static_assert(bigint_literal_test(std::make_tuple(0x10_bigint, 0X10_bigint, 0b10000_bigint, 0B10000_bigint, 020_bigint, 16_bigint), std::tuple<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t>(16, 16, 16, 16, 16, 16, 16, 16)), "ha");
    static_assert(bigint_literal_test(std::make_tuple(0x7F_bigint, 0X7F_bigint, 0b1111111_bigint, 0B1111111_bigint, 0177_bigint, 127_bigint), std::tuple<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t>(127, 127, 127, 127, 127, 127, 127, 127)), "ha");
    static_assert(bigint_literal_test(std::make_tuple(0x80_bigint, 0X80_bigint, 0b10000000_bigint, 0B10000000_bigint, 0200_bigint, 128_bigint), std::tuple<uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t>(128, 128, 128, 128, 128, 128, 128)), "ha");
    static_assert(bigint_literal_test(std::make_tuple(0x7FFF_bigint, 0X7FFF_bigint, 0b111111111111111_bigint, 0B111111111111111_bigint, 077777_bigint, 32767_bigint), std::tuple<int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t>(32767, 32767, 32767, 32767, 32767, 32767)), "ha");
    static_assert(bigint_literal_test(std::make_tuple(0x8000_bigint, 0X8000_bigint, 0b1000000000000000_bigint, 0B1000000000000000_bigint, 0100000_bigint, 32768_bigint), std::tuple<uint16_t, int32_t, uint32_t, int64_t, uint64_t>(32768, 32768, 32768, 32768, 32768)), "ha");
    static_assert(bigint_literal_test(std::make_tuple(-0x1_bigint, -0X1_bigint, -0b1_bigint, -0B1_bigint, -01_bigint, -1_bigint), std::tuple<int8_t, int16_t, int32_t, int64_t>(-1, -1, -1, -1)), "ha");
    static_assert(bigint_literal_test(std::make_tuple(-0x7F_bigint, -0X7F_bigint, -0b1111111_bigint, -0B1111111_bigint, -0177_bigint, -127_bigint), std::tuple<int8_t, int16_t, int32_t, int64_t>(-127, -127,  -127,  -127)), "ha");
    static_assert(bigint_literal_test(std::make_tuple(-0x80_bigint, -0X80_bigint, -0b10000000_bigint, -0B10000000_bigint, -0200_bigint, -128_bigint), std::tuple<int8_t, int16_t, int32_t, int64_t>(-128, -128, -128, -128)), "ha");

    static_assert(           __int128 ( 0x7FFFFFFFFFFFFFFF_bigint                )         ==          (0x7FFFFFFFFFFFFFFF), "ha");
    static_assert((          __int128 ( 0x7FFFFFFFFFFFFFFF0000000000000000_bigint) >>  64) ==          ( 0x7FFFFFFFFFFFFFFF), "ha");
    static_assert(((unsigned __int128)( 0x7FFFFFFFFFFFFFFF0000000000000000_bigint) >>  64) ==          ( 0x7FFFFFFFFFFFFFFF), "ha");
    static_assert((          __int128 (-0x7FFFFFFFFFFFFFFF0000000000000000_bigint) >>  64) ==          (-0x7FFFFFFFFFFFFFFF), "ha");
    static_assert(((unsigned __int128)( 0x40000000000000000000000000000000_bigint) >> 126) ==                            (1), "ha");
    static_assert((          __int128 (-0x80000000000000000000000000000000_bigint) >> 127) ==                           (-1), "ha");
    static_assert((          __int128 (-0x80000000000000000000000000000000_bigint) >>  64) !=          (-0x8000000000000000), "ha");
    static_assert(((unsigned __int128)( 0x80000000000000000000000000000000_bigint) >>  64) ==          ( 0x8000000000000000), "ha");
    static_assert((          __int128 (-0x80000000000000000000000000000000_bigint)       ) == (__int128(-0x8000000000000000) << 64), "ha");
    static_assert(((unsigned __int128)( 0xFFFFFFFFFFFFFFFF0000000000000000_bigint) >>  64) ==          ( 0xFFFFFFFFFFFFFFFF), "ha");

    static_assert((int)15._bigint == 15, "ha");

    std::cout << "Hello World!\n";
}
