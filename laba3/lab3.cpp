//Хренов Геннадий М8О-207Б 
// Созданны классы : квадрат, прямоугольник, трапеция 
//и методы для подсчёта геометрического центра, площади и печать координат. 


#include<iostream>
#include <math.h>
#include <vector>

struct point {
	double x;
	double y;	
};

double dist(point a, point b){
	return sqrt(pow(b.x - a.x,2) + pow(b.y - a.y,2));
}

class Figure {
public:
	
	virtual void GCF() = 0;

	virtual double SF() = 0;

	virtual void print() = 0; 
	
};

class Square : public Figure {

public:

	Square() {}
	Square(const point& z, const point& w) : Square(){
		a.x = z.x;
		c.x = w.x;
		a.y = z.y;
		c.y = w.y;

	}

	void GCF(){
		printf("center : %lf, %lf\n", (a.x+c.x)/2, (a.y+c.y)/2);
	}

	double SF(){
		point b;
		b.x = a.x;
		b.y = c.y;
		return pow(dist(a,b), 2); 
	}

	void print(){
		printf("A = (%lf,%lf) B = (%lf,%lf)  C = (%lf,%lf) D = (%lf,%lf)\n", a.x, a.y, a.x, c.y, c.x, c.y, c.x, a.y); 
	}

private:
	point a;
	point c;
	
};

class Rectan : public Figure {

public:

	Rectan() {}
	Rectan(const point& z, const point& w) : Rectan() {
		a.x = z.x;
		c.x = w.x;
		a.y = z.y;
		c.y = w.y;
	}

	void GCF(){
		printf("center : %lf, %lf\n", (a.x+c.x)/2, (a.y+c.y)/2);;
	}

	double SF(){
		point b;
		b.x = a.x;
		b.y = c.y;
		return dist(a,b) * dist(b,c); 
	}

	void print(){
		printf("A = (%lf,%lf) B = (%lf,%lf) C = (%lf,%lf) D = (%lf,%lf)\n", a.x, a.y, a.x, c.y, c.x, c.y, c.x, a.y); 
	}

private:
	point a;
	point c;
	
};

class Trape : public Figure {

public:

	Trape() {}
	Trape(const point& z, const point& e,const point& w, const point& q) : Trape() {
		a.x = z.x;
		c.x = w.x;
		a.y = z.y;
		c.y = w.y;
		b.x = e.x;
		b.y = e.y;
		d.x = q.x;
		d.y = q.y;

	}

	void GCF(){
		printf("center : %lf, %lf\n", (a.x + c.x + b.x + d.x) / 4, (a.y + c.y + b.y + d.y) / 4);
	}

	double SF(){
		double h = sqrt(pow(dist(a,b),2) - pow((dist(a,d) - dist(c,b))/2,2)); 
		return (dist(a,d) + dist(b,c)) * 0.5 * h; 
	} 

	void print(){
		printf("A = (%lf,%lf) B = (%lf,%lf) C = (%lf,%lf) D = (%lf,%lf)\n", a.x, a.y, b.x, b.y, c.x, c.y, d.x, d.y); 
	}

private:
	point a;
	point b;
	point c;
	point d;
	
};


void read(std::vector<Figure*>& fig)
{
	char shape;
	Square *s = nullptr;
	Rectan *r = nullptr;
	Trape *t = nullptr;
	point a,b,c,d;

	std::cin >> shape;
	switch (shape) {
		case 't':
			std::cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
			if (dist(a,b) != dist(c,d)){
				fprintf(stderr, "wrong coordinates\n");
				break;
			}

			t = new Trape(a,b,c,d);
			
			fig.push_back(t);
			break;
		case 's':
			std::cin >> a.x >> a.y >> c.x >> c.y;
			s = new Square(a,c);
			fig.push_back(s);
			break;
		case 'r':
			std::cin >> a.x >> a.y >> c.x >> c.y;
			r = new Rectan(a,c);
			fig.push_back(dynamic_cast<Figure*>(r));
			break;
		default:
			std::cout << "doing something wrong\n";
			return;
	}
}

double allsq(std::vector<Figure*>& fig) {
	double sum = 0;
	for (int i = 0; i < fig.size(); ++i) {
		sum += fig[i]->SF();
	}
	return sum;
}

void del(std::vector<Figure*>& fig, int n){
	if (n < 0 || n >= fig.size()) {
		std::cout << "invalid index\n";
		return ;
	} else{
		delete fig[n];
		for (int i = n; i < fig.size() - 1; ++i){
			fig[i] = fig[i+1];
		}
		fig.pop_back();
	}
}
int main() {
std:: string str;
std::vector<Figure*> figu;
std::cout << "vector Figure* was created. Press any bottom for istruction\n";
while(std::cin >> str){
	if (str == "push") {
		read(figu);	
	}else if (str == "print") {
		for (int i = 0; i < figu.size(); ++i){
			std::cout << "figure № " << i + 1 << std::endl;
			figu[i]->GCF();
			std::cout << "square : " << figu[i]->SF() << std::endl;
			figu[i]->print();
			std::cout << std::endl;
		}
	}else if (str == "squaresum") {
		std::cout << "squaresum : " <<allsq(figu) << std::endl;
	}else if (str == "del") {
		int i;
		std::cin >> i;
		del(figu,i);
	}else if ( str == "q"){
		figu.clear();
		return 0;
	}else{
		std::cout << "USE:" << std::endl
		 << "'push (s,r,t) + coord' to add" << std::endl
		 << "'print' to see all answers" << std::endl 
		 << "'squaresum' to see sum of all square"<< std:: endl
		 << "'del' to delete" << std::endl
		 << "'q' to quit" << std::endl;
	}
}


}