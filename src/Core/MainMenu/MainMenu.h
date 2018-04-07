#pragma once

#include <vector>
#include "Base/Drawable.h"


namespace nMainMenu {
class cMenuPage;

class cMainMenu :
    public ::nBase::cDrawable
{
public:
    cMainMenu();

public:
    void  AddPage( cMenuPage* iPage );
    void  CurrentPage( int iPage );
    void  MouseClick( int iX, int iY );

public:
    virtual  void Draw( sf::RenderTarget* iRenderTarget ) override;

protected:
    std::vector< cMenuPage* > mPages;
    int mCurrentPage;
};

} //nMainMenu
