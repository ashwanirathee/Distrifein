#ifndef RB_HPP
#define RB_HPP

#include <unordered_set>
#include <vector>
#include <iostream>

#include <distrifein/beb.h>
#include <distrifein/fd.h>
#include <distrifein/event.h>
#include <distrifein/eventbus.h>
#include <distrifein/logger.h>
#include <distrifein/message.h>
#include <distrifein/orderedset.h>

class ReliableBroadcaster
{
public:
    ReliableBroadcaster(BestEffortBroadcaster &beb, FailureDetector &fd, std::vector<int> peers_ids, EventBus &eventBus, int node_id);
    void broadcast(const Event &event);
    void deliver(const Event &event);

    void handleCrashEvent(const Event &event);
    void handleBEBDeliverEvent(const Event &event);

    TcpServer &getServer();

private:
    int node_id;
    std::vector<int> peer_ids;
    BestEffortBroadcaster &beb;
    FailureDetector &fd;
    Logger &logger = Logger::getInstance();
    EventBus &eventBus;
    std::unordered_set<std::string> delivered;         // Set of delivered messages
    std::unordered_map<int, OrderedSet<Message>> from; // from[pi] := ∅
    std::unordered_set<int> correct;                   // Set of correct nodes
};
#endif