//
// Created by ich on 2/5/21.
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "ParserTest"

#include <boost/test/unit_test.hpp>
#include <boost/assert.hpp>
#include "../../src/scanner/StringScanner.h"
#include "../../src/scanner/MultilineCommentResistantStringScanner.h"
#include "../../src/parser/DoubleToFloatParser.h"

BOOST_AUTO_TEST_SUITE(ParserTestSuite)
BOOST_AUTO_TEST_CASE(DereferencingTest) {
    std::string teststring = "BBox.Lower";
    MultilineCommentResistantStringScanner scanner(teststring);
    DoubleToFloatParser parser(scanner);
    const std::stringbuf &outputBuffer = parser.parse();
    std::string parsed = outputBuffer.str();
    std::string expected = teststring;
    BOOST_CHECK_EQUAL(expected, parsed);
}

BOOST_AUTO_TEST_CASE(FloatTest) {
    std::string teststring = "double a = 2.0;";
    std::string expected = "float a = 2.0f;";
    MultilineCommentResistantStringScanner scanner(teststring);
    DoubleToFloatParser parser(scanner);
    const std::stringbuf &outputBuffer = parser.parse();
    std::string parsed = outputBuffer.str();
    BOOST_CHECK_EQUAL(expected, parsed);
}
BOOST_AUTO_TEST_SUITE_END()

