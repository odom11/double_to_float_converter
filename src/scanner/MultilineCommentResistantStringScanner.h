//
// Created by ich on 2/1/21.
//

#ifndef DOUBLE_TO_FLOAT_MULTILINECOMMENTRESISTANTSTRINGSCANNER_H
#define DOUBLE_TO_FLOAT_MULTILINECOMMENTRESISTANTSTRINGSCANNER_H

#include <memory>
#include "Scanner.h"
#include "StringScanner.h"


class MultilineCommentResistantStringScanner : public Scanner {
public:
    MultilineCommentResistantStringScanner(const std::string& filecontent);
    virtual ScannerOutput read() override;
private:
    const std::string multilineCommentText();
    const std::string noCommentText();
    bool isAtMultilineComment();
    void updateLinenumberAndColumnGlobals(const std::string& comment);

    const std::string filecontent;
    decltype(filecontent.begin()) it;
    std::unique_ptr<StringScanner> currentStringScanner;
    bool currentScannerIsDone;
};


#endif //DOUBLE_TO_FLOAT_MULTILINECOMMENTRESISTANTSTRINGSCANNER_H
