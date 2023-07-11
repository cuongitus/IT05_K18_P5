#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

//===================
// Khai bao cau truc dang DSLK don de chua danh Nhan Vien (NV)
struct NV
{
    int maNV;
    char hoTen[25];
    char dienThoai[11];
};
struct NodeNV
{
    NV info;
    struct NodeNV *next;
};
struct ListNV
{
    NodeNV *Head;
    NodeNV *Tail;
};

//===================
// Dinh nghia cac thao tac voi Nhan Vien
void nhapNV(NV &nv)
{
    printf("\n  Nhap Ma Nhan Vien: ");
    scanf("%d", &nv.maNV);
    printf("\n  Nhap Ho va Ten: ");
    fflush(stdin); gets(nv.hoTen);
    printf("\n  Nhap So dien thoai: ");
    fflush(stdin); gets(nv.dienThoai);
}

void inNV(NV nv)
{
    printf("\n Ma NV: %4d", nv.maNV);
    printf(" | Ho va Ten: %20s", nv.hoTen);
    printf(" | SDT: %15s", nv.dienThoai);
}

void initDSNV(ListNV &Q)
{
    Q.Head = NULL;
    Q.Tail = NULL;
}

NodeNV *getNodeNV(NV nv)
{
    NodeNV *p;
    p = new NodeNV();
    if (p == NULL)
    {
        printf("\n Khong thanh cong");
        exit(0);
    }

    p->info = nv;
    p->next = NULL;
    return p;
}

void chenDauNV(ListNV &Q, NodeNV *p)
{
    if (Q.Head == NULL)
    {
        Q.Head = p;
        Q.Tail = p;
    }
    else
    {
        p->next = Q.Head;
        Q.Head = p;
    }
}

int xoaNVTheoMa(ListNV &Q, int k){
    
    NodeNV *p = Q.Head, *q = NULL; 

    while (p != NULL){
        if(p -> info.maNV == k){
            break;
        }

        q = p;
        p = p->next;
    }

    if(p == NULL){
        return 0;
    }
    
    if(q != NULL){
        if(p == Q.Tail){
            Q.Tail = q;
            q ->next = p ->next;
            free(p);
        }
    }else{
        Q.Head = p-> next;
        if(Q.Head == NULL){
            Q.Tail = NULL;
        }
    }

    return 1;
}

NodeNV *timNVMa(ListNV Q, int k)
{
    NodeNV *p;
    for (p = Q.Head; p != NULL; p = p->next)
    {
        if (p->info.maNV == k)
            break;
    }
    return p;
}

NodeNV *timNVTen(ListNV Q, char s[])
{
    NodeNV *p;
    for (p = Q.Head; p != NULL; p = p->next)
    {
        if (strcmp(p->info.hoTen, s) == 0)
            break;
    }
    return p;
}

int demSoNV(ListNV Q)
{
    int count = 0;
    NodeNV *p;
    if ((Q.Head == NULL) && (Q.Tail == NULL)) return count;
    
    for (p = Q.Head; p != NULL; p = p->next)
    {
        count = count + 1;
    }
    return count;
}

void suaNVTheoMa(ListNV &Q, NV nv){

    NodeNV *p; 

    p = timNVMa(Q, nv.maNV);

    if(p != NULL){
        strcpy(p->info.hoTen, nv.hoTen);
        strcpy(p->info.dienThoai, nv.dienThoai);
        printf("\n Sua thong tin Nhan Vien thanh cong.");
    }
    else
    {
        printf("\n Khong co Nhan vien tuong ung de sua.");
    }   
}

void nhapDSNV(ListNV &Q)
{
    int n, i;
    NodeNV *p;
    NV nv;
    printf("\n Nhap so Nhan Vien: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("\n ------- Nhap Nhan Vien %d :", i + 1);
        if (demSoNV(Q) > 0)
        {
            NodeNV *px;
            do
            {
                nhapNV(nv);
                px = timNVMa(Q, nv.maNV);
                if (px != NULL)
                {
                    printf("\n Ma NV da ton tai trong danh sach. Vui long nhap lai thong tin NV.");
                    printf("\n ------- Nhap lai Nhan Vien %d :", i + 1);
                }
            } while (px != NULL);
        }
        else
        {
            nhapNV(nv);
        }
        p = getNodeNV(nv);
        chenDauNV(Q, p);
    }
}

void inDSNV(ListNV Q)
{
    printf("\n ---------- Danh sach Nhan Vien -----------");
    NodeNV *p;
    int count = 1;
    for (p = Q.Head; p != NULL; p = p->next)
    {
        printf("\n + Nhan Vien %d :", count);
        inNV(p->info);
        count++;
    }
    printf("\n ----------------- Het --------------------");
}

void luuFileNV(FILE *f, ListNV Q, char *nameF)
{
    f = fopen(nameF, "wb");
    int n = 0;
    NodeNV *p;
    n = demSoNV(Q);

    fwrite(&n, sizeof(int), 1, f);

    for (p = Q.Head; p != NULL; p = p->next)
    {
        fwrite(&p->info, sizeof(NV), 1, f);
    }
    fclose(f);
}

void docFileNV(FILE *f, ListNV &Q, char *nameF)
{
    NV nv;
    int i, n;
    NodeNV *p;
    f = fopen(nameF, "rb");
    if (f == NULL)
    {
        printf("\n Khong the mo file [%s]", nameF);
        return;
    }
    fread(&n, sizeof(int), 1, f);

    for (i = 0; i < n; i++)
    {
        fread(&nv, sizeof(NV), 1, f);
        p = getNodeNV(nv);
        chenDauNV(Q, p);
    }
    fclose(f);
}