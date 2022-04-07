#pragma once
#include <list>
#include "Declarator.h"

class Singleton
{
private:

	static list<Object*>* List;
	static Game* myGame;

	Singleton(const Singleton& root) = delete;
	Singleton& operator=(const Singleton&) = delete;

public:

	static Game* getGame();
	static void createGame();
	static void deleteGame();

	static void createList();
	static list<Object*>* getList();
	static void destroyList();
	static void clearList();

protected:
	Singleton();
};