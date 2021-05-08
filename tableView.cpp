#include "tableView.h"
#include <QScrollBar>

TableView::TableView(QWidget *parent):QTableView(parent)
{
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	initModel();
}

void TableView::initModel()
{
	m_pTableModel = new TableModel;
    setModel(m_pTableModel);
    m_pTableModel->select();
}
