#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Hello World");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 100);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *label = gtk_label_new("Hello, world!");
    PangoFontDescription *font_desc = pango_font_description_new();
    pango_font_description_set_size(font_desc, 20 * PANGO_SCALE); // Set font size to 20 points
    gtk_widget_override_font(label, font_desc);
    g_object_unref(font_desc);

    gtk_container_add(GTK_CONTAINER(window), label);
    gtk_widget_show_all(window);

    gtk_main();
    return 0;
}
