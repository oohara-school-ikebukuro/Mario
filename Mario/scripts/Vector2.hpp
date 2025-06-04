#pragma once

#include <type_traits>
#include <cmath>

template<typename T>
struct Vector2
{
    // 数値のみ許可する設計
    static_assert(std::is_arithmetic<T>::value, "Vector2<T> は数値型のみ許可");

    T x, y;

    Vector2() : x(T{}), y(T{}) {}
    Vector2(T x,T y) : x(x), y(y) {
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
        return { static_cast<T>(x * other), static_cast<T>(y * other)};
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

    template<typename T1>
    T dot(const Vector2<T1>& other) const {
        return x * other.x + y * other.y; 
    }

    // ベクトルの長さを取得
    T length() const {
        return std::sqrt(x * x + y * y);
    }

    // 正規化処理
    Vector2 normalize() const {
        T len = length();
        if (len > static_cast<T>(0)) {
            return Vector2(x / len, y / len);
        }
        return Vector2(0, 0); // ゼロベクトルの場合はそのまま返す
    }
};