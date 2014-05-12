XSDocgen
========

About
-----

An Apple-like documentation generator based on HeaderDoc.

Example documentation
---------------------

A real world example output can be found at: http://doc.xs-labs.com/XSFoundation/

Command line options:
---------------------

 * `--help`  
   Displays the program's help
 * `--version`  
   Displays the program's version
 * `--silent`  
   Don't output anything to the standard output (including errors)
 * `--enable-c++`  
   Turns on C++ support for HeaderDoc
 * `--with-headerdoc [PATH]`  
   Specifies a custom path for the `headerdoc2html` utility
 * `--source [PATH]`  
   The path of the source files/headers (**mandatory**)
 * `--output [PATH]`  
   The path of the output directory (**mandatory** - the directory must exist)
 * `--project-name [VALUE]`  
   The name of the project (**mandatory**)
 * `--project-copyright [VALUE]`  
   The copyright string (**mandatory** - may contain date format specifiers)
 * `--project-version [VALUE]`  
   The project version string (**mandatory**)
 * `--project-timezone [VALUE]`  
   An optional timezone specifier (eg: `Europe/Zurich`)
 * `--company-name [VALUE]`  
   The company name (**mandatory**)
 * `--company-url [VALUE]`   
   The URL of the company website
 * `--page-home [PATH]`  
   The path to an HTML or PHP file (body contents only) to use as start page
 * `--page-add [PATH] [TITLE]`  
   The path to an HTML or PHP file (body contents only) to add to the documentation
 * `--source-root-prefix [PATH]`  
   A path prefix to strip from the documentation output
 * `--class-prefix [PATH]`  
   An optional path from which the files should be categorised as classes.
 * `--functions-prefix [PATH]`  
   An optional path from which the files should be categorised as functions.
 * `--types-prefix [PATH]`  
   An optional path from which the files should be categorised as types.
   

Invocation example
------------------

    XSDocgen --source ./source \
             --output ./doc \
             --project-name "My Project"
             --project-copyright "XS-Labs &copy; %Y - All Rights Reserved"
             --project-version "1.0.0-0"
             --company-name "XS-Labs"
             --company-url "http://www.xs-labs.com/"

License
-------

XSDocgen is released under the terms of the MIT license.

Repository Infos
----------------

    Owner:			Jean-David Gadina - XS-Labs
    Web:			www.xs-labs.com
    Blog:			www.noxeos.com
    Twitter:		@macmade
    GitHub:			github.com/macmade
    LinkedIn:		ch.linkedin.com/in/macmade/
    StackOverflow:	stackoverflow.com/users/182676/macmade
