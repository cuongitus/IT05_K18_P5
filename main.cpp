#include <iostream>
#include <cstring>
using namespace std;

#include "Tour.cpp"


int main(){
    
    ListTour Q;
    NodeTour *p;

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
        cout << "======================================================================" << endl;
        cout << "Nhap tuy chon: ";
        cin >> key;

        switch (key){
        case 1:
            cout << "1. Them tour du lich." << endl;
            init(Q);
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

        default:
            cout << "Khong co chuc nang nay trong menu." << endl;
            cout << "Vui long chon chuc nang trong hop menu" << endl;
            break;
        }
    }

    inDsTour(Q);
}