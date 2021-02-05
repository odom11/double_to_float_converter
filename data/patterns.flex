DIGIT   [0-9]
INTEGER  [1-9]{DIGIT}*|{DIGIT}
DOUBLE  {INTEGER}"."{DIGIT}*|"."{DIGIT}+
FLOAT   {DOUBLE}(f|F)
LETTER  [a-zA-Z]
MATH_FUNCTION   (sin|cos|atan2|sqrt|pow)
STRING          \"([^\"\n]|(\\\"))*\"
CHAR            '([^\\]|\\.|\\032|[^']*)?'
IDENTIFIER      [a-zA-Z_][a-zA-Z0-9_]*
COMMENT_LINE    "//"[^\n]*
COMMENT_END     "*/"
    int column_number = 1; int line_number = 1;
%%
{INTEGER}           {column_number += yyleng;return 1;}
{DOUBLE}            {column_number += yyleng;return 2;}
double              {column_number += yyleng;return 20;}
{FLOAT}             {column_number += yyleng;return 3;}
{MATH_FUNCTION}     {column_number += yyleng;return 4;}
{MATH_FUNCTION}f    {column_number += yyleng;return 41;}
float               {column_number += yyleng;return 5;}
;                   {column_number += yyleng;return 6;}
(\+|-|\*|\/|<<|=|!|<|>|\?|:|\||%|^)   {column_number += yyleng;return 7;}
{STRING}            {column_number += yyleng;return 9;}
{CHAR}              {column_number += yyleng;return 9;}
{IDENTIFIER}        {column_number += yyleng;return 10;}
<<EOF>>             {return 0;}
[ ]+                {column_number += yyleng;return 11;}
\t+                 {column_number += yyleng;return 11;}
\n                  {++line_number;column_number = 1;return 19;}
("::")              {column_number += yyleng;return 12;}
("."|->)            {column_number += yyleng;return 13;}
,                   {column_number += yyleng;return 14;}
(\[|\]|\(|\)|\{|\}) {column_number += yyleng;return 15;}
#                   {column_number += yyleng;return 16;}
{COMMENT_LINE}      {column_number += yyleng; return 17;}
(&|\\|~)              {column_number += yyleng; return 18;}
.                   {
                        printf("unidentified pattern '%s' in line %d column %d\n", yytext, line_number, column_number);
                        return -1;
                    }
%%