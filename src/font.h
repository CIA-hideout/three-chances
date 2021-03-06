#ifndef _FONT_H_
#define _FONT_H_

#include "image.h"

class Font : public Image {
public:
	Font();
	~Font();

	bool loadTextData(std::string fileName);
	bool loadTextSprite(TextureManager* texture);
	void Print(int x, int y, std::string text);
	virtual void draw();
	virtual bool initialize(Graphics *g, int width, int height, int ncols, TextureManager *textureM);
	void update(float deltaTime);

	int getTotalWidth(std::string text);

private:
	int widths[256];
};

#endif