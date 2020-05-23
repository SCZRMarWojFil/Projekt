// g++ img_display.cpp -o img_display `pkg-config opencv --cflags --libs`
// ./img_display dog.jpg

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int sizeofmat(CvMat *mat) {
    return mat->rows * mat->step;
}

int main( int argc, char** argv )
{
    if( argc != 2)
    {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }

    Mat image;
    image = imread(argv[1], IMREAD_COLOR);   // Read the file

    int count = 0;
    cv::Vec3b* ptr;

    for(int i = 0; i < image.rows; i++){
        cv::Vec3b* ptr = image.ptr<cv::Vec3b>(i);
        for(int j = 0; j < image.cols; j++){
            //cv::Vec3b pixelColor = image.at<cv::Vec3b>(i,j);
            // Inverting blue and red values of the pixel
            ptr[j] = cv::Vec3b(ptr[j][2], ptr[j][1], ptr[j][0]);
            //printf("Blue value: %d \n", ptr[j][0]);
            count++;
        }
    }

    printf("%d\n", 3*count);

    int bytess = image.total() * image.elemSize();

    // Converting Mat to CvMat
    CvMat cvMat = image;

    size_t mem_size = sizeofmat(&cvMat);
    printf("Size after loading image %d\n", sizeof(image));
    printf("IMG SIZEEE %d \n", image.cols*image.rows*image.channels());
    printf("rows %d \n", image.rows);
    printf("clos %d \n", image.cols);

    if(! image.data )                              // Check for invalid input
    {
        cout << "Could not open or find the image" << std::endl ;
        return -1;
    }

    // Converting CvMat to Mat
    Mat cos =  cvarrToMat(&cvMat);

    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", cos );                // Show our image inside it.

    int k = waitKey(0); // Wait for a keystroke in the window

    if(k == 's')
    {
        imwrite("kk.jpg", image);
    }

    return 0;
}