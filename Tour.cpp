#include <iostream>
#include <cstring>


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

void nhapTour(Tour &tour){

    std::cout << "Ma Tour :";
    fflush(stdin); gets(tour.maTour);

    std::cout << "Ten Tour :";
    fflush(stdin); gets(tour.tenTour);  

    std::cout << "So luong hanh khach :";
    scanf("%d", &tour.giaTour);  

    std::cout << "Gia Tour :";
    scanf("%d", &tour.soLuongHanhKhach);  

}

void inTour(Tour tour){

    std::cout << "Ma Tour: " <<  tour.maTour <<  std::endl;
    std::cout << "Ten Tour: " <<  tour.tenTour << std::endl;
    std::cout << "Gia Tour: " <<  tour.giaTour << std::endl;
    std::cout <<  "So luong hanh khach: " << tour.soLuongHanhKhach << std::endl;

}

void init (ListTour &Q){
    
        Q.Head = NULL;
        Q.Tail = NULL;
    
}

NodeTour* getNodeTour(Tour tour){
    NodeTour *p;
    p = new NodeTour();

    if(p == NULL){
        std::cout << "Chua co tour nao duoc khai bao" <<  std::endl;
        exit(0);
    }

    p -> info = tour;
    p -> next = NULL;

    return p;
}

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
        std::cout << "Khong co tour ban chon:" <<  std::endl;
    }   
}


void nhapDSTour(ListTour &Q){

    int n,i;
    NodeTour *p;
    Tour tour;

    std::cout << "Nhap so tour: ";
    scanf("%d", &n);

    for(i = 0; i < n; i ++){
        nhapTour(tour);
        p = getNodeTour(tour);
        ChenCuoiTour(Q,p);
    }
}

void inDsTour(ListTour Q){
    
    NodeTour *p;
    int count  = 1;

    std::cout << "---------- Danh sách Tour ----------" << std::endl;

    for(p  = Q.Head; p!= NULL ; p = p -> next){

        std::cout << "---------- Tour:" << count << "----------" << std::endl;
        inTour(p ->info);

        count ++;
    }
}

