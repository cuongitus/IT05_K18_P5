
#include <iostream>
#include <cstring>

struct HangHoa{
    int mahh;
    char tenhh[20];
    int soluong;
    float dongia, thanhtien;
};

// Nhập thông tin hàng hóa từ bàn phím
void NhapHH(HangHoa &hh){

    printf("\n Nhap Ma Hang Hoa:");
    scanf("%d", &hh.mahh);

    printf("Nhap Ten Hang Hoa:");
    fflush(stdin); gets(hh.tenhh);

    printf("Nhap so luong:");
    scanf("%d", &hh.soluong);

    printf("Nhap don gia:");
    scanf("%f", &hh.dongia);

    hh.thanhtien = hh.soluong * hh.dongia;

}

// In thông tin hàng hóa
void inHH(HangHoa hh){

    std::cout <<  "-----------------" << std::endl;
    std::cout << "Ma HH: " <<  hh.mahh <<  std::endl;
    std::cout << "Ten HH: " <<  hh.tenhh << std::endl;
    std::cout << "So luong HH: " <<  hh.soluong << std::endl;
    std::cout <<  "Don gia: " << hh.dongia << std::endl;
    std::cout <<  "Thanh tien: " <<  hh.thanhtien << std::endl;
    std::cout <<  "-----------------" << std::endl;
}

// Nhập Danh sách thông tin hàng hóa từ bàn phím
void NhapDsHH(HangHoa ds[], int &n){

  std::cout <<  "Nhap so luong hang hoa: " << std::endl;
    scanf("%d", &n);

    std::cout <<  "Thong tin chi tiet Hang hoa " << std::endl;
    for(int i = 0 ; i < n ; i ++){
        NhapHH(ds[i]);
    }

}

// In danh sách thông tin hàng hóa
void InDsHH(HangHoa ds[], int n){

     for(int i = 0 ; i < n ; i ++){
        inHH(ds[i]);
    }

}

int TimHH_Ma(HangHoa ds[], int n , int k){

    int i;

    for(i = 0 ; i < n; i ++){
        if(ds[i].mahh == k){
            return i;
        }
    }
    return -1;
}

int TimHH_Ten(HangHoa ds[], int n , char s[]){

    int i;

    for(i = 0 ; i < n; i ++){
        if(strcmp(ds[i].tenhh, s) == 0){
            return i;
        }
    }
    return -1;
}


int main() {

     HangHoa ds[10];

    ds[0].mahh = 1;
    strcpy(ds[0].tenhh, "Trai Oi");
    ds[0].soluong = 10;
    ds[0].dongia = 5000;
    ds[0].thanhtien = ds[0].soluong * ds[0].dongia

    ds[1].mahh = 2;
    strcpy(ds[1].tenhh, "Trai Man");
    ds[1].soluong = 9;
    ds[1].dongia = 10000;
    ds[1].thanhtien = ds[1].soluong * ds[1].dongia

    ds[2].mahh = 3;
    strcpy(ds[2].tenhh, "Trai Le");
    ds[2].soluong = 6;
    ds[2].dongia = 11000;
    ds[2].thanhtien = ds[2].soluong * ds[2].dongia

    ds[3].mahh = 4;
    strcpy(ds[3].tenhh, "Trai Dua");
    ds[3].soluong = 7;
    ds[3].dongia = 8000;
    ds[3].thanhtien = ds[3].soluong * ds[3].dongia

    ds[4].mahh = 5;
    strcpy(ds[4].tenhh, "Trai Nho");
    ds[4].soluong = 22;
    ds[4].dongia = 88000;
    ds[4].thanhtien = ds[4].soluong * ds[4].dongia

    ds[5].mahh = 6;
    strcpy(ds[5].tenhh, "Trai Dua Luoi");
    ds[5].soluong = 11;
    ds[5].dongia = 18000;
    ds[5].thanhtien = ds[5].soluong * ds[5].dongia

    ds[6].mahh = 7;
    strcpy(ds[6].tenhh, "Trai Dua Luoi");
    ds[6].soluong = 11;
    ds[6].dongia = 18000;

    ds[7].mahh = 8;
    strcpy(ds[7].tenhh, "Trai Dua Gang");
    ds[7].soluong = 22;
    ds[7].dongia = 18000;

    ds[8].mahh = 9;
    strcpy(ds[8].tenhh, "Trai Dua Hau");
    ds[8].soluong = 11;
    ds[8].dongia = 8500;

    ds[9].mahh = 10;
    strcpy(ds[9].tenhh, "Trai Buoi");
    ds[9].soluong = 11;
    ds[9].dongia = 8500;

    InDsHH(ds, 10);
}


