#include "hexfilemodelpanel.h"
#include <QDebug>

HexFileModelPanel::HexFileModelPanel(QWidget *parent) :
    QTableView(parent)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);
    setShowGrid(false);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    verticalHeader()->setDefaultSectionSize(15);

    //    setMouseTracking(true);
    //    viewport()->setMouseTracking(true);
    //    connect(this, SIGNAL(entered(QModelIndex)), this, SLOT(setHighlight(QModelIndex)));
}

HexFileModelPanel::~HexFileModelPanel()
{
    delete itemDelegate();
    delete model();

}

void HexFileModelPanel::calculateMinimumWidth()
{
    int total_width = 0;
    int column_width = 0;
    for(int i = 0; i< model()->columnCount(); i++) {
        column_width += columnWidth(i);
    }
    total_width += column_width;
    total_width += frameWidth()*2;
//    if(verticalHeader()->isVisible())
        total_width += verticalHeader()->width();
    qDebug() << verticalScrollBar()->isVisible();
//    if(verticalScrollBar()->isVisible())
    if(verticalScrollBarPolicy() == Qt::ScrollBarAlwaysOn || verticalScrollBarPolicy() == Qt::ScrollBarAsNeeded)
        total_width += verticalScrollBar()->sizeHint().width();
    setMinimumWidth(total_width);
}

void HexFileModelPanel::setHighlight(QModelIndex index)
{
//    TODO: Implement code to follow mouse cursor in parallel window
//#ifdef DEBUG
//    qDebug() << "HexPanel::setHighlight entered" << index;
//#endif
//#ifdef DEBUG
//    qDebug() << "HexPanel::setHighlight : index->data() = " << index.data(Qt::DisplayRole).toString();
//#endif
    if(index.column() < 16) {

    } else {

    }
}
