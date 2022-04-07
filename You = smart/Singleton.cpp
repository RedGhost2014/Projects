#include "Singleton.h"

Singleton::Singleton() {}

Game* Singleton::myGame = 0;
list<Object*>* Singleton::List = 0;

// Game

Game* Singleton::getGame()
{
	if (myGame)
		return myGame;
	else return 0;
}

void Singleton::createGame()
{
	if (!myGame)
	{
		myGame = new Game;
	}
}

void Singleton::deleteGame()
{
	if (myGame)
		delete myGame;
}









// List of objects

void Singleton::createList()
{
	if (!List)
	{
		List = new list<Object*/*, allocator <Object*>*/>;
	}
}

list<Object*>* Singleton::getList()
{
	if (List)
		return List;
	else return 0;
}

void Singleton::destroyList()
{
	Object* tmpObject = 0;
	for (auto iter = Singleton::getList()->begin(); iter != Singleton::getList()->end(); iter++)
	{
		tmpObject = *iter;
		delete tmpObject;
	}
	List->clear();
	delete List;
}

void Singleton::clearList()
{
	Object* tmpObject = 0;
	for (auto iter = Singleton::getList()->begin(); iter != Singleton::getList()->end(); iter++)
	{
		tmpObject = *iter;
		delete tmpObject;
	}
	List->clear();
}