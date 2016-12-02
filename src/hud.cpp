#include "hud.h"

Hud::Hud() {}

Hud::~Hud() {
	releaseAll();
}

void Hud::initializeTexture(Graphics *graphics) {
	if (!movesHeaderTexture.initialize(graphics, MOVES_HEADER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing moves header texture"));

	if (!healthHeaderTexture.initialize(graphics, HEALTH_HEADER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing health header texture"));

	if (!enemiesLeftHeaderTexture.initialize(graphics, ENEMIES_LEFT_HEADER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemies left header texture"));

	if (!moveIconTexture.initialize(graphics, MOVE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing move icon texture"));

	if (!emptyMoveIconTexture.initialize(graphics, EMPTY_MOVE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing empty move icon texture"));

	if (!healthIconTexture.initialize(graphics, HEART_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing health icon texture"));

	if (!halfHealthIconTexture.initialize(graphics, HALF_HEART_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing half health icon texture"));

	if (!emptyHealthIconTexture.initialize(graphics, EMPTY_HEART_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing empty health icon texture"));

	if (!movesHeader.initialize(graphics, 0, 0, 0, &movesHeaderTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing moves header"));

	if (!healthHeader.initialize(graphics, 0, 0, 0, &healthHeaderTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing health header"));

	if (!enemiesLeftHeader.initialize(graphics, 0, 0, 0, &enemiesLeftHeaderTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemies left header"));

	for (int i = 0; i < PLAYER_DATA.moves; i++) {
		Image moveIcon;
		if (!moveIcon.initialize(graphics, 0, 0, 0, &moveIconTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing move icon"));

		moveIcons.push_back(moveIcon);
	}

	for (int i = 0; i < PLAYER_DATA.moves; i++) {
		Image emptyMoveIcon;
		if (!emptyMoveIcon.initialize(graphics, 0, 0, 0, &emptyMoveIconTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing empty move icon"));

		emptyMoveIcons.push_back(emptyMoveIcon);
	}

	for (int i = 0; i < PLAYER_DATA.health; i++) {
		Image healthIcon;
		if (!healthIcon.initialize(graphics, 0, 0, 0, &healthIconTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing health icon"));

		healthIcons.push_back(healthIcon);
	}

	for (int i = 0; i < PLAYER_DATA.health; i++) {
		Image halfHealthIcon;
		if (!halfHealthIcon.initialize(graphics, 0, 0, 0, &halfHealthIconTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing half health icon"));

		halfHealthIcons.push_back(halfHealthIcon);
	}

	for (int i = 0; i < PLAYER_DATA.health; i++) {
		Image emptyHealthIcon;
		if (!emptyHealthIcon.initialize(graphics, 0, 0, 0, &emptyHealthIconTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing empty health icon"));

		emptyHealthIcons.push_back(emptyHealthIcon);
	}

	initialized = true;
}

void Hud::setInitialPosition() {
	movesHeader.setScale((float)SCALE);
	movesHeader.setY(TILE_SIZE * SCALE * 6);

	healthHeader.setScale((float)SCALE);
	healthHeader.setY(TILE_SIZE * SCALE * 6);
	healthHeader.setX(TILE_SIZE * SCALE * 5);

	enemiesLeftHeader.setScale((float)SCALE);
	enemiesLeftHeader.setX(TILE_SIZE * SCALE * 5);

	for (size_t i = 0; i < moveIcons.size(); i++) {
		moveIcons[i].setScale((float)SCALE);
		moveIcons[i].setX(float(TILE_SIZE * (i) + 2));
		moveIcons[i].setY(TILE_SIZE * SCALE * 6 + 32);
	}

	for (size_t i = 0; i < emptyMoveIcons.size(); i++) {
		emptyMoveIcons[i].setScale((float)SCALE);
		emptyMoveIcons[i].setX(float(TILE_SIZE * (i)+2));
		emptyMoveIcons[i].setY(TILE_SIZE * SCALE * 6 + 32);
	}

	for (size_t i = 0; i < healthIcons.size(); i++) {
		healthIcons[i].setScale((float)SCALE);
		healthIcons[i].setX(float(TILE_SIZE * SCALE * 5 + 32 + (i) * 32));
		healthIcons[i].setY(TILE_SIZE * SCALE * 6 + 32);
	}

	for (size_t i = 0; i < halfHealthIcons.size(); i++) {
		halfHealthIcons[i].setScale((float)SCALE);
		halfHealthIcons[i].setX(float(TILE_SIZE * SCALE * 5 + 32 + (i)* 32));
		halfHealthIcons[i].setY(TILE_SIZE * SCALE * 6 + 32);
	}

	for (size_t i = 0; i < emptyHealthIcons.size(); i++) {
		emptyHealthIcons[i].setScale((float)SCALE);
		emptyHealthIcons[i].setX(float(TILE_SIZE * SCALE * 5 + 32 + (i)* 32));
		emptyHealthIcons[i].setY(TILE_SIZE * SCALE * 6 + 32);
	}
}

void Hud::resetMovesHud() {
	for (size_t i = 0; i < moveIcons.size(); i++) {
		moveIcons[i].setVisible(true);
	}
}

void Hud::update(float frameTime, Player *player) {
	if (player->getMovesLeft() > -1) {
		for (int i = moveIcons.size(); i > player->getMovesLeft(); i--) {
			moveIcons[i - 1].setVisible(false);
		}
	}

	if (player->getHealth() > -1) {
		for (int i = healthIcons.size(); i > player->getHealth(); i--) {
			healthIcons[i - 1].setVisible(false);
			if (player->getHealth() == 0.5f || player->getHealth() == 1.5f || player->getHealth() == 2.5f) {
				if (i != healthIcons.size())
					halfHealthIcons[i].setVisible(false);
				halfHealthIcons[i - 1].setVisible(true);
			}
			else {
				halfHealthIcons[i - 1].setVisible(false);
			}
		}
	}
}

void Hud::draw() {
	movesHeader.draw();
	healthHeader.draw();
	enemiesLeftHeader.draw();

	for (size_t i = 0; i < emptyMoveIcons.size(); i++) {
		emptyMoveIcons[i].draw();
	}

	for (size_t i = 0; i < moveIcons.size(); i++) {
		moveIcons[i].draw();
	}

	for (size_t i = 0; i < emptyHealthIcons.size(); i++) {
		emptyHealthIcons[i].draw();
	}

	for (size_t i = 0; i < healthIcons.size(); i++) {
		halfHealthIcons[i].draw();
		halfHealthIcons[i].setVisible(false);
	}

	for (size_t i = 0; i < healthIcons.size(); i++) {
		healthIcons[i].draw();
	}
}

void Hud::releaseAll() {
	movesHeaderTexture.onLostDevice();
	healthHeaderTexture.onLostDevice();
	enemiesLeftHeaderTexture.onLostDevice();
	moveIconTexture.onLostDevice();
	emptyMoveIconTexture.onLostDevice();
	healthIconTexture.onLostDevice();
	halfHealthIconTexture.onLostDevice();
	emptyHealthIconTexture.onLostDevice();
}

void Hud::resetAll() {
	movesHeaderTexture.onResetDevice();
	healthHeaderTexture.onResetDevice();
	enemiesLeftHeaderTexture.onResetDevice();
	moveIconTexture.onResetDevice();
	emptyMoveIconTexture.onResetDevice();
	healthIconTexture.onResetDevice();
	halfHealthIconTexture.onResetDevice();
	emptyHealthIconTexture.onResetDevice();
}
