#include "warning_file_and_category.h"
#include "ui_warning_file_and_category.h"

warning_file_and_category::warning_file_and_category(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::warning_file_and_category)
{
    ui->setupUi(this);
    setWindowTitle("注意");
}

warning_file_and_category::~warning_file_and_category()
{
    delete ui;
}
