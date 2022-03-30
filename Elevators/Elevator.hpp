#ifndef _ELEVATORS
#define _ELEVATORS

class Elevator
{
private:
	char** field;
	short currentfloor;
	int currentTarget;
	short targetfloorOfHuman;
	short targetfloortoHuman;
	int mode;
	short floorsCount;

public:
	Elevator(short floorsCountn);
	~Elevator();

	bool move();
	char** getField();
	int getCurrentFloor();

	void ActiveState(int state);
	int isActive();
	void setTargetFloor(int floorTo, int floorOf);
};

class Observer
{
private:
	Elevator* elevators[4];

	short floorsCount;
	static void gotoxy(int x, int y);
	void CommandAnalyzer(int floorstart, int floorstop);

public:
	Observer();
	~Observer();

	void setElevators(short floorsCount);
	void _cdecl printElevators();
	void CommandListener();
};

#endif // !_ELEVATORS
