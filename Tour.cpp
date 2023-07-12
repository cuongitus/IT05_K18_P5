#include <iostream>
#include <cstring>
using namespace std;

// Khai bao danh sach lien ket don chua danh sach Tour
struct Tour{
    char maTour[4];
    char tenTour[20];
    int giaTour;
    int soLuongHanhKhach;
};

struct NodeTour{
    Tour info;
    struct NodeTour *next;
};

struct ListTour{
    NodeTour *Head;
    NodeTour *Tail;
};

// Khoi tao List
void init (ListTour &Q){
    
        Q.Head = NULL;
        Q.Tail = NULL;
    
}

NodeTour* getNodeTour(Tour tour){
    NodeTour *p;
    p = new NodeTour();

    if(p == NULL){
        cout << "Chua co tour nao duoc khai bao" <<  endl;
        exit(0);
    }

    p -> info = tour;
    p -> next = NULL;

    return p;
}

// Xu ly nhap/in Tour
void nhapTour(Tour &tour){

    cout << "Ma Tour :";
    fflush(stdin); gets(tour.maTour);

    cout << "Ten Tour :";
    fflush(stdin); gets(tour.tenTour);  

    cout << "So luong hanh khach :";
    scanf("%d", &tour.soLuongHanhKhach);

    cout << "Gia Tour :";
    scanf("%d", &tour.giaTour);  

}

void inTour(Tour tour){

    cout << "Ma Tour: " <<  tour.maTour <<  endl;
    cout << "Ten Tour: " <<  tour.tenTour << endl;
    cout << "Gia Tour: " <<  tour.giaTour << endl;
    cout <<  "So luong hanh khach: " << tour.soLuongHanhKhach << endl;

}

// Xu ly chen Tour
void ChenDauTour(ListTour &Q, NodeTour *p){

    if(Q.Head == NULL){
        Q.Head = p;
        Q.Tail = p;
    }else{
        p -> next = Q.Head;
        Q.Head = p;
    }

}

void ChenCuoiTour(ListTour &Q, NodeTour *p){

    if(Q.Head == NULL){
        Q.Head = p;
        Q.Tail = Q.Head;
    }else{
        Q.Tail -> next = p;
        Q.Tail = p;
    }
}


void xoaDauTour(ListTour &Q){

    NodeTour *p;

    if(Q.Head != NULL){
        p = Q.Head;
        Q.Head = Q.Head ->next;
        free(p);
        if(Q.Head == NULL){
            Q.Tail = NULL;
        }
    }

}

int xoaNodeTour_ma(ListTour &Q, char s[]){
    
    NodeTour *p = Q.Head, *q = NULL; 

    while (p != NULL){
        if(strcasecmp(p -> info.maTour, s) == 0){
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

// Dem Tour
int demTour(ListTour Q){

    NodeTour *p;
    int count = 0;

    for (p  = Q.Head; p!= NULL; p = p -> next){
        count ++;
    }
    return count;
}

// Tim kiem Tour
NodeTour *TimNodeTour_ma(ListTour Q, char s[]){  

    NodeTour *p;

    for (p  = Q.Head; p!= NULL; p = p -> next){
        if(strcasecmp(p -> info.maTour, s) == 0){
            break;
        }
    }
    
    return p;
}

NodeTour *TimNodeTour_ten(ListTour Q, char s[]){  

    NodeTour *p;

    for (p  = Q.Head; p!= NULL; p = p -> next){
        if(strcasecmp(p -> info.tenTour, s) == 0){
            break;
        }
    }
    
    return p;
}

NodeTour *TimNodeTour_soluong(ListTour Q, int k){  

    NodeTour *p;

    for (p  = Q.Head; p!= NULL; p = p -> next){
        if(p -> info.soLuongHanhKhach == 0){
            break;
        }
    }
    
    return p;
}

NodeTour *TimNodeTour_gia(ListTour Q, int k){  

    NodeTour *p;

    for (p  = Q.Head; p!= NULL; p = p -> next){
        if(p -> info.giaTour == 0){
            break;
        }
    }
    
    return p;
}

void suaNodeTour_ma(ListTour &Q, char maTour[], char tenTourMoi[], int giaTourMoi, int soLuongMoi){

    NodeTour *p; 

    p = TimNodeTour_ma(Q,maTour);

    if( p != NULL){
        strcpy(p->info.tenTour, tenTourMoi);
        p -> info.giaTour = giaTourMoi;
        p -> info.soLuongHanhKhach = soLuongMoi;
    }else{
        cout << "Khong co tour ban chon:" <<  endl;
    }   
}


void nhapDSTour(ListTour &Q){

    int n,i;
    NodeTour *p;
    Tour tour;

    cout << "Nhap so tour: ";
    scanf("%d", &n);

    for(i = 0; i < n; i ++){

        nhapTour(tour);
        p = getNodeTour(tour);

        if(TimNodeTour_ma(Q, p->info.maTour) == NULL){
            ChenCuoiTour(Q,p);
        }else{
            cout << "Da ton tai Ma Tour nay trong danh sach" << endl;
        }        
    }
}

void inDsTour(ListTour Q){
    
    NodeTour *p;
    int count  = 1;

    cout << "---------- Danh sách Tour ----------" << endl;

    for(p  = Q.Head; p!= NULL ; p = p -> next){

        cout << "---------- Tour:" << count << "----------" << endl;
        inTour(p ->info);

        count ++;
    }
}

// Xu ly sap xep
int sapXepTourGiaTang(ListTour &Q){
    
    NodeTour *p;
    NodeTour *q;

    Tour tour;

    if(Q.Head == NULL){
        return 0;
    }

    for(p = Q.Head ; p != NULL ; p = p -> next){
        for(q = p->next ; q != NULL ; q = q -> next){
            if(p->info.giaTour > q -> info.giaTour){
                tour = p -> info;
                p -> info = q -> info;
                q -> info = tour;
            }
        }
    }
    
    return 1;

}

int sapXepTourGiaGiam(ListTour &Q){
    
    NodeTour *p;
    NodeTour *q;

    Tour tour;

    if(Q.Head == NULL){
        return 0;
    }

    for(p = Q.Head ; p != NULL ; p = p -> next){
        for(q = p->next ; q != NULL ; q = q -> next){
            if(p->info.giaTour < q -> info.giaTour){
                tour = p -> info;
                p -> info = q -> info;
                q -> info = tour;
            }
        }
    }
    
    return 1;

}


int sapXepTourSoluongTang(ListTour &Q){
    
    NodeTour *p;
    NodeTour *q;

    Tour tour;

    if(Q.Head == NULL){
        return 0;
    }

    for(p = Q.Head ; p != NULL ; p = p -> next){
        for(q = p->next ; q != NULL ; q = q -> next){
            if(p->info.soLuongHanhKhach > q -> info.soLuongHanhKhach){
                tour = p -> info;
                p -> info = q -> info;
                q -> info = tour;
            }
        }
    }
    
    return 1;

}

int sapXepTourSoluongGiam(ListTour &Q){
    
    NodeTour *p;
    NodeTour *q;

    Tour tour;

    if(Q.Head == NULL){
        return 0;
    }

    for(p = Q.Head ; p != NULL ; p = p -> next){
        for(q = p->next ; q != NULL ; q = q -> next){
            if(p->info.soLuongHanhKhach < q -> info.soLuongHanhKhach){
                tour = p -> info;
                p -> info = q -> info;
                q -> info = tour;
            }
        }
    }
    
    return 1;

}

// Cac yeu cau tim phan tu lon nhat, nho nhat

void tour_soluong_max(ListTour Q){

    NodeTour *p;
    int max = p->info.soLuongHanhKhach;

    for(p = Q.Head ; p != NULL ; p = p ->next){
        if(p->info.soLuongHanhKhach > max){
            max = p -> info.soLuongHanhKhach;
        }
    }

    for (p = Q.Head ; p != NULL ; p = p ->next){
        if(p->info.soLuongHanhKhach == max){
            inTour(p ->info);
        }
    }
}

void tour_soluong_min(ListTour Q){
    
    NodeTour *p;
    int min = p->info.soLuongHanhKhach;

    for(p = Q.Head ; p != NULL ; p = p ->next){
        if(p->info.soLuongHanhKhach < min){
            min = p -> info.soLuongHanhKhach;
        }
    }

    for (p = Q.Head ; p != NULL ; p = p ->next){
        if(p->info.soLuongHanhKhach == min){
            inTour(p ->info);
        }
    }
}

void tour_gia_max(ListTour Q){
    
    NodeTour *p;
    int max = p->info.giaTour;

    for(p = Q.Head ; p != NULL ; p = p ->next){
        if(p->info.giaTour > max){
            max = p -> info.giaTour;
        }
    }

    for (p = Q.Head ; p != NULL ; p = p ->next){
        if(p->info.giaTour == max){
            inTour(p ->info);
        }
    }
}

void tour_gia_min(ListTour Q){
    
    NodeTour *p;
    int min = p->info.giaTour;

    for(p = Q.Head ; p != NULL ; p = p ->next){
        if(p->info.giaTour < min){
            min = p -> info.giaTour;
        }
    }

    for (p = Q.Head ; p != NULL ; p = p ->next){
        if(p->info.giaTour == min){
            inTour(p ->info);
        }
    }
}

// Xu ly luu/doc file

void luuFileTour(FILE *f, ListTour Q, const char *tenFile){

    f = fopen(tenFile, "wb");
    int n = 0;
    NodeTour *p;

    for(p = Q.Head ; p != NULL ; p = p -> next){
        n ++;
    }

    fwrite(&n, sizeof(int), 1, f);

    for(p = Q.Head ; p != NULL ; p = p -> next){
        fwrite(&p -> info , sizeof(Tour), 1, f);
    }

    fclose(f);
}

void docFileTour(FILE *f, ListTour Q, const char *tenFile){

    Tour x;
    int i,n;

    NodeTour *p;

    f = fopen(tenFile,"rb");

    if (f == NULL) {
        cout << "Khong the mo file " << tenFile << " de doc." << endl;
        return;
    }

    fread(&n, sizeof(int), 1, f);

    for(i = 0; i < n ; i++){
        fread(&x, sizeof(Tour), 1, f);
        p = getNodeTour(x);
        ChenDauTour(Q,p);  
    }
    fclose(f);

    inDsTour(Q);
}
