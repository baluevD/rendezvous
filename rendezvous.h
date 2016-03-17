#ifndef RENDEZVOUS_H
#define RENDEZVOUS_H
#include <thread>
#include <mutex>
#include <iostream>
#include <condition_variable>
using namespace std;

class RendezvousObject {
private:
	mutex lockMutex;
	condition_variable lock;
	int object;

public:
	void publish(int exchangeObject) {
		unique_lock<mutex> uniqueLock(lockMutex);
		while (!uniqueLock.owns_lock()) {
            lock.wait(uniqueLock);
        }
        object = exchangeObject;
        lock.notify_one();
        while (object != -1) {
            lock.wait(uniqueLock);
        }
	}

	int get() {
		int result;
		unique_lock<mutex> uniqueLock(lockMutex);
		while (object == -1) {
            lock.wait(uniqueLock);
        }
        result = object;
        object = -1;
        lock.notify_one();
        return result;
	}

	RendezvousObject() {
		object = -1;
	}
};


#endif //RENDEZVOUS_H

