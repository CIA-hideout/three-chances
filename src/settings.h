#ifndef _SETTINGS_H
#define _SETTINGS_H

#include "textureManager.h"
#include "image.h"

class Settings {
private:
	TextureManager	mutedAudioTexture;
	TextureManager	unmutedAudioTexture;

	Image mutedAudioImage;
	Image unmutedAudioImage;

public:
	Settings();
	~Settings();

	void initializeTexture(Graphics *graphics);
	void setInitialPosition(bool muted);
	void update(bool muted);
	void draw();
	void releaseAll();
	void resetAll();
};
#endif