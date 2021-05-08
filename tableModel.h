#ifndef _TABLE_MODEL_H
#define _TABLE_MODEL_H
#include <QSqlTableModel>
#include <QVariant>

class TableModel : public QSqlTableModel
{
    Q_OBJECT

public:
    TableModel(QObject *parent = nullptr);
	void previousPage();		
	void nextPage();
protected:
	QString selectStatement() const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
	int queryRecordSize() const;		
	void updateTotalPageNum() const;
private:
    mutable int 	m_iRecordTotal;//当前过滤后的记录总数
    mutable int 		m_iCurPageIndex;//保存当前页号,从0开始
    mutable 	int m_iTotalPageNum;//保存总页数,从1开始
    mutable 	bool m_bUpdateSize;//是否更新总记录数，只有当filter()改变时就需要更新，或者刚启动时
    int m_iMaxTableRow;//表格的最大行数
};

#endif
