# Real-Time Rendering 4

## Rendering Engine Project

<h3>Setup</h3>
   
   1. Download the GitHub Repo.
   2. Open the `real-time-rendering` solution in Visual Studio.
   3. Set the `renderingproject` project as Startup project.
   4. Finally, run the `ProjectRenderer.cpp` file.
   

## Part 1 [Status: ✅]
  
<details>
   <summary><h3>Goal</h3></summary>

   > #### Goal Of Projct <br/><br/>▷ The goal of this part of the project was to refactor the code in such ways so that we can encapsulate the data and its functionality, <br/>i.e. Break down the functionality of a GameObject and a Shader into different classes.
</details>

<details>
    <summary><h3>UML Diagram</h3></summary>
   
   <br/>
   
   As we can see in the UML diagram below, there is a relationship that exists between a GameObject and a ShaderTechnique. This relationship can be described as <i>has-a</i> relationship between the two classes. In basic terms, this means that a single game object **has a** shader attached to it.
   
   <br/>
   
   ![UML Diagram: Showing Relationship between GameObject class & ShaderTechnique class](https://user-images.githubusercontent.com/34424878/218233715-c4c1ceb1-90b4-4640-a164-d878f9ceac1d.png)
  
</details>

<details>
   <summary><h3>Code Implementation</h3></summary>
   
   ### Inhertiance Showcase
   
  ```cpp
  // This class (GameObject) inherits members and functions of ShaderTechnique class as private members and functions
  class GameObject : private ShaderTechnique
  ```
   
   ### GameObject Class (.h file)
   
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
   
   ### ShaderTechnique Class (.h file)
   
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
    <summary><h3>Results</h3></summary>
   
   ### Before
     
| <p><img src="https://user-images.githubusercontent.com/34424878/218224866-a321e4ff-0c1e-4f6a-8bab-207495e6703e.png" width=300 height=200/></p>  |
|---|
| - In this the scene, one shader is applied to every object that is being rendered.  <br><br>- No classes, everything is in one (.cpp) file. <br><br>- The path of the shader files are hard coded, so cannot be changed for different objects. |

  ### After
  
| <p><img src="https://user-images.githubusercontent.com/34424878/218225202-c0adc299-055d-452e-a1d0-7b9c538325e7.png" width=300 height=200/></p>  |
|---|
| - Multiple objects are being rendered with each of them having their own shader.  <br><br>- In this part of project, the different functionalities are divided into their own separate classes ( [GameObject](https://github.com/MehadND/real-time-rendering-4/blob/0cfb8ef77be6ad0702a423c0a3d99f58f9a4429c/gt41samples%20(1)/gt41samples/renderingproject/GameObject.h) & [Shader](https://github.com/MehadND/real-time-rendering-4/blob/0cfb8ef77be6ad0702a423c0a3d99f58f9a4429c/gt41samples%20(1)/gt41samples/renderingproject/ShaderTechnique.h) ) <br><br>- `buildShader(vertexShaderPath, fragmentShaderPath)` function has 2 paramters for allwong users to enter file paths of the (vertex & fragment) shaders to be used for an object. |

</details>


## Part 2 [Status: ❌]
  
<details>
   <summary><h3>Goal</h3></summary>
</details>


## Part ... [Status: ❌]
  
<details>
   <summary><h3>Goal</h3></summary>
</details>


 

 
