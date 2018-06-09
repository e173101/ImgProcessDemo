#include <QCoreApplication>
#include <QtCore>


//main.cpp Demo for img process using OpenCV and Qt
//Lai Yongtian <lai@atian.me> 2018-4-5

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "../PhoneHackCV/jumponejump.h"

#define inputPath "C:/Users/Public/Pictures/inputImage/"
#define outputPath "C:/Users/Public/Pictures/outputImage/"

using namespace cv;

Mat cropMat16(int n, Mat &mat)
{
    int y=n/4;
    int x=n%4;
    int dx=mat.cols/4;
    int dy=mat.rows/4;
    Rect roi;
    roi.x=x*dx;
    roi.y=y*dy;
    roi.width=dx;
    roi.height=dy;
    Mat m=mat(roi);
    return m;
}

int function(Mat &mat)
{
    //GaussianBlur(mat,mat,Size(5,5),0);
    //cvtColor(mat,mat,CV_RGB2GRAY);
    //Canny(mat,mat,50,100);
    return 0;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //got input file
    QDir dir(inputPath);
    if(!dir.exists())
    {
        qDebug() << inputPath << "is not a avaliable path!" << endl;
        return a.exec();
    }

    QStringList nameFilters ;
    nameFilters << "*.jpg" << "*.png";
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable,QDir::Name);

    int outputFileIndex = 1;
    for(int fileIndex = 0; fileIndex < files.size(); ++fileIndex)
    {
        Mat mat = cv::imread((inputPath+files[fileIndex]).toStdString());
        function(mat);
        for(int i=0;i<16;i++)
        {
            imwrite((outputPath+QString::number(outputFileIndex)+".jpg").toStdString(),cropMat16(i,mat));
            outputFileIndex++;
        }
        qDebug((outputPath+files[fileIndex]).toAscii());
    }

    qDebug("Process end");

    return a.exec();
}
