#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

#include "User.cpp"
#include "Employee.cpp"
#include "Tour.cpp"

// ---------------------
// Khai bao cau truc dang DSLK don de chua danh Phieu Dat Tour (PhieuDT)
struct PhieuDT
{
    int maPhieu;
    char maTour[4];
    int maNV;
    int ngayDat;
    int thangDat;
    int namDat;
    int soKH;
    KH dsKH[30];
    int tongTien;
    int tienDatCoc;
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
// Dinh nghia cac thao tac voi Phieu Dat Tour
bool checkDate(int day, int month, int year)
{
    if ((month == 1 || month == 3 || month == 5 || month == 7 ||
         month == 8 || month == 10 || month == 12) &&
        (day > 31 || day < 1))
    {
        return false;
    }
    else if ((month == 4 || month == 6 || month == 9 || month == 11) && (day > 30 || day < 1))
    {
        return false;
    }
    else if ((month == 2) && (year % 4 == 0) && (day > 29 || day < 1))
    {
        return false;
    }
    else if ((month == 2) && (year % 4 != 0) && (day > 28 || day < 1))
    {
        return false;
    }
    else if ((year < 999) || (year > 10000))
    {
        return false;
    }
    if ((month < 1) || (month > 12))
    {
        return false;
    }
    return true;
};

void initDSPhieuDT(ListPhieuDT &Q)
{
    Q.Head = NULL;
    Q.Tail = NULL;
}

NodePhieuDT *getNodePhieuDT(PhieuDT pdt)
{
    NodePhieuDT *p;
    p = new NodePhieuDT();
    if (p == NULL)
    {
        printf("\n Khong thanh cong");
        exit(0);
    }

    p->info = pdt;
    p->next = NULL;
    return p;
}

void chenDauPhieuDT(ListPhieuDT &Q, NodePhieuDT *p)
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

NodePhieuDT *timPhieuDTMa(ListPhieuDT Q, int k)
{
    NodePhieuDT *p;
    for (p = Q.Head; p != NULL; p = p->next)
    {
        if (p->info.maPhieu == k)
            break;
    }
    return p;
}

NodePhieuDT *timPhieuDTMaNV(ListPhieuDT Q, int k)
{
    NodePhieuDT *p;
    for (p = Q.Head; p != NULL; p = p->next)
    {
        if (p->info.maNV == k)
            break;
    }
    return p;
}

void nhapPhieuDT(ListPhieuDT Q, PhieuDT &pdt, ListNV QNV, ListTour QT)
{
    NodePhieuDT *px = Q.Head;
    do
    {
        printf("\n  Nhap Ma Phieu: ");
        scanf("%d", &pdt.maPhieu);
        px = timPhieuDTMa(Q, pdt.maPhieu);
        if (px != NULL)
        {
            printf("\n  Ban nhap ma phieu da co trong danh sach. Vui long nhap lai ma phieu khac.");
        }
    } while (px != NULL);

    NodeNV *nv;
    do
    {
        printf("\n  Nhap Ma NV: ");
        scanf("%d", &pdt.maNV);
        nv = timNVMa(QNV, pdt.maNV);
        if (nv == NULL)
        {
            printf("\n  Ban nhap ma NV khong co trong danh sach. Vui long nhap lai ma NV.");
        }
    } while (nv == NULL);

    NodeTour *t;
    do
    {
        cin.ignore();
        printf("\n  Nhap Ma Tour: ");
        cin.getline(pdt.maTour, sizeof(pdt.maTour));
        t = TimNodeTour_ma(QT, pdt.maTour);
        if (t == NULL)
        {
            printf("\n  Ban nhap ma Tour khong co trong danh sach. Vui long nhap lai ma Tour.");
        }
    } while (t == NULL);

    bool isDate = false;
    do
    {
        printf("\n  Nhap ngay dat (chi nhap ngay): ");
        scanf("%d", &pdt.ngayDat);
        printf("\n  Nhap thang dat (chi nhap thang): ");
        scanf("%d", &pdt.thangDat);
        printf("\n  Nhap nam dat (chi nhap nam): ");
        scanf("%d", &pdt.namDat);
        isDate = checkDate(pdt.ngayDat, pdt.thangDat, pdt.namDat);
        if (t == NULL)
        {
            printf("\n  Ban nhap thong tin ngay/thang/nam dat khong dung. Vui long nhap lai ngay/thang/nam dat.");
        }
    } while (isDate == false);

    bool soKHHopLe = false;
    do
    {
        printf("\n  Nhap so khach hang: ");
        scanf("%d", &pdt.soKH);
        int minKH = t->info.soLuongHanhKhach >= 30 ? 30 : t->info.soLuongHanhKhach;
        soKHHopLe = (pdt.soKH > 0) && (pdt.soKH <= minKH);
        if (soKHHopLe == false)
        {
            printf("\n  Ban nhap so khach hang khong hop le. Vui long nhap lai so khach hang lon 0 và nho hon hoac bang %d ).", minKH);
        }
    } while (soKHHopLe == false);

    for (int i = 0; i < pdt.soKH; i++)
    {
        printf("\n ------- Nhap Khach Hang %d :", i + 1);
        nhapKH(pdt.dsKH[i]);
    }

    pdt.tongTien = t->info.giaTour;
    bool soTienHopLe = false;
    do
    {
        printf("\n  Nhap so tien da dat coc: ");
        scanf("%d", &pdt.tienDatCoc);
        soTienHopLe = (pdt.tienDatCoc > 0) && (pdt.tienDatCoc <= pdt.tongTien);
        if (soTienHopLe == false)
        {
            printf("\n  Ban nhap so tien da dat coc khong dung. Vui long nhap lai so so tien da dat coc lon 0 và nho hon hoac bang %d ).", pdt.tongTien);
        }
    } while (soTienHopLe == false);
}

void inPhieuDT(PhieuDT pdt, ListNV QNV, ListTour QT)
{
    printf("\n Ma Phieu: %4d", pdt.maPhieu);
    NodeNV *pnv;
    pnv = timNVMa(QNV, pdt.maNV);
    if (pnv != NULL)
    {
        printf("\n----------- Thong tin Nhan Vien -----------");
        inNV(pnv->info);
        printf("\n-------------------------------------------");
    }
    else
    {
        printf("\n Khong tim thay thong tin Nhan Vien voi Ma %d", pdt.maNV);
    }

    NodeTour *pt;
    pt = TimNodeTour_ma(QT, pdt.maTour);
    if (pt != NULL)
    {
        printf("\n----------- Thong tin Tour ---------------");
        inTour(pt->info);
        printf("\n-------------------------------------------");
    }
    else
    {
        printf("\n Khong tim thay thong tin Tour voi Ma %s", pdt.maTour);
    }

    printf("\n Tong so Khach Hang: %d", pdt.soKH);
    printf("\n----------- Thong tin Khach Hang ---------");
    for (int i = 0; i < pdt.soKH; i++)
    {
        inKH(pdt.dsKH[i]);
    }
    printf("\n-------------------------------------------");
    printf("\n Ngay dat: %d-%d-%d", pdt.ngayDat, pdt.thangDat, pdt.namDat);
    printf("\n Tong tien: %d", pdt.tongTien);
    printf("\n So tien da dat coc: %d", pdt.tienDatCoc);
}

void nhapDSPhieuDT(ListPhieuDT &Q, ListNV QNV, ListTour QT)
{
    int n, i;
    NodePhieuDT *p;
    PhieuDT pdt;
    printf("\n Nhap so Phieu: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("\n ------- Nhap Phieu %d :", i + 1);
        nhapPhieuDT(Q, pdt, QNV, QT);
        p = getNodePhieuDT(pdt);
        chenDauPhieuDT(Q, p);
    }
}

void inDSPHieuDT(ListPhieuDT Q, ListNV QNV, ListTour QT)
{
    printf("\n ---------- Danh sach Phieu Tour da dat -----------");
    NodePhieuDT *p;
    int count = 1;
    for (p = Q.Head; p != NULL; p = p->next)
    {
        printf("\n + Phieu %d :", count);
        inPhieuDT(p->info, QNV, QT);
        count++;
    }
    printf("\n ----------------- Het --------------------");
}

void luuFileNV(FILE *f, ListPhieuDT Q, char *nameF)
{
    f = fopen(nameF, "wb");
    int n = 0;
    NodePhieuDT *p;
    for (p = Q.Head; p != NULL; p = p->next)
    {
        n = n + 1;
    }

    fwrite(&n, sizeof(int), 1, f);

    for (p = Q.Head; p != NULL; p = p->next)
    {
        fwrite(&p->info, sizeof(PhieuDT), 1, f);
    }
    fclose(f);
}

void docFileNV(FILE *f, ListPhieuDT &Q, char *nameF)
{
    PhieuDT pdt;
    int i, n;
    NodePhieuDT *p;
    f = fopen(nameF, "rb");
    if (f == NULL)
    {
        printf("\n Khong the mo file [%s]", nameF);
        return;
    }

    fread(&n, sizeof(int), 1, f);

    for (i = 0; i < n; i++)
    {
        fread(&pdt, sizeof(PhieuDT), 1, f);
        p = getNodePhieuDT(pdt);
        chenDauPhieuDT(Q, p);
    }
    fclose(f);
}
//===================

int main()
{
    FILE *f;

    // Khai bao danh sach
    ListNV QNV;
    initDSNV(QNV);
    ListTour QT;
    init(QT);
    ListPhieuDT QPDT;
    initDSPhieuDT(QPDT);

    int chon;
    do
    {
        cout << "\n CHUONG TRINH QUAN LY TOUR DU LICH" << endl;
        cout << "=================================MENU=================================" << endl;
        cout << "==  1. Them 1 Nhan Vien                                             ==" << endl;
        cout << "==  2. Sua Nhan Vien theo ma NV                                     ==" << endl;
        cout << "==  3. Xoa Nhan Vien theo ma NV                                     ==" << endl;
        cout << "==  4. Nhap danh sach Nhan Vien                                     ==" << endl;
        cout << "==  5. Nhap danh sach Nhan Vien tu File                             ==" << endl;
        cout << "==  6. Xem danh sach Nhan Vien                                      ==" << endl;
        cout << "==  7. Luu danh sach Nhan Vien vao File                             ==" << endl;
        cout << "==  8. Tim kiem Nhan Vien - Ma                                      ==" << endl;
        cout << "==  9. Tim kiem Nhan Vien - Ten                                     ==" << endl;
        cout << "==  10. Tong so luong Nhan Vien hien co                             ==" << endl;

        cout << "==  10. Them Phieu Dat Tour                                         ==" << endl;
        cout << "==  11. Sua Phieu Dat Tour du lich                                  ==" << endl;
        cout << "==  12. Xoa Phieu Dat Tour du lich                                  ==" << endl;
        cout << "==  13. Nhap danh sach Phieu Dat Tour du lich                       ==" << endl;
        cout << "==  14. Nhap danh sach Phieu Dat Tour du lich tu File               ==" << endl;
        cout << "==  15. Xem danh sach Phieu Dat Tour du lich                        ==" << endl;
        cout << "==  16. Tim kiem Phieu Dat Tour - Ma                                ==" << endl;
        cout << "==  17. Tim kiem Phieu Dat Tour - Ma NV                             ==" << endl;
        cout << "==  18. Tim kiem Phieu Dat Tour - Ma Tour                           ==" << endl;
        cout << "==  19. Sap xep Phieu Dat Tour - Tong tien tang dang                ==" << endl;
        cout << "==  20. Sap xep Phieu Dat Tour - Tong tien giam dang                ==" << endl;
        cout << "==  21. Sap xep Phieu Dat Tour - So luong hanh khach tang dang      ==" << endl;
        cout << "==  22. Sap xep Phieu Dat Tour - So luong hanh khach giam dang      ==" << endl;
        cout << "==  23. Phieu Dat Tour có gia cao nhat                              ==" << endl;
        cout << "==  24. Phieu Dat Tour có gia thap nhat                             ==" << endl;
        cout << "==  25. Tong so luong Phieu Dat Tour hien co                        ==" << endl;
        cout << "==  26. In danh sach Phieu Dat Tour theo ma NV                      ==" << endl;
        cout << "==  27. In danh sach Phieu Dat Tour theo ten NV                     ==" << endl;
        cout << "==  28. In danh sach Phieu Dat Tour theo ma Tour                    ==" << endl;
        cout << "==  39. In danh sach Phieu Dat Tour theo ten Tour                   ==" << endl;
        cout << "==  30. In danh sach Phieu Dat Tour co tong tien lon hon x          ==" << endl;
        cout << "==  31. In danh sach Phieu Dat Tour co tong tien lon hon | bang x   ==" << endl;
        cout << "==  32. In danh sach Phieu Dat Tour co tong tien bang x             ==" << endl;
        cout << "==  33. In danh sach Phieu Dat Tour co tong tien nho hon x          ==" << endl;
        cout << "==  34. In danh sach Phieu Dat Tour co tong tien nho hon | bang x   ==" << endl;
        cout << "==  35. In danh sach Phieu Dat Tour da tra du tien                  ==" << endl;
        cout << "==  36. In danh sach Phieu Dat Tour chua tra du tien                ==" << endl;
        cout << "==  0. Thoat                                                        ==" << endl;
        cout << "======================================================================" << endl;
        cout << "Nhap tuy chon: ";
        cin >> chon;
        switch (chon)
        {
        case 1:
            cout << "\n 1. Them 1 Nhan Vien" << endl;
            NodeNV *pinv;
            NV inv;
            printf("\n ------- Nhap 1 Nhan Vien :");
            if (demSoNV(QNV) > 0)
            {
                NodeNV *pfnv;
                do
                {
                    nhapNV(inv);
                    pfnv = timNVMa(QNV, inv.maNV);
                    if (pfnv != NULL)
                    {
                        printf("\n Ma NV da ton tai trong danh sach. Vui long nhap lai thong tin NV.");
                        printf("\n ------- Nhap lai Nhan Vien");
                    }
                } while (pfnv != NULL);
            }
            else
            {
                nhapNV(inv);
            }

            pinv = getNodeNV(inv);
            chenDauNV(QNV, pinv);
            printf("\n ------- Nhap Nhan Vien thanh cong");
            break;

        case 2:
            cout << "\n 2. Sua Nhan Vien theo ma NV" << endl;
            printf("\n ------- Nhap thong tin Nhan Vien de sua:");
            NV suanv;
            nhapNV(suanv);
            suaNVTheoMa(QNV, suanv);
            break;

        case 3:
            cout << "\n 3. Xoa Nhan Vien theo ma NV" << endl;
            int dmaNV;
            printf("\n ------- Nhap ma NV muon xoa: ");
            scanf("%d", &dmaNV);
            if (xoaNVTheoMa(QNV, dmaNV) == 1)
            {
                printf("\n Xoa Nhan Vien co ma %d thanh cong.", dmaNV);
            }
            else
            {
                printf("\n Xoa Nhan Vien co ma %d that bai. Vui long nhap thong tin ma NV muon xoa trong danh sach hien tại", dmaNV);
            }
            break;

        case 4:
            cout << "\n 4. Nhap danh sach Nhan Vien" << endl;
            nhapDSNV(QNV);
            break;

        case 5:
            cout << "\n 5. Nhap danh sach Nhan Vien tu File" << endl;
            char input[25];
            printf("Nhap ten file de doc DS NV: ");
            fflush(stdin); gets(input);
            docFileNV(f, QNV, input);
            break;

        case 6:
            cout << "\n 6. Xem danh sach Nhan Vien" << endl;
            inDSNV(QNV);
            break;

        case 7:
            cout << "\n 7. Luu danh sach Nhan Vien vao File" << endl;
            char output[25];
            printf("Nhap ten file de luu DS NV: ");
            fflush(stdin); gets(output);
            luuFileNV(f, QNV, output);
            break;

        case 8:
            cout << "\n 8. Tim kiem Nhan Vien - Ma" << endl;
            int smaNV;
            NodeNV *psnv;
            printf("\n ------- Nhap ma NV muon tim: ");
            scanf("%d", &smaNV);
            psnv = timNVMa(QNV, smaNV);
            if (psnv == NULL)
            {
                printf("\n Khong tim thay Nhan Vien tuong ung voi ma: %d", smaNV);
            }
            else
            {
                printf("\n Thong tin Nhan Vien tuong ung voi ma: %d", smaNV);
                inNV(psnv->info);
                printf("\n ----------------------------------------");
            }
            break;

        case 9:
            cout << "\n 8. Tim kiem Nhan Vien - Ten" << endl;
            char stenNV[25];
            NodeNV *pstnv;
            printf("\n ------- Nhap ho va ten NV muon tim: ");
            fflush(stdin); gets(stenNV);
            pstnv = timNVTen(QNV, stenNV);
            if (pstnv == NULL)
            {
                printf("\n Khong tim thay Nhan Vien tuong ung voi ho va ten: %s", stenNV);
            }
            else
            {
                printf("\n Thong tin Nhan Vien tuong ung voi ho va ten: %s", stenNV);
                inNV(pstnv->info);
                printf("\n ----------------------------------------");
            }
            break;

        case 10:
            cout << "\n 10. Tong so luong Nhan Vien hien co" << endl;
            printf("\n Tong so luong Nhan Vien hien co la: %d", demSoNV(QNV));
            break;

        case 0:
            exit(0);

        default:
            cout << "Khong co chuc nang nay trong menu." << endl;
            cout << "Vui long chon chuc nang trong hop menu" << endl;
            break;
        }

    } while (chon != 0);
}