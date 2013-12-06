#ifndef ST_FRONTEND_LEXUTILS
#define ST_FRONTEND_LEXUTILS
#define SG_OP(x) (#x[0])
#define DB_OP(x) (#x[0] * 256 + #x[1])
inline int sg_op(char* x) {return x[0];}
inline int db_op(char* x) {return x[0] * 256 + x[1];}
#endif
