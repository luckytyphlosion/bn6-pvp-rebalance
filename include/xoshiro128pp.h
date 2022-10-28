#pragma once

uint32_t RNGNextInt(void);
uint32_t RNGNextIntBounded(uint32_t bound);
void SeedXoshiro128ppRNG(uint32_t seed1, uint32_t seed2);
