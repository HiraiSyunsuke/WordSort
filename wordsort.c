#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 256
#define N 20

//構造体宣言
struct Word{
        char *key;
        int num;
        struct Word *right;
        struct Word *left;
};

typedef struct Word NODE;
typedef NODE *BTREE;

//関数宣言
//木構造作成
BTREE insertNode(BTREE ,char *);
//単語用構造体作成
BTREE allocNode(char *);
//木構造表示
void printtree(BTREE );
//用意した構造体の開放
void freeBtree(BTREE );

int main(void){

    int i,j;//カウント用
    char sentence[max]={'\0'};//１行読み込み用
    char *text;//単語
    int flag=0;//フラグ管理用
    BTREE p;//単語の構造体のアドレス

    //アリスファイル読み込み
    FILE *fp;
	fp = fopen("Alice_in_Wonderland.txt", "r");

    if (fp == NULL) {
		printf("\nファイルないです\n");
	}
	else {
        
		while (fgets(sentence, 256, fp) != NULL) {
            //改行まで読み込み、文がなくなるまで続ける
			text=strtok(sentence, " \n");//単語に分ける
            if(flag==0){
                //1回目なら実行
                p=allocNode(text);//root用アドレス、構造体確保
                flag=1;
            }

            while(text!=NULL){
                text=strtok(NULL, " \n");//単語に分ける
                if(text!=NULL){
                    insertNode(p,text);//木構造に分類
                }
            }  
		}
	}

    //木構造表示
    printtree(p);
    //用意した構造体の開放
    freeBtree(p);
    //ファイルを閉じる
    fclose(fp);

    return 0;
}

//木構造作成
BTREE insertNode(BTREE node,char *text){
    BTREE p = node;
    int test;//既出の文字か確認用
    
    if(p==NULL){
        //領域確保
        p=allocNode(text);
        return p;
    }
    //既出の文字か確認
    test=strcmp(text,p->key);
    if(test==0){
        p->num=p->num+1;//文字が同じならカウントを増やす
    }
    else if(test>0){
        //辞書的に大きいなら右の枝へ
        p->right=insertNode(p->right,text);
    }
    else{
        //それ以外なら左の枝へ
        p->left=insertNode(p->left,text);
    }

    return p;
}

//単語用構造体作成
BTREE allocNode(char *text){
    BTREE p;

    //単語の構造体の領域確保
    p=(BTREE)malloc(sizeof(NODE));
    //キー、カウント、接続先の初期化
    p->key=malloc(sizeof(char[20]));
    strcpy(p->key,text);
    p->left=p->right=NULL;
    p->num=1;
    return p;
}

//木構造表示
void printtree(BTREE p){
    if(p !=NULL){
        printtree(p->left);//左の枝へ移動
        printf("Word:%s,Count:%d\n",p->key,p->num);//単語:カウント数　を表示
        printtree(p->right);//右の枝へ移動
    }
}

//用意した構造体の開放
void freeBtree(BTREE p){
    if (p != NULL ){
        freeBtree(p->left); // 左の枝を処理
        freeBtree(p->right); // 右の枝を処理
        free(p);//開放
    }
}