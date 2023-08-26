#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    imageName.clear();
    imageName = QFileDialog::getOpenFileName(this,"Open image","","Image Files (*.png *.jpg *.bmp)");
    if(!imageName.isEmpty())
    {
        ui->lineEdit->setText(imageName);
        image.load(imageName);
        ui->label->setPixmap(QPixmap::fromImage(image).scaled(ui->label->width(),ui->label->height()));
    }
    else
    {
        ui->lineEdit->setText("");
        ui->label->setText("Image Here");
    }
    ui->pushButton_3->setEnabled(!imageName.isEmpty()&&!saveName.isEmpty());
}


void MainWindow::on_pushButton_2_clicked()
{
    saveName.clear();
    saveName = QFileDialog::getSaveFileName(this,"Open image","","Text Files (*.h *.c *.cpp)");
    if(!saveName.isEmpty())
    {
        ui->lineEdit_2->setText(saveName);
    }
    else
    {
        ui->lineEdit_2->setText("");
    }

    ui->pushButton_3->setEnabled(!imageName.isEmpty()&&!saveName.isEmpty());
}



void MainWindow::on_pushButton_3_clicked()
{
    qDebug()<<"WIDTH:"<<image.width();
    qDebug()<<"HEIGTH:"<<image.height();
    if(!image.isNull()&&!saveName.isEmpty())
    {
        data.clear();
        if((image.width() % 8)>0)
        {
            image.scaledToWidth((image.width() % 8) * 8);
        }
        if(!compress)
        {
            int bitCount = 0;
            uint8_t byteData = 0;
            for(int y = 0; y < image.height(); y++)
            {
                for(int x = 0; x < image.width(); x++)
                {
                    QRgb pixel = image.pixel(x,y);
                    if(!invertColors)
                    {
                        if(qRed(pixel)>127 || qBlue(pixel) > 127 || qGreen(pixel) > 127)
                        {
                            byteData |= (1 << bitCount);
                        }
                        else
                        {
                            byteData &= ~(1 << bitCount);
                        }
                    }
                    else
                    {
                        if(qRed(pixel)>127 || qBlue(pixel) > 127 || qGreen(pixel) > 127)
                        {
                            byteData &= ~(1 << bitCount);
                        }
                        else
                        {
                            byteData |= (1 << bitCount);
                        }
                    }
                    bitCount++;
                    if(bitCount>7)
                    {
                        data.append(byteData);
                        bitCount = 0;
                        byteData = 0;
                    }
                }
            }
        }
        else
        {
            for(int y = 0; y < image.height(); y++)
            {
                QRgb firstPixel = image.pixel(0,y);
                uint8_t pixelCount = 0;
                uint8_t byteData = 0;
                qDebug()<<"START OF LINE:"<<y;
                for(int x = 0; x < image.width(); x++)
                {
                    QRgb currentPixel = image.pixel(x,y);
                    pixelCount++;
                    if(currentPixel != firstPixel)
                    {
                        byteData = 0;
                        if(!invertColors)
                        {

                            if(qRed(firstPixel)>127 || qBlue(firstPixel) > 127 || qGreen(firstPixel) > 127)
                            {
                                byteData |= (1 << 7);
                            }
                            else
                            {
                                byteData &= ~(1 << 7);
                            }
                        }
                        else
                        {
                            if(qRed(firstPixel)>127 || qBlue(firstPixel) > 127 || qGreen(firstPixel) > 127)
                            {
                                byteData &= ~(1 << 7);
                            }
                            else
                            {
                                byteData |= (1 << 7);
                            }
                        }
                      //  if(pixelCount>1)
                        byteData |= static_cast<uint8_t>(pixelCount-1);
                      //  else
                      //  byteData |= static_cast<uint8_t>(pixelCount);
                      //  qDebug()<<(int8_t)byteData;
                        firstPixel = currentPixel;
                        qDebug()<<"PIXEL:"<<qRed(firstPixel)<<qBlue(firstPixel)<<qGreen(firstPixel)<<x<<y<<pixelCount<<QString::number(byteData,16);
                        data.append(byteData);
                        pixelCount = 0;
                    }
                    else if ((pixelCount >= 128))
                    {
                        byteData = 0;

                        if(!invertColors)
                        {
                            if(qRed(firstPixel)>127 || qBlue(firstPixel) > 127 || qGreen(firstPixel) > 127)
                            {
                                byteData |= (1 << 7);
                            }
                            else
                            {
                                byteData &= ~(1 << 7);
                            }
                        }
                        else
                        {
                            if(qRed(firstPixel)>127 || qBlue(firstPixel) > 127 || qGreen(firstPixel) > 127)
                            {
                                byteData &= ~(1 << 7);
                            }
                            else
                            {
                                byteData |= (1 << 7);
                            }
                        }
                        byteData |= static_cast<uint8_t>(pixelCount-1);
                        firstPixel = currentPixel;
                         data.append(byteData);
                        //qDebug()<<(int8_t)byteData;
                        //qDebug()<<qRed(firstPixel)<<qBlue(firstPixel)<<qGreen(firstPixel)<<x<<y;
                        qDebug()<<"OVERFLOW:"<<qRed(firstPixel)<<qBlue(firstPixel)<<qGreen(firstPixel)<<x<<y<<pixelCount<<QString::number(byteData,16);
                        pixelCount = 0;

                    }
                    else if (x == image.width()-1)
                    {
                        byteData = 0;
//                        pixelCount++;
                        if(!invertColors)
                        {
                            if(qRed(firstPixel)>127 || qBlue(firstPixel) > 127 || qGreen(firstPixel) > 127)
                            {
                                byteData |= (1 << 7);
                            }
                            else
                            {
                                byteData &= ~(1 << 7);
                            }
                        }
                        else
                        {
                            if(qRed(firstPixel)>127 || qBlue(firstPixel) > 127 || qGreen(firstPixel) > 127)
                            {
                                byteData &= ~(1 << 7);
                            }
                            else
                            {
                                byteData |= (1 << 7);
                            }
                        }
                        byteData |= static_cast<uint8_t>(pixelCount-1);
                        firstPixel = currentPixel;
                         data.append(byteData);
                        //qDebug()<<(int8_t)byteData;
                        //qDebug()<<qRed(firstPixel)<<qBlue(firstPixel)<<qGreen(firstPixel)<<x<<y;
                        qDebug()<<"EOL:"<<qRed(firstPixel)<<qBlue(firstPixel)<<qGreen(firstPixel)<<x<<y<<pixelCount<<QString::number(byteData,16);
                        pixelCount = 0;
                    }
                }  
                 qDebug()<<"END OF LINE:"<<y;
            }

        }
    }

    ui->lineEdit_3->setText("Size: " + QString::number(data.size()) + " Bytes");
    QFile file(saveName);
    file.close();
    file.open(QFile::WriteOnly);
    QFileInfo fileInfo(file);
    QDateTime dateTime = QDateTime::currentDateTime();
    QString arrayName = fileInfo.fileName().split(".")[0];
    QString text = "//--------------------------------\n";
    text.append("//THIS FILE GENERATED BY SOFTWARE!\n");
    text.append("//--------------------------------\n");
    if(compress)
        text.append("//THIS FILE IS COMPRESSED BY RLE!\n");
    text.append("//Time generated: ");
    text.append(dateTime.toString());
    text.append("\n");
    text.append("//IMAGE SIZE: ");
    text.append(QString::number(image.width()));
    text.append('x');
    text.append(QString::number(image.height()));
    text.append(" PIXELS.\n");
    text.append("//FILE SIZE: ");
    text.append(QString::number(data.size()));
    text.append(" Bytes.\n");
    text.append("#include <stdint.h>\n");
    text.append("static const uint8_t ");
    text.append(arrayName);
    text.append("[");
    text.append(QString::number(data.size()));
    text.append("] = {\n");
    int byteCount = 0;
    if(!compress)
    {
        for(int y = 0; y < image.height(); y++)
        {
            for(int x = 0; x < image.width()/8; x++)
            {
                text.append("0x");
                QString hexString;
                hexString.setNum(static_cast<uint8_t>(data.at(byteCount)),16);
                text.append(hexString);
                text.append(", ");
                byteCount++;
                if(byteCount >= data.size())
                    break;
            }
            text.append(" //");
            text.append(QString::number(y));
            text.append("\n");
        }
    }
    else
    {
        byteCount = 0;
        for(int y = 0; y < data.size()/16 + 1; y++)
        {
            for(int x = 0; x < 16; x++)
            {
                text.append("0x");
                QString hexString;
                hexString.setNum(static_cast<uint8_t>(data.at(byteCount)),16);
                text.append(hexString);
                text.append(", ");
                byteCount++;
                if(byteCount >= data.size())
                {
                    break;
                }
            }
            text.append(" //");
            text.append(QString::number(y));
            text.append("\n");
        }
    }
    text.append("};");
    text.append("//END OF THE FILE");

    file.write(text.toUtf8());
    file.close();

}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    compress = arg1;
}


void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    invertColors = arg1;
}

