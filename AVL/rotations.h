void rotateLeft(Node* A) {
    //See diagram in lecture notes
    auto B = A -> right;
    auto Y = B -> left;
    //X and Z do not change
    
    //Step 1: Make A the left child of B
    B -> left = A;
    auto P = A -> parent; //It's fine if this is a nullptr
    A -> parent = B; //this will lose a's parent (line before this retains that data)
    //TODO instead of "auto P..." can you just say "B -> parent = A -> parent"?


    //Step 2: Make Y the right child of A
    A -> right = Y;
    if (Y != nullptr) Y -> parent = A; //Seg fault if Y is a nullptr

    //Step 3: Make P the parent of B
    if (P == nullptr) root = B; //TODO add AVL memeber "root"
    else if (P -> left == A) P -> left = B;
    else P -> right = B;
    B -> parent = P;

    //Step 4: Update height
    updateHeight(A);
}

void rotateRight(Node* B) {
    auto A = B -> left;
    auto Y = A -> right;

    //TODO swap lefts and rights from rotateLeft
}

void updateHeight(Node* node) {
    //Assume that each child already has the correct height
    //Maybe useful for bugs: if(abs(getHeight(node -> left) - getHeight(node -> right)) > 1) bad
    node -> height = std::max(getHeight(node -> left), getHeight(node -> right)) + 1;
    if (node -> parent != nullptr) updateHeight(node -> parent);
}

int getHeight(Node* A){
    if (A == nullptr) return 0;
    else return A -> height;
}

void updateSize(Node* n) {
    int l;
    int r;
    if (n -> left != nullptr)  l = n -> left  -> size else l = 0; //TODO (-> size or .size?)
    if (n -> right != nullptr) r = n -> right -> size else r = 0;
    n.size = l + r + 1;
    if (n -> parent != nullptr) updateSize(n -> parent);
}