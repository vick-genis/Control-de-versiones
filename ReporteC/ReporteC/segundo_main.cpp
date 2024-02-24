#include <stdio.h>
#include <glew.h>
#include <glfw3.h>
#include <cstdlib>
#include <random>
#include <string.h>

//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 600;

GLuint VAO, VBO, shader;

//Vertex Shader
static const char* vShader = "						\n\
#version 330										\n\
layout (location =0) in vec3 pos;					\n\
void main()											\n\
{													\n\
	gl_Position=vec4(pos.x,pos.y,pos.z,1.0f); 			\n\
}";

//Fragment Shader
static const char* fShader = "						\n\
#version 330										\n\
out vec4 color;										\n\
void main()											\n\
{													\n\
	color = vec4(1.0f,1.0f,0.0f,1.0f);	 			\n\
}";

void CrearTriangulo()
{
	GLfloat vertices[] = {
		//GENERANDO LA LETRA L vertices utilizados E,J,I,F,G,H
		//Primer triangulo
		-0.8f, 0.8f,0.0f,//E
		-0.6f,0.8f, 0.0f, //J
		-0.6f,0.4f, 0.0f,//I
		//Segundo triangulo
		-0.8f, 0.8f,0.0f,//E
		-0.6f,0.4f, 0.0f,//I
		-0.8f, 0.2f,0.0f,//F
		//Tercer triangulo
		-0.8f, 0.2f,0.0f,//F
		-0.6f,0.4f, 0.0f,//I
		-0.2f,0.2f, 0.0f, //G
		//Cuarto triangulo
		-0.6f,0.4f, 0.0f,//I
		-0.2f,0.2f, 0.0f, //G
		-0.2f,0.4f, 0.0f,//H

		//GENERANDO LA LETRA V vertices utilizados K,N,O,L,M,C1,E1,K1
		//Primer triangulo
		0.1f,0.8f, 0.0f,//K
		0.36f,0.80f, 0.0f, //N
		0.45f,0.35f,0.0f,//E1
		//Segundo triangulo
		0.1f,0.8f, 0.0f,//K
		0.45f,0.35f,0.0f,//E1
		0.4f,0.20f, 0.0f,//M
		//Tercer triangulo
		0.45f,0.35f,0.0f,//E1
		0.4f,0.20f, 0.0f,//M
		0.55f,0.35f,0.0f,//K1
		//Cuarto triangulo
		0.4f,0.20f, 0.0f,//M
		0.55f,0.35f,0.0f,//K1
		0.6f,0.2f,0.0f,//C1
		//Quinto triangulo
		0.55f,0.35f,0.0f,//K1
		0.6f,0.2f,0.0f,//C1
		0.9f,0.79f,0.0f,//L
		//Sexto triangulo
		0.55f,0.35f,0.0f,//K1
		0.6f,0.8f,0.0f,//O
		0.9f,0.79f,0.0f,//L

		//GENERANDO LA LETRA G vertices utilizados P,W,J1,I1,H1,G1,F1,Z,Q,K1,A1,R,S,C1,D1,B1,T,V,U
		//Primer triangulo
		-0.4f,-0.2f, 0.0f,//P
		-0.40f,-0.28f, 0.0f, //W
		-0.66f,-0.29f, 0.0f,//G1
		//Segundo triangulo
		-0.4f,-0.2f, 0.0f,//P
		-0.85f,-0.19f, 0.0f, //Q
		-0.66f,-0.29f, 0.0f,//G1
		//Tercer triangulo
		-0.75f,-0.29f, 0.0f,//Z
		-0.85f,-0.19f, 0.0f, //Q
		-0.66f,-0.29f, 0.0f,//G1
		//Cuarto triangulo
		-0.75f,-0.29f, 0.0f,//Z
		-0.85f,-0.19f, 0.0f, //Q
		-0.75f,-0.43f, 0.0f,//R
		//5 triangulo
		-0.75f,-0.43f, 0.0f,//R
		-0.85f,-0.80f, 0.0f, //S
		-0.85f,-0.19f, 0.0f,//Q
		//6 triangulo
		-0.75f,-0.43f, 0.0f,//R
		-0.85f,-0.80f, 0.0f, //S
		-0.76f,-0.60f, 0.0f,//A1
		//Triangulo 7
		-0.57f,-0.80f, 0.0f,//D1
		-0.85f,-0.80f, 0.0f, //S
		-0.76f,-0.60f, 0.0f,//A1
		//Triangulo 8
		-0.57f,-0.80f, 0.0f,//D1
		-0.4f,-0.6f, 0.0f, //N1
		-0.76f,-0.60f, 0.0f,//A1
		//Triangulo 9
		-0.57f,-0.80f, 0.0f,//D1
		-0.4f,-0.6f, 0.0f, //N1
		-0.3f,-0.8f, 0.0f,//T
		//Triangulo 10
		-0.29f,-0.46f, 0.0f,//U
		-0.4f,-0.6f, 0.0f, //N1
		-0.3f,-0.8f, 0.0f,//T
		//Triangulo 11
		-0.29f, -0.46f, 0.0f,//U
		-0.4f, -0.6f, 0.0f, //N1
		-0.4f, -0.53f, 0.0f,//M1
		//Triangulo 12
		-0.29f, -0.46f, 0.0f,//U
		-0.5f, -0.46f, 0.0f, //V
		-0.4f, -0.53f, 0.0f,//M1
		//Triangulo 13
		-0.51f, -0.53f, 0.0f,//B1
		-0.5f, -0.46f, 0.0f, //V
		-0.4f, -0.53f, 0.0f,//M1
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);
	const GLchar* theCode[1];
	theCode[0] = shaderCode;
	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error al compilar el shader %d: %s\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

void CompileShaders()
{
	shader = glCreateProgram();
	if (!shader)
	{
		printf("Error creando el shader");
		return;
	}

	AddShader(shader, vShader, GL_VERTEX_SHADER);
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error al linkear: %s\n", eLog);
		return;
	}

	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error al validar: %s\n", eLog);
		return;
	}
}

int main()
{
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Primer ventana", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}

	int BufferWidth, BufferHeight;
	glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

	glfwMakeContextCurrent(mainWindow);
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glViewport(0, 0, BufferWidth, BufferHeight);
	// Asignar valores de la ventana y coordenadas
	//Asignar Viewport
	glViewport(0, 0, BufferWidth, BufferHeight);
	printf("\n 420053978 \n");
	printf("Version de Opengl: %s \n", glGetString(GL_VERSION));
	printf("Marca: %s \n", glGetString(GL_VENDOR));
	printf("Renderer: %s \n", glGetString(GL_RENDERER));
	printf("Shaders: %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	//Crear triángulo y compilar shaders
	CrearTriangulo();
	CompileShaders();

	// Vamos a utilizar std::random_device para generar una semilla aleatoria
	std::random_device rd;
	std::mt19937 gen(rd());
	float time = 0.0f;
	float cambioColor = 2.0f; // Variable que se encarga de cambiar el color cada 2 segundos

	while (!glfwWindowShouldClose(mainWindow))
	{
		glfwPollEvents();

		// Verificamos si es tiempo de cambiar el color de la pantalla
		if (time >= cambioColor)
		{
			// Generamos colores aleatorios en el rango RGB 0 a 1
			std::uniform_real_distribution<float> dis(0.0f, 1.0f);
			float rojo = dis(gen);
			float verde = dis(gen);
			float azul = dis(gen);

			// Establecer el color de fondo con las variables anteriores
			glClearColor(rojo, verde, azul, 1.0f);

			// Reiniciar el temporizador de GLFW
			time = 0.0f;
		}
		time += 0.01f; //Incrementamos el valor para el siguiente color

		//Limpiar la ventana
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 69);
		glBindVertexArray(0);

		glUseProgram(0);

		glfwSwapBuffers(mainWindow);
	}

	glfwDestroyWindow(mainWindow);
	glfwTerminate();

	return 0;
}
