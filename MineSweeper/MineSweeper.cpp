// MineSweeper.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "Minefield.h"

int main()
{
	Minefield* f = new Minefield();
	auto gen = f->GenerateMineField(10, 20, 50);
	f->PrintField(gen);
		
	std::cin.get();
}

