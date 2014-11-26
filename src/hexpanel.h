/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#ifndef SRC_HEXPANEL_H_
#define SRC_HEXPANEL_H_

#include "./hexfilemodelpanel.h"
#include "./hexpanelitemdelegate.h"

// TODO(txwiknger): Make width more flexible due to font etc
#define HEXPANEL_DEFAULT_COLUMN_WIDTH 25

/**
 * @brief The HexPanel class
 */
class HexPanel : public HexFileModelPanel
{
    Q_OBJECT
 public:
    explicit HexPanel(QWidget *parent = 0);
    ~HexPanel();

 signals:

 public slots:

 private:
    void formatPanel();
};

#endif  // SRC_HEXPANEL_H_
