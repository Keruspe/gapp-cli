#include <gtk/gtk.h>

#include <stdlib.h>

static void
create_window (GApplication *application,
               const gchar  *text)
{
    GtkWidget *window = gtk_application_window_new (GTK_APPLICATION (application));
    GtkWindow *win = GTK_WINDOW (window);

    gtk_container_add (GTK_CONTAINER (window), gtk_label_new ((text) ? text : "Hello, World"));
    gtk_widget_show_all (window);
}

static gint
foobar_command_line (GApplication            *application,
                     GApplicationCommandLine *command_line)
{
    g_autoptr (GVariant) v = g_variant_dict_lookup_value (g_application_command_line_get_options_dict (command_line), G_OPTION_REMAINING, NULL);
    const gchar *text = (v) ? g_variant_get_strv (v, NULL)[0] : NULL;

    create_window (application, text);

    return EXIT_SUCCESS;
}

/*
static gint
foobar_handle_options (GApplication *application G_GNUC_UNUSED,
                       GVariantDict *options     G_GNUC_UNUSED)
{
    return 0;
}
*/

static void
foobar_activate (GApplication *application)
{
    for (GList *wins = gtk_application_get_windows (GTK_APPLICATION (application)); wins; wins = g_list_next (wins))
    {
        if (gtk_widget_get_realized (wins->data))
        {
            gtk_window_present (wins->data);
            break;
        }
    }

    create_window (application, NULL);
}

gint
main (gint   argc,
      gchar *argv[])
{
    gtk_init (&argc, &argv);

    GtkApplication *app = gtk_application_new ("org.gnome.Foobar", G_APPLICATION_NON_UNIQUE|G_APPLICATION_HANDLES_COMMAND_LINE);
    GApplication *gapp = G_APPLICATION (app);
    GApplicationClass *klass = G_APPLICATION_GET_CLASS (gapp);

    g_application_add_main_option (gapp, G_OPTION_REMAINING, 'e', 0, G_OPTION_ARG_STRING_ARRAY, "the text to display", "text");

    klass->command_line = foobar_command_line;
    // klass->handle_local_options = foobar_handle_options;
    klass->activate = foobar_activate;

    return g_application_run (gapp, argc, argv);
}
