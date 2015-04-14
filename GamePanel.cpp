#include <stdlib.h>
#include "GamePanel.h"
#include "Piece.h"
#include "BlockGroup.h"
#include "BlockFactory.h"

#define pixel 20

GamePanel::GamePanel()
	: m_block(nullptr), gameOver(false)
{
	memset(m_data, 0, sizeof(m_data));
	memset(m_state, 0, sizeof(int) * PanelWidth * PanelHeight);
	memset(m_pieces, 0, sizeof(Piece*) * PanelWidth * PanelHeight);
}

GamePanel* GamePanel::create()
{
	GamePanel* ret = new GamePanel();
	if (ret && ret->init()) {
		ret->autorelease();
		return ret;
	}
		struct Point {
    int x;
    int y;
};
    Point p;
    p.x = 0;
    p.y = 2;
    Point* p1 = &p;
    Point* p2 = &p;
    p1 = NULL;
   // delete p1;
    CCLOG("p2 x, y [%d %d]\n", p2->x, p2->y) ;
	CC_SAFE_DELETE(ret);
	return ret;
}

bool GamePanel::init()
{
	m_origin = Director::getInstance()->getVisibleOrigin();
	for (int i = 0; i < PanelWidth; ++i) {
		for (int j = 0; j < PanelHeight; ++j) {
#if 0
			m_pieces[i][j] = Piece::create();
			if (!m_pieces[i][j]) return false;
			m_pieces[i][j]->setPosition(m_origin.x + i * pixel, m_origin.y + j * pixel);
			this->addChild(m_pieces[i][j]);
#endif
			m_pieces[i][j] = nullptr;
		}
	}

	getRandomBlock();
	this->scheduleUpdate();

	//m_nextBlocks.pop_front();
	return true;
}

void GamePanel::updatePiece(float delat)
{
	
}

bool GamePanel::checkPosition(Block* block, const JJPoint& pos)
{
	if (!block) {
		return false;
	}
#if 1//NonBinary
	int i;
	for (i = 0; i < block->pieces().size(); ++i) {
		int _x = block->pieces()[i]->offset().x + pos.x;
		int _y = block->pieces()[i]->offset().y + pos.y;
		if (0 > _x || PanelWidth <= _x || 0 > _y || PanelHeight <= _y) {
			return false;
		}
		
#if 0
		if (State_Hollow != m_pieces[_x][_y]->State()) {
			return false;
		}
#endif
		if (m_pieces[_x][_y]) {
			return false;
		}
	}

	return true;
#else
//TO DO :Binary option
#endif
}

bool GamePanel::addBlockToPanel(Block* block, const JJPoint &pos)
{
	if (!block) {
		return false;
	}

	int i;
	//bool collapse = false;
	for (i = 0; i < block->pieces().size(); ++i) {
		int x = block->pieces()[i]->offset().x + pos.x;
		int y = block->pieces()[i]->offset().y + pos.y;
		//update bitdata
		m_data[y] |= (1 >> x);
		
		m_pieces[x][y] = Piece::create();
		m_pieces[x][y]->setPosition(PIX * x, PIX * y);
		m_pieces[x][y]->setState(State_Fill);
		m_pieces[x][y]->setTexture(block->pieces()[i]->getTexture());
		//m_pieces[x][y]->setTexture(CCTextureCache::sharedTextureCache()->getTextureForKey("red.png"));
		addChild(m_pieces[x][y]);
	}
    
	getRandomBlock();
    //m_nextBlocks.pop_front();
    //m_nextBlocks.push_back(BlockGroup::instance()->getBlock());

	if (eliminateLines().size() > 0) {
		collapse();
	}

	return true;
}

std::vector<int> GamePanel::eliminateLines()
{
	std::vector<int> clearLayer;
    int h;
    int w;
	for (h = PanelHeight - 1; h >= 0; --h) {
        bool clear = true;
        for (w = 0;w < PanelWidth; w++) {
			if (!m_pieces[w][h]) {
                clear = false;
                break;
            }
        }

		if (clear) {
			clearLayer.push_back(h);
		}
    }
    
    return clearLayer;
}

bool GamePanel::elevate(unsigned int lines)
{
	return true;
}

unsigned int GamePanel::collapse()
{
    int dropLine = 0;
	int w, h;
	for (h = 0; h < PanelHeight; ++h) {
		//checkout if the line of the height be kill
		bool killed = true;
		for (w = 0; w < PanelWidth; ++w) {
			if (!m_pieces[w][h]) {
				killed = false;
				break;
			}
		}

        if (killed) {
            // play animation ~
			for (w = 0; w < PanelWidth; ++w) {
                m_pieces[w][h]->removeFromParentAndCleanup(true);
				m_pieces[w][h] = nullptr;
			}
            ++dropLine;
			continue;
        }

		if (0 == dropLine) continue;
		if (h+dropLine >= 24) break;

		for (w = 0; w < PanelWidth; ++w) {
			if (!m_pieces[w][h]) {
				m_pieces[w][h - dropLine] = nullptr;

				continue;
			}

			m_pieces[w][h]->setPositionY(m_pieces[w][h]->getPositionY() - dropLine * PIX);
			m_pieces[w][h - dropLine] = m_pieces[w][h];
		}

	}

	return dropLine;
}

void GamePanel::debug() 
{
	CCLOG("%s", __PCTYPE_FUNC);
	for (int h = 0; h < 24; ++h) {
		std::string str = "";
		for (int w = 0; w < 12; ++w)
		 {
			
			str += (m_pieces[w][h] != nullptr) ? "1" : "0";
		}
		CCLOG("%s", str.c_str());

	}
}

void GamePanel::reset()
{
	int i, j;
	for (i = 0; i < PanelWidth; ++i) {
		for (j = 0; j < PanelHeight; ++j) {
			if (m_pieces[i][j]) {
				m_pieces[i][j]->removeFromParentAndCleanup(false);
				m_pieces[i][j] = nullptr;
			}
		}
	}
}

void GamePanel::update(float delta)
{
	if (!gameOver && m_block) {
			m_block->update(delta);

		for(int w = 0; w < PanelWidth; ++w) {
			for (int h = 0; h < PanelHeight; ++h) {
				if (m_pieces[w][h]) {
					m_pieces[w][h]->update(delta);
				}
			}
		}

	}
}

bool GamePanel::down()
{
	if (gameOver) return false;
	if (m_block) {
		if (checkPosition(m_block, JJPoint(m_pos.x, m_pos.y - 1))) {
			--m_pos.y;
			m_block->setPosition(m_pos.x * PIX, m_pos.y * PIX);
			return true;
		}

		return addBlockToPanel(m_block, JJPoint(m_pos.x, m_pos.y));
	}

	return false;
}

bool GamePanel::moveLeft()
{
	if (gameOver) return false;
	if (m_block) {
		if (checkPosition(m_block, JJPoint(m_pos.x - 1, m_pos.y))) {
			--m_pos.x;
			m_block->setPosition(m_pos.x * PIX, m_pos.y * PIX);
			return true;
		}
	}

	return false;
}

bool GamePanel::moveRight()
{
	if (gameOver) return false;
	if (m_block) {
		if (checkPosition(m_block, JJPoint(m_pos.x + 1, m_pos.y))) {
			++m_pos.x;
			m_block->setPosition(m_pos.x * PIX, m_pos.y * PIX);
			return true;
		}
	}

	return false;
}

bool GamePanel::rotate(bool clockWise)
{
	if (gameOver) return false;
	m_block->rotate(clockWise, m_pos);

	if (checkPosition(m_block, m_pos)) 
		return true;

	m_block->rotate(!clockWise, m_pos); // tmp
	return false;
}

bool GamePanel::drop()
{
	if (gameOver) return false;
	int h = m_pos.y;
	for (; h >= -1; --h) {
		if (checkPosition(m_block, JJPoint(m_pos.x, h))) {
			continue;
		}

		m_pos.y = h + 1; // 考虑一上来就是不能再下移的情况
		addBlockToPanel(m_block, m_pos);
		return true;
	}

	return false;
}

void GamePanel::moveByLines(unsigned int form, unsigned int to)
{
	if (PanelHeight <= form || PanelHeight <= to) {
		return;
	}

	for (int i = 0; i < PanelWidth; ++i) {
		m_pieces[i][form]->setDestinationY(to);
	}
}

void GamePanel::getRandomBlock()
{
	//move last blocks
	if (m_block) {
		m_block->removeAllPiece();
	}

	    //获取系统时间
    struct timeval now;
    gettimeofday(&now, NULL);
	
    //初始化随机种子
    //timeval是个结构体，里边有俩个变量，一个是以秒为单位的，一个是以微妙为单位的 
    unsigned rand_seed = (unsigned)(now.tv_sec*1000 + now.tv_usec/1000);    //都转化为毫秒 
    srand(rand_seed);
	int rd = rand() % 7;

	Block_Type type = (Block_Type)( Block_Stick + rd);
    m_block = BlockFactory::create(type);

	m_pos.x = PanelWidth / 2 - 1;
	m_pos.y = PanelHeight - 2;
	if (!checkPosition(m_block, m_pos)) {
   		this->gameOverCallback();
		gameOver = true;
		return;
	}
	// offset 0,0 vs -1,-1 in actually // tmp !!!!!!!!!!!!!!!!!!!!!!!!
	m_block->setPosition((m_pos.x) * PIX, (m_pos.y) * PIX);
	for (int i = 0; i < m_block->pieces().size(); ++i) {
		this->addChild(m_block->pieces()[i]);
	}

	/*m_nextBlocks.pop_front();
	m_nextBlocks.push_back(BlockGroup::instance()->getBlock());
	/* TO DO : next block change*/
}

void GamePanel::reStart()
{
	reset();
	gameOver = false;
	init();
}

void GamePanel::tick(float delta)
{
    if (m_block) {
        if (this->down()) {
            
        }
        else {
			return;
            //game over
        }
    }
}