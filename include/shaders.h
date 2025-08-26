
#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

class ShaderManager
{
	//class is used to read the obj files and manageOperations.
	//to be extended to triangle meshes as well.
	//should be singleton

protected:
	ShaderManager();
	static ShaderManager* sm;

public:
    GLuint shaderProgram;
	ShaderManager(ShaderManager& other) = delete;
	void operator=(const ShaderManager&) = delete; 
	static ShaderManager* GetInstance();
	void readShader(std::string filePath, std::string& shaderSrc);
    //void printLogs(GLuint prog, GLenum pname, std::string msg);
    void compileShaders(GLuint &shader, const char* shaderSrc, GLenum shaderType);
    void createShaderProgram();
    void clear();
};

#endif