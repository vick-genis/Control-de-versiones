//Práctica 2 semestre 2024-2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crearían acá
static const char* vShaderRojo = "shaders/shaderRojo.vert";
static const char* fShaderRojo = "shaders/shaderRojo.frag";
static const char* vShaderVerde = "shaders/shaderVerde.vert";
static const char* fShaderVerde = "shaders/shaderVerde.frag";
static const char* vShaderAzul = "shaders/shaderAzul.vert";
static const char* fShaderAzul = "shaders/shaderAzul.frag";
static const char* vShaderVerde2 = "shaders/shaderVerde2.vert";
static const char* fShaderVerde2 = "shaders/shaderVerde2.frag";
static const char* vShaderCafe = "shaders/shaderCafe.vert";
static const char* fShaderCafe = "shaders/shaderCafe.frag";

float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = { 
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3
		
	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

GLfloat cubo_vertices[] = {
	// front
	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	// back
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
	GLfloat vertices_letras[] = {	//0
			//X			Y			Z			R		G		B
			/*-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
			1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
			1.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
			/*1.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
			-1.0f,  1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
			-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,*/

			//GENERANDO LA LETRA L vértices utilizados E,J,I,F,G,H
			//Primer triangulo
			//X    Y      Z   R       G      B
			-0.8f, 0.8f,0.0f,0.0f,0.0f,1.0f,//E
			-0.6f,0.8f, 0.0f,0.0f,0.0f,1.0f, //J
			-0.6f,0.4f, 0.0f,0.0f,0.0f,1.0f,//I
			//Segundo triangulo
			-0.8f, 0.8f,0.0f,0.0f,0.0f,	1.0f,//E
			-0.6f,0.4f, 0.0f,0.0f,0.0f,	1.0f,//I
			-0.8f, 0.2f,0.0f,0.0f,0.0f,	1.0f,//F
			//Tercer triangulo
			-0.8f, 0.2f,0.0f,0.0f,0.0f,	1.0f,//F
			-0.6f,0.4f, 0.0f,0.0f,0.0f,	1.0f,//I
			-0.2f,0.2f, 0.0f,0.0f,0.0f,	1.0f,//G
			//Cuarto triangulo
			-0.6f,0.4f, 0.0f,0.0f,0.0f,	1.0f,//I
			-0.2f,0.2f, 0.0f,0.0f,0.0f,	1.0f, //G
			-0.2f,0.4f, 0.0f,0.0f,0.0f,	1.0f,//H

	};
	MeshColor *letras = new MeshColor();
	letras->CreateMeshColor(vertices_letras,72);
	meshColorList.push_back(letras);

	GLfloat vertices_triangulorojo[] = {//1
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		
	};

	MeshColor* triangulorojo = new MeshColor();
	triangulorojo->CreateMeshColor(vertices_triangulorojo, 18);
	meshColorList.push_back(triangulorojo);

	GLfloat vertices_cuadradoverde[] = {//2
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* cuadradoverde = new MeshColor();
	cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 36);
	meshColorList.push_back(cuadradoverde);

	GLfloat vertices_letras_V[] = { //3
	
		//GENERANDO LA LETRA V vertices utilizados K,N,O,L,M,C1,E1,K1
		//Primer triangulo
		0.1f,0.8f, 0.0f,1.0f, 0.6f,	1.0f,//K
		0.36f,0.80f, 0.0f,1.0f,0.6f,1.0f, //N
		0.45f,0.35f,0.0f,1.0f,0.6f,1.0f,//E1
		//Segundo triangulo
		0.1f,0.8f, 0.0f,1.0f, 0.6f,	1.0f,//K
		0.45f,0.35f,0.0f,1.0f,0.6f,1.0f,//E1
		0.4f,0.20f, 0.0f,1.0f,0.6f,1.0f,//M
		//Tercer triangulo
		0.45f,0.35f,0.0f,1.0f, 0.6f,1.0f,//E1
		0.4f,0.20f, 0.0f,1.0f, 0.6f,1.0f,//M
		0.55f,0.35f,0.0f,1.0f, 0.6f,1.0f,//K1
		//Cuarto triangulo
		0.4f,0.20f, 0.0f,1.0f, 0.6f,1.0f,//M
		0.55f,0.35f,0.0f,1.0f, 0.6f,1.0f,//K1
		0.6f,0.2f,0.0f,1.0f, 0.6f,1.0f,//C1
		//Quinto triangulo
		0.55f,0.35f,0.0f,1.0f, 0.6f,1.0f,//K1
		0.6f,0.2f,0.0f,1.0f, 0.6f,1.0f,//C1
		0.9f,0.79f,0.0f,1.0f,0.6f,	1.0f,//L
		//Sexto triangulo
		0.55f,0.35f,0.0f,1.0f, 0.6f,1.0f,//K1
		0.6f,0.8f,0.0f,1.0f, 0.6f,1.0f,//O
		0.9f,0.79f,0.0f,1.0f,0.6f,1.0f,//L

	};
	MeshColor* letraV = new MeshColor();
	letraV->CreateMeshColor(vertices_letras_V, 108);
	meshColorList.push_back(letraV);

	GLfloat vertices_letras_G[] = { //4

		//GENERANDO LA LETRA G vertices utilizados P,W,J1,I1,H1,G1,F1,Z,Q,K1,A1,R,S,C1,D1,B1,T,V,U
		//Primer triangulo
		-0.4f,-0.2f, 0.0f,1.0f, 0.0f,1.0f,//P
		-0.40f,-0.28f, 0.0f,1.0f, 0.0f,1.0f, //W
		-0.66f,-0.29f, 0.0f,1.0f, 0.0f,1.0f,//G1
		//Segundo triangulo
		-0.4f,-0.2f, 0.0f,1.0f, 0.0f,1.0f,//P
		-0.85f,-0.19f, 0.0f,1.0f, 0.0f,1.0f, //Q
		-0.66f,-0.29f, 0.0f,1.0f, 0.0f,1.0f,//G1
		//Tercer triangulo
		-0.75f,-0.29f, 0.0f,1.0f, 0.0f,1.0f,//Z
		-0.85f,-0.19f, 0.0f, 1.0f, 0.0f,1.0f,//Q
		-0.66f,-0.29f, 0.0f,1.0f, 0.0f,1.0f,//G1
		//Cuarto triangulo
		-0.75f,-0.29f, 0.0f,1.0f, 0.0f,1.0f,//Z
		-0.85f,-0.19f, 0.0f, 1.0f, 0.0f,1.0f,//Q
		-0.75f,-0.43f, 0.0f,1.0f, 0.0f,1.0f,//R
		//5 triangulo
		-0.75f,-0.43f, 0.0f,1.0f, 0.0f,1.0f,//R
		-0.85f,-0.80f, 0.0f,1.0f, 0.0f,1.0f, //S
		-0.85f,-0.19f, 0.0f,1.0f, 0.0f,1.0f,//Q
		//6 triangulo
		-0.75f,-0.43f, 0.0f,1.0f, 0.0f,1.0f,//R
		-0.85f,-0.80f, 0.0f,1.0f, 0.0f,1.0f, //S
		-0.76f,-0.60f, 0.0f,1.0f, 0.0f,1.0f,//A1
		//Triangulo 7
		-0.57f,-0.80f, 0.0f,1.0f, 0.0f,1.0f,//D1
		-0.85f,-0.80f, 0.0f, 1.0f, 0.0f,1.0f,//S
		-0.76f,-0.60f, 0.0f,1.0f, 0.0f,1.0f,//A1
		//Triangulo 8
		-0.57f,-0.80f, 0.0f,1.0f, 0.0f,1.0f,//D1
		-0.4f,-0.6f, 0.0f,1.0f, 0.0f,1.0f, //N1
		-0.76f,-0.60f, 0.0f,1.0f, 0.0f,1.0f,//A1
		//Triangulo 9
		-0.57f,-0.80f, 0.0f,1.0f, 0.0f,1.0f,//D1
		-0.4f,-0.6f, 0.0f,1.0f, 0.0f,1.0f, //N1
		-0.3f,-0.8f, 0.0f,1.0f, 0.0f,1.0f,//T
		//Triangulo 10
		-0.29f,-0.46f, 0.0f,1.0f, 0.0f,1.0f,//U
		-0.4f,-0.6f, 0.0f,1.0f, 0.0f,1.0f, //N1
		-0.3f,-0.8f, 0.0f,1.0f, 0.0f,1.0f,//T
		//Triangulo 11
		-0.29f, -0.46f, 0.0f,1.0f, 0.0f,1.0f,//U
		-0.4f, -0.6f, 0.0f, 1.0f, 0.0f,1.0f,//N1
		-0.4f, -0.53f, 0.0f,1.0f, 0.0f,1.0f,//M1
		//Triangulo 12
		-0.29f, -0.46f, 0.0f,1.0f, 0.0f,1.0f,//U
		-0.5f, -0.46f, 0.0f,1.0f, 0.0f,1.0f, //V
		-0.4f, -0.53f, 0.0f,1.0f, 0.0f,1.0f,//M1
		//Triangulo 13
		-0.51f, -0.53f, 0.0f,1.0f, 0.0f,1.0f,//B1
		-0.5f, -0.46f, 0.0f,1.0f, 0.0f,1.0f,//V
		-0.4f, -0.53f, 0.0f,1.0f, 0.0f,1.0f,//M1

	};
	MeshColor* letraG = new MeshColor();
	letraG->CreateMeshColor(vertices_letras_G, 306);
	meshColorList.push_back(letraG);
}


void CreateShaders()
{

	Shader *shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide 0
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader *shader2 = new Shader();//shader para usar color como parte del VAO: letras  1
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	// SHADER COLOR ROJO 2
	Shader *shaderRojo = new Shader();
	shaderRojo->CreateFromFiles(vShaderRojo, fShaderRojo);
	shaderList.push_back(*shaderRojo);

	// SHADER COLOR VERDE 3
	Shader* shaderVerde = new Shader();
	shaderVerde->CreateFromFiles(vShaderVerde, fShaderVerde);
	shaderList.push_back(*shaderVerde);

	// SHADER COLOR AZUL 4
	Shader* shaderAzul = new Shader();
	shaderAzul->CreateFromFiles(vShaderAzul, fShaderAzul);
	shaderList.push_back(*shaderAzul);

	// SHADER COLOR VERDE FUERTE 5
	Shader* shaderVerde2 = new Shader();
	shaderVerde2->CreateFromFiles(vShaderVerde2, fShaderVerde2);
	shaderList.push_back(*shaderVerde2);

	// SHADER COLOR CAFE 6
	Shader* shaderCafe = new Shader();
	shaderCafe->CreateFromFiles(vShaderCafe, fShaderCafe);
	shaderList.push_back(*shaderCafe);

}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	
	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad
	glm::mat4 model1(1.0);

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		
		/*
		//Para las letras hay que usar el segundo set de shaders con índice 1 en ShaderList 
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();

		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));//SIEMPRE DEBE ESTAR DECLARADO, PARA MANDAR OBJETOS DENTRO DE LA PANTALLA Z DEBE SER NEGATIVO Y LOS 0,0 SIGNIFICA QUE ESTA EN EL ORIGEN
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor();//MANDO A DIBUJAR EL OBJETO CERO (TRIANGULO AZUL) A MESH COLOR
		
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));//SIEMPRE DEBE ESTAR DECLARADO, PARA MANDAR OBJETOS DENTRO DE LA PANTALLA Z DEBE SER NEGATIVO Y LOS 0,0 SIGNIFICA QUE ESTA EN EL ORIGEN
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[3]->RenderMeshColor();//

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));//SIEMPRE DEBE ESTAR DECLARADO, PARA MANDAR OBJETOS DENTRO DE LA PANTALLA Z DEBE SER NEGATIVO Y LOS 0,0 SIGNIFICA QUE ESTA EN EL ORIGEN
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[4]->RenderMeshColor();//
		*/
		
		//QUITAR ESTE PARA EJERCICIO 2
		//Para el cubo y la pirámide se usa el primer set de shaders con índice 0 en ShaderList
		shaderList[2].useShader(); 
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		angulo += 0.01;

		//BASE
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.6f, -4.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//TECHO
		model1 = glm::mat4(1.0);
		model1 = glm::translate(model1, glm::vec3(0.0f, 0.3f, -1.0f));
		model1 = glm::scale(model1, glm::vec3(1.0f, 1.0f, 1.0f));
		//model1 = glm::rotate(model1, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		shaderList[4].useShader();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model1));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//VENTANA DERECHA
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.2f, -0.4f, -2.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//model1 = glm::rotate(model1, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		shaderList[3].useShader();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//VENTANA IZQUIERDA
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.2f, -0.4f, -2.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//model1 = glm::rotate(model1, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		shaderList[3].useShader();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();
		
		//PUERTA
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.8f, -2.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.4f, 0.3f));
		//model1 = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		shaderList[3].useShader();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//TRONCO DERECHO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -1.0f, -2.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.37f, 0.0f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		shaderList[6].useShader();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//ARBOL DERECHO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -0.6f, -1.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.5f, 0.0f));
		//model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		shaderList[5].useShader();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//TRONCO IZQUIERDO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.75f, -1.0f, -2.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.37f, 0.0f));
		shaderList[6].useShader();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//ARBOL IZQUIERDO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.75f, -0.6f, -1.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.5f, 0.0f));
		shaderList[5].useShader();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		/*model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//shaderList[0].useShader(); // Usa el índice correspondiente al nuevo shader
		meshList[0]->RenderMesh();
		*/
		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslación
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACIÓN //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/