#include "tableModel.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

TableModel::TableModel(QObject *parent):QSqlTableModel(parent)
{
    m_iCurPageIndex = 0;
    m_iRecordTotal = 0;
    m_iTotalPageNum = 0;
    m_bUpdateSize = true;
    m_iMaxTableRow = 10;
	
    setTable("person");
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    setHeaderData(1, Qt::Horizontal, QObject::tr("First name"));
    setHeaderData(2, Qt::Horizontal, QObject::tr("Last name"));

    beginResetModel();
    m_iRecordTotal = queryRecordSize();
    fileCount = 0;
    endResetModel();
}

int TableModel::queryRecordSize() const
{
    QSqlQuery sqlQuery(QSqlTableModel::database());

    if(!sqlQuery.exec(QSqlTableModel::selectStatement()))
    {
        qDebug()<< __FILE__ << __FUNCTION__ << __LINE__<<database().lastError();
    }

    int size = 0;

    if(sqlQuery.last())
    {
        size = sqlQuery.at() + 1;
    }

#if 0
https://stackoverflow.com/questions/26495049/qsqlquery-size-always-returns-1
    int size = sqlQuery.size();//is not supported with SQLite
#endif
    return size;
}

void TableModel::updateTotalPageNum() const
{
    m_iRecordTotal = queryRecordSize();

    if(m_iRecordTotal <= 0)
    {
        m_iRecordTotal = 0;
        m_iTotalPageNum = 0;
        return;
    }

    m_iTotalPageNum = m_iRecordTotal/m_iMaxTableRow;

    if(m_iRecordTotal%m_iMaxTableRow > 0)
    {
        m_iTotalPageNum++;
    }

    m_iCurPageIndex = 0;//这里需要重置一下
}

void TableModel::previousPage()
{
    if(m_iCurPageIndex > 0)
    {
        m_iCurPageIndex--;
        select();
    }
}

void TableModel::nextPage()
{
    if(m_iCurPageIndex < m_iTotalPageNum - 1)
    {
        m_iCurPageIndex++;
        select();
    }
}

void TableModel::setCurPage(int page)
{
	if((0 <= page) && (page < m_iTotalPageNum))
    {
        m_iCurPageIndex = page;
        select();
    }
}

int TableModel::getCurPage()
{
	return m_iCurPageIndex;
}

int TableModel::getTotalPage()
{
	return m_iTotalPageNum;
}


//把sql语句加工一下，根据页数最多只显示TABLE_MAX_ROW条记录
QString TableModel::selectStatement() const
{
    if(m_bUpdateSize)
    {
        updateTotalPageNum();
        m_bUpdateSize = false;
    }

    QString queryStr = QSqlTableModel::selectStatement();
    //只查询TABLE_MAX_ROW条，并且加上偏移
    queryStr += QString(" LIMIT %1 OFFSET %2").arg(m_iMaxTableRow).arg(m_iCurPageIndex*m_iMaxTableRow);
    return queryStr;
}

/*
	Returns the data for the given role and section in the header with the specified orientation.
	For horizontal headers, the section number corresponds to the column number.
	Similarly, for vertical headers, the section number corresponds to the row number.
*/
QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch(role)
    {
        case Qt::TextAlignmentRole:
            return QVariant(Qt::AlignCenter | Qt::AlignVCenter);

        case Qt::DisplayRole:
        {
            if(Qt::Vertical == orientation)
            {
                return section + m_iCurPageIndex*m_iMaxTableRow + 1;//section从0开始，真实行号从1开始，这里需要加1
            }
            break;
        }

        default:
            break;
    }

    return QSqlTableModel::headerData(section,orientation,role);
}

#if 0
int TableModel::rowCount(const QModelIndex & /* parent */) const
{
    return fileCount;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_iRecordTotal || index.row() < 0)
        return QVariant();

//    if (role == Qt::BackgroundRole) {
//        int batch = (index.row() / 100) % 2;
//        if (batch == 0)
//            return qApp->palette().base();
//        else
//            return qApp->palette().alternateBase();
//    }
    return QSqlTableModel::data(index,role);
}

bool TableModel::canFetchMore(const QModelIndex & /* index */) const
{
	qDebug()<<__FILE__<<__FUNCTION__<<__LINE__<<fileCount;
    if (fileCount < m_iRecordTotal)
        return true;
    else
        return false;
}
//![1]

//![2]
void TableModel::fetchMore(const QModelIndex & /* index */)
{
    int remainder = m_iRecordTotal - fileCount;
    int itemsToFetch = qMin(100, remainder);

    if (itemsToFetch <= 0)
        return;

    beginInsertRows(QModelIndex(), fileCount, fileCount+itemsToFetch-1);

    fileCount += itemsToFetch;

    endInsertRows();
	qDebug()<<__FILE__<<__FUNCTION__<<__LINE__<<itemsToFetch<<fileCount;

//    emit numberPopulated(itemsToFetch);
}
#endif

