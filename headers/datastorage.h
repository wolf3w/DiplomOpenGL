#ifndef DATASTORAGE_H
#define DATASTORAGE_H

/** Синглтон для хранения данных */
class DataStorage
{
private:
    float gridRed_, gridGreen_, gridBlue_,
          surfRed_, surfGreen_, surfBlue_;

    DataStorage()
        : gridRed_(0.f), gridGreen_(0.f), gridBlue_(0.f),
          surfRed_(1.f), surfGreen_(0.5f), surfBlue_(0.31f)
    {}
    DataStorage(DataStorage const& ) = delete;
    DataStorage(DataStorage &&) = delete;
    DataStorage operator= (DataStorage& ) = delete;
public:
    static DataStorage& getInstance ()
    {
        static DataStorage inst;
        return inst;
    }

    void setGridRed (float redArg);
    void setGridGreen (float greenArg);
    void setGridBlue (float blueArg);
    void setSurfaceRed (float redArg);
    void setSurfaceGreen (float greenArg);
    void setSurfaceBlue (float blueArg);

    float getGridRed ();
    float getGridGreen ();
    float getGridBlue ();
    float getSurfRed ();
    float getSurfGreen ();
    float getSurfBlue();
};

#endif // DATASTORAGE_H
