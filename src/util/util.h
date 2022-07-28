/*
 * util.h
 *
 *  Created on: Jul 23, 2017
 *      Author: disba1ancer
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <type_traits>
#include <memory>
#include <util/Event.h>
#include <util/Observer.h>

namespace sokoban { class Game; }

/*#include "Renderer.h"
#include "matrixmath.h"*/

//#define GET_PRIVATE(_type) (*(tilegame::util::ptr_cast<std::conditional<std::is_const<std::remove_pointer<decltype(this)>::type>::value, const _type, _type>::type*>(this->storage)))
#define GET_PRIVATE(_type)  *static_cast<std::conditional<std::is_const<std::remove_pointer<decltype(this)>::type>::value, const _type, _type>::type*>(this->priv)
//#ifdef PRIVATE_CLASSNAME
#define PRIVATE GET_PRIVATE(PRIVATE_CLASSNAME)
//#endif //PRIVATE_CLASSNAME

namespace util {

	constexpr float PI = 3.14159265f;

	constexpr float degToRad(float deg) { return PI * deg / 180; }

	int doSystemHandlers(sokoban::Game* game = nullptr);
	int standartUILoop();
	void softTerminate(int returnValue);
	/*matrixmath::matrix4f projectionMatrix(float left, float right, float bottom, float top, float zNear, float zFar);
	matrixmath::matrix4f orthoMatrix(float left, float right, float bottom, float top, float zNear, float zFar);
	matrixmath::matrix4f translateMatrix(float x, float y, float z);
	matrixmath::matrix4f scaleMatrix(float x, float y, float z);
	matrixmath::matrix4f rotateXMatrix(float x);
	matrixmath::matrix4f rotateYMatrix(float y);
	matrixmath::matrix4f rotateZMatrix(float z);*/

	template <typename D, typename S>
	D ptr_cast(S source) {
		static_assert(std::is_pointer<S>::value && std::is_pointer<D>::value, "types is not pointers");
		return reinterpret_cast<D>(source);
	}

	template <typename Enum>
	class EnumCompound {
		static_assert(std::is_enum<Enum>::value, "type is not, a enum");
		unsigned value;
		EnumCompound(unsigned value) : value(value) {}
	public:
		EnumCompound(Enum value) : value(1 << static_cast<unsigned>(value)) {}
		EnumCompound& operator =(Enum value) {
			this->value = static_cast<unsigned>(value);
			return *this;
		}
		EnumCompound operator |(const Enum& value) {
			return EnumCompound{this->value | 1 << static_cast<unsigned>(value)};
		}
		EnumCompound& operator |= (const Enum& value) {
			this->value |= 1 << static_cast<unsigned>(value);
			return *this;
		}
		EnumCompound operator |(const EnumCompound& compound) {
			return EnumCompound{this->value | compound.value};
		}
		EnumCompound& operator |= (const EnumCompound& compound) {
			this->value |= compound.value;
			return *this;
		}
		EnumCompound operator &(const Enum& value) {
			return EnumCompound{this->value & 1 << static_cast<unsigned>(value)};
		}
		EnumCompound& operator &= (const Enum& value) {
			this->value &= 1 << static_cast<unsigned>(value);
			return *this;
		}
		EnumCompound operator &(const EnumCompound& compound) {
			return EnumCompound{this->value & compound.value};
		}
		EnumCompound& operator &= (const EnumCompound& compound) {
			this->value &= compound.value;
			return *this;
		}
		operator unsigned(){
			return value;
		}
	};

	template <typename Enum>
	EnumCompound<Enum> operator |(Enum value1, Enum value2) {
		static_assert(std::is_enum<Enum>::value, "values is not, a enums");
		return EnumCompound<Enum>(value1) | value2;
	}

	template <typename Enum>
	EnumCompound<Enum> operator &(Enum value1, Enum value2) {
		static_assert(std::is_enum<Enum>::value, "values is not, a enums");
		return EnumCompound<Enum>(value1) & value2;
	}

	/*template <typename Private, typename Public>
	Private& GET_PRIVATE(Public* pub) {
		return *ptr_cast<Private*>(pub->storage);
	}*/

	inline constexpr size_t alignSize(size_t align, size_t size) {
		return (size + (align - 1)) & ~(align - 1);
	}

	template <typename M>
	struct wrap_helper;

	template <typename Ret, typename Obj, typename ... Args>
	struct wrap_helper<Ret (Obj::*)(Args ...)> {
		template <Ret(Obj::*method)(Args...)>
		static Ret wrapper(Obj* obj, Args ... args) {
			return (obj->*method)(args ...);
		}
	};

	template <typename Ret, typename Obj, typename ... Args>
	struct wrap_helper<Ret (Obj::*)(Args ...) const> {
		template <Ret(Obj::*method)(Args...) const>
		static Ret wrapper(const Obj* obj, Args ... args) {
			return (obj->*method)(args ...);
		}
	};

#define WRAP_METHOD(method) (&::util::wrap_helper<decltype(method)>::template wrapper<method>)

	typedef void (*handler_t)(Observer*, Event*);

	template <typename M, M handler>
	struct handler_helper;

	template <typename Obj, typename Evt, void (Obj::*method)(Evt&)>
	struct handler_helper<void (Obj::*)(Evt&), method> {
		static void handler(Observer* obj, Event* evt) {
			(static_cast<Obj*>(obj)->*method)(static_cast<Evt&>(*evt));
		}
	};

	template <typename Evt, void (*method)(Evt&)>
	struct handler_helper<void (*)(Evt&), method> {
		static void handler(Observer*, Event* evt) {
			method(static_cast<Evt&>(*evt));
		}
	};

#define OBSERVER(method) (&::util::handler_helper<decltype(method), method>::handler)

} /* namespace util */

#endif /* UTIL_H_ */
