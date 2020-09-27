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


class Lab1 {
public:

void fastExpMod(uint64_t base, uint64_t exponent, uint64_t mod, uint64_t *result);
void euclid(int64_t a, int64_t b, int64_t *result);
void dhProtocol(uint64_t *K1, uint64_t *K2, uint64_t max_val);
void bgSteps(uint64_t a, uint64_t p, uint64_t y, uint64_t *result);

void dhGeneratePQ(uint64_t *p, uint64_t *q, uint64_t max_val);
void dhRandKeyX(uint64_t *KeyX, uint64_t max_val);
bool is_prime_num(const uint64_t *p);
void generatePrime(uint64_t *p, uint64_t min_val, uint64_t max_val);
};

#endif /* _Lab1_HPP_ */
