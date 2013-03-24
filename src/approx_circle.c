#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <math.h>

#define MAX(a, b) ((a) >= (b) ? (a) : (b))
#define MIN(a, b) ((a) <= (b) ? (a) : (b))
#define ABS(a) ((a) >= 0 ? (a) : -(a))
#define SQR(a) ((a) * (a))

#define M_PI 3.14159265358979323846264338327

/*
 * Data structure that stores simulations
 * results and settings.
 */
typedef struct _simulation_t {
  double radius;
  int iterations;
  int no_inside;
  double area;
  double pi;
} simulation_t;

/*
 * Print the usage syntax of this program.
 *
 * @param arg the command-line name of this program.
 */
static void usage(const char *arg)
{
  printf("Syntax: %s R N.\n\n"
         "R is a floating point number representing the radius.\n"
         "N is an integer representing the number of iterations.\n", arg);
}

/*
 * Runs the simulation with the given parameters.
 * Remember to call srand before!
 *
 * @param radius the radius of the circle
 * @param iterations the number of iterations of the simulation
 * @param result structure where the results and settings of the simulation
 *               are to be stored
 */
static void simulate(double radius, int iterations, simulation_t *result)
{
  int no_inside = 0;
  assert(radius > 0.0);
  assert(iterations >= 1);

  for (int i = 0; i < iterations; i++) {
    /* assert:  0 <= x,y <= radius */
    double x = radius * ((double) rand() / (double) RAND_MAX);
    double y = radius * ((double) rand() / (double) RAND_MAX);

    if (sqrt(SQR(x) + SQR(y)) <= radius) {
      no_inside++;
    }
  }

  result->radius = radius;
  result->iterations = iterations;
  result->no_inside = no_inside;
  /*
   * Approximate the area of a quarter of a circle with radius r using
   * numbers sampled uniformly at random from the square [0, r^2] x [0, r^2].
   * When the number of iterations is large, the area approximation value is
   * likely near the actual area value: r^2 * PI / 4.
   * We use the approximation formula:
   * area ~ no_inside / (no_inside + no_outside) * r^2
   */
  result->area = (double) no_inside / (double) iterations * SQR(radius);
  /*
   * We approximate PI using the following formula:
   * PI ~ 4 * quarter area / r^2 = 4 * no_inside / (no_inside + no_outside)
   */
  result->pi = (double) 4.0 * ((double) no_inside / (double) iterations);
}

/*
 * Print the simulation data and comparison to accurate values on
 * standard output.
 * 
 * @param sim the simulation values to show
 */
static void show(simulation_t *sim)
{
  /* realArea = r^2 * PI / 4 */
  double realArea = (double) SQR(sim->radius) * M_PI / 4.0;
  printf("\t-- SIMULATION RESULTS --\n"
         "points inside circle: %d. outside: %d.\n"
         "\t-- AREA --\n"
         "area approximation: %f. real area: %f.\n"
         "absolute derivation: %f. relative derivation: %f%%.\n"
         "\t-- PI --\n"
         "PI approximation: %f. \'real\' PI: %f.\n"
         "absolute derivation: %f. relative derivation: %f%%.\n",
         sim->no_inside, sim->iterations - sim->no_inside,
         sim->area, realArea,
         ABS(sim->area - realArea), (1.0 - MIN(sim->area, realArea) / MAX(sim->area, realArea)) * 100.0,
         sim->pi, M_PI,
         ABS(sim->pi - M_PI), (1.0 - MIN(sim->pi, M_PI) / MAX(sim->pi, M_PI)) * 100.0);
}

/*
 * Runs the simulation and prints the result.
 *
 * @param argv radius of the circle to approximate
 *             number of iterations
 */
int main(int argc, char *argv[])
{
  if (argc != 3) {
    usage(argv[0]);
    exit(EXIT_FAILURE);
  } else {
    double radius = atof(argv[1]);
    int iterations = atoi(argv[2]);
    simulation_t result;

    /* Check inputs */
    if (radius <= 0.0) {
      printf("Radius R must not be negative or zero.\n");
      return EXIT_FAILURE;
    }

    if (iterations < 1) {
      printf("Iterations N must be an integer greater or equal to one.\n");
      return EXIT_FAILURE;
    }

    /*
     * Initialize the PRNG with the current time as the seed, run
     * the simulation, and print the results.
     */
    srand(time(NULL));
    simulate(radius, iterations, &result);
    show(&result);
    return EXIT_SUCCESS;
  }
}
