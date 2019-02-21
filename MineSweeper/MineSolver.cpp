#include "pch.h"
#include "MineSolver.h"




void MineSolver::Init( Minefield * field)
{
	_fieldHeight = field->GetHeight();
	_fieldWidth = field->GetWidth();
	_mineField = field;

	while (_mineField -> IsAllSovled())
	{
		//put flag on a certain pos
		CheckFlagPos();
		//Find a position that availiable
		int x,y;
		FindAvailiablePos(x, y);
		if(!Open(x, y))
		{
			//loss
			break;
		}
		PrintProcess();
	}
	//win
}


void MineSolver::PrintProcess()
{

}

void MineSolver::FindAvailiablePos(int& x,int& y)
{

}

void MineSolver::CheckFlagPos()
{

}

bool MineSolver::Open(unsigned int x, unsigned int y)
{
	Cell cell = _mineField->Open(x, y);

	return cell != Cell::MINE;
	
}





void MineSolver::AvailablePos()
{

}