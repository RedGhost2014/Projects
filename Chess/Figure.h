#pragma once
#ifndef _FIGURE_
#define _FIGURE_

#include <iostream>
#include <string>
#include <vector>
#include <raylibcpp/include/raylib-cpp.hpp>
#include "GameSettings.h"
#include "Cell.h"

class Figure
{
public:

	enum class FigureColor
	{
		FIGURE_WHITE,
		FIGURE_BLACK,
	};

	enum class FigureType
	{
		FIGURE_PAWN,
		FIGURE_ROOK,
		FIGURE_BISHOP,
		FIGURE_KNIGHT,
		FIGURE_KING,
		FIGURE_QUEEN,
	};

private:

	std::string figurename;
	raylib::Texture texture;
	size_t X;
	size_t Y;

	FigureType figuretype;
	FigureColor color;
	bool isfirstmove;
	bool isalive;

public:

	virtual std::vector<Cell*>* getPossibleMoves(std::vector<Figure*>& figures, GameSettings& gs);
	virtual void MoveTo(size_t newX, size_t newY);

	Figure& setName(std::string& name);
	Figure& setTexture(const raylib::Texture& _texture);
	Figure& setColor(FigureColor _color);
	Figure& setXY(size_t x, size_t y);
	Figure& setType(FigureType type);
	Figure& setFirstMove(bool move);
	Figure& setAliveMode(bool alive);

	raylib::Texture& getTexture();
	size_t getX();
	size_t getY();
	FigureType& getType();
	FigureColor& getColor();
	bool isFirstMove();
	bool isAlive();
	Figure();
	~Figure();
};




class Pawn : public Figure
{
public:
	std::vector<Cell*>* getPossibleMoves(std::vector<Figure*>& figures, GameSettings& gs) override;
	Pawn();
	~Pawn();

};

class Rook : public Figure
{
public:
	std::vector<Cell*>* getPossibleMoves(std::vector<Figure*>& figures, GameSettings& gs) override;
	Rook();
	~Rook();

};

class Bishop : public Figure
{
public:
	std::vector<Cell*>* getPossibleMoves(std::vector<Figure*>& figures, GameSettings& gs) override;
	Bishop();
	~Bishop();

};

class Knight : public Figure
{
public:
	std::vector<Cell*>* getPossibleMoves(std::vector<Figure*>& figures, GameSettings& gs) override;
	Knight();
	~Knight();

};

class Queen : public Figure
{
public:
	std::vector<Cell*>* getPossibleMoves(std::vector<Figure*>& figures, GameSettings& gs) override;
	Queen();
	~Queen();

};

class King : public Figure
{
public:
	std::vector<Cell*>* getPossibleMoves(std::vector<Figure*>& figures, GameSettings& gs) override;
	King();
	~King();

};

#endif // !_

