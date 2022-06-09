#pragma once
#include <raylibcpp/include/raylib-cpp.hpp>
#include "GameSettings.h"
#include "Figure.h"

//#define DEBUG

class MyMouse : public raylib::Mouse
{
	size_t XCell;
	size_t YCell;

	bool figureWasChoosen;
	size_t choosedFigureX;
	size_t choosedFigureY;

public:
	MyMouse()
	{
		XCell = 0;
		YCell = 0;
		figureWasChoosen = false;
		choosedFigureX = 0;
		choosedFigureY = 0;
	};
	void setCellCords(size_t x, size_t y)
	{
		XCell = x;
		YCell = y;
	}
	void setChooseState(bool state)
	{
		figureWasChoosen = state;
	}
	void setChoosedFigureCoordinates(size_t x, size_t y)
	{
		choosedFigureX = x;
		choosedFigureY = y;
	}

	inline size_t getChoosedFigureCoordinateX()
	{
		return choosedFigureX;
	}
	inline size_t getChoosedFigureCoordinateY()
	{
		return choosedFigureY;
	}

	inline size_t getCellCoordX()
	{
		return XCell;
	}
	inline size_t getCellCoordY()
	{
		return YCell;
	}
	inline bool isFigureChoosen()
	{
		return figureWasChoosen;
	}

};

class Application
{
private:

	struct LastTurn
	{
		Figure* lastfigure;

		int oldX;
		int oldY;
	public:
		LastTurn()
		{
			oldY = 0;
			oldY = 0;
			lastfigure = nullptr;
		}

		//LastTurn(){}
	};

	LastTurn* lastturn;

	raylib::Window mainWindow;
	size_t screenWidth;
	size_t screenHeight;
	size_t leftgap;
	size_t topgap;

	GameSettings gs;
	MyMouse mainMouse;

	std::vector<Figure*> Figures;


	void loadPawns(const char* folder);
	void loadRooks(const char* folder);
	void loadBishops(const char* folder);
	void loadKnights(const char* folder);
	void loadKings(const char* folder);
	void loadQueens(const char* folder);
	Figure* findFigureByChoosedCoords();
	void chooseFigure();
	void drawRectangleOnBoard(int posX, int posY, int width, int height, Color color);
	void drawChoosenFigureMoves();
	void movingChoosedFigure();
	void DrawMouseSelector();
	void DrawField();

	void checkActions();

public:

	Application(size_t width, size_t height, std::string& title, unsigned flags);

	void setGameSettings(size_t widthBoard = 8, size_t heightBoard = 8, size_t sizeOfCellInPixels = 80, size_t countOfFigures = 32, size_t gamemode = 0, size_t skin = 0);

	void startApplicationWorkCycle();

	void loadFigures(const char* foldername);

	~Application();
};
