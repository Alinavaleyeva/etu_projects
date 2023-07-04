#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#define MEM_SIZE 50
#include "structs.h"
#include "sent_changes.h"
#include "read_and_err.h"
#include "cw_all_func.h"

// основная функция
int main(){
    setlocale(LC_ALL, "");
    Text_s text;
    text.count_sentence = 0;
    wprintf(L"\t\tВВЕДИТЕ ТЕКСТ\n");
    read_text(&text);
    del_replay_sentences(&text);
    wprintf(L"---------------ОБРАБОТАННЫЙ ТЕКСТ---------------\n");
    print_text(&text);
    user_selection(&text);
    for (int i = 0; i < text.count_sentence; i++) {
        Sentence_s  sentence = text.text_arr[i];
        free(sentence.sentence_arr);

    }
    free(text.text_arr);
    //wprintf(L"Всё удалено");
    return 0;
}
