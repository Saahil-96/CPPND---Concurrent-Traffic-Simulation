#include <iostream>
#include <random>
#include <stdlib.h>
#include <chrono>
#include <mutex>
#include <thread>
#include <future>

#include "TrafficLight.h"

using namespace std::chrono; 
/* Implementation of class "MessageQueue" */


template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait() 
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function. 
  std::unique_lock<std::mutex> lock(_mutex);
  _condition.wait(lock,[this]{return !_queue.empty();});
  T msg = std::move(_queue.back());
  _queue.pop_back();
  return msg;
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
  std::unique_lock<std::mutex> lock(_mutex);
  _queue.push_back(std::move(msg));
  _condition.notify_one();
}


/* Implementation of class "TrafficLight" */


TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
    _messages = std::make_shared<MessageQueue<TrafficLightPhase>>();
}

void TrafficLight::waitForGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop 
    // runs and repeatedly calls the receive function on the message queue. 
    // Once it receives TrafficLightPhase::green, the method returns.
  std::unique_lock<std::mutex> {_mutex};
  while(true)
  {
    auto msg=_messages->receive();
    if (msg==green)
    {
      break;
    }
  }
  _condition.notify_one();
}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{
    // FP.2b : Finally, the private method „cycleThroughPhases“ should be started in a thread when the public method „simulate“ is called. To do this, use the thread queue in the base class. 
  threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
  high_resolution_clock::time_point start = high_resolution_clock::now(); 
  high_resolution_clock::time_point stop;
	while (true)
	{
      stop = high_resolution_clock::now(); 
      auto duration = duration_cast<milliseconds>(stop - start); 
		if (duration.count()>(rand()%2000+4000))
		{
          if(_currentPhase==green)
          {
            _currentPhase=red;
           }
          else
          {
            _currentPhase=green;
           }
            auto msg= _currentPhase; 
          auto ftr=std::async(std::launch::async,&MessageQueue<TrafficLightPhase>::send,_messages,std::move(_currentPhase));
          ftr.wait();
          start = high_resolution_clock::now(); 
          std::this_thread::sleep_for(std::chrono::milliseconds(1));
         }
	}
    // FP.2a : Implement the function with an infinite loop that measures the time between two loop cycles 
    // and toggles the current phase of the traffic light between red and green and sends an update method 
    // to the message queue using move semantics. The cycle duration should be a random value between 4 and 6 seconds. 
    // Also, the while-loop should use std::this_thread::sleep_for to wait 1ms between two cycles. 
}