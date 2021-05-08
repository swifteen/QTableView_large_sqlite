#include "tableView.h"
#include <QScrollBar>
#include <QDebug>

TableView::TableView(QWidget *parent):QTableView(parent)
{
	//为了自定义控制滚动条，禁用自带的
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	initModel();
}

void TableView::initModel()
{
	m_pTableModel = new TableModel;
    setModel(m_pTableModel);
    m_pTableModel->select();
}

void TableView::previousPage()
{
    if(m_pTableModel)
    {
		m_pTableModel->previousPage();
    }
}

void TableView::nextPage()
{
    if(m_pTableModel)
    {
		m_pTableModel->nextPage();
    }
}

void TableView::setCurPage(int page)
{
    if(m_pTableModel)
    {
		m_pTableModel->setCurPage(page);
    }
}

int TableView::getCurPage()
{
    if(m_pTableModel)
    {
		return m_pTableModel->getCurPage();
    }
	return 0;
}

int TableView::getTotalPage()
{
    if(m_pTableModel)
    {
		return m_pTableModel->getTotalPage();
    }
	return 0;
}

