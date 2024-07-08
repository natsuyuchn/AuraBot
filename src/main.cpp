#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <imgui-cocos.hpp>
#include "ReplayEngine.hpp"
#include "RecordLayer.hpp"

using namespace geode::prelude;

ReplayEngine engine;
bool show = false;

class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		log::debug("Hello from my MenuLayer::init hook! This layer has {} children.", this->getChildrenCount());

		auto myButton = CCMenuItemSpriteExtra::create(
			CCSprite::createWithSpriteFrameName("GJ_likeBtn_001.png"),
			this,
			menu_selector(MyMenuLayer::onMyButton)
		);

		auto menu = this->getChildByID("bottom-menu");
		menu->addChild(myButton);

		myButton->setID("my-button"_spr);

		menu->updateLayout();

		return true;
	}

	void onMyButton(CCObject*) {
		FLAlertLayer::create("Geode", "El que lo lea es puto :3 2", "OK")->show();
	}
};

class $modify(AuraPauseLayer, PauseLayer) {
	void customSetup() {
		PauseLayer::customSetup();

		CCSprite* sprite = CCSprite::createWithSpriteFrameName("GJ_likeBtn_001.png");

		auto button = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(AuraPauseLayer::onButton));
		button->setID("aurabot"_spr);
		button->setScale(0.35f);

		auto menu = this->getChildByID("left-button-menu");
		menu->addChild(button);

		menu->updateLayout();
	};

	void onButton(CCObject*) {
		// RecordLayer::create()->show();
		// log::info("...");
		show = !show;
	};
};

$on_mod(Loaded) {
	ImGuiCocos::get().setup([] {

	}).draw([] {

		if (!show) return;

    	static auto log = "Record/Replay or Save/Load Macros!";
    	ImGui::SetNextWindowPos(ImVec2(5, 15));
    	ImGui::Begin("cheap replay bot :fire:", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);
    	ImGui::Text("El pepe uwu");

    	ImGui::SameLine();

    	int state = engine.state;

    	if (ImGui::RadioButton("Disable", &state, 0)) {
    	    engine.state = ReplayState::Disabled;
		};

    	ImGui::SameLine();

    	if (ImGui::RadioButton("Record", &state, 1)) {
    	    if (engine.state != ReplayState::Recording)
    	        engine.actions.clear();
    	    engine.state = ReplayState::Recording;
    	};

    	ImGui::SameLine();

    	if (ImGui::RadioButton("Play", &state, 2)) {
    		engine.state = ReplayState::Playing;
		};

    	ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);

		// char *macroName = engine.macroName.c_str();

    	// ImGui::InputText("##replay_name", macroName, IM_ARRAYSIZE(macroName));
	});
};