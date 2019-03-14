#include "deklaracjefunkcji.hpp"
int wybor(char *tab[],ALLEGRO_EVENT_QUEUE *event_queue,ALLEGRO_FONT *font8,int dziel)
{
    bool action=false;int ws=0;
    //al_register_event_source(event_queue, al_get_keyboard_event_source());
    while(action==false)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
        if(ev.keyboard.keycode==ALLEGRO_KEY_DOWN)
        {
            al_draw_textf(font8,al_map_rgb(255,255,0), 320, 100+ws*50,ALLEGRO_ALIGN_CENTER,tab[ws]);
            ws++;
            ws=ws%dziel;
            al_draw_textf(font8,al_map_rgb(255,255,255), 320, 100+ws*50,ALLEGRO_ALIGN_CENTER,tab[ws]);
            al_flip_display();
        }
        else if(ev.keyboard.keycode==ALLEGRO_KEY_UP)
        {
            al_draw_textf(font8,al_map_rgb(255,255,0), 320, 100+ws*50,ALLEGRO_ALIGN_CENTER,tab[ws]);
            ws--;
            if(ws<0)ws=dziel-1;
            al_draw_textf(font8,al_map_rgb(255,255,255), 320, 100+ws*50,ALLEGRO_ALIGN_CENTER,tab[ws]);
            al_flip_display();
        }
        else if(ev.keyboard.keycode==ALLEGRO_KEY_ENTER)
        {
            action=true;return ws;
        }
        else if(ev.keyboard.keycode==ALLEGRO_KEY_ESCAPE)
        {
            action=true;return 99;
        }
        }
        cout<<ws<<endl;
    }
}
int menu(ALLEGRO_DISPLAY *menu,ALLEGRO_EVENT_QUEUE *event_queue,ALLEGRO_FONT *font8,int dziel,char *tab[])
{
    int ws=0,i;
    //inicjalizuje okienko
    al_clear_to_color(al_map_rgb_f(0.5,0.5,0.5));
    for(i=0;i<dziel;i++)al_draw_textf(font8,al_map_rgb(255,255,0), 320, 100+i*50,ALLEGRO_ALIGN_CENTER,tab[i]);
    al_draw_textf(font8,al_map_rgb(0,0,0), 320, 50,ALLEGRO_ALIGN_CENTER,tab[i]);
    al_flip_display();
    i=wybor(tab,event_queue,font8,dziel);
    //al_destroy_event_queue(event_queue);
    return i;
    //al_destroy_display(menu);
}
void rysuj2(ALLEGRO_COLOR kol,ALLEGRO_DISPLAY *display,ALLEGRO_BITMAP *kwad,ALLEGRO_FONT *font8,int x,int y,int liczba,int flaga,int tryb)
{
    al_set_target_bitmap(al_get_backbuffer(display));
    al_draw_bitmap(kwad,x,y,NULL);
    if(tryb==1)al_draw_textf(font8,kol,x+8,y,flaga,"%3d",liczba);
    al_flip_display();
}
void poletext(int znakzachety[],int ilemax[],int *war[],int ilejest[],int& nr_pol,
              ALLEGRO_DISPLAY *menu,ALLEGRO_EVENT_QUEUE *event_queue,ALLEGRO_FONT *font,ALLEGRO_BITMAP *kwad,int& sprawdzam)
{
    int i,wsp_x=400,wsp_y=112;bool koniec=false;
    ALLEGRO_EVENT ev;
    ALLEGRO_COLOR kol=al_map_rgb(114,70,69),bia=al_map_rgb(255,255,255),zol=al_map_rgb(255,255,0),cza=al_map_rgb(0,0,0);
    al_draw_filled_rectangle(400,122+nr_pol*50,424,124+nr_pol*50,kol);al_flip_display();
    while(koniec==false)
    {
        al_wait_for_event(event_queue,&ev);
        if(ev.type==ALLEGRO_EVENT_KEY_DOWN)
        {
            if(ev.keyboard.keycode==ALLEGRO_KEY_DOWN)
                {al_draw_filled_rectangle(400,122+nr_pol*50,424,124+nr_pol*50,bia);nr_pol++;nr_pol=nr_pol%3;
            al_draw_filled_rectangle(400,122+nr_pol*50,424,124+nr_pol*50,kol);al_flip_display();
            }
            else if(ev.keyboard.keycode==ALLEGRO_KEY_UP)
                {al_draw_filled_rectangle(400,122+nr_pol*50,424,124+nr_pol*50,bia);nr_pol--;if(nr_pol<0)nr_pol=2;
            al_draw_filled_rectangle(400,122+nr_pol*50,424,124+nr_pol*50,kol);al_flip_display();
            }
            else if((ev.keyboard.keycode>=27 && ev.keyboard.keycode<=36)|| ev.keyboard.keycode==82
                || ev.keyboard.keycode==83 || ev.keyboard.keycode==63)koniec=true;
            else if(ev.keyboard.keycode==ALLEGRO_KEY_ENTER){sprawdzam=1;koniec=true;}
            else if(ev.keyboard.keycode==ALLEGRO_KEY_ESCAPE){sprawdzam=2;koniec=true;}
        }
    }
            //kilka warunkow  27->0  36->9   left ->82 right->83 backspace->63
            if(ev.keyboard.keycode>=27 && ev.keyboard.keycode<=36 && ilejest[nr_pol]<ilemax[nr_pol])
            {
                for(i=ilejest[nr_pol];i>(znakzachety[nr_pol]-400)/8;i--)
                {
                    war[nr_pol][i]=war[nr_pol][i-1];
                    if(war[nr_pol][i]==99)rysuj2(cza,menu,kwad,font,400+i*8,112+nr_pol*50,war[nr_pol][i],2,0);
                    else rysuj2(cza,menu,kwad,font,400+i*8,112+nr_pol*50,war[nr_pol][i],2,1);
                }
                war[nr_pol][(znakzachety[nr_pol]-400)/8]=ev.keyboard.keycode-27;
                rysuj2(cza,menu,kwad,font,znakzachety[nr_pol],112+nr_pol*50,war[nr_pol][(znakzachety[nr_pol]-400)/8],2,1);
                ilejest[nr_pol]++;
                znakzachety[nr_pol]=znakzachety[nr_pol]+8;
            }
            else if(ev.keyboard.keycode==82 && znakzachety[nr_pol]-8>=400)znakzachety[nr_pol]-=8;
            else if(ev.keyboard.keycode==83 && znakzachety[nr_pol]+8<=424 && znakzachety[nr_pol]+8<=(400+ilejest[nr_pol]*8))
                znakzachety[nr_pol]+=8;
            else if(ev.keyboard.keycode==63)
            {
                if(ilejest[nr_pol]>0 && znakzachety[nr_pol]!=400)
                {
                    for(i=(znakzachety[nr_pol]-400)/8-1;i<ilemax[nr_pol]-1;i++)
                    {
                        war[nr_pol][i]=war[nr_pol][i+1];
                        if(war[nr_pol][i]==99)rysuj2(cza,menu,kwad,font,400+i*8,112+nr_pol*50,war[nr_pol][i],2,0);
                        else rysuj2(cza,menu,kwad,font,400+i*8,112+nr_pol*50,war[nr_pol][i],2,1);
                    }
                    war[nr_pol][ilemax[nr_pol]-1]=99;rysuj2(cza,menu,kwad,font,400+(ilemax[nr_pol]-1)*8,112+nr_pol*50,war[nr_pol][i],2,0);
                    ilejest[nr_pol]--;
                    znakzachety[nr_pol]-=8;
                }
            }
}
int Horner(int *war[],int nr_pola,int ile) //szerokosc planszy -0
{
    int sum=0,i=0;
    while(i<ile && war[nr_pola][i]!=99)
    {
        sum=sum*10+war[nr_pola][i];i++;
    }
    return sum;
}
void dowolnemenu(ALLEGRO_DISPLAY *menu,ALLEGRO_EVENT_QUEUE *event_queue,ALLEGRO_FONT *font8,
                 int& gramydalej,char *tab[],int& gramy,int& k_dow,int& w_dow,int& b_dow)
{
    al_clear_to_color(al_map_rgb_f(0.5,0.5,0.5));
    int i,j,nr_pol=0,znakzachety[3],ilemax[3],ilejest[3]={0};
    int **war=new int*[3];
    ALLEGRO_FONT *font=al_create_builtin_font();
    for(i=0;i<3;i++){
            al_draw_textf(font8,al_map_rgb(255,255,0), 160, 100+i*50,ALLEGRO_ALIGN_LEFT,tab[i]);
            al_draw_filled_rectangle(400, 112+i*50,424,130+i*50,al_map_rgb(255, 255, 255));
            if(i!=2){ilemax[i]=2;war[i]=new int[2];}
            else {ilemax[i]=3;war[i]=new int[3];}
    }
    al_draw_textf(font,al_map_rgb(0,0,0), 460, 112,NULL,"od 8 do 32");
    al_draw_textf(font,al_map_rgb(0,0,0), 460, 162,NULL,"od 8 do 24");
    al_draw_textf(font,al_map_rgb(0,0,0), 460, 212,NULL,"od 1 do 1/3 wszystkich");
    al_draw_textf(font,al_map_rgb(0,0,0), 460, 220,NULL,"kwadratow");
    //wstawiam wartosci 99
    for(i=0;i<4;i++)war[i/2][i%2]=99;
    for(i=0;i<3;i++){war[2][i]=99;znakzachety[i]=400;}
    al_flip_display();
    bool sprawd=false,cos;
    ALLEGRO_EVENT ev;
    ALLEGRO_BITMAP *kwad=al_create_bitmap(8,8);
    al_set_target_bitmap(kwad);
    al_clear_to_color(al_map_rgb(255,255,255));
    gramy=0;
    while(sprawd==false)
    {
        poletext(znakzachety,ilemax,war,ilejest,nr_pol,menu,event_queue,font,kwad,gramy);
        if(gramy==1)
        {
            k_dow=Horner(war,0,2);
            w_dow=Horner(war,1,2);
            b_dow=Horner(war,2,3);
            if(k_dow>=8 && k_dow<=32 && w_dow>=8 && w_dow<=24 && b_dow>=1 && b_dow<=int(0.33*k_dow*w_dow))
            {sprawd=true;gramydalej=1;}
            gramy=0;
        }
        else if(gramy==2)sprawd=true;
    }
    al_destroy_font(font);
    for(i=0;i<3;i++)delete[]war[i];delete[]war;
}
void rules_and_help(ALLEGRO_DISPLAY *menu,ALLEGRO_EVENT_QUEUE *event_queue,ALLEGRO_FONT *font8,ALLEGRO_FONT *font)
{
    ALLEGRO_COLOR zol=al_map_rgb(255,255,0),cza=al_map_rgb(0,0,0);
    al_clear_to_color(al_map_rgb_f(0.5,0.5,0.5));
    al_draw_text(font8,cza,20,50,0,"Saper-zasady");
    al_draw_text(font,zol,20,100,0,
                 "Gra polega na odkrywaniu na planszy poszczegolnych pol");
    al_draw_text(font,zol,20,115,0,"w taki sposob, aby nie natrafic na mine. Na kazdym z odkrytych pol");
    al_draw_text(font,zol,20,130,0,"napisana jest liczba min, ktore bezposrednio stykaja sie");
    al_draw_text(font,zol,20,145,0,"z danym polem (od zera do osmiu). Jesli oznaczymy dane pole flaga,");
    al_draw_text(font,zol,20,160,0,"jest ono zabezpieczone przed odslonieciem,");
    al_draw_text(font8,cza,20,180,0,"Sterowanie w grze:");
    al_draw_text(font8,zol,20,210,0,"wyjscie z menu/okienka gry -> ESC");
    al_draw_text(font8,zol,20,240,0,"restart gry -> F2");
    al_draw_text(font8,zol,20,270,0,"poruszanie sie po menu -> strzalki");
    al_draw_text(font8,zol,20,300,0,"pauza/wznowienie gry -> P");
    al_draw_text(font8,zol,20,330,0,"zapisanie gry -> Z");
    al_draw_text(font8,zol,20,360,0,"zaznaczanie pol -> myszka");
    al_draw_text(font8,zol,20,390,0,"zatwierdzenie/przejscie dalej -> ENTER");
    al_draw_text(font8,zol,20,420,0,"usuwanie znaku -> BACKSPACE");
    al_flip_display();
    ALLEGRO_EVENT ev;
    bool esc=false;
    while(!esc)
    {
        al_wait_for_event(event_queue,&ev);
        if(ev.type==ALLEGRO_EVENT_KEY_DOWN)
        {
            if(ev.keyboard.keycode==ALLEGRO_KEY_ESCAPE)esc=true;
        }
    }
}
