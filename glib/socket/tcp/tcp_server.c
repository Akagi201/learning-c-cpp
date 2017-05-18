// refs:
// https://stackoverflow.com/questions/9513327/gio-socket-server-client-example

#include <gio/gio.h>
#include <glib.h>

#define BLOCK_SIZE (1024)
#define PORT (8327)

struct ConnData {
	GSocketConnection *connection;
	char message[BLOCK_SIZE];
};

void message_ready(GObject *source_object, GAsyncResult *res,
                   gpointer user_data) {
	GInputStream *istream = G_INPUT_STREAM(source_object);
	GError *error = NULL;
	struct ConnData *data = user_data;
	int count;

	count = g_input_stream_read_finish(istream, res, &error);

	if (count == -1) {
		g_error("Error when receiving message");
		if (error != NULL) {
			g_error("%s", error->message);
			g_clear_error(&error);
		}
	}

	g_message("Message was: %s", data->message);
	g_object_unref(G_SOCKET_CONNECTION(data->connection));
	g_free(data);
}

/* this function will get called everytime a client attempts to connect */
static gboolean incoming_callback(GSocketService *service,
                                  GSocketConnection *connection,
                                  GObject *source_object, gpointer user_data) {
	g_message("Received Connection from client!");
	GInputStream *istream =
	    g_io_stream_get_input_stream(G_IO_STREAM(connection));
	struct ConnData *data = g_new(struct ConnData, 1);
	data->connection = g_object_ref(connection);
	g_input_stream_read_async(istream, data->message, sizeof(data->message),
	                          G_PRIORITY_DEFAULT, NULL, message_ready, data);
	return FALSE;
}

int main(int argc, char **argv) {
	GError *error = NULL;
	GSocketService *service = NULL;
	gboolean ret = FALSE;

	/* create the new socketservice */
	service = g_socket_service_new();

	ret = g_socket_listener_add_inet_port(G_SOCKET_LISTENER(service), PORT,
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