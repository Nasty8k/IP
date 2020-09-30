#ifndef _Lab1_HPP_
#define _Lab1_HPP_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <cinttypes>
#include <random>
#include <ctime>
#include <cmath>
#include <map>

#define MAX_10EXP9 1000000000

class Lab1 {
public:

    static void fastExpMod(int64_t base, int64_t exponent, int64_t mod, int64_t *result);
    static void euclid(int64_t a, int64_t b, int64_t *result);
    void dhProtocol(int64_t *K1, int64_t *K2);
    static void bgSteps(int64_t a, int64_t p, int64_t y, int64_t *result);

    static void dhGeneratePQ(int64_t *p, int64_t *q, int64_t max_val);
    static void dhRandKeyX(int64_t *KeyX, int64_t max_val);
    static bool is_prime_num(const int64_t *p);
    static void generatePrime(int64_t *p, int64_t min_val, int64_t max_val);
    static void randBig(int64_t *X);
};

#endif /* _Lab1_HPP_ */