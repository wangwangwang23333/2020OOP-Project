#ifndef _HERO_H_
#define _HERO_H_
#include "Entity.h"
#include "cocos2d.h"
#include "GameController.h"
#include "ControlListener.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio;


class Hero :public Entity, public ControlListener {
public:
	Hero();
	~Hero();
	static Hero* create(Sprite* sprite);
	bool init(Sprite* sprite);

	/*从Json文件通过id导入英雄配置*/
	static Hero* createFromJsonFile(int modelId);
	bool initFromJsonFileByID(int modelId);

	/*绑定控制器*/
	void setController(GameController* gameController);

	/* ControlListener接口方法实现*/
	virtual void setTagPosition(int x, int y);
	virtual Point getTagPosition();
	void setViewPointByHero();
	void setSafeRoomTiledMap(TMXTiledMap* map);
	
	/*行为*/
	virtual void attack(Entity* entity);
	virtual void getHurt(int hurtValue);
	virtual void deadResult();

	/*血量、蓝、防御力进度条*/
	void bindHp(LoadingBar* hpBar,Label* hpLabel,Label* hpMaxLabel);
	void bindMp(LoadingBar* mpBar,Label* mpLabel,Label* mpMaxLabel);
	void bindDefense(LoadingBar* defenseBar,Label* defenseLabel,Label* defenseMaxLabel);


	/*也可用于初始化*/
	void setHp(int hpValue);
	void setMp(int mpValue);
	void setDefense(int defenseValue);
	/*武器*/
	CC_SYNTHESIZE(int, _weapon, weapon);
private:
	GameController* _gameController;
	TMXTiledMap* _safeRoomMap;

	/*UI进度条*/
	LoadingBar* _hpLoadingBar;
	LoadingBar* _mpLoadingBar;
	LoadingBar* _defenseLoadingBar;

	/*UI数值*/
	Label* _hpLabel;
	Label* _hpMaxLabel;
	Label* _defenseLabel;
	Label* _defenseMaxLabel;
	Label* _mpLabel;
	Label* _mpMaxLabel;
	
};

#endif // !_HERO_H_