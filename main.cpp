#include <iostream>

#include"glframework/core.h"
#include"glframework/shader.h"
#include"Application/Application.h"
#include"wrapper/CheckError.h"
#include"glframework/texture.h"
#include"application/camera/camera.h"
#include"Application/camera/TrackBallControl.h"
#include"Application/camera/perspectiveCamera.h"
#include"Application/camera/orthographicCamera.h"
#include"Application/camera/GameCameraControl.h"
#include"glframework//geometry.h"


#include<string>
#include<vector>
Texture* diffuseMap =nullptr;
Texture* specularMap = nullptr;
Texture* skyMap = nullptr;

Shader* cubeShader = nullptr;
Shader* lightShader = nullptr;
Shader* skyShader = nullptr;
unsigned int skyboxVAO, skyboxVBO;



Geometry* cube = nullptr;
Geometry* light = nullptr;
Geometry* sky = nullptr;


glm::vec3 lightPos(6.0f, 6.0f, 6.0f);


glm::vec3 cubePositions[] = {
glm::vec3(0.0f,  0.0f,  0.0f),
glm::vec3(2.0f,  5.0f, -15.0f),
glm::vec3(-1.5f, -2.2f, -2.5f),
glm::vec3(-3.8f, -2.0f, -12.3f),
glm::vec3(2.4f, -0.4f, -3.5f),
glm::vec3(-1.7f,  3.0f, -7.5f),
glm::vec3(1.3f, -2.0f, -2.5f),
glm::vec3(1.5f,  2.0f, -2.5f),
glm::vec3(1.5f,  0.2f, -1.5f),
glm::vec3(-1.3f,  1.0f, -1.5f)
};

glm::vec3 pointLightPositions[] = {
	  glm::vec3(0.7f,  0.2f,  2.0f),
	  glm::vec3(2.3f, -3.3f, -4.0f),
	  glm::vec3(-4.0f,  2.0f, -12.0f),
	  glm::vec3(0.0f,  0.0f, -3.0f)
};

float skyboxVertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};

PerspectiveCamera* camera = nullptr;
GameCameraControl* cameraControl = nullptr;
//TrackBallCameraControl* cameraControl = nullptr;




void prepareVAO() {
	cube = Geometry::createBox(1.0f);
	light = Geometry::createBox(1.5f);
	sky = Geometry::createBox(5.0f);

	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

}




void prepareTexture() {
	diffuseMap = new Texture("assets/textures/container2.png", 0);
	specularMap = new Texture("assets/textures/container2_specular.png", 1);

	std::vector<std::string> faces
	{
		"assets/textures/skybox/right.jpg",
		"assets/textures/skybox/left.jpg",
		"assets/textures/skybox/top.jpg",
		"assets/textures/skybox/bottom.jpg",
		"assets/textures/skybox/back.jpg",
		"assets/textures/skybox/front.jpg"
	};
	skyMap = new Texture(faces, 2);
}


void prepareShader() {
	cubeShader = new Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
	lightShader = new Shader("assets/shaders/light.vs", "assets/shaders/light.fs");
	skyShader = new Shader("assets/shaders/test.vs", "assets/shaders/test.fs");
}

void prepareCamera() {
	float size = 3.0f;
	camera = new PerspectiveCamera(60.0f, (float)appl->getWidth() / (float)appl->getHeight(), 0.1f, 1000.0f);
	cameraControl = new GameCameraControl();
	cameraControl->setCamera(camera);

}

void prepareState() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void prepareStencilFunc() {
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
}

void prepareFaceCulling() {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

void onResize(int width,int height) {
	glViewport(0, 0,width, height);
	std::cout << "resize" << std::endl;
}


void OnKey(int key, int action, int mods) {
	cameraControl->onKey(key, action, mods);
}

void OnMouse(int button, int action, int mods) {
	double x, y;
	appl->getCursorPosition(&x, &y);
	cameraControl->onMouse(button, action, x, y);
}

void OnCusor(double xpos, double ypos) {
	cameraControl->onCursor(xpos, ypos);
}

void OnScroll(double offset) {
	cameraControl->onScroll(offset);
}

void prepareBox() {
	//绑定当前的program
	cubeShader->use();
	cubeShader->setInt("material.diffuse", 0);
	cubeShader->setInt("material.specular", 1);

	cubeShader->setMatrix4x4("viewMatrix", camera->getViewMatrix());
	cubeShader->setMatrix4x4("projectionMatrix", camera->getProjectionMatrix());
	cubeShader->setVec3("viewPos", camera->mPosition);
	cubeShader->setFloat("material.shininess", 32.0f);

	glm::vec3 dirLightAmbient(0.05f, 0.05f, 0.05f);
	glm::vec3 dirLightDiffuse(0.4f, 0.4f, 0.4f);
	glm::vec3 dirLightSpecular(0.5f, 0.5f, 0.5f);
	glm::vec3 lightDirection(-0.2f, -1.0f, -0.3f);

	glm::vec3 pointLightAmbient(0.05f, 0.05f, 0.05f);
	glm::vec3 pointLightDiffuse(0.8f, 0.8f, 0.8f);
	glm::vec3 pointLightSpecular(1.0f, 1.0f, 1.0f);

	glm::vec3 spotLightAmbient(0.0f, 0.0f, 0.0f);
	glm::vec3 spotLightDiffuse(1.0f, 1.0f, 1.0f);
	glm::vec3 spotLightSpecular(1.0f, 1.0f, 1.0f);

	
	cubeShader->setVec3("dirLight.direction", lightDirection);
	cubeShader->setVec3("dirLight.ambient", dirLightAmbient);
	cubeShader->setVec3("dirLight.diffuse", dirLightDiffuse);
	cubeShader->setVec3("dirLight.specular", dirLightSpecular);

	// point light 1
	cubeShader->setVec3("pointLights[0].position", pointLightPositions[0]);
	cubeShader->setVec3("pointLights[0].ambient", pointLightAmbient);
	cubeShader->setVec3("pointLights[0].diffuse", pointLightDiffuse);
	cubeShader->setVec3("pointLights[0].specular", pointLightSpecular);
	cubeShader->setFloat("pointLights[0].constant", 1.0f);
	cubeShader->setFloat("pointLights[0].linear", 0.09f);
	cubeShader->setFloat("pointLights[0].quadratic", 0.032f);
	// point light 2
	cubeShader->setVec3("pointLights[1].position", pointLightPositions[1]);
	cubeShader->setVec3("pointLights[1].ambient", pointLightAmbient);
	cubeShader->setVec3("pointLights[1].diffuse", pointLightDiffuse);
	cubeShader->setVec3("pointLights[1].specular", pointLightSpecular);
	cubeShader->setFloat("pointLights[1].constant", 1.0f);
	cubeShader->setFloat("pointLights[1].linear", 0.09f);
	cubeShader->setFloat("pointLights[1].quadratic", 0.032f);
	// point light 3
	cubeShader->setVec3("pointLights[2].position", pointLightPositions[2]);
	cubeShader->setVec3("pointLights[2].ambient", pointLightAmbient);
	cubeShader->setVec3("pointLights[2].diffuse", pointLightDiffuse);
	cubeShader->setVec3("pointLights[2].specular", pointLightSpecular);
	cubeShader->setFloat("pointLights[2].constant", 1.0f);
	cubeShader->setFloat("pointLights[2].linear", 0.09f);
	cubeShader->setFloat("pointLights[2].quadratic", 0.032f);
	// point light 4
	cubeShader->setVec3("pointLights[3].position", pointLightPositions[3]);
	cubeShader->setVec3("pointLights[3].ambient", pointLightAmbient);
	cubeShader->setVec3("pointLights[3].diffuse", pointLightDiffuse);
	cubeShader->setVec3("pointLights[3].specular",pointLightSpecular);
	cubeShader->setFloat("pointLights[3].constant", 1.0f);
	cubeShader->setFloat("pointLights[3].linear", 0.09f);
	cubeShader->setFloat("pointLights[3].quadratic", 0.032f);

	
	
	

	cubeShader->setVec3("spotLight.position", camera->mPosition);
	cubeShader->setVec3("spotLight.direction", glm::cross(camera->mUp, camera->mRight));
	cubeShader->setVec3("spotLight.ambient", spotLightAmbient);
	cubeShader->setVec3("spotLight.diffuse", spotLightDiffuse);
	cubeShader->setVec3("spotLight.specular", spotLightSpecular);
	cubeShader->setFloat("spotLight.constant", 1.0f);
	cubeShader->setFloat("spotLight.linear", 0.09f);
	cubeShader->setFloat("spotLight.quadratic", 0.032f);
	cubeShader->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	cubeShader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

	diffuseMap->bind();
	specularMap->bind();
	//绑定当前的vao；
	glBindVertexArray(cube->getVao());

	for (unsigned int i = 0; i < 10; i++)
	{
		glm::mat4 transform(1.0f);
		transform = glm::translate(transform, cubePositions[i]);
		float angle = 20.0f * i;
		transform = glm::rotate(transform, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		cubeShader->setMatrix4x4("transform", transform);

		
		//发出绘画指令
		glDrawElements(GL_TRIANGLES, cube->getIndicesCount(), GL_UNSIGNED_INT, 0);
		
	}

	glBindVertexArray(0);

	

	cubeShader->end();
}

void prepareLight() {
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, lightPos);

	//绑定当前的program
	lightShader->use();
	lightShader->setMatrix4x4("transform", transform);
	lightShader->setMatrix4x4("viewMatrix", camera->getViewMatrix());
	lightShader->setMatrix4x4("projectionMatrix", camera->getProjectionMatrix());



	//绑定当前的vao；
	glBindVertexArray(light->getVao());

	for (unsigned int i = 0; i < 4; i++)
	{
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, pointLightPositions[i]);
		transform = glm::scale(transform, glm::vec3(0.2f)); // Make it a smaller cube
		lightShader->setMatrix4x4("transform", transform);
		//发出绘画指令
		glDrawElements(GL_TRIANGLES, light->getIndicesCount(), GL_UNSIGNED_INT, 0);
	}
	
	glBindVertexArray(0);

	lightShader->end();
}

void prepareTest() {

	glDepthFunc(GL_LEQUAL);
	

	skyShader->use();
	skyShader->setInt("skyMap", 2);

	glm::mat4 view;
	view = glm::mat4(glm::mat3(camera->getViewMatrix()));

	
	skyShader->setMatrix4x4("view", camera->getViewMatrix());
	skyShader->setMatrix4x4("projection", camera->getProjectionMatrix());
	

	glBindVertexArray(skyboxVAO);
	skyMap->bind1();

 glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);

	skyShader->end();

}


void prepareSky() {
	glDepthFunc(GL_LEQUAL);
	skyShader->use();

	skyShader->setInt("skyMap", 2);
	glm::mat4 view;
	view = glm::mat4(glm::mat3(camera->getViewMatrix()));
	
	skyShader->setMatrix4x4("view", camera->getViewMatrix());
	skyShader->setMatrix4x4("projection", camera->getProjectionMatrix());

	glBindVertexArray(sky->getVao());
	skyMap->bind1();
	glDrawElements(GL_TRIANGLES, sky->getIndicesCount(), GL_UNSIGNED_INT, 0);
	glDepthFunc(GL_LESS);

}

void render(){

	//执行opengl画布清理操作
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//prepareTest();
	//prepareSky();
	prepareBox();
	prepareLight();
	
	
	
	
	

	
	
}

int main() {
	if (!appl->init(800, 600)) {
		return -1;  
	}


	appl->setResizeCallback(onResize);
	appl->setKeyBoardCallback(OnKey);
	appl->setMouseCallback(OnMouse);
	appl->setCursorCallback(OnCusor);
	appl->setScrollCallback(OnScroll);


	//设置opengl视口以及清理颜色
	glViewport(0, 0, 800, 600);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);



	
	prepareShader();
	prepareVAO();
	prepareTexture();
	prepareCamera();
	//prepareStencilFunc();
	prepareState();
	//prepareFaceCulling();



//3 执行窗体循环
	while (appl->update()) {
		cameraControl->update();
		render();
	}
	

//4 退出程序前做相关清理
	appl->destroy();
	return 0;
}