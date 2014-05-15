XSDocgen
========

About
-----

An Apple-like documentation generator for C, C++ and Objective-C based on HeaderDoc.

XSDocgen uses the [HeaderDoc](https://developer.apple.com/library/mac/documentation/DeveloperTools/Conceptual/HeaderDoc/intro/intro.html) utility to produce documentation from header files in XML format.  
Once the XML files have been generated, it will create a standalone PHP website, displaying the documentation.

Highlights
----------

 * Support for custom HTML/PHP pages for additional documentation (companion guides).
 * Printer friendly version.
 * Full search from the documentation and the additional pages.
 * Full XHTML 1.0 strict and CSS compliance.
 * C, C++ and Objective-C support.

Example documentation
---------------------

### C project:

A real world C example output can be found at: http://doc.xs-labs.com/XSFoundation/

### Objective-C project:

A real world Objective-C example output can be found at: http://doc.xs-labs.com/ClangKit/

Build & Installation
--------------------

From the XSDocgen root directory, from a command line prompt, type:

    make
    sudo make install
    
This will build XSDocgen and install it in `/usr/local/`.  
The executable will be located in `/usr/local/bin/`, while the resources will be located in `/usr/local/share/`.

Command line options
--------------------

 * `--help`  
   Displays the program's help.
 * `--version`  
   Displays the program's version.
 * `--verbose`  
   Displays the output from HeaderDoc.
 * `--enable-c++`  
   Turns on C++ support for HeaderDoc.
 * `--source [PATH]`  
   The path of the source files/headers (**mandatory**).
 * `--output [PATH]`  
   The path of the output directory (**mandatory** - the directory must exist).
 * `--clear`  
   Clears all previous output files from the XSDocgen output directories.
 * `--undocumented`  
   Keeps undocumented members.
 * `--project-name [VALUE]`  
   The name of the project (**mandatory**).
 * `--project-copyright [VALUE]`  
   The copyright string (**mandatory** - may contain date format specifiers).
 * `--project-version [VALUE]`  
   The project version string (**mandatory**).
 * `--project-timezone [VALUE]`  
   An optional timezone specifier (eg: `Europe/Zurich`).
 * `--company-name [VALUE]`  
   The company name (**mandatory**).
 * `--company-url [VALUE]`   
   The URL of the company website.
 * `--page-home [PATH]`  
   The path to an HTML or PHP file (body contents only) to use as start page.
 * `--exclude-file [PATH]`  
    The path to file with paths to exclude.
 * `--source-root-prefix [PATH]`  
   A path prefix to strip from the documentation output.
 * `--classes-prefix [PATH]`  
   An optional path from which the files should be categorised as classes.
 * `--functions-prefix [PATH]`  
   An optional path from which the files should be categorised as functions.
 * `--types-prefix [PATH]`  
   An optional path from which the files should be categorised as types.
 * `--page-add [TITLE] [PATH]`  
   The path to an HTML or PHP file (body contents only) to add to the documentation.  
   This argument can be specified multiple times.
 * `--html-header-add [VALUE]`  
   An optional string to add to the header of the HTML output.  
   You can use it to add custom CSS files, scripts, meta tags, etc.  
   This argument can be specified multiple times.
 * `--google-analytics [CODE] [DOMAIN]`  
   An optional tracking code and domain if you want to use Google Analytics.

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
