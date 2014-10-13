//histGray is used to calculate the entropy of a color image

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

float entropy(Mat seq, Size size, int index)
{
  int cnt = 0;
  float entr = 0;
  float total_size = size.height * size.width; //total size of all symbols in an image

  for(int i=0;i<index;i++)
  {
    float sym_occur = seq.at<float>(0, i); //the number of times a sybmol has occured
    
    if(sym_occur>0) //log of zero goes to infinity
      {
        cnt++;
        entr += (sym_occur/total_size)*(log2(total_size/sym_occur));
      }
  }
  cout<<"cnt: "<<cnt<<endl;
  return entr;

}

// myEntropy calculates relative occurrence of different symbols within given input sequence using histogram
Mat myEntropy(Mat seq, int histSize)
{ 

  float range[] = { 0, 256 } ;
  const float* histRange = { range };

  bool uniform = true; 
  bool accumulate = false;

  Mat hist;

  /// Compute the histograms:
  calcHist( &seq, 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate );

  return hist;
}

/**
 * @function main
 */
int main( int, char** argv )
{
  Mat src, converted_image, hist;

  /// Load image
  src = imread( argv[1], 1 );

  if( src.empty() )
    { return -1; }

  /// Establish the number of bins
  int histSize = 256;


  Mat ycrcb[3], hist_y, hist_Cr, hist_Cb;
  cvtColor(src, converted_image, CV_BGR2YCrCb);
  split(converted_image, ycrcb);

    namedWindow( "Original Image", WINDOW_AUTOSIZE );     // Create a window for display.
    imshow( "Original Image", src );                    // Show our image inside it.

    namedWindow( "Y", WINDOW_AUTOSIZE );                  // Create a window for display.
    imshow( "Y", ycrcb[0] );                              // Show our image inside it.

    namedWindow( "Cb", WINDOW_AUTOSIZE );                 // Create a window for display.
    imshow( "Cb", ycrcb[1] );                             // Show our image inside it.

    namedWindow( "Cr", WINDOW_AUTOSIZE );                 // Create a window for display.
    imshow( "Cr", ycrcb[2] );                             // Show our image inside it.


  int hist_w = 512; int hist_h = 400;
  int bin_w = cvRound( (double) hist_w/histSize );

  hist_y = myEntropy(ycrcb[0], histSize);
  hist_Cr = myEntropy(ycrcb[1], histSize);
  hist_Cb = myEntropy(ycrcb[2], histSize);

  cout<<"entropy Y: "<<entropy(hist_y,src.size(), histSize)<<endl;
  cout<<"entropy Cr: "<<entropy(hist_Cr,src.size(), histSize)<<endl;
  cout<<"entropy Cb: "<<entropy(hist_Cb,src.size(), histSize)<<endl;
  
  

  Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

  /// Normalize the result to [ 0, histImage.rows ]
  normalize(hist_y, hist_y, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
  normalize(hist_Cr, hist_Cr, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
  normalize(hist_Cb, hist_Cb, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

  /// Draw histogram
  for( int i = 1; i < histSize; i++ )
  {
      line( histImage, Point( bin_w*(i-1), hist_h - cvRound(hist_y.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(hist_y.at<float>(i)) ),
                       Scalar( 255, 0, 0), 2, 8, 0  );
      line( histImage, Point( bin_w*(i-1), hist_h - cvRound(hist_Cr.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(hist_Cr.at<float>(i)) ),
                       Scalar( 0, 255, 0), 2, 8, 0  );
      line( histImage, Point( bin_w*(i-1), hist_h - cvRound(hist_Cb.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(hist_Cb.at<float>(i)) ),
                       Scalar( 0, 0, 255), 2, 8, 0  );
  }

  /// Display
  namedWindow("calcHist Demo", WINDOW_AUTOSIZE );
  imshow("calcHist Demo", histImage );

  waitKey(0);

  src.release();
  hist.release();
  histImage.release();

  return 0;

}