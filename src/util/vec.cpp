/*
 * vector.cpp
 *
 *  Created on: Oct 6, 2018
 *      Author: disba1ancer
 */

#include <util/vec.h>

namespace util {

template struct vec<unsigned, 2>;
template struct vec<unsigned, 3>;
template struct vec<unsigned, 4>;

template struct vec<int, 2>;
template struct vec<int, 3>;
template struct vec<int, 4>;

template struct vec<float, 2>;
template struct vec<float, 3>;
template struct vec<float, 4>;

} /* namespace util */
