// Last updated: 8/29/2026, 8:25:49 PM
class LRUCache {
public:
    struct Node{
        int key,value;
        Node *prev,*next;
        Node(int k,int v): key(k), value(v), prev(nullptr), next(nullptr){}
    };

    int totalNodes,capacity;
    unordered_map<int,Node*> mp;
    Node *head,*tail;

    void addNode(Node* node){
        totalNodes++;
        node->next=head->next;
        node->prev=head;

        head->next->prev=node;
        head->next=node;
    }

    void removeNode(Node* node){
        node->prev->next=node->next;
        node->next->prev=node->prev;
        totalNodes--;
    }

    void moveToFront(Node* node){
        removeNode(node);
        addNode(node);
    }

    LRUCache(int capacity) {
        totalNodes=0;
        head = new Node(-1,-1);
        tail = new Node(-1,-1);
        head->next=tail;
        tail->prev=head;
        this->capacity=capacity;
    }
    
    int get(int key) {
        if(mp.find(key)==mp.end()){
            return -1;
        }
        moveToFront(mp[key]);
        return mp[key]->value;
    }
    
    void put(int key, int value) {
        if(mp.find(key)!=mp.end()){
            mp[key]->value=value;
            moveToFront(mp[key]);
            return;
        }
        if(totalNodes==capacity){
            Node *lru=tail->prev;
            mp.erase(lru->key);
            removeNode(lru);
            delete lru;
        }
        Node *newNode = new Node(key,value);
        mp[key]=newNode;
        addNode(newNode);
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */