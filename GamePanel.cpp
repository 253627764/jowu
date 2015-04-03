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
	memset(m_pieces, 0, sizeof(Piece*) * PanelWidth * PanelHeight);
}

GamePanel* GamePanel::create()
{
	GamePanel* ret = new GamePanel();
	if (ret && ret->init()) {
		ret->autorelease();
		return ret;
	}

	CC_SAFE_DELETE(ret);
	return ret;
}

bool GamePanel::init()
{
	m_origin = Director::getInstance()->getVisibleOrigin();
	for (int i = 0; i < PanelWidth; ++i) {
		for (int j = 0; j < PanelHeight; ++j) {
			m_pieces[i][j] = Piece::create();
			if (!m_pieces[i][j]) return false;
			m_pieces[i][j]->setPosition(m_origin.x + i * pixel, m_origin.y + j * pixel);
			this->addChild(m_pieces[i][j]);
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
		
		if (State_Hollow != m_pieces[_x][_y]->State()) {
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
	for (i = 0; i < block->pieces().size(); ++i) {
		int x = block->pieces()[i]->offset().x + pos.x;
		int y = block->pieces()[i]->offset().y + pos.y;
		//update bitdata
		m_data[y] |= (1 >> x);

		m_pieces[x][y]->setState(State_Fill);
		m_pieces[x][y]->setTexture(CCTextureCache::sharedTextureCache()->getTextureForKey("red.png"));
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
            if (State_Fill != m_pieces[w][h]->State()) {
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
	debug();
    int dropLine = 0;
	int w, h;
	for (h = 0; h < PanelHeight; ++h) {
		//checkout if the line of the height be kill
		bool killed = true;
		for (w = 0; w < PanelWidth; ++w) {
			if (State_Fill != m_pieces[w][h]->State()) {
				killed = false;
				break;
			}
		}

        if (killed) {
            // play animation ~
			for (w = 0; w < PanelWidth; ++w) {
                m_pieces[w][h]->removeAllChildrenWithCleanup(true);
			}
            ++dropLine;
        }

		if (0 == dropLine) continue;
		if (h+dropLine >= 24) continue;

		for (w = 0; w < PanelWidth; ++w) {
			//m_data[h] = m_data[h + dropLine];
			//m_pieces[w][h + dropLine]->setPositionY(m_pieces[w][h]->getPositionY());
			m_pieces[w][h] = m_pieces[w][h + dropLine];
			m_pieces[w][h]->setPositionY(m_pieces[w][h]->getPositionY() - dropLine * PIX);
		}
	}

	for (h = PanelHeight - 1; h > PanelHeight - dropLine - 1; --h) {
		m_data[h] = 0;
		for (w = 0; w < PanelWidth; ++w) {
			m_pieces[w][h] = Piece::create();
			m_pieces[w][h]->setPosition(w * PIX, h * PIX);
			addChild(m_pieces[w][h]);

		}
	}

	debug();
	return dropLine;
}

void GamePanel::debug() 
{
	CCLOG("%s", __PCTYPE_FUNC);
	for (int h = 0; h < 24; ++h) {
		std::string str = "";
		for (int w = 0; w < 12; ++w)
		 {
			
			str += (m_pieces[w][h]->State() == State_Fill) ? "1" : "0";
		}
		CCLOG("%s", str.c_str());

	}
}

void GamePanel::reset()
{
	int i, j;
	for (i = 0; i < PanelHeight; ++i) {
		for (j = 0; j < PanelWidth; ++j) {
			m_pieces[i][j]->removeFromParentAndCleanup(false);
			m_pieces[i][j] = nullptr;
		}
	}
}

void GamePanel::update(float delta)
{
	if (!gameOver && m_block) {
			m_block->update(delta);

		for(int w = 0; w < PanelWidth; ++w) {
			for (int h = 0; h < PanelHeight; ++h) {
				m_pieces[w][h]->update(delta);
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
