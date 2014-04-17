/*
 * parse_args.c - command line argument parsing Copyright (C) 2012 Erik
 * Ljungstrom.
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 3, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.
 */

/* Author: Erik Ljungstrom.  */

#include "main.h"

/*
 * Parses command line arguments and populates the data and output struct
 * accordingly
 */
void
parse_args (char *argv[], int argc, struct data *d, struct output *o)
{

  static struct option long_options[] =
  {
    /* These options set a flag. */
    {"stdev", no_argument, 0, 's'},
    {"mean", no_argument, 0, 'm'},
    {"stdev-variance", no_argument, 0, 'V'},
    {"version", no_argument, 0, 'v'},
    {"population-stdev", no_argument, 0, 'S'},
    {"population-variance", no_argument, 0, 'w'},
    {"median", no_argument, 0, 'M'},
    {"mode", no_argument, 0, 'f'},
    {"num-elements", no_argument, 0, 'e'},
    {"assume-sorted", no_argument, 0, 'a'},
    {"print-values", no_argument, 0, 'p'},
    {"maxmin", no_argument, 0, 'o'},
    {"sum", no_argument, 0, 't'},
    {"ignore-noise", no_argument, 0, 'i'},
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}
  };


  int c;
  int option_index = 0, idx = 0;
  while ((c = getopt_long (argc, argv, "smVvSwMfeapoti", long_options, &option_index)) != -1)
  {
    idx++;
    switch (c)
    {
    case 'h':
      free (d->vals);
      usage (argv[0]);
      break;
    case 'V':
      if (o->print_variance == 0)
      {
	o->print_variance = 1;
	o->num_outputs++;
      }
      break;
    case 's':
      if (o->print_stdev == 0)
      {
	o->print_stdev = 1;
	o->num_outputs++;
      }
      break;
    case 'S':
      if (o->print_pstdev == 0)
      {
	o->print_pstdev = 1;
	o->num_outputs++;
      }
      break;
    case 'w':
      if (o->print_pvariance == 0)
      {
	o->print_pvariance = 1;
	o->num_outputs++;
      }
      break;
    case 'm':
      if (o->print_mean == 0)
      {
	o->print_mean = 1;
	o->num_outputs++;
      }
      break;
    case 'M':
      if (o->print_median == 0)
      {
	o->print_median = 1;
	o->num_outputs++;
      }
      break;
    case 'f':
      if (o->print_mode == 0)
      {
	o->print_mode = 1;
	o->num_outputs++;
      }
      break;
    case 'e':
      if (o->print_val_cnt == 0)
      {
	o->print_val_cnt = 1;
	o->num_outputs++;
      }
      break;
    case 't':
      if (o->print_sum == 0)
      {
	o->print_sum = 1;
	o->num_outputs++;
      }
      break;
    case 'o':
      if (o->print_maxmin == 0)
      {
	o->print_maxmin = 1;
	o->num_outputs++;
      }
      break;
    case 'a':
      d->need_sorting = DONT_SORT;
      break;
    case 'p':
      o->print_vals = 1;
      break;
    case 'i':
      d->ignore_garbage = 1;
      break;
    case 'v':
      free (d->vals);
      version ();
      break;
    case '?':
      fprintf (stderr, "%s %s\n", ILLEGAL_OPTION, argv[idx]);
      free (d->vals);
      usage (argv[0]);
      break;
    default:
      free (d->vals);
      usage (argv[0]);
      break;
    }
  }



}
