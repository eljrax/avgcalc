#ifndef _MAIN_H
#define MAIN_H

#ifdef MEM_DEBUG
#include <valgrind/memcheck.h>
#endif 

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>
#include <errno.h>

#include "../config.h"

#ifdef ENABLE_NLS
#include <libintl.h>
#include <locale.h>
#define _(STRING) gettext(STRING)
#else
#define _(STRING) STRING 
#endif

#include "nls.h"


/* Used in output.c */
#define O_NONE 0
#define O_ALL 100

/* need_sorting() */
#define SORT 1
#define DONT_SORT 0

/* Initial sizes of mallocs to hold values and amount of modes */
#define VALS_SIZE 100
#define MODES_SIZE 5

struct data {
    int val_cnt;
    double sumx;
    double sumx_2;
    double mean;
    double p_stdev;
    double p_variance;
    double variance;
    double stdev;
    double median;
    double max;
    double min;
	double *vals;
    int need_sorting;
    int num_modes;
    int ignore_garbage;
    double *modes;
} d;

struct output {
    int print_mean;
    int print_median;
    int print_stdev;
    int print_pstdev;
    int print_pvariance;
    int print_variance;
    int print_mode;
    int print_val_cnt;
    int print_maxmin;
    int print_vals;
    int print_sum;
    int num_outputs;
} o;

int get_mode(double **ret, double vals[], int n, size_t modsiz);
/*int get_mode(double *ret, double vals[], int n, size_t modsiz); */
int cmp(const void *x, const void *y);
void parse_args(char *argv[], int argc, struct data *d, struct output *o);
void usage(char *self);
void init(struct data *d, struct output *o);
char *getln(FILE *fp);
void output(struct data *d, struct output *o);
void enable_nls();
void version();
#endif
