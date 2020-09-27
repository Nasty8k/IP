#include <iostream>
#include "../include/Lab1.hpp"

void Lab1::generatePrime(uint64_t *p, const uint64_t min_val, const uint64_t max_val) {
    uint64_t test = 0;
    if (max_val == 0) {
        do {
            test = ((uint64_t)rand() + (uint64_t)rand()) + min_val;
        } while (!is_prime_num(&test));
        *p = test;
        return;
    }

    do {
        test = ((uint64_t)rand() + (uint64_t)rand()) % (max_val - min_val) + min_val;
    } while (!is_prime_num(&test));
    *p = test;
}

bool Lab1::is_prime_num(const uint64_t *p) {
    if (*p == 1) return false;
    uint64_t i;
    for (i = 2; i < sqrt(*p); ++i)
        if ((*p) % i == 0) return false;
    return true;
}

//-------------------Z1------------------------
void Lab1::fastExpMod(uint64_t a, uint64_t x, uint64_t p, uint64_t *res) {
    if (!is_prime_num(&p)) {
        *res = 0;
        return;
    }
    uint64_t y = 1;
    uint64_t s = a;
    while(x > 0) {
        if (x & 1) y = (y * s) % p;
        s = (s * s) % p;
        x = x >> 1;
    }
    *res = y;
}
//-------------------Z2------------------------
void Lab1::euclid(int64_t a, int64_t b, int64_t *result) {
    int64_t u[3] = {a, 1, 0};
    int64_t v[3] = {b, 0, 1};
    int64_t t[3];
    int64_t q;
    while (v[0] != 0) {
        q = u[0] / v[0];
        t[0] = u[0] % v[0];
        t[1] = u[1] - q * v[1];
        t[2] = u[2] - q * v[2];
        std::memcpy(u, v, sizeof(int64_t) * 3);
        std::memcpy(v, t, sizeof(int64_t) * 3);
    }
    std::memcpy(result, u, sizeof(int64_t) * 3);
}

//-------------------Z3------------------------
void Lab1::dhGeneratePQ(uint64_t *p, uint64_t *q, uint64_t max_val) {
    srand(time(NULL));
    uint64_t tp, tq;
    generatePrime(&tq, 2, max_val);
    tp = 2*tq + 1;
    while (!is_prime_num(&tp) && !is_prime_num(&tq) && tp > max_val) {
        generatePrime(&tq, 2, max_val);
        tp = 2*tq + 1;
    }
    *p = tp;
    *q = tq;
}

void Lab1::dhRandKeyX(uint64_t *KeyX, uint64_t max_val) {
    *KeyX = (max_val == 0) ? (UINT64_MAX) *(rand() / (double) RAND_MAX)
            : (uint64_t) ((UINT64_MAX) * (rand() / (double) RAND_MAX)) % (max_val);
}

void Lab1::dhProtocol(uint64_t *K1, uint64_t *K2, uint64_t max_val) {
    uint64_t p, q, g = 1;
    uint64_t Ax = 0, Bx = 0; //secret
    uint64_t Ay = 2, By = 2; //open
    uint64_t tmp = 0;

while (true) {
    bool rule = false; // 1<g<p-1  && g^q %p != 1 && p = 2q+1
    while (rule == false) {
        dhGeneratePQ(&p, &q, max_val);
        for (int times = 1; times < 50; ++times) {
            generatePrime(&g, 2, p - 1);
            fastExpMod(g, q, p, &tmp);
            if (tmp != 1) {
                rule = true;
                break;
            }
        }
        if (rule != true) {
            printf("Generated 50 times for rule! Error Exit");
            return;
        }
    }

    srand(time(NULL));
    dhRandKeyX(&Ax, p);
    dhRandKeyX(&Bx, p);

    Lab1::fastExpMod(g, Ax, p, &Ay);
    Lab1::fastExpMod(g, Bx, p, &By);
    Lab1::fastExpMod(By, Ax, p, K1);
    Lab1::fastExpMod(Ay, Bx, p, K2);

    if (Ay > 1 && By > 2 && K1 != 0 && K2 != 0)
        break;
}
    printf(" P: %" PRIu64" Q: %" PRIu64"  G %" PRIu64"\n", p, q, g);
    printf(" Private: Ax %" PRIu64"  Bx %" PRIu64"\n", Ax, Bx);
    printf(" Open: Ay %" PRIu64"  By %" PRIu64"\n", Ay, By);

}
//-------------------Z4------------------------
void Lab1::bgSteps(uint64_t a, uint64_t p, uint64_t y, uint64_t *result) {
    if (y >= p) {
        printf("y must be smaller than p");
        *result = 0;
        return;
    }
    uint64_t m, k;
    uint64_t i, j;
    m = k = static_cast<std::uint64_t>(ceil(sqrt(p)));
    printf(" M: %" PRIu64"  K: %" PRIu64"\n", m, k);

    uint64_t x;
    std::map<uint64_t,uint64_t> dictBig;
    std::map<uint64_t,uint64_t> dictSmall;

    for (j = 0; j < m; ++j) {
        fastExpMod(a, j, p, &x);
        x = (x * y) % p;
        dictSmall[x] = j;
    }

    for (i = 1; i <= m ; ++i) {
        fastExpMod(a, i * m, p, &x);
        dictBig[x] = i;

        auto it = dictSmall.find(x);
        if (it != dictSmall.end()) {
            printf(" M * i[%lu] - j[%lu] \n ",  i, it->second);
            *result = i * m - it->second;
            return;
        }
    }

    printf("The result is not possible \n");
    *result = 0;

    // Out map dict
    //for (auto it = dict.begin(); it != dict.end(); it++)
    //    printf(" [%lu] = %lu \n", it->first, it->second);
}