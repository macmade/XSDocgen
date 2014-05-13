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
#include <dirent.h>
#include <unistd.h>
#include <string.h>

static void __XSDocgen_ClearFiles( DIR * dir, const char * path );
static void __XSDocgen_ClearFiles( DIR * dir, const char * path )
{
    struct stat     s;
    struct dirent * file;
    int             e;
    char          * filePath;
    DIR           * sub;
    
    if( dir == NULL || path == NULL )
    {
        return;
    }
    
    while( ( file = readdir( dir ) ) )
    {
        if( file->d_namlen > 0 && file->d_name[ 0 ] == '.' )
        {
            continue;
        }
        
        filePath = XSDocgen_CreateString( path );
        filePath = XSDocgen_AppendString( filePath, "/" );
        filePath = XSDocgen_AppendString( filePath, file->d_name );
        
        e = stat( filePath, &s );
        
        if( e == 0 )
        {
            if( S_ISDIR( s.st_mode ) )
            {
                sub = opendir( filePath );
                
                if( sub != NULL )
                {
                    __XSDocgen_ClearFiles( sub, filePath );
                    rmdir( filePath );
                }
            }
            else if( S_ISREG( s.st_mode ) )
            {
                unlink( filePath );
            }
        }
        
        XSDocgen_FreeString( filePath );
    }
}

bool XSDocgen_ClearFiles( const char * path )
{
    DIR * dir;
    
    if( path == NULL )
    {
        return false;
    }
    
    if( strlen( path ) == 0 )
    {
        return false;
    }
    
    if( XSDocgen_DirectoryExists( path ) == false )
    {
        return false;
    }
    
    dir = opendir( path );
    
    if( dir == NULL )
    {
        return false;
    }
    
    __XSDocgen_ClearFiles( dir, path );
    
    closedir( dir );
    
    return true;
}
