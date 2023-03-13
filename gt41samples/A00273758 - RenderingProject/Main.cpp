#include "ShaderTechnique.h"
#include "GameObject.h"
#include "Helper.cpp"

// (global) application window properties
static unsigned int windowWidth = 1000;
static unsigned int windowHeight = 600;
unsigned int windowPos_X = 800;
unsigned int windowPos_Y = 400;
const char* windowTitle = "A00273758 - Rendering Project";

// some GameObjects
GameObject triangleA;
GameObject triangleB;
//GameObject cubeFromObjFile;

// some shaders
ShaderTechnique shaderA;

// Camera stuff
//Camera sceneCamera;
mat4 worldToViewTransform;
mat4 projectionTransform;

float cameraPosZ = 10.0f;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// some other variables
bool isWireframe = false;

// some variables for object loader
vector<vec3> obj_vertices;
vector<vec3> normalVec;
vec3 objVertz[24];	// 8 * 3 = 24 vertices

// variables for object translation
float posX = 0.0f, posY = 0.0f;

bool isLeftArrowDown, isRightArrowDown, isUpArrowDown, isDownArrowDown = false;
const float cameraSpeed = 0.05f;

// some functions declaration
void processMouse(int button, int state, int x, int y);
void processKeyboardDown(unsigned char key, int x, int y);
void processKeyboardUp(unsigned char key, int x, int y);
//void processKeyboardSpecialKeys(int key, int x, int y);
void createGameObjects();
void sceneSetup(float windowWidth, float windowHeight);
static void renderSceneCallBack();
static void initializeGlutCallbacks();

#pragma region Functions

void processMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			isWireframe = !isWireframe;
			Utilities::InputDebugger("Left Mouse Button Clicked");
		}
	}
	if (button == 3)
	{
		cameraPosZ -= 0.25f;
		Utilities::InputDebugger("Mouse Scroll Up");
	}
	if (button == 4)
	{
		cameraPosZ += 0.25f;
		Utilities::InputDebugger("Mouse Scroll Down");
	}


}

void processKeyboardDown(unsigned char key, int x, int y)
{
	switch (key)
	{
		/*case 't':
			isTranslate = true;
			Utilities::InputDebugger("t");
			break;
		case 's':
			isScale = true;
			Utilities::InputDebugger("s");
			break;*/

		case 'i':
			posY += 0.25f;
			Utilities::InputDebugger("i");
			break;
		case 'k':
			posY -= 0.25f;
			Utilities::InputDebugger("k");
			break;
		case 'j':
			posX -= 0.25f;
			Utilities::InputDebugger("j");
			break;
		case 'l':
			posX += 0.25f;
			Utilities::InputDebugger("l");
			break;

		case '4':
			//cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * 0.5f;
			isLeftArrowDown = true;
			Utilities::InputDebugger("4");
			break;
		case '6':
			//cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * 0.5f;
			isRightArrowDown = true;
			Utilities::InputDebugger("6");
			break;
		case '8':
			//cameraPos.y += 0.5f;
			isUpArrowDown = true;
			Utilities::InputDebugger("8");
			break;
		case '2':
			//cameraPos.y -= 0.5f;
			isDownArrowDown = true;
			Utilities::InputDebugger("2");
			break;
		case '5':
			cameraPosZ -= 0.25f;
			Utilities::InputDebugger("5");
			break;
		case '0':
			cameraPosZ += 0.25f;
			Utilities::InputDebugger("0");
			break;
		default:
			break;
	}
}

void processKeyboardUp(unsigned char key, int x, int y)
{
	const unsigned char escapeKey = 27;

	switch (key)
	{
		/*case 't':
			isTranslate = false;
			break;
		case 's':
			isScale = false;
			break;*/
		case escapeKey:
			glutLeaveMainLoop();
			Utilities::InputDebugger("esc");
			cout << "\nApplication Quit...Success!" << endl;
			break;
		case '4':
			//cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * 0.5f;
			isLeftArrowDown = false;
			Utilities::InputDebugger("4");
			break;
		case '6':
			//cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * 0.5f;
			isRightArrowDown = false;
			Utilities::InputDebugger("6");
			break;
		case '8':
			isUpArrowDown = false;
			Utilities::InputDebugger("8");
			break;
		case '2':
			isDownArrowDown = false;
			Utilities::InputDebugger("2");
			break;
	}
}

//void processKeyboardSpecialKeys(int key, int x, int y)
//{
//
//	switch (key)
//	{
//		case GLUT_KEY_UP:
//			cameraPos.y += cameraSpeed;
//			Utilities::InputDebugger("Up Arrow");
//			break;
//		case GLUT_KEY_DOWN:
//			cameraPos.y -= cameraSpeed;
//			Utilities::InputDebugger("Down Arrow");
//			break;
//		case GLUT_KEY_LEFT:
//			//cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//
//			isLeftArrowDown = true;
//			isRightArrowDown = false;
//			Utilities::InputDebugger("Left Arrow");
//			break;
//		case GLUT_KEY_RIGHT:
//			//cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//
//			isLeftArrowDown = false;
//			isRightArrowDown = true;
//			Utilities::InputDebugger("Right Arrow");
//			break;
//		default:
//			isLeftArrowDown = false;
//			isRightArrowDown = false;
//	}
//}

void createGameObjects()
{
	// TODO: Do this using john's lighting project way
	const int numVerts = 3;	// use this once or duplicate for each vbo

	Properties objA_Data[numVerts] = {
		{vec3(0.0f, 1.0f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f)},
		{vec3(-1.0f, 0.0f, 0.0f),  vec4(0.0f, 1.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f)},
		{vec3(0.0f, 0.0f, 0.0f),  vec4(0.0f, 0.0f, 1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f)}
	};

	Properties objB_Data[numVerts] = {
		{vec3(-1.0f, 1.0f, 0.0f), vec4(0.5f, 1.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f)},
		{vec3(-1.0f, 0.0f, 0.0f),  vec4(1.0f, 1.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f)},
		{vec3(0.0f, 1.0f, 0.0f),  vec4(0.8f, 1.0f, 1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f)}
	};

	triangleA.setPrimitiveMode(GL_TRIANGLES);
	triangleA.createVertexBuffer(objA_Data, numVerts);
	triangleA.setShader(&shaderA);

	triangleB.setPrimitiveMode(GL_TRIANGLES);
	triangleB.createVertexBuffer(objB_Data, numVerts);
	triangleB.setShader(&shaderA);

	//obj_vertices = Utilities::objFileLoader("Other/cube.obj", obj_vertices, normalVec);

	//copy(obj_vertices.begin(), obj_vertices.end(), objVertz);

	//cubeFromObjFile.setPrimitiveMode(GL_TRIANGLES);
	//cubeFromObjFile.createVBO(objVertz, 24);
	//cubeFromObjFile.setShader(&shaderA);
}

void sceneSetup(float windowWidth, float windowHeight)
{
	// Create out projection transform
	projectionTransform = perspective(45.0f, (float)windowWidth / (float)windowHeight, 1.0f, 100.0f);
}

static void renderSceneCallBack()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(isLeftArrowDown == true)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if(isRightArrowDown == true)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if(isUpArrowDown == true)
		cameraPos.y += cameraSpeed;
	if (isDownArrowDown == true)
		cameraPos.y -= cameraSpeed;


	// only doing translation when required (i.e. when user presses t)
	//if (isTranslate)
	//{
	//	//printf("\nDoing Translation...");
	//	translateValue += 0.009f;
	//	objA.setTranslate(translateValue, 0, 0);
	//	objB.setTranslate(0, translateValue, 0);
	//}

	triangleA.setTranslate(posX, 0, 0.0f);
	triangleB.setTranslate(0, posY, 0);
	//cubeFromObjFile.setTranslate(0, 0, 0);

	// only doing scaling when required (i.e. when user presses s)
	//if (isScale)
	//{
	//	//printf("\nDoing Scaling...");
	//	scaleValue += 0.01f;
	//	objA.setScale(scaleValue, scaleValue, 0);
	//	objB.setScale(scaleValue, scaleValue, 0);
	//}

	//cubeFromObjFile.setScale(4, 2, 2);

	static float angle = 10.0f;
	angle += 1.0f;
	//triangleA.setRotation(angle, 1.0f, 0.0f, 0.0f);
	//triangleB.setRotation(angle, 0.0f, 0.0f, 1.0f);
	//cubeFromObjFile.setRotation(angle, 0.0f, 1.0f, 0.0f);

	worldToViewTransform = lookAt(vec3(cameraPos.x, cameraPos.y, cameraPosZ), cameraPos + cameraFront, vec3(0.0f, 1.0f, 0.0f));

	shaderA.updateShader(worldToViewTransform, projectionTransform);

	Utilities::ToggleWireFrame(isWireframe);

	triangleA.render();
	triangleB.render();
	//cubeFromObjFile.renderOBJ();

	glutSwapBuffers();
}

static void initializeGlutCallbacks()
{
	glutDisplayFunc(renderSceneCallBack);
	glutIdleFunc(renderSceneCallBack);
	glutMouseFunc(processMouse);
	glutKeyboardFunc(processKeyboardDown);
	glutKeyboardUpFunc(processKeyboardUp);
	//glutSpecialFunc(processKeyboardSpecialKeys);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(windowPos_X, windowPos_Y);
	glutCreateWindow(windowTitle);


	initializeGlutCallbacks();

	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		cerr << "Error: " << glewGetErrorString(res) << "\n";
		return 1;
	}

	Utilities::ControlGuideInConsole();

	// build (all) shaders	
	shaderA.buildShader("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	sceneSetup(windowWidth, windowHeight);

	createGameObjects();	// creates set of gameObjects

	glutMainLoop();

	return 0;
}

#pragma endregion
