#pragma once
#include <vector>
#include "Canvas.h"
#include "Figure.h"

class GameField
{
public:
	void Resize(int width, int height);
	void Draw(Canvas& canvas);
	bool HasCollision(const Figure& figure);
	size_t Merge(const Figure& figure);

private:
	int m_Width;
	int m_Height;

	std::vector<std::vector<wchar_t>> m_Field;
};

