/*
 * getline.c - file input handling Copyright (C) 2012 Erik Ljungstrom.
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
 * Reads a line from a file descriptor - dynamically allocating memory as
 * required. Called from populate(). Returns a pointer to the line read from
 * the file descriptor fp NB: Discards \n
 */

char *
getln (FILE * fp)
{


  char *buffer = malloc (BUFSIZ);
  char *tmp;
  size_t capacity = BUFSIZ, used = 0;
  int ch;

  if (buffer == NULL)
    return NULL;

  while (1)
  {
    ch = fgetc (fp);
    if (ch == EOF)
    {
      free (buffer);
      return NULL;
    }
    if (used == capacity - 2)
    {
      tmp = realloc (buffer, capacity *= 2);
      if (tmp == NULL)
      {
	free (buffer);
	return NULL;
      }
      buffer = tmp;
    }
    /* Stop reading if we hit anything that could be considered garbage (ie.
       not a number or decimal point) */
    if (!ispunct (ch) && !isdigit (ch) && !islower (ch) && !isupper (ch))
      break;

    /* Discard newlines - they're irrelevant */
    if (ch == '\n')
      break;

    buffer[used] = ch;
    used++;


  }

  buffer[used] = '\0';
  return buffer;

}
