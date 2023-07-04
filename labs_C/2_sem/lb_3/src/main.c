#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define MXSZ 5000

typedef struct file{
    char name[50];
    char way[MXSZ];
} file;

void read_file(int size, file **arr){
    FILE *res = fopen("./result.txt", "w");
    for(int i = 0; i < size; i++){
        fprintf(res, "%s\n", arr[i]->way);
    }
    fclose(res);
}

void directory(char* path, file **clt, int *n){
    DIR *dir = opendir(path);
    char temp[MXSZ];
    strcpy(temp, path);
    strcat(temp, "/");
    if(!dir)
        return;
    struct dirent *elem;
    while((elem = readdir(dir))){
        if(!strcmp(elem->d_name, "..") || !strcmp(elem->d_name, "."))
            continue;
        int len = strlen(temp);
        strcat(temp, elem->d_name);
        if(elem->d_type == DT_REG){
            file *nwelem = (file *) malloc(sizeof(file));
            strcpy(nwelem->name, elem->d_name);
            strcpy(nwelem->way, temp);
            temp[len] = '\0';
            clt[(*n)++] = nwelem;

        }
        else if(elem->d_type == DT_DIR){
            directory(temp, clt, n);
            temp[len] = '\0';
        }
    }
}

void mntr(file *elem, file **res, int idx, file **arr, int size, int *flag){

    res[idx] = elem;
    FILE *broker = fopen(elem->way, "r");
    char txt[MXSZ];
    fgets(txt, MXSZ, broker);
    char *t;
    if(!strcmp(txt, "Minotaur")){
        *flag = 1;
        read_file(idx + 1, res);
    }
    while(!feof(broker)){
        t = strchr(txt, '\n');
        if(t){
            *(t) = '\0';
        }
        char *tok = strtok(txt, " ");
        tok = strtok(NULL, " ");
        for (int i = 0; i < size; i++) {
            if (!strcmp(arr[i]->name, tok)) {
                mntr(arr[i], res, idx + 1, arr, size, flag);
                break;
            }
        }
        if(*flag)
            break;
        fgets(txt, MXSZ, broker);
    }

    fclose(broker);
}

int main(){
    int n = 0, i, flag = 0;
    file **clt = (file **)malloc(sizeof(file *) * MXSZ), **res = (file **)malloc(sizeof(file *) * MXSZ);
    directory("./labyrinth", clt, &n);
    for(i = 0; i < n; i++){
        if(!strcmp("file.txt", clt[i]->name)){
            mntr(clt[i], res, 0, clt, n, &flag);
        }
    }
    for(i = 0; i < n; i++){
        free(clt[i]);
    }
    free(clt);
}
