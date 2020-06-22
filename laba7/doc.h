#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <fstream>
#include <cstdint>
#include <memory>
#include <string>
#include <algorithm>
#include "figure.h"
#include <list>


class Document {
public:
	Document(): Id_(1), Name_(""), Buf_(0), squareFactory(), rectangleFactory(), trapeFactory()
	{
	}

	explicit Document(std::string name):Id_(1), Name_(std::move(name)), Buf_(0),
	squareFactory(),
	rectangleFactory(),
	trapeFactory()
	{
	}

	~Document() = default;

	void Rename(const std::string& newName) {
		Name_ = newName;
	}

	void Save(const std::string& filename) const {
		SerializeImpl(filename);
	}

	void Load(const std::string& filename) {
		DeserializeImpl(filename);
	}

	void Print() {
		std::for_each(Buf_.begin(), Buf_.end(), [](std::shared_ptr<IFigure> shape) {
			shape->Print(std::cout) << "\n";
		});
	}

	void RemovePrimitive(int id) {
		auto it = std::find_if(Buf_.begin(), Buf_.end(), [id](std::shared_ptr<IFigure> shape) -> bool {
			return id == shape->Id();
		});

		if (it == Buf_.end())
			throw std::logic_error("Figure with this id doesn't exist");

		Buf_.erase(it);
	}

	using Point = Pair<double,double>;
	void InsertPrimitive(FigureType type, const Point a, const Point b, const Point c, const Point d) {
		switch (type) {
			case SQUARE:
				Buf_.push_back(squareFactory.FigureCreate(Id_++, a, b, c, d));
				break;
			case RECTANGLE:
				Buf_.push_back(rectangleFactory.FigureCreate(Id_++, a, b, c, d));
				break;
			case TRAPE:
				Buf_.push_back(trapeFactory.FigureCreate(Id_++, a, b, c, d));
				break;
		}
	}

private:
	int Id_;
	std::string Name_;
	std::list<std::shared_ptr<IFigure>> Buf_;
	SquareFactory squareFactory;
	RectangleFactory rectangleFactory;
	TrapeFactory trapeFactory;

	friend class InsertCommand;
	friend class RemoveCommand;

	void SerializeImpl(const std::string& filename) const {
		std::ofstream os;

		os.open(filename, std::ios_base::binary | std::ios_base::out);
		if (!os.is_open()) {
			throw std::runtime_error("File is not opened");
		}
		int nameLen = Name_.size();
		os.write((char*)&nameLen, sizeof(nameLen));
		os.write((char*)(Name_.c_str()), nameLen);
		for (const auto& shape : Buf_) {
			shape->Serialize(os);
		}
	}

	void DeserializeImpl(const std::string& filename) {
		std::ifstream is;

		is.open(filename, std::ios_base::binary | std::ios_base::in);
		if (!is.is_open()) {
			throw std::runtime_error("File is not opened");
		}
		int nameLen;
		is.read((char*)&nameLen, sizeof(nameLen));
		char* name = new char[nameLen + 1];
		name[nameLen] = 0;
		is.read(name, nameLen);
		Name_ = std::string(name);
		delete[] name;
		FigureType type;
		while(true) {
			is.read((char*)&type, sizeof(type));
			if (is.eof())
				break;
			switch (type) {
				case SQUARE:
					Buf_.push_back(squareFactory.FigureCreate());
					break;
				case RECTANGLE:
					Buf_.push_back(rectangleFactory.FigureCreate());
					break;
				case TRAPE:
					Buf_.push_back(trapeFactory.FigureCreate());
					break;
			}
			Buf_.back()->Deserialize(is);
		}
		Id_ = Buf_.size();
	}

	std::shared_ptr<IFigure> GetFigure(int id) {
		auto it = std::find_if(Buf_.begin(), Buf_.end(), [id](std::shared_ptr<IFigure> shape) -> bool {
			return id == shape->Id();
		});
		return *it;
	}

	int GetPos(int id) {
		auto it = std::find_if(Buf_.begin(), Buf_.end(), [id](std::shared_ptr<IFigure> shape) -> bool {
			return id == shape->Id();
		});
		return std::distance(Buf_.begin(), it);
	}

	void InsertPrimitive(int pos, std::shared_ptr<IFigure> figure) {
		auto it = Buf_.begin();
		std::advance(it, pos);
		Buf_.insert(it, figure);
	}

	void RemoveLastPrimitive() {
		if (Buf_.empty())
			throw std::logic_error("Document is empty");
		Buf_.pop_back();
	}
};

#endif