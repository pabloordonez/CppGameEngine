#ifndef __ENGINE_CORE_UTILITY_H__
#define __ENGINE_CORE_UTILITY_H__

#include <sstream>

namespace Engine
{
	namespace Core
	{
		namespace Strings
		{
			template <typename T>
			std::string toString(const T& value)
			{
				std::stringstream stream;
				stream << value;
				return stream.str();
			}
		}

		namespace Numeric
		{
			template <typename T>
			inline T clamp(T value, T min, T max)
			{
				if (value < min)
					return min;

				if (value > max)
					return max;

				return value;
			}
		}
	}
}
#endif