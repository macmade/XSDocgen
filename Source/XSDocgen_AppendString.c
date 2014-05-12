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
#include <stdlib.h>
#include <string.h>

char * XSDocgen_AppendString( char * str, const char * append )
{
    size_t l1;
    size_t l2;
    
    l1 = ( str    == NULL ) ? 0 : strlen( str );
    l2 = ( append == NULL ) ? 0 : strlen( append );
    
    if( append == NULL || l2 == 0 )
    {
        return str;
    }
    
    if( str == NULL || l2 == 0 )
    {
        return XSDocgen_CreateString( append );
    }
    
    str = realloc( str, l1 + l2 + 1 );
    
    if( str != NULL )
    {
        strlcat( str, append, l1 + l2 + 1 );
    }
    
    return str;
}
