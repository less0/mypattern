#include "UnitTest++.h"
#include "mypattern-base.h"

using namespace MyPattern::Exceptions;

namespace
{
    TEST(CopyException)
    {
        Exception e("Dies ist eine Testnachricht");

        Exception e1(e);

        CHECK_EQUAL("Dies ist eine Testnachricht", e1.get_message());
    }

    TEST(AssignExeption)
    {
        Exception e("Hallo Welt!");
        Exception e1("Test");
        
        e1=e;

        CHECK_EQUAL("Hallo Welt!", e1.get_message());
    }
}
