# Exercise

In this exercise you have to use the datatype **double** and **std::uint8_t** for certain computations.

Implement the following functions:

```cpp
double calculate_pi(std::uint32_t num_iterations);

void print_dec_to_bin(std::uint8_t value);

// Optional
void print_dec_to_hex(std::uint8_t value);
```

## Calculate Pi

With the following formula you can compute $\frac{\pi}{4}$.  
Implement the formula in the function with $n$ = **num_iterations**.  
Then use a for-loop to sum up the value.
At the end multiply with 4 before you return the value.

$\frac{\pi}{4} = \sum_0^n: \frac{1}{(4k + 1)) - (1 / (4k + 3))}$

## Decimal to Binary

Implement a function that prints out the binary representation of the decimal (regular number) input.

E.g. the decimal number 142 would be 10001110 in binary.

## Optional: Decimal to Hex-Decimal

Implement a function that prints out the hexa-deicmal representation of the decimal (regular number) input.

Note:

To print out a hexadecimal value of a **std::uint8_t** value use the following code:

```cpp
std::cout << std::hex << std::uppercase << static_cast<std::uint32_t>(j) << std::dec;
```

E.g. the decimal number 142 would be 8E in hexa-decimal.
