#include "UnitTest++.h"
#include "xmlnode.h"
#include <memory>

using namespace MyPattern::Data;

namespace
{
    TEST(TestCreateXmlNode)
    {
        XmlNode node("myNode");
        CHECK_EQUAL("myNode", node.get_name());
    }
}
