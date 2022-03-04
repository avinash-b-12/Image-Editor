#include <stdint.h>
#include <iostream>
#include <graphics.h>
using namespace std;
class Point{
public:
    int x,y;
    Point(int a=0,int b=0){
        x=a;
        y=b;
    }
};

class Pixel:public Point{
public:
    int pix;
    Point topLeft,bottomRight;
    int r,g,b;
    Pixel(int p=0,Point tL=(0,0),Point bR=(0,0)){
        pix=p;
        topLeft.x=tL.x;
        topLeft.y=tL.y;
        bottomRight.x=bR.x;
        bottomRight.y=bR.y;
    }
};
class Quadtree:public Pixel{
public:
    int size,height,width,level,fromleaf,count,c;
    Pixel p;
    Pixel **tree;
    Pixel **mirror;
    Pixel **rotated;
    Pixel **grayScale;
    Pixel **negative;
    Pixel **sepia;
    Quadtree(int w=0,int h=0){
        size=0;
        height=h;
        width=w;
    }
    void Initiator();
    void normal_image();
    void mirror_image(int);
    void rotate_image(Pixel**,int);
    void grayScale_image();
    void negative_image();
    void sepia_image();
    void display(Pixel**,int);
};
void Quadtree::Initiator(){
    int s=height*width;
    level=0;
    while(s>=1){
        size+=s;
        s/=4;
        level++;
    }
    s=width*height;
    tree=new Pixel*[size];
    count=0;
    int i,j;
    for(i=width;i>0;i-=2){
        for(j=height;j>0;j-=2){
            tree[size-1-(4*count)]=new Pixel(getpixel(i,j),Point(i,j),Point(i,j));
            tree[size-2-(4*count)]=new Pixel(getpixel(i,j-1),Point(i,j-1),Point(i,j-1));
            tree[size-3-(4*count)]=new Pixel(getpixel(i-1,j),Point(i-1,j),Point(i-1,j));
            tree[size-4-(4*count)]=new Pixel(getpixel(i-1,j-1),Point(i-1,j-1),Point(i-1,j-1));

            tree[size-1-(4*count)]->r=GetRValue(tree[size-1-(4*count)]->pix);
            tree[size-2-(4*count)]->r=GetRValue(tree[size-2-(4*count)]->pix);
            tree[size-3-(4*count)]->r=GetRValue(tree[size-3-(4*count)]->pix);
            tree[size-4-(4*count)]->r=GetRValue(tree[size-4-(4*count)]->pix);

            tree[size-1-(4*count)]->g=GetGValue(tree[size-1-(4*count)]->pix);
            tree[size-2-(4*count)]->g=GetGValue(tree[size-2-(4*count)]->pix);
            tree[size-3-(4*count)]->g=GetGValue(tree[size-3-(4*count)]->pix);
            tree[size-4-(4*count)]->g=GetGValue(tree[size-4-(4*count)]->pix);

            tree[size-1-(4*count)]->b=GetBValue(tree[size-1-(4*count)]->pix);
            tree[size-2-(4*count)]->b=GetBValue(tree[size-2-(4*count)]->pix);
            tree[size-3-(4*count)]->b=GetBValue(tree[size-3-(4*count)]->pix);
            tree[size-4-(4*count)]->b=GetBValue(tree[size-4-(4*count)]->pix);

            count++;
        }
    }
    fromleaf=size-4-(4*(count-1));
}
void Quadtree::normal_image(){
    int i,j;
    //fromleaf=size-4-(4*(count-1));
    for(i=size-(4*count)-1;i>-1;i--){
        int count[]={1,1,1,1};
        int a[4];
        a[0]=tree[4*i+1]->pix;
        a[1]=tree[4*i+2]->pix;
        a[2]=tree[4*i+3]->pix;
        a[3]=tree[4*i+4]->pix;
        if(a[0]==a[1]){
            count[0]++;
        }
        if(a[0]==a[2]){
            count[0]++;
        }
        if(a[0]==a[3]){
            count[0]++;
        }
        if(a[1]==a[0]){
            count[1]++;
        }
        if(a[1]==a[2]){
            count[1]++;
        }
        if(a[1]==a[3]){
            count[1]++;
        }
        if(a[2]==a[0]){
            count[2]++;
        }
        if(a[2]==a[1]){
            count[2]++;
        }
        if(a[2]==a[3]){
            count[2]++;
        }
        if(a[3]==a[0]){
            count[3]++;
        }
        if(a[3]==a[1]){
            count[3]++;
        }
        if(a[3]==a[2]){
            count[3]++;
        }
        int max;
        max=count[0];
        int in;
        for(in=1;in<4;in++){
            if(count[in]>max){
                max=count[in];
            }
        }
        int index;
        if(count[0]==max){
            index=0;
        }
        else if(count[1]==max){
            index=1;
        }
        else if(count[2]==max){
            index=2;
        }
        else{
            index=3;
        }
        tree[i]=new Pixel(a[index],tree[4*i+1]->topLeft,tree[4*i+4]->bottomRight);
    }
}
void Quadtree::mirror_image(int lvl){
    int count=0;
    int i,j;
    mirror=new Pixel*[size];
    for(i=width;i>0;i-=2){
        for(j=height;j>0;j-=2){
            if(lvl==level-1){
                mirror[fromleaf+(4*count)]=new Pixel(tree[size-1-(4*count)]->pix,Point(height-tree[size-1-(4*count)]->topLeft.x,tree[size-1-(4*count)]->topLeft.y),Point(height-tree[size-1-(4*count)]->bottomRight.x,tree[size-1-(4*count)]->bottomRight.y));
                mirror[fromleaf+1+(4*count)]=new Pixel(tree[size-2-(4*count)]->pix,Point(height-tree[size-2-(4*count)]->topLeft.x,tree[size-2-(4*count)]->topLeft.y),Point(height-tree[size-2-(4*count)]->bottomRight.x,tree[size-2-(4*count)]->bottomRight.y));
                mirror[fromleaf+2+(4*count)]=new Pixel(tree[size-3-(4*count)]->pix,Point(height-tree[size-3-(4*count)]->topLeft.x,tree[size-3-(4*count)]->topLeft.y),Point(height-tree[size-3-(4*count)]->bottomRight.x,tree[size-3-(4*count)]->bottomRight.y));
                mirror[fromleaf+3+(4*count)]=new Pixel(tree[size-4-(4*count)]->pix,Point(height-tree[size-4-(4*count)]->topLeft.x,tree[size-4-(4*count)]->topLeft.y),Point(height-tree[size-4-(4*count)]->bottomRight.x,tree[size-4-(4*count)]->bottomRight.y));
            }
            else{
                mirror[fromleaf+(4*count)]=new Pixel(tree[size-1-(4*count)]->pix,Point(width-i+1,j),Point(width-i+1,j));
                mirror[fromleaf+1+(4*count)]=new Pixel(tree[size-2-(4*count)]->pix,Point(width-i+1,j-1),Point(width-i+1,j-1));
                mirror[fromleaf+2+(4*count)]=new Pixel(tree[size-3-(4*count)]->pix,Point(width-i,j),Point(width-i,j));
                mirror[fromleaf+3+(4*count)]=new Pixel(tree[size-4-(4*count)]->pix,Point(width-i,j-1),Point(width-i,j-1));
            }
            count++;
        }
    }
    for(i=size-(4*count)-1;i>-1;i--){
        int count[]={1,1,1,1};
        int a[4];
        a[0]=mirror[4*i+1]->pix;
        a[1]=mirror[4*i+2]->pix;
        a[2]=mirror[4*i+3]->pix;
        a[3]=mirror[4*i+4]->pix;
        if(a[0]==a[1]){
            count[0]++;
        }
        if(a[0]==a[2]){
            count[0]++;
        }
        if(a[0]==a[3]){
            count[0]++;
        }
        if(a[1]==a[0]){
            count[1]++;
        }
        if(a[1]==a[2]){
            count[1]++;
        }
        if(a[1]==a[3]){
            count[1]++;
        }
        if(a[2]==a[0]){
            count[2]++;
        }
        if(a[2]==a[1]){
            count[2]++;
        }
        if(a[2]==a[3]){
            count[2]++;
        }
        if(a[3]==a[0]){
            count[3]++;
        }
        if(a[3]==a[1]){
            count[3]++;
        }
        if(a[3]==a[2]){
            count[3]++;
        }
        int max;
        max=count[0];
        int in;
        for(in=1;in<4;in++){
            if(count[in]>max){
                max=count[in];
            }
        }
        int index;
        if(count[0]==max){
            index=0;
        }
        else if(count[1]==max){
            index=1;
        }
        else if(count[2]==max){
            index=2;
        }
        else{
            index=3;
        }
        mirror[i]=new Pixel(a[index],mirror[4*i+4]->topLeft,mirror[4*i+1]->bottomRight);
    }
}
void Quadtree::rotate_image(Pixel **tree,int index){
    int count=0;
    int i,j;
    rotated=new Pixel*[size];
    for(i=width;i>0;i-=2){
        for(j=height;j>0;j-=2){
                rotated[fromleaf+(4*count)]=new Pixel(tree[size-1-(4*count)]->pix,Point(tree[size-1-(4*count)]->topLeft.y,(width-tree[size-1-(4*count)]->topLeft.x)),Point(tree[size-1-(4*count)]->bottomRight.y,(width-tree[size-1-(4*count)]->bottomRight.x)));
                rotated[fromleaf+1+(4*count)]=new Pixel(tree[size-2-(4*count)]->pix,Point(tree[size-2-(4*count)]->topLeft.y,(width-tree[size-2-(4*count)]->topLeft.x)),Point(tree[size-2-(4*count)]->bottomRight.y,(width-tree[size-2-(4*count)]->bottomRight.x)));
                rotated[fromleaf+2+(4*count)]=new Pixel(tree[size-3-(4*count)]->pix,Point(tree[size-3-(4*count)]->topLeft.y,(width-tree[size-3-(4*count)]->topLeft.x)),Point(tree[size-3-(4*count)]->bottomRight.y,(width-tree[size-3-(4*count)]->bottomRight.x)));
                rotated[fromleaf+3+(4*count)]=new Pixel(tree[size-4-(4*count)]->pix,Point(tree[size-4-(4*count)]->topLeft.y,(width-tree[size-4-(4*count)]->topLeft.x)),Point(tree[size-4-(4*count)]->bottomRight.y,(width-tree[size-4-(4*count)]->bottomRight.x)));
            count++;
        }
    }
    count=0;
    index--;
    if(index>0){
        Pixel **temp=new Pixel*[size];
        for(i=width;i>0;i-=2){
            for(j=height;j>0;j-=2){
                temp[fromleaf+(4*count)]=new Pixel(tree[size-1-(4*count)]->pix,Point(tree[size-1-(4*count)]->topLeft.y,(width-tree[size-1-(4*count)]->topLeft.x)),Point(tree[size-1-(4*count)]->bottomRight.y,(width-tree[size-1-(4*count)]->bottomRight.x)));
                temp[fromleaf+1+(4*count)]=new Pixel(tree[size-2-(4*count)]->pix,Point(tree[size-2-(4*count)]->topLeft.y,(width-tree[size-2-(4*count)]->topLeft.x)),Point(tree[size-2-(4*count)]->bottomRight.y,(width-tree[size-2-(4*count)]->bottomRight.x)));
                temp[fromleaf+2+(4*count)]=new Pixel(tree[size-3-(4*count)]->pix,Point(tree[size-3-(4*count)]->topLeft.y,(width-tree[size-3-(4*count)]->topLeft.x)),Point(tree[size-3-(4*count)]->bottomRight.y,(width-tree[size-3-(4*count)]->bottomRight.x)));
                temp[fromleaf+3+(4*count)]=new Pixel(tree[size-4-(4*count)]->pix,Point(tree[size-4-(4*count)]->topLeft.y,(width-tree[size-4-(4*count)]->topLeft.x)),Point(tree[size-4-(4*count)]->bottomRight.y,(width-tree[size-4-(4*count)]->bottomRight.x)));
                count++;
            }
        }

        rotate_image(temp,index);
    }
    else{
        return;
    }
}
void Quadtree::grayScale_image(){
    int count=0;
    int i,j;
    grayScale=new Pixel*[size];
    for(i=width;i>0;i-=2){
        for(j=height;j>0;j-=2){
            int avg;

            avg=(tree[size-1-(4*count)]->r+tree[size-1-(4*count)]->g+tree[size-1-(4*count)]->b)/3;
            grayScale[size-1-(4*count)]=new Pixel(RGB(avg,avg,avg),tree[size-1-(4*count)]->topLeft,tree[size-1-(4*count)]->bottomRight);

            avg=(tree[size-2-(4*count)]->r+tree[size-2-(4*count)]->g+tree[size-2-(4*count)]->b)/3;
            grayScale[size-2-(4*count)]=new Pixel(RGB(avg,avg,avg),tree[size-2-(4*count)]->topLeft,tree[size-2-(4*count)]->bottomRight);

            avg=(tree[size-3-(4*count)]->r+tree[size-3-(4*count)]->g+tree[size-3-(4*count)]->b)/3;
            grayScale[size-3-(4*count)]=new Pixel(RGB(avg,avg,avg),tree[size-3-(4*count)]->topLeft,tree[size-3-(4*count)]->bottomRight);

            avg=(tree[size-4-(4*count)]->r+tree[size-4-(4*count)]->g+tree[size-4-(4*count)]->b)/3;
            grayScale[size-4-(4*count)]=new Pixel(RGB(avg,avg,avg),tree[size-4-(4*count)]->topLeft,tree[size-4-(4*count)]->bottomRight);
            count++;
        }
    }
    for(i=size-(4*count)-1;i>-1;i--){
        int count[]={1,1,1,1};
        int a[4];
        a[0]=grayScale[4*i+1]->pix;
        a[1]=grayScale[4*i+2]->pix;
        a[2]=grayScale[4*i+3]->pix;
        a[3]=grayScale[4*i+4]->pix;
        if(a[0]==a[1]){
            count[0]++;
        }
        if(a[0]==a[2]){
            count[0]++;
        }
        if(a[0]==a[3]){
            count[0]++;
        }
        if(a[1]==a[0]){
            count[1]++;
        }
        if(a[1]==a[2]){
            count[1]++;
        }
        if(a[1]==a[3]){
            count[1]++;
        }
        if(a[2]==a[0]){
            count[2]++;
        }
        if(a[2]==a[1]){
            count[2]++;
        }
        if(a[2]==a[3]){
            count[2]++;
        }
        if(a[3]==a[0]){
            count[3]++;
        }
        if(a[3]==a[1]){
            count[3]++;
        }
        if(a[3]==a[2]){
            count[3]++;
        }
        int max;
        max=count[0];
        int in;
        for(in=1;in<4;in++){
            if(count[in]>max){
                max=count[in];
            }
        }
        int index;
        if(count[0]==max){
            index=0;
        }
        else if(count[1]==max){
            index=1;
        }
        else if(count[2]==max){
            index=2;
        }
        else{
            index=3;
        }
        grayScale[i]=new Pixel(a[index],grayScale[4*i+1]->topLeft,grayScale[4*i+4]->bottomRight);
    }
}
void Quadtree::negative_image(){
    negative=new Pixel*[size];
    int count=0;
    int i,j;
    for(i=width;i>0;i-=2){
        for(j=height;j>0;j-=2){
            int R,G,B;
            if(tree[size-1-(4*count)]->pix!=15){
                R=255-tree[size-1-(4*count)]->r;
                G=255-tree[size-1-(4*count)]->g;
                B=255-tree[size-1-(4*count)]->b;
            }
            else{
                R=0;
                G=0;
                B=0;
            }
            negative[size-1-(4*count)]=new Pixel(RGB(R,G,B),tree[size-1-(4*count)]->topLeft,tree[size-1-(4*count)]->bottomRight);
            if(tree[size-2-(4*count)]->pix!=15){
                R=255-tree[size-2-(4*count)]->r;
                G=255-tree[size-2-(4*count)]->g;
                B=255-tree[size-2-(4*count)]->b;
            }
            else{
                R=0;
                G=0;
                B=0;
            }
            negative[size-2-(4*count)]=new Pixel(RGB(R,G,B),tree[size-2-(4*count)]->topLeft,tree[size-2-(4*count)]->bottomRight);
            if(tree[size-3-(4*count)]->pix!=15){
                R=255-tree[size-3-(4*count)]->r;
                G=255-tree[size-3-(4*count)]->g;
                B=255-tree[size-3-(4*count)]->b;
            }
            else{
                R=0;
                G=0;
                B=0;
            }
            negative[size-3-(4*count)]=new Pixel(RGB(R,G,B),tree[size-3-(4*count)]->topLeft,tree[size-3-(4*count)]->bottomRight);
            if(tree[size-4-(4*count)]->pix!=15){
                R=255-tree[size-4-(4*count)]->r;
                G=255-tree[size-4-(4*count)]->g;
                B=255-tree[size-4-(4*count)]->b;
            }
            else{
                R=0;
                G=0;
                B=0;
            }
            negative[size-4-(4*count)]=new Pixel(RGB(R,G,B),tree[size-4-(4*count)]->topLeft,tree[size-4-(4*count)]->bottomRight);
            //tree[size-1-(4*count)]->pix=RGB(tree[size-1-(4*count)]->r,tree[size-1-(4*count)]->g,tree[size-1-(4*count)]->b);
            //tree[size-2-(4*count)]->pix=RGB(tree[size-2-(4*count)]->r,tree[size-2-(4*count)]->g,tree[size-2-(4*count)]->b);
            //tree[size-3-(4*count)]->pix=RGB(tree[size-3-(4*count)]->r,tree[size-3-(4*count)]->g,tree[size-3-(4*count)]->b);
            //tree[size-4-(4*count)]->pix=RGB(tree[size-4-(4*count)]->r,tree[size-4-(4*count)]->g,tree[size-4-(4*count)]->b);
            count++;
        }
    }
    for(i=size-(4*count)-1;i>-1;i--){
        int count[]={1,1,1,1};
        int a[4];
        a[0]=negative[4*i+1]->pix;
        a[1]=negative[4*i+2]->pix;
        a[2]=negative[4*i+3]->pix;
        a[3]=negative[4*i+4]->pix;
        if(a[0]==a[1]){
            count[0]++;
        }
        if(a[0]==a[2]){
            count[0]++;
        }
        if(a[0]==a[3]){
            count[0]++;
        }
        if(a[1]==a[0]){
            count[1]++;
        }
        if(a[1]==a[2]){
            count[1]++;
        }
        if(a[1]==a[3]){
            count[1]++;
        }
        if(a[2]==a[0]){
            count[2]++;
        }
        if(a[2]==a[1]){
            count[2]++;
        }
        if(a[2]==a[3]){
            count[2]++;
        }
        if(a[3]==a[0]){
            count[3]++;
        }
        if(a[3]==a[1]){
            count[3]++;
        }
        if(a[3]==a[2]){
            count[3]++;
        }
        int max;
        max=count[0];
        int in;
        for(in=1;in<4;in++){
            if(count[in]>max){
                max=count[in];
            }
        }
        int index;
        if(count[0]==max){
            index=0;
        }
        else if(count[1]==max){
            index=1;
        }
        else if(count[2]==max){
            index=2;
        }
        else{
            index=3;
        }
        negative[i]=new Pixel(a[index],negative[4*i+1]->topLeft,negative[4*i+4]->bottomRight);
    }
}
void Quadtree::sepia_image(){
    sepia=new Pixel*[size];
    int count=0;
    int i,j;
    for(i=width;i>0;i-=2){
        for(j=height;j>0;j-=2){
            int R,G,B;
            if(tree[size-1-(4*count)]->pix!=15){
                R=0.393*tree[size-1-(4*count)]->r + 0.769*tree[size-1-(4*count)]->g + 0.189*tree[size-1-(4*count)]->b;
                G=0.349*tree[size-1-(4*count)]->r + 0.686*tree[size-1-(4*count)]->g + 0.168*tree[size-1-(4*count)]->b;
                B=0.272*tree[size-1-(4*count)]->r + 0.534*tree[size-1-(4*count)]->g + 0.131*tree[size-1-(4*count)]->b;
                if(R>255)
                    R=255;
                if(G>255)
                    G=255;
                if(B>255)
                    B=255;
            }
            else{
                R=112;
                G=66;
                B=20;
            }
            sepia[size-1-(4*count)]=new Pixel(RGB(R,G,B),tree[size-1-(4*count)]->topLeft,tree[size-1-(4*count)]->bottomRight);
            if(tree[size-2-(4*count)]->pix!=15){
                R=0.393*tree[size-2-(4*count)]->r + 0.769*tree[size-2-(4*count)]->g + 0.189*tree[size-2-(4*count)]->b;
                G=0.349*tree[size-2-(4*count)]->r + 0.686*tree[size-2-(4*count)]->g + 0.168*tree[size-2-(4*count)]->b;
                B=0.272*tree[size-2-(4*count)]->r + 0.534*tree[size-2-(4*count)]->g + 0.131*tree[size-2-(4*count)]->b;
                if(R>255)
                    R=255;
                if(G>255)
                    G=255;
                if(B>255)
                    B=255;
            }
            else{
                R=112;
                G=66;
                B=20;
            }
            sepia[size-2-(4*count)]=new Pixel(RGB(R,G,B),tree[size-2-(4*count)]->topLeft,tree[size-2-(4*count)]->bottomRight);
            if(tree[size-3-(4*count)]->pix!=15){
                R=0.393*tree[size-3-(4*count)]->r + 0.769*tree[size-3-(4*count)]->g + 0.189*tree[size-3-(4*count)]->b;
                G=0.349*tree[size-3-(4*count)]->r + 0.686*tree[size-3-(4*count)]->g + 0.168*tree[size-3-(4*count)]->b;
                B=0.272*tree[size-3-(4*count)]->r + 0.534*tree[size-3-(4*count)]->g + 0.131*tree[size-3-(4*count)]->b;
                if(R>255)
                    R=255;
                if(G>255)
                    G=255;
                if(B>255)
                    B=255;
            }
            else{
                R=112;
                G=66;
                B=20;
            }
            sepia[size-3-(4*count)]=new Pixel(RGB(R,G,B),tree[size-3-(4*count)]->topLeft,tree[size-3-(4*count)]->bottomRight);
            if(tree[size-4-(4*count)]->pix!=15){
                R=0.393*tree[size-4-(4*count)]->r + 0.769*tree[size-4-(4*count)]->g + 0.189*tree[size-4-(4*count)]->b;
                G=0.349*tree[size-4-(4*count)]->r + 0.686*tree[size-4-(4*count)]->g + 0.168*tree[size-4-(4*count)]->b;
                B=0.272*tree[size-4-(4*count)]->r + 0.534*tree[size-4-(4*count)]->g + 0.131*tree[size-4-(4*count)]->b;
                if(R>255)
                    R=255;
                if(G>255)
                    G=255;
                if(B>255)
                    B=255;
            }
            else{
                R=112;
                G=66;
                B=20;

            }
            sepia[size-4-(4*count)]=new Pixel(RGB(R,G,B),tree[size-4-(4*count)]->topLeft,tree[size-4-(4*count)]->bottomRight);
            //tree[size-1-(4*count)]->pix=RGB(tree[size-1-(4*count)]->r,tree[size-1-(4*count)]->g,tree[size-1-(4*count)]->b);
            //tree[size-2-(4*count)]->pix=RGB(tree[size-2-(4*count)]->r,tree[size-2-(4*count)]->g,tree[size-2-(4*count)]->b);
            //tree[size-3-(4*count)]->pix=RGB(tree[size-3-(4*count)]->r,tree[size-3-(4*count)]->g,tree[size-3-(4*count)]->b);
            //tree[size-4-(4*count)]->pix=RGB(tree[size-4-(4*count)]->r,tree[size-4-(4*count)]->g,tree[size-4-(4*count)]->b);
            count++;
        }
    }
    for(i=size-(4*count)-1;i>-1;i--){
        int count[]={1,1,1,1};
        int a[4];
        a[0]=sepia[4*i+1]->pix;
        a[1]=sepia[4*i+2]->pix;
        a[2]=sepia[4*i+3]->pix;
        a[3]=sepia[4*i+4]->pix;
        if(a[0]==a[1]){
            count[0]++;
        }
        if(a[0]==a[2]){
            count[0]++;
        }
        if(a[0]==a[3]){
            count[0]++;
        }
        if(a[1]==a[0]){
            count[1]++;
        }
        if(a[1]==a[2]){
            count[1]++;
        }
        if(a[1]==a[3]){
            count[1]++;
        }
        if(a[2]==a[0]){
            count[2]++;
        }
        if(a[2]==a[1]){
            count[2]++;
        }
        if(a[2]==a[3]){
            count[2]++;
        }
        if(a[3]==a[0]){
            count[3]++;
        }
        if(a[3]==a[1]){
            count[3]++;
        }
        if(a[3]==a[2]){
            count[3]++;
        }
        int max;
        max=count[0];
        int in;
        for(in=1;in<4;in++){
            if(count[in]>max){
                max=count[in];
            }
        }
        int index;
        if(count[0]==max){
            index=0;
        }
        else if(count[1]==max){
            index=1;
        }
        else if(count[2]==max){
            index=2;
        }
        else{
            index=3;
        }
        sepia[i]=new Pixel(a[index],sepia[4*i+1]->topLeft,sepia[4*i+4]->bottomRight);
    }
}
void Quadtree::display(Pixel **tree,int level){
    int start=0,i;
    for(i=0;i<level;i++){
        start=4*start+1;
    }
    if(start>size){
        return;
    }
    delay(1000);
    cleardevice();
    delay(2000);
    for(i=start;i<4*start;i++){
        int x1,y1,x2,y2;
        x1=tree[i]->topLeft.x;
        y1=tree[i]->topLeft.y;
        x2=tree[i]->bottomRight.x;
        y2=tree[i]->bottomRight.y;
        int x,y;
        for(x=x1;x<x2+1;x++){
            for(y=y1;y<y2+1;y++){
                putpixel(x,y,tree[i]->pix);
            }
        }
    }
}
int main(){
    initwindow(256,256,"REAl");
    readimagefile("NewRe.jpg",0,0,256,256);
    delay(1500);
    Quadtree q(256,256);
    q.Initiator();
    /*cout<<"Normal"<<endl<<endl;
    q.normal_image();
    q.display(q.tree,lvl);
    delay(10000);
    cout<<"Mirror"<<endl<<endl;
    q.mirror_image(8);
    q.display(q.mirror,lvl);
    delay(10000);
    cout<<"Rotate"<<endl<<endl;
    q.rotate_image(q.tree,1);
    q.display(q.rotated,lvl);
    delay(10000);
    cout<<"GrayScale"<<endl<<endl;
    q.grayScale_image();
    q.display(q.grayScale,lvl);
    delay(10000);
    cout<<"Negative"<<endl<<endl;
    q.negative_image();
    q.display(q.negative,lvl);
    delay(10000);
    cout<<"Sepia"<<endl<<endl;
    q.sepia_image();
    q.display(q.sepia,lvl);
    delay(10000);*/
    while(true){
    int ch,lvl;
    cout<<"Enter your choice from the below list\n\n";
    cout<<"\t1. Normal Image Manipulation.\n\t2. Image Rotation\n\t3. Mirror Image\n\t4. Gray-Scale of Image\n\t5. Negative of Image\n\t6. Sepia Form of the Image\n\n";
    cout<<"Choice : ";
    cin>>ch;
    switch(ch){
    case 1:
        cout<<"Enter the level to display Image"<<endl;
        cout<<"NOTE : The level of the image determines it's Quality. Higher the level, higher the quality\n\nMax Level : "<<q.level-1<<endl<<endl<<"Level : ";
        cin>>lvl;
        if(lvl<=q.level-1 && lvl>=0){
            cout<<"Normal"<<endl<<endl;
            q.normal_image();
            q.display(q.tree,lvl);
            delay(10000);
        }
        else{
            cout<<"Level has exceeded the maximum value allowed. Re-execute the code.\n\n";
        }
        break;
    case 2:
        int indx;
        cout<<"Enter the index for rotation of the Image.\n\n";
        cin>>indx;
        cout<<"Rotate"<<endl<<endl;
        q.rotate_image(q.tree,indx);
        q.display(q.rotated,q.level-1);
        delay(10000);
        break;
    case 3:
        cout<<"Enter the level to display Image"<<endl;
        cout<<"NOTE : The level of the image determines it's Quality. Higher the level, higher the quality\n\nMax Level : "<<q.level-1<<endl<<endl<<"Level : ";
        cin>>lvl;
        if(lvl<=q.level-1 && lvl>=0){
        cout<<"Mirror"<<endl<<endl;
        q.mirror_image(8);
        q.display(q.mirror,lvl);
        delay(10000);
        }
        else{
            cout<<"Level has exceeded the maximum value allowed. Re-execute the code.\n\n";
        }
        break;
    case 4:
        cout<<"Enter the level to display Image"<<endl;
        cout<<"NOTE : The level of the image determines it's Quality. Higher the level, higher the quality\n\nMax Level : "<<q.level-1<<endl<<endl<<"Level : ";
        cin>>lvl;
        if(lvl<=q.level-1 && lvl>=0){
        cout<<"GrayScale"<<endl<<endl;
        q.grayScale_image();
        q.display(q.grayScale,lvl);
        delay(10000);
        }
        else{
            cout<<"Level has exceeded the maximum value allowed. Re-execute the code.\n\n";
        }
        break;
    case 5:
        cout<<"Enter the level to display Image"<<endl;
        cout<<"NOTE : The level of the image determines it's Quality. Higher the level, higher the quality\n\nMax Level : "<<q.level-1<<endl<<endl<<"Level : ";
        cin>>lvl;
        if(lvl<=q.level-1 && lvl>=0){
        cout<<"Negative"<<endl<<endl;
        q.negative_image();
        q.display(q.negative,lvl);
        delay(10000);
        }
        else{
            cout<<"Level has exceeded the maximum value allowed. Re-execute the code.\n\n";
        }
        break;
    case 6:
        cout<<"Enter the level to display Image"<<endl;
        cout<<"NOTE : The level of the image determines it's Quality. Higher the level, higher the quality\n\nMax Level : "<<q.level-1<<endl<<endl<<"Level : ";
        cin>>lvl;
        if(lvl<=q.level-1 && lvl>=0){
        cout<<"Sepia"<<endl<<endl;
        q.sepia_image();
        q.display(q.sepia,lvl);
        delay(10000);
        }
        else{
            cout<<"Level has exceeded the maximum value allowed. Re-execute the code.\n\n";
        }
        break;
    default:
        cout<<"You have entered wrong choice.\n\n";
    }
    cout<<"Do you want to do further Manipulation on the Image. Enter Y to execute.Any other key to terminate.\n\nExecute ??? :";
    char cont;
    cin>>cont;
    if(cont=='Y' || cont=='y'){
        continue;
    }
    else{
        break;
    }
    }
}
