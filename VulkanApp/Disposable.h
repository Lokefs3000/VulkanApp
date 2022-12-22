#pragma once

class Disposable {
private:
	bool isDisposed = false;
public:
	Disposable() {
		//disposables.push_back(*this);
	}

	virtual void Dispose() {
		if (isDisposed)
			return;

		isDisposed = true;
		//TODO remove from list!
	}

	bool IsDisposed() { return this->isDisposed; }
};