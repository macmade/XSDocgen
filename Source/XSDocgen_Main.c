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
#include <stdio.h>
#include <string.h>
#include <XSDocgen.h>

int main( int argc, const char * argv[] )
{
    XSDocgen_Arguments * args;
    bool                 exit;
    int                  e;
    char               * headerdoc;
    char               * xmlDir;
    char               * cssDir;
    char               * phpDir;
    char               * index;
    char               * indexFile;
    FILE               * fh;
    XSDocgen_Page      * page;
    
    exit = false;
    args = XSDocgen_ParseArguments( argc, argv );
    
    if( args == NULL || args->help )
    {
        XSDocgen_ShowHelp();
        
        return EXIT_SUCCESS;
    }
    else if( args->version )
    {
        XSDocgen_ShowVersion();
        
        return EXIT_SUCCESS;
    }
    
    if( args->source           == NULL ) { printf( "Missing argument: --source [PATH]\n" );             exit = true; }
    if( args->output           == NULL ) { printf( "Missing argument: --output [PATH]\n" );             exit = true; }
    if( args->projectName      == NULL ) { printf( "Missing argument: --project-name [VALUE]\n" );      exit = true; }
    if( args->projectCopyright == NULL ) { printf( "Missing argument: --project-copyright [VALUE]\n" ); exit = true; }
    if( args->projectVersion   == NULL ) { printf( "Missing argument: --project-version [VALUE]\n" );   exit = true; }
    if( args->companyName      == NULL ) { printf( "Missing argument: --company-name [VALUE]\n" );      exit = true; }
    
    if( args->source      != NULL && XSDocgen_DirectoryExists( args->source ) == false ) { printf( "Error: source directory does not exist (%s)\n", args->source  ); exit = true; }
    if( args->output      != NULL && XSDocgen_DirectoryExists( args->output ) == false ) { printf( "Error: output directory does not exist (%s)\n", args->output  ); exit = true; }
    if( args->excludeFile != NULL && XSDocgen_FileExists( args->excludeFile ) == false ) { printf( "Error: exclude file does not exist (%s)\n", args->excludeFile ); exit = true; }
    
    if( exit )
    {
        return EXIT_FAILURE;
    }
    
    printf( "Staring XSDocgen\n" );
    printf( "\n" );
    printf( "    Source:                %s\n", args->source );
    printf( "    Output:                %s\n", args->output );
    printf( "    Project name:          %s\n", args->projectName );
    printf( "    Project copyright:     %s\n", args->projectCopyright );
    printf( "    Project version:       %s\n", args->projectVersion );
    printf( "    Company name:          %s\n", args->companyName );
    printf( "    C++ support:           %s\n", ( args->cpp              ) ? "Yes"                  : "No" );
    printf( "    Project timezone:      %s\n", ( args->projectTimezone  ) ? args->projectTimezone  : "Not specified" );
    printf( "    Company URL:           %s\n", ( args->companyURL       ) ? args->companyURL       : "Not specified" );
    printf( "    Start page:            %s\n", ( args->pageHome         ) ? args->pageHome         : "Not specified" );
    printf( "    Exclude file:          %s\n", ( args->excludeFile      ) ? args->excludeFile      : "Not specified" );
    printf( "    Source root prefix:    %s\n", ( args->sourceRootPrefix ) ? args->sourceRootPrefix : "Not specified" );
    printf( "    Classes prefix:        %s\n", ( args->classesPrefix    ) ? args->classesPrefix    : "Not specified" );
    printf( "    Functions prefix:      %s\n", ( args->functionsPrefix  ) ? args->functionsPrefix  : "Not specified" );
    printf( "    Types prefix:          %s\n", ( args->typesPrefix      ) ? args->typesPrefix      : "Not specified" );
    printf( "    Additional pages:      %s", ( args->pages              ) ? ""                     : "None\n" );
    
    page = args->pages;
    
    while( page != NULL )
    {
        if( page != args->pages )
        {
            printf( "                           " );
        }
        
        printf( "%s (%s)\n", page->title, page->path );
        
        page = page->next;
    }
    
    printf( "\n" );
    
    printf( "Creating directories...\n" );
    
    if( XSDocgen_CreateDirectory( args->output, "XML" ) == false ) { printf( "Error: cannot create directory (XML - %s)\n", args->output ); return EXIT_FAILURE; }
    if( XSDocgen_CreateDirectory( args->output, "PHP" ) == false ) { printf( "Error: cannot create directory (PHP - %s)\n", args->output ); return EXIT_FAILURE; }
    if( XSDocgen_CreateDirectory( args->output, "CSS" ) == false ) { printf( "Error: cannot create directory (CSS - %s)\n", args->output ); return EXIT_FAILURE; }
    
    printf( "Generating XML files using HeaderDoc (this might take a while)...\n" );
    
    headerdoc = XSDocgen_CreateString( "headerdoc2html -u -X -H " );
    
    xmlDir    = XSDocgen_CreateString( args->output );
    xmlDir    = XSDocgen_AppendString( xmlDir, "/XML" );
    cssDir    = XSDocgen_CreateString( args->output );
    cssDir    = XSDocgen_AppendString( cssDir, "/CSS" );
    phpDir    = XSDocgen_CreateString( args->output );
    phpDir    = XSDocgen_AppendString( phpDir, "/PHP" );
    
    if( args->cpp )
    {
        headerdoc = XSDocgen_AppendString( headerdoc, "--enable-cpp" );
    }
    
    if( args->excludeFile )
    {
        headerdoc = XSDocgen_AppendString( headerdoc, "-e " );
        headerdoc = XSDocgen_AppendString( headerdoc, args->excludeFile );
        headerdoc = XSDocgen_AppendString( headerdoc, " " );
    }
    
    headerdoc = XSDocgen_AppendString( headerdoc, "-o " );
    headerdoc = XSDocgen_AppendString( headerdoc, xmlDir );
    headerdoc = XSDocgen_AppendString( headerdoc, " " );
    headerdoc = XSDocgen_AppendString( headerdoc, args->source );
    
    if( args->verbose == false )
    {
        headerdoc = XSDocgen_AppendString( headerdoc, "> /dev/null 2>&1" );
    }
    
    e = 0;//e = system( headerdoc );
    
    XSDocgen_FreeString( headerdoc );
    XSDocgen_FreeString( xmlDir );
    
    if( e != 0 ) { printf( "Error: %i\n", e ); return EXIT_FAILURE; }
    
    printf( "Generating index file...\n" );
    
    index = XSDocgen_CreateString
    (
        "<?php\n"
        "\n"
        "require_once dirname( __FILE__ ) . DIRECTORY_SEPARATOR . 'PHP' . DIRECTORY_SEPARATOR . 'Classes' . DIRECTORY_SEPARATOR . 'XS' . DIRECTORY_SEPARATOR . 'Docset.class.php';\n"
        "\n"
        "$DOC = new XS_Docset( dirname( __FILE__ ) . DIRECTORY_SEPARATOR . 'XML' );\n"
        "\n"
    );
    
    index = XSDocgen_AppendString( index, "$DOC->setProjectName( '" );
    index = XSDocgen_AppendString( index, args->projectName );
    index = XSDocgen_AppendString( index, "' );\n" );
    
    index = XSDocgen_AppendString( index, "$DOC->setProjectVersion( '" );
    index = XSDocgen_AppendString( index, args->projectVersion );
    index = XSDocgen_AppendString( index, "' );\n" );
    
    index = XSDocgen_AppendString( index, "$DOC->setCopyright( '" );
    index = XSDocgen_AppendString( index, args->projectCopyright );
    index = XSDocgen_AppendString( index, "' );\n" );
    
    index = XSDocgen_AppendString( index, "$DOC->setTimezone( '" );
    index = XSDocgen_AppendString( index, args->projectTimezone );
    index = XSDocgen_AppendString( index, "' );\n" );
    
    index = XSDocgen_AppendString( index, "$DOC->setCompanyName( '" );
    index = XSDocgen_AppendString( index, args->companyName );
    index = XSDocgen_AppendString( index, "' );\n" );
    
    index = XSDocgen_AppendString( index, "$DOC->setCompanyURL( '" );
    index = XSDocgen_AppendString( index, args->companyURL );
    index = XSDocgen_AppendString( index, "' );\n" );
    
    index = XSDocgen_AppendString( index, "$DOC->setSourceRootPrefix( '" );
    index = XSDocgen_AppendString( index, args->sourceRootPrefix );
    index = XSDocgen_AppendString( index, "' );\n" );
    
    index = XSDocgen_AppendString( index, "$DOC->setClassesPrefix( '" );
    index = XSDocgen_AppendString( index, args->classesPrefix );
    index = XSDocgen_AppendString( index, "' );\n" );
    
    index = XSDocgen_AppendString( index, "$DOC->setFunctionsPrefix( '" );
    index = XSDocgen_AppendString( index, args->functionsPrefix );
    index = XSDocgen_AppendString( index, "' );\n" );
    
    index = XSDocgen_AppendString( index, "$DOC->setTypesPrefix( '" );
    index = XSDocgen_AppendString( index, args->typesPrefix );
    index = XSDocgen_AppendString( index, "' );\n" );
    
    index = XSDocgen_AppendString( index, "$DOC->setHomeFile( '" );
    index = XSDocgen_AppendString( index, args->pageHome );
    index = XSDocgen_AppendString( index, "' );\n" );
    
    page = args->pages;
    
    while( page != NULL )
    {
        index = XSDocgen_AppendString( index, "$DOC->addPage( '" );
        index = XSDocgen_AppendString( index, page->path );
        index = XSDocgen_AppendString( index, "', '" );
        index = XSDocgen_AppendString( index, page->title );
        index = XSDocgen_AppendString( index, "' );\n" );
        
        page = page->next;
    }
    
    index = XSDocgen_AppendString
    (
        index,
        "\n"
        "?>\n"
        "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
        "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n"
        "<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\">\n"
        "<head>\n"
        "    <meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\" />\n"
        "    <title><?php print $DOC->getTitle(); ?></title>\n"
        "    <link rel=\"schema.dc\" href=\"http://purl.org/metadata/dublin_core_elements\" />\n"
        "    <link href=\"CSS/XSDoc.css\" type=\"text/css\" rel=\"stylesheet\" media=\"all\" charset=\"utf-8\" />\n"
        "    <meta http-equiv=\"content-language\" content=\"en\" />\n"
        "    <meta name=\"DC.Language\" scheme=\"NISOZ39.50\" content=\"en\" />\n"
        "    <meta name=\"rating\" content=\"General\" />\n"
        "    <meta name=\"robots\" content=\"all\" />\n"
        "    <meta name=\"generator\" content=\"XSDocgen\" />\n"
        "</head>\n"
        "<body>\n"
        "<?php\n"
        "\n"
        "print $DOC;\n"
        "\n"
        "?>\n"
        "</body>\n"
        "</html>\n"
    );
    
    indexFile = XSDocgen_CreateString( args->output );
    indexFile = XSDocgen_AppendString( indexFile, "/index.php" );
    
    fh = fopen( indexFile, "w" );
    
    if( fh == NULL )
    {
        XSDocgen_FreeString( indexFile );
        XSDocgen_FreeString( index );
        
        printf( "Error: cannot open index file (%s)", indexFile );
        
        return EXIT_FAILURE;
    }
    
    fwrite( index, 1, strlen( index ), fh );
    fclose( fh );
    
    XSDocgen_FreeString( indexFile );
    XSDocgen_FreeString( index );
    
    printf( "Copying resources...\n" );
    
    XSDocgen_CopyFiles( "/usr/local/share/XSDocgen/CSS", cssDir );
    XSDocgen_CopyFiles( "/usr/local/share/XSDocgen/PHP", phpDir );
    
    printf( "Done...\n" );
    
    return EXIT_SUCCESS;
}
