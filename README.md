# Statistics
[![Build Status](https://travis-ci.org/nholthaus/statistics.svg?branch=master)](https://travis-ci.org/github/nholthaus/statistics) ![language](https://img.shields.io/badge/language-c++17-blue.svg) ![license](https://img.shields.io/badge/license-MIT-orange.svg) ![copyright](https://img.shields.io/badge/%C2%A9-Nic_Holthaus-orange.svg) ![msvc2013](https://img.shields.io/badge/MSVC-2013-ff69b4.svg) ![msvc2019](https://img.shields.io/badge/MSVC-2019-ff69b4.svg) ![gcc-4.9.3](https://img.shields.io/badge/GCC-9.3.0-ff69b4.svg)

A modern C++ header-only library to calculate various statistics on a set of data

## Build Instructions

To build and run the unit tests:

``` bash
mkdir build
cd build
cmake -DBUILD_TESTS=ON ..
make -j
ctest
```

The library itself is a single header only. You can use the included CMake in a subdirectory and add the interface library, or just copy the `statistics.h` file (and license) into your project.

## Usage

The `Statistics` object keeps incremental statistical information about a set of data. Operations work in constant time, with a fixed (and small) memory footprint.

- Use the `+=` or `insert` functions to add samples to the population
- Get stats out with the following functions:
	- `count()` - the number of samples in the population.
	- `min()` - minimum valued sample in the population.
	- `max()` - maximum valued sample in the population.
	- `mean()` - average of the population.
	- `sum()` - the sum of all samples in the population.
	- `variance()` - the variance of the population.
	- `standardDeviation()` - the standard deviation of the population.

### Example:

```c++
void main()
{
	Statistics<int> s;

	for(int i = 0; i < 10; ++i)
	{
		s += i;
	}

	std::cout << "mean = " << s.mean() << std::endl;		// prints 'mean = 4.5'
}
```