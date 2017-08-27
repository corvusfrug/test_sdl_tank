#include <iostream>
#include <vector>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

void ModPos(SDL_Rect*,SDL_Rect*,int,char);
void ModAnTow(SDL_Rect*,SDL_Point*,int*,int,int);
void TankShut(SDL_Rect* tow,SDL_Point* cTow ,int* dirTow, SDL_Rect* shImg, SDL_Rect* shut, SDL_Texture*,bool* flag);
void Explosive(SDL_Rect* exp, SDL_Rect* expImg, int,int,bool*);

SDL_Renderer *rnd;
int shutTimer = SDL_GetTicks();
SDL_Texture *testTexture4;
SDL_Texture *testTexture5;
vector<SDL_Rect*> voronki;

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *wnd;
    wnd=SDL_CreateWindow("Tanks",200,200,1024,768,SDL_WINDOW_SHOWN);
    //SDL_Renderer *rnd;
    rnd = SDL_CreateRenderer(wnd,-1,SDL_RENDERER_ACCELERATED);

    SDL_Texture *testTexture = NULL;
    testTexture = IMG_LoadTexture(rnd,"../../texture/54300.png");

    SDL_Texture *testTexture2 = NULL;
    testTexture2 = IMG_LoadTexture(rnd,"../../texture/grunt.bmp");

    SDL_Texture *testTexture3 = NULL;
    testTexture3 = IMG_LoadTexture(rnd,"../../texture/GrenadeExplosion.png");

    testTexture4 = NULL;
    testTexture4 = IMG_LoadTexture(rnd,"../../texture/toon.png");

    testTexture5 = NULL;
    testTexture5 = IMG_LoadTexture(rnd,"../../texture/Nora.png");


    SDL_Rect bg[4];
    for(int i=0;i<4;++i)
    {
        bg[i].w=512;
        bg[i].h=384;
    };
    bg[0].x=bg[0].y=0;
    bg[1].x=512;
    bg[1].y=0;
    bg[2].x=0;
    bg[2].y=384;
    bg[3].x=512;
    bg[3].y=384;

    if(testTexture == NULL) cout << "ERR_IMG\n";
    if(testTexture2 == NULL) cout << "ERR_IMG2\n";
    if(testTexture3 == NULL) cout << "ERR_IMG3\n";
    if(testTexture4 == NULL) cout << "ERR_IMG4\n";

    int timer = SDL_GetTicks();

    int shutTimer = SDL_GetTicks();
    static int mX=0,mY=0;

    //int ExpTimer = SDL_GetTicks();

    SDL_Rect ExpImg;
    ExpImg.x=300;
    ExpImg.y=300;
    ExpImg.w=100;
    ExpImg.h=100;

    SDL_Rect explos;
    explos.x=0;
    explos.y=0;
    explos.w=96;
    explos.h=96;

 ///////////////////////////////

    SDL_Rect shutImg;
    shutImg.x=300;
    shutImg.y=300;
    shutImg.w=20;
    shutImg.h=100;

    SDL_Rect shut;
    shut.x=0;
    shut.y=0;
    shut.w=50;
    shut.h=100;

 ///////////////////////////////

    SDL_Rect Tank1; // position
    Tank1.x=100;
    Tank1.y=100;
    Tank1.w=50;
    Tank1.h=100;


    SDL_Rect tanksTex;
    tanksTex.x=110;
    tanksTex.y=390;
    tanksTex.w=55;
    tanksTex.h=100;

    int tank1Dir=270;
    int tank1DirTemp;

    SDL_Rect tower1;
    tower1.x=103;
    tower1.y=128;
    tower1.w=56;
    tower1.h=110;

    SDL_Rect towerTex;
    towerTex.x=164;
    towerTex.y=390;
    towerTex.w=55;
    towerTex.h=100;

    int tower1Dir=270;
    int tower1DirTemp;

    SDL_Point tower1Center;
    tower1Center.x=22;
    tower1Center.y=22;

    int mouseX;
    int mouseY;

    bool moveForw = false;
    bool moveReve = false;

    bool turnRig = false;
    bool turnLef = false;

    bool ShutFlag = false;
    bool expFlag = false;

    //vector<SDL_Rect*> voronki;


    SDL_Event *evt;

    evt = new SDL_Event();
    bool flag=true;
    //cout << "Start\n";
    //timer = SDL_GetTicks();
    //int shutIter=0;
    while((flag)&&(evt->type!=SDL_QUIT))
    {
        //cout << "Duet " << ++i << endl;
        SDL_RenderClear(rnd);


        for(int i=0;i<4;++i)
        {
            SDL_RenderCopy(rnd,testTexture2,NULL,&bg[i]);
        };

        for(int i=0;i<(int)voronki.size();i++)
            SDL_RenderCopy(rnd,testTexture5,NULL,voronki[i]);

        tank1DirTemp=tank1Dir-270;   //  tank
        tank1DirTemp=tank1DirTemp%360; //

        //tower1DirTemp=tower1Dir-270;
        //tower1DirTemp=tower1DirTemp%360;

        SDL_RenderCopyEx(rnd,testTexture,&tanksTex,&Tank1,tank1DirTemp,NULL,SDL_FLIP_NONE);

        SDL_GetMouseState(&mouseX,&mouseY);

        //cout << "tank1Dir= " << tank1Dir << " tower1DirTemp= " << tower1DirTemp << endl;
        ModAnTow(&tower1,&tower1Center,&tower1Dir,mouseX,mouseY);
        //cout << "tower1Dir= " << tower1Dir << " tower1DirTemp= " << tower1DirTemp << endl;
        tower1DirTemp=tower1Dir-270;
        if(tower1DirTemp<0) tower1DirTemp*=-1;
        if(tower1Dir>270) tower1DirTemp*=-1;
        //if(tower1DirTemp<=0) tower1DirTemp*=-1;
        tower1DirTemp=tower1DirTemp%360;
        //cout << "tank1Dir= " << tank1Dir << " tower1DirTemp= " << tower1DirTemp << endl;
        /*SDL_Point tower1Center;
        tower1Center.x=
        tower1Center.y=*/
        SDL_RenderCopyEx(rnd,testTexture,&towerTex,&tower1,tower1DirTemp,&tower1Center,SDL_FLIP_NONE);

        //cout << "Duet2 " << i-1 << endl;

        SDL_PollEvent(evt);

    ///


        if(evt->type==SDL_MOUSEBUTTONDOWN)
            if(evt->button.button==SDL_BUTTON_LEFT)
                {
                    if(SDL_GetTicks()-shutTimer>1440)
                    {
                        ShutFlag=true;
                        expFlag=true;
                        mX=mouseX;mY=mouseY;
                        shutTimer=SDL_GetTicks();
                    };
                };

        if(evt->type==SDL_KEYDOWN)
            switch(evt->key.keysym.sym)
            {
            case SDLK_1:
                cout << "K1D\n";
                flag=false;
                break;
            case SDLK_w:
            //case SDLk_:
                moveForw=true;
                break;
            case SDLK_s:
                moveReve=true;
                break;
            case SDLK_a:
                turnLef=true;
                break;
            case SDLK_d:
                turnRig=true;
                break;
            default:
                break;
            };

            if(evt->type==SDL_KEYUP)
            switch(evt->key.keysym.sym)
            {
            case SDLK_1:
                cout << "K1D\n";
                flag=false;
                break;
            case SDLK_w:
            //case SDLk_:
                moveForw=false;
                break;
            case SDLK_s:
                moveReve=false;
                break;
            case SDLK_a:
                turnLef=false;
                break;
            case SDLK_d:
                turnRig=false;
                break;
            default:
                break;
            }


            if((SDL_GetTicks()-timer>50)&&(moveForw))
            {
               /* if((SDL_GetTicks()-timer>70)&&(turnLef))
                    tank1Dir-=2;
                if((SDL_GetTicks()-timer>70)&&(turnRig))
                    tank1Dir+=2;*/
                ModPos(&Tank1, &tower1,tank1Dir,'D');
                timer = SDL_GetTicks();
            };
            if((SDL_GetTicks()-timer>50)&&(moveReve))
            {
                /*if((SDL_GetTicks()-timer>50)&&(turnLef))
                    tank1Dir-=2;
                if((SDL_GetTicks()-timer>50)&&(turnRig))
                    tank1Dir+=2;*/
                ModPos(&Tank1, &tower1,tank1Dir,'R');
                timer = SDL_GetTicks();
            };
            //{ModPos(&Tank1, &tower1,tank1Dir,'R'); timer = SDL_GetTicks();};
            if((SDL_GetTicks()-timer>70)&&(turnLef)) {tank1Dir-=2; timer = SDL_GetTicks();};
            if((SDL_GetTicks()-timer>70)&&(turnRig)) {tank1Dir+=2; timer = SDL_GetTicks();};

            if(tank1Dir<0) tank1Dir=360+tank1Dir;
            tank1Dir=tank1Dir%360;


            if((ShutFlag))
            {
                //if(SDL_GetTicks()- shutTimer>600)
                //{
                    TankShut(
                     &tower1,
                     &tower1Center,
                     &tower1DirTemp,
                     &shutImg,
                     &shut,
                     testTexture3,
                     &ShutFlag
                     );
                    // shutTimer=SDL_GetTicks();
               // };
                //shutTimer=SDL_GetTicks();
            };

            if((expFlag))
            {
                SDL_RenderCopy(rnd,testTexture4,&explos,&ExpImg);
                //if(SDL_GetTicks()- shutTimer>600)
                //{
                    Explosive(
                     &explos,
                     &ExpImg,
                     mX,
                     mY,
                     &expFlag
                     );
                    // shutTimer=SDL_GetTicks();
               // };
                //shutTimer=SDL_GetTicks();
            };

           // ModPos(&Tank1, &tower1,tank1Dir,'D');
            //cout << "tankDir " << tankDir << endl;
            ////if(tankDir>=360) tankDir-=360;
            //if(tankDir<0) tankDir=360-tankDir;

        //cout << "Duet3 " << i-1 << endl;

        SDL_RenderPresent(rnd);
        //cout << "Duet4 " << i-1 << endl;
        //timer = SDL_GetTicks();
    };


    for(int i=0;i<(int)voronki.size();i++)
    {delete voronki[i];voronki.pop_back();};
    delete evt;
    SDL_DestroyRenderer(rnd);
    SDL_DestroyTexture(testTexture);
    SDL_DestroyWindow(wnd);
    SDL_Quit();
    //cout << "111" << endl;
    return 0;
}

void ModPos(SDL_Rect *a,SDL_Rect *b, int dir,char command)
{

        int dx=(int)(SDL_cos(dir*(M_PI/180.0))*8.0);
        int dy=(int)(SDL_sin(dir*(M_PI/180.0))*8.0);
        if(dir==0) dy=0;
        if(dir==90) dx=0;
        if(dir==180) dy=0;
        if(dir==270) dx=0;
        //cout << "dx=" << dx << endl;
        //cout << "dy=" << dy << endl;
        /*
        cout << "dir=" << dir << " x=" << a->x << " y=" << a->y << endl;*/
        if(command=='D')
        {
            a->x-=dx;
            a->y-=dy;

            b->x-=dx;
            b->y-=dy;

        } else
        {
            a->x+=dx;
            a->y+=dy;

            b->x+=dx;
            b->y+=dy;


        };
        /*cout << "dir=" << dir << " x=" << a->x << " y=" << a->y << endl;*/
}

void ModAnTow(SDL_Rect* a,SDL_Point* c,int* dir,int mouseX,int mouseY)
{
    int tmp;
    if(mouseX==0) mouseX=2;
    if(mouseY==0) mouseY=1;
    //cout << "mouseX = " << mouseX << " | mouseY = " << mouseY << endl;
    int towCentX =  a->x + c->x;
    int towCentY =  a->y + c->y;
    //cout << "towCentX = " << towCentX << " | towCentY =" << towCentY << endl;

    //cout << "argAtan = " << ((mouseY-towCentY)/(double)(mouseX-towCentX)) << endl;

    double angleRad = SDL_atan((mouseY-towCentY)/(double)(mouseX-towCentX));
    //cout << "angleRad = " << angleRad << " | angleGrad = " << (int) ( (180.0*angleRad)/M_PI ) << endl;
    //tmp = (int) ( (180.0*angleRad)/M_PI )*-2;
    //cout << "dirGrad = " << tmp << endl;
    if((mouseX>=towCentX)&&(mouseY<=towCentY)) tmp = (int) ( (180.0*angleRad)/M_PI )*-1; // 1-й квадрант
    if((mouseX>=towCentX)&&(mouseY>towCentY)) tmp = 360 - (int) ( (180.0*angleRad)/M_PI ); // 4-й квадрант
    if((mouseX<towCentX)&&(mouseY<=towCentY)) tmp = 180 - (int) ( (180.0*angleRad)/M_PI ); // 2-й квадрант
    if((mouseX<towCentX)&&(mouseY>towCentY)) tmp = 180 + (int) ( (180.0*angleRad)/M_PI )*-1; // 3-й квадрант
    if(angleRad==NAN) tmp=270;
    //if((mouseX>=towCentX)&&(mouseY<towCentY)) tmp = 360- (int) ( (180.0*angleRad)/M_PI )*-2;
    //cout << "dirGrad = " << tmp << endl;
    //system("pause");
    *dir=tmp;

}

void TankShut(SDL_Rect* tow,SDL_Point* cTow ,int* dirTow, SDL_Rect* shutImg, SDL_Rect* shut, SDL_Texture* testTexture3,bool* flag)
{
    static int shutIter=0;
    //static int shutTimer = SDL_GetTicks();
    //cout << cTow->x << " | " << cTow->y << endl;
    int centerX=shutImg->w/2.15;
    int centerY=shutImg->h+76;
    SDL_Point tmp;
    tmp.x=centerX;
    tmp.y=centerY;
    shutImg->x=tow->x+(tow->w/4);
    shutImg->y=tow->y-(tow->h/0.71);//0.565
    //cout << centerX << " || " << centerY << endl;
///
    //SDL_RenderCopyEx(rnd,testTexture3,&shut,&shutImg,NULL,NULL,SDL_FLIP_NONE);
    //while(shutIter<=17)
    //if(SDL_GetTicks()- shutTimer>60)
    {
        //SDL_RenderClear(rnd);

        //if(shutIter>17) {shutIter=0;}
        if(SDL_GetTicks()- shutTimer>50)
        {
            shut->x=shut->w*shutIter++;
            shutTimer=SDL_GetTicks();
        };
        SDL_RenderCopyEx(rnd,testTexture3,shut,shutImg,*dirTow+180,&tmp,SDL_FLIP_NONE);
        //SDL_RenderPresent(rnd);
        //shutIter++;
        if(shutIter>17) {shutIter=0;*flag=false;};
        //shutTimer=SDL_GetTicks();
    }
///

}
void Explosive(SDL_Rect* exp, SDL_Rect* expImg, int mouseX, int mouseY, bool* flag)
{
    static int explosIter=0;
    static int ExpTimer = SDL_GetTicks();
    //cout << "BAAM!\n";
    expImg->x=mouseX-expImg->w/2-6;
    expImg->y=mouseY-expImg->h/2-6;

    if(SDL_GetTicks()-ExpTimer>30)
    {
        //cout << "BAAM!\n" << explosIter;
        exp->x=96*explosIter++;
        if(explosIter==10)
        {
            explosIter=0;
            exp->x=96*explosIter++;
            exp->y+=96;
            if(exp->y==96)
            {
                SDL_Rect* tmp = new SDL_Rect;
                tmp->x=mouseX-15;
                tmp->y=mouseY-15;
                tmp->w=30;
                tmp->h=30;
                voronki.push_back(tmp);
            };
            //cout << "BAAM!\n" << exp->y;
            if(exp->y==4*96)
            {
                explosIter=0;
                exp->y=0;
                *flag=false;
            };
        };
        ExpTimer=SDL_GetTicks();
    };
    SDL_RenderCopy(rnd,testTexture4,exp,expImg);
    //SDL_RenderCopy(rnd,testTexture4,&explos,&ExpImg);
    //cout << "BAAM!\n" << exp->y;
}

/*

-lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image


*/
