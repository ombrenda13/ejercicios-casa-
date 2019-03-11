/*---------------------------------------------------------*/
/* ----------------   Práctica 5 --------------------------*/
/*-----------------    2019-2   ---------------------------*/
/*------------- Computación gráfica e interacción humano computadora 
BRENDA ORTIZ MARTÍNEZ 
GRUPO 4 
INSTRUCCIONES:
	flecha izquierda--rotar todo el brazo izquierda
	flecha derecha-- rotar  todo el brazo  derecha
	flecha arriba-- rotar  todo el brazo  hacia arriba
	flecha abajo--- rotar  todo el brazo  hacia abajo
	TECLA A: movimiento  todo el brazo  izquierda
	TECLA D: movimiento  todo el brazo  derecha
	TECLA W: acercar brazo
	TECLA S: alejar brazo

	TECLA T----rota bicep
	TECLA SHIFT(DERECHA)+ TECLA T---regresa bicep a posicion inicial

	TECLA Y--rota antebrazo
	TECLA SHIFT(DERECHA)+ TECLA Y--regresa antebrazo a posicion inicial

	TECLA U--rota muñeca
	TECLA SHIFT(DERECHA)+ TECLA U--regresa muñeca a posicion inicial
	

	TECLA SHIFT(DERECHA)+ TECLA I--mueve pulgar
	TECLA I --regresa pulgar a posicion inicial
	
	TECLA SHIFT(DERECHA)+ TECLA H--mueve indice
	TECLA H--regresa indice a posicion inicial
	
	TECLA SHIFT(DERECHA)+ TECLA J--mueve dedo medio
	TECLA J--regresa dedo medio a posición inicial
	
	TECLA SHIFT(DERECHA)+ TECLA K--mueve dedo anular
	TECLA K--regresa dedo anular a posicion inicial
	
	TECLA SHIFT(DERECHA)+ TECLA L--mueve dedo meñique
	TECLA L--regresa dedo meñique a posicion inicial
	




---------------*/
#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader_m.h>

#include <iostream>

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor *monitors;
GLuint VBO, VAO, EBO;

void myData(void);
void display(void);
void getResolution(void);

//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rotX = 0.0f,
rotY = 0.0f;

float angHombro = 0.0;
float angCodo = 0.0;
float angMuñeca = 0.0;
float angPu = 0.0, angIn = 0.0, angMed = 0.0, angAnu = 0.0, angMeñ = 0.0;


void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

void myData()
{	
		GLfloat vertices[] = {
		//Position				//Color
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V0 - Frontal
		0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V1
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V5
		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V4

		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V2 - Trasera
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 0.0f,	//V3
		-0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V7
		0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V6

		-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	//V4 - Izq
		-0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 1.0f,	//V7
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	//V3
		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	//V0

		0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	//V5 - Der
		0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	//V1
		0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	//V2
		0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	//V6

		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	//V4 - Sup
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	//V5
		0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	//V6
		-0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	//V7

		-0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	//V0 - Inf
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	//V3
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	//V2
		0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	//V1
	};

	unsigned int indices[] =	//I am not using index for this session
	{
		0
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	//Para trabajar con indices (Element Buffer Object)
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}

void display(void)
{
	//Shader myShader("shaders/shader.vs", "shaders/shader.fs");
	Shader projectionShader("shaders/shader_projection.vs", "shaders/shader_projection.fs");

	projectionShader.use();

	// create transformations and Projection
	glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
	glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection


	//Use "projection" in order to change how we see the information
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	//Use "view" in order to affect all models
	view = glm::translate(view, glm::vec3(movX, movY, movZ));
	view = glm::rotate(view, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::rotate(view, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
	// pass them to the shaders
	projectionShader.setMat4("model", model);
	projectionShader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	projectionShader.setMat4("projection", projection);


	glBindVertexArray(VAO);




	//projectionShader.setMat4("model", model);
	//projectionShader.setVec3("aColor", glm::vec3(1, 1, 0));
	
	//glDrawArrays(GL_QUADS, 0, 24);//hombro derecho 
	//model = glm::rotate(model,glm::radians(angHombro),glm::vec3(0,0,1));


	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.5, 2.5, 1));// para hacer escalas al objeto x,y,z
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24); //cabeza

	model = glm::translate(model, glm::vec3(0, -.5, 0));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(0.5, 0.5, 1));// para hacer escalas al objeto x,y,z
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24); //cuello

	model = glm::translate(model, glm::vec3(0, -2.5, 0));
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(4, 4, 1));// para hacer escalas al objeto x,y,z
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24); //torso

	model = glm::translate(model, glm::vec3(0, -0.65, 0));
	projectionShader.setVec3("aColor", glm::vec3(2.5f, 2.5f, 0.0f));
	model = glm::scale(model, glm::vec3(1, .3, 1));// para hacer escalas al objeto x,y,z
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24); //cinturon

	model = glm::translate(model, glm::vec3(.35, -2, 0));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	model = glm::scale(model, glm::vec3(.3, 3, 1));// para hacer escalas al objeto x,y,z
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24); //pierna derecha 

	model = glm::translate(model, glm::vec3(-2.3, 0, 0));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	model = glm::scale(model, glm::vec3(1, 1, 1));// para hacer escalas al objeto x,y,z
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24); //pierna izquierda

	model = glm::translate(model, glm::vec3(-.85, -.7, 0));
	model = glm::scale(model, glm::vec3(2.7, 0.4, 1));// para hacer escalas al objeto x,
	projectionShader.setVec3("aColor", glm::vec3(1.02f, 0.5f, 0.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24); //pie izq

	model = glm::translate(model, glm::vec3(1.48, 0, 0));
	model = glm::scale(model, glm::vec3(1, 1, 1));// para hacer escalas al objeto x,
	projectionShader.setVec3("aColor", glm::vec3(1.02f, 0.5f, 0.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24); //pierna izquierda


	//hombro
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(2, -2.35, 0));
	projectionShader.setVec3("aColor", glm::vec3(1, 1, 0));
	projectionShader.setMat4("model", model);

	glDrawArrays(GL_QUADS, 0, 24);
	model = glm::rotate(model, glm::radians(angHombro), glm::vec3(0, 0, 1));

	model = glm::translate(model, glm::vec3(1.5, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(2, 1, .8));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 1.0f));
	glDrawArrays(GL_QUADS, 0, 24); //bicep
	model = modelTemp;


	model = glm::translate(model, glm::vec3(1, 0, 0));//generamos pivote para la rotacion del antebrazo
	model = glm::rotate(model, glm::radians(angCodo), glm::vec3(0, 1, 0));//recordar poner la rotación despues del pivote(articulacion)
	model = glm::translate(model, glm::vec3(1.5, 0, 0));//se suma la traslacion con la pasada
	modelTemp = model;
	model = glm::scale(model, glm::vec3(3, 1, .7));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24); //antebrazo
	model = modelTemp;
	//palma

	model = glm::translate(model, glm::vec3(1.5, 0, 0));//generamos pivote para la rotacion del antebrazo
	model = glm::rotate(model, glm::radians(angMuñeca), glm::vec3(0, 1, 0));//recordar poner la rotación despues del pivote(articulacion)
	model = glm::translate(model, glm::vec3(.5, 0, 0));//se suma la traslacion con la pasada
	modelTemp = model;
	model = glm::scale(model, glm::vec3(1, 1, .6));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;

	modelTemp2 = model;

	//pulgar
	model = glm::translate(model, glm::vec3(-0.35, 0.5, 0));//pivote articulacion
	model = glm::rotate(model, glm::radians(angPu), glm::vec3(1, 0, 0));

	model = glm::translate(model, glm::vec3(0, 0.15, 0));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.3, .3));//escalas
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.8f, 0.0f, 9.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;

	//pulgar arriba
	model = glm::translate(model, glm::vec3(0.0, 0.15, 0));//pivote articulacion
	model = glm::rotate(model, glm::radians(angPu*0.7f), glm::vec3(1, 0, 0));
	model = glm::translate(model, glm::vec3(0, 0.15, 0));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3));//escalas
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1, 1, .6));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp2;

	//indice

	model = glm::translate(model, glm::vec3(0.5, 0.38, 0));//pivote articulacion
	model = glm::rotate(model, glm::radians(angIn), glm::vec3(0, -1, 0));
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));//escalas
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1, 0.4, 0));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;
	//inice2
	model = glm::translate(model, glm::vec3(0.15, 0, 0));//pivote articulacion
	model = glm::rotate(model, glm::radians(angIn*0.7f), glm::vec3(0, -1, 0));
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));//escalas
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.3, 0.7, .2));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;
	//indice3
	model = glm::translate(model, glm::vec3(0.15, 0, 0));//pivote articulacion
	model = glm::rotate(model, glm::radians(angIn*0.7f), glm::vec3(0, -1, 0));
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));//escalas
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1, 0.2, 0));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp2;


	//medio
	model = glm::translate(model, glm::vec3(0.5, 0.125, 0));//pivote articulacion
	model = glm::rotate(model, glm::radians(angMed), glm::vec3(0, -1, 0));
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.3));//escalas
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1, 0.7, 0.3));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;
	//medio2
	model = glm::translate(model, glm::vec3(0.15, 0, 0));//pivote articulacion
	model = glm::rotate(model, glm::radians(angMed*0.7f), glm::vec3(0, -1, 0));
	model = glm::translate(model, glm::vec3(0.25, 0, 0));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.3));//escalas
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.2, 0.8, 1));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;
	//medio3
	model = glm::translate(model, glm::vec3(0.15, 0, 0));//pivote articulacion
	model = glm::rotate(model, glm::radians(angMed*0.7f), glm::vec3(0, -1, 0));
	model = glm::translate(model, glm::vec3(0.25, 0, 0));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.3));//escalas
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1, 0.7, 0.3));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp2;

	//anular
	model = glm::translate(model, glm::vec3(0.5, -0.125, 0));//pivote articulacion
	model = glm::rotate(model, glm::radians(angAnu), glm::vec3(0, -1, 0));
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));//escalas
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0, .5, 1));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;
	//anular2
	model = glm::translate(model, glm::vec3(0.15, 0, 0));//pivote articulacion
	model = glm::rotate(model, glm::radians(angAnu*0.7f), glm::vec3(0, -1, 0));
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));//escalas
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1, 0.9, .5));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;
	//anular3
	model = glm::translate(model, glm::vec3(0.15, 0, 0));//pivote articulacion
	model = glm::rotate(model, glm::radians(angAnu*0.7f), glm::vec3(0, -1, 0));
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));//escalas
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0, .5, 1));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp2;

	//meñique
	model = glm::translate(model, glm::vec3(0.5, -0.375, 0));//pivote articulacion
	model = glm::rotate(model, glm::radians(angMeñ), glm::vec3(0, -1, 0));
	model = glm::translate(model, glm::vec3(0.1, 0, 0));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.2, 0.25, 0.3));//escalas
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(.4, .5, .7));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;
	//meñique2
	model = glm::translate(model, glm::vec3(0.1, 0, 0));//pivote articulacion
	model = glm::rotate(model, glm::radians(angMeñ*0.7f), glm::vec3(0, -1, 0));
	model = glm::translate(model, glm::vec3(0.1, 0, 0));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.2, 0.25, 0.3));//escalas
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(2, 0.5, .9));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;
	//meñique3
	model = glm::translate(model, glm::vec3(0.1, 0, 0));//pivote articulacion
	model = glm::rotate(model, glm::radians(angMeñ*0.7f), glm::vec3(0, -1, 0));
	model = glm::translate(model, glm::vec3(0.1, 0, 0));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.2, 0.25, 0.3));//escalas
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(.4, .5, .7));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;

	//hombro
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(-2, -2.35, 0));
	projectionShader.setVec3("aColor", glm::vec3(1, 1, 0));
	projectionShader.setMat4("model", model);

	glDrawArrays(GL_QUADS, 0, 24);
	model = glm::rotate(model, glm::radians(angHombro), glm::vec3(0, 0, -1));

	model = glm::translate(model, glm::vec3(-1.5, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(2, 1, .8));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 1.0f));
	glDrawArrays(GL_QUADS, 0, 24); //bicep
	model = modelTemp;


	model = glm::translate(model, glm::vec3(-1, 0, 0));//generamos pivote para la rotacion del antebrazo
	model = glm::rotate(model, glm::radians(angCodo), glm::vec3(0, -1, 0));//recordar poner la rotación despues del pivote(articulacion)
	model = glm::translate(model, glm::vec3(-1.5, 0, 0));//se suma la traslacion con la pasada
	modelTemp = model;
	model = glm::scale(model, glm::vec3(3, 1, .7));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24); //antebrazo
	model = modelTemp;
	//palma

	model = glm::translate(model, glm::vec3(-1.5, 0, 0));//generamos pivote para la rotacion del antebrazo
	model = glm::rotate(model, glm::radians(angMuñeca), glm::vec3(0, -1, 0));//recordar poner la rotación despues del pivote(articulacion)
	model = glm::translate(model, glm::vec3(-.5, 0, 0));//se suma la traslacion con la pasada
	modelTemp = model;
	model = glm::scale(model, glm::vec3(1, 1, .6));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;

	modelTemp2 = model;

	//pulgar
	model = glm::translate(model, glm::vec3(-0.35, 0.5, 0));//pivote articulacion
	model = glm::rotate(model, glm::radians(angPu), glm::vec3(1, 0, 0));

	model = glm::translate(model, glm::vec3(0, 0.15, 0));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.3, .3));//escalas
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.8f, 0.0f, 9.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;

	//pulgar2
	model = glm::translate(model, glm::vec3(0.0, 0.15, 0));//pivote articulacion
	model = glm::rotate(model, glm::radians(angPu*0.7f), glm::vec3(1, 0, 0));
	model = glm::translate(model, glm::vec3(0, 0.15, 0));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3));//escalas
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1, 1, .6));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp2;

	//indice

	model = glm::translate(model, glm::vec3(-0.5, 0.38, 0));//pivote articulacion
	model = glm::rotate(model, glm::radians(angIn), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));//escalas
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1, 0.4, 0));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;
	//inice2
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));//pivote articulacion
	model = glm::rotate(model, glm::radians(angIn*0.7f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));//escalas
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.3, 0.7, .2));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;
	//indice3
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));//pivote articulacion
	model = glm::rotate(model, glm::radians(angIn*0.7f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));//escalas
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1, 0.2, 0));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp2;


	//medio
	model = glm::translate(model, glm::vec3(-0.5, 0.125, 0));//pivote articulacion
	model = glm::rotate(model, glm::radians(angMed), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.3));//escalas
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1, 0.7, 0.3));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;
	//medio2
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));//pivote articulacion
	model = glm::rotate(model, glm::radians(angMed*0.7f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-0.25, 0, 0));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.3));//escalas
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.2, 0.8, 1));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;
	//medio3
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));//pivote articulacion
	model = glm::rotate(model, glm::radians(angMed*0.7f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-0.25, 0, 0));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.3));//escalas
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1, 0.7, 0.3));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp2;

	//anular
	model = glm::translate(model, glm::vec3(-0.5, -0.125, 0));//pivote articulacion
	model = glm::rotate(model, glm::radians(angAnu), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));//escalas
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0, .5, 1));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;
	//anular2
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));//pivote articulacion
	model = glm::rotate(model, glm::radians(angAnu*0.7f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));//escalas
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1, 0.9, .5));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;
	//anular3
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));//pivote articulacion
	model = glm::rotate(model, glm::radians(angAnu*0.7f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));//escalas
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0, .5, 1));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp2;

	//meñique
	model = glm::translate(model, glm::vec3(-0.5, -0.375, 0));//pivote articulacion
	model = glm::rotate(model, glm::radians(angMeñ), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-0.1, 0, 0));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.2, 0.25, 0.3));//escalas
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(.4, .5, .7));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;
	//meñique2
	model = glm::translate(model, glm::vec3(-0.1, 0, 0));//pivote articulacion
	model = glm::rotate(model, glm::radians(angMeñ*0.7f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-0.1, 0, 0));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.2, 0.25, 0.3));//escalas
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(2, 0.5, .9));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;
	//meñique3
	model = glm::translate(model, glm::vec3(-0.1, 0, 0));//pivote articulacion
	model = glm::rotate(model, glm::radians(angMeñ*0.7f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-0.1, 0, 0));
	projectionShader.setMat4("model", model);
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.2, 0.25, 0.3));//escalas
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(.4, .5, .7));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;



	//modeltemp2 nos permite guardar los dedos por individual para no volver a temp

//	model = glm::translate(model, glm::vec3(5, 0, 0));
	//modelTemp = model;//guardo la matriz
	//projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	//model = glm::scale(model, glm::vec3(5, 5, 5));
	//projectionShader.setMat4("model", model);
	//glDrawArrays(GL_QUADS, 0, 24);
	//model = modelTemp;//con esto ya no afecta la escala,  pero el pivote de la traslación sigue siendo el de esta figura

	glBindVertexArray(0);//es el buffer debe ir hasta el final

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

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 5", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
	glfwSetWindowPos(window, 0, 30);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize);

	glewInit();


	//Mis funciones
	//Datos a utilizar
	myData();
	glEnable(GL_DEPTH_TEST);

    // render loop
    // While the windows is not closed
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        my_input(window);

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
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
        glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		movY += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		movY -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		rotX += 0.18f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		rotX -= 0.18f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rotY -= 0.2f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rotY += 0.2f;
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {

		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
			if (angHombro < 90) {
				angHombro += 0.2f;
			}
		}
		else {
			if (angHombro > -90) {
				angHombro -= 0.2f;
			}

		}

	}
		if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {

			if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
				if (angCodo < 0) {
					angCodo += 0.8f;
				}
			}
			else {
				if (angCodo > -140) {
					angCodo -= 0.8f;
				}

			}


		}



		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {

			if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
				if (angMuñeca< 20) {
					angMuñeca += 0.8f;
				}
			}
			else {
				if (angMuñeca > -40) {
					angMuñeca -= 0.8f;
				}

			}


		}


		if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {

			if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
				if (angPu < 40) {
					angPu += 0.8f;
				}
			}
			else {
				if (angPu > 0) {
					angPu -= 0.8f;
				}

			}


		}

		if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {

			if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
				if (angIn < 90) {
					angIn += 0.8f;
				}
			}
			else {
				if (angIn > 0) {
					angIn -= 0.8f;
				}
			}
		}
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {

			if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
				if (angMed < 90) {
					angMed += 0.8f;
				}
			}
			else {
				if (angMed > 0) {
					angMed -= 0.8f;
				}
			}
		}
		if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {

			if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
				if (angAnu < 90) {
					angAnu += 0.8f;
				}
			}
			else {
				if (angAnu > 0) {
					angAnu -= 0.8f;
				}
			}
		}
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {

			if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
				if (angMeñ < 90) {
					angMeñ += 0.8f;
				}
			}
			else {
				if (angMeñ > 0) {
					angMeñ -= 0.8f;
				}
			}
		}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
    // Set the Viewport to the size of the created window
    glViewport(0, 0, width, height);
}