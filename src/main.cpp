#include <Geode/Geode.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>

using namespace geode::prelude;

std::unordered_map<int, ccColor3B> DIFFICULTY_COLORS = {
	{-1, {200, 200, 100}},
	{0,  {122, 122, 122}},
	{1,  {  4,   0, 255}},
	{2,  {  0, 180,   0}},
	{3,  {255, 196,   0}},
	{4,  {255, 115,   0}},
	{5,  {255,   0, 234}},
	{6,  {204,   0, 255}},
	{7,  {223,   0, 223}},
	{8,  {223,   0, 223}},
	{9,  {255,   0,   0}},
	{10, {175,   0,   0}}
};

ccColor3B levelToColor(GJGameLevel *level) {
	int average_difficulty = level->getAverageDifficulty();
	int is_demon = level->m_demon.value();
	return DIFFICULTY_COLORS[average_difficulty + 5*is_demon];
}

class $modify(LevelInfoLayer) {
	bool init(GJGameLevel* level, bool p1) {
		if(!LevelInfoLayer::init(level, p1)) return false;

		CCSprite* m_background = (CCSprite*)(this->getChildByID("background"));
		ccColor3B color = levelToColor(level);
		m_background->setColor(color);

		return true;
	}

	void onPlay(CCObject *sender) {
		LevelInfoLayer::onPlay(sender);

		CCMenuItemSpriteExtra *playBtn = static_cast<CCMenuItemSpriteExtra*> (m_playBtnMenu->getChildByID("play-button"));
		CCSprite *playBtnSpr = getChild<CCSprite>(playBtn, 0);
		
		ccColor3B color = levelToColor(m_level);
		ccColor3B darker_color = { GLubyte(color.r/2), GLubyte(color.g/2), GLubyte(color.b/2) };
		
		if (playBtnSpr->getChildrenCount()) {
			getChildOfType<CCSprite>(playBtnSpr, 0)->setColor(darker_color);
			getChildOfType<CCSprite>(playBtnSpr, 1)->setColor(darker_color);
			getChildOfType<CCSprite>(playBtnSpr, 2)->setColor(color);
		}
	}
};
