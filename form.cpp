#include "form.h"
#include "ui_form.h"
#include <QBoxLayout>
#include <QDebug>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    m_pTableView = new TableView;
    m_pScrollBar = new QScrollBar;
	connect(m_pScrollBar, &QScrollBar::valueChanged, this, &Form::on_scrollBar_valueChanged);
	m_pScrollBar->setOrientation(Qt::Vertical);
	int iTotalPage = m_pTableView->getTotalPage();
	if(iTotalPage > 0)
	{
		m_pScrollBar->setRange(0,iTotalPage);
		m_pScrollBar->setValue(0);
	}
	else
	{
		m_pScrollBar->hide();
	}
    ui->frame->layout()->addWidget(m_pTableView);
    ui->frame->layout()->addWidget(m_pScrollBar);
	
    ((QBoxLayout*)(ui->frame->layout()))->setStretch(0, 1);
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{
    if(m_pTableView){
        m_pTableView->previousPage();
		m_pScrollBar->setValue(m_pTableView->getCurPage());
	}
}

void Form::on_pushButton_2_clicked()
{
    if(m_pTableView){
        m_pTableView->nextPage();
		m_pScrollBar->setValue(m_pTableView->getCurPage());
	}
}

void Form::on_scrollBar_valueChanged(int page)
{
    if(m_pTableView)
		m_pTableView->setCurPage(page);
}


