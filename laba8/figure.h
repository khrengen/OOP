#ifndef FIGURE_H
#define FIGURE_H

#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <memory>
#include <cmath>
#include <iomanip>
#include <chrono>
#include <thread>
#include <string.h>

using namespace std::chrono_literals;

enum FigureType {
    TRAPE,
    SQUARE,
    RECTANGLE
};



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

using Point = Pair<double,double>;
template <class T>
double distance(Pair<T,T> a, Pair<T,T> b) {
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}


class IFigure {
public:
    
    virtual std::ostream& Print(std::ostream& out) const = 0;
    virtual int Id() const = 0;
    virtual ~IFigure() = default;
    Point a, b, c, d;
};


class Square : public IFigure {
public:
        Square(): Id_(0), a(0,0), b(0,0), c(0,0), d(0,0)
        {    
        } 

         Square(int id, Point A, Point B, Point C, Point D): 
            Id_(id), a(std::move(A)), b(std::move(B)), c(std::move(C)), d(std::move(D))
        {    
        } 


        int Id() const override {
            return Id_;
        }

        auto centr() {
            Point cnt;
            cnt.first = (a.first + b.first + c.first + d.first) / 4;
            cnt.second = (a.second + b.second + c.second + d.second) /4;
            return cnt;
        }


        double area () {
            return distance(a, b) * distance(b,c);
        }


    std::ostream& Print(std::ostream& out) const override {
        out << "ID: " << Id_ << "\n";
        out << "Figure: Square" << "\n";
        out << "Coors:\n";
        out << "A = " << a << "\tB = " << b 
        << "\nC = " << c << "\tD = " << d << '\n';
        return out;
    }

private:
        int Id_;
        Point a, b, c, d;
};


class Rectangle : public IFigure {
public:
        Rectangle(): Id_(0), a(0,0), b(0,0), c(0,0), d(0,0)
        {    
        } 

        Rectangle(int id, Point A, Point B, Point C, Point D): 
            Id_(id), a(std::move(A)), b(std::move(B)), c(std::move(C)), d(std::move(D))
        {    
        } 

        int Id() const override {
            return Id_;
        }

        auto centr() {
            Point cnt;
            cnt.first = (a.first + b.first + c.first + d.first) / 4;
            cnt.second = (a.second + b.second + c.second + d.second) /4;
            return cnt;
        }


        double area () {
            return distance(a, b) * distance(b,c);
        }


    std::ostream& Print(std::ostream& out) const override {
        out << "ID: " << Id_ << "\n";
        out << "Figure: Rectangle" << "\n";
        out << "Coors:\n";
        out << "A = " << a << "\tB = " << b 
        << "\nC = " << c << "\tD = " << d << '\n';
        return out;
    }


private:
        int Id_;
        Point a, b, c, d;


};

class Trape : public IFigure {
public:
        Trape(): Id_(0), a(0,0), b(0,0), c(0,0), d(0,0)
        {    
        } 

        Trape(int id, Point A, Point B, Point C, Point D): 
            Id_(id), a(std::move(A)), b(std::move(B)), c(std::move(C)), d(std::move(D))
        {    
        } 


        int Id() const override {
            return Id_;
        }

        auto centr() {
            Point cnt;
            cnt.first = (a.first + b.first + c.first + d.first) / 4;
            cnt.second = (a.second + b.second + c.second + d.second) /4;
            return cnt;
        }


        double area () {
            double h = sqrt(pow(distance(a,b), 2) - pow((distance(a,d)-distance(b,c))/2,2));
            return (distance(a, b) + distance(c,d)) / 2 * h;
        }


    std::ostream& Print(std::ostream& out) const override {
        out << "ID: " << Id_ << "\n";
        out << "Figure: Trape" << "\n";
        out << "Coors:\n";
        out << "A = " << a << "\tB = " << b 
        << "\nC = " << c << "\tD = " << d << '\n';
        return out;
    }

private:
        int Id_;
        Point a, b, c, d;
};

bool isSquare(Point a, Point b, Point c, Point d)
{
    if (distance(a, b) == distance(c,d)) {
        if (distance(b,c) == distance(a,d)) {
            if(distance(a,b) == distance(b,c)) {
                if ((int)(pow(distance(a,b),2) + pow(distance(b,c), 2)) == int(pow(distance(a,c),2))) {
                    return true;
                }   
            }
        }
    }
    return false;
}

bool isRectangle(Point a, Point b, Point c, Point d)
{
    if (distance(a, b) == distance(c,d)) {
        if (distance(b,c) == distance(a,d)) {
            return true;
        }
    }
    return false;
}

bool isTrape(Point a, Point b, Point c, Point d)
{
    if (distance(a, b) == distance(c,d)) {
        if (distance(b,c) != distance(a,d)) {
            return true;
        }
    }
    return false;
}

class Subscriber {
    char* out_file;
    
    public:
        Subscriber() = default;
        Subscriber(char* out_file) : out_file(out_file) {
            if (strcmp(out_file, "stdout") != 0) {
                std::ofstream fl (out_file, std::ofstream::out);
                fl.close();
            }
        }

        int Process(std::vector<IFigure*>& figs, int size) {
            
            if (strcmp(out_file, "stdout") != 0) {
                std::ofstream fl (out_file, std::ofstream::app);

                for (int i = 0; i < size; i++) {
                    figs[i]->Print(fl);

                }
                
                fl.close();

            } else {
                for (int i = 0; i < size; i++) {
                    figs[i]->Print(std::cout);
                }
            }
            
            return true;
        }
};

class Publisher {
    int size;
    int max_size;
    std::vector<IFigure*>& figs;
    std::vector<Subscriber> subs;

    public:
        Publisher(std::vector<IFigure*>& figs, int max_size):
            size(0), max_size(max_size), figs(figs), subs() {}

        int Add(IFigure* fig) {
            figs.push_back(fig);
            size++;
            if (size == max_size) {
                for (Subscriber& sub : subs) {
                    sub.Process(figs, max_size);
                }
                this->size = 0;
                std::this_thread::sleep_for(1000ms);
                for (int i = figs.size() - 1; i >= 0; i--) {
                    delete figs[i];
                    figs.erase(figs.begin() + i);
                }
                return 1;
            }
            return 0;
        }

        void Subscribe(Subscriber& sub) {
            subs.push_back(sub);
        } 

        
};

#endif