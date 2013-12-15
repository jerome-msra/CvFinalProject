#ifndef assert_h
#define assert_h

#if _MSC_VER > 1000

#ifdef _DEBUG
#define _ADEBUG
#endif

bool inline debug_breakpoint(){
	_asm{ int 3 };
	throw;
	return false;
};

#undef assert
#define assert(expression) {if(!(expression)){_asm{ int 3 };throw;}}

#ifdef _ADEBUG
#undef assert
#define assert(expression) {if(!(expression)){_asm{ int 3 }; throw;}}
#define iff(expression) ((expression)?(true):debug_breakpoint())
#else
#undef assert
#define assert(expression) ((void)0)
#define iff(expression) (expression)
#endif

#else
#define assert(expression) ((void)0)
#define iff(expression) (expression)
#endif

#endif