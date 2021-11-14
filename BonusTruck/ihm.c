#include <gtk/gtk.h>
#include <stdio.h>
#include <err.h>

struct interface{
    GtkWindow *root;     //*aPropos; // les deux fenêtres
    GtkWidget *entry;    // le champ où on saisit la formule
    GtkWidget *viewport; // le viewport qui permet de “voir” les cellules
    GtkWidget *filename; // le nom du fichier
} ihm;

GtkWidget * grid;

int main(int argc, char *argv[]){
    
    GtkBuilder * builder;
    builder = gtk_builder_new();
    
    if (gtk_builder_add_from_file(builder, "interfaceMonoplan.glade", &err) == 0){
        printf("problème avec le builder\n");
        exit(1); 
    }

    gtk_builder_connect_signals(builder, &ihm);

    ihm.root = GTK_WINDOW(gtk_builder_get_object(builder, "myWindow"));
    //ihm.aPropos = GTK_WINDOW(gtk_builder_get_object(builder, "aPropos"));
    ihm.viewport = GTK_WIDGET(gtk_builder_get_object(builder, "viewport1"));
    ihm.entry = GTK_WIDGET(gtk_builder_get_object(builder, "entryFormule"));
    ihm.filename = GTK_WIDGET(gtk_builder_get_object(builder, "nomFichier"));

    grid = gtk_grid_new();

    for(int i = 0; i < 26; i++){
        gtk_grid_insert_column(grid, i);
    }

    for(int x = 0; x < 50 ; x++){
        gtk_grid_insert_row(grid, x);
        for(int y = 0; y < 26; y++){
            GtkWidget * mylabel;
            gtk_grid_attach (grid, mylabel, y, x, 1, 1);
        }
    }

    gtk_builder_connect_signals(builder, NULL); 
    g_object_unref(builder);

    //gtk_widget_show_all(ihm.root);

    gtk_main();

    return 0;
}