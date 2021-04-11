/*
 * observer1.h
 *
 *  Created on: Jan 17, 2019
 *      Author: disba1ancer
 */

#ifndef OBSERVER1_H_
#define OBSERVER1_H_

#include <set>

namespace util {

template <typename call>
struct IConnection;

template <typename call>
struct IUnlinker {
	virtual void unlink(IConnection<call>*) = 0;
};

template <typename ... Args>
struct IConnection<void(Args...)> {
	virtual void call(Args...args) = 0;
	virtual void connect(IUnlinker<void(Args...)>*) = 0;
	virtual void disconnect() = 0;
};

template <typename Call, typename Handler>
class Connection;

template <typename Handler, typename ... Args>
class Connection<void(Args ...), Handler> : public IConnection<void(Args ...)>{
	Handler handler;
	IUnlinker<void(Args...)>* unlinker;
public:
	Connection(Handler handler) : handler(handler), unlinker(nullptr) {}
	~Connection() {
		reset();
	}

	virtual void call(Args...args) override {
		if (unlinker) handler(args...);
	}

	virtual void connect(IUnlinker<void(Args...)>* unlinker) override {
		if (this->unlinker) {
			unlinker->unlink(this);
			unlinker = nullptr;
		}
		this->unlinker = unlinker;
	}

	virtual void disconnect() override {
		unlinker = nullptr;
	}

	void reset() {
		if (unlinker) {
			unlinker->unlink(this);
		}
	}
};

template <typename call>
class ObserverStore;

template <typename ... Args>
class ObserverStore<void(Args...)> : public IUnlinker<void(Args...)> {
	std::set<IConnection<void(Args...)>*> connections;
public:
	void addConnection(IConnection<void(Args...)>* connection) {
		connection->connect(this);
		connections.insert(connection);
	}

	virtual void unlink(IConnection<void(Args...)>* connection) override {
		auto con_it = connections.find(connection);
		if (con_it != connections.end()) {
			(*con_it)->disconnect();
		}
	}

	void operator() (Args...args) {
		for (auto connect : connections) {
			connect->call(args...);
		}
	}

	void reset() {
		for (auto connect : connections) {
			connect->disconnect();
		}
		connections.clear();
	}

	~ObserverStore() {
		reset();
	}
};

}

#endif /* OBSERVER1_H_ */
