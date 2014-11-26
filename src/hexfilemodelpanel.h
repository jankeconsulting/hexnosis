/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#ifndef SRC_HEXFILEMODELPANEL_H_
#define SRC_HEXFILEMODELPANEL_H_

#include <QTableView>
#include <QHeaderView>
#include <QScrollBar>

// TODO(txwikinger): Make height more flexible due to font etc
#define DEFAULT_ROW_HEIGHT 15

/**
 * @brief The HexFileModelPanel class
 */
class HexFileModelPanel : public QTableView
{
    Q_OBJECT
 public:
    explicit HexFileModelPanel(QWidget *parent = 0);
    ~HexFileModelPanel();
    void calculateMinimumWidth();

 signals:

 public slots:
};

#endif  // SRC_HEXFILEMODELPANEL_H_
