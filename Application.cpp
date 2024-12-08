#include"Application.h"
#include<glad/glad.h>
#include<iostream>
#include <GLFW/glfw3.h>

//初始化Application的静态变量
Application* Application::mInstance = nullptr;
Application* Application::getInstance() {
	//如果mInstance已经被实例化出来了（new出来了），就直接返回
	//否则需要先要先new出来，在返回
	if (mInstance == nullptr)
	{
		mInstance = new Application;
	}
	return mInstance;
}
bool Application::init(const int& Width , const int& Height ) {
	mWidth = Width;
	mHeight = Height;
	
	//1 初始化GLFW基本环境
	glfwInit();
	//1.1 设置OpenGL主版本号、次版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//1.2 设置OpenGL启用核心模式（非立即渲染模式）
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//2 创建窗体对象
	mWindow = glfwCreateWindow(mWidth,mHeight, "OpenGLWindow", NULL, NULL);
	if (mWindow == NULL) {
		return false;
	}

	//设置当前窗体对象为OpenGL的绘制舞台
	glfwMakeContextCurrent(mWindow);

	//使用glad加载所有当前版本opengl的函数
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}
	
	glfwSetFramebufferSizeCallback(mWindow, frameBufferSizeCallback);
	//键盘响应
	glfwSetKeyCallback(mWindow, keyCallback);
	//鼠标点击事件响应
	glfwSetMouseButtonCallback(mWindow, mouseCallback);
	//鼠标移动事件响应
	glfwSetCursorPosCallback(mWindow, cursorCallback);
	//鼠标滚轮时间响应
	glfwSetScrollCallback(mWindow, scrollCallback);
	return true;

}

bool Application::update() {
	if (glfwWindowShouldClose(mWindow)) {
		return false;
	}
	//接受并分发窗体消息
	//检查消息队列是否有需要处理的鼠标、键盘等消息
	//如果有的话就将消息批量处理，清空队列
	glfwPollEvents();

	//切换双缓存
	glfwSwapBuffers(mWindow);
	return true;
}

void Application::destroy() {
	//退出程序前做相关清理
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

//滚动消息的xoffset没用
void Application::scrollCallback(GLFWwindow* window, double xoffser, double yoffset) {
	if (Application::getInstance()->mScrollCallback!= nullptr)
		Application::getInstance()->mScrollCallback(yoffset);
}
