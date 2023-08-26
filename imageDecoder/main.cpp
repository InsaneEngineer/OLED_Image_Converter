#include <QCoreApplication>
#include <test.h>
#include <QtDebug>
#include<QString>

void ssd1306_DrawCompressedBitmap(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, const uint8_t* bitmap, uint16_t size);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug()<<"OK!";
    ssd1306_DrawCompressedBitmap(0, 0, 128, 64, test, 776);
    return a.exec();
}

void ssd1306_DrawCompressedBitmap(uint8_t x, uint8_t y, uint8_t width, uint8_t heigth, const uint8_t* bitmap, uint16_t size)
{
    uint8_t dx = 0;
    uint8_t row = y;
    uint8_t dy = 0;
    QString rowString = "";
    for(uint16_t byteCount = 0; byteCount < size; byteCount++)
    {
        uint8_t color = (((*(bitmap + byteCount)) >> 7) & 1);
        uint8_t count = (*(bitmap + byteCount)) & 0x7F;
      //  qDebug()<<"COLOR:"<<color;
      //  qDebug()<<"COUNT:"<<count;
      //  qDebug()<<"BYTES:"<<byteCount;
        if(dy >= heigth)
        {
            qDebug()<<"OOOPS!";
            break;
        }
        else
        {

            for(int i = 0; i<= count;i++)
            {

                if(dx>=width-1)
                {
                    qDebug()<<rowString<<"ROW:"<<row<<"WIDTH:"<<dx<<"BYTE:"<<byteCount;
                    rowString.clear();
                    dx = 0;
                    dy++;
                    row++;
                }
                else
                {
                   if(color == 1)
                   {
                    rowString.append("*");
                   }
                   else
                   {
                   rowString.append(" ");
                   }
                   dx++;
                }
            }

        }
    }
}
