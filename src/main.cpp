#include <Geode/loader/SettingEvent.hpp>
#include "CBFDetectedLoser.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

$execute {
	listenForSettingChanges<double>("scale", [](double scale) {
		cocos2d::CCNode* cbf = Utils::getCBFDL();
		if (!cbf) return;
		return cbf->setScale(scale);
	});
	listenForSettingChanges<bool>("canonYPosition", [](bool isCanonical) {
		cocos2d::CCNode* cbf = Utils::getCBFDL();
		if (!cbf) return;
		if (isCanonical) return cbf->setPositionY(24.f);
		return cbf->setPositionY(0.f);
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
	listenForSettingChanges<bool>("toneItDown", [](bool isToneItDown) {
		cocos2d::CCNode* cbf = Utils::getCBFDL();
		if (!cbf) return;
		cocos2d::CCLabelBMFont* titleLabel = Utils::getCBFDLTitle();
		if (!titleLabel) return;
		std::string determinedString = "CBF Detected, loser!";
		cocos2d::ccColor3B determinedColor = ccColor3B({255, 64, 51});
		if (isToneItDown) {
			determinedString = "CBF Detected";
			determinedColor = ccColor3B({250, 237, 114});
		}
		titleLabel->setString(determinedString.c_str());
		return titleLabel->setColor(determinedColor);
	});
	listenForSettingChanges<bool>("adaptiveText", [](bool isAdaptive) {
		cocos2d::CCNode* cbf = Utils::getCBFDL();
		if (!cbf) return;
		cocos2d::CCLabelBMFont* bodyLabelDynamic = Utils::getCBFDLBodyDynamic();
		if (isAdaptive) return bodyLabelDynamic->setString("Click Between Frames is illegitimate and will not be allowed for use in Nullscapes.");
	});
}