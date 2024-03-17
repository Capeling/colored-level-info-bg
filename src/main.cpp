#include <Geode/Geode.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>

using namespace geode::prelude;

std::unordered_map<int, ccColor3B> DIFFICULTY_COLORS = {
	{-1, {200, 200, 100}}, // Auto
	{0,  {122, 122, 122}}, // NA
	{1,  {  4,   0, 255}}, // Easy
	{2,  {  0, 180,   0}}, // Medium
	{3,  {255, 196,   0}}, // Hard
	{4,  {255, 115,   0}}, // Harder
	{5,  {255,   0, 234}}, // Insane
	{6,  {204,   0, 255}}, // Easy Demon
	{7,  {223,   0, 223}}, // Medium Demon
	{8,  {223,   0, 223}}, // Hard Demon
	{9,  {255,   0,   0}}, // Insane Demon
	{10, {175,   0,   0}}  // Extreme Demon
};
// default difficulty color is {0, 102, 255}

ccColor3B levelToColor(GJGameLevel *level) {
	// if the level is not a demon, this is in [-1, 5] 
	// (-1 is auto, 0 is NA, not the other way around for some reason)
	// if the level is a demon, this is in [1, 5]
	int average_difficulty = level->getAverageDifficulty();

	// this is 0 if the level is not a demon, and 1 otherwise
	int is_demon = level->m_demon.value();

 	// combine the two [-1, 5] and [1, 5] ranges to one [-1, 10] range
	// if not demon: [-1, 5] + 5*0 = [-1,  5]
	// if demon:     [ 1, 5] + 5*1 = [ 6, 10]
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

		CCMenuItemSpriteExtra *playBtn = dynamic_cast<CCMenuItemSpriteExtra*>(m_playBtnMenu->getChildByID("play-button"));
		CCSprite *playBtnSpr = dynamic_cast<CCSprite*>(playBtn->getChildren()->objectAtIndex(0));
		
		ccColor3B color = levelToColor(m_level);
		ccColor3B darker_color = { GLubyte(color.r/2), GLubyte(color.g/2), GLubyte(color.b/2) };

		static_cast<CCSprite*>(playBtnSpr->getChildren()->objectAtIndex(0))->setColor(darker_color);
		static_cast<CCSprite*>(playBtnSpr->getChildren()->objectAtIndex(1))->setColor(darker_color);
		static_cast<CCSprite*>(playBtnSpr->getChildren()->objectAtIndex(2))->setColor(color);
	}
};
