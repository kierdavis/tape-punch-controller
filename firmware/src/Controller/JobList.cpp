#include "Controller/Job.hpp"
#include "Controller/JobList.hpp"

Controller::JobList::JobList() : head(nullptr) {}

void Controller::JobList::pushBack(Controller::Job * job) {
  job->next = nullptr;
  if (head == nullptr) {
    head = job;
  } else {
    Controller::Job * tail = head;
    while (tail->next != nullptr) {
      tail = tail->next;
    }
    tail->next = job;
  }
}

void Controller::JobList::pushFront(Controller::Job * job) {
  job->next = head;
  head = job;
}

Controller::Job * Controller::JobList::getFront() const {
  return head;
}

Controller::Job * Controller::JobList::popFront() {
  Controller::Job * job = head;
  if (job != nullptr) {
    head = job->next;
    job->next = nullptr;
  }
  return job;
}
