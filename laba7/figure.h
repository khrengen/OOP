#ifndef FIGURE_H
#define FIGURE_H

#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <memory>
#include <cmath>
#include <iomanip>



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

template <class T>
double distance(Pair<T,T> a, Pair<T,T> b) {
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}


class IFigure {
public:
    
    virtual std::ostream& Print(std::ostream& out) const = 0;
    virtual void Serialize(std::ofstream& os) const = 0;
    virtual void Deserialize(std::ifstream& is) = 0;
    virtual int Id() const = 0;
    virtual ~IFigure() = default;
};

using Point = Pair<double,double>;
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



    void Serialize(std::ofstream& os) const override {
        FigureType type = SQUARE;
        os.write(reinterpret_cast<char*>(&type), sizeof(type));
        os.write((char*)(&Id_), sizeof(Id_));
        os.write((char*)(&a), sizeof(a));
        os.write((char*)(&b), sizeof(b));
        os.write((char*)(&c), sizeof(c));
        os.write((char*)(&d), sizeof(d));
    }

    void Deserialize(std::ifstream& is) override {
        is.read((char*)(&Id_), sizeof(Id_));
        is.read((char*)(&a), sizeof(a));
        is.read((char*)(&b), sizeof(b));
        is.read((char*)(&c), sizeof(c));
        is.read((char*)(&d), sizeof(d));
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



    void Serialize(std::ofstream& os) const override {
        FigureType type = RECTANGLE;
        os.write(reinterpret_cast<char*>(&type), sizeof(type));
        os.write((char*)(&Id_), sizeof(Id_));
        os.write((char*)(&a), sizeof(a));
        os.write((char*)(&b), sizeof(b));
        os.write((char*)(&c), sizeof(c));
        os.write((char*)(&d), sizeof(d));
    }

    void Deserialize(std::ifstream& is) override {
        is.read((char*)(&Id_), sizeof(Id_));
        is.read((char*)(&a), sizeof(a));
        is.read((char*)(&b), sizeof(b));
        is.read((char*)(&c), sizeof(c));
        is.read((char*)(&d), sizeof(d));
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



    void Serialize(std::ofstream& os) const override {
        FigureType type = TRAPE;
        os.write(reinterpret_cast<char*>(&type), sizeof(type));
        os.write((char*)(&Id_), sizeof(Id_));
        os.write((char*)(&a), sizeof(a));
        os.write((char*)(&b), sizeof(b));
        os.write((char*)(&c), sizeof(c));
        os.write((char*)(&d), sizeof(d));
    }

    void Deserialize(std::ifstream& is) override {
        is.read((char*)(&Id_), sizeof(Id_));
        is.read((char*)(&a), sizeof(a));
        is.read((char*)(&b), sizeof(b));
        is.read((char*)(&c), sizeof(c));
        is.read((char*)(&d), sizeof(d));
    }

private:
        int Id_;
        Point a, b, c, d;



};

class IFactory {
public:
    virtual std::shared_ptr<IFigure> FigureCreate(int id, Point a, Point b, Point c, Point d) const = 0;
    virtual std::shared_ptr<IFigure> FigureCreate() const = 0;
};

class SquareFactory : public IFactory {
public:
    std::shared_ptr<IFigure> FigureCreate(int id, Point a, Point b, Point c, Point d) const override {
        return std::shared_ptr<IFigure>(new Square(id, a, b, c, d));
    }

    std::shared_ptr<IFigure> FigureCreate() const override {
        return std::shared_ptr<IFigure>(new Square());
    }
};

class RectangleFactory : public IFactory {
public:
    std::shared_ptr<IFigure> FigureCreate(int id, Point a, Point b, Point c, Point d) const override {
        return std::shared_ptr<IFigure>(new Rectangle(id, a, b, c, d));
    }

    std::shared_ptr<IFigure> FigureCreate() const override {
        return std::shared_ptr<IFigure>(new Rectangle());
    }
};

class TrapeFactory : public IFactory {
public:
    std::shared_ptr<IFigure> FigureCreate(int id, Point a, Point b, Point c, Point d) const override {
        return std::shared_ptr<IFigure>(new Trape(id, a, b, c, d));
    }

    std::shared_ptr<IFigure> FigureCreate() const override {
        return std::shared_ptr<IFigure>(new Trape());
    }
};

#endif