#include "shaders.h"


const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 800;

void viewPortCallBack(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}


void processKeyboard(GLFWwindow* window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		std::cout << "closing!" << std::endl;
		glfwSetWindowShouldClose(window, true);
	}
}

void glfwErrorCallback(int error, const char *description) {}

GLFWwindow* setup()
{

        if(!glfwInit())
	{
		std::cerr << "failed to initialise glfw" << std::endl;
		return	nullptr;
	}

	//context hint
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//WINDOW
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL window", NULL, NULL);
	if(window == nullptr)
	{

		std::cerr << "window is null" << std::endl;
		glfwTerminate();
		return nullptr;
	}

	//context
	glfwMakeContextCurrent(window);

	if( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "failed to load glad" << std::endl;
	}
	
	//call backs
	//glfwSetKeyCallback(window, processKeyboardInputs);
	glfwSetFramebufferSizeCallback(window, viewPortCallBack);

	return window;
}

void frameClear()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void draw(GLuint VAO, GLuint VBO, ShaderManager* sm, std::vector<GLfloat> &vertices)
{
	glUseProgram(sm->shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}


void cleanup(GLuint VAO, GLuint VBO, GLuint shaderProgram)
{
	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

}

void vertexProcessing(GLuint &VAO, GLuint &VBO, std::vector<GLfloat> &vertices)
{
	glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0); 
}

void draw(GLuint shaderProgram, GLuint VAO)
{
	glUseProgram(shaderProgram);
	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) /	 2.0f) + 0.5f;
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}


void renderLoop(GLFWwindow* window, GLuint VAO, GLuint VBO, GLuint shaderProgram)
{
	
	while (!glfwWindowShouldClose(window))
    {
        processKeyboard(window);
        frameClear();
		draw(shaderProgram, VAO);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}

int main() {
	
	GLFWwindow* window = setup();
	if(window == nullptr)
		return -1;

	//shader code.
	ShaderManager *sm = ShaderManager::GetInstance();
    if (sm == nullptr)
    {
        std::cout << "shader Manager uninitialised" << std::endl;
        return 0;
    }
	
	sm->createShaderProgram();

	//vertex processing
    GLuint VBO, VAO;
	std::vector<GLfloat> vertices = {-0.5f, -0.5f, 0.0f, // left  
        							  0.5f, -0.5f, 0.0f, // right 
									  0.0f,  0.5f, 0.0f  // top   
									};

	vertexProcessing(VAO, VBO, vertices);

	//render loop
	renderLoop(window, VAO, VBO, sm->shaderProgram);

	//cleanup
	cleanup(VAO, VBO, sm->shaderProgram);

	glfwTerminate();

	std::cout << "main exit!" << std::endl;
	return 0;
}
