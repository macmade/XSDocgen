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
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

bool XSDocgen_CreateDirectory( const char * path, const char * name )
{
    char * dir;
    int    e;
    
    if( XSDocgen_DirectoryExists( path ) == false )
    {
        return false;
    }
    
    dir = XSDocgen_CreateString( path );
    dir = XSDocgen_AppendString( dir, "/" );
    dir = XSDocgen_AppendString( dir, name );
    
    if( XSDocgen_DirectoryExists( dir ) )
    {
        XSDocgen_FreeString( dir );
        
        return true;
    }
    
    e = mkdir( dir, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH );
    
    XSDocgen_FreeString( dir );
    
    if( e == 0 )
    {
        return true;
    }
    
    return false;
}
