#include <stdio.h>
#include <string.h>

int taille = 0;

enum Priority { HAUTE, MOYENNE, BASSE };

struct date {
    int day;
    int month;
    int year;
};

struct Taches {
    char tache_name[50];
    char description[100];
    enum Priority priority;
    struct date tacheDate;
};

void add_tache(struct Taches tache[]) {
    printf("++ Ajouter une t�che:\n");
    printf("   T�che: ");
    scanf(" %[^\n]s", tache[taille].tache_name);

    printf("   Description: ");
    scanf(" %[^\n]s", tache[taille].description);

    printf("   Priorit� (0-HAUTE, 1-MOYENNE, 2-BASSE): ");
    scanf(" %d", &tache[taille].priority);

    printf("   Date (jour mois ann�e): ");
    scanf("%d/%d/%d", &tache[taille].tacheDate.day, &tache[taille].tacheDate.month, &tache[taille].tacheDate.year);
    printf("\n");

    while (getchar() != '\n'); // Pour consommer le caract�re de nouvelle ligne restant dans le tampon
    taille++;
}

void Affichage(struct Taches tache[]) {
    printf("\n");
    printf("++++++++++++++++++++++++++++\n");
    printf("++ Liste des T�ches:\n");
    for (int i = 0; i < taille; i++) {
        printf("++++++++++++++++++++++++++++\n");
        printf("T�che %d : %s\n", i + 1, tache[i].tache_name);
        printf("   Description : %s\n", tache[i].description);
        printf("   Priorit� : ");
        switch (tache[i].priority) {
            case HAUTE:
                printf("Haute\n");
                break;
            case MOYENNE:
                printf("Moyenne\n");
                break;
            case BASSE:
                printf("Basse\n");
                break;
            default:
                printf("Inconnue\n");
                break;
        }
        printf("   Date : %d/%d/%d\n", tache[i].tacheDate.day, tache[i].tacheDate.month, tache[i].tacheDate.year);
        printf("\n");
    }
}

void modi_name(struct Taches tache[], int num_tache) {
    char new_name[100];
    printf("++ Modifier le nom de la t�che %d:\n", num_tache);
    printf("   Nouveau nom de la t�che : ");
    scanf(" %[^\n]", new_name);

    strcpy(tache[num_tache - 1].tache_name, new_name);
    printf("   Nom modifi� avec succ�s.\n");
}

void modi_description(struct Taches tache[], int num_tache) {
    char new_desc[100];
    printf("++ Modifier la description de la t�che %d:\n", num_tache);
    printf("   Nouvelle description : ");
    scanf(" %[^\n]", new_desc);

    strcpy(tache[num_tache - 1].description, new_desc);
    printf("   Description modifi�e avec succ�s.\n");
}

void modi_priority(struct Taches tache[], int num_tache) {
    int new_prio;
    printf("++ Modifier la priorit� de la t�che %d:\n", num_tache);
    printf("   Nouvelle priorit� (0-HAUTE, 1-MOYENNE, 2-BASSE) : ");
    scanf(" %d", &new_prio);
    tache[num_tache - 1].priority = (enum Priority)new_prio;
    printf("   Priorit� modifi�e avec succ�s.\n");
}

void modi_date(struct Taches tache[], int num_tache) {
    int new_day, new_month, new_year;
    printf("++ Modifier la date de la t�che %d:\n", num_tache);
    printf("   Nouvelle date (jour mois ann�e) : ");
    scanf(" %d %d %d", &new_day, &new_month, &new_year);

    tache[num_tache - 1].tacheDate.day = new_day;
    tache[num_tache - 1].tacheDate.month = new_month;
    tache[num_tache - 1].tacheDate.year = new_year;
    printf("   Date modifi�e avec succ�s.\n");
}

void modification(struct Taches tache[]) {
    int num_tache;
    printf("++ Modifier une t�che:\n");
    printf("   Entrer le num�ro de la t�che que vous voulez modifier : ");
    scanf("%d", &num_tache);

    if (num_tache >= 1 && num_tache <= taille) {
        int where_modi;
        printf("   Que voulez-vous modifier ?\n ");
        printf("      <1> : Nom\n");
        printf("      <2> : Description\n");
        printf("      <3> : Priorit�\n");
        printf("      <4> : Date\n");
        printf("   Choix : ");
        scanf("%d", &where_modi);

        switch (where_modi) {
            case 1:
                modi_name(tache, num_tache);
                break;

            case 2:
                modi_description(tache, num_tache);
                break;

            case 3:
                modi_priority(tache, num_tache);
                break;

            case 4:
                modi_date(tache, num_tache);
                break;

            default:
                break;
        }
    } else {
        printf("   T�che non trouv�e.\n");
    }
}

void remove_tache(struct Taches tache[]) {
    int pos;
    printf("++ Supprimer une t�che:\n");
    printf("   Entrer le num�ro de la t�che � supprimer : ");
    scanf("%d", &pos);

    if (pos >= 1 && pos <= taille) {
        for (int i = pos - 1; i < taille - 1; i++) {
            tache[i] = tache[i + 1];
        }
        taille--;
        printf("   T�che supprim�e avec succ�s.\n");
    } else {
        printf("   Num�ro de t�che invalide.\n");
    }
}

void tri_decroissant(struct Taches tache[]) {
    for (int i = 0; i < taille - 1; i++) {
        for (int j = i + 1; j < taille; j++) {
            if (tache[i].tacheDate.year < tache[j].tacheDate.year ||
                (tache[i].tacheDate.year == tache[j].tacheDate.year &&
                 tache[i].tacheDate.month < tache[j].tacheDate.month) ||
                (tache[i].tacheDate.month == tache[j].tacheDate.month &&
                 tache[i].tacheDate.day < tache[j].tacheDate.day)) {
                struct Taches temp;
                temp = tache[i];
                tache[i] = tache[j];
                tache[j] = temp;
            }
        }
    }
    Affichage(tache);
}

void tri_croissant(struct Taches tache[]) {
    for (int i = 0; i < taille - 1; i++) {
        for (int j = i + 1; j < taille; j++) {
            if (tache[i].tacheDate.year > tache[j].tacheDate.year ||
                (tache[i].tacheDate.year == tache[j].tacheDate.year &&
                 tache[i].tacheDate.month > tache[j].tacheDate.month) ||
                (tache[i].tacheDate.month == tache[j].tacheDate.month &&
                 tache[i].tacheDate.day > tache[j].tacheDate.day)) {
                struct Taches temp;
                temp = tache[i];
                tache[i] = tache[j];
                tache[j] = temp;
            }
        }
    }
    Affichage(tache);
}

void filtrer(struct Taches tache[]) {
    int choix_priopity;
    printf("++ Filtrer les t�ches:\n");
    printf("   Choisissez votre priorit� (0-HAUTE, 1-MOYENNE, 2-BASSE): ");
    scanf("%d", &choix_priopity);

    printf("   R�sultats de filtrage :\n");
    for (int i = 0; i < taille; i++) {
        if (tache[i].priority == choix_priopity) {
            printf("   T�che %d : %s\n", i + 1, tache[i].tache_name);
            printf("      Description : %s\n", tache[i].description);
            printf("      Priorit� : ");
            switch (tache[i].priority) {
                case HAUTE:
                    printf("Haute\n");
                    break;
                case MOYENNE:
                    printf("Moyenne\n");
                    break;
                case BASSE:
                    printf("Basse\n");
                    break;
                default:
                    printf("Inconnue\n");
                    break;
            }
        }
    }
}

void Menu(struct Taches tache[]) {
    int choix;
    do {
        printf("::::::::::::::::::::: Menu :::::::::::::::::::::\n");
        printf("   <1> Ajouter une T�che\n");
        printf("   <2> Afficher la Liste des T�ches\n");
        printf("   <3> Modifier une T�che\n");
        printf("   <4> Supprimer une T�che\n");
        printf("   <5> Ordonner les T�ches\n");
        printf("   <6> Filtrer les T�ches\n");
        printf("   <7> Quitter\n");
        printf("::::::::::::::::::: choix : ");
        
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                add_tache(tache);
                break;

            case 2:
                Affichage(tache);
                break;

            case 3:
                Affichage(tache);
                modification(tache);
                break;

            case 4:
                remove_tache(tache);
                break;

            case 5:
                int num_choix_tri;
                printf("   Voulez-vous que les t�ches soient tri�es dans l'ordre :\n");
                printf("      <1> D�croissant\n");
                printf("      <2> Croissant\n");
                printf("   Choix : ");
                scanf("%d", &num_choix_tri);

                switch (num_choix_tri) {
                    case 1:
                        tri_decroissant(tache);
                        break;

                    case 2:
                        tri_croissant(tache);
                        break;

                    default:
                        printf("   Vous pouvez choisir 1 ou 2 seulement!\n");
                }
                break;

            case 6:
                filtrer(tache);
                break;

            case 7:
                printf("   Au revoir\n");
                break;

            default:
                printf("   Choix invalide. Entrer un choix entre 1 et 7!\n");

        }
    } while (choix != 7);
}

int main() {
    struct Taches tache[50];
    Menu(tache);

    return 0;
}
