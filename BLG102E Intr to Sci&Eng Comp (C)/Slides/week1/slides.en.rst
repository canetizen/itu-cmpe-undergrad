.. title:: Programming

:author: \H. Turgut Uyar

----

Programming
===========

* a computer *program* is:

  * a collection of instructions
  * that can be executed by a computer
  * to perform a specific task

.. class:: substep

* programming: designing and implementing programs

----

Machine Code
============

* programs consist of machine instructions
* *machine code*

..

* instructions encoded as numbers
* `depends on the processor <annotate://box/orange>`_

----

Machine Code Example
====================

* get value in memory location ``47`` into processor
* subtract value in memory location ``62`` from that
* | if result is less than 18,
  | continue with instruction that is 4 positions ahead

.. class:: substep

* example machine code (in hex)::

   A12F0000002B053E00000083F8127C04

----

Source Code
===========

* very difficult to write machine code directly

  * what instructions are available?
  * in which memory locations are the data?

..

* write program in a friendlier language
* *source code*

.. class:: substep

* use a program to convert it to machine code

----

Friendlier?
===========

* more abstract concepts

..

* using names instead of numbers to refer to memory locations
* grouping multiple instructions into `statements <annotate://underline/orange>`_

----

Conversion to Machine Code
==========================

* source code doesn't depend on processor
* but machine code does

..

* | convertor generates machine code
  | `for a particular processor <annotate://box/orange>`_

.. class:: substep

* programmer doesn't have to care

----

Portability
===========

* write processor-independent source code
* use an appropriate convertor for each target processor
* the source code is *portable*

.. class:: substep

* not just the processor, also the operating system
* platform-independent

----

Language Levels
===============

* different source code languages have different levels

..

* closer to platform details: lower level
* closer to human thinking: higher level

..

* *high-level language*: easy enough for humans

----

Conversion Methods
==================

.. container:: column width-1-2

   * interpreting:

     * convert first statement
     * execute it
     * convert next statement
     * execute it
     * ...

.. container:: column width-1-2

   * compiling:

     * | convert whole source code
       | into executable code
     * execute first statement
     * execute next statement
     * ...

----

Interpreting
============

.. image:: interpreting.svg
   :width: 24em
   :alt: Diagram that shows stages of interpreted execution.
     Source code and inputs are fed into the interpreter which produces outputs.

.. class:: substep

* conversion during *runtime*
* more flexible than compiling

----

Compiling
=========

.. image:: compiling.svg
   :width: 32em
   :alt: Diagram that shows stages of compiled execution.
     Source code is fed into the compiler which produces machine code.
     Machine code and inputs are fed into the executor which produces outputs.

.. class:: substep

* conversion during *compile time*
* faster than interpreting

----

Programmer's Workflow
=====================

#. edit source code
#. compile source code to machine code
#. if compilation errors, go to step 1
#. run the program and test it
#. if incorrect behavior, go to step 1

----

Minimal Program
===============

* a program that does nothing:

.. parsed-literal::

   int main() {
       return 0;
   }

----

Starting Point
==============

.. parsed-literal::

   int `main <annotate://underline/orange>`_\ () {
       return 0;
   }

* program starts at :code:`main`: entry point
* every program must have one and exactly one

----

Function
========

.. parsed-literal::

   int main() `{ <annotate://circle/orange>`_
       `return 0; <annotate://box/orange>`_
   `} <annotate://circle/orange>`_

* :code:`main` is a *function*
* functions consist of statements
* enclosed in curly braces

----

Statement
=========

.. parsed-literal::

   int main() {
       return 0\ `; <annotate://circle/orange>`_
   }

* statements end with a semicolon

----

Function Result
===============

.. parsed-literal::

   int main() {
       `return <annotate://underline/orange>`_ 0;
   }

* functions report their results using :code:`return`

----

Program Result
==============

.. parsed-literal::

   `int <annotate://circle/orange>`_ main() {
       return `0 <annotate://circle/orange>`_;
   }

* | result of :code:`main` is the exit status:
  | success (0), failure (1)

* :code:`int` is the type of the result (integer)

----

Keywords
========

* some words in the language have special meaning: *keywords*
* :code:`int`, :code:`return`
* their use is restricted

----

Syntax Highlighting
===================

* | programmer tools use colors and font variations
  | to differentiate between different types of elements

.. code:: c

   int main() {
       return 0;
   }

----

Hello, world!
=============

* a program that prints a message:

.. parsed-literal::

   #include <stdio.h>

   int main() {
       printf("Hello, world!\\n");
       return 0;
   }

----

Output
======

* use the :code:`printf` function to print a message on the screen

.. parsed-literal::

   #include <stdio.h>

   int main() {
       `printf <annotate://underline/orange>`_\ ("Hello, world!\\n");
       return 0;
   }

----

Libraries
=========

* implementation for :code:`printf` is not contained in our code
* commonly used functions are collected into *libraries*

..

* :code:`printf` is part of the `standard library <annotate://underline/orange>`_


----

Header Files
============

* to use a function, include its *header file*

.. parsed-literal::

   `#include <stdio.h> <annotate://box/orange>`_

   int main() {
       printf("Hello, world!\\n");
       return 0;
   }

----

Newline
=======

* the :code:`\n` character is for moving the cursor to the next line

.. parsed-literal::

   #include <stdio.h>

   int main() {
       printf("Hello, world!\ `\\n <annotate://circle/orange>`_\ ");
       return 0;
   }

----

Syntax Highlighting
===================

.. code:: c

   #include <stdio.h>

   int main() {
       printf("Hello, world!\n");
       return 0;
   }

----

Comments
========

* it's helpful to explain the code
* for people who will read the code

..

* comments are ignored by language processors
* no effect during runtime

----

Line Comments
=============

* anything from :code:`//` to the end of the line

.. parsed-literal::

   #include <stdio.h>  `// needed for printf <annotate://box/orange>`_

   int main() {
       printf("Hello, world!\\n");
       return 0;
   }

----

Multiline Comments
==================

* anything between :code:`/*` and :code:`*/`
* can span over multiple lines

.. parsed-literal::

   `/\* (C) H. Turgut Uyar
      Prints a message on the screen. \*/ <annotate://box/orange>`_

   #include <stdio.h>  // needed for printf
   ...

----

Syntax Highlighting
===================

.. code:: c

   /* (C) H. Turgut Uyar
      Prints a message on the screen. */

   #include <stdio.h>  // needed for printf

   int main() {
       printf("Hello, world!\n");
       return 0;
   }

----

Code Style
==========

* programmers follow `style conventions <annotate://underline/orange>`_

  * lowercase or uppercase letters in names
  * spaces for visual separation

.. class:: substep

* these are not rules: not mandatory
* but following them makes code easier to read

----

Different Styles
================

* there is no style that everyone agrees on
* different programmers have different preferences
* in a team, members have to agree on a certain style

----

Line Length
===========

* lines shouldn't be too long
* requires horizontal scrolling

.. class:: substep

* popular value: 80
* can be increased in large monitors

----

Whitespace
==========

* whitespace is insignificant:

  .. code:: c

     #include <stdio.h>

     int main(){printf("Hello, world!\n");return 0;}

.. class:: substep

* but this is not readable

----

Indentation
===========

* statements of a function should start with leading space

  * how much space?
  * which character to use: space or tab?

.. class:: substep

* use spaces, not tabs
* 4 spaces

----

Indentation Example
===================

* statements are indented 4 spaces within function

.. parsed-literal::

   int main() {
   `\     \ <annotate://box/orange>`_\ printf("Hello, world!\\n");
   `\     \ <annotate://box/orange>`_\ return 0;
   }

----

Indentation Bad Example
=======================

* statements are not indented

.. parsed-literal::

   int main() {
   `printf("Hello, world!\\n");
   return 0; <annotate://crossed-off/red>`_
   }

----

Indentation Worse Example
=========================

* statements are inconsistently indented

.. parsed-literal::

   int main() {
      `printf("Hello, world!\\n");
    return 0; <annotate://crossed-off/red>`_
   }

----

Function Braces
===============

* where to put curly braces around function statements?

.. container:: column width-1-2

   * opening brace

     * on the same line
     * on the next line
     * on the next line, indented

.. container:: column width-1-2

   * closing brace

     * on the same line
     * on the next line
     * on the next line, dedented

----

Brace Style Example
===================

* opening brace on the same line
* closing brace on the next line, dedented

.. parsed-literal::

   int main() `{ <annotate://circle/orange>`_
       printf("Hello, world!\\n");
       return 0;
   `} <annotate://circle/orange>`_

----

Brace Style Alternative Example
===============================

* opening brace on the next line
* closing brace on the next line, dedented

.. parsed-literal::

   int main()
   `{ <annotate://circle/orange>`_
       printf("Hello, world!\\n");
       return 0;
   }

----

Function Parentheses
====================

* whether to put around parentheses after function name

----

Function Parentheses Example
============================

* no space before, one space after

.. parsed-literal::

   int main() {
       printf("Hello, world!\\n");
       return 0;
   }

----

Function Parentheses Alternative Examples
=========================================

.. container:: column width-1-2

   * space before

   .. parsed-literal::

      int main () {
          ...
      }


.. class:: substep

.. container:: column width-1-2

   * no space after

   .. parsed-literal::

      int main(){
          ...
      }

.. class:: substep

* these styles are not as popular

----

Blank Lines
===========

* how many blank lines to separate components?

----

Blank Lines Example
===================

* one blank line after :code:`#include` lines

.. parsed-literal::

   `#include <stdio.h> <annotate://box/orange>`_

   `int main() {
       printf("Hello, world!\\n");
       return 0;
   } <annotate://box/orange>`_

----

Blank Lines Bad Example
=======================

* no blank line after :code:`#include` lines

.. parsed-literal::

   #include <stdio.h>
   int main() {
       printf("Hello, world!\\n");
       return 0;
   }

----

Building Executables
====================

* executables get built in two stages

  * compiling
  * linking

----

Build Stages
============

.. image:: building.svg
   :width: 32em
   :alt: Diagram that shows the stages of building an executable.
     Source code is fed into the compiler to produce object code.
     Object code and libraries are fed into the linker
     to produce executable code.

----

Build Problems
==============

* error: no executable gets built

.. class:: substep

* warning: executable gets built
* but possibly won't work as intended

.. class:: substep

* *don't ignore warnings*

----

Syntax Errors
=============

* violating the syntax rules of the language

  * forgetting semicolons
  * not closing parentheses
  * not closing quotes

..

* error at compile-time


----

Forgotten Semicolon
===================

.. container:: column width-3-5

   .. parsed-literal::

      #include <stdio.h>

      int main() {
          printf("Hello, world!\\n")\ `\  \ <annotate://circle/orange>`_
          return 0;
      }

.. container:: column width-2-5

   * no semicolon at end of printing statement

----

Name Errors
===========

* using undefined names
* warning at compile-time, error at link-time

----

Undefined Name
==============

.. container:: column width-3-5

   .. parsed-literal::

      #include <stdio.h>

      int main() {
          `print <annotate://box/orange>`_\ ("Hello, world!\\n")
          return 0;
      }

.. container:: column width-2-5

   * :code:`print` instead of :code:`printf`

----

Case Sensitivity
================

* uppercase and lowercase are not the same
* can cause name issues

----

Incorrect Case
==============

.. container:: column width-3-5

   .. parsed-literal::

      #include <stdio.h>

      int `Main <annotate://box/orange>`_\ () {
          printf("Hello, world!\\n");
          return 0;
      }

.. container:: width-2-5

   * :code:`Main` instead of :code:`main`
   * | no problem at compile-time,
     | error at link-time

----

Algorithm
=========

* *algorithm*: step by step description of a solution
* like a recipe

.. class:: substep

* independent from programming language

----

Properties
==========

* algorithm must be unambiguous
* precise instructions for each step

.. class:: substep

* algorithm must not run forever
* either find a solution, or report that no solution can be found

----

Square Root
===========

* finding the square root of a number

..

* start with an initial guess
* repeatedly improve guess
* until the guess is good enough

----

Variables
=========

* number: :math:`x`
* guess: :math:`g`
* improved guess: :math:`g'`

----

Improving Guess
===============

* improved guess:

  .. math::

     g' = \frac{g + \frac{x}{g}}{2}

----

Termination
===========

* when is guess good enough?

  .. math::

     g^2 \approx x

.. class:: substep

* must be precise:

  .. math::

     |g^2 - x| < 10^{-3}

----

Square Root Algorithm
=====================

* initial guess: :math:`1`

..

#. :math:`g = 1`
#. if :math:`|g^2 - x| < 10^{-3}` then :math:`g` is the result, stop
#. :math:`g' = \frac{g + \frac{x}{g}}{2}`
#. replace :math:`g` with :math:`g'` and go to step 2

----

Square Root Example
===================

.. container:: column width-1-3

   * find: :math:`\sqrt{3}`

.. container:: column width-2-3

   * guesses:

   .. class:: substep

      :math:`1`

      :math:`\frac{1 + \frac{3}{1}}{2} = 2`

      :math:`\frac{2 + \frac{3}{2}}{2} = 1.75`

      :math:`\frac{1.75 + \frac{3}{1.75}}{2} \approx 1.732`

----

Flowchart
=========

* algorithm diagram: *flowchart*

----

Shapes
==========

.. container:: column width-1-3

   * statement

   .. image:: statement.svg
      :width: 6em
      :alt: A rectangle representing a statement.

.. container:: substep column width-1-3

   * decision

   .. image:: decision.svg
      :width: 6em
      :alt: A diamond representing a decision.

.. container:: substep column width-1-3

   * input/output

   .. image:: io.svg
      :width: 6em
      :alt: A parallelogram representing an input/output operation.

.. container:: substep column width-1-3

   * start/end

   .. image:: start_end.svg
      :width: 6em
      :alt: An ellipsis representing the start or end of the algorithm.

.. container:: substep column width-1-3

   * connector

   .. image:: connector.svg
      :width: 6em
      :alt: An arrow representing the connection between two components.

----

Square Root Flowchart
=====================

.. container:: column width-1-3

   .. image:: flowchart-sqrt.svg
      :width: 8em
      :alt: The flowchart of the square root algorithm.

.. container:: column width-2-5

   * using a code-like notation

:pan: -0.3, 0.07, -0.4
