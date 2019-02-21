#include "pch.h"
#include "Minefield.h"
#include<vector>
#include <algorithm>    // std::random_shuffle
#include <iostream>
using namespace std;

Cell Minefield::Open(unsigned int x, unsigned int y)
{
	if (x > _fieldWidth || y > _fieldHeight)
	{
		throw invalid_argument("Invalid x y");
	}
	TryOpenAdjacent(x, y);
	Cell currentCell = _unsolvedCells[y][x];
	if (currentCell == Cell::CLOSED)
	{
		Cell realCell = _cells[y][x];
		switch (realCell)
		{
		case Cell::EMPTY:
			TryOpenAdjacent(x, y);
			break;
		default:
			break;
		}
	}
	return _cells[y][x];
}



Cell Minefield::GetCellAt(unsigned int x, unsigned int y) const
{
	if (x > _fieldWidth || y > _fieldHeight)
	{
		throw invalid_argument("Invalid x y");
	}
	return _unsolvedCells[y][x];
}

Matrix  Minefield::GenerateMineField(unsigned int width, unsigned int height, unsigned int count)
{
	_fieldHeight = height;
	_fieldWidth = width;
	//count must less than width * height
	if (width * height < count)
	{
		throw invalid_argument("count must less than width * height.");
	}
	int totalNumber = width * height;

	//generate a list of Cell with centain number Mines
	vector<Cell> oneDimisonVec;
	//--push mines
	for (int i = 0; i < count; i++) {
		oneDimisonVec.push_back(MINE);
	}
	//--rest of the list are empty
	for (int i = 0; i < totalNumber - count; i++) {
		oneDimisonVec.push_back(EMPTY);
	}

	//shuffle the list of Cells
	std::random_shuffle(oneDimisonVec.begin(), oneDimisonVec.end());

	//put the cells into a 2d diminsion field
	int indexOfOriginalList = 0;
	//init cells
	for (int ny = 0; ny < height; ny++)
	{
		vector<Cell> inner;
		for (int nx = 0; nx < width; nx++)
		{
			inner.push_back(Cell::EMPTY);
		}
		_cells.push_back(inner);
	}
	for (int row = 0; row < height && indexOfOriginalList < oneDimisonVec.size(); row++)
	{
		for (int col = 0; col < width && indexOfOriginalList < oneDimisonVec.size(); col++)
		{
			_cells[row][col] = oneDimisonVec[indexOfOriginalList];
			indexOfOriginalList++;
		}
	}

	//calculate the number of cell
	for (int ny = 0; ny < height; ny++)
	{
		for (int nx = 0; nx < width; nx++)
		{
			
			Cell currentCell = _cells[ny][nx];
			if (currentCell != Cell::MINE) {
				auto neighbors = GetNeighbors(ny, nx, width, height);
				int minesCount = CalculateNumbers(neighbors);
				_cells[ny][nx] = (Cell)minesCount;
			}
		}
	}

	return _cells;
}

// GET NEIGHBORS
std::vector<Cell> Minefield::GetNeighbors(int x, int y,unsigned int width,unsigned int height)
{
	std::vector<Cell> neighbors;

	// find the x field before and after the search position and respect the
	// field bounds
	for (int ny = x - 1; ny <= x + 1; ny++)
	{
		// find the y field before and after the search position and respect
		// the field bounds
		for (int nx= y - 1; nx <= y + 1; nx++)
		{
			// do not include the x/y search tile itself
			if (( ny!= x || nx!= y) && ny>= 0 && ny< height && nx >= 0 && nx < width)
			{
				neighbors.push_back(_cells[ny][nx]);
			}
		}
	}

	return neighbors;
};

int Minefield::CalculateNumbers( const vector<Cell> &vec)
{
	
	int numMinesInNeighbors = 0;

	// find out how many mines are adjacent
	for (Cell neighborCell : vec)
	{
		if (neighborCell ==Cell::MINE)
		{
			numMinesInNeighbors++;
		}
	}

	return numMinesInNeighbors;
}

void Minefield::PrintField(Matrix cells)
{
	cout << "Start " << endl;
	for (int ny = 0; ny < cells.size(); ny++)
	{
		auto inner = cells[ny];
		for (int nx = 0; nx < inner.size(); nx++)
		{
			Cell c = inner[nx];
			switch (c)
			{
			case EMPTY:
				cout << ('.');
				break;
		
			case MINE:
				cout << ('M');
				break;
			case CLOSED:
				cout << ('C');
				break;
			default:
				cout << c;
				break;
			}
			cout << " ";
	
		}
		cout << endl;
	}

}

bool Minefield::HasMine(unsigned int x, unsigned int y)
{
	if (x > _fieldWidth || y > _fieldHeight)
	{
		throw invalid_argument("Invalid x y");
	}

	return _cells[y][x] == Cell::MINE;
}

bool Minefield::IsEmpty(unsigned int x, unsigned int y)
{
	if (x > _fieldWidth || y > _fieldHeight)
	{
		throw invalid_argument("Invalid x y");
	}

	return _cells[y][x] == Cell::EMPTY;
}

unsigned int Minefield::GetWidth()
{
	return _fieldWidth;
}

unsigned int Minefield::GetHeight()
{
	return _fieldHeight;
}

bool Minefield::IsAllSovled()
{
	for (int y = 0; y < _fieldHeight; y++)
	{
		for (int x = 0; x < _fieldWidth; x++)
		{
			if (_unsolvedCells[y][x] == Cell::CLOSED)
			{
				return false;
			}
		}
	}
	return true;
}

void Minefield::TryOpen(unsigned int x, unsigned int y)
{
	if (x >= 0 && x < _fieldWidth && y >= 0 && y < _fieldHeight)
	{
		if (_unsolvedCells[y][x] == Cell::CLOSED &&  _cells[y][x] != Cell::MINE)
		{
			_unsolvedCells[y][x] = _cells[y][x];
			if (IsEmpty(x, y)) {
				TryOpenAdjacent(x, y);
			}

		}
	}
}
void Minefield::TryOpenAdjacent(unsigned int x, unsigned int y)
{
	//up
	TryOpen(x, y - 1);
	//down
	TryOpen(x, y + 1);
	//left
	TryOpen(x - 1, y);
	//right
	TryOpen(x + 1, y);
}

void Minefield::Init()
{	for (int ny = 0; ny < _fieldHeight; ny++)
	{
		vector<Cell> inner;
		for (int nx = 0; nx < _fieldWidth; nx++)
		{
			inner.push_back(Cell::CLOSED);
		}
		_unsolvedCells.push_back(inner);
	}


}
