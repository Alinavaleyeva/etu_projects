#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEXT_SIZE 1000

int cmp(const void *key, const void *b){ // ключ, который передан - указатель имеет тип char *
    const char *k = (const char *) key;
    const char **p2 = (const char **) b;
    return strcmp(k, *p2);
}

int compare(const void* a, const void* b){
    const char** first = (const char**)a;
    const char** second = (const char**)b;
    return strcmp(*first, *second);
}


int main(){
    char** text = (char**) malloc((TEXT_SIZE) * sizeof (char *));
    int count_words = 0;
    char str[1000];
    fgets(str, 1000, stdin);
    char* word;
    word = strtok(str, ". ");
    while (word != NULL){
        char* word_to_dict = malloc((strlen(word)+1)*sizeof (char));
        strcpy(word_to_dict, word);
        text[count_words] = word_to_dict;
        count_words++;
        word = strtok(NULL, ". \n"); // получаем новое слово
    }
    char* key = malloc(sizeof (char) * 31);
    fgets(key, 31, stdin);
    if(key[strlen(key)-1] == '\n')
        key[strlen(key)-1] = '\0';
    qsort(text, count_words, sizeof (char *), compare);
    char **res = bsearch(key, text, count_words, sizeof (char *), cmp);

    if (res != NULL){
        puts("exists");
    }
    else{
        puts("doesn't exist");
    }

    for (int i = 0; i < count_words; i++){
        //printf("%s\n" , text[i]);
        free(text[i]);
    }
    free(text);
    free(key);
}
