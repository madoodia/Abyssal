// madoodia@gmail.com
// ------------------

#ifndef SHADER_H
#define SHADER_H

// C++ Headers
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

// Third Party Headers
#include <GL/glew.h>

class Shader
{
public:
	Shader();
	~Shader();

	void initializeShader(const char* vShaderPath, const char* fShaderPath);

	void compileShader();
	void useShader();

private:
	unsigned int programID;

	const char* vShaderCode;
	const char* fShaderCode;

	typedef PFNGLGETPROGRAMIVPROC GETPOBJECTPROC;
	typedef PFNGLGETPROGRAMINFOLOGPROC GETPOBJECTINFOLOGPROC;

	std::string readFile(const char* filePath);
	std::string readFileStream(const char* filePath);

	void checkStatus(GETPOBJECTPROC objectFunc,
		GETPOBJECTINFOLOGPROC infoLogFunc,
		GLenum status,
		const char* msg);
};

#endif // SHADER_H

