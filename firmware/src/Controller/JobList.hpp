#ifndef __TPC_CONTROLLER_JOB_LIST_HPP
#define __TPC_CONTROLLER_JOB_LIST_HPP

#include "Controller/Job.hpp"

namespace Controller {
  class JobList {
  public:
    JobList();
    void pushBack(Controller::Job * job);
    void pushFront(Controller::Job * job);
    Controller::Job * getFront() const;
    Controller::Job * popFront();

  protected:
    Controller::Job * head;
  };
}

#endif
