/*! \file main.cc
 *  \author Akagi201
 *  \brief glib datetime related functions
 *
 *  glib datetime related functions
 */

#include <glib.h>
#include <stdio.h>

static void print_todays_date(void) {
	GDateTime *dt;
	gchar *str;

	dt = g_date_time_new_now_local();
	str = g_date_time_format(dt, "Today is %x.");
	g_print("%s\n", str);

	g_date_time_unref(dt);
	g_free(str);
}

static void print_tomorrows_date(void) {
	GDateTime *dt;
	GDateTime *dt2;
	gchar *str;

	dt = g_date_time_new_now_local();
	dt2 = g_date_time_add_days(dt, 1);
	str = g_date_time_format(dt2, "Tomorrow is %x.");
	g_print("%s\n", str);

	g_date_time_unref(dt);
	g_date_time_unref(dt2);
	g_free(str);
}

static void print_yesterdays_date(void) {
	GDateTime *dt;
	GDateTime *dt2;
	gchar *str;

	dt = g_date_time_new_now_local();
	dt2 = g_date_time_add_days(dt, -1);
	str = g_date_time_format(dt, "Yesterday was %x.");
	g_print("%s\n", str);

	g_date_time_unref(dt);
	g_date_time_unref(dt2);
	g_free(str);
}

static void print_current_timezone(void) {
	GDateTime *dt;

	dt = g_date_time_new_now_local();
	g_print("The current timezone is %s.\n",
	        g_date_time_get_timezone_abbreviation(dt));
	g_date_time_unref(dt);
}

gint main(gint argc, gchar *argv[]) {
	print_todays_date();
	print_tomorrows_date();
	print_yesterdays_date();
	print_current_timezone();

	return 0;
}