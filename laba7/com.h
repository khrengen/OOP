#ifndef COMMAND_H
#define COMMAND_H

#include "doc.h"
#include "figure.h"
#include <stack>

class ICommand {
protected:
	std::shared_ptr<Document> Doc;
public:
	virtual ~ICommand() = default;
	virtual void Execute() = 0;
	virtual void UnExecute() = 0;

	void SetDocument(std::shared_ptr<Document> doc) {
		Doc = doc;
	}
};

using Point = Pair<double,double>;
class InsertCommand : public ICommand {
public:

	InsertCommand(FigureType type, Point a, Point b, Point c, Point d):
		Type_(type), A_(std::move(a)), B_(std::move(b)),  C_(std::move(c)),  D_(std::move(d))
	{
	}

	void Execute() override {
		Doc->InsertPrimitive(Type_, A_,B_, C_, D_);
	}

	void UnExecute() override {
		Doc->RemoveLastPrimitive();
	}

private:
	FigureType Type_;
	Point A_, B_, C_, D_;
};

class RemoveCommand : public ICommand {
public:
	explicit RemoveCommand(int id): Id_(id), Pos_(0), Figure_(nullptr)
	{
	}

	void Execute() override {
		Figure_ = Doc->GetFigure(Id_);
		Pos_ = Doc->GetPos(Id_);
		Doc->RemovePrimitive(Id_);
	}

	void UnExecute() override {
		Doc->InsertPrimitive(Pos_, Figure_);
	}

private:
	int Id_;
	int Pos_;
	std::shared_ptr<IFigure> Figure_;
};

#endif