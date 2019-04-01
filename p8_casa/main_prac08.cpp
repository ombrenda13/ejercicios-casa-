/*-------------------------------------------------------- - */
/* ----------------  PRATICA_8_Casa --------------------------*/
/*-----------------    2019-2   ---------------------------*/
/*------------- Computación gráfica e interacción humano computadora-------*/
/*BRENDA ORTIZ MARTÍNEZ
GRUPO 4 TEORIA COMPUTACIÓN GRÁFICA
INSTRUCCIONES
EL MOUSE ES LA CAMÁRA.
FLECHAS DEL TECLADO:
	<rotar izquierda
	> rotar derecha
	^ rotar hacia arriba
	v rotar hacia abajo
	TECLA A: movimiento izquierda
	TECLA D: movimiento derecha
	TECLA W: acercar
	TECLA S: alejar
---------------*/
#define STB_IMAGE_IMPLEMENTATION
#include "esfera.h"
#include "camera.h"
#include <stb_image.h>

Esfera my_sphere(1.0f);

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor *monitors;
GLuint VBO, VAO, EBO;

//Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
double	lastX = 0.0f,
lastY = 0.0f;
bool firstMouse = true;

//Timing
double	deltaTime = 0.0f,
lastFrame = 0.0f;

//Lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

void myData(void);
void display(void);
void getResolution(void);
void animate(void);

//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rotX = 0.0f,
rotY=0.0f;

//Texture
unsigned int texture1, texture2; 
void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;

	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;

}


void myData() 
{
	float vertices[] = { 
		// positions          // texture coords
												//front
		0.5f, 0.5f, 0.5f,		1.0f,1.0f, //V0
		0.5f, -0.5f, 0.5f,		1.0f,0.0f,	//V1
		-0.5f, -0.5f, 0.5f,		0.0f,0.0f,//V2 
		-0.5f, 0.5f, 0.5f,		0.0f,1.0f,//V3

												// Trasera
		0.5f, -0.5f, -0.5f,		1.0f,1.0f,	//V4 
		0.5f, 0.5f, -0.5f,		1.0f,0.0f,	//V5 
		-0.5f, 0.5f, -0.5f,		0.0f,0.0f,	//V6 
		-0.5f, -0.5f, -0.5f,    0.0f,1.0f,//V7

												//Izq
		-0.5f, 0.5f, 0.5f,		1.0f, 1.0f,	//V8  
		-0.5f, 0.5f, -0.5f,		1.0f,0.0f,	//V9
		-0.5f, -0.5f, -0.5f,	0.0f,0.0f,	//V10
		-0.5f, -0.5f, 0.5f,		0.0f,1.0f,	//V11

												//Der
		0.5f, 0.5f, 0.5f,		1.0f, 1.0f,	//V12
		0.5f, 0.5f, -0.5f,		1.0f,0.0f,//V13
		0.5f, -0.5f, -0.5f,		0.0f,0.0f,//V14
		0.5f, -0.5f, 0.5f,		0.0f,1.0f,	//V15

												//Sup
		-0.5f, 0.5f, 0.5f,		4.0f, 4.0f,	//V16
		0.5f, 0.5f, 0.5f,		4.0f,0.0f,	//V17
		0.5f, 0.5f, -0.5f,		0.0f,0.0f,		//V18
		-0.5f, 0.5f, -0.5f,		0.0f,4.0f,	//V19

												//Inf
		-0.5f, -0.5f, 0.5f,		1.0f, 1.0f,	//V20
		-0.5f, -0.5f, -0.5f,	1.0f,0.0f,	//V21
		0.5f, -0.5f, -0.5f,		0.0f,0.0f,		//V22
		0.5f, -0.5f, 0.5f,		0.0f,1.0f		//V22
	};
	unsigned int indices[] = {
		0
	
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); //El atributo 0 corresponde a la posicion
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); //El atributo 1 corresponde a la textura
	glEnableVertexAttribArray(1);


	// load and create a texture 
	// -------------------------

	// texture 1
	// ---------
	glGenTextures(1, &texture1); //Leemos una textura
	

	glBindTexture(GL_TEXTURE_2D, texture1); //tipo 2D 
	//glBindTexture(GL_TEXTURE_2D, texture2);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //filtro 
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// load image, create texture and generate mipmaps
	int width, height, nrChannels; 
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char *data = stbi_load("Texturas/piedra.jpg", &width, &height, &nrChannels, 0); 
	if (data)
	{
	
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D); 
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	
	

	//texture 2
	// ---------
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	data = stbi_load("Texturas/ajedrez.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);



}

void animate(void)
{

}

void display(void)
{
	// bind textures on corresponding texture units
	glActiveTexture(GL_TEXTURE0);			//activar la textura a 0. 
	glBindTexture(GL_TEXTURE_2D, texture1); 
	
	//Shader projectionShader("shaders/shader_light.vs", "shaders/shader_light.fs");
	Shader projectionShader("shaders/shader_texture.vs", "shaders/shader_texture.fs");
	Shader lampShader("shaders/shader_lamp.vs", "shaders/shader_lamp.fs");

	//To Use Lighting
	projectionShader.use();
	projectionShader.setInt("texture1", 0); 
	

	// create transformations and Projection
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection
	
	glm::mat4 modelTemp = glm::mat4(1.0f); //Temp


	//Use "projection" to include Camera
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	view = camera.GetViewMatrix();
	view = glm::translate(view, glm::vec3(movX, movY, movZ));
	view = glm::rotate(view, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::rotate(view, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
	// pass them to the shaders
	projectionShader.setVec3("viewPos", camera.Position);
	projectionShader.setMat4("model", model);
	projectionShader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	projectionShader.setMat4("projection", projection);


	glBindVertexArray(VAO);


	modelTemp = model;
	model = glm::scale(model, glm::vec3(1, 2, 1));
	projectionShader.setMat4("model", model);
	//projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 1.0f));
	glDrawArrays(GL_QUADS, 0, 24); //pata central
	model = modelTemp;

	model = glm::translate(model, glm::vec3(0, 1.5, 0));//colocar la mesa encima de la pata 
	modelTemp = model;
	model = glm::scale(model, glm::vec3(4,1,4));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24); //mesa parte superior
	model = modelTemp;
	
	

	model = glm::translate(model, glm::vec3(0, .5, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(3, .02,3));
	projectionShader.setMat4("model", model);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	projectionShader.setInt("texture2", 1);
	glDrawArrays(GL_QUADS, 0, 24); //tablero
	model = modelTemp;


	glBindVertexArray(0);

}

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 8", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resize);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//To Enable capture of our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glewInit();


	//Mis funciones
	//Datos a utilizar
	myData();
	my_sphere.init();
	glEnable(GL_DEPTH_TEST);

	// render loop
	// While the windows is not closed
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// input
		// -----
		my_input(window);
		animate();

		// render
		// Backgound color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Mi función de dibujo
		display();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		rotX -= 0.6f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		rotX += 0.6f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rotY -= 0.6f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rotY += 0.6f;

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}