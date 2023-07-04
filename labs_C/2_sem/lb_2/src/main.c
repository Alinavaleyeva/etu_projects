#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

//структура элемента
typedef struct Musical{
    char *name;
    char *author;
    int year;
    struct Musical *forward;
    struct Musical *back;
}MusicalComposition;

// заполнение полей структуры
MusicalComposition* createMusicalComposition(char* name, char* autor,int year){
    MusicalComposition *trak = malloc(sizeof(MusicalComposition)* 1);
    trak->name = name;
    trak->author = autor;
    trak->year = year;
    trak->back = NULL;
    trak->forward = NULL;
    return trak;
}

// добавление элемент в конец списка
void push(MusicalComposition* head, MusicalComposition* element){
    MusicalComposition *music = head;
    while (music->forward != NULL){
        music = music->forward;
    }
    music->forward = element;
    element->back = music;
}

// создание списка элементов
MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition *head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    for (int n2 = 1; n2 < n; n2++){
        MusicalComposition *elem = createMusicalComposition(array_names[n2], array_authors[n2], array_years[n2]);
        push(head, elem);
    }
    return head;
}

// удаление элемента
void removeEl(MusicalComposition* head, char* name_for_remove){
    MusicalComposition *music = head;
    while (music->forward != NULL){
        if (strcmp(music->name, name_for_remove) == 0){
            if (music->back != NULL){
                music->back->forward = music->forward;
            }
            if (music->forward != NULL){
                music->forward->back = music->back;
            }
        }
        music = music->forward;
    }
}

// количество элементов
int count(MusicalComposition* head){
    MusicalComposition *music = head;
    int count_real = 0;
    while (music != NULL){
        count_real ++;
        music = music->forward;
    }
    return count_real;
}

// печать элементов
void print_names(MusicalComposition* head){
    MusicalComposition *music = head;
    for (int i = 0; music!=NULL; i++){
        printf("%s\n", music->name);
        music = music->forward;
    }
}

int main(){
    int length;
    scanf("%d\n", &length);
    char** names = (char**)malloc(sizeof(char*)*length);
    char** authors = (char**)malloc(sizeof(char*)*length);
    int* years = (int*)malloc(sizeof(int)*length);

    for (int i=0;i<length;i++)
    {
        char name[80];
        char author[80];

        fgets(name, 80, stdin);
        fgets(author, 80, stdin);
        fscanf(stdin, "%d\n", &years[i]);

        (*strstr(name,"\n"))=0;
        (*strstr(author,"\n"))=0;

        names[i] = (char*)malloc(sizeof(char*) * (strlen(name)+1));
        authors[i] = (char*)malloc(sizeof(char*) * (strlen(author)+1));

        strcpy(names[i], name);
        strcpy(authors[i], author);

    }
    MusicalComposition* head = createMusicalCompositionList(names, authors, years, length);
    char name_for_push[80];
    char author_for_push[80];
    int year_for_push;

    char name_for_remove[80];

    fgets(name_for_push, 80, stdin);
    fgets(author_for_push, 80, stdin);
    fscanf(stdin, "%d\n", &year_for_push);
    (*strstr(name_for_push,"\n"))=0;
    (*strstr(author_for_push,"\n"))=0;

    MusicalComposition* element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

    fgets(name_for_remove, 80, stdin);
    (*strstr(name_for_remove,"\n"))=0;

    printf("%s %s %d\n", head->name, head->author, head->year);
    int k = count(head);

    printf("%d\n", k);
    push(head, element_for_push);

    k = count(head);
    printf("%d\n", k);

    removeEl(head, name_for_remove);
    print_names(head);

    k = count(head);
    printf("%d\n", k);

    for (int i=0;i<length;i++){
        free(names[i]);
        free(authors[i]);
    }
    free(names);
    free(authors);
    free(years);

    return 0;

}
