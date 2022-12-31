#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_chose_dir_button_clicked();

    void on_create_dir_button_clicked();

    void on_create_file_button_clicked();

private:
    Ui::Widget *ui;

    QString current_path;
    void show_dirs_content();
    bool creat_dir(QString dir_path);
    bool create_file(QString filePath);
};
#endif // WIDGET_H
