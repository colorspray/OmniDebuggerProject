#include "Scene.h"
#include <stdlib.h>

Scene* Scene::scene = NULL;

Scene::Scene()
{
	width = 512;
	height = 512;
	borderWidth = 64;
	borderHeight = 64;

	Reset();
}

Scene* Scene::Instance()
{
	if (scene == NULL)
	{
		scene = new Scene();
	}
	return scene;
}

void Scene::Reset()
{
}

float Scene::getWidth()
{
	return width;
}

float Scene::getHeight()
{
	return height;
}

float Scene::getBorderWidth()
{
	return borderWidth;
}

float Scene::getBorderHeight()
{
	return borderHeight;
}