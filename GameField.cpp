#include "GameField.h"

void GameField::Resize(int width, int height)
{
	m_Width = width;
	m_Height = height;
	m_Field = std::vector<std::vector<wchar_t>>(m_Height - 2, std::vector<wchar_t>(m_Width - 2, 0x0387));
}

void GameField::Draw(Canvas& canvas)
{
	for (int i = 1; i < m_Width - 1; i++) 
	{
		canvas.SetChar(i, 0, 0x2550);
		canvas.SetChar(i, m_Height - 1, 0x2550);
	}

	for (int i = 1; i < m_Height - 1; i++)
	{
		canvas.SetChar(0, i, 0x2551);
		canvas.SetChar(m_Width - 1, i, 0x2551);
	}
	
	canvas.SetChar(0, 0, 0x2554);
	canvas.SetChar(m_Width - 1, 0, 0x2557);
	canvas.SetChar(0, m_Height - 1, 0x255A);
	canvas.SetChar(m_Width - 1, m_Height - 1, 0x255D);
	
	for (int y = 0; y < m_Field.size(); y++){
		for (int x = 0; x < m_Field[y].size(); x++){
			canvas.SetChar(x + 1, y + 1, m_Field[y][x]);
		}
	}
}

bool GameField::HasCollision(const Figure& figure)
{
	Point position = figure.GetPosition();
	for (const Point& point : figure.GetBody()) {
		if (point.x + position.x < 1 || point.x + position.x > m_Width - 2) return true;
		if (point.y + position.y < 1 || point.y + position.y > m_Height - 2) return true;
		if (m_Field[point.y + position.y - 1][point.x + position.x - 1] != 0x0387) return true;
	}
	return false;
}

size_t GameField::Merge(const Figure& figure)
{
	size_t score = 0;
	Point position = figure.GetPosition();
	for (const Point& point : figure.GetBody())
	{
		m_Field[point.y + position.y - 1][point.x + position.x - 1] = 0x25D8;
	}

	for (size_t i = 0; i < m_Field.size(); ++i)
	{
		bool fool = true;
		for (size_t j = 0; j < m_Field[i].size(); ++j)
		{
			fool = fool && m_Field[i][j] != 0x0387;
		}

		if (fool)
		{
			score = 4;
			for (size_t j = i; j > 0; --j)
			{
				m_Field[j] = m_Field[j - 1];
			}
			m_Field[0] = std::vector < wchar_t >(m_Width - 2, 0x0387);
		}
	}
	return score;
}
