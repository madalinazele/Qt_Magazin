#include "TestDomain.h"
#include "Domain.h"
#include <cassert>

void testAllDomain() {
	Product p = Product(1, "napo", "alfers", "cioco", 5);
	assert(p.getId() == 1);
	assert(p.getNume() == "napo");
	assert(p.getProducator() == "alfers");
	assert(p.getTip() == "cioco");
	assert(p.getPret() == 5);

	assert(p.getId() == 1);
}
