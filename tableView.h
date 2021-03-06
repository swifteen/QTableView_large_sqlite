#ifndef _TABLE_VIEW_H
#define _TABLE_VIEW_H
#include <QTableView>
#include <QVariant>
#include "tableModel.h"

class TableView : public QTableView
{
    Q_OBJECT

public:
    TableView(QWidget *parent = nullptr);
	void previousPage();		
	void nextPage();
	void setCurPage(int page);
	int getCurPage();
	int getTotalPage();
private:		
	void initModel();
private:
	TableModel* m_pTableModel;
};

#endif 
