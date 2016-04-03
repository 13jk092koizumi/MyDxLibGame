#ifndef INCLUDED_SEQUENCE_BASE_H
#define INCLUDED_SEQUENCE_BASE_H

namespace Sequence {
	
	class Base {
	public:
		virtual ~Base() {} //‰½‚à‚µ‚È‚¢
		//TODO:‹¤’Ê‚ÌŠÖ”‚ğ‘‚­
		virtual Base* update( Base* ) = 0; //•`‰æŠÖ”
	};

} //namespace Sequence

#endif