// FCAI – Programming 1 – 2022 - Assignment 3
// Program: Images Filters.cpp
// Author: Abdallah Hussein Ibrahim Hussein - Esraa Mahmoud Abdelmohsen - Youssef Abdelghafar Abdeltawab
// IDs: 20210235 - 20210063 - 20210474
// Group: A
// Date: April  2022
// Section: 5,6

#include <bits/stdc++.h>
#include "bmplib.cpp"

ifstream direction, direction_2 ;
string file_1,file_2;

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char image3[SIZE][SIZE];
unsigned char flip[SIZE][SIZE];
unsigned char edited[SIZE][SIZE];
unsigned char new_image_part1[SIZE][SIZE];
unsigned char new_image_part2[SIZE][SIZE];
unsigned char new_image_part3[SIZE][SIZE];
unsigned char new_image_part4[SIZE][SIZE];

void loadImage ();
void loadImage2 ();
void saveImage ();
void saveImage3 ();

void black_and_white();
void Filter_InvertImage();
void Merge();
void flip_image();
void Darken_and_Lighten();
void Rotate_file_90_Degree();
void Rotate_file_180_Degree();
void Rotate_file_270_Degree();
void detect();
void enlarge();
void shrink();
void mirror();
void shuffle();
void record_part1();
void record_part2();
void record_part3();
void record_part4();
void blur();

int main()
{

  // choose any filter you want to do.
    int num_of_filter , rotate_degree;
    cout << "Ahlan ya user ya habibi :D\n";
    loadImage();
    cout << "Please select a filter to apply or 0 to exit: \n";
    cout << "1- Black & White Filter\n";
    cout << "2- Invert Filter\n";
    cout << "3- Merge Filter\n";
    cout << "4- Flip Image\n";
    cout << "5- Darken and Lighten Image\n";
    cout << "6- Rotate Image\n";
    cout << "7- Detect Image\n";
    cout << "8- Enlarge Image\n";
    cout << "9- Shrink Image\n";
    cout << "10- Mirror Image\n";
    cout << "11- Shuffle Image\n";
    cout << "12- Blur Image\n";
    cout << "0- Exit\n";
    // choose number one if you want Filter_InvertImage.
    cin.ignore(99999,'\n'); // Validate the input.
    cin.clear();
    string get_num;
    while (true)
    {
      getline(cin, get_num);
      if(get_num == "1" || get_num == "2" || get_num == "3"|| get_num == "4"|| get_num == "5"|| get_num == "6"|| get_num == "7"|| get_num == "8"|| get_num == "9"|| get_num == "10"|| get_num == "11"|| get_num == "12"|| get_num == "0")
      {
      num_of_filter = stoi(get_num);
      break;}
      else {
      cout << "INVALD\n";
      }
    }

    if(num_of_filter == 1){

      black_and_white();
      saveImage();
    }
    if(num_of_filter == 2){

      Filter_InvertImage();
      saveImage();
    }
    if(num_of_filter == 3){

      loadImage2();
      Merge();
      saveImage3();
    }
    if(num_of_filter == 4){

      flip_image();
      saveImage();
    }
    if(num_of_filter == 5){

        Darken_and_Lighten();
        saveImage();
    }
    if(num_of_filter == 6){
      string rotate;
    cout << "enter the degree you want(90, 180 or 270): ";
    // choose any degree you want to Rotate Photo .
    while (true)
    {
      getline(cin, rotate);
      if(rotate == "90" || rotate == "180" || rotate == "270")
      {
      rotate_degree = stoi(rotate);
      break;}
      else {
      cout << "INVALD\n";
      }
    }
    if (rotate_degree == 90)
        {

            Rotate_file_90_Degree();
            saveImage();
        }
        // choose 180 degree if you want rotate 180 degree.
        else if (rotate_degree==180)
        {

            Rotate_file_180_Degree();
            saveImage();
        }
        // choose 270 degree if you want rotate 270 degree.
        else if (rotate_degree == 270)
        {

            Rotate_file_270_Degree();
            saveImage();
        }
    }
    if (num_of_filter==7)
    {
        detect();
        saveImage();
    }

    if(num_of_filter == 8){
      enlarge();
      saveImage3();
    }
    if(num_of_filter == 9){
      shrink();
      saveImage3();
    }
     if(num_of_filter == 10){
       mirror();
       saveImage();
     }
    if(num_of_filter == 11){
      shuffle();
      saveImage();
    }
    if(num_of_filter == 12){
      blur();
      saveImage();
    }
    if(num_of_filter == 0){
      return 1;
    }
  return 0;
}
//_________________________________________
void loadImage () {
   char imageFileName[100];
    while(true)   // Validate the image
            {       // Get gray scale image file name
                cout << "Enter the source image file name: \n" ;

                cin >> imageFileName ;
                // Add to it .bmp extension and load image
                file_1 = strcat (imageFileName, ".bmp") ;
                direction.open(file_1) ;
                if(direction)
                {
                    readGSBMP(imageFileName, image) ;
                    break ;
                }
                else

                    cout << "The file is Not Exist.\n" << endl ;
            }
}
void loadImage2 () {
   char imageFileName[100];
    while(true)     // Validate the image
            {       // Get gray scale image file name
                cout << "Enter the second source image file name: \n" ;

                cin >> imageFileName ;
                // Add to it .bmp extension and load image
                file_2 = strcat (imageFileName, ".bmp") ;
                direction_2.open(file_2) ;
                if(direction_2)
                {
                    readGSBMP(imageFileName, image2) ;
                    break ;
                }
                else

                    cout << "The file is Not Exist.\n" << endl ;
            }
}
//_________________________________________
void saveImage () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, image);
}
void saveImage3 () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, image3);
}
void black_and_white() // Author: Esraa Mahmoud Abdelmohsen - 20210063
{
    int sum_pixels=0,average;
    //nested loop for array 2D (IMAGE)
    for (int i=0;i<SIZE;i++) {
        for (int j = 0; j < SIZE; j++)
        {
            sum_pixels += image[i][j];
        }
    }
    average = (sum_pixels / (SIZE*SIZE));

    for (int i=0;i<SIZE;i++)
    {
        for (int j = 0; j < SIZE; j++)
        {

            if (image[i][j]>average)
                //make the index [i][j] white.
                image[i][j] = 255;
            else if (image[i][j]<average)
                //make index [i][j] black.
                image[i][j] = 0;
        }
    }

}
void Filter_InvertImage(){ //Author: Youssef Abdelghafar Abdeltawab
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            image[i][j] = 255 - image[i][j];
        }
    }
}
void Merge() {  //Author: Abdallah Hussein Ibrahim Hussein - 20210235
for (int i = 0; i < SIZE; i++)
{
  for (int j = 0; j < SIZE; j++)
  {
      image3[i][j] = ((image[i][j]+image2[i][j])/2);
  }
}
}
void flip_image() { // Author: Esraa Mahmoud Abdelmohsen - 20210063

    int option, image_needed;
    string need;
    cout << "if you want original image press 1 \n"
            "if you want flip image press 2 \n";
    while (true)
    {
      getline(cin, need);
      if(need == "1" || need == "2")
      {
      image_needed = stoi(need);
      break;}
      else {
      cout << "INVALD\n";
      }
    }
    if (image_needed == 1) {
        image[SIZE][SIZE];
    } else if (image_needed == 2) {
        cout << "if you need  to flip the image horizontally press 1 \n"
                "if you need  to flip the image  vertically press 2 \n";
    string opt;
    while (true)
    {
      getline(cin, opt);
      if(opt == "1" || opt == "2")
      {
      option = stoi(opt);
      break;}
      else {
      cout << "INVALD\n";
      }
    }
        if (option == 1) {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    flip[i][j] = image[i][(SIZE - 1) -
                                          j]; //(SIZE-1)-j to flip indexes horizontally (deal with columns) with each other to make flip to  it.

                }
            }
        }
        if (option == 2) {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    flip[i][j] = image[(SIZE - 1) -
                                       i][j]; //(SIZE-1)-i to flip indexes vertically (deal with rows) with each other to make flip to  it.

                }
            }
        }
        //this loop to save the edit in original image to print it.
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                image[i][j] = flip[i][j];
    }
}
void Darken_and_Lighten() { // Author: Abdallah Hussein Ibrahim Hussein - 20210235
  string choice;    // Validate the input.
  int choice0;
  cout << "Type 1 if you want to Darken the image.\nType 2 if you want to Lighten the image.\n";
  while (true)
  {
    getline(cin,choice);
    if ((choice == "1" || choice == "2"))
    {
    choice0 = stoi(choice);
    break;
    }
    else {
      cout << "INVALD\n";
      }
  }
  switch (choice0)
  {
  case (1):
      for (int i = 0; i < SIZE; i++) {
          for (int j = 0; j< SIZE; j++) {
                                                // darken below
            image[i][j] = (image[i][j]/2);
          }
    }
    break;
    case (2):
      for (int i = 0; i < SIZE; i++) {
          for (int j = 0; j< SIZE; j++) {
                                      // lighten below
              image[i][j] = ((image[i][j]+255)/2);
          }
    }
    break;
  default:
    break;
  }
}

// Function to Rotate 90 degree
void Rotate_file_90_Degree() //Author: Youssef Abdelghafar Abdeltawab - 20210474
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = i; j < SIZE; j++)
            swap(image[i][j], image[j][i]);
    }
}
// Function to Rotate 180 degree
void Rotate_file_180_Degree() // Author: Youssef Abdelghafar Abdeltawab - 20210474
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = i; j < SIZE; j++)
            swap(image[i][j], image[j][i]);
    }
    int i = 0, j = 0, col = 0;
    while (col < SIZE)
    {
        i = 0;
        j = SIZE - 1;
        while (i < j)
        {
            swap(image[i][col], image[j][col]);
            i += 1;
            j -= 1;
        }
        col += 1;
    }
}

// Function to Rotate 270 degree
void Rotate_file_270_Degree() // Author: Youssef Abdelghafar Abdeltawab - 20210474
{
    for (int i = 0; i < SIZE/2; i++)
    {
        for (int j = 0; j < SIZE; j++) {
            swap(image[i][j], image[SIZE-i][SIZE-j]);
        }
    }
}
void detect()// Author: Esraa Mahmoud Abdelmohsen - 20210063
{
    //make empty array in the first called edited.
    for( int i=0;i<SIZE;i++)
    {
        for ( int j=0;j<SIZE;j++)
            //make all indexes white.
            edited[i][j]=255;
    }
    for (int i=0;i<SIZE;i++)
    {
        for(int j=0; j<SIZE;j++)
        {
            //check if the index[i][j]>128 and the index after it(for column) and <128 but black point in array edited
            if (image[i][j]>128 && image[i][j+1]<128)
                edited[i][j]=0;
            //check if the index[i][j]<128 and the index after it and >128(for column) but black point in array edited
            if (image[i][j]<128 && image[i][j+1]>128)
                edited[i][j]=0;
            //check if the index[i][j]>128 and the index after it and <128(for rows) but black point in array edited
            if (image[i][j]>128 && image[i+1][j]<128)
                edited[i][j]=0;
            //check if the index[i][j]<128 and the index after it and >128(for rows) but black point in array edited
            if (image[i][j]<128 && image[i+1][j]>128)
                edited[i][j]=0;
        }
    }
    for (int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
            //move what added in array edited in original image.
            image[i][j]=edited[i][j];
    }
}
// enlarge is zooms in to a specific quarter of the four.
void enlarge()       //Author: Youssef Abdelghafar Abdeltawab
{
    int quarter; // which quarter you want.
    cout << "which quarter you want(1,2,3 or 4): ";
    string rot; // this to definsev to code from crash.
    while (true)
    {
      getline(cin, rot);
      if(rot == "1" || rot == "2" || rot == "3"|| rot == "4")
      {
      quarter = stoi(rot);
      break;}
      else {
      cout << "INVALD\n";
      }
    }
    if (quarter == 1) { // to chosse first quarter and edit to pixels.
        for (int i = 0, rows = 0; i < SIZE/2 && rows < SIZE ;++i,rows+=2) {
            for (int j = 0,columns = 0; j < SIZE/2 && columns < SIZE; ++j,columns+=2) {
                image3[rows][columns] = image[i][j];
                image3[rows][columns+1] = image[i][j];
                image3[rows+1][columns] = image[i][j];
                image3[rows+1][columns+1] = image[i][j];
            }
        }
    }
    else if (quarter == 2)
    {// to chosse secound quarter and edit to pixels.
        for (int i = 0, rows = 0; i < SIZE/2 && rows < SIZE/2; ++i, rows+=1) {
            for (int j = SIZE/2, columns = 0; j < SIZE && columns < SIZE/2; ++j, columns+=1) {
                image3[rows*2][columns*2] = image[i][j];
                image3[rows*2][columns*2+1] = image[i][j];
                image3[rows*2+1][columns*2] = image[i][j];
                image3[rows*2+1][columns*2+1] = image[i][j];
            }
        }
    }
    else if (quarter == 3)
    {// to chosse third quarter and edit to pixels.
        for (int i = SIZE/2, rows = 0; i < SIZE && rows < SIZE; ++i, rows+=2)
        {
            for (int j = 0, columns = 0; j < SIZE && columns < SIZE; ++j, columns+=2)
            {
                image3[rows][columns] = image[i][j];
                image3[rows][columns+1] = image[i][j];
                image3[rows+1][columns] = image[i][j];
                image3[rows+1][columns+1] = image[i][j];
            }
        }
    }
    else if (quarter == 4)
    {// to chosse quater four quarter and edit to pixels.
        for (int i = SIZE/2, rows = 0; i < SIZE && rows < SIZE; ++i, rows+=2)
        {
            for (int j = SIZE/2, columns = 0; j < SIZE && columns < SIZE; ++j, columns+=2)
            {
                image3[rows][columns] = image[i][j];
                image3[rows][columns+1] = image[i][j];
                image3[rows+1][columns] = image[i][j];
                image3[rows+1][columns+1] = image[i][j];
            }
        }
    }
}

void shrink() { // //Author: Abdallah Hussein Ibrahim Hussein - 20210235
string choice;
  int choice0;     // Validate the input
  cout << "Type 1 if you want to to shrink the image dimensions to 1/2.\nType 2 if you want to to shrink the image dimensions to 1/3.\nType 3 if you want to to shrink the image dimensions to 1/4.\n";
  while (true)
  {
    getline(cin,choice);
    if (choice == "1" || choice == "2"|| choice == "3")
    {
    choice0 = stoi(choice);
    break;
    }
    else {
      cout << "INVALD\n";continue;
      }
  }
  switch (choice0)
  {
  case (1):
      for (int i = 0; i < SIZE; i++) {
          for (int j = 0; j< SIZE; j++) {
            image3[i/2][j/2]= image[i][j]; // reduce every pixel to 1/2 to shrink the image dimensions to 1/2
          }
    }
    break;
    case (2):
      for (int i = 0; i < SIZE; i++) {
          for (int j = 0; j< SIZE; j++) {
              image3[i/3][j/3]= image[i][j]; // reduce every pixel to 1/3 to shrink the image dimensions to 1/3
          }
    }
    break;
    case(3):
    for (int i = 0; i < SIZE; i++) {
          for (int j = 0; j< SIZE; j++) {
              image3[i/4][j/4]= image[i][j]; // reduce every pixel to 1/4 to shrink the image dimensions to 1/4
          }
    }
  default:
    break;
  }
}
void mirror()// Author: Esraa Mahmoud Abdelmohsen - 20210063
{
    int option;
    cout<<"1_choose 1 if you want 1/2 right \n"
          "2_choose 2 if you want 1/2 left \n"
          "3_choose 3 if you want 1/2 upper\n"
          "4_choose 4 if you want 1/2 lower\n";
    string need;
    while (true)
    {
      getline(cin, need);
      if(need == "1" || need == "2"|| need == "3"|| need == "4")
      {
      option = stoi(need);
      break;}
      else {
      cout << "INVALD\n";
      }
    }
    if (option==1) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                //(SIZE -1)-j to flip columns in original image.
                flip[i][j] = image[i][(SIZE - 1) - j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            //loop from the middle index (in columns) to the end to edit this part.
            for (int j = (SIZE / 2); j < SIZE; j++) {
                //make second half in columns in original image = second half in columns in flip image.
                image[i][j] = flip[i][j];

            }
        }
    }
    if(option==2)
    {

        for (int i=0;i<SIZE;i++)
        {
            for (int j=0;j<SIZE;j++)
            {
                //(SIZE -1)-i to flip rows in original image.
                flip[i][j] = image[(SIZE - 1) -i][j];
            }
        }
        //loop from the middle index (in rows) to the end to edit this part.
        for (int i=(SIZE/2);i<SIZE;i++)
        {
            for (int j=0;j<SIZE;j++)
            {
                //make second half in rows in original image = second half in rows in flip image.
                image[i][j]=flip[i][j];

            }
        }
    }
    if (option==3)
    {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                //(SIZE -1)-j to flip columns in original image.
                flip[i][j] = image[i][(SIZE - 1) - j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            //loop from the first index (in columns) to middle to edit this part.
            for (int j = 0; j < (SIZE / 2); j++) {
                //make first half in columns in original image = first half in columns in flip image.
                image[i][j] = flip[i][j];

            }
        }



    }
    if(option==4)
    {

        for (int i=0;i<SIZE;i++)
        {
            for (int j=0;j<SIZE;j++)
            {
                //(SIZE -1)-i to flip rows in original image.
                flip[i][j] = image[(SIZE - 1) -i][j];
            }
        }
        //loop from the first index (in rows) to middle to edit this part.
        for (int i=0;i<(SIZE/2);i++)
        {
            for (int j=0;j<SIZE;j++)
            {
                //make first half in rows in original image = first half in rows in flip image.
                image[i][j]=flip[i][j];

            }
        }
    }
}
// shuffle It is dividing the image into four parts and rearranging them as desired by the user.
void shuffle()          //Author: Youssef Abdelghafar Abdeltawab
{
    int part1, part2, part3, part4;
    cout << "enter your order you want: " << endl;
    cout << "Enter: ";
    cin >> part1 >> part2 >> part3 >> part4;
    record_part1(); // all this fuction record each part in one array.
    record_part2();
    record_part3();
    record_part4();
    if (part1 == 1)
    { // this loop to move from part one to one.
        int x = 0 , y = 0;
        for (int i = 0; i < SIZE/2; i++)
        {
            for (int j = SIZE/2; j < SIZE; j++)
            {
                image[i][j] = new_image_part1[x][y++];
            }
            x++;
            y = 0;
        }
    }
    if (part1 == 2)
    {// this loop to move from part two to one.
        int x = 0 , y = 0;
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                image[i][j] = new_image_part2[x][y++];
            }
            x++;
            y = 0;
        }
    }
    if (part1 == 3)
    {// this loop to move from part three to one.
        int x = 0 , y = 0;
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                image[i][j] = new_image_part3[x][y++];
            }
            x++;
            y = 0;
        }
    }
    if (part1 == 4)
    {// this loop to move from part four to one.
        int x = 0 , y = 0;
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                image[i][j] = new_image_part4[x][y++];
            }
            x++;
            y = 0;
        }
    }
    if (part2 == 1)
    {// this loop to move from part one to two.
        int x = 0 , y = 0;
        for (int i = 0; i < SIZE/2; i++)
        {
            for (int j = SIZE/2; j < SIZE; j++)
            {
                image[i][j] = new_image_part1[x][y++];
            }
            x++;
            y = 0;
        }
    }
    if (part2 == 2)
    {// this loop to move from part two to two.
        int x = 0 , y = 0;
        for (int i = 0; i < SIZE/2; i++)
        {
            for (int j = SIZE/2; j < SIZE; j++)
            {
                image[i][j] = new_image_part2[x][y++];
            }
            x++;
            y = 0;
        }
    }
    if (part2 == 3)
    {// this loop to move from part three to two.
        int x = 0 , y = 0;
        for (int i = 0; i < SIZE/2; i++)
        {
            for (int j = SIZE/2; j < SIZE; j++)
            {
                image[i][j] = new_image_part3[x][y++];
            }
            x++;
            y = 0;
        }
    }
    if (part2 == 4)
    {// this loop to move from part four to two.
        int x = 0 , y = 0;
        for (int i = 0; i < SIZE/2; i++)
        {
            for (int j = SIZE/2; j < SIZE; j++)
            {
                image[i][j] = new_image_part4[x][y++];
            }
            x++;
            y = 0;
        }
    }
    if (part3 == 1)
    {// this loop to move from part one to three.
        int x = 0 , y = 0;
        for (int i = SIZE/2; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE/2; j++)
            {
                image[i][j] = new_image_part1[x][y++];
            }
            x++;
            y = 0;
        }
    }
    if (part3 == 2)
    {// this loop to move from part two to three.
        int x = 0 , y = 0;
        for (int i = SIZE/2; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE/2; j++)
            {
                image[i][j] = new_image_part2[x][y++];
            }
            x++;
            y = 0;
        }
    }
    if (part3 == 3)
    {// this loop to move from part three to three.
        int x = 0 , y = 0;
        for (int i = SIZE/2; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE/2; j++)
            {
                image[i][j] = new_image_part3[x][y++];
            }
            x++;
            y = 0;
        }
    }
    if (part3 == 4)
    {// this loop to move from part four to three.
        int x = 0 , y = 0;
        for (int i = SIZE/2; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE/2; j++)
            {
                image[i][j] = new_image_part4[x][y++];
            }
            x++;
            y = 0;
        }
    }
    if (part4 == 1)
    {// this loop to move from part one to four.
        int x = 0 , y = 0;
        for (int i = SIZE/2; i < SIZE; i++)
        {
            for (int j = SIZE/2; j < SIZE; j++)
            {
                image[i][j] = new_image_part1[x][y++];
            }
            x++;
            y = 0;
        }
    }
    if (part4 == 2)
    {// this loop to move from part two to four.
        int x = 0 , y = 0;
        for (int i = SIZE/2; i < SIZE; i++)
        {
            for (int j = SIZE/2; j < SIZE; j++)
            {
                image[i][j] = new_image_part2[x][y++];
            }
            x++;
            y = 0;
        }
    }
    if (part4 == 3)
    {// this loop to move from part three to four.

        int x = 0 , y = 0;
        for (int i = SIZE/2; i < SIZE; i++)
        {
            for (int j = SIZE/2; j < SIZE; j++)
            {
                image[i][j] = new_image_part3[x][y++];
            }
            x++;
            y = 0;
        }
    }
    if (part4 == 4)
    {// this loop to move from part four to four.
        int x = 0 , y = 0;
        for (int i = SIZE/2; i < SIZE; i++)
        {
            for (int j = SIZE/2; j < SIZE; j++)
            {
                image[i][j] = new_image_part4[x][y++];
            }
            x++;
            y = 0;
        }
    }
}
// record (part1/part2/part3/part4) to record each quarter in new array.
void record_part1()     //Author: Youssef Abdelghafar Abdeltawab
{
    int s=0,p=0;
    for (int i = 0; i < SIZE/2; ++i) {
        for (int j = 0; j < SIZE/2; ++j)
        {
            new_image_part1[p][s++] = image[i][j];
        }
        p++;
        s=0;
    }
}
void record_part2()         //Author: Youssef Abdelghafar Abdeltawab
{
    int s=0,p=0;
    for (int i = 0; i < SIZE/2; ++i) {
        for (int j = SIZE/2; j < SIZE; ++j) {
            new_image_part2[p][s++] = image[i][j];
        }
        p++;
        s=0;
    }
}
void record_part3()     //Author: Youssef Abdelghafar Abdeltawab
{
    int s = 0 , p = 0;
    for (int i = SIZE/2; i < SIZE; ++i) {
        for (int j = 0; j < SIZE/2; ++j) {
            new_image_part3[p][s++] = image[i][j];
        }
        p++;
        s = 0;
    }
}

void record_part4()         //Author: Youssef Abdelghafar Abdeltawab
{
    int s = 0, p = 0;
    for (int i = SIZE/2; i < SIZE; ++i) {
        for (int j = SIZE/2; j < SIZE; ++j) {
            new_image_part4[p][s++] = image[i][j];
        }
        p++;
        s = 0;
    }
}
void blur() { //Author: Abdallah Hussein Ibrahim Hussein - 20210235
  for (int i = 0; i <= SIZE; i++)
{
  for (int j = 0; j <= SIZE; j++)
  {
      image2[i][j] = image[i][j];     // make another image that has the same pixels as the first image to avoid calculating a blurred pixel.
  }
}
// entire image without the border
for (int i = 1; i < SIZE-3; i++)
{
  for (int j = 1; j < SIZE-3; j++)
  {         // all entire pixels
      image[i][j] = ((image2[i-1][j-1]+image2[i-1][j]+image2[i-1][j+1]+image2[i-1][j+2]+image2[i-1][j+3]+image2[i][j-1]+image2[i][j]+image2[i][j+1]+image2[i][j+2]+image2[i][j+3]+image2[i+1][j-1]+image2[i+1][j]+image2[i+1][j+1]+image2[i+1][j+2]+image2[i+1][j+3]+image2[i+2][j-1]+image2[i+2][j]+image2[i+2][j+1]+image2[i+2][j+2]+image2[i+2][j+3]+image2[i+3][j-1]+image2[i+3][j]+image2[i+3][j+1]+image2[i+3][j+2]+image2[i+3][j+3])/25);
                            //  0 0          0 1             0 2           1 0             1 1             1 2           2 0           2 1                 2 2
  }
}
// last rows
for (int i = 253; i < SIZE; i++) {
      for (int j = 1; j < SIZE-3; j++) {
          // // get all pixels above last pixels
          image[i][j] = ((image2[i-1][j-1]+image2[i-1][j]+image2[i-1][j+1]+image2[i-1][j+2]+image2[i-1][j+3]+image2[i][j-1]+image2[i][j]+image2[i][j+1]+image2[i][j+2]+image2[i][j+3]+image2[i-4][j-1]+image2[i-4][j]+image2[i-4][j+1]+image2[i-4][j+2]+image2[i-4][j+3]+image2[i-2][j-1]+image2[i-2][j]+image2[i-2][j+1]+image2[i-2][j+2]+image2[i-2][j+3]+image2[i-3][j-1]+image2[i-3][j]+image2[i-3][j+1]+image2[i-3][j+2]+image2[i-3][j+3])/25);
    }   
  }
  // firt rows
for (int i = 0; i < 3; i++) {
      for (int j = 1; j < SIZE-3; j++) {
          // get all pixels below first pixels
        image[i][j] = ((image2[i+1][j+1]+image2[i+1][j]+image2[i+1][j+1]+image2[i+1][j+2]+image2[i+1][j+3]+image2[i][j-1]+image2[i][j]+image2[i][j+1]+image2[i][j+2]+image2[i][j+3]+image2[i+1][j-1]+image2[i+1][j]+image2[i+1][j+1]+image2[i+1][j+2]+image2[i+1][j+3]+image2[i+2][j-1]+image2[i+2][j]+image2[i+2][j+1]+image2[i+2][j+2]+image2[i+2][j+3]+image2[i+3][j-1]+image2[i+3][j]+image2[i+3][j+1]+image2[i+3][j+2]+image2[i+3][j+3])/25);
      }
  }
  // first columns
for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < 3; j++) {
        if(i==255){ // if it's the last row then get the pixels above this row because there aren't any rows below
          image[i][j] = ((image2[i-1][j-1]+image2[i-1][j]+image2[i-1][j+1]+image2[i-1][j+2]+image2[i-1][j+3]+image2[i][j-1]+image2[i][j]+image2[i][j+1]+image2[i][j+2]+image2[i][j+3]+image2[i-4][j-1]+image2[i-4][j]+image2[i-4][j+1]+image2[i-4][j+2]+image2[i-4][j+3]+image2[i-2][j-1]+image2[i-2][j]+image2[i-2][j+1]+image2[i-2][j+2]+image2[i-2][j+3]+image2[i-3][j-1]+image2[i-3][j]+image2[i-3][j+1]+image2[i-3][j+2]+image2[i-3][j+3])/25);}
        else {
          image[i][j] = ((image2[i+1][j-1]+image2[i+1][j]+image2[i+1][j+1]+image2[i+1][j+2]+image2[i+1][j+3]+image2[i][j-1]+image2[i][j]+image2[i][j+1]+image2[i][j+2]+image2[i][j+3]+image2[i+1][j-1]+image2[i+1][j]+image2[i+1][j+1]+image2[i+1][j+2]+image2[i+1][j+3]+image2[i+2][j-1]+image2[i+2][j]+image2[i+2][j+1]+image2[i+2][j+2]+image2[i+2][j+3]+image2[i+3][j-1]+image2[i+3][j]+image2[i+3][j+1]+image2[i+3][j+2]+image2[i+3][j+3])/25);}
    }   
  }
  // last columns
for (int i = 0; i < SIZE; i++) {
      for (int j = 253; j < SIZE; j++) {
        if(i == 255){       // if it's the last row then get the pixels above this row because there aren't any rows below
          image[i][j] = ((image2[i-1][j-1]+image2[i-1][j]+image2[i-1][j+1]+image2[i-1][j+2]+image2[i-1][j+3]+image2[i][j-1]+image2[i][j]+image2[i][j+1]+image2[i][j+2]+image2[i][j+3]+image2[i-1][j-1]+image2[i-1][j]+image2[i-1][j+1]+image2[i-1][j+2]+image2[i-1][j+3]+image2[i-2][j-1]+image2[i-2][j]+image2[i-2][j+1]+image2[i-2][j+2]+image2[i-2][j+3]+image2[i-3][j-1]+image2[i-3][j]+image2[i-3][j+1]+image2[i-3][j+2]+image2[i-3][j+3])/25);}
        else {
        image[i][j] = ((image2[i+1][j-1]+image2[i+1][j]+image2[i+1][j+1]+image2[i+1][j+2]+image2[i+1][j+3]+image2[i][j-1]+image2[i][j]+image2[i][j+1]+image2[i][j+2]+image2[i][j+3]+image2[i+1][j-1]+image2[i+1][j]+image2[i+1][j+1]+image2[i+1][j+2]+image2[i+1][j+3]+image2[i+2][j-1]+image2[i+2][j]+image2[i+2][j+1]+image2[i+2][j+2]+image2[i+2][j+3]+image2[i+3][j-1]+image2[i+3][j]+image2[i+3][j+1]+image2[i+3][j+2]+image2[i+3][j+3])/25);}
    }   
  }
}
