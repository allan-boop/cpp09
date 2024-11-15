#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <iostream>

class RPN {
	private:
		RPN();
		RPN(const RPN& copy);
		RPN &operator=(const RPN &other);
		void fillStack(std::string inp);
		void calc(int sign);
		void add();
		void substract();
		void divide();
		void multiply();
		std::stack<double> _stack;
	public:
		RPN(std::string inp);
		~RPN();
};

#endif