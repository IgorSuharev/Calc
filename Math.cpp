#include "Math.h"
#include <cmath>

double Math::factorial(double n) {
    return tgamma(n + 1);
}
