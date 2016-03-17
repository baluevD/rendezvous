#include "rendezvous.h"

RendezvousObject rendezvous;

void reader() {
	while(true) {	
		cout << "Reading" << "\n";
		rendezvous.get();
		cout << "Read" << "\n";
	}
}

void writer() {
	while(true) {
		cout << "Writing" << "\n";
		rendezvous.publish(10);
		cout << "Wrote" << "\n";
	}
}

int main() {
	thread writerThread = thread(writer);
	thread readerThread = thread(reader);
	writerThread.join();
	readerThread.join();
    return 0;
}
