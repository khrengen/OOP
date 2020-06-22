//Хренов Геннадий
// класс квадрат

#include <iostream>
#include <iomanip>
#include <cmath>

template <class A, class B> 
class myPair : public std::pair<A, B> {
    public:
        myPair() : std::pair<A, B>() {
            this->first = 0;
            this->second = 0; 
        }
        myPair(A firstI, B secondI) : std::pair<A, B>() {
            this->first = firstI;
            this->second = secondI; 
        }
        friend std::ostream& operator<< (std::ostream &out, const myPair<A,B> &point) {
            out << std::fixed << std::setprecision(2) << '(' << point.first << ", " << point.second << ')';
            return out;
        }
        friend std::istream& operator>> (std::istream &in, myPair<A,B> &point) {
            in >> point.first;
            in >> point.second;
            return in;
        } 
};

template <class T>
double distance(myPair<T,T> a, myPair<T,T> b) {
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

template <class T>
class Figure {
    public:
        using Point = myPair<T,T>;
        Point points[4]; 
};


template <class T>
class Square : public Figure<T> {
    public:
        using Point = myPair<T,T>;
        Square(Point a, Point b, Point c, Point d) {
            Figure<T>::points[0] = a;
            Figure<T>::points[1] = b;
            Figure<T>::points[2] = c;
            Figure<T>::points[3] = d;
        }
    
};



template <class T>
void printCoor(Figure<T>& sq) {
    std::cout << "A = " << sq.points[0] << "\tB = " << sq.points[1] << "\nC = " << sq.points[2] << "\tD = " << sq.points[3] << '\n';
}

template <class T>
auto centr(Figure<T>& sq) {
	myPair<double, double> cnt;
	cnt.first = (sq.points[0].first + sq.points[1].first + sq.points[2].first + sq.points[3].first) / 4;
	cnt.second = (sq.points[0].second + sq.points[1].second + sq.points[2].second + sq.points[3].second) /4;
	return cnt;
}

template <class T>
double area (Figure<T>& sq) {
	return pow(distance(sq.points[0], sq.points[1]),2);
}
