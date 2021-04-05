#include "TestValid.h"
#include "Validator.h"
#include <cassert>

void testAllValid() {
	Validator val;
	Product p = Product(1, "gem", "bunica", "afine", 10);
	val.validate(p);

	p = Product(-1, "gem", "bunica", "afine", 10);
	try {
		val.validate(p);
	}
	catch (ValidateException&) {
		assert(true);
	}

	p = Product(1, "", "bunica", "afine", 10);
	try {
		val.validate(p);
	}
	catch (ValidateException&) {
		assert(true);
	}

	p = Product(1, "gem", "", "afine", 10);
	try {
		val.validate(p);
	}
	catch (ValidateException&) {
		assert(true);
	}

	p = Product(1, "gem", "bunica", "", 10);
	try {
		val.validate(p);
	}
	catch (ValidateException&) {
		assert(true);
	}

	p = Product(1, "gem", "bunica", "afine", -10);
	try {
		val.validate(p);
	}
	catch (ValidateException&) {
		assert(true);
	}
}