#ifndef ST_FRONTEND_LEXUTILS
#define ST_FRONTEND_LEXUTILS
#define GOPER(x) (#x[1] * 256 + #x[0])
inline int gOper(const char* x) {return x[1] * 256 + x[0];}
#endif
