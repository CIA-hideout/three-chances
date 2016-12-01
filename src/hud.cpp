#include "hud.h"

Hud::Hud() {}

Hud::~Hud() {
	releaseAll();
}

void Hud::initializeTexture(Graphics *graphics) {
	if (!hudBgTexture.initialize(graphics, HUD_BG_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hud bg texture"));

	if (!turnIconTexture.initialize(graphics, TURN_ICON))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hud bg texture"));

	if (!hudBg.initialize(graphics, 0, 0, 0, &hudBgTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hug bg"));

	for (int i = 0; i < PLAYER_DATA.moves; i++) {
		Image turnIcon;
		if (!turnIcon.initialize(graphics, 0, 0, 0, &turnIconTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turn icon"));

		turnIcons.push_back(turnIcon);
	}

	initialized = true;
}

void Hud::setInitialPosition() {
	hudBg.setScale((float)SCALE);
	hudBg.setY(TILE_SIZE * SCALE * 7);

	for (size_t i = 0; i < turnIcons.size(); i++) {
		turnIcons[i].setScale((float)SCALE);
		turnIcons[i].setX(float(TILE_SIZE * SCALE * (1 + i)));
		turnIcons[i].setY(TILE_SIZE * SCALE * 6);
	}
}

void Hud::resetMovesHud() {
	for (size_t i = 0; i < turnIcons.size(); i++) {
		turnIcons[i].setVisible(true);
	}
}

void Hud::update(float frameTime, Player *player) {
	if (player->getMovesLeft() > -1) {
		for (int i = turnIcons.size(); i > player->getMovesLeft(); i--) {
			turnIcons[i - 1].setVisible(false);
		}
	}
}

void Hud::draw() {
	hudBg.draw();

	for (size_t i = 0; i < turnIcons.size(); i++) {
		turnIcons[i].draw();
	}
}

void Hud::releaseAll() {
	hudBgTexture.onLostDevice();
	turnIconTexture.onLostDevice();
}

void Hud::resetAll() {
	hudBgTexture.onResetDevice();
	turnIconTexture.onResetDevice();
}