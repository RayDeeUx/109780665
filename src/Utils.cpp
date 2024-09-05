#include "Utils.hpp"

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

	cocos2d::CCNode* getCBFDL(cocos2d::CCScene* scene) {
		if (cocos2d::CCNode* cbf = scene->getChildByIDRecursive("cbf-detected-loser"_spr)) return cbf;
		return nullptr;
	}

	cocos2d::CCLabelBMFont* getCBFDLTitle(cocos2d::CCScene* scene) {
		if (cocos2d::CCLabelBMFont* title = typeinfo_cast<CCLabelBMFont*>(getCBFDL(scene)->getChildByIDRecursive("cbf-detected-loser-title-label"_spr))) return title;
		return nullptr;
	}

	cocos2d::CCLabelBMFont* getCBFDLBodyDynamic(cocos2d::CCScene* scene) {
		if (cocos2d::CCLabelBMFont* bodyDynamic = typeinfo_cast<CCLabelBMFont*>(getCBFDL(scene)->getChildByIDRecursive("cbf-detected-loser-body-label-dynamic"_spr))) return bodyDynamic;
		return nullptr;
	}

	cocos2d::CCLabelBMFont* getCBFDLBodyStatic(cocos2d::CCScene* scene) {
		if (cocos2d::CCLabelBMFont* bodyStatic = typeinfo_cast<CCLabelBMFont*>(getCBFDL(scene)->getChildByIDRecursive("cbf-detected-loser-body-label-static"_spr))) return bodyStatic;
		return nullptr;
	}

	void handleCBFDL(cocos2d::CCScene* scene) {
		if (cocos2d::CCNode* cbf = getCBFDL()) {
			std::string resultString = "Click Between Frames is illegitimate and will not be allowed for use ";
			if (auto* bodyLabelDynamic = getCBFDLBodyDynamic()) {
				if (auto gjbgl = getChildOfType<GJBaseGameLayer>(scene, 0)) {
					const auto lel = typeinfo_cast<LevelEditorLayer*>(gjbgl);
					const auto pl = typeinfo_cast<PlayLayer*>(gjbgl);
					if (!gjbgl->m_level) {
						std::string activity = "playing";
						if (lel) activity = "editing";
						resultString = resultString.append(fmt::format("while {} this level.", activity));
					} else {
						resultString = resultString.append(fmt::format("in {}.", gjbgl->m_level->m_levelName));
					}
					if (pl) {
						std::string playLayerVisibility = Utils::getString("visibilityInPlayLayer");
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
						if (Utils::getBool("hideInLevelEditorLayer")) cbf->setVisible(false);
						else cbf->setVisible(true);
					}
				} else {
					resultString = resultString.append("in GD.");
					if (Utils::getBool("hideEverywhereElse")) cbf->setVisible(false);
					else cbf->setVisible(true);
				}
				if (Utils::getBool("adaptiveText")) bodyLabelDynamic->setString(resultString.c_str());
				else bodyLabelDynamic->setString("Click Between Frames is illegitimate and will not be allowed for use in Nullscapes.");
			}
		}
	}
}