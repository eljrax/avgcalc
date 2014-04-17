/*
 * main.c - main driver functions for avg Copyright (C) 2012 Erik Ljungstrom.
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
#include <limits.h>

/*
 * Skips blank lines - determines if there's text to parse or not in
 * populate()
 */
int
parseable (char *line)
{

  if (line == NULL)
  {
    fprintf (stderr, "%s\n", ERROR_READVAL);
    exit (EXIT_FAILURE);
  }
  /* If the line is empty, just a newline or doesn't even start with a number
     - we can safely discard it and not evne try to parse it */

  if (strlen (line) == 0)
    return 0;

  if (!isalnum (line[0]) && !isspace (line[0]))
    return 0;

  return 1;

}

/* Outputs version info. */
void
version ()
{

  printf ("%s-%s\n", PACKAGE_NAME, PACKAGE_VERSION);
  exit (EXIT_SUCCESS);
}


/*
 * Determines whether we actually need to sort the input or not (-a
 * overrides) For example, if the user only wants the mean and/or stdev - we
 * can get away with not sorting the input and save some time.
 */
int
need_sorting (int need_sorting, struct output *o)
{

  /* If -a was given (overrides everything else) */
  if (need_sorting == DONT_SORT)
  {
    return DONT_SORT;
  }
  /* If no output filtering was given - we need to print everything,
     including things that need sorting */
  if (o->num_outputs == 0)
  {
    return SORT;
  }
  /* Operations we need sorting for */
  if (o->print_median || o->print_mode || o->print_maxmin)
  {
    return SORT;
  }
  return DONT_SORT;
}

/*
 * Reads values from given file descriptors, converting them to numbers, if
 * applicable
 */
void
populate (struct data *d, struct output *o, FILE * fd)
{

  char *buf;
  char *endptr = NULL;
  double tmp;

  size_t asiz = VALS_SIZE;

  while ((buf = getln (fd)) != NULL)
  {
    if (parseable (buf))
    {

      errno = 0;
      tmp = strtod (buf, &endptr);
      if ((errno == ERANGE && (tmp == LONG_MAX || tmp == LONG_MIN)) || (errno != 0 && tmp == 0))
      {
	printf ("%s %s\n", CONVERT_ERROR, strerror (errno));
	exit (EXIT_FAILURE);
      }
      /* The conversion from a string to a double wasn't flawless (might be
         letters etc.) - act depending on whether -i was supplied By default,
         without -i, we don't tolerate anything. If there was no conversion
         (else if below), but -i was provided, skip to next value from input */
      if (*endptr != '\0' && !d->ignore_garbage)
      {
	while (endptr)
	{
	  if (!isspace (*endptr))
	  {
	    fprintf (stderr, "%s %c\n", ILLEGAL_INPUT, *endptr);
	    free (buf);
	    free (d->vals);
	    exit (EXIT_FAILURE);
	  }
	  endptr++;
	}
      }
      else if (endptr == buf && d->ignore_garbage)
      {
	free (buf);
	continue;
      }
      d->vals[d->val_cnt] = tmp;
      if (d->val_cnt == (int)asiz - 1)
      {
	asiz += 100;
	d->vals = realloc (d->vals, sizeof (double) * asiz);
	if (d->vals == NULL)
	{
	  fprintf (stderr, "%s %f\n", ERROR_MALLOC, sizeof (double) * (double)asiz);
	  exit (EXIT_FAILURE);
	}
      }
      d->val_cnt++;
      d->sumx += tmp;
      d->sumx_2 += tmp * tmp;
    }
    free (buf);
    if (feof (fd))
      break;

  }

}

void
calculate (struct data *d, struct output *o)
{

  size_t modsiz = MODES_SIZE;

  d->modes = malloc (sizeof (double) * modsiz);
  if (d->modes == NULL)
  {
    fprintf (stderr, "%s %f\n", ERROR_MALLOC, sizeof (double) * (double)modsiz);
    exit (EXIT_FAILURE);
  }
  if (d->val_cnt >= 1)
  {
    d->max = d->vals[d->val_cnt - 1];
    d->min = d->vals[0];
    d->num_modes = get_mode (&d->modes, d->vals, d->val_cnt, modsiz);
    d->median =
      (d->val_cnt % 2) ? d->vals[(d->val_cnt) / 2] : (d->vals[(d->val_cnt / 2)] +
				       d->vals[(d->val_cnt / 2) - 1]) / 2;
    d->mean = d->sumx / d->val_cnt;
    if (d->val_cnt >= 2)
    {
      d->p_variance =
	d->sumx_2 / d->val_cnt - (pow ((d->sumx / d->val_cnt), 2));
      d->p_stdev = sqrt (d->p_variance);
      d->variance =
	(d->sumx_2 - ((d->sumx * d->sumx) / d->val_cnt)) / (d->val_cnt -
							    1.0);
      d->stdev = sqrt (d->variance);
    }
  }
}

/*
 * Repsonsible for outputting the values in the data struct, based on what's
 * in the output struct which in turn is largely controlled via parse_args()
 * - called from main()
 */
int
main (int argc, char *argv[])
{

  FILE *fd;

  struct data d;
  struct output o;


  opterr = 0;

  init (&d, &o);

  enable_nls ();

  parse_args (argv, argc, &d, &o);

  /* Assume all extra arguments are file names */
  if (optind < argc)
  {
    do
    {
      fd = (strcmp (argv[optind], "-") == 0) ? stdin : fopen (argv[optind], "r");
      if (!fd)
      {
	fprintf (stderr, "%s %s: %s\n", ERROR_FILEOPEN,
		 argv[optind], strerror (errno));
	exit (EXIT_FAILURE);
      }
      populate (&d, &o, fd);
      fclose (fd);

    }
    while (++optind < argc);
  }
  else
  {				/* No file name given on the command line -
				   reading from stdin */
    populate (&d, &o, stdin);

  }

  if (need_sorting (d.need_sorting, &o))
  {
    qsort (d.vals, d.val_cnt, sizeof (d.vals[0]), cmp);
  }
  if (d.val_cnt == 0)
  {
    free (d.vals);
    exit (EXIT_SUCCESS);
  }
  calculate (&d, &o);
  output (&d, &o);
  free (d.modes);
  free (d.vals);
#ifdef MEM_DEBUG
  /* Uncomment to cause a memory read error */
  /* printf("error here %f\n", d.vals[1]);  */
  if (RUNNING_ON_VALGRIND)
    printf ("%s %d\n", VALGRIND_ERRORS, VALGRIND_COUNT_ERRORS);
#endif
  exit (EXIT_SUCCESS);

}
