#pragma once

#include <string>
#include <functional>


namespace  nBoltScript
{


class  cBoltScriptEnvironment
{
private:
    typedef  void ( *tOutputRedirectionFunction )( const  std::string& );

public:
    // Construction/Destruction
    ~cBoltScriptEnvironment();
    cBoltScriptEnvironment( std::function<void( const  std::string& )> iOutputRedirectionFunction );
    cBoltScriptEnvironment( const  cBoltScriptEnvironment& ) = delete; // Not Allowed

public:
    // Public Processing Interface
    void  ProcessRawString( const  std::string&  iStr );

private:
    // Data Members
    std::function<void( const  std::string& )>  mOutputRedirectionFunction;

};


}  // namespace  nBoltScript
