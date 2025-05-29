#pragma once

class CBFDetectedLoser : public cocos2d::CCNode {
protected:
	bool init();

public:
	static CBFDetectedLoser* create();
	static std::string adjustFontFile(int64_t);
	void update(float dt) {
		cocos2d::CCNode* notif = Utils::getCBFDL();
		if (!notif) return;
		if (!Utils::modEnabled()) return notif->setVisible(false);
		Utils::handleCBFDL();
	}
};