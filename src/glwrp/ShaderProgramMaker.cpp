/*
 * ShaderProgramMaker.cpp
 *
 *  Created on: Oct 16, 2018
 *      Author: disba1ancer
 */

#include <glwrp/ShaderProgramMaker.h>

#include <memory>

namespace gl {

ShaderProgramMaker::ShaderProgramMaker() {
}

ShaderProgramMaker::~ShaderProgramMaker() {
}

void ShaderProgramMaker::addSource(const char* source, GLenum shaderType) {
	sources.push_back(Unit{source, shaderType});
}

void ShaderProgramMaker::clean() {
	sources.clear();
}

GLuint ShaderProgramMaker::makeProgram() {
	std::vector<GLuint> shaders(sources.size());
	GLuint program = glCreateProgram();
	int t;
	for (size_t i = 0; i < sources.size(); ++i) {
		shaders[i] = glCreateShader(sources[i].type);
		glShaderSource(shaders[i], 1, &(sources[i].source), nullptr);
		glCompileShader(shaders[i]);
		glGetShaderiv(shaders[i], GL_COMPILE_STATUS, &t);
		if (t == GL_FALSE) {
			glGetShaderiv(shaders[i], GL_INFO_LOG_LENGTH, &t);
			std::unique_ptr<char[]> out(new char[t]);
			glGetShaderInfoLog(shaders[i], t, &t, out.get());
			std::cout << out.get() << std::endl;
		}
		glAttachShader(program, shaders[i]);
	}
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &t);
	if (t == GL_FALSE) {
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &t);
		std::unique_ptr<char[]> out(new char[t]);
		glGetProgramInfoLog(program, t, &t, out.get());
		std::cout << out.get() << std::endl;
	}
	for (size_t i = 0; i < shaders.size(); ++i) {
		glDeleteShader(shaders[i]);
	}
	return program;
}

} /* namespace gl */
