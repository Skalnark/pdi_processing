#ifndef DECODE_H
#define DECODE_H
#include "lodepng.hpp"
#include "image.hpp"
#include "pixel.hpp"
#include "yiq.hpp"
#include <iostream>
#include <string>
#include <sstream>

class Processor
{
public:
    Image* source;
    Processor(Image* source);

    void Red();

    void Green();

    void Blue();

    void RGB_to_YIQ_to_RGB_Again();

    std::vector<YIQ> RGB_to_YIQ();

    std::vector<Pixel> YIQ_to_RGB(std::vector<YIQ> source);

    void NegativoRGB();

    void NegativoYIQ();

    void BrilhoAditivoYIQ(int bright);

    void BrilhoAditivoRGB(int bright);

    void BrilhoMultiplicativoYIQ(int bright);

    void BrilhoMultiplicativoRGB(int bright);

    void LimiarizacaoYIQ(int limiar);

    void LimiarizacaoRGB(int limiar);

    Image* Convolucao();

    void FiltroDeMediaRGB(unsigned w, unsigned h, bool convol);

    std::vector<std::vector<Pixel>> ToMatrix();

    std::vector<std::vector<unsigned>> Convolucao(std::vector<std::vector<unsigned>> mask, unsigned width, unsigned height);

private:
    void Save(std::string suffix, Image *source);
};

#endif
