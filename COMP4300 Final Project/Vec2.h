#pragma once
#include <SFML/System.hpp>

class Vec2
{
public:
    float x{ 0.0f };
    float y{ 0.0f };

    Vec2() {}
    Vec2(float inx, float iny)
        : x{ inx }
        , y{ iny }
    { }

    Vec2(int inx, int iny)
        : x{ static_cast<float>(inx) }
        , y{ static_cast<float>(iny) }
    { }

    Vec2(sf::Vector2f in)
        : x{ in.x }
        , y{ in.y }
    { }

    Vec2(sf::Vector2u in)
        : x{ static_cast<float>(in.x) }
        , y{ static_cast<float>(in.y) }
    { }
    
    Vec2 operator+(Vec2 rhs){ return Vec2{ x + rhs.x, y + rhs.y }; }
    
    Vec2 operator-(Vec2 rhs){ return Vec2{ x - rhs.x, y - rhs.y }; }
    
    Vec2 operator*(Vec2 rhs){ return Vec2{ x * rhs.x, y * rhs.y }; }
    
    Vec2 operator/(Vec2 rhs)
    {
        if (rhs.x == 0.0f || rhs.y == 0.0f)
            return Vec2{ 0.0f, 0.0f };
        
        return Vec2{ x / rhs.x, y / rhs.y };
    }

    Vec2 operator+(float rhs){ return Vec2{ x + rhs, y + rhs }; }

    Vec2 operator-(float rhs){ return Vec2{ x - rhs, y - rhs }; }

    Vec2 operator*(float rhs){ return Vec2{ x * rhs, y * rhs }; }

    Vec2 operator/(float rhs)
    {
        if (rhs == 0.0f)
            return Vec2{ 0.0f, 0.0f };

        return Vec2{ x / rhs, y / rhs };
    }
    
    Vec2& operator+=(Vec2 rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    
    Vec2& operator-=(Vec2 rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    
    Vec2& operator*=(Vec2 rhs)
    {
        x *= rhs.x;
        y *= rhs.y;
        return *this;
    }
    
    Vec2& operator/=(Vec2 rhs)
    {
        if (rhs.x == 0.0f || rhs.y == 0.0f)
            return *this;
            
        x /= rhs.x;
        y /= rhs.y;
        return *this;
    }

    Vec2& operator+=(float rhs)
    {
        x += rhs;
        y += rhs;
        return *this;
    }

    Vec2& operator-=(float rhs)
    {
        x -= rhs;
        y -= rhs;
        return *this;
    }

    Vec2& operator*=(float rhs)
    {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    Vec2& operator/=(float rhs)
    {
        if (rhs == 0.0f)
            return *this;

        x /= rhs;
        y /= rhs;
        return *this;
    }

    bool operator==(Vec2 rhs)
    {
        if (x == rhs.x && y == rhs.y)
            return true;
        return false;
    }

    bool operator!=(Vec2 rhs)
    {
        if (x != rhs.x || y != rhs.y)
            return true;
        return false;
    }

    bool operator>(Vec2 rhs)
    {
        if (x > rhs.x && y > rhs.y)
            return true;
        return false;
    }

    bool operator<(Vec2 rhs)
    {
        if (x < rhs.x && y < rhs.y)
            return true;
        return false;
    }

    bool operator>=(Vec2 rhs)
    {
        if (x >= rhs.x && y >= rhs.y)
            return true;
        return false;
    }

    bool operator<=(Vec2 rhs)
    {
        if (x <= rhs.x && y <= rhs.y)
            return true;
        return false;
    }

    operator sf::Vector2f() const
    { return sf::Vector2f{ x, y }; }
};