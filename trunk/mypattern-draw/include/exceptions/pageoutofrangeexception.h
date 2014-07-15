#ifndef PAGEOUTOFRANGEEXCEPTION_H
#define PAGEOUTOFRANGEEXCEPTION_H

#include <exceptions/exception.h>

using namespace MyPattern::Exceptions;

namespace MyPattern
{
namespace Draw
{
namespace Exceptions
{

	class PageOutOfRangeException : public Exception
	{
    public:
        PageOutOfRangeException();
	};

}
}
}

#endif
