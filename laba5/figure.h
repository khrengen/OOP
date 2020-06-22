#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <iomanip>
#include <cmath>

template <class A, class B> 
class Pair : public std::pair<A, B> {
    public:
        Pair() : std::pair<A, B>() {
            this->first = 0;
            this->second = 0; 
        }
        Pair(A firstI, B secondI) : std::pair<A, B>() {
            this->first = firstI;
            this->second = secondI; 
        }
        friend std::ostream& operator<< (std::ostream &out, const Pair<A,B> &point) {
            out << std::fixed << std::setprecision(2) << '(' << point.first << ", " << point.second << ')';
            return out;
        }
        friend std::istream& operator>> (std::istream &in, Pair<A,B> &point) {
            in >> point.first;
            in >> point.second;
            return in;
        } 
};

template <class T>
double distance(Pair<T,T> a, Pair<T,T> b) {
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

template <class T>
class Figure {
    public:
        using Point = Pair<int,int>;
        Point points[4]; 
};

template <class T> 
class Square : public Figure<T> {
    public:
        using Point = Pair<int,int>;
        Square(Point a, Point b, Point c, Point d) {
            Figure<T>::points[0] = a;
            Figure<T>::points[1] = b;
            Figure<T>::points[2] = c;
            Figure<T>::points[3] = d;
    
};



template <class T>
void printCoor(Square<T>& sq) {
    std::cout << "A = " << sq.points[0] << "\tB = " << sq.points[1] << "\nC = " << sq.points[2] << "\tD = " << sq.points[3] << '\n';
}

template <class T>
auto centr(Square<T>& sq) {
	Pair<double, double> cnt;
	cnt.first = (sq.points[0].first + sq.points[1].first + sq.points[2].first + sq.points[3].first) / 4;
	cnt.second = (sq.points[0].second + sq.points[1].second + sq.points[2].second + sq.points[3].second) /4;
	return cnt;
}

template <class T>
double area (Square<T>& sq) {
	return distance(sq.points[0], sq.points[1]);
}


#endif