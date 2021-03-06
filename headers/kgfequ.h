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
#include <omp.h>
#include <GL/gl.h>
#include <cmath>
#include <functional>
#include <glm/glm.hpp>

namespace eqspc
{
    template<typename T> T inline sqr (T);
    inline bool isOdd (int arg);
    inline bool isEven (int arg);
    inline bool isIn (int fArg, int sArg, int max);
    inline bool isSelected (int fArg, int sArg, int del);
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
    std::function<Type(Type)> F;
    int N, M, select, curIter, maxIter;
    Type h;
    QVector<QVector<Type>> uP, uC, uN, uOut;

    void initLayers ();
    void borderCalc (std::function<bool(int)> comp);
    void mainCalc (std::function<bool(int)> comp);
    void updLayers ();
    void refreshOut ();
    /* Запрет конструктора по умолчанию и иных */
    KGFequation() = delete;
    KGFequation(KGFequation const&) = delete;
    KGFequation(KGFequation &&) = delete;
    KGFequation operator= (KGFequation const& ) = delete;
};

#endif // KGFEQU_H
