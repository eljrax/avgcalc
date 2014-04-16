```
NAME
       avgcalc  - get statistical information such as mean, variance, standard
       deviation etc. from input

SYNOPSIS
       avgcalc [options ...] [file ...]

DESCRIPTION
       avgcalc reads decimal values from the named  input  FILE  (or  standard
       input if no files are named

       Note:  All of the "Print" options below can be used in combination with
       each other. Leaving them out entirely will output all available  calcu-
       lations


       -m     Print mean only

       -s     Print standard deviation only

       -v     Print variance (standard deviation) only

       -S     Print population standard deviation only

       -V     Print variance (population standard deviation) only

       -M     Print median only

       -p     Print  out  sorted values (not printed in normal output if omit-
              ted)

       -o     Print max and min values only

       -t     Print sum only

       -i     Ignore lines with garbage input as much as possible (ie.  toler-
              ate 5M and ignore lines not beginning with numbers)

       -f     Print mode only

       -e     Print number of elements only

       -a     Assume sorted input - avoids sorting

       -p     Print  out  sorted values (not printed in normal output if omit-
              ted)

       -o     Print max and min values only

       -t     Print sum only

       -a     Assume that the input is already sorted. This tells  avgcalc  to
              not  sort  the  input,  even  if you request a computation which
              requires a sorted dataset.  There are faster ways of sorting the
              data than letting avgcalc do it as it uses qsort() for portabil-
              ity reasons. However unless the size of your dataset is  in  the
              hundreds and hundreds of megabytes, this will not have a notice-
              able impact. But if you do have a dataset of that size, consider
              sorting it before feeding it to avgcalc.
              Note  though, the data is only sorted if it needs to be. If you,
              for example specify -m, no sorting will take  place  as  avgcalc
              can obtain the mean without sorting.

       -i     Ignore  lines  with garbage input as much as possible. This will
              for example consider "5.1Mb " or "5.1 Mb" and  so  on  as  valid
              input,  but  not "M5.1".  It also silently ignores any lines not
              beginning with numbers. Only use this if you know  exactly  what
              your  dataset  looks like, as it may yield in unexpected results
              otherwise.

EXAMPLES
       Get all available statistic information about values given on stdin:
       $ echo -e "1.2\n1.23\n1.32\n1.11\n1.23" | avgcalc
       number of elements = 5
       standard deviation = 0.075299
       population standard deviation = 0.067350
       variance (standard deviation) = 0.005670
       variance (population standard deviation) = 0.004536
       mean = 1.218000
       median = 1.230000
       max = 1.320000
       min = 1.110000
       sum = 6.090000
       mode = 1.230000


       Get the mean and median size of files in the current working directory:
       $ du -h . | avgcalc -i -m -M
       mean = 64.661538
       median = 4.000000

       Get the max, min, mean and sum of bytes sent in responses by Apache:
       #  awk  '{ print $10 }'  < /var/log/httpd/access_log | avgcalc -o -m -t
       -i
       mean = 23.833465
       max = 5305.000000
       min = 3.000000
       sum = 454099.000000


```
