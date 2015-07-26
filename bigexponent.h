#ifndef BIGEXPONENT_H
#define BIGEXPONENT_H

namespace Algo
{
    double power(double base,size_t exp)
    {
        if(exp>1)
        {
            size_t h = exp/2;
            return power(base,h) * power(base,exp - h);
        }
        else if(exp == 1)
        {
            return base;
        }
        else
        {
            return 1;
        }
    }
}

#endif // BIGEXPONENT_H

