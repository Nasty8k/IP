#include <cinttypes>
#include <cstdint>
#include <string>
#include "Lab1.hpp"

int main() {
    Lab1 l1;
    uint64_t answer = 0;
    int64_t arr[3] = {0};

    // 1) Fast Modular Exponentiation
    uint64_t z1_1_a = 3;
    uint64_t z1_1_x = 100;
    uint64_t z1_1_p = 7;

    l1.fastExpMod(z1_1_a, z1_1_x, z1_1_p, &answer);
    printf("1)Fast Modular Exponentiation { a^x mod p = ? }\n");
    printf(" %" PRIu64"^ %" PRIu64" mod %" PRIu64" = %" PRIu64"\n\n", z1_1_a, z1_1_x, z1_1_p, answer);

    // 2) Generalized Euclidean algorithm  {ax + by = gcd(a, b)} --> 28x + 19y -> [gcd 1, x -2, y 3]
    int64_t z1_2_a = 28;
    int64_t z1_2_b = 19;
    if (z1_2_a < z1_2_b) std::swap(z1_2_a, z1_2_b);
    l1.euclid(z1_2_a,z1_2_b, arr);
    printf("2)Generalized Euclidean algorithm  { ax + by = gcd(a, b) }\n");
    printf(" gcd(%" PRId64 ", %" PRId64 ") = %" PRId64 ", x = %" PRId64  ", y = %" PRId64 "\n\n", z1_2_a, z1_2_b, arr[0], arr[1], arr[2]);

    // 3) Common KEY. Diffie-Hellman's protocol -> X = 7, 13; Y = 17, 21; KEY = 10 (g = 5, p = 23)
    printf("3)Common KEY. Diffie-Hellman's protocol\n");
    uint64_t z1_3_keyA;
    uint64_t z1_3_keyB;
    l1.dhProtocol(&z1_3_keyA, &z1_3_keyB, 700);
    printf(" Key A %" PRIu64" Key B %" PRIu64"\n\n", z1_3_keyA, z1_3_keyB);


    // 4) BabyStep - GiantStep
    uint64_t z1_4_a = 2;
    uint64_t z1_4_p = 23;
    uint64_t z1_4_y = 9;
    printf("4)BabyStep - GiantStep\n");
	l1.bgSteps(z1_4_a, z1_4_p, z1_4_y, &answer);
    printf("%" PRIu64 "^x mod %" PRIu64 " = %" PRIu64 "\n", z1_4_a, z1_4_p, z1_4_y);
    printf(" Result x = %" PRIu64"\n", answer);

    return EXIT_SUCCESS;
}

