ApproxCircle
============

Monte Carlo simulation written in C which approximates the
quarter area of a circle with a specified radius r.
Additionally, this program approximates Pi using the Monte
Carlo method.

This program picks samples from a uniform distribution over
[0, r] x [0, r] and counts the number of points that
lie within the quarter area of the circle with radius r.
Let `no_inside` denote the number of points that lie within
the quarter area and let `no_samples` denote the number of samples.
The quarter area of the circle is approximately:

    qarea := no_inside / no_samples * r^2

Pi is approximately:

    Pi ~ 4 * qarea / r^2

How to Run
----------

Go to the directory containing the Makefile in a shell
and run `make`.

Examples
--------

The first parameter specifies the radius, while the second parameter
specifies the number of iterations.

    $ ./approx_circle 1 100
      -- SIMULATION RESULTS --
    points inside circle: 78. outside: 22.
      -- AREA --
    area approximation: 0.780000. real area: 0.785398.
    absolute derivation: 0.005398. relative derivation: 0.687316%.
      -- PI --
    PI approximation: 3.120000. 'real' PI: 3.141593.
    absolute derivation: 0.021593. relative derivation: 0.687316%.

    $ ./approx_circle 10 100
      -- SIMULATION RESULTS --
    points inside circle: 76. outside: 24.
      -- AREA --
    area approximation: 76.000000. real area: 78.539816.
    absolute derivation: 2.539816. relative derivation: 3.233795%.
      -- PI --
    PI approximation: 3.040000. 'real' PI: 3.141593.
    absolute derivation: 0.101593. relative derivation: 3.233795%.

Copyright
---------

Copyright 2013 Fabian Foerg
