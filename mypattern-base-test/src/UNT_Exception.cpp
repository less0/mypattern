#include "UnitTest++.h"
#include "mypattern-base.h"

using namespace MyPattern::Exceptions;

namespace
{
    TEST(CopyException)
    {
        MyPattern::Exceptions::Exception e("Dies ist eine Testnachricht");

        MyPattern::Exceptions::Exception e1(e);

        CHECK_EQUAL("Dies ist eine Testnachricht", e1.get_message());
    }

    TEST(AssignExeption)
    {
        MyPattern::Exceptions::Exception e("Hallo Welt!");
        MyPattern::Exceptions::Exception e1 = e;

        CHECK_EQUAL("Hallo Welt!", e1.get_message());
    }
}
