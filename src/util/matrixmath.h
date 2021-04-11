#ifndef MATRIXMATH_H
#define MATRIXMATH_H

#include <iostream>
#include <algorithm>

namespace matrixmath {

	template <unsigned int size, typename elemType>
	struct matrix
	{
		elemType values[size][size];

		elemType* getRaw();
		const elemType* getRaw() const;
		matrix<size, elemType>& transpose();
		matrix<size, elemType>  operator  +(const matrix<size, elemType>& summand) const;
		matrix<size, elemType>& operator +=(const matrix<size, elemType>& summand);
		matrix<size, elemType>  operator  -(const matrix<size, elemType>& subtrahend) const;
		matrix<size, elemType>& operator -=(const matrix<size, elemType>& subtrahend);
		matrix<size, elemType>  operator  *(const matrix<size, elemType>& multiplier) const;
		matrix<size, elemType>& operator *=(const matrix<size, elemType>& multiplier);
		matrix<size, elemType>  operator  *(elemType multiplier) const;
		matrix<size, elemType>& operator *=(elemType multiplier);

		template<typename targetType>
		operator matrix<size, targetType>() const;
	};

	template <unsigned size, typename elemType>
	matrix<size, elemType> operator *(elemType multiplier1, const matrix<size, elemType>& multiplier2);

	template <unsigned int size, typename elemType>
	std::ostream& operator <<(std::ostream& stream, const matrix<size, elemType> &mat);

	template<unsigned int size, typename elemType>
	inline elemType * matrix<size, elemType>::getRaw()
	{
		return &values[0][0];
	}

	template<unsigned int size, typename elemType>
	inline const elemType * matrix<size, elemType>::getRaw() const
	{
		return &values[0][0];
	}

	template <unsigned int size, typename elemType>
	inline matrix<size, elemType>& matrix<size, elemType>::transpose() {
		for (unsigned i = 0; i < size - 1; ++i) {
			for (unsigned j = i + 1; j < size; ++j) {
				std::swap(values[i][j], values[j][i]);
			}
		}
		return *this;
	}

	template <unsigned int size, typename elemType>
	inline matrix<size, elemType> matrix<size, elemType>::operator +(const matrix<size, elemType>& summand) const
	{
		matrix<size, elemType> result;
		for (unsigned i = 0; i < size * size; ++i)
		{
			result.values[0][i] = this->values[0][i] + summand.values[0][i];
		}
		return result;
	}

	template <unsigned int size, typename elemType>
	inline matrix<size, elemType>& matrix<size, elemType>::operator +=(const matrix<size, elemType>& summand)
	{
		for (unsigned i = 0; i < size * size; ++i)
		{
			this->values[0][i] += summand.values[0][i];
		}
		return *this;
	}

	template <unsigned int size, typename elemType>
	inline matrix<size, elemType> matrix<size, elemType>::operator -(const matrix<size, elemType>& subtrahend) const
	{
		matrix<size, elemType> result;
		for (unsigned i = 0; i < size * size; ++i)
		{
			result.values[0][i] = this->values[0][i] - subtrahend.values[0][i];
		}
		return result;
	}

	template <unsigned int size, typename elemType>
	inline matrix<size, elemType>& matrix<size, elemType>::operator -=(const matrix<size, elemType>& subtrahend)
	{
		for (unsigned i = 0; i < size * size; ++i)
		{
			this->values[0][i] -= subtrahend.values[0][i];
		}
		return *this;
	}

	template <unsigned int size, typename elemType>
	inline matrix<size, elemType> matrix<size, elemType>::operator *(const matrix<size, elemType>& multiplier) const
	{
		matrix<size, elemType> result;
		for (unsigned i = 0; i < size; ++i)
		{
			for (unsigned j = 0; j < size; ++j)
			{
				auto &r = result.values[i][j];
				r = 0;
				for (unsigned i2 = 0; i2 < size; ++i2)
				{
					r += this->values[i][i2] * multiplier.values[i2][j];
				}
			}
		}
		return result;
	}

	template <unsigned int size, typename elemType>
	inline matrix<size, elemType>& matrix<size, elemType>::operator *=(const matrix<size, elemType>& multiplier)
	{
		for (unsigned i = 0; i < size; ++i)
		{
			elemType row[size];
			for (unsigned j = 0; j < size; ++j)
			{
				elemType &r = row[j];
				r = 0;
				for (unsigned i2 = 0; i2 < size; ++i2)
				{
					r += this->values[i][i2] * multiplier.values[i2][j];
				}
			}
			memcpy(this->values[i], row, sizeof(row));
		}
		return *this;
	}

	template <unsigned int size, typename elemType>
	inline matrix<size, elemType> matrix<size, elemType>::operator *(elemType multiplier) const
	{
		matrix<size, elemType> result;
		for (unsigned i = 0; i < size * size; ++i)
		{
			result.values[0][i] = this->values[0][i] * multiplier;
		}
		return result;
	}

	template <unsigned int size, typename elemType>
	inline matrix<size, elemType>& matrix<size, elemType>::operator *=(elemType multiplier)
	{
		for (unsigned i = 0; i < size * size; ++i)
		{
			this->values[0][i] *= multiplier;
		}
		return *this;
	}

	template<unsigned int size, typename elemType>
	template<typename targetType>
	inline matrix<size, elemType>::operator matrix<size, targetType>() const
	{
		matrix<size, targetType> result;
		for (unsigned i = 0; i < size * size; ++i)
		{
			result.rawValues[i] = static_cast<targetType>(this->values[0][i]);
		}
		return result;
	}

	template <unsigned size, typename elemType>
	inline matrix<size, elemType> operator *(elemType multiplier1, const matrix<size, elemType>& multiplier2)
	{
		matrix<size, elemType> result;
		for (unsigned i = 0; i < size * size; ++i)
		{
			result.rawValues[i] = multiplier2.rawValues[i] * multiplier1;
		}
		return result;
	}

	template <unsigned int size, typename elemType>
	inline std::ostream& operator <<(std::ostream& stream, const matrix<size, elemType> &mat)
	{
		stream << std::endl;
		for (unsigned int i = 0; i < size; ++i)
		{
			for (unsigned int j = 0; j < size; ++j)
			{
				stream << mat.values[i][j] << "\t";
			}
			stream << std::endl;
		}
		return stream;
	}

	typedef matrix<4, float> matrix4f;
	typedef matrix<3, float> matrix3f;
	typedef matrix<2, float> matrix2f;

	typedef matrix<4, int> matrix4i;
	typedef matrix<3, int> matrix3i;
	typedef matrix<2, int> matrix2i;

	constexpr matrix4f identity4f = { { {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} } };
	constexpr matrix3f identity3f = { { {1, 0, 0}, {0, 1, 0}, {0, 0, 1} } };
	constexpr matrix2f identity2f = { { {1, 0}, {0, 1} } };

	constexpr matrix4i identity4i = { { {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1} } };
	constexpr matrix3i identity3i = { { {1, 0, 0}, {0, 1, 0}, {0, 0, 1} } };
	constexpr matrix2i identity2i = { { {1, 0}, {0, 1} } };

	template <unsigned size, typename elemType>
	struct vector
	{
		elemType values[size];

		vector<size, elemType>  operator  +(const vector<size, elemType>& summand) const;
		vector<size, elemType>& operator +=(const vector<size, elemType>& summand);
		vector<size, elemType>  operator  -(const vector<size, elemType>& subtrahend) const;
		vector<size, elemType>& operator -=(const vector<size, elemType>& subtrahend);

		vector<size, elemType>  operator  *(const matrix<size, elemType>& multiplier) const;
		vector<size, elemType>& operator *=(const matrix<size, elemType>& multiplier);

		template<typename targetType>
		operator vector<size, targetType>() const;
	};

	template<unsigned int size, typename elemType>
	inline vector<size, elemType> operator *(const matrix<size, elemType>& multiplier1, const vector<size, elemType>& multiplier2);

	template<unsigned int size, typename elemType>
	inline vector<size, elemType> vector<size, elemType>::operator +(const vector<size, elemType>& summand) const
	{
		vector<size, elemType> result;
		for (unsigned i = 0; i < size; ++i)
		{
			result.values[i] = this->values[i] + summand.values[i];
		}
		return result;
	}

	template<unsigned int size, typename elemType>
	inline vector<size, elemType>& vector<size, elemType>::operator +=(const vector<size, elemType>& summand)
	{
		for (unsigned i = 0; i < size; ++i)
		{
			this->values[i] += summand.values[i];
		}
		return *this;
	}

	template<unsigned int size, typename elemType>
	inline vector<size, elemType> vector<size, elemType>::operator -(const vector<size, elemType>& summand) const
	{
		vector<size, elemType> result;
		for (unsigned i = 0; i < size; ++i)
		{
			result.values[i] = this->values[i] - summand.values[i];
		}
		return result;
	}

	template<unsigned int size, typename elemType>
	inline vector<size, elemType>& vector<size, elemType>::operator -=(const vector<size, elemType>& summand)
	{
		for (unsigned i = 0; i < size; ++i)
		{
			this->values[i] -= summand.values[i];
		}
		return *this;
	}

	template<unsigned int size, typename elemType>
	inline vector<size, elemType> vector<size, elemType>::operator *(const matrix<size, elemType>& multiplier) const
	{
		vector<size, elemType> result;
		for (unsigned i = 0; i < size; ++i)
		{
			elemType& r = result.values[i];
			r = 0;
			for (unsigned i2 = 0; i2 < size; ++i2)
			{
				r += this->values[i2] * multiplier.values[i2][i];
			}
		}
		return result;
	}

	template<unsigned int size, typename elemType>
	inline vector<size, elemType>& vector<size, elemType>::operator *=(const matrix<size, elemType>& multiplier)
	{
		return *this = *this * multiplier;
	}

	template<unsigned int size, typename elemType>
	template<typename targetType>
	inline vector<size, elemType>::operator vector<size, targetType>() const
	{
		vector<size, targetType> result;
		for (unsigned i = 0; i < size; ++i)
		{
			result.values[i] = static_cast<targetType>(this->values[i]);
		}
		return result;
	}

	template<unsigned int size, typename elemType>
	inline vector<size, elemType> operator *(const matrix<size, elemType>& multiplier1, const vector<size, elemType>& multiplier2)
	{
		vector<size, elemType> result;
		for (unsigned i = 0; i < size; ++i)
		{
			elemType& r = result.values[i];
			r = 0;
			for (unsigned i2 = 0; i2 < size; ++i2)
			{
				r += multiplier2.values[i2] * multiplier1.values[i][i2];
			}
		}
		return result;
	}

	template <unsigned int size, typename elemType>
	inline std::ostream& operator <<(std::ostream& stream, const vector<size, elemType> &vec)
	{
		stream << std::endl;
		for (unsigned int i = 0; i < size; ++i)
		{
			stream << vec.values[i] << "\t";
		}
		return stream;
	}

	typedef vector<4, float> vector4f;
	typedef vector<3, float> vector3f;
	typedef vector<2, float> vector2f;

	typedef vector<4, int> vector4i;
	typedef vector<3, int> vector3i;
	typedef vector<2, int> vector2i;

}

#endif // !MATRIXMATH_H
