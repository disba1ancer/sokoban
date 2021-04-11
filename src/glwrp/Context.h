/*
 * Context.h
 *
 *  Created on: Oct 14, 2018
 *      Author: disba1ancer
 */

#ifndef CONTEXT_H_
#define CONTEXT_H_

namespace gl {

class Context {
public:
	Context(const void* winid = nullptr);
	~Context();
	Context(const Context&) = delete;
	Context(Context&& other);
	Context& operator =(const Context&) = delete;
	Context& operator =(Context&& other);
	friend void SwapBuffers(Context&);
private:
	void* context;
};

} /* namespace gl */

#endif /* CONTEXT_H_ */
