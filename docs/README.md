# Welcome to our Projects Webpage
 Author: Gabriel Walbron & Adrien Jacquin
  
## Project  
 The goal of our project is to implement a .OBJ file loader in order to read 3D object files.
   
 The steps are the following :
   - Parse the file
   - If inclusion of .MTL texture file -> parse .MTL file 
   - Generating the object through OpenGL

### Solution 1 
 The first solution of this project is using C++ and OpenGL library to load and show the 3D object based on an OBJ file. 
Find out the code [here](https://github.com/GabrielWal/obj-loader/tree/master/OBJLoader)
 
### Solution 2
 The second solution of this project is using javascript and WebGL library in order to load and show in the browser a 3D object based on an OBJ file.
This solution is actually using WebGL through the babylonjs Library.
Find out more about babylonjs [here](https://www.babylonjs.com/)

Try out our browser OBJ loader [here](https://gabrielwal.github.io/obj-loader/loader.html)

To have an example of a vertex representation [click here](https://gabrielwal.github.io/obj-loader/triangle.html)

