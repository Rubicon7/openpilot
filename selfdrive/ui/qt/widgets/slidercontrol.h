#pragma once

#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>

#include "common/params.h"

class SliderControl : public QWidget {
  Q_OBJECT

public:
  SliderControl(const QString &param, const QString &title, const QString &desc,
                int min = 0, int max = 100, int step = 1, QWidget *parent = nullptr);

private:
  QString param_name;
  QLabel *value_label;
  QSlider *slider;

private slots:
  void valueChanged(int value);
};
