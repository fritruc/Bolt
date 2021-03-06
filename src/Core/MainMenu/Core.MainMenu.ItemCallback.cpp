#include "Core.MainMenu.ItemCallback.h"


#include "Core.Application.Application.h"
#include "Core.MainMenu.MainMenu.h"


#include <SFML/Graphics.hpp>


namespace nMainMenu {


cItemCallback::cItemCallback( cMainMenu* iMasterMenu, const std::string& iText, const sf::RectangleShape& iBox, std::function< void() > iFunction ) :
   tSuperClass( iMasterMenu, iText, iBox ),
    mFunction( iFunction )
{
}


void
cItemCallback::ClickAction()
{
    mFunction();
}


} // namespace nMainMenu

