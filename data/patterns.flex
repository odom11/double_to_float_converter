DIGIT   [0-9]
INTEGER  [1-9]{DIGIT}*
DOUBLE  {INTEGER}"."{DIGIT}*
FLOAT   {DOUBLE}(f|F)
LETTER  [a-zA-Z]
MATH_FUNCTION   (sin|cos|atan2|sqrt|pow)
%%
{INTEGER}           {return 1;}
{DOUBLE}            {return 2;}
{FLOAT}             {return 3;}
{MATH_FUNCTION}     {return 4;}
float               {return 5;}
;                   {return 6;}
(\+|-|\*|\/|<<)     {return 7;}
<<EOF>> {
            printf("reached end of file\n"); return 0;
        }
.           {return -1;}
%%