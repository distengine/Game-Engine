#pragma once

#include "Window.h"

#include <glm/glm.hpp>


enum CameraType {
	ORTHO, FREE
};

enum CameraDirection {
	UP, DOWN, LEFT, RIGHT, FORWARD, BACK, DEFAULT
};

class Camera
{
public:
	Camera();
	~Camera();

	void reset();
	// This function updates the camera based on the projection and the mode
	void update();
	// Move the camera based on a certain direction
	void moveKeyboard();
	// Change the pitch(up,down) for the free camera
	void changePitch(float degrees);
	// Change the heading (left,right) for the free camera
	void changeHeading(float degrees);
	// Change the heading and pitch
	void processMouseMovement(Window& window);
	// This processes our mouse buttons
	void processMouseButtons();
	//----------------------------------------------------------------//
	//------------------------Set Functions--------------------------//
	//--------------------------------------------------------------//
	// Sets the mode type of the camera (ortho,free(perspective))
	void setMode(CameraType type);
	// Sets the positon of the camera
	void setPosition(glm::vec3 pos);
	// Sets the look at point for the camera
	void setLookAt(glm::vec3 pos);
	// Changes the Field of View (FOV) for the camera
	void setFOV(double fov);
	// Change the viewport location and size
	void setViewport(int locX, int locY, int width, int height);
	// Change the clipping distance for the camera
	void setClipping(double nearClipDistance, double farClipDistance);

	//----------------------------------------------------------------//
	//------------------------Get Functions--------------------------//
	//--------------------------------------------------------------//
	CameraType getMode();
	glm::vec3& getPosition() { return _cameraPos; };
	void getViewPort(int& locX, int& locY, int& width, int& height);
	void getMatrices(glm::mat4& view, glm::mat4& projection);
	float getDirection();
	bool getGrab() { return _grab; };
private:
	// This processes our keyboard input to actually do the movement - used by Camera::move()
	void processMovement(CameraDirection direction);;
private:
	CameraType _cameraType;

	int _viewportX, _viewportY, _windowX, _windowY, _lastX, _lastY;

	double _aspect, _fov, _nearClip, _farClip;

	float _cameraScale, _cameraHeading, _cameraPitch;

	float _maxPitch, _maxHeading;

	bool _moveCamera, _grab;

	glm::vec3 _cameraPos, _cameraPosDelta, _cameraLookAt, _cameraDirection, _oldCameraDirection,  _cameraUp;

	glm::mat4 _projection, _view;
};