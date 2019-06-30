#ifndef KGFEQU_H
#define KGFEQU_H

/***
 *  F - нелинейная функция
 *  uP(revious) - u(N-1)(i ,j) прошлый слой
 *  uC(urrent)  - u(N)(i, j) нынешний слой
 *  uN(ext)     - u(N+1)(i, j) следующий слой
 *  h - шаг по пространству
 *
 *  initLayers - задает начальные значения uP и uN
 *  borderCalc - считает 0 и N-1 строки и столбцы
 *  mainCalc   - все остальные значения на диагонали
 *  updLayers  - меняет uN, uC и uP перед след. итерацией
 *  nextIter   - выполнить следующие 10 итераций
*/

/*
 *  inline для вычисл. функций очень хорошо
 *  влияет на скорость вычислений за счет встраивания
*/

#include <QVector>
#include <GL/gl.h>
#include <cmath>
#include <functional>
#include <glm/glm.hpp>

namespace EqSpc
{
    bool isOdd (int arg);
    bool isEven (int arg);
    bool isIn (int fArg, int sArg, int max);
    bool isSelected (int fArg, int sArg, int del);
}

template <typename Type>
class KGFequation
{
public:
    KGFequation (std::function<Type(Type)> FArg, int sizeArg, Type hArg, int selArg);
    void nextIter ();
    QVector<Type> getSurface ();
    QVector<Type> getGrid ();
    int getCurrentIter () const;

private:
    QVector<QVector<Type>> uP, uC, uN, uOut;
    std::function<Type(Type)> F;
    Type h;
    int N, M, select, curIter, maxIter;

    void initLayers ();
    inline void borderCalc (std::function<bool(int)> comp);
    inline void mainCalc (std::function<bool(int)> comp);
    inline void updLayers ();
    inline void refreshOut ();
    /* Запрет конструктора по умолчанию */
    KGFequation();
};

#endif // KGFEQU_H
