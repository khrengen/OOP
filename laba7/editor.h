#ifndef EDITOR_H
#define EDITOR_H

#include "doc.h"
#include "com.h"
#include "figure.h"
#include <stack>


class Editor {
public:
	Editor() : Doc_(nullptr), History_()
	{
	}

	void CreateDocument(const std::string& name) {
		Doc_ = std::make_shared<Document>(name);
	}

	using Point = Pair<double,double>;
	void InsertPrimitive(FigureType type, const Point a, const Point b, const Point c, const Point d) {
		std::shared_ptr<ICommand> command = std::shared_ptr<ICommand>(new InsertCommand(type, a, b, c, d));
		command->SetDocument(Doc_);
		command->Execute();
		History_.push(command);
	}

	void RemovePrimitive(int id) {
		std::shared_ptr<ICommand> command = std::shared_ptr<ICommand>(new RemoveCommand(id));
		command->SetDocument(Doc_);
		command->Execute();
		History_.push(command);
	}

	void SaveDocument(const std::string& filename) {
		Doc_->Save(filename);
	}

	void LoadDocument(const std::string& filename) {
		Doc_ = std::make_shared<Document>("NoName");
		Doc_->Load(filename);
	}

	void Undo() {
		if (History_.empty()) {
			throw std::logic_error("History is empty");
		} else {
		std::shared_ptr<ICommand> lastCommand = History_.top();
		lastCommand->UnExecute();
		History_.pop();
		}
	}

	void PrintDocument() {
		Doc_->Print();
	}

	bool DocumentExist() {
		return Doc_ != nullptr;
	}

	~Editor() = default;
private:
	std::shared_ptr<Document> Doc_;
	std::stack<std::shared_ptr<ICommand>> History_;
};

#endif