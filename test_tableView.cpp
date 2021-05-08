#include "connection.h"

#include <QApplication>
#include <QSqlTableModel>
#include <QTableView>

#include <stdlib.h>
#include "tableView.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    if (!createConnection())
        return -1;

    TableView *view1 = new TableView;
    view1->show();

    return app.exec();
}
