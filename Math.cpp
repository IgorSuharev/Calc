#include "Math.h"

unsigned long long Math::factorial(unsigned n) {
    unsigned long long res = 1;
    for (; n > 1; n--) {
        res *= n;
    }
    return res;
}
