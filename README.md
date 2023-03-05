
<h1  align=center>Real-Time Rendering 4</h1>

<br/>

  

<h2>Rendering Engine Project</h2>

  

<h4>Setup</h4>

1. Download the GitHub Repo.

2. Open the `real-time-rendering` solution in Visual Studio.

3. Set the `A00273758 - RenderingProject` project as Startup project.

4. Finally, run the `ProjectRenderer.cpp` file.

##  

<details>
  <summary> <h2>Part 1 [Status: ✅]</h2> </summary>
<blockquote>
<details>
	<summary><h4>Goal</h4></summary>

  #### The goal of this part of the project was to refactor the code in such ways so that we can encapsulate the data and its functionality, <br/> <br/>i.e. Break down the functionality of a GameObject and a Shader into different classes.
	
  </details> 
	
<details>
    <summary><h4>UML Diagram</h4></summary>

  <br/>
   
   As we can see in the UML diagram below, there is a relationship that exists between a GameObject and a ShaderTechnique. This relationship can be described as <i>has-a</i> relationship between the two classes. In basic terms, this means that a single game object **has a** shader attached to it.
   
   <br/>
   
   ![UML Diagram: Showing Relationship between GameObject class & ShaderTechnique class](https://user-images.githubusercontent.com/34424878/218233715-c4c1ceb1-90b4-4640-a164-d878f9ceac1d.png)
	
  </details> 
	
<details>
   <summary><h4>Code Implementation</h4></summary>
  
   #### GameObject Class (.h file)
   
  ```cpp
  /// A Gameobject class which creates the vertex buffer and renders the gameobject.
/// This class inherits membersand functions of ShaderTechnique class as private membersand functions
class GameObject : private ShaderTechnique
{
public:
	GLuint vbo; // vertex buffer object
	GLuint numOfVertices; // max number of vertices
	ShaderTechnique* shader; // pointer to the attached shader
	// default constructor
	GameObject();
	// Creates a buffer based on the array of vertices passed into the function
	void createVertexBuffer(vec3 vertices[], int numverts);
	// renders the gameobject onto the screen
	void render();
};
  ```
   
   #### ShaderTechnique Class (.h file)
   
  ```cpp
  /// A class that can load, compile and link a vertex and fragment shader onto gameobject(s)
class ShaderTechnique
{
public:
	// default constructor
	ShaderTechnique();
	// reads (shader) file and returns the content of file as a string
	string readFile(string fileName);
	// creates a type of shader object (Vertex & Fragment) and then compiles and attaches the shader object to the program object
	void addShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType);
	// links and validates the shader program and sets it into pipeline
	void buildShader(string vertexShaderPath, string fragmentShaderPath);
};
  ```
   
	
  </details> 
	
<details>
    <summary><h4>Results</h4></summary>

   ### Before
     
| <p><img src="https://user-images.githubusercontent.com/34424878/218224866-a321e4ff-0c1e-4f6a-8bab-207495e6703e.png" width=300 height=200/></p>  |
|---|
| - In this the scene, one shader is applied to every object that is being rendered.  <br><br>- No classes, everything is in one (.cpp) file. <br><br>- The path of the shader files are hard coded, so cannot be changed for different objects. |

  ### After
  
| <p><img src="https://user-images.githubusercontent.com/34424878/218225202-c0adc299-055d-452e-a1d0-7b9c538325e7.png" width=300 height=200/></p>  |
|---|
| - Multiple objects are being rendered with each of them having their own shader.  <br><br>- In this part of project, the different functionalities are divided into their own separate classes ( [GameObject](https://github.com/MehadND/real-time-rendering-4/blob/0cfb8ef77be6ad0702a423c0a3d99f58f9a4429c/gt41samples%20(1)/gt41samples/renderingproject/GameObject.h) & [Shader](https://github.com/MehadND/real-time-rendering-4/blob/0cfb8ef77be6ad0702a423c0a3d99f58f9a4429c/gt41samples%20(1)/gt41samples/renderingproject/ShaderTechnique.h) ) <br><br>- `buildShader(vertexShaderPath, fragmentShaderPath)` function has 2 paramters for allwong users to enter file paths of the (vertex & fragment) shaders to be used for an object. |
	
  </details> 
	
</blockquote>
</details> 

##  

<details>

<summary>  <h2>Part 2 [Status: 🔃]</h2>  </summary>

<blockquote>

<details>

<summary><h4>Goal</h4></summary>

  

The goal of the part 2 of the project is to refactor this code so that you:

- Update your GameObject or Renderable to also encapsulate the scale,

position and rotation of a collection of vertices (3D object).

- Create a Camera object which encapsulates the functionality of the camera.

- Update your GameObject so that you can create the vertex buffer object from

the triangles specified in an OBJ file.

- Create a basic interactive scene demonstrating all features of your project.

* For example navigating around a simple scene of objects loaded from

obj files.

</details>

<details>

<summary><h4>UML Diagram</h4></summary>

  

Diagram

</details>

<details>

<summary><h4>Code Implementation</h4></summary>

  
- rendering
```cpp
static void renderSceneCallBack()
{
	glClear(GL_COLOR_BUFFER_BIT);

	objA.render();
	objB.render();

	// only doing translation when required (i.e. when user presses t)
	if (isTranslate)
	{
		printf("\nDoing Translation...");
		if (translateValue <= 0.8f)
		{
			translateValue += 0.009f;
		}

		objA.setTranslate(translateValue, 0, 0);
		objB.setTranslate(0, translateValue, 0);
	}

	// only doing scaling when required (i.e. when user presses s)
	if (isScale)
	{
		printf("\nDoing Scaling...");
		scaleValue += 0.01f;
		objA.setScale(scaleValue, scaleValue, 0);
		objB.setScale(0, scaleValue*4, 0);
	}

	glutSwapBuffers();
}
```
- creating gameobjects
```cpp
// Create GameObjects and its vertex buffer as well as sets the shader for the gameObject
static void createGameObjects()
{
	const int numVerts = 3;	// use this once or duplicate for each vbo
	
	Properties objA_Data[numVerts] = {
		{vec3(-0.5f, -0.5f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)},
		{vec3(0.5f, -0.5f, 0.0f),  vec4(0.0f, 1.0f, 0.0f, 1.0f)},
		{vec3(0.0f, 0.5f, 0.0f),  vec4(0.0f, 0.0f, 1.0f, 1.0f)}
	};

	Properties objB_Data[numVerts] = {
		{vec3(-0.5f, -0.5f, 0.0f), vec4(0.5f, 1.0f, 0.0f, 1.0f)},
		{vec3(0.5f, -0.5f, 0.0f),  vec4(0.0f, 1.0f, 0.0f, 1.0f)},
		{vec3(0.0f, 0.5f, 0.0f),  vec4(0.8f, 0.0f, 1.0f, 1.0f)}
	};

	objA.setPrimitiveMode(GL_TRIANGLES);
	objA.createVertexBuffer(objA_Data, numVerts);
	objA.setShader(&shaderA);

	objB.setPrimitiveMode(GL_TRIANGLES);
	objB.createVertexBuffer(objB_Data, numVerts);
	objB.setShader(&shaderA);
}
```

Properties struct
```cpp
- struct Properties
{
	vec3		pos;
	vec4		color;
	//glm::vec3		normal;

	ShaderTechnique* shader; // pointer to the attached shader
};
```

- GameObject Class
```cpp
/// A Gameobject class which creates the vertex buffer and renders the gameobject.
class GameObject
{
private:
	GLuint vbo; // vertex buffer object
	GLuint numOfVertices; // max number of vertices

	GLenum primitiveMode;

	Properties gameObjectProperties;

	mat4 finalTrans = mat4(1.0f);
	mat4 translator = mat4(1.0f);
	mat4 rotator = mat4(1.0f);
	mat4 scaler = mat4(1.0f);

	GLuint gTransformLocation;
	
	bool isSetTransform = true;

public:
	// default constructor
	GameObject();

	// Creates a buffer based on the array of vertices passed into the function
	void createVertexBuffer(Properties* properties, int numverts);

	// sets primtive mode for a gameobject
	void setPrimitiveMode(GLenum mode);
	
	// sets the shader (initailizes)
	void setShader(ShaderTechnique* s);

	// sets a (custom) translation
	void setTranslate(float translateXValue, float translateYValue, float translateZValue);

	// sets a (custom) scaling of an object
	void setScale(float scaleXValue, float scaleYValue, float scaleZValue);

	// sets the order of the transformation and links the cpu uniform variable with gpu/shader's uniform variable
	void setTransform();

	void applyTransform();

	// renders the gameobject onto the screen
	void render();
};
```

- ShaderTechnique Class
```cpp
/// A class that can load, compile and link a vertex and fragment shader onto gameobject(s)
class ShaderTechnique
{
public:

	// default constructor
	ShaderTechnique();

	// getter method for saher program
	GLuint getShaderProgram();

	// reads (shader) file and returns the content of file as a string
	string readFile(string fileName);

	// creates a type of shader object (Vertex & Fragment) and then compiles and attaches the shader object to the program object
	void addShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType);

	// links and validates the shader program and sets it into pipeline
	void buildShader(string vertexShaderPath, string fragmentShaderPath);

	// enables the shader for the gameObject
	void useShader();

private:
	GLuint shaderProgram;

};
```

 - Checks for transformation, i.e. only do transformation when translate or scale change

```cpp
// checks for changes in translate
void GameObject::setTranslate(float translateXValue, float translateYValue, float translateZValue)
{
	float oldX{}, oldY{}, oldZ{};
	// checks to see if there is any change in translation then set to new transform
	if (translateXValue != oldX || translateYValue != oldY || translateZValue != oldZ)
	{
		// do some translation here...
		translator = translate(mat4(1.0f), vec3(translateXValue, translateYValue, translateZValue));
		isSetTransform = true;
	}
	oldX = translateXValue;
	oldY = translateYValue;
	oldZ = translateZValue;
}
```
```cpp
// checks for changes in scale
void GameObject::setScale(float scaleXValue, float scaleYValue, float scaleZValue)
{
	float oldX{}, oldY{}, oldZ{};
	// checks to see if there is any change in scale then set to new transform
	if (scaleXValue != oldX || scaleYValue != oldY || scaleZValue != oldZ)
	{
		// do some scaling here...
		scaler = scale(mat4(1.0f), vec3(cosf(scaleXValue) / 2, sinf(scaleYValue) / 2, scaleZValue));
		isSetTransform = true;
	}
	oldX = scaleXValue;
	oldY = scaleYValue;
	oldZ = scaleZValue;
}
```
```cpp

void GameObject::setTransform()
{
	....
}

void GameObject::applyTransform()
{
	....
}

void GameObject::render()
{
	gameObjectProperties.shader->useShader();

	if (isSetTransform)
	{
		// set custom transformations
		setTransform();
		isSetTransform = false;
	}

	applyTransform();
	
	.....
}
```

</details>

<details>
    <summary><h4>Results</h4></summary>

   ### Before
     
| <p><img src="https://user-images.githubusercontent.com/34424878/218225202-c0adc299-055d-452e-a1d0-7b9c538325e7.png" width=500 height=300/></p>  |
|---|

  ### After
  
| <p><video src="https://user-images.githubusercontent.com/34424878/222951473-858de257-d30f-4849-b6ff-5cc8d9804b39.mp4" width=100 height=100/></p>  |
|---|
| *Please note the pauses in between are happening because the transform is done when it is necessary, in my project once user presses 't' or 's' it would do some transform, hence the little pauses in between* |
	

  </details> 
	
</blockquote>
</details> 

##  

<details>

<summary>  <h2>Part ... [Status: ❌]</h2>  </summary>

<blockquote>

<details>

<summary><h4>Goal</h4></summary>

  

Goal

</details>

<details>

<summary><h4>UML Diagram</h4></summary>

  

Diagram

</details>

<details>

<summary><h4>Code Implementation</h4></summary>

  

Code

</details>

<details>

<summary><h4>Results</h4></summary>

  

Results

</details>

</blockquote>

</details>

##  
