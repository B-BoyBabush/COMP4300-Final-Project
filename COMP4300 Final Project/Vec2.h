class Vec2
{
public:
    float x{};
    float y{};
    
    Vec2 operator+(Vec2 rhs)
    {
        return Vec2{ x + rhs.x, y + rhs.y };
    }
    
    Vec2 operator-(Vec2 rhs)
    {
        return Vec2{ x - rhs.x, y - rhs.y };
    }
    
    Vec2 operator*(Vec2 rhs)
    {
        return Vec2{ x * rhs.x, y * rhs.y };
    }
    
    Vec2 operator/(Vec2 rhs)
    {
        if (rhs.x == 0.0f || rhs.y == 0.0f)
            return Vec2{ 0.0f, 0.0f };
        
        return Vec2{ x / rhs.x, y / rhs.y };
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
};