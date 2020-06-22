/*Хренов Геннадий M80-207Б
Спроектировать простейший графический векторный редактор 
со следующими требованиями: 
создание нового документа, 
импорт документа из файла, 
экспорт документа в файл, 
создание графического примитива,
удаление графического примитива,
отображение документа на экран
*/
#include <iostream>
#include "editor.h"
#include "figure.h"

void help() {
	std::cout << "you can use:\n";
	std::cout << "\tCreate\n";
	std::cout << "\tLoad\n";
  	std::cout << "\tSave filename\n";
  	std::cout << "\tAdd S/R/T coords\n";
  	std::cout << "\tRemove ID\n";
  	std::cout << "\tUndo\n";
  	std::cout << "\tPrint\n";
}

void create(Editor& editor) {
	std::string cmd;
	if (editor.DocumentExist()) {
		std::cout << "Save old document? Yes/No\n";
		std::cin >> cmd;
		if (cmd == "Yes") {
			std::string filename;
			std::cout << "Enter name of file\n";
			std::cin >> filename;
			try {
				editor.SaveDocument(filename);
				std::cout << "Document save in file " << filename << "\n";
			} catch (std::runtime_error& err) {
				std::cout << err.what() << "\n";
			}
		}
		std::cout << "Enter name of new project\n";
	}
	std::cin >> cmd;
	editor.CreateDocument(cmd);
	std::cout << "Document " << cmd << " is created\n";
}

void load(Editor& editor) {
	std::string cmd;
	if (editor.DocumentExist()) {
		std::cout << "Save old document? Yes/No\n";
		std::cin >> cmd;
		if (cmd == "Yes") {
			std::string filename;
			std::cout << "Enter name of file\n";
			std::cin >> filename;
			try {
				editor.SaveDocument(filename);
				std::cout << "Document save in file " << filename << "\n";
			} catch (std::runtime_error& err) {
				std::cout << err.what() << "\n";
			}
		}
	}
	std::string filename;
	std::cin >> filename;
	try {
		editor.LoadDocument(filename);
		std::cout << "Document loaded from file " << filename << "\n";
	} catch (std::runtime_error& err) {
		std::cout << err.what() << "\n";
	}
}

void save(Editor& editor) {
	std::string filename;
	std::cin >> filename;

	try {
		editor.SaveDocument(filename);
		std::cout << "Document save in file " << filename << "\n";
	} catch (std::runtime_error& err) {
		std::cout << err.what() << "\n";
	}
}

using Point = Pair<double,double>;
void add (Editor& editor) {
	char type;

    Point a, b, c, d;

	std::cin >> type;
	std::cin >> a >> b >> c >> d;
	switch(type) {
		case 'S':
			editor.InsertPrimitive(SQUARE, a, b, c, d);
			break;
		case 'R':
			editor.InsertPrimitive(RECTANGLE, a, b, c, d);
			break;
		case 'T':
			editor.InsertPrimitive(TRAPE, a, b, c, d);
			break;
		default:
			std::cout << "Unknown figure\n";
			return;
	}
	std::cout << "Figure is added\n";
}

void remove(Editor& editor) {
	int id;
	std::cin >> id;
	try {
		editor.RemovePrimitive(id);
		std::cout << "Primitive with " << id << " is removed\n";
	} catch (std::logic_error& err) {
		std::cout << err.what() << "\n";
	}


}

int main() {
	Editor editor;
	std::string cmd;
	std::cout << "enter 'help' for instructions\n\n";
	std::cout << "you need to create or load document for work(cmd Create, Load)\n";
	while (std::cin >> cmd) {
		if (cmd == "help") {
			help();
		} else if (cmd == "Create") {
			create(editor);
		} else if (cmd == "Load") {
			load(editor);
		} else if (cmd == "Save") {
			save(editor);
		} else if (cmd == "Add") {
			add(editor);
		} else if (cmd == "Remove") {
			remove(editor);
		} else if (cmd == "Undo") {
			editor.Undo();
			std::cout << "OK\n";
		} else if (cmd == "Print") {
			editor.PrintDocument();
		}
	}

	return 0;
}