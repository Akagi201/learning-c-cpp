#include <glib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	GIOChannel *in_channel = NULL, *out_channel = NULL;
	gchar buf[100] = {};
	gsize bytes_read, bytes_written;
	GError *error = NULL;

	if (argc != 3) {
		g_print("usage:<cp SOURCE> <DESTINATION>\n");
		g_print("Press any key to exit\n");
		getchar();
		return 1;
	}

	in_channel = g_io_channel_new_file(argv[1], "r", &error);

	if (!in_channel) {
		g_print("Unable to open the file %s to read\n", argv[1]);
		g_print("Press any key to exit\n");
		getchar();
		return 1;
	}

	out_channel = g_io_channel_new_file(argv[2], "w", &error);

	if (!out_channel) {
		g_print("Unable to open the file %s to write\n", argv[2]);
		g_print("Press any key to exit\n");
		getchar();
		return 1;
	}

	do {
		g_io_channel_read_chars(in_channel, buf, 100, &bytes_read, &error);
		if (error) {
			g_print("Error while reading file %s\n", argv[1]);
			g_print("Press any key to exit\n");
			getchar();
			return 1;
		}

		g_io_channel_write_chars(out_channel, buf, bytes_read, &bytes_written,
		                         &error);
		if (error) {
			g_print("Error while writing file %s\n", argv[2]);
			g_print("Press any key to exit\n");
			getchar();
			return 1;
		}
	} while (bytes_read > 0);

	g_io_channel_shutdown(in_channel, TRUE, &error);
	if (error) {
		g_print("Error has occured\n");
		g_print("Press any key to exit\n");
		getchar();
		return 1;
	}

	g_io_channel_shutdown(out_channel, TRUE, &error);
	if (error) {
		g_print("Error has occured\n");
		g_print("Press any key to exit\n");
		getchar();
		return 1;
	}

	g_print("File copied successfully...\n");
	getchar();

	return 0;
}