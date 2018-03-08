#ifndef DRUDE_MEDIA_H
#define DRUDE_MEDIA_H
struct DrudeMedia{
    //eps/eps0
    double epsr;
    // sigma/eps0
    double sigma;
    DrudeMedia(double e, double s):
        epsr(e), sigma(s)
    {};
};



#endif
