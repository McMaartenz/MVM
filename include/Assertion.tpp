template <class T>
Assertion<T>::Assertion(T expected, Constraint constraint, T actual)
	: expected(expected), actual(actual), constraint(constraint) {
	switch (constraint) {
	case Constraint::EqualTo: {
		if (expected != actual) {
			fail();
		}
		return;
	}
	case Constraint::NotEqualTo: {
		if (expected == actual) {
			fail();
		}
		return;
	}
	default:
		throw std::logic_error("Not implemented");
	}
}

template <class T>
Assertion<T>::~Assertion() {
	//dtor
}

template <class T>
[[noreturn]] Assertion<T>::fail() {
	if (std::is_same<T,bool>::value) {
		if ((BoolConstraint)constraint == BoolConstraint::IsFalse) {
			throw std::runtime_error("Expected false, but was true");
		}
		else {
			throw std::runtime_error("Expected true, but was false");
		}
	}

	std::ostringstream os;
	switch (constraint) {
	case Constraint::EqualTo: {
		os << "Expected to equal " << expected << ", but was " << actual;
		throw std::runtime_error(os.str());
	}
	case Constraint::NotEqualTo: {
		os << "Expected NOT to equal " << expected << ", but was " << actual;
		throw std::runtime_error(os.str());
	}
	default:
		throw std::logic_error("Not implemented");
	}
}
