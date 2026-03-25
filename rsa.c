#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate greatest common divisor (GCD) of two numbers
unsigned long gcd(unsigned long a, unsigned long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);  // Recursive call
}

// Function to calculate modulo inverse using extended Euclidean algorithm
unsigned long modInverse(unsigned long a, unsigned long m) {
    unsigned long m0 = m;
    long x0 = 0, x1 = 1;
    if (m == 1)
        return 0;

    while (a > 1) {
        unsigned long q = a / m;
        unsigned long t = m;
        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

// Function to generate keys for RSA encryption
void generateKeys(unsigned long p, unsigned long q, unsigned long *n, unsigned long *e, unsigned long *d) {
    *n = p * q;
    unsigned long phi = (p - 1) * (q - 1);

    printf("For p = %lu and q = %lu --> phi = %lu\n", p, q, phi);
    printf("Here is e such that 1 < e < phi and gcd(e, phi) = 1\n");

    for (unsigned long i = 2; i < phi; i++) {
        if (gcd(i, phi) == 1)
            printf("Here is e=%lu such that 1 < e < phi and gcd(e, phi) = 1\n", i);
    }

    printf("Select one of the above as e: ");
    scanf("%lu", e);

    *d = modInverse(*e, phi);
}

// Function to perform modular exponentiation (used for encryption and decryption)
unsigned long modExp(unsigned long base, unsigned long exp, unsigned long mod) {
    unsigned long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// Function to encrypt plaintext using RSA
unsigned long encrypt(unsigned long plaintext, unsigned long e, unsigned long n) {
    return modExp(plaintext, e, n);
}

// Function to decrypt ciphertext using RSA
unsigned long decrypt(unsigned long ciphertext, unsigned long d, unsigned long n) {
    return modExp(ciphertext, d, n);
}

unsigned long main() {
    unsigned long p; // prime number
    unsigned long q; // prime number
    unsigned long n, e, d;

    printf("Enter p and q: ");
    scanf("%lu %lu", &p, &q);

    // Generate RSA keys
    generateKeys(p, q, &n, &e, &d);

    printf("Public key (e, n): (%lu, %lu)\n", e, n);
    printf("Private key (d, n): (%lu, %lu)\n\n", d, n);

    unsigned long plaintext;
    printf("Enter an integer between 0 and n-1 as plain text to be encrypted: ");
    scanf("%lu", &plaintext);

    printf("Original plaintext: %lu\n", plaintext);
    unsigned long ciphertext = encrypt(plaintext, e, n);
    printf("Encrypted ciphertext: %lu\n", ciphertext);
    unsigned long decrypted = decrypt(ciphertext, d, n);
    printf("Decrypted plaintext: %lu\n\n", decrypted);

    return 0;
}
