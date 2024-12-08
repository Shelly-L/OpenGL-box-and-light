#include"Application.h"
#include<glad/glad.h>
#include<iostream>
#include <GLFW/glfw3.h>

//��ʼ��Application�ľ�̬����
Application* Application::mInstance = nullptr;
Application* Application::getInstance() {
	//���mInstance�Ѿ���ʵ���������ˣ�new�����ˣ�����ֱ�ӷ���
	//������Ҫ��Ҫ��new�������ڷ���
	if (mInstance == nullptr)
	{
		mInstance = new Application;
	}
	return mInstance;
}
bool Application::init(const int& Width , const int& Height ) {
	mWidth = Width;
	mHeight = Height;
	
	//1 ��ʼ��GLFW��������
	glfwInit();
	//1.1 ����OpenGL���汾�š��ΰ汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//1.2 ����OpenGL���ú���ģʽ����������Ⱦģʽ��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//2 �����������
	mWindow = glfwCreateWindow(mWidth,mHeight, "OpenGLWindow", NULL, NULL);
	if (mWindow == NULL) {
		return false;
	}

	//���õ�ǰ�������ΪOpenGL�Ļ�����̨
	glfwMakeContextCurrent(mWindow);

	//ʹ��glad�������е�ǰ�汾opengl�ĺ���
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}
	
	glfwSetFramebufferSizeCallback(mWindow, frameBufferSizeCallback);
	//������Ӧ
	glfwSetKeyCallback(mWindow, keyCallback);
	//������¼���Ӧ
	glfwSetMouseButtonCallback(mWindow, mouseCallback);
	//����ƶ��¼���Ӧ
	glfwSetCursorPosCallback(mWindow, cursorCallback);
	//������ʱ����Ӧ
	glfwSetScrollCallback(mWindow, scrollCallback);
	return true;

}

bool Application::update() {
	if (glfwWindowShouldClose(mWindow)) {
		return false;
	}
	//���ܲ��ַ�������Ϣ
	//�����Ϣ�����Ƿ�����Ҫ�������ꡢ���̵���Ϣ
	//����еĻ��ͽ���Ϣ����������ն���
	glfwPollEvents();

	//�л�˫����
	glfwSwapBuffers(mWindow);
	return true;
}

void Application::destroy() {
	//�˳�����ǰ���������
	glfwTerminate();
}


void Application::getCursorPosition(double* x,double* y) {
	glfwGetCursorPos(mWindow, x, y);
}

void Application::frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{   if(Application::getInstance()->mResizCallback!=nullptr)
	Application::getInstance()->mResizCallback(width, height);
}

void Application::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (Application::getInstance()->mKeyBoardCallback != nullptr)
		Application::getInstance()->mKeyBoardCallback(key, action, mods);
}

Application::Application() {

}

Application::~Application() {

}

void Application::mouseCallback(GLFWwindow* window, int button, int action, int mods) {
	if (Application::getInstance()->mMouseCallback != nullptr)
		Application::getInstance()->mMouseCallback(button, action, mods);
}
void Application::cursorCallback(GLFWwindow* window, double xpos, double ypos) {
	if (Application::getInstance()->mCursorCallback != nullptr)
		Application::getInstance()->mCursorCallback(xpos, ypos);
}

//������Ϣ��xoffsetû��
void Application::scrollCallback(GLFWwindow* window, double xoffser, double yoffset) {
	if (Application::getInstance()->mScrollCallback!= nullptr)
		Application::getInstance()->mScrollCallback(yoffset);
}
