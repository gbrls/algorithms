#include <stdio.h>
#include <stdlib.h>

struct No {
    int val;
    No* next;
};

struct Lista {
    No* head;

    Lista() {
        head=(No*)malloc(sizeof(No));
        head->next=NULL;
    }

    ~Lista() {
        No* p = head;
        while(p!=NULL) {
            No* prev = p;
            p=p->next;
            free(prev);
        }
    }

    // Retorna um ponteiro para o elemento anterior ao desejado
    No* list_pos(int i) {
        No* p = head;
        int cnt=0;
        while(cnt<i && p!=NULL) {
            p=p->next;
            cnt++;
        }

        return p;
    }

    void print() {
        No*p = head->next;
        while(p!=NULL) {
            printf("%d ",p->val);
            p=p->next;
        }
        putchar('\n');
    }

    void add(int val) {
        No*p = head;
        while(p->next!=NULL) {
            p=p->next;
        }
        p->next = (No*) malloc(sizeof(No));
        p->next->val=val;
    }

    void add_at(int pos, int val) {
        No* p = list_pos(pos);
        No* next = p->next;

        No* novo = (No*) malloc(sizeof(No)); novo->val=val;
        p->next=novo;
        novo->next=next;
    }

    void remove(int i) {
        No* p = list_pos(i);
        No* next;
        if(p->next!=NULL) next=p->next->next;
        free(p->next);
        p->next=next;
    }

};

int main() {

    Lista l = Lista();
    l.add(1);l.add(2);l.add(3);

    l.print();
    l.add_at(1,42);
    l.print();
    l.remove(2);
    l.print();

    printf("%d\n",l.list_pos(3)->val);
    return 0;
}
