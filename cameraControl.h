#pragma once

#include"../../glframework//core.h"
#include"camera.h"
#include<map>//stl:map


class CameraControl {
public:
	CameraControl();
	~CameraControl();

	//由于继承CameraControl的子类，有可能会实现自己的逻辑
	virtual void onMouse(int button, int action, double xpos, double ypos);
	virtual void onCursor(double xpos, double ypos);
	virtual void onKey(int key, int action, int mods);
	virtual void onScroll(float offset);//+1/-1

	//每一帧渲染前都要进行调用，每一帧更新的行为都可以放在这里
	virtual void update();

	void setCamera(Camera* camera) { mCamera = camera; }
	void setSensitivity(float s) { mSensitivity = s; }
	void setScaleSpeed(float s) { mScaleSpeed = s; }



protected:
	//鼠标状态
	bool mLeftMouseDown = false;
	bool mRightMouseDown = false;
	bool mMiddleMouseDown = false;

	//当前鼠标的位置
	float mCurrentX = 0.0f;
	float mCurrentY = 0.0f;

	//敏感度
	float mSensitivity = 0.2f;

	//记录键盘相关按键的按下状态
	std::map<int, bool>mKeyMap;

	//存储当前控制的哪一架摄像机
	Camera* mCamera = nullptr;

	//记录相机缩放的速度
	float mScaleSpeed = 0.2f;
};