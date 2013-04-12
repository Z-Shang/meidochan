/* Code By KYG(Z.Shang)
 * Copyleft 2013
 */

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<gtk/gtk.h>
#include<gdk/gdk.h>
#include<lua.h>
#include<lauxlib.h>
#include<lualib.h>

GtkWidget *txt_main;
GtkWidget *wd_main;
GtkWidget *wd_alarm;

void f_run(GtkWidget *widget, gpointer *data) {
	const gchar *cmd;
	cmd = gtk_entry_get_text (GTK_ENTRY (txt_main));
	char *result = NULL;
	int i = 0;
	char *arg[10]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
	result = strtok(cmd," ");
	while(result != NULL){
		arg[i] = result;
		i++;
		result = strtok(NULL, " ");
	}
	execvp(cmd,arg);
	gtk_main_quit();
}

int main(int argc, char *argv[]) {
	GdkPixbuf *pixbuf = NULL;
	GdkBitmap *bitmap = NULL;
	GdkPixmap *pixmap = NULL;
	GtkWidget *fixed;
	GtkWidget *lbl_welcome;

	/*
	 * Get string from lua file
	 */
	lua_State *L;
	L = luaL_newstate();
	luaL_openlibs(L);
	char *msg;
	int width, height;
	char *mask;
	char *rcpath = getenv("HOME");
	strcat(rcpath,"/.meidochan/rc.lua");
	if(luaL_loadfile(L, rcpath)!=0){
		msg = "Welcome\nMaster\nSama!~";
		width = 620;
		height = 260;
		mask = "/path/to/your/mask.png";
	}
	else{
	lua_pcall(L, 0, 0, 0);
	lua_getglobal(L, "msg");
	msg = (char *)lua_tostring(L, 1);
	//printf("%s\n", msg);
	lua_getglobal(L, "width");
	width = (int)lua_tointeger(L, 2);
	//printf("%d\n", width);
	lua_getglobal(L, "height");
	height = (int)lua_tointeger(L, 3);
	//printf("%d\n", height);
	lua_getglobal(L, "mask");
	mask = (char *)lua_tostring(L, 4);
	//printf("%s\n", mask);
	}
	/*
	 * Done reading from lua file
	 */

	gtk_init(&argc, &argv);

	wd_main = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_decorated(GTK_WINDOW(wd_main), FALSE);
	gtk_widget_set_app_paintable(wd_main, TRUE);
	gtk_window_set_position(GTK_WINDOW(wd_main), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(wd_main), width, height);
	gtk_widget_realize(wd_main);
	pixbuf = gdk_pixbuf_new_from_file(mask, NULL);
	gdk_pixbuf_render_pixmap_and_mask(pixbuf, &pixmap, &bitmap, 128);
	gtk_widget_shape_combine_mask(wd_main,bitmap,0,0);
	gdk_window_set_back_pixmap(wd_main->window,pixmap,FALSE);
	g_object_unref(pixbuf);
	g_object_unref(bitmap);
	g_object_unref(pixmap);
	txt_main = gtk_entry_new();
	lbl_welcome = gtk_label_new(" ");

	/* Welcome message */
	const char *form1 = "<span foreground='#111111' font_desc='16'>";
	const char *form2 = "</span>";
	int i = strlen(form1) + strlen(form2) + strlen(msg);
	char form[i];
	strcpy(form, form1);
	strcat(form, (const char *)msg);
	strcat(form, form2);
	const gchar *wel_msg = (const gchar *)form;
	/* Welcome message done */

	gtk_label_set_markup(GTK_LABEL(lbl_welcome), wel_msg);
	gtk_label_set_width_chars(GTK_LABEL(lbl_welcome), 12);
	gtk_misc_set_alignment(GTK_MISC(lbl_welcome),0.5,0);
	fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(wd_main),fixed);
	gtk_widget_set_size_request(txt_main, 490, 40);
	gtk_fixed_put(GTK_FIXED(fixed),txt_main,0,220);
	gtk_fixed_put(GTK_FIXED(fixed),lbl_welcome,325,50);
	g_signal_connect(G_OBJECT(wd_main), "delete_event", 
			G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(txt_main), "activate", 
			GTK_SIGNAL_FUNC(f_run), G_CALLBACK(f_run));
	gtk_widget_show_all(wd_main);
	gtk_main();
	lua_close(L);
	return 0;
}

