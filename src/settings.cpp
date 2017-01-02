#include "settings.h"

Settings::Settings() {}

Settings::~Settings() {
	releaseAll();
}

void Settings::initializeTexture(Graphics *graphics) {
	if (!mutedAudioTexture.initialize(graphics, MUTED_AUDIO_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing muted audio texture"));

	if (!unmutedAudioTexture.initialize(graphics, UNMUTED_AUDIO_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing unmuted audio texture"));

	if (!mutedAudioImage.initialize(graphics, 0, 0, 0, &mutedAudioTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing muted audio image"));

	if (!unmutedAudioImage.initialize(graphics, 0, 0, 0, &unmutedAudioTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing unmuted audio image"));
}

void Settings::setInitialPosition(bool muted) {
	mutedAudioImage.setScale(SCALE_2X);
	mutedAudioImage.setX(0);
	mutedAudioImage.setY(0);

	unmutedAudioImage.setScale(SCALE_2X);
	unmutedAudioImage.setX(0);
	unmutedAudioImage.setY(0);

	if (muted)
		unmutedAudioImage.setVisible(false);
}

void Settings::update(bool muted) {	
	mutedAudioImage.setVisible(muted ? true : false);
	unmutedAudioImage.setVisible(muted ? false : true);
}

void Settings::draw() {
	mutedAudioImage.draw();
	unmutedAudioImage.draw();
}

void Settings::releaseAll() {
	mutedAudioTexture.onLostDevice();
	unmutedAudioTexture.onLostDevice();
}

void Settings::resetAll() {
	mutedAudioTexture.onResetDevice();
	unmutedAudioTexture.onResetDevice();
}