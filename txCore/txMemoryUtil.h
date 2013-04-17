#pragma once
namespace txMemoryUtil
{
	template<class T>
	void txDelete(T* p) {
		if (p!=NULL) {
			delete p;
			p = NULL;
		}
	};

	template<class T>
	void txDeleteArray(T* p) {
		if (p!=NULL) {
			delete [] p;
			p = NULL;
		}
	}

};

