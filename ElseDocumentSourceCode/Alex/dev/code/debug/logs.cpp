#include "logs.h"
#include "files/xfs.h"


namespace debug{
	using namespace txt;
	stdoutStream stdoutStream::the_stream;
	//pTextStream stream;
	//pTextStream errstream;
	pTextStream stream(new txt::TabbedTextStream(txt::EchoStream(txt::FileStream("log/output.txt",false),stdoutStream::the_stream)),true);
	pTextStream errstream(new txt::TabbedTextStream(txt::EchoStream(txt::FileStream("log/errors.log",false),stdoutStream::the_stream)),true);
};