#pragma once
#include <iostream>
#include <chrono>
#include <math.h>
#include <thread>
#include <windows.h>
#include <thread>
#include <sstream>
#include <string>
#include <time.h>
#include <mutex>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <tgmath.h>
#include <boost/math/special_functions/pow.hpp>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <iterator>

#define LINT boost::multiprecision::cpp_int
#define STMP chrono::steady_clock::time_point
#define BF50 boost::multiprecision::cpp_dec_float_50
#define BF100 boost::multiprecision::cpp_dec_float_100
#define GETTP(x) STMP x = chrono::high_resolution_clock::now();
#define GETUS(x, y, z) chrono::milliseconds x = chrono::duration_cast<chrono::milliseconds>( y - z );
