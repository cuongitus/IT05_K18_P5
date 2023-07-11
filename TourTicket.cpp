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

// ---------------------
// Khai bao cau truc dang DSLK don de chua danh Khach Hang (KH)
struct KH
{
  int maKH;
  char hoTen[25];
  char dienThoai[11];
  char ngaySinh[10];
  int soTienTour;
};
struct NodeKH
{
  KH info;
  struct NodeKH *next;
};
struct ListKH
{
  NodeKH *Head;
  NodeKH *Tail;
};

// ---------------------
// Khai bao cau truc dang DSLK don de chua danh Phieu Dat Tour (PhieuDT)
struct PhieuDT
{
  int maPhieu;
  int maTour;
  int maNV;
  int soKH;
  KH dsKH[30];
  int tongTien;
};
struct NodePhieuDT
{
  PhieuDT info;
  struct NodePhieuDT *next;
};
struct ListPhieuDT
{
  NodePhieuDT *Head;
  NodePhieuDT *Tail;
};

//===================
// Dinh nghia cac thao tac voi Nhan Vien
void nhapNV(NV &nv)
{
  printf("\n  Nhap Ma Nhan Vien: ");
  scanf("%d", &nv.maNV);
  cin.ignore();
  printf("\n  Nhap Ho va Ten: ");
  cin.getline(nv.hoTen, sizeof(nv.hoTen));
  printf("\n  Nhap So dien thoai: ");
  cin.getline(nv.dienThoai, sizeof(nv.dienThoai));
}

void inNV(NV nv)
{
  printf("\n Ma NV     |  Ho va Ten         |  SDT");
  printf("\n %4d", nv.maNV);
  printf("%20s", nv.hoTen);
  printf("%15s", nv.dienThoai);
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
    nhapNV(nv);
    p = getNodeNV(nv);
    chenDauNV(Q, p);
  }
}

void inDSNV(ListNV Q)
{
  printf("\n ---------- Danh sach Nhan Vien -----------");
  NodeNV *p;
  int count = 1;
  for (p = Q.Head; p != NULL; p=p->next)
  {
    printf("\n + Nhan Vien %d :", count);
    inNV(p->info);
    count++;
  }
  printf("\n ----------------- Het --------------------");
}

NodeNV *timNVMa(ListNV Q, int k)
{
  NodeNV *p;
  for (p = Q.Head; p != NULL; p=p->next)
  {
    if (p->info.maNV == k) break;
  }
  return p;
}

NodeNV *timNVTen(ListNV Q, char s[])
{
  NodeNV *p;
  for (p = Q.Head; p != NULL; p=p->next)
  {
    if (strcmp(p->info.hoTen, s) == 0) break;
  }
  return p;
}

void luuFileNV(FILE *f, ListNV Q, char *nameF)
{
  f = fopen(nameF, "wb");
  int n = 0;
  NodeNV *p;
  for (p = Q.Head; p != NULL; p=p->next)
  {
    n = n + 1;
  }

  fwrite(&n, sizeof(int), 1, f);

  for (p = Q.Head; p != NULL; p=p->next)
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

  fread(&n, sizeof(int), 1, f);

  for (i = 0; i < n; i++)
  {
    fread(&nv, sizeof(NV), 1, f);
    p = getNodeNV(nv);
    chenDauNV(Q, p);
  }
  fclose(f);
}
//===================

//===================
// Dinh nghia cac thao tac voi Khach Hang
void nhapKH(KH &kh)
{
  printf("\n  Nhap Ma Khach Hang: ");
  scanf("%d", &kh.maKH);
  cin.ignore();
  printf("\n  Nhap Ho va Ten: ");
  cin.getline(kh.hoTen, sizeof(kh.hoTen));
  printf("\n  Nhap Ngay sinh (yyyy/MM/dd): ");
  cin.getline(kh.ngaySinh, sizeof(kh.ngaySinh));
  printf("\n  Nhap So dien thoai: ");
  cin.getline(kh.dienThoai, sizeof(kh.dienThoai));
}

void inKH(KH kh)
{
  printf("\n Ma KH     |  Ho va Ten         |  Ngay sinh    |  SDT");
  printf("\n %4d", kh.maKH);
  printf("%20s", kh.hoTen);
  printf("%15s", kh.ngaySinh);
  printf("%15s", kh.dienThoai);
}
//===================

//===================
// Dinh nghia cac thao tac voi Phieu Dat Tour

//===================

int main()
{
  FILE *f;

  // Khai bao danh sach
  ListNV QNV;
  NodePhieuDT QPDT;

  initDSNV(QNV);

  int chon;
  do
  {
    cout << endl << "QUAN LY DAT TOUR DU LICH" << endl;
    cout << "  1. Nhap danh sach Nhan Vien" << endl;
    cout << "  2. Nhap danh sach Nhan Vien tu File" << endl;
    cout << "  3. In danh sach Nhan Vien" << endl;
    cout << "  4. Luu danh sach Nhan Vien vao File" << endl;
    cout << "  0. Thoat" << endl;
    cout << "Moi ban chon: ";
    cin >> chon;
    switch (chon)
    {
    case 1:
      nhapDSNV(QNV);
      break;

    case 2:
      char input[25];
      cin.ignore();
      printf("Nhap ten file doc DS NV: ");
      cin.getline(input, sizeof(input));
      docFileNV(f, QNV, input);
      break;

    case 3:
      inDSNV(QNV);
    break;

    case 4:
      char output[25];
      cin.ignore();
      printf("Nhap ten file luu DS NV: ");
      cin.getline(output, sizeof(output));
      luuFileNV(f, QNV, output);
      break;

    case 0:
      exit(0);
    }

  } while (chon != 0);
}