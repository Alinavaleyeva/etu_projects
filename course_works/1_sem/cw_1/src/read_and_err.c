#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#define BUF_SIZE 100
#define MEM_SIZE 50
#include "structs.h"
#include "read_and_err.h"

// функция ошибок
void err(int a) {
    switch (a) {
        case 1:
            wprintf(L"Ошибка! Выделение памяти невозможно!\n"); // если невозможно выделить память
            break;
        case 2:
            wprintf(L"Неверное значение! попробуйте еще раз\n");// не та цифра
            break;
        default:
            break;
    }
}

//чтение предложения
wchar_t *read_sent(int *count_char, int *multiplication) { // на вход длина предложения
    int len = 0; // количество введенных символов
    int size = BUF_SIZE; // буфер
    unsigned int c; // символ
    long int pr = 1;
    int len_word = 0;
    int tabulation_start  = 1;
    wchar_t *str = malloc(size * sizeof(wchar_t)); // выделяем память для предложения
    if (str == NULL) { // если 0, то ошибка переполнения памяти
        err(1);
    }
    do {
        c = getwchar();
        if (tabulation_start  == 1) {
            if (c == ' ') {
                continue;
            }else {
                tabulation_start  = 0;
            }
        }
        if (c != ',' && c != ' ' && c != '.') {
            len_word++;
        } else {
            if (len_word != 0) {
                pr = pr * len_word;
                len_word = 0;
            }
        }
        if (c == L'\n' && len == 0) {
            str[0] = c;
            *count_char = 1;
            return str;
        }
        //непосредственно считывание в массив
        str[len] = c;
        len++;
        if (len == size) {
            size += MEM_SIZE;
            str = (wchar_t *) realloc(str, size * sizeof(wchar_t));
            if (str == NULL) {
                err(1);
            }
        }
    } while (c != '.');
    *count_char = len; // длина предложения = количество введенных символов
    *multiplication = pr;
    str[len] = '\0'; // завершаем предложение
    return str; // возвращаем предложение
}

// чтение текста
void read_text(Text_s *text) {
    int real_size_text_arr = BUF_SIZE;
    text->text_arr = (Sentence_s *) malloc(real_size_text_arr * sizeof(Sentence_s));
    while (1) { // бесконечный цикл
        Sentence_s Sentence; //  создаем переменную типа структуры
        Sentence.sentence_arr = read_sent(&Sentence.count_char, &Sentence.multiplication);
        if (Sentence.sentence_arr[0] == L'\n') { // цикл прерывается, когда пользователь нажал \n
            free(Sentence.sentence_arr);
            break;
        }
        //добавили в массив предложений нашу структуру предложения
        (*text).text_arr[(*text).count_sentence] = Sentence; // так как переменная структуры text с указателем
        (*text).count_sentence++;
        //расширение памяти для хранения структур предложений
        if ((*text).count_sentence == real_size_text_arr) {
            (*text).text_arr = realloc((*text).text_arr, (real_size_text_arr + MEM_SIZE) * sizeof(Sentence_s));
            if ((*text).text_arr == NULL) {
                err(1);
            }
            real_size_text_arr += MEM_SIZE;
        }
    }
}

// создание пустого словаря
Dictionary_s *create_empty_dict(){
    Dictionary_s *empty_dict = malloc(sizeof(Dictionary_s));
    empty_dict->words_arr = NULL;
    empty_dict->count_words = 0;
    return empty_dict;
}

// очищение использованного словаря
void free_dict(Dictionary_s* dict){
    for (int i = 0; i < dict->count_words; i++) {
        Word_s word = dict->words_arr[i];
        free(word.word_arr);
        word.word_arr = NULL;
    }

    free(dict->words_arr);
    free(dict);
}

// функция добавления слов в словарь
void add_word(Dictionary_s *dict, wchar_t *word, int len) {
    Word_s *words_arr;
    if (dict->words_arr == NULL) { // пустой словарь указывает на NULL
        words_arr = malloc(sizeof(Word_s));
        dict->words_arr = words_arr;
    }else {
        //fwprintf(stderr, L"%d", my_dict->count_words+1);
        words_arr = realloc(dict->words_arr, (dict->count_words + 1) * sizeof(Word_s));
        if (words_arr != NULL) {
            dict->words_arr = words_arr;
        }
        else{
            err(1);
        }
    }
    dict->words_arr[dict->count_words].count_symbols = len;
    dict->words_arr[dict->count_words].repeat = 1;
    dict->words_arr[dict->count_words].count_up = -1;

    wchar_t *str;
    str = calloc((len + 1), sizeof(wchar_t));
    dict->words_arr[dict->count_words].word_arr = str;
    if (dict->words_arr[dict->count_words].word_arr == NULL) {
        err(1);
    }
    //fwprintf(stderr, L"%d %d\n", wcslen(word), len+1);
    wcsncpy((dict->words_arr)[dict->count_words].word_arr, word, len);
    dict->count_words++;
}

// заполнение словаря словами предложения
void add_dictionary_from_sent(Dictionary_s *my_dict, Dictionary_s *dict_seps, Sentence_s *sent) {
    wchar_t *sent_copy_w = malloc(sizeof(wchar_t) * (sent->count_char + 1)); // копия для нарезки слов
    wchar_t *sent_copy_s = malloc(sizeof(wchar_t) * (sent->count_char + 1)); // дл сепараторов
    wcscpy(sent_copy_w, sent->sentence_arr);
    wcscpy(sent_copy_s, sent->sentence_arr);
    if (sent_copy_w == NULL) {
        err(1);
    }
    if (sent_copy_s == NULL) {
        err(1);
    }
    wchar_t *ptr = NULL;
    wchar_t *old_ptr = NULL;
    wchar_t *word = wcstok(sent_copy_w, L" ,.\n\t", &ptr);
    while (word != NULL) {
        add_word(my_dict, word, ptr - word - 1/*wcslen(word)*/);
        // сохранение разделителей между словами
        if ((my_dict->count_words > 1) && old_ptr) {
            sent_copy_s[word - sent_copy_w] = '\0';
            add_word(dict_seps, (old_ptr - sent_copy_w + sent_copy_s - 1), (word - old_ptr) + 1);
        }
        old_ptr = ptr;
        word = wcstok(NULL, L" ,.\n\t", &ptr); // обновляем слово
    }
    free(sent_copy_w);
    free(sent_copy_s);
}

// склеивание строки обратно
void sent_from_dict(Dictionary_s *dict_words, Dictionary_s *dict_seps, Sentence_s *sent) {
    //склеивание строки обратно
    wcscpy(sent->sentence_arr, dict_words->words_arr[0].word_arr); // нулевое слово
    if (dict_words->count_words > 1) {
        for (int i = 0; i < dict_seps->count_words; i++) {
            wcscat(sent->sentence_arr, dict_seps->words_arr[i].word_arr); // сепаратор после нулевого слова
            wcscat(sent->sentence_arr, dict_words->words_arr[i + 1].word_arr); // слово
        }
    }
    wcscat(sent->sentence_arr, L"."); // последний сепаратор - точка
}



