/*
 * ShaderProgramMaker.h
 *
 *  Created on: Oct 16, 2018
 *      Author: disba1ancer
 */

#ifndef SHADERPROGRAMMAKER_H_
#define SHADERPROGRAMMAKER_H_

#include <vector>
#include <glwrp/gl31.h>

namespace gl {

class ShaderProgramMaker {
public:
	ShaderProgramMaker();
	~ShaderProgramMaker();
	void addSource(const char * source, GLenum shaderType);
	void clean();
	GLuint makeProgram();
private:
	struct Unit {
		const char *source;
		GLenum type;
	};
	std::vector<Unit> sources;
};

} /* namespace gl */

#endif /* SHADERPROGRAMMAKER_H_ */
