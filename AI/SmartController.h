#include "GamePanel.h"
#include <map>

USING_NS_CC;

class Guide : public Ref
{
public:
	Guide();
	~Guide();

private:
	std::map<int, JJPoint> m_actionLst;
};

class SmartController : public Ref
{
	enum SC_Type {
		SC_DEFENSE = 0,
		SC_ATTACK  = 1,
		SC_PAINTER = 2
	};

	SmartController();
	SmartController(const SmartController&);
	SmartController& operator= (const SmartController&);
public:
	SmartController(GamePanel* owner);
	~SmartController();
	void order(Guide& g);
	void setDestination(std::vector<int> dest);
private:
	void evalute(TetrisBlock* block, JJPoint pos);
};