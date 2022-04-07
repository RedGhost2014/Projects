#pragma once
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <Windows.h>
#include "Object.h"
#include "Field.h"
#include "Game.h"
#include "Singleton.h"
#include "Comparser.h"

BOOL ShowConsoleCursor(BOOL bShow);
void gotoxy(int x, int y);