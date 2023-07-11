#include <iostream>
#include <cstring>
using namespace std;

#include "Tour.cpp"


int main(){
    
    ListTour Q;
    NodeTour *p;

    FILE *f;
    char *tenFile = "danhSachTour.bin"; 

    init(Q);

    int key;
    int kq;

    char maTour[4];
    char tenTourMoi[20];
    int giaTourMoi;
    int soLuongHanhKhachMoi;
    

    

    while (true){
        cout << "CHUONG TRINH QUAN LY TOUR DU LICH" << endl;
        cout << "=================================MENU=================================" << endl;
        cout << "==  1. Them Tour du lich                                            ==" << endl;
        cout << "==  2. Sua Tour du lich                                             ==" << endl;
        cout << "==  3. Xoa Tour du lich                                             ==" << endl;
        cout << "==  4. Xem danh sach Tour du lich                                   ==" << endl;
        cout << "==  5. Tim kiem Tour - Ma                                           ==" << endl;
        cout << "==  6. Tim kiem Tour - Ten                                          ==" << endl;
        cout << "==  7. Sap xep Tour - Gia tour tang dang                            ==" << endl;
        cout << "==  8. Sap xep Tour - Gia tour giam dang                            ==" << endl;
        cout << "==  9. Sap xep Tour - So luong hanh khach tang dang                 ==" << endl;
        cout << "==  10. Sap xep Tour - So luong hanh khach giam dang                ==" << endl;
        cout << "==  11. Tour có gia cao nhat                                        ==" << endl;
        cout << "==  12. Tour có gia thap nhat                                       ==" << endl;
        cout << "==  12. Tour có so luong khach cao nhat                             ==" << endl;
        cout << "==  14. Tour có so luong khach thap nhat                            ==" << endl;
        cout << "==  15. Tong so luong Tour hien co                                  ==" << endl;
        cout << "==  16.                                   ==" << endl;
        cout << "==  21. Luu Ds tour ra file csv                                     ==" << endl;
        cout << "======================================================================" << endl;
        cout << "Nhap tuy chon: ";
        cin >> key;

        switch (key){

        case 1:
            cout << "1. Them tour du lich." << endl;
            nhapDSTour(Q);
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
            
            suaNodeTour_ma(Q, maTour, tenTourMoi, giaTourMoi, soLuongHanhKhachMoi);

            break;
        
        case 3:
            cout << "3. Xoa tour du lich" << endl;
            cout << "Nhap ma Tour: ";
            cin >> maTour;

            kq = xoaNodeTour_ma(Q, maTour);

            if(kq == 1){
                cout << "Xoa tour du lich thanh cong" << endl;
            }else if (kq == 0){
                cout << "Khong tim thay tour du lich" << endl;
            }
            break;

        case 4:
            cout << "4. Xem danh sach tour du lịch." << endl;
            inDsTour(Q);
            break;    
        
        case 5:
            cout << "5. Tim kiem Tour - Ma." << endl;
            cout << "Nhap ma Tour: ";
            cin >> maTour;

            p = TimNodeTour_ma(Q, maTour);
            
            if(p != NULL){

                cout << "Ma Tour: " <<  p -> info.maTour <<  endl;
                cout << "Ten Tour: " <<  p -> info.tenTour << endl;
                cout << "Gia Tour: " <<  p -> info.giaTour << endl;
                cout <<  "So luong hanh khach: " << p -> info.soLuongHanhKhach << endl;
            }else{
                cout << "Khong tim thay Tour" << endl;
            }
            break;

        case 7:
            cout << "7. Sap xep Tour - Gia tour tang dang." << endl;

            kq = sapXepTourGiaTang(Q);

            if(kq == 0){
                cout << "Danh sach Tour dang trong." << endl;
            }else{
                cout << "Sap xep thanh cong." << endl;
            }
            break;
        
        case 8:
            cout << "8. Sap xep Tour - Gia tour giam dang." << endl;

            kq = sapXepTourGiaGiam(Q);

            if(kq == 0){
                cout << "Danh sach Tour dang trong." << endl;
            }else{
                cout << "Sap xep thanh cong." << endl;
            }
            break;

        case 9:
            cout << "9. Sap xep Tour - So luong tang dang." << endl;

            kq = sapXepTourSoluongTang(Q);

            if(kq == 0){
                cout << "Danh sach Tour dang trong." << endl;
            }else{
                cout << "Sap xep thanh cong." << endl;
            }
            break;
        
        case 10:
            cout << "10. Sap xep Tour - So luong giam dang." << endl;

            kq = sapXepTourSoluongGiam(Q);

            if(kq == 0){
                cout << "Danh sach Tour dang trong." << endl;
            }else{
                cout << "Sap xep thanh cong." << endl;
            }
            break;
        
        case 11:
            cout << "11. Danh sach Tour co gia cao nhat" << endl;
            tour_soluong_max(Q);
            break;

        case 12:
            cout << "12. Danh sach Tour co gia thap nhat" << endl;
            tour_soluong_max(Q);
            break;
            
        case 13:
            cout << "13. Danh sach Tour co so luong khach cao nhat" << endl;
            tour_soluong_max(Q);
            break;

        case 14:
            cout << "14. Danh sach Tour co so luong khach thap nhat" << endl;
            tour_soluong_max(Q);
            break;

        case 15:
            cout << "15. Tong so luong Tour hien co: " << demTour(Q) << endl;
            break;

        case 21:
            cout << "21. Luu Ds tour ra file csv" << endl;
            luuFileTour(f, Q, tenFile);
            break; 

        case 22:
            cout << "22. Doc Ds tour ra file csv" << endl;
            docFileTour(f, Q, tenFile);
            break;
            

        default:
            cout << "Khong co chuc nang nay trong menu." << endl;
            cout << "Vui long chon chuc nang trong hop menu" << endl;
            break;
        }
    }

    exit(0);
}