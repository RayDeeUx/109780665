#include <Geode/modify/MenuLayer.hpp>
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

		if (!Utils::modEnabled()) return true;
		if (Utils::getCBFDL()) return true;

		Utils::addCBFDL();

		return true;
	}
};