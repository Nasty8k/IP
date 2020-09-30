#include <iostream>
#include "../include/Lab1.hpp"

void Lab1::generatePrime(int64_t *p, const int64_t min_val, const int64_t max_val) {
    int64_t test = 0;
    if (max_val == 0) {
        do {
            test = (rand() + min_val) % MAX_10EXP9;
        } while (!is_prime_num(&test));
        *p = test;
        return;
    }

    do {
        test = ((rand() % MAX_10EXP9) % (max_val - min_val) + min_val) % MAX_10EXP9;
    } while (!is_prime_num(&test));
    *p = test;
}

void Lab1::randBig(int64_t *X) {
    *X = rand() % MAX_10EXP9;
}

bool Lab1::is_prime_num(const int64_t *p) {
    if (*p == 1) return false;
    int64_t i;
    for (i = 2; i < sqrt(*p); ++i)
        if ((*p) % i == 0) return false;
    return true;
}

//-------------------Z1------------------------
void Lab1::fastExpMod(int64_t a, int64_t x, int64_t p, int64_t *res) {
    if (!is_prime_num(&p)) {
        *res = 0;
        return;
    }
    int64_t y = 1;
    int64_t s = a;
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
void Lab1::dhGeneratePQ(int64_t *p, int64_t *q, int64_t max_val) {
    srand(time(NULL));
    int64_t tp, tq;
    generatePrime(&tq, 2, max_val);
    tp = 2*tq + 1;
    while (!is_prime_num(&tp) && !is_prime_num(&tq) && tp > max_val) {
        generatePrime(&tq, 2, max_val);
        tp = 2*tq + 1;
    }
    *p = tp;
    *q = tq;
}

void Lab1::dhRandKeyX(int64_t *KeyX, int64_t max_val) {
    *KeyX = (max_val == 0) ? (rand() % MAX_10EXP9)
                           : rand() % max_val;
}

void Lab1::dhProtocol(int64_t *K1, int64_t *K2) {
    int64_t p, q, g = 1;
    int64_t Ax = 0, Bx = 0; //secret
    int64_t Ay = 2, By = 2; //open
    int64_t tmp = 0;

    while (true) {
        bool rule = false; // 1 < g < p-1  && g^q %p != 1 && p = 2q+1
        while (!rule) {
            dhGeneratePQ(&p, &q, MAX_10EXP9);
            for (int times = 1; times < 50; ++times) {
                generatePrime(&g, 2, p - 1);
                fastExpMod(g, q, p, &tmp);
                if (tmp != 1) {
                    rule = true;
                    break;
                }
            }
            if (!rule) {
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

        if (Ay > 1 && By > 2 && *K1 != 0 && *K2 != 0)
            break;
    }
    printf(" P: %ld Q: %ld  G %ld \n", p, q, g);
    printf(" Private: Ax %ld  Bx %ld \n", Ax, Bx);
    printf(" Open: Ay %ld  By %ld \n", Ay, By);

}
//-------------------Z4------------------------
void Lab1::bgSteps(int64_t a, int64_t p, int64_t y, int64_t *result) {
    if (y >= p) {
        printf("Y must be smaller than P\n");
        *result = 0;
        return;
    }
    int64_t m, k;
    int64_t i, j;
    m = k = static_cast<std::int64_t>(ceil(sqrt(p)));
    printf(" M: %ld  K: %ld\n", m, k);

    int64_t x;
    std::map<int64_t, int64_t> dictBig;
    std::map<int64_t, int64_t> dictSmall;

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
            printf(" M * i[%ld] - j[%ld] \n ",  i, it->second);
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