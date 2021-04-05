#pragma once
#include <vector>

/* Update method needs to be implemented by observers */
class Observer {
public:
    /* Invoked when Observable change*/
    virtual void update() = 0;
};
/* Derive from this class if you want to provide notifications */
class Observable {
private:
    /*Non owning pointers to observer objects*/
    std::vector<Observer*> observers;
public:
    /* Observers use this method to register for notification*/
    void addObserver(Observer* obs) {
        observers.push_back(obs);
    }
    /* Observers use this to cancel the registration
    !!!Before an observer is destroyed need to cancel the registration*/
    void removeObserver(Observer* obs) {
        observers.erase(std::remove(begin(observers), end(observers), obs),
            observers.end());
    }
protected:
    /* Invoked by the observable object in order to notify interested observer */
    void notify() {
        for (auto obs : observers) {
            obs->update();
        }
    }
};
