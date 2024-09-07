#include "CBFDetectedLoser.hpp"
#include "Utils.hpp"

CBFDetectedLoser *CBFDetectedLoser::create() {
	CBFDetectedLoser *ret = new CBFDetectedLoser();
	if (ret && ret->init()) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool CBFDetectedLoser::init() {
	if (!CCNode::init())
		return false;

	this->setID("cbf-detected-loser"_spr);

	auto bg = CCScale9Sprite::create("bg.png"_spr);
	bg->setContentSize({static_cast<float>(Utils::getDouble("backgroundWidth")), 50.0f});
	bg->setAnchorPoint({0.0f, 0.0f});
	bg->setOpacity(255 * 0.56f);
	bg->setID("cbf-detected-loser-bg"_spr);

	std::string titleFontFile = adjustFontFile(Utils::getInt("titleFont"));
	std::string bodyFontFile = adjustFontFile(Utils::getInt("bodyFont"));

	std::string determinedString = "CBF Detected, loser!";
	cocos2d::ccColor3B determinedColor = ccColor3B({255, 64, 51});
	if (Utils::getBool("toneTextDown")) determinedString = "CBF Detected";
	if (Utils::getBool("toneColorDown")) determinedColor = ccColor3B({250, 237, 114});

	auto titleLabel = CCLabelBMFont::create(determinedString.c_str(), titleFontFile.c_str());
	titleLabel->setAnchorPoint({0.0f, 0.5f});
	titleLabel->setPosition({7.0f, 36.0f});
	titleLabel->setColor(determinedColor);
	titleLabel->setScale(0.6f);
	titleLabel->setID("cbf-detected-loser-title-label"_spr);

	auto bodyLabelDynamic = CCLabelBMFont::create("Click Between Frames is illegitimate and will not be allowed for use in Nullscapes.", bodyFontFile.c_str());
	bodyLabelDynamic->setAnchorPoint({0.0f, 0.5f});
	bodyLabelDynamic->setPosition({7.0f, 20.0f});
	bodyLabelDynamic->setScale(0.32f);
	bodyLabelDynamic->setID("cbf-detected-loser-body-label-dynamic"_spr);

	auto bodyLabelStatic = CCLabelBMFont::create("Please disable the mod in order to continue playing.", bodyFontFile.c_str());
	bodyLabelStatic->setAnchorPoint({0.0f, 0.5f});
	bodyLabelStatic->setPosition({7.0f, bodyLabelDynamic->getPositionY() - 10.0f});
	bodyLabelStatic->setScale(0.32f);
	bodyLabelStatic->setID("cbf-detected-loser-body-label-static"_spr);

	this->addChild(bg);
	this->addChild(titleLabel);
	this->addChild(bodyLabelDynamic);
	this->addChild(bodyLabelStatic);

	this->setPositionY(static_cast<float>(Utils::getDouble("yPosition")));
	this->setScale(static_cast<float>(Utils::getDouble("scale")));
	this->setZOrder(300);

	return true;
}

std::string CBFDetectedLoser::adjustFontFile(int64_t font) {
	if (font == -1) return "goldFont.fnt";
	if (font == -2) return "chatFont.fnt";
	if (font != 0) return fmt::format("gjFont{:02d}.fnt", font);
	return "bigFont.fnt";
}
