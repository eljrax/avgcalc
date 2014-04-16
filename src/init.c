/* init.c - struct initialization function
   Copyright (C) 2012 Erik Ljungstrom.             

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA
   02110-1301, USA.  */

/* Written April 2012 by Erik Ljungstrom.  */

#include "main.h"


/* Sets all struct member values to their default initial values */
void
init (struct data *d, struct output *o)
{
  o->print_stdev = 0;
  o->print_pstdev = 0;
  o->print_pvariance = 0;
  o->print_variance = 0;
  o->print_mean = 0;
  o->print_median = 0;
  o->print_mode = 0;
  o->print_val_cnt = 0;
  o->print_vals = 0;
  o->print_maxmin = 0;
  o->print_sum = 0;
  o->num_outputs = O_NONE;

  d->val_cnt = 0;
  d->mean = 0.;
  d->p_variance = 0.;
  d->sumx = 0.;
  d->sumx_2 = 0.;
  d->p_stdev = 0.;
  d->variance = 0.;
  d->median = 0.;
  d->stdev = 0.;
  d->num_modes = 0;
  d->ignore_garbage = 0;
  d->need_sorting = 0;
  d->max = 0.;
  d->min = 0.;
  d->vals = malloc (sizeof (double) * VALS_SIZE);

  if (d->vals == NULL)
    {
      fprintf (stderr, "%s %f\n", ERROR_MALLOC,  sizeof (double) * (double) VALS_SIZE);
      exit (EXIT_FAILURE);
    }


}

