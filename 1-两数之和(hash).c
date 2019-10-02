struct hash_node{
    struct hash_node * next;
    int key;
    int value;
};

struct hash_table{
    struct hash_node ** head;
    int size;
};

int hash_table_init(struct hash_table * table, int size){
    //alloc table array and set 0
    struct hash_node ** tmp = malloc(sizeof(struct hash_node*) * size );
    if(tmp == NULL)
        return -1;
    table->head = tmp;

    memset(table->head, 0, sizeof(struct hash_node *) * size);
    table->size = size;

    return 0;
}


void hash_table_free(struct hash_table * table){
    if(table->head != NULL){
        struct hash_node *this, *tmp;
        for(int i=0; i < table->size; ++i){
            this = table->head[i]; // head node
            while(this != NULL){
                tmp = this->next;
                free(this);
                this = tmp;    
            }
        }

        free(table->head);
    }
}

int hash_table_findloc(struct hash_table * table, int key){
    return (abs(key) % (table->size));        
}

/*add a hash node to the next pos of concrete entry head*/
int hash_table_insert(struct hash_table * table, int key, int value){
    int pos =  hash_table_findloc(table, key);
    struct hash_node * entry_head = table->head[pos];
    struct hash_node * in_node = malloc(sizeof(struct hash_node));
    if(in_node == NULL)
        return -1;

    in_node->key = key;
    in_node->value = value;

    in_node->next = table->head[pos];
    table->head[pos] = in_node;

    return 0;
}


int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int * res = malloc(sizeof(int) * 2);
    if(res == NULL)
        return NULL;
    *returnSize = 2;

    /*construct&init a table*/
    struct hash_table * table = malloc(sizeof(struct hash_table));
    if(table == NULL)
        return NULL;
    hash_table_init(table, 20);

    int left_value;
    int table_index;
    struct hash_node * tmp;
    for(int i=0; i < numsSize; ++i){
        left_value = target - nums[i];  
        /*search if there are values that matches the left_value in the table */
        table_index = hash_table_findloc(table, left_value);
        tmp = table->head[table_index];
        /*continue to traverse the chain*/
        while(tmp != NULL){
            if((tmp->key == left_value) && (tmp->value != i)){
                res[0] = tmp->value;
                res[1] = i;
                return res;
            }
            
            tmp = tmp->next;
        }
        hash_table_insert(table, nums[i], i);
        
    }

    return NULL;
}