/*
 * mode.c - contains function for extracting the mode Copyright (C) 2012 Erik
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
 * Populates 'ret' with an array of modes. Returns the amount of modes we
 * found
 */
int
get_mode (double **ret, double vals[], int n, size_t modsiz)
{

  int winner = 0, rep = 0, i, siz = 0;
  double last = vals[0];

  double *p;


  for (i = 1; i < n; i++)
  {
    if (siz == (int)modsiz - 2)
    {
      modsiz += modsiz;
      p = realloc (*ret, sizeof (double) * modsiz);
      if (p == NULL)
      {
	fprintf (stderr, "%s %d\n", ERROR_MALLOC, (int)(sizeof (double) * modsiz));
	exit (EXIT_FAILURE);
      }
      *ret = p;
    }
    if (vals[i] == last)
    {
      rep++;
      if (rep > winner)
      {
	/* This value is the mode alone */
	(*ret)[0] = vals[i];
	siz = 1;
	winner = rep;
      }
      else if (rep == winner)
      {
	(*ret)[siz] = vals[i];
	siz++;
      }
    }
    else
      rep = 0;
    last = vals[i];

  }

  return siz;
}
