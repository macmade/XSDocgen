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

#ifndef _XSDOCGEN_FUNCTIONS_H_
#define _XSDOCGEN_FUNCTIONS_H_

#include <XSDocgen-Types.h>

XSDocgen_Arguments * XSDocgen_ParseArguments( int argc, const char ** argv );
void                 XSDocgen_FreeArguments( XSDocgen_Arguments * args );

void XSDocgen_ShowHelp( void );
void XSDocgen_ShowVersion( void );

bool XSDocgen_FileExists( const char * path );
bool XSDocgen_DirectoryExists( const char * path );
bool XSDocgen_CreateDirectory( const char * path, const char * name );
bool XSDocgen_CopyFiles( const char * source, const char * destination );
bool XSDocgen_ClearFiles( const char * path );

char * XSDocgen_CreateString( const char * str );
char * XSDocgen_AppendString( char * str, const char * append );
void   XSDocgen_FreeString( char * str );

#endif /* _XSDOCGEN_FUNCTIONS_H_ */
