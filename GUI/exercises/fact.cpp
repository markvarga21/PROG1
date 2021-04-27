#include<iostream>
#include<math.h>
#include<exception>

unsigned long long fac_iterative(int n)
{
	long long r = 1;
	while(n > 1) {
		r *= n;
		--n;
	}
	return r;
}

unsigned long long fac_recursive(int n)
{
	return (n>1)?(n*fac_recursive(n-1)):1;
}

int main()
try {
	int number = 0;
	std::cin >> number;

	unsigned long long numb_fac_iter = fac_iterative(number);
	unsigned long long numb_fac_rec = fac_recursive(number);

	std::cout << number << "! == " << numb_fac_iter << "(Iterative way)" << std::endl;
	std::cout << number << "! == " << numb_fac_rec << "(Recursive way)" << std::endl;  

	return 0;
} catch (std::exception& e) {
	std::cerr << e.what() << std::endl;
	return 1;
} catch (...) {
	std::cerr << "Something went wrong!" << std::endl;
	return 2;
}