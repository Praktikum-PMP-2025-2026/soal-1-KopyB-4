/** EL2008 Praktikum Pemecahan Masalah dengan Pemrograman 2024/2025
 *   Modul               : 04 - Dynamic Structures
 *   Hari dan Tanggal    : Rabu, 05 Mei 2026
 *   Nama (NIM)          : Luis Matthew Sembiring (13224053)
 *   Nama File           : soal1.c
 *   Deskripsi           : Menampilkan antrian dan waktu yang harus ditunggu
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pasien {
    char ID[100];
    int time;
    struct Pasien* next;
} Pasien;

typedef struct Queue{
    Pasien *front;
    Pasien *back;
} queue;

Pasien *createNode(char* ID, int time){
    Pasien *p = (Pasien *)malloc(sizeof(Pasien));
    strcpy(p->ID, ID);
    p->time = time;
    p->next = NULL;
    return p;
}

queue *createQueue(){
    queue *q = (queue *)malloc(sizeof(queue));
    q->front = q->back = NULL;
    return q;
}

int isEmpty(queue *q){
    return q->front == NULL;
}

void enqueue(queue *q, char* ID, int time){
    Pasien *p = createNode(ID, time);
    if (isEmpty(q)) {
        q->front = q->back = p;
    } else {
        q->back->next = p;
        q->back = p;
    }
}

void printQueue(queue *q){
    Pasien *temp = q->front;
    while (temp != NULL) {
        printf("%s ", temp->ID);
        temp = temp->next;
    }
    printf("\b \b");
    printf("\n");
}

int checktime(queue *q){
    if (isEmpty(q)){
        return -1;
    }
    Pasien *temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL)
        q->back = NULL;
    int data = temp->time;
    free(temp);
    return data;
}

int main(){
    queue *q = createQueue();
    int n;
    int temp = 0;
    int waittime = 0;
    scanf("%d", &n);

    Pasien *data = (Pasien*)malloc(n*sizeof(Pasien));
    if (data == NULL) {
        return 1;
    }

    for (int i=0; i<n; i++){
        scanf("%s %d", data[i].ID, &data[i].time);
        enqueue(q, data[i].ID, data[i].time);
    }

    printf("ORDER ");
    printQueue(q);

    for (int i=0; i<n-1; i++){
        int timedif = checktime(q);
        temp = temp + timedif;
        waittime = waittime + temp;

    }

    printf("WAIT ");
    printf("%d", waittime);

    return 0;
}