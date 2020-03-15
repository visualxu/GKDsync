#ifndef WARNING_FILE_AND_CATEGORY_H
#define WARNING_FILE_AND_CATEGORY_H

#include <QDialog>

namespace Ui {
class warning_file_and_category;
}

class warning_file_and_category : public QDialog
{
    Q_OBJECT

public:
    explicit warning_file_and_category(QWidget *parent = nullptr);
    ~warning_file_and_category();

private:
    Ui::warning_file_and_category *ui;
};

#endif // WARNING_FILE_AND_CATEGORY_H
