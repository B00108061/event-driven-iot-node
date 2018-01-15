#include <iostream>

using namespace std;

class Manager
{
  class State *current;
  public:
    Manager();
    void setCurrent(State *s)
    {
        current = s;
    }
    void idle();
    void sensing();
    void processing();
};

class State
{
  public:
      virtual void idle(Manager *m)
    {
        cout << "   already Idle\n";
    }

    virtual void sensing(Manager *m)
    {
        cout << "   already Sensing\n";
    }

     virtual void processing(Manager *m)
    {
        cout << "   already processing\n";
    }
};

void Manager::idle()
{
  current->idle(this);
}

void Manager::sensing()
{
  current->sensing(this);
}


void Manager::processing()
{
  current->processing(this);
}

class IDLE: public State
{
  public:
    IDLE()
    {
        cout << "   IDLE-ctor ";
    };
    ~IDLE()
    {
        cout << "   dtor-IDLE\n";
    };
    void sensing(Manager *m);

};

class PROCESSING: public State
{
  public:
    PROCESSING()
    {
        cout << "   PROCESSING-ctor ";
    };
    ~PROCESSING()
    {
        cout << "   dtor-PROCESSING\n";
    };
    void idle(Manager *m);
/*{
        cout << "   going from PROCESSING to IDLE";
        m->setCurrent(new IDLE());
        delete this;
    }*/
};

class SENSING: public State
{
  public:
    SENSING()
    {
        cout << "   SENSING-ctor ";
    };
    ~SENSING()
    {
        cout << "   dtor-SENSING\n";
    };
    void processing(Manager *m);
    /*{
        cout << "  going from SENSING to PROCESSING";
      m->setCurrent(new PROCESSING());
        delete this;
    }*/
};

 void IDLE::sensing(Manager *m)
{
        cout << "   going from IDLE to SENSING";
         m->setCurrent(new SENSING());
        delete this;
}

/*void IDLE::sensing(Manager *m)
{
  cout << "   going from IDLE to SENSING";
  m->setCurrent(new SENSING());
  delete this;
}*/

void SENSING::processing(Manager *m)
{
  cout << "   going from SENSING to PROCESSING";
  m->setCurrent(new PROCESSING());
  delete this;
}

void PROCESSING::idle(Manager *m)
{
  cout << "   going from PROCESSING to IDLE";
  m->setCurrent(new IDLE());
  delete this;
}

Manager::Manager()
{
  current = new IDLE();
  cout << '\n';
}

int main()
{
  void(Manager:: *ptrs[])() =
  {
    Manager::idle, Manager::sensing, Manager::processing
  };
  Manager fsm;
  int num;
  while (1)
  {
    cout << "Enter 0/1/2: ";
    cin >> num;
    (fsm.*ptrs[num])();
  }
}
