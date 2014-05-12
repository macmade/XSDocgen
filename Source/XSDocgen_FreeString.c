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
#include <stdio.h>
#include <errno.h>

bool XSDocgen_CreateDirectory( const char * path, const char * name )
{
    char * dir;
    int    e;
    size_t dirLength;
    size_t pathLength;
    size_t nameLength;
    
    if( XSDocgen_DirectoryExists( path ) == false )
    {
        return false;
    }
    
    pathLength = strlen( path );
    nameLength = strlen( name );
    dirLength  = pathLength + nameLength + 2;
    dir        = calloc( dirLength, 1 );
    
    if( dir == NULL )
    {
        return false;
    }
    
    strlcat( dir, path, dirLength );
    
    dirLength -= pathLength;
    
    if( path[ strlen( path ) - 1 ] != '/' )
    {
        strlcat( dir, "/", dirLength );
        
        dirLength -= 1;
    }
    
    strlcat( dir, name, dirLength );
    
    if( XSDocgen_DirectoryExists( dir ) )
    {
        free( dir );
        
        return true;
    }
    
    e = mkdir( dir, 755 );
    
    free( dir );
    
    if( e == 0 || e == EEXIST )
    {
        return true;
    }
    
    return false;
}
