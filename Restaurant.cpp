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
    bool doichieu;
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
        doichieu = true;
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
        customer * temp = hangcho;
        hangcho = hangcho -> next;
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
            if (sokhachban < (MAXSIZE / 2.0)) {
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
                List *l = NULL;
                res(energy, l);
                int vitri = vitrilonnhat(l);
                Node *temp = l->dau;
                for(int i = 1; i < vitri; i++){
                    temp = temp -> tieptheo;
                }
                if (temp->data >= 0) {
                    int k = vitri + 1;
                    them(k, name, energy);
                    x = k;
                } else {
                    them(vitri, name, energy);
                    x = vitri;
                }
                themcuoi(name,energy);
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
        }
        else{
            for (int i = 1; i <= num; i++){
                customer * temp = ttvaoban;
                customer*vitri=timkiem(temp -> name);
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
        customer*vitritruocthaydoi = vitrix(x);
        if (sokhachban == 1 || sokhachban == 0){
            return;
        }
        while (daudangxet(temp -> prev -> energy) == daudangxet(vitrix(x) -> energy) && temp -> prev != vitrix(x)){
            temp = temp -> prev;
        }
        customer*dau = head;
        daonguoc(vitrix(x));
        daonguoc(temp -> prev);
        customer*tam =timkiem(dau -> name);
        head = tam;
        customer*tamtam =timkiem(vitritruocthaydoi -> name);
        customer*vitridau = head;
        x=1;
        for(int i = 2; vitridau -> name != tamtam -> name;i++){
            vitridau = vitridau -> next;
            x=i + 1;
        }
        doichieu = !doichieu;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void UNLIMITED_VOID()
    {
        //cout << "unlimited_void" << endl;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////
    void DOMAIN_EXPANSION()
    {
        //cout << "domain_expansion" << endl;
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
            customer * temp = tail;
            for (int i = sokhachban; i > x; i--){
                temp = temp ->prev;
            }
            customer *vitrix = temp;
            do{
                temp -> print();
                temp = temp -> prev;
            }while (temp != vitrix);
        }
    }
};