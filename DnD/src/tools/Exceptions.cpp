#include "Exceptions.h"

GuiException::GuiException(const std::string& reason)
:myMessage(reason)
{
}

GuiException::~GuiException(void) throw()
{
}

const char* GuiException::what() const throw()
{
    return myMessage.c_str();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

IllegalArgument::IllegalArgument(const std::string& reason)
{
	myMessage = reason;
}
