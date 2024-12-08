#pragma once
#define appl Application::getInstance()
#include<stdint.h>
class GLFWwindow;
//封装application单例类，全局唯一实例，表示应用程序本身

//声明一个函数指针
using ResizeCallback= void(*)(int width, int height);
using KeyBoardCallback = void(*)(int key, int action, int mods);
using MouseCallback = void(*)(int button, int action, int mods);
using CursorCallback = void(*)(double xpos, double ypos);
using ScrollCallback = void(*)(double offset);
class Application {
public:
	~Application() ;
	//用于访问实例的静态函数，因为单例类不允许，随便构造对象，所以通过，这个函数来确定是否实例化
	static Application* getInstance();
	//用于初始化窗口，设置初始信息，生成窗体，载入opengl函数
	bool init(const int&Width=800,const int&Height=600);
	//update，更新双缓存，清理画布，接受并分发窗体消息
	bool update();
	//执行glfwTerminate，退出gl环境
	void destroy();
	uint32_t getWidth()const { return mWidth; }
	uint32_t getHeight()const { return mHeight; }
	void getCursorPosition(double*x,double*y);
	//声明一个setResizeCallback的函数，设置窗体变化响应回调函数
	void setResizeCallback(ResizeCallback callback) {
		mResizCallback = callback;
	}
	void setKeyBoardCallback(KeyBoardCallback callback) {
		mKeyBoardCallback = callback;
	}
	void setMouseCallback(MouseCallback callback) {
		mMouseCallback = callback;
	}
	void setCursorCallback(CursorCallback callback) {
		mCursorCallback = callback;
	}

	void setScrollCallback(ScrollCallback callback) {
		mScrollCallback = callback;
	}

private:
	Application() ;
	static Application* mInstance;
	uint32_t mWidth{ 0 };
	uint32_t mHeight{ 0 };
	GLFWwindow* mWindow{ nullptr };
	ResizeCallback mResizCallback{ nullptr };//声明一个ResizeCallback类型的成员变量
	MouseCallback mMouseCallback{ nullptr };
	CursorCallback mCursorCallback{ nullptr };
	ScrollCallback mScrollCallback{ nullptr };
	//声明一个static的静态函数，用于响应glfww窗体变化,
	static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
	KeyBoardCallback mKeyBoardCallback{ nullptr };//声明一个KeyBoardCallback
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouseCallback(GLFWwindow* window, int button, int action, int mods);
	static void cursorCallback(GLFWwindow* window, double xpos, double ypos);
	static void scrollCallback(GLFWwindow* window, double xoffser, double yoffset);
};