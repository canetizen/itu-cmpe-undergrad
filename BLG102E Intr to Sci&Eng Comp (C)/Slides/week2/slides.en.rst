.. title:: Data

:author: \H. Turgut Uyar

----

Body Mass Index
===============

* measure for body leanness

..

* :math:`w`: weight (mass, kg)
* :math:`h`: height (m)

.. math::

   bmi = \frac{w}{h^2}

----

BMI Table
=========

.. class:: smaller

=================== ===========
 category            BMI range
=================== ===========
 severe thinness     < 16
 moderate thinness   16 - 17
 mild thinness       17 - 18.5
 normal              `18.5 - 25 <annotate://box/orange>`_
 overweight          25 - 30
 obese class I       30 - 35
 obese class II      35 - 40
 obese class III     > 40
=================== ===========

----

Data Type
=========

* every piece of data has a type

..

* which values it can take
* which operations will be allowed on it

----

Common Types
============

* numeric: integer, real
* string
* character
* boolean

----

Real Numbers
============

* representing real numbers is difficult

..

* *floating point*: effective but inaccurate
* fixed point: ineffective and uncommon

----

Floating Point Inaccuracy
=========================

* inaccuracy due to representation

* example:

  :math:`0.1 + 0.2 = 0.30000000000000004`

.. class:: substep

* affects all programming languages

----

Literal
=======

* value directly written into source code: *literal*
* value determines type

----

Numeric Literals
================

.. container:: column width-3-5

   * digits without a point → integer
   * digits with one point → floating point
   * optional sign

.. container:: column width-2-5

   ========================= ================
    value                     type
   ========================= ================
    :code:`42`                integer
    :code:`-6`                integer
    :code:`3.14159`           floating point
    :code:`-1.5`              floating point
   ========================= ================

----

Scientific Notation
===================

* :code:`E` notation for floating point: :code:`mEn`
* :math:`m \cdot 10^n`

========================= ================
 value                     type
========================= ================
 :code:`1E6`               floating point
 :code:`3.14E-2`           floating point
========================= ================

----

Text Literals
=============

* characters between double quotes → string
* character between single quotes → character

.. container:: column width-1-2

   ========================= ================
    value                     type
   ========================= ================
    :code:`"Hello, world!"`   string
    :code:`'t'`               character
    :code:`"t"`               string
   ========================= ================

.. container:: substep column width-1-4

   ========================= ================
    value                     type
   ========================= ================
    :code:`7`                 integer
    :code:`'7'`               character
    :code:`"7"`               string
   ========================= ================

.. container:: substep column width-1-4

   ========================= ================
    value                     type
   ========================= ================
    :code:`""`                string
   ========================= ================

----

Expression
==========

* an *expression* is a construct

  * that will be evaluated
  * to produce a result

----

Expression Types
================

* type of result determines type of expression

  * arithmetic
  * boolean
  * ...

----

Arithmetic Operators
====================

.. container:: column width-1-3

   * addition:

     :code:`38 + 4`

   * subtraction:

     :code:`155 - 113`

   * multiplication:

     :code:`6 * 7`

.. container:: column width-1-3

   * division:

     :code:`126 / 3`

.. container:: column width-1-3

   * unary minus (sign):

     :code:`-(-42)`

----

Precedence
==========

* precedence as in mathematics

  * unary minus
  * :code:`*` and :code:`/`
  * :code:`+` and :code:`-`

..

* use parentheses to adjust computation order

----

Operator Style
==============

* one space each on both sides of operator (except unary minus)

.. container:: column width-1-2

   .. parsed-literal::

      5*1.28+3*17.32

      // prefer
      5 * 1.28 + 3 * 17.32

.. container:: column width-1-2 substep

   .. parsed-literal::

      - (6 * 7)

      // prefer
      -(6 * 7)

----

Parenthesis Style
=================

* no space inside parentheses

.. container:: column width-1-2

   .. parsed-literal::

      5 * ( 1.25 + 0.03 )

      // prefer
      5 * (1.25 + 0.03)

----

Floating Point
==============

.. container:: column width-1-2

   * single precision:

     :code:`float`

   * double precision:

     :code:`double`

   * higher precision:

     :code:`long double`

.. class:: substep

.. container:: column width-1-2

   * prefer :code:`double`

----

Variable
========

* a *variable* is:

  * a memory location (address)
  * associated with a name (identifier)
  * containing some information (value)

----

Understanding Variables
=======================

* different from variables in mathematics

  * mathematical variables are abstract

.. class:: substep

* treated differently in different programming languages

----

Using Variables
===============

* variables can be used in expressions

.. parsed-literal::

   x + 4
   155 - x
   x * y
   -x

----

Variable Definition
===================

.. container:: column width-1-2

   * defining a variable:

     * its name
     * its type
     * optionally, its initial value

.. class:: substep

.. container:: column width-1-2

   * syntax:

   .. parsed-literal::

      `type <annotate://box/orange>`_ `name <annotate://box/orange>`_ = `value <annotate://box/orange>`_;

   * without initial value:

   .. parsed-literal::

      type name;

----

Variable Definition Example
===========================

.. parsed-literal::

   double weight = 65.3;

* name: :code:`weight`
* type: :code:`double`
* initial value: :code:`65.3`

----

Variable Initialization
=======================

* initial values are not required

.. parsed-literal::

   double weight;

* but strongly recommended
* uninitialized variables cause a warning

----

Variable Comments
=================

* adding helpful comments is good style

.. parsed-literal::

   double weight = 65.3;  // mass, in kg

----

Multiple Definitions
====================

* multiple variables can be defined in the same statement
* all of the same type

.. parsed-literal::

   type name1 = value1, name2 = value2, ...;

----

Multiple Definition Example
===========================

.. parsed-literal::

   double weight = 65.3, height = 1.74;

.. container:: substep

   * prefer defining one variable per statement

   .. parsed-literal::

      double weight = 65.3;  // mass, in kg
      double height = 1.74;  // in m

----

Initial Values
==============

* initial value is an expression
* previously defined variable can be used

.. parsed-literal::

   double weight = 65.3;  // mass, in kg
   double height = 1.74;  // in m
   double bmi = weight / (height * height);

----

Variable Names
==============

* using descriptive names is good style
* :code:`weight` is better than :code:`w`

----

Name Rules
==========

* only letters, digits, underscore
* must not start with digit
* reserved words aren't allowed

----

Name Examples
=============

================= ========================================
 name              validity
================= ========================================
 :code:`w`         valid
 :code:`weight1`   valid
 :code:`1weight`   invalid: starts with digit
 :code:`minor?`    invalid: contains question mark
 :code:`return`    invalid: reserved word
================= ========================================

----

Case Sensitivity
================

* lowercase and uppercase names are not the same

================= ========================================
 name              validity
================= ========================================
 :code:`weight1`   valid
 :code:`Weight1`   valid, but not same as :code:`weight1`
================= ========================================

----

Combining Words
===============

* combine words with underscore

========================= ========================================
 name                      validity
========================= ========================================
 :code:`body_mass_index`   valid
 :code:`body mass index`   invalid: contains space
 :code:`body-mass-index`   invalid: contains dash
========================= ========================================

----

Naming Style
============

* prefer underscores to capitalization

========================= ==========================================
 name                      validity
========================= ==========================================
 :code:`body_mass_index`   valid, recommended
 :code:`bodyMassIndex`     valid, but not common C style
 :code:`BodyMassIndex`     valid, but at least start with lowercase
========================= ==========================================

----

Printing Variables
==================

* :code:`printf` function can print variable values

..

* every :code:`%` in string refers to a variable: *format specifier*
* variables listed in same order as in string

----

Print Syntax
============

.. parsed-literal::

   printf("... `%spec1 <annotate://box/orange>`_ ... `%spec2 <annotate://box/blue>`_ ...", `var1 <annotate://box/orange>`_, `var2 <annotate://box/blue>`_, ...);

* :code:`%spec1` specifies :code:`var1`,
  :code:`%spec2` specifies :code:`var2`, ...

----

Floating Point Formatting
=========================

.. container:: column width-1-2

   * specifier:

     :code:`%f`

   * :code:`n` digits after decimal point:

     :code:`%.nf`

   * | :code:`n` digits after decimal point,
     | :code:`m` in total (including point):

     :code:`%m.nf`

.. container:: column width-1-2 substep

   * | value not changed,
     | only formatted for display

----

Floating Point Output Examples
==============================

.. parsed-literal::

   printf("%f\\n", bmi);

.. class:: substep

.. container:: column width-1-2

   * | `one <annotate://box/orange>`_ digit after decimal point:
     |

   .. parsed-literal::

      printf("%\ `.1 <annotate://box/orange>`_\ f\\n", bmi);

.. class:: substep

.. container:: column width-1-2

   * | one digit after decimal point,
     | `four <annotate://box/orange>`_ characters in total:

   .. parsed-literal::

      printf("%\ `4 <annotate://box/orange>`_\ .1f\\n", bmi);

----

Mixed Output
============

* parts other than format specifiers printed as is

.. parsed-literal::

   printf("Body mass index: %.1f\\n", bmi);

----

BMI Program
===========

.. code:: c
   :class: smaller

   /*
    * This program calculates and prints
    * the body mass index of a person
    * who weighs 65.3kg and is 1.74m tall.
    */

   #include <stdio.h>  // printf

   int main() {
       double weight = 65.3;  // mass, in kg
       double height = 1.74;  // in m
       double bmi = weight / (height * height);
       printf("Body mass index: %.1f\n", bmi);
       return 0;
   }

:pan: -0.1, 0.1, -0.3
:pan: 0, 0, 0

----

Printing Expressions
====================

* format specifiers correspond to expressions, not variables
* result of calculation can be printed without assigning to variable

.. code:: c
   :class: smaller

   int main() {
       double weight = 65.3;  // mass, in kg
       double height = 1.74;  // in m
       printf("Body mass index: %.1f\n", weight / (height * height));
       return 0;
   }

:pan: -0.1, 0, -0.3
:pan: 0, 0, 0

----

Data Input
==========

* most programs will need to get data from the user
* working on fixed data: *hard-coded*

.. class:: substep

* get inputs
* process inputs and generate outputs
* print outputs

----

Input Function
==============

* :code:`scanf` function reads data from user
* and stores it in a variable
* variable has to be defined before input

..

* format specification similar to :code:`printf`
* also defined in :code:`stdio.h`

----

Prompt
======

* :code:`scanf` doesn't print `prompt <annotate://underline/orange>`_
* use :code:`printf` to print prompt first

----

Floating Point Input
====================

* specifier for :code:`double`:

  :code:`%lf`

* :code:`&` in front of variable name

----

Input Example
=============

.. parsed-literal::

   double weight = `0.0 <annotate://box/orange>`_;  // mass, in kg
   printf("Enter weight (in kg):`\  \ <annotate://box/orange>`_");
   scanf("`%lf <annotate://box/orange>`_", &weight);

----

BMI Program
===========

.. code:: c
   :class: smallest

   /*
    * This program calculates and prints
    * the body mass index of a person
    * whose weight and height are given by the user.
    */

   #include <stdio.h>  // printf, scanf

   int main() {
       double weight = 0.0;  // mass, in kg
       printf("Enter weight (in kg): ");
       scanf("%lf", &weight);

       double height = 0.0;  // in m
       printf("Enter height (in m): ");
       scanf("%lf", &height);

       double bmi = weight / (height * height);
       printf("Body mass index: %.1f\n", bmi);
       return 0;
   }

:pan: -0.12, 0, -0.4
:pan: -0.12, 0.2, -0.4
:pan: 0, 0, 0

----

Multiple Input
==============

* multiple pieces of data can be read in a single input
* user can separate them with spaces or new lines

.. parsed-literal::

    double weight = 0.0, height = 0.0;
    printf("Enter weight (in kg) and height (in m): ");
    scanf("%lf %lf", &weight, &height);

----

Assignment
==========

* value of variable can be changed
* *assignment*: store new value in variable
* replaces previous value

.. class:: substep

.. parsed-literal::

   variable = expression;

----

Assignment Example
==================

* change value of :code:`weight` to :code:`68.6`

.. parsed-literal::

   weight = 68.6;

----

Definition and Assignment
=========================

* assignment modifies value of `previously defined <annotate://underline/orange>`_ variable

.. parsed-literal::

   double weight = 65.3;  // definition
   ...
   weight = 68.6;         // assignment

----

Type in Assignment
==================

* no type definition in assignment

.. parsed-literal::

   double weight = 65.3;
   ...
   `double <annotate://crossed-off/red>`_ weight = 68.6;

----

Assignment and Equality
=======================

* *assignment is not equality*

.. container:: substep

   * evaluate expresion, store result in variable

   .. math::

      variable \leftarrow expression

----

Assignment and Equality Example
===============================

* what does the below code mean?

.. parsed-literal::

   weight = weight - 1.5;

.. class:: substep

* *weight EQUALS weight - 1.5???*

----

Assignment Explanation
======================

.. parsed-literal::

   double weight = 65.3;
   weight = weight - 1.5;

.. container:: substep

   * look up current value of :code:`weight` (:code:`65.3`)
   * calculate :code:`weight - 1.5` (:code:`63.8`)
   * store result in variable :code:`weight`

----

Left Hand Side
==============

* left hand side of an assignment has to be a variable

.. parsed-literal::

   `68.6 = weight; <annotate://crossed-off/red>`_

----

Variable Definitions
====================

* variables can be defined where they are first needed
* many programmers prefer to define all variables before first statement

----

Where Needed
============

.. parsed-literal::
   :class: small

   double weight = 0.0;  // mass, in kg
   printf("Enter weight (in kg): ");
   scanf("%lf", &weight);

   double height = 0.0;  // in m
   printf("Enter height (in m): ");
   scanf("%lf", &height);

   double bmi = weight / (height * height);

----

Before First Statement
======================

.. parsed-literal::
   :class: small

   double weight = 0.0;  // mass, in kg
   double height = 0.0;  // in m
   `double bmi = 0.0; <annotate://box/orange>`_     // body mass index

   printf("Enter weight (in kg): ");
   scanf("%lf", &weight);

   printf("Enter height (in m): ");
   scanf("%lf", &height);

   `bmi = weight / (height * height); <annotate://box/orange>`_

----

Integer
=======

.. container:: column width-1-3

   * regular:

     :code:`int`

   * narrower range:

     :code:`short int`

   * wider range:

     :code:`long int`

.. container:: column width-3-5

   .. class:: substep

   * sizes and ranges not set by standard

   .. class:: substep

   * if unsigned:

     * :code:`unsigned int`
     * :code:`unsigned short int`
     * :code:`unsigned long int`

----

Fractional Values
=================

* fractional parts of values are discarded

.. parsed-literal::

   double weight = 65.8;
   int weight_kg = weight;

* :code:`weight_kg` becomes :code:`65`

----

Inaccurate Value Problem
========================

* inaccurate representation of floating point values

.. parsed-literal::

   double height = 2.01;
   int height_cm = height * 100;

* :code:`2.01 * 100` gives :code:`200.99999999999997`
* :code:`height_cm` becomes :code:`200`

----

Integer I/O
===========

.. container:: column width-1-2

   * decimal:

     :code:`%d`

   * short:

     :code:`%hi`

   * long:

     :code:`%ld`

   * hexadecimal:

     :code:`%x`

.. container:: column width-1-2

   * unsigned:

     :code:`%u`

   * unsigned short:

     :code:`%hu`

   * unsigned long:

     :code:`%lu`

----

Fixed-Width Integers
====================

* sizes and ranges set by standard
* defined in :code:`stdint.h`

..

.. container:: column width-1-2

   * :code:`int8_t`
   * :code:`int16_t`
   * :code:`int32_t`
   * :code:`int64_t`

.. container:: column width-1-2

   * :code:`uint8_t`
   * :code:`uint16_t`
   * :code:`uint32_t`
   * :code:`uint64_t`

----

Data Size
=========

* getting data size:

  :code:`sizeof`

* size in bytes

----

Integer Sizes
=============

* getting integer sizes:

.. code:: c

   printf("int: %ld bytes\n", sizeof(int));
   printf("short int: %ld bytes\n", sizeof(short int));
   printf("long int: %ld bytes\n", sizeof(long int));

----

Integer Limits
==============

* defined in :code:`limits.h`

.. container:: column width-1-3

   * :code:`INT_MIN`
   * :code:`SHRT_MIN`
   * :code:`LONG_MIN`

.. container:: column width-1-3

   * :code:`INT_MAX`
   * :code:`SHRT_MAX`
   * :code:`LONG_MAX`

.. container:: column width-1-3

   * :code:`UINT_MAX`
   * :code:`USHRT_MAX`
   * :code:`ULONG_MAX`

----

Integer Division
================

* if both operands are integers:

.. container:: column width-1-2

   * quotient:

     :code:`x / y`

     * example:

       :math:`14 / 4 = 3`

.. container:: column width-1-2 substep

   * remainder (modulo):

     :code:`x % y`

     * example:

       :math:`14 \% 4 = 2`

----

Integer Division Example
========================

* convert minutes to hours and minutes

.. parsed-literal::

   int duration = 137;  // in minutes
   int hours = duration / 60;
   int minutes = duration % 60;

----

Unintended Integer Division
===========================

* division between integers gives only quotient

.. parsed-literal::

   int height_cm = 174;
   double height = `height_cm <annotate://box/orange>`_ / `100 <annotate://box/orange>`_;

* result is :code:`1.0`, not :code:`1.74`

----

Fix: Unintended Integer Division
================================

* make an operand floating point:

.. parsed-literal::

   int height_cm = 174;
   double height = height_cm / `100.0 <annotate://box/orange>`_;

----

Type Conversion
===============

* converting values from one type to another:

  *type casting*

----

Conversion Issues
=================

* some conversions are straightforward

   * convert integer to floating point

.. class:: substep

* some conversions require more attention

   * convert floating point to integer

----

Implicit Conversion
===================

* explicit conversion: by programmer

..

* implicit conversion: by compiler

  * when the operation calls for it

----

Implicit Conversion Examples
============================

* when assigned value type is different from variable type

  * assign integer value to floating point variable

.. class:: substep

* when an operand has a different type

  * add a floating point value with an integer value

----

Type Conversion
===============

* syntax for type conversion:

  .. parsed-literal::

       (type) expression

----

Unintended Integer Division
===========================

* division between integers gives only quotient

.. parsed-literal::

   int height_cm = 174;
   double height = height_cm / 100;

* result is :code:`1.0`, not :code:`1.74`

----

Fix: Floating Point Literal
===========================

* make :code:`100` floating point:

.. parsed-literal::

   double height = `height_cm <annotate://box/orange>`_ / 100.0;

----

Fix: Type Conversion
====================

* make :code:`height_cm` floating point:

.. parsed-literal::

  double height = `(double) height_cm <annotate://box/orange>`_ / 100;

----

Incorrect Fix
=============

* conversion applies to first expression

.. parsed-literal::

   double height = (double) `height_cm <annotate://box/orange>`_ / 100;

   double height = (double) `(height_cm / 100) <annotate://box/red>`_;

----

Incompatible Value
==================

* type of expression isn't compatible with type of variable
* compiler error or warning

.. parsed-literal::

   double weight = "65.3";

----

Out of Range Value
==================

* assigned value not in variable type's range: *overflow*
* compiler warning

.. parsed-literal::

   short int x = 70000;

----

Taxi Fare
=========

* switch-on price
* per unit distance price

..

* minimal fare: hop-on hop-off price

----

New York Taxi Fare
==================

* switch-on price:

  $2.50

* per unit distance price:

  $0.50 per 0.2 miles

----

New York Taxi Fare Formula
==========================

* :math:`d`: travel distance (in miles)

.. math::

   2.50 + 0.50 \cdot \left\lfloor \frac{d}{0.2} \right\rfloor

----

Istanbul Taxi Fare
==================

* switch-on price:

  5.00 TL

* per unit distance price:

  0.31 TL per 0.1 km

* minimal fare: 13.00TL

----

Constants
=========

* some values in expressions are fixed: *constant*

.. class:: column width-1-2

   * general constants

     :math:`\pi`: :math:`3.14159...`

     1 inch = :math:`2.54` cm

.. class:: column width-1-2

   * problem-specific constants

----

Literal Constants
=================

* using literals for constants makes the code hard to understand

.. parsed-literal::

   2.50 + 0.50 * (distance / 0.2)

* what do these numbers represent?

..

* named constants are easier to read

----

Maintenance
===========

* literal values also make maintenance harder
* what if you need to change one?

.. class:: substep

* named constants are easier to change

----

Maintenance Example
===================

* assume that your code has many :math:`0.2` literals
* unit distance, tax rate, ...
* tax rate is changed

----

Constant Definition
===================

* defining a constant: :code:`const`

.. code:: c

   const type name = value;

.. class:: substep

* *read-only variable*

----

Manipulating Constants
======================

* assigning to a constant causes a compiler error
* omitting value causes a compiler warning

----

New York Taxi Fare Constants
============================

* define problem-specific constants:

.. code:: c

   const double switch_on = 2.50;     // in dollars
   const double per_unit = 0.50;      // in dollars
   const double unit_distance = 0.2;  // in miles

----

New York Taxi Fare Calculation
==============================

* use the constants:

.. parsed-literal::

   switch_on + per_unit * `(int) (distance / unit_distance) <annotate://box/orange>`_;

----

New York Taxi Fare Program
==========================

.. code:: c
   :class: smallest

   /*
    * This program calculates and prints the approximate taxi fare
    * in New York City for a travel distance given by the user.
    */

   #include <stdio.h>  // printf, scanf

   int main() {
       const double switch_on = 2.50;     // switch-on price, in dollars
       const double per_unit = 0.50;      // price per unit distance, in dollars
       const double unit_distance = 0.2;  // unit distance, in miles
       double distance = 0.0;             // travel distance, in miles
       double fare = 0.0;                 // in dollars

       printf("Enter travel distance (in miles): ");
       scanf("%lf", &distance);

       fare = switch_on + per_unit * (int) (distance / unit_distance);
       printf("Fare: $%.2f\n", fare);
       return 0;
   }

:pan: -0.15, 0.17, -0.42
:pan: 0, 0, 0

----

Macro Constant
==============

.. container:: column width-2-5

   * defining a macro constant:

   .. code:: c

      #define NAME value

   * | use all capital letters
     | (convention)

.. container:: column width-1-2

   .. class:: substep

   * directive
   * outside of functions

   .. class:: substep

   * not a read-only variable
   * no explicit type
   * find and replace in source code

----

Macro Constant Examples
=======================

* define general constants

.. code:: c

   #define PI 3.14159
   #define CM_PER_INCH 2.54

----

New York Taxi Fare
==================

* what if we want to let users enter distance in km?

.. code:: c

   #define KM_PER_MILE 1.6093

----

Distance Conversion
===================

.. code:: c

   double distance_km = 0.0;          // in kilometers
   double distance = 0.0;             // in miles

   printf("Enter distance (in km): ");
   scanf("%lf", &distance_km);
   distance = distance_km / KM_PER_MILE;

----

New York Taxi Fare Program
==========================

.. code:: c
   :class: smallest

   #include <stdio.h>  // printf, scanf

   #define KM_PER_MILE 1.6093

   int main() {
       const double switch_on = 2.50;     // switch-on price, in dollars
       const double per_unit = 0.50;      // price per unit distance, in dollars
       const double unit_distance = 0.2;  // unit distance, in miles
       double distance_km = 0.0;          // travel distance, in km
       double distance = 0.0;             // travel distance, in miles
       double fare = 0.0;                 // in dollars

       printf("Enter distance (in km): ");
       scanf("%lf", &distance_km);
       distance = distance_km / KM_PER_MILE;

       fare = switch_on + per_unit * (int) (distance / unit_distance);
       printf("Fare: $%.2f\n", fare);
       return 0;
   }

:pan: -0.15, 0.12, -0.42
:pan: 0, 0, 0

----

Program Result
==============

.. code:: c

   #include <stdio.h>  // printf

   int main() {
       printf("Hello, world!\n");
       return 0;
   }

* what does that 0 mean?

----

Return Codes
============

* macro constants: :code:`EXIT_SUCCESS` and :code:`EXIT_FAILURE`

.. code:: c
   :class: small

   #include <stdio.h>   // printf
   #include <stdlib.h>  // EXIT_SUCCESS

   int main() {
       printf("Hello, world!\n");
       return EXIT_SUCCESS;
   }

----

Combined Assignment
===================

* assignment can be combined with operation

.. code:: c

   counter += 1;
   // counter = counter + 1;

   total += item_count * item_price;
   // total = total + item_count * item_price;

----

Operators
=========

* works with all operators

.. code:: c

   counter -= 1;
   // counter = counter - 1;

   size *= 2;
   // size = size * 2;

----

Increment and Decrement
=======================

* increment and decrement by 1 are very common

* special operators: :code:`++` and :code:`--`

* before or after variable name

----

Increment and Decrement Examples
================================

.. container:: column width-1-2

   * increment

   .. code:: c

      counter++;

      ++counter;

      // counter = counter + 1;

.. container:: column width-1-2

   * decrement

   .. code:: c

      counter--;

      --counter;

      // counter = counter - 1;

----

Operator Placement
==================

* placement significant when part of expression

..

* after: use current value, then increment/decrement
* before: first increment/decrement, then use value

----

Operator Placement Example
==========================

.. container:: column width-1-2

   * after variable

   .. code:: c

      x = counter++;

      // x = counter;
      // counter++;


.. container:: column width-1-2

   * before variable

   .. code:: c

      x = ++counter;

      // counter++;
      // x = counter;

----

Function
========

* *function*: unit of code that performs a task
* and returns a result

..

* example:

  square root of 7.2


----

Parameters
==========

* functions can take *parameters*
* same function working on different values

..

* examples:

  square root of a number

  greatest common divisor of two numbers

----

Parameter Terminology
=====================

* parameter: *input parameter*
* result: *output parameter*

----

Function Code
=============

.. container:: column width-1-2

   * *function definition*

     * name

     * `formal parameters <annotate://underline/orange>`_

     * description of how

.. container:: column width-1-2

   * *function call*

     * name

     * `actual parameters <annotate://underline/orange>`_

.. container:: column width-1-2

   * only once

.. container:: column width-1-2

   * any number of times

----

Function Code Examples
======================

.. container:: column width-1-2

   * name: :code:`sqrt`
   * formal parameter: :code:`x`

   ..

   * name: :code:`gcd`
   * formal parameters: :code:`m`, :code:`n`

.. container:: column width-1-2 substep

   * :code:`sqrt(7.2)`
   * actual parameter for :code:`x`\: :code:`7.2`

   ..

   * :code:`sqrt(186)`
   * actual parameter for :code:`x`\: :code:`186`

   ..

   * call: :code:`gcd(42, 30)`
   * actual parameter for :code:`m`\: :code:`42`
   * actual parameter for :code:`n`\: :code:`30`

----

Libraries
=========

* libraries contain function definitions

----

Functions in Expressions
========================

* function call can be part of expression
* result replaces call

..

.. parsed-literal::

   (1 + `sqrt(5) <annotate://box/orange>`_\) / 2

   (1 + `2.236 <annotate://box/orange>`_\) / 2

----

Body Surface Area
=================

* Du Bois formula:

  * :math:`w`: weight (mass, kg)
  * :math:`h`: height (cm)
  * :math:`bsa`: body surface area (m\ :sup:`2`)

.. math::

   bsa = 0.007184 \cdot w^{0.425} \cdot h^{0.725}

----

Mathematical Functions
======================

* standard library contains commonly used mathematical functions:

..

* square root, exponentiation, logarithms
* trigonometric functions
* round, ceiling, floor

.. class:: substep

* need to include :code:`math.h`

----

Exponentiation
==============

* :code:`pow` function

..

* :math:`x^y`

  .. parsed-literal::

     pow(x, y)

* parameters and result are all of type :code:`double`

----

Body Surface Area
=================

.. parsed-literal::
   :class: smallest

   #include <stdio.h>   // printf, scanf
   #include <stdlib.h>  // EXIT_SUCCESS
   `#include \<math.h\> <annotate://box/orange>`_    // pow

   int main() {
       double weight = 0.0;  // mass, in kg
       double height = 0.0;  // in cm
       double bsa = 0.0;     // in m2

       printf("Enter weight (in kg): ");
       scanf("%lf", &weight);

       printf("Enter height (in cm): ");
       scanf("%lf", &height);

       bsa = 0.007184 * `pow(weight, 0.425) <annotate://box/orange>`_ * `pow(height, 0.725) <annotate://box/orange>`_;
       printf("Body surface area: %.2f m2\\n", bsa);
       return EXIT_SUCCESS;
   }
