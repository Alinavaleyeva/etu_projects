#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TEXT_SIZE 100

// функция для получения предложения в массив предложений
char* readSentence() {
    int size = TEXT_SIZE;
    int sentence_len = 0;
    char* sentence = malloc(size * sizeof(char));
    int symbol = getchar();
    if (symbol == '\n');
        // работа с табуляцией
    else {
        if (symbol != ' ' && symbol != '\t'){
            sentence[sentence_len++] = symbol;
        }
    }
    symbol = getchar();
    if (symbol != ' ' && symbol != '\t') {
        sentence[sentence_len++] = symbol;
    }
    do{
        symbol = getchar();
        sentence[sentence_len++] = symbol;
        if (sentence_len == size) {
            size += TEXT_SIZE;
            sentence = realloc(sentence, size);
        }
    }while (symbol != '.' && symbol != ';' && symbol != '?' && symbol != '!');
    sentence[sentence_len] = '\0';
    return sentence;
}
// проверка предложения на количество заглавных букв
int check_sentence(char *s){
    int count = 0;
    for(int i=0; i<strlen(s); i++){
        if(isupper(s[i])){
            count += 1;
        }
    }
    if(count > 1){
        return 0; // неподходящее
    }
    return 1; // подходящее
}

int main(){
    int size = TEXT_SIZE;
    char** text = malloc(size*sizeof(char*));
    char* end_sent = "Dragon flew away!";
    int sentence_add = 0, sentence_delete = 0; // sentence_add - количество подходящих, sentence_delete - неподходящих
    char* sentence;
    sentence = readSentence();
    if (check_sentence(sentence)) { // если предложение подходит - добавляем
        text[sentence_add++] = sentence;
    }
    else{
        sentence_delete += 1;
    }
    while (strcmp(sentence, end_sent) != 0) {
        sentence = readSentence();
        if (check_sentence(sentence)) { // если предложение подходит - добавляем
            text[sentence_add++] = sentence;
        }
        else{
            sentence_delete += 1;
        }
        if (sentence_add == size) {
            size += TEXT_SIZE; // eсли память закончилась, добавляем
            text = realloc(text, size * sizeof(char*));
        }
    }
    for (int i = 0; i < sentence_add; i++){
        puts(text[i]);
        free(text[i]);
    }
    free(text);

    printf("Количество предложений до %d и количество предложений после %d\n", sentence_add + sentence_delete - 1, sentence_add - 1);
    return 0;
}
