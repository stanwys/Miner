#include "deklaracjefunkcji.hpp"
void wczytaj(Wyn wyniki[],FILE *p)
{
    int pom,i=0,j=0;
    queue<char>lel;char z1,v[16]={};
    while(!feof(p))
    {
        // wczytuje sumaczasu
        z1=fgetc(p);
        if(z1=='*')
        {//obliczam wartosc
            j=0;
            while(!lel.empty()){
            pom=int(lel.front()-48);j=j*10+pom;lel.pop();}
            wyniki[i].czas=j;
        }
        else if(z1=='\n')
        {
            //wczytuje znaki
            j=0;
            while(!lel.empty()){
            v[j]=lel.front();j++;lel.pop();}
            strcpy(wyniki[i].nazwa,v);i++;
        }
        else lel.push(z1);
    }
}
void zapisz(Wyn wyniki[],FILE *p)
{
    int i=0;char v[3]={};
    while(i<5 && wyniki[i].czas!=9999)
    {
        itoa(wyniki[i].czas,v,10);
        fputs(v,p);fputs("*",p);
        fputs(wyniki[i].nazwa,p);fputs("\n",p);
        i++;
    }
}
void rysuj_wyniki(ALLEGRO_DISPLAY *menu,ALLEGRO_FONT *font8,Wyn wyniki[],int typgry)
{
    int i;
    ALLEGRO_COLOR zol=al_map_rgb(255,255,0);
    al_clear_to_color(al_map_rgb_f(0.5,0.5,0.5));
    switch(typgry)
    {
        case 0:al_draw_text(font8,zol,20,50,0,"Najlepsze wyniki dla poziomu poczatkujacy");break;
        case 1:al_draw_text(font8,zol,20,50,0,"Najlepsze wyniki dla poziomu zaawansowany");break;
        case 2:al_draw_text(font8,zol,20,50,0,"Najlepsze wyniki dla poziomu ekspert");break;
        default:break;
    }
    al_draw_text(font8,zol,20,100,0,"Pozycja");al_draw_text(font8,zol,150,100,0,"Imie");
    al_draw_text(font8,zol,500,100,0,"Wynik");
    i=0;
    while(i<5 && wyniki[i].czas!=9999)
    {
        al_draw_textf(font8,zol,20,150+i*50,0,"%1d",i+1);al_draw_text(font8,zol,150,150+i*50,0,wyniki[i].nazwa);
        al_draw_textf(font8,zol,500,150+i*50,0,"%4d",wyniki[i].czas);
        i++;
    }
    al_flip_display();
}
void przegladaj_wyniki(ALLEGRO_DISPLAY *menu,ALLEGRO_EVENT_QUEUE *event_queue,ALLEGRO_FONT *font8,
                       Wyn Wpocz[],Wyn Wzaaw[],Wyn Weksp[])
{
    ALLEGRO_EVENT ev;
    int ws=0;bool koniec=false;
    rysuj_wyniki(menu,font8,Wpocz,ws);
    while(koniec==false)
    {
        al_wait_for_event(event_queue, &ev);
        if(ev.type==ALLEGRO_EVENT_KEY_DOWN)
        {
            if(ev.keyboard.keycode==ALLEGRO_KEY_RIGHT || ev.keyboard.keycode==ALLEGRO_KEY_LEFT)
            {
                if(ev.keyboard.keycode==ALLEGRO_KEY_RIGHT)
                    {ws=(ws+1)%3;}
                else if(ev.keyboard.keycode==ALLEGRO_KEY_LEFT)
                    {ws--;if(ws<0)ws=2;}
                switch(ws)
                {
                    case 0:rysuj_wyniki(menu,font8,Wpocz,ws);break;
                    case 1:rysuj_wyniki(menu,font8,Wzaaw,ws);break;
                    case 2:rysuj_wyniki(menu,font8,Weksp,ws);break;
                    default:break;
                }
            }
            else if(ev.keyboard.keycode==ALLEGRO_KEY_ESCAPE)koniec=true;
        }
    }
}
