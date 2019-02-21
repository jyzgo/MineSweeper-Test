#pragma once
#include "Minefield.h"
class MineSolver
{
public:
	void Init(Minefield* field);
	void AvailablePos();
	void PrintProcess();
	void FindAvailiablePos(int& x ,int& y);
	void CheckFlagPos();
	bool Open(unsigned int x, unsigned int y);
	void TryOpen(unsigned int x, unsigned int y);
private:

	unsigned int _fieldWidth;
	unsigned int _fieldHeight;
	Minefield* _mineField;
};


