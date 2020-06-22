//Хренов Геннадий М80-207Б
// cоздание динамического массива
// фигура - квадрат
// Программа позволяет вводить с клавиатуры фигуры типа int(по заданию)
//и добавлять их в коллекцию. Из коллекции можно удалять фигуры по индексу,
// а также выводить на экран уже введенные фигуры с их свойствами. 
//Также можно узнать число объектов, площадь которых меньше введенного значения. 
//Для всех входных данных ловятся исключения,
//например существующий ли индекс вводится или правильность ввода квадрата.


#include <iostream>
#include <utility>
#include <algorithm>
#include <map>
#include "vector.hpp"
#include "figure.hpp"


bool isSquare(myPair<int,int> a, myPair<int,int> b, myPair<int,int> c, myPair<int,int> d)
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

template <class T>
void printCoorFE(T In) {
    printCoor(*In);
}



int main(void) {
	std::cout << "use 'help' to see what is available" << '\n';
	using Point = myPair<int,int>;
	Point P1, P2, P3, P4;
	int areaMax;
	int index;
	TVector<Figure<int>*> vec;
	std::string inpt;
	int ex = 0;

	while (ex == 0) {
		std::cin >> inpt;

        if (inpt == "add") {
        	std::cin >> P1 >> P2 >> P3 >> P4;
 
            if(!(isSquare(P1,P2,P3,P4))) {
            	std::cout << "It`s not a Square\n";
            } else { 
            	vec.push_back(dynamic_cast<Figure<int>*>(new Square<int>(P1, P2, P3, P4)));
            	std::cout << "Square added\n";
            }	
        } else if (inpt == "print") {
        	std::cin >> inpt;
        	if (inpt == "all") {
                std::for_each(vec.begin(), vec.end(), [](auto& k){
                    printCoor(*k);
                    putchar('\n');
        	    });
        	} else {
        		try {
        			index = std::stoi(inpt);
            	} catch (std::invalid_argument) {
                	std::cout << "Invalid argument\n";
        		}
        		if (index > (vec.size() - 1) || index < 0) {
                	std::cout << "Invalid index\n";
            	} else {
            		printCoor(*(vec[index]));
            		std::cout << "centr: " << centr(*(vec[index])) << '\n';
            		std::cout << "area: " << area(*vec[index]) << '\n';
            	}	
        	}
        } else if (inpt == "lessthan") {
        	std::cin >> areaMax;
        	if (areaMax < 0) {
        		std::cout << "Invalid areaMax\n";
        	
        	} else {
        		std::cout << std::count_if(vec.begin(), vec.end(), [areaMax](auto& k) {
                	return areaMax > area(*k);
                	}) << '\n';
        	}	
        } else if (inpt == "del") {
        	if (!(std::cin >> index)) {
                std::cout << "Invalid input\n";
            }
            if (index > (vec.size() - 1) || index < 0) {
                std::cout << "Invalid index\n";
            } else {
            	delete vec[index];
            	vec.erase(vec.begin() + index);
            	std::cout << "Element was deleted\n";
            }
        } else if (inpt == "exit") {
        	ex = 1;
        	for (int i = 0; i < vec.size();i++) {
        		delete vec[i];
        	}
        } else if (inpt == "help") {
        	std::cout << "available command:\n";
        	std::cout << "\tadd (use with 4 point)\n";
        	std::cout << "\tprint (use with all or with index)\n";
        	std::cout << "\tlessthan (use with area you want)\n";
        	std::cout << "\tdel (use with index)\n";
        	std::cout << "\texit (if you want to quite)\n";
        	std::cout << "\thelp (if you want to see this menu again)\n";
        } else {
        	std::cout << "unknown comand(use help)\n";
        }
    }
    return 0;
}
