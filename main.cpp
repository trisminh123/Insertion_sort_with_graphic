#include <iostream>
#include <fstream>
#include <graphics.h>
#define MAX 10
using namespace std;
// khai bao cac thuoc tinh cua 1 diem( toa do x,y, gia tri)
struct toado{
    int x;
    int y;
    int giatri;
};

// khai bao toan cuc
toado td[MAX]; // danh sach cac diem
char buffer[10];
int sodinh;// so phan tu can sap xep
bool enable_click = true;
//khai bao prototype

void drawpoint(struct toado p, int color);
void drawpoints(struct toado p[MAX], int size, int skip);
void tomauloang(int x, int y, int color, int bien_color);
void docfile();
void keyboard();
void printpoints();
void GUI_init();
void insertion_sort(struct toado p[MAX], int size);

void drawpoint(toado p, int color){
    setlinestyle(2,0,2);
    setcolor(color);
    rectangle(p.x-20,p.y-3-p.giatri*2,p.x+20,p.y+10);
    tomauloang(p.x,p.y,color,color);
    settextstyle(2,0,6);
    outtextxy(p.x-4, p.y+20, itoa(p.giatri,buffer,10));
}

void drawpoints(toado p[MAX], int size, int skip){ // skip: vi tri xac dinh phan tu bi lay ra de chen vao phan tu khac
    for (int i=0; i<sodinh; i++){
        if (i != skip){
            drawpoint(p[i], 14);
            delay(100);

        }
    }
}

void tomauloang(int x, int y, int color, int border_color){
    int current_color = getpixel(x,y); // lay mau cua diem dang xet
    if(current_color != color and current_color != border_color){ // kiem tra mau diem hien tai da duoc to chua
        putpixel(x,y,color); // to mau va goi de quy xet 4 diem xung quanh
        tomauloang(x-1,y,color,border_color);
        tomauloang(x+1,y,color,border_color);
        tomauloang(x,y-1,color,border_color);
        tomauloang(x,y+1,color,border_color);
    }
}
void docfile(){
    ifstream inp; inp.open("input.txt");
    inp >> sodinh; // nhap so phan tu can sap xep
    cout << "so phan tu can sap xep: " << sodinh << endl;
    // doc toa do va gia tri phan tu tu file input
    for (int i=0; i<sodinh; i++){
        inp >> td[i].x >> td[i].y >> td[i].giatri;
    }
    // in ra console toa do da doc
    for (int i=0; i<sodinh; i++){
        cout << td[i].x  << " " << td[i].y << " " << td[i].giatri << endl;
    }
    inp.close();
}


void printpoints(toado m[MAX], int size){
    for (int i=0; i<size; i++){
        cout<< m[i].x << " " << m[i].y << " " << m[i].giatri << endl;
    }
}

// tao giao dien nguoi dung
void GUI_init(){
    setcolor(YELLOW);
    // main border
    setlinestyle(1,1,5);
    rectangle(10,10,550,370);
    // load file button
    rectangle(560,10,680,50);
    settextstyle(2,0,6);
    outtextxy(570,20,"LOAD FILE");
    //keyboard button
    rectangle(560,70,680,110);
    settextstyle(2,0,6);
    outtextxy(570,80,"KEYBOARD");
    // Sort button
    rectangle(560,130,680,170);
    settextstyle(2,0,6);
    outtextxy(590,140,"SORT");
}

// xac dinh thao tac click chuot
void mouse(){
    int x_mouse;
    int y_mouse;
    while(enable_click){
        // kiem tra su kien click chuot
        if (ismouseclick(WM_LBUTTONDOWN)){
            // lay toa do click chuot
            getmouseclick(WM_LBUTTONDOWN, x_mouse, y_mouse);
            // kiem tra chuot co click vao nut load file khong?
            if (x_mouse > 560 and x_mouse < 680 and y_mouse > 10 and y_mouse < 50){
                cout << "Loading file..." <<endl;
                docfile();
                drawpoints(td,sodinh,MAX+1);
            }
            // kiem tra chuot co click vao nut keyboard khong?
            if (x_mouse > 560 and x_mouse < 680 and y_mouse > 70 and y_mouse < 110){
                // nhap cac diem tu ban phim
                cout << "Input from keyboard..." << endl;
                keyboard();
                // ve cac diem
                drawpoints(td,sodinh,MAX+1);
            }
             // kiem tra chuot co click vao nut sort khong?
            if (x_mouse > 560 and x_mouse < 680 and y_mouse > 130 and y_mouse < 170){
                cout << "Insertion sort performing..." << endl;
                insertion_sort(td,sodinh);
            }
        }
        delay(100);
    }
}

// doc du lieu tu ban phim
void keyboard(){

    cout << "Nhap so phan tu can sap xep: ";
    cin >> sodinh; // nhap so phan tu can sap xep
        // doc toa do cua cac diem
    ifstream inp; inp.open("input_keyboard.txt");
    // doc toa do va gia tri phan tu tu file input
    for (int i=0; i<sodinh; i++){
        inp >> td[i].x >> td[i].y ;
    }

    // nhap gia tri cac diem
    for (int i=0; i<sodinh; i++){
        cout << "Nhap phan tu thu " << i+1 <<": ";
        cin >> td[i].giatri;
    }
    cout << "Finished" << endl;
    // in ra cac diem
    printpoints(td,sodinh);
    inp.close();
}

void insertion_sort(toado p[MAX], int size){
    enable_click = false;
    GUI_init();
    int key, j;
    for (int i=1; i<size; i++){
        cleardevice();
        for (int k = 0; k<sodinh; k++){
            if (k == i){
                drawpoint(td[k],4); // to mau do phan tu thu i
            }
            else{
                drawpoint(td[k],14); // nhung phan tu con lai to mau vang
            }
            delay(100);
        }
        delay(200);
        cleardevice();
        drawpoints(td,sodinh,i); // ve lai cac cot ( tru cot thu i vi phan tu bi lay ra danh sach de so sanh voi cac phan tu truoc)
        key = p[i].giatri; // bien key de luu lai gia tri cua phan tu thu i
        j = i-1; // lay chi so cua phan tu ben trai dau tien
        do{
            drawpoint(p[j],4); // ve cot j dang duoc xet bang mau do
            delay(200);
            if (p[j].giatri > key){
                p[j+1].giatri = p[j].giatri;
                cleardevice();
                for (int k = 0; k<sodinh ; k++){
                    if (k == j+1){
                        drawpoint(td[k],2); // to mau xanh phan tu j+1 sau khi day qua phai
                    }
                    else if (k != j){
                        drawpoint(td[k],14);
                    }
                    delay(100);
                }
                j--; // giam j de xet phan tu ben trai tiep theo
            }
        } while (j >= 0 and p[j].giatri > key);
        p[j+1].giatri = key;
        cleardevice();
        // ve lai danh sach sau khi chen phan tu
        for (int k=0 ; k<sodinh; k++){
            if (k==j+1){
                drawpoint(td[k],2); // ve phan tu duoc chen mau xanh la
            }
            else{
                drawpoint(td[k],14); // nhung phan tu con lai mau vang
            }
            delay(100);
        }
    }
    cleardevice();
    for (int i=0; i<sodinh; i++){
        drawpoint(td[i],2); // ve lai danh sach sau khi hoan thanh sap xep
    }
    // in ra danh sach da sap xep ra console
    cout << "danh sach sau khi sap xep: "<<endl;
    for (int i=0; i<sodinh; i++){
        cout << p[i].giatri << " ";
    }
}
int main()
{
    // khoi tao giao dien do hoa
    initwindow(700,400);
    GUI_init();
    // dung chuot
    mouse();
    // dung man hinh
    getch();
    return 0;
}
