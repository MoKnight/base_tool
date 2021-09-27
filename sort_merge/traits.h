/*
 * @Description: 萃取类型
 * @version: 
 * @Author: MoonKnight
 * @Date: 2021-09-27 22:17:39
 * @LastEditors: MoonKnight
 * @LastEditTime: 2021-09-27 23:00:31
 */

#include <iostream>
#include <limits.h>
using namespace std;

namespace traits
{
	template <class _Tp> //非基本类型不特化
	struct TypeTraits
	{
	};

	template <>
	struct TypeTraits<double>
	{
		static double get_min(){return __DBL_MIN__;};
	};

	template <>
	struct TypeTraits<int>
	{
		static int get_min(){return INT_MIN;};
	};

	template <>
	struct TypeTraits<long>
	{
		static double get_min(){return LONG_MIN;};
	};

	template <>
	struct TypeTraits<float>
	{
		static double get_min(){return __FLT_MIN__;};
	};

	
};
