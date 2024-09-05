#include <Geode/modify/CCScheduler.hpp>
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyCCScheduler, CCScheduler) {
	void update(float dt) {
		CCScheduler::update(dt);
		auto notif = Utils::getCBFDL();
		if (!notif) return;
		if (!Utils::modEnabled()) {
			notif->setVisible(false);
			return;
		}
		Utils::handleCBFDL();
	}
};