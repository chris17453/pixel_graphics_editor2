/* 
 * File:   event.h
 * Author: nd
 *
 * Created on February 14, 2016, 8:18 AM
 */

#ifndef EVENT_H
#define	EVENT_H

// A C++11 lambda function can be used.

// Advantages: 
//   - Relatively direct and straightforward C++11.

// Disadvantages: 
//   - Requires decent C++11 support.

#include <stdio.h>
#include <functional>               // This gets us std::function


typedef std::function<void(void)> CallbackFunction;

class Caller {
public:
    Caller(){
        m_cb=NULL;
    }

    void connectCallback(CallbackFunction cb) {
        m_cb = cb;
    }

    void call(){
       // printf("Caller::call() calling callback...\n");
        if(m_cb!=NULL) m_cb();
    }

private:
    CallbackFunction m_cb;
};

#endif	/* EVENT_H */