/* Code By KYG(Z.Shang)
 * Copyleft 2013
 */

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<gtk/gtk.h>
#include<gdk/gdk.h>

GtkWidget *txt_main;
GtkWidget *wd_main;

void f_run(GtkWidget *widget, gpointer *data) {
	const gchar *cmd;
	cmd = gtk_entry_get_text (GTK_ENTRY (txt_main));
	char *result = NULL;
	int i = 0;
	char *arg[10]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
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

	gtk_init(&argc, &argv);

	wd_main = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_decorated(GTK_WINDOW(wd_main), FALSE);
	gtk_widget_set_app_paintable(wd_main, TRUE);
	gtk_window_set_position(GTK_WINDOW(wd_main), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(wd_main),620, 260);
	gtk_widget_realize(wd_main);
	pixbuf = gdk_pixbuf_new_from_file("mask.png",NULL);
	gdk_pixbuf_render_pixmap_and_mask(pixbuf, &pixmap, &bitmap, 128);
	gtk_widget_shape_combine_mask(wd_main,bitmap,0,0);
	gdk_window_set_back_pixmap(wd_main->window,pixmap,FALSE);
	g_object_unref(pixbuf);
	g_object_unref(bitmap);
	g_object_unref(pixmap);
	txt_main = gtk_entry_new();
	lbl_welcome = gtk_label_new(" ");
	gtk_label_set_markup(GTK_LABEL(lbl_welcome),"<span foreground='#111111' font_desc='16'>Welcome\nMaster\nsama~</span>");
	gtk_label_set_width_chars(GTK_LABEL(lbl_welcome), 12);
	gtk_misc_set_alignment(GTK_MISC(lbl_welcome),0.5,0);
	fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(wd_main),fixed);
//	GtkWidget *tab_main;
//	tab_main = gtk_table_new(3, 1, FALSE);
//	gtk_container_add(GTK_CONTAINER(wd_main), tab_main);
	gtk_widget_set_size_request(txt_main, 490, 40);
//	gtk_table_attach(GTK_TABLE(tab_main), txt_main, 1, 3, 0, 1,
//			(GtkAttachOptions)(GTK_FILL),(GtkAttachOptions)(0), 5, 10);
	gtk_fixed_put(GTK_FIXED(fixed),txt_main,0,220);
	gtk_fixed_put(GTK_FIXED(fixed),lbl_welcome,325,50);
	g_signal_connect(G_OBJECT(wd_main), "delete_event", 
			G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(txt_main), "activate", 
			GTK_SIGNAL_FUNC(f_run), G_CALLBACK(f_run));
	gtk_widget_show_all(wd_main);
	gtk_main();
	return 0;
}

