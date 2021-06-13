#ifndef __STATER__
#define __STATER__

#include <Arduino.h>

class Stater {
  public:
    Stater() {};
    ~Stater() {};

    enum State : byte {
      UNINITIALIZED = 0,
      DEBUGGING = 1,
      CONNECTED = 2,
      DISCONNECTED = 3
    };

    Stater::State GetState() {
      return _state;
    }

    void SetState(Stater::State state) {
      _state = state;
      hasReadUpdate = false;
    }

    bool IsUpdated() {
      if (!hasReadUpdate) {
        hasReadUpdate = true;
        return true;
      }

      return false;
    }
  private:
    Stater::State _state = Stater::State::UNINITIALIZED;
    bool hasReadUpdate = false;
};

#endif // __STATER__
