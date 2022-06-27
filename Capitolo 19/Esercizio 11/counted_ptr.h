#pragma once
template<class T>
class counted_ptr
{
	int* _users;
	T* _p;
public:
	counted_ptr(const T& val = T()) : _users{ new int{0} }, _p{ new T{val} } {
		//if (_p) ++*_users;
	}
	~counted_ptr() {
		// se mi vogliono distruggere distruggo _p se non utilizzato
		// mi distruggo _users perchè non esito più e devo evitare memory leak
		if (*_users == 0) {
			if (_p) delete _p;
		}
		//else --*_users;
		if (_users) delete _users;
	}
	T& operator->() {
		return *_p;
	}
	T& operator*() {
		return *_p;
	}
	int users() const { return *_users; }
	T* release() {
		// condiviso il mio puntatore se punta a qualcosa altrimenti ritorno 0
		if (_p) ++* _users;
		return _p;
	}
	void destroy(const T* p) {
		// abbandono del mio puntatore
		if (!p) return; // puntatore nullo
		if (p == _p) {
			// il puntatore è il mio
			if (*_users > 0)--* _users; // se è condiviso togli un utente
		}
	}
};
