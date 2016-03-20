// $Id: treemap.java,v 1.1 2012-02-07 15:43:17-08 - - $

// Development version of treemap.
// To be deleted and replaced by an actual implementation that
// does *NOT* use java.util.TreeMap.

import static java.lang.System.*;

class treemap {

   class tree {
      String key;
      String value;
      tree left;
      tree right;
   }
   tree root = null;

   public String get (String key) {
     tree x = search(root, key);
     if (x == null) return null;
     return x.value;
   }

   public tree search(tree curr, String key) {
      if (curr == null) return null;
      if (key.compareTo(curr.key) < 0) {
         return search(curr.left, key);
      } else if (key.compareTo(curr.key) > 0) {
         return search(curr.right, key);
      }
        return curr;
    }

   public String put (String key, String value) {
      if (root == null) {
        tree tmp = new tree();
        tmp.key = key;
        tmp.value = value;
        root = tmp;
        return value;
   }
     return put2(root, key, value);
}
    
   public String put2(tree curr, String key, String value){
      if (curr==null) return null;
      
      if (key.compareTo(curr.key) < 0) {
        if (curr.left == null) {
            tree temp = new tree();
            temp.key = key;
            temp.value = value;
            curr.left = temp;
            return curr.value;
        }else{
            return put2(curr.left, key, value);
        }
     }else if (key.compareTo(curr.key) > 0) {
           if (curr.right == null) {
               tree temp = new tree();
               temp.key = key;
               temp.value = value;
               curr.right = temp;
               return curr.value;
     }else{
        return put2(curr.right, key, value);
        }
     }else {
        String y = curr.value;
        curr.value = value;
        return y;
        }
    }

   public void debug_tree () {
      debug_tree_recur (root, 0);
   }

   private void debug_tree_recur (tree node, int depth) {
   if (node == null) return;
   debug_tree_recur(node.left, depth+1);
 
   out.printf("%3d \"%s\" \"%s\" %s %s%n", depth, node.key,
              node.value, node.left, node.right);

     debug_tree_recur(node.right, depth+1);
 }

}
