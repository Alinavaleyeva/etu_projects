#include <iostream>
#include <cstring>
#include <cstdlib>
#define N 3000
#define BUF_SIZE 30

class CustomStack {
public:
    // конструктор
    CustomStack() {
        mHead = nullptr;
    }
    // деструктор
    ~CustomStack() {
        ListNode *cur = mHead;
        ListNode *before;
        while (cur != nullptr) {
            before = cur->mNext;
            delete cur;
            cur = before;
        }
    }

    void push(const char* arr){
        auto * new_el = new ListNode;
        new_el -> mData = new char[strlen(arr)];
        strcpy(new_el -> mData,arr);
        new_el -> mNext = mHead;
        mHead = new_el;
    }

    void pop(){
        if(!size()){
            cout << "wrong" << endl;
            exit(0);
        }

        ListNode* tmp = mHead;
        delete mHead -> mData;
        mHead = mHead -> mNext;
        delete tmp;
    }

    char* top(){
        if(!size()){
            cout << "wrong" << endl;
            exit(0);
        }
        return mHead -> mData;
    }

    size_t size(){
        size_t size_1 = 0;
        ListNode* tmp = mHead;

        while(tmp != nullptr){
            size_1++;
            tmp = tmp -> mNext;
        }
        return size_1;
    }

    bool empty(){
        return size() == 0;
    }

protected:
    ListNode* mHead;
};

int main() {
    char* text = new char[N];
    fgets(text, N, stdin);
    CustomStack stack;
    int i = 0;
    int help = 0;

    while(help <= strlen(text)){

        if(text[help] == '<'){
            char* buff = new char[BUF_SIZE];

            while(text[help] != '>'){
                i++;
                help++;
            }
            strncpy(buff, text+help - i +1, i-1);
            if(strcmp(buff, "br") != 0 && strcmp(buff, "hr") != 0){
                if(buff[0]!='/'){
                    stack.push(buff);
                } else{
                    if(!strcmp(stack.top(), buff+1)) stack.pop();
                    else{
                        cout << "wrong" << endl;
                        return 0;
                    }
                }
            }
            i = 0;
        }
        help++;
    }

    if (stack.empty()){
        cout << "correct" << endl;
    }
    else{
        cout << "wrong" << endl;
    }
    return 0;
}
