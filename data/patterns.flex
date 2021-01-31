DIGIT   [0-9]
INTEGER  [1-9]{DIGIT}*
DOUBLE  {INTEGER}"."{DIGIT}*|"."{DIGIT}*
FLOAT   {DOUBLE}(f|F)
LETTER  [a-zA-Z]
MATH_FUNCTION   (sin|cos|atan2|sqrt|pow)
DUCK_BILL       <[^>]*>
STRING          \"[^\"]*\"
IDENTIFIER      [a-zA-Z_][a-zA-Z0-9_]*
BLANK           [ \n]+
%%
{INTEGER}           {return 1;}
{DOUBLE}            {return 2;}
{FLOAT}             {return 3;}
{MATH_FUNCTION}     {return 4;}
{MATH_FUNCTION}f    {return 41;}
float               {return 5;}
;                   {return 6;}
(\+|-|\*|\/|<<)     {return 7;}
{DUCK_BILL}         {return 8;}
{STRING}            {return 9;}
{IDENTIFIER}        {return 10;}
<<EOF>> {
            printf("reached end of file\n"); return 0;
        }
{BLANK}             {return 11;}
{IDENTIFIER}?"::"{IDENTIFIER}   {return 12;}
("."|->)            {return 13;}
,                   {return 14;}
(\[|\]|\(|\)|\{|\}) {return 15;}
.                   {return -1;}
%%