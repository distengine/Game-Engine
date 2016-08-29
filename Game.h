#pragma once
#include "Window.h"
#include "Camera.h"
#include "SkyBox.h"
#include "Cube.h"
#include "BoundingBox.h"
#include "Direction.h"

class Game
{
public:
	void start();
private:
	void loadSubsytems();
	void loadGLSettings();
	void gameLoop();
	void update(float dt);
	void processInput();
	void render();

	Window _window;
	Camera _camera;
	SkyBox _sky;
	Cube _cube, _cube2;
	bool _paused;
	BoundingBox _bb, _bb2;
	Direction _dir;
};
