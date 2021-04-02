#include "headers/kgfequ.h"

inline bool eqspc::isOdd (int arg)
{
    return (arg % 2) == 1;
}

inline bool eqspc::isEven (int arg)
{
    return (arg % 2) == 0;
}

inline bool eqspc::isIn (int fArg, int sArg, int max)
{
    return (fArg < max && sArg < max);
}

inline bool eqspc::isSelected (int fArg, int sArg, int del)
{
    return (fArg % del) == 0
            &&
           (sArg % del) == 0;
}

template <typename T>
inline T eqspc::sqr (T arg)
{
    return arg * arg;
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
    constexpr Type x0 = 5,
                   y0 = 5;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            Type const shortExp = 2 * exp( -4 * (eqspc::sqr(i * h - x0) + eqspc::sqr(j * h - y0)) );

            uP[i][j] = shortExp;
            uC[i][j] = shortExp;
        }
    }
}

template <typename Type>
void KGFequation<Type>::borderCalc (std::function<bool(int)> comp)
{
    #pragma omp parallel
    {
        int i;
        #pragma omp for private(i)
        for (i = 1; i < N - 1; i++)
        {
            if ( comp(i + 1) )
            {
                Type const tmp = uC[i][1] + uC[i - 1][0] + uC[i + 1][0];

                uN[i][0] = -uP[i][0] + 0.5 * tmp - (0.5 * h * h) * F( 0.25 * tmp );
            }

            if ( comp(i + N) )
            {
                Type const tmp = uC[i][N - 2] + uC[i - 1][N - 1] + uC[i + 1][N - 1];

                uN[i][N - 1] = -uP[i][N - 1] + 0.5 * tmp - (0.5 * h * h) * F(0.25 * tmp);
            }
        }
    }

    #pragma omp parallel
    {
        int j;
        #pragma omp for private(j)
        for (j = 1; j < N - 1; j++)
        {
            if ( comp(j + 1) )
            {
                Type const tmp = uC[1][j] + uC[0][j + 1] + uC[0][j - 1];

                uN[0][j] = -uP[0][j] + 0.5 * tmp - (0.5 * h * h) * F(0.25 * tmp);
            }

            if ( comp(j + N) )
            {
                Type const tmp = uC[N - 2][j] + uC[N - 1][j + 1] + uC[N - 1][j - 1];

                uN[N - 1][j] = -uP[N - 1][j] + 0.5 * tmp - (0.5 * h * h) * F(0.25 * tmp);
            }
        }
    }
}

template <typename Type>
void KGFequation<Type>::mainCalc (std::function<bool(int)> comp)
{
    constexpr Type alf = 50;

    #pragma parallel
    {
        int i, j;
        #pragma omp for private(i, j)
        for (i = 1; i < N - 1; i++)
        {
            for (j = 1; j < N - 1; j++)
            {
                if ( comp(i + j) )
                {
                    Type const tmp = uC[i][j + 1] + uC[i][j - 1] + uC[i - 1][j] + uC[i + 1][j];
                    Type s = 0.25f * tmp;
                    char const sign = (s > 0) ? 1 : -1;

                    s = sign * alf * F(s);

                    uN[i][j] = -uP[i][j] + 0.5 * tmp - (0.5 * h * h) * s;
                }
            }
        }
    } // parallel
}

template <typename Type>
void KGFequation<Type>::updLayers ()
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
        if ( eqspc::isOdd(curIter) )
        {
            borderCalc( eqspc::isEven );
            mainCalc( eqspc::isEven );
            updLayers();
        }

        if ( eqspc::isEven(curIter) )
        {
            borderCalc( eqspc::isOdd );
            mainCalc( eqspc::isOdd );
            updLayers();
        }
    }

    refreshOut();
    maxIter += 10;
}

template <typename Type>
void KGFequation<Type>::refreshOut ()
{
    for (int i = 0; i < N; i++)
    {
        for (int j  = 0; j < N; j++)
        {
            if (eqspc::isSelected(i, j, select))
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
            if (eqspc::isIn(i+1, j+1, M))
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
            if (eqspc::isIn(i+1, j+1, M) && eqspc::isOdd(i) && eqspc::isOdd(j))
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
