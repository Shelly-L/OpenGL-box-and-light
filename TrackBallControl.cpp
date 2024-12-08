#include"TrackBallControl.h"


TrackBallCameraControl::TrackBallCameraControl() {

}

TrackBallCameraControl::~TrackBallCameraControl() {

}


void TrackBallCameraControl::onCursor(double xpos, double ypos) {
	if (mLeftMouseDown) {
		//调整相机的各类参数
		//1 计算经线跟纬线旋转的增量角度（正负都有可能）
		float deltaX = (xpos - mCurrentX) * mSensitivity;
		float deltaY = (ypos - mCurrentY) * mSensitivity;
		//2 分开pitch和yaw各自计算
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
	//绕着mRight向量在旋转
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), mCamera->mRight);
    //影响当前相机的up向量和位置
	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);//vector4给到vector是允许的，给了xyz
	mCamera->mPosition = mat * glm::vec4(mCamera->mPosition, 1.0f);
}


void TrackBallCameraControl::yaw(float angle) {
	//yaw绕着世界坐标系的Y轴旋转
	auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f,1.0f,0.0f));
	mCamera->mUp = mat * glm::vec4(mCamera->mUp, 0.0f);//vector4给到vector是允许的，给了xyz
	mCamera->mPosition = mat * glm::vec4(mCamera->mPosition, 1.0f);
	mCamera->mRight = mat * glm::vec4(mCamera->mRight, 0.0f);


}

void TrackBallCameraControl::onScroll(float offset) {
	mCamera->scale(offset);
}