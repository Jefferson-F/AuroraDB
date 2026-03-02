//
// Created by T.I on 18/09/2025.
//
#include "include/BufferPoolManager.h"

#include <iostream>
#include <memory>
#include <unordered_map>

#include "include/PageManager.h"

BufferPoolManager::BufferPoolManager() {
    this->head = nullptr;
    this->tail = nullptr;
    pageManager = std::make_unique<PageManager>("aurora.db");
    for (short i = 0; i < 4; i++) {
        this->queueFrame.push(i);
    }
}

void BufferPoolManager::newPage(const unsigned int pageId) {
    const auto node = new Node();
    if(this->head == nullptr) {
        const short id = this->queueFrame.front();
        this->queueFrame.pop();
        this->cache[id] = pageManager->readPage(pageId);
        node->prev = nullptr;
        node->next = nullptr;
        this->head = node;
        this->tail = node;
        node->cacheId = id;
        this->cacheMap[this->cache[id].id] = node;
        node->pinCount++;
        return;
    }
    if (this->head == this->tail) {
        const short id = this->queueFrame.front();
        this->queueFrame.pop();
        this->cache[id] = pageManager->readPage(pageId);
        node->prev = this->head;
        this->head->next = node;
        node->next = nullptr;
        node->cacheId = id;
        this->cacheMap[this->cache[id].id] = node;
        node->pinCount++;
        this->tail = node;
        return;
    }
    if (!this->queueFrame.empty()) {
        const short id = this->queueFrame.front();
        this->queueFrame.pop();
        this->cache[id] = pageManager->readPage(pageId);
        node->prev = this->tail;
        node->prev->next = node;
        this->tail = node;
        node->next = nullptr;
        node->cacheId = id;
        this->cacheMap[this->cache[id].id] = node;
        node->pinCount++;
        return;
    }
    std::cerr << "Cache sem espaco" << std::endl;

}

Page *BufferPoolManager::pin(const unsigned int pageId) {
    const auto node = this->cacheMap.find(pageId);
    if (node != this->cacheMap.end() && node->second == this->head) {
        node->second->pinCount++;
        return &this->cache[node->second->cacheId];
    }
    if (node != this->cacheMap.end() && node->second == this->tail) {
        node->second->pinCount++;
        this->tail = node->second->prev;
        this->tail->next = nullptr;
        node->second->next = this->head;
        node->second->prev = nullptr;
        this->head->prev = node->second;
        this->head = node->second;
        return &this->cache[node->second->cacheId];
    }
    if (node != this->cacheMap.end()) {
        node->second->pinCount++;
        node->second->prev->next = node->second->next;
        node->second->next->prev = node->second->prev;
        node->second->next = this->head;
        node->second->prev = nullptr;
        this->head->next->prev = node->second;
        this->head = node->second;
        return &this->cache[node->second->cacheId];
    }
    if (!this->queueFrame.empty()) {
        this->newPage(pageId);
        const unsigned short idCache = this->cacheMap.find(pageId)->second->cacheId;
        return &this->cache[idCache];
    }
    return nullptr;
}

void BufferPoolManager::unpin(const unsigned int pageId) {
    const auto node = this->cacheMap.find(pageId);
    if (node != this->cacheMap.end()) {
        node->second->pinCount--;
    }
    if (node == this->cacheMap.end()) {
        std::cerr << "Page " << pageId << " nao esta em cache" << std::endl;
    }
}

short BufferPoolManager::victim() {
    const Node *temp = this->tail;
    while (temp != nullptr) {
        if (temp->pinCount == 0) {
            return temp->cacheId;
        }
        temp = temp->prev;
    }
    return -1;

}

void BufferPoolManager::removeVictim() {
    const short idVictim = this->victim();
    const unsigned int idPage = this->cache[idVictim].id;
    if (idVictim == -1) {
        std::cerr << "Todas paginas pinnadas" << std::endl;
        return;
    }
    const Node *victimNode = this->cacheMap.find(idPage)->second;

    if (victimNode == this->head) {
        if (victimNode->next != nullptr) {
            victimNode->next->prev = nullptr;
            this->head = victimNode->next;
        }
        if (victimNode->next == nullptr) {
            this->head = nullptr;
            this->tail = nullptr;
        }
        delete victimNode;
        this->queueFrame.push(idVictim);
        this->cacheMap.erase(idPage);
        this->cache[idVictim] = {};
        return;
    }
    if (victimNode == this->tail) {
        victimNode->prev->next = nullptr;
        this->tail = victimNode->prev;
        delete victimNode;
        this->queueFrame.push(idVictim);
        this->cacheMap.erase(idPage);
        this->cache[idVictim] = {};
        return;
    }
    victimNode->prev->next = victimNode->next;
    victimNode->next->prev = victimNode->prev;
    this->queueFrame.push(idVictim);
    this->cacheMap.erase(idPage);
    this->cache[idVictim] = {};
    delete victimNode;
}

BufferPoolManager::~BufferPoolManager() {
    while (this->head != nullptr) {
            const Node *temp = this->head;
            cache[this->head->cacheId] = {};
            this->head = this->head->next;
            delete temp;
    }
    this->tail = nullptr;

}