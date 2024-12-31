%{
#include<stdio.h>
int x=0,y=0,z=0,p=0,a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0,i=0,j=0,k=0,X=0;
%}
%%
auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while printf("\n %s is a Keyword",yytext);
[0-9]+ printf("\n %s is a Constant",yytext);
[+] {a++;x=1;}
[-] {b++;y=1;}
[*] {c++;z=1;}
[/] {d++;p=1;}
[%] {e++;f=1;}
[&] {f++;g=1;}
[|] {g++;h=1;}
[!] {h++;i=1;}
[=] {i++;j=1;}
[<] {j++;k=1;}
[>] {k++;e=1;}
[(] {X++; printf("\n ( is a Left Parenthesis");}
[)] {X++; printf("\n ) is a Right Parenthesis");}
[{] {X++; printf("\n { is a Left Curly Brace");}
[}] {X++; printf("\n } is a Right Curly Brace");}
[\[] {X++; printf("\n [ is a Left Square Bracket");}
[\]] {X++; printf("\n ] is a Right Square Bracket");}
[a-zA-Z_][a-zA-Z0-9_]* printf("\n %s is an Identifier",yytext);
[(){}();,.=*&^%$#@!'":|\\/?><] {X++;}

%%
int main(void) {
    yyin = fopen("file2.txt", "r");
    if (yyin == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    yylex();
    printf("\nOperators used:\n");
    if (x == 1)
        printf("+\t");
    if (y == 1)
        printf("-\t");
    if (z == 1)
        printf("*\t");
    if (p == 1)
        printf("/\t");
    if (f == 1)
        printf("%%\t");
    if (g == 1)
        printf("&\t");
    if (h == 1)
        printf("|\t");
    if (i == 1)
        printf("!\t");
    if (j == 1)
        printf("=\t");
    if (k == 1)
        printf("< >\t");
    printf("\n");
    fclose(yyin);
    return 0;
}

int yywrap() {
    return 1;
}
