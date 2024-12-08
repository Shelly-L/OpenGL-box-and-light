#include"TrackBallControl.h"


TrackBallCameraControl::TrackBallCameraControl() {

}

TrackBallCameraControl::~TrackBallCameraControl() {

}


void TrackBallCameraControl::onCursor(double xpos, double ypos) {
	if (mLeftMouseDown) {
		//��������ĸ������
		//1 ���㾭�߸�γ����ת�������Ƕȣ��������п��ܣ�
		float deltaX = (xpos - mCurrentX) * mSensitivity;
		float deltaY = (ypos - mCurrentY) * mSensitivity;
		//2 �ֿ�pitch��yaw���Լ���
		pitch(-deltaY);
		yaw(-deltaX);
	}
	if (mMiddleMouseDown) {
		float deltaX = (xpos - mCurrentX) * mMoveSpeed;
		float deltaY = (ypos - mCurrentY) * mMoveSpeed;

		mCamera->mPosition += mCamera->mUp * deltaY;
		mCamera->mPosition -= mCamera->mRight * deltaX;

	}

	mCurrentX = xpos;
	mCurrentY = ypos;

}

void TrackBallCameraControl::pitch(float angle) {
	//����mRight��������ת
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), mCamera->mRight);
    //Ӱ�쵱ǰ�����up������λ��
	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);//vector4����vector������ģ�����xyz
	mCamera->mPosition = mat * glm::vec4(mCamera->mPosition, 1.0f);
}


void TrackBallCameraControl::yaw(float angle) {
	//yaw������������ϵ��Y����ת
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f,1.0f,0.0f));
	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);//vector4����vector������ģ�����xyz
	mCamera->mPosition = mat * glm::vec4(mCamera->mPosition, 1.0f);
	mCamera->mRight = mat * glm::vec4(mCamera->mRight, 0.0f);


}

void TrackBallCameraControl::onScroll(float offset) {
	mCamera->scale(offset);
}