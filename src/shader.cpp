// madoodia@gmail.com
// ------------------

// C++ Headers

// Third Party Headers

// Our Headers
#include "shader.h"
Shader::Shader()
{}

void Shader::addShaders(const char* vShaderPath, const char* fShaderPath)
{
	std::string vShader = readFileStream(vShaderPath);
	// a different way to read from files
	std::string fShader = readFileStream(fShaderPath);

	const char* vShaderCode = vShader.c_str();
	const char* fShaderCode = fShader.c_str();

	compile(vShaderCode, fShaderCode);
}

std::string Shader::readFile(const char* filePath)
{
	std::string content;

	std::ifstream fileStream(filePath, std::ios::in);

	if(!fileStream.is_open())
	{
		printf("File %s does not exists!\n", filePath);
		return "";
	}

	std::string line = "";
	while(!fileStream.eof())
	{
		std::getline(fileStream, line);
		content += "\n" + line;
	}

	fileStream.close();

	return content;
}

std::string Shader::readFileStream(const char* filePath)
{
	std::string content;

	// 1. retrieve the vertex/fragment source code from filePath
	std::ifstream shaderFile;
	// ensure ifstream objects can throw exceptions:
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		shaderFile.open(filePath);
		std::stringstream shaderStream;
		// read file's buffer contents into streams
		shaderStream << shaderFile.rdbuf();
		// close file handlers
		shaderFile.close();
		// convert stream into string
		content = shaderStream.str();
	}
	catch(std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	return content;
}

void Shader::compile(const char* vShaderCode, const char* fShaderCode)
{
	unsigned int vertexShader, fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);
	checkStatus(glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS, "compiling");

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);
	checkStatus(glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS, "compiling");

	programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	checkStatus(glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS, "linking");
	checkStatus(glGetProgramiv, glGetProgramInfoLog, GL_VALIDATE_STATUS, "validating");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	uniformHOffset = glGetUniformLocation(programID, "hOffset");
}

int Shader::getHOffset()
{
	return uniformHOffset;
}

void Shader::checkStatus(GETPOBJECTPROC objectFunc,
	GETPOBJECTINFOLOGPROC infoLogFunc,
	GLenum status,
	const char* msg)
{
	int success;
	char eLog[1024] = {0};

	objectFunc(programID, status, &success);

	if(!success)
	{
		infoLogFunc(programID, sizeof(eLog), NULL, eLog);
		printf("Error in %s program '%s'\n", msg, eLog);
		return;
	}
}

void Shader::use()
{
	glUseProgram(programID);
}

Shader::~Shader()
{}