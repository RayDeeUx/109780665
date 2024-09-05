#pragma once

class CBFDetectedLoser : public cocos2d::CCNode {
protected:
	bool init();

public:
	static CBFDetectedLoser *create();
	static std::string adjustFontFile(int64_t);
};
