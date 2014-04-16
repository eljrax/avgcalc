#include "main.h"
#include "nls.h"

void
enable_nls ()
{
#ifdef ENABLE_NLS
  if (setlocale (LC_ALL, "") == NULL)
    fprintf (stderr, "%s %s\n", FAIL_SETLOCALE, strerror (errno));

  if (bindtextdomain ("avgcalc", LOCALEDIR) == NULL)
    fprintf (stderr, "%s %s\n", ERROR_BINDTEXT, strerror (errno));

  if (textdomain ("avgcalc") == NULL)
    fprintf (stderr, "%s %s\n", ERROR_SETTEXT, strerror (errno));
#endif



}
