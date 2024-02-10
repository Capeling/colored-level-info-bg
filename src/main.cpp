#include <Geode/Geode.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>

using namespace geode::prelude;

ccColor3B diffToColor(int diff) {
	switch(diff) {
		default: return {0, 102, 255};
		case 0: return { 122, 122, 122 };
		case 1: return { 4, 0, 255 };
		case 2: return { 0, 180, 0 };
		case 3: return { 255, 196, 0 };
		case 4: return { 255, 115, 0 };
		case 5: return { 255, 0, 234 };
		case 6: return { 204, 0, 255 };
		case 7: return { 223, 0, 223 };
		case 8:
		case 9:
		return { 255, 0, 0 };
		case 10: return { 175, 0, 0 };
	}
}

class $modify(LevelInfoLayer) {
	bool init(GJGameLevel* level, bool isGauntlet) {
		if(!LevelInfoLayer::init(level, isGauntlet))
			return false;
		CCSprite* m_background = (CCSprite*)(this->getChildByID("background"));
		auto color = diffToColor(level->getAverageDifficulty() + (level->m_demon.value() * 5));
		log::info("{}", color);
		m_background->setColor(color);
		return true;
	}
};