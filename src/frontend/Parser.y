#define YYSTYLE AST::Node
%token IF ELSE WHILE BREAK FUNC STATE

%left GOPER(||)
%left GOPER(&&) 
%left GOPER(==) GOPER(!=)
%left GOPER(<=) GOPER(>=) GOPER(<) GOPER(>)
%left GOPER(+) GOPER(-)
%left GOPER(*) GOPER(/) GOPER(%)
%nonassoc UMINUS GOPER(!) 
%left GOPER([) GOPER(.) 
%nonassoc ELSE

%%
Program		:	StmtList
%%
