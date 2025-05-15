#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m"

typedef struct {
    int id;
    char produs[50];
    int cantitate;
    float pret;
} Vanzare;

int este_numar_int(char *str) {
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

int este_nume_valid(char *str) {
    for (int i = 0; str[i]; i++) {
        if (!isalpha(str[i]) && str[i] != ' ') return 0;
    }
    return 1;
}

int este_float_valid(char *str) {
    int punct = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] == '.') {
            if (punct) return 0;
            punct = 1;
        } else if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

void flushInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void asteaptaEnter() {
    printf("\nApasati Enter pentru a reveni la meniul principal...");
    flushInput();
    getchar();
    system("cls");
}

void vizualizare_meniu() {
    FILE *vanzari_file = fopen("vanzari.txt", "r");
    if (vanzari_file == NULL) {
        perror("Eroare la deschiderea fisierului");
        asteaptaEnter();
        return;
    }

    const char *culori[] = {
        "\033[31m", // rosu
        "\033[32m", // verde
        "\033[33m", // galben
        "\033[34m", // albastru
        "\033[35m", // magenta
        "\033[36m", // cyan
        "\033[37m"  // alb
    };
    int nr_culori = sizeof(culori) / sizeof(culori[0]);

    printf("-= VIZUALIZARE MENIU =-\n\n");

    char linie[256];
    int linie_index = 0;
    while (fgets(linie, sizeof(linie), vanzari_file)) {
        char *cuvant = strtok(linie, " \n");
        int culoare_index = linie_index % nr_culori;

        while (cuvant != NULL) {
            printf("%s%s ", culori[culoare_index % nr_culori], cuvant);
            cuvant = strtok(NULL, " \n");
            culoare_index++;
        }

        printf("\033[0m\n"); // reset culori
        linie_index++;
    }

    fclose(vanzari_file);
    printf("\n");
    asteaptaEnter();
}



void adauga_vanzare() {
    Vanzare v;
    char buffer[100];

    printf("-= ADAUGA VANZARE=-\n");

    while (1) {
        printf("ID vanzare: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        if (este_numar_int(buffer)) {
            v.id = atoi(buffer);
            break;
        } else {
            printf("Eroare: ID-ul trebuie sa contina doar cifre. Reincercati.\n");
        }
    }

    while (1) {
        printf("Nume produs: ");
        fgets(v.produs, sizeof(v.produs), stdin);
        v.produs[strcspn(v.produs, "\n")] = '\0';

        if (este_nume_valid(v.produs)) {
            break;
        } else {
            printf("Eroare: Numele trebuie sa contina doar litere. Reincercati.\n");
        }
    }

    while (1) {
        printf("Cantitate: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        if (este_numar_int(buffer)) {
            v.cantitate = atoi(buffer);
            break;
        } else {
            printf("Eroare: Cantitatea trebuie sa fie un numar intreg. Reincercati.\n");
        }
    }

    while (1) {
        printf("Pret unitar: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        if (este_float_valid(buffer)) {
            v.pret = atof(buffer);
            break;
        } else {
            printf("Eroare: Pretul trebuie sa fie un numar real valid. Reincercati.\n");
        }
    }

    FILE *vanzari_file = fopen("vanzari2.txt", "a");
    if (vanzari_file == NULL) {
        perror("Eroare la deschiderea fisierului pentru scriere");
        asteaptaEnter();
        return;
    }

    fprintf(vanzari_file, "%d %s %d %.2f\n", v.id, v.produs, v.cantitate, v.pret);
    fclose(vanzari_file);

    printf("Vanzare adaugata cu succes!\n");
    asteaptaEnter();
}

void statistici_vanzari() {
    while (1) {
        printf("-= Statistici vanzari =-\n");
        printf("1. Cea mai profitabila zi\n");
        printf("2. Cel mai bine vandut produs sunt Shaorma si cartofii prajiti\n");
        printf("3. Media cantitatilor comandate este:\n   - Shaorma: 30 buc\n   - Kebab: 15 buc\n   - Cartofi prajiti: 20 buc\n");
        printf("4. Inapoi la meniu\n");

        int choice2 = 0;
        printf("Introduceti o optiune: ");
        if (scanf("%d", &choice2) != 1) {
            flushInput();
            printf("Optiune invalida! Incercati din nou.\n");
            continue;
        }

        system("cls");
        if (choice2 == 4) {
            break;
        }
        printf("Statistica selectata: %d\n", choice2);
        asteaptaEnter();
    }
}

int main(void) {
    while (1) {
        printf("-= Sistem inregistrare vanzari fast-food =-\n");
        printf("1. VIZUALIZARE MENIU\n");
        printf("2. ADAUGA VANZARE\n");
        printf("3. Statistici vanzari\n");
        printf("4. Iesire Aplicatie\n");

        int choice = 0;
        printf("Introduceti o optiune: ");
        scanf("%d", &choice);
        flushInput();
        system("cls");

        switch (choice) {
            case 1:
                vizualizare_meniu();
                break;
            case 2:
                adauga_vanzare();
                break;
            case 3:
                statistici_vanzari();
                break;
            case 4:
                printf("Iesire din aplicatie.\n");
                return 0;
            default:
                printf("Optiune invalida! Incercati din nou.\n");
                break;
        }
    }
}
