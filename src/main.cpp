#include <Geode/loader/SettingV3.hpp>
#include "CBFDetectedLoser.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

$on_mod(Loaded) {
	listenForSettingChanges<bool>("enabled", [](bool isEnabled) {
		cocos2d::CCNode* cbf = Utils::getCBFDL();
		if (!isEnabled && cbf) return Utils::removeCBFDL();
		if (isEnabled && !cbf) return Utils::addCBFDL();
	});
	listenForSettingChanges<double>("scale", [](double scale) {
		cocos2d::CCNode* cbf = Utils::getCBFDL();
		if (!cbf) return;
		return cbf->setScale(static_cast<float>(scale));
	});
	listenForSettingChanges<int64_t>("zOrder", [](int64_t zOrder) {
		cocos2d::CCNode* cbf = Utils::getCBFDL();
		if (!cbf) return;
		return cbf->setZOrder(static_cast<int>(zOrder));
	});
	listenForSettingChanges<int64_t>("backgroundOpacity", [](int64_t opacity) {
		cocos2d::CCNode* cbf = Utils::getCBFDL();
		if (!cbf) return;
		cocos2d::extension::CCScale9Sprite* bg = Utils::getCBFDLBG();
		if (!bg) return;
		return bg->setOpacity(static_cast<int>(opacity));
	});
	listenForSettingChanges<int64_t>("titleFont", [](int64_t fontID) {
		cocos2d::CCNode* cbf = Utils::getCBFDL();
		if (!cbf) return;
		cocos2d::CCLabelBMFont* titleLabel = Utils::getCBFDLTitle();
		if (!titleLabel) return;
		return titleLabel->setFntFile(CBFDetectedLoser::adjustFontFile(fontID).c_str());
	});
	listenForSettingChanges<int64_t>("bodyFont", [](int64_t fontID) {
		cocos2d::CCNode* cbf = Utils::getCBFDL();
		if (!cbf) return;
		cocos2d::CCLabelBMFont* bodyLabelDynamic = Utils::getCBFDLBodyDynamic();
		if (!bodyLabelDynamic) return;
		bodyLabelDynamic->setFntFile(CBFDetectedLoser::adjustFontFile(fontID).c_str());
		cocos2d::CCLabelBMFont* bodyLabelStatic = Utils::getCBFDLBodyStatic();
		if (!bodyLabelStatic) return;
		return bodyLabelStatic->setFntFile(CBFDetectedLoser::adjustFontFile(fontID).c_str());
	});
	listenForSettingChanges<bool>("toneTextDown", [](bool isToneTextDown) {
		cocos2d::CCNode* cbf = Utils::getCBFDL();
		if (!cbf) return;
		cocos2d::CCLabelBMFont* titleLabel = Utils::getCBFDLTitle();
		if (!titleLabel) return;
		std::string determinedString = "CBF Detected, loser!";
		if (isToneTextDown) {
			determinedString = "CBF Detected";
		}
		return titleLabel->setString(determinedString.c_str());
	});
	listenForSettingChanges<bool>("toneColorDown", [](bool isToneColorDown) {
		cocos2d::CCNode* cbf = Utils::getCBFDL();
		if (!cbf) return;
		cocos2d::CCLabelBMFont* titleLabel = Utils::getCBFDLTitle();
		if (!titleLabel) return;
		cocos2d::ccColor3B determinedColor = ccColor3B({255, 64, 51});
		if (isToneColorDown) {
			determinedColor = ccColor3B({250, 237, 114});
		}
		return titleLabel->setColor(determinedColor);
	});
	listenForSettingChanges<bool>("adaptiveText", [](bool isAdaptive) {
		cocos2d::CCNode* cbf = Utils::getCBFDL();
		if (!cbf) return;
		cocos2d::CCLabelBMFont* bodyLabelDynamic = Utils::getCBFDLBodyDynamic();
		if (isAdaptive) return bodyLabelDynamic->setString("Click Between Frames is illegitimate and will not be allowed for use in Nullscapes.");
	});
	listenForSettingChanges<double>("yPosition", [](double yPos) {
		cocos2d::CCNode* cbf = Utils::getCBFDL();
		if (!cbf) return;
		return cbf->setPositionY(static_cast<float>(yPos));
	});
	listenForSettingChanges<double>("backgroundWidth", [](double width) {
		cocos2d::CCNode* cbf = Utils::getCBFDL();
		if (!cbf) return;
		cocos2d::extension::CCScale9Sprite* bg = Utils::getCBFDLBG();
		if (!bg) return;
		return bg->setContentWidth(static_cast<float>(width));
	});
}
