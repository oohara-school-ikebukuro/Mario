#pragma once

#include <type_traits>

template<typename T>
struct Vector2
{
    // 数値のみ許可する設計
    static_assert(std::is_arithmetic<T>::value, "Vector2<T> は数値型のみ許可");

    T x, y;

    Vector2() : x(T{}), y(T{}) {}
    Vector2(T x, T y) : x(x), y(y) {
        static_assert(std::is_arithmetic<T>::value, "Vector2<T> は数値型のみ許可");
    }

    T getX()const { return x; }
    T getY()const { return y; }

    // + 
    template<typename T1>
    Vector2<T> operator+(const Vector2<T1>& other) const
    {
        static_assert(std::is_arithmetic<T1>::value, "Vector2<T> は数値型のみ許可");
        return { x + other.x , y + other.y };
    }

    template<typename T1>
    void operator+=(const Vector2<T1>& other)
    {
        static_assert(std::is_arithmetic<T1>::value, "Vector2<T> は数値型のみ許可");
        x += other.x;
        y += other.y;
    }

    // - 
    template<typename T1>
    Vector2<T> operator-(const Vector2<T1>& other) const
    {
        static_assert(std::is_arithmetic<T1>::value, "Vector2<T> は数値型のみ許可");
        return { x - other.x , y - other.y };
    }

    template<typename T1>
    void operator-=(const Vector2<T1>& other)
    {
        static_assert(std::is_arithmetic<T1>::value, "Vector2<T> は数値型のみ許可");
        x -= other.x;
        y -= other.y;
    }

    // * 
    template<typename T1>
    Vector2<T> operator*(const T1& other) const
    {
        static_assert(std::is_arithmetic<T1>::value, "Vector2<T> は数値型のみ許可");
        return { static_cast<T>(x * other), static_cast<T>(y * other) };
    }

    // =
    template<typename T1>
    Vector2<T>& operator=(const Vector2<T1>& other)
    {
        static_assert(std::is_arithmetic<T1>::value, "Vector2<T> は数値型のみ許可");
        x = other.x;
        y = other.y;
        return *this;
    }

    // ==
    template<typename T1>
    bool operator==(const Vector2<T1>& other) const
    {
        static_assert(std::is_arithmetic<T1>::value, "Vector2<T> は数値型のみ許可");
        return x == other.x && y == other.y;
    }

    // 内積（dot product）計算関数
    template<typename T1>
    T1 dot(const Vector2<T1>& other) const {
        static_assert(std::is_arithmetic<T1>::value, "Vector2<T> は数値型のみ許可");

        return x * other.x + y * other.y;
    }

    // 反射ベクトルの計算
    template<typename T1>
    Vector2<T1> reflect(const Vector2<T1>& normal) const {

        static_assert(std::is_arithmetic<T1>::value, "Vector2<T> は数値型のみ許可");

        float dotProduct = this->dot(normal);
        return Vector2(x - 2.0f * dotProduct * normal.x, y - 2.0f * dotProduct * normal.y);
    }

};