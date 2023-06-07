#ifndef ASSERTION_H
#define ASSERTION_H

#include <stdexcept>
#include <sstream>

enum Constraint {
	EqualTo,
	NotEqualTo
};

enum BoolConstraint {
	IsTrue = 2,
	IsFalse
};

template <class T>
class Assertion {
public:
	Assertion(T expected, Constraint constraint, T actual);
	Assertion(T value, BoolConstraint constraint);
	virtual ~Assertion();

protected:
	T expected;
	T actual;
	Constraint constraint;

private:
	[[noreturn]] fail();
};

#include "Assertion.tpp"
#endif // ASSERTION_H
