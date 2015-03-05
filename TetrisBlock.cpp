#include "TetrisBlock.h"
#include "TetrisDef.h"

TetrisBlock::TetrisBlock(Block_Type shape, Color_Type color,
             unsigned int maxChangeTime, const std::vector<JJPoint>& lst)
	: m_shape(shape),
	m_color(color),
	m_maxChangeTime(maxChangeTime) {
    memset(m_bitData, 0, 4);
    for (int i = 0; i < lst.size(); ++i) {
        m_bitData[lst[i].x + 2] |=  1 << (lst[i].y + 2);
		Piece* piece = Piece::create(color, lst[i]);
		if (!piece) {
			printf("create piece failed!!\n");
		}

		m_pieces.push_back(piece);
    }
}

int* TetrisBlock::bitData()
{
    return m_bitData;
}

//aglortihm: clockwise(x1=y, y1=x) 
//anitclockwise(x1=-y, y1=x)
TetrisBlock* TetrisBlock::rotate(bool clockWise)
{
	for (int i = 0; i < m_pieces.size(); ++i) {
		m_pieces[i]->setOffset(m_pieces[i]->offset().x,
			(clockWise? 1 : -1) * m_pieces[i]->offset().y);
	}

	return this;
}

bool TetrisBlock::locate(int x, int y)
{
	for (int i = 0; i < m_pieces.size(); ++i) {
		m_pieces[i]->setContentSize(Size(0, 0));

		//m_pieces[i]->setContentSize(Size(PIX * (m_pieces[i]->offset().x + x),
			//PIX * (m_pieces[i]->offset().y + y)));
	}

	return true;
}