#include "RecordLayer.hpp"

RecordLayer* RecordLayer::create() {
    auto ret = new RecordLayer();
    if (ret->init(350, 200)) {
        ret->autorelease();
        return ret;
    };
    CC_SAFE_DELETE(ret);
    return nullptr;
};

bool RecordLayer::setup() {
    auto size = CCDirector::sharedDirector()->getWinSize();

    this->setTitle("meow!");
    this->setID("aura-record-layer");

    auto checkOffSprite = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
    auto checkOnSprite = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");

    auto menu = CCMenu::create();
    menu->setPosition({0, 0});
    menu->setID("record-layer-menu");

    auto label = CCLabelBMFont::create("Record", "bigFont.fnt");
    label->setPosition(size / 2);
    label->setScale(0.8f);
    menu->addChild(label);

    auto recordToggle = CCMenuItemToggler::create(checkOffSprite, checkOnSprite, this, menu_selector(RecordLayer::onRecord));
    recordToggle->setPosition(label->getPosition() + ccp(0, 100));
    recordToggle->setScale(0.8f);
    menu->addChild(recordToggle);

    return true;
};

void RecordLayer::onRecord(CCObject*) {
    // log::info("hi!");
};