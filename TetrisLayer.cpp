#include "TetrisLayer.h"
#include "Piece.h"

bool TetrisLayer::init()
{
	if (!Layer::create()) {
		return false; 
	}

	loadResource();
	m_panel = GamePanel::create();
	m_panel->gameOverCallback = CC_CALLBACK_0(TetrisLayer::gameOver, this);
	Vec2 v = Director::getInstance()->getVisibleOrigin();
	m_panel->setPosition(110, 110);
	addChild(m_panel);
	schedule(schedule_selector(TetrisLayer::tick), 3);
	return true;
}

void TetrisLayer::update(float delat)
{
	if (m_panel) {
		m_panel->updatePiece(delat);
	}
}

void TetrisLayer::tick(float delta)
{
	if (m_panel) {
		m_panel->down();
	}
}

void TetrisLayer::runThisTest()
{

}

void TetrisLayer::loadResource()
{
	//for plist res
	//SpriteFrameCache::getInstance()->addSpriteFrame(
	//getSpriteFrameByName

	Director::getInstance()->getTextureCache()->addImage("darkblue.png");
	Director::getInstance()->getTextureCache()->addImage("red.png");
	Director::getInstance()->getTextureCache()->addImage("yellow.png");
	Director::getInstance()->getTextureCache()->addImage("green.png");
	Director::getInstance()->getTextureCache()->addImage("brown.png");
	Director::getInstance()->getTextureCache()->addImage("blue.png");
	Director::getInstance()->getTextureCache()->addImage("purple.png");
	Director::getInstance()->getTextureCache()->addImage("pink.png");
}

void TetrisLayer::gameOver()
{
	unschedule(schedule_selector(TetrisLayer::tick));
}