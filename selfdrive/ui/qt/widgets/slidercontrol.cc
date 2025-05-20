#include "slidercontrol.h"

SliderControl::SliderControl(const QString &param, const QString &title, const QString &desc,
                             float min, float max, float step, QWidget *parent)
    : QWidget(parent), param_name(param), min_val(min), step_size(step) {
  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->setSpacing(15);

  QLabel *title_label = new QLabel(title, this);
  title_label->setStyleSheet("font-weight: bold;");

  QLabel *desc_label = new QLabel(desc, this);
  desc_label->setWordWrap(true);
  desc_label->setStyleSheet("color: grey; font-size: 35px;");

  value_label = new QLabel(this);
  value_label->setStyleSheet("font-size: 45px;");

  slider = new QSlider(Qt::Horizontal, this);
  int steps = int((max - min) / step);
  slider->setRange(0, steps);
  slider->setSingleStep(1);
  slider->setTickInterval(1);
  slider->setTickPosition(QSlider::TicksBelow);

  // 👉 Force bigger size
  slider->setMinimumHeight(100);
  slider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  // 👉 Optional but helpful: style for better visibility
  slider->setStyleSheet(R"(
    QSlider::groove:horizontal {
      height: 20px;
      background: #444;
      border-radius: 10px;
    }
    QSlider::handle:horizontal {
      background: white;
      border: 2px solid #888;
      width: 40px;
      margin: -10px 0;
      border-radius: 20px;
    }
  )");

  layout->addWidget(title_label);
  layout->addWidget(desc_label);
  layout->addWidget(slider);
  layout->addWidget(value_label);

  Params params;
  bool ok = false;
  float saved_val = QString::fromStdString(params.get(param.toStdString())).toFloat(&ok);
  if (!ok) saved_val = max;
  int initial_step = int((saved_val - min) / step);
  slider->setValue(initial_step);
  value_label->setText(QString::number(saved_val, 'f', 1) + " m/s");

  QObject::connect(slider, &QSlider::valueChanged, this, &SliderControl::valueChanged);
}

void SliderControl::valueChanged(int step_index) {
  float value = min_val + (step_index * step_size);
  Params().put(param_name.toStdString(), std::to_string(value));
  value_label->setText(QString::number(value, 'f', 1) + " m/s");
}
