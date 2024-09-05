#include <Geode/modify/MenuLayer.hpp>
#include "CBFDetectedLoser.hpp"
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
	struct Fields {
		Manager* manager = Manager::getSharedInstance();
	};
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		if (m_fields->manager->calledAlready)
			return true;

		m_fields->manager->calledAlready = true;

		if (auto notif = CBFDetectedLoser::create()) {
			CCScene::get()->addChild(notif);
			SceneManager::get()->keepAcrossScenes(notif);
			if (!Utils::modEnabled()) notif->setVisible(false);
		}

		return true;
	}
};