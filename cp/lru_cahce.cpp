class LRUCache {
public:
    typedef struct node{
        int key;
        int val;
        struct node* next=NULL;
        struct node* prev=NULL;
    }node;

    node* create_node(int key, int val){
        node* temp = new node();
        temp->val=val;
        temp->key=key;
        return temp;
    }

    int cap;
    unordered_map<int,node*>node_map;
    node* head=create_node(-1,-1);
    node* tail=create_node(-1,-1);
    int size=0;
    
    void insert_node(int key, int value){
        node* temp=create_node(key,value);
        temp->prev=head;
        temp->next=head->next;
        head->next->prev=temp;
        head->next=temp;
        node_map[key]=temp;
    }

    int delete_node(node* temp){
        int k=temp->val;
        temp->prev->next=temp->next;
        temp->next->prev=temp->prev;
        temp->next=NULL;
        temp->prev=NULL;
        node_map[temp->key]=NULL;
        node_map.erase(temp->key);
        temp=NULL;
        free(temp);
        return k;
    }


    LRUCache(int capacity) {
        head->next=tail;
        tail->prev=head;
        cap=capacity;
    }
    
    int get(int key) {
        if (node_map[key]==NULL){
            return -1;
        }
        else{
            int ans=delete_node(node_map[key]);
            insert_node(key,ans);
            return ans;
        }
    }
    
    void put(int key, int value) {
        if(node_map[key]!=NULL){
            delete_node(node_map[key]);
            insert_node(key,value);
        }
        else if(size<cap){
            insert_node(key,value);
            size++;
        }
        else{
            delete_node(tail->prev);
            insert_node(key,value);
        }
        
    }
};