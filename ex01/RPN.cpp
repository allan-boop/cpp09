#include "RPN.hpp"
#include <cstdlib>

RPN::RPN() {};

RPN::RPN(const RPN& copy) {(void)copy;};

RPN &RPN::operator=(const RPN &other) {(void)other; return *this;};

RPN::~RPN() {};

void RPN::substract() {
	double tmp = _stack.top();
	_stack.pop();
	_stack.top() -= tmp;
}

void RPN::add() {
	double tmp = _stack.top();
	_stack.pop();
	_stack.top() += tmp;
}

void RPN::multiply() {
	double tmp = _stack.top();
	_stack.pop();
	_stack.top() *= tmp;
}

void RPN::divide() {
	double tmp = _stack.top();
	_stack.pop();
	_stack.top() /= tmp;
}

void RPN::calc(int sign) {
	if (_stack.size() < 2)
		throw std::runtime_error("ERROR: Not enough number in stack");
	switch (sign) {
		case '-':
			substract();
			break;
		case '+':
			add();
			break;
		case '*':
			multiply();
			break;
		case '/':
			divide();
			break;
		default:
			break;
	}
}

void RPN::fillStack(std::string inp) {
	size_t sign_c = 0;
	size_t digit_c = 0;

	for (size_t i = 0; i < inp.length(); i++) {
		if (isdigit(inp[i]))
		{
			 digit_c++;
			_stack.push(atol(&inp[i]));
		} else if (inp[i] == '+' || inp[i] == '-' || inp[i] == '*' || inp[i] == '/') {
			sign_c++;
			calc(inp[i]);
		} else if (inp[i] == ' ') {
			continue;
		} else {
			throw std::runtime_error("ERROR: Character not allowed");
		}
		if (inp[i + 1] && inp[i + 1] != ' ') {
			throw std::runtime_error("ERROR: No space between 2 char");
		}
	}
	if (sign_c != digit_c - 1)
			throw std::runtime_error("ERROR: Not enough sign, or too much sign");
	std::cout << _stack.top() << std::endl;
}

RPN::RPN(std::string inp) {
	fillStack(inp);
}