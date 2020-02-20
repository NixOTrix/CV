import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.File;
import java.util.ArrayList;
import java.io.IOException;

class Main {
    public static int totalBooks;
    public static int totalLibraries;
    public static int totalDays;

    public static boolean[] isBookRead;
    public static int[] bookScore;
    /* ---------------- */
    public static int[] librarySignUp;
    public static int[] libraryBandwidth;
    public static Integer[][] librariesBooks;


    //debug area
    // public static int tester = 0;


    public static void parseHead(String header) {
        String[] headerData = header.split(" ");
        totalBooks = Integer.parseInt(headerData[0]);
        totalLibraries = Integer.parseInt(headerData[1]);
        totalDays = Integer.parseInt(headerData[2]);

        isBookRead = new boolean[totalBooks];
        bookScore = new int[totalBooks];
        /* ---------------- */
        librarySignUp = new int[totalLibraries];
        libraryBandwidth = new int [totalLibraries];
        librariesBooks = new Integer[totalLibraries][];

    }
    public static void parseBookScores(String bookScoresInput) {
        String[] stringbookScore = bookScoresInput.split(" ");
        int i = 0;
        for (String score : stringbookScore){
            bookScore[i] = Integer.parseInt(score);
            i++;
        }
    }
    public static void parseBody(String line1, String line2, int libraryIndex) {
        
        String [] libValues = line1.split(" ");
        // System.out.println("///" + libValues[0] + "///");
        int numOfBooksInLib = Integer.parseInt(libValues[0]);
        librarySignUp[libraryIndex] = Integer.parseInt(libValues[1]);
        libraryBandwidth[libraryIndex] = Integer.parseInt(libValues[2]);



        String [] libBooks = line2.split(" ");
        librariesBooks[libraryIndex] = new Integer[numOfBooksInLib];
        int i = 0;
        for (String book : libBooks){
            librariesBooks[libraryIndex][i] = Integer.parseInt(book);
            i++;
        }

        // System.out.println("TESTER  " + tester + "   TESTER");
        // tester++;

    }
    //public static void parseBody() {
    //}


    public static void main( String[] args ) {
       // data source
       String inputArray[] = {"a_example.txt", "b_read_on.txt", "c_incunabula.txt", "d_tough_choices.txt", "e_so_many_books.txt", "f_libraries_of_the_world.txt"};


        String fileName;
        int lineNumber = 0;
        String header;
        String bookScoreString;
        String body1;
        String body2;
        //int[] code = {};
            
        for (String docName : inputArray){
            fileName = docName;
            try {
                    FileReader fr = new FileReader(fileName);
                    BufferedReader br = new BufferedReader(fr);

                    header = (br.readLine());
                    parseHead( header );
                    bookScoreString = (br.readLine());
                    parseBookScores(bookScoreString);

                    
                    int libraryIndex = 0;
                    while (true){
                        body1 = (br.readLine());
                        if(body1 == null || body1.equals("")){
                            break;
                        }
                        body2 = (br.readLine()); 
                        parseBody(body1, body2, libraryIndex);
                        libraryIndex++;
                    }
                    br.close();


                    // System.out.print(Arrays.deepToString(librariesBooks));
                    // System.out.print(Arrays.toString(librarySignUp));
                    // System.out.print(fileName);
                    
            } catch (IOException e) {
                e.printStackTrace();
            }

            ArrayList<ArrayList<Integer>> solution = solve(totalDays, bookScore, librarySignUp, libraryBandwidth, librariesBooks);

            // for (ArrayList<Integer> library : solution) {
            //     for (Integer i : library) {
            //         System.out.print(i+" ");
            //     }
            //     //System.out.println();
            //     //System.out.println();
            // }
            
            // meta
            StringBuilder output = new StringBuilder();
            output.append(solution.size() + "\n");
            // libraries
            for (ArrayList<Integer> library : solution) {
                if (library.size() < 2)
                    continue;
                
                output.append(library.get(0)+" "+(library.size()-1)+"\n");

                StringBuilder libraryBooksString = new StringBuilder();
                for (int i = 1; i < library.size(); i++) {
                    if (i == library.size()-1) {
                        libraryBooksString.append(library.get(i));
                    } else {
                        libraryBooksString.append(library.get(i)+" ");
                    }
                }
                libraryBooksString.append("\n");
                output.append(libraryBooksString);
            }

            String content = output.toString();

                

            BufferedWriter bw = null;
            try {
                // String[] outname = docName.split(".");
                // System.out.println(outname);
                String outputFilename = docName + "out.txt";
                File file = new File(outputFilename);
                if (!file.exists()) {
                    file.createNewFile();
                }
                FileWriter fw = new FileWriter(file);
                bw = new BufferedWriter(fw);
                bw.write(content);
            
            } catch (IOException e) {
                e.printStackTrace();
            } finally {
                try {
                    if( bw != null ) {
                        bw.close();
                    }
                } catch (Exception ex) {
                    System.out.println("Error closing file: " + ex);
                }
            }
        }
    }

    
    public static ArrayList<ArrayList<Integer>> solve(int days, int[] books, int[] librarySignUp, int[] libraryBandwidth, Integer[][] libraryBooks) {
        ArrayList<ArrayList<Integer>> output = new ArrayList<>();

        boolean[] bookMask = new boolean[books.length];
        boolean[] libraryMask = new boolean[libraryBooks.length];

        for (int i = 0; i < libraryBooks.length; i++) {
            ArrayList<Integer> libList = new ArrayList<>();
            for (int j : libraryBooks[i])
                libList.add(j);

            libList.sort((a, b) -> books[b]-books[a]);
            libraryBooks[i] = libList.toArray(libraryBooks[i]);
        }

        while (days > 0) {

            int bestLibrary = -1;
            int bestLibraryValue = -1;

            for (int i = 0; i < libraryBooks.length; i++) {

                if (!libraryMask[i]) {

                    int possibleBooks = (days - librarySignUp[i]) * libraryBandwidth[i];

                    if (possibleBooks < 0)
                        continue;

                    int libraryValue = 0;
                    for (int j = 0; j < possibleBooks; j++) {
                        if (j >= libraryBooks[i].length)
                            break;
                        if (!bookMask[libraryBooks[i][j]])
                            libraryValue += books[libraryBooks[i][j]];
                    }

                    if (libraryValue > bestLibraryValue) {
                        bestLibrary = i;
                        bestLibraryValue = libraryValue;
                    }

                }

            }

            if (bestLibrary == -1) {
                return output;
            }

            ArrayList<Integer> lib = new ArrayList<>();
            lib.add(bestLibrary);

            int possibleBooks = (days - librarySignUp[bestLibrary]) * libraryBandwidth[bestLibrary];
            for (int i = 0; i < possibleBooks; i++) {
                if (i >= libraryBooks[bestLibrary].length)
                    break;
                if (!bookMask[libraryBooks[bestLibrary][i]]) {
                    lib.add(libraryBooks[bestLibrary][i]);
                    bookMask[libraryBooks[bestLibrary][i]] = true;
                }
            }

            libraryMask[bestLibrary] = true;
            days -= librarySignUp[bestLibrary];

            output.add(lib);
        }

        return output;
    }
}