//práctica 3: Modelado Geométrico y Cámara Sintética.
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
#include <gtc\random.hpp>
//clases para dar orden y limpieza al còdigo
#include"Mesh.h"
#include"Shader.h"
#include"Sphere.h"
#include"Window.h"
#include"Camera.h"
//tecla E: Rotar sobre el eje X
//tecla R: Rotar sobre el eje Y
//tecla T: Rotar sobre el eje Z

using std::vector;

//Dimensiones de la ventana
const float toRadians = 3.14159265f / 180.0; //grados a radianes
const float PI = 3.14159265f;
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;
Camera camera;
Window mainWindow;
vector<Mesh*> meshList;
vector<MeshColor*> meshColorList;
vector<Shader>shaderList;

//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
Sphere sp = Sphere(1.0, 20, 20); //recibe radio, slices, stacks

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
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}

// Pirámide triangular regular
void CrearPiramideTriangular()
{
	unsigned int indices_piramide_triangular[] = {
			/*0,2,3,
			0,1,2,
			1,2,3,
			0,1,3*/
			0,2,3,
			0,1,2,
			1,2,3,
			0,1,3 
		
	};
	GLfloat vertices_piramide_triangular[] = {
		/*-0.5f, -0.5f, 0.0f,
		0.6f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		-0.0f,0.0f,1.0f*/
		3.0f, 1.0f, 0.0f,//A 0
		1.2f, 2.8f, 0.0f, //B 1
		0.5f,0.38f,0.0f, //E 2
		1.62f, 1.39f, 2.02f//ARISTA 3
	};
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices_piramide_triangular, indices_piramide_triangular, 12, 12);
	meshList.push_back(obj1);

}

void CrearTriangulosPequenos() {
	// Coordenadas de vértices para los triángulos amarillos pequeños
	GLfloat vertices_triangulos_pequenos[] = {
		// Triángulo pequeño 1
		-0.4f, -0.4f, 0.0f, //0
		-0.2f, -0.4f, 0.0f, //1
		-0.3f, -0.2f, 0.0f, //2
		// Triángulo pequeño 2
		0.2f, -0.4f, 0.0f,  //3
		0.4f, -0.4f, 0.0f, //4
		0.3f, -0.2f, 0.0f, //5
		// Triángulo pequeño 3
		-0.13f, 0.15f, 0.0f,  //6
		0.11f, 0.15f, 0.0f, //7
		0.0f, 0.4f, 0.0f, //8
		// Triángulo pequeño 4
		0.1f, -0.4f, 0.0f, //9
		-0.1f, -0.4f, 0.0f, //10
		0.0f, -0.2f, 0.0f, //11
		// Triángulo pequeño 5
		-0.24f, -0.2f, 0.0f, //12
		-0.06f, -0.2f, 0.0f, //13
		-0.15f, -0.4f, 0.0f, //14
		// Triángulo pequeño 6
		0.06f, -0.2f, 0.0f, //15
		0.25f, -0.2f, 0.0f, //16
		0.15f, -0.4f, 0.0f, //17
		// Triángulo pequeño 7
		-0.06f, -0.14f, 0.0f, //18
		-0.3f, -0.14f, 0.0f, //19
		-0.2f, 0.1f, 0.0f, //20
		// Triángulo pequeño 8
		0.19f, 0.1f, 0.0f, //21
		0.03f, -0.14f, 0.0f, //22
		0.31f, -0.14f, 0.0f, //23
		// Triángulo pequeño 9
		0.0f, -0.14f, 0.0f, //24
		-0.12f, 0.1f, 0.0f, //25
		0.12f, 0.09f, 0.0f, //26

	};//27x3

	// Índices para los triángulos pequeños
	unsigned int indices_triangulos_pequenos[] = {
		0, 1, 2, // Triángulo pequeño 1
		3, 4, 5, // Triángulo pequeño 2
		6, 7, 8,  // Triángulo pequeño 3
		9, 10, 11,  // Triángulo pequeño 4
		12, 13, 14,  // Triángulo pequeño 5
		15, 16, 17,  // Triángulo pequeño 6
		18, 19, 20,  // Triángulo pequeño 7
		21, 22, 23,  // Triángulo pequeño 8
		24, 25, 26  // Triángulo pequeño 9
	};//9x3

	Mesh* triangulosPequenos = new Mesh();
	triangulosPequenos->CreateMesh(vertices_triangulos_pequenos, indices_triangulos_pequenos, 81, 27);
	meshList.push_back(triangulosPequenos);
}

void CrearTriangulosPequenos2() {
	GLfloat vertices_triangulos_pequenos[] = {
		// Triángulo pequeño 1
		  1.21f, 2.63f, 0.07f, //0
		  1.28f, 2.24f, 0.54f, //1
		  1.03f, 1.99f, 0.07f, //2
		  // Triángulo pequeño 2
		  1.0f, 1.89f, 0.07f,  //3
		  1.09f, 1.59f, 0.52f, //4
		  0.85f, 1.35f, 0.07f, //5
		  // Triángulo pequeño 3
		  0.82f, 1.27f, 0.05f,  //6
		  0.88f, 0.89f, 0.52f, //7
		  0.63f, 0.59f, 0.062f, //8
		  // Triángulo pequeño 4
		  1.02f, 1.94f, 0.08f, //9
		  1.26f, 2.19f, 0.53f, //10
		  1.1f, 1.65f, 0.53f, //11
		  // Triángulo pequeño 5
		  0.84f, 1.3f, 0.08f, //12
		  1.07f, 1.55f, 0.52f, //13
		  0.9f, 0.94f, 0.52f, //14
		  // Triángulo pequeño 6
		  1.28f, 2.22f, 0.57f, //15
		  1.35f, 1.85f, 1.03f, //16
		  1.13f, 1.67f, 0.57f, //17
		  // Triángulo pequeño 7
		  1.1f, 1.6f, 0.57f, //18
		  1.15f, 1.18f, 1.03f, //19
		  0.91f, 0.9f, 0.56f, //20
		  // Triángulo pequeño 8
		  1.12f, 1.62f, 0.6f, //21
		  1.34f, 1.83f, 1.04f, //22
		  1.17f, 1.24f, 1.03f, //23
		  // Triángulo pequeño 9
		  1.36, 1.84f, 1.07f, //24
		  1.44f, 1.43f, 1.61f, //25
		  1.17f, 1.19f, 1.06f, //26
	};//27x3

	// Índices para los triángulos pequeños
	unsigned int indices_triangulos_pequenos[] = {
		0, 1, 2, // Triángulo pequeño 1
		3, 4, 5, // Triángulo pequeño 2
		6, 7, 8,  // Triángulo pequeño 3
		9, 10, 11,  // Triángulo pequeño 4
		12, 13, 14,  // Triángulo pequeño 5
		15, 16, 17,  // Triángulo pequeño 6
		18, 19, 20,  // Triángulo pequeño 7
		21, 22, 23,  // Triángulo pequeño 8
		24, 25, 26  // Triángulo pequeño 9
	};//9x3

	Mesh* triangulosPequenos2 = new Mesh();
	triangulosPequenos2->CreateMesh(vertices_triangulos_pequenos, indices_triangulos_pequenos, 81, 27);
	meshList.push_back(triangulosPequenos2);
}

void CrearTriangulosPequenos3() {
	
	GLfloat vertices_triangulos_pequenos[] = {
		// Triángulo pequeño 1
		2.86f,1.11f, 0.06f, //0
		2.43f, 1.55f, 0.06f, //1
		2.53f, 1.23f, 0.51f, //2
		// Triángulo pequeño 2
		2.36f, 1.62f, 0.06f,  //3
		2.07f, 1.68f, 0.53f, //4
		1.93f, 2.06f, 0.07f, //5
		// Triángulo pequeño 3
		1.87f, 2.12f, 0.07f,  //6
		1.51f, 2.25f, 0.54f, //7
		1.31f, 2.7f, 0.07f, //8
		// Triángulo pequeño 4
		2.49f, 1.25f, 0.54f,  //9
		2.39f, 1.59f, 0.06f, //10
		2.13f, 1.63f, 0.54f, //11
		// Triángulo pequeño 5
		2.03f, 1.73f, 0.54f,  //12
		1.89f, 2.09f, 0.08f, //13
		1.56f, 2.2f, 0.54f, //14
		// Triángulo pequeño 6
		2.48f, 1.23f, 0.6f,  //12
		2.18f, 1.31f, 1.06f, //13
		2.09f, 1.63f, 0.6f, //14
		// Triángulo pequeño 7
		1.96f, 1.77f, 0.6f,  //12
		1.57f, 1.94f, 1.05f, //13
		1.42f, 2.32f, 0.6f, //14
		// Triángulo pequeño 8
		2.13f, 1.36f, 1.06f,  //12
		2.02f, 1.7f, 0.6f, //13
		1.64f, 1.86f, 1.06f, //14
		// Triángulo pequeño 9
		2.12f, 1.35f, 1.14f,  //12
		1.54f, 1.92f, 1.14f, //13
		1.72f, 1.47f, 1.67f, //14

	};//27x3

	// Índices para los triángulos pequeños
	unsigned int indices_triangulos_pequenos[] = {
		0, 1, 2, // Triángulo pequeño 1
		3, 4, 5, // Triángulo pequeño 2
		6, 7, 8, // Triángulo pequeño 3
		9, 10, 11, // Triángulo pequeño 4
		12, 13, 14, // Triángulo pequeño 5
		15, 16, 17, // Triángulo pequeño 6
		18, 19, 20, // Triángulo pequeño 7
		21, 22, 23, // Triángulo pequeño 8
		24, 25, 26 // Triángulo pequeño 9

	};//9x3

	Mesh* triangulosPequenos = new Mesh();
	triangulosPequenos->CreateMesh(vertices_triangulos_pequenos, indices_triangulos_pequenos, 81, 27);
	meshList.push_back(triangulosPequenos);
}

void CrearTriangulosPequenos4() {
	
	GLfloat vertices_triangulos_pequenos[] = {
		// Triángulo pequeño 1
		0.79f,0.46f, 0.06f, //0
		1.09f, 0.68f, 0.47f, //1
		1.37f, 0.61f, 0.07f, //2
		// Triángulo pequeño 2
		1.47f, 0.64f, 0.07f,  //3
		1.81f, 0.86f, 0.45f, //4
		2.16f, 0.81f, 0.07f, //5
		// Triángulo pequeño 3
		2.24f, 0.83f, 0.06f,  //6
		2.45f, 1.0f, 0.4f, //7
		2.79, 0.96f, 0.05f, //8
		// Triángulo pequeño 4
		1.43f, 0.63f, 0.08f,  //9
		1.15f, 0.7f, 0.47f, //10
		1.69f, 0.82f, 0.43f, //11
		// Triángulo pequeño 5
		2.21f, 0.82f, 0.06f,  //12
		1.87f, 0.88f, 0.44f, //13
		2.4f, 1.01f, 0.44f, //14
		// Triángulo pequeño 6
		1.08f, 0.71f, 0.53f,  //12
		1.37f, 0.95f, 1.0f, //13
		1.71f, 0.85f, 0.48f, //14
		// Triángulo pequeño 7
		1.85f, 0.89f, 0.5f,  //12
		2.11f, 1.12f, 0.96f, //13
		2.45f, 1.03f, 0.47f, //14
		// Triángulo pequeño 8
		1.79f, 0.89f, 0.53f,  //12
		1.42f, 0.96f, 1.0f, //13
		2.01f, 1.11f, 1.0f, //14
		// Triángulo pequeño 9
		1.37f, 0.99f, 1.1f,  //12
		1.61f, 1.26f, 1.67f, //13
		2.02f, 1.14f, 1.08f, //14

	};//27x3
	// Índices para los triángulos pequeños
	unsigned int indices_triangulos_pequenos[] = {
		0, 1, 2, // Triángulo pequeño 1
		3, 4, 5, // Triángulo pequeño 2
		6, 7, 8, // Triángulo pequeño 3
		9, 10, 11, // Triángulo pequeño 4
		12, 13, 14, // Triángulo pequeño 5
		15, 16, 17, // Triángulo pequeño 6
		18, 19, 20, // Triángulo pequeño 7
		21, 22, 23, // Triángulo pequeño 8
		24, 25, 26 // Triángulo pequeño 9

	};//9x3

	Mesh* triangulosPequenos = new Mesh();
	triangulosPequenos->CreateMesh(vertices_triangulos_pequenos, indices_triangulos_pequenos, 81, 27);
	meshList.push_back(triangulosPequenos);
}

void CrearTriangulosPequenos5() {
	GLfloat vertices_triangulos_pequenos[] = {
		// Triángulo pequeño 1
		2.89f,1.04f, 0.0f, //0
		2.29f, 1.48f, 0.0f, //1
		2.15f, 0.87f, 0.0f, //2
		// Triángulo pequeño 2
		2.06f, 0.84f, 0.0f,  //3
		1.63f, 1.31f, 0.0f, //4
		1.34f, 0.67f, 0.0f, //5
		// Triángulo pequeño 3
		1.28f, 0.66f, 0.0f,  //6
		0.93f, 1.15f, 0.0f, //7
		0.7, 0.52f, 0.0f, //8
		// Triángulo pequeño 4
		2.1f, 0.9f, 0.0f,  //9
		2.21f, 1.44f, 0.0f, //10
		1.72f, 1.34f, 0.0f, //11
		// Triángulo pequeño 5
		1.31f, 0.73f, 0.0f,  //12
		1.55f, 1.32f, 0.0f, //13
		0.97f, 1.2f, 0.0f, //14
		// Triángulo pequeño 6
		2.23f, 1.58f, 0.0f,  //12
		1.8f, 2.05f, 0.0f, //13
		1.72f, 1.47f, 0.0f, //14
		// Triángulo pequeño 7
		1.56f, 1.43f, 0.0f,  //12
		1.18f, 1.89f, 0.0f, //13
		0.98f, 1.34f, 0.0f, //14
		// Triángulo pequeño 8
		1.63f, 1.47f, 0.0f,  //12
		1.72f, 2.03f, 0.0f, //13
		1.25f, 1.93f, 0.0f, //14
		// Triángulo pequeño 9
		1.75f, 2.13f, 0.0f,  //12
		1.31f, 2.59f, 0.0f, //13
		1.16f, 2.0f, 0.0f, //14

	};//27x3
	// Índices para los triángulos pequeños
	unsigned int indices_triangulos_pequenos[] = {
		0, 1, 2, // Triángulo pequeño 1
		3, 4, 5, // Triángulo pequeño 2
		6, 7, 8, // Triángulo pequeño 3
		9, 10, 11, // Triángulo pequeño 4
		12, 13, 14, // Triángulo pequeño 5
		15, 16, 17, // Triángulo pequeño 6
		18, 19, 20, // Triángulo pequeño 7
		21, 22, 23, // Triángulo pequeño 8
		24, 25, 26 // Triángulo pequeño 9

	};//9x3

	Mesh* triangulosPequenos = new Mesh();
	triangulosPequenos->CreateMesh(vertices_triangulos_pequenos, indices_triangulos_pequenos, 81, 27);
	meshList.push_back(triangulosPequenos);
}

void CrearCaras() {
	// Coordenadas de vértices para la pirámide
	GLfloat vertices_piramide[] = {
		// Triángulo base
		-0.5f, -0.5f, -0.5f,  // V0
		 0.5f, -0.5f, -0.5f,  // V1
		 0.5f, -0.5f,  0.5f,  // V2
		-0.5f, -0.5f,  0.5f,  // V3

		// Vértice superior (vértice de la pirámide)
		 0.0f,  0.5f,  0.0f   // V4
	};

	// Índices para los triángulos de la pirámide
	unsigned int indices_piramide[] = {
		0, 1, 2,  // Base - Triángulo 1
		0, 2, 3,  // Base - Triángulo 2
		0, 1, 4,  // Lado 1
		1, 2, 4,  // Lado 2
		2, 3, 4,  // Lado 3
		3, 0, 4   // Lado 4
	};

	// Crear el objeto MeshColor para la pirámide
	Mesh* piramideMesh = new Mesh();
	piramideMesh->CreateMesh(vertices_piramide, indices_piramide, 15, 18);
	meshList.push_back(piramideMesh);
}

/*
Crear cilindro, cono y esferas con arreglos dinámicos vector creados en el Semestre 2023 - 1 : por Sánchez Pérez Omar Alejandro
*/
void CrearCilindro(int res, float R) {

	//constantes utilizadas en los ciclos for
	int n, i;
	//cálculo del paso interno en la circunferencia y variables que almacenarán cada coordenada de cada vértice
	GLfloat dt = 2 * PI / res, x, z, y = -0.5f;

	vector<GLfloat> vertices;
	vector<unsigned int> indices;

	//ciclo for para crear los vértices de las paredes del cilindro
	for (n = 0; n <= (res); n++) {
		if (n != res) {
			x = R * cos((n)*dt);
			z = R * sin((n)*dt);
		}
		//caso para terminar el círculo
		else {
			x = R * cos((0) * dt);
			z = R * sin((0) * dt);
		}
		for (i = 0; i < 6; i++) {
			switch (i) {
			case 0:
				vertices.push_back(x);
				break;
			case 1:
				vertices.push_back(y);
				break;
			case 2:
				vertices.push_back(z);
				break;
			case 3:
				vertices.push_back(x);
				break;
			case 4:
				vertices.push_back(0.5);
				break;
			case 5:
				vertices.push_back(z);
				break;
			}
		}
	}

	//ciclo for para crear la circunferencia inferior
	for (n = 0; n <= (res); n++) {
		x = R * cos((n)*dt);
		z = R * sin((n)*dt);
		for (i = 0; i < 3; i++) {
			switch (i) {
			case 0:
				vertices.push_back(x);
				break;
			case 1:
				vertices.push_back(-0.5f);
				break;
			case 2:
				vertices.push_back(z);
				break;
			}
		}
	}

	//ciclo for para crear la circunferencia superior
	for (n = 0; n <= (res); n++) {
		x = R * cos((n)*dt);
		z = R * sin((n)*dt);
		for (i = 0; i < 3; i++) {
			switch (i) {
			case 0:
				vertices.push_back(x);
				break;
			case 1:
				vertices.push_back(0.5);
				break;
			case 2:
				vertices.push_back(z);
				break;
			}
		}
	}

	//Se generan los indices de los vértices
	for (i = 0; i < vertices.size(); i++) indices.push_back(i);

	//se genera el mesh del cilindro
	Mesh* cilindro = new Mesh();
	cilindro->CreateMeshGeometry(vertices, indices, vertices.size(), indices.size());
	meshList.push_back(cilindro);
}

//función para crear un cono
void CrearCono(int res, float R) {

	//constantes utilizadas en los ciclos for
	int n, i;
	//cálculo del paso interno en la circunferencia y variables que almacenarán cada coordenada de cada vértice
	GLfloat dt = 2 * PI / res, x, z, y = -0.5f;

	vector<GLfloat> vertices;
	vector<unsigned int> indices;

	//caso inicial para crear el cono
	vertices.push_back(0.0);
	vertices.push_back(0.5);
	vertices.push_back(0.0);

	//ciclo for para crear los vértices de la circunferencia del cono
	for (n = 0; n <= (res); n++) {
		x = R * cos((n)*dt);
		z = R * sin((n)*dt);
		for (i = 0; i < 3; i++) {
			switch (i) {
			case 0:
				vertices.push_back(x);
				break;
			case 1:
				vertices.push_back(y);
				break;
			case 2:
				vertices.push_back(z);
				break;
			}
		}
	}
	vertices.push_back(R * cos(0) * dt);
	vertices.push_back(-0.5);
	vertices.push_back(R * sin(0) * dt);


	for (i = 0; i < res + 2; i++) indices.push_back(i);

	//se genera el mesh del cono
	Mesh* cono = new Mesh();
	cono->CreateMeshGeometry(vertices, indices, vertices.size(), res + 2);
	meshList.push_back(cono);
}

//función para crear pirámide cuadrangular unitaria
void CrearPiramideCuadrangular()
{
	vector<unsigned int> piramidecuadrangular_indices = {
		0,3,4,
		3,2,4,
		2,1,4,
		1,0,4,
		0,1,2,
		0,2,4

	};
	vector<GLfloat> piramidecuadrangular_vertices = {
		0.5f,-0.5f,0.5f,
		0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,0.5f,
		0.0f,0.5f,0.0f,
	};
	Mesh* piramide = new Mesh();
	piramide->CreateMeshGeometry(piramidecuadrangular_vertices, piramidecuadrangular_indices, 15, 18);
	meshList.push_back(piramide);
}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader* shader2 = new Shader();
	shader2->CreateFromFiles(vShaderColor, fShader);
	shaderList.push_back(*shader2);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	//Cilindro y cono reciben resolución (slices, rebanadas) y Radio de circunferencia de la base y tapa

	CrearCubo();//índice 0 en MeshList
	CrearPiramideTriangular();//índice 1 en MeshList
	CrearTriangulosPequenos(); //2
	CrearTriangulosPequenos3();//3
	CrearTriangulosPequenos2();//4
	CrearTriangulosPequenos4();//5
	CrearTriangulosPequenos5();//6
	CrearCaras();//4
	CrearCilindro(5, 1.0f);//índice 2 en MeshList
	CrearCono(25, 2.0f);//índice 3 en MeshList
	CrearPiramideCuadrangular();//índice 4 en MeshList
	CreateShaders();



	/*Cámara se usa el comando: glm::lookAt(vector de posición, vector de orientación, vector up));
	En la clase Camera se reciben 5 datos:
	glm::vec3 vector de posición,
	glm::vec3 vector up,
	GlFloat yaw rotación para girar hacia la derecha e izquierda
	GlFloat pitch rotación para inclinar hacia arriba y abajo
	GlFloat velocidad de desplazamiento,
	GlFloat velocidad de vuelta o de giro
	Se usa el Mouse y las teclas WASD y su posición inicial está en 0,0,1 y ve hacia 0,0,-1.
	*/

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.3f);


	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	GLuint uniformView = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	//glm::mat4 projection = glm::ortho(-1, 1, -1, 1, 1, 10);

	//Loop mientras no se cierra la ventana
	sp.init(); //inicializar esfera
	sp.load();//enviar la esfera al shader

	glm::mat4 model(1.0);//Inicializar matriz de Modelo 4x4

	glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f); //inicializar Color para enviar a variable Uniform;

	while (!mainWindow.getShouldClose())
	{

		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;
		//Recibir eventos del usuario
		glfwPollEvents();
		//Cámara
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		//Limpiar la ventana
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		uniformView = shaderList[0].getViewLocation();
		uniformColor = shaderList[0].getColorLocation();

		//TRIANGULO NEGRO BASE
		model = glm::mat4(1.0);//matriz identidad
		//Traslación inicial para posicionar en -Z a los objetos
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		//otras transformaciones para el objeto
		//model = glm::scale(model, glm::vec3(1.0f,1.0f,1.0f));
		//model = glm::rotate(model, glm::radians(mainWindow.getrotax()), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(mainWindow.getrotay()), glm::vec3(0.0f, 1.0f, 0.0f));  //al presionar la tecla Y se rota sobre el eje y
		//model = glm::rotate(model, glm::radians(mainWindow.getrotaz()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//la línea de proyección solo se manda una vez a menos que en tiempo de ejecución
		//se programe cambio entre proyección ortogonal y perspectiva
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		color = glm::vec3(0.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		meshList[1]->RenderMesh();

		/*//NUEVE TRIANGULOS PEQUEÑOS CARA AMARILLA
		model = glm::mat4(1.0);//matriz identidad
		//Traslación inicial para posicionar en -Z a los objetos
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.01f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.033f));
		//otras transformaciones para el objeto
		//model = glm::scale(model, glm::vec3(1.0f,1.0f,0.5f));
		model = glm::rotate(model, glm::radians(mainWindow.getrotax()), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getrotay()), glm::vec3(0.0f, 1.0f, 0.0f));  //al presionar la tecla Y se rota sobre el eje y
		model = glm::rotate(model, glm::radians(mainWindow.getrotaz()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//la línea de proyección solo se manda una vez a menos que en tiempo de ejecución
		//se programe cambio entre proyección ortogonal y perspectiva
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		color = glm::vec3(1.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		meshList[2]->RenderMesh();*/

		//NUEVE TRIANGULOS PEQUEÑOS CARA ROSA
		model = glm::mat4(1.0);//matriz identidad
		//Traslación inicial para posicionar en -Z a los objetos
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.01f));
		//model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -0.033f));
		//otras transformaciones para el objeto
		//model = glm::scale(model, glm::vec3(1.0f,0.0f,1.0f));
		//model = glm::rotate(model, glm::radians(mainWindow.getrotax()), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(mainWindow.getrotay()), glm::vec3(0.0f, 1.0f, 0.0f));  //al presionar la tecla Y se rota sobre el eje y
		//model = glm::rotate(model, glm::radians(mainWindow.getrotaz()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//la línea de proyección solo se manda una vez a menos que en tiempo de ejecución
		//se programe cambio entre proyección ortogonal y perspectiva
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		color = glm::vec3(1.0f, 0.7f, 0.7f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		meshList[3]->RenderMesh();

		//NUEVE TRIANGULOS PEQUEÑOS CARA MORADA
		model = glm::mat4(1.0);//matriz identidad
		//Traslación inicial para posicionar en -Z a los objetos
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.1f));
		//model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -0.033f));
		//otras transformaciones para el objeto
		//model = glm::scale(model, glm::vec3(1.0f,0.0f,1.0f));
		//model = glm::rotate(model, glm::radians(mainWindow.getrotax()), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(mainWindow.getrotay()), glm::vec3(0.0f, 1.0f, 0.0f));  //al presionar la tecla Y se rota sobre el eje y
		//model = glm::rotate(model, glm::radians(mainWindow.getrotaz()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//la línea de proyección solo se manda una vez a menos que en tiempo de ejecución
		//se programe cambio entre proyección ortogonal y perspectiva
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		color = glm::vec3(0.7f, 0.7f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		meshList[4]->RenderMesh();

		//NUEVE TRIANGULOS PEQUEÑOS CARA VERDE
		model = glm::mat4(1.0);//matriz identidad
		//Traslación inicial para posicionar en -Z a los objetos
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.2f));
		//model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -0.033f));
		//otras transformaciones para el objeto
		//model = glm::scale(model, glm::vec3(1.0f,0.0f,1.0f));
		//model = glm::rotate(model, glm::radians(mainWindow.getrotax()), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(mainWindow.getrotay()), glm::vec3(0.0f, 1.0f, 0.0f));  //al presionar la tecla Y se rota sobre el eje y
		//model = glm::rotate(model, glm::radians(mainWindow.getrotaz()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//la línea de proyección solo se manda una vez a menos que en tiempo de ejecución
		//se programe cambio entre proyección ortogonal y perspectiva
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		color = glm::vec3(0.7f, 1.0f, 0.7f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		meshList[5]->RenderMesh();

		//NUEVE TRIANGULOS PEQUEÑOS CARA AMARILLA
		model = glm::mat4(1.0);//matriz identidad
		//Traslación inicial para posicionar en -Z a los objetos
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.05f));
		//model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -0.033f));
		//otras transformaciones para el objeto
		//model = glm::scale(model, glm::vec3(1.0f,0.0f,1.0f));
		//model = glm::rotate(model, glm::radians(mainWindow.getrotax()), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(mainWindow.getrotay()), glm::vec3(0.0f, 1.0f, 0.0f));  //al presionar la tecla Y se rota sobre el eje y
		//model = glm::rotate(model, glm::radians(mainWindow.getrotaz()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//la línea de proyección solo se manda una vez a menos que en tiempo de ejecución
		//se programe cambio entre proyección ortogonal y perspectiva
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		color = glm::vec3(1.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color)); //para cambiar el color del objetos
		meshList[6]->RenderMesh();
	
		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}


