/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014 Jean-David Gadina - www-xs-labs.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

/* $Id$ */

#include <XSDocgen.h>
#include <stdio.h>

void XSDocgen_ShowHelp( void )
{
    printf
    (
        "XSDocgen - Version %s\n"
        "\n"
        "Available options:\n"
        "\n"
        "    --help                         Displays the program's help.\n"
        "    --version                      Displays the program's version.\n"
        "    --verbose                      Displays the output from HeaderDoc.\n"
        "    --enable-c++                   Turns on C++ support for HeaderDoc.\n"
        "    --source [PATH]                The path of the source files/headers (mandatory).\n"
        "    --output [PATH]                The path of the output directory (mandatory - the directory must exist).\n"
        "    --clear                        Clears all previous output files from the XSDocgen output directories.\n"
        "    --undocumented                 Keeps undocumented members.\n"
        "    --project-name [VALUE]         The name of the project (mandatory).\n"
        "    --project-copyright [VALUE]    The copyright string (mandatory - may contain date format specifiers).\n"
        "    --project-version [VALUE]      The project version string (mandatory).\n"
        "    --project-timezone [VALUE]     An optional timezone specifier (eg: `Europe/Zurich`).\n"
        "    --company-name [VALUE]         The company name.\n"
        "    --company-url [VALUE]          The URL of the company website.\n"
        "    --page-home [PATH]             The path to an HTML or PHP file (body contents only) to use as start page.\n"
        "    --exclude-file [PATH]          The path to file with paths to exclude.\n"
        "    --source-root-prefix [PATH]    A path prefix to strip from the documentation output.\n"
        "    --classes-prefix [PATH]        An optional path from which the files should be categorised as classes.\n"
        "    --functions-prefix [PATH]      An optional path from which the files should be categorised as functions.\n"
        "    --types-prefix [PATH]          An optional path from which the files should be categorised as types.\n"
        "    --page-add [TITLE] [PATH]      The path to an HTML or PHP file (body contents only) to add to the documentation.\n"
        "                                   This argument can be specified multiple times.\n"
        "    --html-header-add [VALUE]      An optional string to add to the header of the HTML output.\n"
        "                                   You can use it to add custom CSS files, scripts, meta tags, etc.\n"
        "                                   This argument can be specified multiple times.\n",
        XSDOCGEN_VERSION
    );
}
