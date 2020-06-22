/* Хренов Геннадий м8о - 207б
Создать приложение, которое будет считывать из стандартного ввода данные фигур,
выводить их характеристики на экран
 и записывать в файл.
*/
#include <iostream>
#include <future> 
#include <chrono>
#include <map>
#include "figure.h"
#include <algorithm>


void help() {
	std::cout << "you can use:\n";
	std::cout << "'add' for adding square(S), rectangle(R) or trape(T)\n";
	std::cout << "'exit' for exit\n";
}

void wait(std::future<int>& fut) {

    int f = fut.get();
    if (f) {
        std::cout << "\n...All data processed successfully...\n\n";
    } 
}

int main (int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "invalid input(enter exec file + buffer size)\n");
        exit(0);
    }

    using Point = Pair<double,double>;
    int size = atoi(argv[1]);
    std::vector<IFigure*> buf;
    Publisher pub(buf, size);
    char sout[] = "stdout";
    char fout[] = "output.txt";
    Subscriber sub2(sout);
    Subscriber sub1(fout);
    pub.Subscribe(sub1);
    pub.Subscribe(sub2);
    int id = 1;
    Point a, b, c, d;
    char ftype;
	std::string str;    
	IFigure* fig;

    while (std::cin >> str) {
        std::future<int> fut;
        if (str == "add") {
        	std::cin >> ftype;
			std::cin >> a >> b >> c >> d;
			if (ftype == 'S') {
                if(isSquare(a,b,c,d)) {
				    fig = new Square(id, a, b, c, d);
                    id++;
                    printf("figure added\n");
                } else printf("it`s not a square\n");
			} else if (ftype == 'R') {
                if (isRectangle(a,b,c,d)){
				    fig = new Rectangle(id, a, b, c, d);
                    id++;
                    printf("figure added\n");
                } else printf("it`s not a rectangle\n");
			} else if (ftype == 'T') {
                if (isTrape(a,b,c,d)) {
				    fig = new Trape(id, a, b, c, d);
                    id++;
                    printf("figure added\n");
                } else printf("it`s not a trape\n");
       		}
                fut = std::async(&Publisher::Add,&pub,fig);
                wait(fut);
        } else if (str == "help") {
        	help();
        } else if (str == "exit") {
            exit(0);
        }
                         
    }
    return 0;
}