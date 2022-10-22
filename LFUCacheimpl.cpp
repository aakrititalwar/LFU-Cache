/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <bits/stdc++.h>
using namespace std;

class KeyNode{
    public:
    int key;
    int value;
    KeyNode* prev;
    KeyNode* next;
    KeyNode(int key, int val){
        this->key = key;
        this->value =val;
        prev=nullptr;
        next=nullptr;
    }
};

class ListNode{
    public:
    KeyNode* head;
    KeyNode* tail;
    ListNode* prev;
    ListNode* next;
    int freq;
    ListNode(int freq){
        this->freq=freq;
    }

    int get(int key, KeyNode* keynodeLoc);
    KeyNode* add(int key, int val);
    int remove();


};

class LFUCache {
    public:
    int capacity;
    int currCapcity;
    ListNode* head; 
    ListNode* tail;
    unordered_map<int, pair<ListNode*, KeyNode*>> cache;
    LFUCache(int capacity) {
        this->capacity=capacity;
        currCapcity=0;
        head=NULL;
        tail=NULL;
    }
    int get(int key);
    void put(int key, int value);
    void remove();
    void print();

    

};

int LFUCache::get(int key) {
        if(capacity==0)
            return -1;
        if(!cache.count(key))                               // if key doesnt exists in cache
            return -1;

        pair<ListNode*, KeyNode*> location = cache[key];
        int val = location.first->get(key, location.second);       
        bool currListNode= false;
        int freq = location.first->freq, headFreq = head->freq;
        ListNode* nextL = location.first->next;
        if(location.first->head==location.first->tail) {   // if the Linklist of listnode's has 1 or no value
            currListNode=true;
            ListNode* prev = location.first->prev;
            ListNode* next = location.first->next;
            nextL = next;
            if(prev==nullptr){                            //  removes that listnode - cases for listnode being in front end or middle of linkedlist
                head = next;
                if(next!=nullptr)
                    next->prev=nullptr;
            }
            else {
                prev->next = next;                        
            }
            if(next==NULL) {
                tail = prev;
                if(prev!=NULL)
                    prev->next=NULL;
            }
            else
                next->prev=prev;
        }
        if(!currListNode) {
            KeyNode* curr = location.second;            
            KeyNode* prev = curr->prev;
            KeyNode* next = curr->next;
            if(prev==NULL) {
                location.first->head = next;           
                next->prev=NULL;
            }
            else if(next==NULL) {
                location.first->tail= prev;
                prev->next=NULL;
            }
            else{
                prev->next=next;
                next->prev=prev;
            }

        }
        ListNode* nextFre;
        if(nextL==NULL) {                          // if next listnode  does not exist create new listnode
            //new freq is created
            nextFre = new ListNode(freq + 1);
            nextFre->prev = tail;
            if(tail!=NULL)
                tail->next=nextFre;
            tail = nextFre;
            if(head==NULL)
                head=nextFre;
        }
        else {
            if(nextL->freq==freq+1)               // if nextnode in the list is not of the numerical next frequency  , create new ListNode
                nextFre = nextL;
            else {
                nextFre = new ListNode(freq + 1);
                ListNode* temp = nextL->prev;
                nextFre->prev = nextL->prev;
                nextL->prev = nextFre;
                nextFre->next=nextL;
                if(temp!=nullptr)//note head
                    temp->next = nextFre;
                else
                    head = nextFre;
            }
        }
        nextFre->add(key,val);                         // add keynode to the end of the list of next frequency listnode 
        cache[key] = make_pair(nextFre,nextFre->tail);
        return val;
    }

int ListNode::get(int key, KeyNode* keynodeLoc) {

        int val = keynodeLoc->value;                    // returns val for the key and removes the node 
        if(keynodeLoc->prev!=nullptr)                   // from the KeyNode  lisnked list of curr frequency
            keynodeLoc->prev->next = keynodeLoc->next;
        if(keynodeLoc->next!=nullptr)
            keynodeLoc->next->prev=keynodeLoc->prev;
        return val;
    }

KeyNode* ListNode::add(int key, int val) {
        if(head==nullptr){
            //new entry
            head = new KeyNode(key,val);               //adds a keynode to the end 
            tail=head;

        }
        else{
            //add to tail of the list
            KeyNode* n = new KeyNode(key,val);
            tail->next = n;
            n->prev = tail;
            tail=n;

        }
        return tail;
    }

void LFUCache::put(int key, int value) {
        if(capacity==0)
            return ;
        if(cache.count(key)){                // if key exists in cache
            pair<ListNode*, KeyNode*> location = cache[key];
            location.second->value=value;
            this->get(key);
           return;
        }
        else {
            if(capacity==cache.size()){    // if cache is full it removes the Least frequently used key 

                this->remove();
                currCapcity--;
            }
            if(head==NULL) {                 // if list is empty creates a new ListNode with frequency 1
                head = new ListNode(1);     
                tail=head;
            }
            else if(head->freq!=1){         // if the first node in the list does not have frequency one add new node to the head of the link list
                ListNode* newHead = new ListNode(1);
                newHead->next=head;
                head->prev=newHead;
                head=newHead;
            }
            //print();
            KeyNode* keynode = head->add(key, value);  // add key,val pair
            currCapcity++;
            cache[key] = make_pair(head,keynode);      // update the cache map
            return;
        }
    }

void LFUCache::remove(){
    int removeKey = head->remove();       // removes the first keynode from the first ListNode in the List and 
    cache.erase(removeKey);               //remove the listnode if after removing the key node the list node becomes empty.
    if(head->head==nullptr) {
        head = head->next;
        if(head!=NULL)
            head->prev=nullptr;
    }
}

void LFUCache::print() {
    ListNode* temp = head;
    //System.out.println("print ");
    cout << "print" << endl;
    while(temp!=NULL){
        KeyNode* temp1 = temp->head;
        cout <<"fre: " << temp->freq <<" [ " << endl;
        while(temp1!=NULL){
            cout << temp1->key  << ":" <<temp1->value <<"\t" << endl;
            temp1=temp1->next;
        }
         cout << " ]" << endl;
         temp=temp->next;
    }
    }

int ListNode::remove() {
        int key = head->key;   // removes the first key from the list node 
        head = head->next;
        if(head!=nullptr)
        head->prev=nullptr;
        return key;
    }





int main(){
    LFUCache* cache= new LFUCache(3);
        cache->put(2,2);
        cache->print();
        cache->put(1,1);
        cache->print();
        cout << "l: 2 -> " << cache->get(2) << endl;
        cache->print();
        //System.out.println("l: 1 -> "+cache.get(1));
        cout << "l: 2 -> " << cache->get(1) << endl;
        cache->print();
        //System.out.println("l: 2 -> "+cache.get(2));
        cout << "l: 2 -> " << cache->get(2) << endl;
        cache->print();
        cache->put(3,3);
        cache->print();
        cache->put(4,4);
        cache->print();
        //System.out.println("l: 3 -> "+cache.get(3));
        cout << "l: 2 -> " << cache->get(3) << endl;
        cache->print();
        //System.out.println("l: 2 -> "+cache.get(2));
        cout << "l: 2 -> " << cache->get(2) << endl;
        cache->print();
        //System.out.println("l: 1 -> "+cache.get(1));
        cout << "l: 2 -> " << cache->get(1) << endl;
        cache->print();
        //System.out.println("l: 4 -> "+cache.get(4));
        cout << "l: 2 -> " << cache->get(4) << endl;
        cache->print();
        return 0;

}
