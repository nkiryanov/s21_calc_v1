#include "SmartCalc/smartcalc.h"

#include "./ui_smartcalc.h"

SmartCalc::SmartCalc(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::SmartCalc) {
  ui->setupUi(this);
}

SmartCalc::~SmartCalc() { delete ui; }
