#pragma once

#include <iostream>
#include "DynamicObject.h"
#include "MyTools.h"

using namespace MyTools;

class Tree;

class TreeState
{
protected:
	int sumTime;
public:
	TreeState() : sumTime(0) {}
	virtual void Grow(uint16_t dTime, Tree* tree) = 0;
	virtual void DrawTree(const double x, const double y) const = 0;
	virtual ~TreeState(){}
};

class Tree : public DynamicObject
{
private:
	TreeState* state;
public:
	void Draw() const override 
	{
		state->DrawTree(x, y);
	}
	virtual void Move(uint16_t time) override 
	{
		state->Grow(time, this);
	}
	void setTree(TreeState* tree)
	{
		if (state != nullptr)
		{
			delete state;
		}
		state = tree;

	}
	~Tree()
	{
		if (state != nullptr) 
		{
			delete state;
		}
	}
};

class BigTree : public TreeState {
public:
	void Grow(uint16_t dTime, Tree* tree) override {}

	void DrawTree(const double x, const double y) const override {
		SetColor(CC_Green);
		GotoXY(x - 2, y - 7);
		std::cout << "+++++";
		GotoXY(x - 3, y - 6);
		std::cout << "+++++++";
		GotoXY(x - 2, y - 5);
		std::cout << "+++++";
		GotoXY(x - 1, y - 4);
		std::cout << "+++";
		SetColor(CC_Brown);
		for (double i = y - 3; i <= y; ++i) {
			GotoXY(x, i);
			std::cout << "+";
		}


	}

};

class MiddleTree : public TreeState {
public:
	void Grow(uint16_t dTime, Tree* tree) override {
		sumTime += dTime;
		if (sumTime > 5000) {
			tree->setTree(new BigTree());
		}
	}

	void DrawTree(const double x, const double y) const override {
		SetColor(CC_Green);
		GotoXY(x - 2, y - 5);
		std::cout << "+++++";
		GotoXY(x - 1, y - 4);
		std::cout << "+++";
		SetColor(CC_Brown);
		for (double i = y - 3; i <= y; ++i) {
			GotoXY(x, i);
			std::cout << "+";
		}

	}

};

class SmallTree : public TreeState {
public:
	void Grow(uint16_t dTime, Tree* tree) override {
		sumTime += dTime;
		if (sumTime > 5000) {
			tree->setTree(new MiddleTree());
		}
	}

	void DrawTree(const double x, const double y) const override {
		SetColor(CC_Green);
		for (double i = y - 3; i <= y; ++i) {
			GotoXY(x, i);
			std::cout << "+";
		}
	}
};
