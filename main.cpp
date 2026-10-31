#include "Image_Class.h"
#include <iostream>
#include <string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std ;

/**
====================================================
============ CS213 - Assignment 1 - Part 1 ===============

Team Members:
1.Name: Zeyad Amr Mohamed
   ID: 20250252

2. Name: Kareem Tamer Samir
   ID: 20250483

3. Name: Mohamed Salah Mohamed
   ID: 20250569

4. Name: Youssef Adly Fathy
   ID: 20250777

Section: ............

Filters:
Filter 1: GrayScale            -> Done by: Zeyad Amr Mohamed
Filter 2: BlackAndWhite        -> Done by: kareem tamer samir
Filter 3: Invert               -> Done by: Mohamed Salah Mohamed
Filter 4: Frame                -> Done by: Youssef Adly Fathy
Filter 5: Flip                 -> Done by: Zeyad Amr Mohamed
Filter 6: Rotate               -> Done by: kareem tamer samir
Filter 7: Darken and Lighten   -> Done by: Mohamed Salah Mohamed
Filter 8: Resize               -> Done by: Youssef Adly Fathy
Filter 9: Merge                -> Done by: Zeyad Amr Mohamed
Filter 10: Edge Detection      -> Done by: kareem tamer samir
Filter 11: Crop                -> Done by: Mohamed Salah Mohamed
Filter 12: Blur                -> Done by: Youssef Adly Fathy
Filter 13: Land of wano        -> Done by: Zeyad Amr Mohamed
Filter 14: Uncle wanno         -> Done by: kareem tamer samir
Filter 15: Purple luffy        -> Done by: Mohamed Salah Mohamed
Filter 16: Infirared           -> Done by: Youssef Adly Fathy

File Description:
This file contains the implementation of Part 2
filters and a console menu to select them.

Video Link:
https://youtu.be/CRgbcE6o94Y

Doc link:
https://drive.google.com/file/d/1qSMGGjoWlOEuvOBmBIGVHZvUJd1tax9-/view
====================================================
**/


/*
Name: Youssef Adly Fathy
ID: 20250777
made :Frame & Resize Filters
Functions Description:

- inputvalidation        -> to validate that the input is only numbers in menus.
- checkColorBoundry      -> Clamp color values between 0 - 255 to ensure safety.
- setPixelColor          -> Takes a pixel (x, y) and RGB array, checks boundaries to prevent crashes and change the color.
- getPixelColor          -> Retrieves pixel color values from an image safely with bounds checking.
- setSimpleFrameColor    -> Fills the entire imaged with a solid color.
- checkHexadecimalColor  -> Checks and cleans hexadecimal color string characters.
- hexadecimalColor       -> Converts hexadecimal color strings into an [R, G, B] integer array.
- simpleFrameImage       -> Creates a framed version of the image with custom thickness and colors.
- frameChoose            -> Console menu interface for selecting frame options.
- resizeImageLogic       -> Computes width/height ratios and handles the core resizing logic.
- resizeImage            -> Console menu interface for entering new dimensions and triggering resize.
- saveImage              -> ask to save in same file or new or doesn't save.
- Vertical  , Horizontal ,Net Black ,Net white
                         -> put 4 designs of frame.
- imageToFrame           -> put the source image inside Frame image.

Filters:
Filter 4: Frame
Filter 8: Resize
Filter 12: Blur
Filter 16: Infirared

*/
/*
Function: inputValidation
Purpose : get the string input and cast it to short for different switch cases across the whole project
Inputs  : string (Geference for speed and memory allocation)
 */
short inputValidation(string &input) {
    string newInput ;
    for (char c : input) {
        if (c >= '0' && c <= '9') {
            newInput += c ;
        }
    }
    if (!newInput.empty()) {
        if (newInput.length() > 4) {
            newInput = newInput.substr(0, 5); // Take only the first 4 digits to prevent overflow for short
        }
        return static_cast<short>(stoi(newInput)) ;
    }
    return -1 ;
}
// constraint on value of color to be between 0 and 255
void checkColorBoundry(short* color)
{
    for (int i = 0 ; i < 3 ; i++) {
        if (color[i] < 0 ) {
            color[i] = 0 ;
        }
        if (color[i] > 255 ) {
            color[i] = 255 ;
        }
    }
}
// Function: setPixelColor
// Purpose : Safely sets the RGB color of a specific pixel at (x, y) with bounds checking
void setPixelColor(Image &img , const short &x, const short &y, const short* color) {
    if (x < 0 || x >= img.width || y < 0 || y >= img.height) {
        cerr << " Image index out of bounds." << endl ;
        return ;
    }
    short scopColor[]={color[0],color[1],color[2]}; // Create a copy of the color array to avoid modifying the original
    checkColorBoundry(scopColor);
    for(int i = 0 ; i < 3 ; i++) {
        img(x,y,i) = scopColor[i];
    }
}
// Function: getPixelColor
// Purpose : Safely gets the RGB color of a specific pixel at (x, y) with bounds checking
void getPixelColor(const Image &img,const short &x,const short &y, short* color) {
    if (x < 0 || x >= img.width || y < 0 || y >= img.height) {
        cerr << " Image index out of bounds." << endl ;
        return ;
    }

    for (int i = 0 ; i < 3 ; i++) {
        color[i] = img(x,y,i) ;
    }
    checkColorBoundry(color) ;
}
/*
Function: setSimpleFrameColor
Purpose : Fills the entire image with a solid color, effectively creating a simple frame.
Inputs  : image (Reference to the Image object to be filled)
*/
void setSimpleFrameColor(Image &image , const short* color) {
    for (int x = 0 ; x < image.width ; x++) {
        for (int y = 0 ; y < image.height ; y++) {
            setPixelColor(image,x,y,color) ;
        }
    }
}
/*
Function: imageToFrame
Purpose : Fills the entire image with a solid color, effectively creating a simple frame.
Inputs  : image (Reference to the Image object to be filled)
*/
void imageToFrame(const Image &image,Image &copyImage,const short &frameInPixels) {
    short color[3] = {0} ;
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            getPixelColor(image,i,j,color);
            setPixelColor(copyImage,i + frameInPixels,j + frameInPixels,color) ;
        }
    }
}
/*
Function: checkHexadecimalColor
Purpose : check each char in string to make sure it's in hexadecimal range.
Inputs  : string (Reference for speed and memory allocation)
*/
void checkHexadecimalColor(string &colorstr) {
    for (char &c : colorstr) {
        if (c >= '0' && c <= '9' || c >= 'a' && c <= 'f'|| c >= 'A' && c <= 'F') {}
        else {
            c = 'F';
        }
    }
}
/*
Function: hexadecimalColor
Purpose : check each first char if "#" and take 6 chars take 1st 2 for R 2nd 2 for G the last two for B.
Inputs  : string (Reference for speed and memory allocation) , color array (Reference for modification)
*/
void hexadecimalColor(string &color, short* intColor) {
    if (color[0] == '#' ) {
        color = color.substr(1) ;
    }
    checkHexadecimalColor(color);
    intColor[0] = static_cast<short>(stoi( color.substr(0,2),nullptr,16)) ;
    intColor[1] =  static_cast<short>(stoi(color.substr(2,2),nullptr,16)) ;
    intColor[2] =  static_cast<short>(stoi(color.substr(4,2),nullptr,16)) ;
}
/*
Function: simpleFrameImage
Purpose : take the original image and make a new bigger image and fill the original on it to prevent data lose.
Inputs  : image (Reference for speed and memory allocation)
*/
Image simpleFrameImage(const Image &image) {
    short color[3] ;
    string colorString ;
    string input;
    short choice = 0 ;
    cout << " Enter Thickness Frame Pixels : " ;
    cin >> input;
    short frameInPixels = inputValidation(input) ;
    if (frameInPixels <= 0 ) {
        cout<<"INVALID FRAME \n- APPLYING DEFULT: 50 px\n";
        frameInPixels = 50 ;
    }
    else if (frameInPixels > 100) {
        cout<<"MAXIMUM FRAME IS: 100 px\n- APPLYING: 100 px\n";
        frameInPixels = 100 ;
    }
    short width  = static_cast<short>(image.width  + frameInPixels * 2);
    short height = static_cast<short>(image.height + frameInPixels * 2);
        cout << "CHOOSE THE FRAME COLOR\n";
        cout << "1. Blue\n";
        cout << "2. Green\n";
        cout << "3. red\n";
        cout << "4. yellow\n";
        cout << "5. black\n";
        cout << "6. white\n";
        cout << "7. Write HEXADECIMAL\n";
        cout << "8. EXIT\n";
        cin>>input;
        choice = inputValidation(input) ;
        switch (choice) {
            case 1 :
                colorString = "0000ff";
                break;
            case 2 :
                colorString = "00ff00";
                break;
            case 3 :
                colorString = "ff0000";
                break;
            case 4 :
                colorString = "ffff00";
                break;
            case 5 :
                colorString = "000000";
                break;
            case 6 :
                colorString = "ffffff";
                break;
            case 7 : {
                cout << " Enter frame color in Hexadecimal : \n you can write (Q) to set to default\n" ;
                cin >> colorString ;
                if (colorString.size()<6) {
                    colorString = "ff0000";
                }
                if (colorString.size() >= 7) {
                    colorString = colorString.substr(0,7);
                }
                break;
            }
            case 8 :
                return image;
            default :
                cout<<"INVALID CHOICE\n";
                return image;
        }

    hexadecimalColor(colorString,color) ;
    Image imageCopy(width,height) ;
    setSimpleFrameColor(imageCopy,color) ;
    imageToFrame(image,imageCopy,frameInPixels);
    return imageCopy ;
}
/*
Function: verticalFancy
Purpose : make frame has vertical black & white lines.
Inputs  : image (Reference for speed and memory allocation)
*/
Image verticalFancy(const Image &image) {
    short frameInPixels =50 ;
    short whiteColor[] = {255,255,255};
    short blackColor[] = {0,0,0};
    Image copyImage(image.width+(frameInPixels*2),image.height+(frameInPixels*2)) ;
    setSimpleFrameColor(copyImage,whiteColor);
    for (int x = 0 ; x < copyImage.width ; x++) {
        if ((x/5)%2==0) {
        for (int y = 0 ; y < copyImage.height ; y++) {
            setPixelColor(copyImage,x,y,blackColor) ;
        }
        }
    }
    imageToFrame(image,copyImage,frameInPixels) ;
    return copyImage ;
}
/*
Function: horizontalFancy
Purpose : make frame has horizontal black & white lines.
Inputs  : image (Reference for speed and memory allocation)
*/
Image horizontalFancy(const Image &image) {
    short frameInPixels =50 ;
    short whiteColor[] = {255,255,255};
    short blackColor[] = {0,0,0};
    Image copyImage(image.width+(frameInPixels*2),image.height+(frameInPixels*2)) ;
    setSimpleFrameColor(copyImage,whiteColor);
    for (int x = 0 ; x < copyImage.width ; x++) {
        for (int y = 0 ; y < copyImage.height ; y++) {
            if ((y/5)%2==0) {
                setPixelColor(copyImage,x,y,blackColor) ;
            }
        }
    }
    imageToFrame(image,copyImage,frameInPixels) ;
    return copyImage ;
}
/*
Function: NetImageBlack
Purpose : make frame has black net.
Inputs  : image (Reference for speed and memory allocation)
*/
Image NetImageBlack(const Image &image) {
    short frameInPixels =50 ;
    short whiteColor[] = {255,255,255};
    short blackColor[] = {0,0,0};
    Image copyImage(image.width+(frameInPixels*2),image.height+(frameInPixels*2)) ;
    setSimpleFrameColor(copyImage,blackColor);
    for (int x = 0 ; x < copyImage.width ; x++) {
        if ((x/5)%2==0) {
            for (int y = 0 ; y < copyImage.height ; y++) {
                if ((y/5)%2==0) {
                    setPixelColor(copyImage,x,y,whiteColor) ;
                }
            }
        }
    }
    imageToFrame(image,copyImage,frameInPixels) ;
    return copyImage ;
}
/*
Function: NetImageWhite
Purpose : make frame has white net.
Inputs  : image (Reference for speed and memory allocation)
*/
Image NetImageWhite(const Image &image) {
    short frameInPixels =50 ;
    short whiteColor[] = {255,255,255};
    short blackColor[] = {0,0,0};
    Image copyImage(image.width+(frameInPixels*2),image.height+(frameInPixels*2)) ;
    setSimpleFrameColor(copyImage,whiteColor);
    for (int x = 0 ; x < copyImage.width ; x++) {
        if ((x/5)%2==0) {
            for (int y = 0 ; y < copyImage.height ; y++) {
                if ((y/5)%2==0) {
                    setPixelColor(copyImage,x,y,blackColor) ;
                }
            }
        }
    }
    imageToFrame(image,copyImage,frameInPixels) ;
    return copyImage ;
}
/*
Function: fancyFrameChoose
Purpose : handle user input.
Inputs  : image (Reference for speed and memory allocation)
*/
Image fancyFrameChoose(const Image &image) {
    cout << " ======== MENU FOR FANCY FRAME CHOOSING ======== \n" ;
    short choice = 0 ;
    string input ;
    while (true) {
        cout << " 1. For Vertical \n";
        cout << " 2. For Horizontal \n";
        cout << " 3. For Net Black\n";
        cout << " 4. For Net white \n";
        cout << " 5. For Return \n";
        cin >> input ;
        choice = inputValidation(input) ;
        switch (choice) {
            case 1 :
                return verticalFancy(image) ;
            case 2 :
                return horizontalFancy(image) ;
            case 3 :
                return NetImageBlack(image) ;
            case 4 :
                return NetImageWhite(image) ;
            case 5 :
                return image ;
            default :
                cout<<"INVALID CHOICE PLEASE TRY AGAIN\n";
                break;
        }
    }
}
/*
Function: frameChoose
Purpose : handle user input.
Inputs  : image (Reference for speed and memory allocation)
*/
Image frameChoose(Image &image) {
    cout << " ======== MENU FOR FRAME CHOOSING ======== \n" ;
     string input  ;
    short choice = 0 ;
    while (true) {
        cout << " 1. For Simple Frame \n";
        cout << " 2. For Fancy Frame \n";
        cout << " 3. For Return \n";
        cin >> input ;
        choice = inputValidation(input) ;
        switch (choice) {
            case 1 :
                return simpleFrameImage(image) ;
            case 2 :
                return fancyFrameChoose(image);;
            case 3 :
                return image ;
            default :
                cout<<"INVALID CHOICE PLEASE TRY AGAIN\n";
                break;
        }
    }
}
/*
Function: resizeImageLogic
Purpose : Resize the image using coordinate mapping ratios and pixel copying.
Inputs  : image (Reference for speed and memory allocation),Target width & height for the resized image.
*/
Image resizeImageLogic(const Image &image,const short &width, const short &height) {
    double widthRatio = static_cast<double>(image.width)/width
     , heightRatio = static_cast<double>(image.height)/height;
    short color[3] ;
    Image resizedImage(width,height) ;
    for (short i = 0 ; i < width ; i++) {
        for (short j = 0 ; j < height ; j++) {
            short x,y;
            x = ceil(widthRatio *(i+1)) - 1;
            y = ceil(heightRatio *(j+1)) - 1;
            getPixelColor(image,x,y,color) ;
            setPixelColor(resizedImage,i,j,color) ;
        }
    }
    return resizedImage ;
}
/*
Function: resizeImage
Purpose : handle user input.
Inputs  : image (Reference for speed and memory allocation)
*/
Image resizeImage(const Image &image) {
    cout << " ======== MENU FOR RESIZE CHOOSING ======== \n" ;
    cout << "NOTE: MAXIMUM DIMENSIONS ARE 10,000 x 10,000\n";
    string input ;
    short width = 0 , height = 0 ;
        cout << " Enter the new width in pixels \n";
        cin >> input ;
        width = inputValidation(input) ;
        if (width <= 0 ) {
            cout << " Invalid Width \n- Applying old Width\n";
            width = static_cast<short>(image.width)  ;
        }
         if(width >10000) {
            cout << "Maximum Width is: 10,000\n- Applying Width = 10,000\n";
            width = 10000;
        }
        cout << " Enter the new Height in pixels \n";
        cin >> input ;
        height = inputValidation(input) ;
        if (height <= 0 ) {
        cout << " Invalid Height \n-Applying old Height\n";
        height = static_cast<short>(image.height) ;
        }
         if(height >10000) {
        cout << "Maximum Height is: 10,000\n- Applying Height = 10,0000\n";
        height = 10000;
    }
    return resizeImageLogic(image,width,height) ;
}
/*
Function: saveImage
Purpose : handle save options.
Inputs  : image (Reference for speed and memory allocation).
*/
void saveImage(Image& img ,const string &oldPlace) {
    cout << "SAVE\n";
    string input;
    short choice;
    bool goodChoice=false;
    string newPlace;
    while(!goodChoice) {
        cout << "1. save in same file\n";
        cout << "2. save in another file\n";
        cout << "3. don't save\n";
        cin >> input;
         choice = inputValidation(input) ;
        switch(choice) {
            case 1:
                img.saveImage(oldPlace);
                goodChoice=true;
                break;

            case 2:
                {
                cout<<"Enter Filename with extension :\n";
                cin>>newPlace;
                bool success = false;
                while (!success) {
                    try {
                        if (img.saveImage(newPlace)) {
                            success = true;
                        }
                    }
                    catch (const exception& e) {
                        cerr << e.what() << '\n';
                        cout << "Enter proper image name: \n";
                        cin >> newPlace;
                    }
                }
            }
                goodChoice=true;
                break;
            case 3:
                return;
            default:
                cout<<"INVALID CHOICE PLEASE TRY AGAIN\n";
                break;
        }
    }
}

/* Name : Mohamed Salah Mohamed
ID : 20250569
Made : invertImage &&& darken_Lighten_Image &&& CropImage &&& PurpleLuffy &&& SkewImage

Functions Description:
- invertImage : inverts the image means the color of each pixel is reflected == 255 - initial value of color
- darken_Lighten_Image : darkens the image means the color of each pixel is reflected == 255 - initial value of color * 0.5
- darken_Lighten_Image : lightens the image means the color of each pixel is reflected == 255 - initial value of color * 1.5
- cropimage : crops the image means remove the unwanted parts of the image and keep the wanted part only
- purple_Luffy : Applies a color filter to the image, enhancing red and blue channels while reducing the green channel, creating a purple effect.
- skew_image : Skews the image by a specified angle, creating a slanted effect.

Filters: 3 - 7 - 11 - 15 - 17

*/

void invertImage(Image& img)
{                                                                                 // inverts the image means the color of each pixel is reflected == 255 - initial value of color
    for (int x = 0 ; x < img.width ; x++)                                         //
    {                                                                             //
        for (int y = 0 ; y < img.height ; y++)                                    // img.getPixel(x,y,c) returns the color of the pixel at (x,y) in the image == initial value of color
        {                                                                         // 255 - initial value of color = 255 - img.getPixel(x,y,c)
            for (int c = 0 ; c < img.channels ; c++)                              // img .setPixel(x,y,c , new value of color) sets the color of the pixel at (x,y) in the image
            {                                                                     //
                img.setPixel(x , y , c , 255 - img.getPixel(x , y , c)) ;
            }
        }
    }
  cout << " You have inverted the image \n" ;
}
void darkenlightValidation(float& num)
{
    if(num>100)
    {
        num=100;
    }
    if(num<0)
    {
        num=0;
    }
}

void darken_Lighten_Image(Image& img )
{
    cout << " Do you want to darken or lighten the image ? (1 for darken, 0 for lighten) : " << "\n" ;
    string input;
    float percent;
    short choice ;
    cin >> input ;
    choice = inputValidation(input) ;
    if (choice == 1)
    {
            cout<<"Enter percentage\n";
            cin>>input;
            percent=inputValidation(input);
            darkenlightValidation(percent);
            percent/=100;
        for (int x = 0 ; x < img.width ; x++)
        {
            for (int y = 0 ; y < img.height ; y++)
            {                                                                      // img.getPixel(x,y,c) == initial value of color
                for (int c = 0 ; c < img.channels ; c++)                           // initial value of color * 0.5 == convert the initial image to half dark
                {
                    img.setPixel(x , y , c , img.getPixel(x , y , c) * percent ) ;
                }
            }
        }
    }
    else
        cout<<"Enter percentage\n";
        cin>>input;
            percent=inputValidation(input);
            darkenlightValidation(percent);
            percent/=100;
        for (int x = 0 ; x < img.width ; x++)
        {
            for (int y = 0 ; y < img.height ; y++)
            {                                                                                       // img.getPixel(x,y,c) == initial value of color
                for (int c = 0 ; c < img.channels ; c++)                                            // initial value of color * 1.5 == convert the initial image to half light
                {                                                                                   // you use min function to make sure the value of color is not greater than 255
                    img.setPixel(x , y , c , min(255 ,(int) (img.getPixel(x , y , c) * (1+percent)))) ;
                }
            }
        }
}
bool validateCropCoordinates(int& x, int& y, int& newWidth, int& newHeight, int imgWidth, int imgHeight)  // Function to validate crop coordinates and dimensions
   {
        if (x < 0 || y < 0 || newWidth <= 0 || newHeight <= 0 || x >= imgWidth-1 || y >= imgHeight-1)
        {
            cerr << "Error: Crop coordinates and dimensions must be positive." << endl;
            return false;
        }
        if (x + newWidth > imgWidth ) { 
            cerr << "Error: Crop width exceeds image boundaries." << endl;
            newWidth=imgWidth-x-2;
            cout<<"New Width = "<<newWidth<<"\n";
        }
        if(y + newHeight > imgHeight){
            cerr << "Error: Crop height exceeds image boundaries." << endl;
            newHeight = imgHeight-y-2;
            cout<<"New height = "<<newHeight<<"\n";
        }
        return true;
    }



 void cropImage(Image& img)
 {  string input;
    int x , y , newWidth , newHeight ;
    bool right=false;
    while (!right) {
    
    cout << "Enter the x and y coordinates of the top left corner of the crop area : " << "\n" ;
    cin >>input;
    x = inputValidation(input);
    cin >> input;
    y = inputValidation(input);
    cout << "Enter the new width and height of the crop area : " << "\n" ;
    cin >> input ;
    newWidth = inputValidation(input);
    cin >> input;
    newHeight = inputValidation(input);
    right = validateCropCoordinates(x , y , newWidth , newHeight , img.width , img.height) ; // Validate the crop coordinates and dimensions
    if(!right){
        cout<<"Please enter valid coordinates and dimensions\n";
    }
}
    Image croppedImg(newWidth , newHeight) ; // Create a new image with the specified dimensions

    for (int i = 0 ; i < newWidth ; i++) //  create a new image with the specified dimensions and copy the pixel values from the original image to the new image
    {
        for (int j = 0 ; j < newHeight ; j++)
        {

            for (int c = 0 ; c < img.channels ; c++)
            {
                croppedImg.setPixel(i , j , c , img.getPixel(x + i , y + j , c)) ; // Set the pixel value in the new cropped image
            }
        }
    }
    img = croppedImg ; // Assign the cropped image to the original image object


 }
 void validateSkewAngle(float &skew_angle)
  {
    if (skew_angle < 0 )
        {
            cerr << "Error: Skew angle must be between 0 and 60 degrees." << endl;
            skew_angle=0;
            cout << "Applying skew angle = "<< skew_angle <<"\n";
        }if (skew_angle > 60 )
        {
            cerr << "Error: Skew angle must be between 0 and 60 degrees." << endl;
            skew_angle=60;
            cout << "Applying skew angle = "<< skew_angle <<"\n";
        }
  }

 float validateSkewAngleInput(string& input,bool& validInput)
  {
    string newInput ;
    bool decimalFound=false;
    for (char c : input) {
        if (c >= '0' && c <= '9') {
            newInput += c ;
        }else if(c == '.' && !decimalFound) {
            newInput += c ;
            decimalFound = true;
        }
    }
    if (!newInput.empty()) {
        validInput = true;
        return stof(newInput);
    }

    cerr << "Error: Invalid input for skew angle." << endl;
    return 0.0f;
  }

  void new_skew_image(Image& img, float skew_angle)
  {
   const double PI = 3.14159265358979323846; // Define PI for angle conversion

   int new_width = img.width + (int)(img.height * tan(skew_angle * PI / 180.0));
   int new_height = img.height;
   Image skewed_img(new_width, new_height);

   for (int y = 0; y < new_height; y++)
   {
       for (int x = 0; x < new_width; x++)
       {
          for(int c = 0; c < img.channels; c++)
          {
            skewed_img.setPixel( x , y , c , 255) ; // Set the pixel value in the new skewed image to white (or any other desired color)
            
          }
       }
   }
      img = skewed_img; // Assign the new skewed image to the original image object
    
  }


  void skew_image(Image& img)
  {
    string input ;
    float skew_angle;
    bool validInput = false;
    do
    {
        cout << "Enter the skew angle in degrees from { 0 to 60 }: ";
        cin >> input;
        skew_angle = validateSkewAngleInput(input, validInput);
    }
    while (!validInput);

    int choice;
    cout << " Enter the skew direction: \n ";
    cout << " you need skew right skew enter (0) \nyou need skew lift skew enter (1) \n";
    cin >> input;
    choice = inputValidation(input);
    validateSkewAngle(skew_angle);

    Image original_img = img; // Create a copy of the original image to avoid modifying it directly

    new_skew_image(img, skew_angle); // Create a new skewed image with the appropriate dimensions and initialize it to white background

    const double PI = 3.14159265358979323846; // Define PI for angle conversion

    if( choice == 0)
    {
        for( int y = 0 ; y < img.height  ; y++)
        {
            int shift = (int)((original_img.height -1 - y)  * tan(skew_angle * PI / 180.0)); // Calculate the horizontal shift for the current row based on the skew angle

            for( int x = 0 ; x < original_img.width ; x++)
            {
                for(int c = 0; c < original_img.channels; c++)
                {
                    int new_x = x + shift;
                    if(new_x >= 0 && new_x < img.width)
                    {
                        img.setPixel(new_x, y, c, original_img.getPixel(x, y, c));
                    }
                }
            }
        }
    }
    else if ( choice == 1)
    {
        for( int y = 0 ; y < img.height  ; y++)
        {


            for( int x = 0 ; x < original_img.width ; x++)
            {
                for(int c = 0; c < original_img.channels; c++)
                {
                    int new_x = x + (int)(y * tan(skew_angle * PI / 180.0));
                    if(new_x >= 0 && new_x < img.width)
                    {
                        img.setPixel(new_x, y, c, original_img.getPixel(x, y, c));
                    }
                }
            }
        }
    }
    else
    {
        cerr << "Error: Invalid skew direction choice.\nreturning to main menu..." << endl;
    }

    
  }

 // Function: purple_luffy
// Purpose : Applies a color filter to the image, enhancing red and blue channels while reducing the green channel, creating a purple effect.

 void purple_Luffy(Image& img)
 {
    for (int x = 0 ; x < img.width ; x++)
    {
        for (int y = 0 ; y < img.height ; y++)
        {
            for (int c = 0 ; c < img.channels ; c++) // Loop through each color channel (0: Red, 1: Green, 2: Blue)
            {
                if (c == 0) // Red channel
                    img.setPixel(x , y , c , min(255.0 ,(int) img.getPixel(x , y , c) * 1.3)) ; // Increase red channel intensity by 1.5 times, ensuring it doesn't exceed 255
                else if (c == 1) // Green channel
                    img.setPixel(x , y , c , img.getPixel(x , y , c) * 0.5 ) ; // Decrease green channel intensity by half
                else if (c == 2) // Blue channel
                    img.setPixel(x , y , c , min(255.0 ,(int) img.getPixel(x , y , c) * 1.3)) ; // Increase blue channel intensity by 1.5 times, ensuring it doesn't exceed 255
            }
        }
    }
 }

  /*//Name: Zeyad Amr Mohamed
//ID: 20250252
//made : Gray Scale & flip image
//flip : either flip an image vertically or horizontally
//Gray Scale : get the (r + g + b) and divide it by 3 to get the average gray of each pixel then assign the avg. for each of (r , g , b ) to get the all gray image

/*
Name: Zeyad Amr
ID:20250252
*/

  void grayScale(Image& image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            unsigned char r = image(i, j, 0);
            unsigned char g = image(i, j, 1);
            unsigned char b = image(i, j, 2);
            unsigned char gray = (r + g + b) / 3;

            image(i, j, 0) = gray;
            image(i, j, 1) = gray;
            image(i, j, 2) = gray;
        }
    }
}
// flip an image horizontally.
void flipHorizontal(Image& image) {
    for (int i = 0; i < image.width / 2; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int c = 0; c < 3; c++) {
                unsigned char temp = image(i, j, c);
                image(i, j, c) = image(image.width - 1 - i, j, c);
                image(image.width - 1 - i, j, c) = temp;
            }
        }
    }
}
// flip an image vertically.
void flipVertical(Image& image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height / 2; j++) {
            for (int c = 0; c < 3; c++) {
                unsigned char temp = image(i, j, c);
                image(i, j, c) = image(i, image.height - 1 - j, c);
                image(i, image.height - 1 - j, c) = temp;
            }
        }
    }
}
// handle user input.
void flipImage(Image& image) {
    string input ;
    cout << "press 1 for vertical and press 2 for horizontal flipping\n" ;
    cout << "Enter choice: \n";
    cin >> input;
    short flipChoice = inputValidation(input) ;
    if (flipChoice == 1) {
        flipVertical(image);
        cout << "Vertical flip applied\n" ;
    }
    else if (flipChoice == 2) {
        flipHorizontal(image);
        cout << "Horizontal flip applied\n" ;
    }
    else {
         cout<<"INVALID CHOICE PLEASE TRY AGAIN\n";
    }
}
void blendPixels(Image &result, const Image &img1, int x1, int y1, const Image &img2, int x2, int y2) {
    for (int c = 0; c < 3; ++c) {
        result(x1, y1, c) = (img1(x1, y1, c) + img2(x2, y2, c)) / 2;
    }
}

void mergeImage(Image &img1) {
    string filename2;
    cout << "Enter the second image file name with extension: \n";
    cin >> filename2;

    Image img2;
    bool success = false;
    while (!success) {
        try {
            if (img2.loadNewImage(filename2)) {
                success = true;
            } else {
                cout << "Enter proper image name: \n";
                cin >> filename2;
            }
        } catch (const exception &e) {
            cerr << e.what() << '\n';
            cout << "Enter proper image name: \n";
            cin >> filename2;
        }
    }

    if (img1.width == img2.width && img1.height == img2.height) {
        Image mergedImg(img1.width, img1.height);
        for (int i = 0; i < img1.width; ++i) {
            for (int j = 0; j < img1.height; ++j) {
                blendPixels(mergedImg, img1, i, j, img2, i, j);
            }
        }
        img1 = mergedImg;
        cout << "Images merged successfully!\n";
        return;
    }

    cout << "\nImages have different dimensions (" << img1.width << "x" << img1.height
         << " vs " << img2.width << "x" << img2.height << ")\n";
    cout << "1. Resize to largest width and height, then merge\n";
    cout << "2. Merge common area (smallest width and height)\n";
    cout << "Choose option (1-2): ";

    string input;
    cin >> input;
    short choice = inputValidation(input);

    if (choice == 1) {
        int maxWidth = max(img1.width, img2.width);
        int maxHeight = max(img1.height, img2.height);

        Image resizedImg1 = (img1.width == maxWidth && img1.height == maxHeight)
                             ? img1
                             : resizeImageLogic(img1, maxWidth, maxHeight);

        Image resizedImg2 = (img2.width == maxWidth && img2.height == maxHeight)
                             ? img2
                             : resizeImageLogic(img2, maxHeight, maxHeight);

        Image mergedImg(maxWidth, maxHeight);
        for (int i = 0; i < maxWidth; ++i) {
            for (int j = 0; j < maxHeight; ++j) {
                blendPixels(mergedImg, resizedImg1, i, j, resizedImg2, i, j);
            }
        }
        img1 = mergedImg;
        cout << "Images resized to " << maxWidth << "x" << maxHeight << " and merged successfully!\n";

    } else if (choice == 2) {
        int minWidth = min(img1.width, img2.width);
        int minHeight = min(img1.height, img2.height);

        Image mergedImg(minWidth, minHeight);
        for (int i = 0; i < minWidth; ++i) {
            for (int j = 0; j < minHeight; ++j) {
                blendPixels(mergedImg, img1, i, j, img2, i, j);
            }
        }
        img1 = mergedImg;
        cout << "Common area (" << minWidth << "x" << minHeight << ") merged successfully!\n";

    } else {
        cout << "INVALID CHOICE. Operation cancelled.\n";
    }
}
void landofWano(Image& image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            unsigned char r = image(i, j, 0);
            unsigned char g = image(i, j, 1);
            unsigned char b = image(i, j, 2);

            int newR = static_cast<int>(r * 1.20);
            int newG = static_cast<int>(g * 1.15);
            int newB = static_cast<int>(b * 0.85);

            image(i, j, 0) = static_cast<unsigned char>(min(255, newR));
            image(i, j, 1) = static_cast<unsigned char>(min(255, newG));
            image(i, j, 2) = static_cast<unsigned char>(max(0, newB));
        }
    }
    cout << "Land of Wano filter applied successfully!\n";
}


/*
Name: Kareem Tamer Samir
ID: 20250483
making 4 filters:
1- BlackAndWhite
2- rotateImage
3- ApplyRGBFilter
4- image edge
*/
//  BlackAndWhite
void BlackAndWhite(Image& img){
    for(int i=0;i<img.width;i++){
        for(int j=0;j<img.height;j++){

            unsigned int average =((img(i,j,0) +img(i,j,1) + img(i,j,2))/3);
            unsigned char color;
            if(average>=127){
                color=255;
            }
            else{
                color=0;
            }
            img(i,j,0)=color;
            img(i,j,1)=color;
            img(i,j,2)=color;
        }
    }}

void ImageEdges(Image& img){
    // Implementation for image edges
    grayScale(img);// Convert the image to grayscale first
    int w=img.width;
    int h=img.height;
    int threshold=30;
    Image tempimage = img; // Create a copy of the original image

    for(int i=1;i<w-1;i++){
        for(int j=1;j<h-1;j++){
            unsigned char currentPixel = tempimage(i,j,0); // Grayscale value
             unsigned char right=tempimage(i+1,j,0);
             unsigned char down=tempimage(i,j+1,0);
             unsigned char left=tempimage(i-1,j,0);
             unsigned char up=tempimage(i,j-1,0);
             int diffi=abs(right- left);
             int diffj=abs(up-down);
             int maxDiff=max(diffi,diffj);
            if(maxDiff>threshold){
                img(i,j,0)=0;
                img(i,j,1)=0;
                img(i,j,2)=0;
             }
             else{
                img(i,j,0)=255;
                img(i,j,1)=255;
                img(i,j,2)=255;
             }
        }
    }

}

//made: rotateImage & BlackAndWhite+
// Function: rotateimage90
// Purpose : Rotates an image 90 degrees clockwise.
// Inputs  : img (Reference to the source Image object)
// Returns : A new Image object rotated 90 degrees clockwise

Image rotateimage90( const Image& img){
    Image newimage(img.height, img.width); // memory allocation for new image
    for(int i =0 ;i<newimage.width;i++){
        for(int j=0;j<newimage.height;j++){
            for(int k=0;k<newimage.channels;k++){
                newimage(i,j,k)=img(j,img.height-1-i,k); // Rotate 90 degrees clockwise
            }
        }

    }
    return newimage;}
// Function: rotateImage
// Purpose : Handles user selection to rotate the image by 90, 180, or 270 degrees.
// Inputs  : img (Reference to the Image object to be modified in-place
void rotateImage(Image& img){
    bool validChoice=false;
    while(!validChoice){
        cout<<"ENTER THE CHOICE OF ROTATION\n";
        cout<<"1-90\n2-180\n3-270\n";
        cout<<"CHOOSE (1-3):\n";
        string input;
        unsigned int choice;
        cin>>input;
        choice = inputValidation(input) ;
        switch(choice){
            case 1:
                img=rotateimage90(img);
                validChoice=true;
                break;
            case 2:
                img=rotateimage90(img);
                img=rotateimage90(img);
                validChoice=true;
                break;
            case 3:
                img=rotateimage90(img);
                img=rotateimage90(img);
                img=rotateimage90(img);
                validChoice=true;
                break;
            default:
                cout<<"INVALID CHOICE,PLEASE TRY AGAIN\n";
        }

    }}

void ApplyRGBFilter(Image& image,const Image& original,int shift=5){
    // create a copy of the original image to avoid modifying it directly
    int width = image.width;
    int height = image.height;
for (int i=0;i<width;i++){
    for(int j=0;j<height;j++){
        // Calculate horizontally shifted boundaries for Red & Blue channels
        // max prevents negative index access on the left edge (Underflow protection)
        // min prevents index overflow on the right edge (Overflow protection)
        int redx = max(0,(i-shift));
        int bluex=min(width-1, (i+shift));
        image(i,j,0)=original(redx,j,0); // Red pulled from left
        image(i,j,1)=original(i,j,1); // Green from original
        image(i,j,2)=original(bluex,j,2); // Blue pulled from right
    }
}}
 //Applies horizontal scanlines to simulate a CRT TV display effect.
 // It darkens every Nth row (defined by 'spaces') by multiplying pixel brightness by 'factor'.
void ApplyScanLines(Image& image,int spaces =3,float factor=0.45f){
    int width = image.width;
    int height = image.height;
for(int j=0;j<height;j++){
    if(j%spaces==0){
        for(int i=0;i<width;i++){
            for(int c=0;c<3;c++){
                // Multiply brightness by factor and cast back to unsigned char (0-255 range)
                image(i,j,c)=static_cast<unsigned char>(image(i,j,c)*factor);
            }
        }
    }
}
}
/*
 Applies a Vignette effect to the image, which darkens the corners
  while keeping the center bright to simulate old camera lenses and CRT displays.
*/
void ApplyVignette(Image& image,float darkness=0.5f){
int width = image.width;
int height = image.height;
float centerX = width / 2.0f;
float centerY = height / 2.0f;
float MaxDistance = sqrt(centerX*centerX + centerY*centerY);

for(int i=0;i<width;i++){
    for(int j=0 ;j<height;j++){
        // Calculate distance components from the center
        float dx = i - centerX;
        float dy = j - centerY;
        float distance = sqrt(dx*dx + dy*dy);
        /*
        dis/maxdis gives a normalized distance from the center  range [0.0,1.0](0 at center, 1 at corners).
        */
        float factor = 1.0f - (distance / MaxDistance) * darkness;
        // Clamp factor within [0.0, 1.0] range to prevent negative brightness or unexpected values
        factor = max(0.0f, min(1.0f, factor));
        for(int c=0;c<3;c++){
            image(i,j,c)=static_cast<unsigned char>(image(i,j,c)*factor);
        }
    }
}
}
void ApplyTVEffect(Image& image){
    Image original = image; // Create a copy of the original image
    ApplyRGBFilter(image,original,5); // Apply RGB filter with a shift of 5 pixels
    ApplyScanLines(image,3,0.45f); // Apply scan lines with a spacing of 3 pixels and a darkening factor of 0.45
    ApplyVignette(image,0.5f); // Apply vignette effect with a darkness factor of 0.5
}

/*youssef Adly's filters
  blur
  infrared
  oil
 */
void infraredImage(Image &image) {
    grayScale(image);
    invertImage(image);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            image(i, j, 0) = 255;
        }
    }
}
void addArr(short* avg, short* color) {
    for (int i = 0; i < 3; i++) {
        avg[i]+=color[i];
    }
}
void blurLogic(Image &image,int num) {
    Image tempImage = image;
    short color[3]={};
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            short averageColor[3]={};
            int counter = min(num, image.height-j);
            for (int k=0;k<counter;k++){
                getPixelColor(tempImage, i, j+k, color);
                addArr(averageColor,color);
            }
            averageColor[0]/=counter;
            averageColor[1]/=counter;
            averageColor[2]/=counter;
                setPixelColor(image, i, j, averageColor);
        }
    }
    tempImage = image;
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            short averageColor[3]={};
            int counter = min(num, image.width-i);
            for (int k=0;k<counter;k++){
                getPixelColor(tempImage, i+k, j, color);
                addArr(averageColor,color);
            }
            averageColor[0]/=counter;
            averageColor[1]/=counter;
            averageColor[2]/=counter;
                setPixelColor(image, i, j, averageColor);
        }
    }

}
void blur(Image& image) {
    string input;
    while (true) {
        cout << "1. Level 1 blur \n" ;
        cout << "2. Level 2 blur \n" ;
        cout << "3. Return \n" ;
        cin >> input;
        short blurChoice = inputValidation(input) ;
        switch (blurChoice) {
            case 1:
                blurLogic(image,30);
                return;
            case 2:
                blurLogic(image,60);
                return ;
            case 3:
                return ;
            default:
                cout << "INVALID CHOICE PLEASE TRY AGAIN\n";
                break;
        }
    }
}
void oil(Image &image) {
    short color[3]={};
    for (short i = 0; i < image.width; i++) {
        for (short j = 0; j < image.height; j++) {
            getPixelColor(image, i, j, color);
            color[0]=static_cast<short>((color[0]/16)*16);
            color[1]=static_cast<short>((color[1]/16)*16);
            color[2]=static_cast<short>((color[2]/16)*16);
            setPixelColor(image, i, j, color);
        }
    }
}
int main()
{
    string input;
string filename ;
cout << "Enter the file name with extension : \n" ;
cin >> filename ;
    Image img;
    bool success = false;
    while (!success) {
        try {
            if (img.loadNewImage(filename)) {
                success = true;
            }
        }
        catch (const exception& e) {
            cerr << e.what() << '\n';
            cout << "Enter proper image name: \n";
            cin >> filename;
        }
    }
    Image copyImage=img;
    bool run=true ;
 while (run) {
     cout << " ======== MENU FOR IMAGE PROCESSING ======== " << "\n" ;
     cout << " 1.  Gray Scale image " << "\n" ;
     cout << " 2.  Black and White image " << "\n" ;
     cout << " 3.  Invert image " << "\n" ;
     cout << " 4.  Frame image " << "\n" ;
     cout << " 5.  Flip image " << "\n" ;
     cout << " 6.  Rotate image " << "\n" ;
     cout << " 7.  Darken and Lighten image " << "\n" ;
     cout << " 8.  Resize image " << "\n" ;
     cout << " 9.  Merge images " << "\n" ;
     cout << " 10. Edges image " << "\n" ;
     cout << " 11. Crop image " << "\n" ;
     cout << " 12. Blur image " << "\n" ;
     cout << " 13. The land of wano image " << "\n" ;
     cout << " 14. TV " << "\n" ;
     cout << " 15. Purple luffy image " << "\n" ;
     cout << " 16. Infrared image " << "\n" ;
     cout << " 17. Oil paint \n" ;
     cout << " 18. Skew image \n";
     cout << " 19. load a new image " << "\n" ;
     cout << " 20. save image " << "\n" ;
     cout << " 21. Clear filter \n" ;
     cout << " 22. Exit \n";
     cin >> input ;
    short choice = inputValidation(input) ;
     switch (choice) {
         case 1 :
             grayScale(img) ;
             break ;
         case 2 :
             BlackAndWhite(img) ;
             break ;
         case 3 :
             invertImage(img) ;
             break ;
         case 4 :{
             img = frameChoose(img) ;
             break ;
         }
         case 5 :
             flipImage(img) ;
             break ;
         case 6 :
             rotateImage(img) ;
             break ;
         case 7 :
             darken_Lighten_Image(img) ;
             break ;
         case 8 :
             {
                 img = resizeImage(img) ;
                 break ;
             }
         case 9 :
             mergeImage(img) ;
             break ;
         case 10 :
             ImageEdges(img) ;
             break ;
         case 11 :
             cropImage(img) ;
             break ;
         case 12:
             blur(img);
             break ;
         case 13 :
             landofWano(img) ;

             break ;
         case 14 :
             ApplyTVEffect(img) ;
             cout << "RGB Shift Filter applied successfully!\n" ;
             break ;
         case 15 :
             purple_Luffy(img) ;
             break ;
         case 16 :
             infraredImage(img) ;
             break ;
        case 17:
            oil(img) ;
             break ;
        case 18:
            skew_image(img) ;
             break ;
         case 19 :
            {
             cout << " Do you want to save the current image before loading a new image ? (1 for yes, 0 for no) : " << "\n" ;

             cin >> input ;
             short newChoice = inputValidation(input) ;
             if (newChoice == 1 )
             {
                 saveImage(img, filename) ;

                 string newFilename ;
                 cout << " Enter the name of new image :\n" ;
                 cin >> newFilename ;
                 Image tempImage ;
                 bool success = false;
                 while (!success) {
                     try {
                         if (tempImage.loadNewImage(newFilename)) {
                             success = true;
                         }
                     }
                     catch (const exception& e) {
                         cerr << e.what() << '\n';
                         cout << "Enter proper image name: \n";
                         cin >> newFilename;
                     }
                 }
                 img = tempImage;
                 copyImage =img;
             }
             else
             {
                 string newFilename ;
                 cout << " Enter the name of new image :\n" ;
                 cin >> newFilename ;
                 Image tempImage ;
                 bool success = false;
                 while (!success) {
                     try {
                         if (tempImage.loadNewImage(newFilename)) {
                             success = true;
                         }
                     }
                     catch (const exception& e) {
                         cerr << e.what() << '\n';
                         cout << "Enter proper image name: \n";
                         cin >> newFilename;
                     }
                 }
                 img = tempImage;
                 copyImage =img;
             }

             break ;
            }
         case 20 :
             saveImage(img, filename) ;
             break ;
         case 21 :
             img=copyImage;
             break ;
         case 22 :
             saveImage(img, filename) ;
             run = false ;
             break ;
         default :
             cout << " Invalid choice \n" ;
             break;
     }
 }
cout << "Exiting the program." << endl ;
    return 0 ;
}