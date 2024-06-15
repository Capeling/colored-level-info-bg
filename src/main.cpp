#include <Geode/Geode.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>

using namespace geode::prelude;

ccColor3B diffToColor(int diff) {
	switch(diff) {
		default: return {0, 102, 255};
		case -1: return { 255, 162, 48 };
		case 0: return { 122, 122, 122 };
		case 1: return { 4, 0, 255 };
		case 2: return { 0, 180, 0 };
		case 3: return { 255, 196, 0 };
		case 4: return { 255, 115, 0 };
		case 5: return { 183, 0, 183 };
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
		
		CCSprite* bg = getChildOfType<CCSprite>(this, 0);

		int averageDiff = level->getAverageDifficulty();

		if (level->m_autoLevel) {
			auto autoGradient = CCLayerGradient::create({ 255, 235, 51, 255 }, { 0, 197, 227, 255 });
			bg->setColor({ 138, 138, 138 });
			addChild(autoGradient, -2);
		}
		else {
			auto color = diffToColor(averageDiff + (level->m_demon.value() * 5));
			bg->setColor(color);
		}
		return true;
	}
	void playStep2() {
		LevelInfoLayer::playStep2();
		auto color = diffToColor(m_level->m_autoLevel ? -1 : m_level->getAverageDifficulty() + (m_level->m_demon.value() * 5));
		ccColor3B darkerColor = { color.r / 2, color.g / 2, color.b / 2 };

		getChildOfType<CCSprite>(m_playSprite, 0)->setColor(darkerColor);
		getChildOfType<CCSprite>(m_playSprite, 1)->setColor(color);
		getChildOfType<CCSprite>(m_playSprite, 2)->setColor(darkerColor);
		
	}
};