#include "Utils.hpp"
#include "Manager.hpp"
#include "CBFDetectedLoser.hpp"

namespace Utils {
	template<class T> T getSetting(std::string setting) { return Mod::get()->getSettingValue<T>(setting); }

	bool getBool(std::string setting) { return getSetting<bool>(setting); }
	
	int64_t getInt(std::string setting) { return getSetting<int64_t>(setting); }
	
	double getDouble(std::string setting) { return getSetting<double>(setting); }

	std::string getString(std::string setting) { return getSetting<std::string>(setting); }

	ccColor3B getColor(std::string setting) { return getSetting<ccColor3B>(setting); }

	ccColor4B getColorAlpha(std::string setting) { return getSetting<ccColor4B>(setting); }

	bool modEnabled() { return getBool("enabled"); }
	
	bool isModLoaded(std::string modID) { return Loader::get()->isModLoaded(modID); }

	Mod* getMod(std::string modID) { return Loader::get()->getLoadedMod(modID); }

	std::string getModVersion(Mod* mod) { return mod->getVersion().toNonVString(); }

	cocos2d::CCNode* getCBFDL() {
		return Manager::getSharedInstance()->cbfdl;
	}

	cocos2d::CCLabelBMFont* getCBFDLTitle() {
		return static_cast<CCLabelBMFont*>(getCBFDL()->getChildByID("cbf-detected-loser-title-label"_spr));
	}

	cocos2d::CCLabelBMFont* getCBFDLBodyDynamic() {
		return static_cast<CCLabelBMFont*>(getCBFDL()->getChildByID("cbf-detected-loser-body-label-dynamic"_spr));
	}

	cocos2d::CCLabelBMFont* getCBFDLBodyStatic() {
		return static_cast<CCLabelBMFont*>(getCBFDL()->getChildByID("cbf-detected-loser-body-label-static"_spr));
	}

	cocos2d::extension::CCScale9Sprite* getCBFDLBG() {
		return static_cast<CCScale9Sprite*>(getCBFDL()->getChildByID("cbf-detected-loser-bg"_spr));
	}

	void handleCBFDL() {
		if (!Utils::modEnabled()) return Utils::removeCBFDL();
		const auto gjbgl = GJBaseGameLayer::get();
		const auto lel = LevelEditorLayer::get();
		const auto pl = PlayLayer::get();
		cocos2d::CCNode* cbf = getCBFDL();
		if (cbf && getBool("hideEverywhereElse") && !pl && !lel) cbf->setVisible(false);
		if (cbf && getBool("hideInLevelEditorLayer") && lel) return removeCBFDL();
		if (!cbf && getBool("hideInLevelEditorLayer") && !lel) {
			addCBFDL();
			cbf = getCBFDL();
		}
		const auto bodyLabelDynamic = getCBFDLBodyDynamic();
		if (!bodyLabelDynamic) return;
		std::string resultString = "Click Between Frames is illegitimate and will not be allowed for use ";
		if (gjbgl) {
			if (!gjbgl->m_level) {
				std::string activity = "playing";
				if (lel) activity = "editing";
				resultString = resultString.append(fmt::format("while {} this level.", activity));
			} else {
				resultString = resultString.append(fmt::format("in {}.", gjbgl->m_level->m_levelName));
			}
			if (pl) {
				std::string playLayerVisibility = getString("visibilityInPlayLayer");
				if (playLayerVisibility.starts_with("Always ")) {
					if (playLayerVisibility == "Always Visible") cbf->setVisible(true);
					else if (playLayerVisibility == "Always Hidden") cbf->setVisible(false);
				} else if (playLayerVisibility.starts_with("Only ") && playLayerVisibility.ends_with(" When Dead")) {
					if (auto player = pl->m_player1) {
						bool onlyShowWhenDead = playLayerVisibility == "Only Show When Dead";
						bool onlyHideWhenDead = playLayerVisibility == "Only Hide When Dead";
						if (player->m_isDead) {
							if (onlyShowWhenDead) cbf->setVisible(true);
							else if (onlyHideWhenDead) cbf->setVisible(false);
						} else {
							if (onlyShowWhenDead) cbf->setVisible(false);
							else if (onlyHideWhenDead) cbf->setVisible(true);
						}
					}
				}
			} else if (lel) {
				if (getBool("hideInLevelEditorLayer")) removeCBFDL();
				else addCBFDL();
			}
		} else {
			resultString = resultString.append("in GD.");
			if (getBool("hideEverywhereElse")) removeCBFDL();
			else addCBFDL();
		}
		if (getBool("adaptiveText")) bodyLabelDynamic->setString(resultString.c_str());
		else bodyLabelDynamic->setString("Click Between Frames is illegitimate and will not be allowed for use in Nullscapes.");
	}

	void addCBFDL() {
		auto cbf = getCBFDL();
		if (cbf) return cbf->setVisible(true);
		auto cbfdl = CBFDetectedLoser::create();
		if (!cbfdl) return;
		CCScene::get()->addChild(cbfdl);
		SceneManager::get()->keepAcrossScenes(cbfdl);
		cbfdl->setVisible(true);
		Manager::getSharedInstance()->cbfdl = cbfdl;
		if (Utils::getBool("logging")) log::info("CBFDL node added");
	}

	void removeCBFDL() {
		auto cbfdl = Utils::getCBFDL();
		if (!cbfdl) return;
		SceneManager::get()->forget(cbfdl);
		Manager::getSharedInstance()->cbfdl = nullptr;
		cbfdl->removeMeAndCleanup();
		if (Utils::getBool("logging")) log::info("CBFDL node removed");
	}
}
