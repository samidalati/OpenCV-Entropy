// this program calcuate the entropy of a grayscaled image without using calcHist
#include <stdlib.h>
#include <stdio.h>
#include <cv.h>
#include <highgui.h>
#include <math.h> 


using namespace cv;
using namespace std;

#define histSize 256

Mat symb = Mat::zeros(1, histSize, CV_32FC1);


// myEntropy calculates relative occurrence of different symbols within given input sequence
void myEntropy(Mat seq)
{	
	int index = 0;

	for(int i = 0;i < seq.cols;i++){
	    for(int j = 0;j < seq.rows;j++){
	    		int y = (seq.at<Vec3b>(i, j)).val[0];
	    		//cout<<"y: "<<(symb.at<float>(0, y))<<endl;
	    		if(y>histSize)
	    			cout<<"y>histSize"<<y;
	    		symb.at<float>(0, y)++;
	    		//cout<<symb.at<float>(0, y)<<endl;
	    		
	        }
	  }
	

	for(int i=0;i<histSize;i++){
		float y = symb.at<float>(0,i);
		cout<<"symbol: "<<i<<" 	was repeated: "<<y<<endl;
	}

}


//entropy(), given a vector of probabilities, calculates it’s entropy
//where seq is a Mat of unique symbols, size is total size of the original image, and index is the number of unique symbols in seq
float entropy(Mat seq, Size size, int index)
{
	float entr = 0;
	float total_size = size.height * size.width; //total size of all symbols in an image
	cout<<"#index: "<<index<<" total_size: "<<total_size<<endl; 
	for(int i=0;i<index;i++)
	{
		float sym_occur = (seq.at<float>(0, i)); //the number of times a sybmol has occured
		if(sym_occur > 0)
			entr += (sym_occur/total_size)*(log2(total_size/sym_occur));
		cout<<sym_occur<<";"<<endl;
	}
	return entr;
}


int main(int argc, char *argv[])
{
	Mat src;
	if( argc != 2)
    {
     cout <<" Usage: ./myHist ImageToCalcEntropy" << endl;
     return -1;
    }

    src = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file

    if(! src.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

	//cout << "M = "<< endl << " "  << image << endl << endl; //use to print all symbols in image
	cout << " M Size: " << src.size() << endl;
	
	myEntropy(src);
	
	cout<<"entropy: "<<entropy(symb, src.size(), histSize )<<endl;

	// release the image
	src.release();
	symb.release();

  return 0;

}
