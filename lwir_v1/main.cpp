#include <QApplication>
#include <QThread>
#include <QMutex>
#include <QMessageBox>
#include <unistd.h>

#include <QColor>
#include <QLabel>
#include <QtDebug>
#include <QString>
#include <QPushButton>

#include <cstdlib>
#include <iostream>
#include <thread>

#include "LeptonThread.h"
#include "MyLabel.h"

using namespace std;

int main( int argc, char **argv )
{
	int img_w = 640;
	int img_h = 480;
	int win_gap = 10;
	int btn_w = 100;
	int btn_h = 30;	
	
	//create the app
	QApplication a( argc, argv );
	
	QWidget *myWidget = new QWidget;
	//setGeometry(win_Start_position:h,w,window_size:w:h)
	myWidget->setGeometry(400, 300, img_w + win_gap*2, img_h + win_gap*2 + btn_h); 

	//create an image placeholder for myLabel
	//fill the top left corner with red, just bcuz
	QImage myImage;
	myImage = QImage(img_w, img_h, QImage::Format_RGB888);
	
	//create a label, and set it's image to the placeholder
	MyLabel myLabel(myWidget);
	myLabel.setGeometry(win_gap, win_gap, img_w, img_h);
	myLabel.setPixmap(QPixmap::fromImage(myImage));

	//create a FFC button
	QPushButton *button1 = new QPushButton("Perform FFC", myWidget);
	button1->setGeometry((img_w/2) - (btn_w/2), (img_h + win_gap*2 + btn_h) - (btn_h + win_gap/2), btn_w, btn_h);
	
	//create a thread to gather SPI data
	//when the thread emits updateImage, the label should update its image accordingly
	LeptonThread *thread = new LeptonThread();
	
	qDebug() << "start..";
	QObject::connect(thread, SIGNAL(updateImage(QImage)), &myLabel, SLOT(setImage(QImage)));
	
	//connect ffc button to the thread's ffc action
	QObject::connect(button1, SIGNAL(clicked()), thread, SLOT(performFFC()));
	thread->start();
	
	myWidget->show();
	
	return a.exec();
}

