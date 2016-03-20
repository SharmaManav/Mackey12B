// $Id: listmap.java,v 1.5 2013-10-16 17:10:32-07 - - $

import java.util.Iterator;
import java.util.Map.Entry;
import java.util.NoSuchElementException;
import static java.lang.System.*;

class listmap implements Iterable<Entry<String,intqueue>> {

   private class node implements Entry<String,intqueue> {
      String key;
      intqueue queue = new intqueue();
      node link;
      public String getKey() {
         return key;
      }
      public intqueue getValue() {
         return queue;
      }
      public intqueue setValue (intqueue queue) {
         throw new UnsupportedOperationException();
      }
   }
   private node head = null;

   public listmap() {
      // Not needed, since head defaults to null anyway.
   }

   public void insert (String key, int linenr) {
      //misc.trace ("insert", key, linenr);
      //FIXME
      Entry<String,intqueue> entry;
      node curr = head;
      node prev = null;
      int comp = 1;
      while (curr != null) {
        comp = curr.key.compareTo(key);
        if (comp >= 0) break;
        prev = curr;
        curr = curr.link;
     }

      if (comp != 0) {
        node tmp = new node ();
        tmp.key = key;
        tmp.link = curr;
        if (prev == null) {
            head = tmp;
        } else {
        prev.link = tmp; 
   }
}
     if (prev == null) {
        head.queue.insert(linenr);
     } else {
       prev.link.queue.insert(linenr);
  }
}
   public Iterator<Entry<String,intqueue>> iterator() {
      return new iterator();
   }


   private class iterator
           implements Iterator<Entry<String,intqueue>> {
      node curr = head;

      public boolean hasNext() {
         return curr != null;
      }

      public Entry<String,intqueue> next() {
         if (curr == null) throw new NoSuchElementException();
         node next = curr;
         curr = curr.link;
         return next;
      }

      public void remove() {
         throw new UnsupportedOperationException();
      }

   }

}
