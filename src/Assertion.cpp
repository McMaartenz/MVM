#include "Assertion.h"

template <>
Assertion<bool>::Assertion(bool value, BoolConstraint constraint)
	: actual(value), constraint((Constraint)constraint) {
	switch (constraint) {
	case BoolConstraint::IsTrue: {
		if (!value) {
			fail();
		}
		return;
	}
	case BoolConstraint::IsFalse: {
		if (value) {
			fail();
		}
		return;
	}
	default:
		throw std::logic_error("Not implemented");
	}
}
