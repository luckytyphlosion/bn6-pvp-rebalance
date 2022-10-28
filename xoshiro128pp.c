/*  Written in 2019 by David Blackman and Sebastiano Vigna (vigna@acm.org)

To the extent possible under law, the author has dedicated all copyright
and related and neighboring rights to this software to the public domain
worldwide. This software is distributed without any warranty.

See <http://creativecommons.org/publicdomain/zero/1.0/>. */

#include <stdint.h>

/* This is xoshiro128++ 1.0, one of our 32-bit all-purpose, rock-solid
   generators. It has excellent speed, a state size (128 bits) that is
   large enough for mild parallelism, and it passes all tests we are aware
   of.

   For generating just single-precision (i.e., 32-bit) floating-point
   numbers, xoshiro128+ is even faster.

   The state must be seeded so that it is not everywhere zero. */


static inline uint32_t rotl(const uint32_t x, int k) {
	return (x << k) | (x >> (32 - k));
}

extern uint32_t eXoshiro128PPState[4];

uint32_t RNGNextInt(void) {
	const uint32_t result = rotl(eXoshiro128PPState[0] + eXoshiro128PPState[3], 7) + eXoshiro128PPState[0];

	const uint32_t t = eXoshiro128PPState[1] << 9;

	eXoshiro128PPState[2] ^= eXoshiro128PPState[0];
	eXoshiro128PPState[3] ^= eXoshiro128PPState[1];
	eXoshiro128PPState[1] ^= eXoshiro128PPState[2];
	eXoshiro128PPState[0] ^= eXoshiro128PPState[3];

	eXoshiro128PPState[2] ^= t;

	eXoshiro128PPState[3] = rotl(eXoshiro128PPState[3], 11);

	return result - 1;
}

/*
 * PCG Random Number Generation for C.
 *
 * Copyright 2014 Melissa O'Neill <oneill@pcg-random.org>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * For additional information about the PCG random number generation scheme,
 * including its license and other licensing options, visit
 *
 *       http://www.pcg-random.org
 */

extern uint32_t umodsi3(uint32_t a, uint32_t b);

uint32_t RNGNextIntBounded(uint32_t bound)
{
    // To avoid bias, we need to make the range of the RNG a multiple of
    // bound, which we do by dropping output less than a threshold.
    // A naive scheme to calculate the threshold would be to do
    //
    //     uint32_t threshold = 0x100000000ull % bound;
    //
    // but 64-bit div/mod is slower than 32-bit div/mod (especially on
    // 32-bit platforms).  In essence, we do
    //
    //     uint32_t threshold = (0x100000000ull-bound) % bound;
    //
    // because this version will calculate the same modulus, but the LHS
    // value is less than 2^32.

    uint32_t threshold = umodsi3(-bound, bound);

    // Uniformity guarantees that this loop will terminate.  In practice, it
    // should usually terminate quickly; on average (assuming all bounds are
    // equally likely), 82.25% of the time, we can expect it to require just
    // one iteration.  In the worst case, someone passes a bound of 2^31 + 1
    // (i.e., 2147483649), which invalidates almost 50% of the range.  In 
    // practice, bounds are typically small and only a tiny amount of the range
    // is eliminated.
    for (;;) {
        uint32_t r = RNGNextInt();
        if (r >= threshold)
            return umodsi3(r, bound);
    }
}

static uint32_t SplitMix32(uint32_t x) {
    x ^= x >> 16;
    x = x * 0x85ebca6b;
    x ^= x >> 16;
    x = x * 0xc2b2ae35;
    x ^= x >> 16;
    return x;
}

void SeedXoshiro128ppRNG(uint32_t seed1, uint32_t seed2)
{
    eXoshiro128PPState[0] = SplitMix32(seed1);
    eXoshiro128PPState[1] = SplitMix32(seed2);
}
