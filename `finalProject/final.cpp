/*
---------------------------------------------------------
---------------MUHTEREM OGUZHAN YILDIRIM-----------------
---------------------------------------------------------
*/



#include <stdio.h>
#include <dos.h>
#include <iostream>

union REGS regin,regout;

void setScreenMode()
{
    regin.x.ax=0x0012;
    int86(0x10,&regin,&regout);
}

void cleanScreen()
{

  regin.h.ah=0x06;
  regin.h.al=0x00;
  /*
  regin.h.bh=0x07;
   */
  regin.h.ch=0x00;
  regin.h.cl=0x00;
  regin.h.dh=24;
  regin.h.dl=79;

  int86(0x10,&regin,&regout);
   regin.h.ah=0x2;
  regin.h.bh=0x0;
  regin.h.dl=0x0;
  regin.h.dh=0x0;
   int86(0x10,&regin,&regout);
}

void waitKey()
{
 regin.h.ah=07;
 int86(0x21,&regin,&regout);
}
void putPixel(int x,int y){
  //union REGS regin,regout;
  regin.h.ah=0x0c;
  regin.h.al=0x01;
  regin.h.bl=0x00;
  regin.x.cx=x;
  regin.x.dx=y;
  int86(0x10,&regin,&regout);

}

int calcHorizantalLength(int vNum)
{
 if(vNum==0 || vNum==1)
 {
  vNum=2;
 }
 double x=(600.0/(vNum-1));
 int z=(int)x;
 double tmp=x-z;
 int kayma=tmp*(vNum-1);
 int length=600-kayma;
 return length;
}

int calcVerticalLength(int hNum)
{
 if(hNum==0 || hNum==1)
 {
  hNum=2;
 }
 double y=(440.0/(hNum-1));
 int z=(int)y;
 double tmp=y-z;
 int kayma=tmp*(hNum-1);
 int length=440-kayma;
 return length;
}

int calcSpace(int Num,int length)

{
 if(Num==0 || Num==1)
 {
  Num=2;
 }
return (length/(Num-1));
}

void drawVerticalLine(int x,int vLength)
{

for(int i=20;i<=vLength+20;i++)
{
putPixel(x,i);
}
}

void drawHorizantalLine(int y,int hLength)
{

for(int j=20;j<=hLength+20;j++)
{
putPixel(j,y);
}
}

void verticalGrid(int vNum,int vSpace,int vlength)
{
	int space=20;
	for(int k=0;k<vNum;k++)
   {

       drawVerticalLine(space,vlength);
     space+=vSpace ;

   }
}

void horizantalGrid(int hNum,int hSpace,int hlength)
{
	int space=20;
	for(int k=0;k<hNum;k++)
   {

     drawHorizantalLine(space,hlength);


     space+=hSpace ;

   }
}


main()
{
    setScreenMode();

  int vNum,hNum;
  take1:
  cout << "Please input the number of your vertical lines? (0-99):  ";
  cin >> vNum;
     while(!cin)
   {
     cout << "error input only can be 0-99 integer"<<"\n";
     cin.clear();
     cin.ignore(22, '\n');
      goto take1;

   }
   if(vNum<0 || vNum>99)
   {
     cout << "error input only can be 0-99 integer"<<"\n";
      goto take1;
   }

  take2:
  cout << "Please input the number of your horizontal lines? (0-99): ";
  cin >> hNum;
    while(!cin)
   {
     cout << "error input only can be 0-99 integer"<<"\n";
     cin.clear();
     cin.ignore(22, '\n');
      goto take2;

   }
      if(hNum<0 || hNum>99)
   {
   cout << "error input only can be 0-99 integer"<<"\n";
      goto take2;
   }
  cout << "Now I will draw your " << vNum  <<"x" << hNum <<" grid. Thank you :) "<< ".\n";
  cout << "First I am going to clean the screen and then start drawing your Grid."<< ".\n";
  cout << "Please press any key to start the drawing operation! ";

  waitKey();
  cleanScreen();
  //vNum=5;
  //hNum=5;
  int vLength=calcVerticalLength(hNum);
  int hLength=calcHorizantalLength(vNum);
  int vSpace=calcSpace(vNum,hLength);
  int hSpace=calcSpace(hNum,vLength);
  verticalGrid(vNum,vSpace,vLength);
  horizantalGrid(hNum,hSpace,hLength);


}
