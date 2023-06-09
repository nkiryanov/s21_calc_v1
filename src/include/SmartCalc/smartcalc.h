#ifndef SMARTCALC_H
#define SMARTCALC_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class SmartCalc;
}
QT_END_NAMESPACE

class SmartCalc : public QMainWindow {
  Q_OBJECT

 public:
  SmartCalc(QWidget *parent = nullptr);
  ~SmartCalc();

 private:
  Ui::SmartCalc *ui;
};
#endif  // SMARTCALC_H
