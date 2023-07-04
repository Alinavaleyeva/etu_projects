#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include "sent_changes.h"
#include "read_and_err.h"
#include "cw_all_func.h"
#include <wctype.h>
#define BUF_SIZE 100
#define MEM_SIZE 50

// заполнение словаря словами текста
void create_dict_from_text(Text_s *text, Dictionary_s *once_words) {
    Dictionary_s *words = create_empty_dict(); // слова
    Dictionary_s *seps = create_empty_dict(); // сепараторы
    for (int i = 0; i < text->count_sentence; i++){
        add_dictionary_from_sent(words, seps, &text->text_arr[i]); // создаем словари из слов и сепараторов предложения
    }
    for (int i = 0; i < words->count_words; i++){
        int flag = 1;
        for (int j = 0; j < once_words->count_words; j++){
            if (wcscasecmp(words->words_arr[i].word_arr, once_words->words_arr[j].word_arr) == 0) {
                once_words->words_arr[j].repeat++;
                flag = 0;
            }
        }
        if (flag == 1){
            add_word(once_words, words->words_arr[i].word_arr, words->words_arr[i].count_symbols);
        }
    }
    free_dict(words);
    free_dict(seps);
}

void print_dict(Dictionary_s *dict){
    wprintf(L"\t\tWORDS ONCE\n\n");
    for (int i = 0; i < dict->count_words; i++) {
        Word_s word = dict->words_arr[i];
       // if (word.repeat == 1 ){
       wprintf(L"%ls %ld\n", word.word_arr, word.repeat);
        //}

    }
    wprintf(L"\t\t------------------------\n\n");
}

// функция, печатающая предложения и произведение длин слов в них
void text_multiplication(Text_s *text){
    wprintf(L"<------------------------------->\n\t\tSORTED\n\n");
    for (int i = 0; i < (*text).count_sentence; i++) {
        wprintf(L"произведение длин слов: <%ld>\t sentence <%ls>\n", (*text).text_arr[i].multiplication,
                (*text).text_arr[i].sentence_arr);
    }
    wprintf(L"<------------------------------->\n");
}

//функция сравнения строк по значению произведения длин слов
int compare(const void *a, const void *b){
    Sentence_s sent_1 = *(Sentence_s *) a; // преобразовываю void * к sentence * и разыменовываю
    Sentence_s sent_2 = *(Sentence_s *) b;
    if (sent_1.multiplication < sent_2.multiplication) {
        return -1;
    }
    if (sent_1.multiplication > sent_2.multiplication) {
        return 1;
    } else {
        return 0;
    }
}

// проверка на число
int is_number(wchar_t* str){
    for (int i = 0; str[i] != '\0'; i++){
        if (iswdigit(str[i]) == 0)
            return 0;
    }
    return 1;
}

// поиск месяца
int number_of_month(wchar_t* month){
    wchar_t months[][20] = {
            L"Января",
            L"Февраля",
            L"Марта",
            L"Апреля",
            L"Мая",
            L"Июня",
            L"Июля",
            L"Августа",
            L"Сентября",
            L"Октября",
            L"Ноября",
            L"Декабря"
    };
    for (int i = 0; i < 12; i++){
        if (wcscasecmp(month, months[i]) == 0){
            return i+1;
        }
    }
    return 0;
}

// проверка на корректность введенной даты
int is_correct_data(unsigned long int date_number, int month_number, unsigned long int year_number){
    if ((1<=date_number <= 31) && (1<=year_number <= 9999)){
        int limit = 31;
        switch (month_number) {
            case 4:
                limit = 30;
                break;
            case 6:
                limit = 30;
                break;
            case 9:
                limit = 30;
                break;
            case 11:
                limit = 30;
                break;
            case 2:
                limit = 28;
                break;
            default:
                break;
        }
        return (date_number <= limit);
    }
}
// замена даты на требуемую
void replace_data(Text_s* text){
        for (int i = 0; i<text->count_sentence; i++){
            //разбиение
            Sentence_s* sent = &text->text_arr[i];
            Dictionary_s* words = create_empty_dict();
            Dictionary_s* seps = create_empty_dict();
            add_dictionary_from_sent(words, seps, sent);
            //обработка
            for (int j = 0; j < words->count_words-3; j++){
                Word_s date = words->words_arr[j];
                Word_s month = words->words_arr[j+1];
                Word_s year = words->words_arr[j+2];
                Word_s g = words->words_arr[j+3];
                if (wcscmp(g.word_arr, L"г") == 0) {
                    if (is_number(date.word_arr) && is_number(year.word_arr)) {
                        int month_number = number_of_month(month.word_arr);
                        if (month_number != 0) {
                            wchar_t* end = NULL;
                            unsigned long int date_number = wcstoul(date.word_arr, &end,10); // 10 с/сч
                            end = NULL;
                            unsigned long int year_number = wcstoul(year.word_arr, &end,10);
                            if (is_correct_data(date_number, month_number, year_number)){

                                // дата
                                date.word_arr = realloc(date.word_arr, 3 * sizeof(wchar_t));
                                err(!date.word_arr);
                                swprintf(date.word_arr, 3, L"%02d", date_number);
                                date.count_symbols = 2;

                                // месяц
                                month.word_arr = realloc(month.word_arr, 3 * sizeof(wchar_t));
                                if (month.word_arr == NULL) {
                                    err(1);
                                }
                                swprintf(month.word_arr, 3, L"%02d", month_number);
                                month.count_symbols = 2;

                                // год
                                year.word_arr = realloc(year.word_arr, 5 * sizeof(wchar_t));
                                if (year.word_arr == NULL) {
                                    err(1);
                                }
                                swprintf(year.word_arr, 5, L"%04d", year_number);
                                year.count_symbols = 4;

                                // буква г
                                g.word_arr[0] = L'\0';
                                g.count_symbols = 0;

                                // слеши как разделители
                                Word_s sep1 = seps->words_arr[j];
                                Word_s sep2 = seps->words_arr[j+1];
                                wcscpy(sep1.word_arr, L"/");
                                wcscpy(sep2.word_arr, L"/");
                            }
                        }
                    }
                }
            }
            //склейка
            sent_from_dict(words,seps, sent);
            //очищаем после склейки
            free_dict(words);
            free_dict(seps);
        }
    print_text(text);
}

// функция вывода текста
void print_text(Text_s *text) {
    for (int i = 0; i < text->count_sentence; i++) {
        wprintf(L"%ls\n", text->text_arr[i].sentence_arr);
    }
    wprintf(L"\n<------------------------------->\n");
}

int cmp_dict(const void *a, const void *b){
    Word_s word_1 = *(Word_s *) a;
    Word_s word_2 = *(Word_s *) b;
    if (word_1.repeat < word_2.repeat) {
        return -1;
    }
    if (word_1.repeat > word_2.repeat) {
        return 1;
    } else {
        return 0;
    }
}


// выбор пользователя (0-4)
void user_selection(Text_s *text) {
    wprintf(L"\n\nТекст считан\n\n");
    wprintf(L"Программа может выполнить следующие функции:\n"
            "1)Распечатать каждое слово которое встречается не более одного раза в тексте.\n"
            "2)Каждую подстроку в тексте имеющую вид “<день> <месяц> <год> г.” заменить на подстроку вида “ДД/ММ/ГГГГ”.\n"
            "3)Отсортировать предложения по произведению длин слов в предложении.\n"
            "4)Удалить все предложения, которые содержат символ ‘#’ или ‘№’, но не содержат ни одной цифры.\n"
            //"5) напечатать текст\n"
            "0)Выход из программы\n");
    long int way;
    Dictionary_s *dict_w = create_empty_dict();
    Dictionary_s *dict_s = create_empty_dict();
    Dictionary_s *once_words = create_empty_dict();
    wprintf(L"\nвыберете что делать: ");
    wscanf(L"%ld", &way);
        switch (way){
            case 1:
                create_dict_from_text(text, once_words);
                // qsort((*once_words).words_arr->word_arr, (*once_words).count_words, sizeof (Dictionary_s),cmp_dict);
                print_dict(once_words);
                break;
            case 2:
                replace_data(text);
                break;
            case 3:
                qsort((*text).text_arr, (*text).count_sentence, sizeof(Sentence_s), compare);
                text_multiplication(text);
                break;
            case 4:
                del_special_sentence(text);
                break;
            case 5:
                create_dict_from_text(text, once_words);
                qsort((*once_words).words_arr, (*once_words).count_words, sizeof (Word_s),cmp_dict);
                print_dict(once_words);
                break;
            case 0:
                wprintf(L"Программа закончилась\nСпасибо за использование!\n");
                break;
            default:
                err(2);
                break;
        }
        free(dict_w);
        free(dict_s);
        free(once_words);
}