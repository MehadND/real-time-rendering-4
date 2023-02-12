# Real-Time Rendering 4

## Rendering Engine Project

#### Steps for running the project:
   1. Download the GitHub Repo.
   2. Open the `real-time-rendering` solution in Visual Studio.
   3. Set the `renderingproject` project as Startup project.
   4. Finally, run the `ProjectRenderer.cpp` file.

<h2>Part 1 [Status: ✅]</h2>
  
<details>
   <summary><h4>Goal</h4></summary>

   #### ▷ The goal of this part of the project was to refactor the code in such ways so that we can encapsulate the data and its functionality, 

   i.e. Break down the functionality of a GameObject and a Shader (ShaderTechnique) into different classes.
</details>

<details>
    <summary><h4>UML Diagram</h4></summary>
   
   > As we can see in the UML diagram below, there is a relationship that exists between a GameObject and a ShaderTechnique. This relationship can be described as <i>has-a</i> relationship between the two classes. In basic terms, this means that a single game object **has a** shader attached to it.
   
   ![UML Diagram: Showing Relationship between GameObject class & ShaderTechnique class](https://user-images.githubusercontent.com/34424878/218233715-c4c1ceb1-90b4-4640-a164-d878f9ceac1d.png)
  
  #### Code Implementation
  ```cpp
  // This class (GameObject) inherits members and functions of ShaderTechnique class as private members and functions
  class GameObject : private ShaderTechnique
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

<hr/>

<h2>Part 2 [Status: ❌]</h2>
  
<details>
   <summary><h4>Goal</h4></summary>
</details>

<hr/>

<h2>Part ... [Status: ❌]</h2>
  
<details>
   <summary><h4>Goal</h4></summary>
</details>

<hr/>

 

 
