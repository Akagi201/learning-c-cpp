#include <glib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	GIOChannel *channel = NULL;
	gchar buf[100];
	gsize bytes_read;
	FILE *fp = NULL;

	if (argc != 2) {
		g_print("usage:cat <file_name>\n");
		g_print("Press any key to exit\n");
		getchar();
		return 1;
	}

	fp = fopen(argv[1], "r");

	if (!fp) {
		g_print("Unable to open the file %s\n", argv[1]);
		return 1;
	}

	channel = g_io_channel_unix_new(fileno(fp));

	do {
		g_io_channel_read_chars(channel, buf, 100, &bytes_read, NULL);
		g_print("%s", buf);

	} while (bytes_read > 0);

	g_io_channel_shutdown(channel, TRUE, NULL);

	fclose(fp);

	return 0;
}