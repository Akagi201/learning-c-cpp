// refs:
// https://stackoverflow.com/questions/9513327/gio-socket-server-client-example

#include <gio/gio.h>
#include <glib.h>

/* this function will get called everytime 25a client attempts to connect */
static gboolean incoming_callback(GSocketService *service,
                                  GSocketConnection *connection,
                                  GObject *source_object, gpointer user_data) {
	g_message("Received Connection from client!");
	GInputStream *istream =
	    g_io_stream_get_input_stream(G_IO_STREAM(connection));
	gchar message[1024] = {};
	g_input_stream_read(istream, message, 1024, NULL, NULL);
	g_print("Message was: \"%s\"\n", message);
	return FALSE;
}

int main(int argc, char **argv) {
	GError *error = NULL;
	GSocketService *service = NULL;
	gboolean ret = FALSE;

	/* create the new socketservice */
	service = g_socket_service_new();

	ret = g_socket_listener_add_inet_port(G_SOCKET_LISTENER(service),
	                                      8327, /* your port goes here */
	                                      NULL, &error);

	/* don't forget to check for errors */
	if (error != NULL) {
		g_error("listen port failed, %s", error->message);
		g_clear_error(&error);
		return -1;
	}

	/* listen to the 'incoming' signal */
	g_signal_connect(service, "incoming", G_CALLBACK(incoming_callback), NULL);

	/* start the socket service */
	g_socket_service_start(service);

	/* enter mainloop */
	g_print("Waiting for client!\n");
	GMainLoop *loop = g_main_loop_new(NULL, FALSE);
	g_main_loop_run(loop);
	g_socket_service_stop(service);
	return 0;
}