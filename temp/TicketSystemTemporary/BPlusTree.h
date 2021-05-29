//
// Created by Rainy Memory on 2021/1/28.
//

#ifndef TICKETSYSTEM_AUTOMATA_BPLUSTREE_H
#define TICKETSYSTEM_AUTOMATA_BPLUSTREE_H

#include "LRUCacheMemoryPool.h"
#include "RTL/algorithm.h"

//#define debug

namespace RainyMemory {
    template<class key, class data, int MM = 50, int LL = 50, int CACHE_SIZE = 300>
    class BPlusTree {
        /*
         * class BPlusTree
         * --------------------------------------------------------
         * A data structure which implements data indexing or storage.
         * This version [DOES NOT] support duplicate key value, and
         * require class T overloaded [operator<] and [operator=].
         *
         */
    private:
        struct splitNodeReturn {
            int offset;
            key nodeKey;
        };
        
        struct insertReturn {
            bool childNodeNumberIncreased;
            splitNodeReturn node;
        };
        
        struct eraseReturn {
            bool sonNodeNeedResize;
            bool eraseSucceed;
        };
        
        class leafNode;
        
        class internalNode;
        
        class basicInfo {
        public:
            int root = -1;
            int head = -1;
            int size = 0;
        };
        
        enum sizeInfo {
            PAGE_SIZE = 4096,
            L = (PAGE_SIZE - 4 * sizeof(int)) / (sizeof(key) + sizeof(data)) - 1,
            M = (PAGE_SIZE - 5 * sizeof(int) - sizeof(bool)) / (sizeof(key) + sizeof(int)) - 1,
            MAX_RECORD_NUM = L + 1,
            MIN_RECORD_NUM = (L + 1) / 2,
            MAX_KEY_NUM = M + 1,
            MIN_KEY_NUM = (M + 1) / 2,
            MAX_CHILD_NUM = M + 2
        };
    
    private:
        LRUCacheMemoryPool <leafNode, basicInfo> *leafPool;
        LRUCacheMemoryPool <internalNode, basicInfo> *internalPool;
        basicInfo info;
        internalNode rootNode;
    
    private:
        class leafNode {
        public:
            int offset = -1;
//            int leftBrother = -1;
//            int rightBrother = -1;
            int dataNumber = 0;
            key leafKey[MAX_RECORD_NUM];
            data leafData[MAX_RECORD_NUM];
        
        public:
            void addElement(BPlusTree *tree, const key &o1, const data &o2) {
                int pos = RainyMemory::upper_bound(leafKey, leafKey + dataNumber, o1) - leafKey;
                for (int i = dataNumber - 1; i >= pos; i--) {
                    leafKey[i + 1] = leafKey[i];
                    leafData[i + 1] = leafData[i];
                }
                leafKey[pos] = o1;
                leafData[pos] = o2;
                dataNumber++;
                tree->leafPool->update(*this, offset);
            }
            
            bool deleteElement(BPlusTree *tree, const key &o) {
                int pos = RainyMemory::lower_bound(leafKey, leafKey + dataNumber, o) - leafKey;
                if (pos == dataNumber)return false;
                else {
                    if (leafKey[pos] != o)return false;
                    else {
                        for (int j = pos; j < dataNumber - 1; j++) {
                            leafData[j] = leafData[j + 1];
                            leafKey[j] = leafKey[j + 1];
                        }
                        dataNumber--;
                        tree->leafPool->update(*this, offset);
                        return true;
                    }
                }
            }
            
            bool updateElement(BPlusTree *tree, const key &o1, const data &newData) {
                int start = RainyMemory::lower_bound(leafKey, leafKey + dataNumber, o1) - leafKey;
                int end = RainyMemory::upper_bound(leafKey, leafKey + dataNumber, o1) - leafKey;
                bool result = false;
                for (int i = start; i < end; i++) {
                    if (o1 == leafKey[i]) {
                        leafData[i] = newData;
                        result = true;
                        break;
                    }
                }
                if (result)tree->leafPool->update(*this, offset);
                return result;
            }
            
            splitNodeReturn splitNode(BPlusTree *tree) {
                leafNode tempNode;
                tempNode.offset = tree->leafPool->tellWritePoint();
                for (int i = MIN_RECORD_NUM; i < MAX_RECORD_NUM; i++) {
                    tempNode.leafKey[i - MIN_RECORD_NUM] = leafKey[i];
                    tempNode.leafData[i - MIN_RECORD_NUM] = leafData[i];
                }
                tempNode.dataNumber = MAX_RECORD_NUM - MIN_RECORD_NUM;
                dataNumber = MIN_RECORD_NUM;
                tree->leafPool->write(tempNode);
                tree->leafPool->update(*this, offset);
                splitNodeReturn temp;
                temp.offset = tempNode.offset;
                temp.nodeKey = tempNode.leafKey[0];
                return temp;
            }
            
            void borrowLeft(BPlusTree *tree, leafNode &leftNode, internalNode &fatherNode, int index) {
                //transfer data
                for (int i = dataNumber - 1; i >= 0; i--) {
                    leafKey[i + 1] = leafKey[i];
                    leafData[i + 1] = leafData[i];
                }
                leafKey[0] = leftNode.leafKey[leftNode.dataNumber - 1];
                leafData[0] = leftNode.leafData[leftNode.dataNumber - 1];
                dataNumber++;
                leftNode.dataNumber--;
                
                //update fatherNode info
                fatherNode.nodeKey[index - 1] = leafKey[0];
                
                tree->internalPool->update(fatherNode, fatherNode.offset);
                tree->leafPool->update(*this, offset);
                tree->leafPool->update(leftNode, leftNode.offset);
            }
            
            void borrowRight(BPlusTree *tree, leafNode &rightNode, internalNode &fatherNode, int index) {
                //transfer data
                leafKey[dataNumber] = rightNode.leafKey[0];
                leafData[dataNumber] = rightNode.leafData[0];
                for (int i = 0; i < rightNode.dataNumber - 1; i++) {
                    rightNode.leafKey[i] = rightNode.leafKey[i + 1];
                    rightNode.leafData[i] = rightNode.leafData[i + 1];
                }
                dataNumber++;
                rightNode.dataNumber--;
                
                //update fatherNode info
                fatherNode.nodeKey[index] = rightNode.leafKey[0];
                
                tree->internalPool->update(fatherNode, fatherNode.offset);
                tree->leafPool->update(*this, offset);
                tree->leafPool->update(rightNode, rightNode.offset);
            }
            
            //keep left node and delete right node anyway
            //only right-most point can merge left
            void mergeLeft(BPlusTree *tree, leafNode &leftNode, internalNode &fatherNode) {
                //update fatherNode info
                fatherNode.keyNumber--;//erase last element
                
                //transfer data
                for (int i = 0; i < dataNumber; i++) {
                    leftNode.leafKey[i + leftNode.dataNumber] = leafKey[i];
                    leftNode.leafData[i + leftNode.dataNumber] = leafData[i];
                }
                leftNode.dataNumber += dataNumber;
                
                tree->internalPool->update(fatherNode, fatherNode.offset);
                tree->leafPool->update(leftNode, leftNode.offset);
                tree->leafPool->erase(offset);
            }
            
            void mergeRight(BPlusTree *tree, leafNode &rightNode, internalNode &fatherNode, int index) {
                //update fatherNode info
                //delete fatherNode.nodeKey[index] & fatherNode.childNode[index + 1]
                for (int i = index; i < fatherNode.keyNumber - 1; i++) {
                    fatherNode.nodeKey[i] = fatherNode.nodeKey[i + 1];
                    fatherNode.childNode[i + 1] = fatherNode.childNode[i + 2];
                }
                fatherNode.keyNumber--;
                
                //transfer data
                for (int i = 0; i < rightNode.dataNumber; i++) {
                    leafKey[i + dataNumber] = rightNode.leafKey[i];
                    leafData[i + dataNumber] = rightNode.leafData[i];
                }
                dataNumber += rightNode.dataNumber;
                
                tree->internalPool->update(fatherNode, fatherNode.offset);
                tree->leafPool->update(*this, offset);
                tree->leafPool->erase(rightNode.offset);
            }
            
            //return father node need resize
            bool resize(BPlusTree *tree, internalNode &fatherNode, int index, int leftBrother, int rightBrother) {
                if (dataNumber < MIN_RECORD_NUM) {
                    if (index == 0 && rightBrother >= 0) {
                        //try borrow/merge right
                        leafNode rightNode = tree->leafPool->read(rightBrother);
                        if (rightNode.dataNumber > MIN_RECORD_NUM) {
                            borrowRight(tree, rightNode, fatherNode, index);
                            return false;
                        }
                        else {
                            mergeRight(tree, rightNode, fatherNode, index);
                            return true;
                        }
                    }
                    else if (index == fatherNode.keyNumber && leftBrother >= 0) {
                        //try borrow/merge left
                        leafNode leftNode = tree->leafPool->read(leftBrother);
                        if (leftNode.dataNumber > MIN_RECORD_NUM) {
                            borrowLeft(tree, leftNode, fatherNode, index);
                            return false;
                        }
                        else {
                            mergeLeft(tree, leftNode, fatherNode);
                            return true;
                        }
                    }
                    else if (leftBrother >= 0 && rightBrother >= 0) {
                        //try borrow/merge left/right
                        leafNode leftNode = tree->leafPool->read(leftBrother);
                        if (leftNode.dataNumber > MIN_RECORD_NUM) {
                            borrowLeft(tree, leftNode, fatherNode, index);
                            return false;
                        }
                        else {
                            leafNode rightNode = tree->leafPool->read(rightBrother);
                            if (rightNode.dataNumber > MIN_RECORD_NUM) {
                                borrowRight(tree, rightNode, fatherNode, index);
                                return false;
                            }
                            else {
                                mergeRight(tree, rightNode, fatherNode, index);
                                return true;
                            }
                        }
                    }
                    else return false;
                }
                else return false;
            }

#ifdef debug
            
            void show() const {
                std::cout << "[leafNode]" << std::endl;
                std::cout << "offset: " << offset << std::endl;
                std::cout << "leftBrother: " << leftBrother << std::endl;
                std::cout << "rightBrother: " << rightBrother << std::endl;
                std::cout << "dataNumber: " << dataNumber << std::endl;
                std::cout << "leafKey & leafData:" << std::endl;
                for (int i = 0; i < dataNumber; i++) {
                    std::cout << "leafKey: " << leafKey[i] << "\t\t\t\t\t\t\t\t\t\t\t" << "leafData: " << leafData[i] << std::endl;
                }
                std::cout << std::endl;
            }

#endif
        };
        
        class internalNode {
        public:
            int offset = -1;
            bool childNodeIsLeaf = false;
            int keyNumber = 0;
            key nodeKey[MAX_KEY_NUM] {};
            int childNode[MAX_CHILD_NUM] {};
        
        public:
//            internalNode() {
//                memset(childNode, -1, sizeof(childNode));
//            }
            
            void addElement(BPlusTree *tree, const splitNodeReturn &o, int pos) {
                for (int i = keyNumber - 1; i >= pos; i--) {
                    childNode[i + 2] = childNode[i + 1];
                    nodeKey[i + 1] = nodeKey[i];
                }
                childNode[pos + 1] = o.offset;
                nodeKey[pos] = o.nodeKey;
                keyNumber++;
                tree->internalPool->update(*this, offset);
            }
            
            void splitRoot(BPlusTree *tree) {
                //oldRoot(*this) -> oldRoot + tempNode
                internalNode newRoot, tempNode;
                newRoot.offset = tree->internalPool->write(newRoot);
                tempNode.offset = tree->internalPool->tellWritePoint();
                tempNode.childNodeIsLeaf = childNodeIsLeaf;
                for (int i = MIN_KEY_NUM + 1; i < keyNumber; i++) {
                    tempNode.nodeKey[i - MIN_KEY_NUM - 1] = nodeKey[i];
                    tempNode.childNode[i - MIN_KEY_NUM - 1] = childNode[i];
                }
                tempNode.childNode[keyNumber - MIN_KEY_NUM - 1] = childNode[keyNumber];
                tempNode.keyNumber = keyNumber - MIN_KEY_NUM - 1;
                keyNumber = MIN_KEY_NUM;
                newRoot.keyNumber = 1;
                newRoot.nodeKey[0] = nodeKey[MIN_KEY_NUM];
                newRoot.childNode[0] = offset;
                newRoot.childNode[1] = tempNode.offset;
                tree->internalPool->write(tempNode);
                tree->internalPool->update(newRoot, newRoot.offset);
                tree->internalPool->update(*this, offset);
                tree->info.root = newRoot.offset;
                tree->rootNode = newRoot;
            }
            
            splitNodeReturn splitNode(BPlusTree *tree) {
                internalNode tempNode;
                tempNode.offset = tree->internalPool->tellWritePoint();
                tempNode.childNodeIsLeaf = childNodeIsLeaf;
                //delete No.MIN_KEY_NUM key, and return it to upper layer
                //in the following example, key 4 will be returned
                //key:    1 2 3 4 5 6 7 8
                //child: 1 2 3 4 5 6 7 8 9
                //               \/
                //key:    1 2 3   4   5 6 7 8
                //child: 1 2 3 4     5 6 7 8 9
                for (int i = MIN_KEY_NUM + 1; i < keyNumber; i++) {
                    tempNode.nodeKey[i - MIN_KEY_NUM - 1] = nodeKey[i];
                    tempNode.childNode[i - MIN_KEY_NUM - 1] = childNode[i];
                }
                tempNode.childNode[keyNumber - MIN_KEY_NUM - 1] = childNode[keyNumber];
                
                tempNode.keyNumber = keyNumber - MIN_KEY_NUM - 1;
                keyNumber = MIN_KEY_NUM;
                tree->internalPool->write(tempNode);
                tree->internalPool->update(*this, offset);
                splitNodeReturn temp;
                temp.offset = tempNode.offset;
                temp.nodeKey = nodeKey[MIN_KEY_NUM];
                return temp;
            }
            
            void borrowLeft(BPlusTree *tree, internalNode &leftNode, internalNode &fatherNode, int index) {
                //transfer data
                childNode[keyNumber + 1] = childNode[keyNumber];
                for (int i = keyNumber - 1; i >= 0; i--) {
                    childNode[i + 1] = childNode[i];
                    nodeKey[i + 1] = nodeKey[i];
                }
                childNode[0] = leftNode.childNode[leftNode.keyNumber];
                nodeKey[0] = fatherNode.nodeKey[index - 1];
                fatherNode.nodeKey[index - 1] = leftNode.nodeKey[leftNode.keyNumber - 1];
                keyNumber++;
                leftNode.keyNumber--;
                
                tree->internalPool->update(fatherNode, fatherNode.offset);
                tree->internalPool->update(*this, offset);
                tree->internalPool->update(leftNode, leftNode.offset);
            }
            
            void borrowRight(BPlusTree *tree, internalNode &rightNode, internalNode &fatherNode, int index) {
                //transfer data
                nodeKey[keyNumber] = fatherNode.nodeKey[index];
                fatherNode.nodeKey[index] = rightNode.nodeKey[0];
                childNode[keyNumber + 1] = rightNode.childNode[0];
                for (int i = 0; i < rightNode.keyNumber - 1; i++) {
                    rightNode.childNode[i] = rightNode.childNode[i + 1];
                    rightNode.nodeKey[i] = rightNode.nodeKey[i + 1];
                }
                rightNode.childNode[rightNode.keyNumber - 1] = rightNode.childNode[rightNode.keyNumber];
                keyNumber++;
                rightNode.keyNumber--;
                
                tree->internalPool->update(fatherNode, fatherNode.offset);
                tree->internalPool->update(*this, offset);
                tree->internalPool->update(rightNode, rightNode.offset);
            }
            
            //keep left node and delete right node anyway
            //only right-most point can merge left
            void mergeLeft(BPlusTree *tree, internalNode &leftNode, internalNode &fatherNode) {
                //transfer data
                //in the following example, key 4 is fatherNode.nodeKey[keyNumber - 1]
                //key:    1 2 3   4   5 6 7 8
                //child: 1 2 3 4     5 6 7 8 9
                //                \/
                //key:    1 2 3 4 5 6 7 8
                //child: 1 2 3 4 5 6 7 8 9
                leftNode.nodeKey[leftNode.keyNumber] = fatherNode.nodeKey[keyNumber - 1];
                for (int i = 0; i < keyNumber; i++) {
                    leftNode.nodeKey[i + leftNode.keyNumber + 1] = nodeKey[i];
                    leftNode.childNode[i + leftNode.keyNumber + 1] = childNode[i];
                }
                leftNode.childNode[leftNode.keyNumber + keyNumber + 1] = childNode[keyNumber];
                leftNode.keyNumber += keyNumber + 1;
                
                //update fatherNode info
                //delete last element
                fatherNode.keyNumber--;
                
                tree->internalPool->update(fatherNode, fatherNode.offset);
                tree->internalPool->update(leftNode, leftNode.offset);
                tree->internalPool->erase(offset);
            }
            
            void mergeRight(BPlusTree *tree, internalNode &rightNode, internalNode &fatherNode, int index) {
                //transfer data
                //in the following example, key 4 is fatherNode.nodeKey[index]
                //key:    1 2 3   4   5 6 7 8
                //child: 1 2 3 4     5 6 7 8 9
                //                \/
                //key:    1 2 3 4 5 6 7 8
                //child: 1 2 3 4 5 6 7 8 9
                nodeKey[keyNumber] = fatherNode.nodeKey[index];
                for (int i = 0; i < rightNode.keyNumber; i++) {
                    nodeKey[i + keyNumber + 1] = rightNode.nodeKey[i];
                    childNode[i + keyNumber + 1] = rightNode.childNode[i];
                }
                childNode[keyNumber + rightNode.keyNumber + 1] = rightNode.childNode[rightNode.keyNumber];
                keyNumber += rightNode.keyNumber + 1;
                
                //update fatherNode info
                //delete fatherNode.nodeKey[index] & fatherNode.childNode[index + 1]
                for (int i = index; i < fatherNode.keyNumber - 1; i++) {
                    fatherNode.nodeKey[i] = fatherNode.nodeKey[i + 1];
                    fatherNode.childNode[i + 1] = fatherNode.childNode[i + 2];
                }
                fatherNode.keyNumber--;
                
                tree->internalPool->update(fatherNode, fatherNode.offset);
                tree->internalPool->update(*this, offset);
                tree->internalPool->erase(rightNode.offset);
            }
            
            void resizeRoot(BPlusTree *tree) {
                if ((!childNodeIsLeaf) && (keyNumber == 0)) {
                    tree->info.root = childNode[0];
                    tree->internalPool->erase(offset);
                    internalNode tempNode = tree->internalPool->read(childNode[0]);
                    tree->internalPool->update(tempNode, tempNode.offset);
                }
            }
            
            //return father node need resize
            bool resize(BPlusTree *tree, internalNode &fatherNode, int index, int leftBrother, int rightBrother) {
                if (keyNumber < MIN_KEY_NUM) {
                    if (index == 0 && rightBrother >= 0) {
                        //try borrow/merge right
                        internalNode rightNode = tree->internalPool->read(rightBrother);
                        if (rightNode.keyNumber > MIN_KEY_NUM) {
                            borrowRight(tree, rightNode, fatherNode, index);
                            return false;
                        }
                        else {
                            mergeRight(tree, rightNode, fatherNode, index);
                            return true;
                        }
                    }
                    else if (index == fatherNode.keyNumber && leftBrother >= 0) {
                        //try borrow/merge left
                        internalNode leftNode = tree->internalPool->read(leftBrother);
                        if (leftNode.keyNumber > MIN_KEY_NUM) {
                            borrowLeft(tree, leftNode, fatherNode, index);
                            return false;
                        }
                        else {
                            mergeLeft(tree, leftNode, fatherNode);
                            return true;
                        }
                    }
                    else if (leftBrother >= 0 && rightBrother >= 0) {
                        internalNode leftNode = tree->internalPool->read(leftBrother);
                        if (leftNode.keyNumber > MIN_KEY_NUM) {
                            borrowLeft(tree, leftNode, fatherNode, index);
                            return false;
                        }
                        else {
                            internalNode rightNode = tree->internalPool->read(rightBrother);
                            if (rightNode.keyNumber > MIN_KEY_NUM) {
                                borrowRight(tree, rightNode, fatherNode, index);
                                return false;
                            }
                            else {
                                mergeRight(tree, rightNode, fatherNode, index);
                                return true;
                            }
                        }
                    }
                    else return false;
                }
                else return false;
            }

#ifdef debug
            
            void show() const {
                std::cout << "[internalNode]" << std::endl;
                std::cout << "offset: " << offset << std::endl;
                std::cout << "leftBrother: " << leftBrother << std::endl;
                std::cout << "rightBrother: " << rightBrother << std::endl;
                std::cout << (childNodeIsLeaf ? "child node is leaf" : "child node is internal") << std::endl;
                std::cout << "keyNumber: " << keyNumber << std::endl;
                std::cout << "nodeKey & childNode:" << std::endl;
                for (int i = 0; i < keyNumber; i++) {
                    std::cout << "\t\t\t\t\t\t\t\t\t\t\t" << "childNode: " << childNode[i] << std::endl;
                    std::cout << "nodeKey: " << nodeKey[i] << std::endl;
                }
                std::cout << "\t\t\t\t\t\t\t\t\t\t\t" << "childNode: " << childNode[keyNumber] << std::endl;
                std::cout << std::endl;
                
            }

#endif
        };
    
    private:
        void initialize(const key &o1, const data &o2) {
            rootNode.offset = internalPool->tellWritePoint();
            rootNode.childNodeIsLeaf = true;
            rootNode.childNode[0] = leafPool->tellWritePoint();
            internalPool->write(rootNode);
            leafNode tempNode;
            tempNode.offset = rootNode.childNode[0];
            tempNode.dataNumber = 1;
            tempNode.leafKey[0] = o1;
            tempNode.leafData[0] = o2;
            leafPool->write(tempNode);
            info.head = tempNode.offset;
            info.root = rootNode.offset;
        }
        
        //first represent child node number ++
        insertReturn recursionInsert(int now, const key &o1, const data &o2) {
            internalNode nowNode {internalPool->read(now)};
            if (nowNode.childNodeIsLeaf) {
                int index = RainyMemory::upper_bound(nowNode.nodeKey, nowNode.nodeKey + nowNode.keyNumber, o1) - nowNode.nodeKey;
                leafNode targetNode {leafPool->read(nowNode.childNode[index])};
                targetNode.addElement(this, o1, o2);
                insertReturn temp;
                if (targetNode.dataNumber == MAX_RECORD_NUM) {
                    nowNode.addElement(this, targetNode.splitNode(this), index);
                    if (nowNode.keyNumber == MAX_KEY_NUM) {
                        temp.childNodeNumberIncreased = true;
                        temp.node = nowNode.splitNode(this);
                    }
                    else temp.childNodeNumberIncreased = false;
                }
                else temp.childNodeNumberIncreased = false;
                return temp;
            }
            else {
                int index = RainyMemory::upper_bound(nowNode.nodeKey, nowNode.nodeKey + nowNode.keyNumber, o1) - nowNode.nodeKey;
                insertReturn temp {recursionInsert(nowNode.childNode[index], o1, o2)};
                if (temp.childNodeNumberIncreased) {
                    nowNode.addElement(this, temp.node, index);
                    if (nowNode.keyNumber == MAX_KEY_NUM)temp.node = nowNode.splitNode(this);
                    else temp.childNodeNumberIncreased = false;
                }
                return temp;
            }
        }
        
        eraseReturn recursionErase(int now, const key &o) {
            internalNode nowNode {internalPool->read(now)};
            if (nowNode.childNodeIsLeaf) {
                int index = RainyMemory::upper_bound(nowNode.nodeKey, nowNode.nodeKey + nowNode.keyNumber, o) - nowNode.nodeKey;
                leafNode targetNode {leafPool->read(nowNode.childNode[index])};
                eraseReturn temp;
                temp.eraseSucceed = targetNode.deleteElement(this, o);
                int leftBrother = index <= 0 ? -1 : nowNode.childNode[index - 1], rightBrother = index >= nowNode.keyNumber ? -1 : nowNode.childNode[index + 1];
                temp.sonNodeNeedResize = targetNode.resize(this, nowNode, index, leftBrother, rightBrother);
                return temp;
            }
            else {
                int index = RainyMemory::upper_bound(nowNode.nodeKey, nowNode.nodeKey + nowNode.keyNumber, o) - nowNode.nodeKey;
                eraseReturn temp {recursionErase(nowNode.childNode[index], o)};
                if (!temp.sonNodeNeedResize || !temp.eraseSucceed)return temp;
                else {
                    internalNode sonNode {internalPool->read(nowNode.childNode[index])};
                    int leftBrother = index <= 0 ? -1 : nowNode.childNode[index - 1], rightBrother = index >= nowNode.keyNumber ? -1 : nowNode.childNode[index + 1];
                    temp.sonNodeNeedResize = sonNode.resize(this, nowNode, index, leftBrother, rightBrother);
                    return temp;
                }
            }
        }
        
        std::pair<data, bool> recursionFind(int now, const key &o) const {
            internalNode nowNode = internalPool->read(now);
            if (nowNode.childNodeIsLeaf) {
                int index = RainyMemory::upper_bound(nowNode.nodeKey, nowNode.nodeKey + nowNode.keyNumber, o) - nowNode.nodeKey;
                leafNode targetNode {leafPool->read(nowNode.childNode[index])};
                int pos = RainyMemory::lower_bound(targetNode.leafKey, targetNode.leafKey + targetNode.dataNumber, o) - targetNode.leafKey;
                if (pos == targetNode.dataNumber)return std::pair<data, bool> {data(), false};
                if (targetNode.leafKey[pos] == o)return std::pair<data, bool> {targetNode.leafData[pos], true};
                else return std::pair<data, bool> {data(), false};
            }
            else {
                int index = RainyMemory::upper_bound(nowNode.nodeKey, nowNode.nodeKey + nowNode.keyNumber, o) - nowNode.nodeKey;
                return recursionFind(nowNode.childNode[index], o);
            }
        }
        
        void recursionUpdate(int now, const key &o1, const data &newData) {
            internalNode nowNode = internalPool->read(now);
            if (nowNode.childNodeIsLeaf) {
                int index = RainyMemory::upper_bound(nowNode.nodeKey, nowNode.nodeKey + nowNode.keyNumber, o1) - nowNode.nodeKey;
                leafNode targetNode = leafPool->read(nowNode.childNode[index]);
                if (!targetNode.updateElement(this, o1, newData)) {
                    while (targetNode.leftBrother >= 0) {
                        targetNode = leafPool->read(targetNode.leftBrother);
                        if (targetNode.updateElement(this, o1, newData))break;
                    }
                }
            }
            else {
                int index = RainyMemory::upper_bound(nowNode.nodeKey, nowNode.nodeKey + nowNode.keyNumber, o1) - nowNode.nodeKey;
                recursionUpdate(nowNode.childNode[index], o1, newData);
            }
        }
    
    public:
        explicit BPlusTree(const string &name) :
                leafPool(new LRUCacheMemoryPool<leafNode, basicInfo>("Leaf" + name, basicInfo {}, CACHE_SIZE)),
                internalPool(new LRUCacheMemoryPool<internalNode, basicInfo>("Internal" + name, basicInfo {}, CACHE_SIZE)),
                info(leafPool->readExtraMessage()),
                rootNode(info.root == -1 ? internalNode {} : internalPool->read(info.root)) {}
        
        ~BPlusTree() {
            leafPool->updateExtraMessage(info);
            internalPool->updateExtraMessage(info);
            internalPool->update(rootNode, info.root);
            delete leafPool;
            delete internalPool;
        }
        
        int size() const {
            return info.size;
        }
        
        bool empty() const {
            return info.size == 0;
        }
        
        void clear() {
            leafPool->clear();
            internalPool->clear();
            info = leafPool->readExtraMessage();
        }
        
        void insert(const key &o1, const data &o2) {
            info.size++;
            if (info.root == -1)return initialize(o1, o2);
            if (rootNode.childNodeIsLeaf) {
                int index = RainyMemory::upper_bound(rootNode.nodeKey, rootNode.nodeKey + rootNode.keyNumber, o1) - rootNode.nodeKey;
                leafNode targetNode {leafPool->read(rootNode.childNode[index])};
                targetNode.addElement(this, o1, o2);
                if (targetNode.dataNumber == MAX_RECORD_NUM)rootNode.addElement(this, targetNode.splitNode(this), index);
                if (rootNode.keyNumber == MAX_KEY_NUM)rootNode.splitRoot(this);
            }
            else {
                int index = RainyMemory::upper_bound(rootNode.nodeKey, rootNode.nodeKey + rootNode.keyNumber, o1) - rootNode.nodeKey;
                insertReturn temp {recursionInsert(rootNode.childNode[index], o1, o2)};
                if (temp.childNodeNumberIncreased) {
                    rootNode.addElement(this, temp.node, index);
                    if (rootNode.keyNumber == MAX_KEY_NUM)rootNode.splitRoot(this);
                }
            }
        }
        
        //return whether erase is successful
        bool erase(const key &o) {
            if (info.size == 0 || info.root == -1)return false;
            bool deleted;
            if (rootNode.childNodeIsLeaf) {
                int index = RainyMemory::upper_bound(rootNode.nodeKey, rootNode.nodeKey + rootNode.keyNumber, o) - rootNode.nodeKey;
                leafNode targetNode {leafPool->read(rootNode.childNode[index])};
                deleted = targetNode.deleteElement(this, o);
                int leftBrother = index <= 0 ? -1 : rootNode.childNode[index - 1], rightBrother = index >= rootNode.keyNumber ? -1 : rootNode.childNode[index + 1];
                if (deleted && targetNode.resize(this, rootNode, index, leftBrother, rightBrother))rootNode.resizeRoot(this);
            }
            else {
                int index = RainyMemory::upper_bound(rootNode.nodeKey, rootNode.nodeKey + rootNode.keyNumber, o) - rootNode.nodeKey;
                eraseReturn temp {recursionErase(rootNode.childNode[index], o)};
                if (!temp.eraseSucceed)return false;
                else {
                    deleted = true;
                    if (temp.sonNodeNeedResize) {
                        internalNode sonNode {internalPool->read(rootNode.childNode[index])};
                        int leftBrother = index <= 0 ? -1 : rootNode.childNode[index - 1], rightBrother = index >= rootNode.keyNumber ? -1 : rootNode.childNode[index + 1];
                        if (sonNode.resize(this, rootNode, index, leftBrother, rightBrother))rootNode.resizeRoot(this);
                    }
                }
            }
            if (deleted)info.size--;
            return deleted;
        }
        
        std::pair<data, bool> find(const key &o) const {
            if (info.size == 0 || info.root == -1)return std::pair<data, bool> {data(), false};
            if (rootNode.childNodeIsLeaf) {
                int index = RainyMemory::upper_bound(rootNode.nodeKey, rootNode.nodeKey + rootNode.keyNumber, o) - rootNode.nodeKey;
                leafNode targetNode {leafPool->read(rootNode.childNode[index])};
                int pos = RainyMemory::lower_bound(targetNode.leafKey, targetNode.leafKey + targetNode.dataNumber, o) - targetNode.leafKey;
                if (pos == targetNode.dataNumber)return std::pair<data, bool> {data(), false};
                if (targetNode.leafKey[pos] == o)return std::pair<data, bool> {targetNode.leafData[pos], true};
                else return std::pair<data, bool> {data(), false};
            }
            else {
                int index = RainyMemory::upper_bound(rootNode.nodeKey, rootNode.nodeKey + rootNode.keyNumber, o) - rootNode.nodeKey;
                return recursionFind(rootNode.childNode[index], o);
            }
        }
        
        void update(const key &o1, const data &newData) {
            if (info.size == 0 || info.root == -1)return;
            if (rootNode.childNodeIsLeaf) {
                int index = RainyMemory::upper_bound(rootNode.nodeKey, rootNode.nodeKey + rootNode.keyNumber, o1) - rootNode.nodeKey;
                leafNode targetNode = leafPool->read(rootNode.childNode[index]);
                if (!targetNode.updateElement(this, o1, newData)) {
                    while (targetNode.leftBrother >= 0) {
                        targetNode = leafPool->read(targetNode.leftBrother);
                        if (targetNode.updateElement(this, o1, newData))break;
                    }
                }
            }
            else {
                int index = RainyMemory::upper_bound(rootNode.nodeKey, rootNode.nodeKey + rootNode.keyNumber, o1) - rootNode.nodeKey;
                recursionUpdate(rootNode.childNode[index], o1, newData);
            }
        }
        
        bool containsKey(const key &k) {
            std::pair<data, bool> temp = find(k);
            return temp.second;
        }

#ifdef debug
        private:
            void show(int offset, bool isLeaf) const {
                std::cout << "[pos] " << offset << std::endl;
                if (isLeaf) {
                    leafNode tempNode = leafPool->read(offset);
                    tempNode.show();
                }
                else {
                    internalNode tempNode = internalPool->read(offset);
                    tempNode.show();
                    std::cout << std::endl;
                    for (int i = 0; i <= tempNode.keyNumber; i++) {
                        if (tempNode.childNodeIsLeaf)show(tempNode.childNode[i], true);
                        else show(tempNode.childNode[i], false);
                    }
                }
            };
        
        public:
            void show() const {
                std::cout << "[show]--------------------------------------------------------------------------------" << std::endl;
                show(info.root, false);
                std::cout << "[show]--------------------------------------------------------------------------------" << std::endl;
            }
            
            void showLeaves() const {
                int cur = info.head;
                while (cur >= 0) {
                    leafNode nowNode = leafPool->read(cur);
                    nowNode.show();
                    cur = nowNode.rightBrother;
                }
            }
#endif
    };
}

#endif //TICKETSYSTEM_AUTOMATA_BPLUSTREE_H
