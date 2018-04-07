/*
 * main.cpp Demo for img process using OpenCV and Qt
 * This program do the "function" to all the .jpg file in inputPath
 * Lai Yongtian <lai@atian.me> 2018-4-5
 *
 */

#include <QCoreApplication>
#include <QtCore>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#define inputPath "C:/Users/Public/Pictures/inputImage/"
#define outputPath "C:/Users/Public/Pictures/outputImage/"

using namespace cv;

int function(Mat &mat)
{
    GaussianBlur(mat,mat,Size(5,5),0);
    cvtColor(mat,mat,CV_RGB2GRAY);
    Canny(mat,mat,50,100);
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
    nameFilters << "*.jpg";
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable,QDir::Name);

    for(int fileIndex = 0; fileIndex < files.size(); ++fileIndex)
    {
        Mat mat = cv::imread((inputPath+files[fileIndex]).toStdString());
        function(mat);
        imwrite((outputPath+files[fileIndex]).toStdString(),mat);
        qDebug((outputPath+files[fileIndex]).toAscii());
    }

    qDebug("Process end");

    return a.exec();
}
