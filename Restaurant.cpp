#include "main.h"

class imp_res : public Restaurant
{
public:
    customer* head;
    customer* tail;
    customer* hangcho;
    customer* ttvaoban;
    customer* vaocuoi;
    int sokhachban;
    int  sokhachcho;
    int x;
public:
    imp_res() {
        head = NULL;
        tail = NULL;
        hangcho = NULL;
        ttvaoban = NULL;
        vaocuoi = NULL;
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
        l -> dau = l -> cuoi = NULL;
    }
    Node *taonode(int x){
        Node * newnode = new Node;
        newnode -> tieptheo = NULL;
        newnode -> phiatruoc = NULL;
        newnode -> data = x;
        return newnode;
    }
    void res(int energy, List *&l){
        l = new List();
        Init(l);
        customer *temp = head;
        if (l -> dau == NULL) {
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
        if (hangcho == NULL){
            hangcho = cus;
            sokhachcho++;
            return;
        }
        while(temp -> next != NULL){
            temp = temp -> next;
        }
        temp -> next = cus;
        cus -> prev = temp;
        sokhachcho++;
    }
    void pop(){
        if (hangcho == NULL) return;
        customer * temp = hangcho;
        hangcho = hangcho -> next;
        if (hangcho != NULL) hangcho -> prev = NULL;
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
        //customer *cus = new customer (name, energy, nullptr, nullptr);
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
                themcuoi(name,energy);
            }
/////////////////////////////////////////////////////////////////
            else if (sokhachban == MAXSIZE) {
                if (sokhachcho < MAXSIZE) {
                    push(name, energy);
                } else return;
            }
/////////////////////////////////////////////////////////////////
            else {
                if (sokhachban == 0) {
                    them(1, name, energy);
                    x = 1;
                }
                else {
                    List *l = NULL;
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
                themcuoi(name, energy);
            }
        }
/////////////////////////////////////////////////////////////////
    }

    void clear(){
        while (sokhachban != 0){
            if (head == NULL && tail == NULL) return;
            customer *temp = head;
            head = head -> next;
            delete temp;
            --sokhachban;
        }
        tail = NULL;
        head = NULL;
    }
    void clearttvao(){
        while (ttvaoban != NULL){
            if (ttvaoban == NULL && vaocuoi == NULL) return;
            customer *temp = ttvaoban;
            ttvaoban = ttvaoban -> next;
            delete temp;
        }
        vaocuoi = NULL;
        ttvaoban = NULL;
    }
/////////////////////////////////////////////////////////////////
    void themcuoi(string name, int energy){
        customer * cus = new customer (name, energy, nullptr, nullptr);
        if (ttvaoban == NULL){
            ttvaoban = vaocuoi = cus;
            return;
        }
        customer * temp = ttvaoban;
        vaocuoi -> next = cus;
        cus -> prev = vaocuoi;
        vaocuoi = cus;
    }

    void xoa(int index){
        customer *temp = ttvaoban;
        if ((ttvaoban == NULL && vaocuoi == NULL) || index < 1 || index > sokhachban) return;
        if (index == 1){
            ttvaoban = ttvaoban -> next;
            ttvaoban -> prev = NULL;
            delete temp;
        }
        else if (index == sokhachban){
            customer *tempcuoi = vaocuoi;
            vaocuoi = vaocuoi -> prev;
            vaocuoi -> next = NULL;
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
    /////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////
    void BLUE(int num)
    {
        //cout << "blue "<< num << endl;
        if (sokhachban == 0) return;
        if (num >= sokhachban) {
            clear();
            clearttvao();
            x = 0;
        }
        else{
            for (int i = 1; i <= num; i++){
                customer * temp = ttvaoban;
                customer*vitri=timkiem(temp -> name);
                if (head == tail){
                    x = 0;
                    xoa(1);
                    customer*hi = head;
                    delete hi;
                    head = tail = NULL;
                }
                if (vitri == head){
                    if (temp -> energy > 0){
                        x = 1;
                    }
                    else{
                        x = sokhachban - 1;
                    }
                    xoa(1);
                    if (head == NULL && tail == NULL) return;
                    else{
                        customer*dautien = head;
                        head = head -> next;
                        delete dautien;
                        tail -> next = head;
                        head -> prev = tail;
                    }
                    --sokhachban;
                }
                else if (vitri == tail){
                    if (head == NULL && tail == NULL) return;
                    else{
                        customer*cuoicung = tail;
                        tail = tail -> prev;
                        delete cuoicung;
                        tail -> next = head;
                        head -> prev = tail;
                    }
                    --sokhachban;
                    if (temp -> energy > 0){
                        x = 1;
                    }
                    else{
                        x = sokhachban - 1;
                    }
                    xoa(1);
                }
                else{
                    customer*dautien = head;
                    for (int j = 1; vitri != dautien; j++){
                        dautien = dautien -> next;
                        x = j + 1;
                    }
                    dautien -> next -> prev = dautien -> prev;
                    dautien -> prev -> next = dautien -> next;
                    delete dautien;
                    --sokhachban;
                    if (temp -> energy > 0){
                        x = x;
                    }
                    else{
                        x = x - 1;
                    }
                    xoa(1);
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
                //if (dauhang == NULL) return;
                //dauhang = dauhang -> next;
            }
        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////
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
        int nhonhat = tong(head,4);
        customer*q = head;
        int temp = 0;
        for (customer*p = head; p -> next != head; p = p -> next){
            for (int i = 4; i <= sokhachban; i++){
                if (tong(p,i) <= nhonhat){
                    nhonhat = tong(p,i);
                    temp = i;
                    q=p;
                }
            }
        }
        for(customer*p = q; temp>=1;temp--){
            p -> print();
            p = p -> next;
        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////
    bool sosanh(customer* p, customer* q) {
        int tongchuthuat = 0;
        int tongchulinh = 0;
        if (p != NULL) {
            if (p->energy < 0) {
                tongchulinh = p->energy;
            } else tongchuthuat = p->energy;
            for (customer *temp = p->next; temp != head; temp = temp->next) {
                if (temp->energy < 0) {
                    tongchulinh += temp->energy;
                } else tongchuthuat += temp->energy;
            }
        }
        if (q != NULL) {
            if (q->energy < 0) {
                tongchulinh += q->energy;
            } else tongchuthuat += q->energy;
            for (customer *temp = q->next; temp != NULL; temp = temp->next) {
                if (temp->energy < 0) {
                    tongchulinh += temp->energy;
                } else tongchuthuat += temp->energy;
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
        if (head == NULL && tail == NULL) return;
        if (sokhachban == 1){
            customer*hi = head;
            delete hi;
            head = tail = NULL;
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
        // tra head tail ttvaoban vaocuoi x
        int vitri = sokhachban;
        customer * temp = vaocuoi;
        do{
            if (daudangxet(temp -> energy) == dungsai){
                temp -> print();
                x = tragiatrix(timkiem(temp -> name));
                xoakhoiban(timkiem(temp -> name));
                temp = temp -> prev;
                if (sokhachban == 1){
                    customer*hi = ttvaoban;
                    delete hi;
                    ttvaoban = vaocuoi = NULL;
                    sokhachban = 0;
                    vitri--;
                    return;
                }
                else xoa(vitri);// thứ tự vào bàn
                sokhachban--;
            }
            else temp = temp -> prev;
            vitri--;
        }
        while(vitri != 0);
    }
    void xoatatcahangcho(bool dungsai){
        customer * chay = hangcho;
        while(chay -> next != NULL){
            chay = chay -> next;
        }
        do{
            if (daudangxet(chay -> energy) == dungsai){
                chay -> print();
                customer*temp = hangcho;
                if (hangcho == NULL) {
                    sokhachcho = 0;
                    chay = NULL;
                    return;
                }
                if (sokhachcho == 1){
                    customer*hi = hangcho;
                    delete hi;
                    hangcho = NULL;
                    chay = NULL;
                    sokhachcho = 0;
                    return;
                }
                if (chay->name == temp->name) {
                    customer *hi = hangcho;
                    hangcho = hangcho -> next;
                    hangcho -> prev = NULL;
                    chay = chay -> prev;
                    delete hi;
                    --sokhachcho;
                }
                else if (chay -> next == NULL){
                    customer * hi = chay;
                    chay = chay -> prev;
                    chay -> next = NULL;
                    delete hi;
                    --sokhachcho;
                }
                else {
                    customer *tmp = chay;
                    chay = chay -> prev;
                    tmp->next->prev = tmp->prev;
                    tmp->prev->next = tmp->next;
                    delete tmp;
                    --sokhachcho;
                }
            }
            else{
                chay = chay -> prev;
            }
        }while(chay != NULL);
    }

    void DOMAIN_EXPANSION()
    {
        //cout << "domain_expansion" << endl;
        if (sokhachban == 0) return;
        bool giu = sosanh(head,hangcho);
        if (sokhachcho != 0) {
            xoatatcahangcho(giu);
        }
        xoatatcakhachban(giu);
        if (sokhachcho > 0) {
            if (sokhachban != MAXSIZE) {
                for (int i = 1; i <= MAXSIZE; i++) {
                    string name = hangcho->name;
                    int energy = hangcho->energy;
                    //dauhang = dauhang -> next;
                    if (sokhachban != MAXSIZE) {
                        pop();
                        RED(name, energy);
                    }
                    if (hangcho == nullptr) return;
                    //if (dauhang == NULL) return;
                    //dauhang = dauhang -> next;
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