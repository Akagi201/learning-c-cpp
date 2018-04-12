#include <glib.h>

gboolean callback(gpointer data) {
	static int i = 0;
	i++;
	g_print("timeout_callback called %d times\n", i);
	if (10 == i) {
		g_main_loop_quit((GMainLoop *)data);
		return FALSE;
	}

	return TRUE;
}

gboolean prepare(GSource *source, gint *timeout_) {
	*timeout_ = -1;
	return TRUE;
}

gboolean check(GSource *source) {
	return TRUE;
}

gboolean dispatch(GSource *source, GSourceFunc callback, gpointer user_data) {
  return callback(user_data);
}

int main() {
	GMainLoop *loop = NULL;
	GMainContext *context = NULL;
	GSource *source = NULL;
	int id;

	// create a variable of type GSourceFuncs
	GSourceFuncs SourceFuncs = {prepare, check, dispatch, NULL};

	// create a new source
	source = g_source_new(&SourceFuncs, sizeof(GSource));

	// create a context
	context = g_main_context_new();

	// attach source to context
	id = g_source_attach(source, context);

	// create a main loop with context
	loop = g_main_loop_new(context, FALSE);

	// set the callback for this source
	g_source_set_callback(source, callback, loop, NULL);

	g_main_loop_run(loop);
	g_main_loop_unref(loop);

	return 0;
}