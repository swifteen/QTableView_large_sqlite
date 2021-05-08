#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QScrollBar>
#include "tableView.h"
namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
	void on_scrollBar_valueChanged(int page);
private:
    Ui::Form *ui;
    TableView *m_pTableView;
    QScrollBar* m_pScrollBar;
};

#endif // FORM_H
