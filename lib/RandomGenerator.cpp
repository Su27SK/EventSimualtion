#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <math.h>
#include "RandomGenerator.h"

using namespace std;

const gsl_rng_type * RandomGenerator::T;

gsl_rng * RandomGenerator::r;

/**
 * @brief init 
 * 初始化，设置种子
 * @param {interge} seed
 */
void RandomGenerator::init(int seed)
{
	stringstream ssseed;
	//ssseed << time(NULL);
	ssseed << seed;

	//this setenv() does not work on sand.cise.ufl.edu, but works under linux	
	//you might remove the comment on your machine
	setenv("GSL_RNG_SEED", (ssseed.str()).data(), 1);
	
	gsl_rng_env_setup();

	T = gsl_rng_default;
	r = gsl_rng_alloc (T);
}

/**
 * @brief destroy 
 */
void RandomGenerator::destroy()
{
	gsl_rng_free (r);

	//this unsetenv() does not work on sand.cise.ufl.edu, but works under linux	
	//you might remove the comment on your machine
	unsetenv("GSL_RNG_SEED");
}

/**
 * @brief genUniformInt 
 * 产生标准随机数(interge类型)
 * @param {interge} lower 下限
 * @param {interge} upper 上限
 *
 * @return {interge}
 */
int RandomGenerator::genUniformInt(int lower, int upper)
{
	if(lower > upper)
	{
		cerr << "lowr needs to be less than or equal to upper." << endl;
		return lower;
	}

	if(lower == upper)
		return lower;

	// u is a uniform random number in the range [0.0, 1.0), 
	double u = gsl_rng_uniform (r);

	return lower + (int) ((upper - lower) * u);
}

/**
 * @brief genUniformDouble 
 * 产生标准随机数(double类型)
 * @param {interge} lower
 * @param {interge} upper
 *
 * @return {interge}
 */
double RandomGenerator::genUniformDouble(double lower, double upper)
{
	if(lower > upper)
	{
		cerr << "lowr needs to be less than or equal to upper." << endl;
		return lower;
	}

	if(lower == upper)
		return lower;

	// u is a uniform random double value in the range [0.0, 1.0), 
	double u = gsl_rng_uniform (r);

	return lower + (upper - lower) * u;
}

/**
 * @brief genUniform 
 * a uniform random numbers in the range [0.0, 1.0), 
 * @return 
 */
double RandomGenerator::genUniform()
{
	return gsl_rng_uniform (r);
}

/**
 * @brief genBernoulliInt 
 * 产生伯努力随机分布
 * @param {double} p
 *
 * @return {interge}
 */
int RandomGenerator::genBernoulliInt(double p)
{
	unsigned int k = gsl_ran_bernoulli(r, p);
	return (int)k;
}

/**
 * @brief genPoissonInt 
 * 产生泊松分布
 * @param {double} mu
 *
 * @return {interge}
 */
int RandomGenerator::genPoissonInt(double mu)
{
	unsigned int k = gsl_ran_poisson(r, mu);
	return (int)k;	
}

/**
 * @brief genPoissonDouble 
 * 产生泊松分布
 * @param {double} mu
 *
 * @return {double}
 */
double RandomGenerator::genPoissonDouble(double mu)
{
	return gsl_ran_poisson(r, mu);
}

double RandomGenerator::genParetoDouble(double a, double b)
{
/* This function returns a random variate from the Pareto distribution of order a. The distribution function is,

			p(x) dx = (a/b) / (x/b)^{a+1} dx

    for x >= b. 
*/
	return gsl_ran_pareto(r, a, b);
}

double RandomGenerator::genTruncatedParetoDouble(double a, double b)
{
/* This function returns a random variate from the Pareto distribution of order a. The distribution function is,

            p(x) dx = (a/b) / (x/b)^{a+1} dx

    for x >= b. 

	mean(x) = ab / a - 1

	if random_value > mean(x), we return a large number max; else we return random_value;
*/
	if(a < 1)
	{
		cerr << "Error: a > 1" << endl;
		exit(1);
	}

	double value = gsl_ran_pareto(r, a, b);

	double mean = a * b / (a - 1);

	double c = Truncated_Factor * mean;

	if(value <= c)
		return value;

	return a * c / (a - 1);
}

/**
 * @brief genGaussianDouble 
 * 产生高斯分布(计算x处的概率密度值)
 * @param {double} x
 * @param {double} sigma
 *
 * @return {double}
 */
double RandomGenerator::genGaussianDouble(double x, double sigma)
{
	return gsl_ran_gaussian_pdf(x, sigma);
}

/**
 * @brief genGaussianDouble 
 * 产生高丝分布，返回期望为0， 标准差为sigma的正态分布随机数
 * @param {double} sigma
 *
 * @return {double}
 */
double RandomGenerator::genGaussianDouble(double sigma)
{
	return gsl_ran_gaussian(r, sigma);
}
