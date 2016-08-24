#include "Camera.h"

#include <gl/glew.h>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>


Camera::Camera(): _viewportX(0), _viewportY(0), _windowX(1920), _windowY(1080), _lastX(0), _lastY(0), _aspect(1), _nearClip(.1f), _farClip(1000.0f), _cameraHeading(0), _cameraPitch(0), _grab(false)
{
	_cameraType = CameraType::FREE;
	_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	_fov = 45.0f;
	_cameraPosDelta = glm::vec3(0);
	_cameraScale = 0.03f;
	_maxPitch = 5;
	_maxHeading = 5;
	_moveCamera = false;

}

Camera::~Camera()
{
}

void Camera::reset()
{
	_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::update()
{
	_oldCameraDirection = _cameraDirection;
	_cameraDirection = glm::normalize(_cameraLookAt - _cameraPos);
	// We need to set the matrix state, this is important because lighting won't work otherwise
	glViewport(_viewportX, _viewportY, _windowX, _windowY);

	if(_cameraType == CameraType::ORTHO)
	{
		_projection = glm::ortho(-1.5f * float(_aspect), 1.5f * float(_aspect), -1.5f, 1.5f, -10.0f, 10.0f);
	}
	else
	{
		_projection = glm::perspective(_fov, _aspect, _nearClip, _farClip);
		// Axis for pitch rotation
		glm::vec3 axis = glm::cross(_cameraDirection, _cameraUp);
		// Compute quaternion for pitch based on the camera pitch angle
		glm::quat pitchQuat = glm::angleAxis(_cameraPitch, axis);
		// Determine heading quaternion from the camera up vector and the heading angle
		glm::quat headingQuat = glm::angleAxis(_cameraHeading, _cameraUp);
		// Add the two quats
		glm::quat tempQuat = glm::cross(pitchQuat, headingQuat);
		tempQuat = glm::normalize(tempQuat);
		// Update the direction from the quaternion 
		_cameraDirection = glm::rotate(tempQuat, _cameraDirection);
		// add the camera delta
		_cameraPos += _cameraPosDelta;
		// set the lookat matrix to be infront of the camera
		_cameraLookAt = _cameraPos + _cameraDirection * 1.0f;
		// Damping for smooth camera
		_cameraHeading *= 0.5f;
		_cameraPitch *= 0.5f;
		_cameraPosDelta *= 0.8f;
	}
	// compute the mvp
	_view = glm::lookAt(_cameraPos, _cameraLookAt, _cameraUp);
}

void Camera::moveKeyboard()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		processMovement(UP);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		processMovement(DOWN);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		processMovement(LEFT);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		processMovement(RIGHT);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		processMovement(FORWARD);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		processMovement(BACK);
}

void Camera::changePitch(float degrees)
{
	//Check bounds with the max pitch rate so that we aren't moving too fast
	if(degrees < -_maxPitch)
	{
		degrees = -_maxPitch;
	}
	else if(degrees > _maxPitch)
	{
		degrees = _maxPitch;
	}
	_cameraPitch += degrees;
	// Check bounds for cameraPitch
	if(_cameraPitch > 360.0f)
	{
		_cameraPitch -= 360.0;
	}
	else if(_cameraPitch < -360.0f)
	{
		_cameraPitch += 360.0f;
	}
}

void Camera::changeHeading(float degrees)
{
	//Check bounds with the max Heading rate so that we aren't moving too fast
	if (degrees < -_maxHeading)
	{
		degrees = -_maxHeading;
	}
	else if (degrees > _maxHeading)
	{
		degrees = _maxHeading;
	}
	_cameraHeading += degrees;

	// This controls how the heading is changed if the camera is pointed straight up or down
	// The heading delta direction changes
	if (_cameraPitch > 90 && _cameraPitch < 270 || (_cameraPitch < -90 && _cameraPitch > -270)) 
	{
		_cameraHeading -= degrees;
	}
	else 
	{
		_cameraHeading += degrees;
	}

	// Check bounds for cameraHeading
	if (_cameraHeading > 360.0f)
	{
		_cameraHeading -= 360.0f;
	}
	else if (_cameraHeading < -360.0f)
	{
		_cameraHeading += 360.0f;
	}
}

void Camera::processMouseMovement(Window& window)
{
	auto mousePos = window.getMousePos();
	if (_lastX == 0 && _lastY == 0)
	{
		_lastX = _windowX / 2;
		_lastY = _windowY / 2;
	}
	if (mousePos != glm::ivec2(_lastX, _lastY))
	{
		GLfloat xOffset = static_cast<GLfloat>(_windowX / 2) - static_cast<GLfloat>(mousePos.x);
		GLfloat yOffset = static_cast<GLfloat>(_windowY / 2) - static_cast<GLfloat>(mousePos.y);
		xOffset *= _cameraScale;
		yOffset *= _cameraScale;
		if (_moveCamera)
		{
			changeHeading(.08f * xOffset);
			changePitch(.08f * yOffset);
		}
	}
	window.centerMouse();
}

void Camera::setMode(CameraType type)
{
	_cameraType = type;
	_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::setPosition(glm::vec3 pos)
{
	_cameraPos = pos;
}

void Camera::setLookAt(glm::vec3 pos)
{
	_cameraLookAt = pos;
}

void Camera::setFOV(double fov)
{
	_fov = fov;
}

void Camera::setViewport(int locX, int locY, int width, int height)
{
	_viewportX = locX;
	_viewportY = locY;
	_windowX = width;
	_windowY = height;
	_aspect = static_cast<double>(_windowX) / static_cast<double>(_windowY);
}

void Camera::setClipping(double nearClipDistance, double farClipDistance)
{
	_nearClip = nearClipDistance;
	_farClip = farClipDistance;
}

void Camera::processMouseButtons()
{	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		_moveCamera = true;
	}
	else
	{
		_moveCamera = false;
	}
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
		_grab = true;
	}
	else
	{
		_grab = false;
	}
}

CameraType Camera::getMode()
{
	return _cameraType;
}

void Camera::getViewPort(int& locX, int& locY, int& width, int& height)
{
	locX = _viewportX;
	locY = _viewportY;
	width = _windowX;
	height = _windowY;

}

void Camera::getMatrices(glm::mat4& view, glm::mat4& projection)
{
	projection = _projection;
	view = _view;
}

float Camera::getDirection()
{
	return acos(glm::dot(_oldCameraDirection.x, _cameraDirection.x));
}

void Camera::processMovement(CameraDirection direction)
{
	if (_cameraType == FREE)
	{
		switch (direction)
		{
		case UP:
			_cameraPosDelta -= _cameraUp * _cameraScale;
			break;
		case DOWN:
			_cameraPosDelta += _cameraUp * _cameraScale;
			break;
		case LEFT:
			_cameraPosDelta -= glm::cross(_cameraDirection, _cameraUp) * _cameraScale;
			break;
		case RIGHT:
			_cameraPosDelta += glm::cross(_cameraDirection, _cameraUp) * _cameraScale;
			break;
		case FORWARD:
			_cameraPosDelta += _cameraDirection * _cameraScale;
			break;
		case BACK:
			_cameraPosDelta -= _cameraDirection * _cameraScale;
			break;
		case DEFAULT:
			break;
		}
	}
}
