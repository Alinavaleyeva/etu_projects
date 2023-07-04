#pragma once
#include "structs.h"

void err(int a);
wchar_t* read_sent(int *count_char, int *multiplication);
void read_text (Text_s* text);
Dictionary_s *create_empty_dict();
void free_dict(Dictionary_s* my_dict);
void add_word(Dictionary_s * my_dict, wchar_t* word, int len);
void add_dictionary_from_sent(Dictionary_s* my_dict,  Dictionary_s *dict_seps, Sentence_s* sent);
void sent_from_dict(Dictionary_s* my_dict,  Dictionary_s *dict_seps, Sentence_s* sent);
