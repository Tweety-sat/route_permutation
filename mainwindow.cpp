#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QChar"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Шифр Маршрутной Перестановки");

}

MainWindow::~MainWindow()
{
    delete ui;
}
QString MainWindow::Encrypt(QString input_string)
{
    int size_height, key_width =8;
    QString space = "";

    //Определяем размерность таблички
    if (key_width >= input_string.length()&&input_string.length()>1)
        key_width = input_string.length() / 2;
    if (input_string.length()<7&&input_string.length()>4)
        key_width=3;

    if (input_string.length() % key_width != 0)
            size_height = input_string.length() / key_width + 1;
        else
            size_height = input_string.length() / key_width;

     //Инициализируем массив
     QChar** arr = new QChar* [size_height];
        for (int i = 0; i < size_height; i++)
            arr[i] = new QChar[key_width];

     //Заполняем недостаток размерности пробелами
     int spac = size_height * key_width - input_string.length(); //Кол-во необходимых пустых клеток
     if (input_string.length() < size_height * key_width)
        for (int q = 0; q < spac; q++)
            space += " ";
     input_string += space;

     //Заполняем матрицу значениями
     for (int i = 0; i < size_height; i++)
        {
            for (int j = 0; j < key_width; j++)
            {
            if (i % 2 == 0)
                arr[i][j] = (QChar)input_string[i * key_width + j];
            else
                arr[i][key_width - j - 1] = (QChar)input_string[i * key_width + j];
            }
        }
      QString EncryptedMess;
      for (int i = 0; i < key_width; i++)
        {
            for (int j = 0; j < size_height; j++)
            {
                if (i % 2 == 0)
                    EncryptedMess += arr[size_height - j - 1][i];
                else
                    EncryptedMess += arr[j][i];
            }
      }
    return EncryptedMess;
}

QString MainWindow::Decrypt(QString input_string)
{
    int key_width = 8;
        if ((key_width >= input_string.length()&&input_string.length()>1))
            key_width = input_string.length() / 2;
        if (input_string.length()<7&&input_string.length()>4)
            key_width=3;

        int size_height = input_string.length() / key_width;


        QChar** arr = new QChar* [size_height];
        for (int i = 0; i < size_height; i++)
            arr[i] = new QChar[key_width];

        int k = 0;

        QString DecryptedMess;
        for (int i = 0; i < key_width; i++)
        {
            for (int j = 0; j < size_height; j++)
            {
                if (i % 2 == 0)
                    arr[size_height - j - 1][i]= input_string[k];
                else
                    arr[j][i]= input_string[k];
                k++;
            }
        }

        for (int i = 0; i < size_height; i++)
        {
            for (int j = 0; j < key_width; j++)
            {
                if (i % 2 == 0)
                    DecryptedMess += arr[i][j];
                else
                    DecryptedMess += arr[i][key_width - j - 1];
            }
        }
        return DecryptedMess;
}

void MainWindow::on_EncryptButton_clicked()
{
   QString input_string;
   ui->Decrypt->clear();
   ui->DecryptedMess->clear();
   input_string=ui->encrypt->text();
   ui->EencrypedMess->setText(Encrypt(input_string));
}


void MainWindow::on_DecryptButton_clicked()
{
    QString input_string;
    ui->encrypt->clear();
    ui->EencrypedMess->clear();
    input_string=ui->Decrypt->text();
    ui->DecryptedMess->setText(Decrypt(input_string));
}

void MainWindow::on_pushButton_clicked()
{
    QString input_string;
    input_string=ui->EencrypedMess->text();
    ui->Decrypt->setText(input_string);
    ui->DecryptedMess->setText(Decrypt(input_string));
}

void MainWindow::on_pushButton_2_clicked()
{
    QString input_string;
    input_string=ui->DecryptedMess->text();
    ui->encrypt->setText(input_string);
    ui->EencrypedMess->setText(Encrypt(input_string));
}
