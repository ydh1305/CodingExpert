#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef struct node{
    struct node* child[63];
    int word;
}node;

node* newNode(){ //init
    node* New = (node *)malloc(sizeof(node));
    New->word=0;
    for (int i=0; i<63; i++) New->child[i]=0;
    return New;
}

void insert(node* root, const char* str){
    int len = strlen(str);
    node* now = root;

    for (int i=0; i<len;i++){
        if (!now->child[str[i]-65]) now->child[str[i]-65]= newNode();
        now=now->child[str[i]-65];
    }
    now->word=1;
}

void showtree(node* now, char* str, int depth){
    if (now->word) printf("%s\n", str);

    for (int i=62; i>=0; i--){
        if(now->child[i]) {
            str[depth]=i+65;
            str[depth+1]=0;
            showtree(now->child[i], str, depth+1);
        }
    }
}

int remove(node* now, const char* str, int i){
    if (i == strlen(str)){
        int chk=0;
        for (int i=0; i<63; i++){
            if (now->child[i]) chk=1;
        }
        if (chk) return 0;
        return 1;
    }

    if ( now->child[str[i]-65]){
        if (remove(now->child[str[i]-65], str, i+1)){
            free(now->child[str[i]-65]);
            now->child[str[i]-65]=0;

            int chk=0; 
            for (int i=0; i<63; i++){
                if (now->child[i]) chk=1;
            }

            if (chk) return 0;
            return 1;
        }
    }
    return 0;
}   

int main(){
    ios::sync_with_stdio(false);
    node* root = newNode();

    int N; cin >> N;
    char temp[21] = { 0, };
    for(int i = 0; i < N; i++) {
        char s1[6], s2[6];
        cin >> s1 >> s2;
        if(s2[0] == 'e') insert(root, s1);
        if(s2[0] == 'l') remove(root, s1, 0); 
    }
    showtree(root, temp, 0);

}
