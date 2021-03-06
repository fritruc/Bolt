#include "Core.Volumetric.SparseOctree.RawData.h"

#include "Core.Benchmark.h"
#include "Core.BoltScript.BoltScriptEnvironment.h"
#include "Core.MainMenu.MainMenu.h"
#include "Core.MainMenu.MenuPage.h"
#include "Core.MainMenu.ItemPageSwaper.h"
#include "Core.MainMenu.ItemCallback.h"
#include "Core.Volumetric.Static.Data.h"
#include "GameMockup.Application.GameApplication.h"
#include "GameMockup.Screen.GameScreen.h"
#include "GameMockup.Screen.ConsoleScreen.h"


#include <SFML/Graphics.hpp>
#include <cpython/Python.h>


#include <chrono>


int
BoltMain( int argc, char *argv[] )
{

    //nBenchmark::RunVectorVsHMapvsMapBenchmark();
    //nBenchmark::EntityStressTest();

    srand( unsigned int( time( NULL ) ) );

    ::nApplication::cGameApplication* app = ::nApplication::cGameApplication::App();
    app->Initialize();
	app->LoadProject( "E:/ProjectTest/ProjectTest.proj" );


    ::nBoltScript::Env()->RegisterFunction( "exit", [ = ]( void ){ app->Window()->close(); } );
#ifdef  CONSOLEDEBUG

    ::nApplication::cGameApplication::App()->PushScreen( new ::nScreen::cConsoleScreen() );

#endif //  CONSOLEDEBUG

    // Small Volumetric benchmark
    ::nBoltScript::Env()->Print( ">>> Size of Volumetric Atomic Data: " + std::to_string( sizeof( ::nVolumetric::nStatic::cData ) ) + "Bytes\n" );

    // PYTHON TEST
    wchar_t *program = Py_DecodeLocale( argv[ 0 ], NULL );
    if( program == NULL )
    {
        fprintf( stderr, "Fatal error: cannot decode argv[0]\n" );
        exit( 1 );
    }

    PyImport_AppendInittab( "PyBolt", &::nBoltScript::PyInit_PyBolt );

    Py_SetProgramName( program );
    Py_Initialize();
    PyRun_SimpleString( "import PyBolt\n" );
    PyRun_SimpleString( "PyBolt.PyBoltPrint(\"\")\n" );
    PyRun_SimpleString( "class Monitor:\n"
                        "    def __init__(self):\n"
                        "      self\n"
                        "\n"
                        "    def write(self, s):\n"
                        "      if s.rstrip() != \"\":\n"
                        "        PyBolt.PyBoltPrint(s)\n"
                        "\n" );
    PyRun_SimpleString( "monitorQ = Monitor()\n" );
    PyRun_SimpleString( "print(\"Redirecting output...\")\n"
                        "import sys\n"
                        "sys.stdout = monitorQ\n"
                        "sys.stderr = monitorQ\n" );

    PyRun_SimpleString( "print(\"Python says i love Bolt\")\n" );
    PyRun_SimpleString( "print(\"Python says i can't wait to see your little voxels\")\n" );


    printf( "\n" );

    static auto gClock = std::chrono::high_resolution_clock::now();

    ////////////////////////////////////////////////////////////

    sf::RenderWindow* window = ::nApplication::cGameApplication::App()->Window();
    sf::Vector2u size = window->getSize();

    sf::Clock clock;
    sf::Time frameTime;
    sf::Event event;

    double          FPSAverage = 0.0;
    unsigned int    fpscounter = 0;

    // Drawing entityMap
    //sf::Vector2f position;
    //sf::RectangleShape square;
    //square.setSize( sf::Vector2f( 32, 32 ) );
    //square.setFillColor( sf::Color( 0, 0, 0, 0 ) );
    //square.setOutlineColor( sf::Color( 255, 0, 0, 120 ) );
    //square.setOutlineThickness( 1.0F );
    // /Drawing entityMap


    while( window->isOpen() )
    {
        frameTime = clock.restart();

        while( window->pollEvent( event ) )
            app->HandleEvents( event );

        app->Update( unsigned int( frameTime.asMicroseconds() ) );
        window->clear( sf::Color( 200, 200, 200 ) );
        app->Draw( window );


        // PERF TESTS============================================================

        // Draw entityMapGrid
        //for( int x = 0; x < 32; ++x )
        //{
        //    for( int y = 0; y < 32; ++y )
        //    {
        //        position.x = x * 32;
        //        position.y = y * 32;
        //        square.setPosition( position );

        //        window->draw( square );
        //    }
        //}
        // /Drawing entityMap

        if( 1 )
        {
            //sf::RectangleShape rect( sf::Vector2f( 10.0F, 10.0F ) );
            //rect.setPosition( sf::Vector2f( sf::Mouse::getPosition( *window ) ) );
            //rect.setFillColor( sf::Color( 10, 10, 255, 255 ) );
            //rect.setSize( sf::Vector2f( 50, 50 ) );
            //window->draw( rect );

            //nBenchmark::DrawStressTest( app->Window() );

            float fps = 1 / frameTime.asSeconds();
            FPSAverage += fps;

            if( fpscounter >= 1000 )
            {
                FPSAverage /= fpscounter;
                std::cout << std::to_string( FPSAverage ) << "\n";
                std::cout << "==============" << std::to_string( ::nApplication::cGameApplication::App()->CurrentScreen()->World()->EntityCount() ) << "\n";
                fpscounter = 0;
                FPSAverage = 0.0;
            }
            else
            {
                ++fpscounter;
            }
        }
        // PERF TESTS============================================================

        window->display();
    }

    app->Finalize();

    if( Py_FinalizeEx() < 0 )
    {
        exit( 120 );
    }
    PyMem_RawFree( program );

    return  0;
}

int
main( int argc, char *argv[] )
{
    return  BoltMain( argc, argv );
}
