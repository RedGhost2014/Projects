#pragma once
#ifndef _GAMESETTINGS_
#define _GAMESETTINGS_
#include <vector>

class GameSettings
{
	size_t countOfFigures;
	size_t boardSizeInWidth;
	size_t boardSizeInHeight;
	size_t sizeOfCell;

	unsigned skinType;
	unsigned mode;

public:
	GameSettings& setGameMode(unsigned mode = 0)
	{
		mode = mode;
		return *this;
	}
	GameSettings& setCountOfFigures(size_t count = 32)
	{
		countOfFigures = count;
		return *this;
	}
	GameSettings& setBoardSize(size_t width = 8, size_t height = 8)
	{
		boardSizeInHeight = height;
		boardSizeInWidth = width;
		return *this;
	}
	GameSettings& setSkin(unsigned skin = 0)
	{
		skinType = skin;
		return *this;
	}
	GameSettings& setCellSize(size_t size = 80)
	{
		sizeOfCell = size;
		return *this;
	}

	inline size_t getCellSize()
	{
		return sizeOfCell;
	}
	inline size_t getWidthSize()
	{
		return boardSizeInWidth;
	}
	inline size_t getHeightSize()
	{
		return boardSizeInHeight;
	}
	
	inline unsigned getCurrentSkin() 
	{
		return skinType; 
	};
	inline unsigned getCurrentGameMode()
	{ 
		return mode;
	};
};

#endif // !_GAMESETTINGS_
