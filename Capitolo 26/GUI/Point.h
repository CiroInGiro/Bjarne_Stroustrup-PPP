
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#ifndef POINT_GUARD
#define POINT_GUARD 1

#include <iostream>

//------------------------------------------------------------------------------

struct Point {
    int x, y;
    Point(int xx, int yy) : x(xx), y(yy) { }
    Point() :x(0), y(0) { }
    friend std::ostream& operator<<(std::ostream& os, Point& point) {
        os << "Point{" << point.x << "," << point.y << "}";
        
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Point& point) {
        char ch{ '\0' };
        std::string comando{ "" };

        while (is >> ch && ch != '{') comando += ch;

        if (comando != "Point") return is;

        is >> point.x;

        if (is >> ch && ch != ',') return is;

        is >> point.y;

        if (is >> ch && ch != '}') return is;

        return is;
    }
};

//------------------------------------------------------------------------------

inline bool operator==(Point a, Point b) { return a.x==b.x && a.y==b.y; } 

//------------------------------------------------------------------------------

inline bool operator!=(Point a, Point b) { return !(a==b); }

//------------------------------------------------------------------------------

// used to sort points by x-value in Striped_closed_polyline
inline bool operator<(Point a, Point b) { return a.x < b.x; }

//------------------------------------------------------------------------------

// used to sort points by x-value in Striped_closed_polyline
inline bool operator>(Point a, Point b) { return a.x > b.x; }

//------------------------------------------------------------------------------

#endif // POINT_GUARD

