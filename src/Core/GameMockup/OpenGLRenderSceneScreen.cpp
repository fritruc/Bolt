#include <GL/glew.h>
#include <gl/GLU.h>
#include "SFML/OpenGL.hpp"

#include "GameMockup/OpenGLRenderSceneScreen.h"
#include "GameMockup/GameApplication.h"

#include "GameMockup/GameApplication.h"


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cOpenGLRenderSceneScreen::~cOpenGLRenderSceneScreen()
{
}


cOpenGLRenderSceneScreen::cOpenGLRenderSceneScreen() :
    mConsoleWidget( 0 )
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cOpenGLRenderSceneScreen::Initialize()
{
    cGameApplication::App()->SetAppTitle( "OpenGL Render Scene" );
    auto window  = cGameApplication::App()->Window();
    mConsoleWidget = new  ::nGUI::cConsoleWidget();
    sf::Vector2f  availableGeometry = sf::Vector2f( float( window->getSize().x ),
                                                    float( window->getSize().y ) );
    double posRatio     = 3./5.;
    double sizeRatio    = 2./5.;
    sf::Vector2f  size      = sf::Vector2f( availableGeometry.x, availableGeometry.y * float(sizeRatio) );
    sf::Vector2f  position  = sf::Vector2f( 0, availableGeometry.y * float(posRatio));
    mConsoleWidget->SetSize( size );
    mConsoleWidget->SetPosition( position );
    //mConsoleWidget->ToggleVisibility();

    cGameApplication::App()->Window()->setKeyRepeatEnabled( true );

    // Init OpenGL stuff
    sf::ContextSettings settings = window->getSettings();
    ::nBoltScript::Env()->Print( "depth bits:" + std::to_string( settings.depthBits ) + "\n" );
    ::nBoltScript::Env()->Print( "stencil bits:" + std::to_string( settings.stencilBits ) + "\n" );
    ::nBoltScript::Env()->Print( "antialiasing level:" + std::to_string( settings.antialiasingLevel ) + "\n" );
    ::nBoltScript::Env()->Print( "version:" + std::to_string( settings.majorVersion ) + "\n" );
    window->setVerticalSyncEnabled(true);
    glViewport(0, 0, window->getSize().x, window->getSize().y );
    glEnable(GL_DEPTH_TEST);
    //glDepthRange( 1.f, 200.f );

    // Set color and depth clear value
    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 0.f);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    // Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double ratio = double( window->getSize().x ) / double( window->getSize().y );
    gluPerspective(50.f, ratio, 1.f, 500.f);

    int radius = 20;
    for( int i = 0; i < radius*2; ++i )
    {
        for( int j = 0; j < radius*2; ++j )
        {
            for( int k = 0; k < radius*2; ++k )
            {
                double x = i - radius;
                double y = j - radius;
                double z = k - radius;
                if( sqrt( double( x*x + y*y + z*z ) ) < double( radius ) )
                    mMap.SafeSetMaterial( i, j, k, 1 );
            }
        }
    }

}


void
cOpenGLRenderSceneScreen::Finalize()
{
    if( mConsoleWidget )
    {
        delete  mConsoleWidget;
        mConsoleWidget = 0;
    }
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------- Main Running functions
// -------------------------------------------------------------------------------------


void
cOpenGLRenderSceneScreen::Draw( sf::RenderTarget* iRenderTarget )
{
    auto window = ::cGameApplication::App()->Window();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef( 0.f, 0.f, -200.f );
    glRotatef( mClock.getElapsedTime().asSeconds() * 50.f, 0.f, 0.f, -1.f );
    glRotatef( mClock.getElapsedTime().asSeconds() * 20.f, 0.f, 1.f, 0.f );
    glRotatef( mClock.getElapsedTime().asSeconds() * 80.f, 1.f, 0.f, 0.f );
    glTranslatef( -20.f, -20.f, -20.f );

    glPushMatrix();
    mMap.DirectDraw();
    glPopMatrix();

    window->pushGLStates();

    mConsoleWidget->Draw( iRenderTarget );

    window->popGLStates();
}


void
cOpenGLRenderSceneScreen::Update( unsigned int iDeltaTime )
{
    mConsoleWidget->Update( iDeltaTime );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cOpenGLRenderSceneScreen::Resized( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::TextEntered( const sf::Event& iEvent )
{
    mConsoleWidget->TextEntered( iEvent );
}


void
cOpenGLRenderSceneScreen::KeyPressed( const sf::Event& iEvent )
{
    mConsoleWidget->KeyPressed( iEvent );
}


void
cOpenGLRenderSceneScreen::KeyReleased( const sf::Event& iEvent )
{
    mConsoleWidget->KeyReleased( iEvent );
}


void
cOpenGLRenderSceneScreen::MouseWheelMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::MouseWheelScrolled( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::MouseButtonPressed( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::MouseButtonReleased( const sf::Event& iEvent )
{
}


void
cOpenGLRenderSceneScreen::MouseMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::MouseEntered( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::MouseLeft( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::JoystickButtonPressed( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::JoystickButtonReleased( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::JoystickMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::JoystickConnected( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::JoystickDisconnected( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::TouchBegan( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::TouchMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::TouchEnded( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::SensorChanged( const sf::Event& iEvent )
{
    // Does nothing
}
