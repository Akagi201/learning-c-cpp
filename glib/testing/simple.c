#include <glib.h>

void computationTest(void) {
	// a suitable test
	g_assert(g_bit_storage(1) == 1);
	// a test with verbose error message
	g_assert_cmpint(g_bit_storage(1), ==, 1);
}

int main(int argc, char** argv) {
	g_test_init(&argc, &argv, NULL);
	g_test_add_func("/package_name/unit", computationTest);
	return g_test_run();
}