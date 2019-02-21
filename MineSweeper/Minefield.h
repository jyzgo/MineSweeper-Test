#pragma once
#include <vector>
using namespace std;
enum Cell {
	EMPTY,
	M1,
	M2,
	M3,
	M4,
	M5,
	M6,
	M7,
	M8,
	M9,
	MINE,
	CLOSED,
};

typedef vector<vector<Cell> > Matrix;

class Minefield {
public:

	Cell Open(unsigned int x, unsigned int y);
	Cell GetCellAt(unsigned int x, unsigned int y) const;
	Matrix GenerateMineField(unsigned int width, unsigned int height, unsigned int count);
	void PrintField(Matrix cells);
	unsigned int GetWidth();
	unsigned int GetHeight();
	bool IsAllSovled();

private:
	Matrix _cells;
	Matrix _unsolvedCells;
	unsigned int _fieldWidth;
	unsigned int _fieldHeight;
	void TryOpen(unsigned int x, unsigned int y);
	void TryOpenAdjacent(unsigned int x, unsigned int y);
	vector<Cell> GetNeighbors(int x, int y, unsigned int width, unsigned int height);
	int CalculateNumbers(const vector<Cell> &vec);

	void Init();
	bool HasMine(unsigned int x, unsigned int y);
	bool IsEmpty(unsigned int x, unsigned int y);
	
};