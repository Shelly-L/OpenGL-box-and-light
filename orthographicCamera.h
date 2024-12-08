#pragma once


#include"camera.h"

class OrthographicCamera :public Camera {
public:
	OrthographicCamera(float l = 0.0f,float r = 0.0f,float t = 0.0f,float b = 0.0f,float n = 0.0f,float f= 0.0f);
	~OrthographicCamera();
     glm::mat4 getProjectionMatrix()override;
	 void scale(float deltaScale)override;

private:
	float mLeft = 0.0f;
	float mRight = 0.0f;
	float mTop = 0.0f;
	float mBottom = 0.0f;
	float mNear = 0.0f;
	float mFar = 0.0f;

	float mScale{ 0.0f };
};