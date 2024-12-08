#include"CameraControl.h"

CameraControl::CameraControl() {

}

CameraControl::~CameraControl()
{

}

	//���ڼ̳�CameraControl�����࣬�п��ܻ�ʵ���Լ����߼�
void CameraControl::onMouse(int button, int action, double xpos, double ypos) {
	//�жϵ�ǰ�İ������Ƿ���
	bool pressed = action == GLFW_PRESS ? true : false;
	//������£���¼��ǰ���µ�λ��
	if (pressed) {
		mCurrentX = xpos;
		mCurrentY = ypos;
	}
	//���ݰ��µ���갴����ͬ�����ͬ�ļ�¼
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
	//���˵�repeat�����
	if (action == GLFW_REPEAT) {
		return;
	}

	//��ⰴ�»���̧�𣬸���һ������
	bool pressed = action == GLFW_PRESS ? true : false;

	//��¼�����ǵ�keymap��
	mKeyMap[key] = pressed;
}

	//ÿһ֡��Ⱦǰ��Ҫ���е��ã�ÿһ֡���µ���Ϊ�����Է�������
void CameraControl::update() {

}

void CameraControl::onScroll(float offset) {

}

