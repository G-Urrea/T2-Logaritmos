#ifndef FIBO_DOT_H    
#define FIBO_DOT_H 

typedef struct _FIB_EL {
    node v;
    double key;
    int degree;
    struct _FIB_EL *left_sibling;
    struct _FIB_EL *right_sibling;
    struct _FIB_EL *parent;
    struct _FIB_EL *child;
    bool mark;
    bool visited;
} FIB_ELEMENT;

typedef struct fibanocci_heap {
    int n; // tamaño del heap
    int capacity; // capacidad total del heap
    FIB_ELEMENT *min;
    int degree;
    FIB_ELEMENT *map[];
} FIB_HEAP;

FIB_HEAP *make_fib_heap(int capacity, FIB_ELEMENT *map[]);
void insertion(FIB_HEAP *H, FIB_ELEMENT *new_elem, node node_v, double new_key);
FIB_ELEMENT *extract_min(FIB_HEAP *H);

void consolidate(FIB_HEAP *H);
void fib_heap_link(FIB_HEAP *H, FIB_ELEMENT *y, FIB_ELEMENT *x);

FIB_ELEMENT *find_min_node(FIB_HEAP *H);
void decrease_key(FIB_HEAP *H, FIB_ELEMENT *node_to_be_decrease, int new_key);
void cut(FIB_HEAP *H, FIB_ELEMENT *node_to_be_decrease, FIB_ELEMENT *parent_node);
void cascading_cut(FIB_HEAP *H, FIB_ELEMENT *parent_node);
void print_heap(FIB_ELEMENT *n);
void print_fibo(FIB_HEAP *H);

#endif