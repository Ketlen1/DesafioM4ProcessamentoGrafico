

#include <iostream>
#include <string>
#include <assert.h>

//STB IMAGE
#include<stb_image.h>


using namespace std;
//using namespace glm; //para n�o usar glm::

//Classe para manipula��o dos shaders
#include "Shader.h"

//Classe para manipula��o das sprites
#include "Sprite.h"

// Prot�tipo da fun��o de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Prot�tipos das fun��es
GLuint loadTexture(string texturePath);

// Dimens�es da janela (pode ser alterado em tempo de execu��o)
const GLuint WIDTH = 800, HEIGHT = 600;


//Variaveis globais
Sprite spr;

// Fun��o MAIN
int main()
{
	

	// Inicializa��o da GLFW
	glfwInit();

	// Inicializa��o da semente para gera��o de nros aleat�rios
	srand((int)glfwGetTime());

	//Muita aten��o aqui: alguns ambientes n�o aceitam essas configura��es
	//Voc� deve adaptar para a vers�o do OpenGL suportada por sua placa
	//Sugest�o: comente essas linhas de c�digo para desobrir a vers�o e
	//depois atualize (por exemplo: 4.5 com 4 e 5)
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

	//Essencial para computadores da Apple
//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif

	// Cria��o da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Ola Triangulo! -- Rossana", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da fun��o de callback para a janela GLFW
	glfwSetKeyCallback(window, key_callback);

	// GLAD: carrega todos os ponteiros d fun��es da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;

	}

	// Obtendo as informa��es de vers�o
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;
	
	//Habilitar teste de profundidade
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS); //a cada ciclo

	//Habilitar o modo de transpar�ncia (blend - mistura de cores)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



	// Compilando e buildando o programa de shader
	//Shader shader("../shaders/helloTriangle.vs", "../shaders/helloTriangle.fs");
	Shader shader("../shaders/tex.vs", "../shaders/tex.fs");

	GLuint texID1 = loadTexture("../../Textures/cenario/1.png");
	GLuint texID2 = loadTexture("../../Textures/cenario/2.png");
	GLuint texID3 = loadTexture("../../Textures/cenario/3.png");
	GLuint texID5 = loadTexture("../../Textures/cenario/5.png");
	GLuint texID6 = loadTexture("../../Textures/cenario/6.png");
	GLuint texID8 = loadTexture("../../Textures/cenario/8.png");
	GLuint texID10 = loadTexture("../../Textures/cenario/10.png");

	//Cria��o de uma sprite

	Sprite background;
	background.setShader(&shader);
	background.inicializar(texID1, glm::vec3(400.0, 300.0, 0.0), glm::vec3(1920.0 / 2.0, 1080.0 / 2.0, 1.0));

	Sprite nuvem;
	nuvem.setShader(&shader);
	nuvem.inicializar(texID2, glm::vec3(400.0, 300.0, 0.0), glm::vec3(1920.0 / 2.0, 1080.0 / 2.0, 1.0));

	Sprite grama1;
	grama1.setShader(&shader);
	grama1.inicializar(texID3, glm::vec3(400.0, 300.0, 0.0), glm::vec3(1920.0 / 2.0, 1080.0 / 2.0, 1.0));

	Sprite grama2;
	grama2.setShader(&shader);
	grama2.inicializar(texID10, glm::vec3(400.0, 300.0, 0.0), glm::vec3(1920.0 / 2.0, 1080.0 / 2.0, 1.0));

	Sprite grama3;
	grama3.setShader(&shader);
	grama3.inicializar(texID5, glm::vec3(400.0, 300.0, 0.0), glm::vec3(1920.0 / 2.0, 1080.0 / 2.0, 1.0));

	Sprite grama4;
	grama4.setShader(&shader);
	grama4.inicializar(texID8, glm::vec3(400.0, 300.0, 0.0), glm::vec3(1920.0 / 2.0, 1080.0 / 2.0, 1.0));

	Sprite arvore;
	arvore.setShader(&shader);
	arvore.inicializar(texID6, glm::vec3(300.0, 260.0, 0.0), glm::vec3(700, 450, 1.0));

	//Ativando o buffer de textura 0 da opengl
	glActiveTexture(GL_TEXTURE0);

	shader.Use();

	//Matriz de proje��o paralela ortogr�fica
	glm::mat4 projection = glm::ortho(0.0,800.0,0.0,600.0,-1.0,1.0);
	//Enviando para o shader a matriz como uma var uniform
	shader.setMat4("projection", glm::value_ptr(projection));
	
	//Matriz de transforma��o do objeto (matriz de modelo)
	shader.setInt("texBuffer", 0);

	// Loop da aplica��o - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as fun��es de callback correspondentes
		glfwPollEvents();

		// Definindo as dimens�es da viewport com as mesmas dimens�es da janela da aplica��o
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height); //unidades de tela: pixel
		
		// Limpa o buffer de cor
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f); //cor de fundo
		glClear(GL_COLOR_BUFFER_BIT);

		background.desenhar();
		nuvem.desenhar();
		grama1.desenhar();
		
		grama2.desenhar();
		grama3.desenhar();
		grama4.desenhar();
		arvore.desenhar();

		// Troca os buffers da tela
		glfwSwapBuffers(window);
	}
	
	// Finaliza a execu��o da GLFW, limpando os recursos alocados por ela
	glfwTerminate();
	return 0;
}

// Fun��o de callback de teclado - s� pode ter uma inst�ncia (deve ser est�tica se
// estiver dentro de uma classe) - � chamada sempre que uma tecla for pressionada
// ou solta via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){}


GLuint loadTexture(string texturePath)
{
	GLuint texID;

	// Gera o identificador da textura na mem�ria 
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	//Configura��o do par�metro WRAPPING nas coords s e t
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Confiruga��o do par�metro FILTERING na minifica��o e magnifica��o da textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		if (nrChannels == 3) //jpg, bmp
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else //png
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;
}

