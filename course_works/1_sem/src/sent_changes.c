#include <string.h>
#include <wchar.h>
#include <ctype.h>
#include "stdlib.h"
#define BUF_SIZE 100
#define MEM_SIZE 50
#include "structs.h"
#include "sent_changes.h"

// функция удаления повторяющихся строк
void del_replay_sentences(Text_s* text){
    for (int i = 0; i < (*text).count_sentence; i++){
        for (int j = i+1; j < (*text).count_sentence; j++){
            // ускорения программы, предложения будут сравниваться только при одинаковом количестве символов
            if ((*text).text_arr[i].count_char == (*text).text_arr[j].count_char) {
                if (wcscasecmp((*text).text_arr[i].sentence_arr, (*text).text_arr[j].sentence_arr) == 0) { // проверка на совпадение без учета регистра
                    free(text->text_arr[j].sentence_arr);
                    memmove(((*text).text_arr) + j, ((*text).text_arr) + j + 1,(((*text).count_sentence) - j) * sizeof(Sentence_s));
                    (*text).count_sentence--;
                    // т.к. предложение удалено, курсор остается на том же индексе
                    j--;
                }
            }
        }
    }
}
// функция удаления предложений, содержащих ‘#’ или ‘№’, но не содержащих цифр
void del_special_sentence(Text_s *text){
    int flag_symbol = 0;
    int flag_digit = 0;
    for (int i = 0; i < (*text).count_sentence; i++) {
        for (int j = 0; j < (*text).text_arr[i].count_char; j++) {
            if ((*text).text_arr[i].sentence_arr[j] == '#' || (*text).text_arr[i].sentence_arr[j] == L'№') {
                flag_symbol = 1;
            }
            if (isdigit((*text).text_arr[i].sentence_arr[j])) {
                flag_digit = 1;
            }
        }
        if (flag_digit == 0 && flag_symbol == 1) {
            free(text->text_arr[i].sentence_arr);
            memmove((*text).text_arr + i, (*text).text_arr + i + 1,(((*text).count_sentence) - i) * sizeof(Sentence_s));
            (*text).count_sentence--;
            i--;
        }
        flag_symbol = 0;
        flag_digit = 0;
    }
    wprintf(L"<------------------------------->\n");
    wprintf(L"\t\tAFTER DELETE\n\n");
    for (int i = 0; i < (*text).count_sentence; i++) {
        wprintf(L"%ls\n", (*text).text_arr[i].sentence_arr);
    }
    wprintf(L"<------------------------------->\n");
}
