#ifndef _SCENE_H_
#define _SCENE_H_

class Scene
{
private:
	float width;
	float height;
	float borderWidth;
	float borderHeight;
	
	static Scene* scene;
	Scene();

public:
	static Scene* Instance();
	void Reset();
	float getWidth();
	float getHeight();
	float getBorderWidth();
	float getBorderHeight();
};


#endif