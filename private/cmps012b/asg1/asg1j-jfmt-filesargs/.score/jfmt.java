// Manav Sharma msharma7
// Christian Lam ctlam
// $Id: jfmt.java,v 1.5 2016-01-17 20:39:24-08 - - $
//
// Starter code for the jfmt utility.  This program is similar
// to the example code jcat.java, which iterates over all of its
// input files, except that this program shows how to use
// String.split to extract non-whitespace sequences of characters
// from each line.
//

import java.io.*;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;
import static java.lang.System.*;

class jfmt {
   // Static variables keeping the general status of the program.
   public static final String JAR_NAME = get_jarname();
   public static final int EXIT_SUCCESS = 0;
   public static final int EXIT_FAILURE = 1;
   public static int exit_status = EXIT_SUCCESS;
   static int max = 65;
   static int min = 0;
   static boolean option = false;

   // A basename is the final component of a pathname.
   // If a java program is run from a jar, the classpath is the
   // pathname of the jar.
   static String get_jarname() {
      String jarpath = getProperty ("java.class.path");
      int lastslash = jarpath.lastIndexOf ('/');
      if (lastslash < 0) return jarpath;
      return jarpath.substring (lastslash + 1);
   }


   // Formats a single file.
   static void format (Scanner infile) {
        List<String> words = new LinkedList<String>();
        
      // Read each line from the opened file, one after the other.
      // Stop the loop at end of file.
      for (int linenr = 1; infile.hasNextLine(); ++linenr) {
         String line = infile.nextLine();

            if (line.length() == 0) {
                while (line.length() == 0) {
                if (infile.hasNextLine()) {
                line = infile.nextLine();
            }
                else { 
            System.exit(0);
            }
        }
    print_paragraph(words);
  }
         // Split the line into words around white space and iterate
         // over the words.
         for (String word: line.split ("\\s+")) {

            // Skip an empty word if such is found.
            if (word.length() == 0) continue;
            // Append the word to the end of the linked list.
            words.add (word);

         }
      }
        print_paragraph(words);
   }

   static void print_paragraph (List <String> words){
      for (String word: words) {
         if (min == 0) {
            out.printf("%s", word);
            min+= word.length();
            continue;
        }

        if (( min + word.length() + 1 > max)) {
            out.printf("%n");
            out.printf(word);
            min = word.length();
            continue;
     }
     out.printf(" " + word);
     min = min + word.length() +1;
    }
     out.printf("%n%n");
     words.clear();
}

   // Main function scans arguments and opens/closes files.
   public static void main (String[] args) {
      if (args.length == 0) {
         // There are no filenames given on the command line.
         out.printf ("FILE: -%n");
         format (new Scanner (in));
      }else {
         // Iterate over each filename given on the command line.
         for (int argix = 0; argix < args.length; ++argix) {
            String filename = args[argix];

            if (filename.startsWith("-")) {
                max = Integer.parseInt(filename.substring(1));
                continue;
        }

            if (filename.equals ("-")) {
               // Treat a filename of "-" to mean System.in.
               out.printf ("FILE: -%n");
               format (new Scanner (in));
            }else {
               // Open the file and read it, or error out.
               try {
                  Scanner infile = new Scanner (new File (filename));
                  format (infile);
                  infile.close();
               }catch (IOException error) {
                  exit_status = EXIT_FAILURE;
                  err.printf ("%s: %s%n", JAR_NAME,
                              error.getMessage());
               }
            }
         }
      }
      exit (exit_status);
   }

}
