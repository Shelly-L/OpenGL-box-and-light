#include"CameraControl.h"

CameraControl::CameraControl() {

}

CameraControl::~CameraControl()
{

}

	//由于继承CameraControl的子类，有可能会实现自己的逻辑
void CameraControl::onMouse(int button, int action, double xpos, double ypos) {
	//判断当前的按键，是否按下
	bool pressed = action == GLFW_PRESS ? true : false;
	//如果按下，记录当前按下的位置
	if (pressed) {
		mCurrentX = xpos;
		mCurrentY = ypos;
	}
	//根据按下的鼠标按键不同，激活不同的记录
	switch (button) {
	case GLFW_MOUSE_BUTTON_LEFT:
		mLeftMouseDown = pressed;
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		mRightMouseDown = pressed;
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		mMiddleMouseDown = pressed;
		break;
	}
}

void CameraControl::onCursor(double xpos, double ypos) {

}

void CameraControl::onKey(int key, int action, int mods) {
	//过滤掉repeat的情况
	if (action == GLFW_REPEAT) {
		return;
	}

	//检测按下或者抬起，给到一个变量
	bool pressed = action == GLFW_PRESS ? true : false;

	//记录在我们的keymap中
	mKeyMap[key] = pressed;
}

	//每一帧渲染前都要进行调用，每一帧更新的行为都可以放在这里
void CameraControl::update() {

}

void CameraControl::onScroll(float offset) {

}

