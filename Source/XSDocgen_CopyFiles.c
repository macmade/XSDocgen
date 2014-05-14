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
#include <dirent.h>
#include <sys/stat.h>

static void __XSDocgen_CopyFiles( DIR * dir, const char * source, const char * destination );
static void __XSDocgen_CopyFiles( DIR * dir, const char * source, const char * destination )
{
    struct stat     s;
    struct dirent * file;
    int             e;
    char          * filePath;
    char          * destPath;
    DIR           * sub;
    FILE          * fh1;
    FILE          * fh2;
    char          * buf;
    size_t          len;
    
    if( dir == NULL || source == NULL || destination == NULL )
    {
        return;
    }
    
    buf = malloc( 4096 );
    
    if( buf == NULL )
    {
        return;
    }
    
    while( ( file = readdir( dir ) ) )
    {
        if( file->d_namlen > 0 && file->d_name[ 0 ] == '.' )
        {
            continue;
        }
        
        filePath = XSDocgen_CreateString( source );
        filePath = XSDocgen_AppendString( filePath, "/" );
        filePath = XSDocgen_AppendString( filePath, file->d_name );
        destPath = XSDocgen_CreateString( destination );
        destPath = XSDocgen_AppendString( destPath, "/" );
        destPath = XSDocgen_AppendString( destPath, file->d_name );
        
        e = stat( filePath, &s );
        
        if( e == 0 )
        {
            if( S_ISDIR( s.st_mode ) )
            {
                sub = opendir( filePath );
                
                if( sub != NULL )
                {
                    XSDocgen_CreateDirectory( destination, file->d_name );
                    __XSDocgen_CopyFiles( sub, filePath, destPath );
                    closedir( sub );
                }
            }
            else if( S_ISREG( s.st_mode ) )
            {
                fh1 = fopen( filePath, "rb" );
                fh2 = fopen( destPath, "wb" );
                
                if( fh1 != NULL && fh2 != NULL )
                {
                    while( !feof( fh1 ) )
                    {
                        len = fread( buf, 1, 4096, fh1 );
                        
                        fwrite( buf, 1, len, fh2 );
                    }
                }
                
                if( fh1 != NULL ) { fclose( fh1 ); }
                if( fh1 != NULL ) { fclose( fh2 ); }
            }
        }
        
        XSDocgen_FreeString( filePath );
        XSDocgen_FreeString( destPath );
    }
    
    free( buf );
}

bool XSDocgen_CopyFiles( const char * source, const char * destination )
{
    DIR * dir;
    
    if( source == NULL || destination == NULL )
    {
        return false;
    }
    
    if( strlen( source ) == 0 || strlen( destination ) == 0 )
    {
        return false;
    }
    
    if( XSDocgen_DirectoryExists( source ) == false || XSDocgen_DirectoryExists( destination ) == false )
    {
        return false;
    }
    
    dir = opendir( source );
    
    if( dir == NULL )
    {
        return false;
    }
    
    __XSDocgen_CopyFiles( dir, source, destination );
    
    closedir( dir );
    
    return true;
}
