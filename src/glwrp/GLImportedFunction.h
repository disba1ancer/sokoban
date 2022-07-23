/*
 * GLImportedFunction.h
 *
 *  Created on: Sep 16, 2018
 *      Author: disba1ancer
 */

#ifndef GLIMPORTEDFUNCTION_H_
#define GLIMPORTEDFUNCTION_H_

#include <platform/win32.h>
#include <exception>
#include <iostream>
#include <type_traits>

/*template <char ... str>
class string_literal_store {
	static const char string[] = {str...};
};*/

template <const char*const functionName, typename Callback> class GLImportedFunction;

template <const char*const functionName, typename RetVal, typename ... Args>
class GLImportedFunction<functionName, RetVal APIENTRY(Args...)> {
	using Callback = RetVal(APIENTRY *)(Args...);
	Callback glFunc = 0;
public:
	void load() {
		if (!glFunc) {
			glFunc = reinterpret_cast<Callback>(
					reinterpret_cast<void(*)()>(wglGetProcAddress(functionName))
			);
			if (!glFunc) {
				std::cout << std::cout.hex << GetLastError() << std::endl;
				struct GLFunctionLoadFail : std::exception {
					const char* what() const noexcept override {
						return "Couldn't load OpenGL function";
					}
				};
				throw GLFunctionLoadFail();
			}
		}
	}

	void reset() {
		glFunc = 0;
	}

	RetVal operator()(Args...args) {
		load();
		return glFunc(args...);
	}
};

#define IMPLEMENT_GL_FUNCTION(_name, _type_part_name) char zzz_ ## _name ## _funcname[] = #_name;\
	GLImportedFunction<zzz_ ## _name ## _funcname, std::remove_pointer_t<PFN ## _type_part_name ## PROC>> _name
#define IMPORT_GL_FUNCTION(_name, _type_part_name) extern char zzz_ ## _name ## _funcname[];\
	extern GLImportedFunction<zzz_ ## _name ## _funcname, std::remove_pointer_t<PFN ## _type_part_name ## PROC>> _name

#endif /* GLIMPORTEDFUNCTION_H_ */
