#include <raylibcpp/include/raylib-cpp.hpp>
#include "Application.h"

void Application::startApplicationWorkCycle()
{
	static int z = 0;
	while (!mainWindow.ShouldClose())
	{
		mainWindow.BeginDrawing();

		mainWindow.ClearBackground(RAYWHITE);

		DrawField();
		DrawMouseSelector();

		
		chooseFigure();
		if (mainMouse.isFigureChoosen())
		{
			drawChoosenFigureMoves();
			movingChoosedFigure();
			checkActions();
		}
		size_t cellsize = gs.getCellSize();
		for (size_t i = 0; i < Figures.size(); i++)
		{
			if (Figures[i]->isAlive())
				Figures[i]->getTexture().Draw(Figures[i]->getX() * cellsize + leftgap, Figures[i]->getY() * cellsize + topgap);
		}

		mainWindow.EndDrawing();
	}
}

void Application::checkActions()
{
	Figure* fig = lastturn->lastfigure;
	if (fig == nullptr)
		return;
	if (fig->getType() == Figure::FigureType::FIGURE_KING)
	{
		if (fig->getX() == lastturn->oldX - 2)
		{
			Figure* leftRook = Cell::getFigureInCell(fig->getX() - 2, fig->getY(), &Figures);
			if (leftRook != nullptr)
				leftRook->MoveTo(fig->getX() + 1, fig->getY());
		}
		else if (fig->getX() == lastturn->oldX + 2)
		{
			Figure* rightRook = Cell::getFigureInCell(fig->getX() + 1, fig->getY(), &Figures);
			if (rightRook != nullptr)
				rightRook->MoveTo(fig->getX() - 1, fig->getY());
		}
	}
}

void Application::loadPawns(const char* folder)
{
	std::string currentFigureWhite = "data/Figures/";
	std::string currentFigureBlack = "data/Figures/";

	currentFigureWhite += folder;
	currentFigureBlack += folder;

	raylib::Texture* imgtexture = nullptr;

	if (!DirectoryExists(currentFigureWhite.c_str()))
	{
		std::cout << "Exception: Cannot open directory" << std::endl;
		return;
	}

	imgtexture = new raylib::Texture;
	currentFigureWhite += "wP.png";
	if (imgtexture->Load(currentFigureWhite))
		std::cout << "White Pawn was loaded." << std::endl;
	else
	{
		imgtexture->Load("data/Figures/outofimage.png");
		std::cout << "Exception: Loading White Pawn was failed." << std::endl;
	}

	for (size_t i = 0; i < 8; i++)
	{
		Figure* newFigure = new Pawn();
		std::string pawn = "Pawn";
		newFigure->setName(pawn).setTexture(*imgtexture).setColor(Figure::FigureColor::FIGURE_WHITE).
			setXY(0 + i, 6).setType(Figure::FigureType::FIGURE_PAWN).setFirstMove(true);
		Figures.push_back(newFigure);
	}

	imgtexture = new raylib::Texture;
	currentFigureBlack += "bP.png";
	if (imgtexture->Load(currentFigureBlack))
		std::cout << "Black Pawn was loaded." << std::endl;
	else
	{
		imgtexture->Load("data/Figures/outofimage.png");
		std::cout << "Exception: Loading Black Pawn was failed." << std::endl;
	}

	for (size_t i = 0; i < 8; i++)
	{
		Figure* newFigure = new Pawn();
		std::string pawn = "Pawn";
		newFigure->setName(pawn).setTexture(*imgtexture).setColor(Figure::FigureColor::FIGURE_BLACK).
			setXY(0 + i, 1).setType(Figure::FigureType::FIGURE_PAWN).setFirstMove(true);
		Figures.push_back(newFigure);
	}
}

void Application::loadRooks(const char* folder)
{
	std::string currentFigureWhite = "data/Figures/";
	std::string currentFigureBlack = "data/Figures/";

	currentFigureWhite += folder;
	currentFigureBlack += folder;

	raylib::Texture* imgtexture = nullptr;

	if (!DirectoryExists(currentFigureWhite.c_str()))
	{
		std::cout << "Exception: Cannot open directory" << std::endl;
		return;
	}

	imgtexture = new raylib::Texture;
	currentFigureWhite += "wR.png";
	if (imgtexture->Load(currentFigureWhite))
		std::cout << "White Rook was loaded." << std::endl;
	else
	{
		imgtexture->Load("data/Figures/outofimage.png");
		std::cout << "Exception: Loading White Rook was failed." << std::endl;
	}

	Figure* newFigure = new Rook();
	std::string rook = "Rook";
	newFigure->setName(rook).setTexture(*imgtexture).setColor(Figure::FigureColor::FIGURE_WHITE).
		setXY(0, 7).setType(Figure::FigureType::FIGURE_ROOK).setFirstMove(true);
	Figures.push_back(newFigure);

	newFigure = new Rook();

	newFigure->setName(rook).setTexture(*imgtexture).setColor(Figure::FigureColor::FIGURE_WHITE).
		setXY(7, 7).setType(Figure::FigureType::FIGURE_ROOK).setFirstMove(true);
	Figures.push_back(newFigure);

	imgtexture = new raylib::Texture;
	currentFigureBlack += "bR.png";
	if (imgtexture->Load(currentFigureBlack))
		std::cout << "Black Rook was loaded." << std::endl;
	else
	{
		imgtexture->Load("data/Figures/outofimage.png");
		std::cout << "Exception: Loading Black Rook was failed." << std::endl;
	}

	newFigure = new Rook();
	newFigure->setName(rook).setTexture(*imgtexture).setColor(Figure::FigureColor::FIGURE_BLACK).
		setXY(0, 0).setType(Figure::FigureType::FIGURE_PAWN).setFirstMove(true);
	Figures.push_back(newFigure);

	newFigure = new Rook();

	newFigure->setName(rook).setTexture(*imgtexture).setColor(Figure::FigureColor::FIGURE_BLACK).
		setXY(7, 0).setType(Figure::FigureType::FIGURE_PAWN).setFirstMove(true);
	Figures.push_back(newFigure);

}

void Application::loadBishops(const char* folder)
{
	std::string currentFigureWhite = "data/Figures/";
	std::string currentFigureBlack = "data/Figures/";

	currentFigureWhite += folder;
	currentFigureBlack += folder;

	raylib::Texture* imgtexture = nullptr;

	if (!DirectoryExists(currentFigureWhite.c_str()))
	{
		std::cout << "Exception: Cannot open directory" << std::endl;
		return;
	}

	imgtexture = new raylib::Texture;
	currentFigureWhite += "wB.png";
	if (imgtexture->Load(currentFigureWhite))
		std::cout << "White Bishop was loaded." << std::endl;
	else
	{
		imgtexture->Load("data/Figures/outofimage.png");
		std::cout << "Exception: Loading White Bishop was failed." << std::endl;
	}

	Figure* newFigure = new Bishop();
	std::string bishop = "Bishop";
	newFigure->setName(bishop).setTexture(*imgtexture).setColor(Figure::FigureColor::FIGURE_WHITE).
		setXY(2, 7).setType(Figure::FigureType::FIGURE_BISHOP).setFirstMove(true);
	Figures.push_back(newFigure);

	newFigure = new Bishop();

	newFigure->setName(bishop).setTexture(*imgtexture).setColor(Figure::FigureColor::FIGURE_WHITE).
		setXY(5, 7).setType(Figure::FigureType::FIGURE_BISHOP).setFirstMove(true);
	Figures.push_back(newFigure);

	imgtexture = new raylib::Texture;
	currentFigureBlack += "bB.png";
	if (imgtexture->Load(currentFigureBlack))
		std::cout << "Black Bishop was loaded." << std::endl;
	else
	{
		imgtexture->Load("data/Figures/outofimage.png");
		std::cout << "Exception: Loading Black Bishop was failed." << std::endl;
	}

	newFigure = new Bishop();
	newFigure->setName(bishop).setTexture(*imgtexture).setColor(Figure::FigureColor::FIGURE_BLACK).
		setXY(2, 0).setType(Figure::FigureType::FIGURE_ROOK).setFirstMove(true);
	Figures.push_back(newFigure);

	newFigure = new Bishop();

	newFigure->setName(bishop).setTexture(*imgtexture).setColor(Figure::FigureColor::FIGURE_BLACK).
		setXY(5, 0).setType(Figure::FigureType::FIGURE_ROOK).setFirstMove(true);
	Figures.push_back(newFigure);

}

void Application::loadKnights(const char* folder)
{
	std::string currentFigureWhite = "data/Figures/";
	std::string currentFigureBlack = "data/Figures/";

	currentFigureWhite += folder;
	currentFigureBlack += folder;

	raylib::Texture* imgtexture = nullptr;

	if (!DirectoryExists(currentFigureWhite.c_str()))
	{
		std::cout << "Exception: Cannot open directory" << std::endl;
		return;
	}

	imgtexture = new raylib::Texture;
	currentFigureWhite += "wN.png";
	if (imgtexture->Load(currentFigureWhite))
		std::cout << "White Knight was loaded." << std::endl;
	else
	{
		imgtexture->Load("data/Figures/outofimage.png");
		std::cout << "Exception: Loading White Knight was failed." << std::endl;
	}

	Figure* newFigure = new Knight();
	std::string knight = "Knight";
	newFigure->setName(knight).setTexture(*imgtexture).setColor(Figure::FigureColor::FIGURE_WHITE).
		setXY(1, 7).setType(Figure::FigureType::FIGURE_KNIGHT).setFirstMove(true);
	Figures.push_back(newFigure);

	newFigure = new Knight();

	newFigure->setName(knight).setTexture(*imgtexture).setColor(Figure::FigureColor::FIGURE_WHITE).
		setXY(6, 7).setType(Figure::FigureType::FIGURE_KNIGHT).setFirstMove(true);
	Figures.push_back(newFigure);

	imgtexture = new raylib::Texture;
	currentFigureBlack += "bN.png";
	if (imgtexture->Load(currentFigureBlack))
		std::cout << "Black Knight was loaded." << std::endl;
	else
	{
		imgtexture->Load("data/Figures/outofimage.png");
		std::cout << "Exception: Loading Black Knight was failed." << std::endl;
	}

	newFigure = new Knight();
	newFigure->setName(knight).setTexture(*imgtexture).setColor(Figure::FigureColor::FIGURE_BLACK).
		setXY(1, 0).setType(Figure::FigureType::FIGURE_KNIGHT).setFirstMove(true);
	Figures.push_back(newFigure);

	newFigure = new Knight();

	newFigure->setName(knight).setTexture(*imgtexture).setColor(Figure::FigureColor::FIGURE_BLACK).
		setXY(6, 0).setType(Figure::FigureType::FIGURE_KNIGHT).setFirstMove(true);
	Figures.push_back(newFigure);

}

void Application::loadKings(const char* folder)
{
	std::string currentFigureWhite = "data/Figures/";
	std::string currentFigureBlack = "data/Figures/";

	currentFigureWhite += folder;
	currentFigureBlack += folder;

	raylib::Texture* imgtexture = nullptr;

	if (!DirectoryExists(currentFigureWhite.c_str()))
	{
		std::cout << "Exception: Cannot open directory" << std::endl;
		return;
	}

	imgtexture = new raylib::Texture;
	currentFigureWhite += "wK.png";
	if (imgtexture->Load(currentFigureWhite))
		std::cout << "White King was loaded." << std::endl;
	else
	{
		imgtexture->Load("data/Figures/outofimage.png");
		std::cout << "Exception: Loading White King was failed." << std::endl;
	}

	Figure* newFigure = new King();
	std::string king = "King";
	newFigure->setName(king).setTexture(*imgtexture).setColor(Figure::FigureColor::FIGURE_WHITE).
		setXY(4, 7).setType(Figure::FigureType::FIGURE_KING).setFirstMove(true);
	Figures.push_back(newFigure);

	imgtexture = new raylib::Texture;
	currentFigureBlack += "bK.png";
	if (imgtexture->Load(currentFigureBlack))
		std::cout << "Black King was loaded." << std::endl;
	else
	{
		imgtexture->Load("data/Figures/outofimage.png");
		std::cout << "Exception: Loading Black King was failed." << std::endl;
	}

	newFigure = new King();
	newFigure->setName(king).setTexture(*imgtexture).setColor(Figure::FigureColor::FIGURE_BLACK).
		setXY(4, 0).setType(Figure::FigureType::FIGURE_KING).setFirstMove(true);
	Figures.push_back(newFigure);

}

void Application::loadQueens(const char* folder)
{
	std::string currentFigureWhite = "data/Figures/";
	std::string currentFigureBlack = "data/Figures/";

	currentFigureWhite += folder;
	currentFigureBlack += folder;

	raylib::Texture* imgtexture = nullptr;

	if (!DirectoryExists(currentFigureWhite.c_str()))
	{
		std::cout << "Exception: Cannot open directory" << std::endl;
		return;
	}

	imgtexture = new raylib::Texture;
	currentFigureWhite += "wQ.png";
	if (imgtexture->Load(currentFigureWhite))
		std::cout << "White Queen was loaded." << std::endl;
	else
	{
		imgtexture->Load("data/Figures/outofimage.png");
		std::cout << "Exception: Loading White Queen was failed." << std::endl;
	}

	Figure* newFigure = new Queen();
	std::string queen = "Queen";
	newFigure->setName(queen).setTexture(*imgtexture).setColor(Figure::FigureColor::FIGURE_WHITE).
		setXY(3, 7).setType(Figure::FigureType::FIGURE_QUEEN).setFirstMove(true);
	Figures.push_back(newFigure);

	imgtexture = new raylib::Texture;
	currentFigureBlack += "bQ.png";
	if (imgtexture->Load(currentFigureBlack))
		std::cout << "Black Queen was loaded." << std::endl;
	else
	{
		imgtexture->Load("data/Figures/outofimage.png");
		std::cout << "Exception: Loading Black Queen was failed." << std::endl;
	}

	newFigure = new Queen();
	newFigure->setName(queen).setTexture(*imgtexture).setColor(Figure::FigureColor::FIGURE_BLACK).
		setXY(3, 0).setType(Figure::FigureType::FIGURE_QUEEN).setFirstMove(true);
	Figures.push_back(newFigure);

}

Figure* Application::findFigureByChoosedCoords()
{
	for (size_t i = 0; i < Figures.size(); i++)
	{
		size_t x = Figures[i]->getX();
		size_t y = Figures[i]->getY();
		//if (Figures[i]->getX() == mainMouse.getChoosedFigureCoordinateX() && Figures[i]->getY() == mainMouse.getChoosedFigureCoordinateY())
		if (x == mainMouse.getChoosedFigureCoordinateX() && y == mainMouse.getChoosedFigureCoordinateY() && Figures[i]->isAlive())
		{
			return Figures[i];
		}
	}
	return nullptr;
}

void Application::chooseFigure()
{
	int x = mainMouse.GetX();
	int y = mainMouse.GetY();

	if (x > leftgap && x < leftgap + gs.getWidthSize() * gs.getCellSize() && y > topgap && y < topgap + gs.getHeightSize() * gs.getCellSize())
	{
		//if (mainMouse.IsButtonPressed(MOUSE_BUTTON_LEFT) &&
		//	mainMouse.getCellCoordX() == mainMouse.getChoosedFigureCoordinateX() &&
		//	mainMouse.getCellCoordY() == mainMouse.getChoosedFigureCoordinateY())
		//{
		//	mainMouse.setChooseState(false);
		//	mainMouse.setChoosedFigureCoordinates(-1, -1);
		//}
		//else if (mainMouse.IsButtonPressed(MOUSE_BUTTON_LEFT) /*&& 
		//	mainMouse.getCellCoordX() != mainMouse.getChoosedFigureCoordinateX() &&
		//	mainMouse.getCellCoordY() != mainMouse.getChoosedFigureCoordinateY()*/)
		//{
		//	mainMouse.setChooseState(true);
		//	mainMouse.setChoosedFigureCoordinates(mainMouse.getCellCoordX(), mainMouse.getCellCoordY());
		//}

		if (mainMouse.IsButtonPressed(MOUSE_BUTTON_RIGHT))
		{
			mainMouse.setChooseState(false);
			mainMouse.setChoosedFigureCoordinates(-1, -1);
		}
		else if (mainMouse.IsButtonPressed(MOUSE_BUTTON_LEFT) && !mainMouse.isFigureChoosen())
		{
			mainMouse.setChoosedFigureCoordinates(mainMouse.getCellCoordX(), mainMouse.getCellCoordY());
			Figure* fig = findFigureByChoosedCoords();
			if (fig != nullptr)
			{
				if (mainMouse.isFigureChoosen() && mainMouse.getCellCoordX() == mainMouse.getChoosedFigureCoordinateX() &&
					mainMouse.getCellCoordY() == mainMouse.getChoosedFigureCoordinateY())
				{
					mainMouse.setChooseState(false);
					mainMouse.setChoosedFigureCoordinates(-1, -1);
				}
				else
				{
#ifdef DEBUG
					std::cout << "Choosed fig (" << mainMouse.getCellCoordX() << "," << mainMouse.getCellCoordY() << ")" << std::endl;
#endif // DEBUG
					mainMouse.setChooseState(true);
				}
			}
			else
			{
				mainMouse.setChooseState(false);
				mainMouse.setChoosedFigureCoordinates(-1, -1);
			}
		}
	}
}

void Application::drawRectangleOnBoard(int posX, int posY, int width, int height, Color color)
{
	DrawRectangle(leftgap + posX * gs.getCellSize(), topgap + posY * gs.getCellSize(), width, height, color);
	DrawRectangle(leftgap + posX * gs.getCellSize() + 5, topgap + posY * gs.getCellSize() + 5, width - 10, height - 10, (posX + posY) % 2 == 0 ? LIGHTGRAY : DARKGRAY);
}

void Application::drawChoosenFigureMoves()
{
	Figure* fig = findFigureByChoosedCoords();
	std::vector<Cell*>* possibleMoves = fig->getPossibleMoves(this->Figures, this->gs);
	size_t cellsize = gs.getCellSize();

	drawRectangleOnBoard(fig->getX(), fig->getY(), cellsize, cellsize, BLUE);

	for (size_t i = 0; i < possibleMoves->size(); i++)
	{
		if (possibleMoves[0][i]->isEnemy())
			drawRectangleOnBoard(possibleMoves[0][i]->getCordX(), possibleMoves[0][i]->getCordY(), cellsize, cellsize, RED);
		else
			drawRectangleOnBoard(possibleMoves[0][i]->getCordX(), possibleMoves[0][i]->getCordY(), cellsize, cellsize, GREEN);
		/*if (fig->getColor() == Figure::FigureColor::FIGURE_WHITE)
		{
			drawRectangleOnBoard(possibleMoves[0][i]->getCordX(), fig->getY() - 1, cellsize, cellsize, GREEN);
		}
		if (fig->getColor() == Figure::FigureColor::FIGURE_BLACK)
		{
			drawRectangleOnBoard(fig->getX(), fig->getY() + 1, cellsize, cellsize, GREEN);
		}*/
	}
	possibleMoves->clear();
	delete possibleMoves;

	/*if (possibleMoves->size() != 0)
	{
		
	}*/

	//if (fig == nullptr)
	//	return;
	//if (fig->getType() == Figure::FigureType::FIGURE_PAWN)
	//{
	//	if (fig->getColor() == Figure::FigureColor::FIGURE_WHITE)
	//	{
	//		drawRectangleOnBoard(fig->getX(), fig->getY() - 1, cellsize, cellsize, GREEN);
	//		if (fig->isFirstMove())
	//			drawRectangleOnBoard(fig->getX(), fig->getY() - 2, cellsize, cellsize, GREEN);
	//	}
	//	if (fig->getColor() == Figure::FigureColor::FIGURE_BLACK)
	//	{
	//		drawRectangleOnBoard(fig->getX(), fig->getY() + 1, cellsize, cellsize, GREEN);
	//		if (fig->isFirstMove())
	//			drawRectangleOnBoard(fig->getX(), fig->getY() + 2, cellsize, cellsize, GREEN);
	//	}
	//	/*DrawRectangle(leftgap + (fig->getX() - 2)* gs.getCellSize(),
	//		topgap + fig->getY() * gs.getCellSize(),
	//		gs.getCellSize(), gs.getCellSize(), GREEN);

	//	DrawRectangle(leftgap + fig->getX() * gs.getCellSize() + 5,
	//		topgap + fig->getY() * gs.getCellSize() + 5,
	//		gs.getCellSize() - 10, gs.getCellSize() - 10, (fig->getX() + fig->getY()) % 2 == 0 ? LIGHTGRAY : DARKGRAY);*/
	//}
}

void Application::movingChoosedFigure()
{
	if (mainMouse.isFigureChoosen() && mainMouse.IsButtonPressed(MOUSE_BUTTON_LEFT))
	{
		Figure* fig = findFigureByChoosedCoords();
		if (fig == nullptr)
			return;
		std::vector<Cell*>* possibleMoves = fig->getPossibleMoves(this->Figures, this->gs);

		if (possibleMoves->size() != 0)
		{
			for (size_t i = 0; i < possibleMoves->size(); i++)
			{
				if (mainMouse.getCellCoordX() == possibleMoves[0][i]->getCordX() && mainMouse.getCellCoordY() == possibleMoves[0][i]->getCordY())
				{
					fig->setFirstMove(false);
					Figure* possibleenemy = Cell::getFigureInCell(mainMouse.getCellCoordX(), mainMouse.getCellCoordY(), &Figures);
					if (possibleenemy != nullptr)
					{
						possibleenemy->setAliveMode(false);
					}
					this->lastturn->lastfigure = fig;
					this->lastturn->oldX = fig->getX();
					this->lastturn->oldY = fig->getY();
					fig->MoveTo(possibleMoves[0][i]->getCordX(), possibleMoves[0][i]->getCordY());
					mainMouse.setChooseState(false);
				}
			}
		}

		/*if (fig->getType() == Figure::FigureType::FIGURE_PAWN)
		{
			if (fig->getColor() == Figure::FigureColor::FIGURE_WHITE)
			{
				if (mainMouse.getCellCoordX() == fig->getX() && mainMouse.getCellCoordY() == fig->getY() - 1)
				{
					fig->setFirstMove(false);
					fig->MoveTo(fig->getX(), fig->getY() - 1);
					mainMouse.setChooseState(false);
				}
				if (fig->isFirstMove() && mainMouse.getCellCoordX() == fig->getX() && mainMouse.getCellCoordY() == fig->getY() - 2)
				{
					fig->setFirstMove(false);
					fig->MoveTo(fig->getX(), fig->getY() - 2);
					mainMouse.setChooseState(false);
				}
			}
			if (fig->getColor() == Figure::FigureColor::FIGURE_BLACK)
			{
				if (mainMouse.getCellCoordX() == fig->getX() && mainMouse.getCellCoordY() == fig->getY() + 1)
				{
					fig->setFirstMove(false);
					fig->MoveTo(fig->getX(), fig->getY() + 1);
					mainMouse.setChooseState(false);
				}
				if (fig->isFirstMove() && mainMouse.getCellCoordX() == fig->getX() && mainMouse.getCellCoordY() == fig->getY() + 2)
				{
					fig->setFirstMove(false);
					fig->MoveTo(fig->getX(), fig->getY() + 2);
					mainMouse.setChooseState(false);
				}
			}
		}*/
	}
}

void Application::DrawMouseSelector()
{
	int x = mainMouse.GetX();
	int y = mainMouse.GetY();

	if (x > leftgap && x < leftgap + gs.getWidthSize() * gs.getCellSize() && y > topgap && y < topgap + gs.getHeightSize() * gs.getCellSize())
	{
		size_t currentWidthButton = x / gs.getCellSize() - 1;
		size_t currentHeightButton = y / gs.getCellSize() - 1;

		mainMouse.setCellCords(currentWidthButton, currentHeightButton);

#ifdef DEBUG
		std::cout << "Mouse cell (X,Y) = (" << mainMouse.getCellCoordX() << "," << mainMouse.getCellCoordY() << ")" << std::endl;
#endif // DEBUG

		DrawRectangle(leftgap + currentWidthButton * gs.getCellSize(),
			topgap + currentHeightButton * gs.getCellSize(),
			gs.getCellSize(), gs.getCellSize(), DARKGREEN);

		DrawRectangle(leftgap + currentWidthButton * gs.getCellSize() + 5,
			topgap + currentHeightButton * gs.getCellSize() + 5,
			gs.getCellSize() - 10, gs.getCellSize() - 10, (currentWidthButton + currentHeightButton) % 2 == 0 ? LIGHTGRAY : DARKGRAY);
	}
}
void Application::DrawField()
{
	size_t cellsize = gs.getCellSize();
	for (size_t i = 0; i < gs.getWidthSize(); i++)
	{
		for (size_t j = 0; j < gs.getHeightSize(); j++)
		{
			DrawRectangle(i * cellsize + leftgap, j * cellsize + topgap, cellsize, cellsize, (i + j) % 2 == 0 ? LIGHTGRAY : DARKGRAY);
		}
	}
}

Application::Application(size_t width, size_t height, std::string& title, unsigned flags)
{
	mainWindow.SetTitle(title);
	mainWindow.SetState(flags);
	mainWindow.SetTargetFPS(60);
	screenHeight = height;
	screenWidth = width;

	this->lastturn = new LastTurn();
}

void Application::setGameSettings(size_t widthBoard, size_t heightBoard, size_t sizeOfCellInPixels, size_t countOfFigures, size_t gamemode, size_t skin)
{
	gs.setBoardSize(widthBoard, heightBoard).setCellSize(sizeOfCellInPixels).setCountOfFigures(countOfFigures).setGameMode(gamemode).setSkin(skin);

	leftgap = gs.getCellSize();
	topgap = gs.getCellSize();
}

void Application::loadFigures(const char* foldername)
{
	loadPawns(foldername);
	loadRooks(foldername);
	loadBishops(foldername);
	loadKnights(foldername);
	loadKings(foldername);
	loadQueens(foldername);
}

Application::~Application() {};
