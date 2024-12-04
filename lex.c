%{
#include <stdio.h>
#include <string.h>

int MAXTOKENLEN=50;

char tokenString[MAXTOKENLEN+1];
int linhas= 1;

%}

DIGITO [0-9]
LETRA [a-zA-Z]
OUTRO [^0-9a-zA-Z;/=\-"+""*""("")""{""[""}"">""<""!"",""\n""\t""\]"]
NEWLINE [\n] // quebra de linha
TAB [\t]+ // caractere de tabulação



%%
{DIGITO}+		            {printf("DIG\t\t%s\n", yytext);}
{LETRA}+	              { printf("ID\t\t%s\n", yytext);}
({LETRA}|{DIGITO})+     { printf("ERRO!\t\t%s\n", yytext); }
"/*"([^]|\+[^/])\+"*/"  { /* Ignorar comentários de bloco */ }
"//".*                  { /* Ignorar comentarios de linha */ }
"+"				              { printf("SUM\t\t%s\n", yytext); }
"-"				              { printf("SUB\t\t%s\n", yytext); }
"*"				              { printf("MULT\t\t%s\n", yytext); }
"/"				              { printf("BAR\t\t%s\n", yytext); }
">="                    { printf("MAIG\t\t%s\n", yytext); }
"<="                    { printf("MENIG\t\t%s\n", yytext); }
"=="                    { printf("IGUAL\t\t%s\n", yytext); }
"="				              { printf("ATR\t\t%s\n", yytext); }
">"                     { printf("MAIOR\t\t%s\n", yytext); }
"<"                     { printf("MENOR\t\t%s\n", yytext); }
"!="                    { printf("DIF\t\t%s\n", yytext); }
","                     { printf("VIRG\t\t%s\n", yytext); }
";"				              { printf("PV\t\t%s\n", yytext); }
"("				              { printf("LPAR\t\t%s\n", yytext); }
")"				              { printf("RPAR\t\t%s\n", yytext); }
"{"                     { printf("LCHA\t\t%s\n", yytext); }
"}"                     { printf("RCHA\t\t%s\n", yytext); }
"["                     { printf("LCO\t\t%s\n", yytext); }
"]"                     { printf("RCO\t\t%s\n", yytext); }
"int"                   { printf("INT\t\t%s\n", yytext); }
"else"                  { printf("ELSE\t\t%s\n", yytext); }
"return"                { printf("RETURN\t\t%s\n", yytext); }
"while"                 { printf("WHILE\t\t%s\n", yytext); }
"if"                    { printf("IF\t\t%s\n", yytext); }
"void"                  { printf("VOID\t\t%s\n", yytext); }
{TAB}                   {}
{NEWLINE}               { /* Simplesmente ignora e incrementa o contador de linha */ novalinha() }
[ ]*                    {/*espaco branco */}
{OUTRO}+		            {printf("ERRO!\t\t%s\n", yytext); }
%%

void novalinha(){
  linhas ++;
}

int main(int argc, char **argv) {
    if (argc <= 1) return 1;
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            fprintf(stderr, "Arquivo com erro: %s\n", argv[1]);
            return 1;
        }
        yyin = file;
    }

    yylex();
    fclose(file);
    return 0;
}
