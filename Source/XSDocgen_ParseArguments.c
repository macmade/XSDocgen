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

#include <stdlib.h>
#include <string.h>
#include <XSDocgen.h>

XSDocgen_Arguments * XSDocgen_ParseArguments( int argc, const char ** argv )
{
    XSDocgen_Arguments * args;
    int                  i;
    bool                 help;
    
    args = calloc( sizeof( XSDocgen_Arguments ), 1 );
    
    if( args == NULL )
    {
        return NULL;
    }
    
    args->help = true;
    help       = false;
    
    if( argc < 2 || argv == NULL )
    {
        return args;
    }
    
    for( i = 1; i < argc; i++ )
    {
        if( strcmp( argv[ i ], "--help" ) == 0 )
        {
            args->help = true;
            help       = true;
        }
        else if( strcmp( argv[ i ], "--version" ) == 0 )
        {
            args->version = true;
        }
        else if( strcmp( argv[ i ], "--verbose" ) == 0 )
        {
            args->verbose = true;
        }
        else if( strcmp( argv[ i ], "--enable-c++" ) == 0 )
        {
            args->cpp = true;
        }
        else if( strcmp( argv[ i ], "--clear" ) == 0 )
        {
            args->clear = true;
        }
        else if( strcmp( argv[ i ], "--undocumented" ) == 0 )
        {
            args->undocumented = true;
        }
        else if( strcmp( argv[ i ], "--google-analytics-display-features" ) == 0 )
        {
            args->analyticsDisplayFeatures = true;
        }
        else if( strcmp( argv[ i ], "--source" ) == 0 && i < ( argc - 1 ) )
        {
            args->source = argv[ ++i ];
            args->help   = ( help == false ) ? false : true;
        }
        else if( strcmp( argv[ i ], "--output" ) == 0 && i < ( argc - 1 ) )
        {
            args->output = argv[ ++i ];
            args->help   = ( help == false ) ? false : true;
        }
        else if( strcmp( argv[ i ], "--project-name" ) == 0 && i < ( argc - 1 ) )
        {
            args->projectName = argv[ ++i ];
            args->help        = ( help == false ) ? false : true;
        }
        else if( strcmp( argv[ i ], "--project-copyright" ) == 0 && i < ( argc - 1 ) )
        {
            args->projectCopyright = argv[ ++i ];
            args->help             = ( help == false ) ? false : true;
        }
        else if( strcmp( argv[ i ], "--project-version" ) == 0 && i < ( argc - 1 ) )
        {
            args->projectVersion = argv[ ++i ];
            args->help           = ( help == false ) ? false : true;
        }
        else if( strcmp( argv[ i ], "--project-timezone" ) == 0 && i < ( argc - 1 ) )
        {
            args->projectTimezone = argv[ ++i ];
            args->help            = ( help == false ) ? false : true;
        }
        else if( strcmp( argv[ i ], "--company-name" ) == 0 && i < ( argc - 1 ) )
        {
            args->companyName = argv[ ++i ];
            args->help        = ( help == false ) ? false : true;
        }
        else if( strcmp( argv[ i ], "--company-url" ) == 0 && i < ( argc - 1 ) )
        {
            args->companyURL = argv[ ++i ];
            args->help       = ( help == false ) ? false : true;
        }
        else if( strcmp( argv[ i ], "--page-home" ) == 0 && i < ( argc - 1 ) )
        {
            args->pageHome = argv[ ++i ];
            args->help     = ( help == false ) ? false : true;
        }
        else if( strcmp( argv[ i ], "--source-root-prefix" ) == 0 && i < ( argc - 1 ) )
        {
            args->sourceRootPrefix = argv[ ++i ];
            args->help             = ( help == false ) ? false : true;
        }
        else if( strcmp( argv[ i ], "--exclude-file" ) == 0 && i < ( argc - 1 ) )
        {
            args->excludeFile = argv[ ++i ];
            args->help        = ( help == false ) ? false : true;
        }
        else if( strcmp( argv[ i ], "--classes-prefix" ) == 0 && i < ( argc - 1 ) )
        {
            args->classesPrefix = argv[ ++i ];
            args->help          = ( help == false ) ? false : true;
        }
        else if( strcmp( argv[ i ], "--functions-prefix" ) == 0 && i < ( argc - 1 ) )
        {
            args->functionsPrefix = argv[ ++i ];
            args->help            = ( help == false ) ? false : true;
        }
        else if( strcmp( argv[ i ], "--types-prefix" ) == 0 && i < ( argc - 1 ) )
        {
            args->typesPrefix = argv[ ++i ];
            args->help        = ( help == false ) ? false : true;
        }
        else if( strcmp( argv[ i ], "--google-analytics" ) == 0 && i < ( argc - 2 ) )
        {
            args->help              = ( help == false ) ? false : true;
            args->analyticsCode     = argv[ ++i ];
            args->analyticsDomain   = argv[ ++i ];
        }
        else if( strcmp( argv[ i ], "--page-add" ) == 0 && i < ( argc - 2 ) )
        {
            args->help = ( help == false ) ? false : true;
            
            {
                XSDocgen_Page * page;
                XSDocgen_Page * prev;
                
                page = calloc( sizeof( XSDocgen_Page ), 1 );
                
                if( page == NULL )
                {
                    continue;
                }
                
                page->title = argv[ ++i ];
                page->path  = argv[ ++i ];
                
                prev = args->pages;
                
                if( prev == NULL )
                {
                    args->pages = page;
                }
                else
                {
                    while( prev != NULL )
                    {
                        if( prev->next == NULL )
                        {
                            prev->next = page;
                            
                            break;
                        }
                        
                        prev = prev->next;
                    }
                }
            }
        }
        else if( strcmp( argv[ i ], "--html-header-add" ) == 0 && i < ( argc - 1 ) )
        {
            args->help = ( help == false ) ? false : true;
            
            {
                XSDocgen_HTMLHeaderLine * line;
                XSDocgen_HTMLHeaderLine * prev;
                
                line = calloc( sizeof( XSDocgen_HTMLHeaderLine ), 1 );
                
                if( line == NULL )
                {
                    continue;
                }
                
                line->html = argv[ ++i ];
                
                prev = args->headerLines;
                
                if( prev == NULL )
                {
                    args->headerLines = line;
                }
                else
                {
                    while( prev != NULL )
                    {
                        if( prev->next == NULL )
                        {
                            prev->next = line;
                            
                            break;
                        }
                        
                        prev = prev->next;
                    }
                }
            }
        }
    }
    
    return args;
}
