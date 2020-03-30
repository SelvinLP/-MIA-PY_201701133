#ifndef BITMAP_H
#define BITMAP_H
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
struct NodoBitmap{
    int8_t Dato;
};
class Bitmap
{
public:
    Bitmap();

    NodoBitmap Nodo_Nuevo;
    void InsertarDato(std::string rutabrir,int posicionStart,int PosicionFinal);
};

#endif // BITMAP_H
