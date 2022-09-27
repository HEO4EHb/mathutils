#include <iostream>
#include <cassert>
#include "inc/matrix.hpp"

using mt::math::Mat22d;
using mt::math::Vec2d;

//

int main()
{
	std::cout << "=== Test 0 ===" << std::endl;
	{
		Mat22d A({ {
			 {1,2},
			 {3,4}
		} });

		try
		{
			std::cout << A.inv() << std::endl;
			std::cout << "After inv in main" << std::endl;
		}
		catch (const std::bad_alloc& e)
		{
			std::cerr << "BAD ALLOC!!!! " << e.what() << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}

	}


	std::cout << "=== Test 1 ===" << std::endl;
	{
		Mat22d A({ {
			 {1,2},
			 {3,4}
		} });

		Vec2d X({ {
			{1},
			{1}
		} });

		auto B = A * X;

		assert(B.get(0, 0) == 3);
		assert(B.get(1, 0) == 7);
	}

	std::cout << "Done!" << std::endl;

	std::cout << "=== Test 2 ===" << std::endl;

	{
		Mat22d A({ {
			 {1,1},
			 {1,1}
		} });

		Vec2d X({ {
			{1},
			{1}
		} });

		auto B = A*X;

		assert(B.get(0, 0) == 2);
		assert(B.get(1, 0) == 2);
	}

	std::cout << "Done!" << std::endl;

	return 0;
}