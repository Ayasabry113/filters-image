//Team members:
//Name : Farouk Hamdi Farouk
// ID : 20220241
//Email : faroukosman53@gmail.com
//---------------------------------
//Name : Aya Sabry Abdelazeem
// ID : 20220078
//Email : ayasabry113@gmail.com
//----------------------------------
//Name : Alaa Hassan Mohammed
// ID : 20220065
//Email : Asd010zxc011@gmail.com
//----------------------------------
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <unistd.h>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char image3[SIZE][SIZE];

void loadImage () {
    char imageFileName[100];

    cout << "Please enter file name of the image to process:\n";
    cin >> imageFileName;



    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}
void filter1() {
    //Black & White
    int avg=0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            avg+=image[i][j];
        }
    }
    avg = avg/(SIZE*SIZE);
    cout << avg<<endl;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {



            if (image[i][j] > avg)
                image[i][j] = 255;
            else
                image[i][j] = 0;

        }
    }
}
void loadImage2 () {
    char imageFileName[100];

    cout << "Please enter file name of the second image to process:\n";
    cin >> imageFileName;

    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image2);
}

void saveImage () {
    char imageFileName[100];


    cout << "Enter the target image file name:\n";
    cin >> imageFileName;



    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

void filter2() {
    for(int i = 0; i < 255; i++){
        for(int j = 0; j < 255; j++){
            image[i][j] = 255 - image[i][j];
        }
    }
}

void filter3() {
    //Merge
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            image[i][j]=(image[i][j]+image2[i][j])/2;

        }
    }
}
void filter4(){
    //Flip
    cout << "Please enter h for horizontal flipping or v for vertical flipping\n";
    tow:
    char f;
    cin >> f;
    if(f=='v' or f=='V')
    {
        unsigned char change[SIZE][SIZE];
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< (SIZE/2); j++) {
                change[i][j] = image[i][j];
                image[i][j]=image[i][255-j];
                image[i][255-j]=change[i][j];
            }
        }
    }
    else if(f=='h' or f=='H')
    {
        unsigned char change[SIZE][SIZE];
        for (int i = 0; i < (SIZE/2); i++) {
            for (int j = 0; j< SIZE; j++) {
                change[i][j] = image[i][j];
                image[i][j]=image[255-i][j];
                image[255-i][j]=change[i][j];
            }
        }
    }
    else
    {
        cout << "Error!\nplease enter with right way\n";
        goto tow;
    }
}

void filter5() {
    cout << "please enter d for darken or l for lighten:\n";
    tow:
    char l;
    cin >> l;
    if (l == 'l' or l == 'L') {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = (image[i][j] + 255) / 2;
            }
        }
    } else if (l == 'd' or l == 'D') {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] /= 2;
                if (image[i][j] <= 0) image[i][j] = 0;
            }
        }
    } else {
        cout << "Erorr!\nplease enter with right way\n";
        goto tow;
    }
}
void filter6(){
    //Rotate
    cout << "Choose your rotation degree:\n1-90\n2-180\n3-270\n";
    tow:
    int n;
    cin >> n;
    if(n==1)
    {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = image2[255-j][i];
            }
        }
    }
    else if(n==2){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = image2[255-i][255-j];
            }
        }
    }
    else if(n==3){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = image2[j][255-i];
            }
        }
    }
    else {
        cout << "Error!\nplease enter with right way\n";
        goto tow;
    }
}
void filter7() {
    //detect image edges
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] < 128)
                image[i][j] = 0;
            else
                image[i][j] = 255;
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (abs(image[i][j] - image[i][j + 1]) > 35 || abs(image[i][j] - image[i + 1][j]) > 35) {
                if (abs(image[i][j] - image[i][j + 1]) > 35 || abs(image[i][j] - image[i + 1][j]) > 35) {
                    image[i][j] = 0;
                } else {
                    image[i][j] = 255;
                }

            }
        }
    }
}
void filter8() {
    unsigned char image2[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image2[i][j] = 255;
        }
    }
    int choose;
    cout << "choose quarter 1 or 2 or 3 or 4 :" << endl;
    cin >> choose;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (choose == 1) {
                image2[i][j] = image[i / 2][j / 2];
            } else if (choose == 2) {
                image2[i][j] = image[i / 2][j / 2 + 127];
            } else if (choose == 3) {
                image2[i][j] = image[i / 2 + 127][j / 2];
            } else if (choose == 4) {
                image2[i][j] = image[i / 2 + 127][j / 2 + 127];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = image2[i][j];
            }

        }
    }
}
void filter9(){
    //Shrink
    cout <<"Choose shrink size:\n1-(1/2)\n2-(1/3)\n3-(1/4)\n";
    tow:
    int n;
    cin >> n;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image3[i][j] = 255;
        }
    }
    if(n==1)
    {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image3[i/2][j/2] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = image3[i][j];
            }
        }
    }
    else if(n==2){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image3[i/3][j/3] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = image3[i][j];
            }
        }
    }
    else if(n==3){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image3[i/4][j/4] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = image3[i][j];
            }
        }
    }
    else {
        cout << "Error!\nplease enter with right way\n";
        goto tow;
    }
}
void filterA(){
    //Mirror
    cout << "Please enter l for left or r for right or u for upper or d for down:\n";
    tow:
    char m;
    cin >> m;
    if(m=='d' or m == 'D')
    {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = image[SIZE-i][j];
            }
        }
    }
    if(m=='l' or m == 'L')
    {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][SIZE-j] = image[i][j];
            }
        }
    }
    else if(m=='r' or m=='R')
    {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = image[i][SIZE-j];
            }
        }
    }
    else if(m=='u' or m=='U')
    {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[SIZE-i][j] = image[i][j];
            }
        }
    }
    else {
        cout << "Error!\nplease enter with right way\n";
        goto tow;
    }

}
void filterB(){
    int quarter1, quarter2, quarter3, quarter4;
    cout << "enter ordering :\n";
    cin >> quarter1 >> quarter2 >> quarter3 >> quarter4;
    for(int i = 0; i < 127; i++){
        for(int j = 0; j < 127; j++){
            if(quarter1 == 1){
                image2[i][j] = image[i][j];
            }
            else if(quarter1 == 2){
                image2[i][j] = image[i][j+127];
            }
            else if(quarter1 == 3){
                image2[i][j] = image[i+127][j];
            }
            else if(quarter1 == 4){
                image2[i][j] = image[i+127][j+127];
            }
        }
    }
    for(int i = 0; i < 127; i++) {
        for (int j = 127; j < 256; j++) {
            if (quarter2 == 1) {
                image2[i][j] = image[i][j-127];
            } else if (quarter2 == 2) {
                image2[i][j] = image[i][j];
            } else if (quarter2 == 3) {
                image2[i][j] = image[i+127][j-127];
            } else if (quarter2 == 4) {
                image2[i][j] = image[i+127][j];
            }
        }
    }
    for(int i = 127; i < 256; i++) {
        for (int j = 0; j < 127; j++) {
            if (quarter3 == 1) {
                image2[i][j] = image[i-127][j];
            } else if (quarter3 == 2) {
                image2[i][j] = image[i-127][j+127];
            } else if (quarter3 == 3) {
                image2[i][j] = image[i][j];
            } else if (quarter3 == 4) {
                image2[i][j] = image[i][j+127];
            }
        }
    }
    for(int i = 127; i < 256; i++) {
        for (int j = 127; j < 256; j++) {
            if (quarter4 == 1) {
                image2[i][j] = image[i-127][j-127];
            } else if (quarter4 == 2) {
                image2[i][j]  = image[i-127][j];
            } else if (quarter4 == 3) {
                image2[i][j]  = image[i][j-127];
            } else if (quarter4 == 4) {
                image2[i][j]  = image[i][j];
            }
        }
    }
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            image[i][j] = image2[i][j];
        }
    }

}
void filterC(){
    //Blur
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if(i==0 and j==0)
            {
                image2[i][j]= (image[i][j]+image[i][j+1]+image[i+1][j]+image[i+1][j+1])/4;
            }
            else if(j==0)
            {
                image2[i][j] = (image[i][j]+image[i][j+1]+image[i+1][j]+image[i+1][j+1]+image[i-1][j]+image[i-1][j+1])/6;
            }
            else if(i==0)
            {
                image2[i][j] = (image[i][j]+image[i][j+1]+image[i+1][j]+image[i+1][j+1]+image[i][j-1]+image[i+1][j-1])/6;
            }
            else
            {
                image2[i][j] = (image[i][j]+image[i][j+1]+image[i+1][j]+image[i+1][j+1]+image[i][j-1]+image[i+1][j-1]+image[i-1][j]+image[i-1][j-1]+image[i-1][j+1])/9;
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = image2[i][j];
        }
    }
}
void filterD(){
    //cropImage
    cout<<"Please enter x y l w: ";
    int x,y,l,w;
    cin>>x>>y>>l>>w;
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(i>x+l/2 || i<abs(x-l/2) || j>y+w/2 || j<abs(y-w/2))
                image[i][j]=255;
        }
    }
}
void filterE() {
    cout << "Please enter the angel of skew:\n";
    double ang;
    cin >> ang;
    ang = (ang * 22.0) / (180.0 * 7.0);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image2[i][j] = 255;
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int ind = j;
            if (tan(ang) < 0) {
                ind += (j - i) * tan(ang);
            } else
                ind += (SIZE - (i + j)) * tan(ang);
            image2[i][ind] = image[i][j];
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = image2[i][j];
        }
    }
}
void filterF(){
        //Skew Up
        cout << "Please enter the angel of skew:\n";
        double ang;
        cin >> ang;
        ang = (ang * 22.0)/(180.0*7.0);
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image2[i][j] = 255;
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                int ind = i;
                if (tan(ang) < 0) {
                    ind += (j-i) * tan(-ang);
                } else
                    ind += (SIZE-(i+j)) * tan(ang);
                image2[ind][j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = image2[i][j];
            }
        }
}
int main()
    {
        char n;
        while (true)
        {
            cout << "Please select a filter to apply or 0 to exit:\n"
                    "1-	Black & White Filter\n"
                    "2-	Invert Filter\n"
                    "3-	Merge Filter\n"
                    "4-	Flip Image\n"
                    "5-	Darken and Lighten Image\n"
                    "6-	Rotate Image\n"
                    "7-	Detect Image Edges\n"
                    "8-	Enlarge Image\n"
                    "9-	Shrink Image\n"
                    "a-	Mirror 1/2 Image\n"
                    "b-	Shuffle Image\n"
                    "c-	Blur Image\n"
                    "d-	Crop Image\n"
                    "e-	Skew Image Right\n"
                    "f-	Skew Image Up\n"
                    "s- Save the image to a file\n"
                    "0-	Exit\n";
            cin >> n;
            switch (n) {
                case '0':
                    return 0;
                case '1':
                    loadImage();
                    filter1();
                    break;
                case '2':
                    loadImage();
                    filter2();
                    break;
                case '3':
                    loadImage();
                    loadImage2();
                    filter3();
                    break;
                case '4':
                    loadImage();
                    filter4();
                    break;
                case '5':
                    loadImage();
                    filter5();
                    break;
                case '6':
                    loadImage2();
                    filter6();
                    break;
                case '7':
                    loadImage();
                    filter7();
                    break;
                case '8':
                    loadImage();
                    filter8();
                    break;
                case '9':
                    loadImage();
                    filter9();
                    break;
                case 'a':
                    loadImage();
                    filterA();
                    break;
                case 'b':
                    loadImage();
                    filterB();
                    break;
                case 'c':
                    loadImage();
                    filterC();
                    break;
                case 'd':
                    loadImage();
                    filterD();
                    break;
                case 'e':
                    loadImage();
                    filterE();
                    break;
                case 'f':
                    loadImage();
                    filterF();
                    break;
                case 's':
                    saveImage();
                    break;
            }
        }
    }