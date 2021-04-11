#include "headers/datastorage.h"

void DataStorage::setGridRed(float redArg) { gridRed_ = redArg; }
void DataStorage::setGridGreen(float greenArg) { gridGreen_ = greenArg; }
void DataStorage::setGridBlue(float blueArg) { gridBlue_ = blueArg; }
void DataStorage::setSurfaceRed(float redArg) { surfRed_ = redArg; }
void DataStorage::setSurfaceGreen(float greenArg) { surfGreen_ = greenArg; }
void DataStorage::setSurfaceBlue(float blueArg) { surfBlue_ = blueArg; }

float DataStorage::getGridRed() { return gridRed_; }
float DataStorage::getGridGreen() { return gridGreen_; }
float DataStorage::getGridBlue() { return gridBlue_; }
float DataStorage::getSurfRed() { return surfRed_; }
float DataStorage::getSurfGreen() { return surfGreen_; }
float DataStorage::getSurfBlue() { return surfBlue_; }
