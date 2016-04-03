#ifndef INDCLUDED_SEQUENCE_PARENT_H
#define INDCLUDED_SEQUENCE_PARENT_H

namespace Sequence {
	class Child;
	
	class Parent {
	public:
		void update();

		static void create();
		static void destroy();
		static Parent* instance();

	private:
		Parent();
		~Parent();
		
		Child* mChild;

		static Parent* mInstance;

	};

}

#endif