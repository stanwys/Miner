#ifndef deklaracjefunkcji_hpp
#define deklaracjefunkcji_hpp
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cstring>
#include<fstream>
#include<stdio.h>
#include<stack>
#include<queue>
#include<allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_primitives.h>
using namespace std;
//definicja struktur
extern int spr;
struct Dane
{
    int bomb=0,byl=0,flag=0,ilebwokol=0;int x,y;
};
struct Wyn
{
    int czas;
    char nazwa[16]={};
};
//definicje funkcji
int ilebomb(Dane d[],int i,int k,int n);
void przeszukaj(Dane d[],int i,int k,int n,ALLEGRO_BITMAP *tile);
void graj(int k,int w,double ib,ALLEGRO_BITMAP *tile,ALLEGRO_DISPLAY *display,ALLEGRO_EVENT_QUEUE *event_queue,
          ALLEGRO_FONT *font8,int& gramydalej,int typgry,int load,Dane inne[],Wyn wyniki[],int flagi,int pauza,int czas);
void pokazbomby(Dane d[],int n,int rozm,ALLEGRO_BITMAP *tile,int pom,int kek);
void ustawflage(Dane d[],int pom,ALLEGRO_BITMAP *tile,int fl);
int menu(ALLEGRO_DISPLAY *Menu,ALLEGRO_EVENT_QUEUE *event_queue,ALLEGRO_FONT *font8,int dziel,char *tab[]);
int wybor(char *tab[],ALLEGRO_EVENT_QUEUE *event_queue,ALLEGRO_FONT *font8,int dziel);
void dowolnemenu(ALLEGRO_DISPLAY *menu,ALLEGRO_EVENT_QUEUE *event_queue,ALLEGRO_FONT *font8,
                 int& gramydalej,char *tab[],int& gramy,int& k_dow,int& w_dow,int& b_dow);
void poletext(int znakzachety[],int ilemax[],int *war[],int ilejest[],int& nr_pol,
              ALLEGRO_DISPLAY *menu,ALLEGRO_EVENT_QUEUE *event_queue,ALLEGRO_FONT *font,ALLEGRO_BITMAP *kwad,int& sprawdzam);
void rysuj2(ALLEGRO_COLOR kol,ALLEGRO_DISPLAY *display,ALLEGRO_BITMAP *kwad,ALLEGRO_FONT *font8,int x,int y,
            int liczba,int flaga,int tryb);
void rysznak(ALLEGRO_COLOR kol,ALLEGRO_DISPLAY *display,ALLEGRO_BITMAP *kwad,ALLEGRO_FONT *font8,int x,int y,
            char znak,int flaga,int tryb);
int Horner(int *war[],int nr_pola,int ile);
void save(int typgry,Dane d[],int k,int w,int ilebomb,int ilemamflag,int pauza,int czas);
void loadgame(FILE *p,Dane inne[],int& k,int& w,int& bomby,int& flagi,int& pauza,int& czas);
void zapiszwynik(int sumaczasu,int trybgry,Wyn wyniki[],int ilemax,
                 ALLEGRO_DISPLAY *zapiswyn,ALLEGRO_EVENT_QUEUE *event_queue,ALLEGRO_BITMAP *kwad,ALLEGRO_FONT *font8);
int wstaw_wynik(int sumaczasu,Wyn wyniki[]);
void wczytaj(Wyn wyniki[],FILE *p);
void zapisz(Wyn wyniki[],FILE *p);
void przegladaj_wyniki(ALLEGRO_DISPLAY *menu,ALLEGRO_EVENT_QUEUE *event_queue,ALLEGRO_FONT *font8,
                       Wyn Wpocz[],Wyn Wzaaw[],Wyn Weksp[]);
void rysuj_wyniki(ALLEGRO_DISPLAY *menu,ALLEGRO_FONT *font8,Wyn wyniki[],int typgry);
void rules_and_help(ALLEGRO_DISPLAY *menu,ALLEGRO_EVENT_QUEUE *event_queue,ALLEGRO_FONT *font8,ALLEGRO_FONT *font);
#endif // struct_hpp

