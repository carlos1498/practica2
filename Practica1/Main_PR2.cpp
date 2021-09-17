#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificación de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 2", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificación de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

	Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
		//TRAPECIO TRIANUGLO 
		-0.3f,  0.8f, 0.0f,    1.0f,1.0f,1.0f,  // top right 00
		-0.6f, 0.2f, 0.0f,    1.0f,1.0f,0.0f,  // bottom right 01
		-0.9f, 0.2f, 0.0f,   1.0f,0.0f,1.0f,  // bottom left 02
		-0.8f,  0.8f, 0.0f,   1.0f,1.0f,0.0f, // top left 03
		-0.2f, 0.2f, 0.0f, 1.0f,1.0f,0.0f, // top left 04
		//TRIANGULO 
		0.5f, 0.9f, 0.0f,  1.0f,1.0f,1.0f,//ALTO TRIANGULO 05
		0.2f, 0.2f, 0.0f, 1.0f,1.0f,1.0f,//fondo izquierdo 06
		0.9f, 0.2f, 0.0f, 1.0f,1.0f,1.0f,//fondo derecho 07
		//pentagono
		-0.3f,  -0.5f, 0.0f,   0.0f,1.0f,1.0f,  // top right 08
		-0.6f, -0.5f, 0.0f,    0.0f,1.0f,0.0f,  // top1 right 09
		-0.8f, -0.8f, 0.0f,   0.0f,0.0f,1.0f,  // bottom left 10
		-0.9f,  -0.5f, 0.0f,   0.0f,1.0f,0.0f, // top left 11
		-0.4f, -0.8f, 0.0f, 0.0f,1.0f,0.0f, // bottom right 12
		-0.6f, -0.2f, 0.0f, 0.0f,1.0f,0.0f, //Punta mayor 13
		//ROMBO
		0.5f, -0.1f, 0.0f,  1.0f,1.0f,0.0f,// punta centro arriba 14 
		0.5, -0.9f, 0.0f, 1.0f,1.0f,0.0f,// punta centro abajo 15
		0.2f, -0.5f, 0.0f, 1.0f,1.0f,0.0f,// punta izquierda 16
		0.8f, -0.5f, 0.0f, 1.0f,1.0f,0.0f,// punta derecha 17
	};
	unsigned int indices[] = {  // note that we start from 0!
		3,2,1,// second Triangle
		0,1,3,
		2,3,1,//TRAPECIO TRIANGULO 1
		0,1,3,//TRAPECIO TRIANGULO 2
		0, 1,4, //Trapecio triangulo 3
		//TRIANGULO
		5, 6, 7,
		//pentagono
		//P. trianguLo 1
		11, 10,9, 
		//P TRIANGULO 2
		10, 9,12,
		//P TRIANGULO 3
		9, 12, 8,
		//p triangulo 4
		11, 13, 8, 
		//rombo
		14, 16, 15, 17,
	};



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT,0);
		//glDrawArrays(GL_LINE_LOOP,0,4);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)(3 * sizeof(GLfloat)));
		//TRAPECIO PRIMER TRIANUGLO
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)(6 * sizeof(GLfloat)));
		//TRAPECIO SEGUNDO TRIANGULO
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)(9 * sizeof(GLfloat)));
		//TRAPECIO tercer TRIANGULO
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)(12 * sizeof(GLfloat)));
		//triangulo
		glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, (GLvoid*)(15 * sizeof(GLfloat)));
		//pentagono
		// pentagono 1T
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)(18 * sizeof(GLfloat)));
		//p. 2T
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)(21 * sizeof(GLfloat)));
		//P 3T
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)(24 * sizeof(GLfloat)));
		//p 4T
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)(27 * sizeof(GLfloat)));
		// rombo lineas
		glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, (GLvoid*)(30 * sizeof(GLfloat)));
		glBindVertexArray(0);
		



		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}