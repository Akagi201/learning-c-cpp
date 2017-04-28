#include <glib.h>
#include <stdio.h>

int main() {
	const gchar *result = NULL;
	result = glib_check_version(1, 0, 0);
	printf("runtime glib check version result: %s\n", result);

	int static_check = 0;
	static_check = GLIB_CHECK_VERSION(1, 0, 0);
	printf("static glib check version result: %d\n", static_check);

	printf("runtime glib version: %u.%u.%u\n", glib_major_version,
	       glib_minor_version, glib_micro_version);

	printf("static glib version: %u.%u.%u\n", GLIB_MAJOR_VERSION,
	       GLIB_MINOR_VERSION, GLIB_MICRO_VERSION);

	return 0;
}