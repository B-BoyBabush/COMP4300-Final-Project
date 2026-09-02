class Vec2
{
public:
    float x{};
    float y{};
    
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
};