#pragma once

using namespace geode::prelude;

namespace Utils {
	template<class T> T getSetting(std::string setting, T type);
	bool getBool(std::string setting);
	int64_t getInt(std::string setting);
	double getDouble(std::string setting);
	std::string getString(std::string setting);
	ccColor3B getColor(std::string setting);
	ccColor4B getColorAlpha(std::string setting);
	bool modEnabled();
	
	bool isModLoaded(std::string modID);
	Mod* getMod(std::string modID);
	std::string getModVersion(Mod* mod);

	cocos2d::CCNode* getCBFDL(cocos2d::CCScene* scene = CCDirector::get()->getRunningScene());
	cocos2d::CCLabelBMFont* getCBFDLTitle(cocos2d::CCScene* scene = CCDirector::get()->getRunningScene());
	cocos2d::CCLabelBMFont* getCBFDLBodyDynamic(cocos2d::CCScene* scene = CCDirector::get()->getRunningScene());
	cocos2d::CCLabelBMFont* getCBFDLBodyStatic(cocos2d::CCScene* scene = CCDirector::get()->getRunningScene());
	cocos2d::extension::CCScale9Sprite* getCBFDLBG(cocos2d::CCScene* scene = CCDirector::get()->getRunningScene());
	void handleCBFDL(cocos2d::CCScene* scene = CCDirector::get()->getRunningScene());
}