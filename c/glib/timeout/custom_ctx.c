#include <glib.h>

gboolean timeout_callback(gpointer data) {
	static int i = 0;

	i++;
	g_print("timeout_callback called %d times\n", i);

	if (10 == i) {
		g_main_loop_quit((GMainLoop *)data);
		return FALSE;
	}

	return TRUE;
}

int main() {
	GMainLoop *loop = NULL;
	GMainContext *context = NULL;
	GSource *source = NULL;
	int id;

	// create a new time-out source
	source = g_timeout_source_new(1000);

	// create a context
	context = g_main_context_new();

	// attach source to context
	id = g_source_attach(source, context);

	// create a main loop with context
	loop = g_main_loop_new(context, FALSE);

	// set the callback for this source
	g_source_set_callback(source, timeout_callback, loop, NULL);

	g_main_loop_run(loop);
	g_main_loop_unref(loop);

	return 0;
}