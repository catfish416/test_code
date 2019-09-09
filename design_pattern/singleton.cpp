#include <signal.h>
#include <stdint.h>
#include <unistd.h>
#include <iostream>

using namespace std;

template <class T>
tr1::shared_ptr<T> CSingletonPtr<T>::m_singletonPtr;

class CSingletonPtr
{
    private: 
        static 
}


