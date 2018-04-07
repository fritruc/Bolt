#pragma once

#include <unordered_map>
#include <SFML/Window.hpp>

#include "tinyxml2.h"

namespace nShortcuts {

class cShortcuts
{
public:
    // Construction/Destruction
    virtual  ~cShortcuts();
    cShortcuts();

public:
    static cShortcuts* Instance();

public:
    // Init/Finalize
    void Initialize();
    void Finalize();

public:
    // Shortcut access
    sf::Keyboard::Key GetKeyForAction( const std::string& iAction );
    const std::string& GetActionForKey( sf::Keyboard::Key iKey );

private:
    // Input/Output
    virtual  void SaveXML();
    virtual  void LoadXML();

public:
    std::unordered_map < sf::Keyboard::Key, std::string > mShortcuts;
};

} //nShortcuts
