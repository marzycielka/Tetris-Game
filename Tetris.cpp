#include "Tetris.h"
#include <string>

Tetris::Tetris() : m_Figure(Point(5, 1))
				 , m_NextFigure(Point(15, 1))
{
	m_GameField.Resize(14, 26);
	m_Canvas.Resize(26, 20);
}

void Tetris::OnKeyPressed(int btnCode)
{
	m_Figure.Backup();
	switch (btnCode)
	{
	case 32:
		m_Figure.Rotate();
		break;
	case 75:
		m_Figure.MoveL();
		break;
	case 77:
		m_Figure.MoveR();
		break;
	case 80:
		m_Figure.Boost();
		return;
	default: 
		break;
	}

	if (m_GameField.HasCollision(m_Figure)) {
		m_Figure.Restore();
	}
}

void Tetris::Update(double dt)
{
	m_Figure.Backup();
	m_Figure.Update(dt);
	if (m_GameField.HasCollision(m_Figure)) 
	{
		m_Figure.Restore();
		m_Score += m_GameField.Merge(m_Figure);
		if (m_Score > 999999) m_Score = 999999;
		m_Figure = m_NextFigure;
		m_Figure.SetPosition(Point(5, 1));
		m_NextFigure = Figure(Point(15, 1));
		if (m_GameField.HasCollision(m_Figure))
		{
			m_End = true;
		}
	}

	m_Canvas.Clear();
	m_GameField.Draw(m_Canvas);
	m_Figure.Draw(m_Canvas);
	m_NextFigure.Draw(m_Canvas);
	DrawScore(m_Canvas);
	m_Canvas.Render();
}

bool Tetris::End()
{
	return m_End;
}

void Tetris::DrawScore(Canvas& canvas)
{
	std::string score = std::to_string(m_Score);

	m_Canvas.SetChar(14, 4, 'S');
	m_Canvas.SetChar(15, 4, 'C');
	m_Canvas.SetChar(16, 4, 'O');
	m_Canvas.SetChar(17, 4, 'R');
	m_Canvas.SetChar(18, 4, 'E');
	m_Canvas.SetChar(19, 4, ':');
	for (size_t i = 0; i < score.size(); ++i)
	{
		m_Canvas.SetChar(14 + i, 5, score[i]);
	}
}
