#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void flush()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

typedef struct {
    char username[15];
    char password[15];
} User;

typedef struct {
    int id;
    char title[50];
    char author[50];
    char ISBN[50];
    char genre[50];
    char publisher[50];
    char description[255];
    int borrowed;
} Book;

int main(){
    char option, admin_option, username[15], password[15], edit_option;
    int first_time, c, i, j, id, found;
    FILE *f;
    User user;
    Book book;

    f = fopen("librarian.check", "r");
    if (f == NULL) {
        fclose(f);
        f = fopen("librarian.check", "w");
        fputc(1, f);
        fclose(f);
    } else {
        fclose(f);
    }

    f = fopen("id.check", "r");
    if (f == NULL) {
        fclose(f);
        f = fopen("id.check", "w");
        fputc(0, f);
        fclose(f);
    } else {
        fclose(f);
    }

    printf("Anmelden als \n");
    printf("1: Bibliothekar\n");
    printf("2: Student\n");
    printf("3: Abbrechen\n");
    printf("Auswahl eingeben: ");
    scanf("%c", &option);
    switch(option) {
        case '1':
            f = fopen("librarian.check", "r");
            if (f == NULL) {
                printf("Datei konnte nicht geoeffnet werden!\n");
                exit(0);
            } else {
                first_time = fgetc(f);
                if (first_time == 1) {
                    fclose(f);
                    flush();
                    printf("Benutzername und Passwort setzen\n");
                    printf("Benutzername (max. 14 Zeichen): ");
                    fgets(user.username, 15, stdin);
                    printf("Passwort (max. 14 Zeichen): ");
                    fgets(user.password, 15, stdin);

                    char str[20],c=' ';



                    f = fopen("credential.bin", "wb");
                    if (f == NULL) {
                        printf("Error\n");
                        exit(0);
                    }
                    fwrite(&user, sizeof(User), 1, f);
                    fclose(f);
                    printf("Bitte neu einloggen\n");
                    f = fopen("librarian.check", "w");
                    fputc(0, f);
                    fclose(f);
                } else {
                    fclose(f);
                    flush();
                    printf("Login Daten eingeben\n");
                    printf("Benutzername: ");
                    fgets(username, 15, stdin);
                    printf("Passwort: ");
                    fgets(password, 15, stdin);


                    f = fopen("credential.bin", "rb");
                    if (f == NULL) {
                        printf("Error\n");
                        exit(0);
                    }
                    fread(&user, sizeof(User), 1, f);
                    if (strcmp(username,user.username) != 0 || strcmp(password, user.password) != 0) {
                        printf("Benutzername oder Passwort falsch!\n");
                        exit(0);
                    }
                    printf("Erfolgreich eingeloggt\n");
                    printf("1: Buch hinzufueger\n");
                    printf("2: Buch suchen\n");
                    printf("3: Buchinfo bearbeiten\n");
                    printf("4: Buch loeschen\n");
                    printf("4: Anfrage bearbeiten\n");
                    printf("Auswahl eingeben: ");
                    scanf("%c", &admin_option);
                    switch(admin_option) {
                        case '1':
                            flush();
                            printf("Geben Sie bitte folgende Informationen ein.\n");
                            printf("Titel: ");
                            fgets(book.title, 50, stdin);
                            printf("Author: ");
                            fgets(book.author, 50, stdin);
                            printf("ISBN: ");
                            fgets(book.ISBN, 50, stdin);
                            printf("Genre: ");
                            fgets(book.genre, 50, stdin);
                            printf("Verlag: ");
                            fgets(book.publisher, 50, stdin);
                            printf("Beschreibung: ");
                            fgets(book.description, 50, stdin);
                            book.borrowed = 0;

                            f = fopen("id.check", "r");
                            if (f == NULL) {
                                printf("Error\n");
                                exit(1);
                            }

                            id = fgetc(f);
                            fclose(f);
                            book.id = id;


                            f = fopen("book.record", "a");
                            fwrite(&book, sizeof(Book), 1, f);
                            fclose(f);

                            id++;
                            f = fopen("id.check", "w");
                            fputc(id, f);
                            fclose(f);

                            printf("Buch erolgreich hinzugefuegt.\n");
                            break;
                        case '2':
                            printf("Nach ID suchen: ");
                            scanf("%d", &id);

                            f = fopen("book.record", "rb");
                            found = 0;
                            i = 0;
                            while(fread(&book, sizeof(Book), 1, f)) {
                                if (book.id == id) {
                                    found = 1;
                                    printf("Suchergebnis\n");
                                    printf("Titel: %s", book.title);
                                    printf("Author: %s", book.author);
                                    printf("ISBN: %s", book.ISBN);
                                    printf("Genre: %s", book.genre);
                                    printf("Verlag: %s", book.publisher);
                                    printf("Beschreibung: %s", book.description);
                                    break;
                                }
                                i++;
                            }
                            if (found == 0) {
                                printf("Buch existiert nicht.\n");
                            }
                            fclose(f);
                            break;
                        case '3':
                            printf("Buch ID fuer Bearbeitung eingeben: ");
                            scanf("%d", &id);
                            f = fopen("book.record", "rb+");
                            found = 0;
                            while(fread(&book, sizeof(Book), 1, f)) {
                                if (book.id == id) {
                                    found = 1;
                                    break;
                                }
                            }
                            if (found == 0) {
                                printf("Buch existiert nicht.\n");
                            } else {
                                printf("Was moechten Sie bearbeiten?\n");
                                printf("1. Titel\n");
                                printf("2. Author\n");
                                printf("3. ISBN\n");
                                printf("4. Genre\n");
                                printf("5. Verlag\n");
                                printf("6. Beschreibung\n");
                                printf("Auswahl eingeben: ");
                                scanf("\n%c", &edit_option);
                                switch(edit_option) {
                                    case '1':
                                        flush();
                                        printf("Neuer Titel: ");
                                        fgets(book.title, 50, stdin);
                                        break;
                                    case '2':
                                        printf("Neuer Author: ");
                                        fgets(book.author, 50, stdin);
                                        break;
                                    case '3':
                                        printf("Neue ISBN: ");
                                        fgets(book.ISBN, 50, stdin);
                                        break;
                                    case '4':
                                        printf("Neues Genre: ");
                                        fgets(book.genre, 50, stdin);
                                        break;
                                    case '5':
                                        printf("Neuer Verlag: ");
                                        fgets(book.publisher, 50, stdin);
                                        break;
                                    case '6':
                                        printf("Neue Beschreibung: ");
                                        fgets(book.description, 255, stdin);
                                        break;
                                    default:
                                        printf("Waehlen Sie bitte eine Option aus Optionen 1-6.\n");
                                        break;
                                }
                                fseek(f, i, SEEK_SET);
                                fwrite(&book, sizeof(Book), 1, f);
                                fclose(f);
                                printf("Aenderungen gespeichert.\n");
                            }
                            break;
                        case '4':
                            printf("Buch ID zum Loeschen eingeben: ");
                            scanf("%d", &id);
                            f = fopen("book.record", "rb");
                            found = 0;
                            while(fread(&book, sizeof(Book), 1, f)) {
                                if (book.id == id) {
                                    found = 1;
                                    break;
                                }
                            }
                            fclose(f);
                            if (found == 0) {
                                printf("Buch existiert nicht.\n");
                            } else {
                                // create a temporary file
                                FILE * temp;
                                temp = fopen("book.temp", "a");
                                if (temp == NULL) {
                                    printf("Error\n");
                                    exit(1);
                                }

                                f = fopen("book.record", "rb");


                                while(fread(&book, sizeof(Book), 1, f)) {
                                    if (book.id != id)
                                        fwrite(&book, sizeof(Book), 1, temp);
                                }
                                fclose(f);
                                fclose(temp);
                                remove("book.record");
                                rename("book.temp", "book.record");
                                printf("Buch erfolgreich geloescht.\n");
                            }
                            break;
                        default:
                            printf("Waehlen Sie bitte eine Option aus Optionen 1-4.\n");
                            break;
                    }
                }
            }

            break;
        case '2':
            printf("ID eingeben, um Buch zu suchen: ");
            scanf("%d", &id);

            // search in the database
            f = fopen("book.record", "rb");
            found = 0;
            i = 0;
            while(fread(&book, sizeof(Book), 1, f)) {
                if (book.id == id) {
                    // matched
                    found = 1;
                    printf("Buch gefunden:\n");
                    printf("Title: %s", book.title);
                    printf("Author: %s", book.author);
                    printf("ISBN: %s", book.ISBN);
                    printf("Genre: %s", book.genre);
                    printf("Verlag: %s", book.publisher);
                    printf("Beschreibung: %s", book.description);
                    printf("Status: ");
                    if (book.borrowed == 1) {
                        printf("Momentan nicht verfuegbar.");
                    } else {
                        printf("Verfuegbar.\n");
                    }
                    break;
                }
                i++;
            }
            if (found == 0) {
                printf("Buch existiert nicht.\n");
            }
            fclose(f);
            break;
        case '3':
            printf("Auf Wiedersehen!\n");
            exit(0);
        default:
            printf("Waehlen Sie bitte eine Option aus Optionen 1 und 2.\n");
            break;
    }
    return 0;
}
