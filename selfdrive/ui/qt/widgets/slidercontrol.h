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
                float min = 0.0, float max = 1.0, float step = 0.1, QWidget *parent = nullptr);

private:
  QString param_name;
  QLabel *value_label;
  QSlider *slider;
  float min_val;
  float step_size;

private slots:
  void valueChanged(int step_index);
};
