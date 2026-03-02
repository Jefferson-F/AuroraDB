//
// Created by T.I on 18/09/2025.
//

#ifndef AURORADB_REPLACER_H
#define AURORADB_REPLACER_H
#include <memory>
#include <queue>
#include <unordered_map>

#include "Page.h"
#include "PageManager.h"

struct Node {
    Node *prev;
    unsigned short cacheId;
    unsigned short pinCount;
    Node *next;

};

class BufferPoolManager{
    Page cache[4]{};
    Node *head;
    Node *tail;
    std::unique_ptr<PageManager> pageManager;
    std::queue<short> queueFrame;
    std::unordered_map<unsigned int, Node*> cacheMap;
    public:
    explicit BufferPoolManager();
    ~BufferPoolManager();
    Page* pin(unsigned int pageId);//Pin irá mover a página até o inicio da lista duplamente encadeada e incrementar pinCount.
    void unpin(unsigned int pageId);//Unpin irá decrementar pinCount.
    short victim();
    void removeVictim();
    void newPage(unsigned int pageId);

};

#endif //AURORADB_REPLACER_H