# Real-Time Rendering 4

## Rendering Engine Project

<details>
  <summary><h2>Part 1 [Status: ✅]</h2></summary>
  
  <hr/>
  
  ### Goal
  1. The goal of this part of the project was to refactor the code in such ways so that we can encapsuulate the data and its functionality, i.e. Separate/break-down the functionality of a GameObject and a Shader (ShaderTechnique) into different classes.
  2. Show the relationship between a [GameObject](https://github.com/MehadND/real-time-rendering-4/blob/0cfb8ef77be6ad0702a423c0a3d99f58f9a4429c/gt41samples%20(1)/gt41samples/renderingproject/GameObject.h) & a [Shader](https://github.com/MehadND/real-time-rendering-4/blob/0cfb8ef77be6ad0702a423c0a3d99f58f9a4429c/gt41samples%20(1)/gt41samples/renderingproject/ShaderTechnique.h)
  
  <hr/>
  
  ### UML Diagram: Showing Relationship between GameObject class & ShaderTechnique class
  ![UML Diagram: Showing Relationship between GameObject class & ShaderTechnique class](https://github.com/MehadND/real-time-rendering-4/blob/main/gt41samples%20(1)/gt41samples/renderingproject/part1%20UML%20diagram.png?raw=true)
    
  > As we can see in the UML diagram above, there is a relationship that exists between a GameObject and a ShaderTechnique. This relationship can be described as <i>has-a</i>. This basically means that a GameObject (instance) has-a ShaderTechnique or in other words an object has-a shader. 
  
  #### Code Implementation
  ```cpp
  // This class inherits members and functions of ShaderTechnique class as private members and functions
  class GameObject : private ShaderTechnique
  ```
     
  <hr/>
  
  ### Results 
  
  - #### Before
  
  | <p><img src="https://user-images.githubusercontent.com/34424878/218224866-a321e4ff-0c1e-4f6a-8bab-207495e6703e.png"/></p>  | <ul><li>In this the scene, one shader is applied to every object that is being rendered.</li><li>No classes, everything is in one (.cpp) file.</li><li>The path of the shader files are hard coded, so cannot be changed for different objects.</li></ul>   |
  |:-:|:--|

  
  
  
  - #### After
  
  | <p><img src="https://user-images.githubusercontent.com/34424878/218225202-c0adc299-055d-452e-a1d0-7b9c538325e7.png"/></p>  | <ul><li>Multiple objects are being rendered with each of them having their own shader.</li><li>In this part of project, there 2 main functionalities/classes<ul><li>GameObject</li><li>ShaderTechnique.</li></ul></li><li>`buildShader(vertexShaderPath, fragmentShaderPath)` function has 2 paramters for allwong users to enter file path of the shaders to be used.</li></ul>  |
  |:-:|:--|
  

  
<hr/>


</details>

  
<details>
 <summary><h2>Part 2 [Status: ❌]</h2></summary>
</details>

<details>
 <summary><h2>Part ... [Status: ❌]</h2></summary>
</details>
 
