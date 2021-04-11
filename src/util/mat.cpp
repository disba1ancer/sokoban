/*
 * mat.cpp
 *
 *  Created on: Feb 24, 2019
 *      Author: disba1ancer
 */

#include "mat.h"

namespace util {

template struct vec<vec<float, 3>, 3>;
template struct vec<vec<float, 4>, 4>;

template
vec<vec<float, 3>, 3> transpose(const vec<vec<float, 3>, 3>& src);

template
vec<vec<float, 3>, 3> operator *(const vec<vec<float, 3>, 3>&, const vec<vec<float, 3>, 3>&);

template
vec<vec<float, 3>, 3>& operator *=(vec<vec<float, 3>, 3>&, const vec<vec<float, 3>, 3>&);

template
vec<vec<float, 4>, 4> transpose(const vec<vec<float, 4>, 4>& src);

template
vec<vec<float, 4>, 4> operator *(const vec<vec<float, 4>, 4>&, const vec<vec<float, 4>, 4>&);

template
vec<vec<float, 4>, 4>& operator *=(vec<vec<float, 4>, 4>&, const vec<vec<float, 4>, 4>&);

}
