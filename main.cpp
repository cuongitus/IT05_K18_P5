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

NodePhieuDT *timPhieuDTMaTour(ListPhieuDT Q, char k[])
{
    NodePhieuDT *p;
    for (p = Q.Head; p != NULL; p = p->next)
    {
        if (strcmp(p->info.maTour, k) == 0)
            break;
    }
    return p;
}

int demSoPhieuDT(ListPhieuDT Q)
{
    int count = 0;
    NodePhieuDT *p;
    if ((Q.Head == NULL) && (Q.Tail == NULL))
        return count;

    for (p = Q.Head; p != NULL; p = p->next)
    {
        count = count + 1;
    }
    return count;
}

void suaTienDatCocPhieuDTTheoMa(ListPhieuDT &Q, int maPhieu,int tienDatCoc)
{

    NodePhieuDT *p;

    p = timPhieuDTMa(Q, maPhieu);

    if (p != NULL)
    {
        if (tienDatCoc > p->info.tienDatCoc)
        {
            printf("\n So tien khong dung. Vui long thu lai.");
            return;
        }
        p->info.tienDatCoc = tienDatCoc;
        printf("\n Sua thong tin thanh cong.");
    }
    else
    {
        printf("\n Khong co Phieu Dat Tour tuong ung de sua.");
    }
}

int xoaPhieuDTTheoMa(ListPhieuDT &Q, int k)
{

    NodePhieuDT *p = Q.Head, *q = NULL;

    while (p != NULL)
    {
        if (p->info.maNV == k)
        {
            break;
        }

        q = p;
        p = p->next;
    }

    if (p == NULL)
    {
        return 0;
    }

    if (q != NULL)
    {
        if (p == Q.Tail)
        {
            Q.Tail = q;
            q->next = p->next;
            free(p);
        }
    }
    else
    {
        Q.Head = p->next;
        if (Q.Head == NULL)
        {
            Q.Tail = NULL;
        }
    }

    return 1;
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
       char *tenFile = "danhSachTour.bin";  int minKH = t->info.soLuongHanhKhach >= 30 ? 30 : t->info.soLuongHanhKhach;
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

void inDSPhieuDT(ListPhieuDT Q, ListNV QNV, ListTour QT)
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

void luuFilePhieuDT(FILE *f, ListPhieuDT Q, char *nameF)
{
    f = fopen(nameF, "wb");
    int n = 0;
    NodePhieuDT *p;
    n = demSoPhieuDT(Q);

    fwrite(&n, sizeof(int), 1, f);

    for (p = Q.Head; p != NULL; p = p->next)
    {
        fwrite(&p->info, sizeof(PhieuDT), 1, f);
    }
    fclose(f);
}

void docFilePhieuDT(FILE *f, ListPhieuDT &Q, char *nameF)
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

void chucNangNhanVien(FILE *f, ListNV &QNV)
{
    int chon;
    do
    {
        cout << "\n CHUC NANG QUAN LY NHAN VIEN" << endl;
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
            fflush(stdin);
            gets(input);
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
            fflush(stdin);
            gets(output);
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
            fflush(stdin);
            gets(stenNV);
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
            chon = 0;
            break;

        default:
            cout << "Khong co chuc nang nay trong menu." << endl;
            cout << "Vui long chon chuc nang trong hop menu" << endl;
            break;
        }

    } while (chon != 0);
}

void chucNangTour(FILE *f, ListTour &QT)
{
    int key;
    int kq;

    NodeTour *pT;
    char maTour[4];
    char tenTourMoi[20];
    int giaTourMoi;
    int soLuongHanhKhachMoi;
    char *tenFile = "danhSachTour.bin"; 

    int chon;
    do
    {
        cout << "\n CHUC NANG QUAN LY TOUR" << endl;
        cout << "=================================MENU=================================" << endl;
        cout << "==  1. Them Tour du lich                                            ==" << endl;
        cout << "==  2. Sua Tour du lich                                             ==" << endl;
        cout << "==  3. Xoa Tour du lich                                             ==" << endl;
        cout << "==  4. Xem danh sach Tour du lich                                   ==" << endl;
        cout << "==  5. Tim kiem Tour - Ma                                           ==" << endl;
        // cout << "==  6. Tim kiem Tour - Ten                                          ==" << endl;
        cout << "==  6. Sap xep Tour - Gia tour tang dan                             ==" << endl;
        cout << "==  7. Sap xep Tour - Gia tour giam dan                             ==" << endl;
        cout << "==  8. Sap xep Tour - So luong hanh khach tang dan                  ==" << endl;
        cout << "==  9. Sap xep Tour - So luong hanh khach giam dan                  ==" << endl;
        cout << "==  10. Tour có gia cao nhat                                        ==" << endl;
        cout << "==  11. Tour có gia thap nhat                                       ==" << endl;
        cout << "==  12. Tour có so luong khach cao nhat                             ==" << endl;
        cout << "==  13. Tour có so luong khach thap nhat                            ==" << endl;
        cout << "==  14. Tong so luong Tour hien co                                  ==" << endl;
        cout << "==  15. Luu Ds tour ra file csv                                     ==" << endl;
        cout << "==  16. Doc Ds tour ra file csv                                     ==" << endl;
        cout << "==  0. Thoat                                                        ==" << endl;
        cout << "======================================================================" << endl;
        cout << "Nhap tuy chon: ";
        cin >> chon;
        switch (chon)
        {
        case 1:
            cout << "1. Them tour du lich." << endl;
            nhapDSTour(QT);
            break;

        case 2:
            cout << "2. Sua tour du lich." << endl;
            cout << "Nhap ma Tour: ";
            cin >> maTour;

            cout << "Nhap ten Tour moi: ";
            cin >> tenTourMoi;

            cout << "Nhap gia Tour moi: ";
            cin >> giaTourMoi;

            cout << "Nhap so luong Tour moi: ";
            cin >> soLuongHanhKhachMoi;
            
            suaNodeTour_ma(QT, maTour, tenTourMoi, giaTourMoi, soLuongHanhKhachMoi);

            break;
        
        case 3:
            cout << "3. Xoa tour du lich" << endl;
            cout << "Nhap ma Tour: ";
            cin >> maTour;

            kq = xoaNodeTour_ma(QT, maTour);

            if(kq == 1){
                cout << "Xoa tour du lich thanh cong" << endl;
            }else if (kq == 0){
                cout << "Khong tim thay tour du lich" << endl;
            }
            break;

        case 4:
            cout << "4. Xem danh sach tour du lịch." << endl;
            inDsTour(QT);
            break;    
        
        case 5:
            cout << "5. Tim kiem Tour - Ma." << endl;
            cout << "Nhap ma Tour: ";
            cin >> maTour;

            pT = TimNodeTour_ma(QT, maTour);
            
            if(pT != NULL){

                cout << "Ma Tour: " <<  pT -> info.maTour <<  endl;
                cout << "Ten Tour: " <<  pT -> info.tenTour << endl;
                cout << "Gia Tour: " <<  pT -> info.giaTour << endl;
                cout <<  "So luong hanh khach: " << pT -> info.soLuongHanhKhach << endl;
            }else{
                cout << "Khong tim thay Tour" << endl;
            }
            break;

        case 6:
            cout << "6. Sap xep Tour - Gia tour tang dan." << endl;

            kq = sapXepTourGiaTang(QT);

            if(kq == 0){
                cout << "Danh sach Tour dang trong." << endl;
            }else{
                cout << "Sap xep thanh cong." << endl;
            }
            break;
        
        case 7:
            cout << "7. Sap xep Tour - Gia tour giam dan." << endl;

            kq = sapXepTourGiaGiam(QT);

            if(kq == 0){
                cout << "Danh sach Tour dang trong." << endl;
            }else{
                cout << "Sap xep thanh cong." << endl;
            }
            break;

        case 8:
            cout << "8. Sap xep Tour - So luong khach tang dan." << endl;

            kq = sapXepTourSoluongTang(QT);

            if(kq == 0){
                cout << "Danh sach Tour dang trong." << endl;
            }else{
                cout << "Sap xep thanh cong." << endl;
            }
            break;
        
        case 9:
            cout << "9. Sap xep Tour - So luong khach giam dan." << endl;

            kq = sapXepTourSoluongGiam(QT);

            if(kq == 0){
                cout << "Danh sach Tour dang trong." << endl;
            }else{
                cout << "Sap xep thanh cong." << endl;
            }
            break;
        
        case 10:
            cout << "10. Danh sach Tour co gia cao nhat" << endl;
            tour_soluong_max(QT);
            break;

        case 11:
            cout << "11. Danh sach Tour co gia thap nhat" << endl;
            tour_soluong_max(QT);
            break;
            
        case 12:
            cout << "12. Danh sach Tour co so luong khach cao nhat" << endl;
            tour_soluong_max(QT);
            break;

        case 13:
            cout << "13. Danh sach Tour co so luong khach thap nhat" << endl;
            tour_soluong_max(QT);
            break;

        case 14:
            cout << "14. Tong so luong Tour hien co: " << demTour(QT) << endl;
            break;

        case 15:
            cout << "15. Luu Ds tour ra file csv" << endl;
            luuFileTour(f, QT, tenFile);
            break; 

        case 16:
            cout << "16. Doc Ds tour ra file csv" << endl;
            docFileTour(f, QT, tenFile);
            break;

        case 0:
            chon = 0;
            break;

        default:
            cout << "Khong co chuc nang nay trong menu." << endl;
            cout << "Vui long chon chuc nang trong hop menu" << endl;
            break;
        }

    } while (chon != 0);
}

void chucNangPhieuDatTour(FILE *f, ListPhieuDT &QPDT, ListNV QNV, ListTour QT)
{
    int chon;
    do
    {
        cout << "\n CHUC NANG QUAN LY PHIEU DAT TOUR" << endl;
        cout << "=================================MENU=================================" << endl;
        cout << "==  1. Them 1 Phieu dat tour                                        ==" << endl;
        cout << "==  2. Sua so tien dat co cua phieu dat theo Ma phieu               ==" << endl;
        cout << "==  3. Xoa phieu dat tour theo Ma Phieu                             ==" << endl;
        cout << "==  4. Nhap danh sach phieu dat tour                                ==" << endl;
        cout << "==  5. Nhap danh sach phieu dat tour tu File                        ==" << endl;
        cout << "==  6. Xem danh sach phieu dat tour                                 ==" << endl;
        cout << "==  7. Luu danh sach phieu dat tour vao File                        ==" << endl;
        cout << "==  8. Tim kiem phieu dat tour - Ma                                 ==" << endl;
        cout << "==  9. Tim kiem phieu dat tour - Ma NV                              ==" << endl;
        cout << "==  10. Tim kiem phieu dat tour - Ma tour                            ==" << endl;
        cout << "==  11. Tong so luong phieu dat tour hien co                        ==" << endl;
        cout << "==  0. Thoat                                                        ==" << endl;
        cout << "======================================================================" << endl;
        cout << "Nhap tuy chon: ";
        cin >> chon;
        switch (chon)
        {
        case 1:
            cout << "\n 1. Them 1 Phieu dat tour" << endl;
            NodePhieuDT *pinv;
            PhieuDT inv;
            printf("\n ------- Nhap 1 Phieu dat tour :");
            if (demSoPhieuDT(QPDT) > 0)
            {
                NodePhieuDT *pfnv;
                do
                {
                    nhapPhieuDT(QPDT, inv, QNV, QT);
                    pfnv = timPhieuDTMa(QPDT, inv.maPhieu);
                    if (pfnv != NULL)
                    {
                        printf("\n Ma phieu da ton tai trong danh sach. Vui long nhap lai thong tin PDT.");
                        printf("\n ------- Nhap lai phieu dat tour");
                    }
                } while (pfnv != NULL);
            }
            else
            {
                nhapPhieuDT(QPDT, inv, QNV, QT);
            }

            pinv = getNodePhieuDT(inv);
            chenDauPhieuDT(QPDT, pinv);
            printf("\n ------- Nhap Phieu thanh cong");
            break;

        case 2:
            cout << "\n 2. Sua so tien dat co cua phieu dat theo Ma phieu" << endl;
            printf("\n ------- Nhap thong tin Nhan Vien de sua:");
            int maP, soTien;
            printf("\n ------- Nhap ma phieu muon sua:");
            scanf("%d", &maP);
            printf("\n ------- Nhap so tien co moi:");
            scanf("%d", &soTien);
            if (soTien <= 0)
            {
                printf("\n So tien khong dung. Vui long thu lai.");
            }
            else
            {
                suaTienDatCocPhieuDTTheoMa(QPDT, maP, soTien);
            }
            break;

        case 3:
            cout << "\n 3. Xoa phieu dat tour theo Ma Phieu" << endl;
            int dmaNV;
            printf("\n ------- Nhap ma Phieu muon xoa: ");
            scanf("%d", &dmaNV);
            if (xoaPhieuDTTheoMa(QPDT, dmaNV) == 1)
            {
                printf("\n Xoa Phieu co ma %d thanh cong.", dmaNV);
            }
            else
            {
                printf("\n Xoa Phieu co ma %d that bai. Vui long nhap thong tin ma Phieu muon xoa trong danh sach hien tại", dmaNV);
            }
            break;

        case 4:
            cout << "\n 4. Nhap danh sach phieu dat tour " << endl;
            nhapDSPhieuDT(QPDT, QNV, QT);
            break;

        case 5:
            cout << "\n 5. Nhap danh sach phieu dat tour tu File" << endl;
            char input[25];
            printf("Nhap ten file de doc DS Phieu: ");
            fflush(stdin);
            gets(input);
            docFilePhieuDT(f, QPDT, input);
            break;

        case 6:
            cout << "\n 6. Xem danh sach phieu dat tour" << endl;
            inDSPhieuDT(QPDT, QNV, QT);
            break;

        case 7:
            cout << "\n 7. Luu danh sach phieu dat tour vao File" << endl;
            char output[25];
            printf("Nhap ten file de luu DS Phieu: ");
            fflush(stdin);
            gets(output);
            luuFilePhieuDT(f, QPDT, output);
            break;

        case 8:
            cout << "\n 8. Tim kiem phieu dat tour - Ma" << endl;
            int smaPDT;
            NodePhieuDT *psnvdt;
            printf("\n ------- Nhap ma Phieu muon tim: ");
            scanf("%d", &smaPDT);
            psnvdt = timPhieuDTMa(QPDT, smaPDT);
            if (psnvdt == NULL)
            {
                printf("\n Khong tim thay Phieu tuong ung voi ma: %d", smaPDT);
            }
            else
            {
                printf("\n Thong tin Phieu tuong ung voi ma: %d", smaPDT);
                inPhieuDT(psnvdt->info, QNV, QT);
                printf("\n ----------------------------------------");
            }
            break;

        case 9:
            cout << "\n 9. Tim kiem phieu dat tour - Ma NV" << endl;
            int smaNV;
            NodePhieuDT *psnv;
            printf("\n ------- Nhap ma NV muon tim: ");
            scanf("%d", &smaNV);
            psnv = timPhieuDTMaNV(QPDT, smaNV);
            if (psnv == NULL)
            {
                printf("\n Khong tim thay Phieu tuong ung voi ma NV: %d", smaNV);
            }
            else
            {
                printf("\n Thong tin Phieu tuong ung voi ma NV: %d", smaNV);
                inPhieuDT(psnv->info, QNV, QT);
                printf("\n ----------------------------------------");
            }
            break;

        case 10:
            cout << "\n 9. Tim kiem phieu dat tour - Ma tour" << endl;
            char smaT[4];
            NodePhieuDT *psnvt;
            printf("\n ------- Nhap ma Tour muon tim: ");
            scanf("%s", &smaT);
            psnvt = timPhieuDTMaTour(QPDT, smaT);
            if (psnvt == NULL)
            {
                printf("\n Khong tim thay Phieu tuong ung voi ma tour: %s", smaT);
            }
            else
            {
                printf("\n Thong tin Phieu tuong ung voi ma tour: %s", smaT);
                inPhieuDT(psnvt->info, QNV, QT);
                printf("\n ----------------------------------------");
            }
            break;
    
        case 11:
            cout << "\n 10. Tong so luong phieu dat tour hien co" << endl;
            printf("\n Tong so luong phieu dat tour hien co la: %d", demSoPhieuDT(QPDT));
            break;

        case 0:
            chon = 0;
            break;

        default:
            cout << "Khong co chuc nang nay trong menu." << endl;
            cout << "Vui long chon chuc nang trong hop menu" << endl;
            break;
        }

    } while (chon != 0);
}

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
        cout << "==  1. Chuc nang quan ly Nhan Vien                                  ==" << endl;
        cout << "==  2. Chuc nang quan ly Tour                                       ==" << endl;
        cout << "==  3. Chuc nang quan ly Phieu Dat Tour                             ==" << endl;
        cout << "==  0. Thoat chuong trinh                                           ==" << endl;
        cout << "======================================================================" << endl;
        cout << "Nhap tuy chon: ";
        cin >> chon;
        switch (chon)
        {
        case 1:
            cout << "\n Dang chọn: Chuc nang quan ly Nhan Vien" << endl;
            chucNangNhanVien(f, QNV);
            break;

        case 2:
            cout << "\n Dang chọn: Chuc nang quan ly Tour" << endl;
            chucNangTour(f, QT);
            break;

        case 3:
            cout << "\n Dang chọn: Chuc nang quan ly Phieu Dat Tour" << endl;
            chucNangPhieuDatTour(f, QPDT, QNV, QT);
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