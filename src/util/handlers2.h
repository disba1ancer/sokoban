/*
 * handlers2.h
 *
 *  Created on: Jan 17, 2019
 *      Author: disba1ancer
 */

#ifndef HANDLERS2_H_
#define HANDLERS2_H_

namespace util {

template <typename Method, Method method>
class methodStore;

template <typename Ret, typename Object, typename ... Args, Ret(Object::*method)(Args...)>
class methodStore<Ret(Object::*)(Args...), method> {
	Object *obj;
public:
	methodStore(Object* obj = nullptr) : obj(obj) {}

	Ret operator() (Args&& ... args) {
		return (obj->*method)(args...);
	}

	template <typename ... Args2>
	Ret operator() (Args2&& ... args) {
		return (obj->*method)(static_cast<Args&&>(args)...);
	}
};

#define UTIL_FUNCTOR(func) ::util::methodStore<decltype(&func), &func>

}

#endif /* HANDLERS2_H_ */
