#include "deklaracjefunkcji.hpp"
//funkcja glowna
int spr=0;
int main()
{
    int k,w,k_dow,w_dow,b_dow,spr=0,ak1,ak2,gramydalej,gramy,czas,bomby,pauza,flagi;
    Dane* inne=new Dane[768];
    FILE *p,*t,*z;
    Wyn Wpocz[5];Wyn Wzaaw[5];Wyn Weksp[5];        //deklaracja struktur z wynikami gier
    for(int i=0;i<5;i++)
    {
        Wpocz[i].czas=9999;Wzaaw[i].czas=9999;Weksp[i].czas=9999;  //przygotowanie struktur
    }
    t=fopen("wynik_pocz.txt","rt");if(t){wczytaj(Wpocz,t);fclose(t);}
    p=fopen("wynik_zaaw.txt","rt");if(p){wczytaj(Wzaaw,p);fclose(p);}
    z=fopen("wynik_eksp.txt","rt");if(z){wczytaj(Weksp,z);fclose(z);}
    al_init();
    al_init_image_addon();
    al_install_mouse();
    al_install_keyboard();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    ALLEGRO_BITMAP *tile;
    ALLEGRO_DISPLAY *Menu,*display;
    tile=al_load_bitmap("saperfile1.bmp");
    if(!al_init())
    {
        al_show_native_message_box(NULL,NULL,NULL,"Could not initialize Allegro 5",NULL,NULL);
    }
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();
    ALLEGRO_FONT *font8 = al_load_font("Meatloaf Solid.ttf",38,NULL),*font=al_create_builtin_font();
    p=NULL;
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    bool jestmenu=false,done=false,done2=false,done3=false; //done- sprawdza czy zamykamy program, done2-sprawdza, czy wychodzimy z submenu
    //ustalam napisy
    char *tab[6],*tab2[5],*tab3[4];
    tab[0]="Graj";tab[1]="Zasady i pomoc";tab[2]="Wczytaj";tab[3]="Statystyki";tab[4]="Wyjdz";tab[5]="Saper";
    tab2[0]="Poczatkujacy";tab2[1]="Zaawansowany";tab2[2]="Ekspert";tab2[3]="Dowolny";tab2[4]="Wybierz poziom trudnosci:";
    tab3[0]="Szerokosc planszy: ";tab3[1]="Wysokosc planszy: ";tab3[2]="Liczba bomb: ";tab3[3]="Ustawienia dowolne:";
    while(done==false)
    {
    if(jestmenu==false){
        Menu=al_create_display(640,480);
        al_set_window_title(Menu,"Saper");jestmenu=true;
    }
    ak1=menu(Menu,event_queue,font8,5,tab);
    switch(ak1)
    {
        case 0:done2=false;
            while(done2==false){ak2=menu(Menu,event_queue,font8,4,tab2);
            switch(ak2)
            {
                case 0:al_destroy_display(Menu);jestmenu=false;
                do
                {   gramydalej=0;
                    display=al_create_display(8*20,10*20);al_set_window_title( display,"Saper");
                    al_set_target_bitmap(al_get_backbuffer(display));al_clear_to_color(al_map_rgb_f(0.5,0.5,0.5));al_flip_display();
                    graj(8,8,64*0.16,tile,display,event_queue,font8,gramydalej,0,0,inne,Wpocz,flagi,pauza,czas);
                }
                while(gramydalej==1);done2=true;break;

                case 1:al_destroy_display(Menu);jestmenu=false;
                do
                {   gramydalej=0;
                    display=al_create_display(16*20,18*20);al_set_window_title( display,"Saper");
                    al_set_target_bitmap(al_get_backbuffer(display));al_clear_to_color(al_map_rgb_f(0.5,0.5,0.5));al_flip_display();
                    graj(16,16,256*0.16,tile,display,event_queue,font8,gramydalej,1,0,inne,Wzaaw,flagi,pauza,czas);
                }
                while(gramydalej==1);done2=true;break;

                case 2:al_destroy_display(Menu);jestmenu=false;
                do
                {   gramydalej=0;
                    display=al_create_display(31*20,18*20);al_set_window_title( display,"Saper");
                    al_set_target_bitmap(al_get_backbuffer(display));al_clear_to_color(al_map_rgb_f(0.5,0.5,0.5));al_flip_display();
                    graj(31,16,496*0.2,tile,display,event_queue,font8,gramydalej,2,0,inne,Weksp,flagi,pauza,czas);
                }
                while(gramydalej==1);done2=true;break;

                case 3:gramydalej=0;gramy=0;dowolnemenu(Menu,event_queue,font8,gramydalej,tab3,gramy,k_dow,w_dow,b_dow);
                if(gramydalej==1)
                {
                    al_destroy_display(Menu);jestmenu=false;
                    do
                    {
                    gramydalej=0;
                    display=al_create_display(k_dow*20,(w_dow+2)*20);al_set_window_title( display,"Saper");
                    al_set_target_bitmap(al_get_backbuffer(display));al_clear_to_color(al_map_rgb_f(0.5,0.5,0.5));al_flip_display();
                    graj(k_dow,w_dow,b_dow,tile,display,event_queue,font8,gramydalej,3,0,inne,Weksp,flagi,pauza,czas);
                    }
                    while(gramydalej==1);done2=true;break;
                }
                break;
                case 99:done2=true;
                default:;
            }
            };break;

        case 1:rules_and_help(Menu,event_queue,font8,font);break;//rules and help

        case 2:done3=false;while(!done3)
        {
            gramy=menu(Menu,event_queue,font8,4,tab2);
            if(gramy==0)p=fopen("pocz.txt","rt");
            else if(gramy==1)p=fopen("zaaw.txt","rt");
            else if(gramy==2)p=fopen("eksp.txt","rt");
            else if(gramy==3)p=fopen("dowo.txt","rt");
            else if(gramy==99)done3=true;
            if(p && done3==false)//jesli jest plik
            {
                al_destroy_display(Menu);jestmenu=false;
                loadgame(p,inne,k,w,bomby,flagi,pauza,czas);
                do
                {   gramydalej=0;
                    display=al_create_display(k*20,(w+2)*20);al_set_window_title( display,"Saper");
                    al_set_target_bitmap(al_get_backbuffer(display));al_clear_to_color(al_map_rgb_f(0.5,0.5,0.5));al_flip_display();
                    switch(gramy)
                    {
                        case 0:graj(k,w,bomby,tile,display,event_queue,font8,gramydalej,gramy,1,inne,Wpocz,flagi,pauza,czas);break;
                        case 1:graj(k,w,bomby,tile,display,event_queue,font8,gramydalej,gramy,1,inne,Wzaaw,flagi,pauza,czas);break;
                        case 2:graj(k,w,bomby,tile,display,event_queue,font8,gramydalej,gramy,1,inne,Weksp,flagi,pauza,czas);break;
                        case 3:graj(k,w,bomby,tile,display,event_queue,font8,gramydalej,gramy,1,inne,Weksp,flagi,pauza,czas);break;
                        default:break;
                    }
                }
                while(gramydalej==1);done3=true;
            }
        };break;//load

        case 3:przegladaj_wyniki(Menu,event_queue,font8,Wpocz,Wzaaw,Weksp);break;//statistics

        case 4:done=true;break;
        case 99:done=true;break;
        default:;
    }
    }
    al_destroy_display(Menu);
    delete[]inne;
    if(Wpocz[0].czas!=9999){p=fopen("wynik_pocz.txt","wt");zapisz(Wpocz,p);fclose(p);}
    if(Wzaaw[0].czas!=9999){t=fopen("wynik_zaaw.txt","wt");zapisz(Wzaaw,t);fclose(t);}
    if(Weksp[0].czas!=9999){z=fopen("wynik_eksp.txt","wt");zapisz(Weksp,z);fclose(z);}
    al_destroy_bitmap(tile);
    al_destroy_font(font8);
    al_destroy_font(font);
}
