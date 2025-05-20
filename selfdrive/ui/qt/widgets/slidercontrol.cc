#include "slidercontrol.h"

SliderControl::SliderControl(const QString &param, const QString &title, const QString &desc,
                             int min, int max, float step, QWidget *parent)
    : QWidget(parent), param_name(param) {
  QVBoxLayout *layout = new QVBoxLayout(this);

  QLabel *title_label = new QLabel(title, this);
  title_label->setStyleSheet("font-weight: bold;");

  QLabel *desc_label = new QLabel(desc, this);
  desc_label->setWordWrap(true);
  desc_label->setStyleSheet("color: grey; font-size: 35px;");

  value_label = new QLabel(this);

  slider = new QSlider(Qt::Horizontal, this);
  slider->setRange(min, max);
  slider->setSingleStep(step);
  slider->setTickInterval(step);
  slider->setTickPosition(QSlider::TicksBelow);

  layout->addWidget(title_label);
  layout->addWidget(desc_label);
  layout->addWidget(slider);
  layout->addWidget(value_label);

  Params params;
  bool ok = false;
  int val = QString::fromStdString(params.get(param.toStdString())).toInt(&ok);
  if (!ok) val = max;
  slider->setValue(val);
  value_label->setText(QString::number(val) + " m/s");

  QObject::connect(slider, &QSlider::valueChanged, this, &SliderControl::valueChanged);
}

void SliderControl::valueChanged(int value) {
  Params().put(param_name.toStdString(), std::to_string(value));
  value_label->setText(QString::number(value) + " m/s");
}
