#include <QCoreApplication>
#include <QtCore>


#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "../PhoneHackCV/jumponejump.h"

#define targetPath "C:/Users/Public/Pictures/targetImage/"
#define outputPath "C:/Users/Public/Pictures/jumpOneJump/"


using namespace cv;
using namespace std;



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //method
    JumpOneJump joj(0.45);
    Point guyLoc, benchLoc;

    //got target file
    QDir dir(targetPath);
    if(!dir.exists()) return a.exec();

    QStringList nameFilters ;
    nameFilters << "*.jpg";
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable,QDir::Name);

    for(int fileIndex = 0; fileIndex < files.size(); ++fileIndex)
    {
        cv::Mat mat = cv::imread((targetPath+files[fileIndex]).toStdString());
        /*
         * do something here
         * mat
         */
        //
        //;
        guyLoc = joj.matchGuy(mat);
        benchLoc = joj.matchBench(guyLoc);
        cv::imwrite((outputPath+files[fileIndex]).toStdString(),joj.matCooked);
        qDebug((outputPath+files[fileIndex]).toAscii());
    }

    qDebug("end");

    return a.exec();
}
