
/*
 * Predecessor
 *  Node with the key immediately before current key (largest key less than me)
 * Successor
 *  Smallest key thats greater than me
 *
 *  these are important for implementing iterators
 *  allow us to write for loops with keys
 *  
 *  How can we implement these?
 *  Successor -> If a right subtree exists
 *                  -> Right Child's smallest element (keep going left until there are no more left
 *                     children)
 *               If you don't have a right subtree
 *                  -> Keep checking parents until you find a parent value greater than the current
 *                     value
 *  Predecessor -> 
 */


struct Node {
    pair<k,v> data;
    Node* left;
    Node* right;
    Node* parent;
}
