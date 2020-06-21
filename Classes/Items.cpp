#include "Items.h"
#include "SafeRoomScene.h"
#include "Knife.h"
#include "gun.h"
#include "QuickGun.h"
#include "DialogManager.h"
Items::Items() :_sprite(nullptr) {

};

Items::~Items() {

}

bool Items::init() {
	if (!Node::init()) {
		return false;
	}

	return true;
}

Items* Items::createItems(int itemsTag, Point position) {
	Items* items = Items::create();
	/*��������*/
	std::string spritePath = StringUtils::format("Items_%d.png", itemsTag);
	items->_sprite = Sprite::create(spritePath);
	items->addChild(items->_sprite);

	/*��������*/
	items->setTag(itemsTag);

	/*�ڴ������ı�*/
	switch (itemsTag)
	{
	case KNIFE_TAG:
	{
		break;
	}
	case GUN_TAG:
	{
		Label* label = Label::create("С���ӣ�\n����ĺ��о���", "Arial", 24);
		
		items->addChild(label);
		break;
	}
	case QUICKGUN_TAG:
	{
		Label* label = Label::create("С���ӣ�\n����ĺ��о���", "Arial", 24);
		items->addChild(label);
		break;
	}
	}

	/*����������Χ�ж�*/
	if (items->getTag() == BAOXIANG_TAG)
	{
		Size size = items->_sprite->getContentSize();
		size.width += 20;
		size.height += 20;
		items->setContentSize(size);
		items->setAnchorPoint(Point(0, 0));
	}
	else
	{
		items->setContentSize(items->_sprite->getContentSize());
		items->setAnchorPoint(Point(0, 0));
	}

	/*���õ���λ��,��ͼ���ȡ*/
	items->setPosition(position);

	/*�����ｻ��*/
	items->keyBoard_k_register();

	/*ע�����¼�*/
	if (itemsTag == BS_TAG || itemsTag == JB_TAG)
		items->scheduleUpdate();

	return items;
}

void Items::keyBoard_k_register() {
	auto keyBoardListener = EventListenerKeyboard::create();

	keyBoardListener->onKeyPressed= [&](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_K:  //k
			if (this->getBoundingBox().intersectsRect(SafeRoomScene::_hero->getBoundingBox())) {
				effectOfItems(this->getTag());
				{
					//��������Ʒ���ڱ��䣬����Ҫ���գ��������ͼƬ����
					if (this->getTag()==BAOXIANG_TAG)
					{
						Sprite* newSprite = Sprite::create("Items_9.png");
						this->_sprite->removeFromParentAndCleanup(true);
						this->_sprite = newSprite;
						this->addChild(this->_sprite);
						//���������滻
						this->setTag(OPENED_BAOXIANG_TAG+0);
					}
					else if (this->getTag()!=OPENED_BAOXIANG_TAG+0)
					{
						this->removeFromParentAndCleanup(true);
					}
				}
		}
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, this);

}

void Items::effectOfItems(int itemsTag) {
	switch (itemsTag) {
	case HP_ADD_TAG:
		GlobalParameter::hero->setHp(GlobalParameter::hero->gethp() + HP_ADD_NUM);
		log("hp add\n");
		break;
	case MP_ADD_TAG:
		GlobalParameter::hero->setMp(GlobalParameter::hero->getmp() + MP_ADD_NUM);
		log("mp add\n");
		break;
	case KNIFE_TAG:
	{
		//��������
		this->throwWeapon();
		//����������Ϊ��
		HitController* hitContro = HitController::create();
		Knife* knife = new Knife(hitContro, 3, "ذ��");
		GlobalParameter::hero->setWeapon(knife);
		break;
	}
	case GUN_TAG:
	{
		//��������
		this->throwWeapon();
		//����������Ϊǹ֧
		Gun* gun = new Gun(3, "ǹ֧");
		GlobalParameter::hero->setWeapon(gun);
		break;
	}
	case QUICKGUN_TAG:
	{
		//��������
		this->throwWeapon();
		//����������Ϊ���ǹ
		QuickGun *quickGun = new QuickGun(2, "���ǹ");
		GlobalParameter::hero->setWeapon(quickGun);
		
		break;
	}
	case BAOXIANG_TAG:
		//����
	{
		//�򿪱���
		//���һ������
		double randomItem = CCRANDOM_0_1();
		//ȷ������
		if (randomItem < 0.2f)
		{
			Items* item = Items::createItems(HP_ADD_TAG, GlobalParameter::hero->getPosition());
			GlobalParameter::mapNow->getParent()->addChild(item, 2);
		}
		else if (randomItem < 0.4f)
		{
			Items* item = Items::createItems(MP_ADD_TAG, GlobalParameter::hero->getPosition());
			GlobalParameter::mapNow->getParent()->addChild(item, 2);
		}
		else if (randomItem < 0.6f)
		{
			Items* item = Items::createItems(GUN_TAG, GlobalParameter::hero->getPosition());
			GlobalParameter::mapNow->getParent()->addChild(item, 2);
		}
		else if (randomItem < 0.7f)
		{
			Items* item = Items::createItems(QUICKGUN_TAG, GlobalParameter::hero->getPosition());
			GlobalParameter::mapNow->getParent()->addChild(item, 2);
		}
		else if (randomItem < 0.9f)
		{
			Items* item = Items::createItems(KNIFE_TAG, GlobalParameter::hero->getPosition());
			GlobalParameter::mapNow->getParent()->addChild(item, 2);
		}
		else
		{
			//������

		}

		break;
	}
	//OPENED_BAOXIANG_TAG����Ҫ��������
	}
}

void Items::update(float dt) {
	int tag = this->getTag();
	
	if (this->getBoundingBox().intersectsRect(SafeRoomScene::_hero->getBoundingBox())) {
		switch (tag) {
		case BS_TAG: {
			/*��ʯ���Ӳ���to do*/
			MoveTo* moveToBS = MoveTo::create(0.1f, SafeRoomScene::_hero->getPosition());
			this->runAction(moveToBS);
			this->removeFromParentAndCleanup(true);
			log("bs add\n");
			break; }
		case JB_TAG: {
			/*������Ӳ���to do*/
			MoveTo* moveToJB = MoveTo::create(0.1f, SafeRoomScene::_hero->getPosition());
			this->runAction(moveToJB);
			this->removeFromParentAndCleanup(true);
			log("jb add\n");
			break; }
		}
	}
}

void Items::throwWeapon()
{
	//����֮ǰ������
	Weapon* weapon = GlobalParameter::hero->removeWeapon();
	if (weapon == nullptr)
		return;
	//������������
	CCString weaponType = typeid(*weapon).name();
	//ȷ����������
	if (weaponType._string == "class Gun")
	{
		Items* item = Items::createItems(GUN_TAG,GlobalParameter::hero->getPosition());
		GlobalParameter::mapNow->getParent()->addChild(item, 2);
	}
	else if (weaponType._string == "class Knife")
	{
		Items* item = Items::createItems(KNIFE_TAG, GlobalParameter::hero->getPosition());
		GlobalParameter::mapNow->getParent()->addChild(item, 2);
	}
	else if (weaponType._string == "class QuickGun")
	{
		Items* item = Items::createItems(QUICKGUN_TAG, GlobalParameter::hero->getPosition());
		GlobalParameter::mapNow->getParent()->addChild(item, 2);
	}
}