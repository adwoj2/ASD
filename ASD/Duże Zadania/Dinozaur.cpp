#include <iostream>

using namespace std;

typedef struct chunk {
    char letter;
    int length;

}
chunk;

typedef struct node {
    char letter;
    int left_size;
    int right_size;
    chunk left_chunk;
    chunk right_chunk;
    chunk biggest_chunk;
    struct node * left_son;
    struct node * right_son;
    struct node * parent;
    bool reversed;
}
node;

void unpack_reverse(node * root, bool par = true) {
    if (root -> reversed) {        
        node * a = root -> left_son;
        root -> left_son = root -> right_son;
        root -> right_son = a;
        int b = root -> left_size;
        root -> left_size = root -> right_size;
        root -> right_size = b;
        chunk c = root -> right_chunk;
        root -> right_chunk = root -> left_chunk;
        root -> left_chunk = c;
        root -> reversed = false;
        if (root -> left_son != NULL) {
            root -> left_son -> reversed = !root -> left_son -> reversed;
        }
        if (root -> right_son != NULL) {
            root -> right_son -> reversed = !root -> right_son -> reversed;
        }
    }
    if (par) {
        if (root -> right_son != NULL)
            unpack_reverse(root -> right_son, false);
        if (root -> left_son != NULL)
            unpack_reverse(root -> left_son, false);
    }
}

void normalize(node * y) {                                 
    if (y -> left_son != NULL) //poprawienie size                                  
        y -> left_size = y -> left_son -> left_size + y -> left_son -> right_size + 1;
    else
        y -> left_size = 0;                                                
    if (y -> right_son != NULL)
        y -> right_size = y -> right_son -> left_size + y -> right_son -> right_size + 1;
    else
        y -> right_size = 0;

    if (y -> right_son == NULL && y -> left_son == NULL) {
        y -> left_chunk.length = 1;
        y -> left_chunk.letter = y -> letter;
        y -> biggest_chunk = y -> left_chunk;
        y -> right_chunk = y -> biggest_chunk;
        return;
    }
                                            
    if (y -> right_son != NULL) {
        if (y -> right_son -> biggest_chunk.length == y -> right_size) { //prawy syn składa się tylko z jednego rodzaju liter                                          
            if (y -> letter == y -> right_son -> biggest_chunk.letter) {
                y -> right_chunk.letter = y -> letter;
                if (y -> left_son != NULL && y -> left_son -> right_chunk.letter == y -> letter) {
                    y -> right_chunk.length = y -> left_son -> right_chunk.length + y -> right_size + 1;
                } else
                    y -> right_chunk.length = y -> right_size + 1;
            } else {
                y -> right_chunk = y -> right_son -> right_chunk;
            }
        } else {
            y -> right_chunk = y -> right_son -> right_chunk;
        }
    } else {
        if (y -> left_son -> right_chunk.letter == y -> letter) {
            y -> right_chunk.letter = y -> letter;
            y -> right_chunk.length = y -> left_son -> right_chunk.length + 1;
        } else {
            y -> right_chunk.letter = y -> letter;
            y -> right_chunk.length = 1;
        }
    }
                                          
    if (y -> left_son != NULL) {
        if (y -> left_son -> biggest_chunk.length == y -> left_size) { //lewy syn składa się tylko z jednego rodzaju liter                                             
            if (y -> letter == y -> left_son -> biggest_chunk.letter) {
                y -> left_chunk.letter = y -> letter;
                if (y -> right_son != NULL && y -> right_son -> left_chunk.letter == y -> letter) {
                    y -> left_chunk.length = y -> right_son -> left_chunk.length + y -> left_size + 1;
                } else
                    y -> left_chunk.length = y -> left_size + 1;
            } else {
                y -> left_chunk = y -> left_son -> left_chunk;
            }
        } else {
            y -> left_chunk = y -> left_son -> left_chunk;
        }
    } else {
        if (y -> right_son -> left_chunk.letter == y -> letter) {
            y -> left_chunk.letter = y -> letter;
            y -> left_chunk.length = y -> right_son -> left_chunk.length + 1;
        } else {
            y -> left_chunk.letter = y -> letter;
            y -> left_chunk.length = 1;
        }
    }
                                                
    if (y -> left_son != NULL && y -> left_son -> right_chunk.letter == y -> letter) {
        if (y -> right_son != NULL && y -> right_son -> left_chunk.letter == y -> letter) {
            y -> biggest_chunk.letter = y -> letter;
            y -> biggest_chunk.length = y -> right_son -> left_chunk.length + y -> left_son -> right_chunk.length + 1;

        } else {
            y -> biggest_chunk.letter = y -> letter;
            y -> biggest_chunk.length = y -> left_son -> right_chunk.length + 1;

        }
    } else if (y -> right_son != NULL && y -> right_son -> left_chunk.letter == y -> letter) {
        y -> biggest_chunk.letter = y -> letter;
        y -> biggest_chunk.length = y -> right_son -> left_chunk.length + 1;

    } else {
        //co najmniej jeden z synów nie jest NULLem                     
        if (y -> right_son == NULL)
            y -> biggest_chunk = y -> left_son -> biggest_chunk;
        else if (y -> left_son == NULL)
            y -> biggest_chunk = y -> right_son -> biggest_chunk;
        else if (y -> right_son -> biggest_chunk.length > y -> left_son -> biggest_chunk.length)
            y -> biggest_chunk = y -> right_son -> biggest_chunk;
        else
            y -> biggest_chunk = y -> left_son -> biggest_chunk;
    }
    //poprawienie gdyby w którymś z synów był większy fragment niż powstały ze zlepienia elementu w węźle                                                       
    if (y -> right_son != NULL && y -> biggest_chunk.length < y -> right_son -> biggest_chunk.length)
        if (y -> left_son != NULL && y -> left_son -> biggest_chunk.length > y -> right_son -> biggest_chunk.length)
            y -> biggest_chunk = y -> left_son -> biggest_chunk;
        else
            y -> biggest_chunk = y -> right_son -> biggest_chunk;

    if (y -> left_son != NULL && y -> biggest_chunk.length < y -> left_son -> biggest_chunk.length)
        if (y -> right_son != NULL && y -> right_son -> biggest_chunk.length > y -> left_son -> biggest_chunk.length)
            y -> biggest_chunk = y -> right_son -> biggest_chunk;
        else
            y -> biggest_chunk = y -> left_son -> biggest_chunk;                                          
}

void zig(node * x) { // w prawo                                                                                                      
    node * y = x -> parent;
    node * B = x -> right_son;
    x -> right_son = y;
    x -> parent = y -> parent;
    y -> left_son = B;
    if (B != NULL)
        B -> parent = y;
    y -> parent = x;

    if (x -> parent != NULL)
        if (x -> parent -> left_son == y)
            x -> parent -> left_son = x;
        else
            x -> parent -> right_son = x;

    normalize(y);
    normalize(x);
}

void zag(node * y) { // w lewo                                                   
    node * x = y -> parent;
    node * B = y -> left_son;
    y -> left_son = x;
    y -> parent = x -> parent;
    x -> right_son = B;
    if (B != NULL)
        B -> parent = x;
    x -> parent = y;
    if (y -> parent != NULL)
        if (y -> parent -> left_son == x)
            y -> parent -> left_son = y;
        else
            y -> parent -> right_son = y;

    normalize(x);
    normalize(y);
}

void local_splay(node * x) {
    if (x -> parent -> parent == NULL) { //gdyby x->parent == NULL to program nie urchomilby local splay                                                            
        if (x -> parent -> left_son == x)
            zig(x);
        else
            zag(x);
        return;
    }

    bool left = false;
    bool father_left = false;
    if (x == x -> parent -> left_son)
        left = true;
    if (x -> parent -> parent -> left_son == x -> parent)
        father_left = true;
                                   
    if (left && father_left) {
        zig(x -> parent);
        zig(x);
    } else if (!left && !father_left) {
        zag(x -> parent);
        zag(x);                                                        
    } else if (left && !father_left) {
        zig(x);
        zag(x);
    } else if (!left && father_left) {
        zag(x);
        zig(x);
    }                                      
    return;
}

node * splay(node * x, int id) {                                          
    node * root = x;
    unpack_reverse(x);
    while (id != x -> left_size) {
        if (id > x -> left_size) {
            id = id - x -> left_size - 1;
            x = x -> right_son;
        } else
            x = x -> left_son;
        unpack_reverse(x);                                                
    }                                  
    int d = 0;
    while (x -> parent != NULL) {                                            
        local_splay(x);
    }
    return x;
}

node * remove_right_son(node * root) {                                 
    node * right_side = root -> right_son;
    root -> right_son = NULL;
    root -> right_size = 0;
    root -> right_chunk.letter = root -> letter;  

    if (root -> left_son != NULL) {                                                 
        if (root -> left_son -> right_chunk.letter == root -> letter) {
            root -> right_chunk.length = root -> left_son -> right_chunk.length + 1;
            if (root -> right_chunk.length > root -> left_son -> biggest_chunk.length)

                root -> biggest_chunk = root -> right_chunk;
            else
                root -> biggest_chunk = root -> left_son -> biggest_chunk;
            if (root -> biggest_chunk.length == root -> left_size + 1)
                root -> left_chunk = root -> biggest_chunk;
        } else {
            root -> right_chunk.length = 1;
        }
    } else {                                          
        root -> biggest_chunk.letter = root -> letter;
        root -> biggest_chunk.length = 1;
        root -> left_chunk = root -> biggest_chunk;
        root -> right_chunk = root -> biggest_chunk;                                                  
    }
    right_side -> parent = NULL;
    return right_side;
}

void connect_right_son(node * root, node * new_son) {
    root -> right_son = new_son;
    new_son -> parent = root;
    root -> right_size = new_son -> left_size + new_son -> right_size + 1;
    if (new_son != NULL) {
        if (new_son -> biggest_chunk.length == root -> right_size) {
            if (new_son -> biggest_chunk.letter == root -> right_chunk.letter)
                root -> right_chunk.length = root -> right_chunk.length + root -> right_size;
            else {
                root -> right_chunk = new_son -> right_chunk;
                if (root -> right_chunk.length > root -> biggest_chunk.length)
                    root -> biggest_chunk = root -> right_chunk;
                if (root -> biggest_chunk.length == root -> left_size + root -> right_size + 1)
                    root -> left_chunk = root -> biggest_chunk;
            }
        }
    }
    normalize(root);
}

node * move(node * root, int beginning, int end, int dest) {
    root = splay(root, beginning - 1);
    node * fragment = remove_right_son(root);
    fragment = splay(fragment, end - root -> left_size - 1);
                                                
    node * right_side = remove_right_son(fragment); //oderwanie zbednego syna z wezla fragment                                                                                                               
    connect_right_son(root, right_side);
                                
    root = splay(root, dest - 1);                                        
    node * tmp = remove_right_son(root);

    connect_right_son(root, fragment);                                  
    connect_right_son(fragment, tmp); //od wezla fragment oderwano wczesniej prawego syna                                                                                                          
    return root;
}

node * show(node * root, int beginning, int end) {                                                     
    root = splay(root, beginning - 1);                                                   
    node * fragment = remove_right_son(root);                                         
    fragment = splay(fragment, end - root -> left_size);       

    printf("%d\n", fragment -> left_son -> biggest_chunk.length);

    connect_right_son(root, fragment);                                                  
    return root;
}

node * reverse(node * root, int beginning, int end) {
    root = splay(root, beginning - 1);
    node * fragment = remove_right_son(root);
    fragment = splay(fragment, end - root -> left_size);
    fragment -> left_son -> reversed = !fragment -> left_son -> reversed;

    unpack_reverse(fragment);
    normalize(fragment); //znormalizowanie ojca obracanego poddrzewa             

    connect_right_son(root, fragment);
    return root;
}

int main() {
    int n, m;
    cin >> n >> m;
    node code[n + 2];

    for (int i = 1; i <= n; i++) {
        cin >> code[i].letter;
        code[i].reversed = false;                                       
    }
    code[0].letter = 'Q';
    code[0].parent = NULL;
    code[0].reversed = false;
    code[n + 1].letter = 'Q'; //atrapy                                          
    code[n + 1].reversed = false;

    for (int i = 0; i <= n + 1; i++) {
        code[i].left_chunk.letter = code[i].letter;
        code[i].left_chunk.length = 1;
        code[i].right_chunk = code[i].left_chunk;
        code[i].biggest_chunk = code[i].left_chunk;
        code[i].left_size = 0;
        code[i].right_size = 0;
        code[i].left_son = NULL;
        code[i].right_son = NULL;
    }

    node * root = & code[0];

    for (int i = 1; i <= n + 1; i++) {
        code[i - 1].right_son = & code[i];
        code[i].parent = & code[i - 1];
    }
    for (int i = n + 1; i >= 0; i--) {
        normalize( & code[i]);
    }//dodawanie węzłów na koniec i normalizacja

    for (int ii = 0; ii < m; ii++) {                                           
        int j, k;
        char command;
        cin >> command;
        switch (command) {
        case 'O':
            cin >> j >> k;
            root = reverse(root, j, k);
            break;
        case 'P':
            int l;
            cin >> j >> k >> l;
            root = move(root, j, k, l);
            break;
        case 'N':
            cin >> j >> k;
            root = show(root, j, k);
            break;
        };                                                 
    }
    return 0;
}