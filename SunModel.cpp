//环境分3步
//1 把glut.dll copy 到 system32 目录下
//2 把要用到的头文件包含进来
//3 在project-->set-->link 中加上用到的库 *.lib
//*.h 文件都要copy到\VC98\Include\GL里 用#include <GL/*.h> 引用
//*.lib文件直接copy到\VC98\LIB里

#include <windows.h>
#include <mmsystem.h>
#include <math.h>
#include <glut.h>
#include "rf.h"
#include "mf.h"
#include "draw.h"


#define  DEG_TO_RAD 0.017453

static GLuint texName;
bool   g_bOrbitOn = true;
float  g_fSpeedmodifier = 1.0f;
float  g_fElpasedTime;
double g_dCurrentTime;
double g_dLastTime;

static GLdouble viewer[]= {-sin(10*DEG_TO_RAD),10*cos(10*DEG_TO_RAD), -25}; //初始化视角
static int year =0 ,day = 0;
float angle=0.0;

TEXTUREIMAGE  sunImg;
TEXTUREIMAGE  mercuImg;
TEXTUREIMAGE  venusImg;
TEXTUREIMAGE  earthImg;
TEXTUREIMAGE  moonImg;
TEXTUREIMAGE  marsImg;
TEXTUREIMAGE  jupiterImg;
TEXTUREIMAGE  saturnImg;
TEXTUREIMAGE  uranusImg;
TEXTUREIMAGE  neptuneImg;
TEXTUREIMAGE  skyImg;


#define NUM_TEXTURES    11
GLuint  textureObjects[NUM_TEXTURES];

MATERIAL material[NUM_TEXTURES];
// 光照
LIGHT light =
{
    {0.0, 0.0, 0.0, 1.0},    // 环境光参数
    {1.0, 1.0, 1.0, 1.0},    // 漫射光参数
    {1.0, 1.0, 1.0, 1.0},    // 镜面光参数
    {0.0, 0.0, 0.0, 1.0}    // 光源位置
};
// 材质
MATERIAL materialSpace =                     //空间
{
    {0.4, 0.4, 0.4, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    0.0
};

MATERIAL materialSun =                       //太阳
{
    {100.0, 100.0, 100.0, 20.0},
    {0.8, 0.8, 0.8, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    0.0
};

MATERIAL materialMercu =                     //水星
{
    {0.1, 0.1, 0.1, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    100.0
};

MATERIAL materialVenus =                     //金星
{
    {0.1, 0.1, 0.1, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    100.0
};

MATERIAL materialEarth =                     //地球        
{
    {0.1, 0.1, 0.1, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    100.0
};
MATERIAL materialMoon =                      //月亮
{
    {0.1, 0.1, 0.1, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    0.0
};

MATERIAL materialMars =                      //火星
{
    {0.1, 0.1, 0.1, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    100.0
};

MATERIAL materialJupiter =                    //木星
{
    {0.1, 0.1, 0.1, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    100.0
};

MATERIAL materialSaturn =                     //土星
{
    {0.1, 0.1, 0.1, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    100.0
};

MATERIAL materialUranus =                     //天王星
{
    {0.1, 0.1, 0.1, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    100.0
};

MATERIAL materialNeptune =                    //海王星
{
    {0.1, 0.1, 0.1, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    100.0
};

void init()
{ 
    glClearColor(0.0,0.0,0.0,0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);

    material[0]=materialSun;
    material[1]=materialEarth ;
    material[2]=materialMoon ;
    material[3]=materialSpace ;

    GLfloat light_ambient[]={1.0, 1.0, 1.0, 1.0};
    GLfloat light_diffuse[]={1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[]={1.0, 1.0, 1.0, 1.0};
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
   
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //初始化所有纹理
    mf(sunImg, &textureObjects[0]);
    mf(mercuImg, &textureObjects[1]);
    mf(venusImg, &textureObjects[2]);
    mf(earthImg, &textureObjects[3]);
    mf(moonImg, &textureObjects[4]);
    mf(marsImg, &textureObjects[5]);
    mf(jupiterImg, &textureObjects[6]);
    mf(saturnImg, &textureObjects[7]);
    mf(uranusImg, &textureObjects[8]);
    mf(neptuneImg, &textureObjects[9]);
    mf(skyImg, &textureObjects[10]);
 }  

void reshape(int w,int h)
{
    glViewport(0,0,(GLfloat) w, (GLfloat) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0,(GLfloat)w/(GLfloat)h,1.0,200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(viewer[0],viewer[1],viewer[2],0,0,0,0,0,1);
    
}
void ShutdownRC(void)
{
    //删除纹理
   glDeleteTextures(NUM_TEXTURES, textureObjects);
}


void display(void)
{
    glLoadIdentity();
    
    //设置观察点的位置和观察的方向
    gluLookAt(viewer[0],viewer[1],viewer[2],0,0,0,0,0,1);

    //获得系统时间使太阳系有动态效果
    g_dCurrentTime = timeGetTime();
    g_fElpasedTime = (float)((g_dCurrentTime - g_dLastTime) * 0.001);
    g_dLastTime    = g_dCurrentTime;

    GLfloat light_position[]={0.0, 0.0, 0.0, 1.0};



    static float fSunSpin    = 0.0f;//太阳自转速度  
    
    static float fMercuSpin  = 0.0f;//水星自转速度    
    static float fMercuOrbit = 0.0f;//水星公转速度

    static float fVenusSpin  = 0.0f;//金星自转速度    
    static float fVenusOrbit = 0.0f;//金星公转速度

    static float fEarthSpin  = 0.0f;//地球自转速度    
    static float fEarthOrbit = 0.0f;//地球公转速度

    static float fMoonSpin   = 0.0f;//月亮自转速度    
    static float fMoonOrbit  = 0.0f;//月亮公转速度

    static float fMarsSpin   = 0.0f;//火星自转速度     
    static float fMarsOrbit  = 0.0f;//火星公转速度

    static float fJupiterSpin   = 0.0f;//木星自转速度    
    static float fJupiterOrbit  = 0.0f;//木星公转速度

    static float fSaturnSpin   = 0.0f;//土星自转速度      
    static float fSaturnOrbit  = 0.0f;//土星公转速度
  
    static float fUranusSpin   = 0.0f;//天王星自转速度      
    static float fUranusOrbit  = 0.0f;//天王星公转速度

    static float fNeptuneSpin   = 0.0f;//海王星自转速度      
    static float fNeptuneOrbit  = 0.0f;//海王星公转速度
    
    static float fSpace      = 0.0f;//太空的转动 

    float spaceWidth =18.50;
    float spacedepth =8.0;

    static float MercuToSun=-3.0;//水星离太阳的距离
    static float VenusToSun =-4.5;//金星离太阳的距离
    static float EarthToSun =-6.0;//地球离太阳的距离    
    static float MoonToEarth = -0.9f;//月亮离地球的距离
    static float MarsToSun =-7.0;//火星离太阳的距离
    static float JupiterToSun =-8.0;//木星离太阳的距离
    static float SaturnToSun =-9.0;//土星离太阳的距离
    static float UranusToSun =-10.0;//天王星离太阳的距离
    static float NeptuneToSun =-11.0;//海王星离太阳的距离

    
     if( g_bOrbitOn == true )
     {
         fSunSpin -= g_fSpeedmodifier * (g_fElpasedTime * 10.0f);
       
         fMercuSpin -= g_fSpeedmodifier * (g_fElpasedTime * 15.0f);
         fMercuOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 40.0f);

         fVenusSpin -= g_fSpeedmodifier * (g_fElpasedTime * 10.0f);
         fVenusOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 30.0f);

         fEarthSpin  -= g_fSpeedmodifier * (g_fElpasedTime * 100.0f);
         fEarthOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 20.0f);

         fMoonSpin  -= g_fSpeedmodifier * (g_fElpasedTime * 50.0f);
         fMoonOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 200.0f);

         fMarsSpin -= g_fSpeedmodifier * (g_fElpasedTime * 30.0f);
         fMarsOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 50.0f);

         fJupiterSpin -= g_fSpeedmodifier * (g_fElpasedTime * 90.0f);
         fJupiterOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 35.0f);

         fSaturnSpin -= g_fSpeedmodifier * (g_fElpasedTime * 90.0f);
         fSaturnOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 25.0f);

         fUranusSpin -= g_fSpeedmodifier * (g_fElpasedTime * 70.0f);
         fUranusOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 15.0f);

         fNeptuneSpin -= g_fSpeedmodifier * (g_fElpasedTime * 40.0f);
         fNeptuneOrbit -= g_fSpeedmodifier * (g_fElpasedTime * 5.0f);

    }

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode( GL_MODELVIEW );


    //设置纹理图象
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    //光源位置
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    //各星体的注释大致和太阳和地球的一样

    /************************太阳*******************************/
    //设置太阳材质
    glMaterialfv(GL_FRONT, GL_SPECULAR,material[0].specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, material[0].ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material[0].diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, material[0].shininess);
    glColor3f(1,1,1);

    //太阳的位置，大小，转速，和纹理
    glPushMatrix();
    glRotatef(10,1,0.0,0.0);
    glRotatef(fSunSpin,0.0,1.0,0.0);
    glRotatef(90,1,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D , textureObjects[0]);
    gltDrawSphere(2,200,200); 
    glPopMatrix();
    /*****************************************************************************/

    /************************水星*******************************/
    glColor3f(192,122,24);
    glPushMatrix();
    glRotatef(fMercuOrbit,0.0,1.0,0.0);
    glTranslatef(0.0,0.0,MercuToSun);
    glRotatef(fMercuSpin,0.0,1.0,0.0);
    glRotatef(90,1,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D , textureObjects[1]);
    gltDrawSphere(0.3,150,200); 
    glPopMatrix();    
    
    glBegin(GL_LINE_LOOP);
        for(angle=0;angle<=360;angle++)
            glVertex3f(MercuToSun*sin(DEG_TO_RAD*angle),0,MercuToSun*cos(DEG_TO_RAD*angle));        
    glEnd();
    /*****************************************************************************/

    /************************金星*******************************/
    glColor3f(192,122,24);
    glPushMatrix();
    glRotatef(fVenusOrbit,0.0,1.0,0.0);
    glTranslatef(0.0,0.0,VenusToSun);
    glRotatef(fVenusSpin,0.0,1.0,0.0);
    glRotatef(90,1,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D , textureObjects[2]);
    gltDrawSphere(0.5,150,200); 
    glPopMatrix();    
    
    glBegin(GL_LINE_LOOP);
        for(angle=0;angle<=360;angle++)
            glVertex3f(VenusToSun*sin(DEG_TO_RAD*angle),0,VenusToSun*cos(DEG_TO_RAD*angle));        
    glEnd();
    /*****************************************************************************/

    /************************地球*******************************/
    //设置地球材质
    glMaterialfv(GL_FRONT, GL_SPECULAR,material[1].specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, material[1].ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material[1].diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, material[1].shininess);

    //地球的位置，大小，转速，和纹理
    glPushMatrix();
    glRotatef(fEarthOrbit,0.0,1.0,0.0);
    glTranslatef(0.0,0.0,EarthToSun);
    glRotatef(fEarthSpin,0.0,1.0,0.0);
    glRotatef(10,0,0.0,1.0);
    glRotatef(90,1,0.0,0.0);

    glBindTexture(GL_TEXTURE_2D , textureObjects[3]);
    gltDrawSphere(0.6,100,100); 
    glPopMatrix();

    //地球的轨道
    glBegin(GL_LINE_LOOP);
        for(angle=0;angle<=360;angle++)
            glVertex3f(EarthToSun*sin(DEG_TO_RAD*angle),0,EarthToSun*cos(DEG_TO_RAD*angle));        
    glEnd();
    /*****************************************************************************/

    /************************月亮*******************************/
    glPushMatrix();
    glRotatef( fEarthOrbit, 0.0f, 1.0f, 0.0f ); 
    glTranslatef( 0.0f, 0.0f, EarthToSun);         
    glRotatef( fMoonOrbit, 0.0f, 1.0f, 0.0f );  
    glTranslatef( 0.0f, 0.0f, MoonToEarth );    
    glRotatef( fMoonSpin, 0.0f, 1.0f, 0.0f );  
    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
    glRotatef(90,1,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D , textureObjects[4]);
    gltDrawSphere(0.2,50,20); 
    glPopMatrix();
    /*****************************************************************************/

    /************************火星*******************************/
    glColor3f(192,122,24);
    glPushMatrix();
    glRotatef(fMarsOrbit,0.0,1.0,0.0);
    glTranslatef(0.0,0.0,MarsToSun);
    glRotatef(fMarsSpin,0.0,1.0,0.0);
    glRotatef(90,1,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D , textureObjects[5]);
    gltDrawSphere(0.3,150,200); 
    glPopMatrix();    

    glBegin(GL_LINE_LOOP);
        for(angle=0;angle<=360;angle++)
            glVertex3f(MarsToSun*sin(DEG_TO_RAD*angle),0,MarsToSun*cos(DEG_TO_RAD*angle));        
    glEnd();
    /*****************************************************************************/

    /************************木星*******************************/
    glColor3f(192,122,24);
    glPushMatrix();
    glRotatef(fJupiterOrbit,0.0,1.0,0.0);
    glTranslatef(0.0,0.0,JupiterToSun);
    glRotatef(fJupiterSpin,0.0,1.0,0.0);
    glRotatef(90,1,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D , textureObjects[6]);
    gltDrawSphere(0.7,150,200); 
    glPopMatrix();    
    
    glBegin(GL_LINE_LOOP);
        for(angle=0;angle<=360;angle++)
            glVertex3f(JupiterToSun*sin(DEG_TO_RAD*angle),0,JupiterToSun*cos(DEG_TO_RAD*angle));        
    glEnd();
    /*****************************************************************************/

    /************************土星*******************************/
    glColor3f(192,122,24);
    glPushMatrix();
    glRotatef(fSaturnOrbit,0.0,1.0,0.0);
    glTranslatef(0.0,0.0,SaturnToSun);
    glRotatef(fSaturnSpin,0.0,1.0,0.0);
    glRotatef(90,1,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D , textureObjects[7]);
    gltDrawSphere(0.7,150,200); 
    glPopMatrix();    
    
    glBegin(GL_LINE_LOOP);
        for(angle=0;angle<=360;angle++)
            glVertex3f(SaturnToSun*sin(DEG_TO_RAD*angle),0,SaturnToSun*cos(DEG_TO_RAD*angle));        
    glEnd();
    /*****************************************************************************/

    /************************天王星*******************************/
    glColor3f(192,122,24);
    glPushMatrix();
    glRotatef(fUranusOrbit,0.0,1.0,0.0);
    glTranslatef(0.0,0.0,UranusToSun);
    glRotatef(fUranusSpin,0.0,1.0,0.0);
    glRotatef(90,1,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D , textureObjects[8]);
    gltDrawSphere(0.7,150,200); 
    glPopMatrix();    

    glBegin(GL_LINE_LOOP);
        for(angle=0;angle<=360;angle++)
            glVertex3f(UranusToSun*sin(DEG_TO_RAD*angle),0,UranusToSun*cos(DEG_TO_RAD*angle));        
    glEnd();
    /*****************************************************************************/

    /************************海王星*******************************/
    glColor3f(192,122,24);
    glPushMatrix();
    glRotatef(fNeptuneOrbit,0.0,1.0,0.0);
    glTranslatef(0.0,0.0,NeptuneToSun);
    glRotatef(fNeptuneSpin,0.0,1.0,0.0);
    glRotatef(90,1,0.0,0.0);
    glBindTexture(GL_TEXTURE_2D , textureObjects[9]);
    gltDrawSphere(0.6,150,200); 
    glPopMatrix();    

    glBegin(GL_LINE_LOOP);
        for(angle=0;angle<=360;angle++)
            glVertex3f(NeptuneToSun*sin(DEG_TO_RAD*angle),0,NeptuneToSun*cos(DEG_TO_RAD*angle));        
    glEnd();
    /*****************************************************************************/

    /************************空间背景*******************************/
    //空间材质
    glMaterialfv(GL_FRONT, GL_SPECULAR,material[3].specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, material[3].ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material[3].diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, material[3].shininess);

    //空间的位置，大小，转速，和纹理。
    glPushMatrix();
    glRotatef(fSpace,0.0,0.0,1.0);
    glBindTexture(GL_TEXTURE_2D , textureObjects[10]);
    glRotatef(90,1,1.0,0.0);
    gltDrawSphere(40,100,100);
    glPopMatrix();
    /*****************************************************************************/
    
    glutSwapBuffers();    
    glFlush();

}



void keyboard(unsigned char key ,int x,int y)
{
    switch(key)
    {
    case'+':
        ++g_fSpeedmodifier;
        glutPostRedisplay();
        break;

    case ' ':
        g_bOrbitOn = !g_bOrbitOn;
        glutPostRedisplay();
        break;

    case'-':
        --g_fSpeedmodifier;
        glutPostRedisplay();
        break;

    case'w':
        viewer[0]+= 0.1;
        break;

    case's':
        viewer[0]-= 0.1;
        break;

    case'a':
        viewer[1]+=0.1;
        break;

    case'd':
        viewer[1]-=0.1;
        break;

    case'x':
        viewer[2]+=0.1;
        break;

    case'c':
        viewer[2]-=0.1;
        break;

    default:
        break;

    }
    display();
}

void mouse(int btn, int state, int x, int y)
{

    //鼠标操作

    static  int axis=0;

    if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
    {
        axis++;
        axis=axis%5;
    }
    if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) 
    {
        axis--;
        if(axis==-1)
            axis=4;
    }
        switch(axis)
        {
        case 0:
            viewer[0]=-sin(10*DEG_TO_RAD);
            viewer[1]=cos(10*DEG_TO_RAD);
            viewer[2]=-15;
            break;

        case 1:
            viewer[0]=1;
            viewer[1]=20;
            viewer[2]=1;
            break;
            
        case 2:
            viewer[0]=-sin(10*DEG_TO_RAD);
            viewer[1]=10*cos(10*DEG_TO_RAD);
            viewer[2]=-13;
            break;

        case 3:
            viewer[0]=-5;
            viewer[1]=15;
            viewer[2]=-15;
            break;


        case 4:
            viewer[0]=-sin(10*DEG_TO_RAD);
            viewer[1]=10*cos(10*DEG_TO_RAD);
            viewer[2]=-25;
            break;

        default:
            break;
        }
        display();
    
}
int main(int argc, char**argv)
{
    //读图片
    LoadBmp("image//Sun.bmp"     , &sunImg);
    LoadBmp("image//Mercu.bmp"   , &mercuImg);
    LoadBmp("image//Venus.bmp"   , &venusImg);
    LoadBmp("image//Earth.bmp"   , &earthImg);
    LoadBmp("image//Moon.bmp"    , &moonImg);
    LoadBmp("image//Mars.bmp"    , &marsImg);
    LoadBmp("image//Jupiter.bmp" , &jupiterImg);
    LoadBmp("image//Saturn.bmp"  , &saturnImg);
    LoadBmp("image//Uranus.bmp"  , &uranusImg);
    LoadBmp("image//Neptune.bmp" , &neptuneImg);
    LoadBmp("image//sky.bmp"     , &skyImg);

    /*******************************************************/

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("模拟太阳系");
    init();
    
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMainLoop();
    ShutdownRC();

    //删除所有纹理
    for(int i=0; i<NUM_TEXTURES; i++)
        glDeleteTextures(1, &textureObjects[i]);

    return 0;
}
