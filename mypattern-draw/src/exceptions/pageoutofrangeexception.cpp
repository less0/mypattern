#include <exceptions/pageoutofrangeexception.h>

namespace MyPattern
{
namespace Draw
{
namespace Exceptions
{
PageOutOfRangeException::PageOutOfRangeException()
{
	m_message = "Die Seite existiert nicht";
}
}
}
}
