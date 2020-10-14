#include "kgfequ.h"

bool EqSpc::isOdd (int arg)
{
    return (arg % 2) == 1;
}

bool EqSpc::isEven (int arg)
{
    return (arg % 2) == 0;
}

bool EqSpc::isIn (int fArg, int sArg, int max)
{
    return (fArg < max && sArg < max);
}

bool EqSpc::isSelected (int fArg, int sArg, int del)
{
    return (fArg % del) == 0
            &&
           (sArg % del) == 0;
}

template <typename Type>
KGFequation<Type>::KGFequation (std::function<Type(Type)> FArg, int sizeArg, Type hArg, int selArg)
    : F(FArg), N(sizeArg), h(hArg), select(selArg)
{
    uP.resize(N);
    uC.resize(N);
    uN.resize(N);
    for (int i = 0; i < N; i++)
    {
        uP[i].resize(N);
        uC[i].resize(N);
        uN[i].resize(N);
    }

    M = N / select;
    uOut.resize(M);
    for (int i = 0; i < M; i++)
    {
        uOut[i].resize(M);
    }

    initLayers();
    refreshOut();

    curIter = 0;
    maxIter = 10;
}

template <typename Type>
void KGFequation<Type>::initLayers ()
{
    Type x0 = 5, y0 = 5;

    std::function<Type(Type)> sqr = [] (Type arg) -> Type
    {
        return arg * arg;
    };

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            uP[i][j] = 2 * exp( -4 * (sqr(i * h - x0) + sqr(j * h - y0)) );
            uC[i][j] = 2 * exp( -4 * (sqr(i * h - x0) + sqr(j * h - y0)) );
        }
    }
}

template <typename Type>
inline void KGFequation<Type>::borderCalc (std::function<bool(int)> comp)
{
    for (int i = 1; i < N - 1; i++)
    {
        if ( comp(i + 1) )
        {
            uN[i][0] = -uP[i][0] + 0.5 * (uC[i][1] + uC[i - 1][0] + uC[i + 1][0])\
                        -(h * h / 2.0) * F(0.25 * ( uC[i][1] + uC[i - 1][0] + uC[i + 1][0] ));
        }

        if ( comp(i + N) )
        {
            uN[i][N - 1] = -uP[i][N - 1] + 0.5 * (uC[i][N - 2] + uC[i - 1][N - 1] + uC[i + 1][N - 1])\
                            -(h * h / 2.0) * F(0.25 * (uC[i][N - 2] + uC[i - 1][N - 1] + uC[i + 1][N - 1]));
        }
    }

    for (int j = 1; j < N - 1; j++)
    {
        if ( comp(j + 1) )
        {
            uN[0][j] = -uP[0][j] + 0.5 * (uC[1][j] + uC[0][j + 1] + uC[0][j - 1])\
                       -(h * h / 2.0) * F(0.25 * (uC[1][j] + uC[0][j + 1] + uC[0][j - 1]));
        }

        if ( comp(j + N) )
        {
            uN[N - 1][j] = -uP[N - 1][j] + 0.5 * (uC[N - 2][j] + uC[N - 1][j + 1] + uC[N - 1][j - 1])\
                           -(h * h / 2.0) * F(0.25 * (uC[N - 2][j] + uC[N - 1][j + 1] + uC[N - 1][j - 1]));
        }
    }
}

template <typename Type>
inline void KGFequation<Type>::mainCalc (std::function<bool(int)> comp)
{
    Type alf = 50;

    for (int i = 1; i < N - 1; i++)
    {
        for (int j = 1; j < N - 1; j++)
        {
            if ( comp(i + j) )
            {
                Type s = 0.25 * (uC[i][j + 1] + uC[i][j - 1] + uC[i - 1][j] + uC[i + 1][j]);
                int sign = (s > 0) ? 1 : -1;

                s = sign * alf * F(s);

                uN[i][j] = -uP[i][j] + 0.5 * (uC[i][j + 1] + uC[i][j - 1] + uC[i - 1][j] + uC[i + 1][j])\
                            -(h * h / 2.0) * s;
            }
        }
    }
}

template <typename Type>
inline void KGFequation<Type>::updLayers ()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            uP[i][j] = uC[i][j];
            uC[i][j] = uN[i][j];
        }
    }
}

template <typename Type>
void KGFequation<Type>::nextIter ()
{
    for (; curIter < maxIter; curIter++)
    {
        if ( EqSpc::isOdd(curIter) )
        {
            borderCalc( EqSpc::isEven );
            mainCalc( EqSpc::isEven );
            updLayers();
        }

        if ( EqSpc::isEven(curIter) )
        {
            borderCalc( EqSpc::isOdd );
            mainCalc( EqSpc::isOdd );
            updLayers();
        }
    }

    refreshOut();
    maxIter += 10;
}

template <typename Type>
inline void KGFequation<Type>::refreshOut ()
{
    for (int i = 0; i < N; i++)
    {
        for (int j  = 0; j < N; j++)
        {
            if (EqSpc::isSelected(i, j, select))
            {
                int iOut = i / select,
                    jOut = j / select;

                uOut[iOut][jOut] = uC[i][j];
            }
        }
    }
}

template <typename Type>
QVector<Type> KGFequation<Type>::getSurface ()
{
    QVector<Type> out;

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (EqSpc::isIn(i+1, j+1, M))
            {
                Type ic = static_cast<Type>(i),
                     jc = static_cast<Type>(j);
                QVector<Type> point_1 {ic, jc, uOut[i][j]},
                              point_2 {ic + 1, jc, uOut[i+1][j]},
                              point_3 {ic, jc + 1, uOut[i][j+1]},
                              point_4 {ic + 1, jc + 1, uOut[i+1][j+1]};
                out.append(point_1);
                out.append(point_2);
                out.append(point_3);

                out.append(point_2);
                out.append(point_3);
                out.append(point_4);
            }
        }
    }

    return out;
}

template <typename Type>
QVector<Type> KGFequation<Type>::getGrid ()
{
    QVector<Type> out;

    for (int i = 1; i < M; i++)
    {
        for (int j = 1; j < M; j++)
        {
            if (EqSpc::isIn(i+1, j+1, M) && EqSpc::isOdd(i) && EqSpc::isOdd(j))
            {
                Type ic = static_cast<Type>(i),
                     jc = static_cast<Type>(j);
                QVector<Type> point_1 {ic, jc, uOut[i][j]},
                              point_2 {ic, jc - 1, uOut[i][j-1]},
                              point_3 {ic - 1, jc, uOut[i-1][j]},
                              point_4 {ic, jc + 1, uOut[i][j+1]},
                              point_5 {ic + 1, jc, uOut[i+1][j]};

                out.append(point_1);
                out.append(point_2);

                out.append(point_1);
                out.append(point_3);

                out.append(point_1);
                out.append(point_4);

                out.append(point_1);
                out.append(point_5);
            }
        }
    }

    return out;
}

template <typename Type>
int KGFequation<Type>::getCurrentIter () const
{
    return this->curIter;
}

/* Для решения проблемы с линковщиком */
template class KGFequation<GLfloat>;
