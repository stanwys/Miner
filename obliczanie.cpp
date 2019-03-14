#include "deklaracjefunkcji.hpp"
//funkcje obliczajace
int ilebomb(Dane d[],int i,int k,int n)
{
    int s=0;
    if(i-k-1>=0){if((d[i].x)-(d[i-k-1].x)==1 &&(d[i].y-d[i-k-1].y)==1 && d[i-k-1].bomb==1)s++;}
    if(i-k>=0){if(d[i].x==d[i-k].x && (d[i].y-d[i-k].y)==1 && d[i-k].bomb==1)s++;}
    if(i-k+1>=0){if((d[i-k+1].x-d[i].x)==1 && (d[i].y-d[i-k+1].y)==1 && d[i-k+1].bomb==1)s++;}
    if(i-1>=0){if((d[i].x-d[i-1].x)==1 && d[i].y==d[i-1].y && d[i-1].bomb==1)s++;}
    if(i+1<n){if((d[i+1].x-d[i].x)==1 && d[i].y==d[i+1].y && d[i+1].bomb==1)s++;}
    if(i+k-1<n){if((d[i].x-d[i+k-1].x)==1 && d[i+k-1].y-d[i].y==1 && d[i+k-1].bomb==1)s++;}
    if(i+k<n){if(d[i].x==d[i+k].x && d[i+k].y-d[i].y==1 && d[i+k].bomb==1)s++;}
    if(i+k+1<n){if((d[i+k+1].x-d[i].x)==1 && d[i+k+1].y-d[i].y==1 && d[i+k+1].bomb==1)s++;}
    return s;
}
void przeszukaj(Dane d[],int i,int k,int n,ALLEGRO_BITMAP *tile)
{
    int pom;
    pom=ilebomb(d,i,k,n);
    if(pom==0 && d[i].flag!=1)
    {
        al_draw_bitmap_region(tile,60,0,20,20,d[i].x*20,d[i].y*20,NULL);//al_flip_display();
        d[i].byl=1;spr++;
        if(i-k>=0){if(d[i].x==d[i-k].x && (d[i].y-d[i-k].y)==1 && d[i-k].byl==0)przeszukaj(d,i-k,k,n,tile);}
        if(i-k+1>=0){if((d[i-k+1].x-d[i].x)==1 && (d[i].y-d[i-k+1].y)==1 && d[i-k+1].byl==0)przeszukaj(d,i-k+1,k,n,tile);}
        if(i+1<n){if((d[i+1].x-d[i].x)==1 && d[i].y==d[i+1].y && d[i+1].byl==0)przeszukaj(d,i+1,k,n,tile);}
        if(i+k+1<n){if((d[i+k+1].x-d[i].x)==1 && d[i+k+1].y-d[i].y==1 && d[i+k+1].byl==0)przeszukaj(d,i+k+1,k,n,tile);}
        if(i+k<n){if(d[i].x==d[i+k].x && d[i+k].y-d[i].y==1 && d[i+k].byl==0)przeszukaj(d,i+k,k,n,tile);}
        if(i+k-1<n){if((d[i].x-d[i+k-1].x)==1 && d[i+k-1].y-d[i].y==1 && d[i+k-1].byl==0)przeszukaj(d,i+k-1,k,n,tile);}
        if(i-1>=0){if((d[i].x-d[i-1].x)==1 && d[i].y==d[i-1].y && d[i-1].byl==0)przeszukaj(d,i-1,k,n,tile);}
        if(i-k-1>=0){if((d[i].x-d[i-k-1].x)==1 && (d[i].y-d[i-k-1].y)==1 && d[i-k-1].byl==0)przeszukaj(d,i-k-1,k,n,tile);}
    }
    else if(d[i].flag!=1)
    {
        d[i].byl=1;spr++;
        al_draw_bitmap_region(tile,(pom-1)*20,20,20,20,d[i].x*20,d[i].y*20,NULL);//al_flip_display();
    }
}
void pokazbomby(Dane d[],int n,int rozm,ALLEGRO_BITMAP *tile,int pom,int kek)
{
    int i;
    for(i=0;i<n;i++)
    {
        if(i==pom && kek==0)al_draw_bitmap_region(tile,120,0,rozm,rozm,(d[i].x)*rozm,(d[i].y)*rozm,NULL);
        else if(d[i].bomb==1 && kek==0 && d[i].flag==1)
        al_draw_bitmap_region(tile,100,0,rozm,rozm,(d[i].x)*rozm,(d[i].y)*rozm,NULL);
        else if(d[i].bomb==1 && kek==0)
        al_draw_bitmap_region(tile,80,0,rozm,rozm,(d[i].x)*rozm,(d[i].y)*rozm,NULL);
        else if(d[i].bomb==1 && kek==1)
        al_draw_bitmap_region(tile,20,0,rozm,rozm,(d[i].x)*rozm,(d[i].y)*rozm,NULL);
    }
    al_flip_display();
}
void ustawflage(Dane d[],int pom,ALLEGRO_BITMAP *tile,int fl)
{
    fl++;
    d[pom].flag=fl%3;
    fl=fl%3;
    al_draw_bitmap_region(tile,fl*20,0,20,20,d[pom].x*20,d[pom].y*20,NULL);
    al_flip_display();
}
void save(int typgry,Dane d[],int k,int w,int ilebomb,int ilemamflag,int pauza,int czas) //zapisanie stanu gry
{
    FILE *p;char t[3]="";int i;
    switch(typgry)
    {
        case 0:p=fopen("pocz.txt","wt");break;
        case 1:p=fopen("zaaw.txt","wt");break;
        case 2:p=fopen("eksp.txt","wt");break;
        case 3:p=fopen("dowo.txt","wt");break;
    }
    itoa(k,t,10);fputs(t,p);fputs("\n",p);itoa(w,t,10);fputs(t,p);fputs("\n",p); // rozmiary planszy
    itoa(ilebomb,t,10);fputs(t,p);fputs("\n",p);itoa(ilemamflag,t,10);fputs(t,p);fputs("\n",p);//ilejest bomb oraz ileflag
    itoa(pauza,t,10);fputs(t,p);fputs("\n",p);itoa(czas,t,10);fputs(t,p);fputs("\n",p);//czypauza oraz ileminelo czasu
    for(i=0;i<k*w;i++) //wstawiam informacje gdzie sa bomby
    {
        itoa(d[i].bomb,t,10);fputs(t,p);
    }
    fputs("\n",p);
    for(i=0;i<k*w;i++) //wstawiam informacje ktore pola sa sprawdzon
    {
        itoa(d[i].byl,t,10);fputs(t,p);
    }
    fputs("\n",p);
    for(i=0;i<k*w;i++) //wstawiam informacje o flagach na polach
    {
        itoa(d[i].flag,t,10);fputs(t,p);
    }
    fputs("\n",p);
    for(i=0;i<k*w;i++) //wstawiam informacje ile bomb wokolpola
    {
        itoa(d[i].ilebwokol,t,10);fputs(t,p);
    }
    fclose(p);
    cout<<"udalo sie zapisac";
}
void loadgame(FILE *p,Dane inne[],int& k,int& w,int& bomby,int& flagi,int& pauza,int& czas)
{
    int mnoz=1,j,tab[6],i,pom,n;stack<char>lel;char z1;
    while(!feof(p))
    {
        for(i=0;i<6;i++)//przypisuje rozmiary pola, liczbe bomb, liczbe flag, czyjest pauza, czas
        {j=0;z1=fgetc(p);
        while(z1!='\n'){lel.push(z1);z1=fgetc(p);}
        while(!lel.empty()){
        pom=int(lel.top()-48);j=j+pom*mnoz;mnoz*=10;lel.pop();}
        mnoz=1;tab[i]=j;
        }
        // tab[0] to liczba kolumn, tab[1] to liczba wierszy
        n=tab[0]*tab[1];
        for(j=0;j<n;j++)
        {
            z1=fgetc(p);pom=int(z1-48);inne[j].bomb=pom;
        }
        z1=fgetc(p);
        for(j=0;j<n;j++)
        {
            z1=fgetc(p);pom=int(z1-48);inne[j].byl=pom;
        }
        z1=fgetc(p);
        for(j=0;j<n;j++)
        {
            z1=fgetc(p);pom=int(z1-48);inne[j].flag=pom;
        }
        z1=fgetc(p);
        for(j=0;j<n;j++)
        {
            z1=fgetc(p);pom=int(z1-48);inne[j].ilebwokol=pom;
        }
        z1=fgetc(p);
    }
    k=tab[0];w=tab[1];bomby=tab[2];flagi=tab[3];pauza=tab[4];czas=tab[5];fclose(p);
}
int wstaw_wynik(int sumaczasu,Wyn wyniki[])
{
    int i=0;
    while(sumaczasu>wyniki[i].czas && i<5)i++;
    if(i==5)return 0;
    else return 1;
}
void rysznak(ALLEGRO_COLOR kol,ALLEGRO_DISPLAY *display,ALLEGRO_BITMAP *kwad,ALLEGRO_FONT *font8,int x,int y,
            char znak,int flaga,int tryb)
{
    al_set_target_bitmap(al_get_backbuffer(display));
    al_draw_bitmap(kwad,x,y,NULL);
    if(tryb==1)al_draw_textf(font8,kol,x,y,flaga,"%c",znak);
    al_flip_display();
}
void zapiszwynik(int sumaczasu,int trybgry,Wyn wyniki[],int ilemax,
                 ALLEGRO_DISPLAY *zapiswyn,ALLEGRO_EVENT_QUEUE *event_queue,ALLEGRO_BITMAP *kwad,ALLEGRO_FONT *font8)
{
    al_clear_to_color(al_map_rgb_f(0.5,0.5,0.5));
    ALLEGRO_COLOR cza=al_map_rgb(0,0,0),bia=al_map_rgb(255,255,255);
    ALLEGRO_EVENT ev;
    ALLEGRO_FONT *font=al_create_builtin_font();
    al_draw_textf(font8,al_map_rgb(255,255,0),20,20,NULL,"Twoj wynik: %3d",sumaczasu);
    al_draw_text(font,al_map_rgb(255,255,0),20,75,NULL,"Wpisz swoj");
    al_draw_text(font,al_map_rgb(255,255,0),20,86,NULL,"pseudonim/imie");
    al_draw_filled_rectangle(20,100,148,108,bia);al_flip_display();//rysuje pole, do ktorego bede wpisywal nazwe gracza
    int znakzachety=20,ilejest=0,pom,i,decyzja=0;char znak[16]={};
    while(decyzja==0)
    {
        al_wait_for_event(event_queue,&ev);
        if(ev.type==ALLEGRO_EVENT_KEY_DOWN)
        {
            if(ev.keyboard.keycode>=1 && ev.keyboard.keycode<=36 && ilejest<ilemax)
            {
                if(ilejest>(znakzachety-20)/8)//wstawiam liczbe
                {
                    for(i=15;i>(znakzachety-20)/8;i--)
                    {
                        znak[i]=znak[i-1];rysznak(cza,zapiswyn,kwad,font,20+i*8,100,znak[i],NULL,1);
                    }                               //znaki zostaly ,,przesuniete" w prawo
                    if(ev.keyboard.keycode<=26)
                    {znak[(znakzachety-20)/8]=char(64+ev.keyboard.keycode);
                    rysznak(cza,zapiswyn,kwad,font,znakzachety,100,char(64+ev.keyboard.keycode),NULL,1);}
                    else {znak[(znakzachety-20)/8]=char(21+ev.keyboard.keycode);
                    rysznak(cza,zapiswyn,kwad,font,znakzachety,100,char(21+ev.keyboard.keycode),NULL,1);}
                }
                else
                {
                    if(ev.keyboard.keycode<=26)
                    {znak[(znakzachety-20)/8]=char(64+ev.keyboard.keycode);
                    rysznak(cza,zapiswyn,kwad,font,znakzachety,100,char(64+ev.keyboard.keycode),NULL,1);}
                    else {znak[(znakzachety-20)/8]=char(21+ev.keyboard.keycode);
                    rysznak(cza,zapiswyn,kwad,font,znakzachety,100,char(21+ev.keyboard.keycode),NULL,1);}
                }
            ilejest++;znakzachety+=8;
            }
            else if(ev.keyboard.keycode==ALLEGRO_KEY_RIGHT && znakzachety+8<=20+ilejest*8)znakzachety+=8;
            else if(ev.keyboard.keycode==ALLEGRO_KEY_LEFT && znakzachety-8>=20)znakzachety-=8;
            else if(ev.keyboard.keycode==ALLEGRO_KEY_BACKSPACE && znakzachety!=20)
            {
                //przesuniecie w lewo znakow;
                for(i=(znakzachety-20)/8-1;i<15;i++)
                {
                    znak[i]=znak[i+1];rysznak(cza,zapiswyn,kwad,font,20+i*8,100,znak[i],NULL,1);
                }
                znak[15]={};rysznak(cza,zapiswyn,kwad,font,140,100,znak[i],NULL,0);
                ilejest--;
                znakzachety-=8;
            }
            else if(ev.keyboard.keycode==ALLEGRO_KEY_ESCAPE)decyzja=1; //wychodze
            else if(ev.keyboard.keycode==ALLEGRO_KEY_ENTER && ilejest>0)
            {
                i=0;
                while(sumaczasu>wyniki[i].czas && i<5)i++;
                pom=i;
                if(i!=5)//przesuwam dane w prawo
                {
                    for(i=4;i>pom;i--){strcpy(wyniki[i].nazwa,wyniki[i-1].nazwa);wyniki[i].czas=wyniki[i-1].czas;}
                    strcpy(wyniki[pom].nazwa,znak);
                    wyniki[pom].czas=sumaczasu;
                    decyzja=2; //zapisuje wynik
                }
            }
        }
        for(i=0;i<16;i++)cout<<znak[i]<<" ";cout<<endl;
    }
}
void graj(int k,int w,double ib,ALLEGRO_BITMAP *tile,ALLEGRO_DISPLAY *display,ALLEGRO_EVENT_QUEUE *event_queue,
          ALLEGRO_FONT *font8,int& gramydalej,int typgry,int load,Dane inne[],Wyn wyniki[],int flagi,int pauza,int czas)
{
    srand(time(0));
    spr=0;
    int n,ilejest=0,i,x1,y1,pom,ileb,sumaczasu=0,ilemamflag;
    n=k*w;
    Dane* d=new Dane[n];
    double start,now,temp,czasik;ileb=int(ib);
    bool koniec=false,akcja,get_event=false,paused=false,pogrze=false;
    for(i=0;i<n;i++)
    {
        d[i].x=i%k;d[i].y=i/k;
    }
    if(load==0)
    {
        while(ilejest<ileb)//generuje bomby na planszy
        {
        i=rand()%n;
        if(d[i].bomb==0)
        {
            d[i].bomb=1;
            ilejest++;
        }
        }
        ilemamflag=ileb;
        for(i=0;i<n;i++)
        {
            d[i].ilebwokol=ilebomb(d,i,k,n);
        }
        //inicjalizuje allegro
        for(int i=0;i<n;i++)
        {
            al_draw_bitmap_region(tile,0,0,20,20,(d[i].x)*20,(d[i].y)*20,NULL);
        }
    }
    else //gra jest wczytywana z pliku
    {   //przepisuje wartosci
        for(i=0;i<n;i++)
        {
            d[i].bomb=inne[i].bomb;
            d[i].byl=inne[i].byl;if(inne[i].byl==1)spr++;
            d[i].flag=inne[i].flag;
            d[i].ilebwokol=inne[i].ilebwokol;
        }
        ilemamflag=flagi;
        sumaczasu=czas;
        if(pauza==1){paused=true;al_draw_text(font8,al_map_rgb(240,6,6),3*(k*20)/5,w*20,0,"P");}
        //czas na rysowanie mapy
        for(int i=0;i<n;i++)
        {
            if(d[i].byl==0)
            al_draw_bitmap_region(tile,d[i].flag*20,0,20,20,(d[i].x)*20,(d[i].y)*20,NULL);
            else if(d[i].byl==1)
            {
                if(d[i].ilebwokol==0)
                al_draw_bitmap_region(tile,60,0,20,20,(d[i].x)*20,(d[i].y)*20,NULL);
                else
                al_draw_bitmap_region(tile,(d[i].ilebwokol-1)*20,20,20,20,(d[i].x)*20,(d[i].y)*20,NULL);
            }
        }
    }
    al_flip_display();
    //dzialanie gry
    ALLEGRO_TIMEOUT timeout;
    ALLEGRO_EVENT ev;
    ALLEGRO_BITMAP *kwad=al_create_bitmap(50,40),*plama=al_create_bitmap(8,8);
    ALLEGRO_DISPLAY *zapiswyn=NULL;
    ALLEGRO_COLOR zol=al_map_rgb(255,255,0);
    al_set_target_bitmap(kwad);
    al_clear_to_color(al_map_rgb_f(0.5,0.5,0.5));
    al_set_target_bitmap(plama);
    al_clear_to_color(al_map_rgb(255,255,255));
    al_register_event_source(event_queue,al_get_display_event_source(display));
    rysuj2(zol,display,kwad,font8,-8,20*w,ilemamflag,0,1);
    start=al_get_time();temp=start;
    while(koniec==false)
    {
        akcja=false; //chce nacisnac przycisk myszki na planszy
        x1=0,y1=0;
        while(akcja==false)
        {
            get_event=false;
            al_init_timeout(&timeout,1.0);
            get_event=al_wait_for_event_until(event_queue, &ev,&timeout);
            if(!paused){
            while(get_event==false || (ev.type != ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && ev.type!=ALLEGRO_EVENT_KEY_DOWN))
            {
                al_init_timeout(&timeout,1.0);
                get_event=al_wait_for_event_until(event_queue, &ev,&timeout);
                now=al_get_time();
                if(now-1>temp)
                {
                    rysuj2(zol,display,kwad,font8,(k-2)*20-8,20*w,int(now-start)+sumaczasu,0,1);
                    temp=now;
                }
            }
            }
            if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && paused==false)
            {
                if(ev.mouse.button & 1)//chce sprawdzic pole
            {
                x1=ev.mouse.x;y1=ev.mouse.y;pom=(y1/20)*k+(x1/20);
                cout<<"x1: "<<x1<<" y1: "<<y1<<endl;
                if(x1<k*20 && x1>=0 && y1<w*20 && y1>=0)
                {
                    if(d[pom].byl==0 && d[pom].flag==0){akcja=true;x1/=20;y1/=20;}
                }
            }
            else if(ev.mouse.button & 2)//ustawiam flage lub znak zapytania
            {
                x1=ev.mouse.x;y1=ev.mouse.y;pom=(y1/20)*k+(x1/20);
                if(x1<k*20 && x1>=0 && y1<w*20 && y1>=0 && d[pom].byl==0)//aktualizuje liczbe dostepnych flag
                {
                    if(d[pom].flag==0 && ilemamflag>0){ilemamflag--;ustawflage(d,pom,tile,0);rysuj2(zol,display,kwad,font8,-8,20*w,ilemamflag,0,1);}
                    else if(d[pom].flag==1){ilemamflag++;ustawflage(d,pom,tile,1);rysuj2(zol,display,kwad,font8,-8,20*w,ilemamflag,0,1);}
                    else if(d[pom].flag==2)ustawflage(d,pom,tile,2);
                }
            }
            }
            else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
                    if(ev.keyboard.keycode==ALLEGRO_KEY_ESCAPE){akcja=true;koniec=true;pogrze=true;}
                    else if(ev.keyboard.keycode==ALLEGRO_KEY_P)
                    {
                        if(paused){
                                al_draw_bitmap(kwad,3*(k*20)/5,w*20,0);al_flip_display();
                                start=al_get_time();temp=start;
                                paused=false;cout<<"start"<<endl;
                        }
                        else{
                            sumaczasu=sumaczasu+int(al_get_time()-start);
                            al_draw_text(font8,al_map_rgb(240,6,6),3*(k*20)/5,w*20,0,"P");al_flip_display();
                            paused=true;cout<<"stop"<<endl;
                        }
                    }
                    else if(ev.keyboard.keycode==ALLEGRO_KEY_F2)
                    {
                        akcja=true;koniec=true;pogrze=true;gramydalej=1;
                    }
                    else if(ev.keyboard.keycode==ALLEGRO_KEY_Z)
                    {
                        czasik=al_get_time();
                        if(paused){pauza=1;czasik=start;}else pauza=0;
                        save(typgry,d,k,w,ileb,ilemamflag,pauza,sumaczasu+int(czasik-start));
                    }
            }
        }
        pom=y1*k+x1;
        if(koniec!=true)
        {
        if(d[pom].bomb==1) //warunek konca przegranej gry
            {koniec=true;cout<<"Game over! You lost.";pokazbomby(d,n,20,tile,pom,0);}
        else{
            przeszukaj(d,pom,k,n,tile);al_flip_display();
            if(spr==n-ileb)//warunek konca wygranej gry
            {
                sumaczasu=sumaczasu+int(al_get_time()-start);
                koniec=true;pogrze=true;
                cout<<"You won! "<<sumaczasu<<endl;
                pokazbomby(d,n,20,tile,pom,1);
                al_rest(1.0);
                pom=wstaw_wynik(sumaczasu,wyniki);
                if(pom==1 && typgry!=3)
                {
                    zapiswyn=al_create_display(200,150);
                    al_set_window_title(zapiswyn,"Saper- zapisanie wyniku");
                    zapiszwynik(sumaczasu,typgry,wyniki,16,zapiswyn,event_queue,plama,font8);
                    al_rest(1.0);
                    al_destroy_display(zapiswyn);
                }
            }
        }
        }
    }
    while(pogrze==false) //sprawdzam czy wydano polecenie restartowania gry
    {
        al_wait_for_event(event_queue,&ev);
        if(ev.type==ALLEGRO_EVENT_KEY_DOWN)
        {
            if(ev.keyboard.keycode==ALLEGRO_KEY_F2)gramydalej=1;    //sprawdzam czy mam restartowac gre
            pogrze=true;
        }
    }
    al_destroy_display(display);
    al_destroy_bitmap(kwad);
    al_destroy_bitmap(plama);
    delete[]d;
}
