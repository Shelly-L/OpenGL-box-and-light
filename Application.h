#pragma once
#define appl Application::getInstance()
#include<stdint.h>
class GLFWwindow;
//��װapplication�����࣬ȫ��Ψһʵ������ʾӦ�ó�����

//����һ������ָ��
using ResizeCallback= void(*)(int width, int height);
using KeyBoardCallback = void(*)(int key, int action, int mods);
using MouseCallback = void(*)(int button, int action, int mods);
using CursorCallback = void(*)(double xpos, double ypos);
using ScrollCallback = void(*)(double offset);
class Application {
public:
	~Application() ;
	//���ڷ���ʵ���ľ�̬��������Ϊ�����಻������㹹���������ͨ�������������ȷ���Ƿ�ʵ����
	static Application* getInstance();
	//���ڳ�ʼ�����ڣ����ó�ʼ��Ϣ�����ɴ��壬����opengl����
	bool init(const int&Width=800,const int&Height=600);
	//update������˫���棬�����������ܲ��ַ�������Ϣ
	bool update();
	//ִ��glfwTerminate���˳�gl����
	void destroy();
	uint32_t getWidth()const { return mWidth; }
	uint32_t getHeight()const { return mHeight; }
	void getCursorPosition(double*x,double*y);
	//����һ��setResizeCallback�ĺ��������ô���仯��Ӧ�ص�����
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
	ResizeCallback mResizCallback{ nullptr };//����һ��ResizeCallback���͵ĳ�Ա����
	MouseCallback mMouseCallback{ nullptr };
	CursorCallback mCursorCallback{ nullptr };
	ScrollCallback mScrollCallback{ nullptr };
	//����һ��static�ľ�̬������������Ӧglfww����仯,
	static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
	KeyBoardCallback mKeyBoardCallback{ nullptr };//����һ��KeyBoardCallback
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouseCallback(GLFWwindow* window, int button, int action, int mods);
	static void cursorCallback(GLFWwindow* window, double xpos, double ypos);
	static void scrollCallback(GLFWwindow* window, double xoffser, double yoffset);
};