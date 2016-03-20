// $Id: airport.java,v 1.1 2016-02-14 21:40:55-08 - - $

import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;

class airport {
   private static final String STDIN_FILENAME = "-";

   public static treemap load_database (String database_name) {
      treemap tree = new treemap ();
      try {
         Scanner database = new Scanner (new File (database_name));
         for (int linenr = 1; database.hasNextLine(); ++linenr) {
            String line = database.nextLine();
            if (line.matches ("^\\s*(#.*)?$")) continue;
            String[] keyvalue = line.split (":");
            if (keyvalue.length != 2) {
               misc.warn (database_name, linenr, "invalid line");
               continue;
            }
            tree.put (keyvalue[0].toUpperCase(), keyvalue[1]);
         }
         database.close();
      }catch (IOException error) {
         misc.warn (error.getMessage());
      }
      return tree;
   } 

   public static void main (String[] args) {
        boolean argchk = false; 
        if (args.length == 0 || args.length > 2) {
            err.printf("Usage: airport [-d] database");
            exit(1);
        }
        for (int i = 0; i<args.length; i++) {
            if (args[i].equals("-d")) {
                argchk = true;
            } else if (args[i].substring(0, 1).equals("-")) {
                err.printf("Usage: airport [-d] database");
                exit(1);
            }
        }
      treemap tree = load_database ( argchk ? args[1] : args[0]);
      if (argchk) {
         tree.debug_tree();
         exit(0);
      }
      
      Scanner stdin = new Scanner (in);
      while (stdin.hasNextLine()){
        String line = stdin.nextLine().toUpperCase().trim();
        if (line.matches("^\\s*(#.*)?$")) continue;
        String[] parts = line.split(" ");
        if (parts.length != 1) {
            misc.warn("Invalid line");
            continue;
        }
         String airport = stdin.nextLine().toUpperCase().trim();
         String airport_name = tree.get (airport);
         if (airport_name == null) {
            out.printf ("%s: no such airport%n", airport);
         }else {
            out.printf ("%s = %s%n", airport, airport_name);
         }
      } 
      exit (misc.exit_status);
  }

}
