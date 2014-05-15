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
    bool                      exit;
    int                       e;
    XSDocgen_Arguments      * args;
    char                    * headerdoc;
    char                    * xmlDir;
    char                    * cssDir;
    char                    * phpDir;
    char                    * index;
    char                    * indexFile;
    FILE                    * fh;
    XSDocgen_Page           * page;
    XSDocgen_HTMLHeaderLine * headerLine;
    
    exit = false;
    args = XSDocgen_ParseArguments( argc, argv );
    
    xmlDir      = NULL;
    cssDir      = NULL;
    phpDir      = NULL;
    headerdoc   = NULL;
    index       = NULL;
    indexFile   = NULL;
    fh          = NULL;
    
    if( args == NULL || args->help )
    {
        XSDocgen_ShowHelp();
        
        goto success;
    }
    else if( args->version )
    {
        XSDocgen_ShowVersion();
        
        goto success;
    }
    
    if( args->source           == NULL ) { printf( "[ XSDocgen ]> Error - Missing argument: --source [PATH]\n" );             exit = true; }
    if( args->output           == NULL ) { printf( "[ XSDocgen ]> Error - Missing argument: --output [PATH]\n" );             exit = true; }
    if( args->projectName      == NULL ) { printf( "[ XSDocgen ]> Error - Missing argument: --project-name [VALUE]\n" );      exit = true; }
    if( args->projectCopyright == NULL ) { printf( "[ XSDocgen ]> Error - Missing argument: --project-copyright [VALUE]\n" ); exit = true; }
    if( args->projectVersion   == NULL ) { printf( "[ XSDocgen ]> Error - Missing argument: --project-version [VALUE]\n" );   exit = true; }
    if( args->companyName      == NULL ) { printf( "[ XSDocgen ]> Error - Missing argument: --company-name [VALUE]\n" );      exit = true; }
    
    if( args->source      != NULL && XSDocgen_DirectoryExists( args->source ) == false ) { printf( "[ XSDocgen ]> Error - source directory does not exist (%s)\n", args->source  ); exit = true; }
    if( args->output      != NULL && XSDocgen_DirectoryExists( args->output ) == false ) { printf( "[ XSDocgen ]> Error - output directory does not exist (%s)\n", args->output  ); exit = true; }
    if( args->excludeFile != NULL && XSDocgen_FileExists( args->excludeFile ) == false ) { printf( "[ XSDocgen ]> Error - exclude file does not exist (%s)\n", args->excludeFile ); exit = true; }
    
    if( exit )
    {
        goto failure;
    }
    
    printf( "[ XSDocgen ]> Starting:\n" );
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
    
    xmlDir    = XSDocgen_CreateString( args->output );
    xmlDir    = XSDocgen_AppendString( xmlDir, "/XML" );
    cssDir    = XSDocgen_CreateString( args->output );
    cssDir    = XSDocgen_AppendString( cssDir, "/CSS" );
    phpDir    = XSDocgen_CreateString( args->output );
    phpDir    = XSDocgen_AppendString( phpDir, "/PHP" );
    
    if( args->clear )
    {
        printf( "[ XSDocgen ]> Clearing previous output\n" );
        
        if( XSDocgen_ClearFiles( xmlDir ) == false ) { printf( "[ XSDocgen ]> Error - Failed to clear the XML resources\n" ); goto failure; }
        if( XSDocgen_ClearFiles( phpDir ) == false ) { printf( "[ XSDocgen ]> Error - Failed to clear the PHP resources\n" ); goto failure; }
        if( XSDocgen_ClearFiles( cssDir ) == false ) { printf( "[ XSDocgen ]> Error - Failed to clear the CSS resources\n" ); goto failure; }
    }
    
    printf( "[ XSDocgen ]> Creating directories\n" );
    
    if( XSDocgen_CreateDirectory( args->output, "XML" ) == false ) { printf( "[ XSDocgen ]> Error - cannot create directory (XML - %s)\n", args->output ); goto failure; }
    if( XSDocgen_CreateDirectory( args->output, "PHP" ) == false ) { printf( "[ XSDocgen ]> Error - cannot create directory (PHP - %s)\n", args->output ); goto failure; }
    if( XSDocgen_CreateDirectory( args->output, "CSS" ) == false ) { printf( "[ XSDocgen ]> Error - cannot create directory (CSS - %s)\n", args->output ); goto failure; }
    
    printf( "[ XSDocgen ]> Generating XML files using HeaderDoc. This might take a while...\n" );
    
    headerdoc = XSDocgen_CreateString( "headerdoc2html -u -X -H -c /usr/local/share/XSDocgen/headerdoc.config " );
    
    if( args->undocumented )
    {
        headerdoc = XSDocgen_AppendString( headerdoc, "-E " );
    }
    
    if( args->cpp )
    {
        headerdoc = XSDocgen_AppendString( headerdoc, "--enable-cpp " );
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
    
    e = system( headerdoc );
    
    if( e != 0 ) { printf( "[ XSDocgen ]> Error - HeaderDoc returned %i\n", e ); goto failure; }
    
    printf( "[ XSDocgen ]> Generating index file\n" );
    
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
        page  = page->next;
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
        "    <!--\n"
        "    \n"
        "    ##################################################\n"
        "    #                                                #\n"
        "    #       Generated with XSDocgen by XS-Labs       #\n"
        "    #                 www.xs-labs.com                #\n"
        "    #                                                #\n"
        "    ##################################################\n"
        "    \n"
        "    -->\n"
        "    <meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\" />\n"
        "    <title><?php print $DOC->getTitle(); ?></title>\n"
        "    <link rel=\"schema.dc\" href=\"http://purl.org/metadata/dublin_core_elements\" />\n"
        "    <link href=\"CSS/XSDoc.css\" type=\"text/css\" rel=\"stylesheet\" media=\"all\" charset=\"utf-8\" />\n"
        "    <meta http-equiv=\"content-language\" content=\"en\" />\n"
        "    <meta name=\"DC.Language\" scheme=\"NISOZ39.50\" content=\"en\" />\n"
        "    <meta name=\"rating\" content=\"General\" />\n"
        "    <meta name=\"robots\" content=\"all\" />\n"
        "    <meta name=\"generator\" content=\"XSDocgen\" />\n"
    );
    
    if( args->analyticsCode && args->analyticsDomain && strlen( args->analyticsCode ) && strlen( args->analyticsDomain ) )
    {
        index = XSDocgen_AppendString
        (
            index,
            "    <script type=\"text/javascript\">\n"
            "        // <![CDATA[\n"
            "        \n"
            "        (\n"
            "            function( i, s, o, g, r, a, m )\n"
            "            {\n"
            "                i[ 'GoogleAnalyticsObject' ] = r;\n"
            "                i[ r ]                       = i[ r ] || function()\n"
            "                {\n"
            "                    ( i[ r ].q = i[ r ].q || [] ).push( arguments )\n"
            "                },\n"
            "                i[ r ].l = 1 * new Date();\n"
            "                a        = s.createElement( o ),\n"
            "                m        = s.getElementsByTagName( o )[ 0 ];\n"
            "                a.async  = 1;\n"
            "                a.src    = g;\n"
            "            \n"
            "                m.parentNode.insertBefore( a, m )\n"
            "            }\n"
            "        )\n"
            "        (\n"
            "            window,\n"
            "            document,\n"
            "            'script',\n"
            "            '//www.google-analytics.com/analytics.js',\n"
            "            'ga'\n"
            "        );\n"
            "        \n"
            "        ga( 'create', '"
        );
        index = XSDocgen_AppendString
        (
            index,
            args->analyticsCode
        );
        index = XSDocgen_AppendString
        (
            index,
            "', '"
        );
        index = XSDocgen_AppendString
        (
            index,
            args->analyticsDomain
        );
        index = XSDocgen_AppendString
        (
            index,
            "' );\n"
            "        ga( 'send', 'pageview' );\n"
            "        \n"
            "        // ]]>\n"
            "    </script>\n"
        );
    }
    
    headerLine = args->headerLines;
    
    while( headerLine != NULL )
    {
        index      = XSDocgen_AppendString( index, "    " );
        index      = XSDocgen_AppendString( index, headerLine->html );
        index      = XSDocgen_AppendString( index, "\n" );
        headerLine = headerLine->next;
    }
    
    index = XSDocgen_AppendString
    (
        index,
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
        printf( "[ XSDocgen ]> Error - cannot open index file (%s)", indexFile );
        
        goto failure;
    }
    
    fwrite( index, 1, strlen( index ), fh );
    
    printf( "[ XSDocgen ]> Copying resources\n" );
    
    if( XSDocgen_CopyFiles( "/usr/local/share/XSDocgen/CSS", cssDir ) == false ) { printf( "Error copying CSS resources\n" ); goto failure; };
    if( XSDocgen_CopyFiles( "/usr/local/share/XSDocgen/PHP", phpDir ) == false ) { printf( "Error copying PHP resources\n" ); goto failure; };
    
    printf( "[ XSDocgen ]> Documentation was successfully generated\n" );
    
    success:
    
    XSDocgen_FreeArguments( args );
    XSDocgen_FreeString( xmlDir );
    XSDocgen_FreeString( phpDir );
    XSDocgen_FreeString( cssDir );
    XSDocgen_FreeString( headerdoc );
    XSDocgen_FreeString( indexFile );
    XSDocgen_FreeString( index );
    
    if( fh != NULL ) { fclose( fh ); }
    
    return EXIT_SUCCESS;
    
    failure:
    
    XSDocgen_FreeArguments( args );
    XSDocgen_FreeString( xmlDir );
    XSDocgen_FreeString( phpDir );
    XSDocgen_FreeString( cssDir );
    XSDocgen_FreeString( headerdoc );
    XSDocgen_FreeString( indexFile );
    XSDocgen_FreeString( index );
    
    if( fh != NULL ) { fclose( fh ); }
    
    return EXIT_FAILURE;
}
