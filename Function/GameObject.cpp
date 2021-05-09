#include "Game.h"
namespace Function {
	GameObject::GameObject(String imagePath) {
		image.loadFromFile("Images/" + imagePath);
		for (int i = 240; i < 256; i++)
			for (int j = 240; j < 256; j++)
				for (int k = 240; k < 256; k++)
					image.createMaskFromColor(Color(i, j, k));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}

	GameObject::~GameObject()
	{
	}
}