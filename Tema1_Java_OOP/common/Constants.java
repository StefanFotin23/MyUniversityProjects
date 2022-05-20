package common;

public final class Constants {
    //cream o constanta pt TESTS_PATH, ca sa citim inputul din teste
    public static final String TESTS_PATH = "tests/test";
    public static final String OUTPUT_PATH = "output/out_";
    public static final String REF_PATH = "ref/ref_test";
    public static final String FILE_EXTENSION = ".json";
    public static final Integer SMALL_TEST_POINTS = 2;
    public static final Integer BIG_TEST_POINTS = 3;
    public static final Integer TESTS_NUMBER = 25;
    public static final Integer MAXIMUM_ERROR_CHECKSTYLE = 30;
    public static final Integer CHECKSTYLE_POINTS = 10;
    public static final Integer TESTS_NUMBER_SMALL = 15;

    private Constants() {
        //constructor for checkstyle
    }

}
