#include "connection.h"

#include <QApplication>
#include <QSqlTableModel>
#include <QTableView>

#include <stdlib.h>
#include "tableView.h"
#include "form.h"


#include <QApplication>
#include <QTableView>
#include <QStandardItemModel>
#include <QScrollBar>

#if 0
class WideScrollBar: public QScrollBar
{
public:
    WideScrollBar(QWidget *p = 0): QScrollBar(p)
    {
        setStyleSheet( "QScrollBar:vertical { width: 25px; } ");
    }
};


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QStandardItemModel model(10, 3);
    for (int i = 0; i < model.rowCount(); ++i) {
        for (int j = 0; j < model.columnCount(); ++j) {
            QStandardItem *item = new QStandardItem(QString("%1, %2").arg(i).arg(j));
            model.setItem(i, j, item);
        }
    }

    QTableView view;
    view.setModel(&model);
    view.setVerticalScrollBar(new WideScrollBar(&view));
    view.show();

    return app.exec();
}
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    if (!createConnection())
        return -1;

    Form *view1 = new Form;
//	view1->setFixedSize(600, 600);
    view1->show();

    return app.exec();
}
