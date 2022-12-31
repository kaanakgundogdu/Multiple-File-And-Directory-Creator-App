#include "widget.h"
#include "./ui_widget.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDirIterator>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::show_dirs_content(){
    QDirIterator it(current_path,QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    ui->content_list_widget->clear();
    while (it.hasNext()) {
        ui->content_list_widget->addItem(it.next());
    }
}

bool Widget::creat_dir(QString dir_path)
{
    QDir dir(dir_path);
    int spin_box_value=ui->spinBox->value();

    for (int i = 0; i < spin_box_value; ++i) {
        if (QDir(dir_path + QString::number(i)).exists())
            return false;
        if (!dir.mkpath(dir_path + QString::number(i)))
            return false;
    }
    return true;
}


bool Widget::create_file(QString filePath)
{
    QFile file;
    int spin_box_value=ui->spinBox->value();

    for (int i = 0; i < spin_box_value; ++i) {

        file.setFileName(filePath + QString::number(i));
        if(file.exists() || !file.open(QIODevice::WriteOnly|QIODevice::Text))
            return false;
        file.close();
    }
    return true;

}
void Widget::on_chose_dir_button_clicked()
{
    QString file_name=QFileDialog::getExistingDirectory(this,"Choose Directory");
    if (file_name.isEmpty()) {
        return;
    }
    current_path=file_name;
    ui->directory_line->setText(file_name);
    show_dirs_content();
}

void Widget::on_create_dir_button_clicked()
{
    QString dir_name= ui->file_name_line->text();
    QString dir_path=ui->directory_line->text();

    if (dir_name.isEmpty() || dir_path.isEmpty()) {
        QMessageBox::critical(this,"Message","File/Dir name or Directory empty.");
        return;
    }
    if(creat_dir(dir_path+ "/" +dir_name))
        QMessageBox::information(this,"Directories Created","Successfully created.");
    else
        QMessageBox::critical(this,"Message","Dir allready exists.");
}

void Widget::on_create_file_button_clicked()
{
    QString dir_name= ui->file_name_line->text();
    QString dir_path=ui->directory_line->text();
    if (dir_name.isEmpty() || dir_path.isEmpty()) {
        QMessageBox::critical(this,"Message","File/Dir name or Directory empty.");
        return;
    }
    if(create_file(dir_path+ "/" +dir_name))
        QMessageBox::information(this,"Files Created","Successfully created.");

    else
        QMessageBox::critical(this,"Message","File allready exists.");
}
