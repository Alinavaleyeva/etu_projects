#include <locale.h>
#include <wchar.h>
// структура для предложений
typedef struct Sentence{
    wchar_t* sentence_arr; // предложение
    int count_char; // длина предложения
    int multiplication; // произведение длин слов
}Sentence_s;

// структура для текста (массива предложений)
typedef struct Text{
    Sentence_s *text_arr; // указатели на начала предложений
    int count_sentence; // количество предложений в тексте
}Text_s;

typedef struct Word{
    wchar_t *word_arr; // указатели на начало слово
    int count_symbols; // длина слова
    int repeat;
} Word_s;

typedef struct Dictionary{
    Word_s *words_arr; // указатель на первое слово
    int count_words; // количество слов
}Dictionary_s;