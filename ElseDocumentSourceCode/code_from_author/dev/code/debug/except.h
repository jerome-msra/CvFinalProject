#ifndef debug_except_h
#define debug_except_h

#include <exception>
#include <string>

class debug_exception : public std::exception{
private:
	//const char * pmsg;
	std::string smsg;
public:
	debug_exception():smsg("unspecified"){
	};
	debug_exception(const char * msg):smsg(msg){
	};
	debug_exception(const std::string & msg):smsg(msg){
	};
	debug_exception(const debug_exception & x):smsg(x.smsg){
	};
	virtual ~debug_exception() throw (){};
public:
	virtual const char *what( ) const throw( ){
		return smsg.c_str();
	};
};

#endif