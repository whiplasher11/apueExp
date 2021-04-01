#include "stdio.h"
#include <stdlib.h>
#include <string.h>

struct stuInfo
{
    char name[10];
    /* data */
};

struct node
{
    struct stuInfo data;
    struct node *next;
        /* data */
};

struct node* CreateList(){
    struct node* head = (struct node*)malloc(sizeof(struct node));
    head->next=NULL;
    return head;
}

void InsertList(struct node* head){
    //struct stuInfo = (struct stuInfo)malloc()
    struct node* n = (struct node*)malloc(sizeof(struct node));
    strcpy(n->data.name, "tlq");

    // 插入到头部
    struct node* next = head->next;
    head->next = n;
    n->next = next;
}

void PrintList(const struct node* head) {
    struct node* p;

    for (p = head->next; p; p = p->next) {
        printf("name: %s\t", p->data.name);
    }
        printf("\n");

}

int main(int argc,char *argv[]){

    int cmd;
    struct node *head;
    while(1){
        scanf("%d", &cmd);
        switch (cmd)
        {
        case 1:
            head=CreateList();
            break;
        case 2:
            InsertList(head);
            break;
        case 3:
            PrintList(head);
        default:
            break;
        }
    }
}

