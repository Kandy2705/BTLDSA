#include "main.h"

class imp_res : public Restaurant
{
public:
    customer* head;
    customer* tail;
    customer* hangcho;
    customer* ttvaonhaan;
    customer* vaocuoi;
    int sokhachban;
    int  sokhachcho;
    int x;
public:
    imp_res() {
        head = nullptr;
        tail = nullptr;
        hangcho = nullptr;
        ttvaonhaan = nullptr;
        vaocuoi = nullptr;
        sokhachban = 0;
        sokhachcho = 0;
        x = 0;
    };

    int ENERGYX(){
        customer*temp = vitrix(x);
        return temp ->energy;
    }
/////////////////////////////////////////////////////////////////

    void them(int k, string name, int energy){
        customer *cus = new customer (name, energy, nullptr, nullptr);
        if (k == 1){
            if(sokhachban == 0) head = tail = cus;
            else{
                head -> prev = cus;
                cus -> next = head;
                head = cus;
            }
            tail -> next = head;
            head -> prev = tail;
            sokhachban++;
        }
        else if (k > sokhachban){
            tail -> next = cus;
            cus -> prev = tail;
            tail = cus;
            tail -> next = head;
            head -> prev = tail;
            sokhachban++;
        }
        else{
            customer *temp = head;
            for(int i = 1;i < k; i++){
                temp = temp -> next;
            }
            cus -> next = temp;
            temp -> prev -> next = cus;
            cus -> prev = temp -> prev;
            temp -> prev = cus;
            sokhachban++;
        }
    }
/////////////////////////////////////////////////////////////////

    struct Node{
        int data;
        Node*tieptheo;
        Node*phiatruoc;
    };
    struct List{
        Node *dau;
        Node *cuoi;
    };
    void Init(List*& l){
        l -> dau = l -> cuoi = nullptr;
    }
    Node *taonode(int x){
        Node * newnode = new Node;
        newnode -> tieptheo = nullptr;
        newnode -> phiatruoc = nullptr;
        newnode -> data = x;
        return newnode;
    }
    void res(int energy, List *&l){
        l = new List();
        Init(l);
        customer *temp = head;
        if (l -> dau == nullptr){
            Node *newNode = taonode(energy - temp -> energy);
            l -> dau = l -> cuoi = newNode;
            l -> dau -> phiatruoc = l -> cuoi;
            l -> cuoi -> tieptheo = l -> dau;
        }
        for(int i=2; i <= sokhachban;i++){
            temp = temp -> next;
            Node *newNode = taonode(energy - temp -> energy);
            l -> cuoi -> tieptheo = newNode;
            newNode -> phiatruoc = l -> cuoi;
            l -> cuoi = newNode;
            l -> dau -> phiatruoc = l -> cuoi;
            l -> cuoi -> tieptheo = l -> dau;
        }

    }
    /////////////////////////////////////////////////////////////////
    int vitrilonnhat(List *&l){
        Node*temp = l -> dau;
        int giutam;
        int giatriln = abs(temp -> data);
        int vitri = 1;
        int i = 2;
        for (; i <= x; i++){
            temp = temp -> tieptheo;
            giatriln = abs(temp -> data);
            vitri = i ;
        }
        i = i - 1;
        Node*vitridau = temp;
        do {
            temp = temp -> tieptheo;
            if (temp == l -> dau){
                i = 1;
            }
            else i++;
            if (temp->data < 0) {
                giutam = abs(temp->data);
                if (giatriln < giutam) {
                    giatriln = giutam;
                    vitri = i;
                }
            } else{
                if (giatriln < temp->data) {
                    giatriln = temp->data;
                    vitri = i;
                }
            }
        }while (temp != vitridau);
        return vitri;
    }

/////////////////////////////////////////////////////////////////
    void push(string name, int energy){
        customer *cus = new customer (name, energy, nullptr, nullptr);
        customer * temp = hangcho;
        if (hangcho == nullptr){
            hangcho = cus;
            sokhachcho++;
            return;
        }
        while(temp -> next != nullptr){
            temp = temp -> next;
        }
        temp -> next = cus;
        cus -> prev = temp;
        sokhachcho++;
    }
    void pop(){
        if (hangcho == nullptr) return;
        customer * temp = hangcho;
        hangcho = hangcho -> next;
        if (hangcho != nullptr) hangcho -> prev = nullptr;
        delete temp;
        sokhachcho--;
    }
    bool trungten(string n){
        customer*temp = head;
        customer*tempcho = hangcho;
        for (int i = 1; i <= sokhachban;i++){
            if (temp -> name == n){
                return true;
            }
            temp = temp -> next;
        }
        for (int i = 1; i <= sokhachcho;i++){
            if (tempcho -> name == n){
                return true;
            }
            tempcho = tempcho -> next;
        }
        return false;
    }

    void RED(string name, int energy)
    {
        //cout << name << " " << energy << endl;
        //customer *cus = new customer (name, energy, nullptrptr, nullptrptr);
        if (trungten(name)) return;
        else {
            if (energy == 0) return;
            if (sokhachban < (MAXSIZE / 2)) {
                if (sokhachban == 0) {
                    them(1, name, energy);
                    x = 1;
                } else {
                    if (energy >= ENERGYX()) {
                        them(x + 1, name, energy);
                        x = x + 1;
                    } else {
                        them(x, name, energy);
                        x = x;
                    }
                }
                if (ttvaonhaan == nullptr || timkiemcho(name,ttvaonhaan,sokhachcho+sokhachban)== nullptr)
                themcuoi(name,energy);
            }
/////////////////////////////////////////////////////////////////
            else if (sokhachban == MAXSIZE) {
                if (sokhachcho < MAXSIZE) {
                    push(name, energy);
                    if (ttvaonhaan == nullptr || timkiemcho(name,ttvaonhaan,sokhachcho+sokhachban) == nullptr)
                    themcuoi(name,energy);
                } else return;
            }
/////////////////////////////////////////////////////////////////
            else {
                if (sokhachban == 0) {
                    them(1, name, energy);
                    x = 1;
                }
                else {
                    List *l = nullptr;
                    res(energy, l);
                    int vitri = vitrilonnhat(l);
                    Node *temp = l->dau;
                    for (int i = 1; i < vitri; i++) {
                        temp = temp->tieptheo;
                    }
                    if (temp->data >= 0) {
                        int k = vitri + 1;
                        them(k, name, energy);
                        x = k;
                    } else {
                        them(vitri, name, energy);
                        x = vitri;
                    }
                }
                if (ttvaonhaan == nullptr ||timkiemcho(name,ttvaonhaan,sokhachcho+sokhachban)== nullptr)
                themcuoi(name, energy);
            }
        }
/////////////////////////////////////////////////////////////////
    }

    void clear(){
        while (sokhachban != 0){
            if (head == nullptr && tail == nullptr) return;
            customer *temp = head;
            xoakhoicho(timkiemcho(temp -> name, ttvaonhaan, sokhachban + sokhachban), ttvaonhaan, sokhachcho+sokhachban);
            head = head -> next;
            delete temp;
            --sokhachban;
        }
        tail = nullptr;
        head = nullptr;
    }
/////////////////////////////////////////////////////////////////
    void themcuoi(string name, int energy){
        customer * cus = new customer (name, energy, nullptr, nullptr);
        if (ttvaonhaan == nullptr){
            ttvaonhaan = vaocuoi = cus;
            return;
        }
        //customer * temp = ttvaonhaan;
        vaocuoi -> next = cus;
        cus -> prev = vaocuoi;
        vaocuoi = cus;
    }

    void xoa(int index){
        customer *temp = ttvaonhaan;
        if ((ttvaonhaan == nullptr && vaocuoi == nullptr) || index < 1 || index > (sokhachban+sokhachcho)) return;
        if (index == 1){
            ttvaonhaan = ttvaonhaan -> next;
            ttvaonhaan -> prev = nullptr;
            delete temp;
        }
        else if (index == sokhachban + sokhachcho){
            customer *tempcuoi = vaocuoi;
            vaocuoi = vaocuoi -> prev;
            vaocuoi -> next = nullptr;
            delete tempcuoi;
        }
        else{
            for (int i = 1; i < index; i++){
                temp = temp -> next;
            }
            temp -> next -> prev = temp -> prev;
            temp -> prev -> next = temp -> next;
            delete temp;
        }
    }
    /////////////////////////////////////////////////////////////////
    customer*timkiem(string n){
        customer*temp = head;
        int i = 1;
        while ((i != sokhachban) && (temp -> name != n)){
            temp = temp -> next;
            i++;
        }
        return temp;
    }
    customer*timkiemcho(string n, customer*hangcho, int sokhachcho){
        customer*temp = hangcho;
        int i = 1;
        if (i == sokhachcho && temp -> name != n) return nullptr;
        while(temp != nullptr && (i != sokhachcho + 1) && (temp -> name != n)){
            temp = temp -> next;
            i++;
        }
        return temp;
    }
    /////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////
    void BLUE(int num)
    {
        //cout << "blue "<< num << endl;
        if (sokhachban == 0) return;
        if (num >= sokhachban) {
            clear();
            //clearttvao();
            x = 0;
        }
        else{
            for (int i = 1; i <= num; i++){
                customer * temp = ttvaonhaan;
                int k = 1;
                if (hangcho != nullptr){
                    while (timkiemcho(temp -> name, hangcho, sokhachcho) != nullptr){
                        k++;
                        temp = temp -> next;
                    }
                }
                customer *vitri = timkiem(temp->name);
                if (sokhachban == 1){
                    x = 0;
                    xoa(k);
                    customer *hi = head;
                    delete hi;
                    head = tail = nullptr;
                }
                if (vitri == head) {
                    if (temp->energy > 0) {
                        x = 1;
                    } else {
                        x = sokhachban - 1;
                    }
                    xoa(k);
                    if (head == nullptr && tail == nullptr) return;
                    else {
                        customer *dautien = head;
                        head = head->next;
                        delete dautien;
                        tail->next = head;
                        head->prev = tail;
                    }
                    --sokhachban;
                } else if (vitri == tail) {
                    if (head == nullptr && tail == nullptr) return;
                    else {
                        customer *cuoicung = tail;
                        tail = tail->prev;
                        delete cuoicung;
                        tail->next = head;
                        head->prev = tail;
                    }
                    if (temp->energy > 0) {
                        x = 1;
                    } else {
                        x = sokhachban - 1;
                    }
                    --sokhachban;
                    xoa(k);
                } else {
                    customer *dautien = head;
                    for (int j = 1; vitri != dautien; j++) {
                        dautien = dautien->next;
                        x = j + 1;
                    }
                    dautien->next->prev = dautien->prev;
                    dautien->prev->next = dautien->next;
                    delete dautien;
                    --sokhachban;
                    if (temp->energy > 0) {
                        x = x;
                    } else {
                        x = x - 1;
                    }
                    xoa(k);
                }
            }
            if (sokhachcho == 0) return;
        }
        //customer*dauhang = hangcho;
        if (sokhachcho > 0) {
            for (int i = 1; i <= num; i++) {
                string name = hangcho->name;
                int energy = hangcho->energy;
                //dauhang = dauhang -> next;
                pop();
                RED(name, energy);
                if (hangcho == nullptr) return;
                //if (dauhang == nullptr) return;
                //dauhang = dauhang -> next;
            }
        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////
    customer*tim(customer* head, int k){
        customer*temp = head;
        for(int i = 0; i < k; i++) temp = temp -> next;
        return temp;
    }
    int diachi(string n){
            customer*temp = ttvaonhaan;
            int i = 1;
            while ((i != sokhachban + sokhachcho) && (temp -> name != n)){
                temp = temp -> next;
                i++;
            }
            return i;
    }
    int insort(customer*& ds, int dodai, int buocnhay){
        int solanswap = 0;
        for(int i = buocnhay; i < dodai; i++){
            for (int j = i; j >= buocnhay ; j -= buocnhay){
                customer* vitri1 = tim(ds, j);
                customer* vitri2 = tim(ds,j - buocnhay);
                if (abs(vitri1 -> energy) > abs(vitri2 -> energy) || abs(vitri1 -> energy) == abs(vitri2 -> energy) && diachi(vitri1 -> name) > diachi(vitri2 -> name) ){
                    swap(vitri1 -> energy,vitri2 -> energy);
                    swap(vitri1 -> name, vitri2 -> name);
                    solanswap++;
                }
                else break;
            }
        }
        return solanswap;
    }
    int shellsort(customer*& ds,int dodai){
        int N = 0;
        for(int i = dodai / 2; i > 2; i = i / 2){
            for(int j = 0; j < i; j++) {
                customer *temp = tim(ds, j);
                N += insort(temp, dodai - j, i);
            }
        }
        customer*temp = tim(ds, 0);
        N += insort(ds,dodai,1);
        return N;
    }
    void PURPLE()
    {
        //cout << "purple"<< endl;

    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    customer*vitrix(int x){
        customer* temp = head;
        for (int i = 2; i <= x; i++){
            temp = temp -> next;
        }
        return temp;
    }

    bool daudangxet(int energy){
        if (energy < 0) return false;
        return true;
    }
    void daonguoc(customer*vitri){
        customer*temp1 = vitri;
        customer*temp2 = temp1 -> next;
        bool bovtdau = false;
        while((temp2 -> name != temp1 -> name && temp1 -> next -> name != temp2 -> name) || bovtdau == false){
            bool p = daudangxet(temp1 -> energy);
            bool q = daudangxet(temp2 -> energy);
            if (p == daudangxet(vitri -> energy) && q == daudangxet(vitri -> energy)){
                swap(temp1 -> energy, temp2 -> energy);
                swap(temp1 -> name, temp2 -> name);
                temp1 = temp1 -> prev;
                temp2 = temp2 -> next;
            }
            else if (p != daudangxet(vitri -> energy) && q != daudangxet(vitri -> energy)){
                temp1 = temp1 -> prev;
                temp2 = temp2 -> next;
            }
            else if (p == daudangxet(vitri -> energy) && q != daudangxet(vitri -> energy)){
                temp2 = temp2 -> next;
            }
            else{
                temp1 = temp1 -> prev;
            }
            bovtdau = true;
        }
    }
    void REVERSAL()
    {
        //cout << "reversal" << endl;
        if (sokhachban == 0 || sokhachban == 1) return;
        customer*temp = vitrix(x);
        string vitritruocthaydoi = vitrix(x) -> name;
        if (sokhachban == 1 || sokhachban == 0){
            return;
        }
        while (daudangxet(temp -> prev -> energy) == daudangxet(vitrix(x) -> energy) && temp -> prev != vitrix(x)){
            temp = temp -> prev;
        }
        string dau = head -> name;
        string cuoi = tail -> name;
        if (temp -> prev == vitrix(x)){
            daonguoc(vitrix(x));
        }
        else {
            daonguoc(vitrix(x));
            daonguoc(temp->prev);
        }
        customer*vitriX = timkiem(vitritruocthaydoi);
        for (int i = x; i > 1; i--){
            vitriX = vitriX -> prev;
        }
        head = vitriX;
        tail = head -> prev;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int tong(customer*x, int k){
        customer * p = x;
        int s = x -> energy;
        for (int i = 1; i <= k; i++){
            p = p -> next;
            s = s + p -> energy;
        }
        return s;
    }
    void UNLIMITED_VOID()
    {
        //cout << "unlimited_void" << endl;
        if (sokhachban < 4) return;
        int nhonhat = tong(vitrix(x),3);
        customer*q = vitrix(x);
        int temp = 0;
        customer*p = vitrix(x);
        do {
            for (int i = 3; i < sokhachban; i++) {
                int s = tong(p, i);
                int temp1 = i + 1;
                if (s < nhonhat ||(s == nhonhat && temp1 >= temp)) {
                    nhonhat = s;
                    temp = i + 1;
                    q = p;
                }
            }
            p = p -> next;
        } while(p != vitrix(x));
        int gtnt = q -> energy;
        customer* vitriin = q;
        customer* cuoichuoi;
        int xx = temp;
        for(customer*nhoxiu = q -> next; xx > 1; xx--){
            if (gtnt > nhoxiu -> energy){
                gtnt = nhoxiu -> energy;
                vitriin = nhoxiu;
            }
            cuoichuoi = nhoxiu;
            nhoxiu = nhoxiu -> next;
        }
        int yy = temp;
        for(customer*pp = vitriin; yy >= 1;yy--){
            if (vitriin == q){
                pp -> print();
                pp = pp -> next;
            }
            else {
                pp -> print();
                if (pp == cuoichuoi){
                    pp = q;
                }
                else pp = pp -> next;
            }
        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////
    bool sosanh(customer* p, customer* q) {
        int tongchuthuat = 0;
        int tongchulinh = 0;
        if (p != nullptr) {
            if (p->energy < 0) {
                tongchulinh = p->energy;
            } else {
                tongchulinh = p->energy;
                tongchuthuat = p->energy;
            }
            for (customer *temp = p->next; temp != head; temp = temp->next) {
                if (temp->energy < 0) {
                    tongchulinh += temp->energy;
                } else {
                    tongchulinh += temp->energy;
                    tongchuthuat += temp->energy;
                }
            }
        }
        if (q != nullptr) {
            if (q->energy < 0) {
                tongchulinh += q->energy;
            } else {
                tongchulinh += q -> energy;
                tongchuthuat += q->energy;
            }
            for (customer *temp = q->next; temp != nullptr; temp = temp->next) {
                if (temp->energy < 0) {
                    tongchulinh += temp->energy;
                } else {
                    tongchulinh += temp->energy;
                    tongchuthuat += temp->energy;
                }
            }
            if (tongchuthuat >= abs(tongchulinh)) {
                return false;
            }
            return true;
        }
        else{
            if (tongchuthuat >= abs(tongchulinh)) {
                return false;
            }
            return true;
        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////
    void xoakhoiban(customer*vitri){
        if (head == nullptr && tail == nullptr) return;
        if (sokhachban == 1){
            customer*hi = head;
            delete hi;
            head = tail = nullptr;
            return;
        }
        if (vitri -> name == head -> name){
            head = head -> next;
            delete vitri;
            head -> prev = tail;
            tail -> next = head;
        }
        else if (vitri -> name == tail -> name){
            customer *tempcuoi = tail;
            tail = tail -> prev;
            delete tempcuoi;
            head -> prev = tail;
            tail -> next = head;
        }
        else{
            vitri -> next -> prev = vitri -> prev;
            vitri -> prev -> next = vitri -> next;
            delete vitri;
        }
    }
    void xoakhoicho(customer*vitri, customer*&hangcho, int sokhachcho){
        if (hangcho == nullptr) return;
        if (sokhachcho == 1){
            customer*hi = hangcho;
            delete hi;
            hangcho = nullptr;
            return;
        }
        if (vitri -> name == hangcho -> name){
            hangcho = hangcho -> next;
            delete vitri;
        }
        else if (vitri -> next == nullptr){
            customer *tempcuoi = vitri;
            vitri = vitri -> prev;
            vitri -> next = nullptr;
            delete tempcuoi;
        }
        else{
            vitri -> next -> prev = vitri -> prev;
            vitri -> prev -> next = vitri -> next;
            delete vitri;
        }
    }
    int tragiatrix(customer*vitri){
        if (timkiem(vitri -> name) -> name == head -> name || timkiem(vitri -> name) -> name == tail -> name) {
            if (vitri->energy > 0) {
                x = 1;
            } else {
                x = sokhachban - 1;
            }
        }
        else{
            customer*dautien = head;
            for (int j = 1; vitri != dautien; j++){
                dautien = dautien -> next;
                x = j + 1;
            }
            if (vitri -> energy > 0){
                x = x;
            }
            else{
                x = x - 1;
            }
        }
        return x;
    }
    void xoatatcakhachban(bool dungsai){
        // tra head tail ttvaonhaan vaocuoi x
        customer * temp = ttvaonhaan;
        customer * temp1 = vaocuoi;

        if(sokhachcho != 0){
            int x = sokhachban + sokhachcho;
            do{
                if(daudangxet(temp1 -> energy) == dungsai){
                   temp1-> print();
                   temp1 = temp1->prev;
                } else temp1 = temp1 -> prev;
                x--;
            }while(x != sokhachban);
        }

        if(sokhachban != 0){
            int x = sokhachban;
            do{
                if (daudangxet(temp1->energy) == dungsai){
                    temp1->print();
                    temp1 = temp1->prev;
                } else temp1 = temp1 -> prev;
                x--;
            }while(x != 0);
        }
        if (sokhachban != 0) {
            int vitri = 1;
            do {
                if (daudangxet(temp->energy) == dungsai) {
                    //temp->print();
                    x = tragiatrix(timkiem(temp->name));
                    xoakhoiban(timkiem(temp->name));
                    temp = temp->next;
                    if (sokhachban + sokhachcho == 1){
                        customer *hi = ttvaonhaan;
                        delete hi;
                        ttvaonhaan = vaocuoi = nullptr;
                        sokhachban = 0;
                        vitri++;
                        return;
                    } else {
                        xoa(vitri);// thứ tự vào bàn
                        vitri--;
                    }
                    sokhachban--;
                } else temp = temp->next;
                vitri++;
            } while (vitri != sokhachban + 1);
        }
        if (sokhachcho != 0) {
            int vitrisau = sokhachban + 1;
            do {
                if (daudangxet(temp->energy) == dungsai) {
                    //temp->print();
                    //xoakhoihangcho
                    xoakhoicho(timkiemcho(temp->name,hangcho,sokhachcho),hangcho,sokhachcho);
                    temp = temp->next;
                    if (sokhachban + sokhachcho == 1){
                        customer *hi = ttvaonhaan;
                        delete hi;
                        ttvaonhaan = vaocuoi = nullptr;
                        sokhachban = 0;
                        vitrisau++;
                        return;
                    } else {
                        xoa(vitrisau);
                        vitrisau--;
                    }
                    sokhachcho--;
                } else temp = temp->next;
                vitrisau++;
            } while (vitrisau != sokhachban + sokhachcho + 1);
        }
    }

    void DOMAIN_EXPANSION()
    {
        //cout << "domain_expansion" << endl;
        if (sokhachban + sokhachcho == 0) return;
        bool giu = sosanh(head,hangcho);
        xoatatcakhachban(giu);
        if (sokhachcho > 0) {
            if (sokhachban != MAXSIZE) {
                for (int i = 1; i <= MAXSIZE; i++) {
                    string name = hangcho->name;
                    int energy = hangcho->energy;
                    if (sokhachban != MAXSIZE) {
                        pop();
                        RED(name, energy);
                    }
                    if (hangcho == nullptr) return;
                }
            }
        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////
    void LIGHT(int num)
    {
        //cout << "light " << num << endl;
        if (num == 0){
            customer * temp = hangcho;
            for (int i = 1; i <= sokhachcho; i++){
                temp -> print();
                temp = temp -> next;
            }
        }
        else if (num > 0){
            if (sokhachban == 0) return;
            customer *Vitrix = vitrix(x);
            do{
                Vitrix -> print();
                Vitrix = Vitrix -> next;
            }while (Vitrix != vitrix(x));
        }
        else{
            if (sokhachban == 0) return;
            customer *temp = tail;
            for (int i = sokhachban; i > x; i--) {
                temp = temp->prev;
            }
            customer *vitrix = temp;
            do {
                temp->print();
                temp = temp->prev;
            } while (temp != vitrix);
        }
    }
};