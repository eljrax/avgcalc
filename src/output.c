/*
 * output.c - program output handling Copyright (C) 2012 Erik Ljungstrom.
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

/* Written April 2012 by Erik Ljungstrom.  */

#include "main.h"

/*
 * Repsonsible for outputting the values in the data struct, based on what's
 * in the output struct which in turn is largely controlled via parse_args()
 * - called from main()
 */

void
output (struct data *d, struct output *o)
{
  int i;

  if (o->print_vals)
  {
    for (i = 0; i < d->val_cnt; i++)
      printf ("%s %f\n", VALUE, d->vals[i]);
  }
  if (o->num_outputs == 0)
    o->num_outputs = O_ALL;

  if (o->print_val_cnt || o->num_outputs == O_ALL)
    printf ("%s%d\n", (o->num_outputs > 1) ? NUMELEMENTS : "",
	    d->val_cnt);

  if (o->print_stdev || o->num_outputs == O_ALL)
    printf ("%s%f\n", (o->num_outputs > 1) ? STDEV : "",
	    d->stdev);

  if (o->print_pstdev || o->num_outputs == O_ALL)
    printf ("%s%f\n",
	    (o->num_outputs > 1) ? PSTDEV : "",
	    d->p_stdev);

  if (o->print_pvariance || o->num_outputs == O_ALL)
    printf ("%s%f\n",
	    (o->num_outputs > 1) ? VARIANCE : "",
	    d->variance);

  if (o->print_variance || o->num_outputs == O_ALL)
    printf ("%s%f\n",
	    (o->num_outputs > 1) ? PSVARIANCE : "",
	    d->p_variance);

  if (o->print_mean || o->num_outputs == O_ALL)
    printf ("%s%f\n", (o->num_outputs > 1) ? MEAN : "", d->mean);

  if (o->print_median || o->num_outputs == O_ALL)
    printf ("%s%f\n", (o->num_outputs > 1) ? MEDIAN : "", d->median);

  if (o->print_maxmin || o->num_outputs == O_ALL)
    printf ("%s%f\n%s%f\n", MAX, d->max, MIN, d->min);

  if (o->print_sum || o->num_outputs == O_ALL)
    printf ("%s%f\n", (o->num_outputs > 1) ? SUM : "", d->sumx);

  if (o->print_mode || o->num_outputs == O_ALL)
  {
    if (d->num_modes == 0)
      printf ("%s\n", ALL_UNIQUE);
    else
    {
      for (i = 0; i < d->num_modes; i++)
	printf ("%s%f\n", (o->num_outputs > 1) ? MODE : "", d->modes[i]);
    }
  }
}

/*
 * Outputs usage information. Invoked by -h or when an erroneous argument is
 * given
 */
void
usage (char *self)
{
  printf (_ ("Usage: %s [OPTION]... [FILE]...\n\
  --mean, -m\t\t\tPrint mean only\n\
  --stdev, -s\t\t\tPrint standard deviation only\n\
  --stdev-variance -V\t\tPrint variance (standard deviation) only\n\
  --population-stdev, -S\tPrint population standard deviation only\n\
  --population-variance, -w\tPrint variance (population standard deviation) only\n\
  --median, -M\t\t\tPrint median only\n\
  --mode, -f\t\t\tPrint mode only\n"), self);
  /* Broken into two because of the 510 byte "limit" in c89 */
  printf (_ ("  --num-elements, -e\t\tPrint number of elements only\n\
  --print-values, -p\t\tPrint out sorted values (not printed in normal output if omitted)\n\
  --maxmin, -o\t\t\tPrint max and min values only\n\
  --sum, -t\t\t\tPrint sum only\n"));
  printf (_ ("  --assume-sorted, -a\t\tAssume sorted input - avoids sorting overhead\n\
  --ignore-noise, -i\t\tIgnore lines with garbage input as much as possible (ie. tolerate 5M and ignore lines not beginning with numbers)\n\
  --help, -h\t\t\tPrint this help text and exit\n\
  --version, -v\t\t\tPrint version information and exit\n"));
  exit (EXIT_FAILURE);
}
