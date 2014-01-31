#include "UnitTest++.h"
#include "xmlnode.h"
#include <memory>
#include <list>

using namespace MyPattern::Data;

namespace
{
    TEST(TestCreateXmlNode)
    {
        XmlNode node("myNode");
        CHECK_EQUAL("myNode", node.get_name());
    }

    TEST(TestCopyXmlNode)
    {
        XmlNode node("testNode");
        XmlNode copyNode(node);
        CHECK_EQUAL("testNode", copyNode.get_name());
    }

    TEST(TestParseRootNodeFromXml)
    {
        shared_ptr<XmlNode> rootNode = XmlNode::parse("<fooBar></fooBar>");
        CHECK_EQUAL("fooBar", rootNode->get_name());
    }

    TEST(TestParseEmptyNodeFromXml)
    {
        shared_ptr<XmlNode> rootNode = XmlNode::parse("<fooFoo />");
        CHECK_EQUAL("fooFoo", rootNode->get_name());
    }

    TEST(TestParseSubnodeFromXml)
    {
        shared_ptr<XmlNode> rootNode = XmlNode::parse("<fooBar><barFoo></barFoo></fooBar>");
        list<shared_ptr<XmlNode>> subnodes = rootNode->get_nodes();
        list<shared_ptr<XmlNode>>::iterator it = subnodes.begin();
        CHECK_EQUAL(false, it == subnodes.end());
        CHECK_EQUAL("barFoo", (*it)->get_name());
    }

    TEST(ParseMultipleSubnodes)
    {
        shared_ptr<XmlNode> rootNode = XmlNode::parse("<Foo><Bar1></Bar1><Bar2></Bar2><Bar3></Bar3></Foo>");
        list<shared_ptr<XmlNode>> subnodes = rootNode->get_nodes();
        CHECK_EQUAL(3, subnodes.size());

        list<shared_ptr<XmlNode>>::iterator it = subnodes.begin();

        CHECK_EQUAL("Bar1", (*it)->get_name());
        it++;
        CHECK_EQUAL("Bar2", (*it)->get_name());
        it++;
        CHECK_EQUAL("Bar3", (*it)->get_name());
    }

    TEST(ParseWithSpaces)
    {
        shared_ptr<XmlNode> rootNode = XmlNode::parse("<fooBar ></fooBar>");
        CHECK_EQUAL("fooBar", rootNode->get_name());
    }

    TEST(ParseSubnodeWithSpaces)
    {
        shared_ptr<XmlNode> rootNode = XmlNode::parse("<fooBar><barFoo ></barFoo></fooBar>");
        list<shared_ptr<XmlNode>> subnodes = rootNode->get_nodes();
        CHECK_EQUAL(1, subnodes.size());
        list<shared_ptr<XmlNode>>::iterator it = subnodes.begin();

        CHECK_EQUAL("barFoo", (*it)->get_name());
    }

    TEST(ParseMultipleSubnodesWithSpaces)
    {
        shared_ptr<XmlNode> rootNode = XmlNode::parse("<foo><bar1 ></bar1><bar2 ></bar2><bar3></bar3></foo>");
        list<shared_ptr<XmlNode>> subnodes = rootNode->get_nodes();
        CHECK_EQUAL(3, subnodes.size());
        list<shared_ptr<XmlNode>>::iterator it = subnodes.begin();

        CHECK_EQUAL("bar1", (*it)->get_name());
        it++;
        CHECK_EQUAL("bar2", (*it)->get_name());
        it++;
        CHECK_EQUAL("bar3", (*it)->get_name());


    }

    TEST(ParseMultipleLevelsOfSubnodes)
    {
        shared_ptr<XmlNode> rootNode = XmlNode::parse("<foo><bar><fooBar></fooBar></bar></foo>");
        list<shared_ptr<XmlNode>> subnodes = rootNode->get_nodes();
        CHECK_EQUAL(1, subnodes.size());
        list<shared_ptr<XmlNode>>::iterator it = subnodes.begin();
        CHECK_EQUAL("bar", (*it)->get_name());
        list<shared_ptr<XmlNode>> subSubnodes = (*it)->get_nodes();
        CHECK_EQUAL(1, subSubnodes.size());
        list<shared_ptr<XmlNode>>::iterator it2 = subSubnodes.begin();
        CHECK_EQUAL("fooBar", (*it2)->get_name());
    }

    TEST(ParseMultipleLevelsOfSubnodesWithSameName)
    {
        //UNITTEST_TIME_CONSTRAINT(20);

        shared_ptr<XmlNode> rootNode = XmlNode::parse("<foo><bar><bar></bar></bar></foo>");
        list<shared_ptr<XmlNode>> subnodes = rootNode->get_nodes();
        CHECK_EQUAL(1, subnodes.size());
        list<shared_ptr<XmlNode>>::iterator it = subnodes.begin();
        CHECK_EQUAL("bar", (*it)->get_name());
        list<shared_ptr<XmlNode>> subSubnodes = (*it)->get_nodes();
        CHECK_EQUAL(1, subSubnodes.size());
        list<shared_ptr<XmlNode>>::iterator it2 = subSubnodes.begin();
        CHECK_EQUAL("bar", (*it2)->get_name());
    }
}
