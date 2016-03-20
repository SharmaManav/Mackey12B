// $Id: hello.java,v 1.5 2016-01-14 23:10:56-08 - - $
// Manav Sharma msharma7
class hello{
   public static void main(String[]args){
      if (args.length == 0){
          System.out.println("Hello, World!");
          System.exit(0);
      }else {
           System.err.println("Usage: hello");
           System.exit(1);
       }
   }
}
