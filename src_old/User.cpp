#include <stdio.h>
#include <iostream>
using namespace std;

// ---------------------
// Khai bao cau truc chua danh Khach Hang (KH)
struct KH
{
    char hoTen[25];
    char dienThoai[11];
};

//===================
// Dinh nghia cac thao tac voi Khach Hang
void nhapKH(KH &kh)
{
    printf("\n  Nhap Ho va Ten: ");
    fflush(stdin); gets(kh.hoTen);
    printf("\n  Nhap So dien thoai: ");
    fflush(stdin); gets(kh.dienThoai);
}

void inKH(KH kh)
{
    printf("Ho va Ten: %20s", kh.hoTen);
    printf("SDT: %15s", kh.dienThoai);
}