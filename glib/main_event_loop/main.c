/*! \file main.cc
 *  \author Akagi201
 *  \brief glib main event loop related functions
 *
 *  glib main event loop related functions
 */

#include <glib.h>

gboolean callback(gpointer data) {
	static guint16 i = 0;
	g_print("Iter=%" G_GUINT16_FORMAT "\n", i++);
	if (i % 5 == 0) {
		g_print("try to stop loop1:%p\n", data);
		g_main_loop_quit((GMainLoop*)data);
	}
	return TRUE;
}

/*
 * http://stackoverflow.com/questions/26410585/add-callback-for-separate-g-main-loop
 */
int main() {
	GMainContext* con1 = NULL;
	GMainContext* con2 = NULL;
	GMainLoop* loop1 = NULL;
	GMainLoop* loop2 = NULL;
	GSource* source1 = NULL;

	con1 = g_main_context_new();
	con2 = g_main_context_new();

	loop1 = g_main_loop_new(con1, FALSE);
	loop2 = g_main_loop_new(con2, FALSE);

	source1 = g_timeout_source_new_seconds(1);
	g_source_set_callback(source1, callback, loop1, NULL);
	g_source_attach(source1, con1);

	// We don't need the GMainContext anymore—the loop has an internal
	// reference so we'll drop ours.
	g_main_context_unref(con1);
	con1 = NULL;

	// Ditto for the GSource
	g_source_unref(source1);
	source1 = NULL;

	g_main_context_unref(con2);
	con2 = NULL;

	g_print("run loop1\n");
	g_main_loop_run(loop1);
	// Use g_main_loop_unref, not g_free
	g_main_loop_unref(loop1);
	loop1 = NULL;

	g_print("run loop2\n");
	// Note that there is no longer a callback attached here, so it will
	// run forever.
	g_main_loop_run(loop2);
	g_main_loop_unref(loop2);
	loop2 = NULL;

	return 0;
}
